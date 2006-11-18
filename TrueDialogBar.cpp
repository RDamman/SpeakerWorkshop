// TrueDialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "TrueDialogBar.h"

#include "MainFrm.h"

#include "dlgLocat.h"
#include "dlgVuMeter.h"

#include "AudTedoc.h"

#include "Clipbd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CzSuperBar

CzSuperBar::CzSuperBar() :  m_CurrentSize(30,30)
{
	m_pFrame = NULL;
}

CzSuperBar::~CzSuperBar()
{
	DestroyWindow();    // avoid PostNcDestroy problems
}


BEGIN_MESSAGE_MAP(CzSuperBar, CControlBar)
	//{{AFX_MSG_MAP(CzSuperBar)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CzSuperBar creation and deletion

// to use a CzSuperBar use classwizard to create a dialogbar
// then change it to a CzSuperBar and add
//		1) Create the Dialog Wnd via    CdlgFoo *cfoo = new CdlgFoo(dialogbar);
//		2) attach it to this via       AttachDialog( cfoo);
//		3) make sure the dialog template has no border and no title

static CString cs_ControlName = "";

BOOL CzSuperBar::Create( CWnd* pParentWnd, UINT nStyle, UINT nID )
{
//	return CControlBar::Create( pParentWnd, CG_IDD_BASE, nStyle, nID);

	ASSERT(pParentWnd != NULL);
	ASSERT_KINDOF(CFrameWnd, pParentWnd);

	m_pFrame = (CFrameWnd *)pParentWnd;

	// save the style
	m_dwStyle = nStyle;
	if ( ! cs_ControlName.GetLength())
		cs_ControlName = AfxRegisterWndClass( 0, NULL, GetSysColorBrush(COLOR_BTNFACE));	// control window

	// create the HWND
	CRect rect;
 	rect.SetRectEmpty();
	if (!CWnd::Create(cs_ControlName, NULL, nStyle, rect, pParentWnd, nID))
		return FALSE;

	// force WS_CLIPSIBLINGS
	ModifyStyle(0, WS_CLIPSIBLINGS);

	// force the size to zero - resizing bar will occur later
	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOZORDER|SWP_NOACTIVATE|SWP_SHOWWINDOW);

	// Note: Parent must resize itself for control bar to be resized

	return TRUE;
}


void	CzSuperBar::RecalcSize()
{					// look in the ctrlbar code in mfc. this sets the size
//	GetFrame()->RecalcLayout();
CWnd *cwframe;

	cwframe = GetParent();
	while( cwframe && ! cwframe->IsKindOf( RUNTIME_CLASS(CFrameWnd)))
		cwframe = cwframe->GetParent();

	if ( cwframe)
		((CFrameWnd *)cwframe)->RecalcLayout();
}

/////////////////////////////////////////////////////////////////////////////
// CzSuperBar message handlers


void CzSuperBar::SetSize( CSize& csNew)
{
	m_CurrentSize = csNew;
	RecalcSize();
}


/////////////////////////////////////////////////////////////////////////////
// CTrueDialogBar

CTrueDialogBar::CTrueDialogBar()
{
	m_pDialog = NULL;
}

CTrueDialogBar::~CTrueDialogBar()
{

}

BEGIN_MESSAGE_MAP(CTrueDialogBar, CzSuperBar)
	//{{AFX_MSG_MAP(CTrueDialogBar)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTrueDialogBar creation and deletion

// to use a cTrueDialogBar use classwizard to create a dialogbar
// then change it to a CTrueDialogBar and add
//		1) Create the Dialog Wnd via    CdlgFoo *cfoo = new CdlgFoo(dialogbar);
//		2) attach it to this via       AttachDialog( cfoo);
//		3) make sure the dialog template has no border and no title

BOOL CTrueDialogBar::Create( CWnd* pParentWnd, UINT nStyle, UINT nID )
{

	return CzSuperBar::Create( pParentWnd, nStyle, nID);
}


void CTrueDialogBar::OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler )
{
	// update the dialog controls added to the status bar
	UpdateDialogControls(pTarget, bDisableIfNoHndler);

//	((CMainFrame *)pTarget)->OnUpdateViewTree( NULL);	// boy is this a kludge!!!!

}


void	CTrueDialogBar::AttachDialog( CDialog *pDialog)
{
	m_pDialog = pDialog;
	RecalcSize();

}

CSize CTrueDialogBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
CRect rc;

	if ( ! m_pDialog)
		return CSize(1,1);

	m_pDialog->GetWindowRect( &rc);
	CSize csize( 9+rc.Width(), 9+rc.Height());
	return csize;
//	return CControlBar::CalcDynamicLayout( nLength, nMode);
}


CSize CTrueDialogBar::CalcDynamicLayout(int nLength, DWORD nMode)
{
CRect rc;

	if ( ! m_pDialog)
		return CSize(1,1);

	m_pDialog->GetWindowRect( &rc);
	CSize csize( 9+rc.Width(), 9+rc.Height());
	return csize;
//	return CControlBar::CalcDynamicLayout( nLength, nMode);
}


/////////////////////////////////////////////////////////////////////////////
// CTrueDialogBar message handlers


void CTrueDialogBar::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CzSuperBar::OnShowWindow(bShow, nStatus);
	
	if ( m_pDialog)
		m_pDialog->ShowWindow( bShow ? SW_SHOW : SW_HIDE);
}


// =========================================================================================
//				CTreeBar
// =========================================================================================

CTreeBar::CTreeBar() : m_cSplitter()
{

}

CTreeBar::~CTreeBar()
{

}


BEGIN_MESSAGE_MAP(CTreeBar, CzSuperBar)
	//{{AFX_MSG_MAP(CTreeBar)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTreeBar creation and deletion

typedef struct tagTREEINFO
	{
	CSize csCurrent;
	BOOL	bIsFloat;
	BOOL	bIsLeft;
	} TREEINFO;


BOOL CTreeBar::Create( CWnd* pParentWnd, UINT nStyle, UINT nID )
{

	CzSuperBar::Create( pParentWnd, nStyle, nID);

	EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);

	return TRUE;
}


int CTreeBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CzSuperBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
static DWORD dw_size = 0;
char szname[100];
RECT rcout;

	sprintf(szname, "zSplit%d", dw_size++);
	rcout.left = rcout.top = 0;
	rcout.right = rcout.bottom = 10;		// random and irrelevant

	m_cSplitter.Create(this, rcout, 12);
	if (m_cTree.Create( rcout, this,  0x103))
		{
		m_cTree.SetFilter(ntAny, uomAny);
		m_cTree.RebuildTree( NULL, 0);
		m_cTree.SetNotifyWnd( GetFrame());		// set up the notification
		}
					// read the parms from the registry
	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	TREEINFO tinf;
					// ignore floating and left/right for now
		if ( capp->ReadRegistry( IDS_TREEINFO, &tinf, sizeof( tinf) ))
			{			// failed to read the starting treeinfo
			tinf.csCurrent.cx = 250;
			tinf.csCurrent.cy = 100;
			}
		SetSize( tinf.csCurrent);
	}

	return 0;
}

void CTreeBar::OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler )
{
			// update the dialog controls added to the status bar
CFrameWnd *cframe = GetFrame();
CFrameWnd *cactive;
CDocument *pdoc = NULL;
CFolder *proot = NULL;


	ASSERT_KINDOF( CFrameWnd, cframe);		// cframe better be a framewnd

	cactive = cframe->GetActiveFrame();						// and the active frame
	if ( cactive)						// if we have a frame, burrow down
		{
		pdoc = cactive->GetActiveDocument();
		if ( pdoc)
			{
			if ( ! IsFloating())
				{
				CString cs;
					cs.LoadString( IDS_PROJTREE);
				SetWindowText( (LPCTSTR )cs);
				}
			proot = ((CAudtestDoc *)pdoc)->GetRoot();
			}
		}

	if ( (!proot) || proot != m_cTree.m_pcRoot )	// works even with no document
		UpdateTree( pdoc, 0, NULL);				// reset the tree

				// check to see if the window has moved
				// if so, reshape the inner components
	{
	CRect rcw;
		GetWindowRect( rcw);
		if ( rcWindow != rcw)
			{
			rcWindow = rcw;
			Reshape();
			}
	}

}

void CTreeBar::Reshape(  )
{
int csp = m_cSplitter.GetWidth();
CRect rc;


	if ( IsWindowVisible() )
		{
		if ( IsFloating())
			{
			m_cSplitter.ShowWindow( SW_HIDE);
			}
		else
			{
			GetClientRect( rc);
			if ( CBRS_ALIGN_LEFT == (CBRS_ALIGN_LEFT & GetBarStyle()))
				{
				m_cSplitter.SetWindowPos(NULL, rc.right - csp, rc.top, csp, rc.Height(), SWP_NOZORDER | SWP_SHOWWINDOW);
				}
			else
				{
				m_cSplitter.SetWindowPos(NULL, rc.left, rc.top, 
							csp, rc.Height(), SWP_NOZORDER | SWP_SHOWWINDOW);
				}
			}
		CalculateClient( rc);
		m_cTree.SetWindowPos(NULL, rc.left, rc.top, 
					rc.Width(), rc.Height(), SWP_NOZORDER | SWP_SHOWWINDOW);
		}
}

CSize CTreeBar::CalcDynamicLayout(int nLength, DWORD nMode)
{
CRect rc;

	if ( nMode & LM_HORZDOCK)		// horizontally docked size
		{
		return CSize( 10,10);		// won't happen
		}
	else if ( nMode & LM_VERTDOCK)	// vertically docked size
		{
		RECT rc;
		CWnd *pparent = GetParent();
		pparent->GetClientRect( &rc);
		return CSize( m_CurrentSize.cx, rc.bottom - rc.top);
		}

	if ( nMode & LM_COMMIT)			// save the settings
		{
		if ( !(nMode & LM_MRUWIDTH))
			{
			if ( nMode & LM_LENGTHY)
				m_CurrentSize.cy = max(10,nLength);
			else
				m_CurrentSize.cx = max(10,nLength);
			}
		}

	if ( ! (nMode & LM_MRUWIDTH))		// user is resizing the window
		{
		if ( nMode & LM_LENGTHY)		// length or width?
			{
			m_CurrentSize.cy = max(10,nLength);
			}
		else 
			m_CurrentSize.cx = max(10,nLength);
		}

	return m_CurrentSize;				// accept it
}


void CTreeBar::UpdateTree( CDocument *pDoc, LPARAM lHint, CObject* pHint)
{
CFolder *proot;

	if ( pDoc)
		proot = ((CAudtestDoc *)pDoc)->GetRoot();			// get the root
	else
		proot = NULL;
	m_cTree.RebuildTree( proot, 0, lHint, pHint);

//	RecalcLayout();
}

BOOL	CTreeBar::HasFocus( void )
{
	return m_cTree.HasFocus();
}

CNamed *CTreeBar::GetCurrentSelection()
{
	return m_cTree.GetNextItem( NULL, TVGN_CARET);
}



// =========================================================================================
//				CLocationBar
// =========================================================================================
CLocationBar::CLocationBar()
{
	m_bHasText = false;
}

CLocationBar::~CLocationBar()
{

}


BEGIN_MESSAGE_MAP(CLocationBar, CTrueDialogBar)
	//{{AFX_MSG_MAP(CLocationBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTreeBar creation and deletion

BOOL CLocationBar::Create( CWnd* pParentWnd, UINT nStyle, UINT nID )
{

	CTrueDialogBar::Create( pParentWnd, nStyle, nID);

	AttachDialog( new CDlgLocations( this));
				// if you do this prior to create it GPFaults
	EnableDocking(CBRS_ALIGN_BOTTOM | CBRS_ALIGN_TOP);

	return TRUE;
}


void CLocationBar::OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler )
{
	if ( IsFloating())
	{
		if( ! m_bHasText)
		{
		CString cs;
			GetWindowText( cs);
			if ( ! cs.GetLength())
				{
				cs.LoadString( IDS_LOCATIONTOP);
				SetWindowText( (LPCTSTR )cs);
				m_bHasText = true;
				}
		}
	}
	else if ( m_bHasText)
		m_bHasText = false;

	CTrueDialogBar::OnUpdateCmdUI( pTarget, bDisableIfNoHndler);
}

void CTreeBar::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	lpMMI->ptMinTrackSize.x = 25;
	lpMMI->ptMinTrackSize.y = 25;

	CzSuperBar::OnGetMinMaxInfo(lpMMI);
}

void CTreeBar::OnDestroy() 
{
	CzSuperBar::OnDestroy();
	
	// TODO: Add your message handler code here
					// read the parms from the registry
	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	TREEINFO tinf;

		tinf.csCurrent = GetSize();
		tinf.bIsFloat = IsFloating();
		tinf.bIsLeft = TRUE;
		capp->WriteRegistry( IDS_TREEINFO, &tinf, sizeof( tinf));
	}
	
}

BOOL CTreeBar::WantCommand(UINT uID)
{
	return m_cTree.WantCommand( uID);
}

BOOL CTreeBar::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ( m_cTree.WantCommand( LOWORD( wParam)) )
		{
		m_cTree.PostMessage( WM_COMMAND, wParam, lParam);
			return TRUE;	// we've handled it
		}
	return CzSuperBar::OnCommand(wParam, lParam);
}


// draw a 3d box from nX,nY to nXf,nYf
void CTreeBar::Draw3dBox( CPaintDC& cDC, int nX, int nY, int nXf, int nYf)
{

	cDC.SelectStockObject( WHITE_BRUSH); 
	cDC.PatBlt( nX,   nY,   1+nXf-nX, 3, PATCOPY);
	cDC.SelectStockObject( LTGRAY_BRUSH); 
	cDC.PatBlt( nX+1, nY+1, nXf-nX-1, 1, PATCOPY);
	cDC.SelectStockObject( DKGRAY_BRUSH); 
	cDC.PatBlt( nX,   nY+2, 1+nXf-nX, 1, PATCOPY);

}


void CTreeBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// draw the frame
	if ( ! IsFloating())
		{
		RECT rc;

			GetClientRect( &rc);
			Draw3dBox( dc, rc.left, rc.top+2, rc.right, rc.top+4);
			Draw3dBox( dc, rc.left, rc.top+6, rc.right, rc.top+8);
			
		}
	// Do not call CzSuperBar::OnPaint() for painting messages
}

void CTreeBar::CalculateClient(CRect &crDest)
{
CRect rc;

	GetClientRect( rc);

	if ( IsWindowVisible() )
		{
		if ( IsFloating())
			{
			crDest.left = rc.left + 3;
			crDest.top = rc.top + 3;
			crDest.right = rc.right - 6;
			crDest.bottom = rc.bottom - 6;
			}
		else
			{
			crDest.top = rc.top + 12;
			crDest.bottom = rc.bottom - 6;
			if ( CBRS_ALIGN_LEFT == (CBRS_ALIGN_LEFT & GetBarStyle()))
				{
				crDest.left = rc.left + 3;
				crDest.right = rc.right - m_cSplitter.GetWidth() - 3;
;
				}
			else
				{
				crDest.left = rc.left + 3 + m_cSplitter.GetWidth();
				crDest.right = rc.right - 3;
				}
			}
		}
}

void CTreeBar::OnSize(UINT nType, int cx, int cy) 
{

	Reshape();

	CzSuperBar::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

// this passes Enter and Escape to the edit control if we're editing a label
// per ms knowledge base
BOOL CTreeBar::PreTranslateMessage(MSG* pMsg) 
{

      // If edit control is visible in tree view control, sending a
      // WM_KEYDOWN message to the edit control will dismiss the edit
      // control.  When ENTER key was sent to the edit control, the parent
      // window of the tree view control is responsible for updating the
      // item's label in TVN_ENDLABELEDIT notification code.
      if (pMsg->message == WM_KEYDOWN &&
         pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
      {
         CEdit* edit = m_cTree.m_cTree.GetEditControl();
         if (edit)
         {
            edit->SendMessage(WM_KEYDOWN, pMsg->wParam, pMsg->lParam);
            return TRUE;
         }
	  }
	return CzSuperBar::PreTranslateMessage(pMsg);
}

// ----------------------

// =========================================================================================
//				CVuMeterBar
// =========================================================================================
CVuMeterBar::CVuMeterBar()
{
	m_bHasText = false;
}

CVuMeterBar::~CVuMeterBar()
{

}


BEGIN_MESSAGE_MAP(CVuMeterBar, CTrueDialogBar)
	//{{AFX_MSG_MAP(CVuMeterBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTreeBar creation and deletion

BOOL CVuMeterBar::Create( CWnd* pParentWnd, UINT nStyle, UINT nID )
{

	CTrueDialogBar::Create( pParentWnd, nStyle, nID);

	AttachDialog( new CDlgVuMeter( this));
				// if you do this prior to create it GPFaults
	EnableDocking(CBRS_ALIGN_BOTTOM | CBRS_ALIGN_TOP);

	return TRUE;
}

void CVuMeterBar::OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler )
{

	if ( IsFloating())
	{
		if( ! m_bHasText)
		{
		CString cs;
			GetWindowText( cs);
			if ( ! cs.GetLength())
				{
				cs.LoadString( IDS_VUMETERTOP);
				SetWindowText( (LPCTSTR )cs);
				m_bHasText = true;
				}
		}
	}
	else if ( m_bHasText)
		m_bHasText = false;

	CTrueDialogBar::OnUpdateCmdUI( pTarget, bDisableIfNoHndler);
}



void CVuMeterBar::SetLeftEntries( float fMax, float fAve, float fMin)
{
	CDlgVuMeter *pmeter = (CDlgVuMeter *)GetTrueDialog();
	if ( pmeter)
		pmeter->SetLeftEntries( fMax, fAve, fMin);
}

void CVuMeterBar::SetRightEntries( float fMax, float fAve, float fMin)
{
	CDlgVuMeter *pmeter = (CDlgVuMeter *)GetTrueDialog();
	if ( pmeter)
		pmeter->SetRightEntries( fMax, fAve, fMin);
}


void CVuMeterBar::GetLeftEntries( float &fMax, float &fAve, float &fMin)
{
	CDlgVuMeter *pmeter = (CDlgVuMeter *)GetTrueDialog();
	if ( pmeter)
		pmeter->GetLeftEntries( fMax, fAve, fMin);

}

void CVuMeterBar::GetRightEntries( float &fMax, float &fAve, float &fMin)
{
	CDlgVuMeter *pmeter = (CDlgVuMeter *)GetTrueDialog();
	if ( pmeter)
		pmeter->GetRightEntries( fMax, fAve, fMin);

}

