// treectrl.h : header file
//

#ifndef ZTREECTRL

/////////////////////////////////////////////////////////////////////////////
// ZcTreeCtrl window

/////////////////////////////////////////////////////////////////////////////
// CSubTree window

class ZcTreeCtrl;

class CSubTree : public CTreeCtrl
{
// Construction
public:
	CSubTree();

// Attributes
public:
	ZcTreeCtrl	*m_pParent;			// the parent window
// Operations
public:
	HTREEITEM GetFocused( void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubTree)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSubTree();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSubTree)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


class ZcTreeCtrl : public CWnd
{

	DECLARE_DYNAMIC(ZcTreeCtrl)


// Construction
public:
	ZcTreeCtrl();

// Attributes
public:
	CFolder		*m_pcRoot;			// the document root
	CSubTree	m_cTree;			// the tree
	CImageList *m_pImageList;

	CWnd		*m_pNotifyWnd;		// window to send notify messages

									// ------- drag and drop processing ONLY
	BOOL		m_bDragging;
	HTREEITEM	m_hDragItem;		// the item we're dragging
	DWORD		m_dwSourceID;		// the source object
	DWORD		m_dwTargetID;		// the target object
	CFolder		*m_cTargetRoot;		// the document for the target
	CWnd		*m_cWndTarget;		// the target window
	BOOL		m_bCopying;			// are we copying???
									// ------- end drag and drop processing ONLY

	bool		m_bInRightClick;	// are we in a right-click menu?
	HTREEITEM	m_hRightSel;		// right selected

									// ------ the filter for the tree
	NAMETYPES	m_nSelect;			// type to be selected (NAMETYPE or ntAny for all)
	UNITMSR		m_nUom;				// uom for data types only (UOM or uomAny for all)


// Operations
public:
 	void RebuildTree(CFolder *cRoot, DWORD dwID, LPARAM lHint = 0, CObject* pHint = NULL);
	CNamed *GetNextItem( CNamed *pItem, UINT nCode );
	HTREEITEM	FindItem( DWORD dwID, HTREEITEM hRoot = NULL);
	void	SetFilter( NAMETYPES nNew, UNITMSR nUom);
	void	SetNotifyWnd( CWnd *pNew)		{ m_pNotifyWnd = pNew; }

//	void BeginDrag(HTREEITEM hItem, POINT *lpPt);
	void BeginDrag(NM_TREEVIEW *pItem);
	void DropItem(UINT nFlags );
	BOOL HasFocus( void);			// do we have the focus???
	BOOL WantCommand(UINT uID);		// can we process this command???
	CNamed *GetSelection( void);
	afx_msg void OnUpdateEditTemp(CCmdUI* pCmdUI);
	bool OnMakeTempString(CString &csNew);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ZcTreeCtrl)
	public:
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~ZcTreeCtrl();

	afx_msg UINT OnGetDlgCode( )		{ return DLGC_WANTALLKEYS; }


	// Generated message map functions
protected:
	//{{AFX_MSG(ZcTreeCtrl)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditDelete();
	afx_msg void OnResourceOpen();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnEditCopy();
	afx_msg void OnEditProperties();
	afx_msg void OnResourceRename();
	afx_msg void OnEditTemp();
	afx_msg void OnResourceExport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#define ZTREECTRL
#endif
