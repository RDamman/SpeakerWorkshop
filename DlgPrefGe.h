// DlgPrefGe.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefGeneral dialog

class CDlgPrefGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgPrefGeneral)

// Construction
public:
	CDlgPrefGeneral();
	~CDlgPrefGeneral();

// Dialog Data
	//{{AFX_DATA(CDlgPrefGeneral)
	enum { IDD = IDD_PREFGENERAL };
	int		m_nUnits;
	BOOL	m_bSingleClick;
	BOOL	m_bUseLast;
	BOOL	m_bLongStatus;
	CString	m_csSummaryName;
	BOOL	m_bEnable48K;
	int		m_iTrails;
	int		m_iAllowedLocale;
	BOOL	m_bAutoSave;
	int		m_iSaveTime;
	BOOL	m_bEnable96K;
	//}}AFX_DATA

// Dialog Data
// ------------------------------------
		float	m_fRightShift;
		CzFormatGroup		m_cfEdits;
// ------------------------------------
	CFxFont		m_SummaryFont;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgPrefGeneral)
	public:
	virtual void OnFinalRelease();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPrefGeneral)
	virtual BOOL OnInitDialog();
	afx_msg void OnUselast();
	afx_msg void OnSingleclick();
	afx_msg void OnSelchangeUnits();
	afx_msg void OnLongstatus();
	afx_msg void OnPickfnt();
	afx_msg void OnChangeTrails();
	afx_msg void OnChangeAllowedlocale();
	afx_msg void OnAutosave();
	afx_msg void OnChangeSavetime();
	afx_msg void OnDeltaposSpin4(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void EnableSave( void);		// enable/disable the autosave timer

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgPrefGeneral)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
