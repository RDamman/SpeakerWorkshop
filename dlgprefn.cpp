// dlgprefn.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "fxFont.h"
#include "dlgprefn.h"

#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefNetwork property page

IMPLEMENT_DYNCREATE(CDlgPrefNetwork, CPropertyPage)

CDlgPrefNetwork::CDlgPrefNetwork() : CPropertyPage(CDlgPrefNetwork::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgPrefNetwork)
	m_csFontName = _T("");
	m_csDataName = _T("");
	m_nPrecision = -1;
	m_nResType = -1;
	m_bDrawEnds = FALSE;
	//}}AFX_DATA_INIT

}

CDlgPrefNetwork::~CDlgPrefNetwork()
{
}

void CDlgPrefNetwork::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgPrefNetwork::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	if ( ! pDX->m_bSaveAndValidate)	// update the display
		{
		m_LabelFont.GetPrettyName(m_csFontName);
		m_DataFont.GetPrettyName(m_csDataName);
		}

	//{{AFX_DATA_MAP(CDlgPrefNetwork)
	DDX_Text(pDX, IDC_FONTNAME, m_csFontName);
	DDX_Text(pDX, IDC_DATANAME, m_csDataName);
	DDX_CBIndex(pDX, IDC_DIGITS, m_nPrecision);
	DDX_CBIndex(pDX, IDC_RESTYPE, m_nResType);
	DDX_Check(pDX, IDC_DRAWENDS, m_bDrawEnds);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPrefNetwork, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgPrefNetwork)
	ON_BN_CLICKED(IDC_SELLABEL, OnSellabel)
	ON_BN_CLICKED(IDC_SELDATA, OnSeldata)
	ON_CBN_SELCHANGE(IDC_DIGITS, OnSelchangeDigits)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgPrefNetwork, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgPrefNetwork)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefNetwork message handlers

void CDlgPrefNetwork::OnSellabel() 
{
	if ( IDOK == m_LabelFont.EditProperties())
	{
		SetModified( TRUE);
		UpdateData( FALSE);
	}

}

void CDlgPrefNetwork::OnSeldata() 
{
	if ( IDOK == m_DataFont.EditProperties())
	{
		SetModified( TRUE);
		UpdateData( FALSE);
	}
	
}

BOOL CDlgPrefNetwork::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	::ComboFillString( this, IDC_DIGITS, IDS_PREFN_DIGITS);
	::ComboFillString( this, IDC_RESTYPE, IDS_PREFN_RESTYPE);

	m_DataFont = CAudtestApp::GetAppFont( ftNetData);
	m_LabelFont =  CAudtestApp::GetAppFont( ftNetLabels);
	m_nPrecision = CAudtestApp::GetPrecision( 0);
	m_nResType = CAudtestApp::GetResistorType() ? 0 : 1;	// invert
	m_bDrawEnds = CAudtestApp::GetDrawEndpoints() ? true : false;

	UpdateData( FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgPrefNetwork::OnApply() 
{
	if ( ! VerboseUpdateData( TRUE))
		return 0;

	CAudtestApp::GetAppFont( ftNetData) = m_DataFont;
	CAudtestApp::GetAppFont(ftNetData).WriteIni( ftNetData);
	CAudtestApp::GetAppFont( ftNetLabels) = m_LabelFont;
	CAudtestApp::GetAppFont(ftNetLabels).WriteIni( ftNetLabels);
	CAudtestApp::SetPrecision(0, m_nPrecision);
	CAudtestApp::SetResistorType( m_nResType ? 0 : 1);		// invert
	CAudtestApp::SetDrawEndpoints( m_bDrawEnds ? 1 : 0);

	SetModified( FALSE);

	return CPropertyPage::OnApply();
}

void CDlgPrefNetwork::OnSelchangeDigits() 
{
	SetModified( TRUE);	
}
