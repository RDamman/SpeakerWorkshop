// dlgnoise.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgnoise.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define IDC_PINK IDC_RADIO1
#define IDC_WHITE IDC_RADIO2

/////////////////////////////////////////////////////////////////////////////
// CDlgNoise property page

IMPLEMENT_DYNCREATE(CDlgNoise, CPropertyPage)

CDlgNoise::CDlgNoise() : CPropertyPage(CDlgNoise::IDD), m_cfEdits()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgNoise)
	//}}AFX_DATA_INIT

	m_bUseAll = TRUE;
	m_bUsePink = FALSE;
}

CDlgNoise::~CDlgNoise()
{
}

void CDlgNoise::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgNoise::DoDataExchange(CDataExchange* pDX)
{
	if ( ! pDX->m_bSaveAndValidate)
		{
		CheckRadioButton( IDC_USEENTIRE, IDC_USEMARKER, m_bUseAll ? IDC_USEENTIRE : IDC_USEMARKER);
		CheckRadioButton( IDC_PINK, IDC_WHITE, m_bUsePink ? IDC_PINK : IDC_WHITE);
		}
	CPropertyPage::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgNoise)
	//}}AFX_DATA_MAP
	if ( pDX->m_bSaveAndValidate)
		{
		m_bUseAll = IsDlgButtonChecked( IDC_USEENTIRE);
		m_bUsePink = IsDlgButtonChecked( IDC_PINK);
		}
}


BEGIN_MESSAGE_MAP(CDlgNoise, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgNoise)
	ON_EN_CHANGE(IDC_FEND, OnChangeFend)
	ON_EN_CHANGE(IDC_FSTART, OnChangeFstart)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgNoise, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgNoise)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNoise message handlers

BOOL CDlgNoise::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[3] = { 
							{IDC_FSTART,	IDC_SCRL1, 0.0f, 2000000.0f, &m_fStart},
							{IDC_FEND,	IDC_SCRL2, 0.0f, 2000000.0f, &m_fEnd},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNoise::OnChangeFend() 
{
	CheckRadioButton( IDC_USEENTIRE, IDC_USEMARKER, IDC_USEMARKER);
	
}

void CDlgNoise::OnChangeFstart() 
{
	CheckRadioButton( IDC_USEENTIRE, IDC_USEMARKER, IDC_USEMARKER);
	
}

void CDlgNoise::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}
