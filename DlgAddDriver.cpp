/////////////////////////////////////////////////////////////////////////////
// DlgAddDriver.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "audtest.h"

#include "Xform.h"
#include "zFormEdt.h"

#include "Passive.h"
#include "Network.h"

#include "DlgAddDriver.h"
#include "Folder.h"
#include "dlgSelec.h"

#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAXCHARLENGTH 30


typedef struct tagDRIVERINFO
{
	float	fOffset;
	DWORD	dwDriverID;
	BOOL	bFlipPolarity;
	BOOL	bIndieResponse;
	char	szDrName[MAXCHARLENGTH];
} DRIVERINFO;


/////////////////////////////////////////////////////////////////////////////
// CDlgAddDriver dialog
/////////////////////////////////////////////////////////////////////////////


CDlgAddDriver::CDlgAddDriver(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddDriver::IDD, pParent), m_cfEdits()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgAddDriver)
	m_bIndieResponse = FALSE;
	m_bFlipPolarity = FALSE;
	m_csDriver = _T("");
	m_strName = _T("");
	//}}AFX_DATA_INIT

	m_fOffset = 0.0f;
}


void CDlgAddDriver::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CDlgAddDriver::DoDataExchange(CDataExchange* pDX)
{
	m_cfEdits.DDX_All( pDX);

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddDriver)
	DDX_Control(pDX, IDC_OFFUNIT, m_czStatOffset);
	DDX_Check(pDX, IDC_INDIE, m_bIndieResponse);
	DDX_Check(pDX, IDC_FLIP, m_bFlipPolarity);
	DDX_Text(pDX, IDC_DRIVER, m_csDriver);
	DDX_Text(pDX, IDC_NAME, m_strName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddDriver, CDialog)
	//{{AFX_MSG_MAP(CDlgAddDriver)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin1)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgAddDriver, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgAddDriver)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgAddDriver to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {615486C0-8967-11CF-AA04-444553540000}
static const IID IID_IDlgAddDriver =
{ 0x615486c0, 0x8967, 0x11cf, { 0xaa, 0x4, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgAddDriver, CDialog)
	INTERFACE_PART(CDlgAddDriver, IID_IDlgAddDriver, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddDriver message handlers
/////////////////////////////////////////////////////////////////////////////


// ---------------------------------------------------------------------------
//			OnInitDialog
// ---------------------------------------------------------------------------
BOOL CDlgAddDriver::OnInitDialog() 
{

	{		// initialize the spinner format group
	FormatGroup cfdata[2] = { 
							{IDC_OFFSET,	IDC_SPIN1, 0.0f, 100.0f, &m_fOffset},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	GroupMetric cfgrp[2] = {
					  { IDC_OFFSET,		 IDC_OFFUNIT,	mtCm },
					  { 0, 0, mtNone }
					  };
		m_cfEdits.AttachMetrics( cfgrp);
	}

	CDialog::OnInitDialog();

	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	DRIVERINFO pf;

		m_bFlipPolarity = FALSE;
		m_bIndieResponse = TRUE;
		m_dwDriverID = 0;
		m_fOffset = 0;
		m_strName = "";

		if ( capp && !capp->ReadRegistry( IDS_DRIVERINFO, &pf, sizeof( pf)) )
		{
			m_bFlipPolarity = pf.bFlipPolarity;
			m_bIndieResponse = pf.bIndieResponse;
			m_dwDriverID = pf.dwDriverID;
			m_fOffset = pf.fOffset;
			m_strName = pf.szDrName;
		}

		m_csDriver.LoadString( IDS_UNKNOWN);
		if (m_dwDriverID)
		{		// verify the driver id passed in here
		CNamed *pnam;

			pnam = m_pRoot->FindByID( m_dwDriverID);
			if ( (! pnam) || !pnam->IsType( ntDriver))
				m_dwDriverID = 0;			// nope, no longer valid id
			else
				m_csDriver = pnam->GetName();
		}
	}

	UpdateData( FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// ---------------------------------------------------------------------------
//			OnOK
// ---------------------------------------------------------------------------
void CDlgAddDriver::OnOK() 
{
				// write the settings to ini
	if (! VerboseUpdateData ( TRUE))
		return;

	if ( ! m_dwDriverID)
	{
		::AfxMessageBox( IDERR_NODRIVER, MB_OK);
		return;
	}

	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	DRIVERINFO pf;
					// use defaults if there isn't one
		pf.bFlipPolarity = m_bFlipPolarity;
		pf.bIndieResponse = m_bIndieResponse;
		pf.dwDriverID = m_dwDriverID;
		pf.fOffset = m_fOffset;
		if ( MAXCHARLENGTH > m_strName.GetLength())
			strcpy( pf.szDrName, (LPCSTR )m_strName);
		else
			pf.szDrName[0] = '\0';
		
		capp->WriteRegistry( IDS_DRIVERINFO, &pf, sizeof( pf));
	}
	
	CDialog::OnOK();
}


// ---------------------------------------------------------------------------
//			OnDeltaposSpin1
// ---------------------------------------------------------------------------
void CDlgAddDriver::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

// ---------------------------------------------------------------------------
//			OnBrowse
// ---------------------------------------------------------------------------
void CDlgAddDriver::OnBrowse() 
{
CDlgSelectObject cdlg;

	cdlg.SetParms( m_pRoot, m_dwDriverID, ntDriver);

	if ( IDOK == cdlg.DoModal())
	{
		UpdateData( TRUE);			// update the other fields
		m_dwDriverID = cdlg.m_dwSelected;
		{
		CNamed *pname = m_pRoot->FindByID( m_dwDriverID);

			if ( pname)
			{
				m_csDriver = pname->GetFullName();
				m_strName = pname->GetName();
			}
		}

		UpdateData( FALSE);
	}
	
}


// ---------------------------------------------------------------------------
//			OnLButtonUp
// ---------------------------------------------------------------------------
void CDlgAddDriver::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! m_cfEdits.ProcessLeftClick( nFlags, point))
		CDialog::OnLButtonUp(nFlags, point);
}

// ---------------------------------------------------------------------------
//			OnRButtonUp
// ---------------------------------------------------------------------------
void CDlgAddDriver::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! 	m_cfEdits.ProcessRightClick( nFlags, point))
		CDialog::OnRButtonUp(nFlags, point);
}


// -------------------------------------------------------------------------------------
//		the AddDriver operation
// -------------------------------------------------------------------------------------
CXtAddDriver::CXtAddDriver( CObject *cTarget) : CXunary( cTarget)
{

}

CXtAddDriver::~CXtAddDriver()
{
}

UINT CXtAddDriver::GetNameID()
{
	return IDOP_ADDDRIVER;
}


// ---------------------------------------------------------------------------
//			DoDialog
// ---------------------------------------------------------------------------
UINT CXtAddDriver::DoDialog( )		// xeq dbox
{
CDlgAddDriver cdlg;
CNetwork *cname;
UINT uout;

	cname = (CNetwork *)FindTargetObject();

	if ( ! cname)
		return IDCANCEL;

	cdlg.m_pRoot = cname->GetRootObject();

	uout = cdlg.DoModal();
	if ( IDOK == uout)
		{
		m_fOffset = cdlg.m_fOffset;
		m_dwDriverID = cdlg.m_dwDriverID;		// the driver id
		m_bFlipPolarity = cdlg.m_bFlipPolarity;	// flip polarity
		m_bIndieResponse = cdlg.m_bIndieResponse;	// generate individual response
		m_strName = cdlg.m_strName;			// name in the dialog
		}

	return uout;

}

// ---------------------------------------------------------------------------
//			DoOperation
// ---------------------------------------------------------------------------
int CXtAddDriver::DoOperation( )	// xeq xform
{
CNetwork *cname;
ZpDriver *zp;

	cname = (CNetwork *)FindTargetObject();

	if ( ! cname)
		return 1;

	zp = new ZpDriver;

	zp->SetOffset( m_fOffset);
	zp->SetDriver( m_dwDriverID);
	zp->SetOutOfPhase( m_bFlipPolarity);
	zp->SetDoChart( m_bIndieResponse);

	zp->SetName( m_strName);
	zp->SetNode(0, 1000);
	zp->SetNode(1, 1001);
	zp->SetPosition( 0, 30);
	zp->SetPosition( 1, 30);
	cname->AddDriver( zp);
	cname->RenumberNodes();
	cname->UpdateViews();

	return 0;
}

UINT CXtAddDriver::GetDialog(void)		// get the dialog id
{
	return CDlgAddDriver::IDD;
}

