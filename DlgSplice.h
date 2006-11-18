// DlgSplice.h : header file

#ifndef DLGSPLICE

//

/////////////////////////////////////////////////////////////////////////////
// CDlgXfSplice dialog

class CDlgXfSplice : public CDialog
{
// Construction
public:
	CDlgXfSplice(CWnd* pParent = NULL);   // standard constructor

// ------------------------------------
		float	m_fStart;

		CzFormatEdit	m_cStart;
// ------------------------------------

// Dialog Data
	//{{AFX_DATA(CDlgXfSplice)
	enum { IDD = IDD_XFSPLICE };
	BOOL	m_bUseBHigh;
	BOOL	m_bUseBRes;
	//}}AFX_DATA

public:
	CFolder *m_pRoot;		// the root object to use with the dwords
	int		m_nStyle;		// which style are we using
	float	m_fStartMarker;
	float	m_fEndMarker;	// the markers of interest
	DWORD	m_dwPicked;		// the B dataset
	DWORD	m_dwSource;		// the A dataset


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXfSplice)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXfSplice)
	afx_msg void OnBrowse();
	afx_msg void OnChangeStart();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgXfSplice)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


class CXformSplice : public CXtBinary
{

	public:
		virtual int  DoOperation( CNamed *pcDest);		// do it
		virtual UINT GetNameID()					{ return IDOP_SPLICE; }
		virtual UINT GetSuffix(void )	 			{ return IDSUF_SPLICE; }

	private:
		float	m_fFreq;				// splice frequency
		BOOL	m_bUseBHigh;			// use B for the high frequency stuff
		BOOL	m_bUseBRes;				// use B for the resolution stuff

	public:
		void	SetFrequency( float fFreq)			{ m_fFreq = fFreq; }
		void	SetUseBHigh( BOOL bNew)				{ m_bUseBHigh = bNew; }
		void	SetUseBRes( BOOL bNew)				{ m_bUseBRes = bNew; }


	public:
		CXformSplice( CObject *cTarget, CObject *cOther);		// must be named and in the tree
		~CXformSplice();

};

#define DLGSPLICE
#endif
