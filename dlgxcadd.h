// dlgxcadd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXcAdd dialog

#ifndef CDLGXCADD

class CDlgXcAdd : public CDialog
{
// Construction
public:
	CDlgXcAdd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgXcAdd)
	enum { IDD = IDD_XCADD };
	int		m_nOperation;
	//}}AFX_DATA

								// used to communicate with app
	DWORD		m_dwPicked;		// currently selected
	DWORD		m_dwSource;		// the source object
	CFolder		*m_pRoot;		// the root for finding strings

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXcAdd)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXcAdd)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowse();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgXcAdd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define CDLGXCADD
#endif
