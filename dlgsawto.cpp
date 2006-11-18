// dlgsawto.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgsawto.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSawtooth property page

IMPLEMENT_DYNCREATE(CDlgSawtooth, CPropertyPage)

CDlgSawtooth::CDlgSawtooth() : CPropertyPage(CDlgSawtooth::IDD), m_cFreq()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgSawtooth)
	//}}AFX_DATA_INIT
}

CDlgSawtooth::~CDlgSawtooth()
{
}

void CDlgSawtooth::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgSawtooth::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cFreq.DDX_Value( pDX, m_fFreq);
	
	//{{AFX_DATA_MAP(CDlgSawtooth)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSawtooth, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgSawtooth)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposScrl1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgSawtooth, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgSawtooth)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSawtooth message handlers

BOOL CDlgSawtooth::OnInitDialog() 
{
	m_cFreq.Subclass( this, IDC_FREQ, IDC_SCRL1);
	m_cFreq.SetLimits( 1.0f, 20000.0f);

	CPropertyPage::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSawtooth::OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cFreq.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}
