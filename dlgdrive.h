// dlgdrive.h : header file
//

#ifndef DLGDRIVER

#include "dlgdrgen.h"
#include "dlgdrPar.h"
#include "dlgDrDat.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDriver

class CDlgDriver : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgDriver)

// Construction
public:
	CDlgDriver(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CAudtestDoc			*m_pDoc;		// document handle
	DWORD				m_dwID;			// id of the target object
   	CDlgDrGeneral	 	m_cGeneral;
	CDlgDrParms		 	m_cParms;
	CDlgDrData		 	m_cDatas;

	void SetDriver( CDriver *pData);
	void UseDriver( CDriver *pData);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDriver)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgDriver();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgDriver)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgDriver)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#define DLGDRIVER
#endif
