// DlgDvEst.h : header file
//

class CXformCalcDriver : public CXunary	// calc parameters class
{

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		virtual UINT GetNameID()					{ return IDOP_CALCDRIVER; }

	public:
		float	m_fStart;
		float	m_fEnd;						// start and end frequencies
		BOOL	m_bUseFreq;					// use entire range???
		bool	m_bRecalcFree;				// recalculate Free Air stuff?

	public:
		CXformCalcDriver( CObject *cTarget);		// must be named and in the tree
		~CXformCalcDriver();
};

/////////////////////////////////////////////////////////////////////////////
// CDlgDriverEstimate dialog

class CDlgDriverEstimate : public CDialog
{
// Construction
public:
	CDlgDriverEstimate(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
// ------------------------------------
		float	m_fStart;
		float	m_fEnd;

		CzFormatGroup		m_cfEdits;
// ------------------------------------


	//{{AFX_DATA(CDlgDriverEstimate)
	enum { IDD = IDD_DRVRESTIMATE };
	BOOL	m_bNoRecalc;
	//}}AFX_DATA


	float	m_fStartMarker;
	float	m_fEndMarker;
	int		m_nStyle;		//  0 == entire, 1 == markers 2 == custom,as per dbox

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDriverEstimate)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDriverEstimate)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChangeEnd();
	afx_msg void OnChangeStart();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgDriverEstimate)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
