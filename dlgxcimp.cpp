// dlgxcimp.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "Folder.h"

#include "dlgxcimp.h"
#include "dlgSelec.h"

#include "DataSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static	DWORD dw_Reference = 0;		// only good for a while

/////////////////////////////////////////////////////////////////////////////
// CDlgXcImpedance dialog


CDlgXcImpedance::CDlgXcImpedance(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXcImpedance::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgXcImpedance)
	//}}AFX_DATA_INIT

	m_dwPicked = dw_Reference;
	m_pRoot = NULL;
		
}


void CDlgXcImpedance::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgXcImpedance::DoDataExchange(CDataExchange* pDX)
{
	if ( ! pDX->m_bSaveAndValidate)
		{
		CString cs("");
		CStatic *cctrl;
			if ( m_dwPicked)
				{
				CNamed *cnam = ((CFolder *)m_pRoot)->GetItem( m_dwPicked);
				if ( cnam)
					cs = cnam->GetFullName();
				}
			cctrl = (CStatic *)GetDlgItem( IDC_CALNAME);
			cctrl->SetWindowText( cs);
		}
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgXcImpedance)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXcImpedance, CDialog)
	//{{AFX_MSG_MAP(CDlgXcImpedance)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgXcImpedance, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgXcImpedance)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXcImpedance message handlers

BOOL CDlgXcImpedance::OnInitDialog() 
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgXcImpedance::OnBrowse() 
{
CDlgSelectObject cdlg;

	cdlg.SetParms( (CFolder *)m_pRoot, m_dwPicked, ntDataSet, uomFreq);

	if ( IDOK == cdlg.DoModal())
		{
		UpdateData( TRUE);			// update the other fields
		m_dwPicked = cdlg.m_dwSelected;
		UpdateData( FALSE);
		}
	
}

void CDlgXcImpedance::OnOK() 
{
BOOL bok = FALSE;

	// TODO: Add extra validation here
	if ( m_dwPicked)
		{
		CNamed *cnam = ((CFolder *)m_pRoot)->GetItem( m_dwPicked);
		if ( ntDataSet == cnam->GetType())
			{
			CDataSet *cdr = (CDataSet *)cnam;
			if ( uomFreq == cdr->GetUOM())
				bok = TRUE;
			}
		}
	if ( bok)
		dw_Reference = m_dwPicked;
	else
		{
		AfxMessageBox( IDS_ERR_VALIDDATA);
		return;			// don't do an OK
		}
	
	CDialog::OnOK();
}
