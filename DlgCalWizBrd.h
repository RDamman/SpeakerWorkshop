// DlgCalWizBrd.h : header file
//

#ifndef CALWIZBOARD


/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizBrdBegin dialog

class CDlgCalWizBrdBegin : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCalWizBrdBegin)

// Construction
public:
	CDlgCalWizBrdBegin();
	~CDlgCalWizBrdBegin();

// Dialog Data
	//{{AFX_DATA(CDlgCalWizBrdBegin)
	enum { IDD = IDD_CAL_BRD_BEGIN };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizBrdBegin)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgCalWizBrdBegin)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizBrdEnd dialog

class CDlgCalWizBrdEnd : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCalWizBrdEnd)

// Construction
public:
	CDlgCalWizBrdEnd();
	~CDlgCalWizBrdEnd();

// Dialog Data
	//{{AFX_DATA(CDlgCalWizBrdEnd)
	enum { IDD = IDD_CAL_BRD_END };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizBrdEnd)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgCalWizBrdEnd)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizBrdJig dialog

class CDlgCalWizBrdJig : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCalWizBrdJig)

// Construction
public:
	CDlgCalWizBrdJig();
	~CDlgCalWizBrdJig();

// Dialog Data
	// --------------------------------
	float	m_fResistor;

	CzFormatGroup		m_cfEdits;
	// --------------------------------
	//{{AFX_DATA(CDlgCalWizBrdJig)
	enum { IDD = IDD_CAL_BRD_JIG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizBrdJig)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgCalWizBrdJig)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizBoard

class CDlgCalWizBoard : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgCalWizBoard)

// Construction
public:
	CDlgCalWizBoard(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CDlgCalWizBrdBegin		m_dlgBegin;
	CDlgCalWizBrdJig		m_dlgJig;
	CDlgCalWizBrdEnd		m_dlgEnd;

	CView			*m_pView;	// the current view

	TESTMSR			m_tTest;	// the original values

	float			m_fResist;
	float			m_fCap;				// new values
	float			m_fReference;		// the reference resistor

// Operations
public:
	void	SetView( CView *pNew)		{ m_pView = pNew; }
	CView	*GetView(void)				{ return m_pView; }


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizBoard)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgCalWizBoard();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgCalWizBoard)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#define CALWIZBOARD
#endif

