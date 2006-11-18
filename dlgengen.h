// dlgengen.h : header file
//

#ifndef DLGENGEN

/////////////////////////////////////////////////////////////////////////////
// CDlgEnGeneral dialog

class CDlgEnGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgEnGeneral)

// Construction
public:
	CDlgEnGeneral();
	~CDlgEnGeneral();

// Dialog Data

	float	m_fStart;
	float	m_fEnd;
	float	m_fDelta;

	CzFormatGroup		m_cfEdits;

	//{{AFX_DATA(CDlgEnGeneral)
	enum { IDD = IDD_ENCLGENERAL };
	CString	m_csDate;
	CString	m_csDescript;
	CString	m_csLastEdit;
	BOOL	m_bInherit;
	//}}AFX_DATA

	void		UseObject( CEnclosure *cWho);
	void		SetObject( CEnclosure *cWho);

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgEnGeneral)
	public:
	virtual void OnFinalRelease();
	virtual BOOL OnApply();
	virtual void OnCancel();
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgEnGeneral)
	afx_msg void OnChangeDescript();
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgEnGeneral)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define DLGENGEN
#endif

