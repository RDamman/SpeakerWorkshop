// dlgsawto.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSawtooth dialog

class CDlgSawtooth : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgSawtooth)

// Construction
public:
	CDlgSawtooth();
	~CDlgSawtooth();

// Dialog Data
// ------------------------------------
		float	m_fFreq;

		CzFormatEdit	m_cFreq;
// ------------------------------------

	//{{AFX_DATA(CDlgSawtooth)
	enum { IDD = IDD_SAWTOOTH };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgSawtooth)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgSawtooth)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgSawtooth)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
