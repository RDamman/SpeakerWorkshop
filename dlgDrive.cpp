// dlgdrive.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "audtedoc.h"

#include "zFormEdt.h"
#include "dlgdrive.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDriver

IMPLEMENT_DYNAMIC(CDlgDriver, CPropertySheet)

CDlgDriver::CDlgDriver(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDS_DRIVER, pParentWnd, iSelectPage)
{
	EnableAutomation();

	AddPage( &m_cGeneral);
	AddPage( &m_cParms);
	AddPage( &m_cDatas);

	m_pDoc = NULL;

}

CDlgDriver::~CDlgDriver()
{
}

void CDlgDriver::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}


BEGIN_MESSAGE_MAP(CDlgDriver, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgDriver)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgDriver, CPropertySheet)
	//{{AFX_DISPATCH_MAP(CDlgDriver)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDriver message handlers


void CDlgDriver::UseDriver( CDriver *pcData)
{
	m_cGeneral.UseGeneral( pcData);
	DBG_TWO( "[DlgDriver.UseDriver] Document set to %s", m_pDoc->GetPathName());
	DBG_TWO( "[DlgDriver.UseDriver] Root set to: %s", m_pDoc->GetRoot()->GetName());
	m_cDatas.UseDatas( m_pDoc->GetRoot(), pcData);
	m_cParms.UseParms( pcData);
}


void CDlgDriver::SetDriver( CDriver *pcData)
{
	m_cGeneral.SetGeneral( pcData);
	m_cDatas.SetDatas( pcData);
	m_cParms.SetParms( pcData);

}


