// speaker.cpp : implementation of the CGeneratorArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include "dataSet.h"
#include "Chart.h"

#include "generat.h"

#include "mmwave.h"
#include "opitem.h"

#include "zFormEdt.h"
#include "dlggener.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CGenerator

IMPLEMENT_SERIAL(CGenerator, CGraphed, VERSIONABLE_SCHEMA | 3)


/////////////////////////////////////////////////////////////////////////////
// CGenerator construction/destruction

CGenerator::CGenerator() : m_csUserDefName( cNullString)
{
int i;
	
	m_nType = gtSine;
	m_nSampleRate = CMMWave::GetMaxRate();	// my default is high rate of speed

		// TODO: add one-time construction code here
	m_pWave = NULL;
	m_pWaveIn = NULL;
	m_tLastCreated = 0;

	m_dwDataInLeft = 0;		// left data set (not serialized)
	m_dwDataInRight = 0;	// right data set (not serialized)
	m_dwDataOutRight = 0;	// output data
	m_dwDataOutLeft = 0;	// output data
		// init variableds...
			// mls
	m_dwMlsCount = 1024;
	m_bMlsEmphasis  = FALSE;
	m_bMlsCorrelate = TRUE;
			// noise
	m_fNoiseStart = (float )20;
	m_fNoiseEnd = (float )20000;
	m_bNoiseFilter = TRUE;
	m_nNoiseType = 0;
			// pulse
	m_fPulseFreq = (float )1000;
	m_fPulseLength = (float )0;
	m_bPulseNegative = FALSE;
	m_bPulseRepeat = FALSE;
			// sawtooth
	m_fSawFreq = (float )1000;
			// sine
	m_fSineFreq = (float )1000;
	m_fSinePhase = (float )0;
			// square
	m_fSquareFreq = (float )1000;
	m_fSquareDuty = (float )50;
			// sweep
	m_fSweepStart = (float )20;
	m_fSweepEnd = (float )20000;
	m_nSweepSteps = 10;
	m_bSweepLinear = TRUE;
	m_bSweepSmooth = TRUE;

	m_fBurstStart	= 100.0f;
	m_fBurstEnd		= 100.0f;
	m_nBurstCycles	= 5;

				// tones
	for ( i=0; i<NUMTONES; i++)
		{
		m_fTonesFreq[i] = (float )(1000 * (i+1));
		m_fTonesAmp[i] = (float )50;
		m_bTonesUse[i] = TRUE;
		}

	m_fWarbleCenter = 500.0f;
	m_fWarbleOctave = 0.5f;
	m_fWarbleRate = 10.0f;

}

CGenerator::~CGenerator()
{

	if ( m_pWave)
		delete m_pWave;
	if ( m_pWaveIn)
		delete m_pWaveIn;
}

/////////////////////////////////////////////////////////////////////////////
// CGenerator serialization

void CGenerator::Serialize(CArchive& ar)
{
WORD w;
DWORD dw;
int i;

	CGraphed::Serialize( ar);

	if (ar.IsStoring())
	{		// storing code here
		ar <<	(WORD )m_nType;
		ar <<   (DWORD )m_nSampleRate;
				// ================== dialog data
				// mls
		ar <<	(WORD )m_bMlsEmphasis;
		ar <<  m_dwMlsCount;
		ar <<	(WORD )m_bMlsCorrelate;
				// noise
		ar <<	m_fNoiseStart;
		ar << 	m_fNoiseEnd;
		ar <<	(WORD )m_bNoiseFilter;
		ar <<	(WORD )m_nNoiseType;
				// pulse
		ar <<	m_fPulseFreq;
		ar <<	m_fPulseLength;
		ar <<	(WORD )m_bPulseNegative;
		ar <<	(WORD )m_bPulseRepeat;
				// sawtooth
		ar <<	m_fSawFreq;
				// sine
		ar <<	m_fSineFreq;
		ar <<	m_fSinePhase;
				// square
		ar <<	m_fSquareFreq;
		ar <<	m_fSquareDuty;
				// sweep
		ar <<	m_fSweepStart;
		ar <<	m_fSweepEnd;
		ar <<	(DWORD )m_nSweepSteps;
		ar <<	(WORD )m_bSweepSmooth;
		ar <<	(WORD )m_bSweepLinear;
				// burst
		ar <<	m_fBurstStart;
		ar <<	m_fBurstEnd;
		ar <<	m_nBurstCycles;
				// tones
		for ( i=0; i<NUMTONES; i++)
			{
			ar << m_fTonesFreq[i];
			ar << m_fTonesAmp[i];
			ar << (WORD )m_bTonesUse[i];
			}

		ar << m_fWarbleCenter;
		ar << m_fWarbleOctave;
		ar << m_fWarbleRate;
			// user defined
		ar << m_csUserDefName;			// pathname to the wave file

				// ================== dialog data
#if 0
		if ( m_pWave)
			{
			ar << (WORD )1;
			m_pWave->Serialize(ar);		// the wave we are using currently
			}
		else
			ar << (WORD )0;
#endif
	}
	else
	{
		ar >>	w; m_nType = (GENTYPES )w;
		ar >>	dw; m_nSampleRate = (int )dw;
				// ================== dialog data
				// mls
		ar >>	w; m_bMlsEmphasis = (BOOL )w;
		ar >>	m_dwMlsCount;
		ar >>	w; m_bMlsCorrelate = w;
				// noise
		ar >>	m_fNoiseStart;
		ar >> 	m_fNoiseEnd;
		ar >>	w; m_bNoiseFilter = w;
		ar >>	w; m_nNoiseType = w;
				// pulse
		ar >>	m_fPulseFreq;
		ar >>	m_fPulseLength;
		ar >>	w; m_bPulseNegative = w;
		ar >>	w; m_bPulseRepeat = w;
				// sawtooth
		ar >>	m_fSawFreq;
				// sine
		ar >>	m_fSineFreq;
		ar >>	m_fSinePhase;
				// square
		ar >>	m_fSquareFreq;
		ar >>	m_fSquareDuty;
				// sweep
		ar >>	m_fSweepStart;
		ar >>	m_fSweepEnd;
		ar >>	dw; m_nSweepSteps = (UINT )dw;
		ar >>	w; m_bSweepSmooth = w;
		ar >>	w; m_bSweepLinear = w;

				// burst
		if ( GetSchema() > 2)
		{
			ar >>	m_fBurstStart;
			ar >>	m_fBurstEnd;
			ar >>	m_nBurstCycles;
		}
		else
		{
			m_fBurstStart = 100.0f;
			m_fBurstEnd = 100.0f;
			m_nBurstCycles = 5;
		}
				// tones
		for ( i=0; i<NUMTONES; i++)
			{
			ar >> m_fTonesFreq[i];
			ar >> m_fTonesAmp[i];
			ar >> w; m_bTonesUse[i] = w;
			}
				// warble
		ar >> m_fWarbleCenter;
		ar >> m_fWarbleOctave;
		ar >> m_fWarbleRate;
				// user defined
		ar >> m_csUserDefName;			// pathname to the wave file


				// ================== dialog data
#if 0
		ar >> w;
		if ( w)		// do we have a wave???
			{
			if ( ! m_pWave)
				m_pWave = new CMMWave;
			m_pWave->Serialize(ar);		// the wave we are using currently
			}
#endif
	}
}

int   CGenerator::EditProperties(CWnd *pParent, CObject * )	// bring up properties dbox
{
CDlgGenerator cgen( pParent);
int nresult;
COpCode *cop;

	cgen.UseGenerator(this);

	nresult = cgen.DoModal();
	if ( IDOK == nresult)
		{
		CGenerator *cgnew = (CGenerator *)Duplicate();
		cgen.SetGenerator(cgnew );
		cop = new COpChange( this, cgnew);
		if ( cop)
			cop->QueueAndDo();
		}

	return nresult;	

}

int CGenerator::RecordWave(CWnd *cWindow, DWORD dwTime)		// play or stop the current wave
{

	if ( m_pWaveIn)
		{				// don't delete this if we can reuse it
		if ( m_pWaveIn->GetTime() != (dwTime/1000.0) ||
			 m_pWaveIn->GetChannels() != 2 ||
			 m_pWaveIn->GetStyle() != 3 ||
			 m_nSampleRate != (int )m_pWaveIn->GetSamplesPerSecond())
			 {
				delete m_pWaveIn;
				m_pWaveIn = NULL;
			 }
		}
	if ( ! m_pWaveIn)
		m_pWaveIn = new CMMInputWave(  m_nSampleRate, dwTime / 1000.0f, 2, 3);		// use both channels by default
	if ( ! m_pWaveIn)
	{
		AfxMessageBox(IDERR_FAILEDCREATEINPUT);
		return IDERR_FAILEDCREATEINPUT;
	}
	return ( m_pWaveIn->RecordWave(cWindow, TRUE) );	// yes, go
}


int CGenerator::StopRecord(void)		// stop the current wave
{
	if ( m_pWaveIn)
		{
		m_pWaveIn->TurnOffRecording();
		m_pWaveIn->TurnOffSound();
		}

	return 1;		// can't turn it off yet
}


int CGenerator::StopPlay(void)		// stop the current wave
{
	if ( ! m_pWave)		// unspeced error
		return 1;

	m_pWave->TurnOffSound();

	return 1;		// can't turn it off yet
}

int CGenerator::PlayWave(CWnd *cWindow, float fVolume, float fBalance,  DWORD dwLoops)
{
	if ( ! m_pWave)		// unspeced error
		return 1;

	return ( m_pWave->PlayWave(cWindow, fVolume, fBalance, dwLoops) );	// looping constant off
}

int CGenerator::CreateWave(DWORD dwTime)	// build the current wave for later...
{
float ftime = (float )(dwTime / 1000.0);

			// if it's MLS and warmup has changed
	if ( m_pWave && m_pWave->IsKindOf( RUNTIME_CLASS( CMMMlsWave)))
	{
	CMMMlsWave *pwave  = (CMMMlsWave *)m_pWave;

	if ( ( pwave->IsWarmOn() ? CAudtestApp::GetWarmup() : 0 ) != pwave->GetWarmUsed()) 	// different warm values
			SetLastEdit();
	}

				// based on current type setting create a new wave file
	if ( m_pWave &&
		 ftime == m_pWave->GetTime() &&
		 m_tLastCreated == GetLastEdit() )
		 return 0;


	if ( m_pWave)
		{
		delete m_pWave;
		m_pWave = NULL;
		}

	switch( m_nType)
		{
		case gtBurst :
			m_pWave = new CMMBurstWave( m_nSampleRate,  ftime, m_fBurstStart, m_fBurstEnd, m_nBurstCycles);
			break;
		case gtMls :
			m_pWave = new CMMMlsWave( m_nSampleRate, ftime, m_dwMlsCount, m_bMlsEmphasis);
			break;
		case gtNoise :
			m_pWave = new CMMNoiseWave( m_nSampleRate,  ftime, m_fNoiseStart, m_fNoiseEnd, m_bNoiseFilter, m_nNoiseType);
			break;
		case gtPulse :
			m_pWave = new CMMPulseWave( m_nSampleRate,  ftime, m_fPulseFreq, m_fPulseLength, m_bPulseNegative, m_bPulseRepeat);
			break;
		case gtSawtooth :
			m_pWave = new CMMSawtoothWave( m_nSampleRate,  ftime, m_fSawFreq);
			break;
		case gtSine :
			m_pWave = new CMMSineWave( m_nSampleRate,  ftime, m_fSineFreq, m_fSinePhase);
			break;
		case gtSquare :
			m_pWave = new CMMSquareWave( m_nSampleRate,  ftime, m_fSquareFreq, m_fSquareDuty);
			break;
		case gtSweep :
			m_pWave = new CMMSweepWave( m_nSampleRate,  ftime, m_fSweepStart, m_fSweepEnd, m_nSweepSteps, m_bSweepSmooth, m_bSweepLinear);
			break;
		case gtTones :
			m_pWave = new CMMTonesWave( m_nSampleRate,  ftime, m_bTonesUse, m_fTonesFreq, m_fTonesAmp);
			break;
		case gtWarble :
			m_pWave = new CMMWarbleWave( m_nSampleRate,  ftime, m_fWarbleCenter, m_fWarbleOctave, m_fWarbleRate);
			break;
		case gtUserDef :
			m_pWave = new CMMUserDefWave( m_nSampleRate,  &m_csUserDefName);
			break;
		default :
			m_pWave = new CMMSineWave( m_nSampleRate,  ftime, m_fSineFreq, (float )0);
			m_nType = gtSine;			// set this
			break;
		}

	if ( m_pWave)	// the above create worked
		{
		if ( ! m_pWave->CreateWave( chMono)) // create the wavefile
			{
			m_tLastCreated = GetLastEdit();			// sync building the wave with current specs

			if ( gtUserDef == m_nType)		// it's user defined, set the samplerate from the data
				{
				m_nSampleRate = m_pWave->GetSamplesPerSecond();
				}

			BuildDataSets();			// new data sets
			}
		}

	return (NULL == m_pWave);
}

//		MakeDatasets
// this takes the left and right channel i/o(bIn) data and converts them
// to pcLeft and pcRight datasets
void CGenerator::MakeDatasets(BOOL bIn, CObject *pcLeft, CObject *pcRight, BOOL bTruncate)
{
CDataSet *pcleft = (CDataSet *)pcLeft;
CDataSet *pcright = (CDataSet *)pcRight;
CMMWave *pwave;

	if ( bIn)			// use input data
		pwave = m_pWaveIn;
	else
		pwave = m_pWave;

					// save this for charting purposes
	m_dwDataOutLeft = ( pcLeft ? pcleft->GetID() : 0);
	m_dwDataOutRight = ( pcRight ? pcright->GetID() : 0);

	if ( ! pwave)
		return;				// !!! message needed

	pwave->ConvertToData( pcLeft, pcRight, bTruncate);
}





/////////////////////////////////////////////////////////////////////////////
// CGenerator diagnostics

#ifdef _DEBUG
void CGenerator::AssertValid() const
{
	CGraphed::AssertValid();
}

void CGenerator::Dump(CDumpContext& dc) const
{
	CGraphed::Dump(dc);
}

#endif //_DEBUG

int	CGenerator::Import( LPCSTR szFileName)								// import some data
{
int nresult = 0;

	if (! m_pWave)
		{
		m_pWave = new CMMWave();
		}

	nresult = m_pWave->LoadWave( szFileName);	// this does all the editing of m_pWave for us
	if ( ! nresult)			// it worked
		{
		m_csUserDefName = szFileName;
		m_nType = gtUserDef;
		m_nSampleRate = m_pWave->GetSamplesPerSecond();
		}
	return nresult;
}


int CGenerator::Export( LPCSTR szFileName)								// export some data
{
	if ( ! m_pWave)
		CreateWave( 100);			// 1/10th of a second

	if ( ! m_pWave)
		return 1;

	m_pWave->SaveWave( szFileName);
	return 0;
}

void CGenerator::GetFilter( CString& csExt, CString& csFilter)
{
	csExt = "WAV";
	csFilter = "Wave Files (*.WAV)|*.WAV|All Files (*.*)|*.*||";

}



CNamed *CGenerator::Duplicate(void )
{
CNamed *cnew = new CGenerator();

	*cnew = *this;
	return cnew;
}


				// operators
CGenerator &CGenerator::operator=(const CGenerator &cIn)
{
CNamed &cin = (CNamed &)cIn;

	*this = cin;
 	return *this;
}



CNamed &CGenerator::operator=(const CNamed &cIn)
{
CGenerator &cin = (CGenerator &)cIn;
int i;

 	CGraphed::operator=( cIn);

					// don't copy the id # or the pointers
		m_nType = cin.m_nType;
		m_nSampleRate = cin.m_nSampleRate;
		                     //      
							 // dialog data
		m_fBurstStart	= cin.m_fBurstStart;
		m_fBurstEnd		= cin.m_fBurstEnd;
		m_nBurstCycles	= cin.m_nBurstCycles;
		                                // mls
		m_bMlsEmphasis  = cin.m_bMlsEmphasis;
		m_dwMlsCount	= cin.m_dwMlsCount;
		m_bMlsCorrelate = cin.m_bMlsCorrelate;
		                                                // noise
		m_fNoiseStart	= cin.m_fNoiseStart;
		m_fNoiseEnd 	= cin.m_fNoiseEnd ;
		m_bNoiseFilter	= cin.m_bNoiseFilter;
		m_nNoiseType	= cin.m_nNoiseType;
		                                                // pulse
		m_fPulseFreq	= cin.m_fPulseFreq;
		m_fPulseLength	= cin.m_fPulseLength;
		m_bPulseNegative= cin.m_bPulseNegative;
		m_bPulseRepeat= cin.m_bPulseRepeat;
		                                                // sawtooth
		m_fSawFreq		= cin.m_fSawFreq;
		                                                // sine
		m_fSineFreq 	= cin.m_fSineFreq ;
		m_fSinePhase 	= cin.m_fSinePhase ;
		                                                // square
		m_fSquareFreq	= cin.m_fSquareFreq;
		m_fSquareDuty	= cin.m_fSquareDuty;
		                                                // sweep
		m_fSweepStart	= cin.m_fSweepStart;
		m_fSweepEnd		= cin.m_fSweepEnd;
		m_nSweepSteps	= cin.m_nSweepSteps;
		m_bSweepSmooth	= cin.m_bSweepSmooth;
		m_bSweepLinear	= cin.m_bSweepLinear;

				// tones
		for ( i=0; i<NUMTONES; i++)
			{
			m_fTonesFreq[i] = cin.m_fTonesFreq[i];
			m_fTonesAmp[i] = cin.m_fTonesAmp[i];
			m_bTonesUse[i] = cin.m_bTonesUse[i];
			}

		m_fWarbleRate   = cin.m_fWarbleRate;
		m_fWarbleCenter	= cin.m_fWarbleCenter;
		m_fWarbleOctave	= cin.m_fWarbleOctave;

		m_csUserDefName = cin.m_csUserDefName;

 	return *this;
}


void	CGenerator::BuildDataSets()
{
CDataSet *pcdata;
CString csname = GetName() + ".Output";

	if ( ! m_pWave)
		CreateWave( 20);			// get 20ms of data

	pcdata = (CDataSet *)CreateByName( csname, ntDataSet);

	if ( pcdata)
		MakeDatasets( FALSE, pcdata, NULL);

}

BOOL	CGenerator::CreateChart( CNamed *cBase)			// build a new chart object to be graphed
{
CSubChart *cch;

					// build the chart
	if ( ! (m_dwDataOutLeft || m_dwDataOutRight))
		{				// we need some data
		BuildDataSets();
		}

	if ( m_dwDataOutLeft || m_dwDataOutRight || m_dwDataInLeft || m_dwDataInRight)
		{
		cch = new CSubChart();
		cch->SetRootObject( (CNamed *)GetRootObject());						// since it doesn't get added to the tree
		cch->CreateDefault( GetName(), uomTime);
		if ( m_dwDataOutLeft)
			cch->Attach( m_dwDataOutLeft, FALSE);			// use the phase for this guy
		if ( m_dwDataOutRight)
			cch->Attach( m_dwDataOutRight, FALSE);			// use the phase for this guy
		if ( m_dwDataInLeft)
			cch->Attach( m_dwDataInLeft, FALSE);			// use the phase for this guy
		if ( m_dwDataInRight)
			cch->Attach( m_dwDataInRight, FALSE);			// use the phase for this guy
		SetChart( cch);
		delete cch;
		}
	else
		SetChart( NULL);		// delete any old chart



	return TRUE;
}


void		CGenerator::SetIntermod( float fFreq1, float fFreq2)
{
int i;

		for ( i=0; i<NUMTONES; i++)
			{
			m_bTonesUse[i] = (i < 2);
			}
		m_fTonesFreq[0] = fFreq1;
		m_fTonesAmp[0] = (float )50;
		m_fTonesFreq[1] = fFreq2;
		m_fTonesAmp[1] = (float )50;

		m_nType = gtTones;
		SetLastEdit();

}

void CGenerator::SetMls( DWORD dwSize, BOOL bEmphasis, BOOL bCorrel)
{
	if ( m_nType != gtMls || 
		 m_dwMlsCount != dwSize || 
		 m_bMlsEmphasis != bEmphasis || 
		 m_bMlsCorrelate != bCorrel)
		{
		m_nType = gtMls; 
		m_dwMlsCount = dwSize; 
		m_bMlsEmphasis = bEmphasis; 
		m_bMlsCorrelate = bCorrel; 

		SetLastEdit();
		}
}

void CGenerator::SetSine( float fFreq, float fPhase)
{
	if ( m_nType != gtSine ||
		 m_fSineFreq != fFreq ||		// this is all new stuff
		 m_fSinePhase != fPhase)		// so set it and setlastedit
		{
		m_nType = gtSine; 
		m_fSineFreq = fFreq; 
		m_fSinePhase = fPhase;

		SetLastEdit();
		}

}

void CGenerator::SetSquare( float fFreq, float fDuty)
{
	if ( m_nType != gtSquare ||
		 m_fSquareFreq != fFreq ||		// this is all new stuff
		 m_fSquareDuty != fDuty)		// so set it and setlastedit
		{
		m_nType = gtSquare; 
		m_fSquareFreq = fFreq; 
		m_fSquareDuty = fDuty;

		SetLastEdit();
		}

}

void CGenerator::SetSampleRate(int nNew)
{
	if ( m_nSampleRate != nNew)
		{
		m_nSampleRate = nNew; 
		SetLastEdit(); 
		}
}
	


