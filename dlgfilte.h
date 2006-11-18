// dlgfilte.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFilter dialog

class CDlgFilter : public CDialog
{
// Construction
public:
	CDlgFilter(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
// ------------------------------------
		float	m_fLowFreq;
		float	m_fHiFreq;
		float	m_fRipple;

		CzFormatGroup		m_cfEdits;
// ------------------------------------
	//{{AFX_DATA(CDlgFilter)
	enum { IDD = IDD_XFFILTER };
	CStatic	m_cImage;
	int		m_nShape;
	int		m_nType;
	UINT	m_nOrder;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFilter)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFilter)
	afx_msg void OnSelchangeFtype();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgFilter)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
