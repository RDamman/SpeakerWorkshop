// dlgdatas.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgPrefer.h"

#include "fxFont.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPreference

IMPLEMENT_DYNAMIC(CDlgPreference, CPropertySheet)

CDlgPreference::CDlgPreference(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDS_PREFERENCE, pParentWnd, iSelectPage), m_cMeasure(),
	m_cImpedance(), m_cNetwork(), m_cCharts(), m_cMarker()
{

	EnableAutomation();

//	AddPage( &m_cTransform);
	AddPage( &m_cMeasure);
	AddPage( &m_cImpedance);
	AddPage( &m_cNetwork);
	AddPage( &m_cCharts);
	AddPage( &m_cMarker);
	AddPage( &m_cGeneral);
	AddPage( &m_cDebug);
	AddPage( &m_cAcoustic);
//	AddPage( &m_cReference);

	SetActivePage( CAudtestApp::GetLastPreference() );
}

CDlgPreference::~CDlgPreference()
{
}

void CDlgPreference::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}




BEGIN_MESSAGE_MAP(CDlgPreference, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgPreference)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgPreference, CPropertySheet)
	//{{AFX_DISPATCH_MAP(CDlgPreference)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPreference message handlers


BOOL CDlgPreference::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
NMHDR *pnmhdr = (NMHDR *)lParam;


       if (TCN_SELCHANGE == pnmhdr->code)
       {
		   CAudtestApp::SetLastPreference( GetActiveIndex());
	   }
           
	
	return CPropertySheet::OnNotify(wParam, lParam, pResult);
}
