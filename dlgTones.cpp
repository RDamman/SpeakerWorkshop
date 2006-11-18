// dlgtones.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgtones.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTones property page

IMPLEMENT_DYNCREATE(CDlgTones, CPropertyPage)

CDlgTones::CDlgTones() : CPropertyPage(CDlgTones::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgTones)
	m_bTone1 = FALSE;
	m_bTone2 = FALSE;
	m_bTone3 = FALSE;
	m_bTone4 = FALSE;
	m_bTone5 = FALSE;
	//}}AFX_DATA_INIT
}

CDlgTones::~CDlgTones()
{
}

void CDlgTones::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgTones::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	{			// handle the floating point minibars
	int i;
	for ( i=0; i<NUMTONES; i++)
		{
		m_cAmp[i].DDX_Value( pDX, m_fAmp[i]);
		m_cFreq[i].DDX_Value( pDX, m_fFreq[i]);
		}
	}
	
	//{{AFX_DATA_MAP(CDlgTones)
	DDX_Check(pDX, IDC_TONE1, m_bTone1);
	DDX_Check(pDX, IDC_TONE2, m_bTone2);
	DDX_Check(pDX, IDC_TONE3, m_bTone3);
	DDX_Check(pDX, IDC_TONE4, m_bTone4);
	DDX_Check(pDX, IDC_TONE5, m_bTone5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTones, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgTones)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC1, OnDeltaposGeneric)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposScrl)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC2, OnDeltaposGeneric)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC3, OnDeltaposGeneric)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC4, OnDeltaposGeneric)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC5, OnDeltaposGeneric)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposScrl)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL3, OnDeltaposScrl)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL4, OnDeltaposScrl)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL5, OnDeltaposScrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgTones, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgTones)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTones message handlers

BOOL CDlgTones::OnInitDialog() 
{

	{			// subclass the floating point minibars
	int i;
	for ( i=0; i<NUMTONES; i++)
		{
		m_cFreq[i].Subclass( this, IDC_FREQ1 + i, IDC_SCRL1 + i);
		m_cFreq[i].SetLimits( 1.0f, 20000.0f);
		m_cAmp[i].Subclass( this, IDC_AMP1 + i, IDC_GENERIC1 + i);
		m_cAmp[i].SetLimits( 0.0f, 100.0f);
		}
	}
	
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgTones::OnDeltaposGeneric(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	ASSERT( IDC_GENERIC1 <= pNMHDR->idFrom && IDC_GENERIC5 >= pNMHDR->idFrom);

	m_cAmp[ pNMHDR->idFrom - IDC_GENERIC1].ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}

void CDlgTones::OnDeltaposScrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	ASSERT( IDC_SCRL1 <= pNMHDR->idFrom && IDC_SCRL5 >= pNMHDR->idFrom);

	m_cFreq[ pNMHDR->idFrom - IDC_SCRL1].ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}
