// DlgCalWizAmp.h : header file
//

#ifndef CALWIZAMP

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizAmpBegin dialog

class CDlgCalWizAmpBegin : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCalWizAmpBegin)

// Construction
public:
	CDlgCalWizAmpBegin();
	~CDlgCalWizAmpBegin();

// Dialog Data
	//{{AFX_DATA(CDlgCalWizAmpBegin)
	enum { IDD = IDD_CAL_AMP_BEGIN };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizAmpBegin)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgCalWizAmpBegin)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizAmpEnd dialog

class CDlgCalWizAmpEnd : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCalWizAmpEnd)
// Construction
public:
	CDlgCalWizAmpEnd();   // standard constructor
	~CDlgCalWizAmpEnd();

// Dialog Data
	//{{AFX_DATA(CDlgCalWizAmpEnd)
	enum { IDD = IDD_CAL_AMP_END };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizAmpEnd)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCalWizAmpEnd)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizAmp

class CDlgCalWizAmp : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgCalWizAmp)

// Construction
public:
	CDlgCalWizAmp(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
	CView			*m_pView;	// the current view
	DWORD			m_dwReferID;		// the final reference ID
	CDlgCalWizAmpBegin		m_dlgBegin;
	CDlgCalWizAmpEnd		m_dlgEnd;


// Operations
public:
	void	SetView( CView *pNew)		{ m_pView = pNew; }
	CView	*GetView(void)				{ return m_pView; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizAmp)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgCalWizAmp();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgCalWizAmp)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#define CALWIZAMP
#endif
