// DataTag.cpp: implementation of the CDataTag class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "audtest.h"
#include "DataTag.h"
#include "math.h"

#include "Utils.h"

#include "Chart.h"
#include "Dataset.h"
#include "DlgNote.h"

// for printerdc stuff
#include <afxpriv.h>

// the scaling factor for the virtual coords
#define TAGSCALE 10000


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

IMPLEMENT_SERIAL(CDataTag, CDrawObj,VERSIONABLE_SCHEMA |  100)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataTag::CDataTag() : m_strText(""), m_cpTextOffset(100,0)
{
	m_pParent = NULL;
	m_iDataset = -1;
}

CDataTag::CDataTag( CDataTag &cTag)
{
	CDataTag::CDataTag();
	*this = cTag;
}


CDataTag::~CDataTag()
{

}

/////////////////////////////////////////////////////////////////////////////
// CDataTag serialization
/////////////////////////////////////////////////////////////////////////////

void CDataTag::Serialize(CArchive& ar)
{
WORD w;

	CDrawObj::Serialize( ar);

	if ( ar.IsStoring())
	{
		ar << m_iDataset;
		ar << m_fXValue ;
		ar << m_strText ;
		ar << m_iLineWeight;
		ar << m_iLineStyle;
		w = (WORD )(m_bDrawLine ? 1 : 0); ar << w;
		w = (WORD )(m_bDrawBox ? 1 : 0); ar << w;
		w = (WORD )(m_bFillBox ? 1 : 0); ar << w;
		ar << m_rgbBoxColor;
	}
	else
	{
		ar >> m_iDataset;
		ar >> m_fXValue;
		ar >> m_strText;
		ar >> m_iLineWeight;
		ar >> m_iLineStyle;
		ar >> w; m_bDrawLine = w ? true : false;
		ar >> w; m_bDrawBox = w ? true : false;
		ar >> w; m_bFillBox = w ? true : false;
		ar >> m_rgbBoxColor;
	}

	m_cfFont.Serialize( ar);
}


// ---------------------------------------------------------------------------
//		Operators
// ---------------------------------------------------------------------------
CDataTag &CDataTag::operator=(const CDataTag &cIn)
{ 					// don't copy the id #
	CDrawObj::operator=( cIn);

	m_iDataset = cIn.m_iDataset;
	m_fXValue = cIn.m_fXValue;
	m_strText = cIn.m_strText;
	m_pParent = cIn.m_pParent;
	m_cpTextOffset = cIn.m_cpTextOffset;
	m_bDrawLine = cIn.m_bDrawLine;
	m_iLineWeight = cIn.m_iLineWeight;
	m_iLineStyle = cIn.m_iLineStyle;
	m_bDrawBox = cIn.m_bDrawBox;
	m_bFillBox = cIn.m_bFillBox;
	m_rgbBoxColor = cIn.m_rgbBoxColor;
	m_cfFont = cIn.m_cfFont;

 	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// CDataTag diagnostics
/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
void CDataTag::AssertValid() const
{
	CDrawObj::AssertValid();
}

void CDataTag::Dump(CDumpContext& dc) const
{
	CDrawObj::Dump(dc);
}

#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
// CDataTag methods
/////////////////////////////////////////////////////////////////////////////

// Get Set stuff

// ---------------------------------------------------------------------------
//		SetParent
// ---------------------------------------------------------------------------
void	CDataTag::SetParent( CSubChart *pParent)
{
	m_pParent = pParent;
}


// ---------------------------------------------------------------------------
//		SetDataset
// ---------------------------------------------------------------------------

void CDataTag::SetDataset( int iNew)
{
	m_iDataset = iNew;
}

// ---------------------------------------------------------------------------
//		SetText
// ---------------------------------------------------------------------------
void CDataTag::SetText( LPCSTR strText)
{
	m_strText = strText;
}

// ---------------------------------------------------------------------------
//		SetValue
// ---------------------------------------------------------------------------
void CDataTag::SetValue( float fNew)
{
	m_fXValue = fNew;
}

// ---------------------------------------------------------------------------
//		GetDataPointer
// set the text offset in client cooords
// ---------------------------------------------------------------------------
CDataSet *CDataTag::GetDataPointer( void)
{
CDataSet *pdata;

	if ( ! m_pParent)
		return NULL;

	if ( m_iDataset > m_pParent->GetDataCount())
		m_iDataset = 0;			// bail out here

	pdata = m_pParent->GetDatasetAt( m_iDataset);

	return pdata;
}

// ---------------------------------------------------------------------------
//		SetTextOffset
// set the text offset in client cooords
// ---------------------------------------------------------------------------
void	CDataTag::SetTextOffset( const CPoint &cPoint)
{
CDataSet *pdata;
POINT ptloc;				// where the data point is
float fx, fy;
CGrid *pgrid;
CRect rcdraw;

	pdata = GetDataPointer();
	if ( ! pdata)
		return;			// yuck

	fx = (float )(cPoint.x - m_pParent->ConvertCoord( ecXCoord, m_fXValue)); // in screen coords
	fy = (float )(cPoint.y - m_pParent->ConvertCoord( ecYCoord, pdata->DataValueAt( m_fXValue))); // in screen coords

			// now fx and fy are in screen coords
	pgrid = m_pParent->GetGrid( ecXCoord);		// get the xgrid
	pgrid->GetDrawRect( rcdraw);
	fx /= rcdraw.Width();
	pgrid = m_pParent->GetGrid( ecYCoord);		// get the xgrid
	pgrid->GetDrawRect( &rcdraw);
	fy /= rcdraw.Height();

	// now fx and fy are relative to the screen coords
	ptloc.x = (int )(fx * TAGSCALE);
	ptloc.y = (int )(fy * TAGSCALE);

	m_cpTextOffset = ptloc;

}



/////////////////////////////////////////////////////////////////////////////
//	Other Methods
/////////////////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------------
//		EditProperties
//			bring up properties dbox
// ---------------------------------------------------------------------------
int CDataTag::EditProperties(CWnd *pParent)
{
CDlgNote cdlg( pParent);

	if ( ! m_pParent)
		return 2;

	if ( m_iDataset < 0)		// we're a newbie
	{
		m_iDataset = 0;
		cdlg.m_bNewObject = true;
	}

	cdlg.SetChart( m_pParent);
	cdlg.m_iDataset =	m_iDataset;		// start with 0th dataset
	cdlg.m_strText =	m_strText;
	cdlg.m_fValue =		m_fXValue;
	cdlg.m_bDrawBox =	m_bDrawBox ? TRUE : FALSE;
	cdlg.m_bDrawLine =	m_bDrawLine ? TRUE : FALSE;
	cdlg.m_bFillBox =	m_bFillBox ? TRUE : FALSE;
	cdlg.m_rgbFillColor = m_rgbBoxColor;
	cdlg.m_cfFont =		m_cfFont;
	cdlg.m_iLineStyle = m_iLineStyle;
	cdlg.m_iLineWeight =m_iLineWeight;


	if ( IDOK == cdlg.DoModal())
	{			// change the object
		m_iDataset =	cdlg.m_iDataset;
		m_strText =		cdlg.m_strText;
		m_fXValue =		cdlg.m_fValue;
		m_bDrawBox =	cdlg.m_bDrawBox ? true : false;
		m_bDrawLine =	cdlg.m_bDrawLine ? true : false;
		m_bFillBox =	cdlg.m_bFillBox ? true : false;
		m_rgbBoxColor = cdlg.m_rgbFillColor;
		m_cfFont =		cdlg.m_cfFont;
		m_iLineStyle =  cdlg.m_iLineStyle;
		m_iLineWeight = cdlg.m_iLineWeight;
		return 0;
	}

	return 1;

}	

// ------------------------------------------------------------------
//		set_ClipRect
//			this is from Microsoft sample code
// ------------------------------------------------------------------
static set_ClipRect(CDC *pDC, CRect &cRect)
{
CRgn rgn;
CRect rectClip = cRect;

// Function to compute the clipping rectangle regardless of
// whether we are in print preview mode. This would be the
// function in your code which computes this rectangle and
// stores it in rectClip

// Now if we are in print preview mode then the clipping
// rectangle needs to be adjusted before creating the
// clipping region
if (pDC->IsKindOf(RUNTIME_CLASS(CPreviewDC)))
    {
    CPreviewDC *pPrevDC = (CPreviewDC *)pDC;

    pPrevDC->PrinterDPtoScreenDP(&rectClip.TopLeft());
    pPrevDC->PrinterDPtoScreenDP(&rectClip.BottomRight());

    // Now offset the result by the viewport origin of
    // the print preview window...

    CPoint ptOrg;
     ::GetViewportOrgEx(pDC->m_hDC,&ptOrg);
    rectClip += ptOrg;
    }

// The following two function calls are the ones that
// select the clipping region into the DC. These would be
// whatever code you already have to create/select the
// clipping region

	rgn.CreateRectRgn(rectClip.left,rectClip.top, rectClip.right,rectClip.bottom);
	pDC->SelectClipRgn(&rgn);

// Other OnDraw code goes here
} 

// ---------------------------------------------------------------------------
//		DoDraw
// ---------------------------------------------------------------------------
void CDataTag::DoDraw( CDC *pDC, LPCRECT lprcDraw)
{
CRect crTotal = *lprcDraw;
CRect crtext = *lprcDraw;
CString strdraw;
POINT ptstart, ptend;
CDataSet *pdata;
CGrid *pgrid;
CGdiObject *cboldfill;
CGdiObject *cboldpen;
CFont *cfold;
CFont *cfont;

				// ------------------ ensure things are copacetic
	if ( ! m_pParent)
	{
		ASSERT(0);
		return;					// we don't have a parent yet
	}

	pgrid = m_pParent->GetGrid( ecXCoord);
	if ( (m_fXValue < pgrid->GetMin()) || (m_fXValue > pgrid->GetMax()) )
		return;			// out of range of this chart

	set_ClipRect( pDC, crTotal);	// clip the tag display

	cfont = m_cfFont.GetCurrentFont( pDC);		// set the typeface
	cfold = pDC->SelectObject( cfont);

				// ------------------  parse the string
	ParseString( strdraw, m_strText);

	if ( ! strdraw.IsEmpty())		// if we have something to draw, find the size
		pDC->DrawText( strdraw, crtext, DT_CALCRECT | DT_LEFT | DT_NOPREFIX );	// get the rectangle

				// ------------------  find the spot to draw from
	ptstart.x = m_pParent->ConvertCoord(ecXCoord, m_fXValue);
	pdata = GetDataPointer();						// get the dataline Y value
	if ( ! pdata)
		return;										// there are no datasets
	{
		float fvalue = pdata->DataValueAt( m_fXValue);		// check Y in range
		pgrid = m_pParent->GetGrid( ecYCoord);
		if ( (fvalue < pgrid->GetMin()) || (fvalue > pgrid->GetMax()) )
			return;			// out of range of this chart
		ptstart.y = m_pParent->ConvertCoord(ecYCoord, fvalue);		// get ptstart.y
	}

					// use m_crText to position this guy
	crtext.OffsetRect( -crtext.TopLeft() );		// move to 0,0
					// offset by screen coords
	ptend.x = ptstart.x + m_cpTextOffset.x * crTotal.Width() / TAGSCALE;
	ptend.y = ptstart.y + m_cpTextOffset.y * crTotal.Height() / TAGSCALE;
	crtext.OffsetRect( ptend.x, ptend.y );		// now crtext points to the rectangle to draw

	//		------------------------------ draw the line/arrow
	if ( m_bDrawLine)
	{
	CPen cp;
	int imin;
	CPoint ptclose;
	POINT pts[4];
	CPoint ptdiff, pt45;
						// ----------  build / select the pen
		cp.CreatePen( m_iLineStyle, m_iLineWeight, RGB(0,0,0));
		cboldpen = pDC->SelectObject( &cp);	// select the pen
						// find the closest point
		{
		POINT tstpts[4];
		double ddist[4];
		double dmin;
		int i;

			tstpts[0].x = crtext.TopLeft().x;
			tstpts[0].y = (crtext.TopLeft().y + crtext.BottomRight().y) / 2;	// average spot
			tstpts[1].x = (crtext.TopLeft().x + crtext.BottomRight().x) / 2;
			tstpts[1].y = crtext.TopLeft().y;
			tstpts[2].x = crtext.BottomRight().x;
			tstpts[2].y = tstpts[0].y;
			tstpts[3].x = tstpts[1].x;
			tstpts[3].y = crtext.BottomRight().y;
							// now pts is the 4 midpoints we connect to
			for ( i=0; i<4; i++)
				ddist[i] = ( tstpts[i].x - ptstart.x) * ( tstpts[i].x - ptstart.x) +
							( tstpts[i].y - ptstart.y) * ( tstpts[i].y - ptstart.y);		// point distance
			dmin = 10000000.0;
			for ( i=0; i<4; i++)
				if ( dmin > ddist[i])
					dmin = ddist[i];
			for ( i=0; i<4; i++)
				if ( dmin == ddist[i])
					break;				// stop at the equals one
			imin = i;					// now imin is the closest point
			ptclose = tstpts[imin];
		}
									// now draw an arrow from data point to ptclose
		ptdiff = ptclose - ptstart;		// delta x and y
		pt45.x = abs( ptdiff.x);
		pt45.y = abs( ptdiff.y);

		if ( pt45.x > pt45.y )			// more X than Y
		{
			pt45.x = (ptdiff.x > 0) ? pt45.y : -pt45.y;		// keep sign the same
			pt45.y = ptdiff.y;
		}
		else
		{
			pt45.y = (ptdiff.y > 0) ? pt45.x : -pt45.x;		// keep sign the same
			pt45.x = ptdiff.x;
		}
					// now pt45 is the 45 degree line portion
		ptdiff -= pt45;			// now ptdiff is the leftover
		if ( (ptdiff.y && (imin==0 || imin == 2)) || (ptdiff.x && (imin==1 || imin == 3)) )
			{
			CPoint ptemp = ptdiff;
				ptdiff = pt45;
				pt45 = ptemp;		// swap the two
			}
		pts[0] = ptclose;
		ptclose -= ptdiff;
		pts[1] = ptclose;
		ptclose -= pt45;
		pts[2] = ptclose;
		pts[3] = ptstart;

		pDC->Polyline( pts, 4);
		pDC->SelectObject( cboldpen);
	}
	//		------------------------------ draw the text
				// pick a pen for the rectangle
	if ( m_bDrawBox || m_bFillBox)
	{
	CBrush cbr;

		cboldpen = pDC->SelectStockObject( m_bDrawBox ? BLACK_PEN : NULL_PEN);	// select the pen
		if ( m_bFillBox)
		{
			cbr.CreateSolidBrush( m_rgbBoxColor);
			cboldfill = (CGdiObject *)pDC->SelectObject( &cbr);			// select the brush
		}
		else
			cboldfill = pDC->SelectStockObject( NULL_BRUSH);			// no fill, please

		crtext.InflateRect(4,2);
		pDC->Rectangle( crtext);				// draw the rectangle
		crtext.InflateRect(-4,-2);				// leave some room for the text

		pDC->SelectObject( cboldpen);
		pDC->SelectObject( cboldfill);
	}

	if ( ! strdraw.IsEmpty())
		pDC->DrawText( strdraw, crtext, DT_LEFT | DT_NOPREFIX );	// draw the text inside it

	pDC->SelectObject( cfold);
	SetDrawRect( crtext);
	pDC->SelectClipRgn(NULL);		// turn off clipping

}

// ---------------------------------------------------------------------------
//		HitTest
// ---------------------------------------------------------------------------
BOOL CDataTag::HitTest( CPoint cPt, UINT *pnFlags)
{
CRect rcdraw;

	GetDrawRect( &rcdraw);

	rcdraw.InflateRect( 4, 2);		// 4 pixel grace

	if ( ! rcdraw.PtInRect( cPt))
		return FALSE;

	return TRUE;

}


// ---------------------------------------------------------------------------
//		ParseString
//				parse the input string
// ---------------------------------------------------------------------------
void	CDataTag::ParseString( CString &strOut, LPCSTR strIn)
{
CString strA;
CString strleft;
int ifound, iset;
CDataSet *pdata;
CString strvalue;

	strleft = strIn;
	strA = "";

	while(-1 != strleft.Find('%'))
	{
		strvalue = "";
		ifound = strleft.Find('%');			// where is it???
		if ( ifound)
			strA += strleft.Left( ifound);	// take up to the %
		strleft = strleft.Right( strleft.GetLength() - ifound);		// clip until the %
		if ( 1 >= strleft.GetLength())
		{
			strleft = "";
			continue;			// we're done here
		}
		if ( 3 <= strleft.GetLength())
			iset = strleft[2] - '1';			// which one (base 0)
		else
			iset = 1;
		pdata = NULL;
		if ( iset >=0 && iset <= m_pParent->GetDataCount() )
			pdata = m_pParent->GetDatasetAt( iset);
		if ( ! pdata)
			pdata = m_pParent->GetDatasetAt( 0);		// get first one

		switch( strleft[1])
		{
		case 'f':
		case 'F':
		case 't':
		case 'T':
		case 'X':
		case 'x':
			::FullFormatValue( strvalue, m_fXValue, -4);
			break;
		case 'Y':
		case 'y':
			::FullFormatValue( strvalue, pdata->DataValueAt( m_fXValue), -4);
			break;
		case 'P':
		case 'p':
			::FullFormatValue( strvalue, pdata->PhaseValueAt( m_fXValue), -3);
			break;
		default :
			strvalue = "Not Found";
			break;
		}
		strvalue.TrimRight();		// get rid of trailing space
		strvalue.TrimLeft();		// and leading space
		strA += strvalue;
		if ( iset >= 0 && iset <= 9)
			strleft = strleft.Right( strleft.GetLength() - 3);
		else
			strleft = strleft.Right( strleft.GetLength() - 2);

	}

	strA += strleft;		// get what's left

	strOut = strA;			// here we go....

}
