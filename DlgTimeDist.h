#if !defined(AFX_DLGTIMEDIST_H__3D6F366D_444B_4563_AE05_DF897C239C27__INCLUDED_)
#define AFX_DLGTIMEDIST_H__3D6F366D_444B_4563_AE05_DF897C239C27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTimeDist.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTimeDist dialog

class CDlgTimeDist : public CDialog
{
// Construction
public:
	CDlgTimeDist(CWnd* pParent = NULL);   // standard constructor
	static	bool	IsShowing( void)	{ return m_bIsShowing; }

// Dialog Data
	// -----------------------------------------------
	float	m_fAirTemp;
	float	m_fTime;
	float	m_fDistance;
	float	m_fFreq;

	CzFormatGroup		m_cfEdits;
	// -----------------------------------------------
	//{{AFX_DATA(CDlgTimeDist)
	enum { IDD = IDD_TIMEDIST };
	CzFormatStatic	m_czDist;
	CzFormatStatic	m_czUnits;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTimeDist)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
private:
	void recalc_Values( bool bTime);
	static bool m_bIsShowing;
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTimeDist)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeTime();
	afx_msg void OnChangeDistance();
	afx_msg void OnClose();
	afx_msg void OnChangeAirtemp();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnChangeFreq();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTIMEDIST_H__3D6F366D_444B_4563_AE05_DF897C239C27__INCLUDED_)
