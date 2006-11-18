// dlgcbox.h : header file
//

#ifndef CDLGCALCBASE

class CDlgCalcBase : public CDialog
{
// Construction
public:
	CFolder *m_cRoot;
	CObject *m_cDest;
	CObject *m_cOriginal;				// the first argument passed to us

	CzFormatGroup	m_cfEdits;			// place to put the edit fields

public:
	CDlgCalcBase(UINT uID, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgCalcBase();


// Dialog Data
	//{{AFX_DATA(CDlgCalcBase)
	enum { IDD = IDD_CALCSEALED };
	//}}AFX_DATA


	void UseObject( CFolder *cRoot, CObject *cDest);
	void SetObject( CFolder *cRoot, CObject *cDest);
	
	virtual void InitDlg(void );
	virtual void OkDlg( void);
	virtual void CalculateVariables( void);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalcBase)
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFolder *GetRoot(void )							{ return m_cRoot;	 }
	CObject *GetDest( void)							{ return m_cDest; 	 }

	// Generated message map functions
	//{{AFX_MSG(CDlgCalcBase)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgCalcBase)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcSealed dialog

class CDlgCalcSealed : public CDlgCalcBase
{
// Construction
public:
	CDlgCalcSealed(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	// -------------------------------------------
	float	m_fQts;
	float	m_fSeriesRes;
	float	m_fVb;
	float	m_fFs;
	float	m_fF3;
	// -------------------------------------------

	//{{AFX_DATA(CDlgCalcSealed)
	enum { IDD = IDD_CALCSEALED };
	CzFormatStatic	m_czVolUnit;
	int		m_nAlignment;
	UINT	m_uDriver;
	int		m_iSeries;
	//}}AFX_DATA

public:
	virtual void InitDlg(void );
	virtual void OkDlg( void);
	virtual void CalculateVariables( void);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalcSealed)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	void set_Enclosure( CEnclosure *pDest);

protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCalcSealed)
	afx_msg void OnSelchangeAlignment();
	afx_msg void OnChangeQts();
	afx_msg void OnChangeSeriesres();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCompare();
	afx_msg void OnChangeNumdriver();
	afx_msg void OnSelchangeSeries();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgCalcSealed)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CDlgCalcBandAir dialog

class CDlgCalcBandAir : public CDlgCalcBase
{
// Construction
public:
	CDlgCalcBandAir(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCalcBandAir)
	enum { IDD = IDD_CALCBANDAIR };
	int		m_nAlignment;
	CString	m_csF3;
	CString	m_csFs;
	CString	m_csPlength;
	CString	m_csPlength2;
	CString	m_csPortUnit;
	CString	m_csPortUnit2;
	CString	m_csVb;
	CString	m_csVb2;
	CString	m_csVolUnit2;
	CString	m_csVolUnit;
	//}}AFX_DATA


public:
	virtual void InitDlg(void );
	virtual void OkDlg( void);
	virtual void CalculateVariables( void);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalcBandAir)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCalcBandAir)
	afx_msg void OnProperties();
	afx_msg void OnSelchangeAlignment();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgCalcBandAir)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CDlgCalcBandChamber dialog

class CDlgCalcBandChamber : public CDlgCalcBase
{
// Construction
public:
	CDlgCalcBandChamber(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCalcBandChamber)
	enum { IDD = IDD_CALCBANDCHAMBER };
	int		m_nALignment;
	CString	m_csF3;
	CString	m_csFs;
	CString	m_csPlength;
	CString	m_csPlength2;
	CString	m_csPortUnit;
	CString	m_csPortUnit2;
	CString	m_csVb;
	CString	m_csVb2;
	CString	m_csVolUnit;
	CString	m_csVolUnit2;
	//}}AFX_DATA


public:
	virtual void InitDlg(void );
	virtual void OkDlg( void);
	virtual void CalculateVariables( void);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalcBandChamber)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCalcBandChamber)
	afx_msg void OnProperties();
	afx_msg void OnSelchangeAlignment();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgCalcBandChamber)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CDlgCalcVented dialog

class CDlgCalcVented : public CDlgCalcBase
{
// Construction
public:
	CDlgCalcVented(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	// -------------------------------------------
	float	m_fVb;
	float	m_fPlength;
	float	m_fSeriesRes;
	float	m_fPDiam;
	float	m_fFb;
	// -------------------------------------------


	float	m_fAlpha;
	float	m_fH;					// speaker tuning parameters

	//{{AFX_DATA(CDlgCalcVented)
	enum { IDD = IDD_CALCVENTED };
	CzFormatStatic	m_czVolUnit;
	CzFormatStatic	m_czPortUnit2;
	CzFormatStatic	m_czPortUnit;
	int		m_nAlignment;
	int		m_iSeriesPar;
	UINT	m_uDriver;
	UINT	m_uPort;
	//}}AFX_DATA


public:
	virtual void InitDlg(void );
	virtual void OkDlg( void);
	virtual void CalculateVariables( );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalcVented)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	void set_Enclosure( CEnclosure *pDest);
	void change_Item( UINT uItem, float fOld);
	void Recalc( UINT uItem, float fOld);
	float CalcPlength( void);

protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCalcVented)
	afx_msg void OnSelchangeAlignment();
	afx_msg void OnChangePlength();
	afx_msg void OnChangeVb();
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangePdiam();
	afx_msg void OnCompare();
	afx_msg void OnChangeSeriesres();
	afx_msg void OnChangeTuning();
	afx_msg void OnChangeNumdriver();
	afx_msg void OnChangeNumport();
	afx_msg void OnSelchangeSeriespar();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgCalcVented)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define CDLGCALCBASE
#endif


