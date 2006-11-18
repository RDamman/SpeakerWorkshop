// DlgCalWizImp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizImpBegin dialog

class CDlgCalWizImpBegin : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCalWizImpBegin)

// Construction
public:
	CDlgCalWizImpBegin();
	~CDlgCalWizImpBegin();

// Dialog Data
	//{{AFX_DATA(CDlgCalWizImpBegin)
	enum { IDD = IDD_CAL_IMP_BEGIN };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizImpBegin)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgCalWizImpBegin)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizEnd dialog

class CDlgCalWizImpEnd : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCalWizImpEnd)

// Construction
public:
	CDlgCalWizImpEnd();
	~CDlgCalWizImpEnd();


// Dialog Data
	float m_fResistor;
	float m_fSeriesRes;

	//{{AFX_DATA(CDlgCalWizImpEnd)
	enum { IDD = IDD_CAL_IMP_END };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizImpEnd)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgCalWizImpEnd)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMeasured();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void enable_Measured( BOOL bOn);
};
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizImpJig1 dialog

class CDlgCalWizImpJig1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCalWizImpJig1)
// Construction
public:
	CDlgCalWizImpJig1();
	~CDlgCalWizImpJig1();

// Dialog Data
	// --------------------------------
	float	m_fResistor;

	CzFormatGroup		m_cfEdits;
	// --------------------------------
	//{{AFX_DATA(CDlgCalWizImpJig1)
	enum { IDD = IDD_CAL_IMP_JIG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizImpJig1)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCalWizImpJig1)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizImpJig2 dialog

class CDlgCalWizImpJig2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCalWizImpJig2)

// Construction
public:
	CDlgCalWizImpJig2();
	~CDlgCalWizImpJig2();

// Dialog Data
	// --------------------------------
	float	m_fResistor;

	CzFormatGroup		m_cfEdits;
	// --------------------------------
	//{{AFX_DATA(CDlgCalWizImpJig2)
	enum { IDD = IDD_CAL_IMP_JIG2 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizImpJig2)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgCalWizImpJig2)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizImpedance

class CDlgCalWizImpedance : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgCalWizImpedance)

// Construction
public:
	CDlgCalWizImpedance(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CDlgCalWizImpBegin		m_dlgBegin;
	CDlgCalWizImpJig1		m_dlgJig1;
	CDlgCalWizImpJig2		m_dlgJig2;
	CDlgCalWizImpEnd		m_dlgEnd;

	CFloatArray				m_ArKnown;
	CFloatArray				m_ArMeasure;
	float					m_fOriginalRes;	// the original series res for replacement
	float					m_fResistor;
	float					m_fSeriesRes;	// the new settings, if set

	CView			*m_pView;	// the current view

// Operations
public:
	void	SetView( CView *pNew)		{ m_pView = pNew; }
	CView	*GetView(void)				{ return m_pView; }


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizImpedance)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgCalWizImpedance();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgCalWizImpedance)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizImpList dialog

class CDlgCalWizImpList : public CDialog
{

// Construction
public:
	CFloatArray * m_pMeasured;
	CFloatArray * m_pKnown;
	CDlgCalWizImpList(CWnd* pParent = NULL);
	~CDlgCalWizImpList();

// Dialog Data
	//{{AFX_DATA(CDlgCalWizImpList)
	enum { IDD = IDD_CAL_IMP_LIST };
	CListBox	m_cMsrOld;
	CListBox	m_cMsrNew;
	CListBox	m_cKnown;
	float	m_fRefNew;
	float	m_fRefOld;
	float	m_fSeriesNew;
	float	m_fSeriesOld;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizImpList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgCalWizImpList)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
