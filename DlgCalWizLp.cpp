// DlgCalWizLp.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "audtedoc.h"
#include "audtevw.h"

#include "Generat.h"
#include "DlgCalWizLp.h"

#include "OpRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_ID	0x123194

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizLoopEnd property page

IMPLEMENT_DYNCREATE(CDlgCalWizLoopEnd, CPropertyPage)

CDlgCalWizLoopEnd::CDlgCalWizLoopEnd() : CPropertyPage(CDlgCalWizLoopEnd::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgCalWizLoopEnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgCalWizLoopEnd::~CDlgCalWizLoopEnd()
{
}

void CDlgCalWizLoopEnd::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CPropertyPage::OnFinalRelease();
}

void CDlgCalWizLoopEnd::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalWizLoopEnd)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalWizLoopEnd, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCalWizLoopEnd)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgCalWizLoopEnd, CPropertyPage)
	//{{AFX_DISPATCH_MAP(CDlgCalWizLoopEnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgCalWizLoopEnd to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {1E22DC44-3519-11D0-AA04-444553540000}
static const IID IID_IDlgCalWizLoopEnd =
{ 0x1e22dc44, 0x3519, 0x11d0, { 0xaa, 0x4, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgCalWizLoopEnd, CPropertyPage)
	INTERFACE_PART(CDlgCalWizLoopEnd, IID_IDlgCalWizLoopEnd, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizLoopEnd message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizLoopBegin property page

IMPLEMENT_DYNCREATE(CDlgCalWizLoopBegin, CPropertyPage)

CDlgCalWizLoopBegin::CDlgCalWizLoopBegin() : CPropertyPage(CDlgCalWizLoopBegin::IDD)
{
	//{{AFX_DATA_INIT(CDlgCalWizLoopBegin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgCalWizLoopBegin::~CDlgCalWizLoopBegin()
{
}

void CDlgCalWizLoopBegin::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalWizLoopBegin)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalWizLoopBegin, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCalWizLoopBegin)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizLoopBegin message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizLoopJig dialog

IMPLEMENT_DYNCREATE(CDlgCalWizLoopJig, CPropertyPage)


CDlgCalWizLoopJig::CDlgCalWizLoopJig()
	: CPropertyPage(CDlgCalWizLoopJig::IDD)
{
	//{{AFX_DATA_INIT(CDlgCalWizLoopJig)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


CDlgCalWizLoopJig::~CDlgCalWizLoopJig()
{
}

void CDlgCalWizLoopJig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalWizLoopJig)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalWizLoopJig, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCalWizLoopJig)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizLoopJig message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizLoop

IMPLEMENT_DYNAMIC(CDlgCalWizLoop, CPropertySheet)

CDlgCalWizLoop::CDlgCalWizLoop(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDS_CALIBRATION, pParentWnd, iSelectPage)
{
	AddPage( &m_dlgBegin);
	AddPage( &m_dlgJig);
	AddPage( &m_dlgEnd);

	SetWizardMode();

}

CDlgCalWizLoop::~CDlgCalWizLoop()
{
}


BEGIN_MESSAGE_MAP(CDlgCalWizLoop, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgCalWizLoop)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizLoop message handlers

LRESULT CDlgCalWizLoopJig::OnWizardNext() 
{
CDlgCalWizLoop *cwnd = (CDlgCalWizLoop *)GetParent();
CAudtestView *pView;			// the parent view
COpCode *cop;
CNamed *pcgen;

	pView = (CAudtestView *)cwnd->GetView();
	pcgen = ((CAudtestDoc *)pView->GetDocument() )->GetDefaultGenerator();
	cop = new COpMsrCalLoop( pcgen, pView);

	pView->SetCurrentOperation( cop);

	if ( cop->QueueAndDo())
		pView->SetCurrentOperation( NULL);		// nope
	
	return CPropertyPage::OnWizardNext();
}

BOOL CDlgCalWizLoopJig::OnSetActive() 
{
	CPropertySheet *cwnd = (CPropertySheet *)GetParent();

	cwnd->SetWizardButtons( PSWIZB_NEXT | PSWIZB_BACK);
	
	return CPropertyPage::OnSetActive();
}

BOOL CDlgCalWizLoopBegin::OnSetActive() 
{
	CPropertySheet *cwnd = (CPropertySheet *)GetParent();

	cwnd->SetWizardButtons( PSWIZB_NEXT | PSWIZB_BACK);
	
	return CPropertyPage::OnSetActive();
}

BOOL CDlgCalWizLoopEnd::OnSetActive() 
{
	CPropertySheet *cwnd = (CPropertySheet *)GetParent();

	cwnd->SetWizardButtons( PSWIZB_DISABLEDFINISH );
	{
	CWnd *pwnd;
	pwnd = cwnd->GetDlgItem( IDCANCEL);
	if ( pwnd)
		{
		pwnd->EnableWindow( FALSE);
		}
	}

	SetTimer( TIMER_ID, 250, NULL);		// 250 milliseconds
	
	return CPropertyPage::OnSetActive();
}

void CDlgCalWizLoopEnd::OnTimer(UINT nIDEvent) 
{
	CPropertySheet *cwnd = (CPropertySheet *)GetParent();

	if ( ! CAudtestApp::GetIsWorking() )
		{
		cwnd->SetWizardButtons( PSWIZB_FINISH );
		KillTimer( nIDEvent);
		}
	
	CPropertyPage::OnTimer(nIDEvent);
}
