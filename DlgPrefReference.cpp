// DlgPrefReference.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "DlgPrefReference.h"

#include "Folder.h"

#include "DataSet.h"
#include "DlgSelec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefReference property page

IMPLEMENT_DYNCREATE(CDlgPrefReference, CPropertyPage)

CDlgPrefReference::CDlgPrefReference() : CPropertyPage(CDlgPrefReference::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgPrefReference)
	m_csLeftResponse = _T("");
	m_csRightResponse = _T("");
	m_csMicResponse = _T("");
	m_fMicSensitivity = 0.0f;
	//}}AFX_DATA_INIT
}

CDlgPrefReference::~CDlgPrefReference()
{
}

void CDlgPrefReference::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CPropertyPage::OnFinalRelease();
}

void CDlgPrefReference::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPrefReference)
	DDX_Text(pDX, IDC_LEFTRESP, m_csLeftResponse);
	DDX_Text(pDX, IDC_RIGHTRESP, m_csRightResponse);
	DDX_Text(pDX, IDC_MICRESP, m_csMicResponse);
	DDX_Text(pDX, IDC_MICSENSE, m_fMicSensitivity);
	DDV_MinMaxFloat(pDX, m_fMicSensitivity, 1.e-002f, 200.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPrefReference, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgPrefReference)
	ON_BN_CLICKED(IDC_LEFTBROWSE, OnLeftbrowse)
	ON_BN_CLICKED(IDC_RIGHTBROWSE, OnRightbrowse)
	ON_BN_CLICKED(IDC_MICBROWSE, OnMicbrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgPrefReference, CPropertyPage)
	//{{AFX_DISPATCH_MAP(CDlgPrefReference)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgPrefReference to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {A308C900-6D10-11CF-AA04-444553540000}
static const IID IID_IDlgPrefReference =
{ 0xa308c900, 0x6d10, 0x11cf, { 0xaa, 0x4, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgPrefReference, CPropertyPage)
	INTERFACE_PART(CDlgPrefReference, IID_IDlgPrefReference, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefReference message handlers
static int do_HitButton( CFolder *cRoot, CString& csName, DWORD& dwID, UNITMSR uom)
{
CDlgSelectObject cdlg;
int nrslt;

	cdlg.SetParms( cRoot, dwID, ntDataSet, uom);

	nrslt = cdlg.DoModal();
	if ( IDOK == nrslt)
		{
		dwID = cdlg.m_dwSelected;
		csName = "";
		if ( cdlg.m_dwSelected)
			{
			CNamed *cnam = cRoot->GetItem( cdlg.m_dwSelected);
			if ( cnam)
				csName = cnam->GetFullName();
			}
		return IDOK;
		}

	return nrslt;
		
}


void CDlgPrefReference::OnLeftbrowse() 
{

	if ( IDOK == do_HitButton( m_cRoot, m_csLeftResponse, m_dwLeftResponse, uomFreq) )
		UpdateData( FALSE);
		
	
}

void CDlgPrefReference::OnRightbrowse() 
{

	if ( IDOK == do_HitButton( m_cRoot, m_csRightResponse, m_dwRightResponse, uomFreq) )
		UpdateData( FALSE);
		
}

void CDlgPrefReference::OnMicbrowse() 
{
	
	if ( IDOK == do_HitButton( m_cRoot, m_csMicResponse, m_dwMicResponse, uomFreq) )
		UpdateData( FALSE);
		
}
