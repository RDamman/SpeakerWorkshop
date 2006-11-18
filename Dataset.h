
/////////////////////////////////////////////////////////////////////////////
// Dataset.h : The datasets
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CDATASET
				// we need to fix roundoff error so anything added to x*1000 would work
#define FTOI(x) ( (INT32 )(0.49f + (x)*1000) )
#define ITOF(x) ( ((float )x)/1000 )

typedef CArray<INT32,INT32> CInt32Array;				// similarly...


class CDataSet : public CGraphed
{

	friend class CDlgDataset;

protected: // create from serialization only
	DECLARE_SERIAL(CDataSet)

// Attributes
public:

protected:
	time_t			m_tTime;				// time & date it was sampled (seconds since 1/1/70)
	int				m_nIdGenerator;			// id of the generator that built this
	CInt32Array		m_ciData;				// the data encoded as 32 bit int
	CInt32Array		m_ciPhase;				// the phase encoded as 32 bit int
//	CUom			m_cUom;					// unit of msure (0=time,1=freq,2=ohms,3=spl)
	float			m_fStart;				// start X value for data
	float			m_fDelta;				// delta value for data
	UNITMSR			m_nBaseUnit;			// unit of measure for base (time,freq,...)
	DATAMSR			m_nDataUnit;			// unit of measure for Y axis (dbw,dbv,v,w)


private:
	
// Operations
public:
	CDataSet();

	virtual int EditProperties(CWnd *pWnd, CObject *cSubject = NULL);	// bring up properties dbox
	virtual void DialogInit( CDialog *pcDlg);			// initialize the dialog
										// get the generator for this guy
//	int  GetGenerator()					{ return m_nIdGenerator;	}
//	void SetGenerator(int nId)			{ m_nIdGenerator = nId;		}

	float	GetStart()					{ return m_fStart; }
	void	SetStart( float m_fSet)		{ m_fStart = m_fSet; }
	float	GetDelta()					{ return m_fDelta;	}
	void	SetDelta( float m_fSet)		{ m_fDelta = m_fSet; }
//	UNITMSR	GetUOM()					{ return m_cUom.GetUnit();	}
//	void	SetUOM(UNITMSR nSet)		{ m_cUom.SetUnit( nSet);	}
	UNITMSR	GetUOM()					{ return m_nBaseUnit;	}
	void	SetUOM(UNITMSR nSet)		{ m_nBaseUnit = nSet;	}
	DATAMSR GetDOM()					{ return m_nDataUnit;		}
	void	SetDOM(DATAMSR nSet)		{ m_nDataUnit = nSet;		}
	int		GetCount()					{ return m_ciData.GetSize(); }
	void	DeleteAll()					{ m_ciData.RemoveAll(); m_ciPhase.RemoveAll(); }
	bool	DeleteLeft( int iCount);	// remove data from the left

	int		SetSize( int nNewSize, int nNewPhase);
	int		SetSize( int nNewSize );
	BOOL	HasPhase( void);

	BOOL	WalkValue( float& fOut, DATASEL nChannel, float fValue, float fStart, float fDelta);

			void  SetAbsolute( int nCoord, float fAmp, float fPhase);	// set the data as amp,phase
	virtual void  SetRectangular( int nCoord, float fX, float fY);		// set the data as rectangular
			void  GetRectangular( int nCoord, float *fX, float *fY);
			void  GetRectangular( int nCoord, ZComplex *zcDest);
			void  GetRectangularAt( float fFreq, float *fX, float *fY);
			void  GetRectangularAt( float fFreq, ZComplex *zcDest);

			void  SetDataAt( int nCoord, INT32 dwAmp, INT32 dwPhase);	// set the actual data
			void  SetDataAt( int nCoord, INT32 dwAmp);					// set the actual data (no phase)
			void  SetPhaseAt( int nCoord, INT32 dwPhase);				// set the actual data (no data)
			void  SetDataEasy( float fFreq, float fAmp, float fPhase);	// set it to a freq

			INT32 GetDataAt( int nCoord);								// get the actual data
			INT32 GetPhaseAt( int nCoord);								// get the actual data
			float DataValueAt( float fCoord, int nMethod = 0);			// extrapolate to a value
			float DataValueAt( int nCoord, int nMethod = 0);			// extrapolate to a value
			float PhaseValueAt( int nCoord, int nMethod = 0);			// extrapolate to a value
			float PhaseValueAt( float fCoord, int nMethod = 0);			// extrapolate to a value

	virtual int	Import( LPCSTR szFileName);								// import some data
	virtual int Export( LPCSTR szFileName);								// export some data
	virtual void GetFilter( CString& csExt, CString& csFilter);

	virtual float Minimum(DATASEL ndWhich);
	virtual float Maximum(DATASEL ndWhich);
	virtual float Minimum(DATASEL ndWhich, float fStart, float fEnd);
	virtual float Maximum(DATASEL ndWhich, float fStart, float fEnd);
	virtual float DataAt( DATASEL ndWhich, int nCoord);						// get the actual data
		   double ConvertToFormat( float fAmplitude, DATAMSR nUom = uomVolts);			// convert to other format
			int   FreqToIndex( float fFreq);

	virtual int  AddData( INT32 nAmp, INT32 nPhase);
	virtual int	 AddData( INT32 nAmp);		// only add amplitude
	virtual void CopyHeader( CDataSet *cdSource);	// copy the data from the source

	virtual BOOL	CreateChart( CNamed *cBase = NULL);			// build a new chart object to be graphed

// Implementation
public:
	virtual DWORD GetObjectSize( BOOL );
	virtual ~CDataSet();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

	virtual CNamed *Duplicate();				// make a duplicate object (different id)
	CNamed &operator=(const CNamed &cIn);
	CDataSet &operator=(const CDataSet &cIn);

	virtual NAMETYPES GetType(void) const		{ return ntDataSet; }


#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:

};


#define CDATASET

#endif
