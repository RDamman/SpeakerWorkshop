// Grid implementation

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "grid.h"
#include "chart.h"

#include "fxFont.h"

#include "utils.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include "dataset.h"
#include "dlgchart.h"

#include "math.h"


IMPLEMENT_SERIAL(CGrid, CDrawObj, VERSIONABLE_SCHEMA | 225)

static int n_LogMajor[4] = { 0, 1,2,5};			// logarithmic majors
// static int n_LogMinor[7] = { 0, 3, 4, 6, 7, 8, 9};			// logarithmic majors

static void calc_LogBase( float fMin, float fMax, float *fBase, float *fDelta)
{
double dt;
int noct;

	if ( fMin <= 0.0)
		fMin = 0.000001f;

	noct = (int )ceil(log10(fMax)) - (int )floor(log10(fMin));		// number of octaves between us

	if ( noct > 2)			// more than 2 octaves, use 3
		*fDelta = (float )pow(10.0, (double ) (ceil(log10(fMax-fMin))-3) );	// give two octaves
	else					// not more than 2 octaves, use 2
		*fDelta = (float )pow(10.0, (double ) (ceil(log10(fMax-fMin))-2) );	// give two octaves
					// look at the min value to get fbase
	dt = (float )pow(10.0, (double )floor(log10(fMin)));
	if ( dt > *fDelta)		// it's a different base ( bigger)
		*fBase = (float )dt;
	else
		*fBase = 0.0f;
}



static int build_Format( CString& cFormat, float fMin, float fMax, float fMajor)
{
int nsize = 0;		// no chars yet
float ftot;
char szf[3];
int ntot;
float fmin, fmax;
int nmax, nmin;
					// calculate the xxx.x portion of all of this
	if ( fMin < 0)
		{
		nsize++;	// now we have a sign
		fmin = -fMin;
		}
	else
		fmin = fMin;

	if ( fMax < 0)
		fmax = -fMax;
	else
		fmax = fMax;

	if ( fmax < fmin)			// if fmin<0 this can happen
		{
		ftot = fmin;
		fmin = fmax;
		fmax = ftot;
		}

	ntot = (int )fmax;								// make it an int
	if ( (ntot % 1000) >= 100)						// do we need to use letters???
		nmax = 3;									// add xxx
	else
		if ( (ntot % 1000) >= 10)					// do we need to use letters???
			nmax = 2;
		else
			nmax = 1;								// min size

	ntot = (int )fmin;								// make it an int
	if ( (ntot % 1000) >= 100)						// hundreds
		nmin = 3;									// add xxx
	else
		if ( (ntot % 1000) >= 10)					// tens
			nmin = 2;
		else
			nmin = 1;								// min size

	if ( (nmin > nmax) || ((int )(fmax/1000)) != (int )(fmin/1000))			// we cycle
		ntot = 3;
	else ntot = nmax;								// this must be the biggest

	nsize += ntot;

	szf[0] = '%';
	szf[2] = '\0';
	szf[1] = (char )('0' + nsize);			// set up the string
	cFormat = szf;

	if ( fmax > 1000000)					// we'll be M'ing this
		fMajor /= 1000000;
	else if ( fmax > 1000)					// we'll be K'ing this
		fMajor /= 1000;

	nmax = (int )(.9 + fMajor * 1000);			// get decimal places of major
	if ( nmax == 1000 * (int )(nmax/1000) )
		cFormat += ".0f";
	else
	if ( nmax == 100 * (int )(nmax/100) )
		{
		cFormat += ".1f";
		nsize += 2;
		}
	else
	if ( nmax == 10 * (int )(nmax/10) )
		{
		cFormat += ".2f";
		nsize += 3;
		}
	else
		{
		cFormat += ".3f";
		nsize += 4;
		}
		
	cFormat += "%c";
	nsize += 1;

	return nsize;

}

static int build_DumbLogFormat( CString& cFormat, float fMin, float fMax, float fMajor)
{
int nsize = 0;		// no chars yet
float ftot;
char *szf = "% ";
int ntot;
float fmin, fmax;
int nmax, nmin;

					// calculate the xxx.x portion of all of this
	if ( fMin <= 0 || fMax <= 0)			// not possible
		{
		cFormat = "%3.3f%c";
		nsize = 6;	// now we have a sign
		return nsize;
		}


	fmax = fMax;
	fmin = fMin;

	if ( fmax < fmin)			// if fmin<0 this can happen
		{
		ftot = fmin;
		fmin = fmax;
		fmax = ftot;
		}

	ntot = (int )fmax;								// make it an int
	if ( (ntot % 1000) >= 100)						// do we need to use letters???
		nmax = 3;									// add xxx
	else
		if ( (ntot % 1000) >= 10)					// do we need to use letters???
			nmax = 2;
		else
			nmax = 1;								// min size

	ntot = (int )fmin;								// make it an int
	if ( (ntot % 1000) >= 100)						// hundreds
		nmin = 3;									// add xxx
	else
		if ( (ntot % 1000) >= 10)					// tens
			nmin = 2;
		else
			nmin = 1;								// min size

	if ( (nmin > nmax) || ((int )(fmax/1000)) != (int )(fmin/1000))			// we cycle
		ntot = 3;
	else ntot = nmax;								// this must be the biggest

	nsize += ntot;

	szf[1] = (char )('0' + nsize);			// set up the string
	cFormat = szf;

	{
	float fstart, fdelta;

		calc_LogBase( fmin, fmax, &fstart, &fdelta);
		fmin = fstart;
		fMajor = fdelta;
	}

	if ( fmin > 1000000)					// we'll be K'ing this
		fMajor /= 1000000;
	else if ( fmin > 1000)					// we'll be K'ing this
		fMajor /= 1000;

	nmax = (int )(.9 + fMajor * 1000);			// get decimal places of major
	if ( nmax == 1000 * (int )(nmax/1000) )
		cFormat += ".0f";
	else
	if ( nmax == 100 * (int )(nmax/100) )
		{
		cFormat += ".1f";
		nsize += 2;
		}
	else
	if ( nmax == 10 * (int )(nmax/10) )
		{
		cFormat += ".2f";
		nsize += 3;
		}
	else
		{
		cFormat += ".3f";
		nsize += 4;
		}
		
	cFormat += "%c";
	nsize += 1;

	return nsize;

}


static void build_LogFormat( CString& cFormat, float fValue, float fDelta)
{
float fbase;
float ft;
int npre;
int npost;
char csuffix;

				// figure out the suffix first
	if ( fValue >= 1000000.0f)		// million
	{
		csuffix = 'M';
		fbase = 1000000.0f;
	}
	else if ( fValue >= 1000.0f)
	{
		csuffix = 'K';
		fbase = 1000.0f;
	}
	else 
	{
		csuffix = ' ';
		fbase = 1.0f;
	}

	ft = (fValue / fbase);
				// how many digits preceding the decimal point?
	if ( ft >= 100.0f)
		npre = 3;
	else if ( ft >= 10.0f)
		npre = 2;
	else
		npre = 1;
				// how many digits after the decimal point?

	npost = (int )floor(log10( fDelta / fbase));		// number of decimals

	if ( npost > 0)
		npost = 0;			// no decimals
	else
		npost = -npost;		// use these

//	if ( csuffix != ' ')
//		cFormat.Format( "%%%d.%df%c%%c", npre + npost, npost, csuffix);
//	else
		cFormat.Format( "%%%d.%df%%c", npre + npost, npost);

}


// draw the actual #
static void draw_Number( CDC *pDC, LPRECT lpRcDraw, CString& cFormat, float fNumber, UINT uStyle)
{
char sznew[100];
float fabs;

	if ( fNumber < 0)
		fabs = -fNumber;
	else
		fabs = fNumber;

	if ( fabs >= 1000000)
		sprintf( sznew, cFormat, fNumber/1000000, 'M');
	else
	if ( fabs >= 1000)
		sprintf( sznew, cFormat, fNumber/1000, 'K');
	else
		sprintf( sznew, cFormat, fNumber, ' ');

	pDC->DrawText(sznew, strlen(sznew), lpRcDraw, uStyle | DT_SINGLELINE);

}


static float get_First( float fStart, float fDelta)
{
int ncount;

	if ( fDelta <= 0)
		return fStart;

	ncount = (int )(fStart / fDelta);		// how many counts is this???
	if ( fStart <= (ncount * fDelta ) )		// it fits exactly (use <= for fStart < 0 case)
		return (ncount * fDelta);

	return (ncount + 1)*fDelta;				// start at the next one

}



//	formats:
//			x.xxx - float < 1
//			xx   - short int
//			xx.x - short float
//			xxx	- stock integer nothing else
//			xxx.x - float
//			xxxK - integer with suffix
//			xxx.xK - float with suffix
void CGrid::DrawScale( CDC *pDC, LPRECT lprcDraw)
{
	if ( ! IsVisible())
		return;

float fi;
CRect crn;
int i;
CString cformat;
CFont *cfold, *cfnew;
COLORREF rgbold;
UINT uformat;
float fmin = m_fMin;		// a limited fmin
CFloatArray faMajor, faMinor;

				// we need this to do the convertcoord stuff later, but the real value is set when we draw
	FixLog();				// fixup
				// the grids
	m_rcDrew.CopyRect(lprcDraw );					// save this for later, if needed

	cfnew = CAudtestApp::GetAppFont(ftScale).GetCurrentFont( pDC);				// set the font for drawing the scale
	if ( ! cfnew)
		return;

	cfold = pDC->SelectObject( cfnew);
	rgbold = pDC->SetTextColor( CAudtestApp::GetAppFont(ftScale).GetColor() );

				// evaluate the character sizes
	if ( IsVertical() )
		uformat = DT_VCENTER | (IsTopLeft() ? DT_RIGHT : DT_LEFT);
	else
		uformat = DT_CENTER | (IsTopLeft() ? DT_BOTTOM : DT_TOP);

	crn = *lprcDraw;

	SetDrawRect( crn);			// here's our hit-test rectangle, save it for later
	DrawHighlight(pDC );

	if ( ! IsLog())
		{
		int j;

			build_Format( cformat, fmin, m_fMax, m_fMajor);

			BuildLinearGrid(pDC, faMajor, faMinor);
			for ( j=0; j<faMajor.GetSize(); j++)
			{
				fi = faMajor.GetAt( j);
				i = ConvertCoord( fi);
				if ( IsVertical())
					{
					crn.top = i - 100;
					crn.bottom = i + 100;		//center it
					}
				else
					{
					crn.left = i - 100;
					crn.right = i + 100;		//center it
					}
				draw_Number( pDC, crn, cformat, fi, uformat);
			}
		}
	else				// logarithmic
		{
		int j;
		int nlastleft = -100;		// end of last number
		CRect crtest;
		BuildLogGrid(pDC, faMajor, faMinor);
		CFloatArray *pUse = &faMajor;
		float fdelta = 1.0f;
		int ndivide = 1;			// divider if all kHz

			if ( m_bDrawMinor && (faMinor.GetSize() < 5) )		// only 10 minor datapoints, use it
				pUse = &faMinor;

#if 0
			if ( faMajor.GetAt(0) >= 1000)			// at least 1 kHz
			{
			CString cstest;
			bool buse = false;

							// find out if we can use kHz as our scale (buse)
				cstest.LoadString( IDSCH_FREQUENCY);
				if ( cstest == GetTitle())			// yep, it's our title
				{
					cstest.LoadString( IDSCH_KFREQUENCY);
					SetTitle( cstest);
					buse = true;
				}
				else
				{
					cstest.LoadString( IDSCH_KFREQUENCY);
					if ( cstest == GetTitle())
						buse = true;
				}
				if ( buse)			// yes we can, we reset the title
				{
					ndivide = 1000;						// use kHz divider
					for ( j=0; j<pUse->GetSize(); j++)
						pUse->SetAt( j, pUse->GetAt(j) / ndivide);		// divide everyone by 1k
				}
			}
			else			// we aren't using khz
			{
			CString cstest;

				cstest.LoadString( IDSCH_KFREQUENCY);
				if ( cstest == GetTitle())
				{
					cstest.LoadString( IDSCH_FREQUENCY);
					SetTitle( cstest);
				}
			}
#endif

			for ( j=0; j<pUse->GetSize(); j++)
			{
				fi = pUse->GetAt( j);
				i = ConvertCoord( fi * ndivide);
				if ( IsVertical())
					{
					crn.top = i - 100;
					crn.bottom = i + 100;		//center it
					}
				else
					{
					crn.left = i - 100;
					crn.right = i + 100;		//center it
					}
				crtest = crn;
				if ( (j+1) != pUse->GetSize())
				{
					fdelta = pUse->GetAt(j+1) - fi;		// fdelta is the difference
				}				// otherwise use prior fdelta
				build_LogFormat( cformat, fi, fdelta);
				draw_Number( pDC, crtest, cformat, fi, uformat | DT_CALCRECT);	// find rectangle
				if ( crtest.left > nlastleft)		// draw it, no overlap
				{
					draw_Number( pDC, crn, cformat, fi, uformat);
					nlastleft = crtest.right;		// end of this one
				}
			}

		}		// end logarithmic


	pDC->SelectObject( cfold);
	pDC->SetTextColor( rgbold);

}


/////////////////////////////////////////////////////////////////////////////
// CGrid construction/destruction

CGrid::CGrid()	: m_ccMajor( RGB(128,128,128)), m_ccMinor( RGB(192,192,192),1,PS_DASH), 
					m_szTitle(cNullString), m_rcDrew(0,0,1,1)
{
	// TODO: add one-time construction code here
	m_bAutoScale 	= TRUE;
	m_bAutoTic 		= TRUE;
	m_bDrawMajor	= TRUE;			// show the grid lines???
	m_bDrawMinor	= FALSE;		// show the grid lines???
	m_bIsLog		= FALSE;		// is it logarithmic
	m_bIsTopLeft	= FALSE;		// default to bottom or right (adjusted in chart create)
	m_bIsVertical	= TRUE;			// is it vertical???
	m_bShowGrid		= TRUE;			// draw the grid lines
	m_bShowTic		= TRUE;			// draw the tic marks
	m_bShowTitle	= TRUE;			// draw the title
	m_fMajor		= 10.0f;		// major tic distance
	m_fMax			= 100.0f;		// max value
	m_fMin			= 0.0f;			// min value
	m_fMinor		= 2.0f;			// minor tic distance
	m_fZOffset		= 0.0f;			// Z Offset

}

CGrid::~CGrid()
{

}

/////////////////////////////////////////////////////////////////////////////
// CGrid serialization

void CGrid::Serialize(CArchive& ar)
{
WORD w;

	CDrawObj::Serialize( ar);

	m_ccMajor.Serialize( ar);
	m_ccMinor.Serialize( ar);

	if (ar.IsStoring())
		{							 // ---------------------- storing 

		w = (WORD )m_bAutoScale;	ar << w; // calc scaling automatically (used by parent only)
		w = (WORD )m_bAutoTic;		ar << w; // select major and minor automatically
		w = (WORD )m_bIsLog;		ar << w; // is it logarithmic
		w = (WORD )m_bIsVertical;	ar << w; // is it vertical???
		w = (WORD )m_bIsTopLeft;	ar << w; // is it vertical???
		w = (WORD )m_bShowGrid;		ar << w; // draw the grid lines
		w = (WORD )m_bShowTic;		ar << w; // draw the tic marks
		w = (WORD )m_bShowTitle;	ar << w; // draw the title
		ar << m_fMin;				 // min value
		ar << m_fMax;				 // max value
		w = (WORD )m_bDrawMajor;	ar << w; // show the grid lines???
		ar << m_fMajor;				 // major tic distance
		w = (WORD )m_bDrawMinor;	ar << w; // show the grid lines???
		ar << m_fMinor;				 // minor tic distance

		ar << m_szTitle;
									// don't bother saving the Z Offset Value
		}
	else
		{							// ---------------------- loading 
		ar >> w; m_bAutoScale = w; 	// calc scaling automatically (used by parent only)
		ar >> w; m_bAutoTic = w;	// select major and minor automatically
		ar >> w; m_bIsLog = w; 		// is it logarithmic
		ar >> w; m_bIsVertical = w; // is it vertical???
		ar >> w; m_bIsTopLeft = w; // is it vertical???
		ar >> w; m_bShowGrid = w; 	// draw the grid lines
		ar >> w; m_bShowTic = w; 	// draw the tic marks
		ar >> w; m_bShowTitle = w; 	// draw the tic marks
		ar >> m_fMin;				// min value
		ar >> m_fMax;				// max value
		ar >> w; m_bDrawMajor = w; 	// show the grid lines???
		ar >> m_fMajor;				// major tic distance
		ar >> w; m_bDrawMinor = w; 	// show the grid lines???
		ar >> m_fMinor;				// minor tic distance

		ar >> m_szTitle;

		m_fZOffset = 0.0f;			// here's where we always start
		}
}

				// operators
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
CGrid &CGrid::operator=(const CGrid &cIn)
{
 	CDrawObj::operator=( cIn);
					// don't copy the id #
		m_ccMajor = cIn.m_ccMajor;
		m_ccMinor = cIn.m_ccMinor;

		m_bAutoScale = 	cIn.m_bAutoScale;	 // calc scaling automatically (used by parent only)
		m_bAutoTic = 	cIn.m_bAutoTic;			 // select major and minor automatically
		m_bIsLog = 		cIn.m_bIsLog;		 // is it logarithmic
		m_bIsVertical = cIn.m_bIsVertical;		 // is it vertical???
		m_bShowGrid = 	cIn.m_bShowGrid;	 // draw the grid lines
		m_bShowTic = 	cIn.m_bShowTic;			 // draw the tic marks
		m_bShowTitle = 	cIn.m_bShowTitle;	 // draw the title
		m_fMin = 		cIn.m_fMin;				 // min value
		m_fMax = 		cIn.m_fMax;				 // max value
		m_bDrawMajor = 	cIn.m_bDrawMajor;	 // show the grid lines???
		m_fMajor = 		cIn.m_fMajor;		 // major tic distance
		m_bDrawMinor = 	cIn.m_bDrawMinor; 		// show the grid lines???
		m_fMinor = 		cIn.m_fMinor;		 // minor tic distance

		m_szTitle =		cIn.m_szTitle;		// copy the title
		m_fZOffset =	cIn.m_fZOffset;		// copy the Z offset

 	return *this;
}



/////////////////////////////////////////////////////////////////////////////
// CGrid diagnostics

#ifdef _DEBUG
void CGrid::AssertValid() const
{
	CObject::AssertValid();
}

void CGrid::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}

#endif //_DEBUG


IMPLEMENT_SERIAL(CGridZ, CGrid, VERSIONABLE_SCHEMA | 294)

/////////////////////////////////////////////////////////////////////////////
// CGridZ construction/destruction

CGridZ::CGridZ()	: CGrid()
{
	// TODO: add one-time construction code here
	m_fSlope = 0.0f;
	m_fTotal = 0.0f;		// no pixel total movement
}

CGridZ::~CGridZ()
{

}

/////////////////////////////////////////////////////////////////////////////
// CGridZ serialization

void CGridZ::Serialize(CArchive& ar)
{

	CGrid::Serialize( ar);

	if ( ar.IsStoring())
		{
		ar << m_fSlope;
		ar << m_fTotal;
		}
	else
		{
		ar >> m_fSlope;
		ar >> m_fTotal;
		}
}

				// operators
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
CGridZ &CGridZ::operator=(const CGridZ &cIn)
{

	CGrid::operator=( cIn);

	m_fSlope = cIn.m_fSlope;
	m_fTotal = cIn.m_fTotal;

 	return *this;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
CGridZ &CGridZ::operator=(const CGrid &cIn)
{

	CGrid::operator=( cIn);

	m_fSlope = 0.0f;
	m_fTotal = 0.0f;

 	return *this;
}



/////////////////////////////////////////////////////////////////////////////
// CGridZ diagnostics

#ifdef _DEBUG
void CGridZ::AssertValid() const
{
	CObject::AssertValid();
}

void CGridZ::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CDrawObj operations

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
int CGrid::ConvertCoord( float fValue)
{
int nout, nwidth;

	if ( m_fMin == m_fMax)
		return 0;

	if ( IsVertical())
		nwidth = m_rcDrew.bottom - m_rcDrew.top;
	else
		nwidth = m_rcDrew.right - m_rcDrew.left;

	if ( ! IsLog())
		nout = (int )(nwidth * ( (fValue - m_fMin) / (m_fMax - m_fMin) ));
	else
		{		// logarthmic, don't let it hit zero
		nout = (int )(nwidth * ( (log10(fValue) - log10(m_fMin)) / (log10(m_fMax) - log10(m_fMin))) );
		}

	if ( IsVertical() )
		return m_rcDrew.bottom + (int )m_fZOffset - nout;
	else
		return m_rcDrew.left + (int )m_fZOffset + nout;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
float CGrid::ConvertLocation( int nIn)
{
double d;
double dout;
float fmin;


	if ( m_fMin == m_fMax)
		return m_fMin;

 	if ( IsVertical())
		d = ((double )(m_rcDrew.bottom - nIn - m_fZOffset)) / ( m_rcDrew.bottom - m_rcDrew.top);
	else
		d = ((double )(nIn - m_rcDrew.left - m_fZOffset)) / ( m_rcDrew.right - m_rcDrew.left);

	if ( ! IsLog())			// linear case
		dout = m_fMin + (m_fMax - m_fMin) * d;
	else								// log case
		{
		fmin = m_fMin;
		if ( fmin <= 0.0f)
			fmin = 0.01f;
		dout = fmin * pow(10.0, d * log10( m_fMax / fmin));
		}

	return (float )dout;			// the Z Offset trick goes here

}


// calculate major and minor tic marks based on total data
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CGrid::CalcAutoTic()
{
int nmult;
double fdif;

	if ( ! m_bAutoTic)
		return;

	if ( IsLog())
		return;

	nmult = (int )( (m_fMax - m_fMin) / 5000000 );
	if ( nmult)
		nmult = 1000000;
	else
		{
		nmult = (int )( (m_fMax - m_fMin) / 5000 );			// auto divide by 5 (1000/5)
		if ( nmult)
			nmult = 1000;
		else
			nmult = 1;
		}
				// now nmult is 1, 1000,or 1000000 (1,K,M)

	fdif = (m_fMax - m_fMin) / nmult;

	if ( 0.0f == fdif)		// nothing there
		fdif = 0.02 * m_fMax;		// make up something
				// get difference between min and max in units

	m_fMajor = (float )floor(fdif / 5);
	
	if ( m_fMajor)					// we have an int delta, make it single digit
		{
		if ( m_fMajor > 100)
			m_fMajor = 100.0f * (int )( m_fMajor / 100);
		else
		if ( m_fMajor > 10)
			m_fMajor = 10.0f * (int )( m_fMajor / 10);
		}
	if ( ! m_fMajor)			// less than 1 delta...
		{
		m_fMajor = (float )( floor(fdif / .5) / 10);
		}
	if ( ! m_fMajor)			// less than 1/10 delta...
		{
		m_fMajor = (float )( floor(fdif / .05) / 100);
		}
	if ( ! m_fMajor)			// less than 1/100 delta...
		{
		m_fMajor = (float )( floor(fdif / .005) / 1000);
		}

	m_fMajor *= nmult;
	m_fMinor = (float )(m_fMajor/4);

}

// this calculates the width (for vertical) of the rectangle that will contain the scale
// rcDraw (input) is the source rectangle return result is the width/height
int CGrid::CalcDraw( CDC *pDC, CRect& rcDraw)
{
CRect crn;
CString cformat;
CFont *cfold, *cfnew;
int nout;

				// we need this to do the convertcoord stuff later, but the real value is set when we draw
				// the grids
	cfnew = CAudtestApp::GetAppFont(ftScale).GetCurrentFont( pDC);				// set the font for drawing the scale
	if ( ! cfnew)
		return 1;				// bogus!

	cfold = pDC->SelectObject( cfnew);

				// evaluate the character sizes
	if ( ! IsLog())
		build_Format( cformat, m_fMin, m_fMax, m_fMajor);
	else
		build_DumbLogFormat( cformat, m_fMin, m_fMax, m_fMajor);

	if ( IsVertical() )
		{
		CString csnum;
		float fnum;
		CRect crn = rcDraw;
		int i;

			fnum = 0.555f;
			for ( i='0'; i<cformat[2]; i++)
				fnum = fnum * 10 + .005f;
			if ( 'c' != cformat[cformat.GetLength()-1])		// appended a 'c' for 'M'
				csnum.Format( cformat, fnum);	// format the number
			else
				csnum.Format( cformat, fnum,'M');	// format the number
		pDC->DrawText( csnum, crn, DT_TOP | DT_LEFT | DT_SINGLELINE | DT_CALCRECT);
		nout = crn.Width();
		}
	else			// not vertical, just return character height
		{
		nout = pDC->DrawText( "999", -1, rcDraw, DT_TOP | DT_LEFT | DT_SINGLELINE | DT_CALCRECT);
		}

	pDC->SelectObject( cfold);

	return nout;

}

void CGrid::FixLog( void)
{
	if ( IsLog())			// logarithmic
	{
		if ( m_fMin <= 0.0f || m_fMax <= 0.0f)
		{
			::AfxMessageBox(IDERR_LOGNEGATIVE);
			if ( m_fMax <= 0.0f)
				m_fMax = m_fMin * 10.0f;
			if ( m_fMin <= 0.0f)
				m_fMin = m_fMax / 10.0f;
			if ( m_fMin <= 0.0f)		// they're both less than zero
			{
				m_fMin = 0.0001f;
				m_fMax = 0.0002f;
			}
		}
	}
}



void CGrid::DoDraw( CDC *pDC, LPCRECT lprcDraw)
{
bool bdrawminor = (m_bDrawMinor ? TRUE : FALSE);

				// we need this to do the convertcoord stuff later, but the real value is set when we draw
	m_rcDrew.CopyRect(lprcDraw );					// save this for later, if needed

	if ( ! IsVisible())
		return;

	if ( ! m_bShowGrid)		// keep this in to draw text later
		return;

	FixLog();				// fixup

CPen *cpenmajor = m_ccMajor.BuildPen();
CPen *cpenminor = m_ccMinor.BuildPen();

CPen *coldpen = pDC->SelectObject( cpenminor);
CFloatArray faMajor, faMinor;

	if ( ! IsLog())
		BuildLinearGrid(pDC, faMajor, faMinor);
	else				// logarithmic
	{
		BuildLogGrid(pDC, faMajor, faMinor);
	}

	if ( IsVertical())
		{					// vertical, linear
		if ( bdrawminor )
			DrawHLines( pDC, faMinor);
		pDC->SelectObject( cpenmajor);
		if ( m_bDrawMajor )
			DrawHLines( pDC, faMajor);
		}
	else
		{				// horizontal linear
		if ( bdrawminor )
			DrawVLines( pDC, faMinor);
		pDC->SelectObject( cpenmajor);
		if ( m_bDrawMajor )
			DrawVLines( pDC, faMajor);
		}


	pDC->SelectObject( coldpen);

	delete cpenmajor;
	delete cpenminor;


}

void CGrid::BuildLinearGrid(CDC *pDC, CFloatArray &faMajor, CFloatArray &faMinor)
{
float fi;
float fmax = m_fMax;
float fmin = m_fMin;

	if ( fmax == m_fMin)			// nothing to really chart
	{
		fmax = 1.1f * m_fMin;
		fmin = 0.9f * m_fMin;
	}

	faMajor.RemoveAll();
	faMajor.SetSize(0, 10);			// set to 0 size, 10 adds
	faMinor.RemoveAll();
	faMinor.SetSize( 0, 10);

	if ( m_fMinor <= 0.0f)
		return;

	if ( GetAuto(1))		// autoscale???
	{
		fi = get_First( fmin, m_fMajor);		// get first tic
		if ( fi > fmin)							// we're below a tic mark
		{
			m_fMin = fi - m_fMajor;				// make it a tic mark
			fmin = m_fMin;
		}
		fi = fmin;
		while ( fi < fmax)
			fi += m_fMajor;
		if ( fi > fmax)							// also not a tic mark
		{
			fmax = fi;
			m_fMax = fi;						// we're at the tic mark
		}
	}

	for ( fi = get_First( fmin, m_fMinor); fi <= fmax; fi += m_fMinor)
		faMinor.Add( fi);

	for ( fi = get_First( fmin, m_fMajor); fi <= fmax; fi += m_fMajor)
		faMajor.Add( fi);
}


void CGrid::BuildLogGrid(CDC *pDC, CFloatArray &faMajor, CFloatArray &faMinor)
{
float fmin = m_fMin;
float fdelta;
int j;
float ffreq;
float forigin;
int nsize;
double dt;
bool blinear = FALSE;
float fminor;
int igridspace = 20;				// spacing required before going to next spot

	faMajor.RemoveAll();
	faMajor.SetSize(0, 10);			// set to 0 size, 10 adds
	faMinor.RemoveAll();
	faMinor.SetSize( 0, 10);

	if ( fmin <= 0.0)
		fmin = 0.000001f;

	igridspace = pDC->GetDeviceCaps( LOGPIXELSX);		// X dimension?
	igridspace /= 4;		// use 1/4 of an inch

				// desired number of gridlines
	nsize = (ConvertCoord( m_fMax) - ConvertCoord( fmin)) / igridspace;

	fdelta = (m_fMax - fmin) / nsize;			// linear delta would be...
	dt = pow( 10.0f,  floor(log10( fdelta)));		// nearest power of 10
	if ( dt <= pow( 10.0f, floor( log10( fmin))))	// too big?
	{
		blinear = TRUE;
	}

	if ( blinear)
	{
		if ( (ConvertCoord( m_fMax) - ConvertCoord( m_fMax  - (float )dt)) < igridspace)
		{
			dt *= 2;								// are halves better?
			if ( (ConvertCoord( m_fMax) - ConvertCoord( m_fMax  - (float )dt)) < igridspace)
			{
				dt *= 2.5;								// are halves better?
			}
			if ( (ConvertCoord( m_fMax) - ConvertCoord( m_fMax  - (float )dt)) < igridspace)
			{
				dt *= 2;								// go to next factor of 10 (sparser)
			}
		}

		fdelta = (float )dt;			// major axis size
		fminor = (float )pow( 10.0, floor( log10( dt)));		// minor?
		if ( fminor == fdelta)
			fminor = fdelta / 2.0f;			// use 1/5 it

		forigin = fdelta * (float )floor(fmin / fdelta);
		ffreq = 0.0f;
		for ( j = 0; ffreq <= m_fMax; j++)
		{
			ffreq = forigin + fdelta * j;
			if ( (ffreq <= m_fMax) && (ffreq >= fmin) )
			{
				faMajor.Add( ffreq);
			}
		}
		ffreq = 0.0f;
		for ( j = 0; ffreq <= m_fMax; j++)
		{
			ffreq = forigin + fminor * j;
			if ( (ffreq <= m_fMax) && (ffreq >= fmin) )
			{
				faMinor.Add( ffreq);
			}
		}
	}
	else			// true logarithmic scale
	{
		fdelta = (float )pow( 10.0f, floor( log10( fmin)));		// use fmin's size

		ffreq = 0.0f;

		while( ffreq < m_fMax)
		{
			for ( j=1; j<10; j++)
				{
				ffreq = fdelta * j;
				if ( (ffreq <= m_fMax) && (ffreq >= fmin) )
					{
					faMinor.Add( ffreq);
					}
				}
			for ( j=1; j<4; j++)
				{
				ffreq = fdelta * n_LogMajor[j];
				if ( (ffreq <= m_fMax) && (ffreq >= fmin) )
					{
					faMajor.Add( ffreq);
					}
				}
			fdelta *= 10.0f;
			ffreq = fdelta;
		}
	}
}

void CGrid::DrawHLines(CDC *pDC, CFloatArray &fLines)
{
int j;
float ffreq;

	for ( j=0; j < fLines.GetSize(); j++)
	{
		ffreq = fLines.GetAt( j);
		int i = ConvertCoord( ffreq);
		if ( i > m_rcDrew.top && i < m_rcDrew.bottom)
			{
			pDC->MoveTo(m_rcDrew.left,i);
			pDC->LineTo(m_rcDrew.right,i);
			}
	}

}

void CGrid::DrawVLines(CDC *pDC, CFloatArray &fLines)
{
int j;
float ffreq;

	for ( j=0; j < fLines.GetSize(); j++)
	{
		ffreq = fLines.GetAt( j);
		int i = ConvertCoord( ffreq);
		if ( i > m_rcDrew.left && i < m_rcDrew.right)
			{
			pDC->MoveTo(i,m_rcDrew.bottom);
			pDC->LineTo(i,m_rcDrew.top);
			}
	}

}

void CGrid::SetColor(int nID, COLORREF clrNew)
{
	if ( ! nID)
		m_ccMajor.SetColor( clrNew);
	else
		m_ccMinor.SetColor( clrNew);
}


void CGrid::CopyFormat( CGrid *pDest)
{
	pDest->m_bAutoScale = m_bAutoScale;
	pDest->m_bAutoTic = m_bAutoTic;
	pDest->m_bIsLog = m_bIsLog;		// is it logarithmic
	pDest->m_bIsVertical = m_bIsVertical;	// is it vertical???
	pDest->m_bIsTopLeft = m_bIsTopLeft;	// is it top/left????
	pDest->m_bShowGrid = m_bShowGrid;	// draw the grid lines
	pDest->m_bShowTic = m_bShowTic;		// draw the tic marks
	pDest->m_bShowTitle = m_bShowTitle;	// draw the tic marks
	pDest->m_fMin = m_fMin;			// min value
	pDest->m_fMax = m_fMax;			// max value
	pDest->m_bDrawMajor = m_bDrawMajor;	// show the grid lines???
	pDest->m_fMajor = m_fMajor;		// major tic distance
	pDest->m_bDrawMinor = m_bDrawMinor;	// show the grid lines???
	pDest->m_fMinor = m_fMinor;		// minor tic distance

	pDest->m_ccMajor = m_ccMajor;		// grid color & style
	pDest->m_ccMinor = m_ccMinor;		// grid color & style

	pDest->SetVisible( IsVisible());
}
