// DlgCalcTuned.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "DlgCalcTuned.h"

#include "math.h"
#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcTuned dialog
typedef struct tagCALCTUNED
	{
	float	fLValue;
	float	fRValue;
	float	fCValue;
	int		nType;
	} CALCTUNED;



bool CDlgCalcTuned::m_bIsShowing = false;			// is it showing????
static WINDOWPLACEMENT g_wpWindowPlace = {0,0};


CDlgCalcTuned::CDlgCalcTuned(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCalcTuned::IDD, pParent), m_cfEdits()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgCalcTuned)
	m_csFreq = _T("");
	m_csQ = _T("");
	//}}AFX_DATA_INIT

	m_bIsShowing = true;
}


void CDlgCalcTuned::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CDlgCalcTuned::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	if ( ! pDX->m_bSaveAndValidate)
		{
		CheckRadioButton( IDC_RADIO1, IDC_RADIO2 ,IDC_RADIO1 + m_nType);
		}


	//{{AFX_DATA_MAP(CDlgCalcTuned)
	DDX_Text(pDX, IDC_FREQ, m_csFreq);
	DDX_Text(pDX, IDC_Q, m_csQ);
	//}}AFX_DATA_MAP

	if ( pDX->m_bSaveAndValidate)
		{
		m_nType = GetCheckedRadioButton( IDC_RADIO1, IDC_RADIO2 ) - IDC_RADIO1;
		}


}


BEGIN_MESSAGE_MAP(CDlgCalcTuned, CDialog)
	//{{AFX_MSG_MAP(CDlgCalcTuned)
	ON_EN_CHANGE(IDC_LVALUE, OnChangeLvalue)
	ON_EN_CHANGE(IDC_RVALUE, OnChangeRvalue)
	ON_EN_CHANGE(IDC_CVALUE, OnChangeCvalue)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO2, OnRadio)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgCalcTuned, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgCalcTuned)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgCalcTuned to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {B4D31A40-78D3-11CF-AA04-444553540000}
static const IID IID_IDlgCalcTuned =
{ 0xb4d31a40, 0x78d3, 0x11cf, { 0xaa, 0x4, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgCalcTuned, CDialog)
	INTERFACE_PART(CDlgCalcTuned, IID_IDlgCalcTuned, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcTuned message handlers

BOOL CDlgCalcTuned::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[4] = { 
							{IDC_CVALUE, IDC_SPIN2, 0.0f, 199000.0f, &m_fCValue},
							{IDC_LVALUE, IDC_SPIN1, 0.0f, 199000.0f, &m_fLValue},
							{IDC_RVALUE, IDC_SPIN3, 0.0f, 199000.0f, &m_fRValue},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CDialog::OnInitDialog();
	
	{
	CALCTUNED clc;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		if ( ! capp->ReadRegistry( IDS_CALCTUNEDINFO, &clc, sizeof(clc)))
			{
			m_fCValue = clc.fCValue;
			m_fLValue = clc.fLValue;
			m_fRValue = clc.fRValue;
			m_nType = clc.nType;
			}
	}
	
	
	UpdateData( FALSE);
	CalculateVariables();	

	if ( g_wpWindowPlace.length == sizeof( g_wpWindowPlace))		// it's not empty, set back there
		SetWindowPlacement( &g_wpWindowPlace);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCalcTuned::CalculateVariables()
{
float fres = 100.0f;		// some random value
float fq;

	if ( m_fCValue && m_fLValue)
		fres = (float )(1.0f / (2 * ONEPI * sqrt( m_fCValue * m_fLValue)));

	if ( m_nType)			// parallel
		{
		if ( m_fLValue)
			{
			fq = m_fRValue * (float )sqrt( m_fCValue / m_fLValue);
			}
		else
			{
			fq = 0.0f;
			}
		}
	else
		{
		if ( m_fRValue && m_fCValue)
			{
			fq = (float )sqrt( m_fLValue / m_fCValue) / m_fRValue;
			}
		else
			{
			fq = 0.0f;
			}
		}

	m_csFreq.Format("%f", fres);
	m_csQ.Format("%f", fq);

	UpdateData( FALSE);
}

void CDlgCalcTuned::OnChangeLvalue() 
{
	if (  VerboseUpdateData( TRUE))	
		CalculateVariables();	
}

void CDlgCalcTuned::OnChangeRvalue() 
{
	if (  VerboseUpdateData( TRUE))	
		CalculateVariables();	
}

void CDlgCalcTuned::OnChangeCvalue() 
{
	if (  VerboseUpdateData( TRUE))	
		CalculateVariables();	
}

void CDlgCalcTuned::OnRadio() 
{
	if (  VerboseUpdateData( TRUE))
		CalculateVariables();	
}

void CDlgCalcTuned::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

void CDlgCalcTuned::OnClose() 
{
	if (  ! VerboseUpdateData( TRUE))
		return;

	{
	CALCTUNED clc;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		clc.fCValue = m_fCValue;
		clc.fRValue = m_fRValue;
		clc.fLValue = m_fLValue;
		clc.nType = m_nType;

		capp->WriteRegistry( IDS_CALCTUNEDINFO, &clc, sizeof(clc));
	}

	g_wpWindowPlace.length = sizeof( g_wpWindowPlace);
	GetWindowPlacement( & g_wpWindowPlace);

	CDialog::OnClose();		// although the doc says this does a destroy, apparently it doesn't for modeless guys

	DestroyWindow();
}

void CDlgCalcTuned::PostNcDestroy() 
{

	CDialog::PostNcDestroy();

	m_bIsShowing = false;

	delete this;			// per microsoft, kill us here
	
}
