// speaker.cpp : implementation of the CDataSetArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include "complex.h"
#include "zFormEdt.h"
#include "dataset.h"
#include "xform.h"

#include <math.h>

#include "filter.h"

#include "dlgFilte.h"

#include "Utils.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

typedef struct tagFilterinfo
	{
	int 	nNotUsed	;
	int 	nShape	;
	int 	nType	;
	int 	nOrder	;
	float	fLowFreq;
	float	fHiFreq;
	float	fRipple;		// attenuation in db
	} FILTERINFO;


CXtFilter::CXtFilter( CObject *cTarget, float *ftPoly, int nTotal) : CXunary( cTarget), 
							m_cPolynomial(), m_cPolyLow(), m_cFreqPoly(), m_cFreqPolyLow()
{
float fx;
int i;
FILTERINFO fi;
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	m_cPolynomial.SetSize(0, 20);
	m_cPolyLow.SetSize(0, 20);
	m_cFreqPoly.SetSize(0, 20);
	m_cFreqPolyLow.SetSize(0, 20);

	m_pDenominator = NULL;
	m_pNumerator = NULL;
	m_pPrevInput = NULL;
	m_pPrevOutput = NULL;

	if ( capp->ReadRegistry( IDS_FILTERINFO, &fi, sizeof(fi)) )	// failed???
		{
		m_nShape	=	0	;
		m_nType		=	0;
		m_nOrder	=	2	;	
		m_fLowFreq	=	1000.0f;
		m_fHiFreq	=	1200.0f;
		m_fRipple = 	1.0f;
		}
	else
		{
		m_nShape	=	fi.nShape	;
		m_nType		=	fi.nType;
		m_nOrder	=	fi.nOrder	;	
		m_fLowFreq  = 	fi.fLowFreq;
		m_fHiFreq = 	fi.fHiFreq;
		m_fRipple = 	fi.fRipple;
		}


	if ( ftPoly)
		{
		fx = *ftPoly++;
		for ( i = 0; i<nTotal; i++)
			{
			m_cPolynomial.Add( fx);
	 		fx = *ftPoly;
			}
		}
/*
	if ( ftLow)
		{
		fx = *ftLow++;
		for ( ; (fx != (float )0); ftLow++)
			{
			m_cPolyLow.Add( fx);
	 		fx = *ftLow;
			}
		}
  */
}

CXtFilter::~CXtFilter()
{
	if ( m_pDenominator)
		delete [] m_pDenominator;
	if ( m_pNumerator)
		delete [] m_pNumerator;
	if ( m_pPrevInput)
		delete [] m_pPrevInput;
	if ( m_pPrevOutput)
		delete [] m_pPrevOutput;

}



UINT CXtFilter::DoDialog( )		// xeq dbox
{
CDlgFilter cdlg;
UINT uout;

				// fill the function with defaults for this dataset
	cdlg.m_nShape	=	m_nShape	;
	cdlg.m_nType	=	m_nType	;
	cdlg.m_nOrder	=	m_nOrder	;
	cdlg.m_fLowFreq	=	m_fLowFreq	;
	cdlg.m_fHiFreq	=	m_fHiFreq	;
	cdlg.m_fRipple = 	m_fRipple;

	uout = cdlg.DoModal();

	if ( IDOK == uout)
		{
		FILTERINFO fi;
		CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		m_nShape	=	cdlg.m_nShape	;
		m_nType		=	cdlg.m_nType	;
		m_nOrder	=	cdlg.m_nOrder	;
		m_fLowFreq	=	cdlg.m_fLowFreq	;
		m_fHiFreq	=	cdlg.m_fHiFreq	;
		m_fRipple = 	cdlg.m_fRipple;

		fi.nShape	=		cdlg.m_nShape	;
		fi.nType		=	cdlg.m_nType	;
		fi.nOrder	=		cdlg.m_nOrder	;
		fi.fLowFreq	=	cdlg.m_fLowFreq	;
		fi.fHiFreq	=	cdlg.m_fHiFreq	;
		fi.fRipple = 	cdlg.m_fRipple;
		capp->WriteRegistry( IDS_FILTERINFO, &fi, sizeof(fi));

					// these may have been initialized at Transform create time
		m_cPolynomial.SetSize(0, 40);
		m_cPolyLow.SetSize(0, 40);
		m_cFreqPoly.SetSize(0, 40);
		m_cFreqPolyLow.SetSize(0, 40);

//		Calc_Variables();
		}

	return uout;

}

// create a low pass bessel filter based at 1Hz
// uses the recurrence relation where bn = (2n-1)bn-1 + s**2bn-2
// this is actually only used by the time domain filter
// the frequency one does it recursively for better stability
int CXtFilter::CreateBessel( void)
{
int i, nord, nsize;
double *fa, *fb;
double *fc;			// temp storage
ZComplex zc;
int nt;

	nsize = 1 + m_nOrder;		// 0...N
	fa = new double [ nsize];
	fb = new double [ nsize];
	for ( i=0; i<nsize; i++)	// zero initialize
		{
		fa[i] = 0.0;
		fb[i] = 0.0;
		}
	fa[0] = 1.0;			// b0 = 1
	fb[0] = 1.0;			// b1 = 1 + s
	fb[1] = 1.0;

	m_cFreqPoly.SetSize( nsize);
	m_cFreqPolyLow.SetSize( nsize);

	for ( nord = 2; nord <= m_nOrder; nord++)
		{			// here fa is bn-2 and fb is bn-1
		nt = 2 * nord - 1;			// temp storage for 2n-1 - note our nord is one less than n
		for ( i = (nsize-1); i>1; i--)
			{				//	multiply by 2n-1
			fa[i] = fa[i-2] + nt * fb[i];
			}
		fa[1] = nt * fb[1];
		fa[0] = nt * fb[0];			// no corresponding fa term
		fc = fa;
		fa = fb;
		fb = fc;		// switch the pointers around
		}

	for ( i=0; i<nsize; i++)
		{
		zc.SetRectangular( i ? 0.0 : fb[0], 0.0);	// zeroth entry is a 1, others are 0
		m_cFreqPoly.SetAt(i, zc);
		zc.SetRectangular( fb[i], 0.0);			// use fb[i] as the current settings
		m_cFreqPolyLow.SetAt(i, zc);
		}

	delete [] fa;
	delete [] fb;

	return 0;

}

int CXtFilter::CreateButter( void)
{
ZComplex zc;
int i;
double theta;

	m_cFreqPolyLow.SetSize( m_nOrder, 1);
	m_cFreqPoly.SetSize( 1, 1);
				// use m_cFreqPoly and m_cFreqPolyLow to make the final m_cFreqPolyLow
	for ( i=1; i<=m_nOrder; i++)
		{		// calc sigma(i) and w(i)
		theta = (2 * i - 1) * ONEPI / (2 * m_nOrder);
		zc.SetRectangular( -sin(theta), cos(theta) );
		m_cFreqPolyLow.SetAt(i-1, zc);
		}

	return 0;
}

static double arc_sinh( double x)
{
	return log( x + sqrt( x * x + 1));
}

static double arc_cosh( double x)
{
	if ( x > 1)
		return log( x + sqrt(x * x - 1));
	else
		return 0;
}

int CXtFilter::CreateCheby( void)
{
ZComplex zc;
int i;
double theta;
double dsigma, dw;		// the correction for ripple

	m_cFreqPolyLow.SetSize( m_nOrder, 1);
	m_cFreqPoly.SetSize( 1, 1);

	if ( m_fRipple > 0)
		{
		double epsilon = sqrt( pow(10.0, m_fRipple / 10.0) - 1 );
		double tsi = (1.0 / m_nOrder) * arc_sinh( 1 / epsilon);
		dsigma = sinh( tsi);
		dw = cosh( tsi);
		double d3db = cosh( (1.0 / m_nOrder) * arc_cosh( 1 / epsilon) );	// switch to 3db point
		dsigma /= d3db;
		dw /= d3db;
		}
	else
		{
		dsigma = 1.0;
		dw = 1.0;
		}

				// use m_cFreqPoly and m_cFreqPolyLow to make the final m_cFreqPolyLow
	for ( i=1; i<=m_nOrder; i++)
		{		// calc sigma(i) and w(i)
		theta = (2 * i - 1) * ONEPI / (2 * m_nOrder);
		zc.SetRectangular( -dsigma * sin(theta), dw * cos(theta) );
		m_cFreqPolyLow.SetAt(i-1, zc);
		}

	return 0;
}


// create the filter as an S transform - setting the two float arrays
int CXtFilter::CreateFilter( void)
{
	m_cFreqPoly.SetSize( 0, 20);
	m_cFreqPolyLow.SetSize(0, 20);		// empty the polynomials

	switch( m_nShape)
		{
		case 0 :			// bessel
			return CreateBessel( );
		case 1 :			// butterworth
			return CreateButter( );
		case 2 :			// chebychev with ripple
		case 3 :			// 
			return CreateCheby();
		default:
			break;
		}

	return 0;
}


// execute a bessel filter
// this uses an iterative procedure akin to the bessel creation procedure
// see notes in "doc for audtest.doc"
int CXtFilter::FilterBessel( ZComplex& zSource, ZComplex& zOmega)
{				// use m_cFreqPoly and m_cFreqPolyLow to make the final m_cFreqPolyLow
ZComplex z0;
ZComplex z1;
ZComplex zn;
double dtemp;
int i;

	z0.SetRectangular( 1.0, 0);
	z1 = z0 + zOmega;		// b1(s) = 1 + s

	for ( i=2; i<=m_nOrder; i++)
		{				// calc s**2/(2n-1)(2n-3)
		dtemp = 1.0 / ((2 * i - 1) * (2 * i - 3));
						// multiply bn-2 by the constant
		z0.SetRectangular( z0.XValue() * dtemp, z0.YValue() * dtemp);
		z0 = z0 * zOmega * zOmega;
		zn = z1 -  z0;		// now bn = bn-1 - new bn-2 
		z0 = z1;			// move them along
		z1 = zn;
		}

	zSource /= z1;			// apply the multiplier

	return 0;


}

// execute a butterworth filter
int CXtFilter::FilterButter( ZComplex& zSource, ZComplex& zOmega)
{
ZComplex ztotal(1.0, 0.0);		// the denominator
ZComplex ztemp, zpart;
int i;

	for ( i=1; i<=m_nOrder/2; i++)		// for each quadratic section
		{
		ztemp = m_cFreqPolyLow.GetAt(i-1);		// get sigma and w(i)
					// s**2 + 2 sigma s + 1
		zpart.SetRectangular( 1.0, 0.0);		// start with real 1,0
		zpart = zpart + zOmega * zOmega + zOmega * (2 * ztemp.XValue());
		ztotal *= zpart;		// put into the stew
		}
	if ( m_nOrder != 2 * (int )(m_nOrder/2))			// odd
		{
		ztemp.SetRectangular( 1.0, 0.0);				// multiply by 1+s
		ztemp += zOmega;
		ztotal *= ztemp;
		}

	zSource /= ztotal;			// modify the supplied data
	return 0;


}

// execute a chebychev filter
int CXtFilter::FilterCheby( ZComplex& zSource, ZComplex& zOmega)
{
ZComplex ztotal(1.0, 0.0);		// the denominator
ZComplex ztemp, zpart;
int i;
double dtemp;

	for ( i=1; i<=m_nOrder/2; i++)		// for each quadratic section
		{
		ztemp = m_cFreqPolyLow.GetAt(i-1);		// get sigma and w(i)
					// the real part is w**2+sigma**2-f**2
					// the imaginary part is 2 sigma f
		dtemp = ztemp.XValue() * ztemp.XValue() + ztemp.YValue() * ztemp.YValue();
		zpart.SetRectangular(dtemp , 0.0);		// start with real 1,0
		zpart = zpart + zOmega * zOmega + zOmega * (2 * ztemp.XValue());
		zpart = zpart * ( 1 / dtemp);			// normalize
		ztotal *= zpart;		// put into the stew
		}
	if ( m_nOrder != 2 * (int )(m_nOrder/2))			// odd
		{
		ztemp = m_cFreqPolyLow.GetAt(i-1);				// get the center data (sinh tsi)
		zpart.SetRectangular(1.0,0);
		zpart = zpart + zOmega * ( 1 / ztemp.XValue());	// use 1/sinh tsi to normalize
		ztotal *= zpart;											// note w is 0
		}

	zSource /= ztotal;			// modify the supplied data
	return 0;

}

// this filters frequency data
int CXtFilter::FilterFrequency()
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
float ffreq;
ZComplex zc;
int i;
ZComplex omega;
double dgamma, d0;


	for ( i=0; i<cdSource->GetCount(); i++)
		{
		ffreq = cdSource->DataAt( dataFreq, i);
		cdSource->GetRectangularAt( ffreq, &zc);
		ShowProgressBar( 10 + (int )(90 * i)/cdSource->GetCount() );		// 10% done
						// now we have the source data and the frequency
		switch( m_nType)
			{
			case 0 :			 // lowpass
				omega.SetRectangular( 0.0, ffreq / m_fLowFreq);
				break;
			case 1 :			 // highpass
				omega.SetRectangular( 0.0, - m_fLowFreq / ffreq);
				break;
			case 2 :			 // bandpass
				d0 = sqrt( m_fLowFreq * m_fHiFreq); 
				dgamma = d0 / (m_fHiFreq - m_fLowFreq);
				omega.SetRectangular( 0.0, dgamma * (ffreq / d0 - d0 / ffreq) );
				break;
			case 3 :			 // bandstop
				d0 = sqrt( m_fLowFreq * m_fHiFreq); 
				dgamma = (m_fHiFreq - m_fLowFreq) / d0;
				omega.SetRectangular( 0.0, - dgamma / (ffreq / d0 - d0 / ffreq) );
				break;
			default:
				break;
			}

		switch( m_nShape)
			{
			case 0 :			// bessel
				 FilterBessel(zc, omega );
				break;
			case 1 :			// butterworth
				 FilterButter(zc, omega  );
				break;
			case 2 :			// chebychev with ripple
			case 3 :			// 
				 FilterCheby( zc, omega );
				break;
			default:
				break;
			}

		cdSource->SetRectangular( i, zc.XValue(), zc.YValue());

		}

	return 0;
}


int CXtFilter::DoOperation( )	// xeq xform
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();

	if ( ! cdSource->GetCount())
		return 0;			// worked ok, nothing to do

	CreateProgressBar(IDS_STATFILTER, 100);

	CreateFilter( );

	ShowProgressBar( 10);		// 10% done

	if ( uomTime == cdSource->GetUOM() )
		{
		FilterTime( );
		}
	else
		{
		FilterFrequency( );
		}

	CloseProgressBar();

	return 0;
}

UINT CXtFilter::GetDialog(void)		// get the dialog id
{
	return IDD_XFFILTER;
}


int	CXtFilter::CalcPolynomials( void)
{
ZComplex zc;
int i;

	switch( m_nShape)
		{
		case 0 :			// bessel
			m_nSections = 1;		// just a big long polynomial!
			break;
		case 1 :			// butterworth
		case 2 :			// chebychev with ripple
		case 3 :			// 
			m_nSections = (m_nOrder+1)/2;		// 1 section per conjugate pair and possibly one for the last guy
			break;
		default:
			m_nSections = 1;		// just a big long polynomial!
			break;
		}

	m_pPrevInput = new CDoubleArray[m_nSections];
	m_pPrevOutput = new CDoubleArray[m_nSections];
	m_pNumerator = new CDoubleArray[m_nSections];
	m_pDenominator = new CDoubleArray[m_nSections];

	switch( m_nShape)
		{
		case 0 :			// bessel
			m_pDenominator[0].SetSize( m_cFreqPolyLow.GetSize() );
			m_pNumerator[0].SetSize( m_cFreqPolyLow.GetSize() );
			for ( i=0; i<m_cFreqPolyLow.GetSize(); i++)
				{
				zc = m_cFreqPolyLow.GetAt( i);
				m_pDenominator[0][i] = zc.XValue();
				m_pNumerator[0][i] = 0.0f;		// just zero it out, set constant later
				}
			zc = m_cFreqPoly.GetAt( 0);
			m_pNumerator[0][0] = zc.XValue();
			break;
		case 1 :			// butterworth
		case 2 :			// chebychev with ripple
		case 3 :			// given the poles, just create the arrays...
			{
			for ( i=0; i<(m_nOrder/2); i++)
				{
				m_pNumerator[i].SetSize( 3, 3);
				m_pDenominator[i].SetSize( 3, 3);
				zc = m_cFreqPolyLow.GetAt(i);		// get the pole
				m_pNumerator[i][0] = zc.XValue() * zc.XValue() + zc.YValue() * zc.YValue(); // the constant
				m_pNumerator[i][1] =  0.0f; // no s coeff
				m_pNumerator[i][2] =  0.0f; // no s**2 coeff
				m_pDenominator[i][0] = zc.XValue() * zc.XValue() + zc.YValue() * zc.YValue();			// the 
				m_pDenominator[i][1] = -2 * zc.XValue();			// -2 sigma( i) s
				m_pDenominator[i][2] = 1.0f;						// 1 s**2
				}
			if ( i == (m_nSections-1))		// must be odd, add the odd man out
				{
				m_pNumerator[i].SetSize( 2, 2);
				m_pDenominator[i].SetSize( 2, 2);
				zc = m_cFreqPolyLow.GetAt(i);		// get the pole - it should be real
				m_pNumerator[i][0]   = -zc.XValue(); // the constant
				m_pNumerator[i][1]   = 0.0f; // no s coefficient
				m_pDenominator[i][0] = -zc.XValue();			// the real part is the constant
				m_pDenominator[i][1] = 1.0f;			// s
				}
			}
			break;
		default:
			m_nSections = 1;		// just a big long polynomial!
			break;
		}

	for ( i=0; i < m_nSections; i++)
		{
		m_pPrevInput[i].SetSize( m_pDenominator[i].GetSize());
		m_pPrevOutput[i].SetSize( m_pDenominator[i].GetSize());
		}


	return 0;
}


float apply_filter( CDoubleArray& pTop, CDoubleArray& pLow, CDoubleArray& pPrev, CDoubleArray& pPost, float fInput)
{
double dtemp = 0.0;
int i;

	for ( i = pPrev.GetSize()-1; i>0; i--)	// we set pPrev now, to make the 0th element the current value
		pPrev[i] = pPrev[i-1];

	pPrev[0] = fInput;

	for ( i=0; i<pTop.GetSize(); i++)	// polynomial expansion
		dtemp += pTop[i] * pPrev[i];

	for ( i=1; i<pLow.GetSize(); i++)
		dtemp -= pLow[i] * pPost[i-1];

	for ( i = pPost.GetSize()-1; i>0; i--)	// now we set ppost, after the fact to get the new data
		pPost[i] = pPost[i-1];
	pPost[0] = dtemp;

	return pPost[0];
}



int CXtFilter::ApplyTimeFilter( void)
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
float fdata;
int i, j;
int ntotal = cdSource->GetCount() * m_nSections;

	for ( j=0; j<m_nSections; j++)
		{
		for ( i=0; i<cdSource->GetCount(); i++)
			{
			if ( 0 == (i % 100) )		// go easy on the resources
				{
				ShowProgressBar( 10 + (int )(90 * (i + j * cdSource->GetCount() )/ntotal) );		// 10% done
				}
			fdata = cdSource->DataValueAt( i, 1);	// get data in absolute terms
			fdata = apply_filter( m_pNumerator[j], m_pDenominator[j], m_pPrevInput[j], m_pPrevOutput[j], fdata);
			cdSource->SetAbsolute( i, fdata, 0.0f);
			}
		}

	return 0;
}

		// convert analog H(s) to bilinear form H(z) using s=(u-1)/(u+1)
int CXtFilter::ConvertBilinear( void)
{
int i, j, k;
int nsize;
int nlastsize = -1;
double tmp;
double *darray = NULL;
double *atmp = NULL;
double *btmp = NULL;

	for ( i=0; i<m_nSections; i++)		// for each section, do a bilinear transform
		{
		nsize = m_pDenominator[i].GetSize();
		if ( nsize != nlastsize)		// recalculate the matrix
			{
			if ( atmp)
				delete [] atmp;
			if ( btmp)
				delete [] btmp;
			atmp = new double[nsize];
			btmp = new double[nsize];
			if ( darray)
				delete [] darray;
			darray = new double[nsize * nsize];		// new array of (nsize)x(nsize)
			for (j = 0 ; j < nsize ; j++)			// set first row to 1.0f
				{
				darray[j * nsize] = 1;
				}
			tmp = 1.0;
			for (j = 0 ; j <= (nsize+1)/2 ; j++)		// set first column to (n choose j)
				{
				darray[j] = tmp;
				darray[nsize-j-1] = tmp;		// symmetric
				tmp *= (nsize - j - 1) / (double) (j+1);	// use j+1th entry
				}
			for (k = 1 ; k < nsize ; k++)		// now calc the rest of the array entries
				{
				for (j = 1 ; j < nsize ; ++j)
					{
					darray[k + j * nsize] = darray[k + (j - 1) * nsize]
											 - darray[k - 1 + j * nsize]
											 - darray[k - 1 + (j - 1) * nsize];
					}
				}
			nlastsize = nsize;		// we're built
			}
										// now do the matrix arithmetic
		for ( j=0; j<nsize; j++)
			{
			btmp[j] = 0.0;
			atmp[j] = 0.0;
			for ( k = 0; k<nsize; k++)		// matrix arith out = darray X floatin
				{
				btmp[j] += darray[j + k * nsize] * m_pDenominator[i][k];
				atmp[j] += darray[j + k * nsize] * m_pNumerator[i][k];
				}
			}

		tmp = btmp[0];
		if (! tmp)						// rescale by a constant
			tmp = 1.0;
										// now replace the polynomials
		for ( j=0; j<nsize; j++)
			{
			m_pDenominator[i][j] = btmp[j] / tmp;
			m_pNumerator[i][j]   = atmp[j] / tmp;
			}

		}			// end for each section

	if ( atmp)
		delete [] atmp;
	if ( btmp)
		delete [] btmp;
	if ( darray)
		delete [] darray;

	return 0;

}

		// get the polynomials built
int CXtFilter::ConvertToNormal( void)
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();	// we need the sample rate
double d1, domega, dhiomega;
int i, j;
int nsize;
double ddelta = cdSource->GetDelta() / 1000;		// delta in seconds

	domega = tan( ONEPI * ddelta * m_fLowFreq);		// as per above to rescale
	dhiomega = tan( ONEPI * ddelta * m_fHiFreq);		// as per above to rescale

	for ( i=0; i<m_nSections; i++)
		{
		nsize = m_pDenominator[i].GetSize();
			{
			switch( m_nType)		// convert based on type of filter
				{
				case 1 :			// highpass, use w/s and flip the coefficients
					for ( j=0; j<nsize / 2; j++)	// flip the coefficients
						{
						d1 = m_pDenominator[i][j];
						m_pDenominator[i][j] = m_pDenominator[i][nsize-j-1];
						m_pDenominator[i][nsize-j-1] = d1;
						d1 = m_pNumerator[i][j];
						m_pNumerator[i][j] = m_pNumerator[i][nsize-j-1];
						m_pNumerator[i][nsize-j-1] = d1;
						}
					domega = dhiomega;		// switch to the high frequency for scaling
									// no break, just do frequency scaling now
				case 0 :			// lowpass use s/w
					d1 = domega;		// start with w**1
					for ( j=1; j<nsize; j++)
						{
						m_pDenominator[i][j] /= d1;
						m_pNumerator[i][j] /= d1;
						d1 *= domega;
						}
					break;
				case 3 :			// bandstop, use s/w - w/s or so
					for ( j=0; j<nsize / 2; j++)	// flip the coefficients
						{
						d1 = m_pDenominator[i][j];
						m_pDenominator[i][j] = m_pDenominator[i][nsize-j-1];
						m_pDenominator[i][nsize-j-1] = d1;
						d1 = m_pNumerator[i][j];
						m_pNumerator[i][j] = m_pNumerator[i][nsize-j-1];
						m_pNumerator[i][nsize-j-1] = d1;
						}
									// no break, just do frequency scaling now
				case 2 :			// bandpass, use w/s  - s/w...
					{
					int ncoef;
					double *da, *db;
					double dw, dw2;
					int nnewsize = 2 * nsize - 1;
					int ls;
					double tmpa, tmpb, tmp;


						da = new double[nnewsize];
						db = new double[nnewsize];		// bigger guys here
						dw = 1.0;
						dw2 = dhiomega * domega;

						for ( j=0; j<nnewsize; j++)
							{
							da[j] = 0.0;
							db[j] = 0.0;
							}

						for ( ncoef = nsize-1; ncoef >= 0; ncoef--)	// to get dw right, do it backwards
							{
							tmpa = m_pNumerator[i][ncoef] * dw;
							tmpb = m_pDenominator[i][ncoef] * dw;
							tmp = 1.0;		// this will be (w2)**j * (ncoef choose j)

							for ( j=0; j<=ncoef; j++)
								{
								ls = nsize + ncoef - ( 2 * j) - 1;	// use nsize-1 as max ncoef
								da[ls] += tmpa * tmp;
								db[ls] += tmpb * tmp;
								tmp *= dw2 * (ncoef - j) / (j+1);	// use j+1 as the constant
								}
							dw *= dhiomega - domega;	// this is (hi-lo)**(nsize-ncoef)
							}

						m_pNumerator[i].SetSize( nnewsize);
						m_pDenominator[i].SetSize( nnewsize);
						m_pPrevInput[i].SetSize( nnewsize);
						m_pPrevOutput[i].SetSize( nnewsize);	// resize all...
						for ( j=0; j<nnewsize; j++)
							{
							m_pNumerator[i][j] = da[j];
							m_pDenominator[i][j] = db[j];
							}

						delete [] da;
						delete [] db;

					}
					break;
				}
			}
		}

	return 0;
}


// this filters time data
int CXtFilter::FilterTime( void)
{
	CalcPolynomials();
	ConvertToNormal();		// handle highpass, bandpass, bandstop
	ConvertBilinear();		// do a bilinear transform on these guys
	ApplyTimeFilter();		// do it
	return 0;
}
