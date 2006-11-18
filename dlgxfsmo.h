// dlgxfsmo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXfSmooth dialog

class CXformSmooth;			// predef

class CDlgXfSmooth : public CDialog
{
// Construction
public:
	CDlgXfSmooth(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
// ------------------------------------
		float	m_fCustom;

		CzFormatGroup		m_cfEdits;
// ------------------------------------

	//{{AFX_DATA(CDlgXfSmooth)
	enum { IDD = IDD_XFSMOOTH };
	int		m_nMethod;
	//}}AFX_DATA

	CNamed		*m_cdSource;			// the data source
	CXformSmooth *m_pCX;				// the delay transform object
	int			 m_nStyle;					// what size to use
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXfSmooth)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXfSmooth)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeCustom();
	afx_msg void OnApply();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgXfSmooth)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
