// Named.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef NAMEDARRAY

typedef enum tagNametype
	{
	ntAny = 10000,
							// --------- base name stuff
	ntGenerator = 0,
	ntDataSet = 1,
	ntChart = 2,
	ntEnclosure = 3,
	ntNetwork = 4,
	ntRoom = 5,
	ntDriver = 6,
	ntFolder = 7,
							// --------- chart stuff
	ntSubChart = 100,
	ntDataLine = 101,
	ntGrid = 102,
	ntLegend = 103,
	ntTitle = 104,
	ntBorder = 105,
	ntMarker = 106,
	ntNote = 107,
	ntInside = 108,
	ntDataTag = 109,
							// --------- passive stuff
	ptResistor = 200,
	ptCapacitor = 201,
	ptInductor = 202,
	ptGenerator = 203,		// these first 4 agree with the combo box in IDD_NETLIST
	ptDriver = 204
	} NAMETYPES;

#define NAMEMAXIMUM (ntFolder)

#define NONAME_ID (0)

typedef enum tagUnitmsr
	{
	uomAny = 10000,
	uomTime = 0,
	uomFreq = 1,
	uomOhms = 2,
	uomNone  = 3
	} UNITMSR;

typedef enum tagDatamsr
	{
	uomdAny = 10000,
	uomDbw = 0,
	uomDbv = 1,
	uomWatts = 2,
	uomVolts = 3
	} DATAMSR;

typedef enum tagDatasel
	{
	dataFreq = 0,
	dataAmp = 1,
	dataPhase = 2
	} DATASEL;


// attributes (flags in dword)
#define ATTRIB_READONLY		1
#define ATTRIB_SYSTEM		2
#define ATTRIB_HIDDEN		4
#define ATTRIB_TEMPORARY	8

class CNamed : public CObject
{
	DECLARE_SERIAL(CNamed)
protected: // create blank from serialization only
	CNamed();

// Attributes
public:
	bool IsSystem( void);
	bool IsReadOnly( void);
	BOOL IsType( NAMETYPES ntType, UNITMSR nUom = uomAny);
static void CheckID(DWORD dwNew);

private:
				// permanent
	CString	m_szName;
	CString m_szDescription;

	DWORD	m_dwID;

	time_t	m_tCreated;			// date and time created
	time_t	m_tLastEdit;		// date and time of last edit

	DWORD	m_dwAttributes;		// attributes (flags)

				// temporary
	CNamed  *m_cRoot;			// root object to find stuff by - not serialized
	int		m_nSchema;			// the version schema during load

// Operations
public:
	DWORD	GetNextID( void);		// get the next available id and increment

	CString& GetName()					{ return m_szName; }
	void SetName( const CString &);
	CString& GetDescription()			{ return m_szDescription; }
	void SetDescription( const CString &strDesc);
	CString GetFullName();
	int		GetSchema( void)			{ return m_nSchema; }
	
	DWORD	GetID()						{ return m_dwID; }
	void	SetID(DWORD dwNew)			{ m_dwID = dwNew; }
	CFolder  *GetRootObject(void)		{ return (CFolder *)m_cRoot; }
	CFolder  *FindParent(void);
	void	SetRootObject(CNamed *pNew) { m_cRoot = pNew; }

	time_t	GetCreated( void)				{ return m_tCreated; }
	void	SetCreated( time_t tNew)		{ m_tCreated = tNew; }
	time_t	GetLastEdit( void)				{ return m_tLastEdit; }
	void	SetLastEdit( void);
	void	SetDateStrings( CString& csCreated, CString &csLastEdit);
   
	DWORD	GetAttributes( void)						{ return m_dwAttributes; }
	void	SetAttributes( DWORD dwNew)					{ m_dwAttributes = dwNew; }

	bool	IsTemporary( void);
	void	SetTemporary( bool bNew);	// set it to temporary or not

	CNamed  *FindByID( DWORD dwID);				// look through the tree for this one...
	bool	SetPointerByID( CNamed *pNew);		// use this pointer with this id
	CNamed  *FindByName( LPCSTR lpszName, BOOL bAll = TRUE);		// look through the tree for this one...
	CNamed	*CreateByName( LPCSTR lpszName, NAMETYPES nType);	// look it up and don't build if it exists, else build it
	virtual CDialog *GetDialog();		// get the properties dialog
	virtual void DialogInit( CDialog *pcDlg);			// initialize the dialog
	virtual NAMETYPES GetType() const;
	virtual CNamed *Duplicate();				// make a duplicate object (different id)

	virtual CDocument *GetDocument( void);
												// ------------------------ import/export
	virtual int	Import( LPCSTR szFileName);								// import some data
	virtual int Export( LPCSTR szFileName);								// export some data
	virtual void GetFilter( CString& csExt, CString& csFilter);

// For use at a higher level
	void UpdateViews( void);
	virtual int EditProperties(CWnd *pWnd, CObject *cSubject = NULL);	// bring up properties dbox

// Implementation
public:
	virtual ~CNamed();
	virtual CNamed &operator=(const CNamed &cIn);
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
	virtual DWORD GetObjectSize( BOOL bDive = FALSE);

protected:

};


// CGraphed
//
/////////////////////////////////////////////////////////////////////////////
class CGraphed : public CNamed
{
protected: // create blank from serialization only
	DECLARE_SERIAL(CGraphed)
	CGraphed();

			// attributes
	CSubChart *m_cChart;
public:
	CSubChart	   *GetChart()					{ return m_cChart; }
	void			SetChart( CSubChart *cNew);
	virtual BOOL	CreateChart( CNamed *cBase = NULL);		// build a new chart object to be graphed

// Implementation
public:
	virtual ~CGraphed();
	virtual CNamed &operator=(const CNamed &cIn);
	CGraphed &operator=(const CGraphed &cIn);
	virtual void Serialize(CArchive& ar);	// overridden for Graphed i/o
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif

	virtual CNamed *Duplicate( void);				// make a duplicate object (different id)

};


// SmartArray.h : SmartArray Components Class
//
/////////////////////////////////////////////////////////////////////////////

class CNamedArray : public CObArray
{

	DECLARE_SERIAL( CNamedArray)
	
public:
	CNamedArray();

// Attributes
public:

protected:

// Operations
public:  
//	CNamedArray &CNamedArray::operator=(CNamedArray &cIn);
	void DeleteEntire();		// same as document type deletecontents 
	void FillList( CListBox &);
	CNamed *GetNamedAt( int );

// Implementation
public:
	virtual ~CNamedArray();
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);	// overridden for Named array i/o

protected:

};

#define NAMEDARRAY

#endif
