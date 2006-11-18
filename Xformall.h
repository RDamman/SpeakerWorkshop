// Xform.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CXFORMALL


// this must agree with the settings in the IDD_XFFFT dialog (where they are treated as int)
typedef enum tagffWindow
	{
	ffBartlett = 0,
	ffBlackman = 1,
	ffHamming = 2,
	ffHann = 3,
	ffKaiser = 4,
	ffParzen = 5,
	ffPretel = 6,
	ffTriangular = 7,
	ffUniform = 8,
	ffWelch = 9
	} FFWINDOW;




// -------------------------------------------------------------------------
//			UNARY TRANSFORMATIONS (in place)

class CXformLimit : public CXunary
{

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		UINT GetNameID()					{ return IDOP_LIMIT; }

	private:
		float 		m_fMin;
		float 		m_fMax;
		BOOL  		m_bUseMin;
		BOOL  		m_bUseMax;
		DATASEL  	m_ndChannel;	// which channel to affect

	public:
		CXformLimit( CObject *cTarget);		// must be named and in the tree
		~CXformLimit();
};


class CXformCorrelate : public CXunary
{

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		virtual UINT GetNameID()					{ return IDOP_LIMIT; }

		void	SetCorrelateSize( int nNew)			{ m_nSize = nNew; }
		void	SetRepeatCount( int nCount)			{ m_nRepeatCount = nCount; }

	private:
		int		m_nSize;				// size of correlation
		int		m_nRepeatCount;
	public:
		CXformCorrelate( CObject *cTarget);			// must be named and in the tree
		~CXformCorrelate();
};


class CXformScale : public CXunary
{

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		virtual UINT GetNameID()					{ return IDOP_SCALE; }
		void	SetVars( float fdB, float fFactor, int nMethod, BOOL bUseDb);		// set the variables

	private:
		float 		m_fdB;
		float 		m_fFactor;
		BOOL  		m_bUseDb;
		int			m_nMethod;				// add, sub, mult, div
	public:
		CXformScale( CObject *cTarget);		// must be named and in the tree
		~CXformScale();
};


class CXformInvert : public CXunary
{

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		virtual UINT GetNameID()					{ return IDOP_INVERT; }

		void	SetParms( BOOL bData, BOOL bPhase)		{ m_bInvertData = bData; m_bInvertPhase = bPhase; }

	private:
		BOOL  		m_bInvertData;
		BOOL		m_bInvertPhase;
	public:
		CXformInvert( CObject *cTarget);		// must be named and in the tree
		~CXformInvert();
};


class CXformTruncate : public CXunary
{

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		virtual UINT GetNameID()					{ return IDOP_TRUNCATE; }
	public:
		float 		m_fMin;
		float 		m_fMax;
	public:
		CXformTruncate( CObject *cTarget);		// must be named and in the tree
		~CXformTruncate();
};


class CXformExtend : public CXunary
{

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		virtual UINT GetNameID()				{ return IDOP_TRUNCATE; }

		void	SetMinMax( int nMin, int nMax)	{ m_nMin = nMin; m_nMax = nMax; }
	public:
		int 		m_nMin;
		int 		m_nMax;
	public:
		CXformExtend( CObject *cTarget);		// must be named and in the tree
		~CXformExtend();
};


class CXformDelay : public CXunary
{

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		virtual UINT GetNameID()					{ return IDOP_DELAY; }

	public:
		float 		m_fTime;				// delay to apply
		BOOL		m_bRemoveExcess;		// do it auomatically
	public:
		CXformDelay( CObject *cTarget);		// must be named and in the tree
		~CXformDelay();
};

class CXformSmooth : public CXunary
{
	private:
		int			m_nStyle;				// how much to smooth
		int			m_nMethod;				// method of smoothing
		float		m_fCustom;				// custom amt of octaves

	public:
		void	SetStyle( int nNew)			{ m_nStyle = nNew; }
		void	SetMethod( int nNew)		{ m_nMethod = nNew; }
		void	SetCustom( float fNew)		{ m_fCustom = fNew; }

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		virtual UINT GetNameID()					{ return IDOP_SMOOTH; }

	public:
		CXformSmooth( CObject *cTarget);		// must be named and in the tree
		~CXformSmooth();
};


class CXformCombine : public CXbinary			// this uses the dataset stuff
{
	private:
		int			m_nOperation;				// how to Combine

	public:
		void SetOperation( int nNew)				{ m_nOperation = nNew; }

		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		virtual UINT GetNameID()					{ return IDOP_COMBINE; }

	public:
		CXformCombine( CObject *cTarget, CObject *cOther);		// must be named and in the tree
		~CXformCombine();
};

void	ExecuteCombine( CDataSet *cdTarget, CDataSet *cdOther, int nOperation);

class CXformMergePort : public CXtransform			// this uses the dataset stuff
{
	private:
		float	m_fPistonArea;		// the piston area
		float	m_fPortArea;		// the port area
		DWORD	m_dwDriver;			// the nearfield driver response
		DWORD	m_dwPort;			// the nearfield port response
	public:
		virtual int  DoOperation( CNamed *cdDest);		// do it
		virtual UINT GetNameID()					{ return IDOP_MERGEPORT; }
		virtual UINT GetSuffix(void )				{ return IDSUF_MERGE; }
		void	SetParameters( DWORD dwDriver, DWORD dwPort, float fPiston, float fPort);

	public:
		CXformMergePort( CObject *cTarget);		// must be named and in the tree
		~CXformMergePort();
};

class CXformDistort : public CXtransform			// this uses the dataset stuff
{
	private:
		float		m_fCenterFreq;				// center frequency

	public:
		void SetCenterFreq( float fNew)				{ m_fCenterFreq = fNew; }

		virtual UINT GetNameID()					{ return IDOP_UNKNOWN; }
		virtual UINT GetSuffix(void )				{ return IDSUF_DISTORT; }

		virtual int  DoOperation( CNamed *cdDest);		// do it

	public:
		CXformDistort( CObject *cTarget);		// must be named and in the tree
		~CXformDistort();
};

class CXformIntermod : public CXtransform			// this uses the dataset stuff
{
	private:
		float		m_fCenterFreq;				// center frequency

	public:
		void SetCenterFreq( float fNew)				{ m_fCenterFreq = fNew; }

		virtual UINT GetNameID()					{ return IDOP_UNKNOWN; }
		virtual UINT GetSuffix(void )				{ return IDSUF_INTERMOD; }

		virtual int  DoOperation( CNamed *cdDest);		// do it

	public:
		CXformIntermod( CObject *cTarget);		// must be named and in the tree
		~CXformIntermod();
};

class CXformIfft : public CXtransform
{

	public:
		virtual	int		DoOperation( CNamed *cdDest);

		virtual UINT GetNameID()					{ return IDOP_IFFT; }
		virtual UINT GetSuffix(void )				{ return IDSUF_IFFT; }
		void	SetRange( int nStart, int nEnd) { m_nStart = nStart; m_nEnd = nEnd; }
		void	SetSampleRate( int nRate, int nStyle)		{ m_nSampleRate = nRate; m_nSampleStyle = nStyle; }

	protected:
		int		m_nStart;		// starting index for the fft
		int		m_nEnd;			// ending index for the fft
		int		m_nSampleRate;	// the sample rate for the output
		int		m_nSampleStyle;	// 0 == use data, 1 == use nSampleRate
	public:
		CXformIfft( CObject *cTarget);		// must be named and in the tree
		~CXformIfft();
};


class CXformFft : public CXtransform
{

	public:
		virtual	int		DoOperation( CNamed *cdDest);

		virtual UINT GetNameID()				{ return IDOP_FFT; }
		virtual UINT GetSuffix(void ) 			{ return IDSUF_FFT; }

		void	SetRange( int nStart, int nEnd) { m_nStart = nStart; m_nEnd = nEnd; }
		void	SetWindowing( int nWindow)		{ m_nWindow = nWindow; }

	protected:
		int		m_nStart;		// starting index for the fft
		int		m_nEnd;			// ending index for the fft
		int		m_nWindow;		// windowing mechanism
	public:
		CXformFft( CObject *cTarget);		// must be named and in the tree
		~CXformFft();
};

				// a global execution function
void	ExecuteFft( CDataSet *pDest, CDataSet *pSource, int nStart, int nEnd, int nWindow);


class CXformImpedance : public CXtBinary
{

	public:
		virtual int  DoOperation( CNamed *pcDest);		// do it

		virtual UINT GetNameID()					{ return IDOP_IMPEDANCE; }

		virtual UINT GetSuffix(void )	 			{ return IDSUF_IMPEDANCE; }


	private:
		float	m_fResistor;				// resistance between the measurements
		float	m_fSeriesRes;				// lead resistance to the object...
		float	m_fInputRes;				// input resistance
		float	m_fInputCap;				// input capacitance
	public:
		CXformImpedance( CObject *cTarget, CObject *cOther);		// must be named and in the tree
		~CXformImpedance();

		float	GetResistor()				{ return m_fResistor; }
		void	SetResistor( float fNew)	{ m_fResistor = fNew; }
		float	GetSeriesRes()				{ return m_fSeriesRes; }
		void	SetSeriesRes( float fNew)	{ m_fSeriesRes = fNew; }
		void	SetParms( TESTMSR *tm);

};



#define CXFORMALL

#endif
