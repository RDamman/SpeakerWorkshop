// DlgCalWizVol.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "audtedoc.h"
#include "audtevw.h"

#include "Generat.h"
#include "DlgCalWizVol.h"

#include "OpRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define TIMER_ID	0x123196

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizVol

IMPLEMENT_DYNAMIC(CDlgCalWizVol, CPropertySheet)

CDlgCalWizVol::CDlgCalWizVol(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDS_CALIBRATION, pParentWnd, iSelectPage)
{
	AddPage( &m_dlgBegin);
	AddPage( &m_dlgEnd);

	SetWizardMode();

	m_dwReferID = 0;		// set to nobody
}

CDlgCalWizVol::~CDlgCalWizVol()
{
}


BEGIN_MESSAGE_MAP(CDlgCalWizVol, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgCalWizVol)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizVol message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizVolBegin property page

IMPLEMENT_DYNCREATE(CDlgCalWizVolBegin, CPropertyPage)

CDlgCalWizVolBegin::CDlgCalWizVolBegin() : CPropertyPage(CDlgCalWizVolBegin::IDD)
{
	//{{AFX_DATA_INIT(CDlgCalWizVolBegin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgCalWizVolBegin::~CDlgCalWizVolBegin()
{
}

void CDlgCalWizVolBegin::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalWizVolBegin)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalWizVolBegin, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCalWizVolBegin)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizVolBegin message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizVolEnd dialog

IMPLEMENT_DYNCREATE(CDlgCalWizVolEnd, CPropertyPage)

CDlgCalWizVolEnd::CDlgCalWizVolEnd() : CPropertyPage(CDlgCalWizVolEnd::IDD)
{
	//{{AFX_DATA_INIT(CDlgCalWizVolEnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgCalWizVolEnd::~CDlgCalWizVolEnd()
{
}


void CDlgCalWizVolEnd::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalWizVolEnd)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalWizVolEnd, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCalWizVolEnd)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizVolEnd message handlers

BOOL CDlgCalWizVolBegin::OnSetActive() 
{
	CPropertySheet *cwnd = (CPropertySheet *)GetParent();

	cwnd->SetWizardButtons( PSWIZB_NEXT | PSWIZB_BACK);
	
	return CPropertyPage::OnSetActive();
}

BOOL CDlgCalWizVolEnd::OnSetActive() 
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

void CDlgCalWizVolEnd::OnTimer(UINT nIDEvent) 
{
CDlgCalWizVol *cwnd = (CDlgCalWizVol *)GetParent();
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

LRESULT CDlgCalWizVolBegin::OnWizardNext() 
{
CDlgCalWizVol *cwnd = (CDlgCalWizVol *)GetParent();
CAudtestView *pView;			// the parent view
COpCode *cop;
CNamed *pcgen;

// we can have up to 3 volumes to set
//		output volume
//		wave out volume
//		wave input volume

// query the mixer to see which volumes we can adjust?
// then adjust output volume until clipping, back off
// then adjust input volume to be the right amplitude, back off

	pView = (CAudtestView *)cwnd->GetView();
	pcgen = ((CAudtestDoc *)pView->GetDocument() )->GetDefaultGenerator();
	cop = new COpMsrTime( pcgen, pView);

	pView->SetCurrentOperation( cop);

	if ( cop->QueueAndDo())						// failed
		pView->SetCurrentOperation( NULL);		// reset
	
	return CPropertyPage::OnWizardNext();
}

