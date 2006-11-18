// DlgPrfIm.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "zFormEdt.h"
#include "DlgPrfIm.h"

#include "DlgCalWizImp.h"
#include "DlgCalWizBrd.h"

#include "Utils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefImpedance property page

IMPLEMENT_DYNCREATE(CDlgPrefImpedance, CPropertyPage)

CDlgPrefImpedance::CDlgPrefImpedance() : CPropertyPage(CDlgPrefImpedance::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgPrefImpedance)
	//}}AFX_DATA_INIT
}

CDlgPrefImpedance::~CDlgPrefImpedance()
{
}

void CDlgPrefImpedance::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CPropertyPage::OnFinalRelease();
}

void CDlgPrefImpedance::DoDataExchange(CDataExchange* pDX)
{
	m_cResistor.DDX_Value( pDX, m_fResistor);
	m_cSeriesRes.DDX_Value( pDX, m_fSeriesRes);
	m_cInputRes.DDX_Value( pDX, m_fInputRes);
	m_cInputCap.DDX_Value( pDX, m_fInputCap);

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPrefImpedance)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPrefImpedance, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgPrefImpedance)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC1, OnDeltaposGeneric1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC2, OnDeltaposGeneric2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC3, OnDeltaposGeneric3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC4, OnDeltaposGeneric4)
	ON_BN_CLICKED(IDC_TEST, OnTest)
	ON_BN_CLICKED(IDC_TEST2, OnTest2)
	ON_EN_CHANGE(IDC_RESISTOR, OnChangeEntry)
	ON_EN_CHANGE(IDC_SERIESRES, OnChangeEntry)
	ON_EN_CHANGE(IDC_INPUTRES, OnChangeEntry)
	ON_EN_CHANGE(IDC_INPUTCAP, OnChangeEntry)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgPrefImpedance, CPropertyPage)
	//{{AFX_DISPATCH_MAP(CDlgPrefImpedance)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgPrefImpedance to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {57BA63E0-AFDD-11CF-AA03-444553540000}
static const IID IID_IDlgPrefImpedance =
{ 0x57ba63e0, 0xafdd, 0x11cf, { 0xaa, 0x3, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgPrefImpedance, CPropertyPage)
	INTERFACE_PART(CDlgPrefImpedance, IID_IDlgPrefImpedance, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefImpedance message handlers

BOOL CDlgPrefImpedance::OnInitDialog() 
{
	m_cSeriesRes.Subclass( this, IDC_SERIESRES, IDC_GENERIC1);
	m_cResistor.Subclass( this, IDC_RESISTOR, IDC_GENERIC2);
	m_cInputRes.Subclass( this, IDC_INPUTRES, IDC_GENERIC3);
	m_cInputCap.Subclass( this, IDC_INPUTCAP, IDC_GENERIC4);

	CPropertyPage::OnInitDialog();

	if ( ! CAudtestApp::GetCurrentView())			// no current view
		{
		CWnd *pwnd = GetDlgItem( IDC_TEST);			// don't allow testing
		pwnd->EnableWindow( FALSE);
		pwnd = GetDlgItem( IDC_TEST2);
		pwnd->EnableWindow( FALSE);
		}

TESTMSR deftest;

	CAudtestApp::GetMeasures( &deftest);

	m_fResistor = deftest.fResistor;
	m_fSeriesRes = deftest.fSeriesRes;
	m_fInputRes = deftest.fInputRes;
	m_fInputCap = deftest.fInputCap;

	UpdateData( FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPrefImpedance::OnDeltaposGeneric1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cSeriesRes.ProcessDelta( pNMUpDown->iDelta);		// that's it....

	SetModified( TRUE);
	
	*pResult = 0;
}

void CDlgPrefImpedance::OnDeltaposGeneric2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cResistor.ProcessDelta( pNMUpDown->iDelta);		// that's it....

	SetModified( TRUE);
	
	*pResult = 0;
}

void CDlgPrefImpedance::OnDeltaposGeneric3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cInputRes.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	SetModified( TRUE);
	
	*pResult = 0;
}

void CDlgPrefImpedance::OnDeltaposGeneric4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cInputCap.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	SetModified( TRUE);
	
	*pResult = 0;
}

// test for the series resistance and reference resistance
void CDlgPrefImpedance::OnTest() 
{
CDlgCalWizImpedance	cdlg( this);
CView *pview = CAudtestApp::GetCurrentView();

	if ( ! VerboseUpdateData( TRUE))
		return;

	if ( pview )
		{
		HWND hwnd = pview->GetSafeHwnd();
		if ( hwnd && IsWindow( hwnd))
			cdlg.SetView( pview);
		}

	if ( IDCANCEL != cdlg.DoModal())		// must be id_wizfinish
		{
		m_fResistor = cdlg.m_fResistor;
		m_fSeriesRes = cdlg.m_fSeriesRes;
		UpdateData( FALSE);
		SetModified( TRUE);
		}
	
}

// test for sound card input impedance
void CDlgPrefImpedance::OnTest2() 
{
CDlgCalWizBoard	cdlg( this);
CView *pview = CAudtestApp::GetCurrentView();

	if ( ! VerboseUpdateData( TRUE))
		return;

	if ( pview )
		{
		HWND hwnd = pview->GetSafeHwnd();
		if ( hwnd && IsWindow( hwnd))
			cdlg.SetView( pview);
		}

	if ( IDCANCEL != cdlg.DoModal())		// must be id_wizfinish
		{
		m_fInputRes = cdlg.m_fResist;
		m_fInputCap = cdlg.m_fCap;
		UpdateData( FALSE);
		SetModified( TRUE);
		}
	
	
}

BOOL CDlgPrefImpedance::OnApply() 
{
TESTMSR deftest;

	if ( ! VerboseUpdateData( TRUE))
		return 0;

	CAudtestApp::GetMeasures( &deftest);

	deftest.fResistor =  	m_fResistor;
	deftest.fSeriesRes =	m_fSeriesRes;
	deftest.fInputRes =		m_fInputRes;
	deftest.fInputCap =		m_fInputCap;

	CAudtestApp::SetMeasures( &deftest);
	
	return CPropertyPage::OnApply();
}

void CDlgPrefImpedance::OnChangeEntry() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

	SetModified( TRUE);
	
}
