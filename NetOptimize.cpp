// speaker.cpp : implementation of the CNetworkArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include "Network.h"

#include "zFormEdt.h"
#include "Dataset.h"
#include "dlgNetwo.h"
#include "passive.h"
#include "Folder.h"

#include "fxFont.h"

#include "opItem.h"
#include "Utils.h"

#include "Math.h"
#include "NetOptimize.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


typedef struct tagNODELOC
	{
	int 	nNode;
	POINT 	ptLoc;
//	int		nDirection;		// which direction this node is pointing
	BYTE	byOrient;	// orientation
	} NODELOC;


#define NODESIZE 2

/////////////////////////////////////////////////////////////////////////////
// CNetwork Operations
/////////////////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------------
//	This performs an orthogonal factorization of a matrix QR using
//	algorithm 3.8 page 236 of Stewart
// ---------------------------------------------------------------------------
void CNetOptimize::Factorize( void)
{
int i,j,k;
int ivars = m_ciVars.GetSize();
double deta, dsigma;
double dt;
double dtau;

	for ( k=0; k<ivars; k++)
	{
		deta = 0.0;
		for ( i=k; i< m_iQRSize; i++)		// find max abs(qr)[.,k]
		{
			dt = fabs( m_dQrMat[ OQR(i,k)] );
			if ( dt > deta) 
				deta = dt;
		}
		if ( 0.0 == deta)
		{
			m_dPi[k] = 0.0;
			m_dRo[k] = 0.0;		// not in the manual
		}
		else
		{
			dsigma = 0.0;
			for ( i=k; i<m_iQRSize; i++)
			{
				m_dQrMat[ OQR(i,k)] /= deta;
				dsigma += m_dQrMat[ OQR(i,k)] * m_dQrMat[ OQR(i,k)];
			}
			dsigma = sqrt( dsigma);
			if ( m_dQrMat[ OQR(k,k)] < 0)
				dsigma = -dsigma;
			else if ( m_dQrMat[ OQR(k,k)] == 0)
				dsigma = 0;
			m_dQrMat[ OQR(k,k)] += dsigma;
			m_dPi[k] = dsigma * m_dQrMat[ OQR(k,k)];
			m_dRo[k] = -deta * dsigma;
			for ( j=k+1; j<ivars; j++)
			{
				dtau = 0.0;
				for( i=k; i<m_iQRSize; i++)
					dtau += m_dQrMat[ OQR(i,k)] * m_dQrMat[ OQR(i,j)];
				dtau /= m_dPi[k];
				for( i=k; i<m_iQRSize; i++)
					m_dQrMat[ OQR(i,j)] -= dtau * m_dQrMat[ OQR(i,k)];
			}
		}
	}
}



// ---------------------------------------------------------------------------
//		This uses the orthogonal factorization to calculate
//		a least squares solution of
//		A + XLA * (diagonal of A) * S = -R
//	See Stewart page 239 algorithm 3.10
// ---------------------------------------------------------------------------
void CNetOptimize::LeastSquares( void)
{
double dtau;
int i,j;
int ivars = m_ciVars.GetSize();

	for ( i=0; i<ivars; i++)
	{
		dtau = 0.0;
		for ( j=i; j<m_iFreqs; j++)
		{
			dtau += m_dQrMat[ OQR(j,i)] * m_dS[j];
		}
		if ( m_dPi[i])
			dtau /= m_dPi[i];
		for ( j=i; j<m_iQRSize; j++)
		{
			m_dS[j] -= dtau * m_dQrMat[ OQR(j,i)];
		}
	}
	if ( m_dRo[ivars-1])
		m_dS[ivars-1] /= m_dRo[ivars-1];
	for ( i=ivars-2; i>=0; i--)
	{
		for ( j=i+1; j<ivars; j++)
			m_dS[i] -= m_dQrMat[ OQR(i,j)] * m_dS[j];
		if ( m_dRo[i])
			m_dS[i] /= m_dRo[i];
	}
}




// ---------------------------------------------------------------------------
//	This solves ZMatrix * zVector = RHS
//		Using LU factorization
// ---------------------------------------------------------------------------
bool CNetOptimize::MatrixSolve( ZComplexArray &zMatrix, ZComplexArray &zVector, CDoubleArray &dBig, CUIntArray &iSwap, int nCount)
{
int i,j,k;
ZComplex zc;
int imax = nCount - 1;			// last element

	for ( k=2; k<imax; k++)
	{
					// swap the rhs based on iswap
		if ( k != iSwap[k])
		{
			zc = zVector[iSwap[k]];
			zVector[iSwap[k]] = zVector[k];
			zVector[k] = zc;
		}
					// now do the decomp
		for ( i = k+1; i<nCount; i++)
		{
			zVector[i] -= zMatrix[ OP(i,k) ] * zVector[k];
//			zVector[i] /= dBig[k];
		}
	}
					// now the back substitution
	zc = zMatrix[ OP(imax, imax) ];
	zc.Conj();		// conjugate
	zVector[imax] *= zc / dBig[imax];

	for ( i=imax-1; i>1; i--)
	{
		for ( j=i+1; j<nCount; j++)
		{
			zVector[i] -= zMatrix[ OP(i,j) ] * zVector[j];
		}
		zc = zMatrix[ OP(i, i) ];
		zc.Conj();
		zVector[i] *= zc / dBig[i];
	}

	return true;

}

// ------------------------------------------------------------------------
//		this does the LU factorization
// ------------------------------------------------------------------------
bool CNetOptimize::MatrixDecomp( ZComplexArray &zMatrix, CDoubleArray &dBig, CUIntArray &iSwap, int nCount)
{
int i,j,k, m;
ZComplex zc;
double zmag;

	for ( k=2; k<nCount; k++)
	{
		dBig[k] = 0.0;
		for ( i=k; i<nCount; i++)	// find biggest magnitude
		{
			zmag = zMatrix[ OP(i,k) ].MagSquared(  );		// get the magnitude
			if ( zmag > dBig[k])
			{
				dBig[k] = zmag;
				iSwap[k] = i;
			}
		}

		m = iSwap[k];
		if ( m != k)
		{
			for ( j=k; j<nCount; j++)
			{
				zc = zMatrix[  OP(k,j) ];
				zMatrix[ OP(k,j) ] = zMatrix[ OP(m,j) ];
				zMatrix[ OP(m,j) ] = zc;
			}
		}
		for ( i=k+1; i<nCount; i++)
		{
			zc = zMatrix[ OP(k,k) ];
			zc.Conj();
			zc *= zMatrix[ OP(i,k) ] / dBig[k];
			zMatrix[ OP(i,k) ] = zc;
			for ( j=k+1; j<nCount; j++)
			{
				zMatrix[  OP(i,j) ] -= zc * zMatrix[  OP(k,j) ];
			}
		}
	}

	return true;
}


// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
double CNetOptimize::Jacobian( void)
{
double derrtotal = 0.0;
int i,j, nf;
ZComplex zc;
ZpPassive *pcomponent;
int imax;
double dfreq;			// frequency
double w;				// omega
double ddb = 10.0 / log( 10.0);
int ivars = m_ciVars.GetSize();

	for ( nf = 0; nf < m_cdFreq.GetSize(); nf++)			// for each data point
	{
		dfreq = m_cdFreq[nf];						// frequency
		w = 2 * ONEPI * dfreq;						// get the frequency in radians

		for ( i=0; i<m_iNodes; i++)		// zero out the rhs and the matrix
		{
			m_zRight[i].SetRectangular(0.0,0.0);				// rhs
			for ( j=0; j<m_iNodes; j++)	// Y matrix
				m_dYMat[ OP( i,j) ].SetRectangular(0.0,0.0);
		}
						// ---------- fill the admittance matrix
		imax = m_cPassive.GetSize();
		for ( i=0; i<imax; i++)
		{
		int in1, in2;
			pcomponent = m_cPassive.GetAt(i);
			if ( ptGenerator == pcomponent->GetType())
				continue;			// don't process the generator
			in1 = pcomponent->MinNode();
			in2 = pcomponent->MaxNode();
			if ( 0 == in1 && 1 == in2)			// it's connected across the generator
				continue;						// blow it off
			switch( pcomponent->GetType())
			{
			case ptResistor :
				zc.SetRectangular( -1.0 / pcomponent->GetValue(), 0.0);
				break;
			case ptGenerator :
				break;
			case ptCapacitor :
				zc.SetRectangular( 0.0, -w * pcomponent->GetValue());
				break;
			case ptDriver :
				break;
			case ptInductor :				// to support inductor Q we get the inductor's impedance
				pcomponent->Impedance( zc, dfreq);		// get the inductor's impedance
				zc = -ZComplex(1.0,0.0)/zc;				// turn into admittance
//				zc.SetRectangular( 0.0, 1.0 / (w * pcomponent->GetValue()) );
				break;
			default :
				ASSERT(0);
				break;
			}
			m_dYMat[ OP( in2, in1) ] += zc;
			if ( in1 == 1 )
				m_zRight[in2] -= zc;			// plug it into the right hand side
		}
					// get the driver admittance
		zc.SetRectangular( m_cdDriveReal[ nf], m_cdDriveImag[nf] );
		m_dYMat[ OP( m_iDriver, 0) ] -= zc;			// put it into the array
						// now make the admittance matrix symmetric and make the diagonal
						// elements the sum of the off-diagonals
		for(i=2; i<m_iNodes; i++)
		{
			for ( j=0; j<i; j++)
			{
				m_dYMat[ OP(i,i)] -= m_dYMat[ OP(i,j)];		// sum off diag
				m_dYMat[ OP(j,i)] = m_dYMat[ OP(i,j)];		// make symmetric
			}
			for ( j=i+1; j<m_iNodes; j++)
			{
				m_dYMat[ OP(i,i)] -= m_dYMat[ OP(j,i)];		// sum off diag
			}
		}
#if _DEBUG
		for ( i=0; i< m_iNodes; i++)
		for ( j=0; j< m_iNodes; j++)
		{
			zc = m_dYMat[ OP(i,j)];
		}
#endif
								// now decompose the admittance matrix
		MatrixDecomp( m_dYMat, m_dBig, m_iSwap, m_iNodes);
								// now solve the system
#if _DEBUG
		for ( i=0; i< m_iNodes; i++)
		for ( j=0; j< m_iNodes; j++)
		{
			zc = m_dYMat[ OP(i,j)];
		}
		for ( i=0; i< m_iNodes; i++)
			zc = m_zRight[ i];
#endif

		MatrixSolve( m_dYMat, m_zRight, m_dBig, m_iSwap, m_iNodes);
								// now set up and solve the adjoint system
#if _DEBUG
		for ( i=0; i< m_iNodes; i++)
			zc = m_zRight[ i];
#endif
		m_zVolt.Copy( m_zRight);		// save the voltages in zvolt
		for ( i=0; i<m_iNodes; i++)
		{
#if _DEBUG
			zc = m_zRight[i];
#endif
			m_zRight[i].SetRectangular(0.0,0.0);				// set m_zRight to 0
		}
		m_zRight[m_iDriver].SetRectangular( -1.0, 0.0);			// set the driver rhs to -1
		m_zVolt[0].SetRectangular( 0.0, 0.0);			// ground
		m_zVolt[1].SetRectangular( 1.0, 0.0);			// input voltage (these weren't set in the matrixstuff)
										// now solve the system again
		MatrixSolve( m_dYMat, m_zRight, m_dBig, m_iSwap, m_iNodes);
										// calculate the magnitude of the voltage applied to the driver
		double dmag = m_zVolt[m_iDriver].MagSquared();
		double derrinc = ddb * log(dmag);
		derrinc += m_cdDriveDb[nf] - m_cdGoal[nf];
		m_dR[nf] = m_cdWeight[nf] * derrinc;		// get the weight * error
		derrtotal += m_dR[nf] * m_dR[nf];			// total error
										// calculate the nfth row of the Jacobian Matrix XJ
		j = 0;
		for ( i=0; i<ivars; i++)
		{
		int n1, n2;
		ZpPassive *zp;
		ZComplex dvda;
		double dt;

			zp = (ZpPassive *)m_cPassive.GetAt(m_ciVars[i]);
			n1 = zp->MinNode();
			n2 = zp->MaxNode();
									// compute the derivative of the driver voltage
			dvda = (-m_zRight[n1] * m_zVolt[n2]) - m_zRight[n2] * m_zVolt[n1];
			dvda += m_zRight[n1] * m_zVolt[n1] + m_zRight[n2] * m_zVolt[n2];
			switch( zp->GetType())
			{
			case ptResistor:
				dvda *= -1.0 / zp->GetValue();
				break;
			case ptCapacitor:
				dvda *= w * zp->GetValue();
				dvda *= ZComplex( 0, 1.0);			// multiply by i
				break;
			case ptInductor:
				dvda *= 1 / (w * zp->GetValue());
				dvda *= ZComplex( 0, 1.0);			// multiply by i
				break;
			default:
				ASSERT(0);
			}
			dt = 2 * m_cdWeight[nf] * ddb *
					( dvda.XValue() * m_zVolt[m_iDriver].XValue() + dvda.YValue() * m_zVolt[m_iDriver].YValue() );
			dt /= dmag;
			m_dXjMat[ OXJ(nf, j) ] = dt;
			j++;
		}
	}		// end of nf loop

	return derrtotal;
}

/////////////////////////////////////////////////////////////////////////////
//			CalculateResponse
/////////////////////////////////////////////////////////////////////////////
void	CNetOptimize::Optimize()
{
int isize = m_iNodes;			// # of nodes
int ifreq = m_cdFreq.GetSize();
int ivars = m_ciVars.GetSize();
int i,j,k;
double derror;
double derrbest;
double dxla;
double dgtv, dgtag;
double dt;
double dra;
double dxlac = 0.0;
bool brun = true;
int iiterate = 0;
	m_iFreqs = ifreq;
	m_iQRSize = ivars + ifreq;
	m_iVars = ivars;

				// set up the global arrays
	CreateProgressBar( IDS_STATCALC, 100);
	m_zVolt.SetSize( isize);			// voltages
	m_zRight.SetSize( isize );			// right hand side
	m_dYMat.SetSize( isize * isize);	// the Y matrix
	m_dBig.SetSize( isize);				// the big values
	m_iSwap.SetSize( isize);			// the swappers
	m_dXjMat.SetSize( ifreq * ivars);	// the Xj matrix
	m_dXjOldMat.SetSize( ifreq * ivars);	// the old xj matrix
	m_dG.SetSize( ivars);				// the G array
	m_dX0.SetSize( ivars);				// X0
	m_dS.SetSize( m_iQRSize);			// S
	m_dPi.SetSize( ivars);
	m_dRo.SetSize( ivars);				// ro
	m_dQrMat.SetSize( ivars * m_iQRSize);// the QR matrix
	m_dAMat.SetSize( ivars * ivars);		// the A matrix
	m_dR.SetSize( ifreq);				// the residuals
	m_dRold.SetSize( ifreq);			// the old residuals

	for ( i=0; i<ivars; i++)
	{
	ZpPassive *zp = m_cPassive.GetAt( m_ciVars[i]);		// get the ith passive variable

		m_cdValues[ i] = log( zp->GetValue());
	}

	derror = Jacobian();				// get the initial error
	derrbest = derror;					// for now, this is the best

	m_dX0.Copy( m_cdValues);			// copy the array values

	dxla = 0.0;
	while( brun && (derrbest > .01) && (iiterate < 1000))			// random error test
	{
		for ( i=0; i<ivars; i++)				// A = XJ (transpose) * XJ
			for ( j=i; j<ivars; j++)
			{
				m_dAMat[ OVAR( i,j)] = 0.0;
				for ( k=0; k<ifreq; k++)
					m_dAMat[ OVAR( i,j)] += m_dXjMat[ OXJ(k,i)] * m_dXjMat[ OXJ(k,j)];
				m_dAMat[ OVAR( j,i)] = m_dAMat[ OVAR( i,j)];
			}

		for ( i=0; i<ivars; i++)			// G = XJ(transpose) * R
		{
			m_dG[i] = 0;					// G == derror / du[k]
			for ( j=0; j<ifreq; j++)
			{
				m_dG[i] += m_dXjMat[ OXJ(j,i)] * m_dR[j];
			}
		}
#if _DEBUG
		for ( i=0; i<ivars; i++)
		{
			dt = m_dG[i];
			dt = m_dG[i];
		}
#endif
		m_dRold.Copy( m_dR);				// copy the r array
		m_dXjOldMat.Copy( m_dXjMat);		// copy the xj matrix

domore:
		ShowProgressBar( iiterate % 100);
					// set up the overdetermined system to solve via orthogonal factorization
		for ( j=0; j<ivars; j++)			// QR = [XJ , sqrt(a) diagonal]
		{
			for ( i=0; i<ifreq; i++)
			{
				m_dQrMat[ OQR(i,j)] = m_dXjOldMat[ OXJ(i,j)];
			}
			for ( ; i<m_iQRSize; i++)
			{
				m_dQrMat[ OQR(i,j)] = 0.0;
			}
			m_dQrMat[ OQR(ifreq + j,j)] = sqrt( dxla * m_dAMat[ OVAR(j,j)] );
		}

		for ( i=0; i<ifreq; i++)		// S = [-R, 0]
			m_dS[i] = -m_dRold[i];
		for ( ; i<m_iQRSize; i++)
			m_dS[i] = 0.0;

						// now do the factorization
		Factorize();
		LeastSquares();
						// calculate the new variable values
		for ( i=0; i<ivars; i++)
		{
		ZpPassive *zp = m_cPassive.GetAt(m_ciVars[i]);
		double dt;

			dt = m_dX0[i] + m_dS[i];
			m_cdValues[i] = dt;
			if ( dt > -25 && dt < 7)
			{
				dt = exp( m_cdValues[i]);
				zp->SetValue( exp( m_cdValues[i]));
			}
			else
				if ( dt <-25)
					zp->SetValue( 1e-11);
				else
					zp->SetValue( 1e3);
		}
						// and the new component values

		derror = Jacobian();		// get the new jacobian error

		dgtv = 0.0;					// (S transpose) * A * S
		dgtag = 0.0;				// (S transpose) * G
		for ( i=0; i<ivars; i++)
		{
			dt = 0.0;
			for ( j=0; j<ivars; j++)
			{
				dt += m_dAMat[ OVAR( i,j)] * m_dS[j];
			}
			dgtag += dt * m_dS[i];
			dgtv += m_dG[i] * m_dS[i];
		}

		// now calculate RA the ratio of reduction in error to predicted reduction
		if ( fabs(2 * dgtv + dgtag) > 1e-8)
			dra = -(derrbest - derror) / ( 2 * dgtv + dgtag);
		else
			dra = 1000;
//		dra = fabs( (derrbest - derror) / ( 2 * dgtv + dgtag) );
//		if ( (derror > derrbest) || dra <= .01)			// if ra is too small, increase xla
//		if ( (derror > derrbest) || dra <= .01)			// if ra is too small, increase xla
		if ( dra <= .01)			// if ra is too small, increase xla
		{
		double dum;

			dum = 2 - (derror - derrbest)/dgtv;
			if ( dum > 10)
				dum = 10.0;
			if ( dum < 2)
				dum = 2;		// limit to 2...10
			if ( dxla == 0.0)
			{
			double anorm = 0.0;
				for ( k=0; k<ivars; k++)
				{
					for ( i=0; i<m_iQRSize; i++)
						m_dS[i] = 0.0;
					m_dS[k] = 1.0;
					LeastSquares();		// do another ls
					dt = 0.0;
					for ( i=0; i<ivars; i++)
						dt += fabs( m_dS[i]);
					if ( dt >= anorm)
						anorm = dt;
				}
				dxlac = 1 / (anorm * anorm);
				dxla = (dum / 2) * dxlac;
			}
			else 
//				if ( derror < derrbest)
				dxla = dum * dxla;
//			else dxla = dxla / 2;
		}
		else if ( dra > .1)			// it was pretty good, reduce xla
		{
			dxla /= 2;
			if ( dxla < dxlac)
				dxla = 0.0;
		}
		iiterate++;
		if ( derror < derrbest)			// we did improve
		{
			double dt = derrbest - derror;
			m_dX0.Copy( m_cdValues);		// copy the current values
			derrbest = derror;				// and the error
			if ( dt < 1e-5)
				brun = false;				// stop
		}
		else							// we didn't improve
		{
//			if ( 0.0 == dxlac)
//			if ( .0001 > dxla)
			if ( ( dxlac + dxla) == dxlac)			// dxla is now very small
				brun = false;			// abrupt stop
			else
				if ( iiterate < 1000)
					goto domore;
		}
	}

	CloseProgressBar();


}




//////////////////////////////////////////////////////////////////////
// CNetOptimize Class
//////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------
//		SetRange
// set up the frequency range as logarithmic
// ------------------------------------------------------------------------

void CNetOptimize::SetRange( float m_fStart, float m_fEnd, int iCount)
{
int i;
double dlog;

	m_cdFreq.SetSize( iCount);
	dlog = log( m_fEnd / m_fStart);		// get the ratio
	for ( i=0; i<iCount; i++)
	{
		m_cdFreq[i] = m_fStart * exp( ( i * dlog) / (iCount-1));			// logarithmic increase
	}
	m_cdWeight.SetSize( iCount);			// the weights
	m_cdDriveDb.SetSize( iCount);			// driver response in dB
	m_cdDriveReal.SetSize( iCount);			// drive admittance (real)
	m_cdDriveImag.SetSize( iCount);			// drive admittance (imaginary)
	m_cdGoal.SetSize( iCount);				// goal values in dB

}

// ------------------------------------------------------------------------
//		SetNetwork
// set the network, and create the driver information
// ------------------------------------------------------------------------

bool CNetOptimize::SetNetwork( CNetwork *pNetwork)
{
int i;
ZpDriver *pdriver;
ZComplex zc;
ZPassiveArray *pdiscrete;

	m_pNetwork = pNetwork;

	m_iNodes = m_pNetwork->RenumberNodes();					// renumber and get # of nodes
	pdiscrete = (ZPassiveArray *)m_pNetwork->GetDiscreteArray();
	m_cPassive.SetSize( 0, 20);				// we will remove generator
	for ( i=0; i< pdiscrete->GetSize(); i++)
		if ( ptGenerator != pdiscrete->GetAt(i)->GetType())
			m_cPassive.Add( pdiscrete->GetAt(i));

	pdriver = (ZpDriver *)pNetwork->GetDriver( 0);			// get the first driver
	if ( ! pdriver)
	{
		AfxMessageBox(IDERR_NODRIVER, MB_OK);
		return false;
	}
	if ( pdriver->GetNode( 0) && pdriver->GetNode(1) )
	{
		AfxMessageBox(IDERR_DRIVETOGND, MB_OK);
		return false;
	}
	pdriver->InitPointers( m_pNetwork->GetRootObject());		// set up the pointers for him
	if ( ! pdriver->GetResponse() )
	{
		AfxMessageBox(IDERR_NORESPONSE, MB_OK);
		return false;
	}
	if ( ! pdriver->GetImpedance() )
	{
		AfxMessageBox(IDERR_NOIMPEDANCE, MB_OK);
		return false;
	}
	if ( pNetwork->GetDriver(1))		// we have a second driver
	{
		AfxMessageBox(IDERR_MULTIDRIVE, MB_OK);
		return false;
	}

	m_iDriver = pdriver->MaxNode();		// get the non-zero node for the driver

					// now get the drive impedance and response
	for ( i=0; i < m_cdFreq.GetSize(); i++)
	{
		m_cdDriveDb[i] = pdriver->ResponseDb( m_cdFreq[i]);
		pdriver->Impedance( zc, m_cdFreq[i]);
		zc = ZComplex( 1.0, 0.0) / zc;			// convert to admittance
		m_cdDriveReal[i] = zc.XValue();
		m_cdDriveImag[i] = zc.YValue();			// get the admittance values
	}
					// default to all variables minus generator
	m_ciVars.SetSize( m_cPassive.GetSize());
	{
	int i;
	int j;

		j = 0;
		for ( i = 0; i < m_cPassive.GetSize(); i++)
			{
				m_ciVars[j] = (UINT )i;
				j++;			// don't use the generator, use the others, though
			}
	}
	m_cdValues.SetSize( m_ciVars.GetSize());

	return true;

}

// ------------------------------------------------------------------------
//		SetGoal
// setup the goal stuff based on the goal dataset
// ------------------------------------------------------------------------

void CNetOptimize::SetGoal( CDataSet *pGoal)
{
int i;
double dmax;
double ddb = 10.0 / log(10.0);		// convert to 10 log

	for ( i=0; i<m_cdGoal.GetSize(); i++)
	{
		m_cdGoal[i] = pGoal->DataValueAt( (float )m_cdFreq[i], 0);		// get it in dB
	}
				// given the goal, create the weights
	dmax = pGoal->Maximum( dataAmp);		// get max amplitude in dB

	for ( i=0; i<m_cdGoal.GetSize(); i++)
	{
		m_cdWeight[i] = exp( (m_cdGoal[i] - dmax) / (2 * ddb) );	// based on diff from max
//		m_cdWeight[i] = 1;	// based on diff from max
		double dt = m_cdWeight[i];
	}

				// ------------------   normalize and scale the weights
	dmax = 0.0;
	for ( i=0; i<m_cdWeight.GetSize(); i++)
	{
		dmax += m_cdWeight[i];								// total the weights
	}
	for ( i=0; i<m_cdWeight.GetSize(); i++)
	{
		m_cdWeight[i] = sqrt( m_cdWeight[i] / dmax);			// normalize
	}
	
}

// ------------------------------------------------------------------------
//		SetVariables
// setup the list of items to vary
// ------------------------------------------------------------------------

void CNetOptimize::SetVariables( CUIntArray &cuVary)
{
	m_ciVars.Copy( cuVary);
	m_cdValues.SetSize( m_ciVars.GetSize());
}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNetOptimize::CNetOptimize()
{

}

CNetOptimize::~CNetOptimize()
{

}
