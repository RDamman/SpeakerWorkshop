// dlgrenam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRename dialog

class CDlgRename : public CDialog
{
// Construction
public:
	CDlgRename(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRename)
	enum { IDD = IDD_RENAME };
	CString	m_csName;
	//}}AFX_DATA

	CString m_csTitle;					// the title to use...


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRename)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRename)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
