#if !defined(AFX_DLGROOT_H__D3A6DB81_51F9_11D2_AAC6_00A0C9923AAC__INCLUDED_)
#define AFX_DLGROOT_H__D3A6DB81_51F9_11D2_AAC6_00A0C9923AAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRoot.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRootView dialog

class CDlgRootView : public CDialog
{
// Construction
public:
	CDlgRootView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRootView)
	enum { IDD = IDD_ROOTVIEW };
	CString	m_csComments;
	CString	m_csDrivers;
	CString	m_csEnclosures;
	CString	m_csFileDate;
	CString	m_csLastEdit;
	CString	m_csFileName;
	CString	m_csFileSize;
	CString	m_csNetworks;
	CString	m_csFolderName;
	CString	m_csFolderSize;
	CString	m_csFolderDate;
	CString	m_csFolderLast;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRootView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRootView)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGROOT_H__D3A6DB81_51F9_11D2_AAC6_00A0C9923AAC__INCLUDED_)
