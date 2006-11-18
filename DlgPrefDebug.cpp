// DlgPrefDebug.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "DlgPrefDebug.h"

#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefDebug property page

IMPLEMENT_DYNCREATE(CDlgPrefDebug, CPropertyPage)

CDlgPrefDebug::CDlgPrefDebug() : CPropertyPage(CDlgPrefDebug::IDD), m_cfEdits()
{
	//{{AFX_DATA_INIT(CDlgPrefDebug)
	m_bDebug = FALSE;
	m_iWarmamount = 0;
	//}}AFX_DATA_INIT
}

CDlgPrefDebug::~CDlgPrefDebug()
{
}

void CDlgPrefDebug::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgPrefDebug)
	DDX_Check(pDX, IDC_DEBUGON, m_bDebug);
	DDX_Text(pDX, IDC_WARMUP, m_iWarmamount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPrefDebug, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgPrefDebug)
	ON_BN_CLICKED(IDC_DEBUGON, OnDebugon)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefDebug message handlers

BOOL CDlgPrefDebug::OnApply() 
{

	if ( ! VerboseUpdateData( TRUE))
		return 0;

	CTopDebug::GetDebugObj()->SetDebugLevel( m_bDebug ? 1 : 0);
	CAudtestApp::SetLatency( m_fLatent);
	CAudtestApp::SetWarmup( m_iWarmamount);
	SetModified( FALSE);
	
	return CPropertyPage::OnApply();
}

BOOL CDlgPrefDebug::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[2] = { 
							{IDC_LATENCY,	IDC_SPIN1, -10000.0f, 10000.0f, &m_fLatent},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	{
	CSpinButtonCtrl *cspin = (CSpinButtonCtrl *)GetDlgItem( IDC_SPIN2);

		cspin->SetRange( 0, 500);
	}

	CPropertyPage::OnInitDialog();
	
	m_bDebug = (0 != CTopDebug::GetDebugObj()->GetDebugLevel());
	CAudtestApp::GetLatency( &m_fLatent);
	m_iWarmamount = CAudtestApp::GetWarmup();

	UpdateData( FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPrefDebug::OnDebugon() 
{
	SetModified( TRUE);	
}

void CDlgPrefDebug::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	
	*pResult = 0;
}
