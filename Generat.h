// Named.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CGENERATOR

class	CMMWave;
class	CMMInputWave;
			// number of tones we can use
#define NUMTONES 5
			// different types of generators
typedef enum tagGentypes
	{
	gtMls = 0,
	gtNoise = 1,
	gtPulse = 2,
	gtSawtooth = 3,
	gtSine = 4,
	gtSquare = 5,
	gtSweep = 6,
	gtTones = 7,
	gtWarble = 8,
	gtUserDef = 9,
	gtBurst = 10
	} GENTYPES;

class CGenerator : public CGraphed
{

	friend class CDlgGenerator;

protected: // create from serialization only
	DECLARE_SERIAL(CGenerator)

// Attributes
protected:
					// not serialized or assigned!
	CMMWave 		*m_pWave;		// the wave we are using currently sending
	CMMInputWave 	*m_pWaveIn;		// the input wave device
	time_t			m_tLastCreated;	// when we last created this

	DWORD			m_dwDataInLeft;	// left data set (not serialized)
	DWORD			m_dwDataInRight;	// right data set (not serialized)
	DWORD			m_dwDataOutRight;	// output data
	DWORD			m_dwDataOutLeft;	// output data if recorded

			// ======================  dialog info
	GENTYPES	m_nType;				// type of generator
	int		m_nSampleRate;				// sampling rate
			// mls
	DWORD	m_dwMlsCount;
	BOOL	m_bMlsEmphasis;
	BOOL	m_bMlsCorrelate;			// cross correlate???
			// noise
	float	m_fNoiseStart;
	float	m_fNoiseEnd;
	BOOL	m_bNoiseFilter;
	int		m_nNoiseType;
			// pulse
	float	m_fPulseFreq;
	float	m_fPulseLength;
	BOOL	m_bPulseNegative;
	BOOL	m_bPulseRepeat;
			// sawtooth
	float	m_fSawFreq;
			// sine
	float	m_fSineFreq;
	float	m_fSinePhase;
			// square
	float	m_fSquareFreq;
	float	m_fSquareDuty;
			// sweep
	float	m_fSweepStart;
	float	m_fSweepEnd;
	int		m_nSweepSteps;
	BOOL	m_bSweepLinear;
	BOOL	m_bSweepSmooth;
			// burst
	float	m_fBurstStart;
	float	m_fBurstEnd;
	int		m_nBurstCycles;
			// tones
	float	m_fTonesFreq[NUMTONES];
	float	m_fTonesAmp[NUMTONES];
	BOOL	m_bTonesUse[NUMTONES];
			// warble
	float	m_fWarbleCenter;
	float	m_fWarbleOctave;
	float	m_fWarbleRate;
			// user defined
	CString	m_csUserDefName;			// pathname to the wave file
			// ======================  dialog info

// Operations
public:
 	CGenerator();
	virtual int EditProperties(CWnd *pWnd, CObject *cSubject = NULL);	// bring up properties dbox
	int			PlayWave(CWnd *cWindow,  float fVolume, float fBalance = 50.0f, DWORD dwLoops = 1);
	virtual int StopPlay();			// stop the current wave
	virtual int RecordWave(CWnd *cWindow, DWORD dwTime);	// record for some amount of time
	virtual int StopRecord();			// stop the current recording
	virtual int CreateWave(DWORD dwTime);			// build the current wave for later...
	void MakeDatasets(BOOL bIn, CObject *pcLeft, CObject *pcRight, BOOL bTruncate = FALSE);	// the objects are cdatasets
	GENTYPES	GetStyle(void )					{ return m_nType; }
	BOOL		GetMlsEmphasis(void )			{ return m_bMlsEmphasis; }
	int			GetMlsSize(void )				{ return (int )m_dwMlsCount; }
	BOOL		GetMlsCorrelate( void)			{ return m_bMlsCorrelate;	}
	void		SetMls( DWORD dwSize, BOOL bEmphasis, BOOL bCorrel);
	void		SetSine( float fFreq, float fPhase);
	void		SetSquare( float fFreq, float fDuty);
	void		SetIntermod( float fFreq1, float fFreq2);
	int			GetSampleRate(void )			{ return m_nSampleRate; }
	void		SetSampleRate(int nNew);

	virtual int	Import( LPCSTR szFileName);				// import some data
	virtual int Export( LPCSTR szFileName);				// export some data
	virtual	void BuildDataSets( void);
	virtual BOOL	CreateChart( CNamed *cBase = NULL);			// build a new chart object to be graphed
	virtual void GetFilter( CString& csExt, CString& csFilter);

	
// Implementation
public:
	virtual ~CGenerator();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

	virtual NAMETYPES GetType(void)	const 	{ return ntGenerator; }

	virtual CNamed *Duplicate();				// make a duplicate object (different id)
	CNamed &operator=(const CNamed &cIn);
	CGenerator &operator=(const CGenerator &cIn);

#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:

private:
};


#define CGENERATOR

#endif
