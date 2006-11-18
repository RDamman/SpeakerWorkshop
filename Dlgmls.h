// dlgmls.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMls dialog

class CDlgMls : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgMls)

// Construction
public:
	CDlgMls();
	~CDlgMls();

// Dialog Data
	//{{AFX_DATA(CDlgMls)
	enum { IDD = IDD_MLS };
	CSliderCtrl	m_clSize;
	BOOL	m_bEmphasis;
	CString	m_csSize;
	BOOL	m_bCorrelate;
	//}}AFX_DATA

	DWORD			m_dwNumber;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgMls)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgMls)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgMls)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
