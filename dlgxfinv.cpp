// dlgxfinv.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgxfinv.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

typedef struct tagINVERTINFO
	{
	BOOL bInvertData;
	BOOL bInvertPhase;
	} INVERTINFO;

/////////////////////////////////////////////////////////////////////////////
// CDlgXfInvert dialog


CDlgXfInvert::CDlgXfInvert(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXfInvert::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgXfInvert)
	m_bInvertData = TRUE;
	m_bInvertPhase = FALSE;
	//}}AFX_DATA_INIT

	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	INVERTINFO fi;
	if ( ! 	capp->ReadRegistry( IDS_INVERTINFO, &fi, sizeof(fi) ))	// success???
		{
		m_bInvertData = fi.bInvertData;
		m_bInvertPhase = fi.bInvertPhase;
		}
	}

}


void CDlgXfInvert::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgXfInvert::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgXfInvert)
	DDX_Check(pDX, IDC_INVDATA, m_bInvertData);
	DDX_Check(pDX, IDC_INVPHASE, m_bInvertPhase);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXfInvert, CDialog)
	//{{AFX_MSG_MAP(CDlgXfInvert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgXfInvert, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgXfInvert)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXfInvert message handlers

void CDlgXfInvert::OnOK() 
{
	if ( UpdateData( TRUE))
		{
		CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
		INVERTINFO fi;

			fi.bInvertData = m_bInvertData;
			fi.bInvertPhase = m_bInvertPhase;
			capp->WriteRegistry( IDS_INVERTINFO, &fi, sizeof(fi) );	// success???
		}
	
	CDialog::OnOK();
}
