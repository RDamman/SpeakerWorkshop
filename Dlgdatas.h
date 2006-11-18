// dlgdatas.h : header file
//


#ifndef DLGDATASET

#include "dlgdsgen.h"
#include "dlgdsdat.h"

#include "dataset.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDataset

class CDlgDataset : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgDataset)

// Construction
public:
	CDlgDataset(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDataSet *m_pcCaller;

// Attributes
public:
	CDlgDsGeneral	 	m_cGeneral;
	CDlgDsDataset	 	m_cDataset;
	void PreDialog( CDataSet *pData);
	void PostDialog( CDataSet *pData);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDataset)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgDataset();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgDataset)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgDataset)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#define DLGDATASET
#endif
