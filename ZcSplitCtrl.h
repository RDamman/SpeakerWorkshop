// ZcSplitCtrl.h : header file
//

#ifndef ZCSPLITCTRL

/////////////////////////////////////////////////////////////////////////////
// ZcSplitCtrl window

class ZcSplitCtrl : public CWnd
{
// Construction
public:
	ZcSplitCtrl();

// Attributes
public:
	int m_nOrient;			// the orientation

// Operations
public:
	void SetOrientation( int nNewOrient)	{ m_nOrient = nNewOrient; }
	int  GetOrientation( void )				{ return m_nOrient; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZcSplitCtrl)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ZcSplitCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(ZcSplitCtrl)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#define ZCSPLITCTRL
#endif
