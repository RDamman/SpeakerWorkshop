// dlgchgen.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgchgen.h"

#include "FxFont.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgChGen property page

IMPLEMENT_DYNCREATE(CDlgChGen, CPropertyPage)

CDlgChGen::CDlgChGen() : CPropertyPage(CDlgChGen::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgChGen)
	m_szDate = _T("");
	m_szDescription = _T("");
	m_csTitle = _T("");
	m_bShowLegend = FALSE;
	m_csLastEdit = _T("");
	//}}AFX_DATA_INIT
}

CDlgChGen::~CDlgChGen()
{
}

void CDlgChGen::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgChGen::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChGen)
	DDX_Text(pDX, IDC_DATE, m_szDate);
	DDX_Text(pDX, IDC_DESCRIPT, m_szDescription);
	DDX_Text(pDX, IDC_TITLE, m_csTitle);
	DDX_Check(pDX, IDC_SHOWLEGEND, m_bShowLegend);
	DDX_Text(pDX, IDC_LASTEDIT, m_csLastEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChGen, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgChGen)
	ON_BN_CLICKED(IDC_SELTITLEFONT, OnSeltitlefont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgChGen, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgChGen)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChGen message handlers


void CDlgChGen::UseGeneral( CSubChart *pcChart)
{
	m_szDescription = pcChart->GetDescription();
	m_csTitle = pcChart->m_csTitle;
	m_bShowLegend = pcChart->m_cLegend.IsVisible();

	pcChart->SetDateStrings( m_szDate, m_csLastEdit);
}


void CDlgChGen::SetGeneral( CSubChart *pcChart)
{
	pcChart->SetDescription( m_szDescription);
	pcChart->m_csTitle = m_csTitle;
	pcChart->m_cLegend.SetVisible(m_bShowLegend);


}



void CDlgChGen::OnSeltitlefont() 
{
	CAudtestApp::EditAppFont( ftTitle);
}
