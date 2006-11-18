// DlgCalibrate.h : header file
//

#ifndef CDLGCALIB

/////////////////////////////////////////////////////////////////////////////
// CDlgCalibrate dialog

class CDlgCalibrate : public CDialog
{
// Construction
public:
	CDlgCalibrate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCalibrate)
	enum { IDD = IDD_CALIBRATE };
	CString	m_csChannelDiff;
	CString	m_csMicResponse;
	CString	m_csAmpResponse;
	//}}AFX_DATA

	DWORD	m_dwChannelDiff;		// the channel dif id
	DWORD	m_dwMicResponse;		// the mic response id
	DWORD	m_dwAmpResponse;		// the amplifier reference response for acoustic measurements
	CAudtestDoc *m_pDocument;		// the doc
	CAudtestView *m_pView;			// the parent view

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalibrate)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCalibrate)
	afx_msg void OnBrowseChan();
	afx_msg void OnBrowseMic();
	afx_msg void OnTestChan();
	afx_msg void OnTestMic();
	afx_msg void OnBrowseAmp();
	afx_msg void OnTestAmp();
	afx_msg void OnHitnoamp();
	afx_msg void OnHitnomic();
	afx_msg void OnHitnone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgCalibrate)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

#define CDLGCALIB
#endif
