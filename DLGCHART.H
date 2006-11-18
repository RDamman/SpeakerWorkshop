// dlgchart.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgChart

#ifndef DLGCHART

#include "dlgchdat.h"
#include "dlggrid.h"
#include "dlgchgen.h"

class CDlgChart : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgChart)

// Construction
public:
	CDlgChart(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
   	void UseChart( CNamed *pcRoot, CSubChart *pcGen, CObject *cFirst = NULL);
	void SetChart( CSubChart *pcGen);

private:
	CDlgChData 		m_cData;
	CDlgGridX		m_cGridX;
	CDlgGridY		m_cGridY;
	CDlgGridY2		m_cGridY2;
	CDlgChGen	 	m_cGeneral;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgChart)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgChart();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgChart)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgChart)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#define DLGCHART 1
#endif

