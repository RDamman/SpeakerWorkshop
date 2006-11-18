// dlgenpar.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgenpar.h"

#include "Enclosur.h"
#include "dlgSelec.h"
#include "dlgEnclo.h"

#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEnParms property page

IMPLEMENT_DYNCREATE(CDlgEnParms, CPropertyPage)

CDlgEnParms::CDlgEnParms( UINT uIDCap) : CPropertyPage(CDlgEnParms::IDD, uIDCap), m_cfEdits()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgEnParms)
	m_bIsRect = FALSE;
	m_bUsePort = FALSE;
	m_bUseChamber = FALSE;
	m_csDriver = _T("");
	m_nDrivers = 0;
	m_iSeriesPar = -1;
	m_uPort = 0;
	//}}AFX_DATA_INIT

	m_nWho = ( (uIDCap == IDS_CHAMBER1) ? 1 : 2 );	// who am i??? based on caption

}

CDlgEnParms::~CDlgEnParms()
{
}

void CDlgEnParms::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgEnParms::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgEnParms)
	DDX_Control(pDX, IDC_STATWIDTH, m_czStatWidth);
	DDX_Control(pDX, IDC_STATVOLUME, m_czStatVolume);
	DDX_Control(pDX, IDC_STATRADIUS, m_czStatRadius);
	DDX_Control(pDX, IDC_STATLENGTH, m_czStatLength);
	DDX_Control(pDX, IDC_STATHEIGHT, m_czStatHeight);
	DDX_Check(pDX, IDC_ISRECT, m_bIsRect);
	DDX_Check(pDX, IDC_USEPORT, m_bUsePort);
	DDX_Check(pDX, IDC_USECHAMBER, m_bUseChamber);
	DDX_Text(pDX, IDC_DRIVER, m_csDriver);
	DDX_Text(pDX, IDC_NUMDRIVER, m_nDrivers);
	DDX_CBIndex(pDX, IDC_SERIESPAR, m_iSeriesPar);
	DDX_Text(pDX, IDC_NUMPORT, m_uPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEnParms, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgEnParms)
	ON_BN_CLICKED(IDC_HITDRIVER, OnHitdriver)
	ON_EN_CHANGE(IDC_PHEIGHT, OnChange)
	ON_BN_CLICKED(IDC_USECHAMBER, OnUsechamber)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC1, OnDeltaposSpin)
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_HITNONE, OnHitnone)
	ON_BN_CLICKED(IDC_USEPORT, OnUsechamber)
	ON_BN_CLICKED(IDC_ISRECT, OnUsechamber)
	ON_EN_CHANGE(IDC_PRADIUS, OnChange)
	ON_EN_CHANGE(IDC_PLENGTH, OnChange)
	ON_EN_CHANGE(IDC_PWIDTH, OnChange)
	ON_EN_CHANGE(IDC_QA, OnChange)
	ON_EN_CHANGE(IDC_QL, OnChange)
	ON_EN_CHANGE(IDC_QP, OnChange)
	ON_EN_CHANGE(IDC_VOLUME, OnChange)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC2, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC3, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC4, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC5, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC6, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC7, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC8, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC9, OnDeltaposSpin)
	ON_CBN_SELCHANGE(IDC_SERIESPAR, OnChange)
	ON_EN_CHANGE(IDC_NUMDRIVER, OnChange)
	ON_EN_CHANGE(IDC_NUMPORT, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgEnParms, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgEnParms)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEnParms message handlers

static void disable_Wnds( CPropertyPage *cProp, UINT *pUid, BOOL bHow)
{
short i;
CWnd *cwnd;

	for ( i=0; pUid[i]; i++)
		{
		cwnd = cProp->GetDlgItem( pUid[i]);
		if ( cwnd && cwnd->GetSafeHwnd())
			cwnd->EnableWindow( ! bHow);
		}
}

static void disable_All( CPropertyPage *cProp, BOOL bHow, BOOL bUsePort, BOOL bUseRect)
{
UINT uids[10] = { IDC_HITDRIVER, IDC_HITNONE, IDC_QA, IDC_QL, IDC_VOLUME, IDC_USEPORT, IDC_DRIVER, IDC_SERIESRES, IDC_NUMDRIVER, 0 };
UINT uidport[4] = { IDC_PLENGTH, IDC_QP, IDC_ISRECT, 0 };
UINT uidrect[3] = { IDC_PHEIGHT, IDC_PWIDTH, 0 };
UINT uidcirc[2] = { IDC_PRADIUS, 0 };

	disable_Wnds( cProp, uids, bHow);
	disable_Wnds( cProp, uidport, bHow || !bUsePort);
	disable_Wnds( cProp, uidrect, bHow || (!bUsePort) || ! bUseRect);
	disable_Wnds( cProp, uidcirc, bHow || (!bUsePort) || bUseRect);

}


// prepare for the dialog box to be invoked by using the object
// note this could be a different object from the setobject call
void CDlgEnParms::UseObject( CEnclosure * cWho)
{
CHAMBER *pch;

	pch = cWho->GetChamber( m_nWho);

	m_cRoot = (CFolder *)cWho->GetRootObject();

	m_bIsRect = !pch->bPIsCircle; 
	m_bUsePort = pch->bUsePort;
	m_fVolume =  pch->fVolume * 1000;	// store in meters and cubic meters 
	m_fPHeight = pch->fPHeight * 100;	// show in cm
	m_fPWidth =  pch->fPWidth * 100;	// show in cm
	m_fPRadius = pch->fPRadius * 100;	// show in cm
	m_fPLength = pch->fPLength * 100;	// show in cm
	m_fQa =      pch->fQDamp; 
	m_fQl =      pch->fQLeak; 
	m_fQp =      pch->fQPort; 
	m_dwDriver = pch->dwDriver;
	m_bUseChamber = pch->bUseChamber;
	m_fSeriesRes = pch->fSeriesRes;
	m_csDriver = "";
	m_nDrivers = pch->wDrivers;			// number of drivers
	m_uPort		=pch->wPorts;
	m_iSeriesPar=pch->bParallel ? 0 : 1;
	if ( m_dwDriver)
		{
		CNamed *cnam = m_cRoot->GetItem( m_dwDriver);
		if ( cnam)
			m_csDriver = cnam->GetFullName();
		}


}

// use the dialog box data to set the object
void CDlgEnParms::SetObject( CEnclosure * cWho)
{
CHAMBER *pch;

	if ( GetSafeHwnd())
		if (! UpdateData( TRUE))		// we can't update data without an hwnd
			return;

	pch = cWho->GetChamber( m_nWho);

	pch->bPIsCircle = ! m_bIsRect;
	pch->bUsePort = 	0 != m_bUsePort;
	pch->fVolume = 		m_fVolume / 1000;		// put fVolume in m**3
	pch->fPHeight = 	m_fPHeight / 100;		// put pheight in m
	pch->fPWidth = 		m_fPWidth  / 100;		// pupt pwdith in m
	pch->fPRadius = 	m_fPRadius / 100;		// put pradius in m
	pch->fPLength = 	m_fPLength / 100;		// put plength in m
	pch->fQDamp = 		m_fQa;
	pch->fQLeak = 		m_fQl;
	pch->fQPort = 		m_fQp;
	pch->dwDriver = 	m_dwDriver;
	pch->bUseChamber =	0 != m_bUseChamber;
	pch->fSeriesRes = 	m_fSeriesRes;
	pch->wDrivers =		(WORD )m_nDrivers;		// number of drivers
	pch->wPorts =		(WORD )m_uPort;
	pch->bParallel =	m_iSeriesPar == 0;

	SetModified( FALSE);	


}

void CDlgEnParms::UpdateDriverName() 
{
CWnd *pwnd = GetDlgItem( IDC_DRIVER);

	if ( pwnd && pwnd->GetSafeHwnd())
	{
		Invalidate( TRUE);		// invalidate the entire dbox to redraw the text field
	}
}


void CDlgEnParms::OnHitdriver() 
{
		// TODO: Add your control notification handler code here
CDlgSelectObject cdlg;

	cdlg.SetParms( m_cRoot, m_dwDriver, ntDriver);

	if ( IDOK == cdlg.DoModal())
		{
		m_dwDriver = cdlg.m_dwSelected;
		m_csDriver = "";
		if ( cdlg.m_dwSelected)
			{
			CNamed *cnam = m_cRoot->GetItem( cdlg.m_dwSelected);
			if ( cnam)
				m_csDriver = cnam->GetFullName();
			}
		UpdateData( FALSE);
		UpdateDriverName();
		SetModified( TRUE);
		}
	
}

// almost everyone calls this on a change
void CDlgEnParms::OnChange() 
{

	SetModified( TRUE);	
	
}


BOOL CDlgEnParms::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[10] = { 
							{IDC_PHEIGHT,	IDC_GENERIC7, 0.0f, 1000.0f, &m_fPHeight},
							{IDC_PLENGTH,	IDC_GENERIC4, 0.0f, 1000.0f, &m_fPLength},
							{IDC_PRADIUS,	IDC_GENERIC6, 0.0f, 1000.0f, &m_fPRadius},
							{IDC_PWIDTH,	IDC_GENERIC8, 0.0f, 1000.0f, &m_fPWidth},
							{IDC_QA,		IDC_GENERIC3, 0.0f, 1000.0f, &m_fQa},
							{IDC_QL,		IDC_GENERIC2, 0.0f, 1000.0f, &m_fQl},
							{IDC_QP,		IDC_GENERIC5, 0.0f, 1000.0f, &m_fQp},
							{IDC_VOLUME,	IDC_GENERIC1, 0.0f, 1000.0f, &m_fVolume},
							{IDC_SERIESRES, IDC_GENERIC9, 0.0f, 1000.0f, &m_fSeriesRes},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);

	GroupMetric cfgrp[6] = {
						  { IDC_PHEIGHT, IDC_STATHEIGHT, mtCm },
						  { IDC_PLENGTH, IDC_STATLENGTH, mtCm },
						  { IDC_PRADIUS, IDC_STATRADIUS, mtCm },
						  { IDC_PWIDTH, IDC_STATWIDTH, mtCm },
						  { IDC_VOLUME, IDC_STATVOLUME, mtLitre },
						  { 0, 0, mtNone }
						  };
		m_cfEdits.AttachMetrics( cfgrp);
	}

	CPropertyPage::OnInitDialog();

	SpinSetRange( this, IDC_SPINNUM, 1, 10);
	SpinSetRange( this, IDC_SPINPORT, 1, 10);

	if ( 1 == m_nWho)					// chamber 1
		{
		CWnd *cwnd;

			cwnd = GetDlgItem( IDC_USECHAMBER);
			if ( cwnd)
				cwnd->ShowWindow( SW_HIDE);		// hide the checkbox
		}

	::ComboFillString( this, IDC_SERIESPAR, IDS_SERIESPAR);

	disable_All( this, !m_bUseChamber, m_bUsePort, m_bIsRect);

	{								// set the group box text
	CString cs;

		cs.LoadString( (1 == m_nWho) ? IDS_DRIVETOAIR : IDS_DRIVETOCH1);

	SetDlgItemText( IDC_DRVRGROUP, cs);
	}

	UpdateData( FALSE);			// update the dialog box data
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEnParms::OnUsechamber() 
{
	// TODO: Add your control notification handler code here
	UpdateData( TRUE);							// get new stuff
	disable_All( this, ! m_bUseChamber, m_bUsePort, m_bIsRect);
	SetModified( TRUE);	
}

BOOL CDlgEnParms::OnApply() 
{
	return CPropertyPage::OnApply();
}

void CDlgEnParms::OnCancel() 
{
	CPropertyPage::OnCancel();
}

void CDlgEnParms::OnOK() 
{
	CPropertyPage::OnOK();
}

void CDlgEnParms::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

void CDlgEnParms::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! m_cfEdits.ProcessRightClick( nFlags, point))
		CPropertyPage::OnRButtonUp(nFlags, point);
}

void CDlgEnParms::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! 	m_cfEdits.ProcessLeftClick( nFlags, point))
		CPropertyPage::OnLButtonUp(nFlags, point);
}

void CDlgEnParms::OnHitnone() 
{
	m_dwDriver = 0;
	m_csDriver = "";
	UpdateData( FALSE);
	UpdateDriverName();
	SetModified( TRUE);
}

