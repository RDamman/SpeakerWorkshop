// DlgPrfIm.h : header file
//

#ifndef CDLGPREFIMPEDANCE


/////////////////////////////////////////////////////////////////////////////
// CDlgPrefImpedance dialog

class CDlgPrefImpedance : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgPrefImpedance)

// Construction
public:
	CDlgPrefImpedance();
	~CDlgPrefImpedance();

	public:
		float	m_fResistor;
		float	m_fSeriesRes;
		float	m_fInputRes;
		float	m_fInputCap;

		CzFormatEdit	m_cResistor;
		CzFormatEdit	m_cSeriesRes;
		CzFormatEdit	m_cInputRes;
		CzFormatEdit	m_cInputCap;


// Dialog Data
	//{{AFX_DATA(CDlgPrefImpedance)
	enum { IDD = IDD_PREFIMPEDANCE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgPrefImpedance)
	public:
	virtual void OnFinalRelease();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPrefImpedance)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposGeneric1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposGeneric2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposGeneric3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposGeneric4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTest();
	afx_msg void OnTest2();
	afx_msg void OnChangeEntry();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgPrefImpedance)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

#endif

#define CDLGPREFIMPEDANCE

