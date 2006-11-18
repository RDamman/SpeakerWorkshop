// audtevw.h : interface of the CAudDataView class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CDATAVW

#include "audtevw.h"

class CAudDataView : public CAudchView
{
protected: // create from serialization only
	CAudDataView();
	DECLARE_DYNCREATE(CAudDataView)

// Attributes
protected:
	float m_fMin[3];	// the three mins
	float m_fMax[3];	// the three maxes

// Operations

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudDataView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAudDataView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAudDataView)
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnTransformLimit();
	afx_msg void OnTransformScale();
	afx_msg void OnTransformTruncate();
	afx_msg void OnTransformSmooth();
	afx_msg void OnTransformDelay();
	afx_msg void OnCalculateCombine();
	afx_msg void OnCalculateIfft();
	afx_msg void OnCalculateFft();
	afx_msg void OnCalculateImpedance();
	afx_msg void OnEditChart();
	afx_msg void OnCalculateCorrelation();
	afx_msg void OnTransformInvert();
	afx_msg void OnTransformFilter();
	afx_msg void OnUpdateCalculateFft(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCalculateIfft(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCalculateImpedance(CCmdUI* pCmdUI);
	afx_msg void OnCalculateGroupdelay();
	afx_msg void OnUpdateCalculateGroupdelay(CCmdUI* pCmdUI);
	afx_msg void OnCalculateFrequency();
	afx_msg void OnCalculateSplice();
	afx_msg void OnUpdateCalculateSplice(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTransformDelay(CCmdUI* pCmdUI);
	afx_msg void OnCalculateWaterfall();
	afx_msg void OnUpdateCalculateWaterfall(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#define CDATAVW
#endif

