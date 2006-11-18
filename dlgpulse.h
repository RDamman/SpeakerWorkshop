// dlgpulse.h : header file
//

#ifndef DLGPULSE

/////////////////////////////////////////////////////////////////////////////
// CDlgPulse dialog

class CDlgPulse : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgPulse)

// Construction
public:
	CDlgPulse();
	~CDlgPulse();

// Dialog Data
// ------------------------------------
		float	m_fDuration;
		float	m_fFreq;

		CzFormatEdit	m_cDuration;
		CzFormatEdit	m_cFreq;
// ------------------------------------

	//{{AFX_DATA(CDlgPulse)
	enum { IDD = IDD_PULSE };
	BOOL	m_bNegative;
	BOOL	m_bRepeat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgPulse)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPulse)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposScrl2(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgPulse)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define DLGPULSE
#endif

