//////////////////////////////////////////////////////////////////////////////
// DlgCalWizBrd.cpp : implementation file
//
//	This does the input impedance portion of the Jig Test
// to find the input impedance of a sound card
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "audtest.h"

#include "audtedoc.h"
#include "audtevw.h"

#include "Generat.h"

#include "zFormEdt.h"
#include "DlgCalWizBrd.h"

#include "OpRecord.h"
#include "Utils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_ID	0x123196


static void enable_Cancel( CPropertySheet *pSheet, BOOL bEnable)
{
	{
	CWnd *pwnd;
	pwnd = pSheet->GetDlgItem( IDCANCEL);
	if ( pwnd)
		{
		pwnd->EnableWindow( bEnable);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizBrdBegin property page

IMPLEMENT_DYNCREATE(CDlgCalWizBrdBegin, CPropertyPage)

CDlgCalWizBrdBegin::CDlgCalWizBrdBegin() : CPropertyPage(CDlgCalWizBrdBegin::IDD)
{
	//{{AFX_DATA_INIT(CDlgCalWizBrdBegin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgCalWizBrdBegin::~CDlgCalWizBrdBegin()
{
}

void CDlgCalWizBrdBegin::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalWizBrdBegin)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalWizBrdBegin, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCalWizBrdBegin)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizBrdBegin message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizBrdEnd property page

IMPLEMENT_DYNCREATE(CDlgCalWizBrdEnd, CPropertyPage)

CDlgCalWizBrdEnd::CDlgCalWizBrdEnd() : CPropertyPage(CDlgCalWizBrdEnd::IDD)
{
	//{{AFX_DATA_INIT(CDlgCalWizBrdEnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgCalWizBrdEnd::~CDlgCalWizBrdEnd()
{
}

void CDlgCalWizBrdEnd::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalWizBrdEnd)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalWizBrdEnd, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCalWizBrdEnd)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizBrdEnd message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizBrdJig property page

IMPLEMENT_DYNCREATE(CDlgCalWizBrdJig, CPropertyPage)

CDlgCalWizBrdJig::CDlgCalWizBrdJig() : CPropertyPage(CDlgCalWizBrdJig::IDD), m_cfEdits()
{
	//{{AFX_DATA_INIT(CDlgCalWizBrdJig)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgCalWizBrdJig::~CDlgCalWizBrdJig()
{
}

void CDlgCalWizBrdJig::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgCalWizBrdJig)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalWizBrdJig, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCalWizBrdJig)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizBrdJig message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizBoard

IMPLEMENT_DYNAMIC(CDlgCalWizBoard, CPropertySheet)

CDlgCalWizBoard::CDlgCalWizBoard(CWnd* pParentWnd, UINT iSelectPage)
	: CPropertySheet(IDS_CALIBRATION, pParentWnd, iSelectPage)
{
	AddPage( &m_dlgBegin);
	AddPage( &m_dlgJig);
	AddPage( &m_dlgEnd);

	SetWizardMode();

	CAudtestApp::GetMeasures( &m_tTest);	// save early values

}

CDlgCalWizBoard::~CDlgCalWizBoard()
{
}


BEGIN_MESSAGE_MAP(CDlgCalWizBoard, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgCalWizBoard)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizBoard message handlers

BOOL CDlgCalWizBrdJig::OnInitDialog() 
{
	
		{		// initialize the spinner format group
		FormatGroup cfdata[2] = { 
							{IDC_RESIST,	IDC_SPIN1, 0.0f, 1000.0f, &m_fResistor},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);

		}
	
	CPropertyPage::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgCalWizBrdBegin::OnSetActive() 
{
CPropertySheet *cwnd = (CPropertySheet *)GetParent();

	cwnd->SetWizardButtons( PSWIZB_NEXT);
	
	return CPropertyPage::OnSetActive();
}

BOOL CDlgCalWizBrdJig::OnSetActive() 
{
CPropertySheet *cwnd = (CPropertySheet *)GetParent();

	cwnd->SetWizardButtons( PSWIZB_NEXT | PSWIZB_BACK);
	
	return CPropertyPage::OnSetActive();
}

BOOL CDlgCalWizBrdEnd::OnSetActive() 
{
CPropertySheet *cwnd = (CPropertySheet *)GetParent();

	cwnd->SetWizardButtons( PSWIZB_DISABLEDFINISH);
	enable_Cancel( cwnd, FALSE);

	SetTimer( TIMER_ID, 250, NULL);		// 250 milliseconds
	
	return CPropertyPage::OnSetActive();
}

void CDlgCalWizBrdEnd::OnTimer(UINT nIDEvent) 
{
CDlgCalWizBoard *cwnd = (CDlgCalWizBoard *)GetParent();
TESTMSR deftest;

	if ( ! CAudtestApp::GetIsWorking() )
		{
		cwnd->SetWizardButtons( PSWIZB_FINISH | PSWIZB_BACK);
		enable_Cancel( cwnd, TRUE);
		KillTimer( nIDEvent);
					// the timer is done, store the saved value
		CAudtestApp::GetMeasures( &deftest);	// get the new values

		cwnd->m_fResist = deftest.fInputRes;
		cwnd->m_fCap    = deftest.fInputCap;

		CString csout;				// format the values to the screen

		::FullFormatValue( csout, deftest.fInputRes, 2);
		CWnd *pwnd = GetDlgItem( IDC_RESISTOR);
		if ( pwnd)
			pwnd->SetWindowText( csout);
		::FullFormatValue( csout, deftest.fInputCap, 2);
		pwnd = GetDlgItem( IDC_CAPACITOR);
		if ( pwnd)
			pwnd->SetWindowText( csout);

		CAudtestApp::SetMeasures( &cwnd->m_tTest);	// put the original values back
		}
	
	CPropertyPage::OnTimer(nIDEvent);
}

void CDlgCalWizBrdJig::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------


LRESULT CDlgCalWizBrdJig::OnWizardNext() 
{
CDlgCalWizBoard *cwnd = (CDlgCalWizBoard *)GetParent();
CAudtestView *pView;			// the parent view
COpCode *cop;
CNamed *pcgen;

	if ( ! VerboseUpdateData ( TRUE))			// get m_fresist
		return -1;

	cwnd->m_fReference = m_fResistor;

	{
	TESTMSR deftest;
		CAudtestApp::GetMeasures( &deftest);	// get the new values
		deftest.fResistor = m_fResistor;		// set fresistor
		deftest.fSeriesRes = 0.2f;				// good approximation
		CAudtestApp::SetMeasures( &deftest);
	}

	pView = (CAudtestView *)cwnd->GetView();
	pcgen = ((CAudtestDoc *)pView->GetDocument() )->GetDefaultGenerator();
	cop = new COpMsrBrdJig( pcgen, pView);

	pView->SetCurrentOperation( cop);

	if ( cop->QueueAndDo())
		pView->SetCurrentOperation( NULL);		// nope
	
	return CPropertyPage::OnWizardNext();
}
