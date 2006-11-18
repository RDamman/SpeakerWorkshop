// dlgnetge.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgnetge.h"
#include "dlgNetwo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNetGeneral property page

IMPLEMENT_DYNCREATE(CDlgNetGeneral, CPropertyPage)

CDlgNetGeneral::CDlgNetGeneral() : CPropertyPage(CDlgNetGeneral::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgNetGeneral)
	m_csDescript = _T("");
	m_csLastDate = _T("");
	m_csFirstDate = _T("");
	m_bDoImpedance = FALSE;
	m_bAutoChart = FALSE;
	m_bDoResponse = FALSE;
	//}}AFX_DATA_INIT
}

CDlgNetGeneral::~CDlgNetGeneral()
{
}

void CDlgNetGeneral::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgNetGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNetGeneral)
	DDX_Text(pDX, IDC_DESCRIPT, m_csDescript);
	DDX_Text(pDX, IDC_DATE2, m_csLastDate);
	DDX_Text(pDX, IDC_DATE, m_csFirstDate);
	DDX_Check(pDX, IDC_DOIMPEDANCE, m_bDoImpedance);
	DDX_Check(pDX, IDC_AUTOCHART, m_bAutoChart);
	DDX_Check(pDX, IDC_DOREPONSE, m_bDoResponse);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNetGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgNetGeneral)
	ON_BN_CLICKED(IDC_AUTOCHART, OnAutochart)
	ON_BN_CLICKED(IDC_DOIMPEDANCE, OnDoimpedance)
	ON_BN_CLICKED(IDC_DOREPONSE, OnDoreponse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgNetGeneral, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgNetGeneral)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNetGeneral message handlers


void CDlgNetGeneral::UseGeneral( CNetwork *pcNet)
{
	m_csDescript = pcNet->GetDescription();
	m_bDoResponse = pcNet->HasResponse();
	m_bDoImpedance = pcNet->HasImpedance();
	m_bAutoChart = pcNet->HasAutoChart();

	pcNet->SetDateStrings( m_csFirstDate, m_csLastDate);

}


void CDlgNetGeneral::SetGeneral( CNetwork *pcNet)
{
	pcNet->SetDescription( m_csDescript);
	pcNet->GenResponse( m_bDoResponse);
	pcNet->GenImpedance( m_bDoImpedance);
	pcNet->GenAutoChart( m_bAutoChart);
}



void CDlgNetGeneral::OnAutochart() 
{
	SetModified();	
	
}

void CDlgNetGeneral::OnDoimpedance() 
{
	SetModified();	
	
}

void CDlgNetGeneral::OnDoreponse() 
{
	SetModified();	
	
}

// ----------------------------------------------------------------------------------
//		OnApply
// ----------------------------------------------------------------------------------
BOOL CDlgNetGeneral::OnApply() 
{
	UpdateData( TRUE);
	m_pParent->SetReapply( true);

	return CPropertyPage::OnApply();
}
