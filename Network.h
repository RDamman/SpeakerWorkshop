// Named.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CNETWORK

class COpMulti;

class CNetwork : public CNamed
{

	friend class CDlgNetwork;

protected: // create from serialization only
	DECLARE_SERIAL(CNetwork)

// Attributes
private:
	BOOL			m_bIsDragging;			// only during drag and drop, not serialized

protected:
	CObArray	 	m_cDiscretes;			// the discrete components
	CObArray	 	m_cDrivers;				// the drivers (also discrete components)
	BOOL			m_bMainResponse;		// do we build a total reponse???
	BOOL			m_bMainImpedance;		// do we generate impedance??
	BOOL			m_bAutoChart;			// do a chart when we generate response

public:
	void			CalculateResponse(COpMulti *pOpCode, CObArray &cData);
	void			Optimize(COpMulti *pOpCode, CObArray &cData);
	CObject			*GetDiscrete( int nWhich);
	void			SetDiscrete( int nWhich, CObject *pNew);
	CObArray		*GetDiscreteArray( void)		{ return &m_cDiscretes;	}
	CObject			*GetDriver( int nWhich);
	CObArray		*GetTotalArray( void);
	int				GetTotalCount( void);
	CObject			*GetPassive( int nWhich);
	void			SetDriver( int nWhich, CObject *pNew);
	int				AddDiscrete( CObject *pNew);
	int				AddDriver( CObject *pNew);
	int				AddCrossover( int nWhich, int nType, int nStyle, int nOrder, float fFS, float fDCRes);
	int				AddLPad( float fLevel, float fDCRes);
	int				AddZobel( DWORD dwDriver, int nType, float fFrequency, BOOL bUseDriver);
	CObArray		*GetDriverArray( void)			{ return &m_cDrivers;	}
	int				RenumberNodes( void);			// make nodes go 0...n, returns number of max node
	BOOL			HasResponse( void)				{ return m_bMainResponse; }
	BOOL			HasImpedance( void)				{ return m_bMainImpedance; }
	BOOL			HasAutoChart( void)				{ return m_bAutoChart; }
	BOOL			IsDragging( void)				{ return m_bIsDragging; }
	void			GenResponse(BOOL bNew)			{ m_bMainResponse = bNew; }
	void			GenImpedance(BOOL bNew)			{ m_bMainImpedance = bNew; }
	void			GenAutoChart(BOOL bNew)			{ m_bAutoChart = bNew; }
	void			SetDragging( BOOL bNew)			{ m_bIsDragging = bNew; }
	void			DoDraw( CDC *pDC, LPCRECT lpWhere);
	void			GetBounds( CRect& rcBound, BOOL bSelect);

	virtual int	Import( LPCSTR szFileName);								// import some data
	virtual int Export( LPCSTR szFileName);								// export some data
	virtual void GetFilter( CString& csExt, CString& csFilter);
							// subobject functions
	CObject 		*GetClosest( LPPOINT pcPos);
	CObject			*GetHighlighted( void);
	void			SetHighlighted( CObject *cNew, BOOL bOnly = TRUE);
	void			SetRectHighlight( POINT ptStart, POINT ptEnd);
	POINT			MoveObjects( POINT ptMove);	// return new move point
	int				FillObjArray( CObArray &cSelected, BOOL bHighlight = TRUE); // fill cSelected
	CNamed 			*CreateSubCopy(BOOL bHighlight, BOOL bUnHighlight );
	int 			AppendNet( CNetwork *pSource);

	CObject			*GetObjByName( CString &cName);
	void			SetObjNodes( CObject *cWho, int nNode, CObject *cOther, int nOther, BOOL bAdd = FALSE);
	void 			GetObjEndLocation( CObject *cWho, LPPOINT lpptWhere);
	void 			GetObjLocation( CObject *cWho, LPPOINT lpptWhere);
	void 			SetObjLocation( CObject *cWho, LPPOINT lpptWhere);
	void			SetObjValue( CObject *cWho, float fNewValue);
	float			GetObjValue( CObject *cWho);

	int				ValidateNet( BOOL bShow = FALSE);		// make sure it works....

	int				EditComponent(CWnd *pParent, CObject *cWho);
										// -------- clipboard stuff
	int				CutObjects( BOOL bOnly);
	int				CopyObjects( BOOL bOnly);
	int				PasteObjects( void);
	int				DeleteObjects( BOOL bOnly);

	
			// dialog info

// Operations
public:
 	CNetwork();
	virtual int EditProperties(CWnd *pWnd, CObject *cSubject = NULL);	// bring up properties dbox

// Implementation
public:
	virtual DWORD GetObjectSize( BOOL );
	virtual ~CNetwork();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

	virtual CNamed *Duplicate();				// make a duplicate object (different id)
	virtual CNamed &operator=(const CNamed &cIn);
	CNetwork &operator=(const CNetwork &cIn);

	virtual NAMETYPES GetType(void) const		{ return ntNetwork; }

#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:

};


#define CNETWORK

#endif
