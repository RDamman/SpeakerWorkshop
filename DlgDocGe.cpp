// DlgDocGe.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "DlgDocGe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDocGeneral property page

IMPLEMENT_DYNCREATE(CDlgDocGeneral, CPropertyPage)

CDlgDocGeneral::CDlgDocGeneral() : CPropertyPage(CDlgDocGeneral::IDD)
{
	//{{AFX_DATA_INIT(CDlgDocGeneral)
	m_csDate = _T("");
	m_csDescript = _T("");
	m_csLastEdit = _T("");
	//}}AFX_DATA_INIT
	m_pDocument = NULL;
}

CDlgDocGeneral::~CDlgDocGeneral()
{
}

void CDlgDocGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDocGeneral)
	DDX_Text(pDX, IDC_DATE, m_csDate);
	DDX_Text(pDX, IDC_DESCRIPT, m_csDescript);
	DDX_Text(pDX, IDC_LASTEDIT, m_csLastEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDocGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgDocGeneral)
	ON_EN_CHANGE(IDC_DESCRIPT, OnChangeDescript)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDocGeneral message handlers

void CDlgDocGeneral::PostDialog(CAudtestDoc *pDoc)
{
CFolder *proot = pDoc->GetRoot();

	if ( proot)
	{
	CString csold = proot->GetDescription();

		if (  csold.Compare( m_csDescript))	// has it changed???
		{
			proot->SetDescription( m_csDescript);
			proot->SetLastEdit();
			pDoc->SetModifiedFlag( TRUE);
		}
	}


}

void CDlgDocGeneral::PreDialog(CAudtestDoc *pDoc)
{
CFolder *proot = pDoc->GetRoot();

	m_pDocument = pDoc;

	if ( proot)
		{
		proot->SetDateStrings( m_csDate, m_csLastEdit);
		m_csDescript = proot->GetDescription();

		}
	SetModified( FALSE);

}

void CDlgDocGeneral::OnChangeDescript() 
{
	SetModified( TRUE);	
}

BOOL CDlgDocGeneral::OnApply() 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( m_pDocument)
	{
		ASSERT( m_pDocument->IsKindOf( RUNTIME_CLASS( CAudtestDoc)));
		PostDialog( m_pDocument);
		SetModified( FALSE);
	}
	
	return CPropertyPage::OnApply();
}
