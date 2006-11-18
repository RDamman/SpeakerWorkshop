// DlgNetLayout.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "DlgNetLayout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNetLayout dialog


CDlgNetLayout::CDlgNetLayout(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNetLayout::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgNetLayout)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgNetLayout::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CDlgNetLayout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNetLayout)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNetLayout, CDialog)
	//{{AFX_MSG_MAP(CDlgNetLayout)
	ON_BN_CLICKED(IDC_HORZ1, OnHorz1)
	ON_BN_CLICKED(IDC_HORZ2, OnHorz2)
	ON_BN_CLICKED(IDC_HORZ3, OnHorz3)
	ON_BN_CLICKED(IDC_VERT1, OnVert1)
	ON_BN_CLICKED(IDC_VERT2, OnVert2)
	ON_BN_CLICKED(IDC_VERT3, OnVert3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgNetLayout, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgNetLayout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgNetLayout to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {A9092EE0-8AEC-11CF-AA04-444553540000}
static const IID IID_IDlgNetLayout =
{ 0xa9092ee0, 0x8aec, 0x11cf, { 0xaa, 0x4, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgNetLayout, CDialog)
	INTERFACE_PART(CDlgNetLayout, IID_IDlgNetLayout, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNetLayout message handlers

static void set_Icon( CDialog *pDlg, UINT nID, UINT nIcon)
{
CWinApp *papp = AfxGetApp();
HICON hicon;

	hicon = papp->LoadIcon( nIcon);
	if ( hicon)			// the icon exists, at least
		{
		CButton *pbut = (CButton *)pDlg->GetDlgItem( nID);
		if ( pbut)
			pbut->SetIcon( hicon);
		}
}

BOOL CDlgNetLayout::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_nLayStyle = 0;
	// Set up the icon displays
	set_Icon( this, IDC_VERT1, IDR_COMPVERT1);
	set_Icon( this, IDC_VERT2, IDR_COMPVERT2);
	set_Icon( this, IDC_VERT3, IDR_COMPVERT3);
	set_Icon( this, IDC_HORZ1, IDR_COMPHORZ1);
	set_Icon( this, IDC_HORZ2, IDR_COMPHORZ2);
	set_Icon( this, IDC_HORZ3, IDR_COMPHORZ3);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNetLayout::OnHorz1() 
{
	m_nLayStyle = 1;
	EndDialog( IDOK);
}

void CDlgNetLayout::OnHorz2() 
{
	m_nLayStyle = 2;
	EndDialog( IDOK);
	
}

void CDlgNetLayout::OnHorz3() 
{
	m_nLayStyle = 3;
	EndDialog( IDOK);
	
}

void CDlgNetLayout::OnVert1() 
{
	m_nLayStyle = 4;
	EndDialog( IDOK);
	
}

void CDlgNetLayout::OnVert2() 
{
	m_nLayStyle = 5;
	EndDialog( IDOK);
	
}

void CDlgNetLayout::OnVert3() 
{
	m_nLayStyle = 6;
	EndDialog( IDOK);
	
}
