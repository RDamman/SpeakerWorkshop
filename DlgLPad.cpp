// DlgLPad.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "Xform.h"
#include "DlgLPad.h"

#include "Network.h"
#include "Passive.h"
#include "Driver.h"
#include "Dataset.h"

#include "DlgSelec.h"
#include "Folder.h"
#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


typedef struct tagLpadInfo
{
	float	fLevel;
	float	fFStart;
	float	fFEnd;
	float	fRe;
	selLPad	isUseWhich;			// which to use
	DWORD	dwDriver;			// driver name
	DWORD	dwDataset;			// a random impedance dataset
} LPADINFO;


/////////////////////////////////////////////////////////////////////////////
// CDlgLPad dialog


CDlgLPad::CDlgLPad(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLPad::IDD, pParent), m_cfEdits()
{
	//{{AFX_DATA_INIT(CDlgLPad)
	m_iDriver = -1;
	m_csDataset = _T("");
	//}}AFX_DATA_INIT

	m_isUseWhich = sllRe;		// do we want to use a driver?
	m_dwDriver = 0;				// the driver to use
	m_dwDataset = 0;			// which dataset to use
}


void CDlgLPad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgLPad)
	DDX_CBIndex(pDX, IDC_DRIVER, m_iDriver);
	DDX_Text(pDX, IDC_DATASET, m_csDataset);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLPad, CDialog)
	//{{AFX_MSG_MAP(CDlgLPad)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_CBN_SELCHANGE(IDC_DRIVER, OnSelchangeDriver)
	ON_EN_CHANGE(IDC_RE, OnChangeRe)
	ON_BN_CLICKED(IDC_SELDATA, OnSelData)
	ON_BN_CLICKED(IDC_SELDRIVER, OnSelDriver)
	ON_BN_CLICKED(IDC_SELRESIST, OnSelResist)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLPad message handlers

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
BOOL CDlgLPad::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[5] = { 
							{IDC_LEVEL,	IDC_SPIN1, 0.0f, 100.0f, &m_fLevel},
							{IDC_STARTFREQ,	IDC_SPIN2, 0.01f, 2000000.0f, &m_fStartFreq},
							{IDC_ENDFREQ,	IDC_SPIN3, 0.01f, 2000000.0f, &m_fEndFreq},
							{IDC_RE,	IDC_SPIN4, 0.01f, 2000.0f, &m_fRe},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CDialog::OnInitDialog();
	// read the old settings from ini
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
LPADINFO xv;

	if ( ! capp->ReadRegistry( IDS_LPADINFO, &xv, sizeof( xv)))
	{
		m_fLevel = xv.fLevel;
		m_fRe = xv.fRe;
		m_fStartFreq = xv.fFStart;
		m_fEndFreq = xv.fFEnd;
		m_isUseWhich = xv.isUseWhich;
		m_dwDriver = xv.dwDriver;
		m_dwDataset = xv.dwDataset;
		if ( m_dwDataset)
		{
		CNamed *pname = m_pNetwork->FindByID( m_dwDataset);

			if ( pname)
				m_csDataset = pname->GetFullName();
		}
	}
	else
	{				// no registry, just default this stuff
		m_fLevel = 3;
		m_fRe = 8;
		m_fStartFreq = 1000.0f;
		m_fEndFreq = 1500.0f;
		m_isUseWhich = sllRe;
	}

	setup_DriverList();
	setup_Radios( m_isUseWhich);
	UpdateData( FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CDlgLPad::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void CDlgLPad::OnBrowse() 
{
CDlgSelectObject cdlg;
CFolder *m_pRoot = m_pNetwork->GetRootObject();


	cdlg.SetParms( (CFolder *)m_pRoot, m_dwDataset, ntDataSet, uomOhms);

	if ( IDOK == cdlg.DoModal())
	{
	CNamed *pname;

		UpdateData( TRUE);			// update the other fields
		m_dwDataset = cdlg.m_dwSelected;
		pname = m_pRoot->FindByID( m_dwDataset);

		if ( pname)
			m_csDataset = pname->GetFullName();

		OnSelData();

		UpdateData( FALSE);
	}
	
}

// ---------------------------------------------------------------------------
//	setup_Radios
//		setup the radio buttons for the style of impedance match
// ---------------------------------------------------------------------------
void CDlgLPad::setup_Radios( selLPad slUse)
{
	CheckDlgButton( IDC_SELDRIVER, sllDriver == slUse);
	CheckDlgButton( IDC_SELRESIST, sllRe == slUse);
	CheckDlgButton( IDC_SELDATA, sllData == slUse);
}

// ---------------------------------------------------------------------------
//	setup_DriverList
//			setup the list of drivers
// ---------------------------------------------------------------------------
void CDlgLPad::setup_DriverList( void)
{
CComboBox *pwnd = (CComboBox *)GetDlgItem( IDC_DRIVER);
CString strmatch;

	if ( (!pwnd) || !pwnd->GetSafeHwnd())
		return;			// whoops

	pwnd->ResetContent();		// clear it out
	m_iDriver = 0;

	{
	int i, inow;
	CNamed *pname;
	DWORD dwdrive;

		for ( i=0; ; i++)
		{
			ZpDriver *pdrive = (ZpDriver *)m_pNetwork->GetDriver( i);
			if ( ! pdrive)
				break;			// we're done
						// get the named driver
			dwdrive = pdrive->GetDriver();
			if ( dwdrive)
			{
				pname = m_pNetwork->FindByID( dwdrive);		// find the driver
				pwnd->AddString( pname->GetName());
				inow = pwnd->FindString( -1, pname->GetName());
				pwnd->SetItemData( inow, dwdrive);			// store the driver id
				if ( dwdrive == m_dwDriver)
					strmatch = pname->GetName();
			}
		}
	}

	if ( strmatch.GetLength())
		m_iDriver = pwnd->FindString(-1, strmatch);			// this is the one to pick
	else
		m_iDriver = 0;
	pwnd->SetCurSel( m_iDriver);					// select the right one

}


void CDlgLPad::OnSelchangeDriver() 
{
	OnSelDriver();
	
}

void CDlgLPad::OnChangeRe() 
{
	OnSelResist();
	
}

void CDlgLPad::OnSelData() 
{
	m_isUseWhich = sllData;
	setup_Radios( m_isUseWhich);
	
}

void CDlgLPad::OnSelDriver() 
{
	m_isUseWhich = sllDriver;	
	setup_Radios( m_isUseWhich);
	
}

void CDlgLPad::OnSelResist() 
{
	m_isUseWhich = sllRe;
	setup_Radios( m_isUseWhich);
	
}

void CDlgLPad::OnOK() 
{
	if (! VerboseUpdateData ( TRUE))
		return;

	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	LPADINFO xv;

		xv.fLevel =		m_fLevel;
		xv.fFStart =	m_fStartFreq;
		xv.fFEnd =		m_fEndFreq;
		xv.fRe =		m_fRe;
		xv.isUseWhich = m_isUseWhich;
		xv.dwDataset =	m_dwDataset;
		{
		CComboBox *pwnd = (CComboBox *)GetDlgItem( IDC_DRIVER);

			if ( pwnd->GetCurSel() >= 0)
				xv.dwDriver = pwnd->GetItemData( pwnd->GetCurSel());
			else
				xv.dwDriver = 0;
		}
		capp->WriteRegistry( IDS_LPADINFO, &xv, sizeof(xv));
	}
	
	CDialog::OnOK();
}




// -------------------------------------------------------------------------------------
//		the crossover operation
// -------------------------------------------------------------------------------------
CXtLPad::CXtLPad( CObject *cTarget) : CXunary( cTarget)
{
}

CXtLPad::~CXtLPad()
{
}


UINT CXtLPad::DoDialog( )		// xeq dbox
{
CDlgLPad cdlg;
CNetwork *cname;
UINT uout;

	cname = (CNetwork *)FindTargetObject();

	if ( ! cname)
		return IDCANCEL;

	cdlg.m_pNetwork = cname;

	uout = cdlg.DoModal();
	if ( IDOK == uout)
		{
		m_fLevel	=	cdlg.m_fLevel;
		m_fFStart	=	cdlg.m_fStartFreq;
		m_fFEnd		=	cdlg.m_fEndFreq;
		m_fRe		=	cdlg.m_fRe;
		m_isUseWhich =	cdlg.m_isUseWhich;
		m_dwDriver =	cdlg.m_dwDriver;
		m_dwDataset =	cdlg.m_dwDataset;
		}

	return uout;

}

int CXtLPad::DoOperation( )	// xeq xform
{
CNetwork *cname;
float fmatch;
CDataSet *pimp = NULL;

	cname = (CNetwork *)FindTargetObject();

	if ( ! cname)
		return 1;

	fmatch = m_fRe;			// default to fRe to match to

	if ( (m_isUseWhich == sllDriver) && m_dwDriver)			// we want to match to a driver's impedance
	{
	CDriver *pdrive;

		pdrive = (CDriver *)cname->FindByID( m_dwDriver);
		if ( pdrive && (ntDriver == pdrive->GetType()))	// yes, it really is a driver
		{
		DWORD dwimpedance = pdrive->GetImpedance();
			if ( dwimpedance)
			{
			pimp = (CDataSet *)cname->FindByID( dwimpedance);
			}
		}

	}

	if ( (m_isUseWhich == sllData) && m_dwDataset)			// we want to match to a driver's impedance
	{
		pimp = (CDataSet *)cname->FindByID( m_dwDataset);
	}

	if ( pimp && pimp->IsType(ntDataSet, uomOhms))	// yes, it really is an impedance
		{
		int ncount;
		int nstart;
		int i;
		double dtotal = 0.0;

			nstart = pimp->FreqToIndex( m_fFStart);
			ncount = pimp->FreqToIndex( m_fFEnd) - nstart;
			if ( ncount <= 0)
				ncount = 1;
			for ( i=0; i<ncount; i++)
			{
				dtotal += pimp->DataValueAt( i + nstart);
			}
			dtotal /= ncount;
			fmatch = (float )dtotal;
		}


	cname->AddLPad(m_fLevel, fmatch);
	cname->UpdateViews();

	return 0;
}

UINT CXtLPad::GetDialog(void)		// get the dialog id
{
	return IDD_LPAD;
}
