// dlgnoise.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNoise dialog

class CDlgNoise : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgNoise)

// Construction
public:
	CDlgNoise();
	~CDlgNoise();

// Dialog Data
		BOOL	m_bUseAll;		// entire frequency range?
		BOOL	m_bUsePink;		// pink noise?
// ------------------------------------
		float	m_fStart;
		float	m_fEnd;

		CzFormatGroup		m_cfEdits;
// ------------------------------------
	//{{AFX_DATA(CDlgNoise)
	enum { IDD = IDD_NOISE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgNoise)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgNoise)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeFend();
	afx_msg void OnChangeFstart();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgNoise)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
