// dlgxfsca.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXfScale dialog

class CXformScale;			// predef


class CDlgXfScale : public CDialog
{
// Construction
public:
	CDlgXfScale(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
// ------------------------------------
		float	m_fdB;
		float	m_fFactor;

		CzFormatEdit	m_cdB;
		CzFormatEdit	m_cFactor;
// ------------------------------------

	//{{AFX_DATA(CDlgXfScale)
	enum { IDD = IDD_XFSCALE };
	int		m_nMethod;
	//}}AFX_DATA

	CNamed		*m_cdSource;			// the data source
	CXformScale *m_pCX;				// the delay transform object
	BOOL		 m_bUseDb;		// use absolute or db


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXfScale)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXfScale)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeFactor();
	afx_msg void OnChangeDb();
	afx_msg void OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposScrl2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnApply();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgXfScale)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
