#if !defined(AFX_DLGVOLUMECALC_H__808862A5_C1DE_4FC8_BE3C_801038FC5E14__INCLUDED_)
#define AFX_DLGVOLUMECALC_H__808862A5_C1DE_4FC8_BE3C_801038FC5E14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVolumeCalc.h : header file
//

#include "zFormEdt.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgVolumeCalc dialog

class CDlgVolumeCalc : public CDialog
{
// Construction
public:
	CDlgVolumeCalc(CWnd* pParent = NULL);   // standard constructor
	static	bool	IsShowing( void)	{ return m_bIsShowing; }

	static	bool	m_bIsShowing;

// Dialog Data
	// -----------------------------------------------
	float	m_fVolume;
	float	m_fHeight;
	float	m_fWidth;
	float	m_fDepth;
	float	m_fRatio;

	CzFormatGroup		m_cfEdits;
	// -----------------------------------------------
	//{{AFX_DATA(CDlgVolumeCalc)
	enum { IDD = IDD_VOLUMECALC };
	CzFormatStatic	m_czStdWidth;
	CzFormatStatic	m_czStdVolume;
	CzFormatStatic	m_czStdHeight;
	CzFormatStatic	m_czStdDepth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVolumeCalc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	void recalc_Values(bool bCalcVolume);

	// Generated message map functions
	//{{AFX_MSG(CDlgVolumeCalc)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeWidth();
	afx_msg void OnChangeVolume();
	afx_msg void OnChangeDepth();
	afx_msg void OnChangeHeight();
	afx_msg void OnClose();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnUseratio();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVOLUMECALC_H__808862A5_C1DE_4FC8_BE3C_801038FC5E14__INCLUDED_)
