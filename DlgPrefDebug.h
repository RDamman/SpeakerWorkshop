#if !defined(AFX_DLGPREFDEBUG_H__820B0421_EE9A_11D2_AAC8_00A0C9923AAC__INCLUDED_)
#define AFX_DLGPREFDEBUG_H__820B0421_EE9A_11D2_AAC8_00A0C9923AAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPrefDebug.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefDebug dialog

class CDlgPrefDebug : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgPrefDebug)

// Construction
public:
	CDlgPrefDebug();
	~CDlgPrefDebug();

// Dialog Data
	//{{AFX_DATA(CDlgPrefDebug)
	enum { IDD = IDD_PREFDEBUG };
	BOOL	m_bDebug;
	int		m_iWarmamount;
	//}}AFX_DATA

// ------------------------------------
		float	m_fLatent;

		CzFormatGroup		m_cfEdits;
// ------------------------------------

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgPrefDebug)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPrefDebug)
	virtual BOOL OnInitDialog();
	afx_msg void OnDebugon();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREFDEBUG_H__820B0421_EE9A_11D2_AAC8_00A0C9923AAC__INCLUDED_)
