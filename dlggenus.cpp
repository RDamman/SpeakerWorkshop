// dlggenus.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlggenus.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGenUserDef property page

IMPLEMENT_DYNCREATE(CDlgGenUserDef, CPropertyPage)

CDlgGenUserDef::CDlgGenUserDef() : CPropertyPage(CDlgGenUserDef::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgGenUserDef)
	m_csUserName = _T("");
	//}}AFX_DATA_INIT
}

CDlgGenUserDef::~CDlgGenUserDef()
{
}

void CDlgGenUserDef::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgGenUserDef::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGenUserDef)
	DDX_Text(pDX, IDC_USERNAME, m_csUserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGenUserDef, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgGenUserDef)
	ON_BN_CLICKED(IDC_BROWSEWAVE, OnBrowsewave)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgGenUserDef, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgGenUserDef)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGenUserDef message handlers
/////////////////////////////////////////////////////////////////////////////



void CDlgGenUserDef::OnBrowsewave() 
{
CFileDialog cfd(TRUE, "Wav", NULL, OFN_HIDEREADONLY, 
					"Wave files|*.WAV|All files|*.*||", this );

	if ( IDOK == cfd.DoModal())
		{
		m_csUserName = cfd.GetPathName();
		UpdateData( FALSE);
		}

}


void CDlgGenUserDef::OnClear() 
{
	m_csUserName = "";
	UpdateData( FALSE);

}

// CDlgGenWarble property page

IMPLEMENT_DYNCREATE(CDlgGenWarble, CPropertyPage)

CDlgGenWarble::CDlgGenWarble() : CPropertyPage(CDlgGenWarble::IDD), m_cRate(), m_cOctave(), m_cCenter()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgGenWarble)
	//}}AFX_DATA_INIT
}

CDlgGenWarble::~CDlgGenWarble()
{
}

void CDlgGenWarble::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgGenWarble::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cRate.DDX_Value( pDX, m_fRate);
	m_cOctave.DDX_Value( pDX, m_fOctave);
	m_cCenter.DDX_Value( pDX, m_fCenter);
	
	//{{AFX_DATA_MAP(CDlgGenWarble)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGenWarble, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgGenWarble)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposScrl1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposScrl2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL3, OnDeltaposScrl3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgGenWarble, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgGenWarble)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGenWarble message handlers

BOOL CDlgGenWarble::OnInitDialog() 
{
	m_cCenter.Subclass( this, IDC_CENTERFREQ, IDC_SCRL1);
	m_cCenter.SetLimits( 1.0f, 20000.0f);
	m_cOctave.Subclass( this, IDC_OCTAVE, IDC_SCRL2);
	m_cOctave.SetLimits( 0.0f, 10.0f);
	m_cRate.Subclass( this, IDC_WRATE, IDC_SCRL3);
	m_cRate.SetLimits( 0.001f, 20000.0f);

	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgGenWarble::OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cCenter.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}

void CDlgGenWarble::OnDeltaposScrl2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cOctave.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}

void CDlgGenWarble::OnDeltaposScrl3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cRate.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}

