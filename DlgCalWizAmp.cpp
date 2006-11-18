// DlgCalWizAmp.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "audtedoc.h"
#include "audtevw.h"

#include "Generat.h"
#include "DlgCalWizAmp.h"

#include "OpRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define TIMER_ID	0x123196

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizAmp

IMPLEMENT_DYNAMIC(CDlgCalWizAmp, CPropertySheet)

CDlgCalWizAmp::CDlgCalWizAmp(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDS_CALIBRATION, pParentWnd, iSelectPage)
{
	AddPage( &m_dlgBegin);
	AddPage( &m_dlgEnd);

	SetWizardMode();

	m_dwReferID = 0;		// set to nobody
}

CDlgCalWizAmp::~CDlgCalWizAmp()
{
}


BEGIN_MESSAGE_MAP(CDlgCalWizAmp, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgCalWizAmp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizAmp message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizAmpBegin property page

IMPLEMENT_DYNCREATE(CDlgCalWizAmpBegin, CPropertyPage)

CDlgCalWizAmpBegin::CDlgCalWizAmpBegin() : CPropertyPage(CDlgCalWizAmpBegin::IDD)
{
	//{{AFX_DATA_INIT(CDlgCalWizAmpBegin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgCalWizAmpBegin::~CDlgCalWizAmpBegin()
{
}

void CDlgCalWizAmpBegin::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalWizAmpBegin)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalWizAmpBegin, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCalWizAmpBegin)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizAmpBegin message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizAmpEnd dialog

IMPLEMENT_DYNCREATE(CDlgCalWizAmpEnd, CPropertyPage)

CDlgCalWizAmpEnd::CDlgCalWizAmpEnd() : CPropertyPage(CDlgCalWizAmpEnd::IDD)
{
	//{{AFX_DATA_INIT(CDlgCalWizAmpEnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgCalWizAmpEnd::~CDlgCalWizAmpEnd()
{
}


void CDlgCalWizAmpEnd::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalWizAmpEnd)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalWizAmpEnd, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCalWizAmpEnd)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizAmpEnd message handlers

BOOL CDlgCalWizAmpBegin::OnSetActive() 
{
	CPropertySheet *cwnd = (CPropertySheet *)GetParent();

	cwnd->SetWizardButtons( PSWIZB_NEXT | PSWIZB_BACK);
	
	return CPropertyPage::OnSetActive();
}

BOOL CDlgCalWizAmpEnd::OnSetActive() 
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

void CDlgCalWizAmpEnd::OnTimer(UINT nIDEvent) 
{
CDlgCalWizAmp *cwnd = (CDlgCalWizAmp *)GetParent();
CAudtestView *pView;			// the parent view

	if ( ! CAudtestApp::GetIsWorking() )
		{
		CNamed *pcgen;
		CNamed *pcout = NULL;

		KillTimer( nIDEvent);

		pView = (CAudtestView *)cwnd->GetView();
		pcgen = ((CAudtestDoc *)pView->GetDocument() )->GetDefaultGenerator();
		if ( pcgen)
			pcout = pcgen->FindByName( pcgen->GetName() + ".Pulse");

		cwnd->SetWizardButtons( PSWIZB_FINISH );
		if ( pcout)
			cwnd->m_dwReferID = pcout->GetID();		// set it to something or other....
		}
	
	CPropertyPage::OnTimer(nIDEvent);
}

LRESULT CDlgCalWizAmpBegin::OnWizardNext() 
{
CDlgCalWizAmp *cwnd = (CDlgCalWizAmp *)GetParent();
CAudtestView *pView;			// the parent view
COpCode *cop;
CNamed *pcgen;

	pView = (CAudtestView *)cwnd->GetView();
	pcgen = ((CAudtestDoc *)pView->GetDocument() )->GetDefaultGenerator();
	cop = new COpMsrTime( pcgen, pView);

	pView->SetCurrentOperation( cop);

	if ( cop->QueueAndDo())						// failed
		pView->SetCurrentOperation( NULL);		// reset
	
	return CPropertyPage::OnWizardNext();
}
