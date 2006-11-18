// dlggenus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGenUserDef dialog

class CDlgGenUserDef : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgGenUserDef)

// Construction
public:
	CDlgGenUserDef();
	~CDlgGenUserDef();

// Dialog Data
	//{{AFX_DATA(CDlgGenUserDef)
	enum { IDD = IDD_USERWAVE };
	CString	m_csUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgGenUserDef)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgGenUserDef)
	afx_msg void OnBrowsewave();
	afx_msg void OnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgGenUserDef)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CDlgGenWarble dialog

class CDlgGenWarble : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgGenWarble)

// Construction
public:
	CDlgGenWarble();
	~CDlgGenWarble();

// Dialog Data
// ------------------------------------
		float	m_fRate;
		float	m_fCenter;
		float	m_fOctave;

		CzFormatEdit	m_cRate;
		CzFormatEdit	m_cCenter;
		CzFormatEdit	m_cOctave;
// ------------------------------------

	//{{AFX_DATA(CDlgGenWarble)
	enum { IDD = IDD_WARBLE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgGenWarble)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgGenWarble)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposScrl2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposScrl3(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgGenWarble)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
