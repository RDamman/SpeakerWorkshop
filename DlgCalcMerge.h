#if !defined(AFX_DLGCALCMERGE_H__1A93C467_B139_43B1_BF0F_0325766ED5BB__INCLUDED_)
#define AFX_DLGCALCMERGE_H__1A93C467_B139_43B1_BF0F_0325766ED5BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCalcMerge.h : header file
//

#include "ZFormEdt.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcMerge dialog

class CDlgCalcMerge : public CDialog
{
// Construction
public:
	CDlgCalcMerge(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCalcMerge)
	enum { IDD = IDD_CALCMERGE };
	CzFormatStatic	m_czPortUnits;
	CzFormatStatic	m_czPistonUnits;
	CString	m_csDriver;
	CString	m_csPort;
	//}}AFX_DATA

								// used to communicate with app
	DWORD		m_dwDriver;		// driver nearfield
	DWORD		m_dwPort;		// port nearfield
	CFolder		*m_pRoot;		// the root for finding strings
// ------------------------------------
	float		m_fPistonArea;	// the piston area
	float		m_fPortArea;	// the port area

		CzFormatGroup		m_cfEdits;
// ------------------------------------

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCalcMerge)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCalcMerge)
	virtual BOOL OnInitDialog();
	afx_msg void OnHitdriver();
	afx_msg void OnHitport();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCALCMERGE_H__1A93C467_B139_43B1_BF0F_0325766ED5BB__INCLUDED_)
