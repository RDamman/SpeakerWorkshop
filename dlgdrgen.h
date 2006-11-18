// dlgdrgen.h : header file
//

#ifndef DLGDRGEN

#include "Driver.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDrGeneral dialog

class CDlgDrGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgDrGeneral)

// Construction
public:
	CDlgDrGeneral();
	~CDlgDrGeneral();

	void SetGeneral( CDriver *pData);
	void UseGeneral( CDriver *pData);


// Dialog Data
	//{{AFX_DATA(CDlgDrGeneral)
	enum { IDD = IDD_DRGENERAL };
	CString	m_szDescription;
	CString	m_szDate;
	CString	m_szLastEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgDrGeneral)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgDrGeneral)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgDrGeneral)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define DLGDRGEN
#endif
