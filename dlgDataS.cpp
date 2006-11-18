// dlgdatas.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dataset.h"

#include "dlgdatas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDataset

IMPLEMENT_DYNAMIC(CDlgDataset, CPropertySheet)

CDlgDataset::CDlgDataset(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDS_DATASET, pParentWnd, iSelectPage), m_cGeneral(), m_cDataset()
{
	EnableAutomation();

	AddPage( &m_cGeneral);
	AddPage( &m_cDataset);

}

CDlgDataset::~CDlgDataset()
{
}

void CDlgDataset::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}




BEGIN_MESSAGE_MAP(CDlgDataset, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgDataset)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgDataset, CPropertySheet)
	//{{AFX_DISPATCH_MAP(CDlgDataset)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDataset message handlers

// called before the dialog is shown
void CDlgDataset::PreDialog( CDataSet *pcData)
{
	m_cGeneral.PreDialog( pcData);
	m_cDataset.PreDialog( pcData);
}

// called after ok is pressed
void CDlgDataset::PostDialog( CDataSet *pcData)
{
	m_cGeneral.PostDialog( pcData);
	m_cDataset.PostDialog( pcData);

}


