// Complex.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef COPRECORD


typedef enum tagRecordtypes
	{
	rtFrequency = 0,
	rtImpedance = 1,
	rtTime = 2
	} RECORDTYPES;

// these are used as indices into the dword array
typedef enum tagNamedOuttypes
	{
	noDataIn = 0,
	noReferIn = 1,
	noFftData = 2,
	noFftRefer = 3,
	noImpedance = 4,
	noDataOut = 5,
	noResultData = 6,
	noResultRefer = 7,
	noNumResults = 8
	} NAMEDOUTTYPES;

typedef enum tagGatetype
{
	fqFull = 0,
	fqGateStart = 1,
	fqGateAll = 2
} GATETYPE;


// generic recorder oepration class
class COpRecord : public COpCustom
{
private:
		GATETYPE	m_gtFreqType;					// acoustic, anechoic, transfer
		BOOL		m_bIsStopped;					// was it stopped???
		RECORDINGINFO m_cRecInfo;

protected:
		CView		*m_cView;						// the view (needed to send done msg)
		DWORD		m_dwResults[noNumResults];
		DWORD		m_dwGenerator;					// the generator we're using
	
public:
	CNamed  	   *GetDataset( int nWhich);
	void			SetDataset( int nWhich, CNamed *cNew );
	void			SetDataset( int nWhich, DWORD dwID );
	BOOL			HasDataset( int nWhich)		{ return 0 != m_dwResults[nWhich]; }
													// set the times for play and record
	void			SetRecordInfo( RECORDINGINFO *pNewInfo)	{ m_cRecInfo = *pNewInfo; }
	void			GetRecordInfo( RECORDINGINFO *pOldInfo) { *pOldInfo = m_cRecInfo; }

	GATETYPE		GetFreqType(void )				{ return m_gtFreqType; }
	void			SetFreqType( GATETYPE gtNew)	{ m_gtFreqType = gtNew; }

	CNamed			*GetGenerator( void);
	void			SetGenerator( DWORD dwID)		{ m_dwGenerator = dwID;  }

	BOOL			IsStopped()						{ return m_bIsStopped; }

							// for internal use only
protected:													// --------- virtuals
	virtual int		DoStdFinish();							// the usual finishup to a record session

public:
	virtual int		DoRecord( void);
	virtual int		DoPlay( void);
	virtual void	StopSound( void);				// for when looping, or long records...
	BOOL			IsRecording()					{ return m_cRecInfo.m_bIsRecording; }


	virtual int		DoExe( bool bRedo = true);
	virtual int		ProcessInput(void ) = 0;		// do the process

public:
	COpRecord(CNamed *cTarget, CView *cView);
	~COpRecord();

};

class COpRecordStd : public COpRecord
{

public:
	virtual int		ProcessInput( void);
public:
	COpRecordStd(CNamed *cTarget, CView *cView);
	~COpRecordStd();

};


class COpPlayStd : public COpRecord
{

public:
	virtual int		ProcessInput( void);
	virtual int		DoExe( bool bRedo = true);
public:
	COpPlayStd(CNamed *cTarget, CView *cView);
	~COpPlayStd();

};


class COpRecordVol : public COpRecordStd
{

public:
	COpRecordVol(CNamed *cTarget, CView *cView);
	~COpRecordVol();

protected:
	void SetCurrentLoop( int nLoop)		{ m_nCurrentLoop = nLoop; }
	int  GetCurrentLoop( void)			{ return m_nCurrentLoop; }
	void SetMaxLoop( int nLoop)			{ m_nMaxLoop = nLoop; }
	int  GetMaxLoop( void)				{ return m_nMaxLoop; }
	virtual void Describe( UINT idDesc, CNamed *pDest, CDataSet *pData);		// set the description appropriately

private:
	int		m_nCurrentLoop;		// current loop value
	int		m_nMaxLoop;			// max loop value

};

class COpMeasure : public COpRecordStd
{

public:
	COpMeasure(CNamed *cTarget, CView *cView);
	~COpMeasure();

protected:
	void SetCurrentLoop( int nLoop)		{ m_nCurrentLoop = nLoop; }
	int  GetCurrentLoop( void)			{ return m_nCurrentLoop; }
	void SetMaxLoop( int nLoop)			{ m_nMaxLoop = nLoop; }
	int  GetMaxLoop( void)				{ return m_nMaxLoop; }
	int	 CopyOutput( UINT uIDName, int nDataset);
	int	 TrailOutput( UINT uIDName, int nDataset);
	virtual void Describe( UINT idDesc, CNamed *pDest, CDataSet *pData);		// set the description appropriately
	void	DescribeGating( CNamed *pData);
private:
	void DescGating( CNamed *pData);
	void DescStartGate( CNamed *pData);

private:
	int		m_nCurrentLoop;		// current loop value
	int		m_nMaxLoop;			// max loop value

};


class COpMsrTransfer : public COpMeasure
{

public:
	virtual int		ProcessInput( void);
public:
	COpMsrTransfer(CNamed *cTarget, CView *cView);
	~COpMsrTransfer();

};

class COpMsrImpedance : public COpMeasure
{

public:
	virtual int		ProcessInput( void);
public:
	COpMsrImpedance(CNamed *cTarget, CView *cView);
	~COpMsrImpedance();

};


class COpMsrPassive : public COpMeasure
{

public:
	virtual int		ProcessInput( void);
public:
	COpMsrPassive(CNamed *cTarget, CView *cView);
	~COpMsrPassive();

};


class COpMsrCalLoop : public COpMeasure
{
public:
	DWORD			m_dwLastCal;
public:
	virtual int		ProcessInput( void);
public:
	COpMsrCalLoop(CNamed *cTarget, CView *cView);
	~COpMsrCalLoop();
};

class COpMsrCalJig1 : public COpMeasure
{

public:
	virtual int		ProcessInput( void);
public:
	COpMsrCalJig1(CNamed *cTarget, CView *cView);
	~COpMsrCalJig1();

};

class COpMsrBrdJig : public COpMeasure
{

public:
	virtual int		ProcessInput( void);
public:
	COpMsrBrdJig(CNamed *cTarget, CView *cView);
	~COpMsrBrdJig();

};

class COpMsrCalJig2 : public COpMeasure
{

public:
	virtual int		ProcessInput( void);
public:
	COpMsrCalJig2(CNamed *cTarget, CView *cView);
	~COpMsrCalJig2();

};

class COpMsrFrequency : public COpMeasure
{

public:
	virtual int		ProcessInput( void);
public:
	COpMsrFrequency(CNamed *cTarget, CView *cView);
	~COpMsrFrequency();

};

class COpMsrMicrophone : public COpMeasure
{

public:
	virtual int		ProcessInput( void);
	void			MungeInput( UINT idDesc = 0);		// do the input processing
public:
	COpMsrMicrophone(CNamed *cTarget, CView *cView);
	~COpMsrMicrophone();

};

class COpMsrMicTotal : public COpMsrMicrophone
{
public:
	COpMsrMicTotal(CNamed *cTarget, CView *cView);
	~COpMsrMicTotal();
};

class COpMsrMicAnechoic : public COpMsrMicrophone
{
public:
	COpMsrMicAnechoic(CNamed *cTarget, CView *cView);
	~COpMsrMicAnechoic();
};


class COpMsrTime : public COpMeasure
{

public:
	virtual int		ProcessInput( void);
public:
	COpMsrTime(CNamed *cTarget, CView *cView);
	~COpMsrTime();

};

typedef struct tagMsrintermod
	{
	float		fFreq1;			// starting freq
	float		fFreq2;			// ending freq
	float		fPower;			// the power (volume) to use
	} MSRINTERMODINFO;

class COpMsrIntermod : public COpMeasure
{

public:
	virtual int		ProcessInput( void);
	void			SetParms( MSRINTERMODINFO *pInfo);
	void			GetParms( MSRINTERMODINFO *pInfo)	{ *pInfo = m_dInfo; }

protected:
		MSRINTERMODINFO	m_dInfo;

public:
	COpMsrIntermod(CNamed *cTarget, CView *cView);
	~COpMsrIntermod();

};

typedef struct tagMsrDistortinfo
	{
	BOOL		bLogRange;		// do it logish
	int			nStyle;			// how to do it (0=spectrum,1=freq,2=power)
	int			nPoints;		// number of test points
	float		fFreq;			// the freq to use if single
	float		fFreq1;			// starting freq
	float		fFreq2;			// ending freq
	float		fPower;			// the power to use if single
	float		fPower1;		// starting power
	float		fPower2;		// ending power
	float		fWatt;			// watt equivalent
	} MSRDISTORTINFO;


class COpMsrDistortion : public COpMeasure
{

public:
	virtual int		ProcessInput( void);
	void			SetParms( MSRDISTORTINFO *pInfo);
	void			GetParms( MSRDISTORTINFO *pInfo)	{ *pInfo = m_dInfo; }
	int				CalcDistortion(CDataSet *cdOut[], CDataSet *cdSource, float fCenter);

protected:
	MSRDISTORTINFO	m_dInfo;
	CDataSet		*m_Outputs[4];

private:
	void		SetupTimes( float fFreq);


public:
	COpMsrDistortion(CNamed *cTarget, CView *cView);
	~COpMsrDistortion();

};








#define COPRECORD

#endif
