#if !defined(AFX_DLGXFWATERFALL_H__CCD852E9_0EC6_42DB_A7D3_49BDBEE78429__INCLUDED_)
#define AFX_DLGXFWATERFALL_H__CCD852E9_0EC6_42DB_A7D3_49BDBEE78429__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgXfWaterfall.h : header file
//

#include "ZFormEdt.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgXfWaterfall dialog

class CDlgXfWaterfall : public CDialog
{
// Construction
public:
	CDlgXfWaterfall(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	CFolder *m_pRoot;		// the root object to use with the dwords
	DWORD	m_dwReference;	// the ref dataset
	DWORD	m_dwSource;		// the src dataset
	int		m_nStyle;		// std style 0=entire,1=marker,2=custom
	float	m_fStartMarker;
	float	m_fEndMarker;
// ------------------------------------
		float	m_fStart;
		float	m_fEnd;
		float	m_fTotalTime;
		float	m_fSmooth;		// smoothing

		CzFormatGroup		m_cfEdits;
// ------------------------------------
	//{{AFX_DATA(CDlgXfWaterfall)
	enum { IDD = IDD_XFWATERFALL };
	int		m_iSamples;
	CString	m_csMarkLow;
	CString	m_csMarkHigh;
	int		m_iWindow;
	CString	m_csReference;
	CString	m_csSource;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXfWaterfall)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DrawPointsInfo( void);
	// Generated message map functions
	//{{AFX_MSG(CDlgXfWaterfall)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEnd();
	afx_msg void OnChangeStart();
	afx_msg void OnUsecustom();
	afx_msg void OnDeltaposScrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSrcselect();
	afx_msg void OnRefnone();
	afx_msg void OnRefselect();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGXFWATERFALL_H__CCD852E9_0EC6_42DB_A7D3_49BDBEE78429__INCLUDED_)
