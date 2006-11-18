// dlgengen.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgengen.h"

#include "Enclosur.h"
#include "DlgEnclo.h"

#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEnGeneral property page

IMPLEMENT_DYNCREATE(CDlgEnGeneral, CPropertyPage)

CDlgEnGeneral::CDlgEnGeneral() : CPropertyPage(CDlgEnGeneral::IDD), m_cfEdits()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgEnGeneral)
	m_csDate = _T("");
	m_csDescript = _T("");
	m_csLastEdit = _T("");
	m_bInherit = FALSE;
	//}}AFX_DATA_INIT


}

CDlgEnGeneral::~CDlgEnGeneral()
{
}

void CDlgEnGeneral::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgEnGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgEnGeneral)
	DDX_Text(pDX, IDC_DATE, m_csDate);
	DDX_Text(pDX, IDC_DESCRIPT, m_csDescript);
	DDX_Text(pDX, IDC_LASTEDIT, m_csLastEdit);
	DDX_Check(pDX, IDC_INHERIT, m_bInherit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEnGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgEnGeneral)
	ON_EN_CHANGE(IDC_DESCRIPT, OnChangeDescript)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgEnGeneral, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgEnGeneral)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEnGeneral message handlers


// prepare for the dialog box to be invoked by using the object
void CDlgEnGeneral::UseObject( CEnclosure * cWho)
{

	cWho->SetDateStrings( m_csDate, m_csLastEdit);

	m_csDescript = cWho->GetDescription();

	m_fStart = cWho->m_fStart;
	m_fDelta = cWho->m_fDelta;
	m_fEnd = m_fStart + m_fDelta * cWho->m_nPoints;
	m_bInherit = cWho->m_bInherit;

	SetModified( TRUE);

}

// use the dialog box data to set the object
void CDlgEnGeneral::SetObject( CEnclosure * cWho)
{

	if ( GetSafeHwnd())
		if (! UpdateData( TRUE))		// we can't update data without an hwnd
			return;

	cWho->SetDescription( m_csDescript);
	cWho->SetLastEdit();

	cWho->m_fStart = m_fStart;
	cWho->m_fDelta = m_fDelta;
	cWho->m_nPoints = (int )ceil((double) (m_fEnd - m_fStart) / m_fDelta);
	cWho->m_bInherit = 0 != m_bInherit;

	SetModified( FALSE);	

}



void CDlgEnGeneral::OnChangeDescript() 
{
	SetModified( TRUE);	
}

BOOL CDlgEnGeneral::OnApply() 
{
	return CPropertyPage::OnApply();
}

void CDlgEnGeneral::OnCancel() 
{
CDlgEnclosure *cp = (CDlgEnclosure *)GetParent();

	cp->ProcessCancel();
	
	CPropertyPage::OnCancel();
}

void CDlgEnGeneral::OnOK() 
{
CDlgEnclosure *cp = (CDlgEnclosure *)GetParent();

	cp->ProcessApply();
	
	CPropertyPage::OnOK();
}

BOOL CDlgEnGeneral::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[4] = { 
							{IDC_START,	IDC_SPIN1, 0.0f, 199000.0f, &m_fStart},
							{IDC_END,	IDC_SPIN2, 0.0f, 199000.0f, &m_fEnd},
							{IDC_DELTA,	IDC_SPIN3, 0.0f, 199000.0f, &m_fDelta},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEnGeneral::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}
