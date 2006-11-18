// dlgxfgrp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXfGrpDelay dialog

class CDlgXfGrpDelay : public CDialog
{
// Construction
public:
	CDlgXfGrpDelay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
// ------------------------------------
		float	m_fStart;
		float	m_fEnd;

		CzFormatGroup		m_cfEdits;
// ------------------------------------


	//{{AFX_DATA(CDlgXfGrpDelay)
	enum { IDD = IDD_GRPDELAY };
	//}}AFX_DATA

	int		m_nStyle;
	float	m_fStartMarker;
	float	m_fEndMarker;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXfGrpDelay)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXfGrpDelay)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEnd();
	afx_msg void OnChangeStart();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgXfGrpDelay)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};


// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------
class CXformCalcDelay : public CXtransform
{

	public:
		virtual	int		DoOperation( CNamed *cdDest);

		virtual UINT GetNameID()					{ return IDOP_GRPDELAY; }
		virtual UINT GetSuffix(void )				{ return IDSUF_GRPDELAY; }
		void	SetRange( int nStart, int nEnd) { m_nStart = nStart; m_nEnd = nEnd; }

	protected:
		int		m_nStart;		// starting index for the fft
		int		m_nEnd;			// ending index for the fft
	public:
		CXformCalcDelay( CObject *cTarget);		// must be named and in the tree
		~CXformCalcDelay();
};


