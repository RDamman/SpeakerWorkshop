// DlgAddDriver.h : header file
//

#ifndef DLGADDDRIVER

/////////////////////////////////////////////////////////////////////////////
// CDlgAddDriver dialog

class CDlgAddDriver : public CDialog
{
// Construction
public:
	CDlgAddDriver(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAddDriver)
	enum { IDD = IDD_ADDDRIVER };
	CzFormatStatic	m_czStatOffset;
	BOOL	m_bIndieResponse;
	BOOL	m_bFlipPolarity;
	CString	m_csDriver;
	CString	m_strName;
	//}}AFX_DATA

		CFolder *m_pRoot;			// the root object (used for selection)

		DWORD	m_dwDriverID;		// the driver id

// ------------------------------------
		float	m_fOffset;		// the value of the object

		CzFormatGroup		m_cfEdits;
// ------------------------------------


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAddDriver)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAddDriver)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBrowse();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgAddDriver)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


class CXtAddDriver : public CXunary
{
	public:
		float	m_fOffset;			// the driver offset
		DWORD	m_dwDriverID;		// the driver id
		BOOL	m_bFlipPolarity;	// flip polarity
		BOOL	m_bIndieResponse;	// generate individual response
		CString	m_strName;			// name in the dialog

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		UINT GetNameID();

	private:

	public:					// include the type of object
		CXtAddDriver( CObject *cTarget);
		~CXtAddDriver();
};


#define DLGADDDRIVER
#endif
