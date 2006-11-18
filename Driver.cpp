// speaker.cpp : implementation of the CDriverArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "Driver.h"

#include "AudteDoc.h"
#include "dlgDrive.h"
#include "DataSet.h"

#include "opItem.h"
#include "chart.h"
#include "Utils.h"

#include "math.h"
#include "Complex.h"


// #include "dlggener.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDriver

IMPLEMENT_SERIAL(CDriver, CGraphed, 275 | VERSIONABLE_SCHEMA)


/////////////////////////////////////////////////////////////////////////////
// CDriver construction/destruction


			// number of response charts in a driver
#define NUM_RESPONSES 9

CDriver::CDriver()
{
		m_DP.fFs = 50.0f;					// Resonant frequency
		m_DP.fLe = 0.001f;					// inductance
		m_DP.fQms = 0.5f;					// mechanical Q
		m_DP.fQes = 0.5f;					// electrical Q
		m_DP.fQts = 0.4f;					// total Q
		m_DP.fRe = 1.0f;					// dc resistance
		m_DP.fVas = 1.0f;					// effective compliance

		m_DP.fPistonArea = 2.0f;			// diameter
		m_DP.fXmax = 1.0f;				// maximum excursion
		m_DP.fSensitivity = 1.0f;				// maximum excursion
		m_DP.fVolume = 1.0f;			// volume of sealed box
		m_DP.fMass = 1.0f;
		m_DP.fDCRes = 8.0f;
		m_DP.bUseDC = FALSE;
		m_DP.bUseMass = FALSE;
		m_DP.fBL = 0.1f;
		m_DP.fPe = 10.0f;
						//------------ now the datasets
		m_DP.dwResponse = 0;			// response curve
		m_DP.dwImpedance = 0;			// impedance
		m_DP.dwFreeAir = 0;			// free air impedance
		m_DP.dwSealed = 0;				// sealed box impedance
		m_DP.dwAddMass = 0;
		m_DP.dwTimeRes = 0;
		m_DP.dwNearField = 0;
		m_DP.dwFreq30 = 0;
		m_DP.dwFreq60 = 0;
		m_DP.dwGated = 0;
		m_DP.dwPort = 0;

		m_DEq.fRe = 10.0f;
		m_DEq.fL1a = 0.10f;
		m_DEq.fR1 = 10.0f;
		m_DEq.fL1b= 0.10f;
		m_DEq.fR2 = 10.0f;
		m_DEq.fL2 = 0.10f;
		m_DEq.fC2 = 0.01f;
}

CDriver::~CDriver()
{

}

/////////////////////////////////////////////////////////////////////////////
// CDriver serialization

void CDriver::Serialize(CArchive& ar)
{

	CGraphed::Serialize( ar);

	if (ar.IsStoring())
		{		// storing code here
		ValidateCurves();				// clean the driver before storing it away
		ar << m_DP.fQms;				// mechanical Q
		ar << m_DP.fQes;				// electrical Q
		ar << m_DP.fQts;				// total Q
		ar << m_DP.fFs;					// Resonant frequency
		ar << m_DP.fLe;
		ar << m_DP.fRe;					// dc resistance
		ar << m_DP.fPistonArea;			// diameter
		ar << m_DP.fVas;				// effective compliance
		ar << m_DP.fXmax;				// maximum excursion
		ar << m_DP.fVolume;				// volume of sealed box
		ar << m_DP.fMass;				// volume of sealed box
		ar << m_DP.fDCRes;				// DC resistance???
		ar << m_DP.bUseDC;				// user has supplied DC resistance
		ar << m_DP.bUseMass;			// user has supplied DC resistance
		ar << m_DP.fBL;					// motor strength of driver
		ar << m_DP.fPe;					// maximum power input
		ar << m_DP.fSensitivity;		// save the sensitivity
							//------------ now the datasets
		ar << m_DP.dwResponse;			// response curve
		ar << m_DP.dwImpedance;			// impedance
		ar << m_DP.dwSealed;			// sealed box impedance
		ar << m_DP.dwFreeAir;			// free air impedance
		ar << m_DP.dwAddMass;			// free air impedance
		ar << m_DP.dwTimeRes;			// time response
		ar << m_DP.dwNearField;			// nearfield response
		ar << m_DP.dwFreq30;			// 30 degrees response
		ar << m_DP.dwFreq60;			// 60 degrees response
		ar << m_DP.dwGated;				// gated response
		ar << m_DP.dwPort;				// port response

		ar << m_DEq.fRe;
		ar << m_DEq.fL1a;
		ar << m_DEq.fR1;
		ar << m_DEq.fL1b;
		ar << m_DEq.fR2;
		ar << m_DEq.fL2;
		ar << m_DEq.fC2;
		}
	else
		{								// loading code here 
		ar >> m_DP.fQms;					// mechanical Q
		ar >> m_DP.fQes;					// electrical Q
		ar >> m_DP.fQts;					// total Q
		ar >> m_DP.fFs;					// Resonant frequency
		ar >> m_DP.fLe;
		ar >> m_DP.fRe;					// dc resistance
		ar >> m_DP.fPistonArea;				// diameter
		ar >> m_DP.fVas;					// effective compliance
		ar >> m_DP.fXmax;					// maximum excursion
		ar >> m_DP.fVolume;				// volume of sealed box
		if ( GetSchema() >= 273)
			{
			ar >> m_DP.fMass;				// Resonant frequency ! (was <<)
			}
		else
			m_DP.fMass = 1.0f;
		ar >> m_DP.fDCRes;					// DC resistance???
		ar >> m_DP.bUseDC;					// user has supplied DC resistance
		if ( GetSchema() >= 273)
			{
			ar >> m_DP.bUseMass;				// Resonant frequency ! (was <<)
			}
		else
			m_DP.bUseMass = FALSE;
		if ( GetSchema() >= 271)
			{
			ar >> m_DP.fBL;					// motor strength of driver !
			ar >> m_DP.fPe;					// maximum power input !
			}
		else
			{
			m_DP.fBL = 1.0f;
			m_DP.fPe = 1.0f;
			}
		if ( GetSchema() >= 274)
			ar >> m_DP.fSensitivity;		// load if appropriate
		else
			m_DP.fSensitivity = 1.0f;		// save the sensitivity
								//------------ now the datasets
		ar >> m_DP.dwResponse;				// response curve
		ar >> m_DP.dwImpedance;			// impedance
		ar >> m_DP.dwSealed;				// sealed box impedance
		ar >> m_DP.dwFreeAir;			// free air impedance
		if ( GetSchema() >= 273)
			{
			ar >> m_DP.dwAddMass;				// Resonant frequency ! (was <<)
			}
		else
			m_DP.dwAddMass = 0;
		ar >> m_DP.dwTimeRes;			// time response
		ar >> m_DP.dwNearField;			// nearfield response
		ar >> m_DP.dwFreq30;				// 30 degrees response
		ar >> m_DP.dwFreq60;				// 60 degrees response
		if ( GetSchema() >= 275)
			{
			ar >> m_DP.dwGated;				// Gated
			ar >> m_DP.dwPort;				// Gated
			}
		else
		{
			m_DP.dwGated = 0;
			m_DP.dwPort = 0;
		}

		
		ar >> m_DEq.fRe;
		ar >> m_DEq.fL1a;
		ar >> m_DEq.fR1;
		ar >> m_DEq.fL1b;
		ar >> m_DEq.fR2;
		ar >> m_DEq.fL2;
		ar >> m_DEq.fC2;
		}
}

int   CDriver::EditProperties(CWnd *pParent, CObject * )	// bring up properties dbox
{
CDlgDriver cdlg( pParent);

	ValidateCurves();		// make sure everyone is happy here

	cdlg.m_pDoc = (CAudtestDoc *)GetDocument();
	cdlg.m_dwID = GetID();

	cdlg.UseDriver(this);

	if ( IDOK == cdlg.DoModal())
		{
		CDriver *cgnew = (CDriver *)Duplicate();		// make a copy of "this"
		COpCode *cop;

		if ( cgnew)
			{
			cdlg.SetDriver( cgnew);
			cop = new COpChange( this, cgnew);
			cop->QueueAndDo( );
			return 0;
			}
		}

	return 1;
}



/////////////////////////////////////////////////////////////////////////////
// CDriver diagnostics

#ifdef _DEBUG
void CDriver::AssertValid() const
{
	CGraphed::AssertValid();
}

void CDriver::Dump(CDumpContext& dc) const
{
	CGraphed::Dump(dc);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
CNamed *CDriver::Duplicate(void )
{
CDriver *cnew = new CDriver();

	*cnew = *this;
	return cnew;
}


/////////////////////////////////////////////////////////////////////////////
				// operators
CDriver &CDriver::operator=(const CDriver &cIn)
{
CNamed &cin = (CNamed &)cIn;

	*this = cin;
 	return *this;
}


CNamed &CDriver::operator=(const CNamed &cIn)
{
	CGraphed::operator=( cIn);

	m_DP = ((CDriver &)cIn).m_DP;
	m_DEq = ((CDriver &)cIn).m_DEq;
 					// don't copy the id #
 	return *this;
}

// our network has 7 components
//		  0    1,2    3   4  5  6
//		-Re-+-L1a--+-L1b--+--+--+
//			|-R1---|      |  |  |
//					      R2 L2 C2
//					      |  |  |
//		------------------+--+--+
//
#define NETSIZE 7

static void calc_Impedance( CDataSet *cDest, DRIVEEQUIV& dEq, CDataSet *cTest)
{
	if ( dEq.fRe < 0 || dEq.fL1a < 0 || dEq.fR1 < 0 || dEq.fL1b < 0 || dEq.fR2 <= 0 || dEq.fL2 <= 0 || dEq.fC2 <= 0)
		return;

int ncount;
int i;
ZComplex zcalc, ztest;
ZComplex zc;
double dfreq;

	if ( cTest)
	{
		ncount = cTest->GetCount();
		cDest->CopyHeader( cTest);
	//	*cDest = *cTest;

	//	cDest->SetName( cTest->GetName() + ".Estimate");

		cDest->SetSize( ncount);
	}
	else
		ncount = cDest->GetCount();


	for ( i=0; i<ncount; i++)
		{
		dfreq = 2 * ONEPI * cDest->DataAt( dataFreq, i);
									// R1 | L1a
		zcalc.SetRectangular( dEq.fR1, 0);
		zc.SetRectangular( 0, dfreq*dEq.fL1a);
		zcalc = zc | zcalc;
									// +Re +L1b
		zc.SetRectangular( dEq.fRe, dfreq*dEq.fL1b);			// resistor and inductor in series
		zcalc += zc;
									// + R2| L2| C2
		zc.SetRectangular( dEq.fR2, 0);
		ztest.SetRectangular( 0, dfreq*dEq.fL2);
		ztest = zc | ztest;
		zc.SetRectangular( 0, -1 / (dfreq*dEq.fC2));

		zcalc += zc | ztest;			// now zcalc is the total impedance at this frequency
		cDest->SetRectangular( i, (float )zcalc.XValue(), (float )zcalc.YValue());
		}

}

#if 0
static double calc_Error( DRIVEEQUIV& dEq, CDataSet *cTest)
{
	if ( dEq.fRe < 0 || dEq.fL1a < 0 || dEq.fR1 < 0 || dEq.fL1b < 0 || dEq.fR2 <= 0 || dEq.fL2 <= 0 || dEq.fC2 <= 0)
		return 100000000;

double derr = 0;
ZComplex zcalc, ztest;
ZComplex zc;
double dfreq;
double dx, dy;
double df;
double dfmax = cTest->Maximum( dataFreq);
double dmult;
double dweight;
double dcenter;
			
	dmult = cTest->GetDelta();
	dy = cTest->Minimum(dataFreq)*16;		// take first four octaves for free
	dcenter = sqrt(1/(dEq.fL2 * dEq.fC2)) / (2*ONEPI);	// the center frequency

	for ( df = cTest->Minimum( dataFreq); df < dfmax; df += dmult)
		{
		dweight = dcenter / df;
		if ( dweight > 1.0)	// freq less than center
			{
			dweight = 1 / dweight;	// take 1/ratio
			}
		dweight = sqrt( dweight);	// change the curve shape
		dfreq = 2 * ONEPI * df;
									// R1 | L1a
		zcalc.SetRectangular( dEq.fR1, 0);
		zc.SetRectangular( 0, dfreq*dEq.fL1a);
		zcalc = zc | zcalc;
									// +Re +L1b
		zc.SetRectangular( dEq.fRe, dfreq*dEq.fL1b);			// resistor and inductor in series
		zcalc += zc;
									// + R2| L2| C2
		zc.SetRectangular( dEq.fR2, 0);
		ztest.SetRectangular( 0, dfreq*dEq.fL2);
		ztest = zc | ztest;
		zc.SetRectangular( 0, -1 / (dfreq*dEq.fC2));

		zcalc += zc | ztest;			// now zcalc is the total impedance at this frequency

										// here's the error arithmetic
		dx = zcalc.Amplitude() - cTest->DataValueAt( (float )df);
		dx *= dx * dweight;
		derr += dx;
		dx = (zcalc.Phase() - cTest->PhaseValueAt((float )df)) / 20;		// about a 20:1 ratio between phase and z
		dx *= dx * dweight;
		derr += dx;
					// change the addon for each octave we go
		if ( 2 < (df / dy) )
			{
			dmult += cTest->GetDelta();
			dy = df;
			}
		}

	return derr;
}
#endif

static double calc_ResError( DRIVEEQUIV& dEq, CDataSet *cTest, float fEnd)
{
	if ( dEq.fRe < 0 || dEq.fL1a < 0 || dEq.fR1 < 0 || dEq.fL1b < 0 || dEq.fR2 <= 0 || dEq.fL2 <= 0 || dEq.fC2 <= 0)
		return 100000000;

double derr = 0;
ZComplex zcalc, ztest;
ZComplex zc;
double dfreq;
double dx, dy;
double df;
double dfmax = fEnd;
double dmult;
double dweight;
double dcenter;
			
	dmult = cTest->GetDelta();
	dy = cTest->Minimum(dataFreq)*16;		// take first four octaves same delta
	dcenter = sqrt(1/(dEq.fL2 * dEq.fC2)) / (2*ONEPI);	// the center frequency

	for ( df = cTest->Minimum( dataFreq); df < dfmax; df += dmult)
		{
		dweight = dcenter / df;
		if ( dweight > 1.0)	// freq less than center
			{
			dweight = 1 / dweight;	// take 1/ratio
			}
		dweight = sqrt( dweight);	// change the curve shape
		dfreq = 2 * ONEPI * df;
									// R1 | L1a
		zcalc.SetRectangular( dEq.fR1, 0);
		zc.SetRectangular( 0, dfreq*dEq.fL1a);
		zcalc = zc | zcalc;
									// +Re +L1b
		zc.SetRectangular( dEq.fRe, dfreq*dEq.fL1b);			// resistor and inductor in series
		zcalc += zc;
									// + R2| L2| C2
		zc.SetRectangular( dEq.fR2, 0);
		ztest.SetRectangular( 0, dfreq*dEq.fL2);
		ztest = zc | ztest;
		zc.SetRectangular( 0, -1 / (dfreq*dEq.fC2));

		zcalc += zc | ztest;			// now zcalc is the total impedance at this frequency

										// here's the error arithmetic
		dx = zcalc.Amplitude() - cTest->DataValueAt( (float )df);
		dx *= dx * dweight;
		derr += dx;
		dx = (zcalc.Phase() - cTest->PhaseValueAt((float )df)) / 20;		// about a 20:1 ratio between phase and z
		dx *= dx * dweight;
//		cTest->GetRectangularAt( (float )df, &zc);			// get impedance
//		zcalc -= zc;
//		derr += dweight * zcalc.Amplitude();
		derr += dx;
					// change the addon for each octave we go
		if ( 2 < (df / dy) )
			{
			dmult += cTest->GetDelta();
			dy = df;
			}
		}

	return derr;
}


static double calc_IndError( DRIVEEQUIV& dEq, CDataSet *cTest, float fStart, float fEnd)
{
	if ( dEq.fRe < 0 || dEq.fL1a < 0 || dEq.fR1 < 0 || dEq.fL1b < 0 || dEq.fR2 <= 0 || dEq.fL2 <= 0 || dEq.fC2 <= 0)
		return 100000000;

double derr = 0;
ZComplex zcalc, ztest;
ZComplex zc;
double dfreq;
double dx, dy;
double df;
double dmult;
double dweight;
double dcenter;
			
	dmult = cTest->GetDelta() * 4;			// every four datapoints for now
	dy = fStart * 4;						// start doubling at 2 octaves up
	dcenter = (fStart + fEnd)/( 4 * ONEPI);	// midpoint in radians

	for ( df = fStart; df < fEnd; df += dmult)
		{
//		dweight = dcenter / df;			// weight from center
//		if ( dweight > 1.0)	// freq less than center
//			{
//			dweight = 1 / dweight;	// take 1/ratio
//			}
//		dweight = sqrt( dweight);	// change the curve shape
		dweight = .01;				// constant weighting
		dfreq = 2 * ONEPI * df;
									// R1 | L1a
		zcalc.SetRectangular( dEq.fR1, 0);
		zc.SetRectangular( 0, dfreq*dEq.fL1a);
		zcalc = zc | zcalc;
									// +Re +L1b
		zc.SetRectangular( dEq.fRe, dfreq*dEq.fL1b);			// resistor and inductor in series
		zcalc += zc;
									// + R2| L2| C2
		zc.SetRectangular( dEq.fR2, 0);
		ztest.SetRectangular( 0, dfreq*dEq.fL2);
		ztest = zc | ztest;
		zc.SetRectangular( 0, -1 / (dfreq*dEq.fC2));

		zcalc += zc | ztest;			// now zcalc is the total impedance at this frequency

										// here's the error arithmetic
		dx = zcalc.Amplitude() - cTest->DataValueAt( (float )df);
		dx *= dx * dweight;
		derr += dx;
		dx = (zcalc.Phase() - cTest->PhaseValueAt((float )df)) / 20;		// about a 20:1 ratio between phase and z
		dx *= dx * dweight;
//		cTest->GetRectangularAt( (float )df, &zc);			// get impedance
//		zcalc -= zc;
//		derr += dweight * zcalc.Amplitude();
		derr += dx;
					// change the addon for each octave we go
		if ( 2 < (df / dy) )
			{
			dmult += cTest->GetDelta();
			dy = df;
			}
		}

	return derr;
}

static void calc_Resonant( CDataSet *cFree, DRIVEEQUIV& dEq, BOOL bFixDC, float fEnd)
{
double fdelta[6] = {.001, .001, .000001, .00000001, .000001, .000001};
int ndiv[6] = { 1,1,1,1,1,1 };			// divisors
double fcurerror;
double flast;
// DRIVEEQUIV driveq = m_DEq;
DRIVEEQUIV driveq = dEq;
DRIVEEQUIV dq;			// make a copy of it
int i;
int isize = 6;
bool bdone = FALSE;


	CreateProgressBar( IDS_STATCALC, 150);	// approximately correct in general

	if ( driveq.fRe ) fdelta[0] = driveq.fRe / 10;
	if ( driveq.fR2 ) fdelta[1] = driveq.fR2 / 10;
	if ( driveq.fL2 ) fdelta[2] = driveq.fL2 / 10;
	if ( driveq.fC2 ) fdelta[3] = driveq.fC2 / 10;

	fdelta[4] = fdelta[3];			// change C2
	fdelta[5] = fdelta[3];			// change C2


	if ( bFixDC)
		ndiv[0] = 10;		// automatically we're done with this one
 
	fcurerror = calc_ResError( driveq, cFree, fEnd);
	do
	{
		IncProgressBar();

		flast = fcurerror;
		for ( i=0; i<isize; i++)			// order of importance is inverted
		{
			double fright;

			dq = driveq;			// make a copy of it
			switch( i)
			{
				case 0 : if ( bFixDC)		// do nothing if fixed Dc value
							 continue;
						 dq.fRe += fdelta[i]; 
						 break;
				case 1 : dq.fR2 += fdelta[i]; break;
				case 2 : dq.fL2 += fdelta[i]; break;
				case 3 : dq.fC2 += fdelta[i]; break;
				case 4 : fright = dq.fC2 * dq.fL2;		// keep this fixed
						 dq.fC2 += fdelta[i];
						 dq.fL2 = fright / dq.fC2;		// keeps the product fixed
						 break;
				case 5 : fright = dq.fL2 / dq.fC2;		// keep this fixed
						 dq.fC2 += fdelta[i];
						 dq.fL2 = fright * dq.fC2;		// keeps the quotient fixed
						 break;
				default:
					ASSERT(0);
					break;
			}
			fright = calc_ResError(dq, cFree, fEnd);

			if ( fright >= flast)			// no improvement, try other direction
			{
				switch( i)
				{
					case 0 : if ( bFixDC)		// do nothing if fixed Dc value
								 continue;
							 dq.fRe -= 2 * fdelta[i]; 
							 break;
					case 1 : dq.fR2 -= 2 * fdelta[i]; break;
					case 2 : dq.fL2 -= 2 * fdelta[i]; break;
					case 3 : dq.fC2 -= 2 * fdelta[i]; break;
					case 4 : fright = dq.fC2 * dq.fL2;		// keep this fixed
							 dq.fC2 -= 2 * fdelta[i];
							 dq.fL2 = fright / dq.fC2;		// keeps the product fixed
							 break;
					case 5 : fright = dq.fL2 / dq.fC2;		// keep this fixed
							 dq.fC2 -= 2 * fdelta[i];
							 dq.fL2 = fright * dq.fC2;		// keeps the quotient fixed
							 break;
					default:
						ASSERT(0);
						break;
				}
				fright = calc_ResError(dq, cFree, fEnd);
			}

			if ( fright < (0.99999f * flast))		// improvement
			{
				DBG_INT("added resonant data for %d", i);
				driveq = dq;
				flast = fright;
				if ( ndiv[i] < 8)
					i--;		// do this one again
			}
			else if ( ndiv[i] < 8)						// no improvement, move on
			{
				fdelta[i] /= 2;
				ndiv[i] ++;				// next divisor
			}
		}				// end of for loop

		for ( i=0; i<isize; i++)
			if ( ndiv[i] < 8)
				break;				// 8th fdelta is tiny
		bdone = (i == isize);		// we're done if all ndivs are at least 8

	} while( ! bdone);


	dEq = driveq;

	CloseProgressBar();

}

#if 0
static void oldcalc_Resonant( CDataSet *cFree, DRIVEEQUIV& dEq, BOOL bFixDC, float fEnd)
{
double fdelta[4] = {.001, .001, .000001, .00000001};
double fcurerror;
double flast;
// DRIVEEQUIV driveq = m_DEq;
DRIVEEQUIV driveq = dEq;
DRIVEEQUIV dq;			// make a copy of it
int i;
int isize = 4;
DRIVEEQUIV dq2;


	CreateProgressBar( IDS_STATCALC, 150);	// approximately correct in general

	if ( driveq.fRe ) fdelta[0] = driveq.fRe / 1000;
	if ( driveq.fR2 ) fdelta[1] = driveq.fR2 / 1000;
	if ( driveq.fL2 ) fdelta[2] = driveq.fL2 / 1000;
	if ( driveq.fC2 ) fdelta[3] = driveq.fC2 / 1000;
 
	fcurerror = calc_ResError( driveq, cFree, fEnd);
	do
		{
		IncProgressBar();

		flast = fcurerror;
		for ( i=0; i<isize; i++)			// order of importance is inverted
			{
			double fleft, fright;
			float fnew;

			dq = driveq;			// make a copy of it
			switch( i)
				{
				case 0 : if ( bFixDC)		// do nothing if fixed Dc value
							 continue;
						 dq.fRe += fdelta[i]; 
						 break;
				case 1 : dq.fR2 += fdelta[i]; break;
				case 2 : dq.fL2 += fdelta[i]; break;
				case 3 : dq.fC2 += fdelta[i]; break;
//				case 2 : dq.fC2 /= (dq.fL2 + fdelta[i]) / dq.fL2;  // change Q
//						 dq.fL2 += fdelta[i]; 
//						 break;
//				case 3 : dq.fL2 *= (dq.fC2 + fdelta[i]) / dq.fC2;	// change Resonance
//						 dq.fC2 += fdelta[i]; 
//						 break;
				default:
					ASSERT(0);
					break;
				}
			fright = calc_ResError(dq, cFree, fEnd);
			dq2 = dq;

							// now we have left - us - right
			fnew = 	- (float )( (fright * fdelta[i]) / (20.0f * (fright - fcurerror)) - fdelta[i]);
							// use f(x) / f'(x); the last - is to undo the above change
							// do 1/20th of that requested
			switch( i)
				{
				case 0 : dq.fRe += fnew; break;
				case 1 : dq.fR2 += fnew; break;
				case 2 : dq.fL2 += fnew; break;
				case 3 : dq.fC2 += fnew; break;
//				case 2 : dq.fC2 /= (dq.fL2 + fnew) / dq.fL2;  dq.fL2 += fnew; break;
//				case 3 : dq.fL2 *= (dq.fC2 + fnew) / dq.fC2; dq.fC2 += fnew; break;
				default:
					ASSERT(0);
					break;
				}
			fleft = calc_ResError(dq, cFree, fEnd);
			if ( fleft < fcurerror)				// we did improve!
				{
				DBG_INT("added resonant data for %d", i);
				driveq = dq;
				fcurerror = fleft;
				}
			else if ( fright < fcurerror)		// the test improved it
				{
				DBG_INT("added resonant data A for %d", i);
				driveq = dq2;
				fcurerror = fright;
				}

			}

		} while( (0.9999*flast) > fcurerror);


	dEq = driveq;

	CloseProgressBar();

}
#endif


static void calc_Induct( CDataSet *cFree, DRIVEEQUIV& dEq, BOOL /* bFixDC */, float fStart)
{
double fdelta[3] = {.000001, .000001, .001};
double fcurerror;
double flast;
DRIVEEQUIV driveq = dEq;
DRIVEEQUIV dq;			// make a copy of it
int i;
int isize = 3;
float fend = cFree->Maximum( dataFreq);


	CreateProgressBar( IDS_STATCALC, 150);	// approximately correct in general

	if ( driveq.fL1b) fdelta[0] = driveq.fL1b/ 1000;
	if ( driveq.fL1a) fdelta[1] = driveq.fL1a/ 1000;
	if ( driveq.fR1 ) fdelta[2] = driveq.fR1 / 1000;

	fcurerror = calc_IndError( driveq, cFree, fStart, fend);
	do
		{
		IncProgressBar();

		flast = fcurerror;
		for ( i=0; i<isize; i++)			// order of importance is inverted
			{
			double fleft, fright;
			float fnew;

			dq = driveq;			// make a copy of it
			switch( i)
				{
				case 0 : dq.fL1b += fdelta[i]; break;
				case 1 : dq.fL1a += fdelta[i]; break;
				case 2 : dq.fR1 += fdelta[i]; break;
				default:
					ASSERT(0);
					break;
				}
			fright = calc_IndError(dq, cFree, fStart, fend);

							// now we have left - us - right
			fnew = 	- (float )( (fright * fdelta[i]) / (20.0f * (fright - fcurerror)) - fdelta[i]);
							// use f(x) / f'(x); the last - is to undo the above change
							// do 1/20th of that requested
			switch( i)
				{
				case 0 : dq.fL1b += fnew; break;
				case 1 : dq.fL1a += fnew; break;
				case 2 : dq.fR1 += fnew; break;
				default:
					ASSERT(0);
					break;
				}
			fleft = calc_IndError(dq, cFree, fStart, fend);
			if ( fleft < fcurerror)				// we did improve!
				{
				DBG_INT("added inductive data for %d", i);
				driveq = dq;
				fcurerror = fleft;
				}

			}

		} while( (0.9999*flast) > fcurerror);


	dEq = driveq;

	CloseProgressBar();

}

static int calc_Equiv( CDataSet *cFree, DRIVEEQUIV& dEq, BOOL bFixDC)
{
float fFs;
float fImp;			// where to look for impedance

	if ( dEq.fL2 && dEq.fC2)
		fFs = (float )(sqrt(1/(dEq.fL2 * dEq.fC2)) / (2*ONEPI));
	else
		{
		::AfxMessageBox(IDERR_NOSTART);
		return 1;
		}

					// find next 0 crossing
	if ( ! cFree->WalkValue( fImp, dataPhase, 0, fFs*1.3f, 5))
		{
		::AfxMessageBox(IDERR_NOZERO2);
		return 1;
		}

	calc_Induct( cFree, dEq, bFixDC, fImp);		// get the inductances right

	calc_Resonant( cFree, dEq, bFixDC, fImp);		// get the inductances right

	return 0;


}

#if 0
static void oldcalc_Equiv( CDataSet *cFree, DRIVEEQUIV& dEq, BOOL bFixDC)
{
double fdelta[NETSIZE] = {.000001, .001, .001, .000001, .00000001, .001, .000001};
double fcurerror;
double flast;
// DRIVEEQUIV driveq = m_DEq;
DRIVEEQUIV driveq = dEq;
DRIVEEQUIV dq;			// make a copy of it
int i;


	CreateProgressBar( IDS_STATCALC, 150);	// approximately correct in general

	if ( driveq.fL1b) fdelta[0] = driveq.fL1b/ 1000;
	if ( driveq.fRe ) fdelta[1] = driveq.fRe / 1000;
	if ( driveq.fR2 ) fdelta[2] = driveq.fR2 / 1000;
	if ( driveq.fL2 ) fdelta[3] = driveq.fL2 / 1000;
	if ( driveq.fC2 ) fdelta[4] = driveq.fC2 / 1000;
	if ( driveq.fR1 ) fdelta[5] = driveq.fR1 / 1000;
	if ( driveq.fL1a) fdelta[6] = driveq.fL1a/ 1000;

	fcurerror = calc_Error( driveq, cFree);
	do
		{
		IncProgressBar();

		flast = fcurerror;
		for ( i=0; i<NETSIZE; i++)			// order of importance is inverted
			{
			double fleft, fright;
			float fnew;

			dq = driveq;			// make a copy of it
			switch( i)
				{
				case 0 : dq.fL1b += fdelta[i]; break;
				case 1 : if ( bFixDC)		// do nothing if fixed Dc value
							 continue;
						 dq.fRe += fdelta[i]; 
						 break;
				case 2 : dq.fR2 += fdelta[i]; break;
				case 3 : dq.fC2 /= (dq.fL2 + fdelta[i]) / dq.fL2;  
						 dq.fL2 += fdelta[i]; 
						 break;
				case 4 : dq.fL2 *= (dq.fC2 + fdelta[i]) / dq.fC2; 
						 dq.fC2 += fdelta[i]; 
						 break;
				case 5 : dq.fR1 += fdelta[i]; break;
				case 6 : dq.fL1a += fdelta[i]; break;
				default:
					ASSERT(0);
					break;
				}
			fright = calc_Error(dq, cFree);

							// now we have left - us - right
			fnew = 	- (float )( (fright * fdelta[i]) / (20.0f * (fright - fcurerror)) - fdelta[i]);
							// use f(x) / f'(x); the last - is to undo the above change
							// do 1/20th of that requested
			switch( i)
				{
				case 0 : dq.fL1b += fnew; break;
				case 1 : dq.fRe += fnew; break;
				case 2 : dq.fR2 += fnew; break;
				case 3 : dq.fC2 /= (dq.fL2 + fnew) / dq.fL2;  dq.fL2 += fnew; break;
				case 4 : dq.fL2 *= (dq.fC2 + fnew) / dq.fC2; dq.fC2 += fnew; break;
				case 5 : dq.fR1 += fnew; break;
				case 6 : dq.fL1a += fnew; break;
				default:
					ASSERT(0);
					break;
				}
			fleft = calc_Error(dq, cFree);
			if ( fleft < fcurerror)				// we did improve!
				{
				DBG_INT("added data for %d", i);
				driveq = dq;
				fcurerror = fleft;
				}

//			if( (0.9999*flast) > fcurerror)			// we found a good one, skip onward
//				break;

			}

		} while( (0.9999*flast) > fcurerror);


	dEq = driveq;

	CloseProgressBar();

}


static int calc_Newl( CDataSet *cFree, DRIVEEQUIV& dEq, BOOL bFixDC)
{
double fdelta;
double fcurerror;
double flast;
// DRIVEEQUIV driveq = m_DEq;
DRIVEEQUIV driveq = dEq;
DRIVEEQUIV dq;			// make a copy of it
double ffirstL = driveq.fL2;


	
	CreateProgressBar( IDS_STATCALC, 150);	// approximately correct in general

	if ( driveq.fL2 ) 
		fdelta = driveq.fL2 / 10;
	else
		fdelta = .00001;

	fcurerror = calc_Error( driveq, cFree);
	dq = driveq;			// make a copy of it

	do
		{
		double fright;

			IncProgressBar();

			flast = fcurerror;

			dq.fL2 += fdelta; 
			fright = calc_Error(dq, cFree);
			if ( fright > flast)			// worse off??
			{
				dq.fL2 -= 2*fdelta;
				fright = calc_Error(dq, cFree);
				if ( fright > flast)
				{
					dq.fL2 += fdelta;
					fdelta /= 2;
				}
				else fcurerror = fright;
			}
			else fcurerror = fright;

		} while( (dq.fL2 / fdelta) < 1000.0f);

	dEq = dq;

	CloseProgressBar();

	
	if ( dq.fL2 < (2 * ffirstL) && dq.fL2 > (ffirstL/2))
		return 0;		// success

	return 1;			// failed if L2 changed too much



}
#endif


void CDriver::ConvertDQtoDP( DRIVEPARM &dP, DRIVEEQUIV &dEQ)
{
		dP.fRe = (float )dEQ.fRe;
		dP.fLe = (float )dEQ.fL1b;
		if ( dEQ.fL2 && dEQ.fC2)
			dP.fFs = (float )(sqrt(1/(dEQ.fL2 * dEQ.fC2)) / (2*ONEPI));
		else
			dP.fFs = 1.0f;

		if ( dEQ.fL2)
			dP.fQms = (float )(dEQ.fR2 * sqrt( dEQ.fC2 / dEQ.fL2));
		else
			dP.fQms = 10.0f;

		dP.fQes = dP.fQms * (float )(dEQ.fRe / dEQ.fR2);	// imp at resonance / dc imp
		dP.fQts = (dP.fQes * dP.fQms) / ( dP.fQes + dP.fQms);

}


// get the first approximation
static int calc_First( CDataSet *cFree, DRIVEEQUIV& DEq)
{
float fFs, fQ, fRe, fL1a, fL1b, fR1, fR2;
float flower, fupper;
float fmax;

		fRe = (float )DEq.fRe;		// the only one passed in the structure

						// find zero phase crossing to get Fs first shot
		if ( ! cFree->WalkValue( fFs, dataPhase, 0, 5, 5))
			{
			::AfxMessageBox(IDERR_NOZERO);
			return 1;
			}
						// real impedance at resonance is ~R2 - Re (later calc)
		fR2 = cFree->DataValueAt( fFs);
						// find -6db points to get Q - mech Q is 1/sqrt(2) * max impedance
		if( ! cFree->WalkValue( flower, dataAmp, fRe + .707f*(fR2-fRe), fFs, -1))
			{
			::AfxMessageBox(IDERR_NOPEAK);
			return 2;
			}
		if( ! cFree->WalkValue( fupper, dataAmp, fRe + .707f*(fR2-fRe), fFs, 1))
			{
			::AfxMessageBox(IDERR_NOPEAK);
			return 3;
			}

		fQ = fFs / ( fupper - flower);


							// now estimate the upper impedances
							// approximate L1b and R1 by looking at high frequency impedance
 		fmax = cFree->Maximum( dataFreq);
		{
		int i;
		float fx, fy;
		float ffreq;
		int ntotal = 100;
		
			fR1 = 0;
			fL1b = 0;
			for ( i=0; i<ntotal; i++)			// sample 10 data points in the upper scale
				{
				ffreq = fmax - (i+10) * cFree->GetDelta();	// make sure this is an even match
				cFree->GetRectangularAt( ffreq, &fx, &fy);
				fR1 += fx;
				fL1b += fy / ffreq;		// normalize to an inductance
				}

			fR1 = fR1 / ntotal - fRe;		// estimate for R1 is real part w/out Re
			if ( fR1 < 0)
				fR1 = 5;				// random guess in this case
			fL1b /= (float )(2 * ONEPI * ntotal);	// estimate for L1b is similarly imaginary part
		}

						// now estimate L1a by looking a bit lower
						// now start finding inductance when angle > 10
		if ( ! cFree->WalkValue( fupper, dataPhase, 10, 2*fFs, 1))
			{
			::AfxMessageBox(IDERR_NORISE);
			return 4;
			}

		{
		int i;
		float fx, fy;
		float ffreq;
		int ntotal = 100;
		
			fL1a = 0;
			for ( i=0; i<ntotal; i++)			// sample 10 data points in the upper scale
				{
				ffreq = fupper + i * cFree->GetDelta();	// make sure this is an even match
				cFree->GetRectangularAt( ffreq, &fx, &fy);
//				fy -= (float )(fL1b * 2 * ONEPI * ffreq);		// subtract off the l1b component
													// now it's L || R for which values?
				fL1a += fy / ffreq;					// normalize to an inductance
							// here we assume that R is greater than the impedance due to L by a lot
				}
			fL1a = fL1a / (float )( 2 * ONEPI * ntotal );	// estimate for L1b is similarly imaginary part
		}




		DEq.fRe= fRe;
		DEq.fR1 = fR1;
		DEq.fL1b = fL1b;
		DEq.fL1a= fL1a;
		DEq.fR2= fR2 - fRe;				// this is approx the impedance of the parallel resistor
		DEq.fL2= DEq.fR2 / (2 * ONEPI * fFs * fQ);
		DEq.fC2= fQ / (2 * ONEPI * fFs * DEq.fR2);

		return 0;
}



/////////////////////////////////////////////////////////////////////////////
//		CalculateDriverParameters - the nonwindowed version
/////////////////////////////////////////////////////////////////////////////
int CDriver::CalculateDriverParameters( CDataSet *cDest, bool bDoFree) 
{
CDataSet *cdata = NULL;
float fs, fe;

	if ( GetFreeAir())
		{
		cdata = (CDataSet *)FindByID( GetFreeAir());
		fs = cdata->Minimum( dataFreq);
		fe = cdata->Maximum( dataFreq);
		return CalculateDriverParameters( cDest, bDoFree, fs, fe);
		}

	return 1;

}


// truncate a dataset to fmin and fmax
static void truncate_Data( CDataSet *cData, float fStart, float fEnd)
{
					// truncate to the window dimension
int i;
int nmin, nmax;

	nmin = cData->FreqToIndex( fStart);
	nmax = cData->FreqToIndex( fEnd);

	if ( nmin)		// we need to move stuff down
		for ( i=nmin; i<nmax; i++)
			{
			cData->SetDataAt( i-nmin, cData->GetDataAt( i));
			cData->SetPhaseAt( i-nmin, cData->GetPhaseAt( i));
			cData->SetStart( fStart);
			}
	cData->SetSize( nmax - nmin);
}


/////////////////////////////////////////////////////////////////////////////
//		CalculateDriverParameters - the windowed version
/////////////////////////////////////////////////////////////////////////////
int CDriver::CalculateDriverParameters( CDataSet *cDest, bool bDoFree, float fStart, float fEnd) 
{
CDataSet *cdata = NULL;
CDataSet *cfree = NULL;
float fFc;
BOOL	bfixdc;			// is dc fixed by user????

		if ( ValidateResponse( rsFreeAir) || ! GetFreeAir())	// make sure we have a valid free air response
			{
			::AfxMessageBox(IDERR_NOFREEAIR);
			return 1;
			}

		cfree = (CDataSet *)FindByID( GetFreeAir());

		_ASSERT( cfree != NULL);		// no way

		bfixdc = GetDriverParameters()->bUseDC;

						// ------------------- First shot approximations
		if ( bDoFree)
		{
		DRIVEEQUIV dq;			// make a copy of it
		DRIVEPARM  dp;
						// now make a truncated version of cfre for the optimization steps
			cdata = (CDataSet *)cfree->Duplicate();		// make a copy
			dq = m_DEq;
			dp = m_DP;

			truncate_Data( cdata, fStart, fEnd);

			{
			const DRIVEPARM *pdp = GetDriverParameters();

				if ( bfixdc)
					{
					dq.fRe = pdp->fDCRes;					// use user given DC resistance
					}
				else
					{
					dq.fRe = cdata->Minimum( dataAmp);		// first approx at dc resistance
					}
			}

			if ( calc_First( cdata, dq))			// calc first failed verbosely
			{
				delete cdata;
				return 1;
			}

			if ( calc_Equiv( cdata, dq, bfixdc))	// similarly
			{
				delete cdata;
				return 1;
			}

			ConvertDQtoDP( dp, dq);

			m_DEq = dq;
			m_DP = dp;				// save them, everything worked

			delete cdata;
		}
				// calculate vas if we can

		if ( ! m_DP.bUseMass)
		{
			if ( GetSealed())
			{
				CDataSet *csealed;
				csealed = (CDataSet *)FindByID( GetSealed());
				if ( csealed)										// find zero phase crossing to get Fs first shot
				{
					DRIVEEQUIV dq;			// make a copy of it
					DRIVEPARM  dp;

					cdata = (CDataSet *)csealed->Duplicate();		// make a copy

					truncate_Data( cdata, fStart, fEnd);

					dq.fRe = m_DEq.fRe;					// use user given DC resistance

					if ( calc_First( cdata, dq))			// calc first failed verbosely
						{
							delete cdata;
							return 1;
						}

					if ( calc_Equiv( cdata, dq, bfixdc))		// find whole new chart
						{
							delete cdata;
							return 1;
						}

					delete cdata;

					ConvertDQtoDP( dp, dq);

					m_DP.fVas = m_DP.fVolume * (( dp.fFs * dp.fQes) / ( m_DP.fFs * m_DP.fQes) - 1);	// from Small
					fFc = ( dp.fFs * m_DP.fQes) / ( m_DP.fFs * dp.fQes);  // should be between 0.8 and 0.95 "

				}
			}
			else
				::AfxMessageBox(IDS_ERR_NOVAS);
			}
		else			// use added mass technique
		{
			if ( GetAddMass())
			{
				CDataSet *cmass;
				cmass = (CDataSet *)FindByID( GetAddMass());
				if ( cmass)										// find zero phase crossing to get Fs first shot
				{
					DRIVEEQUIV dq;			// make a copy of it
					DRIVEPARM  dp;

					cdata = (CDataSet *)cmass->Duplicate();		// make a copy

					truncate_Data( cdata, fStart, fEnd);

					dq.fRe = m_DEq.fRe;					// use user given DC resistance
					if ( calc_First( cdata, dq))			// calc first failed verbosely
						{
							delete cdata;
							return 1;
						}

					if ( calc_Equiv( cdata, dq, bfixdc))		// find whole new chart
						{
							delete cdata;
							return 1;
						}

					delete cdata;

					ConvertDQtoDP( dp, dq);
								// this is from Benson p.66
					if ( dp.fFs > m_DP.fFs)
					{
						::AfxMessageBox( IDERR_MASSBIG);
					}
					else
					if ( m_DP.fPistonArea <= 0.0f)
					{
						::AfxMessageBox( IDERR_NOPISTON);
					}
					else
					{
						double dconemass, dcms;
									// mass is in grams
						dconemass = m_DP.fMass / ((m_DP.fFs / dp.fFs) * (m_DP.fFs / dp.fFs) - 1 );
									// now based on the Q values we can calculate compliance
						dcms = 1 / ( m_DP.fFs * m_DP.fFs * dconemass);		// from eq 9 p 66
						dcms /= (4 * ONEPI * ONEPI);		// since we wanted radians
									// finally vas is proportional to cms
									// piston area is in m*m
						m_DP.fVas = (float )(dcms * m_DP.fPistonArea * m_DP.fPistonArea * 1200 * 344 * 344);
									// where R0 = 1200 gram/m*m
									// C is 344 m/s
									// we want vas in m*m*m
					}
				}
			}
			else
			{
				::AfxMessageBox(IDS_ERR_NOVAS);
			}
		}

		calc_Impedance( cDest, m_DEq, cfree);

		SetLastEdit();

		return 0;

}


/////////////////////////////////////////////////////////////////////////////
//		CalculateDriverParameters - the windowed version
/////////////////////////////////////////////////////////////////////////////
int CDriver::UseDriverEquiv( CDataSet *cDest, DRIVEEQUIV &DQ) 
{
CDataSet *cfree = NULL;

	if (  GetFreeAir())
	{
	cfree = (CDataSet *)FindByID( GetFreeAir());

	_ASSERT( cfree != NULL);		// no way
	}

	SetDriverEquiv( &DQ);
	ConvertDQtoDP( m_DP, DQ);

	calc_Impedance( cDest, DQ, cfree);

	SetLastEdit();

	return 0;

}

int		CDriver::ValidateResponse( int nWhich)
{
DWORD dwid = GetResponse( nWhich);		// get the response chart
CDataSet *pdata;
UNITMSR uom;

	if ( ! dwid)
		return 0;			// valid OK
							// make sure we have it in the tree
	pdata = (CDataSet *)FindByID( dwid);

	if ( pdata == NULL)
		return 1;		// invalid, no dataset here

						// make sure it is a named object
	if ( ! pdata->IsKindOf(RUNTIME_CLASS( CNamed)))
		return 2;		// it isn't a named object!

	switch( nWhich)			// depending on kind of dataset
		{
		case rsResponse :
		case rsNearField :
		case rsFreq30 :
		case rsFreq60 :
			uom = uomFreq;
			break;
		case rsImpedance :
		case rsFreeAir :
		case rsSealed :
		case rsAddMass :
			uom = uomOhms;
			break;
		case rsTimeRes :
			uom = uomTime;
			break;
		default :
			_ASSERT( 0);
			return 3;
		}

	if ( ! pdata->IsType( ntDataSet, uom))		// must be a freq chart
		return 3;

	return 0;		// AOK

}


void	CDriver::ValidateCurves( void)
{
int i;

	for ( i=0; i<NUM_RESPONSES; i++)
		if ( ValidateResponse( i))		// dwResponse off
			SetResponse(i,0);

}


void	CDriver::SetResponse(int nWhich, DWORD dwNew)
{
	switch( nWhich)
		{
		case rsResponse :
			 m_DP.dwResponse = dwNew;
			break;
		case rsFreq30 :
			 m_DP.dwFreq30 = dwNew;
			break;
		case rsFreq60 :
			 m_DP.dwFreq60 = dwNew;
			break;
		case rsNearField :
			 m_DP.dwNearField = dwNew;
			break;
		case rsImpedance :
			 m_DP.dwImpedance = dwNew;
			break;
		case rsFreeAir :
			 m_DP.dwFreeAir = dwNew;
			break;
		case rsSealed :
			 m_DP.dwSealed = dwNew;
			break;
		case rsAddMass :
			 m_DP.dwAddMass = dwNew;
			break;
		case rsTimeRes :
			 m_DP.dwTimeRes = dwNew;
			break;
		case rsGated :
			 m_DP.dwGated = dwNew;
			break;
		case rsPort :
			 m_DP.dwPort = dwNew;
			break;
		default:
			_ASSERT(0);
			break;
		}

}

DWORD	CDriver::GetResponse(int nWhich)
{
	switch( nWhich)
		{
		case rsResponse :
			return m_DP.dwResponse;
		case rsFreq30 :
			return m_DP.dwFreq30;
		case rsFreq60 :
			return m_DP.dwFreq60;
		case rsNearField :
			return m_DP.dwNearField;
		case rsImpedance :
			return m_DP.dwImpedance;
		case rsFreeAir :
			return m_DP.dwFreeAir;
		case rsSealed :
			return m_DP.dwSealed;
		case rsAddMass :
			return m_DP.dwAddMass;
		case rsTimeRes :
			return m_DP.dwTimeRes;
		case rsGated :
			return m_DP.dwGated;
		case rsPort :
			return m_DP.dwPort;
		default:
			return 0;
		}
}

// ---------------------------------------------------------------------------------------
// ---------		CreateChart
// ---------------------------------------------------------------------------------------

BOOL	CDriver::CreateChart( CNamed * /* cBase */)			// build a new chart object to be graphed
{
CSubChart *cch;

	ValidateCurves();		// here is our first chance to validate stuff

					// build the chart
	if ( GetResponse() || GetResponse( rsImpedance))
		{
		cch = new CSubChart();
		cch->SetRootObject( GetRootObject());			// since it doesn't get added to the tree
		cch->CreateDefault( GetName(), uomFreq);
		if ( GetResponse( ))
			cch->Attach( GetResponse(), FALSE);			// don't use the phase for this guy
		if ( GetResponse( rsImpedance))
			cch->Attach( GetResponse(rsImpedance), FALSE);			// don't use the phase for this guy
		SetChart( cch);
		delete cch;
		}
	else
		SetChart( NULL);		// delete any old chart

	return TRUE;
}



