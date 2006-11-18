// Xform.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CXFILTER

// -------------------------------------------------------------------------
//			UNARY TRANSFORMATIONS (in place)



class CXtFilter : public CXunary
{
	public:
			int 	m_nShape;
			int 	m_nType;
			int 	m_nOrder;
			float 	m_fLowFreq;
			float 	m_fHiFreq;
			float	m_fRipple;

	private:		// the stuff for each section
		CDoubleArray	*m_pPrevInput;		// x(j)'s
		CDoubleArray	*m_pPrevOutput;	// y(j)'s
		CDoubleArray	*m_pNumerator;		// numerators
		CDoubleArray	*m_pDenominator;	// denominators
		int				m_nSections;		// number of sections

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		UINT GetNameID()					{ return IDOP_FILTER; }

	private:
		void Calc_Variables();				// get the vars
		int CreateFilter( void);
		int CreateBessel( void);
		int CreateButter( void);
		int CreateCheby( void);
		int	FilterFrequency( void);
		int FilterBessel( ZComplex& zSource, ZComplex& zOmega);
		int FilterButter( ZComplex& zSource, ZComplex& zOmega);
		int FilterCheby( ZComplex& zSource, ZComplex& zOmega);
		int	CalcPolynomials( void);		// get the polynomials built
		int ConvertToNormal( void);
		int ConvertBilinear( void);
		int FilterTime( void);
		int ApplyTimeFilter( void);

	public:
		CFloatArray	m_cPolynomial;			// the fir representation (complex variables)
		CFloatArray	m_cPolyLow;				// the iir polynomial portion
		ZComplexArray	m_cFreqPoly;			// the fir representation (complex variables)
		ZComplexArray	m_cFreqPolyLow;			// the iir polynomial portion

	public:
		CXtFilter( CObject *cTarget, float *ftPoly, int nTotal);		// must be named and in the tree
		~CXtFilter();
};



#endif
