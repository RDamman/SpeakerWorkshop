// dlgxftru.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXfTruncate dialog

class CDlgXfTruncate : public CDialog
{
// Construction
public:
	CDlgXfTruncate(CWnd* pParent = NULL);   // standard constructor

// ------------------------------------
		float	m_fStart;
		float	m_fEnd;

		CzFormatGroup		m_cfEdits;
// ------------------------------------

// Dialog Data
	//{{AFX_DATA(CDlgXfTruncate)
	enum { IDD = IDD_XFTRUNCATE };
	//}}AFX_DATA

	BOOL	m_bUseMarker;		// use the markers?
	float	m_fStartMarker;
	float	m_fEndMarker;		// to set these up front


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXfTruncate)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXfTruncate)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEnd();
	afx_msg void OnChangeStart();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgXfTruncate)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
