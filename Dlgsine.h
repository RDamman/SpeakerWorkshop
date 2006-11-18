// dlgsine.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSine dialog

class CDlgSine : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgSine)

// Construction
public:
	CDlgSine();
	~CDlgSine();

// Dialog Data
// ------------------------------------
		float	m_fPhase;
		float	m_fFreq;

		CzFormatEdit	m_cPhase;
		CzFormatEdit	m_cFreq;
// ------------------------------------
	//{{AFX_DATA(CDlgSine)
	enum { IDD = IDD_SINE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgSine)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgSine)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposScrl2(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgSine)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
