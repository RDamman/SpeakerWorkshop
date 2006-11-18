#if !defined(AFX_DLGDOCGE_H__AB7982C1_52F8_11D2_AAC6_00A0C9923AAC__INCLUDED_)
#define AFX_DLGDOCGE_H__AB7982C1_52F8_11D2_AAC6_00A0C9923AAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDocGe.h : header file
//

#include "AudteDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDocGeneral dialog

class CDlgDocGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgDocGeneral)

// Construction
public:
	void PreDialog( CAudtestDoc *pDoc);
	void PostDialog( CAudtestDoc *pDoc);
	CDlgDocGeneral();
	~CDlgDocGeneral();

// Dialog Data
	//{{AFX_DATA(CDlgDocGeneral)
	enum { IDD = IDD_DOCGENERAL };
	CString	m_csDate;
	CString	m_csDescript;
	CString	m_csLastEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgDocGeneral)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CAudtestDoc *m_pDocument;
	// Generated message map functions
	//{{AFX_MSG(CDlgDocGeneral)
	afx_msg void OnChangeDescript();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDOCGE_H__AB7982C1_52F8_11D2_AAC6_00A0C9923AAC__INCLUDED_)
