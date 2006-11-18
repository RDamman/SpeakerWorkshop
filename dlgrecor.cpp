// dlgrecor.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "audtedoc.h"
#include "dlgrecor.h"

#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecord dialog


CDlgRecord::CDlgRecord(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecord::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgRecord)
	m_nCalib = -1;
	m_nData = -1;
	m_fVolumeAmt = 0.0f;
	m_bNoOutput = FALSE;
	m_fPlayTime = 0.0f;
	m_fRecordTime = 0.0f;
	m_nOutput = -1;
	//}}AFX_DATA_INIT


}


void CDlgRecord::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecord)
	DDX_CBIndex(pDX, IDC_CALIB, m_nCalib);
	DDX_CBIndex(pDX, IDC_DATA, m_nData);
	DDX_Text(pDX, IDC_VOLUMEAMT, m_fVolumeAmt);
	DDX_Check(pDX, IDC_NOOUTPUT, m_bNoOutput);
	DDX_Text(pDX, IDC_PLAYTIME, m_fPlayTime);
	DDX_Text(pDX, IDC_RECORDTIME, m_fRecordTime);
	DDX_CBIndex(pDX, IDC_OUTPUT, m_nOutput);
	//}}AFX_DATA_MAP

	if ( pDX->m_bSaveAndValidate)
		{
		if ( IsDlgButtonChecked( IDC_RADIO1) )
			m_nType = 0;
		else
		if ( IsDlgButtonChecked( IDC_RADIO2) )
			m_nType = 1;
		else
			m_nType = 2;
		}
	else
		{
		int nradio;

		switch( m_nType)
			{
			case 0 :
				nradio = IDC_RADIO1;
				break;
			case 1 :
				nradio = IDC_RADIO2;
				break;
			default :
			case 2 :
				nradio = IDC_RADIO3;
				break;
			}
		CheckRadioButton(IDC_RADIO1, IDC_RADIO3, nradio);
		}
}


BEGIN_MESSAGE_MAP(CDlgRecord, CDialog)
	//{{AFX_MSG_MAP(CDlgRecord)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC2, OnDeltaposGeneric2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC3, OnDeltaposGeneric3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgRecord, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgRecord)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRecord message handlers

void CDlgRecord::SetDocument( CAudtestDoc *pDoc)
{
RECORDINGINFO rec;

	CAudtestApp::GetRecordingInfo( &rec);

	rec.m_nDataType  = m_nType;
 	rec.m_fDataAmplitude = m_fVolumeAmt;	// amplitude of wave
	rec.m_nDataChannel = ComboToChannel(m_nData);		// channel to use for data
	rec.m_nCalibChannel = ComboToChannel(m_nCalib);		// calibration channel
	rec.m_nOutChannel = ComboToChannel(m_nOutput);		// calibration channel
	rec.m_fPlayTime = m_fPlayTime;
	rec.m_fRecordTime = m_fRecordTime;
	rec.m_bOutput = ! m_bNoOutput;
//	rec.m_fInLeftVolume;
//	rec.m_fInRightVolume;		// left and right input volume settings

	CAudtestApp::SetRecordingInfo( &rec);
}

void CDlgRecord::UseDocument( CAudtestDoc *pDoc)
{
RECORDINGINFO rec;

	CAudtestApp::GetRecordingInfo( &rec);

	m_nType 	= rec.m_nDataType; 
 	m_fVolumeAmt = rec.m_fDataAmplitude; 	// amplitude of wave
	m_nData 	= ComboFromChannel(rec.m_nDataChannel);  	// channel to use for data
	m_nCalib 	= ComboFromChannel(rec.m_nCalibChannel);  	// calibration channel
	m_nOutput 	= ComboFromChannel(rec.m_nOutChannel);		// output channel
	m_fPlayTime = rec.m_fPlayTime; 		// play time
	m_fRecordTime = rec.m_fRecordTime; 	// record time
	m_bNoOutput = ! rec.m_bOutput;

}

void CDlgRecord::OnDeltaposGeneric2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	UpdateData( TRUE);
	m_fPlayTime += .01f * pNMUpDown->iDelta;
	if ( m_fPlayTime < 0.0f)
		m_fPlayTime = 0.0f;
	UpdateData( FALSE);
	
	*pResult = 0;
}

void CDlgRecord::OnDeltaposGeneric3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	UpdateData( TRUE);
	m_fRecordTime += .01f * pNMUpDown->iDelta;
	if ( m_fRecordTime < 0.0f)
		m_fRecordTime = 0.0f;
	UpdateData( FALSE);
	
	*pResult = 0;
}

BOOL CDlgRecord::OnInitDialog() 
{
	CDialog::OnInitDialog();

	::ComboFillString( this, IDC_OUTPUT, IDS_RECORD_OUTPUT);
	::ComboFillString( this, IDC_CALIB, IDS_RECORD_CALIB);
	::ComboFillString( this, IDC_DATA, IDS_RECORD_DATA);
	
	// TODO: Add extra initialization here
	CSpinButtonCtrl *pbutton;

	pbutton = (CSpinButtonCtrl *)GetDlgItem( IDC_GENERIC1);
	if ( pbutton)
		pbutton->SetRange(0,100);
	pbutton = (CSpinButtonCtrl *)GetDlgItem( IDC_GENERIC2);
	if ( pbutton)
		pbutton->SetRange(0,100);
	pbutton = (CSpinButtonCtrl *)GetDlgItem( IDC_GENERIC3);
	if ( pbutton)
		pbutton->SetRange(0,100);

	UpdateData( FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRecord::OnOK() 
{
	if ( ! VerboseUpdateData( TRUE))
		return;
	
	CDialog::OnOK();
}
