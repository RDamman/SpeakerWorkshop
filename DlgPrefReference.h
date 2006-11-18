// DlgPrefReference.h : header file
//

#ifndef DLGPREFREFER

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefReference dialog

class CDlgPrefReference : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgPrefReference)
// attributes
public:
	DWORD	m_dwLeftResponse;
	DWORD	m_dwRightResponse;
	DWORD	m_dwMicResponse;		// the id's
	CFolder *m_cRoot;

// Construction
public:
	CDlgPrefReference();
	~CDlgPrefReference();

// Dialog Data
	//{{AFX_DATA(CDlgPrefReference)
	enum { IDD = IDD_PREFREFERENCE };
	CString	m_csLeftResponse;
	CString	m_csRightResponse;
	CString	m_csMicResponse;
	float	m_fMicSensitivity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgPrefReference)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPrefReference)
	afx_msg void OnLeftbrowse();
	afx_msg void OnRightbrowse();
	afx_msg void OnMicbrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgPrefReference)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


#define DLGPREFREFER
#endif
