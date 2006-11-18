// DlgDisable48K.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "DlgDisable48K.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDisable48K dialog


CDlgDisable48K::CDlgDisable48K(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDisable48K::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDisable48K)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgDisable48K::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDisable48K)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDisable48K, CDialog)
	//{{AFX_MSG_MAP(CDlgDisable48K)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDisable48K message handlers

void CDlgDisable48K::OnOK() 
{
	CAudtestApp::SetDisable48K( true);		// yep, turn it off
	
	CDialog::OnOK();
}

void CDlgDisable48K::OnCancel() 
{
			// there's nothing to do here
	
	CDialog::OnCancel();
}
