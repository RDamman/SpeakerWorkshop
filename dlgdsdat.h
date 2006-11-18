// dlgdsdat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDsDataset dialog

class CDlgDsDataset : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgDsDataset)

// Construction
public:
	CDlgDsDataset();
	~CDlgDsDataset();

	void PreDialog( CDataSet *pData);
	void PostDialog( CDataSet *pData);

	// dialog data via float stuff
// ------------------------------------
		float	m_fStart;
		float	m_fEnd;
		float	m_fPoints;

		CzFormatGroup		m_cfEdits;
// ------------------------------------
		BOOL	m_bUsePoints;	// radio status


// Dialog Data
	//{{AFX_DATA(CDlgDsDataset)
	enum { IDD = IDD_DSDATA };
	int		m_nUom;
	int		m_nDom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgDsDataset)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgDsDataset)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeStart();
	afx_msg void OnChangeNpoints();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgDsDataset)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
