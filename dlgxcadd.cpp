// dlgxcadd.cpp : implementation file
//				CDlxXfCombine
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgxcadd.h"

#include "Folder.h"

#include "dataset.h"
#include "dlgSelec.h"

#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

typedef struct tagCALCADDINFO
	{
	DWORD dwReference;
	int nOperation;
	} CALCADDINFO;

/////////////////////////////////////////////////////////////////////////////
// CDlgXcAdd dialog


CDlgXcAdd::CDlgXcAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXcAdd::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgXcAdd)
	m_nOperation = -1;
	//}}AFX_DATA_INIT

	{
	CALCADDINFO fi;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		if ( capp->ReadRegistry( IDS_CALCADDINFO, &fi, sizeof(fi)))	// success???
			{		// failure, we need to set it
			fi.nOperation = 0;
			fi.dwReference = 0;
			}
		m_nOperation = fi.nOperation;
		m_dwPicked = fi.dwReference;
	}

	m_dwSource = 0;
	
}


void CDlgXcAdd::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgXcAdd::DoDataExchange(CDataExchange* pDX)
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
			cctrl = (CStatic *)GetDlgItem( IDC_DEST);
			cctrl->SetWindowText( cs);
			cs = "";		// reset to nothing
			if ( m_dwSource)
				{
				CNamed *cnam = ((CFolder *)m_pRoot)->GetItem( m_dwSource);
				if ( cnam)
					cs = cnam->GetFullName();
				}
			cctrl = (CStatic *)GetDlgItem( IDC_SOURCE);
			cctrl->SetWindowText( cs);
		}
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgXcAdd)
	DDX_CBIndex(pDX, IDC_OPERATION, m_nOperation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXcAdd, CDialog)
	//{{AFX_MSG_MAP(CDlgXcAdd)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgXcAdd, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgXcAdd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXcAdd message handlers

BOOL CDlgXcAdd::OnInitDialog() 
{

	CDialog::OnInitDialog();

	::ComboFillString( this, IDC_OPERATION, IDS_XCADD_OPERATION);

	UpdateData( FALSE);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgXcAdd::OnBrowse() 
{				// select the secondary file for the selection
CDlgSelectObject cdlg;
CDataSet *cdsrc = (CDataSet *)m_pRoot->GetItem( m_dwSource);

	cdlg.SetParms( m_pRoot, m_dwPicked, ntDataSet, cdsrc->GetUOM());

	if ( IDOK == cdlg.DoModal())
		{
		UpdateData( TRUE);			// update the other fields
		m_dwPicked = cdlg.m_dwSelected;
		UpdateData( FALSE);
		}
	
}


void CDlgXcAdd::OnOK() 
{
BOOL bok = FALSE;
UNITMSR uomme = uomAny;

	CNamed *cnam = ((CFolder *)m_pRoot)->GetItem( m_dwSource);
	if ( ntDataSet == cnam->GetType())
		{
		CDataSet *cdr = (CDataSet *)cnam;
		uomme = cdr->GetUOM();
		}

	if ( m_dwPicked)
		{
		CNamed *cnam = ((CFolder *)m_pRoot)->GetItem( m_dwPicked);
		if ( ntDataSet == cnam->GetType())
			{
			CDataSet *cdr = (CDataSet *)cnam;
			if ( uomme == cdr->GetUOM())
				bok = TRUE;
			}
		}
	if ( ! bok)
		{
		AfxMessageBox( IDS_ERR_VALIDDATA);
		return;			// don't do an OK
		}
	
	if ( UpdateData( TRUE))
		{
		CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
		CALCADDINFO fi;

			fi.nOperation = m_nOperation;
			fi.dwReference = m_dwPicked;
			capp->WriteRegistry( IDS_CALCADDINFO, &fi, sizeof(fi) );	// success???
		}

	CDialog::OnOK();
}
