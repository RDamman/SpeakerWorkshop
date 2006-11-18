// DlgNotch.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "DlgNotch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNotch dialog


CDlgNotch::CDlgNotch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNotch::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgNotch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgNotch::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CDlgNotch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNotch)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNotch, CDialog)
	//{{AFX_MSG_MAP(CDlgNotch)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgNotch, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgNotch)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgNotch to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {5401F4E2-897F-11CF-AA04-444553540000}
static const IID IID_IDlgNotch =
{ 0x5401f4e2, 0x897f, 0x11cf, { 0xaa, 0x4, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgNotch, CDialog)
	INTERFACE_PART(CDlgNotch, IID_IDlgNotch, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNotch message handlers
