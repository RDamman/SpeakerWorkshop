// audtevw.cpp : implementation of the CAudtestView class
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "audtedoc.h"
#include "audtevw.h"
#include "vwdrive.h"

#include "childfrm.h"
#include "mainfrm.h"

#include "Chart.h"
#include "generat.h"
#include "dataset.h"
#include "network.h"

#include "mmwave.h"

#include "dlgrenam.h"
#include "dlgLocat.h"
#include "dlgCalibrate.h"
#include "dlgCalcTuned.h"
#include "dlgCalcPassive.h"
#include "dlgTimeDist.h"
#include "dlgSelec.h"
#include "dlgCalWizVol.h"
#include "dlgVolumeCalc.h"

#include "opItem.h"

#include "FxFont.h"
#include "xform.h"
#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 						CAudtestView 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CAudtestView, CView)

BEGIN_MESSAGE_MAP(CAudtestView, CView)
	//{{AFX_MSG_MAP(CAudtestView)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(ID_EDIT_PROPERTIES, OnEditProperties)
	ON_COMMAND(ID_RESOURCE_RENAME, OnResourceRename)
	ON_COMMAND(ID_RESOURCE_IMPORT, OnResourceImport)
	ON_COMMAND(ID_RESOURCE_EXPORT, OnResourceExport)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_SOUND_STOP, OnSoundStop)
	ON_COMMAND(ID_OPTIONS_CALIBRATE, OnOptionsCalibrate)
	ON_COMMAND(ID_OPTIONS_TUNED, OnOptionsTuned)
	ON_COMMAND(ID_OPTIONS_PASSIVE, OnOptionsPassive)
	ON_COMMAND(ID_WIZARD_SETVOLUME, OnWizardSetvolume)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_OPTIONS_DISTANCE, OnOptionsDistance)
	ON_COMMAND(ID_OPTIONS_VOLUME, OnOptionsVolume)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	// msz - try to handle text display
		// mmio stuff
	ON_MESSAGE( MM_WIM_DATA, OnWimData)
	ON_MESSAGE( MM_WOM_DONE, OnWomDone)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudtestView construction/destruction

CAudtestView::CAudtestView()
{
	m_pTracker = NULL;
	m_nTrackType = ntAny;
	m_pOperation = NULL;
}

CAudtestView::~CAudtestView()
{
}

// ---------------------------------------------------------------------------
//		setup_Tracker
//			setup the data tracker for the item selected
// ---------------------------------------------------------------------------
static CRectTracker *setup_Tracker(CDrawObj* pItem)
{
RECT rcdraw;
CRectTracker *cr;

	pItem->GetDrawRect( &rcdraw);

	switch( pItem->GetType())
	{
	case ntMarker:
	case ntInside:
		cr = new CRectTracker(&rcdraw, 
				CRectTracker::dottedLine | CRectTracker::resizeOutside);
		break;
	case ntDataTag:
		cr = new CRectTracker(&rcdraw, 
				CRectTracker::solidLine | CRectTracker::hatchedBorder);
		break;
	default:
		cr = new CRectTracker(&rcdraw, 
				CRectTracker::solidLine | CRectTracker::resizeOutside | CRectTracker::hatchedBorder);
		break;
	}

	return cr;
}

/////////////////////////////////////////////////////////////////////////////
// CAudtestView drawing
/////////////////////////////////////////////////////////////////////////////

void CAudtestView::OnDraw(CDC* pDC)
{
	// TODO: add draw code for native data here
CRectTracker *cr = GetTracker();

	if ( cr)
		cr->Draw( pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CAudtestView printing

BOOL CAudtestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(1);

	return DoPreparePrinting(pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CAudtestView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CAudtestView diagnostics

#ifdef _DEBUG
void CAudtestView::AssertValid() const
{
	CView::AssertValid();
}

void CAudtestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

CAudtestDoc* CAudtestView::GetDocument() // non-debug version is inline
{
	ASSERT_KINDOF( CAudtestDoc, m_pDocument);
	return (CAudtestDoc*)m_pDocument;
}

/////////////////////////////////////////////////////////////////////////////
// CAudtestView message handlers

// -----------------------------------------------------------------
// -------------  UpdateTarget
// -----------------------------------------------------------------
void		CAudtestView::UpdateTarget( void)
{
CNamed *cnam = GetTargetObject();

	if ( cnam)
		cnam->UpdateViews();
}



// -----------------------------------------------------------------
// -------------  ResetTarget
//		call this when a target name changes
// -----------------------------------------------------------------
void	CAudtestView::ResetTarget( void)
{
CWnd *cw;
DWORD dwid;
CString csname;
CAudtestDoc* pDoc = GetDocument();
CNamed *pname = NULL;

	cw  = GetParent();

	while ( cw && ! cw->IsKindOf(RUNTIME_CLASS( CChildFrame)))
		{
		cw = cw->GetParent();
		}

	if ( ! cw)
		return;

CChildFrame *ccf = (CChildFrame *)cw;

	dwid = ccf->GetTarget();

	if ( dwid)
	{
		pname = pDoc->GetByID( dwid);

		if ( pname)
			ccf->SetTarget( dwid, pDoc->GetFullTextName( pDoc->GetByID( dwid)));
	}
	else			// the document
	{
		ccf->SetTarget( dwid, pDoc->GetTitle());
	}


}


// -----------------------------------------------------------------
// -------------  GetTarget
// -----------------------------------------------------------------
DWORD		CAudtestView::GetTarget( void)
{
CWnd *cw;

	cw  = GetParent();

	while ( cw && ! cw->IsKindOf(RUNTIME_CLASS( CChildFrame)))
		{
		cw = cw->GetParent();
		}

	if ( ! cw)
		return 0;

CChildFrame *ccf = (CChildFrame *)cw;

	return ccf->GetTarget();
}



//	ConvertTarget
//	convert the target dword id into a CNamed pointer
// -----------------------------------------------------------------
// -------------  GetTargetObject
// -----------------------------------------------------------------
CNamed *CAudtestView::GetTargetObject( void)
{
CNamed *cname;
CAudtestDoc* pDoc = GetDocument();

	cname = pDoc->GetByID( GetTarget());

	return cname;		// returns NULL if not found
						// use cname temp variable for easier debugging
}


// -----------------------------------------------------------------
// -------------  OnUpdate
// -----------------------------------------------------------------
void CAudtestView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
				// tell the dlglocations window to update itself if we're it
	if ( (!lHint) || (DWORD )lHint == GetTarget())
	{
		InvalidateRect( NULL);			// if !lHint, or it's us invalidate everything
		if ( (DWORD )lHint == GetTarget())
		{
			DBG_PRINT("Resetting Target");
			ResetTarget();
			DBG_PRINT("Reset target");
		}
	}

	 CView::OnUpdate(pSender, lHint, pHint);
}

 				// rename the current object
// -----------------------------------------------------------------
// -------------  OnResourceRename
// -----------------------------------------------------------------
void CAudtestView::OnResourceRename() 
{
CDlgRename cdlg(this);
CNamed *cname;
CAudtestDoc* pDoc = GetDocument();
COpRename *cop;

	cname = pDoc->GetByID( GetTarget());

	if ( ! cname)
		return;

	cdlg.m_csName = cname->GetName();

	if ( IDOK == cdlg.DoModal())
		{
		cop = new COpRename( cname, cdlg.m_csName);
		cop->QueueAndDo();
		}
}

// -----------------------------------------------------------------
// -------------  OnEditProperties
// -----------------------------------------------------------------
void CAudtestView::OnEditProperties() 
{
CNamed *cname;
CAudtestDoc* pDoc = GetDocument();
DWORD dwid;

	cname = GetTargetObject();
	if ( ! cname)
		return;
	dwid = cname->GetID();		// do it before the edit properties, since that does a change

	if ( IDOK == cname->EditProperties( this))
		pDoc->UpdateAll( NULL, dwid);
	
}



		// this imports data for a dataset
// -----------------------------------------------------------------
// -------------  OnResourceImport
// -----------------------------------------------------------------
void CAudtestView::OnResourceImport() 
{
CAudtestDoc* pDoc = GetDocument();
CString csimport;
CString csuffix;
CString cstitle;

CFileDialog cdlg( TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, 
		"Network (*.CIR)|*.CIR|Frequency (*.FRD)|*.FRD|Text (*.TXT)|*.TXT|Wave (*.WAV)|*.WAV|Impedance (*.ZMA)|*.ZMA|Time (*.IMP)|*.IMP|All Files (*.*)|*.*||",
		 this );

	cstitle.LoadString( IDS_IMPORT);

    cdlg.m_ofn.lpstrTitle = (LPCSTR )cstitle;

	CAudtestApp::GetLastImport( csimport);			// get last file imported
	if ( csimport.GetLength() > 3)
	{			// look for a suffix
	int idot = csimport.ReverseFind(TCHAR('.'));	// find the last period
		if ( idot == csimport.GetLength() - 4)		// at the right place?
		{
			csuffix = csimport.Right( 3);			// get the last 3 chars
			csuffix.MakeUpper();					// upcase it
		}
	}

	{			// get the initial directory
	CString csdir;

		if ( !csimport.IsEmpty())
		{
		int islash = csimport.ReverseFind(TCHAR('\\'));		// find the last slash
			if ( islash >= 0)
				csimport = csimport.Left( islash);			// up to the last slash is the directory
			else
				csimport = "";			// empty it
		}
		cdlg.m_ofn.lpstrInitialDir = csimport;
	}

	{			// get the filter index
	CString call = "CIRFRDTXTWAVZMAIMP";		// suffixes
	int isuf = call.Find( csuffix);				// is it in there
		if ( isuf < 0)
			isuf = 0;
		else
			isuf = 1 + isuf / 3;				// divide by 3 to get the # (base 1)
		cdlg.m_ofn.nFilterIndex = isuf;
	}

	if ( IDOK == cdlg.DoModal())
		{					// import cdlg.GetPathname();
		CNamed *cnam;

		pDoc->BeginWaitCursor();
		switch( cdlg.m_ofn.nFilterIndex)
			{
			case 1 :			// network
				cnam = new CNetwork;
				break;
			case 4 :			// wav file
				cnam = new CGenerator;
				break;
			default :
				cnam = new CDataSet;
			}
		cnam->Import( cdlg.GetPathName());
		DBG_PRINT("Did import");
		cnam->SetName( cdlg.GetFileName());
		DBG_PRINT("Did set name");

		csimport = cdlg.GetPathName();
		CAudtestApp::SetLastImport( csimport);

		{			// do an op insert here
		pDoc->InsertNewObject( pDoc->GetRoot(), cnam);
		}
//		pDoc->GetRoot()->AddItem( cnam);
		DBG_PRINT("Did add item");
		pDoc->EndWaitCursor();
		pDoc->UpdateAll( NULL, cnam->GetID());
		DBG_PRINT("Did update all");
		}
	
}


// -----------------------------------------------------------------
// -------------  Dialog_Perform
// -----------------------------------------------------------------
void CAudtestView::Dialog_Perform( void *pcThis)
{
CXcalc *cxthis = (CXform *)pcThis;
CAudtestDoc* pDoc = GetDocument();
CNamed *cname;

	cname = pDoc->GetByID( GetTarget());
	if ( ! cname)
		return;

	if ( IDOK == cxthis->DoDialog(  ) )
		{
		if ( cxthis->QueueAndDo( ))			// succeeded
			delete cxthis;
		}
	else
		delete cxthis;
}



// -----------------------------------------------------------------
// -------------  OnResourceExport
// -----------------------------------------------------------------
void CAudtestView::OnResourceExport() 
{
CAudtestDoc* pDoc = GetDocument();
DWORD dwid = GetTarget();
CNamed *cnam;

	if ( ! dwid)
		return;
		
	cnam = pDoc->GetByID( dwid);

	pDoc->ExportResource( cnam);
		
}


// -----------------------------------------------------------------
// -------------  OnMouseMove
// -----------------------------------------------------------------
void CAudtestView::OnMouseMove(UINT nFlags, CPoint point) 
{	// TODO: Add your message handler code here and/or call default

	CView::OnMouseMove(nFlags, point);
}

// -----------------------------------------------------------------
// -------------  OnLButtonUp
// -----------------------------------------------------------------
void CAudtestView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_ptMouseUp = point;

	CView::OnLButtonUp(nFlags, point);
}

// -----------------------------------------------------------------
// -------------  OnLButtonDown
// -----------------------------------------------------------------
void CAudtestView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_ptMouseDown = point;

	CView::OnLButtonDown(nFlags, point);
}

// -----------------------------------------------------------------
// -------------  OnRButtonDown
// -----------------------------------------------------------------
void CAudtestView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	m_ptMouseDown = point;

	CView::OnRButtonDown(nFlags, point);
}

// -----------------------------------------------------------------
// -------------  OnRButtonUp
// -----------------------------------------------------------------
void CAudtestView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_ptMouseUp = point;
	
	DoPopupMenu( point.x, point.y);
	
	CView::OnRButtonUp(nFlags, point);
}

// -----------------------------------------------------------------
// -------------  OnLButtonDblClk
// -----------------------------------------------------------------
void CAudtestView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonDblClk(nFlags, point);
}


// -----------------------------------------------------------------
// -------------  GetMenuResource
// -----------------------------------------------------------------
UINT CAudtestView::GetMenuResource(void )
{
			    /*
			     * Build a popup menu for this object with Cut, Copy, Delete,
			     * and object verbs.
			     */
	return( IDR_MTESTVIEW);
}


// -----------------------------------------------------------------
// -------------  DoPopupMenu
// -----------------------------------------------------------------
BOOL CAudtestView::DoPopupMenu(UINT x, UINT y)
{
POINT       pt;
CMenu		cmenures;
CMenu		*pmenu;
CWnd		*cwndframe, *cwnd;

			    //Select the tenant under the mouse, if there is one.
//    if (!FSelectTenantAtPoint(x, y))
//	      return FALSE;
			    /*
			     * Get the top-level window to which menu command will go. This
			     * will be whatever parent doesn't have a parent itself...
			     */
    cwnd = GetParent();

	if ( ! cwnd)
		return FALSE;

    do
        {
        cwndframe = cwnd;
        cwnd = cwnd->GetParent();
        } while( cwnd);

			    /*
			     * Build a popup menu for this object with Cut, Copy, Delete,
			     * and object verbs.
			     */
	UINT uidmenu = GetMenuResource( );

	if ( ! uidmenu)
		return FALSE;

	cmenures.LoadMenu( uidmenu);
	pmenu = cmenures.GetSubMenu(0);
		    //Resource-loaded menus don't work, so we'll copy the items.
    pt.x = x; pt.y = y;
    ClientToScreen( &pt);

    pmenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_LEFTBUTTON, pt.x, pt.y, cwndframe);

    cmenures.DestroyMenu( );
    return FALSE;
}
  

BOOL CAudtestView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
CRectTracker *ptrack = GetTracker();

	if ( ptrack)			// we're tracking
		if ( ptrack->SetCursor( this, nHitTest))
			return 0;			// that's all
	
	return CView::OnSetCursor(pWnd, nHitTest, message);
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 						CAudchView 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CAudchView, CAudtestView)

CAudchView::CAudchView()
{
	m_cChart = NULL;
	::SetRectEmpty( & m_rcSubview);
	m_iCharWidth = 0;			// not yet
	m_iCharHeight = 0;			// not yet calculated
	m_ptFloatFormat.x = 10;		// total field size
	m_ptFloatFormat.y = 3;		// decimal points
	m_iIntFormat = 6;			// # of int places
	m_pDrawDC = NULL;			// no dc pointer for now
}

CAudchView::~CAudchView()
{
	SetViewChart( NULL);
}


BEGIN_MESSAGE_MAP(CAudchView, CAudtestView)
	//{{AFX_MSG_MAP(CAudchView)
	ON_COMMAND(ID_EDIT_CHARTPROPERTIES, OnEditChartproperties)
	ON_COMMAND(ID_TRANSFORM_CHART, OnMakeChart)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_EDIT_INSERT, OnEditInsert)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditData)
	ON_COMMAND(ID_VIEW_ZOOM, OnViewZoom)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
	ON_COMMAND(ID_CHART_ADDDATA, OnChartAdddata)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_EDIT_CHARTDEFAULT, OnEditChartdefault)
	ON_COMMAND(ID_EDIT_USEDEFAULT, OnEditUsedefault)
	ON_WM_CHAR()
	ON_COMMAND(ID_CHART_NOTE, OnChartNote)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAudchView drawing

// -----------------------------------------------------------------
// -------------  BuildCharSizes
// -----------------------------------------------------------------
int		CAudchView::CharWidth( CDC *pDC)
{
	BuildCharSizes( pDC);

	return m_iCharWidth;
}


// -----------------------------------------------------------------
// -------------  BuildCharSizes
// -----------------------------------------------------------------
int		CAudchView::CharHeight( CDC *pDC)
{
	BuildCharSizes( pDC);

	return m_iCharHeight;
}

// -----------------------------------------------------------------
// -------------  BuildCharSizes
// -----------------------------------------------------------------
// -----------------------------------------------------------------
// -------------  BuildCharSizes
// -----------------------------------------------------------------
void	CAudchView::BuildCharSizes( CDC *pDC)		// build the character sizes
{
CSize csz;

	if ( pDC == m_pDrawDC)			// we've done it already?
		return;
	csz = pDC->GetTextExtent( "000", 3);
	m_iCharWidth = csz.cx / 3;			// size of a zero
	m_iCharHeight = csz.cy;				// height of a zero
	m_pDrawDC = pDC;					// save so we know we did it
}


// -----------------------------------------------------------------
// -------------  DrawVariable
// -----------------------------------------------------------------
int CAudchView::DrawVariable( CDC *pDC, sFormField *pField, float fVar, int iOffset)
{
CString csi;
CString csout;
CString csformat;
CSize  csize, csz2;
int ioldmode;

	BuildCharSizes( pDC);					// make sure char sizes are right
	ioldmode = pDC->SetBkMode( TRANSPARENT);


	csi.LoadString( pField->uidPrompt);		// get the string
	pDC->TextOut( m_iCharWidth*pField->iX, m_iCharHeight*pField->iY, csi);
	csformat.Format("%%%d.0f", m_ptFloatFormat.x - m_ptFloatFormat.y);		// total size
	csi.Format(csformat, fVar);
	csz2 = pDC->GetTextExtent( csi);				// get char size and decimal point location
	csformat.Format("%%%d.%df", m_ptFloatFormat.x, m_ptFloatFormat.y);
	csi.Format(csformat, fVar);
				//move to the left by cx to get decimals to line up
	pDC->TextOut( m_iCharWidth*pField->iX + iOffset - csz2.cx, 
				  m_iCharHeight*pField->iY, csi);
	csize = pDC->GetTextExtent( csi);				// get char size and decimal point location
	csz2.cx = m_iCharWidth + csize.cx + iOffset - csz2.cx;		// new offset
	csi.LoadString( pField->uidEndPrompt);				// get the string
	pDC->TextOut(  m_iCharWidth*pField->iX + csz2.cx, m_iCharHeight * pField->iY, csi);

	pDC->SetBkMode( ioldmode);
	csize = pDC->GetTextExtent( csi);
	return (csize.cx + csz2.cx);

}

// -----------------------------------------------------------------
// -------------  DrawVariable
// -----------------------------------------------------------------
int CAudchView::DrawVariable( CDC *pDC, sFormField *pField, int iVar, int iOffset)
{
CString csi;
CString csout;
CString csformat;
CSize  csize, csz2;
int ioldmode;

	BuildCharSizes( pDC);					// make sure char sizes are right
	ioldmode = pDC->SetBkMode( TRANSPARENT);

	csi.LoadString( pField->uidPrompt);		// get the string
	pDC->TextOut( m_iCharWidth*pField->iX, m_iCharHeight*pField->iY, csi);
	csformat.Format("%%%dd", m_iIntFormat);		// total size
	csi.Format(csformat, iVar);
	csz2 = pDC->GetTextExtent( csi);				// get char size and decimal point location
				//move to the left by cx to get decimals to line up
	pDC->TextOut( m_iCharWidth*pField->iX + iOffset - csz2.cx, 
				  m_iCharHeight*pField->iY, csi);
	csize = pDC->GetTextExtent( csi);				// get char size and decimal point location
	csz2.cx = m_iCharWidth * (1 + m_ptFloatFormat.y) + csize.cx + iOffset - csz2.cx;		// new offset
	csi.LoadString( pField->uidEndPrompt);				// get the string
	pDC->TextOut(  m_iCharWidth*pField->iX + csz2.cx, m_iCharHeight * pField->iY, csi);

	pDC->SetBkMode( ioldmode);
	csize = pDC->GetTextExtent( csi);
	return (csize.cx + csz2.cx);

}

// -----------------------------------------------------------------
// -------------  DrawVariable
// -----------------------------------------------------------------
int CAudchView::DrawVariable( CDC *pDC, sFormField *pField, bool bValue)
{
CString csi;
CSize  csz2, csize;
int ioldmode;

	BuildCharSizes( pDC);					// make sure char sizes are right
	ioldmode = pDC->SetBkMode( TRANSPARENT);

	csi.LoadString( pField->uidPrompt);		// get the string
	pDC->TextOut( m_iCharWidth*pField->iX, m_iCharHeight*pField->iY, csi);
	csz2 = pDC->GetTextExtent( csi);				// get char size and decimal point location
				//move to the left by cx to get decimals to line up
	csi = bValue ? "Yes" : "No";
	pDC->TextOut( m_iCharWidth*pField->iX + csz2.cx + m_iCharWidth, m_iCharHeight*pField->iY, csi);

	pDC->SetBkMode( ioldmode);
	csize = pDC->GetTextExtent( csi);
	return (csize.cx + csz2.cx + m_iCharWidth);
}

// -----------------------------------------------------------------
// -------------  DrawVariable
// -----------------------------------------------------------------
int CAudchView::DrawVariable( CDC *pDC, sFormField *pField, CString &csValue)
{
CString csi;
CSize  csz2, csize;
int ioldmode;

	BuildCharSizes( pDC);					// make sure char sizes are right
	ioldmode = pDC->SetBkMode( TRANSPARENT);

	csi.LoadString( pField->uidPrompt);		// get the string
	pDC->TextOut( m_iCharWidth*pField->iX, m_iCharHeight*pField->iY, csi);
	csz2 = pDC->GetTextExtent( csi);				// get char size and decimal point location
				//move to the left by cx to get decimals to line up
	pDC->TextOut( m_iCharWidth*(pField->iX+1) + csz2.cx, m_iCharHeight*pField->iY, csValue);

	pDC->SetBkMode( ioldmode);
	csize = pDC->GetTextExtent( csValue);
	return (csize.cx + csz2.cx);
}


// -----------------------------------------------------------------
// -------------  DrawForm
// -----------------------------------------------------------------
int CAudchView::DrawForm( CDC *pDC, sFormField *pField)
{
CString csi;
CString csout;
CSize  csz;

	BuildCharSizes( pDC);					// make sure char sizes are right

	csi.LoadString( pField->uidPrompt);		// get the string
	pDC->TextOut( m_iCharWidth*pField->iX, m_iCharHeight*pField->iY, csi);

	csz = pDC->GetTextExtent( csi);

	return csz.cx;

}

// -----------------------------------------------------------------
// -------------  FormExtent
// -----------------------------------------------------------------
int CAudchView::FormExtent( CDC *pDC, sFormField *pField)
{
CString csi;
CSize  csz;

	csi.LoadString( pField->uidPrompt);		// get the string
	csz = pDC->GetTextExtent( csi);

	return csz.cx;

}

// -----------------------------------------------------------------
// -------------  MakeViewChart
// -----------------------------------------------------------------
void CAudchView::MakeViewChart( void)
{
CAudtestDoc* pDoc = GetDocument();
CGraphed *cdata;
CNamed *cname = GetTargetObject();

	ASSERT( cname);
	if ( ! cname)
		return;
	cdata = (CGraphed *)cname;

	if ( ! GetViewChart())						// does this view have a chart???
		{
		CSubChart *chart;

		if ( ! cdata->GetChart())
			cdata->CreateChart();
		chart = cdata->GetChart();
		if ( ! chart)
			return;
		SetViewChart ( chart);		// keep this
		GetViewChart()->SetRootObject( pDoc->GetRoot());	// since it doesn't get added to the tree
		}

}


// -----------------------------------------------------------------
// -------------  OnDraw
// -----------------------------------------------------------------
void CAudchView::OnDraw(CDC* pDC)
{
CRect rcclient;
CSubChart *cch;

			// adjust m_rcPrint based on the subarray
	if (m_rcSubview.top != 0)
	{
	RECT rcnew;
					// adjust the supplied rectangle
		rcnew.left =  m_rcSubview.left;
		rcnew.right = m_rcPrint.right - m_rcSubview.right;
		rcnew.top =    m_rcSubview.top;
		rcnew.bottom = m_rcPrint.bottom - m_rcSubview.bottom;

		if ( (rcnew.right <= (rcnew.left+30)) || (rcnew.bottom <= (rcnew.top+70)))		// nothing to draw
			::SetRectEmpty( &m_rcPrint);
		else
			m_rcPrint = rcnew;			// adjust the rectangle

		if ( pDC->IsPrinting())		// this is taken from PrepareDC
		{
		int nth = m_rcPrint.top + (3 * (m_rcPrint.right - m_rcPrint.left)) / 4;
			if ( m_rcPrint.bottom < nth)		// shrink width
				{
				m_rcPrint.right = m_rcPrint.left + (4 * (m_rcPrint.bottom - m_rcPrint.top)) / 3;
				}
			else if ( m_rcPrint.bottom > nth)		// shrink height
				{
				m_rcPrint.bottom = nth;
				}
		}

	}

	MakeViewChart();

	rcclient = m_rcPrint;	// use printing rectangle

	cch = (CSubChart *)GetViewChart();
	if ( cch && ! IsRectEmpty( &m_rcPrint))
		cch->DoDraw( pDC, &rcclient);

	CAudtestView::OnDraw( pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CAudchView diagnostics
/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
void CAudchView::AssertValid() const
{
	CAudtestView::AssertValid();
}

void CAudchView::Dump(CDumpContext& dc) const
{
	CAudtestView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAudchView message handlers

// -----------------------------------------------------------------
// -------------  OnEditChartproperties
// -----------------------------------------------------------------
void CAudchView::OnEditChartproperties() 
{
	if ( m_cChart)
		if ( IDOK == m_cChart->EditProperties(this ))
			{
			CGraphed *cnam;
			CAudtestDoc* pDoc = GetDocument();

				cnam = (CGraphed *)GetTargetObject();
				if ( cnam)			// we have a target dataset, store the chart def
					{				// so as to reuse the definition by default later
					cnam->SetChart( m_cChart);
					}
		
			pDoc->UpdateAll( NULL, GetTarget());
			}
}


// -----------------------------------------------------------------
// -------------  OnMakeChart
// -----------------------------------------------------------------
void CAudchView::OnMakeChart() 
{
CNamed *cname;
CAudtestDoc* pDoc = GetDocument();
CChart *cchart;
CDataSet *cdata;
COpMakeChart *cmake;

	cname = GetTargetObject();
	if ( ! cname)
		return;

	if ( ntDataSet != cname->GetType() )
		return;

	cdata = (CDataSet *)cname;

	cmake = new COpMakeChart( pDoc, cname->GetID());
	cmake->QueueAndDo( );
	cchart = cmake->GetChart();

	pDoc->OpenResource( cchart);

}

void CAudchView::SetViewChart( CSubChart *cNew)
{
				// tell the dlglocations window to update itself if we're it
		{
		CDlgLocations *cloc = (CDlgLocations *)CAudtestApp::GetLocationWindow();
		CNamed *cchart = GetViewChart();

			if ( cchart && cloc)
				if ( cchart == cloc->GetLocator())
					{
					cloc->SetLocator( NULL);			// now recalc for a "new" owner
					}
		}

	if ( ! cNew)
		{
		if ( m_cChart)
			delete m_cChart;
		m_cChart = NULL;
		}
	else
		{
		if ( m_cChart)
			*m_cChart = *cNew; 
		else 
			m_cChart = (CSubChart *)(cNew->Duplicate());
		}

}

// find any new datasets in the target object's chart and move them over
// -----------------------------------------------------------------
// -------------  SyncDataSets
// -----------------------------------------------------------------
void CAudchView::SyncDataSets()
{
CSubChart *cdest, *csource;
CGraphed *cnam = (CGraphed *)GetTargetObject();
CDataLine *cdl;
int i;

	if ( ! cnam)
		return;		// !!!!

	cdest = (CSubChart *)GetViewChart();

	csource = (CSubChart *)cnam->GetChart();

	if ( (!csource) || !cdest)
		return;

	cdl = csource->GetDataAt( 0);
	for ( i=0; cdl; i++)
		{
		cdest->Attach( cdl->GetDataID(), TRUE);		// does nothing if already there
		cdl = csource->GetDataAt( i+1);
		}

}


// -----------------------------------------------------------------
// -------------  OnMouseMove
// -----------------------------------------------------------------
void CAudchView::OnMouseMove(UINT nFlags, CPoint point) 
{
						// -------------------------------
						// send location to locations dbox
	{					// -------------------------------
	CDlgLocations *cloc = (CDlgLocations *)CAudtestApp::GetLocationWindow();
	CSubChart *cc = (CSubChart *)GetViewChart();

		if ( cloc && cc)
			cloc->UpdateLocator( cc, point);
	}

						
	CAudtestView::OnMouseMove(nFlags, point);
}

// -----------------------------------------------------------------
// -------------  OnUpdate
// -----------------------------------------------------------------
void CAudchView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
				// tell the dlglocations window to update itself if we're it
	if ( (!lHint) || (DWORD )lHint == GetTarget())
		{
		CDlgLocations *cloc = (CDlgLocations *)CAudtestApp::GetLocationWindow();
		CNamed *cchart = GetViewChart();

			if ( cchart && cloc)
				if ( cchart == cloc->GetLocator())
					{
					cloc->SetLocator( NULL);			// now recalc for a "new" owner
					}
		}

				// check to see if we're charting any of these datasets
	if ( lHint && (GetTarget() != (DWORD )lHint))	// if it's us, do it automatically
		{
		CSubChart *cchart = (CSubChart *)GetViewChart();
		int i;
		BOOL bshow = FALSE;

			if ( cchart)
				for ( i = 0; cchart->GetDatasetAt(i); i++)
					{
					CNamed *cdata = cchart->GetDatasetAt(i);	// get the dataset
					if ( (DWORD )lHint == cdata->GetID())
						{
						bshow = TRUE;
						break;
						}
					}
			if ( !bshow)	// nothing to do here
				return;				// default view OnUpdate is repaint the screen...
		}

	CAudtestView::OnUpdate( pSender, lHint, pHint);
	
}

// -----------------------------------------------------------------
// -------------  GetMenuResource
// -----------------------------------------------------------------
UINT CAudchView::GetMenuResource(void )
{
	return IDR_MSUBCHARTVIEW;
}





// -----------------------------------------------------------------
// -------------  OnLButtonDblClk
// -----------------------------------------------------------------
void CAudchView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
CSubChart *cch;

	cch = (CSubChart *)GetViewChart();
	if ( cch)
		{
		CDrawObj *cnew;

			cnew = cch->GetHitObject( point);

			if ( cnew && (ntDataTag == cnew->GetType()) )	// it's a datatag
			{
			CDataTag *ptag = (CDataTag *)cnew;

				ptag->EditProperties( this);
				InvalidateRect( NULL);
			}
			else
			if ( IDOK == cch->EditProperties( this, cnew))
				{
				CGraphed *cnam;
				CAudtestDoc* pDoc = GetDocument();

					cnam = (CGraphed *)GetTargetObject();
					if ( cnam)			// we have a target dataset, store the chart def
						{				// so as to reuse the definition by default later
						cch = (CSubChart *)GetViewChart();	// in case it changed in edit properties
						cnam->SetChart( cch);
						}
			
				pDoc->UpdateAll( NULL, GetTarget());
				}
		}
	
	
	CAudtestView::OnLButtonDblClk(nFlags, point);
}


// -----------------------------------------------------------------
// -------------  OnLButtonDown
// -----------------------------------------------------------------
void CAudchView::OnLButtonDown(UINT nFlags, CPoint point) 
{
CSubChart *cch;
CRectTracker *ptrack = GetTracker();

	m_ptMouseDown = point;
	cch = (CSubChart *)GetViewChart();

	if ( ptrack)			// we're tracking
		{
		int nhit = ptrack->HitTest( point);
			switch( nhit)
			{
			case CRectTracker::hitMiddle :
				if ( m_nTrackType == ntDataTag)
				{
				CDataTag *ptag;

					ptag = (CDataTag *)m_pTrackObject;
					if ( ptrack->Track( this, point, FALSE) )			// track it
					{
						// move the datatag
						ptag->SetTextOffset( ptrack->m_rect.TopLeft());
						InvalidateRect(NULL);
					}
					return;			// we're done tracking this guy - dont continue
				}
				else
					SetTracker( NULL, NULL);
				break;
			case CRectTracker::hitNothing :
				SetTracker( NULL, NULL);
				break;
			default:
				if ( m_nTrackType != ntDataTag)
				{
				CRect crzoom;
				ptrack->SetCursor( this, nhit);
				if ( ptrack->Track( this, point, FALSE) )			// track it
					{
					crzoom = ptrack->m_rect;
					if ( cch)
						{
						cch->Zoom( crzoom);
						cch->GetBorder( &ptrack->m_rect);		// reset it to the whole thing
						InvalidateRect( NULL);
						return;									// we're done
						}
					}
				}
				else			// it was a datatag
					SetTracker( NULL, NULL);
				break;
			}
		}
	cch = (CSubChart *)GetViewChart();
	if ( cch)
		{
		CDrawObj *cnew;

			cnew = cch->GetHitObject( point);
			if ( ( (!cnew) && cch->GetHighlighted() ) ||
				 (cnew && !cnew->IsHighlighted()) )
				{
				cch->SetHitObject( cnew, (MK_SHIFT & nFlags) ? TRUE : FALSE);
				if ( cnew)
					{
					switch( cnew->GetType())
						{
						case ntBorder :
							{
							CRectTracker *cr = setup_Tracker(cnew);
							SetTracker( cr, cnew);
							}
							break;
						case ntInside :
							{
							CRectTracker *cr = setup_Tracker(cnew);
							CPoint ptstart = point;
							SetTracker( cr, cnew);
							if ( cr->TrackRubberBand(this, ptstart))
								{
								CRect rc = cr->m_rect;
								if ( rc.right < rc.left)
									{
									int n = rc.left;
									rc.left = rc.right;
									rc.right = n;
									}
								if ( rc.bottom < rc.top)
									{
									int n = rc.top;
									rc.top = rc.bottom;
									rc.bottom = n;
									}
								if ( (rc.right - rc.left) > 10 && (rc.bottom - rc.top) > 10)		// do it
									{
									cch->Zoom( rc);
									}
								}
							SetTracker( NULL, NULL);
							cch->SetHitObject(NULL, FALSE);
							}
							break;
						case ntMarker :
							{
							CRectTracker *cr = setup_Tracker(cnew);
							CPoint ptstart = point;
							ptstart.y = cr->m_rect.top;
							ptstart.x = cr->m_rect.left;
							SetTracker( cr, cnew);
							cr->m_sizeMin.cy = cr->m_rect.bottom - cr->m_rect.top;
							if ( cr->TrackRubberBand(this, ptstart))
								{
								cch->SetMarkerLocation( (CMarker *)cnew, cr->m_rect.right);
								}
							SetTracker( NULL, NULL);
							cch->SetHitObject(NULL, FALSE);
							}
							break;

						case ntDataTag :
							{
							CRectTracker *cr = setup_Tracker(cnew);
							SetTracker( cr, cnew);
							}
							break;

						default:
							break;
						}
					}
				InvalidateRect( NULL);
				}
		}
	
	CAudtestView::OnLButtonDown(nFlags, point);
}

// -----------------------------------------------------------------------
//		SetTracker
//			set the View local tracker variables
// -----------------------------------------------------------------------
void CAudtestView::SetTracker( CRectTracker *cNew, CDrawObj *pObject)
{
	if ( m_pTracker)
		delete m_pTracker;
	m_pTracker = cNew; 
	m_pTrackObject = pObject;
	if ( NULL != pObject)
		m_nTrackType = pObject->GetType();
	else
		m_nTrackType = ntAny;
}
// -----------------------------------------------------------------
// -------------  OnLButtonUp
// -----------------------------------------------------------------
void CAudchView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_ptMouseUp = point;
	
	CAudtestView::OnLButtonUp(nFlags, point);
}


// -----------------------------------------------------------------
// -------------  OnEditDelete
// -----------------------------------------------------------------
void CAudchView::OnEditDelete() 
{
CSubChart *cchart;

	cchart = (CSubChart *)GetViewChart();
	if ( ! cchart)
		return;

	if ( cchart)
		{
		CDrawObj *cnew;

			cnew = cchart->GetHighlighted();

			if ( cnew)
			{
				switch( cnew->GetType() )
				{
				case ntDataLine :
					cchart->Detach( ((CDataLine *)cnew)->GetDataID());
					break;
				case ntDataTag :
					cchart->DeleteNote( (CDataTag *)cnew);
					break;
				default:
					ASSERT(0);
					break;			// we shouldn't get here
				}
			}

		InvalidateRect(NULL );
		}
	
}

// -----------------------------------------------------------------
// -------------  OnEditInsert
// -----------------------------------------------------------------
void CAudchView::OnEditInsert() 
{
	OnChartAdddata();	
}


// -----------------------------------------------------------------
// -------------  OnUpdateEditData
// -----------------------------------------------------------------
void CAudchView::OnUpdateEditData(CCmdUI* pCmdUI) 
{
CSubChart *cch;
BOOL benable = FALSE;

	cch = (CSubChart *)GetViewChart();
	if ( cch)
		{
		CDrawObj *cnew;

			cnew = cch->GetHighlighted();

			if ( cnew)
				benable = ( ntDataLine == cnew->GetType() ) || ( ntDataTag == cnew->GetType() );
		}
	
	pCmdUI->Enable( benable);

}


// -----------------------------------------------------------------
// -------------  OnViewZoom
// -----------------------------------------------------------------
void CAudchView::OnViewZoom() 
{
CSubChart *cch;
		
	cch = (CSubChart *)GetViewChart();
	if ( cch)
		{
		if ( ! cch->Zoom( GetMouseDown() ) )		// we did something
			InvalidateRect( NULL);
		else
			AfxMessageBox(IDS_ERR_NOZOOM );
		}
}

// -----------------------------------------------------------------
// -------------  OnViewZoomout
// -----------------------------------------------------------------
void CAudchView::OnViewZoomout() 
{
CSubChart *cch;
		
	cch = (CSubChart *)GetViewChart();
	if ( cch)
		{
		if ( ! cch->Zoom(  ) )		// we did something
			InvalidateRect( NULL);
		}
		
}


// -----------------------------------------------------------------
// -------------  OnOptionsCalibrate
// -----------------------------------------------------------------
void CAudtestView::OnOptionsCalibrate() 
{
CDlgCalibrate cdlg;
TESTCAL tcal;

	cdlg.m_pView = this;
	cdlg.m_pDocument = (CAudtestDoc *)this->GetDocument();
	tcal = *cdlg.m_pDocument->GetCalib();
	cdlg.m_dwChannelDiff = tcal.dwLeftRight;
	cdlg.m_dwMicResponse = tcal.dwMicrophone;
	cdlg.m_dwAmpResponse = tcal.dwAmplifier;

	if ( IDOK == cdlg.DoModal())
		{
		if ( cdlg.m_csChannelDiff.GetLength())
			tcal.dwLeftRight = cdlg.m_dwChannelDiff;
		else
			tcal.dwLeftRight = 0;
		if ( cdlg.m_csMicResponse.GetLength())
			tcal.dwMicrophone = cdlg.m_dwMicResponse;
		else
			tcal.dwMicrophone = 0;
		if ( cdlg.m_csAmpResponse.GetLength())
			tcal.dwAmplifier = cdlg.m_dwAmpResponse;
		else
			tcal.dwAmplifier = 0;
		cdlg.m_pDocument->SetCalib( &tcal);
		}

}

// -----------------------------------------------------------------
// -------------  OnOptionsTuned
// bring up the tuned circuits dialog box
// -----------------------------------------------------------------
void CAudtestView::OnOptionsTuned() 
{
	if ( CDlgCalcTuned::IsShowing())
		return;

CDlgCalcTuned *pdlg = new CDlgCalcTuned(AfxGetMainWnd());

	pdlg->Create( IDD_CALCTUNED);

	pdlg->ShowWindow( SW_SHOW );
	
}

// -----------------------------------------------------------------
// -------------  OnOptionsTuned
// bring up the passive calculation dialog box
// -----------------------------------------------------------------
void CAudtestView::OnOptionsPassive() 
{
	if ( CDlgCalcPassive::IsShowing())
		return;

CDlgCalcPassive *pdlg = new CDlgCalcPassive(AfxGetMainWnd());

	pdlg->Create( IDD_CALCPASSIVE);

	pdlg->ShowWindow( SW_SHOW );
	
}

// -----------------------------------------------------------------
// -------------  OnOptionsDistance
// bring up the time distance calculation box
// -----------------------------------------------------------------
void CAudtestView::OnOptionsDistance() 
{
	if ( CDlgTimeDist::IsShowing())
		return;

CDlgTimeDist *pdlg = new CDlgTimeDist(AfxGetMainWnd());

	pdlg->Create( IDD_TIMEDIST);

	pdlg->ShowWindow( SW_SHOW );
	
	
}

// -----------------------------------------------------------------
// -------------  OnOptionsVolume
// bring up the volume calculation box
// -----------------------------------------------------------------
void CAudtestView::OnOptionsVolume() 
{
	if ( CDlgVolumeCalc::IsShowing())
		return;

CDlgVolumeCalc *pdlg = new CDlgVolumeCalc(AfxGetMainWnd());

	pdlg->Create( IDD_VOLUMECALC);

	pdlg->ShowWindow( SW_SHOW );
	
	
}


// -----------------------------------------------------------------
// -------------  OnChartAdddata
// add a dataset to the chart
// -----------------------------------------------------------------
void CAudchView::OnChartAdddata() 
{
CDlgSelectObject cdlg;
CAudtestDoc* pDoc = GetDocument();
CSubChart *cchart;
CDataSet *cdest;
UNITMSR nuom = uomAny;

	cchart = (CSubChart *)GetViewChart();
	if ( ! cchart)
		return;

	cdest = cchart->GetDatasetAt( 0);
	if ( cdest)
		nuom = cdest->GetUOM();			// restrict to the uom of any existing data set

	cdlg.SetParms( pDoc->GetRoot(), 0, ntDataSet, nuom);

	if ( IDOK == cdlg.DoModal())
		{
		if ( cdlg.GetSelected())			// did we add one?
			{
			cchart->Attach( cdlg.GetSelected());

			UpdateBaseChart();

			pDoc->UpdateAllViews( NULL, (LPARAM )GetTarget());
			}
		}
	
}

// -----------------------------------------------------------------
// -------------  UpdateBaseChart
// update the base chart definition if it's a chart
// -----------------------------------------------------------------
void	CAudchView::UpdateBaseChart( void)		// copy the current view chart to the base chart
{
CSubChart *cchart;
CGraphed *cnam;

	cchart = (CSubChart *)GetViewChart();
	if ( ! cchart)
		return;

	cnam = (CGraphed *)GetTargetObject();
	if ( cnam )			// we have a target object, store the chart def into it
		{				// so as to reuse the definition by default later
		cnam->SetChart( cchart);	// so we have the def'n updated in the chart
		}

}


// -----------------------------------------------------------------
// -------------  SetSubView
// set a smaller rectangle to draw the chart into
// -----------------------------------------------------------------
void	CAudchView::SetSubView( LPCRECT lpcrNew)
{
	if ( lpcrNew)
		m_rcSubview = *lpcrNew;
	else
	{
		::SetRectEmpty( & m_rcSubview);
	}
}


// this sets up the print area so that we print the right # of pixels when drawing charts

void CAudchView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
CRect rc;

	CAudtestView::OnPrepareDC(pDC, pInfo);

			// if we're printing, set the map mode
	if ( pInfo && pInfo->m_nCurPage)		// per doc, this is how you check
		{
		CAudtestApp::ClearAllPrinterFonts();

		pDC->SetMapMode( MM_TEXT); 

		rc.SetRect( 0,0,pDC->GetDeviceCaps( HORZRES), pDC->GetDeviceCaps( VERTRES) );
		}
	else
			GetClientRect( &rc);

	m_rcPrint = rc;
			// change the aspect ratio if we're printing to (3::4) && not driver view
	if ( pInfo && pInfo->m_nCurPage && ! IsKindOf( RUNTIME_CLASS(CAudDriverView)))		// per doc, this is how you check
		{
		int nth = m_rcPrint.top + (3 * (m_rcPrint.right - m_rcPrint.left)) / 4;
		if ( m_rcPrint.bottom < nth)		// shrink width
			{
			m_rcPrint.right = m_rcPrint.left + (4 * (m_rcPrint.bottom - m_rcPrint.top)) / 3;
			}
		else if ( m_rcPrint.bottom > nth)		// shrink height
			{
			m_rcPrint.bottom = nth;
			}
		}
	
}

void CAudtestView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
CRect rc;
CFont *cfont;
CFont *cfold;
CString cshead;
int nheight;

	if ( pInfo)
		rc = pInfo->m_rectDraw;		// note that here it is accurate

				// get the header font
	cfont = CAudtestApp::GetAppFont( ftNetData).GetCurrentFont( pDC);
	cfold = pDC->SelectObject( cfont);

	{			// format the date and time string
	CString csname;
	CString csfilename;
	CString csdatetime;

	CNamed *cname = GetTargetObject();

		if ( cname)
			csname = cname->GetFullName();

		csfilename = GetDocument()->GetTitle();
		{
		CTime theTime;
			theTime = CTime::GetCurrentTime();
			csdatetime = theTime.Format("%c");
		}

	cshead.Format( "Speaker Workshop  %s  %s  %s", (LPCSTR )csfilename, (LPCSTR )csname, (LPCSTR )csdatetime);
	}

	nheight = pDC->DrawText( (LPCSTR )cshead, -1, &rc, DT_NOPREFIX | DT_SINGLELINE | DT_CENTER | DT_BOTTOM);

	if ( cfold)
		pDC->SelectObject( cfold);
	
	CView::OnPrint(pDC, pInfo);
}

void CAudtestView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{				// tell the mainframe to reset the toolbar

	if ( bActivate)
		{
		CMainFrame *cw = (CMainFrame *)AfxGetMainWnd();

			cw->ResetToolbar( pActivateView);

			CAudtestApp::SetCurrentView( pActivateView);
		}
//	else
//	{
//			CAudtestApp::SetCurrentView( NULL);
//	}
		
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


void CAudtestView::OnWizardSetvolume() 
{

				// temporarily
	AfxMessageBox(IDS_UNDERCONSTRUCT);
	return;
#if 0
CDlgCalWizVol cdlg( this);

	cdlg.SetView( this);
	cdlg.DoModal();
#endif	
	
}

BOOL CAudtestView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CAudchView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
CSubChart *cch;
		
	cch = (CSubChart *)GetViewChart();
	if ( cch)
	{
		ScreenToClient( &pt);
		if ( zDelta > 0)				// zoom in
		{
			if ( ! cch->Zoom( pt ) )		// we did something
				InvalidateRect( NULL);
			else
				AfxMessageBox(IDS_ERR_NOZOOM );
		}
		else
		{								// zoom out
			if ( ! cch->ZoomOut( pt ) )		// we did something
				InvalidateRect( NULL);
			else
				AfxMessageBox(IDS_ERR_NOZOOM );
		}
	}
	
	return CAudtestView::OnMouseWheel(nFlags, zDelta, pt);
}

void CAudchView::OnEditChartdefault() 
{

	if ( GetViewChart())						// does this view have a chart???
	{
		CSubChart *chart = (CSubChart *)GetViewChart();

		CAudtestApp::SetDefaultChart( chart->GetUom(), chart);

	}
	
}

void CAudchView::OnEditUsedefault() 
{

	if ( GetViewChart())						// does this view have a chart???
	{
		CSubChart *chart = (CSubChart *)GetViewChart();

		chart->InheritDefault( CAudtestApp::GetDefaultChart( chart->GetUom()));

		UpdateTarget();
	}
	
}

void CAudchView::OnChartNote() 
{
CSubChart *pchart;
CGrid *pgrid;
CDataTag ctag;

	if ( ! GetViewChart())						// does this view have a chart???
		return;

	pchart = (CSubChart *)GetViewChart();

	ctag.SetParent( pchart);
	pgrid = pchart->GetGrid( ecXCoord);
	ctag.SetValue( pgrid->ConvertLocation(GetMouseDown().x));

	if ( ! ctag.EditProperties( this))			// he said OK
	{
		CString strtext;
		ctag.GetText( strtext);
		if ( ! strtext.IsEmpty())
			pchart->AddNote( ctag);
		InvalidateRect( NULL);
	}
	
}

void CAudchView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	// we want to add processing here for the note window and maybe zoom in/out as well
	
	CAudtestView::OnChar(nChar, nRepCnt, nFlags);
}


void CAudchView::OnDestroy() 
{
	CAudtestView::OnDestroy();
	
	UpdateBaseChart();
	
}

void CAudchView::OnSize(UINT nType, int cx, int cy) 
{

	CAudtestView::OnSize(nType, cx, cy);
	
	if ( GetTracker() && m_pTrackObject)				// we have a tracking rectangle, rebuild it
	{
	CDrawObj *poldtrack = NULL;
	CSubChart *cch;

		poldtrack = m_pTrackObject;
		SetTracker(NULL, NULL);							// turn off the tracker
		cch = (CSubChart *)GetViewChart();
		if ( cch && poldtrack == cch->GetHighlighted())
			SetTracker( setup_Tracker( poldtrack), poldtrack);		// turn it back on
	}

	
}


void CAudtestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	ResetTarget();	
}


// -------------------------------------------------------------
//		GetDlgBar
//			get the window corresponding to a dialogbar
// -------------------------------------------------------------
CDialog * CAudtestView::GetDlgBar( void)
{
CMainFrame *cw = (CMainFrame *)AfxGetMainWnd();	// get mainframe

	if ( cw && cw->IsKindOf(RUNTIME_CLASS( CMainFrame)))
		{
		CDialog *pdlg = cw->GetDialogBar();

			return pdlg;
		}

	ASSERT(0);		// what?
	return NULL;
}
