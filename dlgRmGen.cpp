// dlgrmgen.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgrmgen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRoomGeneral property page

IMPLEMENT_DYNCREATE(CDlgRoomGeneral, CPropertyPage)

CDlgRoomGeneral::CDlgRoomGeneral() : CPropertyPage(CDlgRoomGeneral::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgRoomGeneral)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgRoomGeneral::~CDlgRoomGeneral()
{
}

void CDlgRoomGeneral::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgRoomGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRoomGeneral)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRoomGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgRoomGeneral)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgRoomGeneral, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgRoomGeneral)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRoomGeneral message handlers
