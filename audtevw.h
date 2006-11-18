// audtevw.h : interface of the CAudtestView class
//
/////////////////////////////////////////////////////////////////////////////


#ifndef AUDTESTVIEW

typedef struct tagFormField
{
	int		iX;
	int		iY;
	UINT	uidPrompt;
	UINT	uidEndPrompt;
} sFormField;

class CDrawObj;


class CAudtestView : public CView
{
protected: // create from serialization only
	CAudtestView();
	DECLARE_DYNCREATE(CAudtestView)

// Attributes
public:
	CAudtestDoc* GetDocument();
protected:

protected:
	void	*m_pOperation;				// the thing we're current executing

	CPoint	 m_ptMouseDown;			// where the mouse went down
	CPoint	 m_ptMouseUp;			// where the mouse went up
	CRectTracker *m_pTracker;		// track that rectangle
	NAMETYPES	m_nTrackType;		// type of track
	CDrawObj *m_pTrackObject;		// the object we're tracking

	RECT	m_rcPrint;				// the print region

// Operations
protected:
	void	StdOperation( void *pOpcode);		// local guy to handle the std operation
public:
	void	FinishInput( void);
	void	FinishPlay( void);

public:
	DWORD	GetTarget( void);					// get this guy's target object id
	void	ResetTarget( void);					// reassign the target stuff
	CNamed *GetTargetObject( void);				// get target id and convert to target object*
	void	UpdateTarget( void);				// do an updateview for the target

	BOOL DoPopupMenu(UINT x, UINT y);
	virtual	UINT GetMenuResource(void );

	CRectTracker *GetTracker( void)					{ return m_pTracker; }
	NAMETYPES	GetTrackType( void)					{ return m_nTrackType; }
	void		  SetTracker( CRectTracker *cNew, CDrawObj *pObject);

	void	*GetCurrentOperation()					{ return m_pOperation; }
	void	SetCurrentOperation( void *pNew)		{ m_pOperation = pNew; }

	CPoint	GetMouseDown( void)						{ return m_ptMouseDown; }
	CPoint	GetMouseUp( void)						{ return m_ptMouseUp; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudtestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAudtestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void Dialog_Perform(void *);		// takes a xform pointer

// Generated message map functions
protected:
	CDialog* GetDlgBar( void);			// get the dialog bar
	//{{AFX_MSG(CAudtestView)
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnEditProperties();
	afx_msg void OnResourceRename();
	afx_msg void OnResourceImport();
	afx_msg void OnResourceExport();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSoundStop();
	afx_msg void OnOptionsCalibrate();
	afx_msg void OnOptionsTuned();
	afx_msg void OnOptionsPassive();
	afx_msg void OnWizardSetvolume();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnOptionsDistance();
	afx_msg void OnOptionsVolume();
	//}}AFX_MSG

	afx_msg LRESULT OnWimData( WPARAM, LPARAM);
 	afx_msg LRESULT OnWomDone( WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()
};

//	#ifndef _DEBUG  // debug version in audtevw.cpp
//	inline CAudtestDoc* CAudtestView::GetDocument()
//   { return (CAudtestDoc*)m_pDocument; }
//	#endif

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CAudchView view
// this is the sub-chart view used by
//		Chart, Generator, Dataset, Enclosure, Driver(?), Room(?)
class CAudchView : public CAudtestView
{
protected:
	CAudchView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAudchView)

// Attributes
private:
	int		m_iCharHeight;		// character height
	int		m_iCharWidth;		// character width
	CDC		*m_pDrawDC;			// cached draw dc
	POINT	m_ptFloatFormat;	// the float format
	int		m_iIntFormat;		// the int format
protected:
	CSubChart	*m_cChart;				// the chart object
	RECT		m_rcSubview;			// if drawn in a subview
									// temporaries used during printing
public:
	CSubChart *GetViewChart( void)							{ return m_cChart; }
	void	SetViewChart( CSubChart *cNew);
	void	MakeViewChart( void);		// make a view chart
	void	SyncDataSets( void);		// synchronize with the target object's chart data
	void	UpdateBaseChart( void);		// copy the current view chart to the base chart
protected:
	int		DrawVariable( CDC *pDC, sFormField *pField, bool bValue);		// draw a boolean yes/no
	int		DrawVariable( CDC *pDC, sFormField *pField, int iVar, int iOffset);
	int		DrawVariable( CDC *pDC, sFormField *pField, float fVar, int iOffset);		// draw a variable in the form field
	int		DrawVariable( CDC *pDC, sFormField *pField, CString &csOut);	// draw a variable in the form field
	int		DrawForm( CDC *pDC, sFormField *pField);						// draw a variable in the form field
	int		FormExtent( CDC *pDC, sFormField *pField);						// draw a variable in the form field
	int		CharHeight( CDC *pDC);
	int		CharWidth( CDC *pDC);
	void	SetFloatFormat( int iX, int iY)		{ m_ptFloatFormat.x = iX; m_ptFloatFormat.y = iY; }
	void	SetIntFormat( int iX)				{ m_iIntFormat = iX; }

	virtual	UINT GetMenuResource(void );
private:
	void	BuildCharSizes( CDC *pDC);		// build the character sizes

// Operations
public:
	void	SetSubView( LPCRECT lpcrNew);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudchView)
	public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAudchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CAudchView)
	afx_msg void OnEditChartproperties();
	afx_msg void OnMakeChart();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditDelete();
	afx_msg void OnEditInsert();
	afx_msg void OnUpdateEditData(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom();
	afx_msg void OnViewZoomout();
	afx_msg void OnChartAdddata();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnEditChartdefault();
	afx_msg void OnEditUsedefault();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChartNote();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#define AUDTESTVIEW
#endif
