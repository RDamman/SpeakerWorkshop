// srvritem.h : interface of the CAudtestSrvrItem class
//

#ifndef CSRVRITEM

class CAudtestSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(CAudtestSrvrItem)

// Constructors
public:
	CAudtestSrvrItem(CAudtestDoc* pContainerDoc);

// Attributes
	CAudtestDoc* GetDocument() const
		{ return (CAudtestDoc*)COleServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudtestSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CAudtestSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////

#define CSRVRITEM
#endif
