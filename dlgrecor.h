// dlgrecor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecord dialog

class CDlgRecord : public CDialog
{
// Construction
public:
	CDlgRecord(CWnd* pParent = NULL);   // standard constructor

	void	SetDocument( CAudtestDoc *pDoc);
	void	UseDocument( CAudtestDoc *pDoc);

// Dialog Data
	//{{AFX_DATA(CDlgRecord)
	enum { IDD = IDD_RECORD };
	int		m_nCalib;
	int		m_nData;
	float	m_fVolumeAmt;
	BOOL	m_bNoOutput;
	float	m_fPlayTime;
	float	m_fRecordTime;
	int		m_nOutput;
	//}}AFX_DATA

				// non-afx data
	int		m_nType;				// type of data.. from radio buttons


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecord)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRecord)
	afx_msg void OnDeltaposGeneric2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposGeneric3(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgRecord)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
