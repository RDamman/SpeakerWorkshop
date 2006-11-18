// XformGoal.cpp: implementation of the CXformGoal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "audtest.h"

#include "XformGoal.h"
#include "Network.h"
#include "Driver.h"
#include "Dataset.h"
#include "Passive.h"
#include "math.h"
#include "complex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXformGoal::CXformGoal(CObject *cTarget) : CXtransform( cTarget)
{

}

CXformGoal::~CXformGoal()
{

}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

// --------------------------------------------------------------------
//		eval_LPoly
//			evalue the low-pass polynomial
// --------------------------------------------------------------------
static ZComplex eval_LPoly( double *pPoly, double dFreq, int nOrder)
{
ZComplex cp(0.0,0.0);			// init to 0

	cp	+= ZComplex(pPoly[0], 0.0);		// real constant

	cp += ZComplex( 0.0, dFreq * pPoly[1]);		// ones constant
	if ( nOrder == 1)
		return cp;

	cp -= ZComplex( dFreq * dFreq * pPoly[2], 0.0);
	if ( nOrder == 2)
		return cp;

	cp -= ZComplex( 0.0, dFreq * dFreq * dFreq * pPoly[3]);
	if ( nOrder == 3)
		return cp;

	cp += ZComplex( dFreq * dFreq * dFreq * dFreq * pPoly[4], 0.0);

	return cp;			// 4th order
}

// --------------------------------------------------------------------
//		eval_LPoly
//			evalue the low-pass polynomial
// --------------------------------------------------------------------
static ZComplex eval_HPoly( double *pPoly, double dFreq, int nOrder)
{
ZComplex cp(0.0,0.0);			// init to 0
int iindex;

	iindex = nOrder;		// start at the other end

	cp	+= ZComplex(pPoly[iindex], 0.0);		// real constant

	cp += ZComplex( 0.0, -pPoly[iindex-1] / dFreq);		// ones constant
	if ( nOrder == 1)
		return cp;

	cp -= ZComplex( pPoly[iindex-2] / (dFreq * dFreq), 0.0);
	if ( nOrder == 2)
		return cp;

	cp -= ZComplex( 0.0, -pPoly[iindex-3] / (dFreq * dFreq * dFreq));
	if ( nOrder == 3)
		return cp;

	cp += ZComplex( pPoly[iindex-4] / (dFreq * dFreq * dFreq * dFreq), 0.0);

	return cp;			// 4th order
}

// --------------------------------------------------------------------
//		GenPoly
//	note the filters are always in alphabetical order
// --------------------------------------------------------------------
void	CXformGoal::GenPoly( double *pPoly)
{
	pPoly[0] = 1.0;			// first one is always 1
	pPoly[m_nOrder] = 1.0;	// last one is always 1
	switch( m_nOrder)
	{
	case 1 :
		break;				// butterworth first order is 1,1
	case 2 :
		switch( m_nType)
		{
		case xoBessel :					// bessel
			pPoly[1] = sqrt(3.0);
			break;
		case xoButterworth :			// butterworth 2nd order
			pPoly[1] = sqrt(2.0);
			break;
		case xoChebychev :				// chebychev 2nd order
			pPoly[1] = 1.0;
			break;
		case xoLinkwitz :				// lr
			pPoly[1] = 2.0;
			break;
		default :
			break;
		}
		break;
	case 3 :
		pPoly[2] = 2.0;
		pPoly[1] = 2.0;		// butterworth 3rd order
		break;
	case 4 :
		switch( m_nType)
		{
		case xoBessel :				// bessel
			pPoly[1] = 3.201;
			pPoly[2] = 4.392;
			pPoly[3] = 3.124;
			break;
		case xoButterworth :		// butterworth 4th order
			pPoly[1] = 2.613;
			pPoly[2] = 3.414;
			pPoly[3] = pPoly[1];
			break;
		case xoGaussian :			// Gaussian
			break;
		case xoLegendre :			// Legendre
			break;
		case xoLinear :				// Linear-Phase
			break;
		case xoLinkwitz :			// lr
			pPoly[1] = 2.0 * sqrt(2.0);
			pPoly[2] = 4.0;
			pPoly[3] = pPoly[1];		// symmetric
			break;
		default :
			break;
		}
		break;
	default :
		break;
	}

}

// --------------------------------------------------------------------
//		DoOperation
// --------------------------------------------------------------------
int CXformGoal::DoOperation( CNamed *cdDest)	// xeq xform
{
CNetwork *cname;
float fmatch;
CDataSet *pdata = (CDataSet *)cdDest;
CDataSet *presponse = NULL;

	if ( 4 == m_nOrder)
	{
		switch( m_nType)
		{
		case xoGaussian :			// Gaussian
		case xoLegendre :			// Legendre
		case xoLinear :				// Linear-Phase
			AfxMessageBox(IDS_UNDERCONSTRUCT, MB_OK);
			m_nType = xoLinkwitz;
			break;
		default :
			break;
		}
	}

	cname = (CNetwork *)FindTargetObject();

	if ( ! cname)
		return 1;

	if ( (m_isUseWhich == sglDriver) && m_dwDriver)			// we want to match to a driver's frequency response
	{
	CDriver *pdrive;

		pdrive = (CDriver *)cname->FindByID( m_dwDriver);
		if ( pdrive && (ntDriver == pdrive->GetType()))	// yes, it really is a driver
		{
		DWORD dwresponse = pdrive->GetResponse();
			if ( dwresponse)
			{
			presponse = (CDataSet *)cname->FindByID( dwresponse);
			}
		}
	}

	if ( (m_isUseWhich == sglData) && m_dwDataset)			// we want to match to a dataset
	{
		presponse = (CDataSet *)cname->FindByID( m_dwDataset);
	}

	if ( presponse && presponse->IsType(ntDataSet, uomFreq))	// yes, it really is a response
	{
	int istart, iend;
	int i;
	double dtotal = 0;
		istart = presponse->FreqToIndex( m_fStart);
		iend = presponse->FreqToIndex( m_fEnd);
		if ( istart > iend)
			iend = istart + 1;
		for ( i=istart; i<iend; i++)
			dtotal += presponse->DataValueAt( i, 1);			// the matching value
		fmatch = (float )(dtotal / (iend - istart));
	}
	else
		fmatch = (float )pow( 10.0f, m_fValue / 20);				// convert from dbW

	pdata->SetDOM( 	uomDbw);
	pdata->SetUOM(  uomFreq);
	pdata->SetDelta( 19.0f);
	pdata->SetStart( 20.0f);
	pdata->SetSize( 1024, 1024);			// phase and magnitude

				// here's where we actually set the data up for the goal based
				// on the crossover type selected
	if ( m_nOrder)			// not flat
	{
	int i;
	double dpoly[10];				// we never have more than 5 elements for 4th order
	double dfreq;

		GenPoly( dpoly);			// make the lowpass denominator polynomial

		for ( i=0; i<pdata->GetCount(); i++)
		{
		ZComplex cp;

			dfreq = pdata->DataAt( dataFreq, i) / m_fFS;		// get the frequency
			if ( m_nHighLow)		// lowpass?
				cp = eval_LPoly( dpoly, dfreq, m_nOrder);		// evaluate the polynomial (normalized)
			else
				cp = eval_HPoly( dpoly, dfreq, m_nOrder);		// evaluate the polynomial (normalized)
			cp = ZComplex(fmatch,0.0) / cp;			// invert it
			pdata->SetRectangular( i, (float )cp.XValue(), (float )cp.YValue() );
		}

	}
	else			// it's flat, just build a straight line
	{
	int i;

		for ( i=0; i<pdata->GetCount(); i++)
		{
			pdata->SetRectangular( i, fmatch, 0 );
		}

	}

	cname->UpdateViews();


return 0;

}


