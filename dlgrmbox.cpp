// dlgrmbox.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgrmbox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRoomBoxes property page

IMPLEMENT_DYNCREATE(CDlgRoomBoxes, CPropertyPage)

CDlgRoomBoxes::CDlgRoomBoxes() : CPropertyPage(CDlgRoomBoxes::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgRoomBoxes)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgRoomBoxes::~CDlgRoomBoxes()
{
}

void CDlgRoomBoxes::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgRoomBoxes::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRoomBoxes)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRoomBoxes, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgRoomBoxes)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgRoomBoxes, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgRoomBoxes)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRoomBoxes message handlers
