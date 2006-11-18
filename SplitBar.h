// SplitBar.h : header file
//

#ifndef SPLITTERBAR

/////////////////////////////////////////////////////////////////////////////
// CSplitterBar window

class CSplitterBar : public CWnd
{
// Construction
public:
	CSplitterBar();

// Attributes
private:
	BOOL	m_bDragging;
	CPoint	m_pLast;
	CPoint	m_pFirst;		// first spot

// Operations
protected:
	void	draw_SplitBar( CPoint& cPoint);

public:
	BOOL	IsVertical( void);
	BOOL	IsLeft( void);
	BOOL	IsTop( void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitterBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetWidth( void);
	virtual ~CSplitterBar();
	void	Create(CWnd *pParent, RECT& rcout, int nID);

	// Generated message map functions
protected:
	//{{AFX_MSG(CSplitterBar)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#define SPLITTERBAR
#endif

