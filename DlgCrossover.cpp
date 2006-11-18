// DlgCrossover.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "xform.h"
#include "Network.h"
#include "Passive.h"
#include "Driver.h"
#include "Dataset.h"

#include "DlgCrossover.h"

#include "DlgSelec.h"
#include "Folder.h"

#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// ------------------ the resource structure
typedef struct tagCrossoverInfo
{
	int		nOrder;
	BOOL	bHighLow;
	int		nType;
	float	fFS;
	float	fRe;
	selType	isUseWhich;			// which to use
	DWORD	dwDriver;			// driver name
	DWORD	dwDataset;			// a random impedance dataset
} CROSSOVERINFO;

/////////////////////////////////////////////////////////////////////////////
// CDlgCrossover dialog


CDlgCrossover::CDlgCrossover(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCrossover::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgCrossover)
	m_nHighLow = -1;
	m_nOrder = -1;
	m_nType = -1;
	m_iDriver = -1;
	m_csDataset = _T("");
	//}}AFX_DATA_INIT

	m_isUseWhich = selRe;		// do we want to use a driver?
	m_dwDriver = 0;				// the driver to use
	m_dwDataset = 0;			// which dataset to use

}


void CDlgCrossover::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CDlgCrossover::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cFS.DDX_Value( pDX, m_fFS);
	m_cRe.DDX_Value( pDX, m_fRe);

	//{{AFX_DATA_MAP(CDlgCrossover)
	DDX_CBIndex(pDX, IDC_HIGHLOW, m_nHighLow);
	DDX_CBIndex(pDX, IDC_ORDER, m_nOrder);
	DDX_CBIndex(pDX, IDC_XOVERTYPE, m_nType);
	DDX_CBIndex(pDX, IDC_DRIVER, m_iDriver);
	DDX_Text(pDX, IDC_DATASET, m_csDataset);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCrossover, CDialog)
	//{{AFX_MSG_MAP(CDlgCrossover)
	ON_CBN_SELCHANGE(IDC_ORDER, OnSelchangeOrder)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin2)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_SELDRIVER, OnSeldriver)
	ON_BN_CLICKED(IDC_SELRESIST, OnSelresist)
	ON_CBN_SELCHANGE(IDC_DRIVER, OnSelchangeDriver)
	ON_EN_CHANGE(IDC_RE, OnChangeRe)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_SELDATA, OnSeldata)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgCrossover, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgCrossover)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgCrossover to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {1B6B9BA2-895B-11CF-AA04-444553540000}
static const IID IID_IDlgCrossover =
{ 0x1b6b9ba2, 0x895b, 0x11cf, { 0xaa, 0x4, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgCrossover, CDialog)
	INTERFACE_PART(CDlgCrossover, IID_IDlgCrossover, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCrossover message handlers

void CDlgCrossover::copy_String( int nWhich)
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
void CDlgCrossover::setup_List( void)
{
CComboBox *pwnd = (CComboBox *)GetDlgItem( IDC_XOVERTYPE);

	pwnd->ResetContent();		// clear it out
	switch( 1+m_nOrder)			// these strings are the same as the list in Utils.h
		{
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
void CDlgCrossover::setup_Radios( selType slUse)
{
	CheckDlgButton( IDC_SELDRIVER, selDriver == slUse);
	CheckDlgButton( IDC_SELRESIST, selRe == slUse);
	CheckDlgButton( IDC_SELDATA, selData == slUse);
}

// ---------------------------------------------------------------------------
//	setup_DriverList
//			setup the list of drivers
// ---------------------------------------------------------------------------
void CDlgCrossover::setup_DriverList( void)
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

// ---------------------------------------------------------------------------
//		OnSelchangeOrder
// reset the types of crossovers available
// ---------------------------------------------------------------------------
void CDlgCrossover::OnSelchangeOrder() 
{
	UpdateData( TRUE);

	setup_List( );

	m_nType = 0;			// start at the top of the list

}

// ---------------------------------------------------------------------------
//			OnInitDialog
// ---------------------------------------------------------------------------
BOOL CDlgCrossover::OnInitDialog() 
{
	m_cFS.Subclass( this, IDC_FS, IDC_SPIN1);
	m_cRe.Subclass( this, IDC_RE, IDC_SPIN2);
	
	CDialog::OnInitDialog();

	::ComboFillString( this, IDC_ORDER, IDS_CROSS_ORDER);
	::ComboFillString( this, IDC_HIGHLOW, IDS_CROSS_HIGHLOW);
	::ComboFillString( this, IDC_XOVERALL, IDS_CROSS_XOVERALL);

	// read the old settings from ini
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
CROSSOVERINFO xv;

	if ( ! capp->ReadRegistry( IDS_XOVERINFO, &xv, sizeof( xv)))
		{
			m_nOrder = xv.nOrder;
			m_nType = xv.nType;
			m_nHighLow = xv.bHighLow;
			m_fRe = xv.fRe;
			m_fFS = xv.fFS;
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
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// ---------------------------------------------------------------------------
//			OnOK
// ---------------------------------------------------------------------------
void CDlgCrossover::OnOK() 
{

	if (! VerboseUpdateData ( TRUE))
		return;

	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	CROSSOVERINFO xv;

		xv.nOrder = m_nOrder;
		xv.nType = m_nType;
		xv.bHighLow = m_nHighLow;
		xv.fRe = m_fRe;
		xv.fFS = m_fFS;
		xv.isUseWhich = m_isUseWhich;
		xv.dwDataset = m_dwDataset;
		{
		CComboBox *pwnd = (CComboBox *)GetDlgItem( IDC_DRIVER);

			if ( pwnd->GetCurSel() >= 0)
				xv.dwDriver = pwnd->GetItemData( pwnd->GetCurSel());
			else
				xv.dwDriver = 0;
		}
		capp->WriteRegistry( IDS_XOVERINFO, &xv, sizeof(xv));
	}

	
	CDialog::OnOK();
}


// ---------------------------------------------------------------------------
//			OnDeltaPosSpin
// ---------------------------------------------------------------------------
void CDlgCrossover::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cFS.ProcessDelta( pNMUpDown->iDelta);

	*pResult = 0;
}

void CDlgCrossover::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cRe.ProcessDelta( pNMUpDown->iDelta);

	*pResult = 0;
}


BOOL CDlgCrossover::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CDialog::OnHelpInfo(pHelpInfo);
}

void CDlgCrossover::OnSeldriver() 
{
	m_isUseWhich = selDriver;	
	setup_Radios( m_isUseWhich);
}

void CDlgCrossover::OnSelresist() 
{
	m_isUseWhich = selRe;
	setup_Radios( m_isUseWhich);
}

void CDlgCrossover::OnSelchangeDriver() 
{
	m_isUseWhich = selDriver;	
	setup_Radios( m_isUseWhich);
}

void CDlgCrossover::OnChangeRe() 
{
	m_isUseWhich = selRe;
	setup_Radios( m_isUseWhich);
	
}

void CDlgCrossover::OnBrowse() 
{
CDlgSelectObject cdlg;
CFolder *m_pRoot = m_pNetwork->GetRootObject();


	cdlg.SetParms( (CFolder *)m_pRoot, m_dwDataset, ntDataSet, uomOhms);

	if ( IDOK == cdlg.DoModal())
		{
		UpdateData( TRUE);			// update the other fields
		m_dwDataset = cdlg.m_dwSelected;
		{
		CNamed *pname = m_pRoot->FindByID( m_dwDataset);

			if ( pname)
				m_csDataset = pname->GetFullName();
		}

		m_isUseWhich = selData;
		setup_Radios( m_isUseWhich);
		UpdateData( FALSE);
		}
}

void CDlgCrossover::OnSeldata() 
{
	m_isUseWhich = selData;
	setup_Radios( m_isUseWhich);
	
}

// -------------------------------------------------------------------------------------
//		the crossover operation
// -------------------------------------------------------------------------------------
CXtCrossover::CXtCrossover( CObject *cTarget) : CXunary( cTarget)
{
}

CXtCrossover::~CXtCrossover()
{
}


UINT CXtCrossover::DoDialog( )		// xeq dbox
{
CDlgCrossover cdlg;
CNetwork *cname;
UINT uout;

	cname = (CNetwork *)FindTargetObject();

	if ( ! cname)
		return IDCANCEL;

	cdlg.m_pNetwork = cname;

	uout = cdlg.DoModal();
	if ( IDOK == uout)
		{
		m_nHighLow	=	cdlg.m_nHighLow;
		m_nOrder	=	cdlg.m_nOrder;
		m_nType		=	::ComboToXover( 1 + m_nOrder, cdlg.m_nType);
		m_fFS		=	cdlg.m_fFS;
		m_fRe		=	cdlg.m_fRe;
		m_isUseWhich =	cdlg.m_isUseWhich;
		m_dwDriver =	cdlg.m_dwDriver;
		m_dwDataset =	cdlg.m_dwDataset;
		}

	return uout;

}

int CXtCrossover::DoOperation( )	// xeq xform
{
CNetwork *cname;
float fmatch;

	cname = (CNetwork *)FindTargetObject();

	if ( ! cname)
		return 1;

	fmatch = m_fRe;			// default to fRe to match to

	if ( (m_isUseWhich == selDriver) && m_dwDriver)			// we want to match to a driver's impedance
	{
	CDriver *pdrive;

		pdrive = (CDriver *)cname->FindByID( m_dwDriver);
		if ( pdrive && (ntDriver == pdrive->GetType()))	// yes, it really is a driver
		{
		DWORD dwimpedance = pdrive->GetImpedance();
			if ( dwimpedance)
			{
			CDataSet *pimp = (CDataSet *)cname->FindByID( dwimpedance);
				if ( pimp && pimp->IsType(ntDataSet, uomOhms))	// yes, it really is an impedance
				{
					fmatch = pimp->DataValueAt( m_fFS);			// the matching impedance
				}

			}
		}

	}

	if ( (m_isUseWhich == selData) && m_dwDataset)			// we want to match to a driver's impedance
	{
	CDataSet *pimp = (CDataSet *)cname->FindByID( m_dwDataset);
		if ( pimp && pimp->IsType(ntDataSet, uomOhms))	// yes, it really is an impedance
		{
			fmatch = pimp->DataValueAt( m_fFS);			// the matching impedance
		}
	}

	cname->AddCrossover(0, m_nHighLow, m_nType, 1+m_nOrder, m_fFS, fmatch);
	cname->UpdateViews();

	return 0;
}

UINT CXtCrossover::GetDialog(void)		// get the dialog id
{
	return IDD_CROSSOVER;
}

