#if !defined(AFX_DLGDEFWR_H__0AD7E1A1_D333_11D4_BBF9_00A0C9923AAC__INCLUDED_)
#define AFX_DLGDEFWR_H__0AD7E1A1_D333_11D4_BBF9_00A0C9923AAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDefWr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDefaultWarning dialog

class CDlgDefaultWarning : public CDialog
{
// Construction
public:
	CDlgDefaultWarning(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDefaultWarning)
	enum { IDD = IDD_WARNDEFAULT };
	BOOL	m_bCheckInputRes;
	BOOL	m_bCheckResistor;
	BOOL	m_bCheckSeriesRes;
	BOOL	m_bCheckInputCap;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDefaultWarning)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDefaultWarning)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void FormatStatic( UINT uID, float fValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEFWR_H__0AD7E1A1_D333_11D4_BBF9_00A0C9923AAC__INCLUDED_)
