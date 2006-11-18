#if !defined(AFX_DLGDISABLE48K_H__C138679E_52BF_4918_B892_5E671B6E02CF__INCLUDED_)
#define AFX_DLGDISABLE48K_H__C138679E_52BF_4918_B892_5E671B6E02CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDisable48K.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDisable48K dialog

class CDlgDisable48K : public CDialog
{
// Construction
public:
	CDlgDisable48K(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDisable48K)
	enum { IDD = IDD_DISABLE48K };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDisable48K)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDisable48K)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDISABLE48K_H__C138679E_52BF_4918_B892_5E671B6E02CF__INCLUDED_)
