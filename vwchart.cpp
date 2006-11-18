// audtevw.cpp : implementation of the CAudChartView class
//

#include "stdafx.h"
#include "audtest.h"

#include "audtedoc.h"
#include "vwChart.h"


#include "generat.h"
#include "dataset.h"

#include "dlgrenam.h"

#include "chart.h"

#include "dlgLocat.h"

#include "dlgSelec.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudChartView

IMPLEMENT_DYNCREATE(CAudChartView, CAudchView)

BEGIN_MESSAGE_MAP(CAudChartView, CAudchView)
	//{{AFX_MSG_MAP(CAudChartView)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CAudchView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CAudchView::OnFilePrintPreview)
	// custom stuff
	ON_MESSAGE( WM_LOCATION_GONE, OnLocationGone)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudChartView construction/destruction

CAudChartView::CAudChartView()
{
	// TODO: add construction code here
	m_pLocations = NULL;
}

CAudChartView::~CAudChartView()
{
	if( m_pLocations)
		m_pLocations->DestroyWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CAudChartView drawing

void CAudChartView::OnDraw(CDC* pDC)
{

	CAudchView::OnDraw( pDC);

}

/////////////////////////////////////////////////////////////////////////////
// CAudChartView printing

LONG CAudChartView::OnLocationGone( WPARAM , LPARAM  )
{
	m_pLocations = NULL;
    return 0L;
}



/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CAudChartView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CAudChartView diagnostics

#ifdef _DEBUG
void CAudChartView::AssertValid() const
{
	CAudchView::AssertValid();
}

void CAudChartView::Dump(CDumpContext& dc) const
{
	CAudchView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAudChartView message handlers

void CAudChartView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if ( GetTarget())		// not yet inited
		{
			if ( (! lHint) || lHint == (LPARAM )GetTarget())
			{
				InvalidateRect( NULL);
			}
			if ( lHint == (LPARAM )GetTarget())
			{
			UpdateBaseChart();
			}
 		}

	CAudchView::OnUpdate(pSender, lHint, pHint); 
}

// define this to cause an entry in the command table, so base class gets called
void CAudChartView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CAudchView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

