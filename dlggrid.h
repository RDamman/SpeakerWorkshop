// dlggrid.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGrid dialog

#ifndef CDLGGRID

class CDlgGrid : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgGrid)

// Construction
public:
	CDlgGrid(int nIdCaption);
	~CDlgGrid();
protected:
	CDlgGrid(void );
protected:

	CGrid *m_pcGrid;

// Dialog Data
	//{{AFX_DATA(CDlgGrid)
	enum { IDD = IDD_CHGRID };
	BOOL	m_bAutoScale;
	BOOL	m_bAutoTic;
	BOOL	m_bIsLog;
	BOOL	m_bShowGrid;
	BOOL	m_bShowTic;
	BOOL	m_bDrawMajor;
	BOOL	m_bDrawMinor;
	int		m_nColor;
	int		m_nColor2;
	int		m_nLineStyle;
	int		m_nLineStyle2;
	int		m_nLineWeight;
	int		m_nLineWeight2;
	CString	m_szGridTitle;
	BOOL	m_bShowGTitle;
	//}}AFX_DATA

	float			m_fMajor;
	float			m_fMax;
	float			m_fMin;
	float			m_fMinor;

	CzFormatGroup	m_cfEdits;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgGrid)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
   	void UseGrid( CGrid *pcGrid);
	void SetGrid( CGrid *pcGrid);

				// ---------------------------
	CObjColor m_cMajor;
	CObjColor m_cMinor;

	CColorBox m_cclrMajor;
	CColorBox m_cclrMinor;
	CLineStyleBox m_clsMajor;
	CLineStyleBox m_clsMinor;
	CLineWidthBox m_clwMajor;
	CLineWidthBox m_clwMinor;
	

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgGrid)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelfont();
	afx_msg void OnSeltitlefont();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeMaxGrid();
	afx_msg void OnChangeMinGrid();
	afx_msg void OnChangeScale();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgGrid)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};


class CDlgGridX : public CDlgGrid
{
	DECLARE_DYNCREATE(CDlgGridX)

public:
	CDlgGridX();

};

class CDlgGridY : public CDlgGrid
{
	DECLARE_DYNCREATE(CDlgGridY)

public:
	CDlgGridY();

};

class CDlgGridY2 : public CDlgGrid
{
	DECLARE_DYNCREATE(CDlgGridY2)

public:
	CDlgGridY2();

};




#define CDLGGRID
#endif
