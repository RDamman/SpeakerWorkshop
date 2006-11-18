// DlgMsrDistort.h : header file
//

#ifndef DLGMSRDISTORT

/////////////////////////////////////////////////////////////////////////////
// CDlgMsrDistort dialog

class CDlgMsrDistort : public CDialog
{
// Construction
public:
	CDlgMsrDistort(CWnd* pParent = NULL);   // standard constructor

	int m_nStyle;		// which style

// Dialog Data
// ------------------------------------
		float	m_fPower;
		float	m_fPowerStart;
		float	m_fPowerEnd;
		float	m_fFreq;
		float	m_fFreqStart;
		float	m_fFreqEnd;
		float	m_fEquate;

		CzFormatGroup		m_cfEdits;
// ------------------------------------
	//{{AFX_DATA(CDlgMsrDistort)
	enum { IDD = IDD_MSRDISTORT };
	BOOL	m_bLogRange;
	int		m_nPoints;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMsrDistort)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMsrDistort)
	afx_msg void OnSpectrum();
	afx_msg void OnFreq();
	afx_msg void OnPower();
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgMsrDistort)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


#define DLGMSRDISTORT
#endif
