// DlgCalcPassive.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "DlgCalcPassive.h"

#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcPassive dialog

typedef struct tagCALCPASSIVE
	{
	float	fValue;
	float	fFreq;
	int		nType;
	} CALCPASSIVE;


bool CDlgCalcPassive::m_bIsShowing = false;			// is it showing????
static WINDOWPLACEMENT g_wpWindowPlace = {0,0};


CDlgCalcPassive::CDlgCalcPassive(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCalcPassive::IDD, pParent), m_cfEdits()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgCalcPassive)
	m_csAmp = _T("");
	m_csPhase = _T("");
	m_csReal = _T("");
	m_csImaginary = _T("");
	//}}AFX_DATA_INIT

	m_bIsShowing = true;			// we have it now
}


void CDlgCalcPassive::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();

}

void CDlgCalcPassive::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	if ( ! pDX->m_bSaveAndValidate)
		{
		CheckRadioButton( IDC_RADIO1, IDC_RADIO3 ,IDC_RADIO1 + m_nType);
		}

	//{{AFX_DATA_MAP(CDlgCalcPassive)
	DDX_Text(pDX, IDC_AMP, m_csAmp);
	DDX_Text(pDX, IDC_PHASE, m_csPhase);
	DDX_Text(pDX, IDC_REAL, m_csReal);
	DDX_Text(pDX, IDC_IMAGINARY, m_csImaginary);
	//}}AFX_DATA_MAP

	if ( pDX->m_bSaveAndValidate)
		{
		m_nType = GetCheckedRadioButton( IDC_RADIO1, IDC_RADIO3 ) - IDC_RADIO1;
		}

}


BEGIN_MESSAGE_MAP(CDlgCalcPassive, CDialog)
	//{{AFX_MSG_MAP(CDlgCalcPassive)
	ON_EN_CHANGE(IDC_FREQ, OnChangeFreq)
	ON_EN_CHANGE(IDC_VALUE, OnChangeValue)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO2, OnRadio)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgCalcPassive, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgCalcPassive)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgCalcPassive to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {B4D31A42-78D3-11CF-AA04-444553540000}
static const IID IID_IDlgCalcPassive =
{ 0xb4d31a42, 0x78d3, 0x11cf, { 0xaa, 0x4, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgCalcPassive, CDialog)
	INTERFACE_PART(CDlgCalcPassive, IID_IDlgCalcPassive, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcPassive message handlers

BOOL CDlgCalcPassive::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[3] = { 
							{IDC_FREQ,	IDC_SPIN2, 0.0f, 199000.0f, &m_fFreq},
							{IDC_VALUE,	IDC_SPIN1, 0.0f, 199000.0f, &m_fValue},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CDialog::OnInitDialog();
	
	{
	CALCPASSIVE clc;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		if ( ! capp->ReadRegistry( IDS_CALCPASSINFO, &clc, sizeof(clc)))
			{
			m_fValue = clc.fValue;
			m_fFreq = clc.fFreq;
			m_nType = clc.nType;
			}
		else
			{
			m_fValue = .001f;
			m_fFreq = 1000.0f;
			m_nType = 0;
			}
	}
	
	UpdateData( FALSE);
	recalc_Values();

	if ( g_wpWindowPlace.length == sizeof( g_wpWindowPlace))		// it's not empty, set back there
		SetWindowPlacement( &g_wpWindowPlace);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCalcPassive::recalc_Values()
{
float fomega = (float )(2 * ONEPI * m_fFreq);

	switch( m_nType)			// what type of component
		{
		case 0 :			// capacitor
			if (m_fValue)
				m_csAmp.Format( "%f", (float )(1.0f / (m_fValue * fomega)));
			else
				m_csAmp.Format( "%f", 1000000.0f);
			m_csImaginary = "-" + m_csAmp;
			m_csReal.Format( "%f", 0.0f);
			m_csPhase.Format( "%f", -90.0f);
			break;
		case 1 :			// inductor
			m_csAmp.Format( "%f", (float )(m_fValue * fomega));
			m_csImaginary = m_csAmp;
			m_csReal.Format( "%f", 0.0f);
			m_csPhase.Format( "%f", 90.0f);
			break;
		case 2 :			// resistor (removed from dbox mz)
			break;
		}

	UpdateData( FALSE);
}

void CDlgCalcPassive::OnChangeFreq() 
{
	if ( VerboseUpdateData( TRUE))
		recalc_Values();	
}

void CDlgCalcPassive::OnChangeValue() 
{
	if ( VerboseUpdateData( TRUE))
		recalc_Values();	

}

void CDlgCalcPassive::OnRadio() 
{

	UpdateData( TRUE);
	{
	char *pout;

		if ( IsDlgButtonChecked( IDC_RADIO1))
			pout = "F";		// capacitor was checked, use farads
		else
			pout = "H";		// inductors was checked, use Henries

		SetDlgItemText(IDC_UNITS, pout);
	}

	recalc_Values();	
	
}

void CDlgCalcPassive::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

void CDlgCalcPassive::PostNcDestroy() 
{
	CDialog::PostNcDestroy();

	m_bIsShowing = false;

	delete this;			// per microsoft, kill us here
}

void CDlgCalcPassive::OnClose() 
{
	if (! VerboseUpdateData( TRUE))
		return;

	CALCPASSIVE clc;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		clc.fValue = m_fValue;
		clc.fFreq = m_fFreq;
		clc.nType = m_nType;

		capp->WriteRegistry( IDS_CALCPASSINFO, &clc, sizeof(clc));

	g_wpWindowPlace.length = sizeof( g_wpWindowPlace);
	GetWindowPlacement( & g_wpWindowPlace);

	CDialog::OnClose();

	DestroyWindow();
}
