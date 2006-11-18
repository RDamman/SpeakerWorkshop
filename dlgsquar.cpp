// dlgsquar.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgsquar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSquare property page

IMPLEMENT_DYNCREATE(CDlgSquare, CPropertyPage)

CDlgSquare::CDlgSquare() : CPropertyPage(CDlgSquare::IDD), m_cDutyCycle(), m_cFreq()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgSquare)
	//}}AFX_DATA_INIT
}

CDlgSquare::~CDlgSquare()
{
}

void CDlgSquare::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgSquare::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cDutyCycle.DDX_Value( pDX, m_fDutyCycle);
	m_cFreq.DDX_Value( pDX, m_fFreq);
	
	//{{AFX_DATA_MAP(CDlgSquare)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSquare, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgSquare)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposScrl1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposScrl2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgSquare, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgSquare)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSquare message handlers

BOOL CDlgSquare::OnInitDialog() 
{
	m_cFreq.Subclass( this, IDC_FREQ, IDC_SCRL1);
	m_cFreq.SetLimits( 1.0f, 20000.0f);
	m_cDutyCycle.Subclass( this, IDC_DUTYCYCLE, IDC_SCRL2);
	m_cDutyCycle.SetLimits( 0.0f, 100.0f);

	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSquare::OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cFreq.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}

void CDlgSquare::OnDeltaposScrl2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cDutyCycle.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}
