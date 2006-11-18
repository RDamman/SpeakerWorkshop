// DlgVolumeCalc.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "DlgVolumeCalc.h"

#include "Utils.h"
#include "Math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
typedef struct tagCALCVOLUME
	{
	float	fVolume;
	float	fDepth;
	float	fHeight;
	float	fWidth;
	float	fRatio;
	} VOLUMECALC;

// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
bool CDlgVolumeCalc::m_bIsShowing = false;			// is it showing????
static WINDOWPLACEMENT g_wpWindowPlace = {0,0};

/////////////////////////////////////////////////////////////////////////////
// CDlgVolumeCalc dialog
/////////////////////////////////////////////////////////////////////////////


// -------------------------------------------------------------------------
//		CDlgVolumeCalc
// -------------------------------------------------------------------------
CDlgVolumeCalc::CDlgVolumeCalc(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVolumeCalc::IDD, pParent), m_cfEdits()
{
	//{{AFX_DATA_INIT(CDlgVolumeCalc)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bIsShowing = true;			// we have it now
}


// -------------------------------------------------------------------------
//		DoDataExchange
// -------------------------------------------------------------------------
void CDlgVolumeCalc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgVolumeCalc)
	DDX_Control(pDX, IDC_STDWIDTH, m_czStdWidth);
	DDX_Control(pDX, IDC_STDVOLUME, m_czStdVolume);
	DDX_Control(pDX, IDC_STDHEIGHT, m_czStdHeight);
	DDX_Control(pDX, IDC_STDDEPTH, m_czStdDepth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVolumeCalc, CDialog)
	//{{AFX_MSG_MAP(CDlgVolumeCalc)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin)
	ON_EN_CHANGE(IDC_WIDTH, OnChangeWidth)
	ON_EN_CHANGE(IDC_VOLUME, OnChangeVolume)
	ON_EN_CHANGE(IDC_DEPTH, OnChangeDepth)
	ON_EN_CHANGE(IDC_HEIGHT, OnChangeHeight)
	ON_WM_CLOSE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN5, OnDeltaposSpin)
	ON_BN_CLICKED(IDC_USERATIO, OnUseratio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// -------------------------------------------------------------------------
//		recalc_Values
// -------------------------------------------------------------------------
void CDlgVolumeCalc::recalc_Values(bool bCalcVolume)
{
	if ( m_fVolume < .000001f)
		m_fVolume = .000001f;

	if ( bCalcVolume)
	{
		m_fVolume = .000001f * m_fDepth * m_fHeight * m_fWidth;
	}
	else
	{
	float fold = .000001f * m_fDepth * m_fHeight * m_fWidth;
	float fratio = m_fVolume / fold;

		fratio = (float )exp( log( fratio) / 3);
		m_fHeight *= fratio;
		m_fWidth *=fratio;
		m_fDepth = m_fVolume / ( .000001f * m_fHeight * m_fWidth);		// to be exact
	}

	UpdateData( FALSE);
}



/////////////////////////////////////////////////////////////////////////////
// CDlgVolumeCalc message handlers
/////////////////////////////////////////////////////////////////////////////

// -------------------------------------------------------------------------
//		OnInitDialog
// -------------------------------------------------------------------------
BOOL CDlgVolumeCalc::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[6] = { 
							{IDC_VOLUME,	IDC_SPIN4, 0.0f, 19900000.0f, &m_fVolume},
							{IDC_HEIGHT,	IDC_SPIN1, 0.0f, 19900000.0f, &m_fHeight},
							{IDC_WIDTH,		IDC_SPIN2, 0.0f, 19900000.0f, &m_fWidth},
							{IDC_DEPTH,		IDC_SPIN3, 0.0f, 19900000.0f, &m_fDepth},
							{IDC_RATIO,		IDC_SPIN5, 0.0f, 19900000.0f, &m_fRatio},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	GroupMetric cfgrp[5] = {
						  { IDC_VOLUME,	IDC_STDVOLUME,		mtCuMeter },
						  { IDC_HEIGHT,	IDC_STDHEIGHT,		mtCm },
						  { IDC_WIDTH,	IDC_STDWIDTH,		mtCm },
						  { IDC_DEPTH,	IDC_STDDEPTH,		mtCm },
						  { 0, 0, mtNone }
						  };
		m_cfEdits.AttachMetrics( cfgrp);
	}

	CDialog::OnInitDialog();
	
	{
	VOLUMECALC clc;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		if ( ! capp->ReadRegistry( IDS_VOLCALCINFO, &clc, sizeof(clc)))
			{
			m_fVolume = clc.fVolume;
			m_fHeight = clc.fHeight;
			m_fWidth = clc.fWidth;
			m_fDepth = clc.fDepth;
			m_fRatio = clc.fRatio;
			}
		else
			{
			m_fVolume = 1.0f;
			m_fHeight = 1.0f;
			m_fWidth = 1.0f;
			m_fDepth = 1.0f;
			m_fRatio = 1.0f;
			}
	}

	recalc_Values( true);

	UpdateData( FALSE);

	if ( g_wpWindowPlace.length == sizeof( g_wpWindowPlace))		// it's not empty, set back there
		SetWindowPlacement( &g_wpWindowPlace);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// -------------------------------------------------------------------------
//		OnDeltaposSpin
// -------------------------------------------------------------------------
void CDlgVolumeCalc::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}



// -----------------------------------------------------------------------------------------
//		OnChangeVolume,...
// -----------------------------------------------------------------------------------------
void CDlgVolumeCalc::OnChangeVolume() 
{
	if ( GetDlgItem( IDC_VOLUME) == GetFocus())
	{
		if ( VerboseUpdateData( TRUE))
			recalc_Values( false);	
	}
	
}

void CDlgVolumeCalc::OnChangeWidth() 
{
	if ( GetDlgItem( IDC_WIDTH) == GetFocus())
	{
		if ( VerboseUpdateData( TRUE))
			recalc_Values( true);	
	}
	
}

void CDlgVolumeCalc::OnChangeDepth() 
{
	if ( GetDlgItem( IDC_DEPTH) == GetFocus())
	{
		if ( VerboseUpdateData( TRUE))
			recalc_Values( true);	
	}
	
}

void CDlgVolumeCalc::OnChangeHeight() 
{
	if ( GetDlgItem( IDC_HEIGHT) == GetFocus())
	{
		if ( VerboseUpdateData( TRUE))
			recalc_Values( true);	
	}
	
}

// -----------------------------------------------------------------------------------------
//	OnClose
// -----------------------------------------------------------------------------------------
void CDlgVolumeCalc::OnClose() 
{
	if (! VerboseUpdateData( TRUE))
		return;

	{
	VOLUMECALC clc;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		clc.fVolume = m_fVolume;
		clc.fHeight = m_fHeight;
		clc.fWidth  = m_fWidth;
		clc.fDepth  = m_fDepth;
		clc.fRatio  = m_fRatio;

		capp->WriteRegistry( IDS_VOLCALCINFO, &clc, sizeof(clc));
	}
	

	g_wpWindowPlace.length = sizeof( g_wpWindowPlace);
	GetWindowPlacement( & g_wpWindowPlace);

	CDialog::OnClose();

	DestroyWindow();
}


// -----------------------------------------------------------------------------------------
//	PostNcDestroy
// -----------------------------------------------------------------------------------------
void CDlgVolumeCalc::PostNcDestroy() 
{
	
	CDialog::PostNcDestroy();
	
	m_bIsShowing = false;

	delete this;			// per microsoft, kill us here
}

// -----------------------------------------------------------------------------------------
//	OnLButtonUp
// -----------------------------------------------------------------------------------------
void CDlgVolumeCalc::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! m_cfEdits.ProcessLeftClick( nFlags, point))
		CDialog::OnLButtonUp(nFlags, point);
}

// -----------------------------------------------------------------------------------------
//	OnRButtonUp
// -----------------------------------------------------------------------------------------
void CDlgVolumeCalc::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! 	m_cfEdits.ProcessRightClick( nFlags, point))
		CDialog::OnRButtonUp(nFlags, point);
}


// -----------------------------------------------------------------------------------------
//	OnUseRatio
// -----------------------------------------------------------------------------------------
void CDlgVolumeCalc::OnUseratio() 
{
float ftotal, fratio;

	if ( VerboseUpdateData( TRUE))
	{
		m_fHeight = 1.0f;
		m_fWidth = m_fRatio;
		m_fDepth = m_fRatio * m_fRatio;
		ftotal = .000001f * m_fDepth * m_fHeight * m_fWidth;
		fratio = m_fVolume / ftotal;
		fratio = (float )exp( log( fratio) / 3);		// cube root it

		m_fHeight *= fratio;
		m_fWidth *= fratio;
		m_fDepth *= fratio;

		recalc_Values( true);	
	}
	
}
