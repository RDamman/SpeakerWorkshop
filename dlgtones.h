// dlgtones.h : header file
//

#define NUMTONES 5

/////////////////////////////////////////////////////////////////////////////
// CDlgTones dialog

class CDlgTones : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgTones)

// Construction
public:
	CDlgTones();
	~CDlgTones();

// Dialog Data
// ------------------------------------
		float	m_fFreq[NUMTONES];
		float	m_fAmp[NUMTONES];

		CzFormatEdit	m_cFreq[NUMTONES];
		CzFormatEdit	m_cAmp[NUMTONES];
// ------------------------------------

	//{{AFX_DATA(CDlgTones)
	enum { IDD = IDD_TONES };
	BOOL	m_bTone1;
	BOOL	m_bTone2;
	BOOL	m_bTone3;
	BOOL	m_bTone4;
	BOOL	m_bTone5;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgTones)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgTones)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposGeneric(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposScrl(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgTones)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
