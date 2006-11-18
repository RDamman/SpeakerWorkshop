#if !defined(AFX_DLGDRVEQUIV_H__3B630C81_5B08_11D4_BBF9_00A0C9923AAC__INCLUDED_)
#define AFX_DLGDRVEQUIV_H__3B630C81_5B08_11D4_BBF9_00A0C9923AAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDrvEquiv.h : header file
//

class CXformCalcEquiv : public CXunary	// calc parameters class
{

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		virtual UINT GetNameID()					{ return IDOP_CALCEQUIV; }

	public:
		DRIVEEQUIV	m_DQ;					// the driver equivalent


	public:
		CXformCalcEquiv( CObject *cTarget);		// must be named and in the tree
		~CXformCalcEquiv();
};


/////////////////////////////////////////////////////////////////////////////
// CDlgDrvEquiv dialog

class CDlgDrvEquiv : public CDialog
{
// Construction

public:
	CDlgDrvEquiv(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDrvEquiv)
	enum { IDD = IDD_DRVEQUIV };
	float	m_fFs;
	float	m_fQes;
	float	m_fQms;
	float	m_fQts;
	//}}AFX_DATA

// Dialog Data
// ------------------------------------
		float		m_fL1a;
		float		m_fL1b;
		float		m_fL2;
		float		m_fC2;
		float		m_fRe;
		float		m_fR1;
		float		m_fR2;
		CzFormatGroup		m_cfEdits;
// ------------------------------------

		CDriver		*m_Driver;
		DRIVEEQUIV	m_DQ;
		DRIVEPARM	m_DP;
		DRIVEEQUIV	m_LastDQ;
		DRIVEPARM	m_LastDP;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDrvEquiv)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateDQ( void);
	void UpdateDP( void);

	// Generated message map functions
	//{{AFX_MSG(CDlgDrvEquiv)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeVar();
	afx_msg void OnChart();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ResetParms( void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDRVEQUIV_H__3B630C81_5B08_11D4_BBF9_00A0C9923AAC__INCLUDED_)
