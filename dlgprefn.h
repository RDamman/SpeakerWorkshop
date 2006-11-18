// dlgprefn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefNetwork dialog

class CDlgPrefNetwork : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgPrefNetwork)

// Construction
public:
	CDlgPrefNetwork();
	~CDlgPrefNetwork();

// Dialog Data
	//{{AFX_DATA(CDlgPrefNetwork)
	enum { IDD = IDD_PREFNETWORK };
	CString	m_csFontName;
	CString	m_csDataName;
	int		m_nPrecision;
	int		m_nResType;
	BOOL	m_bDrawEnds;
	//}}AFX_DATA

	CFxFont		m_LabelFont;
	CFxFont		m_DataFont;

public:

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgPrefNetwork)
	public:
	virtual void OnFinalRelease();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPrefNetwork)
	afx_msg void OnSellabel();
	afx_msg void OnSeldata();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDigits();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgPrefNetwork)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
