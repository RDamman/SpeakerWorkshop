// DlgMsrIn.h : header file
//

#ifndef DLGMSRINTERMOD

/////////////////////////////////////////////////////////////////////////////
// CDlgMsrIntermod dialog

class CDlgMsrIntermod : public CDialog
{
// Construction
public:
	CDlgMsrIntermod(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
// ------------------------------------
		float	m_fFreqStart;
		float	m_fFreqEnd;
		float	m_fPower;

		CzFormatGroup		m_cfEdits;
// ------------------------------------
	//{{AFX_DATA(CDlgMsrIntermod)
	enum { IDD = IDD_MSRINTERMOD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMsrIntermod)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMsrIntermod)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



#define DLGMSRINTERMOD
#endif
