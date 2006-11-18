#if !defined(AFX_DLGNETOPTIMIZE_H__5F3087E3_3AAD_4092_9990_4D049C96ABAF__INCLUDED_)
#define AFX_DLGNETOPTIMIZE_H__5F3087E3_3AAD_4092_9990_4D049C96ABAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNetOptimize.h : header file
//

#include "zFormEdt.h"

/////////////////////////////////////////////////////////////////////////////
// CCheckList window

class CCheckList : public CCheckListBox
{
// Construction
public:
	CCheckList();

// Attributes
public:
	BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	void SetVariables( CWnd *pBasis);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCheckList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCheckList)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CDlgNetOptimize dialog

class CDlgNetOptimize : public CDialog
{
// Construction
public:
	CDlgNetOptimize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
// ------------------------------------
		float	m_fStart;
		float	m_fEnd;

		CzFormatGroup		m_cfEdits;
// ------------------------------------
		DWORD		m_dwTarget;				// the target id
		CNetwork	*m_pNetwork;			// the network we're using
		CCheckList	m_cComponentList;		// the check list of components
		CUIntArray	m_cVary;				// the list of items to vary (built on ok)

	//{{AFX_DATA(CDlgNetOptimize)
	enum { IDD = IDD_NETOPTIMIZE };
	int		m_iPoints;
	CString	m_csTarget;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNetOptimize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UseTarget( void);

	// Generated message map functions
	//{{AFX_MSG(CDlgNetOptimize)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSeltarget();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


class CXtNetOptimize : public CXunary
{
	public:
		float	m_fStart;
		float	m_fEnd;
		int		m_iPoints;
		DWORD	m_dwTarget;
		CUIntArray m_cuVary;				// which items (indices in discretearray) to vary

	public:
		virtual UINT DoDialog( void);		// xeq dbox
		virtual UINT GetDialog(void);		// get the dialog id
		virtual int  DoOperation( void);		// do it
		UINT GetNameID()					{ return IDOP_NETOPT; }

	private:

	public:
		CXtNetOptimize( CObject *cTarget);		// must be named and in the tree
		~CXtNetOptimize();
};




/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNETOPTIMIZE_H__5F3087E3_3AAD_4092_9990_4D049C96ABAF__INCLUDED_)
