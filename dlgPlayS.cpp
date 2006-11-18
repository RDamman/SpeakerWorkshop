// dlgplays.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "audtedoc.h"
#include "dlgplays.h"

#include "Utils.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPlaySound dialog


CDlgPlaySound::CDlgPlaySound(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPlaySound::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgPlaySound)
	m_fPlayTime = 0.0f;
	m_fVolumeAmt = 0.0f;
	m_nOutput = -1;
	//}}AFX_DATA_INIT
}


void CDlgPlaySound::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgPlaySound::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPlaySound)
	DDX_Text(pDX, IDC_PLAYTIME, m_fPlayTime);
	DDX_Text(pDX, IDC_VOLUMEAMT, m_fVolumeAmt);
	DDX_CBIndex(pDX, IDC_OUTPUT, m_nOutput);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPlaySound, CDialog)
	//{{AFX_MSG_MAP(CDlgPlaySound)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC2, OnDeltaposGeneric2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgPlaySound, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgPlaySound)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPlaySound message handlers

void CDlgPlaySound::SetDocument( CAudtestDoc *)
{
RECORDINGINFO rec;

	CAudtestApp::GetRecordingInfo( &rec);

 	rec.m_fDataAmplitude = m_fVolumeAmt;	// amplitude of wave
	rec.m_nOutChannel = ComboToChannel(m_nOutput);		// calibration channel
	rec.m_fPlayTime = m_fPlayTime;
	rec.m_bOutput = TRUE;

	CAudtestApp::SetRecordingInfo( &rec);

}

void CDlgPlaySound::UseDocument( CAudtestDoc *)
{
RECORDINGINFO rec;

	CAudtestApp::GetRecordingInfo( &rec);

 	m_fVolumeAmt = rec.m_fDataAmplitude; 	// amplitude of wave
	m_nOutput 	= ComboFromChannel(rec.m_nOutChannel);		// output channel
	m_fPlayTime = rec.m_fPlayTime; 		// play time


}

BOOL CDlgPlaySound::OnInitDialog() 
{
	CDialog::OnInitDialog();

	::ComboFillString( this, IDC_OUTPUT, IDS_PLAYS_OUTPUT);
	
CSpinButtonCtrl *pbutton;

	pbutton = (CSpinButtonCtrl *)GetDlgItem( IDC_GENERIC1);
	if ( pbutton)
		pbutton->SetRange(0,100);
	pbutton = (CSpinButtonCtrl *)GetDlgItem( IDC_GENERIC2);
	if ( pbutton)
		pbutton->SetRange(0,100);

	UpdateData( FALSE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPlaySound::OnDeltaposGeneric2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	UpdateData( TRUE);
	m_fPlayTime += .01f * pNMUpDown->iDelta;
	if ( m_fPlayTime < 0.0f)
		m_fPlayTime = 0.0f;
	UpdateData( FALSE);
		
	*pResult = 0;
}

void CDlgPlaySound::OnOK() 
{
	if ( ! VerboseUpdateData( TRUE))
		return;
	
	CDialog::OnOK();
}
