// dlgdrgen.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgdrgen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDrGeneral property page

IMPLEMENT_DYNCREATE(CDlgDrGeneral, CPropertyPage)

CDlgDrGeneral::CDlgDrGeneral() : CPropertyPage(CDlgDrGeneral::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgDrGeneral)
	m_szDescription = _T("");
	m_szDate = _T("");
	m_szLastEdit = _T("");
	//}}AFX_DATA_INIT
}

CDlgDrGeneral::~CDlgDrGeneral()
{
}

void CDlgDrGeneral::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgDrGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDrGeneral)
	DDX_Text(pDX, IDC_DESCRIPT, m_szDescription);
	DDX_Text(pDX, IDC_DATE, m_szDate);
	DDX_Text(pDX, IDC_LASTEDIT, m_szLastEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDrGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgDrGeneral)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgDrGeneral, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgDrGeneral)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDrGeneral message handlers

void CDlgDrGeneral::UseGeneral( CDriver *pcDriver)
{
	m_szDescription = pcDriver->GetDescription();

	pcDriver->SetDateStrings( m_szDate, m_szLastEdit);

}


void CDlgDrGeneral::SetGeneral( CDriver *pcDriver)
{
	pcDriver->SetDescription( m_szDescription);
}


