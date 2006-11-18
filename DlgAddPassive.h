// DlgAddPassive.h : header file
//

#ifndef DLGADDPASSIVE

/////////////////////////////////////////////////////////////////////////////
// CDlgAddPassive dialog

class CDlgAddPassive : public CDialog
{
// Construction
public:
	CDlgAddPassive(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAddPassive)
	enum { IDD = IDD_ADDPASSIVE };
	CString	m_csName;
	CString	m_csType;
	CString	m_csCompUnit;
	//}}AFX_DATA

	NAMETYPES		m_nType;		// the type used by the program

	float			GetValue( void);	// get the component value

// ------------------------------------
		float	m_fValue;		// the value of the object
		float	m_fResist;		// the internal resistance of the object

		CzFormatGroup		m_cfEdits;
// ------------------------------------


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAddPassive)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAddPassive)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgAddPassive)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


class CXtAddPassive : public CXunary
{
	public:
		NAMETYPES	m_nType;		
		float		m_fValue;
		float		m_fQ;
		CString		m_csName;

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		UINT GetNameID();

	private:

	public:					// include the type of object
		CXtAddPassive( CObject *cTarget, NAMETYPES ntObject);
		~CXtAddPassive();
};


#define DLGADDPASSIVE
#endif
