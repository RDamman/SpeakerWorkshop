// dlgxffft.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXfFft dialog

class CDlgXfFft : public CDialog
{
// Construction
public:
	CDlgXfFft(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
		CDataSet *m_pData;				// the dataset in question
// ------------------------------------
		float	m_fStart;
		float	m_fEnd;

		CzFormatGroup		m_cfEdits;
// ------------------------------------

	//{{AFX_DATA(CDlgXfFft)
	enum { IDD = IDD_XFFFT };
	int		m_nWindow;
	//}}AFX_DATA

	int		m_nStyle;				// std style 0=entire,1=marker,2=custom
	float	m_fStartMarker;
	float	m_fEndMarker;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXfFft)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	DrawPointsInfo();
	// Generated message map functions
	//{{AFX_MSG(CDlgXfFft)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEnd();
	afx_msg void OnChangeStart();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUsecustom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgXfFft)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
