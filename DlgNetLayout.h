// DlgNetLayout.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNetLayout dialog

class CDlgNetLayout : public CDialog
{
// Construction
public:
	CDlgNetLayout(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNetLayout)
	enum { IDD = IDD_NETLAYOUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	int		m_nLayStyle;		// which style to use/pick


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNetLayout)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNetLayout)
	virtual BOOL OnInitDialog();
	afx_msg void OnHorz1();
	afx_msg void OnHorz2();
	afx_msg void OnHorz3();
	afx_msg void OnVert1();
	afx_msg void OnVert2();
	afx_msg void OnVert3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgNetLayout)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
