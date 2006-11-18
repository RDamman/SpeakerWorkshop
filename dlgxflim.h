// dlgxflim.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXfLimit dialog

class CDlgXfLimit : public CDialog
{
// Construction
public:
	CDlgXfLimit(CWnd* pParent = NULL);   // standard constructor

// ------------------------------------
		float	m_fMin;
		float	m_fMax;

		CzFormatEdit	m_cMin;
		CzFormatEdit	m_cMax;
// ------------------------------------

// Dialog Data
	//{{AFX_DATA(CDlgXfLimit)
	enum { IDD = IDD_XFLIMIT };
	//}}AFX_DATA

	BOOL	m_bLimitMin;
	BOOL	m_bLimitMax;		// do we limit these guys
	float	m_fCurrentMin;
	float	m_fCurrentMax;		// to place into the static fields


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXfLimit)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXfLimit)
	afx_msg void OnChangeMax();
	afx_msg void OnChangeMin();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposScrl2(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgXfLimit)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
