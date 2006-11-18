// dlgrenam.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgrenam.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRename dialog


CDlgRename::CDlgRename(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRename::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRename)
	m_csName = _T("");
	//}}AFX_DATA_INIT

	m_csTitle = "";
}


void CDlgRename::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRename)
	DDX_Text(pDX, IDC_NAME, m_csName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRename, CDialog)
	//{{AFX_MSG_MAP(CDlgRename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgRename message handlers

BOOL CDlgRename::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if ( m_csTitle.GetLength())			// there's a user title
		SetWindowText( m_csTitle);		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
