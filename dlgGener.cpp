// dlggener.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlggener.h"

#include "mmwave.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGenerator

IMPLEMENT_DYNAMIC(CDlgGenerator, CPropertySheet)

static GENTYPES n_TypeList[] = 
{
	gtBurst,
	gtMls,
	gtNoise,
	gtPulse,
	gtSawtooth,
	gtSine,
	gtSquare,
	gtSweep,
	gtTones,
	gtWarble,
	gtUserDef,
	(GENTYPES )-1
};

// convert an int generator type into an index for the combobox
static int FindGenType( int nType)
{
int i;

	for ( i=0; -1 != n_TypeList[i]; i++)
		if ( nType == n_TypeList[i])
			return i;
	return -1;			// what do we do here
}

CDlgGenerator::CDlgGenerator(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDS_GENERATE, pParentWnd, iSelectPage),
		m_cSine(), m_cSweep(), m_cMls(), m_cPulse()
{
	EnableAutomation();

	AddPage( &m_cGeneral);
	AddPage( &m_cBurst);
	AddPage( &m_cMls);
	AddPage( &m_cNoise);
	AddPage( &m_cPulse);
	AddPage( &m_cSawtooth);
	AddPage( &m_cSine);
	AddPage( &m_cSquare);
	AddPage( &m_cSweep);
	AddPage( &m_cTones);
	AddPage( &m_cWarble);
	AddPage( &m_cUserDef);

	m_iLastPage = iSelectPage;		// get page we start at to begin wtih

}

CDlgGenerator::~CDlgGenerator()
{
}

void CDlgGenerator::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgGenerator::UseGenerator( CGenerator *pcGen)
{
					// for a generator, set the active page to the type page
	SetActivePage( GetTypePage( pcGen->m_nType));
	m_cGeneral.m_csDescript = pcGen->GetDescription();
	m_cGeneral.m_nType		= FindGenType(pcGen->m_nType);

	pcGen->SetDateStrings( m_cGeneral.m_csDate, m_cGeneral.m_csLastDate);
	{
	const CDWordArray *prate = CMMWave::GetRateArray();
	int i;

		for ( i=0; i<prate->GetSize(); i++)
			if ( pcGen->m_nSampleRate == (int )prate->GetAt(i) )
				{
				m_cGeneral.m_nRate      = i;
				break;
				}
	}

				// mls
	m_cMls.m_dwNumber	=  	pcGen->m_dwMlsCount;
	m_cMls.m_bEmphasis	=	pcGen->m_bMlsEmphasis;
	m_cMls.m_bCorrelate =  pcGen->m_bMlsCorrelate;
				// noise
	m_cNoise.m_fStart	=	pcGen->m_fNoiseStart;
	m_cNoise.m_fEnd		=	pcGen->m_fNoiseEnd;
	m_cNoise.m_bUseAll	=	! pcGen->m_bNoiseFilter;
	m_cNoise.m_bUsePink =	(0 == pcGen->m_nNoiseType);
//		ar >>	w;=	m_nNoiseType;
				// pulse
	m_cPulse.m_fFreq 	=	pcGen->m_fPulseFreq;
	m_cPulse.m_bNegative= 	pcGen->m_bPulseNegative;
	m_cPulse.m_bRepeat  =	pcGen->m_bPulseRepeat;
	m_cPulse.m_fDuration =  pcGen->m_fPulseLength;

				// sawtooth
	m_cSawtooth.m_fFreq	=	pcGen->m_fSawFreq;
				// sine
	m_cSine.m_fFreq 	=	pcGen->m_fSineFreq;
	m_cSine.m_fPhase 	=	pcGen->m_fSinePhase;
				// square
	m_cSquare.m_fFreq	=	pcGen->m_fSquareFreq;
	m_cSquare.m_fDutyCycle =pcGen->m_fSquareDuty;
				// sweep
	m_cSweep.m_fStart	=	pcGen->m_fSweepStart;
	m_cSweep.m_fEnd		=	pcGen->m_fSweepEnd;
	m_cSweep.m_bSmooth	=	pcGen->m_bSweepSmooth;
	m_cSweep.m_nSteps	=	pcGen->m_nSweepSteps;
	m_cSweep.m_bLinear  =	pcGen->m_bSweepLinear;
				// burst
	m_cBurst.m_fEnd =			pcGen->m_fBurstEnd;
	m_cBurst.m_fStart =		pcGen->m_fBurstStart;
	m_cBurst.m_nCycles =		pcGen->m_nBurstCycles;

				// tones
	{
	int i;
		for ( i=0; i<NUMTONES; i++)
			{
			m_cTones.m_fFreq[i] = pcGen->m_fTonesFreq[i];
			m_cTones.m_fAmp[i] = pcGen->m_fTonesAmp[i];
			}
	}
	m_cTones.m_bTone1	=	pcGen->m_bTonesUse[0];
	m_cTones.m_bTone2	=	pcGen->m_bTonesUse[1];
	m_cTones.m_bTone3	=	pcGen->m_bTonesUse[2];
	m_cTones.m_bTone4	=	pcGen->m_bTonesUse[3];
	m_cTones.m_bTone5	=	pcGen->m_bTonesUse[4];

	m_cWarble.m_fOctave	=	pcGen->m_fWarbleOctave;	
	m_cWarble.m_fCenter = 	pcGen->m_fWarbleCenter; 
	m_cWarble.m_fRate	=  	pcGen->m_fWarbleRate;	

	m_cUserDef.m_csUserName = pcGen->m_csUserDefName;

}


void CDlgGenerator::SetGenerator( CGenerator *pcGen)
{
	pcGen->SetDescription( m_cGeneral.m_csDescript);
	if ( m_iLastPage > 0)
	{			// we had a last page, so use it to set the datatype
	GENTYPES gtall[] = { gtBurst, gtMls, gtNoise, gtPulse, gtSawtooth, gtSine, 
			gtSquare, gtSweep, gtTones, gtUserDef, gtWarble};	// the generator pages0types

		pcGen->m_nType = gtall[m_iLastPage-1];
	}
	else
		pcGen->m_nType	=	n_TypeList[m_cGeneral.m_nType];
	pcGen->SetSampleRate( (int )CMMWave::GetRateArray()->GetAt(m_cGeneral.m_nRate));

				// mls      
	pcGen->m_bMlsEmphasis	= m_cMls.m_bEmphasis;
	pcGen->m_dwMlsCount = 	  m_cMls.m_dwNumber;
	pcGen->m_bMlsCorrelate =  m_cMls.m_bCorrelate;
				// noise    
	pcGen->m_fNoiseStart = 	  m_cNoise.m_fStart;
	pcGen->m_fNoiseEnd = 	  m_cNoise.m_fEnd;
	pcGen->m_bNoiseFilter =   ! m_cNoise.m_bUseAll;
	pcGen->m_nNoiseType =	 (m_cNoise.m_bUsePink ? 0 : 1);
				// pulse    
	pcGen->m_fPulseFreq 	= m_cPulse.m_fFreq;
	pcGen->m_bPulseNegative = m_cPulse.m_bNegative;
	pcGen->m_bPulseRepeat 	= m_cPulse.m_bRepeat;
	pcGen->m_fPulseLength 	= m_cPulse.m_fDuration;

				// sawtooth 
	pcGen->m_fSawFreq = 	  m_cSawtooth.m_fFreq;
				// sine     
	pcGen->m_fSineFreq = 	  m_cSine.m_fFreq;
	pcGen->m_fSinePhase = 	  m_cSine.m_fPhase;
				// square   
	pcGen->m_fSquareFreq = 	  m_cSquare.m_fFreq;
	pcGen->m_fSquareDuty = 	  m_cSquare.m_fDutyCycle;
				// sweep    
	pcGen->m_fSweepStart = 	  m_cSweep.m_fStart;
	pcGen->m_fSweepEnd = 	  m_cSweep.m_fEnd;
	pcGen->m_bSweepSmooth =	  m_cSweep.m_bSmooth;
	pcGen->m_nSweepSteps = 	  m_cSweep.m_nSteps;
	pcGen->m_bSweepLinear =	  m_cSweep.m_bLinear;
				// burst
	pcGen->m_fBurstEnd		= m_cBurst.m_fEnd;
	pcGen->m_fBurstStart	= m_cBurst.m_fStart;
	pcGen->m_nBurstCycles	= m_cBurst.m_nCycles;
	
				// tones 
	{
	int i;
		for ( i=0; i<NUMTONES; i++)
			{
			pcGen->m_fTonesFreq[i] = m_cTones.m_fFreq[i];
			pcGen->m_fTonesAmp[i] =   m_cTones.m_fAmp[i];
			}
	}
	pcGen->m_bTonesUse[0] =   m_cTones.m_bTone1;
	pcGen->m_bTonesUse[1] =   m_cTones.m_bTone2;
	pcGen->m_bTonesUse[2] =   m_cTones.m_bTone3;
	pcGen->m_bTonesUse[3] =   m_cTones.m_bTone4;
	pcGen->m_bTonesUse[4] =   m_cTones.m_bTone5;

	pcGen->m_fWarbleCenter = m_cWarble.m_fCenter;
	pcGen->m_fWarbleOctave = m_cWarble.m_fOctave; 	
	pcGen->m_fWarbleRate =	 m_cWarble.m_fRate;

	pcGen->m_csUserDefName = m_cUserDef.m_csUserName;

	pcGen->SetLastEdit();

}




BEGIN_MESSAGE_MAP(CDlgGenerator, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgGenerator)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgGenerator, CPropertySheet)
	//{{AFX_DISPATCH_MAP(CDlgGenerator)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGenerator message handlers

CPropertyPage *CDlgGenerator::GetTypePage(GENTYPES nType)
{
	switch( nType)
		{
		case gtMls :
			return &m_cMls;
		case gtNoise :
			return &m_cNoise;
		case gtPulse :
			return &m_cPulse;
		case gtSawtooth :
			return &m_cSawtooth;
		case gtSine :
			return &m_cSine;
		case gtSquare :
			return &m_cSquare;
		case gtSweep :
			return &m_cSweep;
		case gtTones :
			return &m_cTones;
		case gtWarble :
			return &m_cWarble;
		case gtUserDef :
			return &m_cUserDef;
		case gtBurst :
			return &m_cBurst;
		}
	return 0;

}




BOOL CDlgGenerator::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
NMHDR *pnmhdr = (NMHDR *)lParam;


       if (TCN_SELCHANGE == pnmhdr->code)
       {
		   m_iLastPage =  GetActiveIndex();	// if he switched pages, note it
	   }
           
	
	return CPropertySheet::OnNotify(wParam, lParam, pResult);
}
