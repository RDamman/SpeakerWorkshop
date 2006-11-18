// chart.cpp : implementation of the CSubChartArray classes
//


#include "stdafx.h"
#include "audtest.h"


#include "zFormEdt.h"
#include "chart.h"
#include "DlgChartProp.h"

#include "fxFont.h"

#include "utils.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include "dataset.h"
#include "dlgchart.h"

#include "math.h"


/////////////////////////////////////////////////////////////////////////////
// CSubChart
/////////////////////////////////////////////////////////////////////////////

// actually we use the CChart schema (USCHEMA in the header)
IMPLEMENT_SERIAL(CSubChart, CNamed, VERSIONABLE_SCHEMA | 223)


// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// this draws the border and deflates the rectangle
// ------------------------------------------------------------------------------
static void draw_Border( CDC *pDC, RECT& crTotal)
{

				// note FromHandle creates a temp object that is automatically
				// deleted by the system when the time comes
//CGdiObject *coldbrush = pDC->SelectStockObject( WHITE_BRUSH);

//	pDC->PatBlt( crTotal.left, crTotal.top, nx, ny, PATCOPY);
//	if ( coldbrush)
//		pDC->SelectObject( coldbrush);

CPen *cpen;
CPen *cold;
CRect rcdraw;

	rcdraw = crTotal;
	{
		CBrush cback( CAudtestApp::GetAppColor( clrInterior));
		pDC->FillRect(rcdraw , &cback);
	}
	rcdraw.InflateRect(2,2);

	cpen = new CPen( PS_SOLID, 1, RGB(128,128,128));			// dkgray pen
	cold = pDC->SelectObject( cpen);
	pDC->MoveTo( rcdraw.left, rcdraw.bottom-1);
	pDC->LineTo( rcdraw.left, rcdraw.top);
	pDC->LineTo( rcdraw.right-1, rcdraw.top);
	pDC->LineTo( rcdraw.right-1, rcdraw.bottom-1);
	pDC->LineTo( rcdraw.left, rcdraw.bottom-1);
	pDC->SelectObject( cold);
	delete cpen;
	cpen = new CPen( PS_SOLID, 1, RGB(0,0,0));					// black
	cold = pDC->SelectObject( cpen);
	pDC->MoveTo( rcdraw.left+1, rcdraw.bottom-2);
	pDC->LineTo( rcdraw.left+1, rcdraw.top+1);
	pDC->LineTo( rcdraw.right-1, rcdraw.top+1);
	pDC->SelectObject( cold);
	delete cpen;
	cpen = new CPen( PS_SOLID, 1, RGB(0xff,0xff,0xff));
	cold = pDC->SelectObject( cpen);
	pDC->MoveTo( rcdraw.right, rcdraw.top);
	pDC->LineTo( rcdraw.right, rcdraw.bottom);
	pDC->LineTo( rcdraw.left, rcdraw.bottom);
	pDC->SelectObject( cold);
	delete cpen;

}




/////////////////////////////////////////////////////////////////////////////
// CSubChart construction/destruction
/////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------
// constructor
// ------------------------------------------------------------------------------
CSubChart::CSubChart() : m_csTitle(cNullString), m_cDataLines(), m_cGridX(), m_cGridY(), m_cGridY2(),
						m_cGridZ(), m_cLegend(), m_cBorder(), m_cInside(), m_cMarker1(), m_cMarker2(),
						m_cTags()
{
				// one-time construction code here
	m_cGridX.SetVisible( TRUE);
	m_cGridX.SetVertical( FALSE);
	m_cGridY.SetVisible( TRUE);
	m_cGridY.SetVertical( TRUE);
	m_cGridY.SetTopLeft( TRUE);
	m_cGridY2.SetVisible( TRUE);
	m_cGridY2.SetVertical( TRUE);
	m_cLegend.SetVisible( FALSE);
	m_cGridX.SetLog( FALSE);
	m_cGridY.SetLog( FALSE);
	m_cGridY2.SetLog( FALSE);
	m_cDataLines.SetSize(0, 5);
	m_cMarker1.SetGrid( &m_cGridX);
	m_cMarker2.SetGrid( &m_cGridX);
	m_cTags.SetSize(0, 20);		// use 20 as a reasonable growth size

	m_fMin = 0.001f;
	m_fMax = 100.0f;			// random initial values

}

// ------------------------------------------------------------------------------
// destructor
// ------------------------------------------------------------------------------
CSubChart::~CSubChart()
{
	::KillArray( &m_cDataLines);
}

/////////////////////////////////////////////////////////////////////////////
// CSubChart serialization

// ---------------------------------------------------------------------------
//	Serialize
// ---------------------------------------------------------------------------
void CSubChart::Serialize(CArchive& ar)
{
int i;
WORD w;

	CNamed::Serialize(ar);
	m_cGridX.Serialize(ar);
	m_cGridY.Serialize(ar);
	m_cGridY2.Serialize(ar);

	i = GetSchema();			// debug

	if ( ar.IsStoring() || (241 <= GetSchema()) )
		m_cGridZ.Serialize(ar);
	else
	{
		CGrid cgdummy;
		cgdummy.Serialize(ar);		// waste the incoming data
		m_cGridZ = cgdummy;
	}

	m_cMarker1.Serialize( ar);
	m_cMarker2.Serialize( ar);

	m_cLegend.Serialize( ar);
	m_cBorder.Serialize( ar);

	if ( ar.IsStoring())			// storing
	{
		ar << m_csTitle;
		w = (WORD )m_cDataLines.GetSize();
		ar << w;
		for ( i=0; i < (int )w; i++)
			{
			m_cDataLines.GetAt(i)->Serialize(ar);
			}
		int itags = m_cTags.GetSize();

		ar << itags;

		if ( itags)
			for ( i=0; i<itags; i++)
				m_cTags[i].Serialize( ar);		// save each of these
	}
	else							// loading
	{
		ar >> m_csTitle;
		ar >> w;
		for ( i=0; i < w; i++)
			{
			CDataLine *cdata = new CDataLine( this);
			cdata->Serialize( ar);
			m_cDataLines.Add( cdata);
			}
		m_cMarker1.SetGrid( &m_cGridX);		// update marker pointers
		m_cMarker2.SetGrid( &m_cGridX);
		if ( GetSchema() >= 240)			// when we added data tags (see CChart)
		{
		int itags;

			ar >> itags;

			if ( itags)
			{
				m_cTags.SetSize( itags, 20);
				for ( i=0; i<itags; i++)
				{
					m_cTags[i].Serialize( ar);		// load each of these
					m_cTags[i].SetParent( this);	// set us to the parent
				}
			}
		}
		else
			m_cTags.SetSize( 0, 20);
	}

}

// ---------------------------------------------------------------------------
//	EditProperties
// ---------------------------------------------------------------------------
int   CSubChart::EditProperties(CWnd *pParent, CObject *cSubject )	// bring up properties dbox
{
int nresult;
int ipage = 0;

#if _DEBUG
	DWORD dwid;
	CDataLine *pset = GetDataAt(0);

		if ( pset)
			dwid = pset->GetDataID();		// who are we graphing, anyway?
#endif

	if ( cSubject == &m_cGridX)
		ipage = 2;
	else
	if ( cSubject == &m_cGridY)
		ipage = 3;
	else
	if ( cSubject == &m_cGridY2)
		ipage = 4;
	else
	if ( cSubject)			// must be a dataline
		ipage = 1;

	if ( cSubject)
	{
	CDrawObj *pobj;

		ASSERT_KINDOF( CDrawObj, cSubject);
		pobj = (CDrawObj *)cSubject;

		if ( ntDataTag == pobj->GetType())
		{			// it's a datatag, do a different editprop
		CDataTag *ptag = (CDataTag *)pobj;			// it's really a data tag
			ptag->EditProperties( pParent);
		}
	}

CDlgChart cchar( pParent, ipage);

	cchar.UseChart( GetRootObject(), this, cSubject);

	nresult = cchar.DoModal();
	if ( IDOK == nresult)
		{
		cchar.SetChart( this);
		}

	return nresult;
}


// this draws the border and deflates the rectangle
// ---------------------------------------------------------------------------
//	DrawBorder
// ---------------------------------------------------------------------------
void CSubChart::DrawBorder( CDC *pDC, CRect& crTotal)
{

	draw_Border( pDC, crTotal);

}

// ---------------------------------------------------------------------------
//	GetMember
// ---------------------------------------------------------------------------
int	 CSubChart::GetMember( DWORD dwID)
{
int i;
CDataLine *cnew;

				// check to see if he's already attached for use by stupid fns that do an attach
	for ( i= 0; i<m_cDataLines.GetSize(); i++)
		{
		cnew = (CDataLine *)m_cDataLines.GetAt(i);
		if ( dwID == cnew->GetDataID())
			return (i+1);			// do nothing, we already have this guy
		}

	return 0;					// not found
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
int CSubChart::Attach( DWORD dwID, BOOL bUsePhase)
{
CDataLine *cnew;
CObjColor *cclr;
int nsize = m_cDataLines.GetSize();
CDataSet *pdata = NULL;
ColorDefinition cdef;
UNITMSR uuom;


	nsize = min( 15, nsize);
				// check to see if he's already attached for use by stupid fns that do an attach
	if ( GetMember( dwID))
		return 2;
	
				// if we don't find a pdata then this has a dangling ID
	pdata = (CDataSet *)FindByID( dwID);
	_ASSERTE( pdata != NULL);
	_ASSERTE( pdata->IsKindOf(RUNTIME_CLASS( CDataSet)));

	uuom = pdata->GetUOM();

	if ( ! nsize)		// currently empty, reset vars
		{

		CString cs;

			if ( m_csTitle.GetLength())
				cs = m_csTitle;
			else
				cs = cNullString;
			CreateDefault( cs, uuom);
		}

	cnew = new CDataLine( this);

	cclr = cnew->GetColor();
	cdef = CAudtestApp::GetColorDefinition( false, uuom, nsize);
	cclr->SetDefinition( &cdef);

	cclr = cnew->GetPhaseColor();
	cdef = CAudtestApp::GetColorDefinition( true, uuom, nsize);
	cclr->SetDefinition( &cdef);

	cnew->SetDataID( dwID);
	cnew->ShowPhase( bUsePhase && m_cGridY2.IsVisible());
	cnew->ShowAmp( TRUE);
	m_cDataLines.Add( cnew);

	return 0;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CSubChart::Detach( DWORD dwID)
{
int i;

	i = GetMember( dwID);
	if ( i)			// we have one
		{
		i--;		// base 0
		delete m_cDataLines.GetAt(i);
		m_cDataLines.RemoveAt(i);
		}

}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CSubChart::DetachAll( void)
{

	while ( m_cDataLines.GetSize())			// we have one
		{
		delete m_cDataLines.GetAt(0);
		m_cDataLines.RemoveAt(0);
		}

}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
float	CSubChart::ConvertXLocation( int nIn)	// given an X location, return the float value...
{
	return ConvertLocation( ecXCoord, nIn);
}

// ---------------------------------------------------------------------------
//		ConvertCoord
// given an xyy2 coord get value
// ---------------------------------------------------------------------------
float	CSubChart::ConvertLocation( eCoord eCo, int nIn)
{
	switch( eCo)
	{
	case ecXCoord :
		return m_cGridX.ConvertLocation( nIn);
	case ecYCoord :
		return m_cGridY.ConvertLocation( nIn);
	case ecY2Coord :
		return m_cGridY2.ConvertLocation( nIn);
	default :
		ASSERT(0);
		break;
	}
	return 0.0f;
}

// ---------------------------------------------------------------------------
//		ConvertCoord
// given an xyy2 coord get value
// ---------------------------------------------------------------------------
int		CSubChart::ConvertCoord( eCoord eCo, float fValue)
{
	switch( eCo)
	{
	case ecXCoord :
		return m_cGridX.ConvertCoord( fValue);
	case ecYCoord :
		return m_cGridY.ConvertCoord( fValue);
	case ecY2Coord :
		return m_cGridY2.ConvertCoord( fValue);
	default :
		ASSERT(0);
		break;
	}
	return 0;
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CSubChart::SetMarkerLocation( CMarker *pMarker, int nNew)
{
CAudtestApp *capp;
TESTMARK tm;
CDataSet *cdata = (CDataSet *)GetDatasetAt(0);
int nmark;
float floc;

	if ( ! cdata)
		return;			// nothing to do here

	switch( cdata->GetUOM())		// get the 
		{
		case uomTime :
			nmark = 0;
			break;
		case uomFreq :
			nmark = 1;
			break;
		case uomOhms :
			nmark = 2;
			break;
		default:
			return;
		}

	capp = (CAudtestApp *)AfxGetApp();
	tm = *capp->GetMarker( nmark);		// freq
	floc = ConvertXLocation( nNew);
	if ( pMarker == &m_cMarker1)			// first marker???
		tm.fStart = floc;
	else
		tm.fEnd = floc;
	capp->SetMarker(nmark, &tm);
	pMarker->SetLocation( floc);
}


										// ============================== draw the chart
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CSubChart::DoDraw( CDC *pDC, LPCRECT lpRcDraw)
{
int i;
int nline;
int noldmode;
int nchwidth, nchheight;		// width is width of a string of length 7
float fmin, fmax;
float fstart, fend;
BOOL bdrawphase = FALSE;
CDataLine *cnow;
CDataSet *cdata;
CRect rcDraw;
CRect rcuse;
CPtrArray psData;				// array of all datasets
float fXoffset;					// the offset per item
float fYoffset;					// the offset per item

	psData.SetSize(0,10);		// make it ten max, ten growth

				// make sure all of the data  is still valid

	 for ( i = m_cDataLines.GetSize(); i > 0; i--)
		{
		cnow = GetDataAt(i-1);								// get the id of the dataset
		cdata = (CDataSet *)(FindByID( cnow->GetDataID()));	// look it up
		if ( cdata && (ntDataSet == cdata->GetType()))										// it's a valid entry
			{
			if ( ! cdata->HasPhase())		// don't plot phase if there is none
				cnow->ShowPhase( FALSE);	// turn off phase display
			else
				if ( cnow->IsShowingPhase())
					bdrawphase = TRUE;		// found one with phase, showing
			}
		else
			{
			m_cDataLines.RemoveAt(i-1);		// invalid entry, toss it
			}
		}


	 m_cGridY2.SetVisible( bdrawphase);		// make it visible/invisible

											// have we tossed all entries?
	 for ( i = 0; i < m_cDataLines.GetSize(); i ++)
		{
		cnow = GetDataAt(i);								// get the id of the dataset
		cdata = (CDataSet *)(FindByID( cnow->GetDataID()));	// look it up
		psData.Add( cdata);							// add it to the list
		}

	if ( ! m_cDataLines.GetSize())
		return;

	if ( ! psData.GetSize())				// no one home
		return;

	cdata = (CDataSet *)(psData.GetAt(0));
	if ( ! cdata->GetCount())				// first guy has no data, goodbye
		return;

				// -----------------------------------------------------------------
				//			autoscaling
				// -----------------------------------------------------------------
				//			Frequency range autoscaling
				// -----------------------------------------------------------------

		{
		float f;		// just to run faster
		fmin = (float )1e20;
		fmax = (float )-1e20;
		for ( i=0; i<psData.GetSize(); i++)
			{				// get the data and draw it
			cdata = (CDataSet *)psData[i];
			f = cdata->Minimum( dataFreq);
			if ( fmin > f)
				fmin = f;
			f = cdata->Maximum( dataFreq);
			if ( f > fmax)
				fmax = f;
			}
		if ( fmax < fmin)
			fmax = (float )(fmin + .5);

		if ( m_cGridX.m_bIsLog)			// not time based, so frequency
			{
			if ( fmin <= 1.0f)
				fmin = 1.0f;		// min at freq 1.0 hz arbitrarily!!!!
			}

		m_fMin = fmin;
		m_fMax = fmax;				// set the chart min/max values

		if ( m_cGridX.m_bAutoScale)			// calc scale for X?
			{
			m_cGridX.SetMin( fmin);
			m_cGridX.SetMax( fmax);
			}
		}

	fstart = m_cGridX.GetMin();
	fend   = m_cGridX.GetMax();

				// -----------------------------------------------------------------
				//			Y Axis autoscaling
				// -----------------------------------------------------------------
	if ( m_cGridY.m_bAutoScale)			// calc scale for X?
		{
		fmin = (float )1e20;
		fmax = (float )-1e20;
		for ( i=0; i<m_cDataLines.GetSize(); i++)
			{				// get the data and draw it
			cnow = GetDataAt(i);
			if ( ! cnow->IsShowingAmp())
				continue;						// on to the next one
			cdata = (CDataSet *)psData[i];
			float f;		// just to run faster
			f = cdata->Minimum( dataAmp, fstart, fend);
			if ( fmin > f)
				fmin = f;
			f = cdata->Maximum( dataAmp, fstart, fend);
			if ( f > fmax)
				fmax = f;
			}
		if ( fmax < fmin)
			fmax = (float )(fmin + .5);
		if ( fmin > 0.0f)
		{
			if ( fmax <= 1.001 * fmin)			// it's flat
			{
				fmax = 1.1f * fmin;
				fmin = 0.9f * fmin;		// give it a random range
			}
		}
		else if ( fmin < 0)
		{
			if ( fmax <= 0.999f * fmin)			// it's flat
			{
				fmax = 0.9f * fmin;
				fmin = 1.1f * fmin;		// give it a random range
			}
		}
		else					// fmin == 0
		{
			if ( fmax <= 0.0001f)
			{
				fmax = .1f;
				fmin = -.1f;
			}
		}

		m_cGridY.SetMin( fmin);
		m_cGridY.SetMax( fmax);
		}

				// -----------------------------------------------------------------
				//			Y2 (phase) Axis autoscaling
				// -----------------------------------------------------------------
	if ( bdrawphase && m_cGridY2.m_bAutoScale)			// calc scale for X?
		{
		fmin = (float )1e20;
		fmax = (float )-1e20;
		for ( i=0; i<m_cDataLines.GetSize(); i++)
			{				// get the data and draw it
			cnow = GetDataAt(i);
			if ( ! cnow->IsShowingPhase())
				continue;						// on to the next one
			cdata = (CDataSet *)psData[i];
			float f;		// just to run faster
			f = cdata->Minimum( dataPhase, fstart, fend);
			if ( fmin > f)
				fmin = f;
			f = cdata->Maximum( dataPhase, fstart, fend);
			if ( f > fmax)
				fmax = f;
			}
		if ( fmax < fmin)
			fmax = (float )(fmin + .5);

		m_cGridY2.SetMin( fmin);
		m_cGridY2.SetMax( fmax);
		}
				// -----------------------------------------------------------------
				//			autoticing
	m_cGridX.FixLog();
	m_cGridY.FixLog();
	if ( bdrawphase)
		m_cGridY2.FixLog();


				// -----------------------------------------------------------------


	m_cGridX.CalcAutoTic();		// each grid does its own autoticing
	m_cGridY.CalcAutoTic();
	if ( bdrawphase)
		m_cGridY2.CalcAutoTic();

				// -----------------------------------------------------------------
				//					DRAW
				// -----------------------------------------------------------------
				// who are we drawing into??
	if ( lpRcDraw)
		rcDraw = *lpRcDraw;
	else
		{
		pDC->GetBoundsRect( &rcDraw, 0);
		}

	noldmode = pDC->SetBkMode( TRANSPARENT);		// so lines draw correctly

					// calculate typical string sizes
	rcuse = rcDraw;
	nchheight = CAudtestApp::GetAppFont( ftAxisTitle).DrawString( pDC, "-123.3K", rcuse,  
					DT_CALCRECT | DT_LEFT | DT_TOP | DT_SINGLELINE | DT_NOPREFIX);
	nchwidth = rcuse.Width();
	

				// -----------------------------------------------------------------
				//			draw the background
				// -----------------------------------------------------------------
	{
		CBrush cback( CAudtestApp::GetAppColor( clrBackground));
		pDC->FillRect(rcDraw , &cback);
	}
	
				// -----------------------------------------------------------------
				// draw the title
				// -----------------------------------------------------------------
	if ( ! m_csTitle.IsEmpty())
		{
		CRect rcnew;

		CFxFont &pfont = CAudtestApp::GetAppFont( ftTitle);
			rcuse = rcDraw;
			rcnew = rcuse;			// calculate the font draw size
			pfont.DrawString( pDC, m_csTitle, rcnew,  
				DT_CALCRECT | DT_LEFT | DT_TOP | DT_SINGLELINE | DT_NOPREFIX);
									// add some space for typical string
			rcuse.bottom = rcuse.top + rcnew.Height() + nchheight / 2 - 1;	// the -1 is cuz we're setting bottom
			pfont.DrawString( pDC, m_csTitle, rcuse, 
				DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
			rcDraw.top = rcuse.bottom;		// reset draw rectangle
		}

				// -----------------------------------------------------------------
				// draw the legend
				// -----------------------------------------------------------------

	if ( m_cLegend.IsVisible())
		{
		m_cLegend.ClearStringData();
		for ( i=0; i<psData.GetSize(); i++)
			{				// get the data and calc the rectangles
			cnow = GetDataAt(i);
			cdata = (CDataSet *)psData[i];
			m_cLegend.AddStringData( (LPCSTR )cdata->GetName(), (DWORD )cnow->GetColor()->GetColor());
			}

		m_cLegend.DoDraw( pDC, rcDraw);

						// ---- change the draw rect based on the legend
		m_cLegend.GetDrawRect( &rcuse);			// where did it draw?
		rcDraw.right = rcuse.left - 1;			// our new right hand side
		}

				// -----------------------------------------------------------------
				// draw the axis titles
				// -----------------------------------------------------------------
	CFxFont &pfont = CAudtestApp::GetAppFont( ftAxisTitle);		// *** set this here
				// -----------------------------------------------------------------
				// draw the X axis title
				// -----------------------------------------------------------------
	if ( m_cGridX.m_bShowTitle && m_cGridX.GetTitle().GetLength())
		{
			rcuse = rcDraw;
			rcuse.top = rcuse.bottom - nchheight - nchheight / 3;
			pfont.DrawString( 
				pDC, m_cGridX.GetTitle(), rcuse, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
			rcDraw.bottom = rcuse.top;
		}
				// -----------------------------------------------------------------
				// draw the Y axis title
				// -----------------------------------------------------------------
	if (  m_cGridY.m_bShowTitle && m_cGridY.GetTitle().GetLength())
		{
			rcuse = rcDraw;
			rcuse.bottom -= nchheight + nchheight / 3;		// take out space for the scale text

			rcuse.right = rcuse.left + nchheight + nchheight / 3;
			pfont.DrawStringVertical( pDC, m_cGridY.GetTitle(), rcuse, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
			rcDraw.left = rcuse.right;
		}
				// -----------------------------------------------------------------
				// draw the Phase axis title
				// -----------------------------------------------------------------
	if (  bdrawphase && m_cGridY2.m_bShowTitle && m_cGridY2.GetTitle().GetLength())
		{
			rcuse = rcDraw;
			rcuse.bottom -= nchheight + nchheight / 3;		// take out space for the scale text
			rcuse.left = rcuse.right - nchheight - nchheight / 3;
			pfont.DrawStringVertical( pDC, m_cGridY2.GetTitle(), rcuse, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
			rcDraw.right = rcuse.left;
		}

				// -----------------------------------------------------------------
					// -----------------------------------------------------------------
					// draw the scale
					// -----------------------------------------------------------------
	{
	CRect rcborder;
	int nheight = nchheight;
	int nwidth = nchwidth;

		rcborder = rcDraw;
		if ( m_csTitle.IsEmpty())				// if there's no title, leave a
			rcborder.top += nheight / 3;		// small amount of extra space

		if ( m_cGridY.m_bShowGrid)				// if there's a Y scale
			rcborder.left += m_cGridY.CalcDraw( pDC, rcDraw);

		rcborder.left += nwidth / 4;

		if ( bdrawphase && m_cGridY2.m_bShowGrid)
			rcborder.right -= m_cGridY2.CalcDraw( pDC, rcDraw);

		rcborder.right -= nwidth / 4;

		if ( m_cGridX.m_bShowGrid)
			rcborder.bottom -= nheight;	// room for X scale

		rcborder.bottom -= nheight / 4;

					// --------------------------------------------------------
					// draw the border
					// --------------------------------------------------------
		m_cBorder.DoDraw( pDC, rcborder);
		m_cInside.DoDraw( pDC, rcborder);	// does nothing but set rectangle

					// --------------------------------------------------------
					// draw X Grid and Scale
					// --------------------------------------------------------
		rcuse.left = rcborder.left;
		rcuse.right = rcborder.right;
		rcuse.top = rcborder.bottom + nheight / 4;
		rcuse.bottom = rcDraw.bottom;
		m_cGridX.DrawScale( pDC, rcuse);
		rcuse.top = rcborder.top;
		rcuse.bottom = rcborder.bottom;
		m_cGridX.DoDraw( pDC, rcuse);

					// -------------------------------------------------------
					// draw Y Grid and Scale
					// -------------------------------------------------------
		rcuse.bottom = rcborder.bottom;
		rcuse.top = rcborder.top;
		rcuse.left = rcDraw.left;
		rcuse.right = rcborder.left - nwidth / 8;
		m_cGridY.DrawScale( pDC, rcuse);
		rcuse.left = rcborder.left;
		rcuse.right = rcborder.right;
		m_cGridY.DoDraw( pDC, rcuse);

					// ---------------------------------------------------------
					// draw Phase Grid and Scale
					// ---------------------------------------------------------
		if ( bdrawphase)
			{
			rcuse.left = rcborder.right + nwidth / 8;
			rcuse.right = rcDraw.right;
			m_cGridY2.DrawScale( pDC, rcuse);
			rcuse.left = rcborder.left;
			rcuse.right = rcborder.right;
			m_cGridY2.DoDraw( pDC, rcuse);
			}

		rcDraw = rcborder;
	}
				// -----------------------------------------------------------------
				//			draw the markers
				// -----------------------------------------------------------------
	{			// set visibility to turn off display and mouse-hits
	UNITMSR uom = cdata->GetUOM();		// by now cdata is set to something valid
	int nwhich = (uomTime == uom) ? 0 : (uomFreq == uom) ? 1 : 2;
	BOOL bshow = CAudtestApp::IsMarkerShown( nwhich);
	TESTMARK tm;

		tm = *CAudtestApp::GetMarker( nwhich);
		m_cMarker1.SetLocation( tm.fStart);
		m_cMarker2.SetLocation( tm.fEnd);

		m_cMarker1.SetVisible( bshow);
		m_cMarker2.SetVisible( bshow);
	}

	m_cMarker1.DoDraw( pDC, &rcDraw);
	m_cMarker2.DoDraw( pDC, &rcDraw);

				// -----------------------------------------------------------------
				//			draw data
				// -----------------------------------------------------------------
	fXoffset = 0.0f;
	fYoffset = 0.0f;
	for ( nline=0; nline<m_cDataLines.GetSize(); nline++)
	{				// get the data and draw it
	CRect rcd = rcDraw;			// so we can move it if needed

		if ( m_cGridZ.GetTotal())
		{
			fXoffset = nline * m_cGridZ.GetTotal() * cos( ONEPI * m_cGridZ.GetSlope() / 180 );
			fYoffset = nline * m_cGridZ.GetTotal() * sin( ONEPI * m_cGridZ.GetSlope() / 180 );
			rcd.bottom -= m_cDataLines.GetSize() * m_cGridZ.GetTotal() * sin( ONEPI * m_cGridZ.GetSlope() / 180 );
			rcd.left += m_cDataLines.GetSize() * m_cGridZ.GetTotal() * cos( ONEPI * m_cGridZ.GetSlope() / 180 );
			m_cGridX.m_fZOffset = fXoffset;
			m_cGridY.m_fZOffset = fYoffset;
			rcd.OffsetRect( (int )fXoffset, (int )fYoffset);	// move around here
			((CDataLine *)(m_cDataLines.GetAt( nline)))->SetShow3d( TRUE);
		}

		((CDrawObj *)m_cDataLines.GetAt( nline))->DoDraw( pDC, &rcd);
		((CDataLine *)(m_cDataLines.GetAt( nline)))->SetShow3d( FALSE);
	}
	m_cGridX.m_fZOffset = 0.0f;
	m_cGridY.m_fZOffset = 0.0f;		// reset them


				// -----------------------------------------------------------------
				//			draw tags
				// -----------------------------------------------------------------
	for ( i=0; i<m_cTags.GetSize(); i++)
	{
		m_cTags[i].DoDraw( pDC, &rcDraw);
	}

	pDC->SetBkMode( noldmode);		// so lines draw correctly

}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
CDataLine *CSubChart::GetDataAt( int i)
{
	if ( i < 0 || i >= m_cDataLines.GetSize() )
		return NULL;

	return (CDataLine *)m_cDataLines.GetAt(i);
}


// ---------------------------------------------------------------------------
//			GetDatasetAt
// ---------------------------------------------------------------------------
CDataSet *CSubChart::GetDatasetAt( int i)
{
CDataLine *cp;

	if ( i < 0 || i >= m_cDataLines.GetSize() )
		return NULL;

	cp = (CDataLine *)m_cDataLines.GetAt(i);
	return (CDataSet *)FindByID( cp->GetDataID() );

}

// ---------------------------------------------------------------------------
//			GetGrid
// ---------------------------------------------------------------------------
CGrid *CSubChart::GetGrid( eCoord ecGrid)
{
	switch( ecGrid)
	{
	case ecXCoord :
		return &m_cGridX;
	case ecYCoord :
		return &m_cGridY;
	case ecY2Coord :
		return &m_cGridY2;
	case ecZCoord :
		return &m_cGridZ;
	default :
		ASSERT(0);
		break;
	}
	return &m_cGridX;

}


// set to the default parameters for this data set
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CSubChart::CreateDefault(LPCSTR szName, UNITMSR uUom )
{
CString cs;
TESTMARK tm;

 	m_csTitle = szName;

	m_cGridX.SetVisible( TRUE);			// default all visible
	m_cGridY.SetVisible( TRUE);
	m_cGridY2.SetVisible( TRUE);
	m_cGridX.SetColor( 0, CAudtestApp::GetAppColor( clrGrid));
	m_cGridY.SetColor( 0, CAudtestApp::GetAppColor( clrGrid));

	m_cGridX.SetLog( FALSE);			// default all linear
	m_cGridY.SetLog( FALSE);
	m_cGridY2.SetLog( FALSE);

	cs.LoadString( IDSCH_FREQUENCY);		// default freq/amp/phase
	m_cGridX.SetTitle( cs);
	cs.LoadString( IDSCH_AMPLITUDE);
	m_cGridY.SetTitle( cs);
	cs.LoadString( IDSCH_PHASE);
	m_cGridY2.SetTitle( cs);

	m_cGridY2.SetMin( (float )-180);	// set y2 up for phase display
	m_cGridY2.SetMax( (float )180);

	tm = *CAudtestApp::GetMarker( uUom);

	m_cMarker1.SetLocation( tm.fStart);
	m_cMarker2.SetLocation( tm.fEnd);
	m_cMarker1.SetVisible( tm.bUse);
	m_cMarker2.SetVisible( tm.bUse);

	switch( uUom)
		{
		case uomTime:
			m_cGridY2.SetVisible( FALSE);		// no phase
			cs.LoadString( IDSCH_TIME);
			m_cGridX.SetTitle( cs);
			break;
		case uomFreq:
			m_cGridX.SetLog( TRUE);
			cs.LoadString( IDSCH_AMPDB);
			m_cGridY.SetTitle( cs);
			break;
		case uomOhms:
			m_cGridX.SetLog( TRUE);
			cs.LoadString( IDSCH_IMPEDANCE);
			m_cGridY.SetTitle( cs);
			break;
		case uomNone:
			break;
		}

	if ( strcmp( szName, "xxx")	)		// the special no-inherit default
		InheritDefault( CAudtestApp::GetDefaultChart( uUom));
	else
	{
		CMiniChart cmini;
		UINT uid;
		CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
		switch( uUom)
		{
		case uomTime :
			uid = IDS_DEFCHARTTIME;
			break;
		case uomFreq :
			uid = IDS_DEFCHARTFREQ;
			break;
		case uomOhms :
			uid = IDS_DEFCHARTOHM;
			break;
		default:
			uid = 0;
			break;		// not going to happen
		}
		if ( uid && ! capp->ReadRegistry( uid, &cmini))	// there is a default
			FromMiniChart( &cmini);
	}
}


// set to the default parameters for this data set
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CSubChart::InheritDefault(CSubChart *pDefault)
{
bool bphase;
int i;
CDataLine *cnow;
CObjColor *cclr;
ColorDefinition cdef;
UNITMSR uuom;

	uuom = GetUom();

	pDefault->m_cGridX.CopyFormat( &m_cGridX);
	pDefault->m_cGridY.CopyFormat( &m_cGridY);
	pDefault->m_cGridY2.CopyFormat( &m_cGridY2);

	bphase = 0 != m_cGridY2.IsVisible();			// phase equivalent to visibility of Y2 grid

	for ( i = 0; i < m_cDataLines.GetSize(); i ++)
	{
		cnow = GetDataAt(i);								// get the id of the dataset
		cnow->ShowPhase( bphase);

		cclr = cnow->GetColor();
		cdef = CAudtestApp::GetColorDefinition( false, uuom, i);
		cclr->SetDefinition( &cdef);

		cclr = cnow->GetPhaseColor();
		cdef = CAudtestApp::GetColorDefinition( true, uuom, i);
		cclr->SetDefinition( &cdef);

	}



}


// set to the default parameters for this data set
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CSubChart::MakeDefault(int nDefault, CSubChart *pDefault)
{
	CAudtestApp::SetDefaultChart( nDefault, pDefault);
}

// get the unit of measure for this chart if there is one
UNITMSR		CSubChart::GetUom( void)
{
CDataSet *cd = GetDatasetAt( 0);

	if ( ! cd)
		return uomNone;

	return cd->GetUOM();		// return the first uom

}


// ---------------------------------------------------------------------------
// --------------  ZoomOut( CPoint)
// ---------------------------------------------------------------------------
int		CSubChart::ZoomOut( CPoint cPoint)		// zoom out at a point
{
CRect rcdraw;
int nxmin, nxmax;
float fmin, fmax;

	m_cGridX.GetDrawRect( (LPRECT ) rcdraw);
	nxmin = cPoint.x - rcdraw.Width();
	nxmax = cPoint.x + rcdraw.Width();

	fmin = m_cGridX.ConvertLocation( nxmin);
	fmax = m_cGridX.ConvertLocation( nxmax);

	if ( fmin < GetMinimum())
		fmin = GetMinimum();
	if ( fmax > GetMaximum())
		fmax = GetMaximum();

	m_cGridX.SetMin( fmin);
	m_cGridX.SetMax( fmax);
	m_cGridX.SetAuto(1, FALSE);

	return 0;		// worked ok


}


// ---------------------------------------------------------------------------
// --------------  Zoom( CPoint)
// ---------------------------------------------------------------------------
int		CSubChart::Zoom( void)		// zoom out to 1:1
{
	if ( m_cGridX.GetAuto( 1) && m_cGridY.GetAuto(1))
		return 1;			// nothing to do

	m_cGridX.SetAuto(1, TRUE);
	m_cGridY.SetAuto(1, TRUE);

	return 0;		// worked ok


}

// ---------------------------------------------------------------------------
// --------------  Zoom( CPoint)
// ---------------------------------------------------------------------------
int		CSubChart::Zoom( CPoint cPoint)		// zoom in on a point
{
RECT rcdraw;
int nxmin, nxmax;
float fmin, fmax;

	m_cGridX.GetDrawRect( & rcdraw);
	nxmin = (cPoint.x + rcdraw.left) / 2;
	nxmax = (cPoint.x + rcdraw.right) / 2;

	if ( (nxmin < rcdraw.left) || (nxmax > rcdraw.right) )
		return 1;			// do nothing

	fmin = m_cGridX.ConvertLocation( nxmin);
	fmax = m_cGridX.ConvertLocation( nxmax);

	m_cGridX.SetMin( fmin);
	m_cGridX.SetMax( fmax);
	m_cGridX.SetAuto(1, FALSE);

	return 0;		// worked ok


}


// ---------------------------------------------------------------------------
// --------------  Zoom( CRect)
// ---------------------------------------------------------------------------
int		CSubChart::Zoom( CRect cRange)		// zoom into a box
{
RECT rcborder;
float fmin, fmax;
BOOL bchangex, bchangey;

	GetBorder( &rcborder);

	if ( (rcborder.left == cRange.left) && (rcborder.right == cRange.right) )
		bchangex = FALSE;
	else
		bchangex = TRUE;
	if ( (rcborder.top == cRange.top) && (rcborder.bottom == cRange.bottom) )
		bchangey = FALSE;
	else
		bchangey = TRUE;

	if ( bchangex)
		{
		fmin = m_cGridX.ConvertLocation( cRange.left);
		fmax = m_cGridX.ConvertLocation( cRange.right);
		m_cGridX.SetMin( fmin);
		m_cGridX.SetMax( fmax);
		m_cGridX.SetAuto(1, FALSE);
		}

	if ( bchangey)
		{
		fmin = m_cGridY.ConvertLocation( cRange.bottom);
		fmax = m_cGridY.ConvertLocation( cRange.top);
		m_cGridY.SetMin( fmin);
		m_cGridY.SetMax( fmax);
		m_cGridY.SetAuto(1, FALSE);
		}

	return 0;		// worked ok


}

// ---------------------------------------------------------------------------
// --------------  AddNote
// ---------------------------------------------------------------------------
CDataTag	*CSubChart::AddNote( CDataTag &cTag)
{

	m_cTags.Add( cTag);

	return & m_cTags[ m_cTags.GetSize() - 1];

}

// ---------------------------------------------------------------------------
// --------------  DeleteNote
// ---------------------------------------------------------------------------
void	CSubChart::DeleteNote( CDataTag *pTag)
{
int i, nsize;

	nsize = m_cTags.GetSize();

	for ( i=0; i<nsize; i++)
	{
		if ( pTag == &m_cTags[i])
			break;
	}
	if ( i == nsize)
	{
		ASSERT(0);			// we shouldn't get here!
		return;
	}
	for( i++; i<nsize; i++)
		m_cTags[i-1] = m_cTags[i];		// copy them down
	m_cTags.SetSize( nsize-1, 5);		// and that's it
}



/////////////////////////////////////////////////////////////////////////////
// CSubChart diagnostics

#ifdef _DEBUG
void CSubChart::AssertValid() const
{
	CNamed::AssertValid();
}

void CSubChart::Dump(CDumpContext& dc) const
{
	CNamed::Dump(dc);
}

#endif //_DEBUG




// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

IMPLEMENT_SERIAL(CDataLine, CDrawObj, VERSIONABLE_SCHEMA | 225)


/////////////////////////////////////////////////////////////////////////////
// CDataLine construction/destruction

CDataLine::CDataLine( CNamed *pParent) : m_ccLine( RGB(0,0,0)),  m_ccPhase( RGB(0,0,0),1,PS_DOT)
{
	// TODO: add one-time construction code here
	m_bShowPhase = TRUE;
	m_bShowAmp = TRUE;
	m_pParent = pParent;
	m_bShow3d = FALSE;
}

CDataLine::CDataLine() : m_ccLine( RGB(0,0,0)),  m_ccPhase( RGB(0,0,0),1,PS_DOT)
{
	// TODO: add one-time construction code here
	m_bShowPhase = TRUE;
	m_bShowAmp = TRUE;
	m_pParent = NULL;
	m_bShow3d = FALSE;
}

CDataLine::~CDataLine()
{

}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
CDataLine &CDataLine::operator=(const CDataLine &cIn)
{
	CDrawObj::operator=( cIn);

	m_ccLine		= cIn.m_ccLine;			// line color
	m_ccPhase		= cIn.m_ccPhase;		// phase color
	m_dwID			= cIn.m_dwID;			// id of the line to draw
	m_bShowPhase	= cIn.m_bShowPhase;		// show the phase of this guy (if he has one)
	m_bShowAmp		= cIn.m_bShowAmp;		// show the amplitude of this guy (if he has one)
	m_bShow3d		= cIn.m_bShow3d;		// showing in 3d (polygon?)

 					// don't copy the id #
 	return *this;
}





/////////////////////////////////////////////////////////////////////////////
// CDataLine serialization

void CDataLine::Serialize(CArchive& ar)
{
WORD w;

	CDrawObj::Serialize( ar);

	m_ccLine.Serialize( ar);
	m_ccPhase.Serialize( ar);

	if (ar.IsStoring())
		{
					// storing code here
		ar << m_dwID;
		w = (WORD )m_bShowPhase; ar << w;
		w = (WORD )m_bShowAmp; ar << w;
		}
	else
		{
					// loading code here 
		ar >> m_dwID;
		ar >> w; m_bShowPhase = (BOOL )w;
		ar >> w; m_bShowAmp = (BOOL )w;
		}
}



/////////////////////////////////////////////////////////////////////////////
// CDataLine diagnostics

#ifdef _DEBUG
void CDataLine::AssertValid() const
{
	CObject::AssertValid();
}

void CDataLine::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawObj operations


static int limit_Coord( int nCoord, int nMin, int nMax)
{
	if ( nCoord > nMin && nCoord < nMax)
		return nCoord;
	if ( nCoord > nMin)
		return nMax;
	return nMin;
}



int CDataLine::CreateDrawing( LPPOINT ptDraw, CDataSet *pData, DATASEL dataSel, LPCRECT lprcDraw)
{
float fend, famp, ffreq;
int nstart, nend;
int nx, ny, ny2, nlast;
CGrid *xgrid;
CGrid *ygrid;
POINT pt;
CSubChart *cch = (CSubChart *)m_pParent;
RECT rcDraw = *lprcDraw;
bool bwassingle;
int i;
int icurrent = 0;

		xgrid  = cch->GetGrid( ecXCoord);
		ygrid  = cch->GetGrid( (dataSel == dataAmp) ? ecYCoord : ecY2Coord);
					// calculate the starting and ending indices
		ffreq = xgrid->ConvertLocation( rcDraw.left);	// get left coord as a freq
		if ( ffreq < pData->Minimum(dataFreq))
			nstart = 0;
		else
			nstart = pData->FreqToIndex( ffreq);			// convert to index
		ffreq = xgrid->ConvertLocation( rcDraw.right);	// get right coord as freq
		if ( ffreq > pData->Maximum(dataFreq))
			nend = pData->GetCount() - 2;
		else
			nend = 1 + pData->FreqToIndex( ffreq);				// ditto

		if ( nstart < 0)
			nstart = 0;
		if ( nend >= (pData->GetCount()-1))
			nend = pData->GetCount() - 2;
		if ( nstart > nend)
			return 0;

		ffreq =  pData->DataAt(dataFreq, nstart);
		nx = xgrid->ConvertCoord( ffreq);
		famp = pData->DataAt( dataSel, nstart);
		ny = ygrid->ConvertCoord( famp);
		ny = limit_Coord( ny, rcDraw.top, rcDraw.bottom);
		bwassingle = TRUE;
		pt.x = nx;
		pt.y = ny;
		ptDraw[icurrent++] = pt;
//		pDC->MoveTo( nx, ny);
		for ( i=nstart; i <= nend; i++)
		{
			ffreq = pData->DataAt(dataFreq, i);
			nx = xgrid->ConvertCoord( ffreq);
			if ( nx != xgrid->ConvertCoord(pData->DataAt( dataFreq, i+4)))
			{
				famp = pData->DataAt( dataSel, i);
				ny = ygrid->ConvertCoord( famp);
				ny = limit_Coord( ny, rcDraw.top, rcDraw.bottom);
				bwassingle = TRUE;
				pt.x = nx;
				pt.y = ny;
				ptDraw[icurrent++] = pt;

//				pDC->LineTo( nx, ny);
			}
			else		// more than 2 people at the same X spot
			{
				fend = xgrid->ConvertLocation( nx+1);
				nlast = pData->FreqToIndex( fend) - 1;
				if ( nlast < i)			// whacko
					nlast = i;			// fix it if very tiny values
				fend = pData->DataAt( dataFreq, nlast);	// last freq in range

				famp = pData->Minimum( dataSel, ffreq, fend);
				ny = ygrid->ConvertCoord( famp);
				ny = limit_Coord( ny, rcDraw.top, rcDraw.bottom);
				
				famp = pData->Maximum( dataSel, ffreq, fend);
				ny2 = ygrid->ConvertCoord( famp);
				ny2 = limit_Coord( ny2, rcDraw.top, rcDraw.bottom);

				pt.x = nx;
				pt.y = ny;
				ptDraw[icurrent++] = pt;
	//			if ( bwassingle)
	//				pDC->LineTo( nx, ny);
	//			else
	//				pDC->MoveTo( nx, ny);
				if ( ny2 != ny)
				{
					pt.x = nx;
					pt.y = ny;
					ptDraw[icurrent++] = pt;
	//				pDC->LineTo( nx, ny2 + ((ny2 > ny) ? 1 : -1));		// draw a vertical line
	//				pDC->MoveTo( nx, (ny2 + ny) / 2);	// go to the midpoint
				}
				bwassingle = FALSE;
				i = nlast;
			}
		}

	if ( icurrent)			// we have some data, add the last two points
	{
		famp = ygrid->GetMin();						// get min Y grid value
		ny = ygrid->ConvertCoord( famp) - 1;			// get the Y coord of that
		famp = xgrid->GetMax();						// get min Y grid value
		nx = xgrid->ConvertCoord( famp)-1;			// get the Y coord of that
		pt.x = nx;
		pt.y = ny;
		ptDraw[icurrent++] = pt;
		famp = xgrid->GetMin();						// get min Y grid value
		nx = xgrid->ConvertCoord( famp)+1;			// get the Y coord of that
		pt.x = nx;
		pt.y = ny;
		ptDraw[icurrent++] = pt;					// this makes a solid polygon
	}

	return icurrent;
}


void CDataLine::DoDraw( CDC *pDC, LPCRECT lprcDraw)
{
CRect rcDraw = *lprcDraw;
CDataSet *cdata;
int nwidth, nheight;
CPen *coldpen;
CBrush *poldbrush;
CGrid *xgrid;
CSubChart *cch = (CSubChart *)m_pParent;
POINT *ptdraw;
int ipoints;
CPen *cpen;


	SetDrawRect( &rcDraw);			// here's our rectangle, save it for later
	nwidth = 1+rcDraw.right - rcDraw.left;
	nheight = 1+rcDraw.bottom - rcDraw.top;

	if ( (nwidth <= 5) || (nheight <= 5) || (!m_pParent) || ! IsVisible())
		return;

	ASSERT_KINDOF( CSubChart,  m_pParent);

	cdata = (CDataSet *)(cch->FindByID( GetDataID()));

	if ( cdata->GetCount())
	{
		float ffreq;
		int nstart, nend;

		xgrid  = cch->GetGrid( ecXCoord);

					// calculate the starting and ending indices

		ffreq = xgrid->ConvertLocation( rcDraw.left);	// get left coord as a freq
		if ( ffreq < cdata->Minimum(dataFreq))
			nstart = 0;
		else
			nstart = cdata->FreqToIndex( ffreq);			// convert to index
		ffreq = xgrid->ConvertLocation( rcDraw.right);	// get right coord as freq
		if ( ffreq > cdata->Maximum(dataFreq))
			nend = cdata->GetCount() - 2;
		else
			nend = 1 + cdata->FreqToIndex( ffreq);				// ditto

		if ( nstart < 0)
			nstart = 0;
		if ( nend >= (cdata->GetCount()-1))
			nend = cdata->GetCount() - 2;
		if ( nstart > nend)
			return;

		ptdraw = new POINT[2 + 2 * (1 + nend - nstart)];		// 2 extra to finish the polygon
					// clip to the drawing area
		pDC->IntersectClipRect( &rcDraw);

		if ( IsShowingPhase())
		{
			ipoints = CreateDrawing( ptdraw, cdata, dataPhase, rcDraw);		// create the drawing
			if ( ipoints > 2)
			{
				cpen = GetPhaseColor()->BuildPen();
				coldpen = pDC->SelectObject( cpen);
				if ( ! m_bShow3d)
					pDC->Polyline( ptdraw, ipoints-2);		// draw it
				else
					pDC->Polygon( ptdraw, ipoints);			// draw it
				pDC->SelectObject( coldpen);
				delete cpen;
			}
		}
		if ( IsShowingAmp())
		{
			ipoints = CreateDrawing( ptdraw, cdata, dataAmp, rcDraw);		// create the drawing
			if ( ipoints > 2)
			{
				if ( ! m_bShow3d)
				{
					cpen = GetColor()->BuildPen();
					coldpen = pDC->SelectObject( cpen);
					pDC->Polyline( ptdraw, ipoints-2);		// draw it
					pDC->SelectObject( coldpen);
					delete cpen;
				}
				else
				{
				CBrush cbr( GetColor()->GetColor());		// looks dumb but is right
				CPen   pen(PS_SOLID, 1, RGB(0,0,0));		// solid black pen
					coldpen = pDC->SelectObject( &pen);
					poldbrush = pDC->SelectObject( &cbr);	// use this brush
					pDC->Polygon( ptdraw, ipoints);			// draw it
					pDC->SelectObject( poldbrush);
					pDC->SelectObject( coldpen);
				}
			}
		}
		DrawHighlight( pDC);				// now's the time

		delete[] ptdraw;
							// clip to the drawing area
		pDC->SelectClipRgn( (CRgn *) NULL );
	}			// endif count


}

BOOL CDataLine::HitTest( CPoint cPt, UINT *)
{
CGrid *xgrid, *ygrid;
CSubChart *cch = (CSubChart *)m_pParent;

	if ( ! m_pParent)
		return FALSE;

CDataSet *cd = (CDataSet *)cch->FindByID( GetDataID() );

	if ( ! cd)
		return FALSE;

	xgrid = cch->GetGrid( ecXCoord);
	ygrid = cch->GetGrid( ecYCoord);

float ffreq = xgrid->ConvertLocation( cPt.x);

int nindex = cd->FreqToIndex( ffreq);

float fmin = cd->DataAt( dataFreq, nindex - 2);
float fmax = cd->DataAt( dataFreq, nindex + 2);

float fdatamax = cd->Maximum( dataAmp, fmin, fmax);
float fdatamin = cd->Minimum( dataAmp, fmin, fmax);

RECT rclook;

	rclook.left = xgrid->ConvertCoord( fmin) - 2;
	rclook.right = xgrid->ConvertCoord( fmax) + 2;
	rclook.top = ygrid->ConvertCoord( fdatamax) - 2;
	rclook.bottom = ygrid->ConvertCoord( fdatamin) + 2;

	return ( ::PtInRect( &rclook, cPt));

}


void CDataLine::DrawHighlight( CDC *pDC)
{
	if ( ! IsHighlighted() )			// highlighted....draw a box
		return;

CGrid *xgrid, *ygrid;
CSubChart *cch = (CSubChart *)m_pParent;
RECT rclook;

	if ( ! m_pParent)
		return;

CDataSet *cd = (CDataSet *)cch->FindByID( GetDataID() );
int i, nmin, nmax;

	if ( ! cd)
		return;

	xgrid = cch->GetGrid( ecXCoord);
	ygrid = cch->GetGrid( ecYCoord);

	xgrid->GetDrawRect( &rclook);

				// now rclook is the x drawing area (good enough for us)
	nmin = xgrid->ConvertCoord( cd->Minimum( dataFreq));
	if ( nmin < rclook.left)
		nmin = rclook.left;
	nmax = xgrid->ConvertCoord( cd->Maximum( dataFreq));
	if ( nmax > rclook.right)
		nmax = rclook.right;

	for ( i=nmin; i<nmax; i+= 20)			// every 20 pels (randomly)
		{
		float ffreq = xgrid->ConvertLocation( i);	// convert to freq
		float fdata = cd->DataValueAt( ffreq);			// get data value
		int n = ygrid->ConvertCoord( fdata); // convert to pixel coord
		pDC->Ellipse( i -4, n - 4,i + 4, n + 4);
		}


}


// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

IMPLEMENT_SERIAL(CLegend, CDrawObj, VERSIONABLE_SCHEMA | 227)


/////////////////////////////////////////////////////////////////////////////
// CLegend construction/destruction

CLegend::CLegend() : m_pcNames(), m_pcColors()
{
	// TODO: add one-time construction code here
	m_wShape = 1;
	m_pcNames.SetSize(0,5);
	m_pcColors.SetSize(0,5);
}

CLegend::~CLegend()
{

}

/////////////////////////////////////////////////////////////////////////////
// CLegend serialization

void CLegend::Serialize(CArchive& ar)
{

	CDrawObj::Serialize( ar);

	if (ar.IsStoring())
		{					// storing code here
		ar << m_wShape;
		}
	else
		{					// loading code here 
		ar >> m_wShape;
		}
}


				// operators
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
CLegend &CLegend::operator=(const CLegend &cIn)
{
 	CDrawObj::operator=( cIn);
					// don't copy the id #
	m_wShape = cIn.m_wShape;
 	return *this;
}




/////////////////////////////////////////////////////////////////////////////
// CLegend diagnostics

#ifdef _DEBUG
void CLegend::AssertValid() const
{
	CObject::AssertValid();
}

void CLegend::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawObj operations


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void	CLegend::AddStringData( LPCSTR lpNew, COLORREF rgbNew)
{
 	m_pcNames.Add( lpNew);
	m_pcColors.Add( (DWORD )rgbNew);
}



// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CLegend::DoDraw( CDC *pDC, LPCRECT lprcDraw)
{
CFont *cfold, *cfnew;
COLORREF rgbold;
short i;

	if ( ! IsVisible())
		return;

	cfnew = CAudtestApp::GetAppFont( ftLegend).GetCurrentFont( pDC);
	if ( ! cfnew)
		return;

	cfold = pDC->SelectObject( cfnew);
	rgbold = pDC->SetTextColor( CAudtestApp::GetAppFont(ftLegend).GetColor() );


CString csmax;
RECT rcmax;
int nheight;

	::SetRect( &rcmax, 0,0,0,0);

						// get max drawing size for a line of text
	for ( i=0; i<m_pcNames.GetSize(); i++)
		{				// get the data and calc the rectangles
		csmax = m_pcNames.GetAt( i);
		RECT rcuse;

		::SetRect( &rcuse, 0,0,1000,1000);
		pDC->DrawText( (LPCSTR )csmax, -1, &rcuse,  DT_LEFT | DT_TOP | DT_NOPREFIX | DT_CALCRECT);

		if ( rcuse.right > rcmax.right)
			rcmax.right = rcuse.right;

		if ( rcuse.bottom > rcmax.bottom)
			rcmax.bottom = rcuse.bottom;
		}

				// now rcmax is the size of the biggest line
	nheight = rcmax.bottom - rcmax.top + 1;
	rcmax.bottom = rcmax.top + nheight * m_pcNames.GetSize();	// now enough for each line

	rcmax.right += 18 + 12;			// 18 for color box + 12 for extra


									// now convert to screen coords
	rcmax.left = lprcDraw->right - (rcmax.right - rcmax.left);
									// vertical center
	rcmax.top = (lprcDraw->top + lprcDraw->bottom - rcmax.bottom + rcmax.top) / 2;
	rcmax.bottom += rcmax.top;
	rcmax.right += rcmax.left;				// move over

						// draw the border
	rcmax.right -= 6;				// move over some
	rcmax.left += 6;				// again

	draw_Border( pDC, rcmax);

	SetDrawRect( &rcmax);			// here's our rectangle, save it for later
	
						// now draw the text
	CBrush cbrush;
	CBrush *coldb;
	for ( i=0; i<m_pcNames.GetSize(); i++)
		{				// get the data and draw it
		csmax = m_pcNames.GetAt(i);
		RECT rcuse;

		::SetRect( &rcuse, rcmax.left, rcmax.top + i * nheight, 
							rcmax.right, rcmax.top + (i+1) * nheight);

		cbrush.CreateSolidBrush( (COLORREF )m_pcColors.GetAt(i));
		coldb = pDC->SelectObject( &cbrush);
		pDC->Rectangle( rcuse.left+2, rcuse.top+2, rcuse.left+13, rcuse.top+13);
		pDC->SelectObject( coldb);
		cbrush.DeleteObject();

		rcuse.left += 15;			// move over

		pDC->DrawText( (LPCSTR )csmax, -1, &rcuse,  DT_LEFT | DT_TOP | DT_NOPREFIX);
		}

	pDC->SelectObject( cfold);
	pDC->SetTextColor( rgbold);

}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
IMPLEMENT_SERIAL(CMarker, CDrawObj, VERSIONABLE_SCHEMA | 258)

/////////////////////////////////////////////////////////////////////////////
// CMarker construction/destruction

CMarker::CMarker()
{
	// TODO: add one-time construction code here
	m_fLocation = 0.0f;
	m_pGrid = NULL;
}

CMarker::~CMarker()
{

}

/////////////////////////////////////////////////////////////////////////////
// CMarker serialization
void CMarker::Serialize(CArchive& ar)
{
	CDrawObj::Serialize( ar);
	if ( ar.IsStoring())
		ar << m_fLocation;
	else
		ar >> m_fLocation;
}


				// operators
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
CMarker &CMarker::operator=(const CMarker &cIn)
{
 	CDrawObj::operator=( cIn);
					// don't copy the id #
	m_fLocation = cIn.m_fLocation;
 	return *this;
}




/////////////////////////////////////////////////////////////////////////////
// CMarker diagnostics

#ifdef _DEBUG
void CMarker::AssertValid() const
{
	CObject::AssertValid();
}

void CMarker::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawObj operations


// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CMarker::DoDraw( CDC *pDC, LPCRECT lprcDraw)
{
CRect crTotal;
int nloc;
CBrush cnewbrush;

	crTotal.SetRect( 0,0,0,0);
	SetDrawRect( crTotal);

	if ( (! m_pGrid) || ! IsVisible())
		return;

	if ( m_fLocation < m_pGrid->GetMin() || m_fLocation > m_pGrid->GetMax() )
		return;

	crTotal = *lprcDraw;

	cnewbrush.CreateSolidBrush( RGB(140,0,0));

CGdiObject *coldbrush = pDC->SelectObject( &cnewbrush);

	nloc = m_pGrid->ConvertCoord( m_fLocation);

	pDC->PatBlt( nloc-1, crTotal.top, 3, 1+crTotal.bottom - crTotal.top, PATCOPY);

	pDC->SelectStockObject( GRAY_BRUSH);
	cnewbrush.DeleteObject();
	pDC->PatBlt( nloc, crTotal.top, 1, 1+crTotal.bottom - crTotal.top, PATCOPY);

	pDC->SelectStockObject( BLACK_BRUSH);
	pDC->PatBlt( nloc+1, crTotal.top, 1, 1+crTotal.bottom - crTotal.top, PATCOPY);

	pDC->SelectObject( coldbrush);

	crTotal.left = nloc - 1;
	crTotal.right = nloc + 1;

	SetDrawRect( crTotal);
}


// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

IMPLEMENT_SERIAL(CBorder, CDrawObj, VERSIONABLE_SCHEMA | 257)


/////////////////////////////////////////////////////////////////////////////
// CBorder construction/destruction

CBorder::CBorder()
{
}

CBorder::~CBorder()
{
}

/////////////////////////////////////////////////////////////////////////////
// CBorder serialization

void CBorder::Serialize(CArchive& ar)
{
	CDrawObj::Serialize( ar);
}

				// operators
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
CBorder &CBorder::operator=(const CBorder &cIn)
{ 					// don't copy the id #
	CDrawObj::operator=( cIn);
 	return *this;
}




/////////////////////////////////////////////////////////////////////////////
// CBorder diagnostics

#ifdef _DEBUG
void CBorder::AssertValid() const
{
	CDrawObj::AssertValid();
}

void CBorder::Dump(CDumpContext& dc) const
{
	CDrawObj::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBorder operations


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CBorder::DoDraw( CDC *pDC, LPCRECT lprcDraw)
{
CRect crTotal = *lprcDraw;

	draw_Border( pDC, crTotal);
	SetDrawRect( crTotal);

}

BOOL CBorder::HitTest( CPoint cPt, UINT *)
{
CRect rcdraw;

	GetDrawRect( &rcdraw);

	rcdraw.InflateRect( 4, 4);		// 4 pixel grace

	if ( ! rcdraw.PtInRect( cPt))
		return FALSE;

	rcdraw.InflateRect( -8, -8);	// both ways
	if ( rcdraw.PtInRect( cPt))
		return FALSE;

	return TRUE;

}


// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

IMPLEMENT_SERIAL(CInside, CDrawObj, VERSIONABLE_SCHEMA | 257)


/////////////////////////////////////////////////////////////////////////////
// CInside construction/destruction

CInside::CInside()
{
}

CInside::~CInside()
{
}

/////////////////////////////////////////////////////////////////////////////
// CInside serialization

void CInside::Serialize(CArchive& ar)
{
	CDrawObj::Serialize( ar);
}

				// operators
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
CInside &CInside::operator=(const CInside &cIn)
{ 					// don't copy the id #
 	CDrawObj::operator=( cIn);
	return *this;
}




/////////////////////////////////////////////////////////////////////////////
// CInside diagnostics

#ifdef _DEBUG
void CInside::AssertValid() const
{
	CDrawObj::AssertValid();
}

void CInside::Dump(CDumpContext& dc) const
{
	CDrawObj::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInside operations


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CInside::DoDraw( CDC *, LPCRECT lprcDraw)
{
CRect crTotal = *lprcDraw;

	SetDrawRect( crTotal);

}

BOOL CInside::HitTest( CPoint cPt, UINT *)
{
CRect rcdraw;

	GetDrawRect( &rcdraw);

	rcdraw.InflateRect( -2, -2);		// 4 pixel grace

	return rcdraw.PtInRect( cPt);
}


void CSubChart::GetBorder( LPRECT lprcDest)
{
CGrid *cgr;
RECT rc;

	cgr = GetGrid( ecXCoord);		// ge tthe x grid
	cgr->GetDrawRect( &rc);
	lprcDest->left = rc.left;
	lprcDest->right = rc.right;
	cgr = GetGrid( ecYCoord);		// get the y grid
	cgr->GetDrawRect( &rc);
	lprcDest->top = rc.top;
	lprcDest->bottom = rc.bottom;

}



/////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
CNamed *CSubChart::Duplicate(void )
{
CSubChart *cnew = new CSubChart();

	*cnew = *this;
	return cnew;
}


				// operators
// ---------------------------------------------------------------------------
CSubChart &CSubChart::operator=(const CSubChart &cIn)
{
CNamed &cin = (CNamed &)cIn;

	*this = cin;
 	return *this;
}


// ---------------------------------------------------------------------------
CNamed &CSubChart::operator=(const CNamed &cIn)
{
CSubChart &cin = (CSubChart &)cIn;

	CNamed::operator=( cIn);
 					// don't copy the id #
	m_csTitle = cin.m_csTitle;		// the title
	m_cGridX= cin.m_cGridX;		// the bottom grid
	m_cGridY= cin.m_cGridY;		// the left hand side grid
	m_cGridY2= cin.m_cGridY2;		// the right hand side grid
	m_cGridZ = cin.m_cGridZ;
	m_cBorder = cin.m_cBorder;
	m_cInside = cin.m_cInside;
	m_cLegend= cin.m_cLegend;		// the legend if any
	m_cMarker1 = cin.m_cMarker1;
	m_cMarker1.SetGrid( &m_cGridX);
	m_cMarker2 = cin.m_cMarker2;
	m_cMarker2.SetGrid( &m_cGridX);

	::KillArray( &m_cDataLines);		// remove any prior datasets

	{					// copy the datalines
	int i,nsize;
	
		nsize = cin.m_cDataLines.GetSize();
		for ( i=0; i<nsize; i++)
			{
			CDataLine *pd, *ps;

				ps = (CDataLine *)cin.m_cDataLines.GetAt(i);
				pd = new CDataLine( this);
				*pd = *ps;
				m_cDataLines.Add( pd);
			}
	}

	{			// process the tags array
	int i;
		m_cTags.Copy( cin.m_cTags);

		for ( i=0; i<m_cTags.GetSize(); i++)
			m_cTags[i].SetParent( this);		// switch the parent
	}
 	return *this;
}


/////////////////////////////////////////////////////////////////////////////
//			Hit Object functions
/////////////////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
CDrawObj   *CSubChart::GetHitObject( CPoint cPt)			// did we hit anyone?
{
CObArray call;
CDrawObj *cold;
int i;

	BuildDrawList( call);
	for ( i=0; i<call.GetSize(); i++)
		{
		cold = (CDrawObj *)call.GetAt(i);
		if ( cold->HitTest( cPt))
			return cold;
		}

	return NULL;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
CDrawObj   *CSubChart::GetHighlighted( void)			// get the first highlighted object
{
CObArray call;
CDrawObj *cold;
int i;

	BuildDrawList( call);
	for ( i=0; i<call.GetSize(); i++)
		{
		cold = (CDrawObj *)call.GetAt(i);
		if ( cold->IsHighlighted() )
			return cold;
		}

	return NULL;
}

// ---------------------------------------------------------------------------
//			SetHitObject
// ---------------------------------------------------------------------------
void		CSubChart::SetHitObject( CDrawObj *cNew, BOOL bAdd)
{
CObArray call;
CDrawObj *cold;
int i;

	if ( ! bAdd)
		{
		BuildDrawList( call);
		for ( i=0; i<call.GetSize(); i++)
			{
			cold = (CDrawObj *)call.GetAt(i);
			cold->SetHighlight( FALSE);
			}
		}

	if ( cNew)
		cNew->SetHighlight( TRUE);
}


// ---------------------------------------------------------------------------
//			BuildDrawList
// ---------------------------------------------------------------------------
void CSubChart::BuildDrawList( CObArray &cArray)
{
	cArray.Add( &m_cGridX);
	cArray.Add( &m_cGridY);
	cArray.Add( &m_cGridY2);
	cArray.Add( &m_cLegend);
	cArray.Add( &m_cMarker1);
	cArray.Add( &m_cMarker2);

	{			// copy in the datatag array
	int i;

		for ( i=0; i<m_cTags.GetSize(); i++)
			{
			cArray.Add( & m_cTags[ i]);
			}
	}
	{			// copy in the datalines array
	int i;

		for ( i=0; i<m_cDataLines.GetSize(); i++)
			{
			cArray.Add( m_cDataLines.GetAt( i));
			}
	}
	cArray.Add( &m_cBorder);			// check this last
	cArray.Add( &m_cInside);			// check this last
}




IMPLEMENT_SERIAL(CChart, CGraphed, VERSIONABLE_SCHEMA | CChart::USCHEMA)


/////////////////////////////////////////////////////////////////////////////
// CChart construction/destruction

CChart::CChart()
{		// TODO: add one-time construction code here
	CreateChart();
}

CChart::~CChart()
{
}

/////////////////////////////////////////////////////////////////////////////
// CChart serialization

void CChart::Serialize(CArchive& ar)
{
	CGraphed::Serialize( ar);
	if ( GetChart())
	{
		ar.SetObjectSchema( GetSchema());	// use the chart schema #
		GetChart()->Serialize( ar);			// serialize the subchart
	}

}

int   CChart::EditProperties(CWnd *, CObject * )	// bring up properties dbox
{
CDlgChartProp cdlg;

	cdlg.m_pcChart = this;

	if ( IDOK == cdlg.DoModal())
	{
		SetDescription( cdlg.m_csDescript);
		SetLastEdit();
	}

	return 0;		
}



/////////////////////////////////////////////////////////////////////////////
// CChart diagnostics

#ifdef _DEBUG
void CChart::AssertValid() const
{
	CGraphed::AssertValid();
}

void CChart::Dump(CDumpContext& dc) const
{
	CGraphed::Dump(dc);
}

#endif //_DEBUG


CNamed *CChart::Duplicate(void )
{
CChart *cn = new CChart();

	*cn = *this;
	return cn;
}


				// operators
CChart &CChart::operator=(const CChart &cIn)
{
CNamed &cin = (CNamed &)cIn;

	*this = cin;
 	return *this;
}



CNamed &CChart::operator=(const CNamed &cIn)
{
	CGraphed::operator=( cIn);
 					// don't copy the id #
 	return *this;
}


BOOL	CChart::CreateChart( CNamed *cBase)			// build a new chart object to be graphed
{
CSubChart *cch;

	cch = new CSubChart();
	cch->SetRootObject( GetRootObject());						// since it doesn't get added to the tree
	if ( cBase )			// we have a base object
		{
		if ( ntDataSet == cBase->GetType() )
			{
			CDataSet *cd = (CDataSet *)cBase;
			cch->CreateDefault( cd->GetName(), cd->GetUOM());
			cch->Attach( cd->GetID(), cd->HasPhase());			// use the phase for this guy
			}
		else
			cch->CreateDefault( cBase->GetName(), uomFreq);
		}
	else
		cch->CreateDefault( cNullString,uomFreq);
	SetChart( cch);
	delete cch;
	return TRUE;
}

int CSubChart::GetDataCount( void)
{
	return m_cDataLines.GetSize();
}


// for serializing the mini chart to the registry
void CSubChart::ToMiniChart(CMiniChart *pMini)
{
	pMini->m_cGridX = m_cGridX;
	pMini->m_cGridY = m_cGridY;
	pMini->m_cGridY2 = m_cGridY2;
}


// for serializing the mini chart from the registry
void CSubChart::FromMiniChart(CMiniChart *pMini)
{
	m_cGridX = pMini->m_cGridX  ;
	m_cGridY = pMini->m_cGridY  ;
	m_cGridY2= pMini->m_cGridY2 ;
}

/////////////////////////////////////////////////////////////////////////////
// CMiniChart

#define CMININOW 221

IMPLEMENT_SERIAL(CMiniChart, CObject, CMININOW)

CMiniChart::CMiniChart() : m_cGridX(), m_cGridY(), m_cGridY2()
{

}

CMiniChart::~CMiniChart()
{

}

// ---------------------------------------------------------------------------
// Serialize - serialize for registry load/save
// ---------------------------------------------------------------------------
void CMiniChart::Serialize(CArchive& ar)
{
	CObject::Serialize( ar);

	m_cGridX.Serialize( ar);
	m_cGridY.Serialize( ar);
	m_cGridY2.Serialize( ar);
}
