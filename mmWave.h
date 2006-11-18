// zsound.h : main header file for the ZSOUND application
//

#ifndef _INC_MMWAVE

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
                		// if mmsystem not loaded, do so using internal defn
#ifndef _INC_MMSYSTEM         
#include "mmsystem.h"
#endif

#define _INC_MMWAVE


#define ON_MM_WOM_DONE() \
	{ MM_WOM_DONE, 0, AfxSig_vh, \
		(AFX_PMSG)(AFX_PMSGW)(void (AFX_MSG_CALL CWnd::*)(HWAVEOUT ))OnMMWomDone },

#define ON_MM_WIM_DATA() \
	{ MM_WIM_DATA, 0, AfxSig_vh, \
		(AFX_PMSG)(AFX_PMSGW)(void (AFX_MSG_CALL CWnd::*)(HWAVEIN ))OnMMWimData },


// #include "resource.h"		// main symbols

#define IDERR_FILENOTFOUND 100
#define IDERR_NOTWAVE 101
#define IDERR_CORRUPT 102
#define IDERR_FAILREAD 103
#define IDERR_NODATA 104
#define IDERR_NOTPCM 105


/////////////////////////////////////////////////////////////////////////////
// CMMWave:
// See zsound.cpp for the implementation of this class
//


class CMMWave : public CObject
{     
DECLARE_SERIAL( CMMWave)

public:  
//AFX required stuff
	virtual void Serialize( CArchive &ar);
	CMMWave();
	~CMMWave(); 
	
	void ConvertToData(CObject *pcLeft, CObject *pcRight, BOOL bTruncate);	// convert to datasets...
	void ConvertFromData(CObject *pcLeft, CObject *pcRight);	// convert from datasets...

	int  SaveWave( const char*  pszFileName);
	int  LoadWave( const char*  pszFileName);
//
	int PlayWave(CWnd *cWindow,  float fVolume, float fBalance = 50.0f, int nLoops = 1);

	virtual int CreateWave(enChannel enType);			// create the wave data

	void	SetVolume( float fVolume = 100.0f, float fBalance = 50.0f)	{ m_fVolume = fVolume; m_fBalance = fBalance; }
	float	GetTime( void)				 { return m_fTime; }
	DWORD 	GetSize( void)				 { return ( m_dwTotal ); }
	int		GetChannels( void)            { return (int )(m_Format.nChannels); } 
	int		GetBitsPerSample( void)		 { return (int )(m_Format.wBitsPerSample); }
	DWORD	GetSamplesPerSecond( void)	 { return ( m_Format.nSamplesPerSec); }
	virtual char   *GetCharData( BOOL bTruncate = TRUE);
	virtual int		GetCharDataSize(BOOL bTruncate = TRUE);

	static CMMWave *WhoIsPlaying( void);
	static CMMWave *WhoIsRecording( void);				// return who is recording
	static  const CDWordArray *GetRateArray( void);		// get rate array supported
	static  DWORD GetMaxRate( void);					// get max sample rate supported

	static	int		TurnOffSound( void);				// turn off playback and recording
	static	int		TurnOffRecording( void);			// turn off any recording device

	static	UINT	CheckDuplex( void);			// see if the card supports full duplex right

	int		WaitOutput( DWORD dwWait);

protected:
	virtual void DeleteContents();
	int		CleanUp( UINT uidPrompt);			// message box and return passed uint

	void	SetNotify(DWORD dwIn)		{ m_dwNotify = dwIn; }	// set word to notify at
	int		WaitNotify( DWORD dwWait);

						// note dure is in 0.1ms units (e.g. wDure=10,000 <=> 1 second)
	virtual void PrepareForm( int nChannels, float fMaxAmp, float fTime, int nSampleRate);
						// internal i/o functions
	int		LoadWaveFile( CArchive& ar);
	int		SaveWaveFile( CArchive& ar);

					// --- these items define the wave data itself
protected: 						// ---- temporary data sets
	char	   *m_pWaveData; 	// where the actual wave data is
	DWORD		m_dwDataSize;	// how much data in bytes
	DWORD		m_dwTotal;		// # of samples in the wave
	HWAVEOUT	m_hWaveOut;		// who is playing this???
	HWAVEIN		m_hWaveIn;		// who is recording this???
	WAVEHDR		m_Header;		// descriptor of the data (for use while playing) 

	WAVEFORMATEX m_Format;		// format of the data
	DWORD		m_dwNotify;		// time to notification

					// --- these items describe the wave to be built
								// ---- permanent data sets
protected:						// these belong to all of the superclasses
	WORD		m_wAmplitude;	// max amplitude of data
	int			m_nSampleRate;	// temp storage for functions
	float		m_fTime;		// the time requested
	float		m_fVolume;		// output volume control setting
	float		m_fBalance;		// the balance on output
	
}; 


class CMMSineWave : public CMMWave
{
DECLARE_SERIAL( CMMSineWave)

public:  
	virtual int CreateWave(enChannel enType);			// create the wave data
	CMMSineWave( int nSampleRate, float fTime, float fFreq, float fPhase);
	~CMMSineWave();
//
protected:
	float m_fPhase;
	float m_fFreq;
	CMMSineWave();
	
private:
	
};

class CMMSquareWave : public CMMWave
{
DECLARE_SERIAL( CMMSquareWave)

public:  
	virtual int CreateWave(enChannel enType);			// create the wave data
	CMMSquareWave( int nSampleRate, float fTime, float fFreq, float fDutyCycle);
	~CMMSquareWave();
//
protected:
	float	m_fFreq;
	float	m_fDutyCycle;

	CMMSquareWave();
	
private:
	short m_wDuty;			// 0...100 duty cycle
	
};

class CMMPulseWave : public CMMWave
{
DECLARE_SERIAL( CMMPulseWave)

public:
	virtual int CreateWave(enChannel enType);			// create the wave data
	CMMPulseWave( int nSampleRate, float fTime, float fFreq, float fLength, BOOL bNegative, BOOL bRepeat);
	~CMMPulseWave();
//
protected:
	float	m_fFreq;
	float	m_fLength;
	BOOL	m_bNegative;
	BOOL	m_bRepeat;

	CMMPulseWave();
	
private:
	
};


class CMMInputWave : public CMMWave
{
DECLARE_SERIAL( CMMInputWave)

protected:
	int		m_nChannels;
	WORD	m_wStyle;

public:  
	virtual int CreateWave(enChannel enType);			// create the wave data
	int		GetChannels( void)				{ return m_nChannels; }
	WORD	GetStyle( void)					{ return m_wStyle;	}

	CMMInputWave( int nSampleRate, float fTime, int nChannels, WORD wStyle);
	~CMMInputWave();

	virtual int RecordWave(CWnd *cWindow, BOOL bOn);
	virtual char   *GetCharData(BOOL bTruncate = TRUE);		// overridden in order to strip leading junk
	virtual int		GetCharDataSize(BOOL bTruncate = TRUE);
//
protected:
	CMMInputWave();
	
};


class CMMNoiseWave : public CMMWave
{
DECLARE_SERIAL( CMMNoiseWave)

public:  
	virtual int CreateWave(enChannel enType);			// create the wave data
	CMMNoiseWave( int nSampleRate, float fTime, float fStart, float fEnd, BOOL bFilter, int nStyle);
	~CMMNoiseWave();
//
protected:
	float m_fStart;
	float m_fEnd;
	BOOL m_bFilter;
	int m_nStyle;

	CMMNoiseWave();
	
private:
	
};


class CMMSweepWave : public CMMWave
{
DECLARE_SERIAL( CMMSweepWave)

public:  
	virtual int CreateWave(enChannel enType);			// create the wave data
	CMMSweepWave( int nSampleRate, float fTime, float fStart, float fEnd, UINT uSteps, BOOL bSmooth, BOOL bLinear);
	~CMMSweepWave();
//
protected:

	float	m_fStart;
	float	m_fEnd;
	UINT	m_uSteps;
	BOOL	m_bSmooth;
	BOOL	m_bLinear;

	CMMSweepWave();
	
private:
	
};

class CMMBurstWave : public CMMWave
{
DECLARE_SERIAL( CMMBurstWave)

public:  
	virtual int CreateWave(enChannel enType);			// create the wave data
	CMMBurstWave( int nSampleRate, float fTime, float fStart, float fEnd, int nCycles);
	~CMMBurstWave();
//
protected:

	float	m_fStart;
	float	m_fEnd;
	int		m_nCycles;

	CMMBurstWave();
	
private:
	
};


class CMMTonesWave : public CMMWave
{
DECLARE_SERIAL( CMMTonesWave)

public:  
	virtual int CreateWave(enChannel enType);			// create the wave data
	CMMTonesWave( int nSampleRate, float fTime, BOOL *pbUse, float *pfFreqs, float *pfAmps);
	~CMMTonesWave();
//
protected:

	CByteArray m_cbUse;
	CFloatArray m_cfFreqs;
	CFloatArray m_cfAmps;

	CMMTonesWave();
	
private:
	
};


class CMMMlsWave : public CMMWave
{
DECLARE_SERIAL( CMMMlsWave)

public:  
	virtual int CreateWave(enChannel enType);			// create the wave data
	CMMMlsWave( int nSampleRate, float fTime, DWORD dwCount, BOOL bEmphasis);
	void	SetWarmOn( bool bOn);	// turn warmup processing on/off
	bool	IsWarmOn( void)	{ return m_bDoWarmup; }	// is warmup turned on
	int		GetWarmUsed( void)	{ return m_iWarmUsed; }
	void	SetWarmUsed( int iUsed) { m_iWarmUsed = iUsed; }	// set amount of warmup
	~CMMMlsWave();
//
protected:
	DWORD m_dwCount;
	BOOL  m_bEmphasis;		// pre-filter
	bool	m_bDoWarmup;	// do a warmup for this guy?
	int		m_iWarmUsed;	// amount of warmup used on create

	CMMMlsWave();
	
private:
	
};


class CMMSawtoothWave : public CMMWave
{
DECLARE_SERIAL( CMMSawtoothWave)

public:  
	virtual int CreateWave(enChannel enType);			// create the wave data
	CMMSawtoothWave( int nSampleRate, float fTime, float fFreq);
	~CMMSawtoothWave();
//
protected:
	float	m_fFreq;

	CMMSawtoothWave();
	
private:
	
};


class CMMWarbleWave : public CMMWave
{
DECLARE_SERIAL( CMMWarbleWave)

public:  
	virtual int CreateWave(enChannel enType);			// create the wave data
	CMMWarbleWave( int nSampleRate, float fTime, float fCenterFreq, float fOctave, float fRate);
	~CMMWarbleWave();
//
protected:

	float	m_fCenterFreq;
	float	m_fOctave;
	float	m_fRate;

	CMMWarbleWave();
	
private:
	
};

class CMMUserDefWave : public CMMWave
{
DECLARE_SERIAL( CMMUserDefWave)

public:  
	virtual int CreateWave(enChannel enType);			// create the wave data
	CMMUserDefWave( int nSampleRate, CString *pcsPathName);
	~CMMUserDefWave();
//
protected:
	CString m_csPathName;

	CMMUserDefWave();
	
private:
	
};


#endif

/////////////////////////////////////////////////////////////////////////////
