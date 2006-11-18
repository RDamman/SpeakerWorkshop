#if !defined(AFX_BARNETWORK_H__C8F94B19_111F_478F_8E0D_7FE92E29B7B5__INCLUDED_)
#define AFX_BARNETWORK_H__C8F94B19_111F_478F_8E0D_7FE92E29B7B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zFormEdt.h"

// BarNetwork.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBarNetwork dialog

class CBarNetwork : public CDialog
{
// Construction
public:
	CObject * GetSelected( void);
	void SetSelected( CObject *pSel);
	CBarNetwork(CWnd* pParent = NULL);   // standard constructor
	static	bool	IsShowing( void)	{ return m_bIsShowing; }

	float	GetValue( void);
	void	SetValue( float fValue);

// Dialog Data
	// -----------------------------------------------
	float	m_fValue;
	CzFormatGroup		m_cfEdits;
	// -----------------------------------------------
	//{{AFX_DATA(CBarNetwork)
	enum { IDD = IDD_NETBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBarNetwork)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
private:
	static bool m_bIsShowing;
	CObject		*m_pSelected;			// the selected object in the network
protected:

	// Generated message map functions
	//{{AFX_MSG(CBarNetwork)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnApply();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BARNETWORK_H__C8F94B19_111F_478F_8E0D_7FE92E29B7B5__INCLUDED_)
