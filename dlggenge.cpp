// dlggenge.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlggenge.h"

#include "mmwave.h"
#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGenGeneral property page

IMPLEMENT_DYNCREATE(CDlgGenGeneral, CPropertyPage)

CDlgGenGeneral::CDlgGenGeneral() : CPropertyPage(CDlgGenGeneral::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgGenGeneral)
	m_csDescript = _T("");
	m_csDate = _T("");
	m_nType = -1;
	m_nRate = -1;
	m_csLastDate = _T("");
	//}}AFX_DATA_INIT
}

CDlgGenGeneral::~CDlgGenGeneral()
{
}

void CDlgGenGeneral::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgGenGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGenGeneral)
	DDX_Control(pDX, IDC_RATE, m_cDataRates);
	DDX_Text(pDX, IDC_DESCRIPT, m_csDescript);
	DDX_Text(pDX, IDC_DATE, m_csDate);
	DDX_CBIndex(pDX, IDC_TYPE, m_nType);
	DDX_CBIndex(pDX, IDC_RATE, m_nRate);
	DDX_Text(pDX, IDC_LASTDATE, m_csLastDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGenGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgGenGeneral)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgGenGeneral, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgGenGeneral)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGenGeneral message handlers

BOOL CDlgGenGeneral::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	::ComboFillString( this, IDC_TYPE, IDS_GENGENERAL_TYPE);
	::ComboFillString( this, IDC_RATE, IDS_GENGENERAL_RATE);

	// TODO: Add extra initialization here
//	UpdateData( FALSE);			// get the control set
//	UpdateData( TRUE);			// set the control set

	ASSERT( m_cDataRates.GetSafeHwnd());
	{
	const CDWordArray *prate = CMMWave::GetRateArray();
	int i;

		m_cDataRates.ResetContent();
		for ( i=0; i<prate->GetSize(); i++)
			{
			char cs[20];
				sprintf(cs, "%d", (int )prate->GetAt(i) );
			m_cDataRates.AddString( cs);
			}
	UpdateData( FALSE);			// get the control set
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
