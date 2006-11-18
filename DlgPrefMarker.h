// DlgPrefMarker.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefMarker dialog

class CDlgPrefMarker : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgPrefMarker)

// Construction
public:
	CDlgPrefMarker();
	~CDlgPrefMarker();

// ------------------------------------
	float			m_fFreq1;
	float			m_fFreq2;
	float			m_fOhms1;
	float			m_fOhms2;
	float			m_fTime1;
	float			m_fTime2;
	CzFormatEdit	m_cFreq1;
	CzFormatEdit	m_cFreq2;
	CzFormatEdit	m_cOhms1;
	CzFormatEdit	m_cOhms2;
	CzFormatEdit	m_cTime1;
	CzFormatEdit	m_cTime2;
// ------------------------------------

// Dialog Data
	//{{AFX_DATA(CDlgPrefMarker)
	enum { IDD = IDD_PREFMARKER };
	BOOL	m_bUseFreq;
	BOOL	m_bUseOhms;
	BOOL	m_bUseTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgPrefMarker)
	public:
	virtual void OnFinalRelease();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPrefMarker)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin6(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUseIt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgPrefMarker)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
