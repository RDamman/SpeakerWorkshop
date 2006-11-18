// dlggenge.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGenGeneral dialog

class CDlgGenGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgGenGeneral)

// Construction
public:
	CDlgGenGeneral();
	~CDlgGenGeneral();

// Dialog Data
	//{{AFX_DATA(CDlgGenGeneral)
	enum { IDD = IDD_GENGENERAL };
	CComboBox	m_cDataRates;
	CString	m_csDescript;
	CString	m_csDate;
	int		m_nType;
	int		m_nRate;
	CString	m_csLastDate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgGenGeneral)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgGenGeneral)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgGenGeneral)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
