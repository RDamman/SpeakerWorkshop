// audtevw.h : interface of the CAudRoomView class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CROOMVW

#include "audtevw.h"

class CAudRoomView : public CAudtestView
{
protected: // create from serialization only
	CAudRoomView();
	DECLARE_DYNCREATE(CAudRoomView)

// Attributes
protected:
// Operations

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudRoomView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAudRoomView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAudRoomView)
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnEditRename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#define CROOMVW
#endif

