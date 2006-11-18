cle// fxfont.cpp : implementation of the CFxFont classes
//		subroutines for character i/o using fonts


#include "stdafx.h"
#include "audtest.h"

#include "fxfont.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CFxFont, CObject, VERSIONABLE_SCHEMA | 237)


/////////////////////////////////////////////////////////////////////////////
// CFxFont construction/destruction
static LOGFONT base_lf = {14,0,0,0,400,FALSE,FALSE,FALSE,ANSI_CHARSET,
			  OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
			  PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE , "Arial"};

CFxFont::CFxFont() : m_csStyleName()
{
					// TODO: add one-time construction code here
	m_lFont = base_lf;
	m_nHeight = 100;			// 10 point by default
	SetEffect( 0);
	SetColor( RGB(0,0,0));
	m_cfCurrent = NULL;
	m_cfCurrentPrint = NULL;
	m_cfCurrentVert = NULL;
	m_cfCurrentPrintVert = NULL;
}

CFxFont::~CFxFont()
{
	clear_Fonts();
}

/////////////////////////////////////////////////////////////////////////////
// CFxFont serialization

void CFxFont::Serialize(CArchive& ar)
{
DWORD dw;

	CObject::Serialize( ar);

	if (ar.IsStoring())
		{
		ar.Write( &m_lFont, sizeof(LOGFONT));
		ar << m_rgbFont;
		dw = (DWORD )m_nHeight; ar << dw;			// height in 10ths of a point
		ar << m_csStyleName;		// name of the style
		}
	else
		{
		ar.Read( &m_lFont, sizeof(LOGFONT));
		ar >> m_rgbFont;
		ar >> dw; m_nHeight = (int )dw;			// height in 10ths of a point
		ar >> m_csStyleName;		// name of the style
		clear_Fonts();
		}

}


int   CFxFont::EditProperties(CWnd *pWnd )	// bring up properties dbox
{
CFontDialog	cfd( &m_lFont, CF_TTONLY | CF_BOTH | CF_EFFECTS | CF_INITTOLOGFONTSTRUCT | CF_USESTYLE, NULL, pWnd);
int nret;
char szstyle[200];

	strcpy( szstyle, (LPCSTR )m_csStyleName);
	cfd.m_cf.lpszStyle = szstyle;
	cfd.m_cf.rgbColors = m_rgbFont;
	nret = cfd.DoModal();
	if ( IDOK == nret)
		{
		m_lFont = *cfd.m_cf.lpLogFont;
		m_rgbFont = (COLORREF )cfd.m_cf.rgbColors;
		m_nHeight = cfd.GetSize();
		m_csStyleName = cfd.GetStyleName();
		clear_Fonts();
		}

	return nret;

}

void CFxFont::ClearPrinterFonts( void)
{
	if ( m_cfCurrentPrint)
		{
		delete m_cfCurrentPrint;
		m_cfCurrentPrint = NULL;
		}
	if ( m_cfCurrentPrintVert)
		{
		delete m_cfCurrentPrintVert;
		m_cfCurrentPrintVert = NULL;
		}
}

void CFxFont::clear_Fonts( void)
{
	ClearPrinterFonts();
	if ( m_cfCurrent)		// this guy has changed, delete the font
		{
		delete m_cfCurrent;
		m_cfCurrent = NULL;
		}
	if ( m_cfCurrentVert)		// this guy has changed, delete the font
		{
		delete m_cfCurrentVert;
		m_cfCurrentVert = NULL;
		}
}



// -----------------------------------------------------------
//			GetCurrentFont
// this returns the current font. do not delete the pointer
// -----------------------------------------------------------
CFont *CFxFont::GetCurrentFont(CDC *pDC)
{
					// if we have a valid font, use it
	if ( pDC->IsPrinting())
		{
		if ( m_cfCurrentPrint)
			return m_cfCurrentPrint;
		}
	else
		if ( m_cfCurrent)
			return m_cfCurrent;

CFont *cnew = new CFont();
	if ( ! cnew)
		return NULL;

CSize cs = pDC->GetWindowExt();			// get the window extent to test for a network (kludge)

	if ( pDC->IsPrinting() && (800 == cs.cx) )// we're printing and it's a network
		{
		int npixy = 100;			// acting like 100 dots per inch for the print
		int nheight = (m_nHeight * npixy) / 720;	// nheight in 1/10 pts
		LOGFONT lnew = m_lFont;

			lnew.lfHeight = -nheight;		// make it right
			lnew.lfWidth = 0;				// use aspect ratio
			cnew->CreateFontIndirect( &lnew);
	
		}
	else
		{
		int npixy = pDC->GetDeviceCaps( LOGPIXELSY);
		int nheight = (m_nHeight * npixy) / 720;	// nheight in 1/10 pts
		LOGFONT lnew = m_lFont;

			lnew.lfHeight = -nheight;		// make it right (in pixels)
			lnew.lfWidth = 0;				// use aspect ratio
			cnew->CreateFontIndirect( &lnew);
	
		}

	if ( ! cnew->GetSafeHandle())		// something failed
		{
		delete cnew;
		cnew = NULL;
		}

	if ( pDC->IsPrinting())
		m_cfCurrentPrint = cnew;
	else
		m_cfCurrent = cnew;

	return cnew;
}


// -----------------------------------------------------------
//			GetCurrentVert
// this returns the current font. do not delete the pointer
// -----------------------------------------------------------
CFont *CFxFont::GetCurrentVert(CDC *pDC)
{
					// if we have a valid font, use it
	if ( pDC->IsPrinting())
		{
		if ( m_cfCurrentPrintVert)
			return m_cfCurrentPrintVert;
		}
	else
		if ( m_cfCurrentVert)
			return m_cfCurrentVert;

CFont *cnew = new CFont();

	if ( ! cnew)
		return NULL;

LOGFONT lnew = m_lFont;

	lnew.lfEscapement = 900;					// go vertical
	lnew.lfOrientation = 0;

CSize cs = pDC->GetWindowExt();			// get the window extent to test for a network (kludge)

	if ( pDC->IsPrinting() && (800 == cs.cx) )// we're printing and it's a network
		{
		int npixy = 100;			// fixed at 100 dpi
		int nheight = (m_nHeight * npixy) / 720;	// nheight in 1/10 pts

			lnew.lfHeight = -nheight;		// make it right
			lnew.lfWidth = 0;				// use aspect ratio
			cnew->CreateFontIndirect( &lnew);
		}
	else
		{
		int npixy = pDC->GetDeviceCaps( LOGPIXELSY);
		int nheight = (m_nHeight * npixy) / 720;	// nheight in 1/10 pts

			lnew.lfHeight = -nheight;		// make it right
			lnew.lfWidth = 0;				// use aspect ratio
			cnew->CreateFontIndirect( &lnew);
		}

	if ( ! cnew->GetSafeHandle())		// something failed
		{
		delete cnew;
		cnew = NULL;
		}

	if ( pDC->IsPrinting())
		m_cfCurrentPrintVert = cnew;
	else
		m_cfCurrentVert = cnew;

	return cnew;
}


void CFxFont::SetCurrentFont( CFont *cfNew)
{
	if ( cfNew)
		{
		cfNew->GetObject( sizeof(LOGFONT) , &m_lFont);
		}
	clear_Fonts();
}


void CFxFont::GetPrettyName(CString& csDest)
{
char szout[200];
	
		sprintf( szout, "%s %s %dpt", m_lFont.lfFaceName, (LPCSTR )m_csStyleName, m_nHeight/10);

		csDest = szout;
}

void CFxFont::GetFontName(CString& csDest)
{
	csDest = m_lFont.lfFaceName;
}

void CFxFont::GetFontStyle(CString& csDest )
{
	csDest = m_csStyleName;
}


int	 CFxFont::GetFontSize()
{
	return m_nHeight;
}


CFxFont &CFxFont::operator=(const CFxFont &cIn)
{

	m_lFont = cIn.m_lFont;
	m_rgbFont = cIn.m_rgbFont;
	m_wEffect = cIn.m_wEffect;
	m_nHeight = cIn.m_nHeight;
	m_csStyleName = cIn.m_csStyleName;
	clear_Fonts();

	return *this;
}


int CFxFont::DrawString( CDC *pDC, LPCTSTR lpszString, LPRECT lpRect, UINT nFormat )
{
CFont *cold, *cnew;
int nout;
COLORREF rgbold;

	cnew = GetCurrentFont( pDC);

	if ( ! cnew)
		{
		_ASSERT(0);		// whoops
		return 1;		// couldn't create font
		}

	cold = pDC->SelectObject( cnew);			// use the new font
	rgbold = pDC->SetTextColor( GetColor());
	nout = pDC->DrawText( lpszString, -1, lpRect, nFormat);
	pDC->SelectObject( cold);					// put it back
	pDC->SetTextColor( rgbold);

	return nout;
}


int CFxFont::DrawStringVertical( CDC *pDC, LPCTSTR lpszString, LPRECT lpRect, UINT nFormat )
{
CFont *cold, *cnew;
RECT rcnew = *lpRect;
int nout;
RECT rcdraw;
COLORREF rgbold;

	cnew = GetCurrentVert( pDC);

	if ( ! cnew)
		{
		_ASSERT(0);		// bad bad
		return 1;
		}

	if ( nFormat & DT_CALCRECT)	// just return size information
		{
		cold = pDC->SelectObject( cnew);			// use the new font
		nout = pDC->DrawText( lpszString, -1, &rcnew, DT_LEFT | DT_TOP | DT_CALCRECT);	// this will give us the rect???
		pDC->SelectObject( cold);					// put it back
		*lpRect = rcnew;
		return nout;
		}

	cold = pDC->SelectObject( cnew);			// use the new font
	rgbold = pDC->SetTextColor( GetColor());
	nout = pDC->DrawText( lpszString, -1, &rcnew, DT_LEFT | DT_TOP | DT_CALCRECT);	// this will give us the rect???
					// oddly enough, calcrect here works sideways and returns dx,dy = (dy,dx)
	rcdraw = *lpRect;
	if ( nFormat & DT_VCENTER)			// vertical centering
		{
		rcdraw.bottom = (rcdraw.bottom + rcdraw.top) /2 + (rcnew.right - rcnew.left) /2;
		nFormat = (nFormat & ~DT_VCENTER) | DT_BOTTOM;
		}
	else if (nFormat & DT_BOTTOM)		// this just works
		{
		}
	else								// DT_TOP ( == 0)
		{
		rcdraw.bottom = rcdraw.top + rcnew.right - rcnew.left;
		nFormat = (nFormat & ~DT_TOP) | DT_BOTTOM;
		}
	if ( nFormat & DT_LEFT)
		{
		}
	else if (nFormat & DT_RIGHT)
		{
		rcdraw.left = rcdraw.right - (rcnew.bottom - rcnew.top);
		nFormat = (nFormat & ~DT_RIGHT) | DT_LEFT;
		}
	else							// horizontal centering
		{
		rcdraw.left =(rcdraw.right + rcdraw.left)/2 - (rcnew.bottom - rcnew.top) / 2;
		nFormat = (nFormat & ~DT_CENTER) | DT_LEFT;
		}
	nout = pDC->DrawText( lpszString, -1, &rcdraw, nFormat | DT_NOCLIP);						// draw it
	pDC->SelectObject( cold);					// put it back
	pDC->SetTextColor( rgbold);

	return nout;

}


// -------------------------------------------------------------------------
//			Registry Functions
// -------------------------------------------------------------------------

typedef struct tagFXFONTINFO
{
	LOGFONT		lFont;
	COLORREF	rgb;
	int			nHeight;
	WORD		wEffect;			// not yet used
	char		szStyle[30];		// random max???
} FXFONTINFO;


void CFxFont::ReadIni( UINT nName)
{
FXFONTINFO finfo;
UINT idcs[NUMFONTTYPES] = { IDS_CHARTTITLE, IDS_CHARTSUBTITLE, IDS_CHARTAXISTITLE, IDS_CHARTSCALE, IDS_CHARTLEGEND, IDS_NETDATA, IDS_NETLEGEND, IDS_SUMMARY, IDS_NOTEFONT };
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( ! capp->ReadRegistry(idcs[nName], &finfo, sizeof(finfo)))
		{
		m_lFont = finfo.lFont;
		m_rgbFont = finfo.rgb;
		m_nHeight = finfo.nHeight;
		m_csStyleName = finfo.szStyle;		// make it a cstring
		clear_Fonts();
		}

}


void CFxFont::WriteIni( UINT nName)
{
FXFONTINFO finfo;
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
UINT idcs[NUMFONTTYPES] = { IDS_CHARTTITLE, IDS_CHARTSUBTITLE, IDS_CHARTAXISTITLE, IDS_CHARTSCALE, IDS_CHARTLEGEND, IDS_NETDATA, IDS_NETLEGEND, IDS_SUMMARY, IDS_NOTEFONT };

	finfo.lFont = m_lFont;
	finfo.rgb = m_rgbFont;
	finfo.nHeight = m_nHeight;
	strcpy( finfo.szStyle, (LPCSTR )m_csStyleName);

	capp->WriteRegistry(idcs[nName], &finfo, sizeof(finfo));

}

