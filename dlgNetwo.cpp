// dlgnetwo.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgNetwo.h"

// #include "named.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNetwork

IMPLEMENT_DYNAMIC(CDlgNetwork, CPropertySheet)

CDlgNetwork::CDlgNetwork(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDS_NETWORK, pParentWnd, iSelectPage)
{
	EnableAutomation();

	m_bDidApply = false;			// don't reapply

	m_cGeneral.m_pParent = this;
	m_cDatalist.m_pParent = this;
	m_cDrivers.m_pParent = this;

	AddPage( &m_cGeneral);
	AddPage( &m_cDatalist);
	AddPage( &m_cDrivers);

}

CDlgNetwork::~CDlgNetwork()
{
}

void CDlgNetwork::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}


BEGIN_MESSAGE_MAP(CDlgNetwork, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgNetwork)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgNetwork, CPropertySheet)
	//{{AFX_DISPATCH_MAP(CDlgNetwork)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNetwork message handlers



void CDlgNetwork::UseNetwork( CNetwork *pcData, CObject *cSubject)
{
	m_cGeneral.UseGeneral( pcData);
	m_cDatalist.UseNetlist( pcData, cSubject);
	m_cDrivers.UseDrivers( pcData, cSubject);
}


void CDlgNetwork::SetNetwork( CNetwork *pcData)
{
	m_cGeneral.SetGeneral( pcData);
	m_cDatalist.SetNetlist( pcData);
	m_cDrivers.SetDrivers( pcData);

}


void CDlgNetwork::SetReapply( bool bNew)
{
	m_bDidApply = bNew;

	PostMessage( WM_COMMAND, IDOK);
}


