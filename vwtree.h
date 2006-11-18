// audtevw.h : interface of the CAudTreeView class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CTREEVW

#include "audtevw.h"

#include "treectrl.h"

#include "DlgRoot.h"

class CAudTreeView : public CAudtestView
{
protected: // create from serialization only
	CAudTreeView();
	DECLARE_DYNCREATE(CAudTreeView)

// Attributes
	CDlgRootView	m_cRootView;
protected:
// Operations
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudTreeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
private:

public:
	virtual ~CAudTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAudTreeView)
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnUpdateEdits(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#define CTREEVW
#endif

