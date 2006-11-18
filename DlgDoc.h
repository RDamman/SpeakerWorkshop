#if !defined(AFX_DLGDOC_H__AB7982C0_52F8_11D2_AAC6_00A0C9923AAC__INCLUDED_)
#define AFX_DLGDOC_H__AB7982C0_52F8_11D2_AAC6_00A0C9923AAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDoc.h : header file
//

#include "DlgDocGe.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDoc

class CDlgDoc : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgDoc)

// Construction
public:
	CDlgDoc(BOOL bRoot = FALSE, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CDlgDocGeneral m_cGeneral;
// Operations
public:
	void PreDialog( CAudtestDoc *pDoc);
	void PostDialog( CAudtestDoc *pDoc);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDoc)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgDoc();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDOC_H__AB7982C0_52F8_11D2_AAC6_00A0C9923AAC__INCLUDED_)
