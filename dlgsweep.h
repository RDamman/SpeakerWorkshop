// dlgsweep.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSweep dialog

class CDlgSweep : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgSweep)

// Construction
public:
	CDlgSweep();
	~CDlgSweep();

// Dialog Data
// ------------------------------------
		float	m_fStart;
		float	m_fEnd;

		CzFormatGroup		m_cfEdits;
// ------------------------------------


	//{{AFX_DATA(CDlgSweep)
	enum { IDD = IDD_SWEEP };
	BOOL	m_bSmooth;
	UINT	m_nSteps;
	//}}AFX_DATA

	BOOL	m_bLinear;		// almost afx data but radio button related


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgSweep)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgSweep)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgSweep)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
