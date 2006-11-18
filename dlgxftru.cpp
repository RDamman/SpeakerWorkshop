// dlgxftru.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgxftru.h"

#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

typedef struct tagTRUNCATE
	{
	BOOL	bUseMarker;
	float	fStart;
	float	fEnd;
	} TRUNCATEINFO;

/////////////////////////////////////////////////////////////////////////////
// CDlgXfTruncate dialog


CDlgXfTruncate::CDlgXfTruncate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXfTruncate::IDD, pParent), m_cfEdits()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgXfTruncate)
	//}}AFX_DATA_INIT

	m_bUseMarker = TRUE;

	{
	TRUNCATEINFO fi;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		if ( ! capp->ReadRegistry( IDS_TRUNCATEINFO, &fi, sizeof(fi)))	// success???
			{
			m_fStart = fi.fStart;
			m_fEnd = fi.fEnd;
			m_bUseMarker = fi.bUseMarker;
			}
	}


}


void CDlgXfTruncate::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgXfTruncate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgXfTruncate)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXfTruncate, CDialog)
	//{{AFX_MSG_MAP(CDlgXfTruncate)
	ON_EN_CHANGE(IDC_END, OnChangeEnd)
	ON_EN_CHANGE(IDC_START, OnChangeStart)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgXfTruncate, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgXfTruncate)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXfTruncate message handlers

void CDlgXfTruncate::OnOK() 
{
	if (! VerboseUpdateData( TRUE))
		return;

	m_bUseMarker = IsDlgButtonChecked( IDC_USEMARKER);
	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	TRUNCATEINFO fi;

		fi.fStart = m_fStart;
		fi.fEnd =	m_fEnd;
		fi.bUseMarker = m_bUseMarker;

		capp->WriteRegistry( IDS_TRUNCATEINFO, &fi, sizeof(fi) );	// success???
	}

	CDialog::OnOK();
}

BOOL CDlgXfTruncate::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[3] = { 
							{IDC_START,	IDC_SCRL1, 0.0f, 20000.0f, &m_fStart},
							{IDC_END,	IDC_SCRL2, 0.0f, 20000.0f, &m_fEnd},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CDialog::OnInitDialog();
	
CStatic *cctrl;
CString cs;

	FullFormatValue( cs, m_fStartMarker, 0);
	cctrl = (CStatic *)GetDlgItem( IDC_MARKLOW);
	cctrl->SetWindowText( cs);

	FullFormatValue( cs, m_fEndMarker, 0);
	cctrl = (CStatic *)GetDlgItem( IDC_MARKHIGH);
	cctrl->SetWindowText( cs);

	CheckRadioButton( IDC_USEMARKER, IDC_USECUSTOM, m_bUseMarker ? IDC_USEMARKER : IDC_USECUSTOM);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgXfTruncate::OnChangeEnd() 
{

	CheckRadioButton( IDC_USEMARKER, IDC_USECUSTOM, IDC_USECUSTOM);
	
}

void CDlgXfTruncate::OnChangeStart() 
{

	CheckRadioButton( IDC_USEMARKER, IDC_USECUSTOM, IDC_USECUSTOM);
	
}


void CDlgXfTruncate::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}
