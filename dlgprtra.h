// dlgprtra.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefTransform dialog

class CDlgPrefTransform : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgPrefTransform)

// Construction
public:
	CDlgPrefTransform();
	~CDlgPrefTransform();

// Dialog Data
	//{{AFX_DATA(CDlgPrefTransform)
	enum { IDD = IDD_PREFTRANSFORM };
	BOOL	m_bAutoIncrement;
	BOOL	m_bBinAutoIncrement;
	BOOL	m_bExeInPlace;
	BOOL	m_bBinExeInPlace;
	int		m_nFftWindow;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgPrefTransform)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPrefTransform)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgPrefTransform)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
