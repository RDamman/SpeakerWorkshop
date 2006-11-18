#if !defined(AFX_DLGCHARTPROP_H__F50DE577_CE0E_4656_8979_8DF30CB2B545__INCLUDED_)
#define AFX_DLGCHARTPROP_H__F50DE577_CE0E_4656_8979_8DF30CB2B545__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgChartProp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgChartProp dialog

class CDlgChartProp : public CDialog
{
// Construction
public:
	CDlgChartProp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgChartProp)
	enum { IDD = IDD_CHARTPROP };
	CString	m_csDate;
	CString	m_csDescript;
	CString	m_csLastEdit;
	//}}AFX_DATA

	CChart	*m_pcChart;				// the chart
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgChartProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgChartProp)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHARTPROP_H__F50DE577_CE0E_4656_8979_8DF30CB2B545__INCLUDED_)
