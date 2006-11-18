// DlgCalWizVol.h : header file
//

#ifndef CALWIZVOL

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizVolBegin dialog

class CDlgCalWizVolBegin : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCalWizVolBegin)

// Construction
public:
	CDlgCalWizVolBegin();
	~CDlgCalWizVolBegin();

// Dialog Data
	//{{AFX_DATA(CDlgCalWizVolBegin)
	enum { IDD = IDD_CAL_VOL_BEGIN };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizVolBegin)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgCalWizVolBegin)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizVolEnd dialog

class CDlgCalWizVolEnd : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCalWizVolEnd)
// Construction
public:
	CDlgCalWizVolEnd();   // standard constructor
	~CDlgCalWizVolEnd();

// Dialog Data
	//{{AFX_DATA(CDlgCalWizVolEnd)
	enum { IDD = IDD_CAL_VOL_END };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizVolEnd)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCalWizVolEnd)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizVol

class CDlgCalWizVol : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgCalWizVol)

// Construction
public:
	CDlgCalWizVol(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
	CView			*m_pView;	// the current view
	DWORD			m_dwReferID;		// the final reference ID
	CDlgCalWizVolBegin		m_dlgBegin;
	CDlgCalWizVolEnd		m_dlgEnd;


// Operations
public:
	void	SetView( CView *pNew)		{ m_pView = pNew; }
	CView	*GetView(void)				{ return m_pView; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalWizVol)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgCalWizVol();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgCalWizVol)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#define CALWIZVOL
#endif
