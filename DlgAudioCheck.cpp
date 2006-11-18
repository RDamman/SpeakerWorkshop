// DlgAudioCheck.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "DlgAudioCheck.h"
#include "mmWave.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioCheck dialog


CDlgAudioCheck::CDlgAudioCheck(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAudioCheck::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAudioCheck)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgAudioCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAudioCheck)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAudioCheck, CDialog)
	//{{AFX_MSG_MAP(CDlgAudioCheck)
	ON_BN_CLICKED(IDC_MOREINPUT, OnMoreinput)
	ON_BN_CLICKED(IDC_MOREOUTPUT, OnMoreoutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioCheck message handlers

BOOL CDlgAudioCheck::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	{			// input channel checking
	int nin;
	int nout;
	int nduplex;

		nin = CheckInput();
		check_Fill( IDC_TXTINPUT, nin);
		nout = CheckOutput();
		check_Fill( IDC_TXTOUTPUT, nout);
		if ( (nout != CHECK_FAILED) && (nin != CHECK_FAILED))
			nduplex = CheckDuplex();
		else
			nduplex = CHECK_FAILED;

		check_Duplex( IDC_TXTDUPLEX, nduplex);

		check_All( IDC_TXTSUMMARY, nin, nout, nduplex);
	}
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAudioCheck::SetIDText( int nID, UINT uidString)
{
CString cst;

	cst.LoadString( uidString);
	SetDlgItemText( nID, (LPCTSTR )cst);
}

static CString build_Support( bool bMono, int nBits, int nFreq)
{
CString csr;
CString csout;

	if ( bMono)
		csr.LoadString( IDS_MONO);
	else
		csr.LoadString( IDS_STEREO);

	csr += _T(" ");			// add a space

	csout.Format( IDS_CHK_FORMAT, nBits, nFreq);
	csout = csr + csout;

	return csout;

}


void CDlgAudioCheck::check_Fill( int nTxt, int nStyle)
{
	switch( nStyle)
		{
		case CHECK_SUCCESS :
			SetIDText( nTxt, IDS_FULLCOMP);
			break;
		case CHECK_PARTIAL :
			SetIDText( nTxt, IDS_PARTIALCOMP);
			break;
		case CHECK_FAILED :
			SetIDText( nTxt, IDS_NOTCOMP);
			break;
		default :
			SetDlgItemText( nTxt, cNullString);
			break;
		}

}

void CDlgAudioCheck::check_Duplex( int nTxt, int nStyle)
{
	switch( nStyle)
		{
		case CHECK_SUCCESS :
			SetIDText( nTxt, IDS_DUPFULL);
			break;
		case CHECK_PARTIAL :
			SetIDText( nTxt, IDS_PARTIALCOMP);
			break;
		case CHECK_FAILED :
			SetIDText( nTxt, IDS_DUPNOT);
			break;
		default :
			SetDlgItemText( nTxt, cNullString);
			break;
		}
}

void CDlgAudioCheck::check_All( int nTxt, int nInStat, int nOutStat, int nDupStat)
{
UINT utxt;

	if ( nDupStat == CHECK_SUCCESS)
		{
		if ( (CHECK_SUCCESS == nOutStat) && (CHECK_SUCCESS == nInStat))
			utxt =  IDS_CHK_USEFULL;
		else
		if ( CHECK_PARTIAL == nOutStat && CHECK_SUCCESS == nInStat)
			utxt =  IDS_CHK_PLAYLOW;
		else
		if ( CHECK_SUCCESS == nOutStat && CHECK_PARTIAL == nInStat)
			utxt =  IDS_CHK_RECLOW;
		else
//		if ( CHECK_PARTIAL == nOutStat && CHECK_PARTIAL == nInStat)
			utxt =  IDS_CHK_USELOW;
		}
	else		// half duplex only
		{
		if ( CHECK_SUCCESS == nOutStat)
			utxt =  IDS_CHK_NOREC;
		else
			if ( CHECK_PARTIAL == nOutStat)
				utxt =  IDS_CHK_NOLOW;
			else
				utxt =  IDS_CHK_NOUSE;
		}

		SetIDText( nTxt, utxt);

}

int CDlgAudioCheck::CheckDuplex( void)
{
WAVEFORMATEX wfx;
HWAVEIN hwvin;
HWAVEOUT hwvout;

	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = 2;
	wfx.wBitsPerSample = 16;
	wfx.nSamplesPerSec = 44100;
	wfx.nBlockAlign = (WORD )(wfx.nChannels * 2);
	wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;	// 2 bytes per sample
	wfx.cbSize = sizeof( wfx);

	if ( waveInOpen( & hwvin, WAVE_MAPPER, &wfx, 0L, 0L, WAVE_FORMAT_QUERY))
	    {
		wfx.nSamplesPerSec = 22050;
		wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;	// 2 bytes per sample
		if ( waveInOpen( & hwvin, WAVE_MAPPER, &wfx, 0L, 0L, WAVE_FORMAT_QUERY))
			{
			wfx.nSamplesPerSec = 11025;
			wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;	// 2 bytes per sample
			if ( waveInOpen( & hwvin, WAVE_MAPPER, &wfx, 0L, 0L, WAVE_FORMAT_QUERY))
				{
				return CHECK_FAILED;
				}
			}
    	}               
    if (waveInOpen(&hwvin, WAVE_MAPPER, &wfx, 0L, 0L, CALLBACK_NULL))
		{
	    return CHECK_FAILED;
		}
	if ( waveOutOpen( & hwvout, WAVE_MAPPER, &wfx, 0L, 0L, WAVE_FORMAT_QUERY | WAVE_ALLOWSYNC))
	    {
	   	waveInReset( hwvin);
		waveInClose( hwvin);
		return CHECK_FAILED;
    	}               
    if (waveOutOpen(&hwvout, WAVE_MAPPER, &wfx, 0L, 0L, CALLBACK_NULL | WAVE_ALLOWSYNC))
		{
		waveInReset( hwvin);
		waveInClose( hwvin);
	    return CHECK_FAILED;
		}

	waveInReset( hwvin);
	waveInClose( hwvin);
	waveOutClose( hwvout);


					// try it the other way - input then output
    if (waveOutOpen(&hwvout, WAVE_MAPPER, &wfx, 0L, 0L, CALLBACK_NULL | WAVE_ALLOWSYNC))
		{
	    return CHECK_FAILED;
		}

    if (waveInOpen(&hwvin, WAVE_MAPPER, &wfx, 0L, 0L, CALLBACK_NULL))
		{
		waveOutClose( hwvout);
	    return CHECK_FAILED;
		}

	waveInReset( hwvin);
	waveInClose( hwvin);

	{
	UINT urslt;
		urslt = CMMWave::CheckDuplex();
		if ( urslt)			// failure
			return CHECK_FAILED;
	}

	return CHECK_SUCCESS;

}


int CDlgAudioCheck::CheckInput( void)
{
int i;
int ndevs;
WAVEINCAPS wavin;
int nmessage = CHECK_FAILED;

	ndevs = waveInGetNumDevs();

	if ( 0 == ndevs)		// none at all
		{
//		MessageBox( "There are no input devices.", "Output Check Message", MB_OK);
		return nmessage;
		}

	for ( i=0; i<ndevs; i++)
		{
		if ( MMSYSERR_NOERROR == waveInGetDevCaps(i, &wavin, sizeof( wavin) ))	
			{	// we got a wavein structure. Is it ok?
			if ( WAVE_FORMAT_4S16 & wavin.dwFormats)	// supports 44k 16 bit
				{
				nmessage = CHECK_SUCCESS;
				break;
				}
			if ( WAVE_FORMAT_2S16 & wavin.dwFormats)	// supports 22k 16 bit
				{
				nmessage = CHECK_PARTIAL;
				break;
				}
			if ( WAVE_FORMAT_1S16 & wavin.dwFormats)	// supports 11k 16 bit
				{
				nmessage = CHECK_PARTIAL;
				break;
				}
			}
		}

	if ( CHECK_FAILED == nmessage)	// didn't find one
		{
//		MessageBox( "There are no stereo input devices.", "Input Check Message", MB_OK);
		return nmessage;
		}

	return nmessage;


}


int CDlgAudioCheck::CheckOutput( void)
{
int i;
int ndevs;
WAVEOUTCAPS wavout;
int nmessage = CHECK_FAILED;

	ndevs = waveOutGetNumDevs();

	if ( 0 == ndevs)		// none at all
		{
//		MessageBox( "There are no input devices.", "Output Check Message", MB_OK);
		return nmessage;
		}

	for ( i=0; i<ndevs; i++)
		{
		if ( MMSYSERR_NOERROR == waveOutGetDevCaps(i, &wavout, sizeof( wavout) ))	
			{	// we got a waveOut structure. Is it ok?
			if ( WAVE_FORMAT_4M16 & wavout.dwFormats)	// supports 44k 16 bit
				{
				nmessage = CHECK_SUCCESS;
				break;
				}
			if ( WAVE_FORMAT_2M16 & wavout.dwFormats)	// supports 22k 16 bit
				{
				nmessage = CHECK_PARTIAL;
				break;
				}
			if ( WAVE_FORMAT_1M16 & wavout.dwFormats)	// supports 11k 16 bit
				{
				nmessage = CHECK_PARTIAL;
				break;
				}
			}
		}

	if ( CHECK_FAILED == nmessage)	// didn't find one
		{
//		MessageBox( "There are no valid output devices.", "Output Check Message", MB_OK);
		return nmessage;
		}
	return nmessage;


}

void CDlgAudioCheck::OnMoreinput() 
{
CDlgAudchkInput cdlg;

	cdlg.DoModal();	
}

void CDlgAudioCheck::OnMoreoutput() 
{
CDlgAudchkOutput cdlg;

	cdlg.DoModal();	
	
}
/////////////////////////////////////////////////////////////////////////////
// CDlgAudchkInput dialog


CDlgAudchkInput::CDlgAudchkInput(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAudchkInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAudchkInput)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgAudchkInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAudchkInput)
	DDX_Control(pDX, IDC_FORMATS, m_cFormats);
	DDX_Control(pDX, IDC_PREVIOUS, m_cPrevious);
	DDX_Control(pDX, IDC_NEXT, m_cNext);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAudchkInput, CDialog)
	//{{AFX_MSG_MAP(CDlgAudchkInput)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAudchkInput message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgAudchkOutput dialog


CDlgAudchkOutput::CDlgAudchkOutput(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAudchkOutput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAudchkOutput)
	//}}AFX_DATA_INIT
}


void CDlgAudchkOutput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAudchkOutput)
	DDX_Control(pDX, IDC_FORMATS, m_cFormats);
	DDX_Control(pDX, IDC_SPECIAL, m_cSpecials);
	DDX_Control(pDX, IDC_PREVIOUS, m_cPrevious);
	DDX_Control(pDX, IDC_NEXT, m_cNext);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAudchkOutput, CDialog)
	//{{AFX_MSG_MAP(CDlgAudchkOutput)
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAudchkOutput message handlers

BOOL CDlgAudchkOutput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_nMaxDev = ::waveOutGetNumDevs();

	if ( m_nMaxDev)		// at least 1 exists
		{
		fill_Dialog( 0);	// use the first
		}
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgAudchkInput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_nMaxDev = ::waveInGetNumDevs();

	if ( m_nMaxDev)		// at least 1 exists
		{
		fill_Dialog( 0);	// use the first
		}
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAudchkInput::SetIDText( int nID, UINT uidString)
{
CString cst;

	cst.LoadString( uidString);
	SetDlgItemText( nID, (LPCTSTR )cst);
}


void CDlgAudchkInput::fill_Dialog( int nDevice)
{
CString csr;


	{			// mixer debugging
		UINT ui, uid;
		MMRESULT mx;
		MIXERCAPS mixcap;

		ui = mixerGetNumDevs();
		mx = mixerGetID( 0, &uid, MIXER_OBJECTF_MIXER );
		mixerGetDevCaps( uid, &mixcap, sizeof( mixcap));
		ui = 12;
	}

	if ( (nDevice >= 0) && (nDevice < (int )::waveInGetNumDevs()))
		{
		waveInGetDevCaps(nDevice, &m_Caps, sizeof( m_Caps));	// get device capabilities
		m_nDevice = nDevice;
		SetDlgItemInt( IDC_DEVID, nDevice);
		SetDlgItemInt( IDC_MFRID, m_Caps.wMid);
		SetDlgItemInt( IDC_PRODID, m_Caps.wPid);
		if ( 2 == m_Caps.wChannels)	// mono
			SetIDText( IDC_STEREO, IDS_STEREO);
		else
		if ( 1 == m_Caps.wChannels)	// mono
			SetIDText( IDC_STEREO, IDS_MONO);
		else
			SetIDText( IDC_STEREO, IDS_UNKNOWN);
		csr.Format("%d.%d", HIBYTE(m_Caps.vDriverVersion), LOBYTE(m_Caps.vDriverVersion));
		SetDlgItemText( IDC_VERSION, csr);
		csr = m_Caps.szPname;
		SetDlgItemText( IDC_AUDCHKNAME, csr);

		UpdateData( TRUE);

		m_cFormats.ResetContent();
		if ( m_Caps.dwFormats & WAVE_FORMAT_1M08)
			m_cFormats.AddString( build_Support( true, 8, 11));
		if ( m_Caps.dwFormats & WAVE_FORMAT_1M16)
			m_cFormats.AddString( build_Support( true, 16, 11));
		if ( m_Caps.dwFormats & WAVE_FORMAT_1S08)
			m_cFormats.AddString( build_Support( false, 8, 11));
		if ( m_Caps.dwFormats & WAVE_FORMAT_1S16)
			m_cFormats.AddString( build_Support( false, 16, 11));
		if ( m_Caps.dwFormats & WAVE_FORMAT_2M08)
			m_cFormats.AddString( build_Support( true, 8, 22));
		if ( m_Caps.dwFormats & WAVE_FORMAT_2M16)
			m_cFormats.AddString( build_Support( true, 16, 22));
		if ( m_Caps.dwFormats & WAVE_FORMAT_2S08)
			m_cFormats.AddString( build_Support( false, 8, 22));
		if ( m_Caps.dwFormats & WAVE_FORMAT_2S16)
			m_cFormats.AddString( build_Support( false, 16, 22));
		if ( m_Caps.dwFormats & WAVE_FORMAT_4M08)
			m_cFormats.AddString( build_Support( true, 8, 44));
		if ( m_Caps.dwFormats & WAVE_FORMAT_4M16)
			m_cFormats.AddString( build_Support( true, 16, 44));
		if ( m_Caps.dwFormats & WAVE_FORMAT_4S08)
			m_cFormats.AddString( build_Support( false, 8, 44));
		if ( m_Caps.dwFormats & WAVE_FORMAT_4S16)
			m_cFormats.AddString( build_Support( false, 16, 44));

		m_cNext.EnableWindow( (1+nDevice) < (int )::waveInGetNumDevs() );
		m_cPrevious.EnableWindow( nDevice> 0);

		UpdateData( FALSE);
		}

}

void CDlgAudchkOutput::SetIDText( int nID, UINT uidString)
{
CString cst;

	cst.LoadString( uidString);
	SetDlgItemText( nID, (LPCTSTR )cst);
}

void CDlgAudchkOutput::fill_Dialog( int nDevice)
{
CString csr;

	if ( (nDevice >= 0) && (nDevice < (int )::waveOutGetNumDevs()))
		{
		waveOutGetDevCaps(nDevice, &m_Caps, sizeof( m_Caps));	// get device capabilities
		m_nDevice = nDevice;
		SetDlgItemInt( IDC_DEVID, nDevice);
		SetDlgItemInt( IDC_MFRID, m_Caps.wMid);
		SetDlgItemInt( IDC_PRODID, m_Caps.wPid);
		if ( 2 == m_Caps.wChannels)	// mono
			SetIDText( IDC_STEREO, IDS_STEREO);
		else
		if ( 1 == m_Caps.wChannels)	// mono
			SetIDText( IDC_STEREO, IDS_MONO);
		else
			SetIDText( IDC_STEREO, IDS_UNKNOWN);
		csr.Format("%d.%d", HIBYTE(m_Caps.vDriverVersion), LOBYTE(m_Caps.vDriverVersion));
		SetDlgItemText( IDC_VERSION, csr);
		csr = m_Caps.szPname;
		SetDlgItemText( IDC_AUDCHKNAME, csr);

		UpdateData( TRUE);

		m_cFormats.ResetContent();
		if ( m_Caps.dwFormats & WAVE_FORMAT_1M08)
			m_cFormats.AddString( build_Support( true, 8, 11));
		if ( m_Caps.dwFormats & WAVE_FORMAT_1M16)
			m_cFormats.AddString( build_Support( true, 16, 11));
		if ( m_Caps.dwFormats & WAVE_FORMAT_1S08)
			m_cFormats.AddString( build_Support( false, 8, 11));
		if ( m_Caps.dwFormats & WAVE_FORMAT_1S16)
			m_cFormats.AddString( build_Support( false, 16, 11));
		if ( m_Caps.dwFormats & WAVE_FORMAT_2M08)
			m_cFormats.AddString( build_Support( true, 8, 22));
		if ( m_Caps.dwFormats & WAVE_FORMAT_2M16)
			m_cFormats.AddString( build_Support( true, 16, 22));
		if ( m_Caps.dwFormats & WAVE_FORMAT_2S08)
			m_cFormats.AddString( build_Support( false, 8, 22));
		if ( m_Caps.dwFormats & WAVE_FORMAT_2S16)
			m_cFormats.AddString( build_Support( false, 16, 22));
		if ( m_Caps.dwFormats & WAVE_FORMAT_4M08)
			m_cFormats.AddString( build_Support( true, 8, 44));
		if ( m_Caps.dwFormats & WAVE_FORMAT_4M16)
			m_cFormats.AddString( build_Support( true, 16, 44));
		if ( m_Caps.dwFormats & WAVE_FORMAT_4S08)
			m_cFormats.AddString( build_Support( false, 8, 44));
		if ( m_Caps.dwFormats & WAVE_FORMAT_4S16)
			m_cFormats.AddString( build_Support( false, 16, 44));

		m_cSpecials.ResetContent();
		if ( m_Caps.dwSupport & WAVECAPS_LRVOLUME)
		{
			csr.LoadString( IDS_CHK_LRVOLUME);
			m_cSpecials.AddString((LPCTSTR )csr);
		}
		if ( m_Caps.dwSupport & WAVECAPS_PITCH)
		{
			csr.LoadString( IDS_CHK_PITCH);
			m_cSpecials.AddString((LPCTSTR )csr);
		}
		if ( m_Caps.dwSupport & WAVECAPS_PLAYBACKRATE)
		{
			csr.LoadString( IDS_CHK_PLAYBACKRATE);
			m_cSpecials.AddString((LPCTSTR )csr);
		}
		if ( m_Caps.dwSupport & WAVECAPS_SYNC)
		{
			csr.LoadString( IDS_CHK_SYNC);
			m_cSpecials.AddString((LPCTSTR )csr);
		}
		if ( m_Caps.dwSupport & WAVECAPS_VOLUME)
		{
			csr.LoadString( IDS_CHK_VOLUME);
			m_cSpecials.AddString((LPCTSTR )csr);
		}
		if ( m_Caps.dwSupport & WAVECAPS_SAMPLEACCURATE)
		{
			csr.LoadString( IDS_CHK_SAMPLEACCURATE);
			m_cSpecials.AddString((LPCTSTR )csr);
		}

		m_cNext.EnableWindow( (1+nDevice) < (int )::waveOutGetNumDevs() );
		m_cPrevious.EnableWindow( nDevice> 0);

		UpdateData( FALSE);
		}
}

void CDlgAudchkOutput::OnPrevious() 
{
	fill_Dialog( m_nDevice-1);
}

void CDlgAudchkOutput::OnNext() 
{
	fill_Dialog( m_nDevice+1);	
}


void CDlgAudchkInput::OnNext() 
{
	fill_Dialog( m_nDevice+1);	
	
}

void CDlgAudchkInput::OnPrevious() 
{
	fill_Dialog( m_nDevice-1);
	
}
