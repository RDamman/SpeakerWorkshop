// dlgxfdel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXfDelay dialog

class CXformDelay;			// predef

class CDlgXfDelay : public CDialog
{
// Construction
public:
	CDlgXfDelay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	CNamed	 *m_cdSource;			// the data source
	CXformDelay *m_pCX;				// the delay transform object
// ------------------------------------
		float	m_fFactor;
		CzFormatEdit	m_cFactor;
// ------------------------------------

	//{{AFX_DATA(CDlgXfDelay)
	enum { IDD = IDD_XFDELAY };
	CStatic	m_txtDelay;
	BOOL	m_bRemoveExcess;
	//}}AFX_DATA

	void SetSource( CNamed *pSource)	{ m_cdSource = pSource; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXfDelay)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXfDelay)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnApply();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgXfDelay)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
