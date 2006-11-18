// audtevw.h : interface of the CAudNetView class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CNETVW

#include "audtevw.h"

class CAudNetView : public CAudtestView
{
protected: // create from serialization only
	CAudNetView();
	DECLARE_DYNCREATE(CAudNetView)

// Attributes
private:
	CObject *m_cSelect;			// who's selected during a mouse operation
	int		m_nHasCapture;		// do we have capture here? 0 = no, 1 = move, 2 = nodelink
	POINT	m_ptObj;			// location for object
	POINT	m_ptMouse;			// last mouse location
	POINT	m_ptMouseDown;		// where mouse was first pressed during a move or linedraw
	int		m_nNode;			// which node we've selected
	CObject *m_cOldNetwork;		// copy of old net during mouse moves

	POINT	m_ptViewOrg;		// origin in the viewport of the network (usually 0,0)
	POINT	m_ptWindowOrg;		// window origin
	float	m_fWindowScale;		// window zoom scale factor

private:
	void do_Deselect( CPoint& cpWhere);
	void do_Move( CPoint& cpWhere);
	void to_Logical( POINT& cpDevice);
	void to_Device( POINT& cpLogical);
	void rubber_Line( POINT ptStart, POINT ptEnd);
	void rubber_Box( POINT ptStart, POINT ptEnd);
	void set_DlgBar( void);				// set the dlg bar values
	void get_DlgBarValue( void);		// get the dlg bar values

// Operations

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudNetView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAudNetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual	UINT GetMenuResource(void );

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAudNetView)
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnCalculateFrequency();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnCalculatePerturb();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnEditCut();
	afx_msg void OnEditDelete();
	afx_msg void OnEditPaste();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditAny(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnNetworkAddCapacitor();
	afx_msg void OnNetworkAddInductor();
	afx_msg void OnNetworkAddResistor();
	afx_msg void OnNetworkStock();
	afx_msg void OnNetworkCompensation();
	afx_msg void OnViewZoom();
	afx_msg void OnViewZoomout();
	afx_msg void OnViewZoomall();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnNetworkGridOff();
	afx_msg void OnNetworkGrid2x2();
	afx_msg void OnNetworkGrid4x4();
	afx_msg void OnNetworkGrid8x8();
	afx_msg void OnUpdateNetworkGrid2x2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNetworkGrid4x4(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNetworkGrid8x8(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNetworkGridOff(CCmdUI* pCmdUI);
	afx_msg void OnNetworkLpad();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnNetworkCreategoal();
	afx_msg void OnNetworkOptimize();
	afx_msg void OnNetworkAddDriver();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#define CNETVW
#endif

