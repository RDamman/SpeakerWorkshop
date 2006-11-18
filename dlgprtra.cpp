// dlgprtra.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgprtra.h"

#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefTransform property page

IMPLEMENT_DYNCREATE(CDlgPrefTransform, CPropertyPage)

CDlgPrefTransform::CDlgPrefTransform() : CPropertyPage(CDlgPrefTransform::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgPrefTransform)
	m_bAutoIncrement = FALSE;
	m_bBinAutoIncrement = FALSE;
	m_bExeInPlace = FALSE;
	m_bBinExeInPlace = FALSE;
	m_nFftWindow = -1;
	//}}AFX_DATA_INIT
}

CDlgPrefTransform::~CDlgPrefTransform()
{
}

void CDlgPrefTransform::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgPrefTransform::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPrefTransform)
	DDX_Check(pDX, IDC_AUTOINCREMENT, m_bAutoIncrement);
	DDX_Check(pDX, IDC_AUTOINCREMENT2, m_bBinAutoIncrement);
	DDX_Check(pDX, IDC_EXEINPLACE, m_bExeInPlace);
	DDX_Check(pDX, IDC_EXEINPLACE2, m_bBinExeInPlace);
	DDX_CBIndex(pDX, IDC_FFTWINDOW, m_nFftWindow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPrefTransform, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgPrefTransform)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgPrefTransform, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgPrefTransform)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefTransform message handlers

BOOL CDlgPrefTransform::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	::ComboFillString( this, IDC_FFTWINDOW, IDS_PREFT_FFTWINDOW);

	UpdateData( FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
