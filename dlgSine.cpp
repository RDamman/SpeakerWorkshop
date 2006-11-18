// dlgsine.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgsine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSine property page

IMPLEMENT_DYNCREATE(CDlgSine, CPropertyPage)

CDlgSine::CDlgSine() : CPropertyPage(CDlgSine::IDD), m_cPhase(), m_cFreq()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgSine)
	//}}AFX_DATA_INIT
}

CDlgSine::~CDlgSine()
{
}

void CDlgSine::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgSine::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cPhase.DDX_Value( pDX, m_fPhase);
	m_cFreq.DDX_Value( pDX, m_fFreq);
	
	//{{AFX_DATA_MAP(CDlgSine)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSine, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgSine)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposScrl1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposScrl2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgSine, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgSine)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSine message handlers





BOOL CDlgSine::OnInitDialog() 
{
	
	m_cFreq.Subclass( this, IDC_FREQ, IDC_SCRL1);
	m_cFreq.SetLimits( 1.0f, 20000.0f);
	m_cPhase.Subclass( this, IDC_PHASE, IDC_SCRL2);
	m_cPhase.SetLimits( -180.0f, 360.0f);
	
	CPropertyPage::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSine::OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cFreq.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}

void CDlgSine::OnDeltaposScrl2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cPhase.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}
