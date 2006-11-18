// audtevw.cpp : implementation of the CAudTreeView class
//

#include "stdafx.h"
#include "audtest.h"

#include "audtedoc.h"
#include "vwTree.h"

#include "Utils.h"

#include "opitem.h"
#include "clipbd.h"

// #include "childfrm.h"

#include "generat.h"
#include "dataset.h"

#include "dlgrenam.h"

#include "chart.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudTreeView

IMPLEMENT_DYNCREATE(CAudTreeView, CAudtestView)

BEGIN_MESSAGE_MAP(CAudTreeView, CAudtestView)
	//{{AFX_MSG_MAP(CAudTreeView)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PROPERTIES, OnUpdateEdits)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CAudtestView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CAudtestView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudTreeView construction/destruction


CAudTreeView::CAudTreeView()
{
}

CAudTreeView::~CAudTreeView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CAudTreeView drawing

/////////////////////////////////////////////////////////////////////////////
// CAudTreeView printing

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CAudTreeView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CAudTreeView diagnostics

#ifdef _DEBUG
void CAudTreeView::AssertValid() const
{
	CAudtestView::AssertValid();
}

void CAudTreeView::Dump(CDumpContext& dc) const
{
	CAudtestView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAudTreeView message handlers

void CAudTreeView::OnUpdateEdits(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( TRUE);
}

// define this to cause an entry in the command table, so base class gets called
void CAudTreeView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CAudtestView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


int CAudTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CAudtestView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_cRootView.Create ( IDD_ROOTVIEW, this);
	m_cRootView.EnableWindow( FALSE);
	return 0;
}

void CAudTreeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
CAudtestDoc* pDoc = GetDocument();
DWORD dwl;
int ncount;
CFolder *proot = pDoc->GetRoot();
CFolder *pbase = (CFolder *)GetTargetObject();

	if ( pbase)
		{
		m_cRootView.m_csFileName = pDoc->GetTitle();
		m_cRootView.m_csFolderName = pbase->GetName();
		dwl = pDoc->GetSize();	
			::CommaFormat( m_cRootView.m_csFileSize, (int )dwl);
		dwl = pbase->GetObjectSize(TRUE);
			::CommaFormat( m_cRootView.m_csFolderSize, (int )dwl);
		proot->SetDateStrings( m_cRootView.m_csFileDate, m_cRootView.m_csLastEdit);
		pbase->SetDateStrings( m_cRootView.m_csFolderDate, m_cRootView.m_csFolderLast);
		m_cRootView.m_csComments = pbase->GetDescription();
		ncount = pbase->GetCount( ntDriver);
			m_cRootView.m_csDrivers.Format( "%d", ncount);
		ncount = pbase->GetCount( ntEnclosure);
			m_cRootView.m_csEnclosures.Format( "%d", ncount);
		ncount = pbase->GetCount( ntNetwork);
			m_cRootView.m_csNetworks.Format( "%d", ncount);

		m_cRootView.UpdateData( FALSE);	
		}
	
}

void CAudTreeView::OnInitialUpdate() 
{
	CAudtestView::OnInitialUpdate();

	{
	int cx, cy;
	CRect crect;

		m_cRootView.GetWindowRect( crect);

		cx = crect.Width();
		cy = crect.Height();

		cy += GetSystemMetrics(SM_CYCAPTION);

		GetParent()->SetWindowPos(NULL, 0,0,cx,cy, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER);

		UpdateWindow();
	}
	
}
