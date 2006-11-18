// speaker.cpp : implementation of the CDataSetArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include "Complex.h"

#include "math.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//				ZComplex
/////////////////////////////////////////////////////////////////////////////

ZComplex::ZComplex( ) 
{
	m_dX = m_dY = 0.0;
}

ZComplex::ZComplex(const ZComplex &cIn ) 
{
	m_dX = cIn.m_dX;
	m_dY = cIn.m_dY;
}

ZComplex::ZComplex(double dX, double dY)
{
	m_dX = dX;
	m_dY = dY;
}

ZComplex::~ZComplex()
{
}


/////////////////////////////////////////////////////////////////////////////
//				ZComplex Operations
/////////////////////////////////////////////////////////////////////////////

double	ZComplex::Amplitude()
{
	return sqrt( m_dX * m_dX + m_dY * m_dY);
}

double	ZComplex::Phase()
{
	return (180 * atan2( m_dY, m_dX) / ONEPI );
}

/////////////////////////////////////////////////////////////////////////////
//				ZComplex Operators
/////////////////////////////////////////////////////////////////////////////

void ZComplex::SetRectangular( double dX, double dY)
{
	m_dX = dX;
	m_dY = dY;
}

void ZComplex::SetPolar( double dAmp, double dPhase)
{
	m_dX = dAmp * cos( ONEPI * dPhase / 180);
	m_dY = dAmp * sin( ONEPI * dPhase / 180);
}

// -------------------------- assignment
const ZComplex& ZComplex::operator=(const ZComplex& cIn)
{
	m_dX = cIn.m_dX;
	m_dY = cIn.m_dY;
	return *this;
}

// -------------------------- + assignment
const ZComplex& ZComplex::operator+=(const ZComplex& cIn)
{
	m_dX += cIn.m_dX;
	m_dY += cIn.m_dY;
	return *this;
}

// -------------------------- - assignment
const ZComplex& ZComplex::operator-=(const ZComplex& cIn)
{
	m_dX -= cIn.m_dX;
	m_dY -= cIn.m_dY;
	return *this;
}

// -------------------------- * assignment
const ZComplex& ZComplex::operator*=(const ZComplex& cIn)
{
	*this = (*this)*cIn;
	return *this;
}

// -------------------------- * assignment by double
const ZComplex& ZComplex::operator*=(const double& dMult)
{
	m_dX *= dMult;
	m_dY *= dMult;
	return *this;
}

// -------------------------- / assignment
const ZComplex& ZComplex::operator/=(const ZComplex& cIn)
{
	*this = (*this)/cIn;
	return *this;
}

// -------------------------- * assignment by double
const ZComplex& ZComplex::operator/=(const double& dDiv)
{
	m_dX /= dDiv;
	m_dY /= dDiv;
	return *this;
}


 // -------------------------- unary -
ZComplex AFXAPI operator- (const ZComplex &cIn)
{
ZComplex zout( -cIn.m_dX, -cIn.m_dY);

	return zout;
}


/////////////////////////////////////////////////////////////////////////////
// -------------------------- add
/////////////////////////////////////////////////////////////////////////////
ZComplex AFXAPI operator+ (const ZComplex &cIn, const ZComplex &cSrc)
{
ZComplex zout;

	zout.m_dX = cIn.m_dX + cSrc.m_dX;
	zout.m_dY = cIn.m_dY + cSrc.m_dY;
	return zout;
}

/////////////////////////////////////////////////////////////////////////////
// -------------------------- subtract
/////////////////////////////////////////////////////////////////////////////
ZComplex AFXAPI operator- (const ZComplex &cIn, const ZComplex &cSrc)
{
ZComplex zout;

	zout.m_dX = cIn.m_dX - cSrc.m_dX;
	zout.m_dY = cIn.m_dY - cSrc.m_dY;
	return zout;
}

/////////////////////////////////////////////////////////////////////////////
// -------------------------- multiply
/////////////////////////////////////////////////////////////////////////////
ZComplex AFXAPI operator* (const ZComplex &cIn, const ZComplex &cSrc)
{
ZComplex zout;

	zout.m_dX = cIn.m_dX * cSrc.m_dX - cIn.m_dY * cSrc.m_dY;
	zout.m_dY = cIn.m_dX * cSrc.m_dY + cIn.m_dY * cSrc.m_dX;
	return zout;
}

ZComplex AFXAPI operator* (const ZComplex &cIn, const double &dMult)
{
ZComplex zout;

	zout.m_dX = cIn.m_dX * dMult;
	zout.m_dY = cIn.m_dY * dMult;
	return zout;
}

/////////////////////////////////////////////////////////////////////////////
// -------------------------- divide
/////////////////////////////////////////////////////////////////////////////
ZComplex AFXAPI operator/ (const ZComplex &cIn, const ZComplex &cSrc)
{
ZComplex zout;
double damp = cSrc.m_dX * cSrc.m_dX + cSrc.m_dY * cSrc.m_dY;

	zout.m_dX = (cIn.m_dX * cSrc.m_dX + cIn.m_dY * cSrc.m_dY) / damp;
	zout.m_dY = (cIn.m_dY * cSrc.m_dX - cIn.m_dX * cSrc.m_dY) / damp;
	return zout;
}

ZComplex AFXAPI operator/ (const ZComplex &cIn, const double &dDiv)
{
ZComplex zout;

	zout.m_dX = cIn.m_dX / dDiv;
	zout.m_dY = cIn.m_dY / dDiv;
	return zout;
}

/////////////////////////////////////////////////////////////////////////////
// -------------------------- parallel (operator | )
/////////////////////////////////////////////////////////////////////////////
ZComplex AFXAPI operator| (const ZComplex &cIn, const ZComplex &cSrc)
{
double sx, sy;			// sum coefficients
ZComplex zsum;

	sx = cIn.XValue() + cSrc.XValue();
	sy = cIn.YValue() + cSrc.YValue();

	if ( sx || sy)
		{				// do this to avoid building more zcomplex structures
		double rl = cIn.XValue() * cSrc.XValue() - cIn.YValue() * cSrc.YValue();
		double cp = cIn.XValue() * cSrc.YValue() + cIn.YValue() * cSrc.XValue();
		double x = rl * sx + cp * sy;
		double y = cp * sx - rl * sy;
		rl = sx * sx + sy * sy;
		zsum.SetRectangular( x / rl, y / rl);
		}
	else
	    zsum.SetRectangular( 1000000, 1000000);
//		return ( cIn * cSrc / zsum);

	return zsum;
}

