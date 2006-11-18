// DlgDoc.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "DlgDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDoc

IMPLEMENT_DYNAMIC(CDlgDoc, CPropertySheet)

CDlgDoc::CDlgDoc(BOOL bRoot, CWnd* pParentWnd, UINT iSelectPage)
		:CPropertySheet(bRoot ? IDS_DOCUMENT : IDS_FOLDER, pParentWnd, iSelectPage)
{

		AddPage( &m_cGeneral);

}

CDlgDoc::~CDlgDoc()
{
}


BEGIN_MESSAGE_MAP(CDlgDoc, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDoc message handlers
void CDlgDoc::PostDialog(CAudtestDoc *pDoc)
{
	m_cGeneral.PostDialog( pDoc);

}

void CDlgDoc::PreDialog(CAudtestDoc *pDoc)
{
	m_cGeneral.PreDialog( pDoc);

}
