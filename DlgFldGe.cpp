// DlgFldGe.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "DlgFldGe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFldGeneral property page

IMPLEMENT_DYNCREATE(CDlgFldGeneral, CPropertyPage)

CDlgFldGeneral::CDlgFldGeneral() : CPropertyPage(CDlgFldGeneral::IDD)
{
	//{{AFX_DATA_INIT(CDlgFldGeneral)
	m_csDate = _T("");
	m_csDescript = _T("");
	m_csLastEdit = _T("");
	//}}AFX_DATA_INIT
}

CDlgFldGeneral::~CDlgFldGeneral()
{
}

void CDlgFldGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFldGeneral)
	DDX_Text(pDX, IDC_DATE, m_csDate);
	DDX_Text(pDX, IDC_DESCRIPT, m_csDescript);
	DDX_Text(pDX, IDC_LASTEDIT, m_csLastEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFldGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgFldGeneral)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFldGeneral message handlers



void CDlgFldGeneral::SetFolder(CFolder *pFolder)
{
	m_pFolder = pFolder;
}

BOOL CDlgFldGeneral::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	if ( m_pFolder)
	{
		m_pFolder->SetDateStrings( m_csDate, m_csLastEdit);
		m_csDescript = m_pFolder->GetDescription();
	}

	UpdateData( FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgFldGeneral::OnApply() 
{

	if ( m_pFolder)
	{
	CString csold = m_pFolder->GetDescription();


		UpdateData( TRUE);
	
		if (  csold.Compare( m_csDescript))	// has it changed???
		{
			m_pFolder->SetDescription( m_csDescript);
			m_pFolder->SetLastEdit();
			m_pFolder->GetDocument()->SetModifiedFlag( TRUE);
		}
	}
	
	return CPropertyPage::OnApply();
}
