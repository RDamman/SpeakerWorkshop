// DlgOptXover.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "DlgOptXover.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptXover dialog


CDlgOptXover::CDlgOptXover(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptXover::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgOptXover)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgOptXover::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CDlgOptXover::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptXover)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptXover, CDialog)
	//{{AFX_MSG_MAP(CDlgOptXover)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgOptXover, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgOptXover)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgOptXover to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {1B6B9BA0-895B-11CF-AA04-444553540000}
static const IID IID_IDlgOptXover =
{ 0x1b6b9ba0, 0x895b, 0x11cf, { 0xaa, 0x4, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgOptXover, CDialog)
	INTERFACE_PART(CDlgOptXover, IID_IDlgOptXover, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptXover message handlers
