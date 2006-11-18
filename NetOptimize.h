// NetOptimize.h: interface for the CNetOptimize class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETOPTIMIZE_H__9DC4A298_4619_44F3_8333_6095A0DEDE76__INCLUDED_)
#define AFX_NETOPTIMIZE_H__9DC4A298_4619_44F3_8333_6095A0DEDE76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Complex.h"

class CNetOptimize  
{
private:

				// ------------------------the network
	CNetwork		*m_pNetwork;
	ZPassiveArray	m_cPassive;			// the array of passive elements

				// ------------------------user supplied variables
	CDoubleArray	m_cdFreq;			// the frequency list
	CDoubleArray	m_cdWeight;			// the weights
	CDoubleArray	m_cdDriveDb;		// driver response in dB
	CDoubleArray	m_cdDriveReal;		// drive admittance (real)
	CDoubleArray	m_cdDriveImag;		// drive admittance (imaginary)
	CDoubleArray	m_cdGoal;			// goal values in dB
	CUIntArray		m_ciVars;			// the variables component indices
	CDoubleArray	m_cdValues;			// the values of the components
				// ------------------------calculated stuff
	int				m_iNodes;			// # of nodes
	int				m_iDriver;			// node of the driver
	int				m_iQRSize;			// row-size of qr matrix
	int				m_iFreqs;			// # of frequencies
	int				m_iVars;			// # of variables
	ZComplexArray	m_zVolt;			// voltages
	ZComplexArray	m_zRight;			// right hand side
	ZComplexArray	m_dYMat;			// the Y matrix
	CDoubleArray	m_dBig;			// the big values
	CUIntArray		m_iSwap;			// the swappers
	CDoubleArray	m_dXjMat;			// the Xj matrix
	CDoubleArray	m_dG;				// the G array
	CDoubleArray	m_dX0;				// X0
	CDoubleArray	m_dS;				// S
	CDoubleArray	m_dPi;
	CDoubleArray	m_dRo;				// ro
	CDoubleArray	m_dQrMat;			// the QR matrix
	CDoubleArray	m_dAMat;			// the A matrix
	CDoubleArray	m_dR;				// the residuals
	CDoubleArray	m_dXjOldMat;		// the old xj matrix
	CDoubleArray	m_dRold;			// the old residuals

public:
	void SetRange( float m_fStart, float m_fEnd, int iCount);	// call this first
	bool SetNetwork( CNetwork *pNetwork);						// call this next
	void SetGoal( CDataSet *pGoal);								// then this
	void SetVariables( CUIntArray &cuVary);						// list of items to vary (indices)
	void Optimize( void);										// finally, do this

protected:
	double Jacobian( void);			// do the jacobian
	bool MatrixSolve( ZComplexArray &zMatrix, ZComplexArray &zVector, CDoubleArray &dBig, CUIntArray &iSwap, int nCount);
	bool MatrixDecomp( ZComplexArray &zMatrix, CDoubleArray &dBig, CUIntArray &iSwap, int nCount);
	void LeastSquares( void);
	void Factorize( void);

	inline int OP(int i, int j)		{ return i + j * m_iNodes; }	// matrix index
	inline int OQR(int i, int j)	{ return i + j * m_iQRSize; }	// qr indexing
	inline int OXJ(int i, int j)	{ return i + j * m_iFreqs;	}	// xj indexing
	inline int OVAR(int i, int j)	{ return i + j * m_iVars;	}	// variable matrices
public:
	CNetOptimize();
	virtual ~CNetOptimize();

};

#endif // !defined(AFX_NETOPTIMIZE_H__9DC4A298_4619_44F3_8333_6095A0DEDE76__INCLUDED_)
