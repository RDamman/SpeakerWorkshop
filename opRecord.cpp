// speaker.cpp : implementation of the CDataSetArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include "opcode.h"

//#include "named.h"
#include "folder.h"
#include "generat.h"
#include "dataset.h"

#include "mmwave.h"

#include "OpRecord.h"
#include "OpItem.h"

#include "xform.h"
#include "xformall.h"

#include "audtedoc.h"

#include "dlgMsrPa.h"

#include "utils.h"

#include "math.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// ///////////////////////////////////////////////////////
//				Opcode Record Base Class
// ///////////////////////////////////////////////////////

COpRecord::COpRecord( CNamed *cTarget, CView *cView) : COpCustom( cTarget)
{
CAudtestDoc *pdoc = (CAudtestDoc *)m_cDocument;

	m_bIsStopped = FALSE;

	m_cView = cView;
	m_gtFreqType = fqFull;		// use all data
	SetNameID( IDOP_RECORD);

	if ( pdoc)				// by default use the std recording info
		{
		RECORDINGINFO rec;

			CAudtestApp::GetRecordingInfo( &rec);
			SetRecordInfo( &rec);
		}

	{
	int i;

	for ( i=0; i<noNumResults; i++)
		{
		m_dwResults[i] = 0;
		}
	}
	
}

COpRecord::~COpRecord()
{

}



void COpRecord::SetDataset( int nWhich, DWORD dwID)
{
	m_dwResults[nWhich] = dwID;
}

void COpRecord::SetDataset( int nWhich, CNamed *cWho)
{
	if ( ! cWho)			// set to null
		m_dwResults[nWhich] = 0;
	else
		m_dwResults[nWhich] = cWho->GetID();
}

CNamed *COpRecord::GetDataset( int nWhich)
{
	if ( ! m_dwResults[nWhich])
		return NULL;

CNamed *cbase = (CNamed *)FindTargetObject();

	return cbase->FindByID( m_dwResults[nWhich]);

}

// get the generator to use for recording (may not be the target object)
CNamed *COpRecord::GetGenerator( void)
{
CNamed *cbase = (CNamed *)FindTargetObject();

	if ( cbase && m_dwGenerator)
		return cbase->FindByID( m_dwGenerator);

	return NULL;

}

// this does a record...
int COpRecord::DoRecord( void)
{
CGenerator *ctarg = (CGenerator *)GetGenerator();
RECORDINGINFO rcp;
float fbalance;
int nerr = 0;

	if ( ctarg)
		{

		CAudtestApp::SetIsWorking( TRUE);
		GetRecordInfo( &rcp);
		rcp.m_bIsRecording = TRUE;
		SetRecordInfo( &rcp);

		switch( rcp.m_nOutChannel)
			{
			case chLeft :		// left
				fbalance = 0.0f;
				break;
			case chRight :		// right
				fbalance = 100.0f;
				break;
			case chBoth :		// both
			default:
				fbalance = 50.0f;
				break;
			}

		ctarg->CreateWave( (DWORD )(1000 * rcp.m_fPlayTime) );
		if ( rcp.m_bOutput)		// if there's output at all
			nerr = ctarg->PlayWave(m_cView, rcp.m_fDataAmplitude, fbalance);
		if ( ! nerr)
			nerr = ctarg->RecordWave(m_cView, (DWORD )(1000 * rcp.m_fRecordTime));
		}
	return nerr;

}


// this does a record...
int COpRecord::DoPlay( void)
{
CGenerator *ctarg = (CGenerator *)GetGenerator();
RECORDINGINFO rcp;
float fbalance;

	if ( ctarg)
		{
		CAudtestApp::SetIsWorking( TRUE);

		GetRecordInfo( &rcp);

		switch( rcp.m_nOutChannel)
			{
			case chLeft :		// left
				fbalance = 0.0f;
				break;
			case chRight :		// right
				fbalance = 100.0f;
				break;
			case chBoth :		// both
			default:
				fbalance = 50.0f;
				break;
			}

		ctarg->CreateWave( (DWORD )(1000 * rcp.m_fPlayTime) );
		ctarg->PlayWave(m_cView, rcp.m_fDataAmplitude, fbalance, rcp.m_bLoopPlay ? 12000 : 1);

		rcp.m_bIsRecording = FALSE;
		SetRecordInfo( &rcp);
		}
	return 0;

}

// this does a record...
int COpRecord::DoExe( bool)
{
	return DoRecord();
}

void	COpRecord::StopSound( void)				// for when looping, or long records...
{
CGenerator *pcgen = (CGenerator *)GetGenerator();
RECORDINGINFO rcd;

	if ( ! pcgen)
		return;

	GetRecordInfo( &rcd);
									// turn off playing and recording
	rcd.m_bIsRecording = FALSE;
	rcd.m_bLoopRecord = FALSE;		// don't loop if we were...
	rcd.m_bLoopPlay = FALSE;		// don't loop if we were...
	SetRecordInfo( &rcd);

	pcgen->StopPlay( );
	pcgen->StopRecord( );

	m_bIsStopped = TRUE;			// stop doing things... if looping

	CAudtestApp::SetIsWorking( FALSE);

}



int COpRecord::DoStdFinish(void )
{
CGenerator *pcgen = (CGenerator *)GetGenerator();
CAudtestDoc* pDoc = (CAudtestDoc *)m_cDocument;
RECORDINGINFO rcd;
CDataSet *pcinput = NULL;
CDataSet *pcrefer = NULL;
int nout;

	GetRecordInfo( & rcd);

	rcd.m_bIsRecording = FALSE;
	SetRecordInfo( & rcd);				// turn it off

	pcgen->StopPlay( );			// turn off any sound output just in case...
	pcgen->StopRecord( );

	CreateProgressBar( IDS_PROGRECORD, 10 + 
									(( gtMls == pcgen->GetStyle()) ? 20 : 0) +
									(( rcd.m_nDataType != rtTime) ? 30 : 0) +
									(( rcd.m_nDataType == rtImpedance) ? 10 : 0) );



	if ( ! HasDataset( noDataOut))
		SetDataset( noDataOut, pcgen->FindByName( pcgen->GetName() + ".Output", FALSE));

	StepProgressBar();

			// find or build the input dataset pointers
	if ( ! HasDataset( noDataIn) )
		{
		COpFindOrCreate *ccr;
		CNamed *pbase = pcgen;			// which parent - always generator
		CDataSet *pcleft = NULL;
		CDataSet *pcright = NULL;

			ccr = new COpFindOrCreate(pbase,  pbase->GetName() + ".in.l", ntDataSet);
			if ( ! PrivateQueue( ccr) )
				pcleft = (CDataSet *)ccr->GetFound();

			ccr = new COpFindOrCreate(pbase,  pbase->GetName() + ".in.r", ntDataSet);
			if ( ! PrivateQueue( ccr) )
				pcright = (CDataSet *)ccr->GetFound();

			switch( rcd.m_nDataChannel)
				{
				case chLeft :		// left
					SetDataset( noDataIn, pcleft);
					break;
				case chRight :		// right
					SetDataset( noDataIn, pcright);
					break;
				default :
					SetDataset( noDataIn, (CDataSet * )NULL);
					ASSERT( 0);
					break;
				}

			switch( rcd.m_nCalibChannel)
				{
				case chLeft :		// left
					SetDataset( noReferIn, pcleft);
					break;
				case chRight :		// right
					SetDataset( noReferIn, pcright);
					break;
				case chNone :		// none
					SetDataset( noReferIn, (CDataSet * )NULL);
					break;
				default :
					SetDataset( noReferIn, (CDataSet * )NULL);
					ASSERT( 0);
					break;
				}

		}

	pcinput = (CDataSet *)GetDataset(noDataIn);
	pcrefer = (CDataSet *)GetDataset(noReferIn);

			// this converts the input wave data to datasets
			// it starts at the first non-zero input data (for the stereo pair)
			// and hence both datasets begin at the same spot in time

	if ( chLeft == rcd.m_nDataChannel )		// right left orientation normal
		pcgen->MakeDatasets( TRUE, pcinput, pcrefer, FALSE);
	else
		pcgen->MakeDatasets( TRUE, pcrefer, pcinput, FALSE);

	StepProgressBar();
						// now depending on type, we need to build additional stuff

	if ( (gtMls == pcgen->GetStyle()) && pcgen->GetMlsCorrelate())		// it's mls and is correlated
		{
		CXformCorrelate *cop;				// do a hadamard correlation on the datasets
		TESTMSR tm;

			CAudtestApp::GetMeasures( &tm);			// we want the measurement guys

			cop = new CXformCorrelate( pcinput);
			cop->SetCorrelateSize( pcgen->GetMlsSize() );
			cop->SetRepeatCount( tm.nNumberSamples);
//			rcd.m_bLoopRecord ? cop->DoExe() : PrivateQueue( cop);
			cop->DoExe( false);
//			if ( rcd.m_bLoopRecord)
				delete cop;

			StepProgressBar();

			if ( pcrefer)
				{
				cop = new CXformCorrelate( pcrefer);
				cop->SetCorrelateSize( pcgen->GetMlsSize() );
				cop->SetRepeatCount( tm.nNumberSamples);
//				rcd.m_bLoopRecord ? cop->DoExe() : PrivateQueue( cop);	// we don't need to queue correlation
				cop->DoExe( false);
//				if ( rcd.m_bLoopRecord)
					delete cop;
				}

			StepProgressBar();
		}

	if ( rcd.m_nDataType != rtTime)			// not just time
		{								// always build the ffts
		int nstart = 0;
		int nend = 0;					// range variables

			if ( gtMls == pcgen->GetStyle() )		// it's mls
				{
				TESTMARK tm;
				tm = *CAudtestApp::GetMarker( 0);		// time markers

				if ( ! pcrefer)				// there's no reference, must be microphonic
					{
					CNamed *puse = pDoc->GetAmpResponse();
					if ( puse)
						pcrefer = (CDataSet *)puse;	// pcrefer is null if puse is null
					}

				switch( GetFreqType())
					{
					case fqFull :				// entire range
						nstart = nend = 0;
						break;
					case fqGateStart :				// acoustic, entire
						nstart = pcinput->FreqToIndex(tm.fStart);
						nend   = pcinput->GetCount()-1;			// last index...
						break;
					case fqGateAll :				// acoustic, anechoic
						nstart = pcinput->FreqToIndex(tm.fStart);
						nend   = pcinput->FreqToIndex(tm.fEnd);
						break;
					default :				// entire range
						ASSERT(0);			// shouldn't be here!
						nstart = nend = 0;
						break;
					}
				}
						// note that queueanddo keeps the pointer for its own
						// but it is guaranteed valid for a while....
			{
			CXformFft *cxf;
			cxf = new CXformFft( pcinput);
			cxf->SetRange( nstart, nend);
			nout = (rcd.m_bLoopRecord ? cxf->DoExe() : PrivateQueue( cxf) );	// no undo if looping
			if ( ! nout)					// worked ok?
				pcinput = (CDataSet *)cxf->GetDestination();		// update to the fft
			if ( rcd.m_bLoopRecord)
				delete cxf;
			StepProgressBar();
			SetDataset(noFftData, pcinput);
			}

			if ( pcrefer)
				{
				CXformFft *cxf;
				cxf = new CXformFft( pcrefer);
				cxf->SetRange( 0, nend - nstart);	// this lets us lag the input
//				cxf->SetRange( nstart, nend);		//			to agree with the reference which is autotimed
				nout = (rcd.m_bLoopRecord ? cxf->DoExe() : PrivateQueue( cxf) );	// no undo if looping
				if ( ! nout)					// worked ok?
					pcrefer = (CDataSet *)cxf->GetDestination();
				if ( rcd.m_bLoopRecord)
					delete cxf;
				StepProgressBar();
				SetDataset(noFftRefer, pcrefer);
				}

						// now do the delay if needed
			if ( pcinput && pcrefer && CAudtestApp::GetRightShift())
			{
				pcinput = (CDataSet *)GetDataset( noFftRefer);	// Data *= (cal left/cal right)
				if ( pcinput)
				{
					CXformDelay *cf = new CXformDelay( pcinput);	// input chan
					cf->m_fTime = CAudtestApp::GetRightShift() / 1000.0f;
							// do a multiply if channels reversed
					cf->DoExe( false);		// don't queue the delay
					delete cf;
				}
			}
						// if there is calibration data, use it
						//		combine divide the right one ONLY
			if ( pcinput && pcrefer)
				{
				TESTCAL tcal;

					tcal = *pDoc->GetCalib();
					if ( tcal.dwLeftRight)		// we have a cal dataset
						{
						CNamed *pccal = pDoc->GetByID( tcal.dwLeftRight);
						if ( pccal)
							{
							pcinput = (CDataSet *)GetDataset( noFftRefer);	// Data *= (cal left/cal right)
							if ( pcinput)
							{
								CXformCombine *cf = new CXformCombine( pcinput, pccal);	// input chan
										// do a multiply if channels reversed
								cf->SetOperation((chRight == rcd.m_nCalibChannel) ? 2 : 3);		// multiply to convert right->left type
								cf->DoExe( false);		// don't queue the divide by
								delete cf;
#if 0
								rcd.m_bLoopRecord ? cf->DoExe() : PrivateQueue( cf);	// no undo if looping
								if ( rcd.m_bLoopRecord)
									delete cf;
#endif
							}
							StepProgressBar();
							}
						}
				}

		}

	if ( rcd.m_nDataType == rtImpedance)			// impedance
		{
			pcinput = (CDataSet *)GetDataset( noFftData);
			pcrefer = (CDataSet *)GetDataset( noFftRefer);
			if ( pcinput && pcrefer)
			{
				CXformImpedance *cxi = new CXformImpedance( pcinput, pcrefer);
					{
					TESTMSR tm;

					CAudtestApp::GetMeasures( &tm);			// we want the measurement guys
					cxi->SetParms( &tm);
					}
					nout = (rcd.m_bLoopRecord ? cxi->DoExe() : PrivateQueue( cxi) );	// no undo if looping
					if ( ! nout)					// worked ok?
						SetDataset(noImpedance, cxi->GetDestination());
					if ( rcd.m_bLoopRecord)
						delete cxi;
			}
			StepProgressBar();
		}

	{
	int i;

		for ( i=0; i<noNumResults; i++)
			{
			CNamed *cdata = GetDataset(i);
			if ( cdata)
				cdata->UpdateViews();
			}
	}

	CloseProgressBar();

	return 0;

}



// ///////////////////////////////////////////////////////
//				Opcode Record -- Standard Recording Class
// ///////////////////////////////////////////////////////

COpRecordStd::COpRecordStd( CNamed *cTarget, CView *cView) : COpRecord( cTarget, cView)
{
	SetGenerator( ((CNamed *)FindTargetObject())->GetID() );
}

COpRecordStd::~COpRecordStd()
{
	// add a line so we can set a breakpoint here
#ifdef _DEBUG
//	int i = 0;
#endif
}


int COpRecordStd::ProcessInput( void)
{
int nout;

	nout = DoStdFinish( );

	if ( ! nout)			// worked ok
		{
		RECORDINGINFO rcp;

			GetRecordInfo( &rcp);

			if ( (!IsStopped()) && rcp.m_bLoopRecord)		// do it again...
				{
				if ( m_cView)
					m_cView->GetParent()->UpdateWindow();
				DoRecord();
				}
		}

CNamed *pparent = (CNamed *)FindTargetObject();

	if ( pparent)
		pparent->UpdateViews();
   
   return nout;
}


// ///////////////////////////////////////////////////////
//				Opcode Play -- Standard Play Class
// ///////////////////////////////////////////////////////

COpPlayStd::COpPlayStd( CNamed *cTarget, CView *cView) : COpRecord( cTarget, cView)
{
	SetGenerator( ((CNamed *)FindTargetObject())->GetID() );
}

COpPlayStd::~COpPlayStd()
{
}


// -----------------------------------------------------------------------------
// this does a record...
// -----------------------------------------------------------------------------
int COpPlayStd::DoExe( bool)
{
	return DoPlay();
}

// -----------------------------------------------------------------------------
// actually nothing to do here..., just say ok
// -----------------------------------------------------------------------------
int COpPlayStd::ProcessInput( void)
{
	return 0;		// never fails
}

// /////////////////////////////////////////////////////////////////
//				Opcode Record Volume -- Align volume controls
// /////////////////////////////////////////////////////////////////

COpRecordVol::COpRecordVol( CNamed *cTarget, CView *cView) : COpRecordStd( cTarget, cView)
{
RECORDINGINFO rcp;
TESTMSR tm;
CGenerator *pcgen;

	pcgen = (CGenerator *)((CAudtestDoc *)GetDocument() )->GetDefaultGenerator();
	SetGenerator( pcgen->GetID());

	CAudtestApp::GetMeasures( &tm);			// we want the measurement guys

	GetRecordInfo( &rcp);
	rcp.m_bLoopRecord = FALSE;		// type of data to generate (freq/time/impedance)
	rcp.m_bLoopPlay = FALSE;		// type of data to generate (freq/time/impedance)
	rcp.m_nDataType = rtTime;	// type of data to generate (freq/time/impedance)
					// --- test specific
	rcp.m_fDataAmplitude = tm.fPlayVolume;	// amplitude of wave
	if ( tm.bReverseChannel)
		{
		rcp.m_nDataChannel = chLeft;		// channel to use for data
		rcp.m_nCalibChannel = chRight;	// calibration channel
		}
	else
		{
		rcp.m_nDataChannel = chRight;		// channel to use for data
		rcp.m_nCalibChannel = chLeft;	// calibration channel
		}
	rcp.m_nOutChannel = chBoth;		// both output channels are active
	rcp.m_fInLeftVolume = 100.0f;
	rcp.m_fInRightVolume = 100.0f;		// left and right input volume settings
	rcp.m_fPlayTime = (float )(.001 + (double)tm.nSampleSize / tm.nSampleRate);
	rcp.m_fRecordTime = (float )(.2 + rcp.m_fPlayTime);
	SetRecordInfo( &rcp);

	SetMaxLoop( 0);
	SetCurrentLoop( 0);

	pcgen->SetMls( tm.nSampleSize, tm.bEmphasis, FALSE);	// sample size and emphasis - NO correlation
	pcgen->SetSampleRate( tm.nSampleRate);
		// don't think we need to do this and it causes recalc of gen each time

}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
COpRecordVol::~COpRecordVol()
{
}

// -----------------------------------------------------------------------------
// the description is of the form:
//			Impedance in Free Air of Mid85 size 2048 at 22050/s.
// -----------------------------------------------------------------------------
void COpRecordVol::Describe( UINT idDesc, CNamed *pDest, CDataSet *pData)
{
CString csdesc;
CString csend;
CGenerator *pcgen;
UINT id = idDesc;

	pcgen = (CGenerator *)((CAudtestDoc *)GetDocument() )->GetDefaultGenerator();

	if ( ! id)
		switch ( pData->GetUOM())
			{
			case uomFreq :
				id = IDS_MSR_FREQ;
				break;
			case uomTime :
				id = IDS_MSR_TIME;
				break;
			case uomOhms :
				id = IDS_MSR_IMP;
				break;
			default:
				id = IDS_MSR_RESPONSE;
				break;
			}
	csdesc.LoadString( id);						// get the prefix
	csend.Format( IDS_MSR_FORMAT, 
		csdesc, pDest->GetName(), pcgen->GetMlsSize(), pcgen->GetSampleRate());	// %s %s size %d at %d/s
	pData->SetDescription( csend);
}



// ///////////////////////////////////////////////////////
//				Opcode Record -- Measure Base Function
// ///////////////////////////////////////////////////////

COpMeasure::COpMeasure( CNamed *cTarget, CView *cView) : COpRecordStd( cTarget, cView)
{
RECORDINGINFO rcp;
TESTMSR tm;
CGenerator *pcgen;

	pcgen = (CGenerator *)((CAudtestDoc *)GetDocument() )->GetDefaultGenerator();
	SetGenerator( pcgen->GetID());

	CAudtestApp::GetMeasures( &tm);			// we want the measurement guys

	GetRecordInfo( &rcp);
	rcp.m_bLoopRecord = FALSE;		// type of data to generate (freq/time/impedance)
	rcp.m_bLoopPlay = FALSE;		// type of data to generate (freq/time/impedance)
	rcp.m_nDataType = rtFrequency;	// type of data to generate (freq/time/impedance)
					// --- test specific
	rcp.m_fDataAmplitude = tm.fPlayVolume;	// amplitude of wave
	if ( tm.bReverseChannel)
		{
		rcp.m_nDataChannel = chLeft;		// channel to use for data
		rcp.m_nCalibChannel = chRight;	// calibration channel
		}
	else
		{
		rcp.m_nDataChannel = chRight;		// channel to use for data
		rcp.m_nCalibChannel = chLeft;	// calibration channel
		}
	rcp.m_nOutChannel = chBoth;		// both output channels are active
	rcp.m_fInLeftVolume = 100.0f;
	rcp.m_fInRightVolume = 100.0f;		// left and right input volume settings
//	rcp.m_fPlayTime = (float )(.001 + (double)((2*tm.nNumberSamples-1) * tm.nSampleSize) / tm.nSampleRate);
	{
	int isamples = tm.nNumberSamples;
		if ( isamples > 1)
			isamples++;			// act like we have one more so we can skip the first
		rcp.m_fPlayTime = (float )(.001 + (double)(isamples * tm.nSampleSize) / tm.nSampleRate);
	}
	rcp.m_fRecordTime = (float )(.2 + rcp.m_fPlayTime);
	SetRecordInfo( &rcp);

	SetMaxLoop( 0);
	SetCurrentLoop( 0);

	pcgen->SetMls( tm.nSampleSize, tm.bEmphasis, TRUE);	// frequency and phase
	pcgen->SetSampleRate( tm.nSampleRate);

}

COpMeasure::~COpMeasure()
{
}

// -----------------------------------------------------------------------------
// the description is of the form:
//			Impedance in Free Air of Mid85 size 2048 at 22050/s.
// -----------------------------------------------------------------------------
void COpMeasure::Describe( UINT idDesc, CNamed *pDest, CDataSet *pData)
{
CString csdesc;
CString csend;
CGenerator *pcgen;
UINT id = idDesc;

	pcgen = (CGenerator *)((CAudtestDoc *)GetDocument() )->GetDefaultGenerator();

	if ( ! id)
		switch ( pData->GetUOM())
			{
			case uomFreq :
				id = IDS_MSR_FREQ;
				break;
			case uomTime :
				id = IDS_MSR_TIME;
				break;
			case uomOhms :
				id = IDS_MSR_IMP;
				break;
			default:
				id = IDS_MSR_RESPONSE;
				break;
			}
	csdesc.LoadString( id);						// get the prefix
	csend.Format( IDS_MSR_FORMAT, 
		csdesc, pDest->GetName(), pcgen->GetMlsSize(), pcgen->GetSampleRate());	// %s %s size %d at %d/s
	pData->SetDescription( csend);
}


// -----------------------------------------------------------------------------
// the description is of the form:
//			Impedance in Free Air of Mid85 size 2048 at 22050/s.
// -----------------------------------------------------------------------------
void COpMeasure::DescribeGating( CNamed *pData)
{
	switch( GetFreqType())
	{
	case fqFull :
		break;
	case fqGateStart :
		DescStartGate( pData);
		break;
	case fqGateAll :
		DescGating( pData);
		break;
	default :
		ASSERT(0);
		break;
	}

}

// -----------------------------------------------------------------------------
// the description is of the form:
//			Impedance in Free Air of Mid85 size 2048 at 22050/s.
// -----------------------------------------------------------------------------
void COpMeasure::DescGating( CNamed *pData)
{
CString csdesc;
CString csgate;
float fstart, fend;

	csdesc = pData->GetDescription();

	{
	TESTMARK tm;
		tm = *CAudtestApp::GetMarker( 0);		// time markers
		fstart = tm.fStart;
		fend = tm.fEnd;
	}

	csgate.Format( IDS_DESCGATE, fstart, fend);
	csdesc += csgate;

	pData->SetDescription( csdesc);
}

// -----------------------------------------------------------------------------
// the description is of the form:
//			Impedance in Free Air of Mid85 size 2048 at 22050/s.
// -----------------------------------------------------------------------------
void COpMeasure::DescStartGate( CNamed *pData)
{
CString csdesc;
CString csgate;
float fstart;

	csdesc = pData->GetDescription();

	{
	TESTMARK tm;
		tm = *CAudtestApp::GetMarker( 0);		// time markers
		fstart = tm.fStart;
	}

	csgate.Format( IDS_DESCSTARTGATE, fstart);
	csdesc += csgate;

	pData->SetDescription( csdesc);
}

// -----------------------------------------------------------------------------
//		CopyOutput
//			take the output dataset and copy it to a new named dataset
// -----------------------------------------------------------------------------
int	COpMeasure::CopyOutput( UINT uIDName, int nDataset)
{
CNamed *pparent = (CNamed *)FindTargetObject();
CDataSet *pcout, *pcin;
COpFindOrCreate *ccr;
CString cs;

	cs.LoadString( uIDName);
	cs = pparent->GetName() + "." + cs;

	ccr = new COpFindOrCreate(pparent, cs, ntDataSet);
	if ( ! PrivateQueue( ccr) )
		{
		COpCode *cop;

			pcout = (CDataSet *)ccr->GetFound();	// our correctly named guy
			SetDataset( noResultData, pcout);		// first result

			pcin = (CDataSet *)GetDataset( nDataset);		// impedance

			pcin = (CDataSet *)pcin->Duplicate();		// make a copy of myself
			pcin->SetName( cs);
			cop = new COpChange( pcout, pcin);
			PrivateQueue( cop);

		}

   return 0;
}

// -----------------------------------------------------------------------------
//		TrailOutput
//			take the output dataset and copy it to a new named dataset
//			leaving trails behind
// -----------------------------------------------------------------------------
int	COpMeasure::TrailOutput( UINT uIDName, int nDataset)
{

	if ( ! CAudtestApp::GetTrails())					// no trails ??
		return CopyOutput( uIDName, nDataset);			// just do a copy output


CNamed *pparent = (CNamed *)FindTargetObject();
CDataSet *pcout, *pcin;
CString cs;
CNamed *cfind;
int irslt;

	cs.LoadString( uIDName);
	cs = pparent->GetName() + "." + cs;

	cfind = pparent->FindByName( cs, FALSE);		// look only in his tree
	if ( ! cfind)			// didn't find one
	{
		irslt = CopyOutput( uIDName, nDataset);		// just do a copyoutput
		if ( irslt)
			return irslt;							// failure, don't build the chart

		cfind = pparent->FindByName( cs, FALSE);		// look only in his tree
		if ( cfind)			// now we have it
		{
		CNamed *pchart;
		CString csname;
		CDWordArray dwids;

			dwids.Add( cfind->GetID());
			csname.Format(_T("%s.Chart"), cfind->GetName());
			pchart = m_cDocument->BuildBaseChart( cfind, csname, dwids);
			if ( pchart)
				pchart->SetTemporary( true);
		}

		return irslt;
	}

	{
	COpCode *cop;

		pcout = (CDataSet *)cfind;
		SetDataset( noResultData, pcout);		// first result

		pcin = (CDataSet *)GetDataset( nDataset);		// impedance

		pcin = (CDataSet *)pcin->Duplicate();		// make a copy of myself
		cop = new COpNameTrails( cfind, pcin);			// we did find it, make the trails
		PrivateQueue( cop);									// queue it up
	}

   return 0;
}



// ///////////////////////////////////////////////////////
//				Opcode Record -- Measure Transfer Function
// ///////////////////////////////////////////////////////

COpMsrTransfer::COpMsrTransfer( CNamed *cTarget, CView *cView) : COpMeasure( cTarget, cView)
{
RECORDINGINFO rcp;

	SetNameID( IDOP_MSRTRANSFER);
	GetRecordInfo( &rcp);
	rcp.m_nDataType = rtFrequency;			// Frequency
	SetFreqType( fqFull);				// use all data
	SetRecordInfo( &rcp);

}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
COpMsrTransfer::~COpMsrTransfer()
{
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int COpMsrTransfer::ProcessInput( void)
{
int nout;
CDataSet *pcout, *pcright;

	nout = DoStdFinish( );

	if ( ! nout)			// worked ok
		{
		if ( ! CopyOutput( IDS_TRANSFER, noFftData) )
			{
			pcout = (CDataSet *)GetDataset( noResultData);		// left fft
			pcright = (CDataSet *)GetDataset( noFftRefer);		// right fft
			CXformCombine *cop = new CXformCombine( pcout, pcright);
			cop->SetOperation( 3);			// divide
			PrivateQueue( cop);
			}
		else
			nout = 1;
		}

   return nout;
}

// ///////////////////////////////////////////////////////
//				Opcode Record -- Measure Impedance
// ///////////////////////////////////////////////////////

COpMsrImpedance::COpMsrImpedance( CNamed *cTarget, CView *cView) : COpMeasure( cTarget, cView)
{
RECORDINGINFO rcp;

	SetNameID( IDOP_MSRIMPEDANCE);
	GetRecordInfo( &rcp);
	rcp.m_nDataType = rtImpedance;			// impedance
	SetRecordInfo( &rcp);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
COpMsrImpedance::~COpMsrImpedance()
{
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int COpMsrImpedance::ProcessInput( void)
{
int nout = DoStdFinish();

	if ( ! nout)
		{
		TrailOutput( IDS_IMPEDANCE, noImpedance);
		CNamed *pdest = (CNamed *)FindTargetObject();
		if ( pdest)
			Describe( IDS_MSR_IMP, pdest, (CDataSet *) GetDataset( noResultData));
		}

	return nout;

}


// ///////////////////////////////////////////////////////
//				Opcode Record -- Measure Impedance
// ///////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
static float msr_Average( CDataSet *pcData)
{
double dsumx;
			// now smooth the data
int j,nstart, nend;
float fmin, fmax;
float fx, fy;

				// get the geometric mean
//	fmin = (float )sqrt( pcData->Minimum( dataFreq) * pcData->Maximum( dataFreq) );
				// use 1K for 44k data
	fmin = (float )( pcData->Maximum( dataFreq) / 22);
				// use +- 1/2 octave
	fmax = fmin * 2.0f;
	fmin = fmin / 2.0f;

	nstart = pcData->FreqToIndex( fmin);
	nend = pcData->FreqToIndex( fmax);

	dsumx = 0;
	for ( j=nstart; j<=nend; j++)
		{
		fmin = pcData->DataAt( dataFreq, j);		// convert to frequency
		pcData->GetRectangularAt( fmin, &fx, &fy);
		dsumx += fx;		// use the real part only
		}
	dsumx /= (1 + nend - nstart);

	return (float ) fabs( dsumx);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
static float msr_Capacitor( CDataSet *pcData, float fResist)
{
double dsumx;
			// now smooth the data
int j,nstart, nend;
float fmin, fmax;
float fx, fy;

				// get the geometric mean
//	fmin = (float )sqrt( pcData->Minimum( dataFreq) * pcData->Maximum( dataFreq) );
				// use max of 19K for 44k data
	fmax = (float )( 0.9 * pcData->Maximum( dataFreq));
				// use +- 1/2 octave
	fmin = fmax / 2;	// get one octave of data

	nstart = pcData->FreqToIndex( fmin);
	nend = pcData->FreqToIndex( fmax);

	dsumx = 0;
	for ( j=nstart; j<=nend; j++)
		{
		fmin = pcData->DataAt( dataFreq, j);		// convert to frequency
		pcData->GetRectangularAt( fmin, &fx, &fy);
		dsumx += 1/(2 * ONEPI * fy * fmin);			// use the cap estimate only
		}
	dsumx /= (1 + nend - nstart);

	return (float ) fabs( dsumx);
}

// -----------------------------------------------------------------------
// setup for calibrating the impedance jig - series and divider resistance
// -----------------------------------------------------------------------
COpMsrCalJig1::COpMsrCalJig1( CNamed *cTarget, CView *cView) : COpMeasure( cTarget, cView)
{
//  CGenerator *pcgen = (CGenerator *)cTarget;		// it's a signal...

//	pcgen->SetSampleRate( CMMWave::GetMaxRate());
//	pcgen->SetMls( 0x4000, FALSE, TRUE);

RECORDINGINFO rcp;

	SetNameID( IDOP_MSRIMPEDANCE);
	GetRecordInfo( &rcp);
	rcp.m_nDataType = rtImpedance;			// impedance
	SetRecordInfo( &rcp);

					// set the series resistance to 0 to avoid double counting
TESTMSR deftest;

	CAudtestApp::GetMeasures( &deftest);
	deftest.fSeriesRes = 0.0f;
	CAudtestApp::SetMeasures( &deftest);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
COpMsrCalJig1::~COpMsrCalJig1()
{
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int COpMsrCalJig1::ProcessInput( void)
{
int nout = DoStdFinish();

	if ( ! nout)
		{
		if ( ! CopyOutput( IDS_IMPEDANCE, noImpedance))
			{
			float favg;
			TESTMSR deftest;
			CDataSet *pcout;

				pcout = (CDataSet *)GetDataset( noResultData);		// left fft
				favg = msr_Average( pcout);
				CAudtestApp::GetMeasures( &deftest);
				deftest.fSeriesRes = favg;
				CAudtestApp::SetMeasures( &deftest);
			}
		else
			nout = 1;
		}

   return nout;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
COpMsrBrdJig::COpMsrBrdJig( CNamed *cTarget, CView *cView) : COpMeasure( cTarget, cView)
{
RECORDINGINFO rcp;

	SetNameID( IDOP_MSRIMPEDANCE);
	GetRecordInfo( &rcp);
	rcp.m_nDataType = rtImpedance;			// impedance
	SetRecordInfo( &rcp);

					// set the series resistance to 0 to avoid double counting

// CGenerator *pcgen = (CGenerator *)cTarget;		// it's a signal...

//	pcgen->SetSampleRate( CMMWave::GetMaxRate());
//	pcgen->SetMls( 0x4000, FALSE, TRUE);


TESTMSR deftest;

	CAudtestApp::GetMeasures( &deftest);
	deftest.fInputRes = 1000000.0f;
	deftest.fInputCap = 0.0f;
	CAudtestApp::SetMeasures( &deftest);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
COpMsrBrdJig::~COpMsrBrdJig()
{
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int COpMsrBrdJig::ProcessInput( void)
{
int nout = DoStdFinish();

	if ( ! nout)
		{
		if ( ! CopyOutput( IDS_IMPEDANCE, noImpedance))
			{
			float favg;
			TESTMSR deftest;
			CDataSet *pcout;

				pcout = (CDataSet *)GetDataset( noResultData);		// left fft
				favg = msr_Average( pcout);
				CAudtestApp::GetMeasures( &deftest);
				deftest.fInputRes = msr_Average( pcout);
				deftest.fInputCap = msr_Capacitor( pcout, deftest.fInputRes);
				CAudtestApp::SetMeasures( &deftest);
			}
		else
			nout = 1;
		}

   return nout;
}


// ///////////////////////////////////////////////////////
//				Opcode Record -- Measure Impedance
// ///////////////////////////////////////////////////////

// ---------------------------------------------------------------
// setup for calibrating the impedance jig - input resistance
// ---------------------------------------------------------------
COpMsrCalJig2::COpMsrCalJig2( CNamed *cTarget, CView *cView) : COpMeasure( cTarget, cView)
{
// CGenerator *pcgen = (CGenerator *)cTarget;		// it's a signal...

//	pcgen->SetSampleRate( CMMWave::GetMaxRate());
//	pcgen->SetMls( 0x4000, FALSE, TRUE);

RECORDINGINFO rcp;

	SetNameID( IDOP_MSRIMPEDANCE);
	GetRecordInfo( &rcp);
	rcp.m_nDataType = rtImpedance;			// impedance
	SetRecordInfo( &rcp);
TESTMSR deftest;

	CAudtestApp::GetMeasures( &deftest);
	deftest.fInputRes = 1000000.0f;
	deftest.fInputCap = 0.0f;
	CAudtestApp::SetMeasures( &deftest);
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
COpMsrCalJig2::~COpMsrCalJig2()
{
}


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
int COpMsrCalJig2::ProcessInput( void)
{
int nout = DoStdFinish();

	if ( ! nout)
		{
		if ( ! CopyOutput( IDS_IMPEDANCE, noImpedance))
			{
			float favg;
			TESTMSR deftest;
			CDataSet *pcout;

				pcout = (CDataSet *)GetDataset( noResultData);	// left fft
				favg = msr_Average( pcout);				// here's what program says...
				CAudtestApp::GetMeasures( &deftest);
				deftest.fInputRes = 10000.0f;	// TBD!!!!
				deftest.fInputCap = 0.0f;
				CAudtestApp::SetMeasures( &deftest);

			}
		else
			nout = 1;
		}

   return nout;

}
// ///////////////////////////////////////////////////////
//				Opcode Record -- Measure Passive
// ///////////////////////////////////////////////////////

COpMsrPassive::COpMsrPassive( CNamed *cTarget, CView *cView) : COpMeasure( cTarget, cView)
{
RECORDINGINFO rcp;

	SetNameID( IDOP_MSRPASSIVE);
	GetRecordInfo( &rcp);
	rcp.m_nDataType = rtImpedance;			// Passive
	SetRecordInfo( &rcp);
}

COpMsrPassive::~COpMsrPassive()
{
}


// this determines the type of the input dataset
// Returns: it puts the values of the object into dReal:dImag
//			it returns the datatype
static int calc_P( CDataSet *cData, int nMin, int nMax, double *dReal, double *dImag)
{
double rvalue, dvalue, dtotal;
double dtemp;
int i, ncount;
int ntype;

	ncount = 1 + nMax - nMin;

	dvalue = 0;				// get the average phase
	for ( i=nMin; i<nMax; i++)
		dvalue += cData->DataAt(dataPhase, i);
	dvalue /= ncount;

	if ( dvalue > 30)
		ntype = 1;				// inductor
	else
		if ( dvalue < -30)		// sb capactor
			ntype = 0;
	else
		ntype = 2;			// sb resistor

	dvalue = 0;
	rvalue = 0;				// series resistance for inductors
	dtotal = 0;
				// weight this by the distance from the center
	for ( i=nMin; i<nMax; i++)
		{
		float ffreq = cData->DataAt( dataFreq, i);
		float x,y;
		cData->GetRectangularAt( ffreq, &x, &y);
		if ( i > (nMax+nMin)/2)
			{
			dtemp = (nMax - i);
			}
		else
			dtemp = i;
		dtemp /= ncount;		// reduce to near 1
		if ( ntype == 0)
			dvalue += dtemp * (-1 / (2 * ONEPI * y * ffreq));
		else
			dvalue += dtemp * (y / (2 * ONEPI * ffreq));
		rvalue += dtemp * x;
				// now weight it
		dtotal += dtemp;
		}

	dvalue /= dtotal;
	rvalue /= dtotal;

	*dReal = rvalue;
	*dImag = dvalue;

	return ntype;			// what kind was it?
}

// here's where we calculate the passive component
static void calc_Passive( CDlgMsrPassive * pDlg, CDataSet *cData)
{
			// first, is it resistor, capacitor, or inductor???
int ntype;
double dvalue;
double rvalue;
double dold, rold;
int nmin, nmax;
float frefer;
int i, j;
float ffreq;
float fval;
float fminbound, fmaxbound;
float fbase;

	if ( ! pDlg)
		return;

	{
	TESTMSR tmr;

		CAudtestApp::GetMeasures( &tmr);
		frefer = tmr.fResistor;				// the reference resistor value

	}

	fmaxbound = 0.25f * cData->Maximum( dataFreq);
	fminbound = 0.04f * fmaxbound;				// get min max frequencies M/4, M/100
	nmin = cData->FreqToIndex( fminbound);
	nmax = cData->FreqToIndex( fmaxbound);

	for ( j=0, i=nmin; i < nmax; i++)
	{
		fval = cData->DataAt( dataAmp, i) / frefer;		// get the amplitude of the impedance
		if ( (0.9 < fval) && (fval < 1.1))			// within 10% of reference
		{
			if ( 10 < ++j)
				break;
		}
		else j = 0;
	}
	fbase = cData->DataAt( dataFreq, i);		// freq at which we hit the reference

	{		// start around 1KHz to find the datatype
	nmin = cData->FreqToIndex( 950.0f);
	nmax = cData->FreqToIndex( 1050.0f);

	ntype = calc_P( cData, nmin, nmax, &rvalue, &dvalue);
	}

	switch( ntype)
	{
	case 2 :	// resistor
		nmin = cData->FreqToIndex( 400.0f);
		nmax = cData->FreqToIndex( 800.0f);		// go from 400 to 800
		ntype = calc_P( cData, nmin, nmax, &rvalue, &dvalue);
		break;
	case 1 :	// inductor
		nmin = cData->FreqToIndex( fbase * 0.8f);
		nmax = cData->FreqToIndex( fbase * 1.2f);			// use 80% to 120% of the base frequency
		ntype = calc_P( cData, nmin, nmax, &rvalue, &dvalue);
				// to find the Q we use a low frequency to get best resolution
		nmin = cData->FreqToIndex( fminbound);
		nmax = cData->FreqToIndex( fmaxbound);

		for ( j=0, i=nmin; i < nmax; i++)
		{
			fval = cData->DataAt( dataAmp, i) / (frefer/4);		// get the amplitude of the impedance
			if ( (0.9 < fval))			// within 10% of reference
			{
				if ( 10 < ++j)
					break;
			}
			else j = 0;
		}
		ffreq = cData->DataAt( dataFreq, i);		// freq at which we hit the reference / 4
		nmin = cData->FreqToIndex( ffreq * 0.8f);
		nmax = cData->FreqToIndex( ffreq * 1.2f);			// use 80% to 120% of the base frequency
		ntype = calc_P( cData, nmin, nmax, &rold, &dold);
		rvalue = rold;
		break;
	case 0 :	// capacitor
		nmin = cData->FreqToIndex( fbase * 0.8f);
		nmax = cData->FreqToIndex( fbase * 1.2f);			// use 80% to 120% of the base frequency
		ntype = calc_P( cData, nmin, nmax, &rvalue, &dvalue);

		if ( fbase > 8000)			// above 8KHz we try a lower frequency
		{
					// to find the Q we use a low frequency to get best resolution
			nmin = cData->FreqToIndex( fminbound);
			nmax = cData->FreqToIndex( fmaxbound);

			for ( j=0, i=nmin; i < nmax; i++)
			{
				fval = cData->DataAt( dataAmp, i) / (2*frefer);		// get the amplitude of the impedance
				if ( 1.1 > fval)			// within 10% of reference
				{
					if ( 10 < ++j)
						break;
				}
				else j = 0;
			}
			ffreq = cData->DataAt( dataFreq, i);		// freq at which we hit the reference / 4
			nmin = cData->FreqToIndex( ffreq * 0.8f);
			nmax = cData->FreqToIndex( ffreq * 1.2f);			// use 80% to 120% of the base frequency
			ntype = calc_P( cData, nmin, nmax, &rold, &dold);
			rvalue = rold;
		}
		break;
	default:
		break;
	}

	pDlg->m_nType = ntype;
	if ( ntype == 2)			// resistor
		{
		pDlg->m_fValue = (float )rvalue;
		pDlg->m_fOther = 0.0f;
		}
	else						// capacitor or inductor
		{
		pDlg->m_fValue = (float )dvalue;
		pDlg->m_fOther = (float )rvalue;
		}

	pDlg->UpdateData( FALSE);
}


int COpMsrPassive::ProcessInput( void)
{
int nout;

	nout = DoStdFinish( );

	if ( ! nout)			// worked ok
		{
			if ( ! CDlgMsrPassive::IsShowing())		// do we need to createthe dialog?
			{
			CDlgMsrPassive *pdlg = new CDlgMsrPassive(AfxGetMainWnd());

				pdlg->Create( IDD_PASSIVERESULT);

				pdlg->ShowWindow( SW_SHOW );
			}
			calc_Passive( CDlgMsrPassive::GetPointer(), (CDataSet *)GetDataset( noImpedance));	// show results
		}
   return nout;
}


// ///////////////////////////////////////////////////////
//				Opcode Record -- Measure Distortion
// ///////////////////////////////////////////////////////

COpMsrDistortion::COpMsrDistortion( CNamed *cTarget, CView *cView) : COpMeasure( cTarget, cView)
{
RECORDINGINFO rcp;
CGenerator *pcgen = (CGenerator *)GetGenerator();
int nmax;

	m_dInfo.fFreq1 = 1000.0f;
	m_dInfo.fFreq2 = 5000.0f;
	m_dInfo.fWatt = 1.0f;
	m_dInfo.fPower1 = .05f;
	m_dInfo.fPower2 = 5.0f;
	m_dInfo.bLogRange = TRUE;
	m_dInfo.nStyle = 0;			// spectrum by default

	SetMaxLoop( 12);		// temporarily random
	m_Outputs[0] = NULL;

	SetNameID( IDOP_MSRDISTORTION);
	GetRecordInfo( &rcp);
	rcp.m_nDataType = rtFrequency;			// Distortion use frequency data
	{
	CGenerator *cgen = (CGenerator *)pcgen->Duplicate();
	const CDWordArray *parray = CMMWave::GetRateArray();

		nmax = parray->GetAt( parray->GetSize()-1);
		cgen->SetSine( 1000.0f, 0.0f);		// frequency and phase
		cgen->SetSampleRate(nmax);
		COpCode *cop = new COpChange( pcgen, cgen);
		PrivateQueue( cop);

	}

	rcp.m_fPlayTime = 64000.0f/nmax;			// 16000 data points
	rcp.m_fRecordTime = 64000.0f/nmax;
	SetRecordInfo( &rcp);
}

COpMsrDistortion::~COpMsrDistortion()
{
}

// this needs the generator already created, then it sets record and playback times
void COpMsrDistortion::SetupTimes( float fFreq)
{
RECORDINGINFO rcp;
CGenerator *pcgen = (CGenerator *)GetGenerator();

		GetRecordInfo( &rcp);
		rcp.m_fPlayTime = 128000.0f / pcgen->GetSampleRate();			// 128000 data points
					// get at least 10 cycles of this
		if ( (rcp.m_fPlayTime * fFreq) < 10)		// no?
			{
			rcp.m_fPlayTime = 10 / fFreq;		// use this much...
			}
		rcp.m_fRecordTime = rcp.m_fPlayTime;
		SetRecordInfo( &rcp);

}



void COpMsrDistortion::SetParms( MSRDISTORTINFO *pInfo)
{
CGenerator *pcgen = (CGenerator *)GetGenerator();
float freq;

	m_dInfo = *pInfo;		// set the whole structure / brute force

	if ( 1 == m_dInfo.nStyle)		// vary frequency
		{
		pcgen->SetSine( m_dInfo.fFreq1, 0.0f);		// set frequency
		freq = m_dInfo.fFreq2;						// use ending frequency to set sample rate
		}
	else
		{
		pcgen->SetSine( m_dInfo.fFreq, 0.0f);		// set frequency
		freq = m_dInfo.fFreq;
		}

	SetMaxLoop( pInfo->nPoints);			// set it right

	SetupTimes( freq);

	{
	RECORDINGINFO rcp;
		GetRecordInfo( &rcp);
		if ( 2 == m_dInfo.nStyle)		// vary power
			rcp.m_fDataAmplitude = m_dInfo.fPower1 * m_dInfo.fWatt / 2;	// volume is volts, power is 2x therefore
		else
			rcp.m_fDataAmplitude = m_dInfo.fPower * m_dInfo.fWatt / 2;
		SetRecordInfo( &rcp);
	}

}

int		COpMsrDistortion::CalcDistortion(CDataSet *cdOut[], CDataSet *cdSource, float fCenter)
{
int i;
double fdat;
double damp, ddat, dmax;

	fdat = cdSource->Maximum( dataAmp);		// the generator output
	fdat = cdSource->ConvertToFormat( (float )fdat, uomVolts) / 100; // in percent

	for ( i=2; i <= 4; i++)		// do 2,3,4th harmonics
		{
		ddat = cdSource->Maximum( dataAmp, fCenter*i*.98f, fCenter*i*1.02f);		// and data value (absolute)
		ddat = cdSource->ConvertToFormat( (float )ddat, uomVolts); // in percent

		damp = ddat / fdat;

		cdOut[i-2]->AddData( FTOI(damp), 0);
		}			// end of for loop

	ddat = 0;
	dmax = cdSource->Maximum( dataFreq);		// max frequency
	for ( i=5; ; i++)		// do 2,3,4th harmonics
		{
		if ( (i * fCenter) > dmax)
			break;
		ddat += cdSource->Maximum( dataAmp, fCenter*i*.98f, fCenter*i*1.02f);		// and data value (absolute)


		}			// end of for loop
	damp = ddat / fdat;
	cdOut[3]->AddData( FTOI(damp), 0);

	return 0;
}

int COpMsrDistortion::ProcessInput( void)
{
int nout;
CDataSet *pcout, *pcright;
CNamed *pparent = (CNamed *)FindTargetObject();

	nout = DoStdFinish( );

	if ( m_dInfo.nStyle && ! m_Outputs[0])		// not yet built
		{
		COpFindOrCreate *ccr;
		int i;

			ccr = new COpFindOrCreate(pparent,  pparent->GetName() + ".2nd Harmonic", ntDataSet);
			if ( ! PrivateQueue( ccr) )
				m_Outputs[0] = (CDataSet *)ccr->GetFound();
			ccr = new COpFindOrCreate(pparent,  pparent->GetName() + ".3rd Harmonic", ntDataSet);
			if ( ! PrivateQueue( ccr) )
				m_Outputs[1] = (CDataSet *)ccr->GetFound();
			ccr = new COpFindOrCreate(pparent,  pparent->GetName() + ".4th Harmonic", ntDataSet);
			if ( ! PrivateQueue( ccr) )
				m_Outputs[2] = (CDataSet *)ccr->GetFound();
			ccr = new COpFindOrCreate(pparent,  pparent->GetName() + ".Upper Harmonic", ntDataSet);
			if ( ! PrivateQueue( ccr) )
				m_Outputs[3] = (CDataSet *)ccr->GetFound();

		for ( i=0; i<3; i++)
			{
			if ( m_Outputs[i])
				{
				m_Outputs[i]->SetSize(0,0);
				m_Outputs[i]->SetUOM( uomFreq);
				m_Outputs[i]->SetDOM( uomVolts);
				m_Outputs[i]->SetDelta((m_dInfo.fFreq2 - m_dInfo.fFreq1) / GetMaxLoop());
				m_Outputs[i]->SetStart(m_dInfo.fFreq1);
				}
			}
		}

	switch( m_dInfo.nStyle)
		{
		case 0 :		// spectrum
			if ( ! nout)			// worked ok
				{
				pcright = (CDataSet *)GetDataset( noFftData);		// right fft
						
				CXformDistort *cop = new CXformDistort( pcright);
				cop->SetBase( pparent);
				cop->SetCenterFreq( m_dInfo.fFreq);
				if ( ! PrivateQueue( cop))
					{
					pcout = (CDataSet *)cop->GetDestination();
					SetDataset( noResultData, pcout);		// first result
					}
				}
			return nout;			// do NOT loop
		case 1 :					// vary frequency
			{
			pcright = (CDataSet *)GetDataset( noFftData);		// right fft
			CalcDistortion( m_Outputs, pcright, m_dInfo.fFreq1 + (m_dInfo.fFreq2 - m_dInfo.fFreq1) * GetCurrentLoop() / GetMaxLoop() );
			CGenerator *pcgen = (CGenerator *)GetGenerator();
			float freq = m_dInfo.fFreq1 + (m_dInfo.fFreq2 - m_dInfo.fFreq1) * (1+GetCurrentLoop()) / GetMaxLoop();
			pcgen->SetSine( freq, 0.0f);				// set new frequency
			SetupTimes( freq);
			}

			break;
		case 2 :					// vary power
			pcright = (CDataSet *)GetDataset( noFftData);		// right fft
			CalcDistortion( m_Outputs, pcright, m_dInfo.fFreq);
			{
			RECORDINGINFO rcp;
				GetRecordInfo( &rcp);
				rcp.m_fDataAmplitude = (m_dInfo.fWatt / 2) *
					(m_dInfo.fPower1 + (m_dInfo.fPower2 - m_dInfo.fPower1) * (1+GetCurrentLoop()) / GetMaxLoop());
				SetRecordInfo( &rcp);
			}
			break;
		}

	SetCurrentLoop( 1 + GetCurrentLoop());
	if ( (GetMaxLoop() > GetCurrentLoop()) && !IsStopped())
		{
		DoRecord();
		}
  return nout;
}

// ///////////////////////////////////////////////////////
//				Opcode Record -- Measure Frequency
// ///////////////////////////////////////////////////////

COpMsrCalLoop::COpMsrCalLoop( CNamed *cTarget, CView *cView) : COpMeasure( cTarget, cView)
{
RECORDINGINFO rcp;
TESTCAL tcal;
CAudtestDoc *pdoc;
// CGenerator *pcgen = (CGenerator *)cTarget;		// it's a signal...

//	pcgen->SetSampleRate( CMMWave::GetMaxRate());
//	pcgen->SetMls( 0x4000, FALSE, TRUE);

	pdoc = (CAudtestDoc *)GetDocument();
	tcal = *pdoc->GetCalib();
	m_dwLastCal = tcal.dwLeftRight;		// disable calibration
	tcal.dwLeftRight = 0;		// disable calibration
	pdoc->SetCalib( &tcal);

	SetNameID( IDOP_MSRFREQUENCY);
	GetRecordInfo( &rcp);
	rcp.m_nDataType = rtFrequency;			// Frequency
	SetFreqType( fqFull);				// use all data
	SetRecordInfo( &rcp);
}

COpMsrCalLoop::~COpMsrCalLoop()
{
}


int COpMsrCalLoop::ProcessInput( void)
{
int nout;
NAMEDOUTTYPES nodata, norefer;
CDataSet *pcout, *pcright;
RECORDINGINFO rcd;

	nout = DoStdFinish( );

	if ( ! nout)			// worked ok
		{
			GetRecordInfo( &rcd);
			if ( chLeft == rcd.m_nDataChannel)			// backwards
			{
				nodata = noFftRefer;
				norefer = noFftData;
			}
			else
			{
				nodata = noFftData;
				norefer = noFftRefer;
			}
		if ( ! CopyOutput( IDS_CALIB, norefer))
			{
			pcout = (CDataSet *)GetDataset( noResultData);		// left fft
			pcright = (CDataSet *)GetDataset( nodata);			// right fft
			if ( pcright)
				{
				CXformCombine *cop;
					cop = new CXformCombine( pcout, pcright);
					cop->SetOperation( 3);			// divide
					PrivateQueue( cop);				// produce a/b
				}

#if 0
						// ------------ now smooth the data
			{
			CXformSmooth *cop;

				cop = new CXformSmooth( pcout);
				cop->SetStyle( 4);		// 1/6 octave
				cop->SetMethod( 0);		// absolute averaging
				PrivateQueue( cop);
			}
#endif
			TESTCAL tcal;
			CAudtestDoc *pdoc;

			pdoc = (CAudtestDoc *)GetDocument();
			tcal = *pdoc->GetCalib();
			tcal.dwLeftRight = pcout->GetID();
			pdoc->SetCalib( &tcal);
			}
		else
			nout = 1;
		}

   return nout;
}

// ///////////////////////////////////////////////////////
//				Opcode Record -- Measure Frequency
// ///////////////////////////////////////////////////////

COpMsrFrequency::COpMsrFrequency( CNamed *cTarget, CView *cView) : COpMeasure( cTarget, cView)
{
RECORDINGINFO rcp;

	SetNameID( IDOP_MSRFREQUENCY);
	GetRecordInfo( &rcp);
	rcp.m_nDataType = rtFrequency;			// Frequency
	SetFreqType( fqFull);				// use all data
	SetRecordInfo( &rcp);
}

COpMsrFrequency::~COpMsrFrequency()
{
}


int COpMsrFrequency::ProcessInput( void)
{
int nout;
CDataSet *pcout, *pcright;

	nout = DoStdFinish( );

	if ( ! nout)			// worked ok
		{
		if ( ! TrailOutput( IDS_FREQUENCY, noFftData))
			{
			pcout = (CDataSet *)GetDataset( noResultData);		// left fft
			pcright = (CDataSet *)GetDataset( noFftRefer);		// right fft
			if ( pcright)
				{
				CXformCombine *cop;
					cop = new CXformCombine( pcout, pcright);
					cop->SetOperation( 3);			// divide
					PrivateQueue( cop);
				}
			}
		else
			nout = 1;
		}

   return nout;
}

// ///////////////////////////////////////////////////////
//				Opcode Record -- Measure Microphone
// ///////////////////////////////////////////////////////

COpMsrMicTotal::COpMsrMicTotal( CNamed *cTarget, CView *cView) : COpMsrMicrophone( cTarget, cView)
{
	SetNameID( IDOP_MSRMICROPHONE);
	SetFreqType( fqGateStart);						// total mic response
}

COpMsrMicTotal::~COpMsrMicTotal()
{
}



COpMsrMicAnechoic::COpMsrMicAnechoic( CNamed *cTarget, CView *cView) : COpMsrMicrophone( cTarget, cView)
{
	SetNameID( IDOP_MSRMICGATED);
	SetFreqType( fqGateAll);						// anechoic response
}

COpMsrMicAnechoic::~COpMsrMicAnechoic()
{
}



COpMsrMicrophone::COpMsrMicrophone( CNamed *cTarget, CView *cView) : COpMeasure( cTarget, cView)
{
RECORDINGINFO rcp;

	GetRecordInfo( &rcp);
	rcp.m_nDataType = rtFrequency;			// Microphone
	{
	ACOUSTICINFO iaco;

		CAudtestApp::GetAcousticInfo( &iaco);		// what do we do??
		rcp.m_nDataChannel = iaco.m_nMicChannel;	// left data input
		rcp.m_nCalibChannel = iaco.m_nRefChannel;	// no calibration channel
	}
	SetRecordInfo( &rcp);
}

COpMsrMicrophone::~COpMsrMicrophone()
{
}

void COpMsrMicrophone::MungeInput( UINT idDesc)
{
CDataSet *pcout, *pcright;
CNamed *pparent = (CNamed *)FindTargetObject();
CAudtestDoc *pdoc = (CAudtestDoc *)pparent->GetDocument();
CXformCombine *cop;

	pcout = (CDataSet *)GetDataset( noResultData);
	pcright = (CDataSet *)GetDataset( noFftRefer);		// right fft
	if ( pcright)
		{
		cop = new CXformCombine( pcout, pcright);
		cop->SetOperation( 3);			// divide
		PrivateQueue( cop);
		}
	if ( pdoc->GetMicResponse())
		{
		cop = new CXformCombine( pcout, pdoc->GetMicResponse());
		cop->SetOperation( 3);			// divide
		PrivateQueue( cop);
		}

	Describe( idDesc, pparent, pcout);

}

int COpMsrMicrophone::ProcessInput( void)
{
int nout;
UINT uname;

	nout = DoStdFinish( );

	if ( ! nout)			// worked ok
	{
		if ( fqGateAll != GetFreqType())	// not gated
			uname = IDS_MICRESPONSE;		// .Mic Response
		else
			uname = IDS_MICGATED;			// .Mic Gated

		if ( ! TrailOutput( uname, noFftData))
		{
		CNamed *cout;
			MungeInput( IDS_MSR_MIC);
			cout = GetDataset( noResultData);
			DescribeGating( cout);
		}
		else 
			nout = 1;
	}

   return nout;
}

// ///////////////////////////////////////////////////////
//				Opcode Record -- Measure Time
// ///////////////////////////////////////////////////////

COpMsrTime::COpMsrTime( CNamed *cTarget, CView *cView) : COpMeasure( cTarget, cView)
{
RECORDINGINFO rcp;

	SetNameID( IDOP_MSRTIME);
	GetRecordInfo( &rcp);
	rcp.m_nDataType = rtTime;			// Time
	SetRecordInfo( &rcp);
}

COpMsrTime::~COpMsrTime()
{
}


int COpMsrTime::ProcessInput( void)
{
int nout;

	nout = DoStdFinish( );

	if ( ! nout)			// worked ok
		{
		nout = CopyOutput( IDS_PULSE, noDataIn);
		}

	return nout;

}

// ///////////////////////////////////////////////////////
//				Opcode Record -- Measure Intermod
// ///////////////////////////////////////////////////////

COpMsrIntermod::COpMsrIntermod( CNamed *cTarget, CView *cView) : COpMeasure( cTarget, cView)
{
RECORDINGINFO rcp;
CGenerator *pcgen;

	pcgen = (CGenerator *)((CAudtestDoc *)GetDocument() )->GetDefaultGenerator();
	SetNameID( IDOP_MSRDISTORTION);
	GetRecordInfo( &rcp);
	rcp.m_nDataType = rtFrequency;			// Distortion use frequency data
	{
	CGenerator *cgen = (CGenerator *)pcgen->Duplicate();
		cgen->SetIntermod( (float )19000, (float )20000);		// frequency and phase
		COpCode *cop = new COpChange( pcgen, cgen);
		PrivateQueue( cop);

	}
	rcp.m_fPlayTime = 16000.0f/44100.0f;			// 32000 data points
	rcp.m_fRecordTime = 16000.0f/44100.0f;
	SetRecordInfo( &rcp);
}

COpMsrIntermod::~COpMsrIntermod()
{
}

void COpMsrIntermod::SetParms( MSRINTERMODINFO *pInfo)
{
RECORDINGINFO rcp;
CGenerator *pcgen = (CGenerator *)GetGenerator();
float freq1, freq2;

	m_dInfo = *pInfo;		// set the whole structure / brute force

	freq1 = m_dInfo.fFreq1;
	freq2 = m_dInfo.fFreq2;
	pcgen->SetIntermod( freq1, freq2);		// set the two frequencies

	{
	const CDWordArray *parray = CMMWave::GetRateArray();
	int nmax;

		nmax = parray->GetAt( parray->GetSize()-1);

	pcgen->SetSampleRate(nmax);
	}

	GetRecordInfo( &rcp);
	rcp.m_fPlayTime = 128000.0f / pcgen->GetSampleRate();			// set the play time
	rcp.m_fRecordTime = rcp.m_fPlayTime;
	SetRecordInfo( &rcp);

}

int COpMsrIntermod::ProcessInput( void)
{
int nout;
CNamed *pparent = (CNamed *)FindTargetObject();
CDataSet *pcout, *pcleft, *pcright;

	nout = DoStdFinish( );

	if ( ! nout)			// worked ok
		{
		pcleft = (CDataSet *)GetDataset( noFftData);		// left fft
		pcright = (CDataSet *)GetDataset( noFftRefer);		// right fft
				
		CXformIntermod *cop = new CXformIntermod( pcright);
		cop->SetBase( pparent);
		cop->SetCenterFreq( m_dInfo.fFreq1);
		if ( ! PrivateQueue( cop))
			{
			pcout = (CDataSet *)cop->GetDestination();
			SetDataset( noResultData, pcout);		// first result
			}
		}

   return nout;
}

