// dlgselec.h : header file
//

#ifndef DLGSELECTOBJ

#include "TreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectObject dialog


class CDlgSelectObject : public CDialog
{
// Attributes
public:
										// --- these are all inputs from other programs
	CFolder		*m_cRoot;				// pointer to doc
	DWORD		m_dwTargetID;			// target to be highlighted, 0 if none
	NAMETYPES	m_nSelect;				// type to be selected (NAMETYPE or ntAny for all)
	UNITMSR		m_nUOM;					// uom for data types only (UOM or uomAny for all)
										// --- output from the program is result==dlg result ok
	DWORD		m_dwSelected;			// and the guy selected
	DWORD		m_dwLastSel;			// last one selected

	ZcTreeCtrl	m_cTree;				// the tree display for this view


	void SetParms( CFolder *cRoot, DWORD dwID = 0, NAMETYPES nSelect = ntAny, UNITMSR nUom = uomAny);
	DWORD GetSelected(void)  { return m_dwSelected; }

// Construction
public:
	CDlgSelectObject(CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(CDlgSelectObject)
	enum { IDD = IDD_SELECTOBJECT };
	CStatic	m_cTreeFrame;
	CString	m_csCreated;
	CString	m_csDescript;
	CString	m_csEdited;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelectObject)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSelectObject)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgSelectObject)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
private:
	BOOL m_bAllowOK;
};

#define DLGSELECTOBJ
#endif
