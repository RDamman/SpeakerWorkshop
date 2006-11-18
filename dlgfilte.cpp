// dlgfilte.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgfilte.h"
#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFilter dialog


CDlgFilter::CDlgFilter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFilter::IDD, pParent), m_cfEdits()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgFilter)
	m_nShape = -1;
	m_nType = -1;
	m_nOrder = 0;
	//}}AFX_DATA_INIT
}


void CDlgFilter::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgFilter)
	DDX_Control(pDX, IDC_IMAGE, m_cImage);
	DDX_CBIndex(pDX, IDC_FSHAPE, m_nShape);
	DDX_CBIndex(pDX, IDC_FTYPE, m_nType);
	DDX_Text(pDX, IDC_ORDER, m_nOrder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFilter, CDialog)
	//{{AFX_MSG_MAP(CDlgFilter)
	ON_CBN_SELCHANGE(IDC_FTYPE, OnSelchangeFtype)
	ON_CBN_SELCHANGE(IDC_FSHAPE, OnSelchangeFtype)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINFREQ1, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINFREQ2, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINFREQ3, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgFilter, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgFilter)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFilter message handlers

void CDlgFilter::OnSelchangeFtype() 
{
UINT ubit;			// the bitmap id


	// TODO: Add your control notification handler code here
	UpdateData( TRUE);			// get the control

	{
	switch( m_nType)
		{
		case 0 :			// lowpass
			ubit = IDB_LOWPASS;
			break;
		case 1 :			// highpass
			ubit = IDB_HIGHPASS;
			break;
		case 2 :			// bandpass
			ubit = IDB_BANDPASS;
			break;
		case 3 :			// bandstop
			ubit = IDB_BANDSTOP;
			break;
		default :
			_ASSERT(0);
			ubit = IDB_LOWPASS; // remove warning
			break;
		}
	}

	{
	HBITMAP hnew;
	HBITMAP hold;

		hnew = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(ubit) );
		if ( hnew)
			{
			hold = m_cImage.SetBitmap( hnew );

			if ( hold != hnew )
				DeleteObject( hold);		// toss the prior hbitmap
			}
	}

	CWnd *pwnd;

	switch( m_nType)
		{
		case 0 :			// lowpass
			pwnd = GetDlgItem( IDC_FREQ1);
			pwnd->EnableWindow( TRUE );
			pwnd = GetDlgItem( IDC_FREQ2);
			pwnd->EnableWindow( FALSE);
			break;
		case 1 :			// highpass
			pwnd = GetDlgItem( IDC_FREQ1);
			pwnd->EnableWindow( FALSE);
			pwnd = GetDlgItem( IDC_FREQ2);
			pwnd->EnableWindow( TRUE);
			break;
		case 2 :			// bandpass
		case 3 :			// bandstop
			pwnd = GetDlgItem( IDC_FREQ1);
			pwnd->EnableWindow( TRUE);
			pwnd = GetDlgItem( IDC_FREQ2);
			pwnd->EnableWindow( TRUE);
			break;
		}

	pwnd = GetDlgItem( IDC_RIPPLE);
	pwnd->EnableWindow( m_nShape >1 );		//chebychev w both ripples

}


BOOL CDlgFilter::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[4] = { 
							{IDC_FREQ1,	IDC_SPINFREQ1, 0.0f, 2000000.0f, &m_fLowFreq},
							{IDC_FREQ2,	IDC_SPINFREQ2, 0.0f, 2000000.0f, &m_fHiFreq},
							{IDC_RIPPLE,	IDC_SPINFREQ3, 0.0f, 2000000.0f, &m_fRipple},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CDialog::OnInitDialog();

	::ComboFillString( this, IDC_FTYPE, IDS_XFFILTER_FTYPE);
	::ComboFillString( this, IDC_FSHAPE, IDS_XFFILTER_FSHAPE);

	{
	CSpinButtonCtrl *pbutton;

	pbutton = (CSpinButtonCtrl *)GetDlgItem( IDC_SPINORDER);
	if ( pbutton)
		pbutton->SetRange(1,50);
	}
	
	// TODO: Add extra initialization here
	UpdateData( FALSE);	// put the initial conditions into the controls
	OnSelchangeFtype();	// I think this is legit, and it does what I want
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFilter::OnOK() 
{
UINT uerror = 0;

	if ( ! VerboseUpdateData( TRUE))
		return;

	if ( m_nType > 1)			// bandpass or bandstop
		if ( m_fLowFreq > m_fHiFreq)
			{
			uerror = IDS_F2;
			}

	if ( uerror)
		{
		::AfxMessageBox( uerror, NULL, MB_OK);
		return;
		}

	CDialog::OnOK();
}

void CDlgFilter::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}
