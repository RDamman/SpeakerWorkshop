// dlgrmwal.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgrmwal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRoomWall property page

IMPLEMENT_DYNCREATE(CDlgRoomWall, CPropertyPage)

CDlgRoomWall::CDlgRoomWall() : CPropertyPage(CDlgRoomWall::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgRoomWall)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgRoomWall::~CDlgRoomWall()
{
}

void CDlgRoomWall::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgRoomWall::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRoomWall)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRoomWall, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgRoomWall)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgRoomWall, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgRoomWall)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRoomWall message handlers
