// DlgBurst.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "DlgBurst.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBurst property page

IMPLEMENT_DYNCREATE(CDlgBurst, CPropertyPage)

CDlgBurst::CDlgBurst() : CPropertyPage(CDlgBurst::IDD), m_cfEdits()
{
	//{{AFX_DATA_INIT(CDlgBurst)
	m_nCycles = 0;
	//}}AFX_DATA_INIT
}

CDlgBurst::~CDlgBurst()
{
}

void CDlgBurst::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgBurst)
	DDX_Text(pDX, IDC_BRSTCYCLES, m_nCycles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBurst, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgBurst)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBurst message handlers

BOOL CDlgBurst::OnInitDialog() 
{
	
	{		// initialize the spinner format group
	FormatGroup cfdata[3] = { 
							{IDC_FSTART,	IDC_SCRL1, 1.0f, 20000.0f, &m_fStart},
							{IDC_FEND,		IDC_SCRL2, 1.0f, 20000.0f, &m_fEnd},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CPropertyPage::OnInitDialog();

	{					// the spin button for the # of points
	CSpinButtonCtrl *pbutton;
	pbutton = (CSpinButtonCtrl *)GetDlgItem( IDC_SCRL3);
	if ( pbutton)
		pbutton->SetRange(1,100);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgBurst::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}
