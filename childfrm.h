// childfrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CCHILDFRAME

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
protected:
//	CSplitterWnd m_wndSplitter;
	DWORD	m_dwTarget;			// the target object for this frame
	CString	m_csTitle;			// title of this window...
public:
	DWORD	GetTarget();
	void	SetTarget(DWORD dwNew, LPCSTR lpszTitle);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#define CCHILDFRAME
#endif
