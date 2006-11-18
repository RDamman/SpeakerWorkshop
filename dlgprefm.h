// dlgprefm.h : header file
//

#include "zFormEdt.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefMeasure dialog

class CDlgPrefMeasure : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgPrefMeasure)

// Construction
public:
	void Apply( void);
	void Initial( void);
	CDlgPrefMeasure();
	~CDlgPrefMeasure();

// Dialog Data
	//{{AFX_DATA(CDlgPrefMeasure)
	enum { IDD = IDD_PREFMEASURE };
	CSpinButtonCtrl	m_cSpinCount;
	CSliderCtrl	m_clRate;
	CSliderCtrl	m_clSize;
	BOOL	m_bEmphasis;
	CString	m_csRate;
	CString	m_csSize;
	CString	m_csShowFreq;
	BOOL	m_bReverse;
	int		m_nRepCount;
	CString	m_csMaxRate;
	//}}AFX_DATA

	int				m_nRate;		// sampling rate
	int				m_nSize;
	float			m_fVolume;		// play volume
	CzFormatEdit	m_cVolume;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgPrefMeasure)
	public:
	virtual void OnFinalRelease();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPrefMeasure)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDeltaposSpinvolume(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeVolume();
	afx_msg void OnPreemphasis();
	afx_msg void OnReverse();
	afx_msg void OnChangeRepcount();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgPrefMeasure)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
