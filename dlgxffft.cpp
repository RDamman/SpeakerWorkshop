// dlgxffft.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dataset.h"

#include "dlgxffft.h"

#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

typedef struct tagFftinfo
	{
	float	fStart;
	float	fEnd;
	int		nWindow;
	int		nStyle;
	}	FFTINFO;

/////////////////////////////////////////////////////////////////////////////
// CDlgXfFft dialog


CDlgXfFft::CDlgXfFft(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXfFft::IDD, pParent), m_cfEdits()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgXfFft)
	m_nWindow = -1;
	//}}AFX_DATA_INIT

	{
	FFTINFO fi;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		if ( capp->ReadRegistry( IDS_FFTINFO, &fi, sizeof(fi)))	// success???
			{
			fi.fStart = 0.0f;
			fi.fEnd = 1.0f;
			fi.nWindow = 0;
			fi.nStyle = 0;
			}
		m_fStart = fi.fStart;
		m_fEnd = fi.fEnd;
		m_nWindow = fi.nWindow;
		m_nStyle = fi.nStyle;
	}

					// get marker info
}


void CDlgXfFft::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgXfFft::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgXfFft)
	DDX_CBIndex(pDX, IDC_FFTWINDOW, m_nWindow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXfFft, CDialog)
	//{{AFX_MSG_MAP(CDlgXfFft)
	ON_EN_CHANGE(IDC_END, OnChangeEnd)
	ON_EN_CHANGE(IDC_START, OnChangeStart)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposSpin)
	ON_BN_CLICKED(IDC_USECUSTOM, OnUsecustom)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposSpin)
	ON_BN_CLICKED(IDC_USEENTIRE, OnUsecustom)
	ON_BN_CLICKED(IDC_USEMARKER, OnUsecustom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgXfFft, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgXfFft)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXfFft message handlers

void CDlgXfFft::OnOK() 
{
	if (! VerboseUpdateData( TRUE))
		return;

	m_nStyle = GetCheckedRadioButton( IDC_USEENTIRE, IDC_USECUSTOM) - IDC_USEENTIRE;
	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	FFTINFO fi;

		fi.fStart = m_fStart;
		fi.fEnd =	m_fEnd;
		fi.nStyle = m_nStyle;
		fi.nWindow = m_nWindow;

		capp->WriteRegistry( IDS_FFTINFO, &fi, sizeof(fi) );	// success???
	}

	
	CDialog::OnOK();
}

BOOL CDlgXfFft::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[3] = { 
							{IDC_START,	IDC_SCRL1, 0.0f, 2000000.0f, &m_fStart},
							{IDC_END,	IDC_SCRL2, 0.0f, 2000000.0f, &m_fEnd},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CDialog::OnInitDialog();

	::ComboFillString( this, IDC_FFTWINDOW, IDS_XFFFT_FFTWINDOW);
	
CStatic *cctrl;
CString cs;

	FullFormatValue( cs, m_fStartMarker, -4);
	cctrl = (CStatic *)GetDlgItem( IDC_MARKLOW);
	cctrl->SetWindowText( cs);

	FullFormatValue( cs, m_fEndMarker, -4);
	cctrl = (CStatic *)GetDlgItem( IDC_MARKHIGH);
	cctrl->SetWindowText( cs);

	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USEENTIRE + m_nStyle);

	UpdateData( FALSE);		// set it now

	DrawPointsInfo();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgXfFft::DrawPointsInfo() 
{
int nstyle;
int nstart, nend;

	UpdateData( TRUE);

	nstyle = GetCheckedRadioButton( IDC_USEENTIRE, IDC_USECUSTOM) - IDC_USEENTIRE;
	switch( nstyle)
		{
		case 0 :			// use them all
			nstart = 0;
			nend = m_pData->GetCount()-1;		// n
			break;
		case 1 :			// use markers
			nstart = m_pData->FreqToIndex( m_fStartMarker);
			nend = m_pData->FreqToIndex( m_fEndMarker) ;
			break;
		case 2 :			// use entries
			nstart = m_pData->FreqToIndex( m_fStart);
			nend = m_pData->FreqToIndex( m_fEnd) ;
			break;
		default:
			ASSERT( 0);
			nstart = nend = 0; // remove warning
			break;
		}
	
CWnd *pstat = GetDlgItem( IDC_NPOINTS);	// get the static item

CString csnum;

	csnum.Format( "%d", 1 + nend - nstart);
	pstat->SetWindowText( csnum);
	
}


void CDlgXfFft::OnChangeEnd() 
{

	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USECUSTOM);
	DrawPointsInfo();	
}

void CDlgXfFft::OnChangeStart() 
{
	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USECUSTOM);
	DrawPointsInfo();	
	
}



void CDlgXfFft::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

void CDlgXfFft::OnUsecustom() 
{
	
	DrawPointsInfo();
	
}
