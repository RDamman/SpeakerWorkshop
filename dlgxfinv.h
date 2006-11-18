// dlgxfinv.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXfInvert dialog

class CDlgXfInvert : public CDialog
{
// Construction
public:
	CDlgXfInvert(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgXfInvert)
	enum { IDD = IDD_XFINVERT };
	BOOL	m_bInvertData;
	BOOL	m_bInvertPhase;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXfInvert)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXfInvert)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgXfInvert)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
