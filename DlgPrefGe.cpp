// DlgPrefGe.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "fxFont.h"
#include "DlgPrefGe.h"

#include "Utils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefGeneral property page

IMPLEMENT_DYNCREATE(CDlgPrefGeneral, CPropertyPage)

CDlgPrefGeneral::CDlgPrefGeneral() : CPropertyPage(CDlgPrefGeneral::IDD), m_cfEdits()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgPrefGeneral)
	m_nUnits = -1;
	m_bSingleClick = FALSE;
	m_bUseLast = FALSE;
	m_bLongStatus = FALSE;
	m_csSummaryName = _T("");
	m_bEnable48K = FALSE;
	m_iTrails = 0;
	m_iAllowedLocale = 0;
	m_bAutoSave = FALSE;
	m_iSaveTime = 0;
	m_bEnable96K = FALSE;
	//}}AFX_DATA_INIT

	m_fRightShift = 0.0f;
}

CDlgPrefGeneral::~CDlgPrefGeneral()
{
}

void CDlgPrefGeneral::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CPropertyPage::OnFinalRelease();
}

void CDlgPrefGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	if ( ! pDX->m_bSaveAndValidate)	// update the display
		{
		m_SummaryFont.GetPrettyName(m_csSummaryName);
		}

	//{{AFX_DATA_MAP(CDlgPrefGeneral)
	DDX_CBIndex(pDX, IDC_UNITS, m_nUnits);
	DDX_Check(pDX, IDC_SINGLECLICK, m_bSingleClick);
	DDX_Check(pDX, IDC_USELAST, m_bUseLast);
	DDX_Check(pDX, IDC_LONGSTATUS, m_bLongStatus);
	DDX_Text(pDX, IDC_SUMMARYFONT, m_csSummaryName);
	DDX_Check(pDX, IDC_ENABLE48K, m_bEnable48K);
	DDX_Text(pDX, IDC_TRAILS, m_iTrails);
	DDX_Text(pDX, IDC_ALLOWEDLOCALE, m_iAllowedLocale);
	DDX_Check(pDX, IDC_AUTOSAVE, m_bAutoSave);
	DDX_Text(pDX, IDC_SAVETIME, m_iSaveTime);
	DDX_Check(pDX, IDC_ENABLE96K, m_bEnable96K);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPrefGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgPrefGeneral)
	ON_BN_CLICKED(IDC_USELAST, OnUselast)
	ON_BN_CLICKED(IDC_SINGLECLICK, OnSingleclick)
	ON_CBN_SELCHANGE(IDC_UNITS, OnSelchangeUnits)
	ON_BN_CLICKED(IDC_LONGSTATUS, OnLongstatus)
	ON_BN_CLICKED(IDC_PICKFNT, OnPickfnt)
	ON_EN_CHANGE(IDC_TRAILS, OnChangeTrails)
	ON_EN_CHANGE(IDC_ALLOWEDLOCALE, OnChangeAllowedlocale)
	ON_BN_CLICKED(IDC_AUTOSAVE, OnAutosave)
	ON_EN_CHANGE(IDC_SAVETIME, OnChangeSavetime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, OnDeltaposSpin4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgPrefGeneral, CPropertyPage)
	//{{AFX_DISPATCH_MAP(CDlgPrefGeneral)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgPrefGeneral to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {013D3B80-3171-11D0-AA04-444553540000}
static const IID IID_IDlgPrefGeneral =
{ 0x13d3b80, 0x3171, 0x11d0, { 0xaa, 0x4, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgPrefGeneral, CPropertyPage)
	INTERFACE_PART(CDlgPrefGeneral, IID_IDlgPrefGeneral, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
//		Methods
/////////////////////////////////////////////////////////////////////////////


void CDlgPrefGeneral::EnableSave()
{
bool benable;
CWnd *pwnd;

	benable = IsDlgButtonChecked( IDC_AUTOSAVE) ? true : false;
	pwnd = GetDlgItem( IDC_SAVETIME);
	if ( pwnd && pwnd->GetSafeHwnd())
		pwnd->EnableWindow( benable);		// enable/disable based on checkmark

}


/////////////////////////////////////////////////////////////////////////////
// CDlgPrefGeneral message handlers
/////////////////////////////////////////////////////////////////////////////

BOOL CDlgPrefGeneral::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[2] = { 
							{IDC_RIGHTSHIFT,	IDC_SPIN4, -1000.0f, 1000.0f, &m_fRightShift},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CPropertyPage::OnInitDialog();

	::ComboFillString( this, IDC_UNITS, IDS_PREFG_UNITS);
	
	m_nUnits = (CAudtestApp::GetIsMetric() ? 1 : 0);
	m_bSingleClick = (CAudtestApp::GetSingleClick() ? 1 : 0);
	m_bUseLast = (CAudtestApp::GetUseLast() ? 1 : 0);
	m_bLongStatus = (CAudtestApp::GetLongStatus() ? 1 : 0);
	m_fRightShift = (CAudtestApp::GetRightShift());
	m_SummaryFont = CAudtestApp::GetAppFont( ftStatus);
	m_bEnable48K = CAudtestApp::GetDisable48K() ? FALSE : TRUE;
	m_bEnable96K = CAudtestApp::GetDisable96K() ? FALSE : TRUE;
	m_iTrails = CAudtestApp::GetTrails();
	m_iAllowedLocale = CAudtestApp::GetAllowedLocale();
	m_bAutoSave = CAudtestApp::GetAutoSave();
	m_iSaveTime = CAudtestApp::GetAutoSaveTime();

	{
	CSpinButtonCtrl *pbutton;
	pbutton = (CSpinButtonCtrl *)GetDlgItem( IDC_SPIN2);
	if ( pbutton && pbutton->GetSafeHwnd())
		pbutton->SetRange(0,8);
	pbutton = (CSpinButtonCtrl *)GetDlgItem( IDC_SPIN1);
	if ( pbutton && pbutton->GetSafeHwnd())
		pbutton->SetRange(0,10000);
	pbutton = (CSpinButtonCtrl *)GetDlgItem( IDC_SPIN3);
	if ( pbutton && pbutton->GetSafeHwnd())
		pbutton->SetRange(0,100);
	}
	UpdateData( FALSE);

	EnableSave();		// enable or disable the autosave time button based on check
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgPrefGeneral::OnApply() 
{
	if ( ! VerboseUpdateData( TRUE))	// get current data
		return 0;

	CAudtestApp::SetIsMetric( m_nUnits == 1);
	CAudtestApp::SetSingleClick( m_bSingleClick);
	CAudtestApp::SetUseLast( m_bUseLast);
	CAudtestApp::SetLongStatus( m_bLongStatus);
	CAudtestApp::SetRightShift( m_fRightShift);
	CAudtestApp::GetAppFont( ftStatus) = m_SummaryFont;
	CAudtestApp::GetAppFont(ftStatus).WriteIni( ftStatus);
	CAudtestApp::SetDisable48K( m_bEnable48K ? false : true);
	CAudtestApp::SetDisable96K( m_bEnable96K ? false : true);
	CAudtestApp::SetTrails( m_iTrails);
	CAudtestApp::SetAllowedLocale( m_iAllowedLocale);
	CAudtestApp::SetAutoSave(m_bAutoSave);
	CAudtestApp::SetAutoSaveTime(m_iSaveTime);

	SetModified( FALSE);
	
	return CPropertyPage::OnApply();
}


void CDlgPrefGeneral::OnUselast() 
{
	SetModified( TRUE);	
}

void CDlgPrefGeneral::OnSingleclick() 
{
	SetModified( TRUE);	
}

void CDlgPrefGeneral::OnSelchangeUnits() 
{
	SetModified( TRUE);	
}

void CDlgPrefGeneral::OnLongstatus() 
{
	SetModified( TRUE);	

}

void CDlgPrefGeneral::OnPickfnt() 
{
	if ( IDOK == m_SummaryFont.EditProperties())
	{
		SetModified( TRUE);
		UpdateData( FALSE);
	}
}


void CDlgPrefGeneral::OnChangeTrails() 
{
	SetModified( TRUE);	
	
}

void CDlgPrefGeneral::OnChangeAllowedlocale() 
{
	SetModified( TRUE);	

}

void CDlgPrefGeneral::OnAutosave() 
{

	SetModified( TRUE);	

	EnableSave();
}


void CDlgPrefGeneral::OnChangeSavetime() 
{
	SetModified( TRUE);	
	
}

void CDlgPrefGeneral::OnDeltaposSpin4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}
