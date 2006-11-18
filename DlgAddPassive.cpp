// DlgAddPassive.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "Xform.h"
#include "zFormEdt.h"

#include "Passive.h"
#include "Network.h"

#include "DlgAddPassive.h"

#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


typedef struct tagPASSIVEINFO
{
	float fCapValue;
	float fResValue;
	float fIndValue;
	float fIndResist;
} PASSIVEINFO;

/////////////////////////////////////////////////////////////////////////////
// CDlgAddPassive dialog


CDlgAddPassive::CDlgAddPassive(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddPassive::IDD, pParent), m_cfEdits()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgAddPassive)
	m_csName = _T("");
	m_csType = _T("");
	m_csCompUnit = _T("");
	//}}AFX_DATA_INIT

	m_fValue = 0.0f;
	m_fResist = 0.0f;
}


void CDlgAddPassive::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CDlgAddPassive::DoDataExchange(CDataExchange* pDX)
{
	m_cfEdits.DDX_All( pDX);

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddPassive)
	DDX_Text(pDX, IDC_COMPNAME, m_csName);
	DDX_Text(pDX, IDC_TYPE, m_csType);
	DDX_Text(pDX, IDC_COMPUNIT, m_csCompUnit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddPassive, CDialog)
	//{{AFX_MSG_MAP(CDlgAddPassive)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgAddPassive, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgAddPassive)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgAddPassive to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {615486C0-8967-11CF-AA04-444553540000}
static const IID IID_IDlgAddPassive =
{ 0x615486c0, 0x8967, 0x11cf, { 0xaa, 0x4, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgAddPassive, CDialog)
	INTERFACE_PART(CDlgAddPassive, IID_IDlgAddPassive, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddPassive message handlers



BOOL CDlgAddPassive::OnInitDialog() 
{
CString csout;
UINT uids[] = { IDC_RESSTATIC, IDC_RESSUFFIX, IDC_SPIN2, IDC_RESISTANCE };

	{		// initialize the spinner format group
	FormatGroup cfdata[3] = { 
							{IDC_VALUE,			IDC_SPIN1, 0.0f, 2000000.0f, &m_fValue},
							{IDC_RESISTANCE,	IDC_SPIN2, 0.0f, 2000000.0f, &m_fResist},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CDialog::OnInitDialog();

	::ComboFillString( this, IDC_COMPTYPE, IDS_ADDP_COMPTYPE);
	
	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	PASSIVEINFO pf;

		m_fResist = 0.0f;

		if ( capp && !capp->ReadRegistry( IDS_PASSIVEINFO, &pf, sizeof( pf)) )
			{
			switch( m_nType)
				{
				case ptCapacitor:
					m_fValue = pf.fCapValue * 1000000.0f;
					break;
				case ptInductor:
					m_fValue = pf.fIndValue * 1000.0f;
					m_fResist = pf.fIndResist;
					break;
				case ptResistor:
					m_fValue = pf.fResValue;
					break;
				default:
					break;
				}
			}
	}

	int i;
	switch( m_nType)
		{
		case ptCapacitor:
			i = 1;
			m_csCompUnit.LoadString(IDS_UFARAD);
			break;
		case ptInductor:
			m_csCompUnit.LoadString(IDS_MHENRY);
			i = 2;
			break;
		case ptResistor:
			m_csCompUnit.LoadString(IDS_OHM);
			i = 0;
			break;
		case ptDriver:
			m_csCompUnit = cNullString;
			i = 4;
			break;
		case ptGenerator:
			m_csCompUnit.LoadString(IDS_VOLT);
			i = 3;
			break;
		default:
			m_csCompUnit = cNullString;
			i = 4;
			break;
		}

	{			// enable the inductor fields
	int i, imax;
	CWnd *pwnd;

		imax = sizeof( uids) / sizeof( UINT);

		for ( i=0; i<imax; i++)
		{
			pwnd = GetDlgItem( uids[i]);
			if ( pwnd && pwnd->GetSafeHwnd())
				pwnd->EnableWindow( ptInductor == m_nType);
		}
	}

	CComboBox *psrc = (CComboBox *)GetDlgItem( IDC_COMPTYPE);
	char sz[50];
	psrc->GetLBText( i, sz);
	m_csType = sz;


	UpdateData( FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAddPassive::OnOK() 
{

	// write the settings to ini
	if ( UpdateData ( TRUE))
		{
		CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
		PASSIVEINFO pf;
					// use defaults if there isn't one
		if ( capp->ReadRegistry( IDS_PASSIVEINFO, &pf, sizeof( pf)) )
			{
			pf.fCapValue = 1.0f;
			pf.fResValue = 1.0f;
			pf.fIndValue = 1.0f;
			pf.fIndResist = 0.0f;
			}
		switch( m_nType)
			{
			case ptCapacitor:
				m_fValue *= .000001f;
				pf.fCapValue = m_fValue;
				break;
			case ptInductor:
				m_fValue *= .001f;
				pf.fIndValue = m_fValue;
				pf.fIndResist = m_fResist;
				break;
			case ptResistor:
				pf.fResValue = m_fValue;
				break;
			default:
				break;
			}

		
		capp->WriteRegistry( IDS_PASSIVEINFO, &pf, sizeof( pf));
		}
	
	CDialog::OnOK();
}


void CDlgAddPassive::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

float CDlgAddPassive::GetValue( void)
{
	switch( m_nType)
		{
		case ptCapacitor:
			return ( m_fValue * .000001f);
		case ptInductor:
			return ( m_fValue * .001f);
			break;
		case ptResistor:
			return ( m_fValue);
			break;
		default:
			ASSERT(0);
			break;
		}

	return 0.0f;		// to avoid a warning

}


// -------------------------------------------------------------------------------------
//		the AddPassive operation
// -------------------------------------------------------------------------------------
CXtAddPassive::CXtAddPassive( CObject *cTarget, NAMETYPES ntObj) : CXunary( cTarget)
{
	m_nType = ntObj;
	m_fQ = 1000000;		// default to 1,000,000
}

CXtAddPassive::~CXtAddPassive()
{
}

UINT CXtAddPassive::GetNameID()
{
	switch( m_nType)
		{
		case ptCapacitor :
			return IDOP_ADDCAPACITOR;
		case ptInductor :
			return IDOP_ADDINDUCTOR;
		case ptResistor :
			return IDOP_ADDRESISTOR;
		}

	ASSERT(0);
	return IDOP_ADDRESISTOR;
}


UINT CXtAddPassive::DoDialog( )		// xeq dbox
{
CDlgAddPassive cdlg;
CNetwork *cname;
UINT uout;

	cname = (CNetwork *)FindTargetObject();

	if ( ! cname)
		return IDCANCEL;

	cdlg.m_nType = m_nType;		// init the datatype

	uout = cdlg.DoModal();
	if ( IDOK == uout)
		{
		m_fValue	= cdlg.GetValue();
		m_csName	= cdlg.m_csName;
		if ( ptInductor == m_nType)
			{
				if ( cdlg.m_fResist > 0)
					m_fQ = (float )(m_fValue * 2 * ONEPI * 1000.0 / cdlg.m_fResist);
				else
					m_fQ = 1000000;			// default to 1000000
			}
		}

	return uout;

}

int CXtAddPassive::DoOperation( )	// xeq xform
{
CNetwork *cname;
ZpPassive *zp;

	cname = (CNetwork *)FindTargetObject();

	if ( ! cname)
		return 1;

	switch( m_nType)
		{
		case ptCapacitor :
			zp = new ZpCapacitor();
			break;
		case ptInductor :
			zp = new ZpInductor();
			zp->SetQ( m_fQ);			// set this guy's Q
			break;
		case ptResistor :
		default :
			zp = new ZpResistor();
			break;
		}

	zp->SetValue( m_fValue);
	zp->SetName( m_csName);
	zp->SetNode(0, 1000);
	zp->SetNode(1, 1001);
	zp->SetPosition( 0, 30);
	zp->SetPosition( 1, 30);
	cname->AddDiscrete( zp);
	cname->RenumberNodes();
	cname->UpdateViews();

	return 0;
}

UINT CXtAddPassive::GetDialog(void)		// get the dialog id
{
	return IDD_ADDPASSIVE;
}

