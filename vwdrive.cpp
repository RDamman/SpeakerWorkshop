// vwdrive.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "audtedoc.h"
#include "DlgCalcMerge.h"

				// we need the drive operators
#define DRIVEUSEOPS
#include "vwdrive.h"

#include "audtedoc.h"
//#include "named.h"

#include "driver.h"

#include "opRecord.h"
#include "XformAll.h"

#include "zFormEdt.h"
#include "DlgDvEst.h"
#include "DlgDrvEquiv.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudDriverView

IMPLEMENT_DYNCREATE(CAudDriverView, CAudchView)

CAudDriverView::CAudDriverView()
{
}

CAudDriverView::~CAudDriverView()
{
}


BEGIN_MESSAGE_MAP(CAudDriverView, CAudchView)
	//{{AFX_MSG_MAP(CAudDriverView)
	ON_COMMAND(ID_CALCULATE_DRIVERPARAMETERS, OnCalculateDriverParameters)
	ON_COMMAND(ID_MEASURE_DISTORTION, OnMeasureDistortion)
	ON_COMMAND(ID_MEASURE_IMPEDANCE, OnMeasureImpedance)
	ON_COMMAND(ID_MEASURE_FREEAIR, OnMeasureFreeair)
	ON_COMMAND(ID_MEASURE_PULSERESPONSE, OnMeasurePulseresponse)
	ON_COMMAND(ID_MEASURE_SEALED, OnMeasureSealed)
	ON_COMMAND(ID_MEASURE_NEARFIELD, OnMeasureNearfield)
	ON_COMMAND(ID_MEASURE_FARFIELD, OnMeasureFarfield)
	ON_COMMAND(ID_MSR_FREQ_ONAXIS, OnMsrFreqOnaxis)
	ON_COMMAND(ID_MSR_FREQ_30, OnMsrFreq30)
	ON_COMMAND(ID_MSR_FREQ_60, OnMsrFreq60)
	ON_COMMAND(ID_MEASURE_MASS, OnMeasureMass)
	ON_COMMAND(ID_DRIVER_SETEQUIVALENCE, OnDriverSetequivalence)
	ON_COMMAND(ID_MEASURE_GATEFREQ, OnMeasureGatefreq)
	ON_COMMAND(ID_MEASURE_PORT, OnMeasurePort)
	ON_COMMAND(ID_CALC_MERGE, OnCalcMerge)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


static enum	formVar
{
	frm_Name,
	frm_Descript,
	frm_FS,
	frm_Le,
	frm_L1,
	frm_R1,
	frm_Qms,
	frm_Qes,
	frm_Qts,
	frm_Vas,
	frm_Re,
	frm_Piston,
	frm_Xmax,
	frm_Sensitivity,
	frm_Pe,
	frm_BL,
	frm_Vol,
	frm_Mass,
	frm_Userre,
	frm_Useadded,
	frm_AVas,			// american stuff
	frm_APiston,
	frm_AXmax,
	frm_AVol,
	frm_AMass
};

static sFormField	form_Entries[] =
{ 
	{10,  0,   IDS_DRV_NAME	,IDS_DRVS_NULL} ,
	{10,  1,   IDS_DRV_DESCRIPT	,IDS_DRVS_NULL} ,
	{ 1,  2,   IDS_DRV_RESONANT_FREQ	,IDS_DRVS_RESONANT_FREQ} ,
	{ 1,  7,   IDS_DRV_INDUCTANCE	,IDS_DRVS_INDUCTANCE} ,
	{ 1,  8,   IDS_DRV_IND2	,IDS_DRVS_IND2} ,
	{ 1,  9,   IDS_DRV_R1	,IDS_DRVS_R1} ,
	{ 1,  5,   IDS_DRV_QMS	,IDS_DRVS_NULL} ,
	{ 1,  6,   IDS_DRV_QES	,IDS_DRVS_NULL} ,
	{ 1,  4,   IDS_DRV_TOTALQ	,IDS_DRVS_NULL} ,
	{ 1,  3,   IDS_DRV_VAS	,IDS_DRVS_VAS} ,
	{ 1,  10,   IDS_DRV_RE	,IDS_DRVS_RE} ,


	{ 40,  2,	IDS_DRV_PISTON	,IDS_DRVS_PISTON} ,
	{ 40,  3,	IDS_DRV_XMAX	,IDS_DRVS_XMAX} ,
	{ 40,  4,	IDS_DRV_SENSITIVITY	,IDS_DRVS_SENSITIVITY} ,
	{ 40,  5,	IDS_DRV_PE	,IDS_DRVS_PE} ,
	{ 40,  6,	IDS_DRV_BL	,IDS_DRVS_NULL} ,

	{ 40,  7,	IDS_DRV_VOL	,IDS_DRVS_VOL} ,
	{ 40,  8,	IDS_DRV_MASS	,IDS_DRVS_MASS} ,
	{ 40,  9,	IDS_DRV_USERRE	,IDS_DRVS_USERRE} ,
	{ 40,  10,	IDS_DRV_USEADDED 	,IDS_DRVS_USEADDED },
				// american units
	{ 1,  3,   IDS_DRV_VAS	,IDS_FRM_CUFT} ,
	{ 40,  2,	IDS_DRV_PISTON	,IDS_FRM_SQIN} ,
	{ 40,  3,	IDS_DRV_XMAX	,IDS_FRM_INCH} ,
	{ 40,  7,	IDS_DRV_VOL	,IDS_FRM_CUFT} ,
	{ 40,  8,	IDS_DRV_MASS	,IDS_FRM_OZ}

};


/////////////////////////////////////////////////////////////////////////////
// CAudDriverView drawing

void CAudDriverView::OnDraw(CDC* pDC)
{
CDriver *pdriver = (CDriver *)GetTargetObject();
const DRIVEPARM	*dparm = pdriver->GetDriverParameters();
const DRIVEEQUIV *deq = pdriver->GetDriverEquiv();
CFont *cfont;
CFont *cfold;

	cfont = CAudtestApp::GetAppFont( ftStatus).GetCurrentFont( pDC);
	cfold = pDC->SelectObject( cfont);

	SetFloatFormat( 8, 3);
	SetIntFormat( 5);

	{
	int i;
	int iwidth;
	CSize csmax(0,0);

		for ( i=0; i< frm_Useadded; i++)
		{
			iwidth = FormExtent( pDC, &form_Entries[i]);
			if ( csmax.cx < iwidth)
				csmax.cx = iwidth;
			if ( csmax.cy < form_Entries[i].iY)
				csmax.cy = form_Entries[i].iY;
		}

		m_iRowWidth = csmax.cx + 7 * CharWidth( pDC);			// add in space for 10 chars
		m_iMaxHeight = csmax.cy * CharHeight( pDC);

		for ( i=0; i< frm_AMass; i++)
		{
			if ( form_Entries[i].iX > 20)		// it's column 2
			{
				form_Entries[i].iX = 15 + m_iRowWidth / CharWidth( pDC);
			}
		}

	}


				// format the variables for on-screen display

	{
	CString stryes;
	CString strno;

		stryes.LoadString( IDS_YES);
		strno.LoadString( IDS_NO);

		DrawVariable( pDC, 	&form_Entries[ frm_Name], pdriver->GetName());
		DrawVariable( pDC, 	&form_Entries[ frm_Descript], pdriver->GetDescription());
		DrawVariable( pDC, 	&form_Entries[ frm_FS], dparm->fFs, m_iRowWidth);
		DrawVariable( pDC, &form_Entries[ frm_Le],  dparm->fLe * 1000.0f, m_iRowWidth);
		DrawVariable( pDC, &form_Entries[ frm_L1],  (float )deq->fL1a * 1000.0f, m_iRowWidth);
		DrawVariable( pDC, &form_Entries[ frm_R1],  (float )deq->fR1, m_iRowWidth);
		DrawVariable( pDC, &form_Entries[ frm_Qms], dparm->fQms, m_iRowWidth);
		DrawVariable( pDC, &form_Entries[ frm_Qes], dparm->fQes, m_iRowWidth);
		DrawVariable( pDC, &form_Entries[ frm_Qts], dparm->fQts, m_iRowWidth);
		DrawVariable( pDC, &form_Entries[ frm_Re], dparm->fRe, m_iRowWidth);
		DrawVariable( pDC, &form_Entries[ frm_Sensitivity], dparm->fSensitivity, m_iRowWidth);
		DrawVariable( pDC, &form_Entries[ frm_Pe], dparm->fPe, m_iRowWidth);
		DrawVariable( pDC, &form_Entries[ frm_BL], dparm->fBL, m_iRowWidth);
		DrawVariable( pDC, &form_Entries[ frm_Userre], dparm->bUseDC ? stryes : strno);
		DrawVariable( pDC, &form_Entries[ frm_Useadded], dparm->bUseMass ? stryes : strno);

		if ( CAudtestApp::GetIsMetric())
		{
			DrawVariable( pDC, &form_Entries[ frm_Vas], dparm->fVas * 1000.0f, m_iRowWidth);
			DrawVariable( pDC, &form_Entries[ frm_Piston], dparm->fPistonArea * 10000.0f, m_iRowWidth);	// m**2 to cm**2
			DrawVariable( pDC, &form_Entries[ frm_Xmax], dparm->fXmax, m_iRowWidth);
			DrawVariable( pDC, &form_Entries[ frm_Vol], dparm->fVolume * 1000.0f, m_iRowWidth);
			DrawVariable( pDC, &form_Entries[ frm_Mass], dparm->fMass, m_iRowWidth);
		}
		else
		{
		float fo;
			fo = CzFormatEdit::ConvertBaseToBase( dparm->fVas, mtCuFoot, mtCuMeter);
			DrawVariable( pDC, &form_Entries[ frm_AVas], fo, m_iRowWidth);
			fo = CzFormatEdit::ConvertBaseToBase( dparm->fPistonArea, mtSqInch, mtSqMeter);
			DrawVariable( pDC, &form_Entries[ frm_APiston], fo, m_iRowWidth);	// m**2 to cm**2
			fo = CzFormatEdit::ConvertBaseToBase( dparm->fXmax, mtInch, mtCm);
			DrawVariable( pDC, &form_Entries[ frm_AXmax], fo, m_iRowWidth);
			fo = CzFormatEdit::ConvertBaseToBase( dparm->fVolume, mtCuFoot, mtCuMeter);
			DrawVariable( pDC, &form_Entries[ frm_AVol], fo, m_iRowWidth);
			fo = CzFormatEdit::ConvertBaseToBase( dparm->fMass, mtOz, mtGram);
			DrawVariable( pDC, &form_Entries[ frm_AMass], fo, m_iRowWidth);
		}

	}

#if 0
	if ( ! GetViewChart())						// does this view have a chart???
	{
		CString csi;
		csi.LoadString( IDERR_DRVCHART);
		pDC->TextOut( 10, 10, csi);
	}
#endif

	{
	RECT rccl;

		::SetRect( &rccl, CharWidth( pDC) * 4, m_iMaxHeight + CharHeight( pDC) * 2, 
						  CharWidth( pDC) * 4, CharHeight( pDC) * 2);		// set width in %
		SetSubView( &rccl);
	}

	pDC->SelectObject( cfold);		// reset the font


	CAudchView::OnDraw( pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CAudDriverView diagnostics

#ifdef _DEBUG
void CAudDriverView::AssertValid() const
{
	CAudchView::AssertValid();
}

void CAudDriverView::Dump(CDumpContext& dc) const
{
	CAudchView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAudDriverView message handlers

void CAudDriverView::OnCalculateDriverParameters() 
{
CNamed *cnam = GetTargetObject();

	if ( cnam && ntDriver == cnam->GetType())
		{
		CXformCalcDriver *cxfl = new CXformCalcDriver ( GetTargetObject() );

			Dialog_Perform(cxfl);
		}
}

void CAudDriverView::OnMeasureDistortion() 
{
	StdOperation( new COpMsrDistortion( GetTargetObject(), this) );
}

void CAudDriverView::OnMeasureImpedance() 
{
	StdOperation( new COpDriveImpedance( GetTargetObject(), this) );
}

void CAudDriverView::OnMeasureFreeair() 
{
	StdOperation( new COpDriveFreeAir( GetTargetObject(), this) );
}


void CAudDriverView::OnMeasureMass() 
{
	StdOperation( new COpDriveAddedMass( GetTargetObject(), this) );
	
}

void CAudDriverView::OnMeasurePulseresponse() 
{
	StdOperation( new COpDrivePulse( GetTargetObject(), this) );
}

void CAudDriverView::OnMeasureSealed() 
{
	StdOperation( new COpDriveSealed( GetTargetObject(), this) );
}


void CAudDriverView::OnMeasureNearfield() 
{
	StdOperation( new COpDriveNearfield( GetTargetObject(), this) );
	
}

void CAudDriverView::OnMeasureFarfield() 
{
	StdOperation( new COpDriveFarfield( GetTargetObject(), this) );
}

void CAudDriverView::OnMsrFreqOnaxis() 
{
	StdOperation( new COpDriveFreqOnaxis( GetTargetObject(), this) );
	
}

void CAudDriverView::OnMsrFreq30() 
{
	StdOperation( new COpDriveFreq30( GetTargetObject(), this) );
	
}

void CAudDriverView::OnMsrFreq60() 
{
	StdOperation( new COpDriveFreq60( GetTargetObject(), this) );
	
}

void CAudDriverView::OnMeasureGatefreq() 
{
	StdOperation( new COpDriveGated( GetTargetObject(), this) );
	
}

void CAudDriverView::OnMeasurePort() 
{
	StdOperation( new COpDrivePort( GetTargetObject(), this) );
	
}


/////////////////////////////////////////////////////////////////////////////
// Driver OpCodes


// ///////////////////////////////////////////////////////
//				Opcodes -- Measure Impedance Function
// ///////////////////////////////////////////////////////

COpDriveFreeAir::COpDriveFreeAir( CNamed *cTarget, CView *cView) : COpMsrImpedance( cTarget, cView)
{
}

COpDriveFreeAir::~COpDriveFreeAir()
{
}


int COpDriveFreeAir::ProcessInput( void)
{
int nout;

	nout = DoStdFinish();

	if ( ! nout)			// worked ok???
		{
		TrailOutput( IDS_FREEAIR, noImpedance);

		CNamed *cout = GetDataset( noResultData);

		if ( cout)
			{
			DRIVEPARM dp;
			CDriver *pdrive = (CDriver *)FindTargetObject();

				dp = *pdrive->GetDriverParameters( );
				dp.dwFreeAir = cout->GetID();
				pdrive->SetDriverParameters( &dp);
			Describe( IDS_MSR_IMPFREE, pdrive, (CDataSet *)cout);
			}
		}

	return nout;
}


COpDriveSealed::COpDriveSealed( CNamed *cTarget, CView *cView) : COpMsrImpedance( cTarget, cView)
{
}

COpDriveSealed::~COpDriveSealed()
{
}


int COpDriveSealed::ProcessInput( void)
{
int nout;

	nout = DoStdFinish();

	if ( ! nout)			// worked ok???
		{
		CopyOutput( IDS_SEALED, noImpedance);

		CNamed *cout = GetDataset( noResultData);

		if ( cout)
			{
			DRIVEPARM dp;
			CDriver *pdrive = (CDriver *)FindTargetObject();

				dp = *pdrive->GetDriverParameters( );
				dp.dwSealed = cout->GetID();
				pdrive->SetDriverParameters( &dp);
			Describe( IDS_MSR_IMPSEAL, pdrive, (CDataSet *)cout);
			}
		}

	return nout;
}


COpDriveAddedMass::COpDriveAddedMass( CNamed *cTarget, CView *cView) : COpMsrImpedance( cTarget, cView)
{
}

COpDriveAddedMass::~COpDriveAddedMass()
{
}


int COpDriveAddedMass::ProcessInput( void)
{
int nout;

	nout = DoStdFinish();

	if ( ! nout)			// worked ok???
		{
		CopyOutput( IDS_ADDEDMASS, noImpedance);

		CNamed *cout = GetDataset( noResultData);

		if ( cout)
			{
			DRIVEPARM dp;
			CDriver *pdrive = (CDriver *)FindTargetObject();

				dp = *pdrive->GetDriverParameters( );
				dp.dwAddMass = cout->GetID();
				pdrive->SetDriverParameters( &dp);
			Describe( IDS_MSR_IMPMASS, pdrive, (CDataSet *)cout);
			}
		}

	return nout;
}


COpDriveImpedance::COpDriveImpedance( CNamed *cTarget, CView *cView) : COpMsrImpedance( cTarget, cView)
{
}

COpDriveImpedance::~COpDriveImpedance()
{
}


int COpDriveImpedance::ProcessInput( void)
{
int nout;

	nout = DoStdFinish();

	if ( ! nout)			// worked ok???
		{
		TrailOutput( IDS_IMPEDANCE, noImpedance);

		CNamed *cout = GetDataset( noResultData);

		if ( cout)
			{
			DRIVEPARM dp;
			CDriver *pdrive = (CDriver *)FindTargetObject();

				dp = *pdrive->GetDriverParameters( );
				dp.dwImpedance = cout->GetID();
				pdrive->SetDriverParameters( &dp);
			}
		}

	return nout;
}

COpDrivePulse::COpDrivePulse( CNamed *cTarget, CView *cView) : COpMsrTime( cTarget, cView)
{
}

COpDrivePulse::~COpDrivePulse()
{
}


int COpDrivePulse::ProcessInput( void)
{
int nout;

	nout = COpMsrTime::ProcessInput();

	if ( ! nout)			// worked ok???
		{
		CNamed *cout = GetDataset( noResultData);

		if ( cout)
			{
			DRIVEPARM dp;
			CDriver *pdrive = (CDriver *)FindTargetObject();

				dp = *pdrive->GetDriverParameters( );
				dp.dwTimeRes = cout->GetID();
				pdrive->SetDriverParameters( &dp);
			Describe( IDS_MSR_PULSE, pdrive, (CDataSet *)cout);
			}
		}

	return nout;
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
COpDriveNearfield::COpDriveNearfield( CNamed *cTarget, CView *cView) : COpMsrMicTotal( cTarget, cView)
{
		SetFreqType( fqFull);						// total mic response - not gated at all
}

COpDriveNearfield::~COpDriveNearfield()
{
}


int COpDriveNearfield::ProcessInput( void)
{
int nout;

	nout = DoStdFinish();

	if ( ! nout)			// worked ok???
		{
		TrailOutput( IDS_NEARFIELD, noFftData);

		CNamed *cout = GetDataset( noResultData);

		if ( cout)
			{
			DRIVEPARM dp;
			CDriver *pdrive = (CDriver *)FindTargetObject();

				MungeInput(IDS_MSR_NEAR);			// finish the input processing

				dp = *pdrive->GetDriverParameters( );
				dp.dwNearField = cout->GetID();
				pdrive->SetDriverParameters( &dp);
			}
		}

	return nout;
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
COpDriveFarfield::COpDriveFarfield( CNamed *cTarget, CView *cView) : COpMsrMicTotal( cTarget, cView)
{
}

COpDriveFarfield::~COpDriveFarfield()
{
}


int COpDriveFarfield::ProcessInput( void)
{
int nout;

	nout = DoStdFinish();

	if ( ! nout)			// worked ok???
		{
		TrailOutput( IDS_FARFIELD, noFftData);

		CNamed *cout = GetDataset( noResultData);

		if ( cout)
			{
			DRIVEPARM dp;
			CDriver *pdrive = (CDriver *)FindTargetObject();

				MungeInput( IDS_MSR_FAR);			// finish the input processing
				DescribeGating( cout);

				dp = *pdrive->GetDriverParameters( );
//				dp.dwFarfield = cout->GetID();
				pdrive->SetDriverParameters( &dp);
			}
		}

	return nout;
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
COpDrivePort::COpDrivePort( CNamed *cTarget, CView *cView) : COpMsrMicTotal( cTarget, cView)
{
	SetFreqType( fqFull);			// total mic response - not gated at all
}

COpDrivePort::~COpDrivePort()
{
}


int COpDrivePort::ProcessInput( void)
{
int nout;

	nout = DoStdFinish();

	if ( ! nout)			// worked ok???
		{
		TrailOutput( IDS_PORTFREQ, noFftData);

		CNamed *cout = GetDataset( noResultData);

		if ( cout)
			{
			DRIVEPARM dp;
			CDriver *pdrive = (CDriver *)FindTargetObject();

				MungeInput( IDS_MSR_PORTFREQ);			// finish the input processing

				dp = *pdrive->GetDriverParameters( );
				dp.dwPort = cout->GetID();
				pdrive->SetDriverParameters( &dp);
			}
		}

	return nout;
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
COpDriveFreqOnaxis::COpDriveFreqOnaxis( CNamed *cTarget, CView *cView) : COpMsrMicAnechoic( cTarget, cView)
{
}

COpDriveFreqOnaxis::~COpDriveFreqOnaxis()
{
}


int COpDriveFreqOnaxis::ProcessInput( void)
{
int nout;

	nout = DoStdFinish();

	if ( ! nout)			// worked ok???
		{
		TrailOutput( IDS_FREQONAXIS, noFftData);

		CNamed *cout = GetDataset( noResultData);

		if ( cout)
			{
			DRIVEPARM dp;
			CDriver *pdrive = (CDriver *)FindTargetObject();

				MungeInput(IDS_MSR_ONAXIS);			// finish the input processing
				DescribeGating( cout);

				dp = *pdrive->GetDriverParameters( );
				dp.dwResponse = cout->GetID();
				pdrive->SetDriverParameters( &dp);
			}
		}

	return nout;
}

// ------------------------------------------------------------------------
COpDriveFreq30::COpDriveFreq30( CNamed *cTarget, CView *cView) : COpMsrMicAnechoic( cTarget, cView)
{
}

COpDriveFreq30::~COpDriveFreq30()
{
}


int COpDriveFreq30::ProcessInput( void)
{
int nout;

	nout = DoStdFinish();

	if ( ! nout)			// worked ok???
		{
		TrailOutput( IDS_FREQ30, noFftData);

		CNamed *cout = GetDataset( noResultData);

		if ( cout)
			{
			DRIVEPARM dp;
			CDriver *pdrive = (CDriver *)FindTargetObject();

				MungeInput(IDS_MSR_FREQ30);			// finish the input processing
				DescribeGating( cout);

				dp = *pdrive->GetDriverParameters( );
				dp.dwFreq30 = cout->GetID();
				pdrive->SetDriverParameters( &dp);
			}
		}

	return nout;
}

// ------------------------------------------------------------------------
COpDriveFreq60::COpDriveFreq60( CNamed *cTarget, CView *cView) : COpMsrMicAnechoic( cTarget, cView)
{
}

COpDriveFreq60::~COpDriveFreq60()
{
}


int COpDriveFreq60::ProcessInput( void)
{
int nout;

	nout = DoStdFinish();

	if ( ! nout)			// worked ok???
		{
		TrailOutput( IDS_FREQ60, noFftData);

		CNamed *cout = GetDataset( noResultData);

		if ( cout)
			{
			DRIVEPARM dp;
			CDriver *pdrive = (CDriver *)FindTargetObject();

				MungeInput(IDS_MSR_FREQ60);			// finish the input processing
				DescribeGating( cout);

				dp = *pdrive->GetDriverParameters( );
				dp.dwFreq60 = cout->GetID();
				pdrive->SetDriverParameters( &dp);
			}
		}

	return nout;
}

// ------------------------------------------------------------------------
COpDriveGated::COpDriveGated( CNamed *cTarget, CView *cView) : COpMsrMicAnechoic( cTarget, cView)
{
}

COpDriveGated::~COpDriveGated()
{
}


int COpDriveGated::ProcessInput( void)
{
int nout;

	nout = DoStdFinish();

	if ( ! nout)			// worked ok???
		{
		TrailOutput( IDS_GATEFREQ, noFftData);

		CNamed *cout = GetDataset( noResultData);

		if ( cout)
			{
			DRIVEPARM dp;
			CDriver *pdrive = (CDriver *)FindTargetObject();

				MungeInput(IDS_MSR_GATEFREQ);			// finish the input processing
				DescribeGating( cout);

				dp = *pdrive->GetDriverParameters( );
				dp.dwGated = cout->GetID();
				pdrive->SetDriverParameters( &dp);
			}
		}

	return nout;
}


void CAudDriverView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
CDriver *cdrv = (CDriver *)GetTargetObject();
DWORD dwh = (DWORD )lHint;

	if ( cdrv )		// we have a target, and we have changed a single object
		{
		if( (!dwh) || dwh == cdrv->GetID() || dwh == cdrv->GetImpedance() || dwh == cdrv->GetResponse())	// it's ours
			{
			if ( dwh && ( (! GetViewChart()) || (cdrv->GetImpedance() != m_dwImpedance) || (cdrv->GetResponse() != m_dwResponse) ) )
				{
				SetViewChart( NULL);	// delete the currently viewed chart
				cdrv->CreateChart() ;	// build a new base chart
				}
			else
				SyncDataSets();

			InvalidateRect( NULL);

			m_dwImpedance = cdrv->GetImpedance();
			m_dwResponse = cdrv->GetResponse();
			}
		}

	CAudchView::OnUpdate(pSender, lHint, pHint);
	
}

void CAudDriverView::OnDriverSetequivalence() 
{
CNamed *cnam = GetTargetObject();

	if ( cnam && ntDriver == cnam->GetType())
		{
		CXformCalcEquiv *cxfl = new CXformCalcEquiv ( GetTargetObject() );

			Dialog_Perform(cxfl);
		}
	
}



void CAudDriverView::OnCalcMerge() 
{
CDriver *cdSource = (CDriver *)GetTargetObject();
CDlgCalcMerge cdlg;
UINT uout;

				// fill the function with defaults for this dataset
	cdlg.m_pRoot = (CFolder *)cdSource->GetRootObject();

	cdlg.m_fPortArea = 1.0f;

	{			// get piston area
	const DRIVEPARM *pparm = cdSource->GetDriverParameters();

		cdlg.m_fPistonArea = pparm->fPistonArea;
	}

	{		// get driver nearfield response
	const DRIVEPARM *pparm = cdSource->GetDriverParameters();

		cdlg.m_dwDriver = pparm->dwNearField;		// so name can be filled in, and uom found
		cdlg.m_dwPort = pparm->dwPort;				// port response
	}

	uout = cdlg.DoModal();

	if ( IDOK == uout)
		{
		CXformMergePort *cxfl = new CXformMergePort ( cdSource );
				// set the parameters for the merge
			cxfl->SetParameters( cdlg.m_dwDriver, cdlg.m_dwPort, cdlg.m_fPistonArea, cdlg.m_fPortArea);
				// do the merge
			if ( cxfl->QueueAndDo())						// do the fft
				delete cxfl;			// we failed this
		}

}
