#if !defined(AFX_DLGBURST_H__E39D32F9_5522_419B_866A_D47DE7844214__INCLUDED_)
#define AFX_DLGBURST_H__E39D32F9_5522_419B_866A_D47DE7844214__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBurst.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBurst dialog

class CDlgBurst : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgBurst)

// Construction
public:
	CDlgBurst();
	~CDlgBurst();

// Dialog Data
// ------------------------------------
		float	m_fStart;
		float	m_fEnd;

		CzFormatGroup		m_cfEdits;
// ------------------------------------
// Dialog Data
	//{{AFX_DATA(CDlgBurst)
	enum { IDD = IDD_BURST };
	UINT	m_nCycles;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgBurst)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgBurst)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBURST_H__E39D32F9_5522_419B_866A_D47DE7844214__INCLUDED_)
