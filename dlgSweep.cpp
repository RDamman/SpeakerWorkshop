// dlgsweep.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgsweep.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSweep property page

IMPLEMENT_DYNCREATE(CDlgSweep, CPropertyPage)

CDlgSweep::CDlgSweep() : CPropertyPage(CDlgSweep::IDD), m_cfEdits()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgSweep)
	m_bSmooth = FALSE;
	m_nSteps = 0;
	//}}AFX_DATA_INIT

	m_bLinear = TRUE;
}

CDlgSweep::~CDlgSweep()
{
}

void CDlgSweep::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgSweep::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgSweep)
	DDX_Check(pDX, IDC_SMOOTH, m_bSmooth);
	DDX_Text(pDX, IDC_SWPSTEPS, m_nSteps);
	//}}AFX_DATA_MAP
	if ( pDX->m_bSaveAndValidate)
		{
		m_bLinear = IsDlgButtonChecked( IDC_SWPLINEAR);
		}
	else
		{
		int nradio = (m_bLinear ? IDC_SWPLINEAR : IDC_SWPLOG);
		CheckRadioButton(IDC_SWPLINEAR, IDC_SWPLOG, nradio);
		}
}


BEGIN_MESSAGE_MAP(CDlgSweep, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgSweep)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgSweep, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgSweep)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSweep message handlers

BOOL CDlgSweep::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[3] = { 
							{IDC_FSTART,	IDC_SCRL1, 1.0f, 20000.0f, &m_fStart},
							{IDC_FEND,	IDC_SCRL2, 1.0f, 20000.0f, &m_fEnd},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CPropertyPage::OnInitDialog();
	
	{					// the spin button for the # of points
	CSpinButtonCtrl *pbutton;
	pbutton = (CSpinButtonCtrl *)GetDlgItem( IDC_SCRL3);
	if ( pbutton)
		pbutton->SetRange(1,100);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSweep::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}
