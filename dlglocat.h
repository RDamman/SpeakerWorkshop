// dlglocat.h : header file
//

#ifndef DLGLOCAT

#define WM_LOCATION_GONE  WM_USER+10

/////////////////////////////////////////////////////////////////////////////
// CDlgLocations dialog

class CDlgLocations : public CDialog
{
// Construction
public:
	CDlgLocations(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLocations)
	enum { IDD = IDD_LOCATIONS };
	CListBox	m_clListDelta2;
	CListBox	m_clListFirst;
	CListBox	m_clListDelta;
	CListBox	m_clListLast;
	CListBox	m_clList;
	CString	m_csFreqFirst;
	//}}AFX_DATA

				// the data storage
	CFloatArray	m_cfList;
	CFloatArray	m_cfLast;
	CFloatArray m_cfDelta;
	CFloatArray m_cfDelta2;
				// the names
	CStringArray m_cszNames;

private:
	int m_nLastSize;
	CObject		*m_cwOwner;				// the subchart who owns us

public:

	CObject		*GetLocator(void)					{ return m_cwOwner; }
	void		SetLocator( CObject *cNew)			{ m_cwOwner = cNew; }
	void		UpdateLocator( CObject *cChart, CPoint& cPt);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLocations)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLocations)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgLocations)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define DLGLOCAT
#endif
