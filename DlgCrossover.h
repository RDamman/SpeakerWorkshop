// DlgCrossover.h : header file
//

#ifndef DLGCROSSOVER

#include "zFormEdt.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgCrossover dialog


enum	selType
{
	selRe = 0,
	selDriver = 1,
	selData = 2
};



class CDlgCrossover : public CDialog
{
// Construction
public:
	CDlgCrossover(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCrossover)
	enum { IDD = IDD_CROSSOVER };
	int		m_nHighLow;
	int		m_nOrder;
	int		m_nType;
	int		m_iDriver;
	CString	m_csDataset;
	//}}AFX_DATA

	float			m_fFS;
	float			m_fRe;
	CzFormatEdit	m_cRe;
	CzFormatEdit	m_cFS;

	selType		 m_isUseWhich;		// do we want to use a driver?
	DWORD		 m_dwDriver;		// the driver to use
	DWORD		 m_dwDataset;
	CNetwork	*m_pNetwork;		// the network we are using

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCrossover)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
		void setup_List(void );
		void setup_DriverList( void);
		void copy_String( int nWhich);
		void setup_Radios( selType slUse);	// set the radios up
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCrossover)
	afx_msg void OnSelchangeOrder();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnSeldriver();
	afx_msg void OnSelresist();
	afx_msg void OnSelchangeDriver();
	afx_msg void OnChangeRe();
	afx_msg void OnBrowse();
	afx_msg void OnSeldata();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgCrossover)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};




class CXtCrossover : public CXunary
{
	public:
		selType	m_isUseWhich;
		int		m_nHighLow;
		int		m_nOrder;
		int		m_nType;
		DWORD	m_dwDriver;
		DWORD	m_dwDataset;
		float	m_fFS;
		float	m_fRe;

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		UINT GetNameID()					{ return IDOP_CROSSOVER; }

	private:

	public:
		CXtCrossover( CObject *cTarget);		// must be named and in the tree
		~CXtCrossover();
};


#define DLGCROSSOVER
#endif

