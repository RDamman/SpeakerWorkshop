// dlgplays.h : header file
//


#ifndef DLGPLAYS

/////////////////////////////////////////////////////////////////////////////
// CDlgPlaySound dialog

class CDlgPlaySound : public CDialog
{
// Construction
public:
	CDlgPlaySound(CWnd* pParent = NULL);   // standard constructor

	void	SetDocument( CAudtestDoc *pDoc);
	void	UseDocument( CAudtestDoc *pDoc);

// Dialog Data
	//{{AFX_DATA(CDlgPlaySound)
	enum { IDD = IDD_PLAYSOUND };
	float	m_fPlayTime;
	float	m_fVolumeAmt;
	int		m_nOutput;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPlaySound)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPlaySound)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposGeneric2(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgPlaySound)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define DLGPLAYS
#endif
