// mainfrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef CMAINFRAME

#include "TreeCtrl.h"
#include "TrueDialogBar.h"

typedef struct tagVuValues
{
	float	fMax;
	float	fAve;
	float	fMin;
} VuValues;

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	void UpdateTree( CView* pSender, LPARAM lHint = 0, CObject* pHint = NULL);
	CDialog *LocationWindow(void )			{ return m_wndLocations.GetTrueDialog(); }
	CDialog *VuMeterWindow(void )			{ return m_wndVuMeter.GetTrueDialog(); }
	CTreeBar *TreeBar( void)				{ return &m_wndTree;		}
	CDialog  *ResourceDlg( void)			{ return m_wndResourceDialog; }
	
	void SetLeftValues( float fMax, float fAve, float fMin);
	void SetRightValues( float fMax, float fAve, float fMin);
	VuValues GetVuValues( bool bRight);
	void SetVuValues( VuValues &vuNew, bool bRight);


private:
	UINT		m_idRestype;		// current resource bar idres
	UINT		m_idResDialog;		// dialog resource

// Operations
public:
	void CreateProgressBar( UINT uidCaption, UINT uMax);
	void CreateProgressBar( CString& csCaption, UINT uMax);
	void ShowProgressBar( UINT uCurrent);
	void StepProgressBar( void);
	void IncProgressBar( void);		// go to next increment if rollover
	void CloseProgressBar( void);

	void ResetToolbar( CView *pNewView);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	CDialog		*GetDialogBar( void);
	afx_msg BOOL OnSubBarCheck(UINT nID);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CLocationBar	m_wndLocations;
	CTreeBar		m_wndTree;
	CStatusBar		m_wndStatusBar;
	CVuMeterBar		m_wndVuMeter;

	CToolBar		m_wndToolBar;
	CToolBar		m_wndResourceBar;
	CDialog			*m_wndResourceDialog;

	CProgressCtrl	m_wndProgress;
	int				m_nProgressDepth;	// to handle deeper progress


// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnUpdateEdits(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditTemp(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnUpdateStatusValues(CCmdUI* pCmdUI);

protected:

	afx_msg LRESULT OnWimData( WPARAM, LPARAM);
 	afx_msg LRESULT OnWomDone( WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#define CMAINFRAME
#endif
