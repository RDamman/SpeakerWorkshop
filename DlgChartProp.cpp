// DlgChartProp.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "DlgChartProp.h"
#include "Chart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgChartProp dialog


CDlgChartProp::CDlgChartProp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChartProp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgChartProp)
	m_csDate = _T("");
	m_csDescript = _T("");
	m_csLastEdit = _T("");
	//}}AFX_DATA_INIT
}


void CDlgChartProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChartProp)
	DDX_Text(pDX, IDC_DATE, m_csDate);
	DDX_Text(pDX, IDC_DESCRIPT, m_csDescript);
	DDX_Text(pDX, IDC_LASTEDIT, m_csLastEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgChartProp, CDialog)
	//{{AFX_MSG_MAP(CDlgChartProp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChartProp message handlers

void CDlgChartProp::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CDlgChartProp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_csDescript = m_pcChart->GetDescription();
	m_pcChart->SetDateStrings( m_csDate, m_csLastEdit);

	UpdateData( FALSE);		// update the dbox

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
