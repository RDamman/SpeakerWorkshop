// DlgMsrIn.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "DlgMsrIn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMsrIntermod dialog


CDlgMsrIntermod::CDlgMsrIntermod(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMsrIntermod::IDD, pParent), m_cfEdits()
{
	//{{AFX_DATA_INIT(CDlgMsrIntermod)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgMsrIntermod::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgMsrIntermod)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMsrIntermod, CDialog)
	//{{AFX_MSG_MAP(CDlgMsrIntermod)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL3, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMsrIntermod message handlers

BOOL CDlgMsrIntermod::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[4] = { 
							{IDC_FREQ1,			IDC_SCRL1, 1.0f,   20000.0f, &m_fFreqStart},
							{IDC_FREQ2,			IDC_SCRL2, 1.0f,   20000.0f, &m_fFreqEnd},
							{IDC_WATT,			IDC_SCRL3, 0.01f,    100.0f, &m_fPower},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CDialog::OnInitDialog();
	
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMsrIntermod::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}
