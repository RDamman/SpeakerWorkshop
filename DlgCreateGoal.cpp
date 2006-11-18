// DlgCreateGoal.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "xform.h"
#include "Network.h"
#include "Passive.h"
#include "Driver.h"
#include "Dataset.h"

#include "DlgCreateGoal.h"

#include "DlgSelec.h"
#include "Folder.h"

#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// ------------------ the resource structure
#define NAMELEN 20

typedef struct tagCrossoverInfo
{
	int		nOrder;
	BOOL	bHighLow;
	int		nType;
	float	fFS;
	float	fValue;
	float	fStart;
	float	fEnd;
	selGoalType	isUseWhich;		// which to use
	DWORD	dwDriver;			// driver name
	DWORD	dwDataset;			// a random impedance dataset
} GOALINFO;


/////////////////////////////////////////////////////////////////////////////
// CDlgCreateGoal dialog


CDlgCreateGoal::CDlgCreateGoal(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCreateGoal::IDD, pParent), m_cfEdits()
{
	//{{AFX_DATA_INIT(CDlgCreateGoal)
	m_nHighLow = -1;
	m_nOrder = -1;
	m_iDriver = -1;
	m_csDataset = _T("");
	m_nType = -1;
	//}}AFX_DATA_INIT
}


void CDlgCreateGoal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgCreateGoal)
	DDX_CBIndex(pDX, IDC_HIGHLOW, m_nHighLow);
	DDX_CBIndex(pDX, IDC_ORDER, m_nOrder);
	DDX_CBIndex(pDX, IDC_DRIVER, m_iDriver);
	DDX_Text(pDX, IDC_DATASET, m_csDataset);
	DDX_CBIndex(pDX, IDC_XOVERTYPE, m_nType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCreateGoal, CDialog)
	//{{AFX_MSG_MAP(CDlgCreateGoal)
	ON_CBN_SELCHANGE(IDC_ORDER, OnSelchangeOrder)
	ON_BN_CLICKED(IDC_SELDRIVER, OnSeldriver)
	ON_BN_CLICKED(IDC_SELVALUE, OnSelvalue)
	ON_BN_CLICKED(IDC_SELDATA, OnSeldata)
	ON_CBN_SELCHANGE(IDC_DRIVER, OnSelchangeDriver)
	ON_EN_CHANGE(IDC_VALUE, OnChangeValue)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void CDlgCreateGoal::copy_String( int nWhich)
{
CComboBox *pwnd = (CComboBox *)GetDlgItem( IDC_XOVERTYPE);
CComboBox *psrc = (CComboBox *)GetDlgItem( IDC_XOVERALL);		// all of the strings are here....
char sz[200];

	psrc->GetLBText( nWhich, sz);
	pwnd->AddString( sz);				// butterworth

}

// ---------------------------------------------------------------------------
//		setup_List
// ---------------------------------------------------------------------------
void CDlgCreateGoal::setup_List( void)
{
CComboBox *pwnd = (CComboBox *)GetDlgItem( IDC_XOVERTYPE);
UINT uwndlist[] = { IDC_HIGHLOW, IDC_XOVERTYPE, IDC_FS, IDC_SPIN1 };
int i;

	for ( i=0; i< (sizeof( uwndlist) / sizeof( UINT)); i++)
	{
	CWnd *pwnd = GetDlgItem( uwndlist[i]);

		if ( pwnd && pwnd->GetSafeHwnd())
			pwnd->EnableWindow( m_nOrder != 0);
	}

	pwnd->ResetContent();		// clear it out
	switch( m_nOrder)
		{
		case 0 :			// no strings if flat
			break;
		case 1 :
		case 3 :			// butterworth, only
			copy_String( xoButterworth);
			break;
		case 2 :
			copy_String( xoBessel);			// bessel
			copy_String( xoButterworth);	// butter
			copy_String( xoChebychev);		// cheby
			copy_String( xoLinkwitz);		// L-R
			break;
		case 4 :
			copy_String( xoBessel);			// bessel
			copy_String( xoButterworth);	// butter
			copy_String( xoLegendre);		// Legendre
			copy_String( xoGaussian);		// Gaussian
			copy_String( xoLinkwitz);		// L-R
			copy_String( xoLinear);			// LinearPhase
			break;
		}

	pwnd->SetCurSel( 0);					// select the first one

}


// ---------------------------------------------------------------------------
//	setup_Radios
//		setup the radio buttons for the style of impedance match
// ---------------------------------------------------------------------------
void CDlgCreateGoal::setup_Radios( selGoalType slUse)
{
	CheckDlgButton( IDC_SELDRIVER, sglDriver == slUse);
	CheckDlgButton( IDC_SELVALUE, sglValue == slUse);
	CheckDlgButton( IDC_SELDATA, sglData == slUse);

UINT uwndlist[] = { IDC_FSTART, IDC_SPIN3, IDC_FEND, IDC_SPIN4 };
int i;

	for ( i=0; i< (sizeof( uwndlist) / sizeof( UINT)); i++)
	{
	CWnd *pwnd = GetDlgItem( uwndlist[i]);

		if ( pwnd && pwnd->GetSafeHwnd())
			pwnd->EnableWindow( sglValue != slUse);
	}
}

// ---------------------------------------------------------------------------
//	setup_DriverList
//			setup the list of drivers
// ---------------------------------------------------------------------------
void CDlgCreateGoal::setup_DriverList( void)
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

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateGoal message handlers

// ---------------------------------------------------------------------------
//		OnSelchangeOrder
// reset the types of crossovers available
// ---------------------------------------------------------------------------
void CDlgCreateGoal::OnSelchangeOrder() 
{
	UpdateData( TRUE);

	setup_List( );

	m_nType = 0;			// start at the top of the list
}

// ---------------------------------------------------------------------------
//			OnInitDialog
// ---------------------------------------------------------------------------
BOOL CDlgCreateGoal::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[5] = { 
							{IDC_FS,	IDC_SPIN1, 1.0f, 2000000.0f, &m_fFS},
							{IDC_VALUE,	IDC_SPIN2, -100.0f, 100.0f, &m_fValue},
							{IDC_FSTART,	IDC_SPIN3, 1.0f, 2000000.0f, &m_fStart},
							{IDC_FEND,	IDC_SPIN4, 1.0f, 2000000.0f, &m_fEnd},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}
	
	CDialog::OnInitDialog();

	::ComboFillString( this, IDC_ORDER, IDS_GOAL_ORDER);
	::ComboFillString( this, IDC_HIGHLOW, IDS_GOAL_HIGHLOW);
	::ComboFillString( this, IDC_XOVERALL, IDS_GOAL_XOVERALL);

	// read the old settings from ini
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
GOALINFO xv;

	if ( ! capp->ReadRegistry( IDS_GOALINFO, &xv, sizeof( xv)))
		{
			m_nOrder = xv.nOrder;
			m_nType = xv.nType;
			m_nHighLow = xv.bHighLow;
			m_fValue = xv.fValue;
			m_fFS = xv.fFS;
			m_fStart = xv.fStart;
			m_fEnd = xv.fEnd;
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
	setup_List();		// fill the combo based on order
	setup_DriverList();
	setup_Radios( m_isUseWhich);
	UpdateData( FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

// ---------------------------------------------------------------------------
//			OnOK
// ---------------------------------------------------------------------------
void CDlgCreateGoal::OnOK() 
{
	if ( ! VerboseUpdateData ( TRUE))
		return;

	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	GOALINFO xv;

		xv.nOrder = m_nOrder;
		xv.nType = m_nType;
		xv.bHighLow = m_nHighLow;
		xv.fValue = m_fValue;
		xv.fFS = m_fFS;
		xv.fStart = m_fStart;
		xv.fEnd = m_fEnd;
		xv.isUseWhich = m_isUseWhich;
		xv.dwDataset = m_dwDataset;
		{
		CComboBox *pwnd = (CComboBox *)GetDlgItem( IDC_DRIVER);

			if ( pwnd->GetCurSel() >= 0)
				xv.dwDriver = pwnd->GetItemData( pwnd->GetCurSel());
			else
				xv.dwDriver = 0;
		}
		capp->WriteRegistry( IDS_GOALINFO, &xv, sizeof(xv));
	
	CDialog::OnOK();
}

void CDlgCreateGoal::OnSeldriver() 
{
	m_isUseWhich = sglDriver;	
	
	setup_Radios( m_isUseWhich);
}

void CDlgCreateGoal::OnSelvalue() 
{
	m_isUseWhich = sglValue;

	setup_Radios( m_isUseWhich);
}

void CDlgCreateGoal::OnSeldata() 
{
	m_isUseWhich = sglData;
	setup_Radios( m_isUseWhich);
}

void CDlgCreateGoal::OnSelchangeDriver() 
{
	m_isUseWhich = sglDriver;	
	setup_Radios( m_isUseWhich);

}

void CDlgCreateGoal::OnChangeValue() 
{
	m_isUseWhich = sglValue;
	setup_Radios( m_isUseWhich);
	
}

void CDlgCreateGoal::OnBrowse() 
{
CDlgSelectObject cdlg;
CFolder *m_pRoot = m_pNetwork->GetRootObject();


	cdlg.SetParms( (CFolder *)m_pRoot, m_dwDataset, ntDataSet, uomFreq);

	if ( IDOK == cdlg.DoModal())
		{
		UpdateData( TRUE);			// update the other fields
		m_dwDataset = cdlg.m_dwSelected;
		{
		CNamed *pname = m_pRoot->FindByID( m_dwDataset);

			if ( pname)
				m_csDataset = pname->GetFullName();
		}

		m_isUseWhich = sglData;
		setup_Radios( m_isUseWhich);
		UpdateData( FALSE);
		}
	
}

// ---------------------------------------------------------------------------
//			OnDeltaPosSpin
// ---------------------------------------------------------------------------
void CDlgCreateGoal::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}
