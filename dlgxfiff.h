// dlgxfiff.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXfIfft dialog

class CDlgXfIfft : public CDialog
{
// Construction
public:
	CDlgXfIfft(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
// ------------------------------------
		float	m_fStart;
		float	m_fEnd;

		CzFormatGroup		m_cfEdits;
// ------------------------------------

	//{{AFX_DATA(CDlgXfIfft)
	enum { IDD = IDD_XFIFFT };
	CString	m_csSampleRate;
	//}}AFX_DATA

	int		m_nStyle;
	int		m_nSampleRate;
	int		m_nSampleStyle;		// 0 == use data, 1 == use nSampleRate
	int		m_nDefaultRate;		// default sample rate
	float	m_fStartMarker;
	float	m_fEndMarker;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXfIfft)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXfIfft)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEnd();
	afx_msg void OnChangeStart();
	afx_msg void OnEditchangeSamplerate();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgXfIfft)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
