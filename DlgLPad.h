#if !defined(AFX_DLGLPAD_H__588B9966_40AA_489F_B1EF_81485873AF4B__INCLUDED_)
#define AFX_DLGLPAD_H__588B9966_40AA_489F_B1EF_81485873AF4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLPad.h : header file
//

enum	selLPad
{
	sllRe = 0,
	sllDriver = 1,
	sllData = 2
};


/////////////////////////////////////////////////////////////////////////////
// CDlgLPad dialog

class CDlgLPad : public CDialog
{
// Construction
public:
	CDlgLPad(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
		DWORD		 m_dwDataset;			// the potential dataset
		DWORD		 m_dwDriver;				// the potential driver
		selLPad		 m_isUseWhich;		// do we want to use a driver?
		CNetwork	*m_pNetwork;		// the network we are using

// ------------------------------------
		float	m_fStartFreq;
		float	m_fEndFreq;
		float	m_fLevel;
		float	m_fRe;

		CzFormatGroup		m_cfEdits;
// ------------------------------------
	//{{AFX_DATA(CDlgLPad)
	enum { IDD = IDD_LPAD };
	int		m_iDriver;
	CString	m_csDataset;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLPad)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
		void setup_DriverList( void);
		void copy_String( int nWhich);
		void setup_Radios( selLPad slUse);	// set the radios up
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLPad)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBrowse();
	afx_msg void OnSelchangeDriver();
	afx_msg void OnChangeRe();
	afx_msg void OnSelData();
	afx_msg void OnSelDriver();
	afx_msg void OnSelResist();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CXtLPad : public CXunary
{
	public:
		selLPad	m_isUseWhich;
		DWORD	m_dwDriver;
		DWORD	m_dwDataset;
		float	m_fLevel;
		float	m_fFStart;
		float	m_fFEnd;
		float	m_fRe;

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		UINT GetNameID()					{ return IDOP_LPAD; }

	private:

	public:
		CXtLPad( CObject *cTarget);		// must be named and in the tree
		~CXtLPad();
};




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLPAD_H__588B9966_40AA_489F_B1EF_81485873AF4B__INCLUDED_)
