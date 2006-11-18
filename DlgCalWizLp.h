// DlgCalWizLp.h : header file
//

#ifndef CALWIZLOOP

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizLoopEnd dialog

class CDlgCalWizLoopEnd : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCalWizLoopEnd)

// Construction
public:
	CDlgCalWizLoopEnd();
	~CDlgCalWizLoopEnd();

// Dialog Data
	//{{AFX_DATA(CDlgCalWizLoopEnd)
	enum { IDD = IDD_CAL_LP_END };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizLoopEnd)
	public:
	virtual void OnFinalRelease();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgCalWizLoopEnd)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgCalWizLoopEnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizLoopBegin dialog

class CDlgCalWizLoopBegin : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCalWizLoopBegin)

// Construction
public:
	CDlgCalWizLoopBegin();
	~CDlgCalWizLoopBegin();

// Dialog Data
	//{{AFX_DATA(CDlgCalWizLoopBegin)
	enum { IDD = IDD_CAL_LP_BEGIN };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizLoopBegin)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgCalWizLoopBegin)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizLoopJig dialog

class CDlgCalWizLoopJig : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCalWizLoopJig)

// Construction
public:
	CDlgCalWizLoopJig( );   // standard constructor
	~CDlgCalWizLoopJig();

// Dialog Data
	//{{AFX_DATA(CDlgCalWizLoopJig)
	enum { IDD = IDD_CAL_LP_JIG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizLoopJig)
	public:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCalWizLoopJig)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizLoop

class CDlgCalWizLoop : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgCalWizLoop)

// Construction
public:
	CDlgCalWizLoop(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CDlgCalWizLoopBegin		m_dlgBegin;
	CDlgCalWizLoopJig		m_dlgJig;
	CDlgCalWizLoopEnd		m_dlgEnd;

	CView			*m_pView;	// the current view

// Operations
public:
	void	SetView( CView *pNew)		{ m_pView = pNew; }
	CView	*GetView(void)				{ return m_pView; }


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizLoop)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgCalWizLoop();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgCalWizLoop)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#define CALWIZLOOP
#endif

