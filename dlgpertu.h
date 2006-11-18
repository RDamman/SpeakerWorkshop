// dlgpertu.h : header file
//

#ifndef DLGPERTUR

/////////////////////////////////////////////////////////////////////////////
// CDlgPerturb dialog

class CDlgPerturb : public CDialog
{
// Construction
public:
	CDlgPerturb(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
// ------------------------------------
		float	m_fStart;
		float	m_fEnd;

		CzFormatGroup		m_cfEdits;
// ------------------------------------


	//{{AFX_DATA(CDlgPerturb)
	enum { IDD = IDD_PERTURB };
	CComboBox	m_cComponent;
	int		m_nPoints;
	CString	m_csObjName;
	BOOL	m_bLog;
	//}}AFX_DATA

	CNetwork	*m_pNet;		// the network we're working with


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPerturb)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

				// local
private:
	void fill_Combo( CComboBox& pList);

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPerturb)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgPerturb)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define DLGPERTUR
#endif
