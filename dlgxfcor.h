// dlgxfcor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXfCorrelate dialog

class CDlgXfCorrelate : public CDialog
{
// Construction
public:
	CDlgXfCorrelate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgXfCorrelate)
	enum { IDD = IDD_XFCORRELATE };
	CSpinButtonCtrl	m_cSpinCount;
	int		m_nSize;
	int		m_nRepeatCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXfCorrelate)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXfCorrelate)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgXfCorrelate)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
