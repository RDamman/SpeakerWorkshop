#if !defined(AFX_DLGCREATEGOAL_H__EEA7D12A_C67D_4399_A75E_C4E83CBEC6FC__INCLUDED_)
#define AFX_DLGCREATEGOAL_H__EEA7D12A_C67D_4399_A75E_C4E83CBEC6FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCreateGoal.h : header file
//

#include "zFormEdt.h"


enum	selGoalType
{
	sglValue = 0,
	sglDriver = 1,
	sglData = 2
};



/////////////////////////////////////////////////////////////////////////////
// CDlgCreateGoal dialog

class CDlgCreateGoal : public CDialog
{
// Construction
public:
	CDlgCreateGoal(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCreateGoal)
	enum { IDD = IDD_CREATEGOAL };
	int		m_nHighLow;
	int		m_nOrder;
	int		m_iDriver;
	CString	m_csDataset;
	int		m_nType;
	//}}AFX_DATA

// ------------------------------------
		float	m_fFS;
		float	m_fValue;
		float	m_fStart;
		float	m_fEnd;

		CzFormatGroup		m_cfEdits;
// ------------------------------------

	selGoalType	 m_isUseWhich;		// do we want to use a driver?
	DWORD		 m_dwDriver;		// the driver to use
	DWORD		 m_dwDataset;
	CNetwork	*m_pNetwork;		// the network we are using

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCreateGoal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
		void setup_List(void );
		void setup_DriverList( void);
		void copy_String( int nWhich);
		void setup_Radios( selGoalType slUse);	// set the radios up
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCreateGoal)
	afx_msg void OnSelchangeOrder();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSeldriver();
	afx_msg void OnSelvalue();
	afx_msg void OnSeldata();
	afx_msg void OnSelchangeDriver();
	afx_msg void OnChangeValue();
	afx_msg void OnBrowse();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCREATEGOAL_H__EEA7D12A_C67D_4399_A75E_C4E83CBEC6FC__INCLUDED_)
