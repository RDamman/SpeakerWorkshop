// dlgmsrpa.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMsrPassive dialog

class CDlgMsrPassive : public CDialog
{
// Construction
public:
	CDlgMsrPassive(CWnd* pParent = NULL);   // standard constructor

	static	bool	IsShowing( void)			{ return m_bIsShowing; }
	static	CDlgMsrPassive *GetPointer( void)	{ return m_pThis; }
// Dialog Data
	//{{AFX_DATA(CDlgMsrPassive)
	enum { IDD = IDD_PASSIVERESULT };
	CString	m_csOValue;
	CString	m_csValue;
	CString	m_csType;
	//}}AFX_DATA

// user variables
	float	m_fValue;
	float	m_fOther;
	int		m_nType;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMsrPassive)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	static bool				m_bIsShowing;
	static CDlgMsrPassive * m_pThis;

	// Generated message map functions
	//{{AFX_MSG(CDlgMsrPassive)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgMsrPassive)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
