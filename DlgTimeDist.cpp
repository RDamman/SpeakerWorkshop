// DlgTimeDist.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "zFormEdt.h"
#include "math.h"

#include "DlgTimeDist.h"

#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTimeDist dialog

typedef struct tagCALCPASSIVE
	{
	float	fTemp;
	float	fDistance;
	float	fTime;
	float	fFreq;
	} TIMEDIST;


bool CDlgTimeDist::m_bIsShowing = false;			// is it showing????
static WINDOWPLACEMENT g_wpWindowPlace = {0,0};


// -------------------------------------------------------------------------
// -------------------------------------------------------------------------

CDlgTimeDist::CDlgTimeDist(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTimeDist::IDD, pParent), m_cfEdits()
{
	//{{AFX_DATA_INIT(CDlgTimeDist)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bIsShowing = true;			// we have it now
}


// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
void CDlgTimeDist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgTimeDist)
	DDX_Control(pDX, IDC_STDIST, m_czDist);
	DDX_Control(pDX, IDC_UNITS, m_czUnits);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTimeDist, CDialog)
	//{{AFX_MSG_MAP(CDlgTimeDist)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin)
	ON_EN_CHANGE(IDC_TIME, OnChangeTime)
	ON_EN_CHANGE(IDC_DISTANCE, OnChangeDistance)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_AIRTEMP, OnChangeAirtemp)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_EN_CHANGE(IDC_FREQ, OnChangeFreq)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTimeDist message handlers

BOOL CDlgTimeDist::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[5] = { 
							{IDC_AIRTEMP,	IDC_SPIN1, -10000.0f, 1000.0f, &m_fAirTemp},
							{IDC_DISTANCE,	IDC_SPIN2, 0.0f, 199000.0f, &m_fDistance},
							{IDC_TIME,	IDC_SPIN3, 0.0f, 199000.0f, &m_fTime},
							{IDC_FREQ,	IDC_SPIN4, 0.0f, 199000.0f, &m_fFreq},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	GroupMetric cfgrp[3] = {
						  { IDC_DISTANCE,	IDC_STDIST,		mtMeter },
						  { IDC_AIRTEMP,	IDC_UNITS,		mtCelsius },
						  { 0, 0, mtNone }
						  };
		m_cfEdits.AttachMetrics( cfgrp);
	}

	CDialog::OnInitDialog();

	{
	TIMEDIST clc;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		if ( ! capp->ReadRegistry( IDS_TIMEDISTINFO, &clc, sizeof(clc)))
			{
			m_fDistance = clc.fDistance;
			m_fTime = clc.fTime;
			m_fAirTemp = clc.fTemp;
			m_fFreq = clc.fFreq;
			}
		else
			{
			m_fDistance = .001f;
			m_fTime = 1000.0f;
			m_fAirTemp = 20.0;
			m_fFreq = 1000.0f;
			}
	}
	
	UpdateData( FALSE);
	recalc_Values( true);

	if ( g_wpWindowPlace.length == sizeof( g_wpWindowPlace))		// it's not empty, set back there
		SetWindowPlacement( &g_wpWindowPlace);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
void CDlgTimeDist::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

// -------------------------------------------------------------------------
//		Speed of sound ==
// -------------------------------------------------------------------------
void CDlgTimeDist::recalc_Values(bool bTime)
{
double dspeed;

	dspeed = sqrt( m_fAirTemp + 271.3);		// kelvin temperature
				// speed at 0C == 331.5m/s so constant is 331.5/sqrt(271.3)
	dspeed *= (.3315 / sqrt( 271.3));		// put it in meters/ms

	if ( bTime)
	{
		m_fTime = (float )(m_fDistance / dspeed);		// in meter / celsius
	}
	else
	{
		m_fDistance = (float )(m_fTime * dspeed);	// time is in ms
	}

	m_fFreq = 1000.0f / m_fTime;

	UpdateData( FALSE);
}


// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
void CDlgTimeDist::OnChangeTime() 
{
	if ( GetDlgItem( IDC_TIME) == GetFocus())
	{
		if ( VerboseUpdateData( TRUE))
			recalc_Values( false);	
	}
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
void CDlgTimeDist::OnChangeDistance() 
{
	if ( GetDlgItem( IDC_DISTANCE) == GetFocus())
	{
		if ( VerboseUpdateData( TRUE))
			recalc_Values( true);	
	}
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
void CDlgTimeDist::OnChangeAirtemp() 
{
	if ( GetDlgItem( IDC_AIRTEMP) == GetFocus())
	{
		if ( VerboseUpdateData( TRUE))
			recalc_Values( true);	
	}
}

void CDlgTimeDist::OnChangeFreq() 
{
	if ( GetDlgItem( IDC_FREQ) == GetFocus())
	{
		if ( VerboseUpdateData( TRUE))
		{
			m_fTime = 1000.0f / m_fFreq;			// freq and time are allied
			recalc_Values( false);					// as if time changed
		}
	}	
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
void CDlgTimeDist::OnClose() 
{
	if (! VerboseUpdateData( TRUE))
		return;

	{
	TIMEDIST clc;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		clc.fTemp = m_fAirTemp;
		clc.fDistance = m_fDistance;
		clc.fTime = m_fTime;
		clc.fFreq = m_fFreq;

		capp->WriteRegistry( IDS_TIMEDISTINFO, &clc, sizeof(clc));
	}
	

	g_wpWindowPlace.length = sizeof( g_wpWindowPlace);
	GetWindowPlacement( & g_wpWindowPlace);

	CDialog::OnClose();

	DestroyWindow();
}


// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
void CDlgTimeDist::PostNcDestroy() 
{
	
	CDialog::PostNcDestroy();
	
	m_bIsShowing = false;

	delete this;			// per microsoft, kill us here

}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
void CDlgTimeDist::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! m_cfEdits.ProcessLeftClick( nFlags, point))
		CDialog::OnLButtonUp(nFlags, point);
}

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
void CDlgTimeDist::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! 	m_cfEdits.ProcessRightClick( nFlags, point))
		CDialog::OnRButtonUp(nFlags, point);
}


