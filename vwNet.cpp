// audtevw.cpp : implementation of the CAudNetView class
//
//	To make life simpler, all mouse coordinates are immediately converted into logical coordinates
//	for the network display and selection operations

#include "stdafx.h"
#include "audtest.h"

#include "audtedoc.h"
#include "vwNet.h"

#include "math.h"

#include "DrawObj.h"

#include "generat.h"
#include "dataset.h"

#include "opItem.h"
#include "xform.h"

#include "network.h"
#include "netclip.h"

#include "zFormEdt.h"

#include "dlgrenam.h"
#include "dlgpertu.h"
#include "dlgCrossover.h"
#include "dlgZobel.h"
#include "dlgNotch.h"
#include "dlgAddPassive.h"
#include "dlgLPad.h"
#include "dlgCreateGoal.h"
#include "XformGoal.h"
#include "dlgNetOptimize.h"
#include "dlgAddDriver.h"

#include "Utils.h"
#include "Passive.h"

#include "BarNetwork.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudNetView

IMPLEMENT_DYNCREATE(CAudNetView, CAudtestView)

BEGIN_MESSAGE_MAP(CAudNetView, CAudtestView)
	//{{AFX_MSG_MAP(CAudNetView)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(ID_CALCULATE_FREQUENCYRESPONSE, OnCalculateFrequency)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_CALCULATE_PERTURB, OnCalculatePerturb)
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditAny)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_NETWORK_ADD_CAPACITOR, OnNetworkAddCapacitor)
	ON_COMMAND(ID_NETWORK_ADD_INDUCTOR, OnNetworkAddInductor)
	ON_COMMAND(ID_NETWORK_ADD_RESISTOR, OnNetworkAddResistor)
	ON_COMMAND(ID_NETWORK_STOCK, OnNetworkStock)
	ON_COMMAND(ID_NETWORK_COMPENSATION, OnNetworkCompensation)
	ON_COMMAND(ID_VIEW_ZOOM, OnViewZoom)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
	ON_COMMAND(ID_VIEW_ZOOMALL, OnViewZoomall)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_COMMAND(ID_NETWORK_GRID_OFF, OnNetworkGridOff)
	ON_COMMAND(ID_NETWORK_GRID_2X2, OnNetworkGrid2x2)
	ON_COMMAND(ID_NETWORK_GRID_4X4, OnNetworkGrid4x4)
	ON_COMMAND(ID_NETWORK_GRID_8X8, OnNetworkGrid8x8)
	ON_UPDATE_COMMAND_UI(ID_NETWORK_GRID_2X2, OnUpdateNetworkGrid2x2)
	ON_UPDATE_COMMAND_UI(ID_NETWORK_GRID_4X4, OnUpdateNetworkGrid4x4)
	ON_UPDATE_COMMAND_UI(ID_NETWORK_GRID_8X8, OnUpdateNetworkGrid8x8)
	ON_UPDATE_COMMAND_UI(ID_NETWORK_GRID_OFF, OnUpdateNetworkGridOff)
	ON_COMMAND(ID_NETWORK_LPAD, OnNetworkLpad)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_NETWORK_CREATEGOAL, OnNetworkCreategoal)
	ON_COMMAND(ID_NETWORK_OPTIMIZE, OnNetworkOptimize)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditAny)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditAny)
	ON_COMMAND(ID_NETWORK_ADD_DRIVER, OnNetworkAddDriver)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CAudtestView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CAudtestView::OnFilePrintPreview)
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////


static int get_SetCursor( CNetwork *cNet, POINT ptMouse, BOOL bUseAll)
{
int nnode = -1; 
SHORT state;

	if ( cNet)
		{
		CDrawObj *cselect;

			cselect = (CDrawObj *)cNet->GetClosest( &ptMouse);			// current location???
			if ( cselect && (bUseAll || cselect->IsHighlighted()))		// only if it's on
				{
				UINT nflags;

				cselect->HitTest( ptMouse, &nflags);	// well???
				if ( nflags & TVHT_TOLEFT)			// left node
					nnode = 0;
				else if ( nflags & TVHT_TORIGHT)
					nnode = 1;
			   										// at this point, inside, may a node
				if ( -1 == nnode)
					return IDC_MOVER;

													// see if we're shifted
				state = GetKeyState( VK_SHIFT);
				if ( state < 0)			// top bit is 1, key is down
					return IDC_CROSSPLUS;
				else
					return IDC_SMALLCROSS;
				}

		}
	
	return 0;
}


// --------------------------------------------------------------------------------
//		set_DlgBar
// --------------------------------------------------------------------------------
void CAudNetView::set_DlgBar( void)
{				// check to see if one item is highlighted, and then set the edit field
CNetwork *cnet = (CNetwork *)GetTargetObject();		// it may have changed above
CObject *psel;
CBarNetwork *pdlgnet;

	if ( NULL == cnet)				// object was deleted
	{
		return;
	}
	psel = cnet->GetHighlighted();	// is something highlighted?

	pdlgnet = (CBarNetwork *)GetDlgBar();		// get the window
	if ( pdlgnet && pdlgnet->GetSafeHwnd())
	{
		if ( psel)						// yes
		{
		ZpPassive *ppass;				// the real datatype
		double dvalue;
		CString strt;

			ppass = (ZpPassive *)psel;	// here we go
			dvalue = ppass->GetValue();	// get the value
			pdlgnet->SetValue( (float )dvalue);
			pdlgnet->SetSelected( ppass);
		}
		else
			pdlgnet->SetSelected( NULL);		// nothing is selected
	}
}


// --------------------------------------------------------------------------------
//		get_DlgBarValue
// --------------------------------------------------------------------------------
void CAudNetView::get_DlgBarValue( void)
{
				// check to see if one item is highlighted, and then set the edit field
CNetwork *cnet = (CNetwork *)GetTargetObject();		// it may have changed above
CObject *psel;

	ASSERT( cnet);
	psel = cnet->GetHighlighted();	// is something highlighted?

	if ( psel)						// yes
	{
	ZpPassive *ppass;				// the real datatype
	double dvalue;
	CBarNetwork *pdlgnet;
	CString strt;

		ppass = (ZpPassive *)psel;	// here we go
		dvalue = ppass->GetValue();	// get the value
		pdlgnet = (CBarNetwork *)GetDlgBar();		// get the window
		if ( pdlgnet && pdlgnet->GetSafeHwnd())
		{
		float fnew;

			fnew = pdlgnet->GetValue();
			if ( fnew > 0.0f)			// value must be > 0
			{
				if ( ppass == pdlgnet->GetSelected())
					ppass->SetValue( fnew);
				else
					ASSERT(0);
			}
		}
	}
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void CAudNetView::rubber_Line( POINT ptStart, POINT ptEnd)
{
CDC *pdc = GetDC();

	to_Device( ptStart);
	to_Device( ptEnd);

	if ( pdc)
		{
		int nold = pdc->SetROP2( R2_NOT);

			pdc->MoveTo( ptStart);
			pdc->LineTo( ptEnd);

			pdc->SetROP2( nold);

		ReleaseDC( pdc);
		}

}


void CAudNetView::rubber_Box( POINT ptStart, POINT ptEnd)
{
CDC *pdc = GetDC();

	to_Device( ptStart);
	to_Device( ptEnd);

	if ( pdc)
		{
		int nold = pdc->SetROP2( R2_NOT);
		CGdiObject *cold = pdc->SelectStockObject( NULL_BRUSH);

			pdc->Rectangle( ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);

			pdc->SetROP2( nold);

			if ( cold)
				pdc->SelectObject( cold);

		ReleaseDC( pdc);
		}

}


/////////////////////////////////////////////////////////////////////////////
// CAudNetView construction/destruction

CAudNetView::CAudNetView() : m_ptMouse(CPoint(0,0))
{
	// TODO: add construction code here
		m_nHasCapture = 0;
		m_cSelect = NULL;
		m_cOldNetwork = NULL;

		m_fWindowScale = 1.0f;		// start at 1:1
		m_ptWindowOrg.x = 0;		// and at origin
		m_ptWindowOrg.y = 0;

}

CAudNetView::~CAudNetView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CAudNetView drawing

void CAudNetView::OnDraw(CDC* pDC)
{
CNetwork *cname;

	cname = (CNetwork *)GetTargetObject();

	if ( ! cname)
		return;

	cname->DoDraw( pDC, &m_rcPrint);
}

/////////////////////////////////////////////////////////////////////////////
// CAudNetView printing

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CAudNetView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CAudNetView diagnostics

#ifdef _DEBUG
void CAudNetView::AssertValid() const
{
	CAudtestView::AssertValid();
}

void CAudNetView::Dump(CDumpContext& dc) const
{
	CAudtestView::Dump(dc);
}

#endif //_DEBUG

// -----------------------------------------------------------------
// -------------  GetMenuResource
// -----------------------------------------------------------------
UINT CAudNetView::GetMenuResource(void )
{
	return( IDR_MNETVIEW);
}


/////////////////////////////////////////////////////////////////////////////
// CAudNetView message handlers

BOOL CAudNetView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle | WS_HSCROLL | WS_VSCROLL, rect, pParentWnd, nID, pContext);
}

void CAudNetView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
CRect rcbound;
CRect rcc;
CNetwork *cnet;
SCROLLINFO sif;

	if ( ! GetTarget())		// check to make sure it's valid
		return;

	cnet = (CNetwork *)GetTargetObject();

	if ( ! cnet)
		return;

	cnet->GetBounds( rcbound, FALSE);
	rcbound.left = min( 0, rcbound.left);
	rcbound.top = min(0, rcbound.top);
	GetClientRect( rcc);
		{
		CPoint pt( rcc.Width(), rcc.Height());
		to_Logical( pt);
		rcc.right = pt.x - m_ptWindowOrg.x;
		rcc.bottom = pt.y - m_ptWindowOrg.y;
		}

	sif.cbSize = sizeof( sif);
	sif.fMask = SIF_ALL;
	sif.nMin = 0;

	sif.nMax = rcbound.Width();
	sif.nPage = rcc.Width();
	sif.nPos = m_ptWindowOrg.x;
	SetScrollInfo( SB_HORZ, &sif);

	sif.nMax = rcbound.Height();
	sif.nPage = rcc.Height();
	sif.nPos = m_ptWindowOrg.y;
	SetScrollInfo( SB_VERT, &sif);

	CAudtestView::OnUpdate(pSender, lHint, pHint);
}


#if 0
void CAudNetView::OnCalculateValidate() 
{
CNetwork *cname;

	cname = (CNetwork *)GetTargetObject();
	if ( ! cname)
		return;

	cname->RenumberNodes();
	
		
}
#endif

#include "chart.h"

void CAudNetView::OnCalculateFrequency() 
{
int i;
CAudtestDoc* pDoc = GetDocument();
CObArray pf;
CFolder *pcroot = pDoc->GetRoot();
CNetwork *cnet = (CNetwork *)GetTargetObject();

	if ( ! cnet)
		return;

	get_DlgBarValue();		// in case the dlg bar initiated this

COpCustom *copcalc = new COpCustom( cnet);

	copcalc->SetNameID( IDOP_CALCFREQ);

	copcalc->QueueAndDo();

	cnet->CalculateResponse(copcalc, pf);

	if ( cnet->HasAutoChart())					// should we build a chart?
		{
		CString csname = cnet->GetName() + ".chart";

		if (! pcroot->GetItemByName( csname) )
			{
			CChart *cchart = new CChart();
			CSubChart *csub = (CSubChart *)cchart->GetChart();
			csub->CreateDefault( cnet->GetName() + ".Frequency Response", uomFreq);
			cchart->SetName( csname);
			pcroot->AddItem( cchart);
			csub->SetRootObject( pcroot);	// necessary
			for ( i=pf.GetSize()-1; i >= 0; i--)	// start with the totals first
				{
				CNamed *cn = (CNamed *) ( pf.GetAt(i) ) ;
				if ( cn->IsType( ntDataSet, uomFreq))
					csub->Attach( cn->GetID() );		// don't add the impedances
				}
			}
		}

	pDoc->UpdateAll( this);		
}

void CAudNetView::OnLButtonDown(UINT nFlags, CPoint point) 
{
CNetwork *cnet;
CDrawObj *cselect;
BOOL bshifted = (MK_SHIFT & nFlags) ? TRUE : FALSE; 
int nnode = -1;

	to_Logical( point);

	cnet = (CNetwork *)GetTargetObject();
	if ( ! cnet)
		return;

	m_cSelect = cnet->GetClosest( &point);
	cselect = (CDrawObj *)m_cSelect;

	if ( cselect)
		{				// --------- user has picked an object
		if (! cselect->IsHighlighted())
			{
			cnet->SetHighlighted( cselect, !bshifted);			// bOnly based on shift key
			InvalidateRect( NULL);
			}
		else			// --------- highlighted - user picked a node???
			{
			UINT nflags;

				cselect->HitTest( point, &nflags);	// well???
				if ( nflags & TVHT_TOLEFT)			// left node
					nnode = 0;
				else if ( nflags & TVHT_TORIGHT)
					nnode = 1;
				else if ( bshifted)									// shift key down, turn this one off
					cselect->SetHighlight( FALSE);
			}
		}
	else				// --------- user has picked no object
		{
		if ( cnet->GetHighlighted())							// something is already highlighted
			if ( ! (MK_SHIFT & nFlags))							// no shift, de-all
				{
				cnet->SetHighlighted( NULL, TRUE);				// clear all
				InvalidateRect( NULL);
				}
		}

	if ((!cselect) || (cselect && ! cselect->IsHighlighted()) )			// somehow it isn't highlited (shift-key)
		{
		m_cSelect = cnet->GetHighlighted();
		cselect = (CDrawObj *)m_cSelect;
		}

		SetCapture();			// let's start getting captured
		m_cOldNetwork = cnet->Duplicate();		// and make a copy of the net
		m_nNode = nnode;

		if ( nnode < 0)			// move it
			{
			if ( m_cSelect)
				m_nHasCapture = 1;
			else
				m_nHasCapture = 3;
			}
		else
			m_nHasCapture = 2;			// rubber band box

		if ( m_cSelect)
			cnet->GetObjLocation( m_cSelect, &m_ptObj);
		m_ptMouse = point;
		m_ptMouseDown = point;		// starting point

		switch( m_nHasCapture)
			{
			case 2 :					// rubber band line
				cnet->SetDragging( TRUE);		// set to dragging mode
				InvalidateRect( NULL, FALSE);
				UpdateWindow();
				if ( 1 == m_nNode)			// other node
					cnet->GetObjEndLocation(m_cSelect, &m_ptObj);	// use end location
				rubber_Line( m_ptObj, m_ptMouse);
				break;
			default :
				break;
			}

	CAudtestView::OnLButtonDown(nFlags, point);
}



void CAudNetView::do_Move( CPoint& cpWhere)
{
CNetwork *cnet;
POINT ptmove;

	cnet = (CNetwork *)GetTargetObject();
	if ( ! cnet)
		return;

	ptmove.x = cpWhere.x - m_ptMouse.x;
	ptmove.y = cpWhere.y - m_ptMouse.y;

	ptmove = cnet->MoveObjects( ptmove);		// capture amount moved

	m_ptMouse.x += ptmove.x;
	m_ptMouse.y += ptmove.y;

	InvalidateRect(NULL, TRUE);
}

void CAudNetView::to_Device( POINT& cpLogical)
{
	cpLogical.x -= m_ptWindowOrg.x;
	cpLogical.y -= m_ptWindowOrg.y;
	cpLogical.x = (long )(cpLogical.x * m_fWindowScale);
	cpLogical.y = (long )(cpLogical.y * m_fWindowScale);
}

void CAudNetView::to_Logical( POINT& cpDevice)
{
	cpDevice.x = (long )(cpDevice.x / m_fWindowScale);
	cpDevice.y = (long )(cpDevice.y / m_fWindowScale);
	cpDevice.x += m_ptWindowOrg.x;
	cpDevice.y += m_ptWindowOrg.y;
}

void CAudNetView::do_Deselect( CPoint& cpWhere)
{
	do_Move( cpWhere);

	m_nHasCapture = 0;

	::ReleaseCapture();
}


void CAudNetView::OnLButtonUp(UINT nFlags, CPoint point) 
{
CAudtestDoc* pDoc = GetDocument();
BOOL bchange = FALSE;

	to_Logical( point);

	if ( m_nHasCapture)					// we've captured it
		{
		CNetwork *cnet = (CNetwork *)GetTargetObject();

		switch( m_nHasCapture)
			{
			case 1 :					// moving guys
				{
				CPoint pt;

					pt.x = m_ptMouseDown.x - point.x;
					pt.y = m_ptMouseDown.y - point.y;

					if ( (pt.x * pt.x + pt.y * pt.y) > 25)
						{
						bchange = TRUE;
						}
					else
						{
						pt = m_ptMouseDown;
						do_Move( pt);		// put it all back
						}
				}
				break;
			case 2 :					// rubber band line - renode
				cnet->SetDragging( FALSE);
				if ( m_cSelect && cnet)
					{
					CDrawObj *cselect = (CDrawObj *)cnet->GetClosest( &point);
					if ( cselect)			// we are near someone
						{
						UINT nflags;

							cselect->HitTest( point, &nflags);	// well???
							if ( nflags & TVHT_TOLEFT)			// left node
								{
								cnet->SetObjNodes( m_cSelect, m_nNode, cselect, 0, (nFlags & MK_SHIFT) ? 1 : 0);
								bchange = TRUE;
								}
							else if ( nflags & TVHT_TORIGHT)
								{
								cnet->SetObjNodes( m_cSelect, m_nNode, cselect, 1, (nFlags & MK_SHIFT) ? 1 : 0);
								bchange = TRUE;
								}

						}
					}
				break;
			case 3 :					// rubber band box - rehighlight
				if ( cnet)
					cnet->SetRectHighlight( m_ptMouseDown, m_ptMouse);
				break;
			default :
				break;
			}

		do_Deselect( point);			// release the capture

		if ( bchange)
			{
			CNamed *cnew = cnet->Duplicate();
			*cnet = *(CNamed *)m_cOldNetwork;				// copy in the old data
	
			COpCode *cop = new COpChange( cnet, cnew);
				cop->QueueAndDo();

			}
		if ( m_cOldNetwork)
			{
			delete m_cOldNetwork;
			m_cOldNetwork = NULL;
			}
		}
	
	CAudtestView::OnLButtonUp(nFlags, point);

	set_DlgBar();

	pDoc->UpdateAll(NULL, (LPARAM )GetTarget());
}

void CAudNetView::OnMouseMove(UINT nFlags, CPoint point) 
{

	to_Logical( point);

	switch( m_nHasCapture)
		{
		case 0 :
			m_ptMouse = point;
			break;			// nope
		case 1 :			// move
			do_Move( point);
			break;
		case 2 : 			// rubber line
			rubber_Line( m_ptObj, m_ptMouse);	// erase old line
			m_ptMouse = point;
			rubber_Line( m_ptObj, m_ptMouse);	// draw new line
			{
			CNetwork *cnet = (CNetwork *)GetTargetObject();
			int ncursor = get_SetCursor( cnet, m_ptMouse, TRUE);
			if ( ncursor && ncursor == IDC_SMALLCROSS)
				{
				::SetCursor( AfxGetApp()->LoadCursor( ( MK_SHIFT & nFlags) ? IDC_CROSSPLUS : IDC_SMALLCROSS) );
				}
			else
				::SetCursor( ::LoadCursor( NULL, IDC_ARROW) );
			}
			break;
		case 3 : 			// rubber box
			rubber_Box( m_ptMouseDown, m_ptMouse);	// erase old Box
			m_ptMouse = point;
			rubber_Box( m_ptMouseDown, m_ptMouse);	// draw new Box
			break;
		}
	
	CAudtestView::OnMouseMove(nFlags, point);
}


void CAudNetView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
CAudtestDoc* pDoc = GetDocument();
CNetwork *cnet;

	to_Logical( point);

	cnet = (CNetwork *)GetTargetObject();
	if ( ! cnet)
		return;

CObject *cgot = cnet->GetHighlighted();

	if ( cgot)					// we've selected an object
		{

		if ( IDOK == cnet->EditComponent(this, cgot) )
			pDoc->UpdateAll(NULL, (LPARAM )GetTarget());

		}
	
	CAudtestView::OnLButtonDblClk(nFlags, point);
}

void CAudNetView::OnCalculatePerturb() 
{
int i;
CAudtestDoc* pDoc = GetDocument();
CObArray pf;
CFolder *pcroot = pDoc->GetRoot();
CNetwork *cnet;
int nnow;
CChart *cchart;
CSubChart *csub;
CDlgPerturb	cdlg;

	cnet = (CNetwork *)GetTargetObject();
	if ( ! cnet)
		return;

	cdlg.m_pNet = cnet;
	if ( IDOK != cdlg.DoModal())
		return;
	if ( ! cdlg.m_nPoints)
		return;

CString csname = cnet->GetName() + ".Perturb." + cdlg.m_csObjName;
COpCustom *copcalc = new COpCustom( cnet);

	copcalc->SetNameID( IDOP_CALCFREQ);
	copcalc->QueueAndDo();

	cchart = (CChart *)pcroot->GetItemByName( csname);
	if (! cchart)
		{
		cchart = new CChart();
 		csub = (CSubChart *)cchart->GetChart();
 		csub->CreateDefault( csname , uomFreq);
		cchart->SetName( csname);
		pcroot->AddItem( cchart);
		csub->SetRootObject( pcroot);	// this is not done automatically
		}
	else
		csub = (CSubChart *)cchart->GetChart();

	csub = (CSubChart *)cchart->GetChart();

	float fstart = cdlg.m_fStart;
	float fend = cdlg.m_fEnd;
	CString cscomponent;
	CObject *cob = cnet->GetObjByName( cdlg.m_csObjName);
	float foldvalue = cnet->GetObjValue( cob);
	float fcurrent;

	for ( nnow=0; nnow < cdlg.m_nPoints; nnow++)
		{
		fcurrent = fstart + ((fend - fstart) * nnow) / cdlg.m_nPoints;
		cnet->SetObjValue(cob, fcurrent);
		cnet->CalculateResponse(copcalc, pf);

		for ( i=0; i<pf.GetSize(); i++)
			{
			CNamed *cn = (CNamed *) ( pf.GetAt(i) ) ;
			CString csvalue;
			FullFormatValue( csvalue, fcurrent, -3);
			cn->SetName( cnet->GetName() + "." + cdlg.m_csObjName + "=" + csvalue );
			if ( ! i)
				csub->Attach( cn->GetID() );
			}
		pf.RemoveAll();
		}

	cnet->SetObjValue( cob, foldvalue);			// set it back to old

	pDoc->UpdateAll( this);		
	
}

BOOL CAudNetView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
CNetwork *cnet;

	cnet = (CNetwork *)GetTargetObject();
	if ( cnet)
		{
		int ncursor = get_SetCursor( cnet, m_ptMouse, FALSE);

		if ( ncursor)
			{					// at this point, inside, may a node
			::SetCursor( AfxGetApp()->LoadCursor( ncursor) );
			return TRUE;
			}

		}
	
	return CAudtestView::OnSetCursor(pWnd, nHitTest, message);
}

void CAudNetView::OnEditCut() 
{
CNetwork *cnet;

	cnet = (CNetwork *)GetTargetObject();

	if ( cnet && cnet->GetHighlighted())
		{
		cnet->CutObjects( TRUE );			// copy highlighted objects
		}
	
	
}

void CAudNetView::OnEditDelete() 
{
CNetwork *cnet;

	cnet = (CNetwork *)GetTargetObject();

	if ( cnet && cnet->GetHighlighted())
		{
		cnet->DeleteObjects( TRUE );			// copy highlighted objects
		}
	
	
}

void CAudNetView::OnEditPaste() 
{
CNetwork *cnet;

	cnet = (CNetwork *)GetTargetObject();

	if ( cnet)
		{
		cnet->SetHighlighted( NULL, TRUE);			// turn off highlighting
		cnet->PasteObjects( );						// paste highlighted objects
		}
	
}

void CAudNetView::OnEditCopy() 
{
CNetwork *cnet;

	cnet = (CNetwork *)GetTargetObject();

	if ( cnet)
		{
		cnet->CopyObjects( NULL != cnet->GetHighlighted());			// copy highlighted objects
		}
	
}


void CAudNetView::OnUpdateEditAny(CCmdUI* pCmdUI) 
{
CNetwork *cnet;

	cnet = (CNetwork *)GetTargetObject();

	if ( cnet && cnet->GetHighlighted())
		pCmdUI->Enable( TRUE);
	else
		pCmdUI->Enable( FALSE);
	
}

void CAudNetView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
    // See if there is a list available.
    if ( ::OpenClipboard( NULL))
		{
		UINT uiFmt = EnumClipboardFormats(0);
		
		while (uiFmt)
		{
			if (uiFmt == COpNetClipPaste::GetFormat())
				{
				CloseClipboard();
				pCmdUI->Enable(TRUE);
				return;
				}
			uiFmt = EnumClipboardFormats(uiFmt);
		}
	    pCmdUI->Enable(FALSE);
    	::CloseClipboard();    
		}
	
}

// add a capacitor
void CAudNetView::OnNetworkAddCapacitor() 
{
CXtAddPassive *cxt = new CXtAddPassive( GetTargetObject(), ptCapacitor);

	Dialog_Perform(cxt);
}

void CAudNetView::OnNetworkAddInductor() 
{
CXtAddPassive *cxt = new CXtAddPassive( GetTargetObject(), ptInductor);

	Dialog_Perform(cxt);
}

void CAudNetView::OnNetworkAddResistor() 
{
CXtAddPassive *cxt = new CXtAddPassive( GetTargetObject(), ptResistor);

	Dialog_Perform(cxt);
}

void CAudNetView::OnNetworkAddDriver() 
{
CXtAddDriver *cxt = new CXtAddDriver( GetTargetObject());

	Dialog_Perform(cxt);
	
}

void CAudNetView::OnNetworkOptimize() 
{
CXtNetOptimize *cxt = new CXtNetOptimize( GetTargetObject());

	Dialog_Perform(cxt);
}


void CAudNetView::OnNetworkStock() 
{
CXtCrossover *cxt = new CXtCrossover( GetTargetObject());

	Dialog_Perform(cxt);
	
}

#if 0
void CAudNetView::OnNetworkNotchfilter() 
{
CDlgNotch cdlg;

	cdlg.DoModal();
	
}
#endif

void CAudNetView::OnNetworkCompensation() 
{
CXtZobel *cxt = new CXtZobel( GetTargetObject());

	Dialog_Perform(cxt);
	
}

void CAudNetView::OnViewZoom() 
{
	if ( m_fWindowScale < 20)
		m_fWindowScale *= 1.3f;

	UpdateTarget();
	
}

void CAudNetView::OnViewZoomout() 
{
	if ( m_fWindowScale > .1)
		m_fWindowScale *= (1.0f/1.3f);

	UpdateTarget();
}


void CAudNetView::OnViewZoomall() 
{
CRect rcbound;
CNetwork *cnet;
CRect rcc;
double d1, d2;

	cnet = (CNetwork *)GetTargetObject();

	if ( ! cnet)
		return;

	cnet->GetBounds( rcbound, FALSE);

	GetClientRect( rcc);

	d1 = rcc.Width() / (double )rcbound.Width();
	d2 = rcc.Height() / (double )rcbound.Height();
	if ( d1 > d2)
		d1 = d2;			// use the min scale

	{
	d2 = log( d1);		// take log
	d2 /= log( 1.3);	// divide by log 1.3
	d2 = (int )d2;		// convert to int
	d2 *= log( 1.3);	// put it back
	d1 = exp( d2);		// then exp it to get something in the sequence
	m_fWindowScale = (float )d1;
	}

	UpdateTarget();

}

static int alter_Scroll( CWnd *pWnd, int nBar, UINT nSBCode)
{
SCROLLINFO sif;

	pWnd->GetScrollInfo( nBar, &sif);

 	switch(nSBCode)
		{
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			sif.nPos = sif.nTrackPos;
			break;
		case SB_ENDSCROLL:
			break;
		case SB_LINEUP:
//		case SB_LINELEFT:		... note these are the same in xxx.h
			sif.nPos--;
			if ( sif.nPos < sif.nMin)
				sif.nPos = sif.nMin;
			break;
		case SB_LINEDOWN:
			sif.nPos++;
			if ( sif.nPos > sif.nMax)
				sif.nPos = sif.nMax;
			break;
		case SB_PAGEUP:
			sif.nPos -= sif.nPage;
			if ( sif.nPos < sif.nMin)
				sif.nPos = sif.nMin;
			break;
		case SB_PAGEDOWN:
			sif.nPos += sif.nPage;
			if ( sif.nPos > sif.nMax)
				sif.nPos = sif.nMax;
			break;
		case SB_TOP:
			sif.nPos = sif.nMin;
			break;
		case SB_BOTTOM:
			sif.nPos = sif.nMax;
			break;
		default:
			break;
		}

	pWnd->SetScrollInfo( nBar, &sif);
	pWnd->InvalidateRect( NULL);

	return sif.nPos;
}


void CAudNetView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{

	m_ptWindowOrg.x = alter_Scroll( this, SB_HORZ, nSBCode);
	
	CAudtestView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CAudNetView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{

	m_ptWindowOrg.y = alter_Scroll( this, SB_VERT, nSBCode);
	
	CAudtestView::OnVScroll(nSBCode, nPos, pScrollBar);
}

// here we handle rescaling for the network view
void CAudNetView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
CRect rc(0,0,0,0);

	CAudtestView::OnPrepareDC(pDC, pInfo);

	if ( pInfo && pInfo->m_nCurPage)		// per doc, this is how you check for printing
		{
		CAudtestApp::ClearAllPrinterFonts();

		pDC->SetMapMode( MM_TEXT);
		rc.SetRect( 0,0,pDC->GetDeviceCaps( HORZRES), pDC->GetDeviceCaps( VERTRES) );
				// set the map mode
		pDC->SetMapMode( MM_ISOTROPIC);
		pDC->SetWindowOrg( 0,0);
		pDC->SetWindowExt( 800, 800 );
		pDC->SetViewportOrg( 0,0);
		pDC->SetViewportExt( rc.Width(), rc.Height() );
		m_rcPrint = rc;
		}
	else			// screen display, allow zooming
		{
		pDC->SetMapMode( MM_TEXT);
		GetClientRect( rc);
		pDC->SetMapMode( MM_ISOTROPIC);
		pDC->SetWindowOrg ( m_ptWindowOrg);
		pDC->SetWindowExt ( rc.Width(), rc.Height() );			// 8 x 8 display theoretically
		pDC->SetViewportOrg( 0,0);
		pDC->SetViewportExt( (int )(rc.Width() * m_fWindowScale), (int )(rc.Height() * m_fWindowScale) );
		m_rcPrint = rc;
		}


}


// define this to cause an entry in the command table, so base class gets called
void CAudNetView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	set_DlgBar();
	CAudtestView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CAudNetView::OnNetworkGridOff() 
{
POINT pt = {0,0};

	CAudtestApp::SetNetGrid( pt);	
}

void CAudNetView::OnNetworkGrid2x2() 
{
POINT pt = {2,2};

	CAudtestApp::SetNetGrid( pt);	
}

void CAudNetView::OnNetworkGrid4x4() 
{
POINT pt = {5,5};

	CAudtestApp::SetNetGrid( pt);	
	
}

void CAudNetView::OnNetworkGrid8x8() 
{
POINT pt = {10,10};

	CAudtestApp::SetNetGrid( pt);	
	
}

void CAudNetView::OnUpdateNetworkGrid2x2(CCmdUI* pCmdUI) 
{
POINT pt = CAudtestApp::GetNetGrid();	

	pCmdUI->SetCheck( pt.x == 2);

}

void CAudNetView::OnUpdateNetworkGrid4x4(CCmdUI* pCmdUI) 
{
POINT pt = CAudtestApp::GetNetGrid();	
	
	pCmdUI->SetCheck( pt.x == 5);
}

void CAudNetView::OnUpdateNetworkGrid8x8(CCmdUI* pCmdUI) 
{
POINT pt = CAudtestApp::GetNetGrid();	
	
	pCmdUI->SetCheck( pt.x == 10);
}

void CAudNetView::OnUpdateNetworkGridOff(CCmdUI* pCmdUI) 
{
POINT pt = CAudtestApp::GetNetGrid();

	pCmdUI->SetCheck( pt.x == 0);
	
}

void CAudNetView::OnNetworkLpad() 
{
CXtLPad *cxt = new CXtLPad( GetTargetObject());

	Dialog_Perform(cxt);
	
}

BOOL CAudNetView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// do zoomin and zoomout
	if ( zDelta < 0)
		OnViewZoomout();
	else if ( zDelta > 0)
		OnViewZoom();
	return CAudtestView::OnMouseWheel(nFlags, zDelta, pt);
}

void CAudNetView::OnNetworkCreategoal() 
{
CDlgCreateGoal cdlg;
CNetwork *pnet = (CNetwork *)GetTargetObject();

	cdlg.m_pNetwork = pnet;
	if ( IDOK == cdlg.DoModal())
		{
		CXformGoal *cxfl = new CXformGoal ( pnet);

			cxfl->m_nHighLow	=	cdlg.m_nHighLow;
			cxfl->m_nOrder		=	cdlg.m_nOrder;
			cxfl->m_nType		=	::ComboToXover( cxfl->m_nOrder, cdlg.m_nType);
			cxfl->m_fFS			=	cdlg.m_fFS;
			cxfl->m_fStart		=	cdlg.m_fStart;
			cxfl->m_fEnd		=	cdlg.m_fEnd;
			cxfl->m_fValue		=	cdlg.m_fValue;
			cxfl->m_isUseWhich	=	cdlg.m_isUseWhich;
			cxfl->m_dwDriver	=	cdlg.m_dwDriver;
			cxfl->m_dwDataset	=	cdlg.m_dwDataset;

			cxfl->QueueAndDo();						// do the fft
		}
		
	
}


