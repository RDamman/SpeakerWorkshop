// DlgFolder.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "DlgFolder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFolder

IMPLEMENT_DYNAMIC(CDlgFolder, CPropertySheet)

CDlgFolder::CDlgFolder(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDS_FOLDER, pParentWnd, iSelectPage)
{

		AddPage( &m_cGeneral);

}

CDlgFolder::~CDlgFolder()
{
}


BEGIN_MESSAGE_MAP(CDlgFolder, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgFolder)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFolder message handlers

void CDlgFolder::SetFolder( CFolder *pFolder)
{
	m_pFolder = pFolder;
	m_cGeneral.SetFolder( pFolder);
}