// dlgpulse.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgpulse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPulse property page

IMPLEMENT_DYNCREATE(CDlgPulse, CPropertyPage)

CDlgPulse::CDlgPulse() : CPropertyPage(CDlgPulse::IDD), m_cDuration(), m_cFreq()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgPulse)
	m_bNegative = FALSE;
	m_bRepeat = FALSE;
	//}}AFX_DATA_INIT
}

CDlgPulse::~CDlgPulse()
{
}

void CDlgPulse::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgPulse::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cDuration.DDX_Value( pDX, m_fDuration);
	m_cFreq.DDX_Value( pDX, m_fFreq);
	
	//{{AFX_DATA_MAP(CDlgPulse)
	DDX_Check(pDX, IDC_NEGATIVE, m_bNegative);
	DDX_Check(pDX, IDC_CONTINUOUS, m_bRepeat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPulse, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgPulse)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposScrl1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposScrl2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgPulse, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgPulse)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPulse message handlers

BOOL CDlgPulse::OnInitDialog() 
{
	m_cDuration.Subclass( this, IDC_DURATION, IDC_SCRL1);
	m_cDuration.SetLimits( 0.0f, 100000.0f);
	m_cFreq.Subclass( this, IDC_FREQ, IDC_SCRL2);
	m_cFreq.SetLimits( 1.0f, 20000.0f);

	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPulse::OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cDuration.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}

void CDlgPulse::OnDeltaposScrl2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cFreq.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}
