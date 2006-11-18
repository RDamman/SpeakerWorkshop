// zFormEdt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CzFormatEdit window


#ifndef ZFORMATEDIT

// ---------------------------------
//	Here's how we set up a group
// ---------------------------------

typedef struct tagFORMATGRP
	{
	UINT	idControl;
	UINT	idBuddy;
	float	fMin;
	float	fMax;
	float	*pfValue;
	} FormatGroup;

typedef struct tagGroupMetric
	{
	UINT idControl;
	UINT idStatic;
	METRICS mBase;
	} GroupMetric;


class CzFormatEdit
{
// Construction
public:
	CzFormatEdit();

// Attributes
private:
	CWnd			*m_pParent;
	int				 m_nDigits;				// formatting style (# of digits)
	float			 m_fValue;				// current value
	float			 m_fMin;				// min allowed value
	float			 m_fMax;				// max allowed value
	UINT			 m_uEdit;				// the edit field id
	UINT			 m_uSpin;				// the spin button id
	UINT			 m_uStatic;				// the static (metric) id
	METRICS			 m_BaseMetric;			// the base metric to use with this
	METRICS			 m_Metric;				// the current metric to use with this

// Operations
public:
	static	float	ConvertBaseToBase( float fValue, METRICS mDest, METRICS mSource);
public:
	bool	IsValid( void);					// is the char string valid entry???
	float	GetValue( void);				// always returns a valid value
	void	SetValue( float fNew);			// set chars to new value
	void	DDX_Value( CDataExchange *pDX, float& fValue);	// for dboxes
	void	Subclass( CWnd *pParent, UINT nID, UINT uBuddy = 0);
	void	ProcessDelta( int iDelta);
	void	SetLimits( float fMin, float fMax);
	void	GetLimits( float *fMin, float *fMax)		{ *fMin = m_fMin; *fMax = m_fMax; }
	UINT	GetEditID( void);
	UINT	GetBuddyID( void);
	UINT	GetStaticID( void);
	void	BaseMetric( METRICS mBase, CStatic *pStatic);	// set the base metric and static field
	void	SetMetric( METRICS mNew);		// set a new metric
	void	SetMetricType( BOOL bIsMetric);	// set the metric type
	void	CycleMetric();					// cycle through the metrics (doubleclick)
	METRICS	GetNextMetric( METRICS metStart);		// get the next cyclic metric
	void	RightClick();					// right click the static metric display
	void	SetDigits( int nNew)		{ m_nDigits = nNew; }
	int		GetDigits( void)			{ return m_nDigits; }

private:
	float	GetDisplayValue( void);			// get the displayed value
	void	SetDisplayValue( float fNew);	// set the displayed value
	float	XtoBase( float fValue);			// convert to base metric
	float	XfromBase( float fValue);		// convert to current metric
	void	DrawMetric( void);				// fill the static field with the right text string

// Overrides

// Implementation
public:
	virtual ~CzFormatEdit();

	// Generated message map functions
protected:

};

class CzFormatGroup
{
// Construction
public:
	CzFormatGroup();
// Attributes
private:
	CPtrArray	m_pControls;		// the array of controls
	CPtrArray	m_pValues;			// pointers to the floating values
	CWnd		*m_pParent;			// parent dialog box
// Overrides

public:
	int AttachGroup( CWnd *pParent, const FormatGroup pNewGroup[]);
	int	AttachMetrics( const GroupMetric pBaseMetrics[]);
	void DetachGroup( void);
	CzFormatEdit *GetControl( UINT idControl);
	CzFormatEdit *GetBuddy( UINT idBuddy);

	void	DDX_All( CDataExchange *pDX);				// for dboxes
	void	ProcessAllDelta( NMHDR* pNMHDR);
	int		ProcessLeftClick( UINT nFlags, CPoint point);	// switch units if allowed
	int		ProcessRightClick( UINT nFlags, CPoint point);	// switch units if allowed

// Implementation
public:
	virtual ~CzFormatGroup();

	// Generated message map functions
protected:

};

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CzFormatStatic window

class CzFormatStatic : public CStatic
{
// Construction
public:
	CzFormatStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CzFormatStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CzFormatStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CzFormatStatic)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#define ZFORMATEDIT
#endif
