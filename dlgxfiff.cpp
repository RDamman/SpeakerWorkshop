// dlgxfiff.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgxfiff.h"

#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

typedef struct tagIfftinfo
	{
	float	fStart;
	float	fEnd;
	int		nStyle;
	int		nSampleRate;
	int		nSampleStyle;
	}	IFFTINFO;



/////////////////////////////////////////////////////////////////////////////
// CDlgXfIfft dialog


CDlgXfIfft::CDlgXfIfft(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXfIfft::IDD, pParent), m_cfEdits()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgXfIfft)
	m_csSampleRate = _T("");
	//}}AFX_DATA_INIT

	{
	IFFTINFO fi;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		if ( capp->ReadRegistry( IDS_IFFTINFO, &fi, sizeof(fi)))	// success???
			{
			fi.fStart = 0.0f;
			fi.fEnd = 1.0f;
			fi.nStyle = 0;
			fi.nSampleRate = 22050;
			fi.nSampleStyle = 0;
			}
		m_fStart = fi.fStart;
		m_fEnd = fi.fEnd;
		m_nStyle = fi.nStyle;
		m_nSampleRate = fi.nSampleRate;
		m_nSampleStyle = fi.nSampleStyle;
	}

}


void CDlgXfIfft::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgXfIfft::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgXfIfft)
	DDX_CBString(pDX, IDC_SAMPLERATE, m_csSampleRate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXfIfft, CDialog)
	//{{AFX_MSG_MAP(CDlgXfIfft)
	ON_EN_CHANGE(IDC_END, OnChangeEnd)
	ON_EN_CHANGE(IDC_START, OnChangeStart)
	ON_CBN_EDITCHANGE(IDC_SAMPLERATE, OnEditchangeSamplerate)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgXfIfft, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgXfIfft)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXfIfft message handlers

void CDlgXfIfft::OnOK() 
{
	if ( ! VerboseUpdateData( TRUE))
		return;

	{
	m_nStyle = GetCheckedRadioButton( IDC_USEENTIRE, IDC_USECUSTOM) - IDC_USEENTIRE;
	m_nSampleStyle = GetCheckedRadioButton( IDC_RADIO1, IDC_RADIO2) - IDC_RADIO1;
	sscanf( m_csSampleRate, "%d", &m_nSampleRate);

	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	IFFTINFO fi;

		fi.fStart = m_fStart;
		fi.fEnd =	m_fEnd;
		fi.nStyle = m_nStyle;
		fi.nSampleRate = m_nSampleRate;
		fi.nSampleStyle = m_nSampleStyle;

		capp->WriteRegistry( IDS_IFFTINFO, &fi, sizeof(fi) );	// success???
	}
	
	CDialog::OnOK();
}

BOOL CDlgXfIfft::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[3] = { 
							{IDC_START,	IDC_SPIN1, 0.01f, 2000000.0f, &m_fStart},
							{IDC_END,	IDC_SPIN2, 0.01f, 2000000.0f, &m_fEnd},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CDialog::OnInitDialog();
	
CStatic *cctrl;
CString cs;

	cs.Format( "%d", (int )m_fStartMarker);
	cctrl = (CStatic *)GetDlgItem( IDC_MARKLOW);
	cctrl->SetWindowText( cs);
	cs.Format( "%d", (int )m_fEndMarker);
	cctrl = (CStatic *)GetDlgItem( IDC_MARKHIGH);
	cctrl->SetWindowText( cs);

	cs.Format( "%d", m_nDefaultRate);
	cctrl = (CStatic *)GetDlgItem( IDC_SAMPLE);
	cctrl->SetWindowText( cs);

	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USEENTIRE + m_nStyle);
	CheckRadioButton( IDC_RADIO1, IDC_RADIO2, IDC_RADIO1 + m_nSampleStyle);

	m_csSampleRate.Format( "%d", m_nSampleRate);

	UpdateData( FALSE);		// set it now
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgXfIfft::OnChangeEnd() 
{

	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USECUSTOM);
	
	
}

void CDlgXfIfft::OnChangeStart() 
{

	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USECUSTOM);
	
	
}

void CDlgXfIfft::OnEditchangeSamplerate() 
{
	CheckRadioButton( IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
	
}

void CDlgXfIfft::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}
