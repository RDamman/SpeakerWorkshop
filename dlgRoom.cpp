// dlgroom.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgroom.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRoom

IMPLEMENT_DYNAMIC(CDlgRoom, CPropertySheet)

CDlgRoom::CDlgRoom(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDS_ROOM, pParentWnd, iSelectPage)
{
	EnableAutomation();

	AddPage( &m_cGeneral);
	AddPage( &m_cWalls);
	AddPage( &m_cBoxes);

}

CDlgRoom::~CDlgRoom()
{
}

void CDlgRoom::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}


BEGIN_MESSAGE_MAP(CDlgRoom, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgRoom)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgRoom, CPropertySheet)
	//{{AFX_DISPATCH_MAP(CDlgRoom)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRoom message handlers
