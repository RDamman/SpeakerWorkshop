// dlgdsgen.h : header file
//

#ifndef DLGDSGEN

/////////////////////////////////////////////////////////////////////////////
// CDlgDsGeneral dialog

class CDlgDsGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgDsGeneral)

// Construction
public:
	CDlgDsGeneral();
	~CDlgDsGeneral();

	void PreDialog( CDataSet *pData);
	void PostDialog( CDataSet *pData);

// Dialog Data
	//{{AFX_DATA(CDlgDsGeneral)
	enum { IDD = IDD_DSGENERAL };
	CString	m_csDate;
	CString	m_csDescript;
	CString	m_csLastEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgDsGeneral)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgDsGeneral)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgDsGeneral)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define DLGDSGEN
#endif
