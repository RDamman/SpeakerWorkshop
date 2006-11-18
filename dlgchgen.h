// dlgchgen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgChGen dialog

#ifndef CDLGCHGEN

#include "chart.h"

class CDlgChGen : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgChGen)

// Construction
public:
	CDlgChGen();
	~CDlgChGen();

// Dialog Data
	//{{AFX_DATA(CDlgChGen)
	enum { IDD = IDD_CHGEN };
	CString	m_szDate;
	CString	m_szDescription;
	CString	m_csTitle;
	BOOL	m_bShowLegend;
	CString	m_csLastEdit;
	//}}AFX_DATA

public:
   	void UseGeneral( CSubChart *pcChart);
	void SetGeneral( CSubChart *pcChart);

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgChGen)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgChGen)
	afx_msg void OnSeltitlefont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgChGen)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};


#define CDLGCHGEN
#endif
