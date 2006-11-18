// DlgZobel.h : header file
//

#ifndef DLGZOBEL

#include "zFormEdt.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgZobel dialog

class CDlgZobel : public CDialog
{
// Construction
public:
	CDlgZobel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgZobel)
	enum { IDD = IDD_COMPENSATION };
	int			m_nDriver;
	int			m_nType;
	//}}AFX_DATA

	// ------------------------ formatted edits
	float			m_fFreq;		// the frequency of interest
	CzFormatGroup	m_cfEdits;		// ""
	// ------------------------

	DWORD		 m_dwDriver;			// the driver id
	CNetwork	*m_pNetwork;		// the base network
	BOOL		 m_bUseDriver;		// use the driver as input???

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgZobel)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgZobel)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgZobel)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


class CXtZobel : public CXunary
{
	public:
		float	m_fFreq;			// the frequency of main interest
		int		m_nType;			// the type of compensation
		DWORD	m_dwDriver;			// the driver to compensate
		BOOL	m_bUseDriver;

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		UINT GetNameID()					{ return IDOP_ZOBEL; }

	private:

	public:
		CXtZobel( CObject *cTarget);		// must be named and in the tree
		~CXtZobel();
};



#define DLGZOBEL
#endif
