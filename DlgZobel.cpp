// DlgZobel.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "xform.h"
#include "Network.h"
#include "Passive.h"

#include "DlgZobel.h"

#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct tagZOBELINFO
{
	float	fFreq;			// frequency of interest
	DWORD	dwDriver;		// driver id
	int		nType;			// type of compensation (resonance,inductive)
	BOOL	bUseDriver;		// use the driver as input???
} ZOBELINFO;

/////////////////////////////////////////////////////////////////////////////
// CDlgZobel dialog


CDlgZobel::CDlgZobel(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgZobel::IDD, pParent), m_cfEdits()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgZobel)
	m_nDriver = -1;
	m_nType = -1;
	//}}AFX_DATA_INIT
}


void CDlgZobel::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CDlgZobel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	if ( ! pDX->m_bSaveAndValidate)		// data to dbox
		{								// convert dwdriver to ndriver
		CComboBox *pbox = (CComboBox *)GetDlgItem( IDC_SELDRIVER);
		if ( pbox)
			{
			int i;
			for ( i=0; i < pbox->GetCount(); i++)
				if ( m_dwDriver == pbox->GetItemData( i))
					{
					m_nDriver = i;
					break;
					}
			if ( i == pbox->GetCount())		// not found
				{
				m_nDriver = 0;
				m_dwDriver = pbox->GetItemData(0);
				}
			}
		CheckRadioButton(IDC_RADIO1, IDC_RADIO2, m_bUseDriver ? IDC_RADIO2 : IDC_RADIO1);
		}

	//{{AFX_DATA_MAP(CDlgZobel)
	DDX_CBIndex(pDX, IDC_SELDRIVER, m_nDriver);
	DDX_CBIndex(pDX, IDC_TYPE, m_nType);
	//}}AFX_DATA_MAP
	if ( pDX->m_bSaveAndValidate)			// dbox to data
		{								// convert index to dwdriver
		CComboBox *pbox = (CComboBox *)GetDlgItem( IDC_SELDRIVER);
		if ( pbox)
			{
			m_dwDriver = pbox->GetItemData( m_nDriver);
			}
		m_bUseDriver = IsDlgButtonChecked( IDC_RADIO2);
		}
}


BEGIN_MESSAGE_MAP(CDlgZobel, CDialog)
	//{{AFX_MSG_MAP(CDlgZobel)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgZobel, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgZobel)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgZobel to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {5401F4E0-897F-11CF-AA04-444553540000}
static const IID IID_IDlgZobel =
{ 0x5401f4e0, 0x897f, 0x11cf, { 0xaa, 0x4, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgZobel, CDialog)
	INTERFACE_PART(CDlgZobel, IID_IDlgZobel, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgZobel message handlers

BOOL CDlgZobel::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[2] = { 
							{IDC_FREQ,	IDC_SCRL1, 1.0f, 20000.0f, &m_fFreq},
							{0,0,0.0f,0.0f,NULL}
							};
		m_cfEdits.AttachGroup( this, cfdata);
	}

	::ComboFillString( this, IDC_TYPE, IDS_COMPEN_TYPE);

	{						// fill the combo box
	CComboBox *wmd = (CComboBox *)GetDlgItem( IDC_SELDRIVER);
	int i;

		if ( m_pNetwork && wmd)
			for ( i=0; m_pNetwork->GetDriver(i); i++)
				{
				ZpDriver *pdrive = (ZpDriver *)m_pNetwork->GetDriver(i);
				int nloc = wmd->AddString( pdrive->GetName());
				wmd->SetItemData( nloc, pdrive->GetDriver());
				}
		m_nDriver = 0;			// init to 0
		m_dwDriver = wmd->GetItemData(0);
	}

	{		// read the old settings from ini
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	ZOBELINFO xv;

		if ( ! capp->ReadRegistry( IDS_ZOBELINFO, &xv, sizeof( xv)))
			{
			m_fFreq = xv.fFreq;
			m_nType = xv.nType;
			m_dwDriver = xv.dwDriver;
			m_bUseDriver = xv.bUseDriver;
			}
		else
			{
			m_fFreq = 10.0f;
			m_nType = 0;
			m_bUseDriver = FALSE;
			}
	}

	CDialog::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgZobel::OnOK() 
{

	// write the settings to ini
	if ( ! VerboseUpdateData( TRUE))
		return;

	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	ZOBELINFO xv;

		xv.fFreq = m_fFreq;
		xv.nType = m_nType;
		xv.dwDriver = m_dwDriver;
		xv.bUseDriver = m_bUseDriver;
		capp->WriteRegistry( IDS_ZOBELINFO, &xv, sizeof( xv));
	}
	
	CDialog::OnOK();
}


void CDlgZobel::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	
	*pResult = 0;
}


// -------------------------------------------------------------------------------------
//		the Zobel operation
// -------------------------------------------------------------------------------------
CXtZobel::CXtZobel( CObject *cTarget) : CXunary( cTarget)
{
	m_dwDriver = 0;
}

CXtZobel::~CXtZobel()
{
}


UINT CXtZobel::DoDialog( )		// xeq dbox
{
CDlgZobel cdlg;
CNetwork *cname;
UINT uout;

	cname = (CNetwork *)FindTargetObject();

	if ( ! cname)
		return IDCANCEL;

	cdlg.m_pNetwork = cname;

	uout = cdlg.DoModal();
	if ( IDOK == uout)
		{
		m_fFreq		= cdlg.m_fFreq;
		m_nType		= cdlg.m_nType;
		m_dwDriver  = cdlg.m_dwDriver;
		m_bUseDriver = cdlg.m_bUseDriver;
		}

	return uout;

}

int CXtZobel::DoOperation( )	// xeq xform
{
CNetwork *cname;
int nerr;

	cname = (CNetwork *)FindTargetObject();

	if ( ! cname)
		return 1;

	nerr = cname->AddZobel(m_dwDriver, m_nType, m_fFreq, m_bUseDriver);
	if ( nerr)
		{
		switch( nerr)
			{
			case 1 :		// unable to find a driver
				::AfxMessageBox( IDERR_NODRIVER);
				break;
			case 2 :
				::AfxMessageBox( IDERR_NOIMPED);
				break;
			case 3 :
				::AfxMessageBox( IDERR_BADFREQ);
				break;
			case 4 :
				::AfxMessageBox( IDERR_DRVNOIMP);
				break;
			default :
				ASSERT(0);		// oops
				break;
			}
		}
	cname->UpdateViews();

	return 0;
}

UINT CXtZobel::GetDialog(void)		// get the dialog id
{
	return IDD_COMPENSATION;
}



