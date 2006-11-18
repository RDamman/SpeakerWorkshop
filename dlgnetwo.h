// dlgnetwo.h : header file
//

#ifndef DLGNETWORK

#include "network.h"

#include "dlgNetDr.h"
#include "dlgNetLi.h"
#include "dlgNetGe.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgNetwork

class CDlgNetwork : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgNetwork)

// Construction
public:
	CDlgNetwork(CWnd* pParentWnd, UINT iSelectPage = 0);

// Attributes
public:
	CDlgNetGeneral	 	m_cGeneral;
	CDlgNetList	 		m_cDatalist;
	CDlgNetDriver	 	m_cDrivers;

	bool				bReapply( void)				{ return m_bDidApply; }
	void				SetReapply( bool bNew);

	void SetNetwork( CNetwork *pData);
	void UseNetwork( CNetwork *pData, CObject *cSubject);

// Operations
public:
private:
	bool			m_bDidApply;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNetwork)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgNetwork();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgNetwork)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgNetwork)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define DLGNETWORK
#endif

/////////////////////////////////////////////////////////////////////////////
