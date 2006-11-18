// dlgnetge.h : header file
//

#ifndef DLGNETGENERAL

#include "network.h"

class	CDlgNetwork;

/////////////////////////////////////////////////////////////////////////////
// CDlgNetGeneral dialog

class CDlgNetGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgNetGeneral)

// Construction
public:
	CDlgNetGeneral();
	~CDlgNetGeneral();
	CDlgNetwork		*m_pParent;

// Dialog Data
	//{{AFX_DATA(CDlgNetGeneral)
	enum { IDD = IDD_NETGENERAL };
	CString	m_csDescript;
	CString	m_csLastDate;
	CString	m_csFirstDate;
	BOOL	m_bDoImpedance;
	BOOL	m_bAutoChart;
	BOOL	m_bDoResponse;
	//}}AFX_DATA

public:
   	void UseGeneral( CNetwork *pcNet);
	void SetGeneral( CNetwork *pcNet);


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgNetGeneral)
	public:
	virtual void OnFinalRelease();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgNetGeneral)
	afx_msg void OnAutochart();
	afx_msg void OnDoimpedance();
	afx_msg void OnDoreponse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgNetGeneral)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define DLGNETGENERAL
#endif

