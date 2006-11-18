// DlgMsrDistort.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "DlgMsrDistort.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMsrDistort dialog


CDlgMsrDistort::CDlgMsrDistort(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMsrDistort::IDD, pParent), m_cfEdits()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgMsrDistort)
	m_bLogRange = FALSE;
	m_nPoints = 0;
	//}}AFX_DATA_INIT
}


void CDlgMsrDistort::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CDlgMsrDistort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	if ( ! pDX->m_bSaveAndValidate)
		{
		CheckRadioButton( IDC_SPECTRUM, IDC_POWERDIST ,IDC_SPECTRUM + m_nStyle);
		}

	//{{AFX_DATA_MAP(CDlgMsrDistort)
	DDX_Check(pDX, IDC_ISLOG, m_bLogRange);
	DDX_Text(pDX, IDC_NPOINTS, m_nPoints);
	DDV_MinMaxInt(pDX, m_nPoints, 1, 1000);
	//}}AFX_DATA_MAP

	if ( pDX->m_bSaveAndValidate)
		{
		m_nStyle = GetCheckedRadioButton( IDC_SPECTRUM, IDC_POWERDIST ) - IDC_SPECTRUM;
		}
}

// note that scrl7 is number of points and handled elsewhere

BEGIN_MESSAGE_MAP(CDlgMsrDistort, CDialog)
	//{{AFX_MSG_MAP(CDlgMsrDistort)
	ON_BN_CLICKED(IDC_SPECTRUM, OnSpectrum)
	ON_BN_CLICKED(IDC_FREQDIST, OnFreq)
	ON_BN_CLICKED(IDC_POWERDIST, OnPower)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL3, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL4, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL5, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL6, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL8, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgMsrDistort, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgMsrDistort)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgMsrDistort to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {11B046E0-666C-11CF-AA04-444553540000}
static const IID IID_IDlgMsrDistort =
{ 0x11b046e0, 0x666c, 0x11cf, { 0xaa, 0x4, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgMsrDistort, CDialog)
	INTERFACE_PART(CDlgMsrDistort, IID_IDlgMsrDistort, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMsrDistort message handlers

void CDlgMsrDistort::OnFreq() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgMsrDistort::OnPower() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgMsrDistort::OnSpectrum() 
{
	// TODO: Add your control notification handler code here
	
}


BOOL CDlgMsrDistort::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[8] = { 
							{IDC_ONEPOWER,		IDC_SCRL1, 1.0f,   20000.0f, &m_fPower},
							{IDC_ONEFREQ,		IDC_SCRL2, 0.001f, 10000.0f, &m_fFreq},
							{IDC_FREQ1,			IDC_SCRL3, 1.0f,   20000.0f, &m_fFreqStart},
							{IDC_FREQ2,			IDC_SCRL4, 1.0f,   20000.0f, &m_fFreqEnd},
							{IDC_POWER1,		IDC_SCRL5, 0.001f, 10000.0f, &m_fPowerStart},
							{IDC_POWER2,		IDC_SCRL6, 0.001f, 10000.0f, &m_fPowerEnd},
							{IDC_WATT,			IDC_SCRL8, 0.01f,    100.0f, &m_fEquate},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CDialog::OnInitDialog();

	{
	CSpinButtonCtrl *pwnd = (CSpinButtonCtrl *)GetDlgItem( IDC_SCRL7);		// get the npoints spin
		if ( pwnd)
			pwnd->SetRange(1, 1000);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMsrDistort::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}
