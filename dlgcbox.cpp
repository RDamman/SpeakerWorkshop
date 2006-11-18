// dlgcbox.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"


#include "zFormEdt.h"
#include "dlgcbox.h"

#include "Enclosur.h"
#include "Driver.h"

#include "Utils.h"

#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// index of custom for sealed box
#define SEALED_CUSTOM 4

typedef enum tagAlignment
{
	alBB4 = 0,
	alC4 = 1,
	alQB3 = 2,
	alCustom = 3
} ALIGNMENTS;


/////////////////////////////////////////////////////////////////////////////
// CDlgCalcBase dialog


CDlgCalcBase::CDlgCalcBase(UINT uID, CWnd* pParent /*=NULL*/)
	: CDialog(uID, pParent), m_cfEdits()
{
	//{{AFX_DATA_INIT(CDlgCalcBase)
	//}}AFX_DATA_INIT

}

CDlgCalcBase::~CDlgCalcBase()
{
	if ( m_cOriginal)
		((CEnclosure *)m_cOriginal)->DeleteTrialData();

}


BEGIN_MESSAGE_MAP(CDlgCalcBase, CDialog)
	//{{AFX_MSG_MAP(CDlgCalcBase)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgCalcBase, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgCalcBase)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------------------------
// -----------		InitDlg
// --------------------------------------------------------------------------

void CDlgCalcBase::UseObject( CFolder *cRoot, CObject *cDest)
{
	m_cRoot = cRoot;
	m_cDest = cDest;
	m_cOriginal  = cDest;			// keep this for later
	((CEnclosure *)m_cOriginal)->BuildTrialData();
	InitDlg();
}

// --------------------------------------------------------------------------
// -----------		InitDlg
// --------------------------------------------------------------------------

void CDlgCalcBase::SetObject( CFolder *cRoot, CObject *cDest)
{
	m_cRoot = cRoot;
	m_cDest = cDest;
	OkDlg();
	((CEnclosure *)m_cOriginal)->SetNewProperties( (CNamed *)cDest);
}


// --------------------------------------------------------------------------
// -----------		InitDlg
// --------------------------------------------------------------------------

void CDlgCalcBase::InitDlg(void )
{
	ASSERT(0);
}


// --------------------------------------------------------------------------
// -----------		OkDlg
// --------------------------------------------------------------------------

void CDlgCalcBase::OkDlg( void)
{
	ASSERT(0);
}

// --------------------------------------------------------------------------
// -----------		CalculateVariables
// --------------------------------------------------------------------------

void CDlgCalcBase::CalculateVariables( void)
{
		ASSERT(0);			// not me....
}

	


/////////////////////////////////////////////////////////////////////////////
// CDlgCalcSealed dialog

typedef struct tagCalcSealed
	{
	float	fQts;			// total Q
	int		nAlignment;		// alignment
	float	fSeriesRes;		// series resistance
	int		uDrivers;		// # of drivers
	int		iSeries;		// series or parallel
	} CALCSEALED;


CDlgCalcSealed::CDlgCalcSealed(CWnd* pParent /*=NULL*/)
	: CDlgCalcBase(CDlgCalcSealed::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgCalcSealed)
	m_nAlignment = -1;
	m_uDriver = 0;
	m_iSeries = -1;
	//}}AFX_DATA_INIT
}


void CDlgCalcSealed::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgCalcSealed::DoDataExchange(CDataExchange* pDX)
{
	CDlgCalcBase::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgCalcSealed)
	DDX_Control(pDX, IDC_VOLUNIT, m_czVolUnit);
	DDX_CBIndex(pDX, IDC_ALIGNMENT, m_nAlignment);
	DDX_Text(pDX, IDC_NUMDRIVER, m_uDriver);
	DDX_CBIndex(pDX, IDC_SERIESPAR, m_iSeries);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalcSealed, CDlgCalcBase)
	//{{AFX_MSG_MAP(CDlgCalcSealed)
	ON_CBN_SELCHANGE(IDC_ALIGNMENT, OnSelchangeAlignment)
	ON_EN_CHANGE(IDC_QTS, OnChangeQts)
	ON_EN_CHANGE(IDC_SERIESRES, OnChangeSeriesres)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC1, OnDeltaposSpin)
	ON_BN_CLICKED(IDC_COMPARE, OnCompare)
	ON_EN_CHANGE(IDC_NUMDRIVER, OnChangeNumdriver)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC2, OnDeltaposSpin)
	ON_CBN_SELCHANGE(IDC_SERIESPAR, OnSelchangeSeries)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgCalcSealed, CDlgCalcBase)
	//{{AFX_DISPATCH_MAP(CDlgCalcSealed)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcSealed message handlers
/////////////////////////////////////////////////////////////////////////////

// InitDialog
BOOL CDlgCalcSealed::OnInitDialog() 
{
	{		// initialize the spinner format group
		FormatGroup cfdata[6] = { 
							{IDC_QTS,	IDC_GENERIC1, 0.0f, 10.0f, &m_fQts},
							{IDC_SERIESRES,	IDC_GENERIC2, 0.0f, 1000.0f, &m_fSeriesRes},
							{IDC_F3,	0, 0.0f, 10000.0f, &m_fF3},
							{IDC_FS,	0, 0.0f, 10000.0f, &m_fFs},
							{IDC_VB,	0, 0.0f, 10000.0f, &m_fVb},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);

		GroupMetric cfgrp[2] = {
						  { IDC_VB,		 IDC_VOLUNIT,	mtLitre },
						  { 0, 0, mtNone }
						  };
		m_cfEdits.AttachMetrics( cfgrp);
	}
	

	CDlgCalcBase::OnInitDialog();

	::ComboFillString( this, IDC_ALIGNMENT, IDS_CALCS_ALIGNMENT);

	{
	CComboBox *pcombo = (CComboBox *)GetDlgItem( IDC_SERIESPAR);	// get series parallel box

		if ( pcombo && pcombo->GetSafeHwnd())
			pcombo->EnableWindow( 1 != m_uDriver);
	}

	UpdateData( FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// onDeltaPos
void CDlgCalcSealed::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

// --------------------------------------------------------------------------
// -----------		InitDlg
// --------------------------------------------------------------------------


void CDlgCalcSealed::InitDlg(void )
{
CEnclosure *ce = (CEnclosure *)GetDest();
CHAMBER *ch;

					// make it a sealed box by turning off chamber 2 and port 1
	ch = ce->GetChamber( 2);
	ch->bUseChamber = FALSE;
	ch = ce->GetChamber( 1);
	ch->bUsePort = FALSE;

	m_nAlignment = 0;
	m_fQts = 0.7f;
	m_fSeriesRes = 0.0f;
	m_uDriver = 1;
	m_iSeries = 0;

	{
	CALCSEALED clc;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		if ( ! capp->ReadRegistry( IDS_SEALEDINFO, &clc, sizeof(clc)))
			{
			m_nAlignment = clc.nAlignment;
			m_fQts = clc.fQts;
			m_fSeriesRes = clc.fSeriesRes;
			m_iSeries = clc.iSeries;
			m_uDriver = clc.uDrivers;
			}
	}

	CalculateVariables();


}


// --------------------------------------------------------------------------
// -----------		OnOK
// --------------------------------------------------------------------------

void CDlgCalcSealed::OnOK() 
{
	if (! VerboseUpdateData( TRUE))
		return;

	CalculateVariables();
	
	CDlgCalcBase::OnOK();
}

// --------------------------------------------------------------------------
// -----------		OkDlg
// --------------------------------------------------------------------------

void CDlgCalcSealed::set_Enclosure( CEnclosure *pDest)
{
CHAMBER *ch;

					// make it a sealed box by turning off chamber 2 and port 1
	ch = pDest->GetChamber( 2);
	ch->bUseChamber = FALSE;

	ch = pDest->GetChamber( 1);
	ch->bUsePort = FALSE;
					// now transfer the design parameters
//	if ( 1 == sscanf( (LPCSTR )m_csVb, "%f", &ch->fVolume))
//		ch->fVolume /= 1000;				// rescale
	ch->fVolume = m_fVb / 1000;
	ch->fSeriesRes = m_fSeriesRes;
	ch->wDrivers = (WORD )m_uDriver;
	ch->bParallel = (m_iSeries == 0);

}


void CDlgCalcSealed::OkDlg( void)
{
CEnclosure *ce = (CEnclosure *)GetDest();

	set_Enclosure( ce);

	{
	CALCSEALED clc;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		clc.nAlignment = m_nAlignment;
		clc.fQts = m_fQts;
		clc.fSeriesRes = m_fSeriesRes;
		clc.iSeries = m_iSeries;
		clc.uDrivers = m_uDriver;
		capp->WriteRegistry( IDS_SEALEDINFO, &clc, sizeof(clc));
	}

}

// --------------------------------------------------------------------------
// -----------		CalculateVariables
// --------------------------------------------------------------------------

void CDlgCalcSealed::CalculateVariables( void)
{
CEnclosure *ce = (CEnclosure *)GetDest();
// CHAMBER *ch = ce->GetChamber( 1);
CDriver *cdrive = (CDriver *)ce->FindByID( ce->GetDriver(1));
double driverq;


	if ( ntDriver != cdrive->GetType())
		return;

const DRIVEPARM	*dp = cdrive->GetDriverParameters();

	if ( m_fQts < .05)
		return;			// nothing to do here

	{
	float fseries = m_fSeriesRes;

	if ( m_uDriver > 1)			// more than one driver
	{
		if ( m_iSeries == 0)	// parallel
			fseries *= m_uDriver;
		else
			fseries /= m_uDriver;	// here's the change for more than one driver
	}

						// use the series resistance in Qnew = Qold(Re + fSeries)/Re
	driverq = dp->fQts * ( dp->fRe + fseries) / dp->fRe;
	}

double dAlpha = (m_fQts / driverq) * (m_fQts / driverq) - 1;
double dtemp;
double dfc;


	dtemp = (dp->fVas * m_uDriver / dAlpha);
	m_fVb = (float )(1000 * dtemp);
	dtemp = (dp->fFs * m_fQts / driverq);
	m_fFs = (float )dtemp;
	dfc = dtemp;								// Fc
	dtemp = -2 + 1/(m_fQts * m_fQts);
	dtemp = sqrt( (dtemp + sqrt(dtemp*dtemp+4)) / 2) * dfc;
	m_fF3 = (float )dtemp;

}

	



/////////////////////////////////////////////////////////////////////////////
// CDlgCalcBandAir dialog


CDlgCalcBandAir::CDlgCalcBandAir(CWnd* pParent /*=NULL*/)
	: CDlgCalcBase(CDlgCalcBandAir::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgCalcBandAir)
	m_nAlignment = -1;
	m_csF3 = _T("");
	m_csFs = _T("");
	m_csPlength = _T("");
	m_csPlength2 = _T("");
	m_csPortUnit = _T("");
	m_csPortUnit2 = _T("");
	m_csVb = _T("");
	m_csVb2 = _T("");
	m_csVolUnit2 = _T("");
	m_csVolUnit = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCalcBandAir::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgCalcBandAir::DoDataExchange(CDataExchange* pDX)
{
	CDlgCalcBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalcBandAir)
	DDX_CBIndex(pDX, IDC_ALIGNMENT, m_nAlignment);
	DDX_Text(pDX, IDC_F3, m_csF3);
	DDX_Text(pDX, IDC_FS, m_csFs);
	DDX_Text(pDX, IDC_PLENGTH, m_csPlength);
	DDX_Text(pDX, IDC_PLENGTH2, m_csPlength2);
	DDX_Text(pDX, IDC_PORTUNIT, m_csPortUnit);
	DDX_Text(pDX, IDC_PORTUNIT2, m_csPortUnit2);
	DDX_Text(pDX, IDC_VB, m_csVb);
	DDX_Text(pDX, IDC_VB2, m_csVb2);
	DDX_Text(pDX, IDC_VOLUNIT2, m_csVolUnit2);
	DDX_Text(pDX, IDC_VOLUNIT, m_csVolUnit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalcBandAir, CDlgCalcBase)
	//{{AFX_MSG_MAP(CDlgCalcBandAir)
	ON_BN_CLICKED(IDC_PROPERTIES, OnProperties)
	ON_CBN_SELCHANGE(IDC_ALIGNMENT, OnSelchangeAlignment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgCalcBandAir, CDlgCalcBase)
	//{{AFX_DISPATCH_MAP(CDlgCalcBandAir)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcBandAir message handlers
/////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------------------------
// -----------		InitDlg
// --------------------------------------------------------------------------

void CDlgCalcBandAir::InitDlg(void )
{
}


// --------------------------------------------------------------------------
// -----------		OkDlg
// --------------------------------------------------------------------------

void CDlgCalcBandAir::OkDlg( void)
{
}

// --------------------------------------------------------------------------
// -----------		CalculateVariables
// --------------------------------------------------------------------------

void CDlgCalcBandAir::CalculateVariables( void)
{
}

	


/////////////////////////////////////////////////////////////////////////////
// CDlgCalcBandChamber dialog
/////////////////////////////////////////////////////////////////////////////


CDlgCalcBandChamber::CDlgCalcBandChamber(CWnd* pParent /*=NULL*/)
	: CDlgCalcBase(CDlgCalcBandChamber::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgCalcBandChamber)
	m_nALignment = -1;
	m_csF3 = _T("");
	m_csFs = _T("");
	m_csPlength = _T("");
	m_csPlength2 = _T("");
	m_csPortUnit = _T("");
	m_csPortUnit2 = _T("");
	m_csVb = _T("");
	m_csVb2 = _T("");
	m_csVolUnit = _T("");
	m_csVolUnit2 = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCalcBandChamber::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgCalcBandChamber::DoDataExchange(CDataExchange* pDX)
{
	CDlgCalcBase::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalcBandChamber)
	DDX_CBIndex(pDX, IDC_ALIGNMENT, m_nALignment);
	DDX_Text(pDX, IDC_F3, m_csF3);
	DDX_Text(pDX, IDC_FS, m_csFs);
	DDX_Text(pDX, IDC_PLENGTH, m_csPlength);
	DDX_Text(pDX, IDC_PLENGTH2, m_csPlength2);
	DDX_Text(pDX, IDC_PORTUNIT, m_csPortUnit);
	DDX_Text(pDX, IDC_PORTUNIT2, m_csPortUnit2);
	DDX_Text(pDX, IDC_VB, m_csVb);
	DDX_Text(pDX, IDC_VB2, m_csVb2);
	DDX_Text(pDX, IDC_VOLUNIT, m_csVolUnit);
	DDX_Text(pDX, IDC_VOLUNIT2, m_csVolUnit2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalcBandChamber, CDlgCalcBase)
	//{{AFX_MSG_MAP(CDlgCalcBandChamber)
	ON_BN_CLICKED(IDC_PROPERTIES, OnProperties)
	ON_CBN_SELCHANGE(IDC_ALIGNMENT, OnSelchangeAlignment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgCalcBandChamber, CDlgCalcBase)
	//{{AFX_DISPATCH_MAP(CDlgCalcBandChamber)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcBandChamber message handlers
/////////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------------
// -----------		InitDlg
// --------------------------------------------------------------------------

void CDlgCalcBandChamber::InitDlg(void )
{
}


// --------------------------------------------------------------------------
// -----------		OkDlg
// --------------------------------------------------------------------------

void CDlgCalcBandChamber::OkDlg( void)
{
}

// --------------------------------------------------------------------------
// -----------		CalculateVariables
// --------------------------------------------------------------------------

void CDlgCalcBandChamber::CalculateVariables( void)
{

}

	


/////////////////////////////////////////////////////////////////////////////
// CDlgCalcVented dialog


typedef struct tagCalcVented
	{
	int		nAlignment;		// alignment
	float	fPDiam;			// port diameter
	float	fPlength;		// port length
	float	fSeriesRes;		// series resistance
	float	fVb;			// total volume
	float	fFb;			// tuning frequency
	int		iPorts;			// # of ports
	int		iDrivers;		// # of drivers
	int		iSeriesPar;		// series=1 or parallel=0
	} CALCVENTED;

CDlgCalcVented::CDlgCalcVented(CWnd* pParent /*=NULL*/)
	: CDlgCalcBase(CDlgCalcVented::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgCalcVented)
	m_nAlignment = -1;
	m_iSeriesPar = -1;
	m_uDriver = 0;
	m_uPort = 0;
	//}}AFX_DATA_INIT
}


void CDlgCalcVented::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgCalcVented::DoDataExchange(CDataExchange* pDX)
{
	CDlgCalcBase::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgCalcVented)
	DDX_Control(pDX, IDC_VOLUNIT, m_czVolUnit);
	DDX_Control(pDX, IDC_PORTUNIT2, m_czPortUnit2);
	DDX_Control(pDX, IDC_PORTUNIT, m_czPortUnit);
	DDX_CBIndex(pDX, IDC_ALIGNMENT, m_nAlignment);
	DDX_CBIndex(pDX, IDC_SERIESPAR, m_iSeriesPar);
	DDX_Text(pDX, IDC_NUMDRIVER, m_uDriver);
	DDX_Text(pDX, IDC_NUMPORT, m_uPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalcVented, CDlgCalcBase)
	//{{AFX_MSG_MAP(CDlgCalcVented)
	ON_CBN_SELCHANGE(IDC_ALIGNMENT, OnSelchangeAlignment)
	ON_EN_CHANGE(IDC_PLENGTH, OnChangePlength)
	ON_EN_CHANGE(IDC_VB, OnChangeVb)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC1, OnDeltaposSpin)
	ON_EN_CHANGE(IDC_PDIAM, OnChangePdiam)
	ON_BN_CLICKED(IDC_COMPARE, OnCompare)
	ON_EN_CHANGE(IDC_SERIESRES, OnChangeSeriesres)
	ON_EN_CHANGE(IDC_TUNING, OnChangeTuning)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC2, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC3, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC4, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC5, OnDeltaposSpin)
	ON_EN_CHANGE(IDC_NUMDRIVER, OnChangeNumdriver)
	ON_EN_CHANGE(IDC_NUMPORT, OnChangeNumport)
	ON_CBN_SELCHANGE(IDC_SERIESPAR, OnSelchangeSeriespar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgCalcVented, CDlgCalcBase)
	//{{AFX_DISPATCH_MAP(CDlgCalcVented)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcVented message handlers



// InitDialog
BOOL CDlgCalcVented::OnInitDialog() 
{
	{		// initialize the spinner format group
		FormatGroup cfdata[6] = { 
							{IDC_SERIESRES,	IDC_GENERIC1, 0.0f, 1000.0f, &m_fSeriesRes},
							{IDC_VB,		IDC_GENERIC2, 0.0f, 10000.0f, &m_fVb},
							{IDC_PDIAM,		IDC_GENERIC3, 0.0f, 1000.0f, &m_fPDiam},
							{IDC_PLENGTH,	IDC_GENERIC4, 0.0f, 1000.0f, &m_fPlength},
							{IDC_TUNING,	IDC_GENERIC5, 0.0f, 1000.0f, &m_fFb},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	
		GroupMetric cfgrp[4] = {
						  { IDC_VB,		 IDC_VOLUNIT,	mtLitre },
						  { IDC_PDIAM,	 IDC_PORTUNIT2,	mtCm },
						  { IDC_PLENGTH, IDC_PORTUNIT,	mtCm },
						  { 0, 0, mtNone }
						  };
		m_cfEdits.AttachMetrics( cfgrp);
	}

	
	CDlgCalcBase::OnInitDialog();

	::ComboFillString( this, IDC_ALIGNMENT, IDS_CALCV_ALIGNMENT);

	::SpinSetRange( this, IDC_SPINPORT, 1, 10);

	UpdateData( FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgCalcVented::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}


// --------------------------------------------------------------------------
// -----------		InitDlg
// --------------------------------------------------------------------------

void CDlgCalcVented::InitDlg(void )
{
CEnclosure *ce = (CEnclosure *)GetDest();
CHAMBER *ch;
					// make it a sealed box by turning off chamber 2 and port 1
	ch = ce->GetChamber( 2);
	ch->bUseChamber = FALSE;
	ch = ce->GetChamber( 1);
	ch->bUsePort = TRUE;

	m_fVb = 1000 * ch->fVolume;				// rescale to litres
	m_fPlength = 100 * ch->fPLength;		// rescale to cm
	m_fSeriesRes = ch->fSeriesRes;
	m_fPDiam = 200 * ch->fPRadius;			// rescale to cm and diameter
	m_fFb = 1.0f;
	m_uDriver = 1;
	m_uPort = 1;
	m_iSeriesPar = 0;

	{
	CALCVENTED clc;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		if ( ! capp->ReadRegistry( IDS_VENTEDINFO, &clc, sizeof(clc)))
			{
			m_nAlignment	= clc.nAlignment;
			m_fSeriesRes	= clc.fSeriesRes;
			m_fPDiam		= clc.fPDiam	;
			m_fPlength		= clc.fPlength;
			m_fVb			= clc.fVb		;
			m_fFb			= clc.fFb;
			m_iSeriesPar	= clc.iSeriesPar;
			m_uDriver		= clc.iDrivers;
			m_uPort			= clc.iPorts;
			}
	}

}


// --------------------------------------------------------------------------
// -----------		OkDlg
// --------------------------------------------------------------------------

void CDlgCalcVented::set_Enclosure( CEnclosure *pDest)
{
CHAMBER *ch;
					// make it a sealed box by turning off chamber 2 and port 1
	ch = pDest->GetChamber( 2);
	ch->bUseChamber = FALSE;
	ch = pDest->GetChamber( 1);
	ch->bUsePort = TRUE;
	ch->bPIsCircle = TRUE;
	ch->fVolume = m_fVb / 1000;				// rescale to m**3
	ch->fPLength = m_fPlength / 100;		// rescale to m
	ch->fSeriesRes = m_fSeriesRes;
	ch->fPRadius = m_fPDiam / 200;			// rescale to m and radius
	ch->bParallel = (m_iSeriesPar == 0);
	ch->wDrivers = (WORD )m_uDriver;
	ch->wPorts = (WORD )m_uPort;
}

void CDlgCalcVented::OkDlg( void)
{
CEnclosure *ce = (CEnclosure *)GetDest();

	set_Enclosure( ce);

	{
	CALCVENTED clc;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		clc.nAlignment	= m_nAlignment;
		clc.fSeriesRes	= m_fSeriesRes;
		clc.fPDiam		= m_fPDiam;
		clc.fPlength	= m_fPlength;
		clc.fVb			= m_fVb;
		clc.fFb			= m_fFb;
		clc.iSeriesPar	= m_iSeriesPar;
		clc.iDrivers	= m_uDriver;
		clc.iPorts		= m_uPort;
		capp->WriteRegistry( IDS_VENTEDINFO, &clc, sizeof(clc));
	}


}

// --------------------------------------------------------------------------
// -----------		CalculateVariables
// --------------------------------------------------------------------------

// given Vb and Port Length, recalculate stuff
void CDlgCalcVented::CalculateVariables( void)
{


}

	


/////////////////////////////////////////////////////////////////////////////

void CDlgCalcBandAir::OnProperties() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgCalcBandChamber::OnProperties() 
{
	// TODO: Add your control notification handler code here
	
}

// --------------------------------------------------------------------------
// -----------		OnSelchangeAlignment
// --------------------------------------------------------------------------

static void calc_Poly( int nAlign, double dParm, double *dPoly)
{
double sq2 = sqrt( 2.0);

	switch( nAlign)
		{
//		case alB4 :		// b4
//			{
//			dPoly[0] = sqrt( 4 + 2 * sq2);
//			dPoly[1] = 2 + sq2;
//			dPoly[2] = dPoly[0];
//			}
//			break;
		case alBB4 :		// bb4
			{
			dPoly[0] = 4 * dParm;
			dPoly[1] = 2 + 4 * dParm * dParm;
			dPoly[2] = 4 * dParm;
			}
			break;
		case alC4 :		// C4
			{
			double d = dParm * dParm;
			d = sqrt((d * d + 6 * d + 1) / 8);		//		D1/2 = (k4 + 6k2 + 1)/8
			dPoly[2] = dParm * sqrt(4 + 2 * sq2) / sqrt(d);		// yes D**1/4
			dPoly[1] = (1 + dParm * dParm * (1 + sq2) ) / d;
			dPoly[0] = dPoly[2] * ( 1 - (1 - dParm * dParm) / (2 * sq2)) / d;
			}
			break;
		case alQB3 :		// QB3
			{
//			dPoly[1] = dParm + (2 + sq2);	// so dparm = .1 to inf...
			dPoly[1] = dParm + 2.1;			// so dparm = .1 to inf...
			dPoly[0] = sqrt(2.0 * dPoly[1]);
			dPoly[2] = (dPoly[1] * dPoly[1] + 2) / (2 * dPoly[0]);
			}
			break;
		}
}

// this is from Small JAES Oct 1973 p635
// find positive real root of r4 - c1r3 + c2r - 1 = 0
// now poly at 0 is -1, so find when it goes positive
// start at sqrt(a3/a1) as a first approx then move it around
static double quad_Root( double dC1, double dC2)
{				// use newton's method around 1.0
double dxk;				// x
double fx;				// f x
double fxp;				// fx prime
int nstep = 0;

	if ( dC1 == dC2)
		return 1.0;			// easy case

	dxk = dC2/dC1;

	do
	{
		fx = (dxk * dxk * dxk * dxk - dC1 * dxk * dxk * dxk + dC2 * dxk - 1);
		fxp = (4 * dxk * dxk * dxk - 3 * dC1 * dxk * dxk + dC2);
		if ( fxp == 0)
			dxk -= fx / 100;
		else
			dxk -= fx / fxp;
		nstep++;
	} while ( (fabs(fx) > .0001) && (nstep < 100));		// max at 100 steps

	return dxk;
}

void CDlgCalcVented::OnSelchangeAlignment() 
{
double dpoly[3];			// the polynomial we are using
double dparm = 1.0;			// starting parameter value
double derror = 1.0;
double dlasterror = derror;
double dstep;
CEnclosure *ce = (CEnclosure *)GetDest();
CHAMBER *ch = ce->GetChamber( 1);
CDriver *cdrive = (CDriver *)ce->FindByID( ce->GetDriver(1));
double dq;
double droot;
double dmin;

	if ( ! cdrive)
	{
		::AfxMessageBox(IDERR_NODRIVER, MB_OK);
		return;
	}

	ASSERT ( ntDriver == cdrive->GetType());

DRIVEPARM dp = *cdrive->GetDriverParameters();
DRIVEEQUIV deq = *cdrive->GetDriverEquiv();

	UpdateData( TRUE);			// get the new alignment

	ce->ConvertMultiple( dp, deq, m_uDriver, (0==m_iSeriesPar) ? true : false);

	if ( m_nAlignment < 0 || m_nAlignment >= alCustom)
	{
		UpdateData( FALSE);
		return;			// whoops or custom
	}

	CreateProgressBar(IDS_STATCALC, 500);

	switch( m_nAlignment)
	{
		case alBB4 :		// bb4
			dmin = 0.0;
			break;
		case alC4 :		// C4
			dmin = 0.0;
			break;
		case alQB3 :		// QB3
			dmin = 0;
			break;
		default:
			dmin = 0;
			ASSERT(0);
			break;
	}

	dq = dp.fQts * ( dp.fRe + m_fSeriesRes) / dp.fRe;
	dstep = 1.0;
	dparm = dmin;
					// get initial conditions for the approximation
	{
	calc_Poly( m_nAlignment, dparm, dpoly);		// get the polynomial
	droot = quad_Root( dpoly[0] * ch->fQLeak, dpoly[2] * ch->fQLeak);
	dlasterror = dq - droot * droot * ch->fQLeak / ( dpoly[2] * droot * ch->fQLeak - 1);
	dlasterror = fabs( dlasterror);
	}
					// now find the parameter we want
	while( derror > .0001 && fabs(dstep) > .0001)	// while error large and stepsize significant
		{
			calc_Poly( m_nAlignment, dparm+dstep, dpoly);		// get the polynomial
			droot = quad_Root( dpoly[0] * ch->fQLeak, dpoly[2] * ch->fQLeak);	// get 4th root of poly
			derror = dq - droot * droot * ch->fQLeak / ( dpoly[2] * droot * ch->fQLeak - 1);
			derror = fabs( derror);
			if ( derror >= dlasterror)
			{			// calculate next step
				if ( dparm > (dstep+dmin))
				{
					calc_Poly( m_nAlignment, dparm-dstep, dpoly);		// get the polynomial
					droot = quad_Root( dpoly[0] * ch->fQLeak, dpoly[2] * ch->fQLeak);	// get 4th root of poly
					derror = dq - droot * droot * ch->fQLeak / ( dpoly[2] * droot * ch->fQLeak - 1);
					derror = fabs( derror);
					if ( derror >= dlasterror)		// both worse
					{
						dstep /= 2;
					}
					else
					{
						dparm -= dstep;
						dlasterror  = derror;
					}
				}
				else
					{
						dstep /= 2;
					}
			}
			else
			{
				dparm += dstep;
				dlasterror = derror;
			}
			StepProgressBar();
		}


	CloseProgressBar();

				// now the simple version....
	double dh = droot * droot;
	double dalpha = dpoly[1] * dh - dh * dh - 1 - (dpoly[2] * sqrt(dh) * ch->fQLeak - 1) / (ch->fQLeak * ch->fQLeak);
	double dfb = dh * dp.fFs;

	m_fVb = (float )(1000 * dp.fVas / dalpha);
	m_fFb = (float )dfb;
	m_fPlength = CalcPlength();

	if ( m_fPlength <= 0.0f)		// we're off the end
	{
		AfxMessageBox( IDERR_CANTALIGN);
		m_fPlength = 0.0f;
	}

	UpdateData( FALSE);

}

// --------------------------------------------------------------------------
// -----------		OnSelchangeAlignment
// --------------------------------------------------------------------------

void CDlgCalcSealed::OnSelchangeAlignment() 
{
float fqs[5] = { 0.5f, 0.577f, 0.707f, 1.0f, 0.0f };

	UpdateData( TRUE);			// get the new alignment

	if ( m_nAlignment < 0)
		return;			// whoops

	if ( fqs[m_nAlignment])			// not custom
		m_fQts = fqs[m_nAlignment];

	CalculateVariables();

	UpdateData( FALSE);

}

// --------------------------------------------------------------------------
// -----------		OnSelchangeAlignment
// --------------------------------------------------------------------------

void CDlgCalcBandChamber::OnSelchangeAlignment() 
{
	// TODO: Add your control notification handler code here

}

// --------------------------------------------------------------------------
// -----------		OnSelchangeAlignment
// --------------------------------------------------------------------------

void CDlgCalcBandAir::OnSelchangeAlignment() 
{
	// TODO: Add your control notification handler code here
	
}

// --------------------------------------------------------------------------
// -----------		OnChangeQts
// --------------------------------------------------------------------------

void CDlgCalcSealed::OnChangeQts() 
{
	if ( GetDlgItem( IDC_QTS) != GetFocus())
		return;

	if ( ! VerboseUpdateData( TRUE))
		return;

	m_nAlignment = SEALED_CUSTOM;
	CalculateVariables();

	UpdateData( FALSE);

}

// --------------------------------------------------------------------------
// -----------		OnChangeSeriesres
// --------------------------------------------------------------------------

void CDlgCalcSealed::OnChangeSeriesres() 
{
	if ( GetDlgItem( IDC_SERIESRES) != GetFocus())
		return;

	if ( ! VerboseUpdateData( TRUE))
		return;

	OnSelchangeAlignment();
	CalculateVariables();

	UpdateData( FALSE);
}


// --------------------------------------------------------------------------
// -----------		OnChangeNumdriver
// --------------------------------------------------------------------------
void CDlgCalcSealed::OnChangeNumdriver() 
{

	if ( GetDlgItem( IDC_NUMDRIVER) != GetFocus())
		return;

	if ( ! VerboseUpdateData( TRUE))
		return;

	{
	CComboBox *pcombo = (CComboBox *)GetDlgItem( IDC_SERIESPAR);	// get series parallel box

		if ( pcombo && pcombo->GetSafeHwnd())
			pcombo->EnableWindow( 1 != m_uDriver);

	}

	CalculateVariables();

	UpdateData( FALSE);
	
}

// --------------------------------------------------------------------------
// -----------		OnSelchangeSeries
// --------------------------------------------------------------------------
void CDlgCalcSealed::OnSelchangeSeries() 
{
	if ( ! VerboseUpdateData( TRUE))
		return;

	CalculateVariables();

	UpdateData( FALSE);
	
}

// --------------------------------------------------------------------------
// -----------		CalcPLength
// --------------------------------------------------------------------------

float CDlgCalcVented::CalcPlength( void)
{
double ddiam;
double dplength;
double drslt;

	if ( 1 == m_uPort)
	{
		ddiam = m_fPDiam;		// for debugging
		dplength =  (float )((2.54f * 2.54f/4000.0f) * 14630000 * m_fPDiam * m_fPDiam / (m_fFb * m_fFb * m_fVb));
		drslt = (float )((2.54f * 2.54f/4000.0f) * 14630000 * m_fPDiam * m_fPDiam / (m_fFb * m_fFb * m_fVb) - 1.463 * m_fPDiam / 2);
	}
	else
	{
		ddiam = m_fPDiam * sqrt((double)m_uPort);		// effective diameter is area'd
				// length without end correction
		dplength = (2.54 * 2.54/4000.0) * 14630000 * ddiam * ddiam / (m_fFb * m_fFb * m_fVb);

		drslt = dplength - 1.46 * m_fPDiam / 2;			// end correction for the right diameter;
	}

	return (float )drslt;

}


// --------------------------------------------------------------------------
// -----------		Recalc
// --------------------------------------------------------------------------

void CDlgCalcVented::Recalc( UINT uItem, float fOldValue)
{
float fratio;

	switch( uItem)
	{
	case IDC_VB :
		m_fPlength = CalcPlength();
		break;
	case IDC_PLENGTH :
		double db;
		db = m_fPlength + 1.463 * m_fPDiam / 2;
		db /= (2.54f * 2.54f/4000.0f) * 14630000 * m_fPDiam * m_fPDiam * m_uPort;
		db = 1 / (m_fFb * m_fFb * db);
		m_fVb = (float )db;
		break;
	case IDC_TUNING :
		fratio = fOldValue / m_fFb;		// old vs new
		m_fVb *= (float )sqrt( fratio);					// apply part of this here
		m_fPlength = CalcPlength();
		break;
	case IDC_SERIESRES :
	case IDC_SERIESPAR :
	case IDC_NUMDRIVER :
		UpdateData( FALSE);			// save the alignment value
		OnSelchangeAlignment();
		break;
	case IDC_NUMPORT :
	case IDC_PDIAM :
		m_fPlength = CalcPlength();
		break;
	default :
		ASSERT( 0);
		break;
	}
}

void CDlgCalcVented::change_Item( UINT uItem, float fOldValue)
{
	if ( GetFocus() == GetDlgItem( uItem) )
		{
		if ( ! VerboseUpdateData( TRUE))
			return;

		switch( uItem)
		{
		case IDC_VB:
		case IDC_PLENGTH:
		case IDC_TUNING:
			m_nAlignment = alCustom;
			break;
		case IDC_SERIESRES:
		case IDC_NUMDRIVER:
		case IDC_SERIESPAR:
			if ( alCustom == m_nAlignment)			// we can't deal with this
			{
				m_nAlignment = alQB3;				// so use qb3
			}
			break;
		default :
			break;
		}


		Recalc( uItem, fOldValue);
		CalculateVariables( );

		UpdateData( FALSE);
		}
}


void CDlgCalcVented::OnChangePdiam() 
{
	change_Item( IDC_PDIAM, m_fPDiam);
}

void CDlgCalcVented::OnChangeSeriesres() 
{
	change_Item( IDC_SERIESRES, m_fSeriesRes);
}


void CDlgCalcVented::OnChangeTuning() 
{
	change_Item( IDC_TUNING, m_fFb);
}

// --------------------------------------------------------------------------
// -----------		OnChangePlength
// --------------------------------------------------------------------------

void CDlgCalcVented::OnChangePlength() 
{
	change_Item( IDC_PLENGTH, m_fPlength);
}

// --------------------------------------------------------------------------
// -----------		OnChangeVb
// --------------------------------------------------------------------------

void CDlgCalcVented::OnChangeVb() 
{
	change_Item( IDC_VB, m_fVb);
}



void CDlgCalcVented::OnChangeNumdriver() 
{
	change_Item( IDC_NUMDRIVER, 1.0f);
	
}

void CDlgCalcVented::OnChangeNumport() 
{
	change_Item( IDC_NUMPORT, 1.0f);
	
}

void CDlgCalcVented::OnSelchangeSeriespar() 
{
	change_Item( IDC_SERIESPAR, 1.0f);
	
}


// --------------		For testing purposes
/*		Chebychev C4 (Ql == oo)
k		D		a3		a1		qt
0.100	0.133	0.433	0.773	1.728
0.200	0.155	0.833	1.396	0.927
0.300	0.194	1.182	1.822	0.681
0.400	0.248	1.481	2.090	0.568
0.500	0.320	1.737	2.255	0.505
0.600	0.411	1.958	2.362	0.465
0.700	0.523	2.151	2.440	0.436
0.800	0.656	2.323	2.502	0.415
0.900	0.815	2.476	2.559	0.397
1.000	1.000	2.613	2.613	0.383
1.100	1.216	2.738	2.667	0.370
1.200	1.464	2.851	2.722	0.359
1.300	1.750	2.954	2.778	0.349
1.400	2.075	3.048	2.834	0.340
1.500	2.445	3.134	2.890	0.332
1.600	2.864	3.214	2.946	0.325
1.700	3.337	3.287	3.002	0.318
1.800	3.867	3.354	3.056	0.312
1.900	4.462	3.416	3.110	0.307
2.000	5.125	3.473	3.162	0.302
2.100	5.864	3.526	3.212	0.297
2.200	6.683	3.576	3.261	0.293
2.300	7.591	3.621	3.308	0.289
2.400	8.592	3.663	3.353	0.285
2.500	9.695	3.702	3.396	0.282
2.600	10.907	3.739	3.437	0.279
2.700	12.236	3.772	3.477	0.276
2.800	13.688	3.804	3.515	0.273
2.900	15.274	3.833	3.551	0.271
3.000	17.000	3.861	3.585	0.269
*/


// QB3 alignments for checking
/*
k		D		a3		a1		qt
0.100	4.928	4.187	3.140	0.276
0.200	5.028	4.302	3.171	0.271
0.300	5.128	4.418	3.203	0.266
0.400	5.228	4.536	3.234	0.261
0.500	5.328	4.655	3.264	0.257
0.600	5.428	4.775	3.295	0.252
0.700	5.528	4.896	3.325	0.248
0.800	5.628	5.019	3.355	0.244
0.900	5.728	5.143	3.385	0.240
1.000	5.828	5.268	3.414	0.236
1.100	5.928	5.394	3.443	0.232
1.200	6.028	5.521	3.472	0.228
1.300	6.128	5.650	3.501	0.225
1.400	6.228	5.779	3.529	0.221
1.500	6.328	5.910	3.558	0.218
1.600	6.428	6.041	3.586	0.215
1.700	6.528	6.174	3.613	0.212
1.800	6.628	6.308	3.641	0.209
1.900	6.728	6.443	3.668	0.206
2.000	6.828	6.579	3.696	0.203
2.100	6.928	6.716	3.722	0.200
2.200	7.028	6.855	3.749	0.197
2.300	7.128	6.994	3.776	0.195
2.400	7.228	7.134	3.802	0.192
2.500	7.328	7.275	3.828	0.189
2.600	7.428	7.418	3.854	0.187
2.700	7.528	7.561	3.880	0.185
2.800	7.628	7.705	3.906	0.182
2.900	7.728	7.850	3.932	0.180
3.000	7.828	7.997	3.957	0.178
3.100	7.928	8.144	3.982	0.176
*/


void CDlgCalcVented::OnCompare() 
{
CEnclosure *ce = ((CEnclosure *)m_cOriginal)->GetTrial();

	if ( ! ce)
		return;

	set_Enclosure( ce);

	((CEnclosure *)m_cOriginal)->ChangeTrialData();

}

void CDlgCalcSealed::OnCompare() 
{
CEnclosure *ce = ((CEnclosure *)m_cOriginal)->GetTrial();

	if ( ! ce)
		return;

	set_Enclosure( ce);

	((CEnclosure *)m_cOriginal)->ChangeTrialData();

}


void CDlgCalcBase::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! m_cfEdits.ProcessLeftClick( nFlags, point))
		CDialog::OnLButtonUp(nFlags, point);
}

void CDlgCalcBase::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! 	m_cfEdits.ProcessRightClick( nFlags, point))
		CDialog::OnRButtonUp(nFlags, point);
}




BOOL CDlgCalcBase::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	{
	CSpinButtonCtrl *pwnd = (CSpinButtonCtrl *)GetDlgItem( IDC_SPINNUM);

		if ( pwnd && pwnd->GetSafeHwnd())			// it's in here
			pwnd->SetRange(1,10);					// max at 10 drivers duh
	}

	{
	CComboBox *pcombo = (CComboBox *)GetDlgItem( IDC_SERIESPAR);	// get series parallel box

		if ( pcombo && pcombo->GetSafeHwnd())
		{
			ComboFillString( this, IDC_SERIESPAR, IDS_SERIESPAR);
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

