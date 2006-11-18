// dlgdrpar.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgdrpar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDrParms property page

IMPLEMENT_DYNCREATE(CDlgDrParms, CPropertyPage)

CDlgDrParms::CDlgDrParms() : CPropertyPage(CDlgDrParms::IDD), m_cfEdits()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgDrParms)
	//}}AFX_DATA_INIT
}

CDlgDrParms::~CDlgDrParms()
{
}

void CDlgDrParms::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgDrParms::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgDrParms)
	DDX_Control(pDX, IDC_STATVAS, m_czStatVas);
	DDX_Control(pDX, IDC_STATMAX, m_czStatMax);
	DDX_Control(pDX, IDC_STATDIAM, m_czStatDiam);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDrParms, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgDrParms)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC1, OnDeltaposAll)
	ON_WM_LBUTTONUP()
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC2, OnDeltaposAll)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC3, OnDeltaposAll)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC4, OnDeltaposAll)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC5, OnDeltaposAll)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC6, OnDeltaposAll)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC7, OnDeltaposAll)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC8, OnDeltaposAll)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC9, OnDeltaposAll)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC10, OnDeltaposAll)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC11, OnDeltaposAll)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC12, OnDeltaposAll)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC13, OnDeltaposAll)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC14, OnDeltaposAll)
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgDrParms, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgDrParms)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDrParms message handlers


// use the argument to generate parameters for the dbox
void CDlgDrParms::UseParms( CDriver *pcDriver)
{
	{
	DRIVEPARM dp;

		dp = *pcDriver->GetDriverParameters();

		m_fRe = dp.fRe;
		m_fDiameter = dp.fPistonArea;
		m_fFs = dp.fFs;
		m_fLe = dp.fLe;
		m_fQes = dp.fQes;
		m_fQms = dp.fQms;
		m_fQts = dp.fQts;
		m_fVas = dp.fVas * 1000;				// put m_fVas in litres
		m_fXmax = dp.fXmax;
		m_fBL = dp.fBL;
		m_fPe = dp.fPe;
		m_fSense = dp.fSensitivity;
	}

	{
	DRIVEEQUIV de;

		de = *pcDriver->GetDriverEquiv();
		m_fL1 = (float )de.fL1a;
		m_fR1 = (float )de.fR1;
	}

}


void CDlgDrParms::SetParms( CDriver *pcDriver)
{
	{
	DRIVEPARM dp;

		dp = *pcDriver->GetDriverParameters();		// put in any parms we don't edit

		dp.fRe = m_fRe;
		dp.fPistonArea = m_fDiameter;
		dp.fFs = m_fFs;
		dp.fLe = m_fLe;
		dp.fQes = m_fQes;
		dp.fQms = m_fQms;
		dp.fQts = m_fQts;
		dp.fVas = m_fVas / 1000;			// convert m_fVas to m**3
		dp.fXmax = m_fXmax;
		dp.fBL = m_fBL;
		dp.fPe = m_fPe;
		dp.fSensitivity = m_fSense;

		pcDriver->SetDriverParameters( &dp);
	}

	{
	DRIVEEQUIV de;

		de = *pcDriver->GetDriverEquiv();
		de.fL1a = m_fL1;
		de.fR1 = m_fR1;
		pcDriver->SetDriverEquiv( &de);
	}

}


BOOL CDlgDrParms::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[15] = { 
							{IDC_XMAX,		IDC_GENERIC1, 0.0f, 1000.0f,	&m_fXmax},
							{IDC_BL,		IDC_GENERIC2, 0.0f, 1000000.0f, &m_fBL},
							{IDC_PE,		IDC_GENERIC3, 0.0f, 1000000.0f, &m_fPe},
							{IDC_SENSE,		IDC_GENERIC4, 0.0f, 10000.0f,	&m_fSense},
							{IDC_DIAMETER,	IDC_GENERIC5, 0.0f, 1000.0f,	&m_fDiameter},
							{IDC_DCRES,		IDC_GENERIC6, 0.0f, 1000.0f,	&m_fRe},
							{IDC_QMS,		IDC_GENERIC7, 0.0f, 1000.0f,	&m_fQms},
							{IDC_QES,		IDC_GENERIC8, 0.0f, 1000.0f,	&m_fQes},
							{IDC_QTS,		IDC_GENERIC9, 0.0f, 1000.0f,	&m_fQts},
							{IDC_VAS,		IDC_GENERIC10, 0.0f, 10000.0f,	&m_fVas},
							{IDC_LE,		IDC_GENERIC11, 0.0f, 1000.0f,	&m_fLe},
							{IDC_L1,		IDC_GENERIC12, 0.0f, 10.0f,		&m_fL1},
							{IDC_R1,		IDC_GENERIC13, 0.0f, 100.0f,	&m_fR1},
							{IDC_FS,		IDC_GENERIC14, 0.0f, 100000.0f, &m_fFs},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);

	GroupMetric cfgrp[4] = {
						  { IDC_XMAX,		IDC_STATMAX,	mtCm },
						  { IDC_DIAMETER,	IDC_STATDIAM,	mtSqMeter },
						  { IDC_VAS,		IDC_STATVAS,	mtLitre },
						  { 0, 0, mtNone }
						  };
		m_cfEdits.AttachMetrics( cfgrp);
	}

	CPropertyPage::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgDrParms::OnDeltaposAll(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	
	*pResult = 0;
}

void CDlgDrParms::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! m_cfEdits.ProcessLeftClick( nFlags, point))
		CPropertyPage::OnLButtonUp(nFlags, point);
}

void CDlgDrParms::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! 	m_cfEdits.ProcessRightClick( nFlags, point))
		CPropertyPage::OnRButtonUp(nFlags, point);
}
