// DlgCalcTuned.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcTuned dialog

class CDlgCalcTuned : public CDialog
{
// Construction
public:
	CDlgCalcTuned(CWnd* pParent = NULL);   // standard constructor
	static	bool	IsShowing( void)	{ return m_bIsShowing; }

// Dialog Data
	// -----------------------------------------------
	float	m_fCValue;
	float	m_fLValue;
	float	m_fRValue;

	CzFormatGroup		m_cfEdits;
	// -----------------------------------------------
	//{{AFX_DATA(CDlgCalcTuned)
	enum { IDD = IDD_CALCTUNED };
	CString	m_csFreq;
	CString	m_csQ;
	//}}AFX_DATA

	int		m_nType;			// type of circuit


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalcTuned)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
private:
	void	CalculateVariables( void);
	static bool m_bIsShowing;

protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCalcTuned)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeLvalue();
	afx_msg void OnChangeRvalue();
	afx_msg void OnChangeCvalue();
	afx_msg void OnRadio();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgCalcTuned)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
