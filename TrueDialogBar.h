// TrueDialogBar.h : header file
//

#ifndef CTRUEDIALOG

#include "SplitBar.h"
#include "TreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CTrueDialogBar window


class CzSuperBar : public CControlBar
{
// Construction
public:
	CzSuperBar();

// Attributes
protected:
	CSize		m_CurrentSize;

private:
	CFrameWnd	*m_pFrame;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CzSuperBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CzSuperBar();
							// create the dialogbar
	BOOL Create( CWnd* pParentWnd,  UINT nStyle, UINT nID);
							// return the cdialog contained within
	CSize	GetSize()							{ return m_CurrentSize; }
	void	SetSize( CSize& csNew);
	void	RecalcSize( void);
	CFrameWnd *GetFrame(void)					{ return m_pFrame; }

	// Generated message map functions
protected:
	//{{AFX_MSG(CzSuperBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CTrueDialogBar : public CzSuperBar
{
// Construction
public:
	CTrueDialogBar();

// Attributes
protected:

private:
	CDialog		*m_pDialog;			// the actual dbox and its code

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrueDialogBar)
	//}}AFX_VIRTUAL
	virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler );

// Implementation
public:
	virtual ~CTrueDialogBar();
							// create the dialogbar
	BOOL Create( CWnd* pParentWnd,  UINT nStyle, UINT nID );
							// return the cdialog contained within
	CDialog *GetTrueDialog( void)				{ return m_pDialog; }
	void	AttachDialog( CDialog *pDialog);	// attach a dialog

	// Generated message map functions
protected:
	//{{AFX_MSG(CTrueDialogBar)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

class CTreeBar : public CzSuperBar
{
// Construction
public:
	CTreeBar();

// Attributes
protected:
	CSplitterBar		m_cSplitter;
	ZcTreeCtrl			m_cTree;

// Operations
public:
	void UpdateTree( CDocument *pDoc, LPARAM lHint, CObject* pHint);
	CNamed *GetCurrentSelection( void);		// may return NULL if nothing sel'ed
	BOOL	HasFocus( void);
	BOOL	WantCommand( UINT uID);			// can the tree process this command?
	ZcTreeCtrl			*GetControl( void) 	{ return &m_cTree; }
	// -----------------------------------------------

private:
	void Draw3dBox( CPaintDC& cDC, int nX, int nY, int nXf, int nYf);
	void CalculateClient( CRect& crDest);
	void Reshape( void);				// move the splitter bar around and resize the client
	CRect	rcWindow;					// the window location and size

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeBar)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
	virtual CSize CalcDynamicLayout(int nLength, DWORD nMode);
	virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler );

// Implementation
public:
	virtual ~CTreeBar();
							// create the dialogbar
	BOOL Create( CWnd* pParentWnd,  UINT nStyle, UINT nID );

	// Generated message map functions
protected:
	//{{AFX_MSG(CTreeBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

class CVuMeterBar : public CTrueDialogBar
{
// Construction
public:
	CVuMeterBar();

// Attributes
private:
	bool	m_bHasText;
public:
	void SetLeftEntries( float fMax, float fAve, float fMin);
	void SetRightEntries( float fMax, float fAve, float fMin);
	void GetLeftEntries( float &fMax, float &fAve, float &fMin);
	void GetRightEntries( float &fMax, float &fAve, float &fMin);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVuMeterBar)
	//}}AFX_VIRTUAL
	virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler );

// Implementation
public:
	virtual ~CVuMeterBar();
							// create the dialogbar
	BOOL Create( CWnd* pParentWnd,  UINT nStyle, UINT nID );

	// Generated message map functions
protected:
	//{{AFX_MSG(CVuMeterBar)

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// -----------------------------------------------------------
// Location Bar
// -----------------------------------------------------------

class CLocationBar : public CTrueDialogBar
{
// Construction
public:
	CLocationBar();

// Attributes
private:
	bool	m_bHasText;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocationBar)
	//}}AFX_VIRTUAL
	virtual void OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler );

// Implementation
public:
	virtual ~CLocationBar();
							// create the dialogbar
	BOOL Create( CWnd* pParentWnd,  UINT nStyle, UINT nID );

	// Generated message map functions
protected:
	//{{AFX_MSG(CLocationBar)

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////



#define CTRUEDIALOG
#endif
