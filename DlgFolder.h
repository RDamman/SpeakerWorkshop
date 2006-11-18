#if !defined(AFX_DLGFOLDER_H__C27CCF61_8706_11D4_BBF9_00A0C9923AAC__INCLUDED_)
#define AFX_DLGFOLDER_H__C27CCF61_8706_11D4_BBF9_00A0C9923AAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFolder.h : header file
//

#include "DlgFldGe.h"


/////////////////////////////////////////////////////////////////////////////
// CDlgFolder

class CDlgFolder : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgFolder)

// Construction
public:
	CDlgFolder(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CDlgFldGeneral m_cGeneral;

	void		SetFolder( CFolder *pFolder);
private:
	CFolder			*m_pFolder;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFolder)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgFolder();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgFolder)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFOLDER_H__C27CCF61_8706_11D4_BBF9_00A0C9923AAC__INCLUDED_)
