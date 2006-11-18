/////////////////////////////////////////////////////////////////////////////
// Passive.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef ZPASSIVE

#include "Complex.h"

#include "DrawObj.h"

/////////////////////////////////////////////////////////////////////////////
// ZpPassive Definition
/////////////////////////////////////////////////////////////////////////////
class ZpPassive : public CDrawObj
{
protected:
	DECLARE_SERIAL(ZpPassive)

					// ----------------attributes
private:
	double	m_dValue;			// works for most passives
	double	m_dQ;				// the Q of the object
	WORD 	m_wNode[2];			// the two nodes it is connected to
	int		m_nPosition[2];		// where to draw the component
	CString	m_csName;
	BYTE	m_byOrient;			// draw it flipped
	int		m_nLabelWhere;		// orientation and labeling combined...

protected:
					// ---------------- attributes
public:
	void	SetName( LPCSTR pszNew)					{ m_csName = pszNew; }
	CString& GetName()								{ return m_csName; }
	double 	GetValue()								{ return m_dValue; }
	void   	SetValue(double dNew)					{ m_dValue = dNew; }
	double	GetQ()									{ return m_dQ;		}
	void	SetQ( double dNew)						{ m_dQ = dNew;		}
	int		GetNode(int nWhich)						{ return (int )(m_wNode[nWhich]); }
	int		MinNode( void)							{ return (int )(m_wNode[ (m_wNode[0] < m_wNode[1]) ? 0 : 1]); }
	int		MaxNode( void)							{ return (int )(m_wNode[ (m_wNode[0] > m_wNode[1]) ? 0 : 1]); }
	void	SetNode(int nWhich, int nNewValue)		{ m_wNode[nWhich] = (WORD )nNewValue; }
	int		GetPosition(int nWhich)					{ return (int )(m_nPosition[nWhich]); }
	void	GetPosition(LPPOINT lpptPos)			{ lpptPos->x = m_nPosition[0]; lpptPos->y = m_nPosition[1]; }
	void	SetPosition(int nWhich, int nNewValue)	{ m_nPosition[nWhich] = (WORD )nNewValue; }
	void	SetPosition(LPPOINT lpptPos)			{ m_nPosition[0] = (short )lpptPos->x; m_nPosition[1] = (short )lpptPos->y; }
	void	SetOrientation( BYTE byNew)				{ m_byOrient = byNew;		}
	void	SetLabeling( int nDirection);			// set new orientation and layout
	int		GetLabeling( void)						{ return m_nLabelWhere; }
 	int		GetEndPosition( int nWhich);
 	void	GetEndPosition( LPPOINT lpptPos);
					// ---------------- operations
public:
	void 	AdjustDrawRect( LPCRECT lprcOut, LPCRECT lprcFull);
					// ------ impedance calculation
	double Amplitude(double fFreq);
	double Phase(double fFreq);
	double XValue(double fFreq);
	double YValue(double fFreq);
	virtual void Impedance(ZComplex& ZcOut, double fFreq);
					 // ------ more specific stuff
	virtual NAMETYPES GetType(void) const ;		// type of passive object
	virtual ZpPassive *Duplicate(void);		// make a duplicate of this object

					 // ------ drawing stuff
	virtual POINT	GetDrawSize(void);		// get the draw size
	virtual LPCSTR	GetValueSuffix( void);	// get the label suffix

	virtual BYTE	GetOrientation(int nWhich);		// get orientation of each end
	virtual	BYTE	GetOrientation(void)			{ return m_byOrient;	}
					// ---------------- operators
	const ZpPassive& operator= (const ZpPassive& cIn);
	virtual	int		EditProperties();
	virtual int		ImportLine( LPCSTR szLine);
	virtual int		ExportLine( LPSTR szLine);

					// ----------------implementation
	virtual void DoDraw( CDC *pDC, LPCRECT lpRcDraw = (LPRECT )NULL);	// draw the object
	virtual void DrawLabels( CDC *pDC, LPCRECT lprcDraw);
	virtual BOOL HitTest( CPoint cPt, UINT *pnFlags = NULL);	// do a hittest: type of hit -> nFlags 
	virtual void DrawHighlight( CDC *pDC);
			void DrawSubHighlight( CDC *pDC);		// draw for drag-node only


public:
	ZpPassive();
	ZpPassive( const ZpPassive& cIn);
	~ZpPassive();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif



};

/////////////////////////////////////////////////////////////////////////////
// ZpResistor Definition
/////////////////////////////////////////////////////////////////////////////

class ZpResistor : public ZpPassive
{
protected:
	DECLARE_SERIAL(ZpResistor)


public:
	virtual NAMETYPES GetType( void) const 			{ return ptResistor; }
	virtual void Impedance(ZComplex &ZcOut, double dFreq);
	virtual void DoDraw( CDC *pDC, LPCRECT lpRcDraw = (LPRECT )NULL);	// draw the object
	virtual POINT	GetDrawSize();		// get the draw size

public:
	ZpResistor();
	ZpResistor( const ZpResistor& cIn);
	~ZpResistor();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


};


/////////////////////////////////////////////////////////////////////////////
// ZpCapacitor Definition
/////////////////////////////////////////////////////////////////////////////
class ZpCapacitor : public ZpPassive
{
protected:
	DECLARE_SERIAL(ZpCapacitor)


public:
	virtual NAMETYPES GetType(void) const 			{ return ptCapacitor; }
	virtual void Impedance(ZComplex &ZcOut, double dFreq);
	virtual void DoDraw( CDC *pDC, LPCRECT lpRcDraw = (LPRECT )NULL);	// draw the object
	virtual POINT	GetDrawSize();		// get the draw size
	virtual LPCSTR	GetValueSuffix( void)	{ return "F"; }	// get the label suffix


public:
	ZpCapacitor();
	ZpCapacitor( const ZpCapacitor& cIn);
	~ZpCapacitor();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif



};



/////////////////////////////////////////////////////////////////////////////
// ZpInductor Definition
/////////////////////////////////////////////////////////////////////////////
class ZpInductor : public ZpPassive
{
protected:
	DECLARE_SERIAL(ZpInductor)


public:
	virtual NAMETYPES GetType(void ) const 			{ return ptInductor; }
	virtual void Impedance(ZComplex &ZcOut, double dFreq);
	virtual void DoDraw( CDC *pDC, LPCRECT lpRcDraw = (LPRECT )NULL);	// draw the object
	virtual POINT	GetDrawSize();		// get the draw size
	virtual LPCSTR	GetValueSuffix( void)	{ return "H"; }	// get the label suffix

public:
	ZpInductor();
	ZpInductor( const ZpInductor& cIn);
	~ZpInductor();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif



};

/////////////////////////////////////////////////////////////////////////////
// ZpGenerator Definition
/////////////////////////////////////////////////////////////////////////////

class ZpGenerator : public ZpPassive
{
protected:
	DECLARE_SERIAL(ZpGenerator)


public:
	virtual NAMETYPES GetType(void)	const 		{ return ptGenerator; }
	virtual void Impedance(ZComplex &ZcOut, double dFreq);
	virtual void DoDraw( CDC *pDC, LPCRECT lpRcDraw = (LPRECT )NULL);	// draw the object
	virtual POINT	GetDrawSize();		// get the draw size
	virtual int		ImportLine( LPCSTR szLine);
	virtual int		ExportLine( LPSTR szLine);
	virtual BYTE	GetOrientation(int nWhich);		// get orientation of each end
	virtual	BYTE	GetOrientation(void);

public:
	ZpGenerator();
	ZpGenerator( const ZpGenerator& cIn);
	~ZpGenerator();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


};

/////////////////////////////////////////////////////////////////////////////
// ZpDriver Definition
/////////////////////////////////////////////////////////////////////////////
class ZpDriver : public ZpPassive
{
protected:
	DECLARE_SERIAL(ZpDriver)

private:
	DWORD	m_dwDriver;
	CDriver *m_pDriver;
	CDataSet *m_pResponse;
	CDataSet *m_pImpedance;
	BOOL	m_bChart;			// do we chart this guy individually?
	BOOL	m_bOutOfPhase;		// invert the response??
	float	m_fOffset;			// offset of the driver in centimeters

public:
	virtual NAMETYPES GetType(void)	const 		{ return ptDriver; }
	virtual void Impedance(ZComplex &ZcOut, double dFreq);
	virtual void Response( ZComplex &ZcOut, double dFreq);
	virtual double ResponseDb( double dFreq);
	virtual int		ImportLine( LPCSTR szLine);
	virtual int		ExportLine( LPSTR szLine);

	BOOL	IsNotValid( CFolder *pRoot, BOOL bShow = FALSE);		// will this work for network calcs????

	void	SetDoChart( BOOL bNew)			{ m_bChart = bNew; }
	BOOL	DoChart()						{ return m_bChart; }
	float	GetOffset( void)				{ return m_fOffset; }
	void	SetOffset( float fNew)			{ m_fOffset = fNew; }

	DWORD	GetDriver()						{ return m_dwDriver; }
	void	SetDriver(DWORD dwNew)			{ m_dwDriver = dwNew; m_pDriver = NULL; }
	BOOL	IsOutOfPhase()					{ return m_bOutOfPhase; }
	void	SetOutOfPhase( BOOL bNew)		{ m_bOutOfPhase = bNew; }
	void	GetRange(CNamed *pInfo, float* pfStart, float *pfDelta);
	int		GetCount(CNamed *pInfo );
	CDataSet *GetImpedance( void)			{ return m_pImpedance; }
	CDataSet *GetResponse( void)			{ return m_pResponse; }

	void	InitPointers(CObject *pcSource);	// set up the pointers for data i/o

	virtual void DoDraw( CDC *pDC, LPCRECT lpRcDraw = (LPRECT )NULL);	// draw the object
	virtual POINT	GetDrawSize();		// get the draw size

public:
	ZpDriver();
	ZpDriver( const ZpDriver& cIn);
	~ZpDriver();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o
	virtual ZpPassive *Duplicate( void);		// make a duplicate of this object

protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


};



#define ZPASSIVE

#endif
