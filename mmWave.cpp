// mdwmwave.cpp : Defines the class behaviors for the application.
//

	// there is no  in 32 bit
#include "stdafx.h"
#include "audtest.h"
                   
#include "mmwave.h"
#include "assert.h"

#include "math.h"		// for sin/cos etc.
#include "malloc.h"

#include "audtedoc.h"
#include "audtevw.h"
#include "xform.h"
#include "Complex.h"
#include "filter.h"
#include "dataset.h"

#include "DlgDisable48K.h"


//from windowsx.h

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static CMMWave *CMWavePlayer = NULL;		// who is currently playing????
static CMMWave *CMWaveReader = NULL;		// who is reading???

static CDWordArray ci_DataRates;

/////////////////////////////////////////////////////////////////////////////
//Local Functions

static WORD w_GetMaxLength( )
{
WAVEOUTCAPS wvcap;

	::waveOutGetDevCaps(WAVE_MAPPER, &wvcap, sizeof( wvcap));
	
	if ( wvcap.dwFormats & (WAVE_FORMAT_4M16 | WAVE_FORMAT_4S16 | WAVE_FORMAT_2M16 | 
							WAVE_FORMAT_2S16 | WAVE_FORMAT_1M16 | WAVE_FORMAT_1S16))
		return 16;
		
	if ( wvcap.dwFormats & (WAVE_FORMAT_4M08 | WAVE_FORMAT_4S08 | WAVE_FORMAT_2M08 | 
							WAVE_FORMAT_2S08 | WAVE_FORMAT_1M08 | WAVE_FORMAT_1S08))
		return 8;

	assert ( FALSE);
			
	return 8;		// unknown format

}

const CDWordArray *CMMWave::GetRateArray( void)
{
int *nrates;
bool bmess = FALSE;
bool bout;
int nr96[9] = {11050, 12000, 22100, 24000, 44100, 48000, 88200, 96000, 0};
int nr48[7] = {11050, 12000, 22100, 24000, 44100, 48000, 0};
int	nrno48[4] =  {11050, 22100, 44100, 0};

	if ( ! CAudtestApp::GetDisable96K())
		nrates = nr96;
	else
		nrates = CAudtestApp::GetDisable48K() ? nrno48 : nr48;

	if ( ci_DataRates.GetSize())			// see if we've changed
	{
		if ( (96000 == ci_DataRates[ci_DataRates.GetSize()-1]) && CAudtestApp::GetDisable96K() )
			ci_DataRates.RemoveAll();		// turn off 96K option
		else
		if ( (48000 == ci_DataRates[ci_DataRates.GetSize()-1]) && CAudtestApp::GetDisable48K() )
			ci_DataRates.RemoveAll();		// turn off 48K option
		else
		if ( (44100 == ci_DataRates[ci_DataRates.GetSize()-1]) && !CAudtestApp::GetDisable48K() )
			ci_DataRates.RemoveAll();		// allow 48K checking
	}

	if ( ! ci_DataRates.GetSize())			// not yet inited
		{
		WAVEFORMATEX waveform;
		int i;
		HWAVEOUT hwave;		// we shouldn't need this
		HWAVEIN hwavein;

			waveform.cbSize = 0;							// no extra information
			waveform.wBitsPerSample = 16;					// 16 bps
			waveform.wFormatTag = WAVE_FORMAT_PCM;  		// pcm
			waveform.nChannels = (WORD )1;					// mono
			waveform.nBlockAlign = (WORD )(waveform.nChannels * (waveform.wBitsPerSample / 8) );// bytes per total sample (channels*bps)  

			for( i=0; nrates[i]; i++)
			{
				waveform.nSamplesPerSec = nrates[i];	// 44.1 kHz
				waveform.nAvgBytesPerSec = waveform.nSamplesPerSec * waveform.nBlockAlign;	// data rate
				hwave = NULL;
				hwavein = NULL;
				bout = FALSE;

				if (MMSYSERR_NOERROR == waveOutOpen(&hwave, WAVE_MAPPER, (LPCWAVEFORMATEX)&waveform, 0L, 0L,
							WAVE_FORMAT_QUERY | WAVE_ALLOWSYNC))
					{
					bout = TRUE;
    				}               
				if ( hwave)			// this shouldn't happen
					{
					waveOutClose( hwave);
					hwave = NULL;
					bmess = TRUE;		// flag so we can tell the user it's gummed up
					}
				if ( bout)				// output worked, what about input ?
				{
					if (MMSYSERR_NOERROR == waveInOpen(&hwavein, WAVE_MAPPER, (LPCWAVEFORMATEX)&waveform, 0L, 0L,
								WAVE_FORMAT_QUERY | WAVE_ALLOWSYNC))
						{
						ci_DataRates.Add( waveform.nSamplesPerSec);		// we support this
    					}               
					if ( hwavein)			// this shouldn't happen
						{
						waveInClose( hwavein);
						hwavein = NULL;
						bmess = TRUE;		// flag so we can tell the user it's gummed up
						}
				}
			}

			if ( bmess)
				AfxMessageBox(IDERR_WAVEQUERY);


#if 0
		WAVEOUTCAPS wvcap;

			::waveOutGetDevCaps(WAVE_MAPPER, &wvcap, sizeof( wvcap));
	
			if ( wvcap.dwFormats & (WAVE_FORMAT_1M08 | WAVE_FORMAT_1S08 | 
									WAVE_FORMAT_1M16 | WAVE_FORMAT_1S16))
				ci_DataRates.Add(11025);
		
			if ( wvcap.dwFormats & (WAVE_FORMAT_2M08 | WAVE_FORMAT_2S08 | 
									WAVE_FORMAT_2M16 | WAVE_FORMAT_2S16))
				ci_DataRates.Add(22050);
		
			if ( wvcap.dwFormats & (WAVE_FORMAT_4M08 | WAVE_FORMAT_4S08 | 
									WAVE_FORMAT_4M16 | WAVE_FORMAT_4S16))
				ci_DataRates.Add(44100);
#endif
		}


		return &ci_DataRates;
}


DWORD CMMWave::GetMaxRate( void)
{
const CDWordArray *parray = CMMWave::GetRateArray();

	return parray->GetAt( parray->GetSize()-1);

}

// here fTime is in seconds
// fMaxAmp is 0...1
void CMMWave::PrepareForm( int nChannels, float fMaxAmp, float fTime,  int nSampleRate)
{
int ndatarate;
DWORD dwmax;
WORD wmaxlength;


	DeleteContents();		// if there was one, toss it

	m_fTime = fTime;

	wmaxlength = w_GetMaxLength();
	dwmax = GetMaxRate();
	ndatarate = min( nSampleRate, (int )dwmax);
	
				// set up the m_Format structure for use in wave i/o
	m_Format.wBitsPerSample = wmaxlength;		// 16 bps
	m_Format.wFormatTag = WAVE_FORMAT_PCM;  		// pcm
	m_Format.nChannels = (WORD )nChannels;				// mono or stereo
	m_Format.nSamplesPerSec = ndatarate;	// 44.1 kHz
	m_Format.nBlockAlign = (WORD )(nChannels * (wmaxlength / 8) );// bytes per total sample (channels*bps)  
	m_Format.nAvgBytesPerSec = ndatarate * m_Format.nBlockAlign;	// data rate
	m_Format.cbSize = 0;

				// also set the globals in the class for use during generation
	if ( fMaxAmp > 0)			// could be a "?" but too complex
		m_wAmplitude = (WORD )( (16 == m_Format.wBitsPerSample) ? fMaxAmp * 32767 : fMaxAmp * 127);
	else
		m_wAmplitude = (WORD )( (16 == m_Format.wBitsPerSample) ? 32767 : 127);
							// get 1 second if 0 or less speced
	m_dwTotal = (fTime > 0 ? (DWORD )(fTime * m_Format.nSamplesPerSec) : 
						 	 (DWORD )m_Format.nSamplesPerSec );
	m_dwDataSize = m_dwTotal * sizeof(short);		// 2 bytes per sample, in general
	
}

// wait for output
int CMMWave::WaitOutput( DWORD dwWait)
{
	return WaitNotify( dwWait);			// no wait if not direct
}




/////////////////////////////////////////////////////////////////////////////
// the sound callback function


CMMWave * CMMWave::WhoIsPlaying()
{
	return ( CMWavePlayer);
}

CMMWave * CMMWave::WhoIsRecording()
{
	return ( CMWaveReader);
}

/////////////////////////////////////////////////////////////////////////////
//	turn off all sounds for this wave
int CMMWave::TurnOffSound()
{
	if ( CMWavePlayer)			// someone is playing...
		{
	    if ( CMWavePlayer->m_hWaveOut)			// we have one still around
	    	{
	    	waveOutReset( CMWavePlayer->m_hWaveOut);
		    waveOutUnprepareHeader(CMWavePlayer->m_hWaveOut, &CMWavePlayer->m_Header, sizeof(WAVEHDR));
	    	waveOutClose( CMWavePlayer->m_hWaveOut);
	    	CMWavePlayer->m_hWaveOut = 0;
	    	}
	    CMWavePlayer = (CMMWave *)NULL;	// don't delete it, just remove it from notice
		}
    	
    return ( 0);            
}

int CMMWave::TurnOffRecording()
{
	if ( CMWaveReader)			// someone is playing...
		{
	    if ( CMWaveReader->m_hWaveIn)			// we have one still around
	    	{
	    	waveInReset( CMWaveReader->m_hWaveIn);
		    waveInUnprepareHeader(CMWaveReader->m_hWaveIn, &CMWaveReader->m_Header, sizeof(WAVEHDR));
	    	waveInClose( CMWaveReader->m_hWaveIn);
	    	CMWaveReader->m_hWaveIn = 0;
	    	}
	    CMWaveReader = (CMMWave *)NULL;
		}

    	
    return ( 0);            
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

int CMMWave::SaveWaveFile(CArchive& ar)
{
HMMIO           hmmio;
MMCKINFO        mmckinfoParent;
MMCKINFO        mmckinfoSubchunk;
int				nresult = 0;

    /* Open the given file for reading using buffered I/O.
     */
    {
    MMIOINFO mmio;
	const CFile* fp = ar.GetFile();

		memset( (PSTR )&mmio, 0, sizeof( MMIOINFO));	// null it out    
    	mmio.fccIOProc = FOURCC_DOS;	// use DOS i/o
    	mmio.pchBuffer = NULL;			// no buffer
//    	mmio.adwInfo[0] = fp->m_hFile;	// dos file handle to use
    
    	if(!(hmmio = mmioOpen(NULL, &mmio, MMIO_READWRITE | MMIO_CREATE | MMIO_ALLOCBUF | MMIO_DENYNONE)))
		    {
    		return ( IDERR_FILENOTFOUND);
	    	}
	}
	
    /* Make a 'RIFF' chunk with a 'WAVE' form type
     * to make sure it's a WAVE file.
     */
	memset( (PSTR )&mmckinfoParent, 0, sizeof( MMCKINFO));	// null it out    
	memset( (PSTR )&mmckinfoSubchunk, 0, sizeof( MMCKINFO));	// null it out    
	
    mmckinfoParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    mmckinfoSubchunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    
    if (mmioCreateChunk(hmmio, (LPMMCKINFO) &mmckinfoParent, MMIO_CREATERIFF))
    {
    	nresult = IDERR_NOTWAVE;
    	goto Errout;
    }

    /* Now, create the format chunk (form type 'fmt '). It should be
     * a subchunk of the 'RIFF' parent chunk.
     */
    mmckinfoSubchunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if (mmioCreateChunk(hmmio, &mmckinfoSubchunk, 0))
	    {
    	nresult = IDERR_CORRUPT;
    	goto Errout;
    	}

    /* Read the format chunk.
     */
   	if (mmioWrite(hmmio, (HPSTR)(LPWAVEFORMAT )&m_Format, sizeof(m_Format)) != sizeof(m_Format))
	    {
    	nresult =  IDERR_FAILREAD;
    	goto Errout;
    	}

    /* Ascend out of the format subchunk.
     */
    mmioAscend(hmmio, &mmckinfoSubchunk, 0);

    /* Create the data subchunk.
     */
    mmckinfoSubchunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
    if (mmioCreateChunk(hmmio, &mmckinfoSubchunk, 0))
    	{
    	nresult = IDERR_NODATA;
    	goto Errout;
	    }

    /* Write the waveform data subchunk.
     */
    if(mmioWrite(hmmio, (HPSTR )m_pWaveData, m_dwDataSize) != (LONG) m_dwDataSize)
	    {
    	nresult = IDERR_FAILREAD;
    	} 

					// these ascends are done to keep the file neat and clean    	
     /* Ascend out of the data subchunk.
     */
    mmioAscend(hmmio, &mmckinfoSubchunk, 0);
     /* Ascend out of the wave subchunk.
     */
    mmioAscend(hmmio, &mmckinfoParent, 0);


Errout:
	mmioClose( hmmio, MMIO_FHOPEN);    	// pseduo-close the file for mm
    return ( nresult);
    
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
int CMMWave::LoadWaveFile(CArchive& ar)
{
HMMIO           hmmio;
MMCKINFO        mmckinfoParent;
MMCKINFO        mmckinfoSubchunk;
int				nresult = 0;
int				i;

    /* Open the given file for reading using buffered I/O.
     */
    {
    MMIOINFO mmio;
	const CFile* fp = ar.GetFile();

		memset( (PSTR )&mmio, 0, sizeof( MMIOINFO));	// null it out    
    	mmio.fccIOProc = FOURCC_DOS;	// use DOS i/o
    	mmio.pchBuffer = NULL;			// no buffer
//    	mmio.adwInfo[0] = fp->m_hFile;	// dos file handle to use
    
    	if(!(hmmio = mmioOpen(NULL, &mmio, MMIO_READ | MMIO_ALLOCBUF | MMIO_DENYWRITE)))
		    {
    		return ( IDERR_FILENOTFOUND);
	    	}
	}
	
    /* Locate a 'RIFF' chunk with a 'WAVE' form type
     * to make sure it's a WAVE file.
     */
    mmckinfoParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    if (mmioDescend(hmmio, (LPMMCKINFO) &mmckinfoParent, NULL, MMIO_FINDRIFF))
    {
    	nresult = IDERR_NOTWAVE;
    	goto Errout;
    }

    /* Now, find the format chunk (form type 'fmt '). It should be
     * a subchunk of the 'RIFF' parent chunk.
     */
    mmckinfoSubchunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if (mmioDescend(hmmio, &mmckinfoSubchunk, &mmckinfoParent,
        MMIO_FINDCHUNK))
	    {
    	nresult = IDERR_CORRUPT;
    	goto Errout;
    	}

			    // Read the format chunk.
				// we'll read it as a waveformat structure !?!
	if ( mmckinfoSubchunk.cksize < sizeof( WAVEFORMATEX))
		i = (int )mmckinfoSubchunk.cksize;
	else
		i = sizeof(WAVEFORMATEX);
   	if ( mmioRead(hmmio, (HPSTR)(LPWAVEFORMAT )&m_Format, i) != i)
	    {
    	nresult =  IDERR_FAILREAD;
    	goto Errout;
    	}

	m_Format.cbSize = 0;
	if ( i < sizeof( WAVEFORMATEX))
		{
		if ( 1 == m_Format.nChannels)
			m_Format.wBitsPerSample = (m_Format.nBlockAlign == 2) ? (short)16u : (short)8u;
		else
			m_Format.wBitsPerSample = (m_Format.nBlockAlign == 4) ? (short)16u : (short)8u;
		}

    /* Make sure it's a PCM file.
     */
    if (m_Format.wFormatTag != WAVE_FORMAT_PCM)
	    {
    	nresult = IDERR_NOTPCM;
    	goto Errout;
    	}

    /* Ascend out of the format subchunk.
     */
    mmioAscend(hmmio, &mmckinfoSubchunk, 0);

    /* Find the data subchunk.
     */
    mmckinfoSubchunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
    if (mmioDescend(hmmio, &mmckinfoSubchunk, &mmckinfoParent,
        MMIO_FINDCHUNK))
    	{
    	nresult = IDERR_NODATA;
    	goto Errout;
	    }

    /* Get the size of the data subchunk.
     */
    m_dwDataSize = mmckinfoSubchunk.cksize;
    if (m_dwDataSize == 0L)
    	{
    	nresult = IDERR_NODATA;
    	goto Errout;
    	}													 

    /* Allocate memory for the waveform data.
     */
	m_pWaveData = new char[m_dwDataSize];
	
    /* Read the waveform data subchunk.
     */
    if(mmioRead(hmmio, m_pWaveData, m_dwDataSize) != (LONG) m_dwDataSize)
	    {
   		delete [] m_pWaveData;
    	nresult = IDERR_FAILREAD;
    	}
	else
		{
		m_dwTotal = m_dwDataSize / m_Format.nBlockAlign;
		m_nSampleRate = m_Format.nSamplesPerSec;
		m_wAmplitude = (WORD )((16 == m_Format.wBitsPerSample) ? 32767 : 127);
		m_fBalance = 50.0f;
		m_fTime = ((float )m_dwTotal) / (float )m_Format.nSamplesPerSec;
		m_Header.lpData = m_pWaveData;
		m_Header.dwBufferLength = m_dwDataSize;
		}

Errout:

	mmioClose( hmmio, MMIO_FHOPEN);    	// pseduo-close the file for mm
    return ( nresult);
    
}

/////////////////////////////////////////////////////////////////////////////
// CMMWave construction

CMMWave::CMMWave()
{

	m_dwDataSize = 0L;
	m_dwTotal = 0L;
	m_fBalance = 50.0f;			// vol and balance are 0...100
	m_Format.cbSize = 0;		// no extra data for these guys (pcm all the way)
	m_fTime = 1.0f;
	m_fVolume = 50.0f;
	m_Header.lpData = NULL;
	m_hWaveOut = (HWAVEOUT )NULL;
	m_hWaveIn = (HWAVEIN )NULL;
	m_nSampleRate = 22050;
				// for the other guys
	m_pWaveData = NULL;
	m_wAmplitude = 0;

}   


/////////////////////////////////////////////////////////////////////////////
CMMWave::~CMMWave()
{
	DeleteContents();
}  

/////////////////////////////////////////////////////////////////////////////
int CMMWave::CreateWave(enChannel )			// create the wave data
{
	_ASSERT(0);
	return 1;
}


/////////////////////////////////////////////////////////////////////////////
void CMMWave::DeleteContents()
{
	if ( this == WhoIsPlaying())
		TurnOffSound();

	if ( m_Header.lpData == m_pWaveData)		// input device, they're the same
		m_Header.lpData = NULL;		// disable the deletion, required for output

	if ( m_dwDataSize)
		{
		m_dwDataSize = 0L;
		m_dwTotal = 0L;
		if ( m_pWaveData)
			delete [] m_pWaveData;
		m_pWaveData = NULL;
		}

	if ( m_Header.lpData)
		{
		delete [] m_Header.lpData;
		m_Header.lpData = NULL;
		}

}

// ----------------------------------------------------------------------------------
//			CleanUp
// error handling
// return the prompt ID as an error message to pass on and close the device if opened
// ----------------------------------------------------------------------------------
int	CMMWave::CleanUp( UINT uidPrompt)
{
	if ( m_hWaveIn)
	{
		waveInClose( m_hWaveIn);
		m_hWaveIn = NULL;
	}
	if ( m_hWaveOut)
	{
		waveOutClose( m_hWaveOut);
		m_hWaveOut = NULL;
	}

	if ( WhoIsPlaying())		// someone is playing already
	{
		WhoIsPlaying()->DeleteContents();
	}
	AfxMessageBox(uidPrompt, NULL, MB_OK | MB_ICONEXCLAMATION);
	return (int )uidPrompt;
}



// ----------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
void CMMWave::Serialize( CArchive& ar)
{
int nresult;


	TurnOffSound();

	if ( ar.IsStoring())
		{
		// TODO: Add storing code here
		nresult = SaveWaveFile( ar);
		}
	else
		{
		// TODO: Add loading code here 
		nresult = LoadWaveFile( ar);
		}
}

/////////////////////////////////////////////////////////////////////////////
// CMMWave commands
/////////////////////////////////////////////////////////////////////////////



// ----------------------------------------------------------------------------------
//		PlayWave
//			return 0 if successful
//			error result else
// ----------------------------------------------------------------------------------

int CMMWave::PlayWave(CWnd *cWindow, float fVolume, float fBalance,  int nLoops)
{
int noffset = 0;
float ftoffset = 0.16f;			// white space at the front

	if ( ! m_pWaveData)
		{
		if ( CreateWave( chMono))
			return 1;			// we have nothing to play - out of memory
		}
		
	TurnOffSound();			// remove anything pending
		
    m_Header.dwBytesRecorded = m_dwDataSize;
    m_Header.dwUser = 0L;
    m_Header.dwFlags = 0;	// WHDR_BEGINLOOP | WHDR_ENDLOOP are set later per spec
    m_Header.dwLoops = (DWORD )nLoops;
    m_Header.lpNext = NULL;
    m_Header.reserved = 0L;

	if ( ! m_Header.lpData)	// if there is one, it should be valid
		{
		char *cdata;
		int nsize = (int )(ftoffset * m_Format.nSamplesPerSec * m_Format.nChannels * 2);

		nsize += 4 - (nsize & 3);		// round up to 4 byte increments

		cdata = new char[nsize + m_dwDataSize];
		m_Header.lpData = cdata;

		int i, mdata;

									// add 100ms of silence to begin
			for ( i=0; i<nsize; i++)
				cdata[i] = '\0';

			mdata = (int )m_dwDataSize;		// to get rid of type warning below
									// now plug in the actual wave data
			for ( i = 0; i<mdata; i++)
				cdata[i + nsize] = m_pWaveData[i];
									// update the buffer length to include the silence
		m_Header.dwBufferLength = m_dwDataSize + nsize;
		}
					// set the volume for the desired output
	m_fVolume = fVolume;
	m_fBalance = fBalance;

	{					// ------------- correct for any latency value in options preferences
	float flat;
		CAudtestApp::GetLatency( &flat);		// latency offset is offset + more?
		noffset = (m_Header.dwBufferLength - m_dwDataSize) + (int )((flat/1000.0f) * m_Format.nSamplesPerSec * m_Format.nChannels * 2);
		if ( IsKindOf( RUNTIME_CLASS( CMMMlsWave)))
			{
			CMMMlsWave *pwave = (CMMMlsWave *)this;
				if ( pwave->IsWarmOn())		// using warmup
					noffset += CAudtestApp::GetWarmup()* sizeof(short);
			}
		noffset = max(0, noffset);
	}

	SetNotify( (DWORD )noffset);				// set notification amount

	m_hWaveOut = NULL;
						// Make sure a waveform output device supports this format.
	if (MMSYSERR_NOERROR != waveOutOpen(&m_hWaveOut, WAVE_MAPPER, (LPCWAVEFORMATEX)&m_Format, 0L, 0L,
                    WAVE_FORMAT_QUERY | WAVE_ALLOWSYNC))
	    {
		return CleanUp( IDERR_CANTPLAYFORMAT);
    	}               

	if ( m_hWaveOut)		// this shouldn't happen
		waveOutClose( m_hWaveOut);

    /* Open a waveform output device.                        
     */   					// if we don't use (DW)(WORD ) the compiler produces ds:hwnd
     						// and waveoutopen fails!
	if ( cWindow)			// we passed a cwindow
		{
	    if (MMSYSERR_NOERROR != waveOutOpen((LPHWAVEOUT)&m_hWaveOut, WAVE_MAPPER,
	                  (LPCWAVEFORMATEX)&m_Format, (DWORD )(cWindow->m_hWnd), 0L, CALLBACK_WINDOW | WAVE_ALLOWSYNC))
	    	{
			return CleanUp( IDERR_FAILOPENWAVEOUT);
	    	}
		}
	else					// no callback window passed, use the main window
	    if (MMSYSERR_NOERROR != waveOutOpen((LPHWAVEOUT)&m_hWaveOut, WAVE_MAPPER,
	                  (LPCWAVEFORMATEX)&m_Format, (DWORD )(AfxGetApp()->m_pMainWnd->m_hWnd), 0L, CALLBACK_WINDOW | WAVE_ALLOWSYNC))
	    	{
			return CleanUp( IDERR_FAILOPENWAVEOUT);
	    	}

						// ----------- set the volume using the internal volume call
	{
	WAVEOUTCAPS wvcaps;

		waveOutGetDevCaps( WAVE_MAPPER, &wvcaps, sizeof( wvcaps));

		if ( wvcaps.dwSupport & WAVECAPS_LRVOLUME)	// can set independent volume
			{
			DWORD dwvol;
			WORD  wamp, wright;

			if ( m_fBalance > 50.0f)
				{
				wamp = (WORD )((100.0f - m_fBalance) * m_fVolume * 0xffff / 5000.0f);
				wright = (WORD )(m_fVolume * 0xffff / 100.0f);
				}
			else
				{
				wamp = (WORD )(m_fVolume * 0xffff / 100.0f);
				wright = (WORD )(m_fBalance * m_fVolume * 0xffff / 5000.0f);
				}
			dwvol = MAKELONG( wamp, wright);
			waveOutSetVolume( m_hWaveOut, dwvol);
			}

	}

							// prepare the header
    if(MMSYSERR_NOERROR != waveOutPrepareHeader(m_hWaveOut, &m_Header, sizeof(WAVEHDR)))
    {
		return CleanUp( IDERR_PREPAREHDR);
    }

						// set the looping flags now (per spec)
	m_Header.dwFlags |= WHDR_BEGINLOOP | WHDR_ENDLOOP;
	
					    // Then the data block can be sent to the output device.
    {   
    UINT	mmResult;

		mmResult = waveOutWrite(m_hWaveOut, &m_Header, sizeof(WAVEHDR));
		if (MMSYSERR_NOERROR != mmResult)
			{
			waveOutReset( m_hWaveOut);
			waveOutUnprepareHeader( m_hWaveOut, &m_Header, sizeof(WAVEHDR));
			return CleanUp( IDERR_FAILWRITEBLOCK);
			}
    }

    CMWavePlayer = this;

	return 0;    
}

int  CMMWave::SaveWave( const char* pszPathName)
{
CFile file;
CFileException fe;

	if (!file.Open(pszPathName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive, &fe))
	{
//		ReportSaveLoadException(pszPathName, &fe, TRUE, AFX_IDP_INVALID_FILENAME);
		return FALSE;
	}

	CArchive saveArchive(&file, CArchive::store | CArchive::bNoFlushOnDelete);
	TRY
	{
//		BeginWaitCursor();
		Serialize(saveArchive);     // save me
		saveArchive.Close();
		file.Close();
	}
	CATCH_ALL(e)
	{
		file.Abort(); // will not throw an exception
//		EndWaitCursor();

//		TRY
//			ReportSaveLoadException(pszPathName, e,
//				TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
//		END_TRY
		return FALSE;
	}
	END_CATCH_ALL

//	EndWaitCursor();
//	SetModifiedFlag(FALSE);     // back to unmodified

	return 0;
}

int  CMMWave::LoadWave( const char* pszPathName)
{
CFile file;
CFileException fe;

	DeleteContents();		// get rid of anything prior

	if ( ! pszPathName[0])	// empty string
		return 1;			// whoops

	if (!file.Open(pszPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))
	{
		return 1;
	}

	CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);
	TRY
	{
//		BeginWaitCursor();
		Serialize(loadArchive);     // load me
		loadArchive.Close();
		file.Close();
	}
	CATCH_ALL(e)
	{
		file.Abort(); // will not throw an exception
		DeleteContents();   // remove failed contents
//		EndWaitCursor();

//		TRY
//			ReportSaveLoadException(pszPathName, e,
//				FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
//		END_TRY
		return 1;
	}
	END_CATCH_ALL

//	EndWaitCursor();

 	return 0;
}



char   *CMMWave::GetCharData( BOOL )
{
 return (m_pWaveData); 
}

int CMMWave::GetCharDataSize( BOOL)
{
	return ( m_dwTotal);		// # of samples to get
}


int CMMWave::WaitNotify( DWORD dwWait)
{
DWORD dwclk;
MMTIME mmtime;
MMRESULT mrslt;

	dwclk = GetTickCount();

	mmtime.wType = TIME_BYTES;			// byte position
	mrslt = waveOutGetPosition(m_hWaveOut, &mmtime, sizeof( mmtime));
	if ( MMSYSERR_NOERROR != mrslt)
		return 0;						// failed for some reason

	if ( mmtime.wType != TIME_BYTES)		// not supported
		return 0;

	while ( dwWait > (GetTickCount() - dwclk))
	{
		mrslt = waveOutGetPosition(m_hWaveOut, &mmtime, sizeof( mmtime) );
		if ( ( MMSYSERR_NOERROR != mrslt) || mmtime.u.cb > m_dwNotify)		// we're there
			return 0;
	}
	return 1;			// timed out


}

  
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//	CMMSineWave Functionality

/////////////////////////////////////////////////////////////////////////////
// CMMWave construction

CMMSineWave::CMMSineWave()
{
	 
}   

/////////////////////////////////////////////////////////////////////////////
int CMMSineWave::CreateWave(enChannel enType)			// create the wave data
{
DWORD dwi;			// counter
double df;

				// initialize the format with out only default!
	PrepareForm( 1, 1.0f, m_fTime, m_nSampleRate);			// use all of the amplitude
	
											// now build the full data set
	df = (2 * ONEPI) * m_fFreq / m_Format.nSamplesPerSec;
	
    if ( 16 == m_Format.wBitsPerSample)		// 16 bit???
    	{
    	short  *hpw;
    	
    	hpw = new short[m_dwTotal];
    			/* Allocate memory for the short waveform data.
			     */
		if ( ! hpw)
			return 1;
			// algorithm....
			// f(x) = sin( x / freq / samples)
		for ( dwi=0; dwi < m_dwTotal; dwi++)
			{
			hpw[dwi] = (short )(.49 + m_wAmplitude * sin(m_fPhase + dwi * df));
			}
		m_pWaveData = (char  *)hpw;
    	}
    	
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
CMMSineWave::CMMSineWave( int nSampleRate, float fTime, float fFreq, float fPhase)
{

	m_nSampleRate = nSampleRate;
	m_fTime = fTime;
	m_fFreq = fFreq;
	m_fPhase = fPhase;

}


/////////////////////////////////////////////////////////////////////////////
CMMSineWave::~CMMSineWave()
{
	DeleteContents();
}  


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//	CMMSquareWave Functionality

/////////////////////////////////////////////////////////////////////////////
// CMMWave construction

CMMSquareWave::CMMSquareWave()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_wDuty = 50;
	 
}   

/////////////////////////////////////////////////////////////////////////////
int CMMSquareWave::CreateWave(enChannel enType)			// create the wave data
{
DWORD dwi;			// counter
double df;
double dftotal = 0.0;
WORD	wduty = (WORD )(10 * m_fDutyCycle);			// duty cycle to nearest 1/1000
    
    PrepareForm( 1, 1.0f, m_fTime, m_nSampleRate);
	
							// now build the full data set
	df = m_fFreq / m_Format.nSamplesPerSec;
	
    if ( 16 == m_Format.wBitsPerSample)		// 16 bit???
    	{
    	short  *hpw;
    			/* Allocate memory for the short waveform data.
			     */
		hpw = new short[m_dwTotal];
		if ( ! hpw)
			return 1;
			// algorithm....
			// f(x) = sin( x / freq / samples)
		for ( dwi=0; dwi < m_dwTotal; dwi++)
			{
			dftotal += 1000 * df;
			if ( dftotal >= 1000)
				dftotal -= 1000;
			hpw[dwi] = (short )((wduty >= (WORD )dftotal) ? m_wAmplitude : -m_wAmplitude);
			}
		m_pWaveData = (char  *)hpw;
    	}
    	
	return 0;

}
/////////////////////////////////////////////////////////////////////////////
CMMSquareWave::CMMSquareWave( int nSampleRate, float fTime, float fFreq, float fDutyCycle)
{
	m_nSampleRate = nSampleRate;
	m_fTime = fTime;
	m_fFreq = fFreq;
	m_fDutyCycle = fDutyCycle;
}


/////////////////////////////////////////////////////////////////////////////
CMMSquareWave::~CMMSquareWave()
{
	DeleteContents();
}  


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//	CMMPulseWave Functionality

/////////////////////////////////////////////////////////////////////////////
// CMMWave construction

CMMPulseWave::CMMPulseWave()
{
	// TODO: add construction code here,

}   


int CMMPulseWave::CreateWave( enChannel enType)
{

DWORD dwi;			// counter
double df;
double dftotal = 0.0;
short son, soff;
BOOL bshot;
int ncount;
int ntotal;

    PrepareForm( 1, 1.0f, m_fTime, m_nSampleRate);
	
							// now build the full data set
	df = 100 * m_fFreq / m_Format.nSamplesPerSec;
	if ( m_bNegative)
		{
		son = (short )-m_wAmplitude;
		soff = 0;
		}
	else
		{
		son = m_wAmplitude;
		soff = 0;
		}

					// flength is in ms.
	ntotal = (int )(m_fLength * m_Format.nSamplesPerSec / 1000);		// # of bits per on-cycle
	
    if ( 16 == m_Format.wBitsPerSample)		// 16 bit???
    	{
    	short  *hpw;
    			/* Allocate memory for the short waveform data.
			     */
		hpw = new short[ m_dwTotal];
		if ( ! hpw)
			return 1;
			// algorithm....
			// f(x) = sin( x / freq / samples)
		dftotal = 100;			// shoot the first time
		ncount = 1;
		for ( dwi=0; dwi < m_dwTotal; dwi++)
			{
			if ( dftotal < 100)
				bshot = FALSE;
			else
				{
				bshot = TRUE;
				if ( ncount < ntotal)
					ncount++;
				else
					{
					dftotal -= 100;
					ncount = 1;
					}
				}

			hpw[dwi] = (bshot ? son : soff);
			dftotal += (m_bRepeat ? df : 0);		// go nowhere if not repeating
			}
		m_pWaveData = (char  *)hpw;
    	}
    	
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
CMMPulseWave::CMMPulseWave( int nSampleRate,  float fTime, float fFreq, float fLength, BOOL bNegative, BOOL bRepeat)
{

	m_nSampleRate = nSampleRate;
	m_fTime = fTime;
	m_fFreq = fFreq;
	m_fLength = fLength;
	m_bNegative = bNegative;
	m_bRepeat = bRepeat;
}


/////////////////////////////////////////////////////////////////////////////
CMMPulseWave::~CMMPulseWave()
{
	DeleteContents();
}  



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//	CMMInputWave Functionality
// 	unlike the others, this provides an input function
/////////////////////////////////////////////////////////////////////////////
// CMMWave construction

CMMInputWave::CMMInputWave()
{
	 
}   

int CMMInputWave::CreateWave(enChannel enType)			// create the wave data
{
int nbuf;

	PrepareForm( m_nChannels, 1.0f, m_fTime, m_nSampleRate);

	nbuf = (int )(.200 * m_Format.nSamplesPerSec); // buffer # of samples
	m_dwDataSize = sizeof( short) * m_nChannels * (m_dwTotal + nbuf);
	
							// now build the full data set
	
    if ( 16 == m_Format.wBitsPerSample)		// 16 bit???
    	{
    	short  *hpw;
    			/* Allocate memory for the short waveform data.and another 100ms
			     */
		hpw = new short[m_nChannels * (m_dwTotal + nbuf)];
		if ( ! hpw)
			return 1;
		m_pWaveData = (char  *)hpw;
    	}
    	
	return 0;

}

/////////////////////////////////////////////////////////////////////////////
CMMInputWave::CMMInputWave( int nSampleRate, float fTime, int nChannels, WORD wStyle)
{
	m_nChannels = nChannels;
	m_wStyle = wStyle;
	m_fTime = fTime;
	m_nSampleRate = nSampleRate;

}


/////////////////////////////////////////////////////////////////////////////
CMMInputWave::~CMMInputWave()
{
	if ( CMWaveReader == this)
		TurnOffRecording();
	DeleteContents();
}  


// return 0 if everything worked ok
// else return error result
int CMMInputWave::RecordWave(CWnd *cWindow,  BOOL bOn)
{

	if ( ! m_pWaveData)
		if ( CreateWave( chBoth) )
			return IDERR_FAILEDCREATEINWAVE;				// we have nothing to record to
		
    m_Header.lpData = (char *)m_pWaveData;
    m_Header.dwBufferLength = m_dwDataSize;
    m_Header.dwBytesRecorded = 0;
    m_Header.dwUser = 0L;
    m_Header.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
    m_Header.dwLoops = 1;
    m_Header.lpNext = NULL;
    m_Header.reserved = 0L;

	TurnOffRecording();			// if someone else was recording, too bad     
								// check the format for compatability (again)
	if (MMSYSERR_NOERROR != waveInOpen(&m_hWaveIn, WAVE_MAPPER, (LPCWAVEFORMATEX)&m_Format, 0L, 0L,
                    WAVE_FORMAT_QUERY))
	    {
			if ( m_Format.nSamplesPerSec == 48000)		// it's a 48KHz
			{
				CDlgDisable48K cdlg;
					cdlg.DoModal();
			}
			return CleanUp( IDERR_CANTREADFORMAT);
    	}               

							// ------------ Open a waveform output device.                        
        					// if we don't use (DW)(WORD ) the compiler produces ds:hwnd
     						// and waveoutopen fails!
	if ( cWindow)
		{					// if passed a window use it for callback
	    if (MMSYSERR_NOERROR != waveInOpen(&m_hWaveIn, WAVE_MAPPER,
	                  (LPCWAVEFORMATEX)&m_Format, (DWORD )(cWindow->m_hWnd), 0L, CALLBACK_WINDOW))
		    {
			return CleanUp( IDERR_FAILEDOPENINPUT);
		    }
		}
	else
		{					// not passed a window, use stock mainwnd
	    if (MMSYSERR_NOERROR != waveInOpen(&m_hWaveIn, WAVE_MAPPER,
	                  (LPCWAVEFORMATEX)&m_Format, (DWORD )(AfxGetApp()->m_pMainWnd->m_hWnd), 0L, CALLBACK_WINDOW))
		    {
			return CleanUp( IDERR_FAILEDOPENINPUT);
		    }
		}

    if(MMSYSERR_NOERROR != waveInPrepareHeader(m_hWaveIn, &m_Header, sizeof(WAVEHDR)))
	    {
		return CleanUp( IDERR_PREPAREINHDR);
		}

    /* Then the data block can be read from the input device.
     */
    	{   
    	MMRESULT mmResult;
       		mmResult = waveInAddBuffer(m_hWaveIn, &m_Header, sizeof(WAVEHDR));
			if (MMSYSERR_NOERROR != mmResult)
			{
			    waveInUnprepareHeader(m_hWaveIn, &m_Header, sizeof(WAVEHDR));
				return CleanUp( IDERR_FAILADDINBUFFER);
			}

			CMMWave *pout = WhoIsPlaying();
			if ( pout)
				pout->WaitOutput( 1000);

			mmResult = waveInStart(m_hWaveIn);
			if (MMSYSERR_NOERROR != mmResult)
        		{
			    waveInUnprepareHeader(m_hWaveIn, &m_Header, sizeof(WAVEHDR));
				return CleanUp( IDERR_FAILBLOCKREAD);
        		}
    	}
    	
	CMWaveReader = this;

	return 0;    
}

int CMMInputWave::GetCharDataSize(BOOL bTruncate)
{
int noff;
int nmax = m_dwDataSize / 4;

	if ( ! m_pWaveData)
		return 0;

	noff =  GetCharData(bTruncate) - m_pWaveData;	// offset eaten up (in bytes)
	noff /= 2 * m_Format.nChannels;			// always 16 bit samples
	if ( (noff + (int )m_dwTotal) < nmax)
		return m_dwTotal;
	else
		return nmax - noff;
}


// return the address of the character data
char   *CMMInputWave::GetCharData(BOOL bTruncate)
{
	if ( ! bTruncate)			// don't do the truncation
		return m_pWaveData;

								// find the first good data
short *minput;
int nmax = (int )(m_Format.nSamplesPerSec * .2 * m_Format.nChannels);		// 100 ms is our max
int nmin = (int )(m_Format.nSamplesPerSec * .05 * m_Format.nChannels);		// 100 ms is our max
int i, nzero;
int nf, nfmax;

	i = m_dwDataSize / (2*m_Format.nChannels);
	if ( nmax > i)
		nmax = i-1;
	if ( nmin > i)
		nmin = i-1;

	minput = (short *)m_pWaveData;

	nzero = nmin;
				// find the pair with the greatest delta
				// take note of where it lies
	nfmax = 0;
	for ( i=nmin; i<nmax; i++)	// 16 bpc
		{
		nf = minput[i] - minput[i-2];  nf = abs(nf);
		if ( nf > nfmax)
			{
			nfmax = nf;
			nzero = i;
			}
		}
				// now nzero points at the pair that is largest
	if ( ( nmin & 1) != (nzero & 1))	// is odd/even of i same as that of max pair?
		nmin++;			// move to the next pair if we need to
				// first, find 25 zeros in a row
	for (nzero = 5, i = nmin; (i<nmax) && (nzero < 25); i += 2)
		{
		nf = minput[i] - minput[i-2];  nf = abs(nf);
		if ( nf < 400)		// my sony has 400 hum....
			nzero++;
		else
			nzero = 0;
		}
					// scan until non-dc
	for ( nzero=0; i< nmax; i += 2)
		{
		if ( abs(minput[i] - minput[i-2]) > 400)	// trigger setting!!!
			nzero++;
		else
			nzero = 0;
		if ( nzero > 4)
			break;
		}

				// now find the first non-zeroes
//	for (nzero=0; (i<nmax) && (nzero < 8); i++)
//		if ( minput[i] > 20 || minput[i] < -20)
//			nzero++;
//		else
//			nzero = 0;

	if ( i > 12 )
		i -= 8;		// move back to the first 400 data point
	else
		i = 0;

	i = i / 2;		// convert to an index into data

//	i = 0;			//debug

 return (m_pWaveData + 4*i);	// convert to a pointer offset


}



/////////////////////////////////////////////////////////////////////////////
//	CMMNoiseWave Functionality

/////////////////////////////////////////////////////////////////////////////
// CMMWave construction

CMMNoiseWave::CMMNoiseWave()
{
	// TODO: add construction code here,
	 
}   

/////////////////////////////////////////////////////////////////////////////
int CMMNoiseWave::CreateWave(enChannel enType)			// create the wave data
{
CFolder *proot = NULL;

	PrepareForm( 1, 1.0f, m_fTime, m_nSampleRate);
	
							// now build the full data set
	
    if ( 16 == m_Format.wBitsPerSample)		// 16 bit???
    	{
		CDataSet *cd;
		int nmax = (int )m_dwTotal;
		float famp;
		int i;

			cd = new CDataSet();			// start empty
			cd->SetUOM( uomTime);			// time data
			cd->SetStart( 0.0f);			// time begins at 0
			cd->SetDelta(  1000.0f / (float )m_nSampleRate);
			cd->SetSize( nmax, 0);
			cd->SetDOM( uomVolts);			// use the data 
			{
			CAudtestView *pview = (CAudtestView *)CAudtestApp::GetCurrentView();
			if ( pview)
				{
				proot = (CFolder *)pview->GetDocument()->GetRoot();
				cd->SetRootObject( proot);
				}
			}

		if ( proot)
			{
			proot->AddItem( cd);		// put it in the tree so filter works
			}

		for ( i=0; i<nmax; i++)
			{
			famp = m_wAmplitude - 2 * (float )((double )m_wAmplitude * rand() / RAND_MAX);
			cd->SetAbsolute( i, famp, 0.0f);
			}
					// now filter cd
		if ( m_bFilter)		// filter is ON
			{
			CXtFilter cxt( cd, NULL, 0);
			cxt.m_nOrder = 6;
			cxt.m_fHiFreq = m_fEnd;
			cxt.m_fLowFreq = m_fStart;
			cxt.m_nShape = 1;		// butterworth
			cxt.m_nType = 2;		// bandpass
			cxt.DoOperation();
			}

					// use pink noise
		if ( ! m_nStyle)		// it's pink, filter it again
			{
			CXtFilter cxt( cd, NULL, 0);
			cxt.m_nOrder = 1;
			cxt.m_fHiFreq = m_fEnd;
			cxt.m_fLowFreq = 20.0f;
			cxt.m_nShape = 1;		// butterworth
			cxt.m_nType = 0;		// lowpass
			cxt.DoOperation();
			}

		{						// rescale
		float	fmax = cd->Maximum( dataAmp);	// get maximum amplitude
		float	fmin = -cd->Minimum( dataAmp);

			if ( fmax < fmin)
				fmax = fmin;		// use biggest of Max, -Min

			for ( i=0; i<nmax; i++)
				{
				famp = cd->DataValueAt( i);
				cd->SetAbsolute( i, famp * m_wAmplitude / fmax, 0.0f);
				}
		}

		if ( proot)				// take it back out of the tree
			{
			proot->RemoveItem( cd->GetID());
			}
					// finally, store it into our dataset
    	short  *hpw;
    			/* Allocate memory for the short waveform data.
			     */
		hpw = new short[ m_dwTotal];
		if ( ! hpw)
			{
			delete cd;
			return 1;
			}
			// algorithm....
			// f(x) = sin( x / freq / samples)
		for ( i=0; i<nmax; i++)
			{
			hpw[i] = (short )cd->DataValueAt( i);
			}
		m_pWaveData = (char  *)hpw;
		delete cd;
    	}
    	
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
CMMNoiseWave::CMMNoiseWave( int nSampleRate, float fTime, float fStart, float fEnd, BOOL bFilter, int nStyle)
{
	m_nSampleRate = nSampleRate;
	m_fTime = fTime;
	m_fStart = fStart;
	m_fEnd = fEnd;
	m_bFilter = bFilter;
	m_nStyle = nStyle;

}


/////////////////////////////////////////////////////////////////////////////
CMMNoiseWave::~CMMNoiseWave()
{
	DeleteContents();
}  


/////////////////////////////////////////////////////////////////////////////
//	CMMSweepWave Functionality

/////////////////////////////////////////////////////////////////////////////
// CMMWave construction

CMMSweepWave::CMMSweepWave()
{
	// TODO: add construction code here,
	 
}   
/////////////////////////////////////////////////////////////////////////////
int CMMSweepWave::CreateWave(enChannel enType)			// create the wave data
{
DWORD dwi;			// counter
double dfreq;
double dstep;
double dlasttime;
double dlastdata;
double ddelta;

	PrepareForm( 1, 1.0f, m_fTime, m_nSampleRate);
	
							// now build the full data set
	if ( m_fEnd < m_fStart)
		{
		float f = m_fStart;
		m_fStart = m_fEnd;
		m_fEnd = f;
		}
	
	
    if ( 16 == m_Format.wBitsPerSample)		// 16 bit???
    	{
    	short  *hpw;
    			/* Allocate memory for the short waveform data.
			     */
		hpw = new short[ m_dwTotal];
		if ( ! hpw)
			return 1;
			// algorithm....
			// f(x) = sin( x / freq / samples)
		dlastdata = 0;
		dlasttime = 0;
		for ( dwi=0; dwi < m_dwTotal; dwi++)
			{
			if ( m_bSmooth)
				dstep = dwi;					// use the count
			else
				dstep = (m_dwTotal / (double )m_uSteps) * floor( dwi * (m_uSteps+1) / (double )m_dwTotal);

			if ( m_bLinear)		// linear
				dfreq = m_fStart + (m_fEnd - m_fStart) * dstep / m_dwTotal;
			else				// logarithmic
				dfreq = m_fStart * exp((log(m_fEnd/m_fStart) * dstep / m_dwTotal));

			dstep = dwi / (double )m_Format.nSamplesPerSec;							// this is time
			dfreq *= (2 * ONEPI);													// omega

			ddelta = dfreq * ( dstep - dlasttime);			// the change in theta caused by f
			dlasttime = dstep;								// new time

								// now dfreq is the desired frequency (modulated by the ramp)
								// so delta theta is t*newfreq-t*oldfreq
								// want df' such that df'*(1 + df/dt) == dfreq
			dlastdata += ddelta;
			hpw[dwi] = (short )(.49 + m_wAmplitude * sin(dlastdata));
			}
		m_pWaveData = (char  *)hpw;
    	}
    	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
CMMSweepWave::CMMSweepWave( int nSampleRate, float fTime, float fStart, float fEnd, UINT uSteps, BOOL bSmooth, BOOL bLinear)
{

	m_nSampleRate = nSampleRate;
	m_fTime = fTime;
	m_fStart = fStart;
	m_fEnd = fEnd;
	m_uSteps = uSteps;
	m_bSmooth = bSmooth;
	m_bLinear = bLinear;


}


/////////////////////////////////////////////////////////////////////////////
CMMSweepWave::~CMMSweepWave()
{
	DeleteContents();
}  


/////////////////////////////////////////////////////////////////////////////
//	CMMBurstWave Functionality

/////////////////////////////////////////////////////////////////////////////
// CMMWave construction

CMMBurstWave::CMMBurstWave()
{
	// TODO: add construction code here,
	 
}   
/////////////////////////////////////////////////////////////////////////////
int CMMBurstWave::CreateWave(enChannel enType)			// create the wave data
{
DWORD dwi;			// counter
double dfreq;
double dstep;
double dlasttime;
double dlastdata;
double ddelta;
DWORD dwtotal;

	PrepareForm( 1, 1.0f, m_fTime, m_nSampleRate);
	
							// now build the full data set
	if ( m_fEnd < m_fStart)
		{
		float f = m_fStart;
		m_fStart = m_fEnd;
		m_fEnd = f;
		}
	
	
    if ( 16 == m_Format.wBitsPerSample)		// 16 bit???
   	{
    	short  *hpw;
    			/* Allocate memory for the short waveform data.
			     */
		hpw = new short[ m_dwTotal];
		if ( ! hpw)
			return 1;
			// algorithm....
			// f(x) = sin( x / freq / samples)
		dlastdata = 0;
		dlasttime = 0;
		dwtotal = m_Format.nSamplesPerSec * m_nCycles / m_fStart;	// total # of samples to generate
		dwtotal = min( dwtotal, m_dwTotal);		// in case this is too many bytes
		for ( dwi=0; dwi < dwtotal; dwi++)
		{
			dstep = dwi;				// smooth

//			if ( m_bLinear)		// linear
				dfreq = m_fStart + (m_fEnd - m_fStart) * dstep / m_dwTotal;
//			else				// logarithmic
//				dfreq = m_fStart * exp((log(m_fEnd/m_fStart) * dstep / m_dwTotal));

			dstep = dwi / (double )m_Format.nSamplesPerSec;							// this is time
			dfreq *= (2 * ONEPI);													// omega

			ddelta = dfreq * ( dstep - dlasttime);			// the change in theta caused by f
			dlasttime = dstep;								// new time

								// now dfreq is the desired frequency (modulated by the ramp)
								// so delta theta is t*newfreq-t*oldfreq
								// want df' such that df'*(1 + df/dt) == dfreq
			dlastdata += ddelta;
			hpw[dwi] = (short )(.49 + m_wAmplitude * sin(ONEPI * dwi / dwtotal) * sin(dlastdata));
		}

		for ( dwi; dwi < m_dwTotal; dwi++)
		{
			hpw[dwi] = 0;		// end with white space
		}

		m_pWaveData = (char  *)hpw;
   	}
    	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
CMMBurstWave::CMMBurstWave( int nSampleRate, float fTime, float fStart, float fEnd, int nCycles)
{

	m_nSampleRate = nSampleRate;
	m_fTime = fTime;
	m_fStart = fStart;
	m_fEnd = fEnd;
	m_nCycles = nCycles;

}


/////////////////////////////////////////////////////////////////////////////
CMMBurstWave::~CMMBurstWave()
{
	DeleteContents();
}  

/////////////////////////////////////////////////////////////////////////////
//	CMMTonesWave Functionality

/////////////////////////////////////////////////////////////////////////////
// CMMWave construction

CMMTonesWave::CMMTonesWave()
{
	// TODO: add construction code here,
	 
}

int CMMTonesWave::CreateWave( enChannel enType)
{
DWORD dwi;			// counter
short i;			// counter to 5
double df[5];
double dfamps[5];	// normalized amplitudes


	PrepareForm( 1, 1.0f, m_fTime, m_nSampleRate);

	{
	double dftotal = 0.0;
	for ( i=0; i<5; i++)
		if ( m_cbUse[i])
			{
			df[i] = (2 * ONEPI) * m_cfFreqs[i] / m_Format.nSamplesPerSec;
			dftotal += m_cfAmps[i];
			}
	if ( dftotal)			// we have a total amplitude
		for ( i=0; i<5; i++)	// normalize
			if ( m_cbUse[i])
				dfamps[i] = m_cfAmps[i] / dftotal;
	}
							// now build the full data set
    if ( 16 == m_Format.wBitsPerSample)		// 16 bit???
    	{
    	short  *hpw;
		double dtemp;
    			/* Allocate memory for the short waveform data.
			     */
		hpw = new short[ m_dwTotal];
		if ( ! hpw)
			return 1;
			// algorithm....
			// f(x) = sin( x / freq / samples)
		for ( dwi=0; dwi < m_dwTotal; dwi++)
			{
			dtemp = 0;
			for ( i=0; i<5; i++)			// NUMTONES
				if ( m_cbUse[i] )
					dtemp += dfamps[i] * m_wAmplitude * sin(dwi * df[i]);
			hpw[dwi] = (short )( 0.49 + dtemp);
			}
		m_pWaveData = (char  *)hpw;
    	}
    	
	return 0;

}

/////////////////////////////////////////////////////////////////////////////
CMMTonesWave::CMMTonesWave( int nSampleRate, float fTime, BOOL *pbUse, float *pfFreqs, float *pfAmps) :
				m_cbUse(), m_cfFreqs(), m_cfAmps()
{
	m_nSampleRate = nSampleRate;
	m_fTime = fTime;

int i;

	for ( i=0; i<5; i++)
		{
		m_cbUse.Add( pbUse[i] ? '\1' : '\0' );
		m_cfFreqs.Add( pfFreqs[i]);
		m_cfAmps.Add( pfAmps[i]);
		}
}


/////////////////////////////////////////////////////////////////////////////
CMMTonesWave::~CMMTonesWave()
{
	DeleteContents();
}  


/////////////////////////////////////////////////////////////////////////////
//	CMMMlsWave Functionality

/////////////////////////////////////////////////////////////////////////////
// CMMWave construction

//
// from JAES 42/4   4/1994 Vanderkooy - MLS Measuring Systems
//
#define POLYWIDTH 10
static int p_PolyOrder[17][POLYWIDTH] = 
	{	
		{ 3,1,0,0,0 },				//	     8 - 3 bits
		{ 4,1,0,0,0 },				//	    16 - 4 bits
		{ 5,2,0,0,0 },				//	    32 - 5 bits
		{ 6,1,0,0,0 },				//	    64 - 6 bits
		{ 7,1,0,0,0 },				//	   128 - 7 bits
		{ 8,6,5,1,0 },				//	   256 - 8 bits
		{ 9,4,0,0,0 },				//     512
		{ 10,7,0,0,0 },				//   1,024         
		{ 11,2,0,0,0 },				//   2,048         
		{ 12,11,10,2,0 },			//   4,096
		{ 13,12,11,9,6,5,2,1,0 },	//   8,192         
		{ 14,12,11,1,0 },			//  16,384         
		{ 15,12,11,8,7,6,4,2,0 },	//  32,768         
		{ 16,12,11,10,7,4,3,2,0 },	//  65,536         
		{ 17,14,11,9,6,5,0 },		// 131,072         
		{ 18,7,0,0,0 }, 			// 262,144         
		{ 19,6,5,1,0 }				// 524,287
		};

CMMMlsWave::CMMMlsWave()
{
	 m_bDoWarmup = true;		// start off with using a warmup
}   

/////////////////////////////////////////////////////////////////////////////
int CMMMlsWave::CreateWave(enChannel enType)			// create the wave data
{
DWORD dwi;			// counter
DWORD dwmask;
DWORD dwuppermask;
DWORD dwvalue = 1;					// the starting value and the seed
DWORD dwoffset;
int nrow;

//	fTime = dwCount / (float )dw_GetMaxRate();
	PrepareForm( 1, 1.0f, m_fTime, m_nSampleRate);
	if ( m_dwTotal < m_dwCount)
		m_dwTotal = m_dwCount;
	m_dwDataSize = m_dwTotal * sizeof( short);	// since we may have changed it
//	m_dwTotal = dwCount;				// make it exact...

	nrow = 0;
	for ( dwi = m_dwCount / 16; dwi; dwi /= 2)
		nrow++;

					// now nrow is which row of the matrix to use
	{
	int i;

	dwmask = 0;

		for ( i=0; (i<POLYWIDTH) && p_PolyOrder[nrow][i]; i++)
			{
//			dwmask |= (1 << (nrow + 3 - p_PolyOrder[nrow][i]) );
			dwmask |= (1 << (p_PolyOrder[nrow][i]-1));
			}


	dwuppermask = (1 << (nrow+2));
//	dwuppermask = 1;
	}

							// now build the full data set
    if ( 16 == m_Format.wBitsPerSample)		// 16 bit???
    	{
    	short  *hpw;
		short  *hpstart;
		int iwarmup;			//	amount to warmup
		DWORD dwmin;
								// if local on, use system amount
			iwarmup = IsWarmOn() ? CAudtestApp::GetWarmup() : 0;

		SetWarmUsed( iwarmup);			// this is what we were built with
						    			// Allocate memory for the short waveform data.
		hpstart = new short[ m_dwTotal + iwarmup];
		if ( ! hpstart)
			return 1;

		hpw = hpstart + iwarmup;

					// do the warmup data
		dwmin = (DWORD )iwarmup;
		if ( iwarmup > 20)
			dwmin -= 20;
			
		for ( dwi=0; dwi < dwmin; dwi++)
		{
		int ipass;

			if ( dwi & 8)
				ipass = ( 7 - (dwi & 7)) * 1000000;
			else
				ipass = (dwi & 7) * 1000000;
			ipass = (int )sqrt( (double)ipass);
			hpstart[dwi] = ( short )( (dwi & 16) ? (-ipass) : ipass);
		}
		for ( ; dwi < (DWORD )iwarmup; dwi++)
			hpstart[dwi] = 0;		// no garbage near the data

										// algorithm....
		for ( dwi=0; dwi < (m_dwCount-1); dwi++)
			{
//			if ( dwvalue & dwuppermask)
			if ( dwvalue & 1)
				{
				hpw[dwi] = (short )-32767;	// use -1 when data is 1?
//				dwvalue = ((dwvalue ^ dwmask) >> 1) | dwuppermask;
				dwvalue = (dwvalue >> 1) ^ dwmask;
				}
			else
				{
				hpw[dwi] = (short )32767;
				dwvalue = dwvalue >> 1;
				}
			}
		if ( m_bEmphasis)			// do preemphasis
			{
			short hplastin = hpw[0] / 2;
			short hplastout = hpw[0] / 2;

			for ( dwi = 0; dwi < (m_dwCount-1); dwi++)
				{
				short hp = hpw[dwi];
								// from butterworth at order 1
//											at 10000 hz
				hpw[dwi] = (short )(hpw[dwi] * .4634255 + hplastin * .4634255 + hplastout * .073149);
//											at 2500 hz
//				hpw[dwi] = (short )(hpw[dwi] * .152544 + hplastin * .152544 + hplastout * .694912);
//											at 1000 Hz
//				hpw[dwi] = (short )(hpw[dwi] * .0666058 + hplastin * .0666058 + hplastout * .866788);

				hplastin = hp;
				hplastout = hpw[dwi];
				}
			}
					// now repeat the mls data until we run out
#if 1
		bool bswitch = true;

		dwoffset = 0;
		for ( ; dwi < m_dwTotal; dwi++)
			{
			hpw[dwi] = (bswitch ? hpw[dwoffset] : 0);
				dwoffset++;
				if ( dwoffset == (m_dwCount-1))
				{
					dwoffset = 0;			// start over again
//					bswitch = ! bswitch;	// flip to use data
				}
			}
#else
		for ( ; dwi < m_dwTotal; dwi++)
			{
			hpw[dwi] = 0;
			}
#endif
		m_pWaveData = (char  *)hpstart;
    	}
    	
	return 0;
}   

/////////////////////////////////////////////////////////////////////////////
//	Warmup processing
/////////////////////////////////////////////////////////////////////////////

void	CMMMlsWave::SetWarmOn( bool bOn)	// turn warmup processing on/off
{
	m_bDoWarmup = bOn;		// set it
}

/////////////////////////////////////////////////////////////////////////////
CMMMlsWave::CMMMlsWave( int nSampleRate, float fTime, DWORD dwCount, BOOL bEmphasis)
{
	m_nSampleRate = nSampleRate;
	m_fTime = fTime;
	m_dwCount = dwCount;
	m_bEmphasis = bEmphasis;
	m_bDoWarmup = true;			// default to using a warmup
}


/////////////////////////////////////////////////////////////////////////////
CMMMlsWave::~CMMMlsWave()
{
	DeleteContents();
}  


/////////////////////////////////////////////////////////////////////////////
//	CMMSawtoothWave Functionality

/////////////////////////////////////////////////////////////////////////////
// CMMWave construction

CMMSawtoothWave::CMMSawtoothWave()
{
	 
}   

/////////////////////////////////////////////////////////////////////////////
int CMMSawtoothWave::CreateWave(enChannel enType)			// create the wave data
{
DWORD dwi;			// counter
double df;
double dtotal;

				// initialize the format with out only default!
				
	PrepareForm( 1, 1.0f, m_fTime, m_nSampleRate);			// use all of the amplitude
	
												// now build the full data set
	df = (1 * m_fFreq) / m_Format.nSamplesPerSec;	// # of cycles / samples
	
    if ( 16 == m_Format.wBitsPerSample)		// 16 bit???
    	{
    	short  *hpw;
    	
    	hpw = new short[m_dwTotal];
    			/* Allocate memory for the short waveform data.
			     */
		if ( ! hpw)
			return 1;
			// algorithm....
			// f(x) = sin( x / freq / samples)
		dtotal = 0;
		for ( dwi=0; dwi < m_dwTotal; dwi++)
			{
			hpw[dwi] = (short )(.49 + m_wAmplitude * dtotal);
			dtotal += df;
			if ( dtotal >= 1)
				{
//				dtotal = 2 - dtotal;
				dtotal = 0;
//				df = -df;
				}
			else
			if ( dtotal <= 0)
				{
				dtotal = -dtotal;
				df = -df;
				}
			}
		m_pWaveData = (char  *)hpw;
    	}
    	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
CMMSawtoothWave::CMMSawtoothWave( int nSampleRate, float fTime, float fFreq)
{
	m_nSampleRate = nSampleRate;
	m_fTime = fTime;
	m_fFreq = fFreq;

}


/////////////////////////////////////////////////////////////////////////////
CMMSawtoothWave::~CMMSawtoothWave()
{
	DeleteContents();
}  


//	CMMWarbleWave Functionality

/////////////////////////////////////////////////////////////////////////////
// CMMWave construction

CMMWarbleWave::CMMWarbleWave()
{
	 
}   


CMMWarbleWave::CreateWave( enChannel enType)
{
double dstart, dend;
double dfreq;
double ddelta;
double dstep;
double dlasttime;
double dlastdata;
DWORD dwi;			// counter
DWORD dwcycle;		// cycle time
DWORD dwnew;
BOOL bSmooth = TRUE;
BOOL bLinear = TRUE;		// use logarithmic
UINT uSteps = 1;			// irrelevant

				// initialize the format with out only default!
				
	PrepareForm( 1, 1.0f, m_fTime, m_nSampleRate);			// use all of the amplitude
						// start and end frequency
	dstart = m_fCenterFreq / pow(2.0,m_fOctave/2.0);
	dend =   m_fCenterFreq * pow(2.0,m_fOctave/2.0);

	dwcycle = (DWORD )(m_Format.nSamplesPerSec / (2*m_fRate));		// 1/2 cycle

											// now build the full data set
    if ( 16 == m_Format.wBitsPerSample)		// 16 bit???
    	{
    	short  *hpw = new short[m_dwTotal];	// Allocate memory for the short waveform data.
		if ( ! hpw)
			return 1;
											// algorithm....
											// f(x) = sin( lastt + newdeltat)
		dlastdata = 0;
		dlasttime = 0;
		for ( dwi=0; dwi < m_dwTotal; dwi++)
			{
//			hpw[dwi] = (short )(.49 + m_wAmplitude * dmult / dmax);
//			dstep = (dmax / (double )10) * floor( dmult * (11) / dmax);
				{
				 	dwnew = dwi % (2 * dwcycle);			// where are we in the cycles?? 
					if ( dwnew > dwcycle)
						dwnew = (2 * dwcycle) - dwnew;		// use difference to move down, not up
				}
			if ( bSmooth)
				dstep = dwnew;					// use the count
			else
				dstep = (dwcycle / (double )uSteps) * floor( dwnew * (uSteps+1) / (double )dwcycle);

			if ( bLinear)		// linear
				dfreq = dstart + (dend - dstart) * dstep / dwcycle;
			else				// logarithmic
				dfreq = dstart * exp((log(dend/dstart) * dstep / dwcycle));

			dstep = dwi / (double )m_Format.nSamplesPerSec;							// this is time
			dfreq *= (2 * ONEPI);													// omega

			ddelta = dfreq * ( dstep - dlasttime);			// the change in theta caused by f
			dlasttime = dstep;								// new time
								// now dfreq is the desired frequency (modulated by the ramp)
								// so delta theta is t*newfreq-t*oldfreq
								// want df' such that df'*(1 + df/dt) == dfreq
			dlastdata += ddelta;
			hpw[dwi] = (short )(.49 + m_wAmplitude * sin(dlastdata));
			}
		m_pWaveData = (char  *)hpw;
    	}
    	
	return 0;
}   


/////////////////////////////////////////////////////////////////////////////
CMMWarbleWave::CMMWarbleWave( int nSampleRate, float fTime, float fCenterFreq, float fOctave, float fRate)
{

	m_nSampleRate = nSampleRate;
	m_fTime = fTime;
	m_fCenterFreq = fCenterFreq;
	m_fOctave = fOctave;
	m_fRate = fRate;


}


/////////////////////////////////////////////////////////////////////////////
CMMWarbleWave::~CMMWarbleWave()
{
	DeleteContents();
}  


/////////////////////////////////////////////////////////////////////////////
//	CMMUserDefWave Functionality

/////////////////////////////////////////////////////////////////////////////
// CMMWave construction

CMMUserDefWave::CMMUserDefWave() : m_csPathName("")
{

	 
}

int    CMMUserDefWave::CreateWave( enChannel enType)
{
	if ( ! m_pWaveData)		// no data to speak of
		{
		PrepareForm( 1, 1.0f, 1.0f, m_nSampleRate);		// a dummy set, to init the vars
								// now build the full data set
		m_dwDataSize = 0;

		if( LoadWave( (LPCSTR )m_csPathName))	// it loaded ok
			{
			return 1;
			}
		}
    	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
CMMUserDefWave::CMMUserDefWave( int nSampleRate, CString *pcsPathName)
{
	m_nSampleRate = nSampleRate;
	m_csPathName = *pcsPathName;
}


/////////////////////////////////////////////////////////////////////////////
CMMUserDefWave::~CMMUserDefWave()
{
	DeleteContents();
}  


/////////////////////////////////////////////////////////////////////////////
//			CMMWave::CheckDuplex
//				see if the sound card supports duplex i/o
//				return 0 if success, error message if failure
/////////////////////////////////////////////////////////////////////////////
UINT CMMWave::CheckDuplex( void)
{
				// beef this up at some time soon....
	return 0;
}



/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL( CMMWave, CObject, VERSIONABLE_SCHEMA | 241)
IMPLEMENT_SERIAL( CMMSineWave, CMMWave, VERSIONABLE_SCHEMA | 242)
IMPLEMENT_SERIAL( CMMSquareWave, CMMWave, VERSIONABLE_SCHEMA | 243)
IMPLEMENT_SERIAL( CMMPulseWave, CMMWave, VERSIONABLE_SCHEMA | 244)
IMPLEMENT_SERIAL( CMMInputWave, CMMWave, VERSIONABLE_SCHEMA | 246)
IMPLEMENT_SERIAL( CMMNoiseWave, CMMWave, VERSIONABLE_SCHEMA | 247)
IMPLEMENT_SERIAL( CMMSweepWave, CMMWave, VERSIONABLE_SCHEMA | 248)
IMPLEMENT_SERIAL( CMMUserDefWave, CMMWave, VERSIONABLE_SCHEMA | 249)
IMPLEMENT_SERIAL( CMMMlsWave, CMMWave, VERSIONABLE_SCHEMA | 251)
IMPLEMENT_SERIAL( CMMSawtoothWave, CMMWave, VERSIONABLE_SCHEMA | 252)
IMPLEMENT_SERIAL( CMMTonesWave, CMMWave, VERSIONABLE_SCHEMA | 253)
IMPLEMENT_SERIAL( CMMWarbleWave, CMMWave,VERSIONABLE_SCHEMA |  254)
IMPLEMENT_SERIAL( CMMBurstWave, CMMWave, VERSIONABLE_SCHEMA | 255)
