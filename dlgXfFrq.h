// dlgxfgrp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXfCalcFrequency dialog

class CDlgXfCalcFrequency : public CDialog
{
// Construction
public:
	CDlgXfCalcFrequency(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
// ------------------------------------
		float	m_fStart;
		float	m_fEnd;

		CzFormatGroup		m_cfEdits;
// ------------------------------------

	//{{AFX_DATA(CDlgXfCalcFrequency)
	enum { IDD = IDD_XFCALCFREQ };
	int		m_nCalibType;
	int		m_nWindow;
	BOOL	m_bUseReference;
	//}}AFX_DATA

	int		m_nStyle;
	float	m_fStartMarker;
	float	m_fEndMarker;
	DWORD	m_dwReference;		// the reference id

protected:
	CFolder *m_pRoot;			// the root object for dword lookup

public:
	void	SetRoot( CFolder *pRoot)	{ m_pRoot = pRoot; }


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXfCalcFrequency)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXfCalcFrequency)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEnd();
	afx_msg void OnChangeStart();
	afx_msg void OnSelrefer();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgXfCalcFrequency)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};


// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------
class CXformCalcFrequency : public CXtransform
{

	public:
		virtual	int		DoOperation( CNamed *cdDest);

		virtual UINT GetNameID()					{ return IDOP_CALCFREQ; }
		virtual UINT GetSuffix(void )				{ return IDSUF_CALCFREQ; }
		void	SetRange( int nStart, int nEnd) { m_nStart = nStart; m_nEnd = nEnd; }
		void	SetCalib( int nType)		{ m_nCalibType = nType; }
		void	SetWindow( int nWindow)		{ m_nWindow = nWindow; }
		void	SetReference( BOOL bNew, DWORD dwNew)	{ m_bUseReference = bNew; m_dwReference = dwNew; }

	protected:
		int		m_nStart;		// starting index for the fft
		int		m_nEnd;			// ending index for the fft

		BOOL	m_bUseReference;	// do we use a reference???
		DWORD	m_dwReference;		// what is the dword ??
		int		m_nCalibType;		// do we use a calib? 0=no,1=l/r,2=microphone
		int		m_nWindow;			// windowing used

	public:
		CXformCalcFrequency( CObject *cTarget);		// must be named and in the tree
		~CXformCalcFrequency();
};


