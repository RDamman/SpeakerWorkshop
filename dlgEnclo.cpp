// dlgenclo.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgenclo.h"

#include "Enclosur.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEnclosure

IMPLEMENT_DYNAMIC(CDlgEnclosure, CPropertySheet)

CDlgEnclosure::CDlgEnclosure(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDS_ENCLOSURE, pParentWnd, iSelectPage), m_cParms( IDS_CHAMBER1), m_cParms2(IDS_CHAMBER2)
{
	EnableAutomation();

	AddPage( &m_cGeneral);
	AddPage( &m_cParms);
	AddPage( &m_cParms2);

	m_cDupe = NULL;
	m_cWho = NULL;
	m_bWasApplied = FALSE;

}

CDlgEnclosure::~CDlgEnclosure()
{
	if ( m_cDupe)
		delete m_cDupe;
}

void CDlgEnclosure::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}


BEGIN_MESSAGE_MAP(CDlgEnclosure, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgEnclosure)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BEGIN_DISPATCH_MAP(CDlgEnclosure, CPropertySheet)
	//{{AFX_DISPATCH_MAP(CDlgEnclosure)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEnclosure message handlers

// prepare for the dialog box to be invoked by using the object
void CDlgEnclosure::UseObject( CEnclosure * cWho)
{

	m_cWho = cWho;			// the enclosure
	m_cDupe = (CEnclosure *)cWho->Duplicate();

	m_cGeneral.UseObject( cWho);
	m_cParms.UseObject( cWho);
	m_cParms2.UseObject( cWho);

}

// use the dialog box data to set the object
void CDlgEnclosure::SetObject( CEnclosure * cWho)
{

	m_cGeneral.SetObject( cWho);
	m_cParms.SetObject( cWho);
	m_cParms2.SetObject( cWho);


}


void CDlgEnclosure::ProcessApply()
{
CEnclosure *ce = (CEnclosure *)m_cWho;

	m_cGeneral.SetObject( m_cWho);
	m_cParms.SetObject( m_cWho);
	m_cParms2.SetObject( m_cWho);

	ce->BuildDataSets();
	ce->UpdateViews();				// if attached to a doc, update the views

	m_bWasApplied = TRUE;

//	CPropertySheet::OnApply();		// seems to send an idok to each propertypage

}

void CDlgEnclosure::ProcessCancel()
{
CEnclosure *cdest, *csource;

	if ( m_bWasApplied)
		{
		cdest = (CEnclosure *)m_cWho;
		csource = (CEnclosure *)m_cDupe;
		if ( cdest && csource)
			*cdest = *csource;

		cdest->BuildDataSets();		// update the datasets
		cdest->UpdateViews();		// if attached to a doc, update the views
		m_bWasApplied = FALSE;
		}
//	CPropertySheet::OnCancel();		// do a cancel

}

void CDlgEnclosure::ProcessOk()
{
CEnclosure *cdest, *csource;

	if ( m_bWasApplied)
		{
		cdest = (CEnclosure *)m_cWho;
		csource = (CEnclosure *)m_cDupe;
		if ( cdest && csource)
			*cdest = *csource;

		cdest->BuildDataSets();		// update the datasets
		cdest->UpdateViews();		// if attached to a doc, update the views
		m_bWasApplied = FALSE;
		}
//	CPropertySheet::OnOK();		// do a cancel

}


BOOL CDlgEnclosure::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ProcessCancel();			// no matter what, set it back	
	return CPropertySheet::DestroyWindow();
}
