// Complex.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef ZCOMPLEX

// standard transformation. same as base class
class ZComplex 
{
protected:

					// ----------------attributes
private:
	double	m_dX;
	double	m_dY;

protected:
					// ---------------- operations
public:
					// set functions
	void SetRectangular( double dX, double dY);
	void SetPolar( double dAmp, double dPhase);

					// get functions
	double Amplitude();
	double Phase();
	inline double XValue() const		{ return m_dX; }
	inline double YValue()	const		{ return m_dY; }
	inline double MagSquared() const	{ return m_dX * m_dX + m_dY * m_dY; }
	void   Conj()				{ m_dY = -m_dY; }
	BOOL	IsZero()		{ return (0 == m_dX && 0 == m_dY); }

					// ---------------- operators
	const ZComplex& operator= (const ZComplex& cIn);
	const ZComplex& operator+= (const ZComplex& cIn);
	const ZComplex& operator-= (const ZComplex& cIn);
	const ZComplex& operator*= (const ZComplex& cIn);
	const ZComplex& operator*= (const double& dMult);
	const ZComplex& operator/= (const ZComplex& cIn);
	const ZComplex& operator/= (const double& dAmt);

	friend ZComplex AFXAPI operator- (const ZComplex& cIn);
	friend ZComplex AFXAPI operator+ (const ZComplex& cIn, const ZComplex& cIn2);
	friend ZComplex AFXAPI operator- (const ZComplex& cIn, const ZComplex& cIn2);
	friend ZComplex AFXAPI operator* (const ZComplex& cIn, const ZComplex& cIn2);
	friend ZComplex AFXAPI operator* (const ZComplex& cIn, const double& dMult);
	friend ZComplex AFXAPI operator/ (const ZComplex& cIn, const ZComplex& cIn2);
	friend ZComplex AFXAPI operator/ (const ZComplex& cIn, const double &dDiv);
	friend ZComplex AFXAPI operator| (const ZComplex& cIn, const ZComplex& cIn2);

					// ----------------implementation
public:
	ZComplex();
	ZComplex( const ZComplex& cIn);
	ZComplex( double dX, double dY);
	~ZComplex();

};

typedef CArray<ZComplex,ZComplex&> ZComplexArray;		// similarly

#define ZCOMPLEX

#endif
