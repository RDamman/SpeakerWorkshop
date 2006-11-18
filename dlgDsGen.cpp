// dlgdsgen.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "dataset.h"

#include "dlgdsgen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDsGeneral property page

IMPLEMENT_DYNCREATE(CDlgDsGeneral, CPropertyPage)

CDlgDsGeneral::CDlgDsGeneral() : CPropertyPage(CDlgDsGeneral::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgDsGeneral)
	m_csDate = _T("");
	m_csDescript = _T("");
	m_csLastEdit = _T("");
	//}}AFX_DATA_INIT
}

CDlgDsGeneral::~CDlgDsGeneral()
{
}

void CDlgDsGeneral::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgDsGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDsGeneral)
	DDX_Text(pDX, IDC_DATE, m_csDate);
	DDX_Text(pDX, IDC_DESCRIPT, m_csDescript);
	DDX_Text(pDX, IDC_LASTEDIT, m_csLastEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDsGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgDsGeneral)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgDsGeneral, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgDsGeneral)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDsGeneral message handlers
// called before the dialog is shown
void CDlgDsGeneral::PreDialog( CDataSet *pcData)
{

	pcData->SetDateStrings( m_csDate, m_csLastEdit);
	m_csDescript = pcData->GetDescription();

	SetModified( FALSE);

}

// called after ok is pressed
void CDlgDsGeneral::PostDialog( CDataSet *pcData)
{
	pcData->SetDescription( m_csDescript);
}


