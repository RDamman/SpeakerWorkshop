// audtevw.h : interface of the CAudChartView class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CCHARTVW

#include "audtevw.h"

class CAudChartView : public CAudchView
{
protected: // create from serialization only
	CAudChartView();
	DECLARE_DYNCREATE(CAudChartView)

// Attributes
	CWnd 	*m_pLocations;
protected:
// Operations
	afx_msg LONG OnLocationGone( WPARAM wParam, LPARAM lParam );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudChartView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAudChartView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAudChartView)
	afx_msg void OnCancelEditSrvr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#define CCHARTVW
#endif

