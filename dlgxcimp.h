// dlgxcimp.h : header file
//

#ifndef DLGXCIMP

/////////////////////////////////////////////////////////////////////////////
// CDlgXcImpedance dialog

class CDlgXcImpedance : public CDialog
{
// Construction
public:
	CDlgXcImpedance(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgXcImpedance)
	enum { IDD = IDD_XCIMP };
	//}}AFX_DATA

								// used to communicate with app
	DWORD	m_dwPicked;			// which one is our second???
	CNamed  *m_pRoot;			// the root object


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXcImpedance)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXcImpedance)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowse();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgXcImpedance)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};


#define DLGXCIMP
#endif
