// DlgCalcPassive.h : header file
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcPassive dialog

class CDlgCalcPassive : public CDialog
{
// Construction
public:
	CDlgCalcPassive(CWnd* pParent = NULL);   // standard constructor
	static	bool	IsShowing( void)	{ return m_bIsShowing; }

// Dialog Data
	// -----------------------------------------------
	float	m_fValue;
	float	m_fFreq;

	CzFormatGroup		m_cfEdits;
	// -----------------------------------------------

	//{{AFX_DATA(CDlgCalcPassive)
	enum { IDD = IDD_CALCPASSIVE };
	CString	m_csAmp;
	CString	m_csPhase;
	CString	m_csReal;
	CString	m_csImaginary;
	//}}AFX_DATA

	int		m_nType;		// radio button control


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalcPassive)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
private:
	void recalc_Values( void);
	static bool m_bIsShowing;

protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCalcPassive)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeFreq();
	afx_msg void OnChangeValue();
	afx_msg void OnRadio();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgCalcPassive)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
