// dlgsquar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSquare dialog

class CDlgSquare : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgSquare)

// Construction
public:
	CDlgSquare();
	~CDlgSquare();

// Dialog Data
// ------------------------------------
		float	m_fDutyCycle;
		float	m_fFreq;

		CzFormatEdit	m_cDutyCycle;
		CzFormatEdit	m_cFreq;
// ------------------------------------

	//{{AFX_DATA(CDlgSquare)
	enum { IDD = IDD_SQUARE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgSquare)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgSquare)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposScrl2(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgSquare)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
