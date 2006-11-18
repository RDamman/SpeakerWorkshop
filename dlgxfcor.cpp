// dlgxfcor.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgxfcor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgXfCorrelate dialog


CDlgXfCorrelate::CDlgXfCorrelate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXfCorrelate::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgXfCorrelate)
	m_nSize = 0;
	m_nRepeatCount = 0;
	//}}AFX_DATA_INIT
}


void CDlgXfCorrelate::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgXfCorrelate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgXfCorrelate)
	DDX_Control(pDX, IDC_SPINCNT, m_cSpinCount);
	DDX_Text(pDX, IDC_CORRELSIZE, m_nSize);
	DDX_Text(pDX, IDC_REPCOUNT, m_nRepeatCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXfCorrelate, CDialog)
	//{{AFX_MSG_MAP(CDlgXfCorrelate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgXfCorrelate, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgXfCorrelate)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXfCorrelate message handlers

BOOL CDlgXfCorrelate::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData( TRUE);			// get spincount control value

	m_cSpinCount.SetRange( 1, 10);

	UpdateData( FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
