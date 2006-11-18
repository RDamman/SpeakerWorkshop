#if !defined(AFX_DLGFLDGE_H__586BC421_8709_11D4_BBF9_00A0C9923AAC__INCLUDED_)
#define AFX_DLGFLDGE_H__586BC421_8709_11D4_BBF9_00A0C9923AAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFldGe.h : header file
//
#include "Folder.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgFldGeneral dialog

class CDlgFldGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgFldGeneral)

// Construction
public:
	CDlgFldGeneral();
	~CDlgFldGeneral();

private:
	CFolder	*m_pFolder;

public:
	void SetFolder( CFolder *pFolder);
// Dialog Data
	//{{AFX_DATA(CDlgFldGeneral)
	enum { IDD = IDD_FLDGENERAL };
	CString	m_csDate;
	CString	m_csDescript;
	CString	m_csLastEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgFldGeneral)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgFldGeneral)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFLDGE_H__586BC421_8709_11D4_BBF9_00A0C9923AAC__INCLUDED_)
