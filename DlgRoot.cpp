// DlgRoot.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "DlgRoot.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRootView dialog


CDlgRootView::CDlgRootView(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRootView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRootView)
	m_csComments = _T("");
	m_csDrivers = _T("");
	m_csEnclosures = _T("");
	m_csFileDate = _T("");
	m_csLastEdit = _T("");
	m_csFileName = _T("");
	m_csFileSize = _T("");
	m_csNetworks = _T("");
	m_csFolderName = _T("");
	m_csFolderSize = _T("");
	m_csFolderDate = _T("");
	m_csFolderLast = _T("");
	//}}AFX_DATA_INIT
}


void CDlgRootView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRootView)
	DDX_Text(pDX, IDC_COMMENTS, m_csComments);
	DDX_Text(pDX, IDC_DRIVERS, m_csDrivers);
	DDX_Text(pDX, IDC_ENCLOSURES, m_csEnclosures);
	DDX_Text(pDX, IDC_FILEDATE, m_csFileDate);
	DDX_Text(pDX, IDC_FILELAST, m_csLastEdit);
	DDX_Text(pDX, IDC_FILENAME, m_csFileName);
	DDX_Text(pDX, IDC_FILESIZE, m_csFileSize);
	DDX_Text(pDX, IDC_NETWORKS, m_csNetworks);
	DDX_Text(pDX, IDC_FOLDERNAME, m_csFolderName);
	DDX_Text(pDX, IDC_FOLDERSIZE, m_csFolderSize);
	DDX_Text(pDX, IDC_FOLDERDATE, m_csFolderDate);
	DDX_Text(pDX, IDC_FOLDERLAST, m_csFolderLast);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRootView, CDialog)
	//{{AFX_MSG_MAP(CDlgRootView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRootView message handlers

void CDlgRootView::OnOK() 
{
	UpdateData( TRUE);
	
}

void CDlgRootView::OnCancel() 
{
	
}


