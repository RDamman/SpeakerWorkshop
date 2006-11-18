// audtevw.h : interface of the CAudEnclView class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CENCLVW

#include "audtevw.h"

class CAudEnclView : public CAudchView
{
protected: // create from serialization only
	CAudEnclView();
	DECLARE_DYNCREATE(CAudEnclView)

// Attributes
private:
	int		m_iRowWidth;
	int		m_iColWidth;
	int		m_iMaxHeight;
protected:
// Operations

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudEnclView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAudEnclView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

private:
	void calc_Dialog( CDialog *cDlg);

// Generated message map functions
protected:
	//{{AFX_MSG(CAudEnclView)
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnEditRename();
	afx_msg void OnCalcSealed();
	afx_msg void OnCalcVented();
	afx_msg void OnCalcBandchamber();
	afx_msg void OnCalcBandair();
	afx_msg void OnCalculateFrequencyresponse();
	afx_msg void OnCalculateImpedance();
	afx_msg void OnCalculateGroupdelay();
	afx_msg void OnCalculateConeexcursion();
	afx_msg void OnCalculateTransientresponse();
	afx_msg void OnUpdateCalculateConeexcursion(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCalculateGroupdelay(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCalculateImpedance(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCalculateTransientresponse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCalculateFrequencyresponse(CCmdUI* pCmdUI);
	afx_msg void OnCalcMerge();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#define CENCLVW
#endif

