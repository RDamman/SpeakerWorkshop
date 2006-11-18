// speaker.cpp : implementation of the CDataSetArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include "xform.h"
#include "xformall.h"

#include "Dataset.h"

#include "zFormEdt.h"

#include "dlgxfiff.h"
#include "dlgxffft.h"

#include "math.h"

#include "mmwave.h"
#include "Utils.h"

			// this must agree with the list in IDD_XFFFT dialog

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/* --------------------- Local variables -------------------------- */

/* --------------------- Function implementations ----------------- */
/* --------------------- ShuffleIndex ----------------------------- */

/* Function     : Finds the shuffle index of array elements. The array length
                  must be a power of two; The power is stored in "WordLength".
   Return value : With "i" the source array index, "ShuffleIndex"
                  returns the destination index for shuffling.
   Comment      : -
*/
static unsigned int shuffle_Index(unsigned int uIndex, int nBitLength)
{
unsigned int unew;
int nbit;

	unew = 0;
	for (nbit = 0; nbit <= nBitLength - 1; nbit++)
		{
		unew <<= 1;
		if (uIndex & 1)
			unew++;
		uIndex >>= 1;
		}
	return unew;
}


/* --------------------- Shuffle2Arr ------------------------------ */
/* Function     : Shuffles both arrays "a" and "b". This function is called 
                 before performing the actual FFT so the array elements
                 are in the right order after FFT.
  Return value : -
  Comment      : -
*/
static void shuffle_2Arr(double *pdReal, double *pdImag, int nBitLength)
{
unsigned int  ui, unew;
unsigned int  ucnt;
double         dtemp;
int nbittemp;

	ucnt = 1;								/* Find array-length */
	for ( nbittemp = nBitLength; nbittemp > 0; nbittemp--)
		ucnt *= 2;
	                                		/* Shuffle all elements */
	for (ui = 0; ui <= ucnt - 1; ui++)
		{									/* Find index to exchange elements */
		unew = shuffle_Index(ui, nBitLength);
		if (unew > ui)
			{								/* Exchange elements: */
			dtemp = pdReal[ui];				/* Of array a */
			pdReal[ui] = pdReal[unew];
			pdReal[unew] = dtemp;
			dtemp = pdImag[ui];				/* Of array a */
			pdImag[ui] = pdImag[unew];
			pdImag[unew] = dtemp;
			}
		}
}

/* --------------------- Fft -------------------------------------- */
/* Function     : Actual FFT algorithm. "Re" and "Im" point to start of real 
                 and imaginary arrays of numbers, "Pwr" holds the array sizes
                 as a power of 2 while "Dir" indicates whether an FFT (Dir>=1)
                 or an inverse FFT must be performed (Dir<=0).
  Return value : The transformed information is returned by "Re"
                 and "Im" (real and imaginary part respectively).
  Comment      : -
*/
static void simple_Fft(double *Re, double *Im, int nSamples, int Dir)
{
int i;
int Section;
int FlyDistance;
int FlyCount;
int index1;
int index2;
double tempr, tempi;
double Qr, Qi;
int npower;

	npower = 25;					// find nsamples to nearest power of 2
	for( i = (256*256*256); i > 0; i >>= 1)
		{
		if ( i < nSamples)
			break;
		npower--;
		}
									// build temps
	shuffle_2Arr(Re, Im, npower);                /* Shuffle before (i)FFT */

	ShowProgressBar( 10);		// 10% done

	if ( nSamples != cTempStore.nPower)		// we need to do it
		{
		if ( cTempStore.dSine)
			delete [] cTempStore.dSine;
		if ( cTempStore.dCosine)
			delete [] cTempStore.dCosine;
		cTempStore.dSine = new double[nSamples / 2];
		cTempStore.dCosine = new double[nSamples / 2];
		cTempStore.dSine[0] = 0;
		cTempStore.dCosine[0] = 1;
		for ( i=1; i< nSamples/2; i++)
			{
			cTempStore.dSine[i] = sin( (2 * ONEPI * i ) / nSamples);
			cTempStore.dCosine[i] = cos( (2 * ONEPI * i ) / nSamples);
			}
		cTempStore.nPower = nSamples;
		}
					// nSection is the size of each grouping
	for ( Section = 1; Section < nSamples; Section *= 2)
		{
		ShowProgressBar( 10 + (int )(90 * log((float )Section)/log((float )nSamples)) );		// 10% done
		FlyDistance = 2 * Section;
		Qr = 1; Qi = 0;
		for (FlyCount = 0; FlyCount < Section; FlyCount++)		// for each group
			{
			Qr = cTempStore.dCosine[ FlyCount * (nSamples / FlyDistance) ];
			Qi = cTempStore.dSine[ FlyCount * (nSamples / FlyDistance) ];	// flydistance happens to be 2*Section
			if ( Dir >= 1)
				Qi = -Qi;			// use minus the angle

			for ( index1 = FlyCount; index1 < nSamples; index1 += FlyDistance)	// for all items per index in a group
				{
				index2 = index1 + Section;
				                                    /* Perform 2-Point DFT  */
				tempr = Qr * Re[index2] - Qi * Im[index2];
				tempi = Qr * Im[index2] + Qi * Re[index2];

				Re[index2] = Re[index1] - tempr;             /* For Re-part */
				Re[index1] += tempr;
				Im[index2] = Im[index1] - tempi;             /* For Im-part */
				Im[index1] += tempi;
				}
			}
		}

  if (Dir <= 0)                                    /* Normalize for */
	{                                             /* inverse FFT only */
	double scale = 1.0/nSamples;
	for (i = 0; i < nSamples; i++)
		{
		Re[i] = scale * Re[i];
		Im[i] = scale * Im[i];
		}
	}


}
/* ---------------------------------------------------------------- */

static double get_Window( int nCur, int nTotal, int nWindow)
{
	/* windows from the dialog itself
		Bartlett
		Blackman
		Hamming
		Hann
		Kaiser
		Parzen
		Pretel
		Triangular
		Uniform (none)
	*/

	nTotal--;			// they all use n-1

	switch( nWindow)
		{
		case ffBartlett :
			return 1.0 - fabs( nCur - (nTotal / 2.0)) / (nTotal / 2.0);
		case ffBlackman :
			return 0.42 - 0.5 * cos((double) (nCur * 2) * ONEPI
				       / ((double) nTotal))
		      + 0.08 * cos((double) (nCur * 4) * ONEPI
				   / ((double) nTotal));
		case ffHamming :
			return 0.54 - 0.46 * cos((double) (nCur * 2) * ONEPI
					/ ((double) nTotal));
		case ffHann :
			return 0.5 * (1.0 - cos((double) (nCur * 2) * ONEPI
				       / ((double) nTotal)));
		case ffKaiser :			// actually tapered rectangular
			{
			double dret = 1.0;
			int l;
				l = (nTotal - 1) / 10;

				if (nCur <= l)
				{
				dret = 0.5 * (1.0 - cos((double) nCur * ONEPI
							   / ((double) l + 1.0)));
				}

				if (nCur > (nTotal - l - 1))
				{
				dret = 0.5 * (1.0 - cos((double) (nTotal - nCur) * ONEPI
							   / ((double) l + 1.0)));
				}
			return dret;
			}
		case ffParzen :			// bartlett temporarily
			return 1.0 - fabs( nCur - (nTotal / 2.0)) / (nTotal / 2.0);
		case ffPretel :			// nyi
			{
			double fmid;
#define IMAXX 100.0

				if ( (nCur >= IMAXX ) && ((nCur + IMAXX) <= nTotal))		// random
					return 1.0;
				if ( nCur < IMAXX)
					fmid = (IMAXX - nCur) / IMAXX;
				else
					fmid = (IMAXX + nCur - nTotal) / IMAXX;
				return 1.0 - fmid * fmid;
			}
		case ffTriangular :			// this is a bartlett window definition!
			return 1.0 - fabs( 1.0 - (2.0f * nCur)/(nTotal) );		// windowing
		case ffUniform :
			return 1.0;
		case ffWelch :
			{
			double fmid = (nCur - nTotal / 2.0) / (nTotal / 2.0);
			return 1.0 - fmid * fmid;
			}
		}

	return 1.0f;

}


/* ---------------------------------------------------------------- */
static void do_InverseFft(CDataSet *cdDest, CDataSet *cdSource, int nStart, int nEnd)
{
int i;
int nsamples = cdSource->GetCount();			// how much is in the source???
double *Real, *Imag;
float fstart, fend;
float ftest, fmax;

	fstart = cdSource->DataAt( dataFreq, nStart);
	fend = cdSource->DataAt( dataFreq, nEnd - 1);	// since fend is inclusive but nEnd isn't
	fmax = 500.0f / cdDest->GetDelta();				// the delta in f to get our desired sample rate

//	nsamples = nEnd - nStart;
	nsamples = nEnd;				// # of samples we will use is based only on ending frequency

	nsamples += nsamples-2;			// we will duplicate it all...

									// set nsamples to be a power of 2
	for( i = (256*256*256); i > 0; i >>= 1)
		{
		if ( i < nsamples)
			{
			nsamples = i * 2;
			break;
			}
		}
									// build temps
	Real = new double[nsamples];
	Imag = new double[nsamples];
									// set boundaries
	Real[0] = Imag[0] = 0;			// dc offset is 0

	for ( i=1; i<=(nsamples/2); i++)
		{
		double da;			// amplitude
		double dp;			// phase

		ftest = fmax * i / (nsamples/2);		// regular spacing on frequency always
					// current frequency is ftest
		if ( ftest >= fstart && ftest <= fend)
			{
			da = cdSource->DataValueAt(ftest, 1);
			dp = ONEPI * cdSource->PhaseValueAt(ftest, 1) / 180.0;
			}
		else
			{
			da = 0;			// dp is irrelevant
			dp = 0;
			}
		Real[i] = da * cos( dp);
		Imag[i] = da * sin( dp);
		if ( i != (nsamples/2) )
			{
			Real[nsamples-i] = Real[i];			// use the value with -phase 
			Imag[nsamples-i] = -Imag[i];
			}
		}


	simple_Fft( Real, Imag, nsamples, 0);

						// now create the destination
	double damp = 1;
//	for ( i = 0; i < nsamples; i++)		// normalize the data
//		{
//		if ( damp < Real[i])			// real[i] > 0
//			damp = Real[i];
//		else if ( damp < -Real[i])		// real[i] < 0
//			damp = -Real[i];
//		}
//	damp /= 32767;						// this is our maximum desired qty
	cdDest->SetSize( nsamples, 0);
	for ( i = 0; i < nsamples; i++)		// normalize the data
		{
		cdDest->SetDataAt( i, FTOI( Real[i] / damp) );
		}

	delete [] Real;
	delete [] Imag;
}



/////////////////////////////////////////////////////////////////////////////
//				CXformIfft
//					Ifft two datasets.....
/////////////////////////////////////////////////////////////////////////////
CXformIfft::CXformIfft( CObject *cTarget) : CXtransform( cTarget)
{
	m_nStart = 0;
	m_nEnd = 0;			// need these defaults to indicate entire range
	m_nSampleRate = 0;
}

CXformIfft::~CXformIfft( void)
{
}


int CXformIfft::DoOperation( CNamed *cdDest)	// xeq xform
{
CDataSet *cdsource = (CDataSet *)FindTargetObject();
CDataSet *cdnew = (CDataSet *)cdDest;
int nstart = m_nStart;
int nend = m_nEnd + 1;	// go 1 more to be non-inclusive

	cdnew->SetUOM( uomTime);
	cdnew->SetDOM( uomVolts);
																// data doubling
	if ( nstart == 0 && nend == 1)		// means use entire sample
		{
		nstart = 0;
		nend = cdsource->GetCount();
		}

	if ( nstart >= nend)
		return 1;			// couldn't do it! bad data

	if ( nstart < 0)
		nstart = 0;
	if ( nend > cdsource->GetCount())
		nend = cdsource->GetCount();

	{
	CString csform, cstart, cend;
		csform.GetBuffer(1024);	// this could be pretty long
		cstart.Format( "%f", cdsource->DataAt( dataFreq, nstart));
		cend.Format( "%f", cdsource->DataAt( dataFreq, nend-1));
		csform.Format( IDS_IFFTDESC, (LPCSTR )cdsource->GetName(), (LPCSTR )cstart, (LPCSTR )cend);
	cdnew->SetDescription( csform);
	}

	cdnew->SetStart( 0.0f);
	if ( (! m_nSampleStyle) || ! m_nSampleRate)	// sample style != 0 --> fixed sample rate
		{						// use a standard rate
		int nt = 11025;
		float ft = 2 * cdsource->Maximum( dataFreq);		// get ending frequency * 2
		if ( ft > nt)			// nope, more than 11k
			{
			nt *= 2;			// use 22k
			if ( ft > nt)
				{
				nt *= 2;		// 44k
				if ( ft > nt)
					nt = (int )ft;	// give up, use their input
				}
			}
		cdnew->SetDelta( 1000.0f / (float )nt );	// use 2x max frequency after
		}
	else
		cdnew->SetDelta( 1000.0f / (float )m_nSampleRate);

	CreateProgressBar( IDS_STATCALCIFFT, 100);

	do_InverseFft( cdnew, cdsource, nstart, nend);

	CloseProgressBar();

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
//				CXformFft
//					Fft two datasets.....
/////////////////////////////////////////////////////////////////////////////
CXformFft::CXformFft( CObject *cTarget) : CXtransform( cTarget)
{
	m_nStart = 0;
	m_nEnd = 0;
	m_nWindow = ffUniform;
}

CXformFft::~CXformFft()
{
}


int CXformFft::DoOperation( CNamed *cdDest)	// xeq xform
{
CDataSet *cdsource = (CDataSet *)FindTargetObject();
CDataSet *cdnew = (CDataSet *)cdDest;
int nstart = m_nStart;
int nend = m_nEnd + 1;	// go 1 more to be non-inclusive
int nwindow = m_nWindow;

	if ( nstart == 0 && nend == 1)		// means use entire sample
		{
		nstart = 0;
		nend = cdsource->GetCount();
		}

	if ( nstart >= nend)
		return 1;			// couldn't do it! bad data

	if ( nstart < 0)
		nstart = 0;
	if ( nend > cdsource->GetCount())
		nend = cdsource->GetCount();

	{
	CString csform;
		csform.GetBuffer(1024);	// this could be pretty long
		csform.Format( IDS_FFTDESC, (LPCSTR )cdsource->GetName(), nstart, nend-1, nwindow);
	cdnew->SetDescription( csform);
	}

	CreateProgressBar( IDS_STATCALCFFT, 100);

	::ExecuteFft( cdnew, cdsource, nstart, nend, nwindow);

	CloseProgressBar();

	return 0;
}


void ::ExecuteFft( CDataSet *cdDest, CDataSet *cdSource, int nStart, int nEnd, int nWindow)
{
int i;
int nsamples = cdSource->GetCount();			// how much is in the source???
double *Real, *Imag;
double a1;
int ntotal = nEnd - nStart;

	cdDest->CopyHeader( cdSource);

	cdDest->SetUOM( uomFreq);
	cdDest->SetDOM( uomDbw);

	nsamples = ntotal;

				// set nsamples to be a power of 2
	for( i = (256*256*256); i > 0; i >>= 1)
		{
		if ( i < nsamples)
			{
			nsamples = i * 2;
			break;
			}
		}

								// build temp arrays
	Real = new double[nsamples];
	Imag = new double[nsamples];
								// read the input data
	for ( i=0; i<ntotal && i<nsamples; i++)
		{
		Real[i] = cdSource->DataValueAt( nStart + i, 1);		// convert to real value
		Imag[i] = 0;
		if ( ffUniform != nWindow)
			Real[i] *= get_Window( i, nsamples, nWindow);
		}

	for ( ; i<nsamples; i++)	// fill the remainder of the 2**n array with zeros
		{
		Real[i] = 0.0;
		Imag[i] = 0.0;
		}
							// normalize to a mean of zero
	{
	double rsum = 0;

		for ( i=0; i<ntotal && i<nsamples; i++)
			{
			rsum += Real[i];
			}
		rsum /= ntotal;
		for ( i=0; i<ntotal && i<nsamples; i++)
			{
			Real[i] -= rsum;
			}

	}
							// do the actual fft
	simple_Fft( Real, Imag, nsamples, 1);
							// now create the destination
	a1 = nsamples * cdSource->GetDelta() / 1000;		// total time we are testing
	cdDest->SetStart( (float )(1 / a1));		// start freq = delta
	cdDest->SetDelta( (float )(1 / a1));		// delta = 1/sample time
	cdDest->SetSize( nsamples/2);				// this is symmetric around 0
	for ( i=1; i <= (nsamples/2); i++)		// the zeroth coef is just a dc offset
		{
		cdDest->SetRectangular( i-1, (float )Real[i], (float )Imag[i]);
		}

	delete [] Real;
	delete [] Imag;

}


static void simple_Hadamard(int *pnData, int nPower)
{
int i;
int N;
int Section;
int FlyDistance;
int FlyCount;
int index1;
int index2;
int ni;

	N = 1;
	for ( i = nPower; i; i--)
		N *= 2;									// calculate number of data points

	for ( Section = 1; Section < N; Section *= 2)
		{
		ShowProgressBar( 10 + (int )(80 * log((float )Section)/log((float )N)) );		// 10% done
		FlyDistance = 2 * Section;		// distance between butterfly pairs
		for (FlyCount = 0; FlyCount < Section; FlyCount++)	// which pair to do
			{							// do all pairs of this index per section
			for ( index1 = FlyCount; index1 < N; index1 += FlyDistance)
				{						// the other guy is section offset away
				index2 = index1 + Section;
				                                    /* Perform 2-Point DFT  */
				ni = pnData[index1] - pnData[index2];
				pnData[index1] += pnData[index2];
				pnData[index2] = ni;
				}
			}
		}
}

static void simple_BigHadamard(__int64 *pnData, int nPower)
{
int i;
int N;
int Section;
int FlyDistance;
int FlyCount;
int index1;
int index2;
__int64 ni;

	N = 1;
	for ( i = nPower; i; i--)
		N *= 2;									// calculate number of data points

	for ( Section = 1; Section < N; Section *= 2)
		{
		ShowProgressBar( 10 + (int )(80 * log((float )Section)/log((float )N)) );		// 10% done
		FlyDistance = 2 * Section;		// distance between butterfly pairs
		for (FlyCount = 0; FlyCount < Section; FlyCount++)	// which pair to do
			{							// do all pairs of this index per section
			for ( index1 = FlyCount; index1 < N; index1 += FlyDistance)
				{						// the other guy is section offset away
				index2 = index1 + Section;
				                                    /* Perform 2-Point DFT  */
				ni = pnData[index1] - pnData[index2];
				pnData[index1] += pnData[index2];
				pnData[index2] = ni;
				}
			}
		}
}

/* ---------------------------------------------------------------- */


/////////////////////////////////////////////////////////////////////////////
//				CXformCorrelate:DoOperation
//					Correlate a dataset with MLS data
/////////////////////////////////////////////////////////////////////////////
/* this uses info from "An Efficient Algorithm for Meeasuring the Impulse Response Using
	Pseudorandom Noise" - JAES 7/83

  Essentially - we use a fast hadamard transform of the form
		N = P S H   S P
		 n   2 2 n+1 1 1

  Where P and P are transposition matrices and S and S add/subtract a zero row
		 1     2
  

	*/
// --------------------------------------------------------------------
//			class CCorrelateVars
// we use this class in order to  keep some static vectors around
// they take a long time to calculate, and this speeds things up
// meanwhile, to delete them at exit time, it's simplest to just delete the
// class, as vc++ will automatically do when the app exits
// --------------------------------------------------------------------
class	CCorrelateVars
	{
	public:
		CCorrelateVars();
		~CCorrelateVars();
	public:
		int n_prevSize;
		int *p_perm1;
		int *p_perm2;
	};

static class CCorrelateVars c_Vars;

CCorrelateVars::CCorrelateVars()
{
	n_prevSize = 0;
	p_perm1 = NULL;
	p_perm2 = NULL;
}

CCorrelateVars::~CCorrelateVars()
{
	if ( n_prevSize)
		{
		delete [] p_perm1;
		delete [] p_perm2;
		n_prevSize = 0;
		}
}
// --------------------------------------------------------------------

#define DOSINGLE 1

int CXformCorrelate::DoOperation( )	// xeq xform
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
int i,j;
short *mlsdata;
char *mlsbinary;
int nbits;
int nsize = m_nSize - 1;			// vector length
int nfullsize;
int nrepeat;
int nrepoffset;
// int nrepeatcount = ( 2 * m_nRepeatCount - 1);
int nrepeatcount = m_nRepeatCount;

	if( m_nRepeatCount > 1)
		nrepeatcount++;			// act like we have one more

		// m_nSize is 2**n
	j = m_nSize / 2;
	nbits = 0;
	nfullsize = 1;
	for ( i=0; i<32; i++, j >>= 1)
		if ( j)
		{
			nbits++;
			nfullsize += nfullsize;
		}
		else
			break;

	nsize = nfullsize - 1;

#if 1
	if ( ( nrepeatcount * nsize ) > cdSource->GetCount())
		cdSource->SetSize( nrepeatcount * nsize, 0);	// no phase data, lost of other data
#else
	m_nSize = 8;
	nsize = 7;
#endif

	if ( (c_Vars.n_prevSize != nsize))		// have we already cached the perm vectors???
		{
		CreateProgressBar( IDS_STATCALC, 100);

		if ( c_Vars.n_prevSize)			// not right size, but they exist
			{
			delete [] c_Vars.p_perm1;
			delete [] c_Vars.p_perm2;
			c_Vars.n_prevSize = 0;
			}
		CMMMlsWave *mwave = new CMMMlsWave( (int )(.1 + 1000 / cdSource->GetDelta()), .001f + (float )(nfullsize * cdSource->GetDelta()/1000), (DWORD )nfullsize, FALSE);
		mwave->SetWarmOn( false);		// don't do a warmup for this guy
		mwave->CreateWave(chMono);
		mlsdata = (short *)mwave->GetCharData();

		ShowProgressBar( 20);		// 20% done, mls is built

		// start by building a 0,1 version of the mlsdata to use in creating the
			// permutation arrays
		mlsbinary = new char[nfullsize];	// fit the data
			// and we need a modulus speed-up array
		int *modulus = new int[3 * nfullsize];
    		
		for ( j=0; j<nsize; j++)
			{
			mlsbinary[j] = ((mlsdata[j] < 0) ? '\1' : '\0');	// revert back to original 0,1 data
			modulus[j] = j;
			modulus[nsize+j] = j;
			modulus[nsize+nsize+j] = j;
			}

		delete mwave;

		ShowProgressBar( 40);

			// we also need the input and output permutation vectors
		int *perm1 = new int[nfullsize];
		int *perm2 = new int[nfullsize];
		int *tnew  = new int[nfullsize];

			// now calculate the permutation vectors
			// begin by turning the data into a single value

		int nbvalue;
					// convert the data set into a binary #set
			for ( i=0; i<nsize; i++)
				{
				nbvalue = 0;
				for ( j=0; j<nbits; j++)
					{
					nbvalue = (nbvalue << 1) + mlsbinary[modulus[nsize+i-(nbits-j-1)]];
					}
				tnew[i] = nbvalue-1;		// temp storage (make it zero relative)
// XX 					tnew[i] = nbvalue;		// temp storage (make it zero relative)
				}
					// now invert the permutation values to get a real perm matrix
					// note that tnew contains values 0...n-1 
			ShowProgressBar( 60);

			for ( i=0; i<nsize; i++)
				perm1[tnew[i]] = i;

				// at this point perm1 is correctly the right side permutation vector (inverted)

				// now calculate the second permutation vector based on this data
					// convert the data set into a binary #set
			for ( i=0; i<nsize; i++)
				{
				nbvalue = 0;
				for ( j=(nbits-1); j>=0; j--)
					{
					nbvalue = (nbvalue << 1) + mlsbinary[modulus[nsize+perm1[(1<<j)-1]-i]];
					}
				perm2[i] = nbvalue-1;
// XX 				perm2[i] = nbvalue;
				}
		// at this point perm2 is correctly the left side permutation vector (inverted)

		ShowProgressBar( 80);

			// ----------- now invert the first permutation vector
		for ( i=0; i<nsize; i++)		// copy the vector
			tnew[i] = perm1[i];
		for ( i=0; i<nsize; i++)			// calc the inverse
			perm1[tnew[i]] = i;

		delete [] tnew;
		delete [] mlsbinary;
		delete [] modulus;

		c_Vars.n_prevSize = nsize;
		c_Vars.p_perm1 = perm1;
		c_Vars.p_perm2 = perm2;

		CloseProgressBar();
		}

				// permute and modify the input dataset
#if 0
	{
	for ( i=0; i<8; i++)
		cdSource->SetDataAt(i, 256 * (1 << i) );
	}
#endif

	CreateProgressBar( IDS_STATCORRELATE, 100);

#if 1
	if ( nrepeatcount > 1)			// average the data
	{
	__int64 nb;

		for( i=0; i<nsize; i++)
		{
			nb = 0;
			for ( j=1; j<nrepeatcount; j++)		// we don't count the first one, at all - it's noisy
				nb += cdSource->GetDataAt( i + j * nsize);
//			nb = cdSource->GetDataAt( i + nsize);
			nb = (nb + (m_nRepeatCount-1)/2) / m_nRepeatCount;		// average
			cdSource->SetDataAt( i, (INT32 )nb);		// put it back in the beginning
		}
	}

#endif

#if DOSINGLE
	nrepeatcount = 1;
#else
	nrepeatcount = m_nRepeatCount;
#endif

#if 1
	for ( nrepeat = 0; nrepeat < nrepeatcount; nrepeat++)
	{
		nrepoffset = (2*nrepeat) * nsize;
		if ( nfullsize < 60000)			// it's smallish
		{
			INT32  *hpw;
			INT32 nmult = FTOI(1);			// gives us the dataset multiplier
			hpw = new INT32[nfullsize];

			hpw[0] = 0;			// extend the vector by 1

			for ( i=1; i<nfullsize; i++)
				hpw[1+c_Vars.p_perm1[i-1]] = (cdSource->GetDataAt( nrepoffset + i-1) + nmult/2 - 1) / nmult;

			ShowProgressBar( 10);

						// perform the fast hadamard transform
			simple_Hadamard( hpw, nbits);

						// clip and permute the transformed data
			for( i=0; i<nsize; i++)
				{
				__int64 nb;

					nb = hpw[1+c_Vars.p_perm2[i]];
					nb = (nmult * nb) / nsize;

				cdSource->SetDataAt( nrepoffset + i, (INT32 )nb);
				}

			ShowProgressBar( 100);

			delete [] hpw;
		}
		else		// it's biggish
		{
			__int64  *hpw;
			INT32 nmult = FTOI(1);			// gives us the dataset multiplier
			hpw = new __int64[nfullsize];

			hpw[0] = 0;			// extend the vector by 1

			for ( i=1; i<nfullsize; i++)
				hpw[1+c_Vars.p_perm1[i-1]] = cdSource->GetDataAt(nrepoffset + i-1) / nmult;

			ShowProgressBar( 10);

						// perform the fast hadamard transform
			simple_BigHadamard( hpw, nbits);

						// clip and permute the transformed data
			for( i=0; i<nsize; i++)
				{
				__int64 nb;

					nb = hpw[1+c_Vars.p_perm2[i]];
					nb = (nmult * nb) / nsize;

				cdSource->SetDataAt( nrepoffset + i, (INT32 )nb);
				}

			ShowProgressBar( 100);

			delete [] hpw;
		}
	}
#endif
				// now resize the dataset to a single sample
#if DOSINGLE
	cdSource->SetSize( nsize, 0);	// no phase data, lost of other data
#endif

	CloseProgressBar();

	return 0;
}

