// dlgxfsmo.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgxfsmo.h"
#include "Utils.h"

#include "Xform.h"
#include "XformAll.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


typedef struct tagDLGSMOOTH
	{
	int nMethod;
	int nStyle;
	float fCustom;
	} SMOOTHINFO;

/////////////////////////////////////////////////////////////////////////////
// CDlgXfSmooth dialog


CDlgXfSmooth::CDlgXfSmooth(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXfSmooth::IDD, pParent), m_cfEdits()
{
	EnableAutomation();

	m_pCX = NULL;
	m_cdSource = NULL;

	//{{AFX_DATA_INIT(CDlgXfSmooth)
	m_nMethod = -1;
	//}}AFX_DATA_INIT
}


void CDlgXfSmooth::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgXfSmooth::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgXfSmooth)
	DDX_CBIndex(pDX, IDC_METHOD, m_nMethod);
	//}}AFX_DATA_MAP
	if ( pDX->m_bSaveAndValidate)
		{
		int i;

		for ( i=0; i<9; i++)
			if ( IsDlgButtonChecked( IDC_RSMOOTH1 + i) )
				{
				m_nStyle = i;
				break;
				}
		}
	else
		{
		int nradio = IDC_RSMOOTH1 + m_nStyle;
		CheckRadioButton(IDC_RSMOOTH1, IDC_RSMOOTH9, nradio);
		}

}


BEGIN_MESSAGE_MAP(CDlgXfSmooth, CDialog)
	//{{AFX_MSG_MAP(CDlgXfSmooth)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposSpin)
	ON_EN_CHANGE(IDC_CUSTOM, OnChangeCustom)
	ON_BN_CLICKED(IDAPPLY, OnApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgXfSmooth, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgXfSmooth)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXfSmooth message handlers

BOOL CDlgXfSmooth::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[2] = { 
							{IDC_CUSTOM,	IDC_SCRL1, 0.0f, 2000000.0f, &m_fCustom},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CDialog::OnInitDialog();

	::ComboFillString( this, IDC_METHOD, IDS_XFSMOOTH_METHOD);
	
	{
	SMOOTHINFO clc;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		if ( ! capp->ReadRegistry( IDS_SMOOTHINFO, &clc, sizeof(clc)))
			{
			m_nStyle = clc.nStyle;
			m_nMethod = clc.nMethod;
			m_fCustom = clc.fCustom;
			}
	}

	UpdateData( FALSE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgXfSmooth::OnOK() 
{
	if ( ! VerboseUpdateData( TRUE))
		return;

	if ( m_pCX)
	{
		m_pCX->DoUndo();			// undo it
		delete m_pCX;				// clean up
	}

	{
	SMOOTHINFO clc;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		clc.nStyle = m_nStyle;
		clc.nMethod = m_nMethod;
		clc.fCustom = m_fCustom;
		capp->WriteRegistry( IDS_SMOOTHINFO, &clc, sizeof(clc));
	}
	
	CDialog::OnOK();
}

void CDlgXfSmooth::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

void CDlgXfSmooth::OnChangeCustom() 
{
int nradio = IDC_RSMOOTH9;

	CheckRadioButton(IDC_RSMOOTH1, IDC_RSMOOTH9, nradio);
	
}

void CDlgXfSmooth::OnApply() 
{
	if ( ! m_cdSource)
		return;

	if ( ! VerboseUpdateData( TRUE))
		return;

	if ( m_pCX)
	{
		m_pCX->DoUndo();			// undo it
		delete m_pCX;				// clean up
	}
	m_pCX = new CXformSmooth( m_cdSource);		// the transform

	m_pCX->SetStyle( m_nStyle);
	m_pCX->SetCustom( m_fCustom);
	m_pCX->SetMethod( m_nMethod);

	m_pCX->DoExe( true);		// allow undo
	
}

void CDlgXfSmooth::OnCancel() 
{
	if ( m_pCX)
	{
		m_pCX->DoUndo();			// undo it
		delete m_pCX;				// clean up
	}
	
	CDialog::OnCancel();
}
