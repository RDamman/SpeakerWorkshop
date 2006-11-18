// Named.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CFOLDER

class CFolder : public CNamed
{

	friend class CDlgFolder;

protected: // create from serialization only
	DECLARE_SERIAL(CFolder)

// Attributes
protected:
	CNamedArray m_coArray;
	CDocument   *m_pcDoc;		// for the root object only, the document pointer

// Operations
public:
 	CFolder();
	virtual int EditProperties(CWnd *pWnd, CObject *cSubject = NULL);	// bring up properties dbox

					// ------------- folder specific
public:
	void AddItem( CNamed *cnAdd);						// add a new item
	void Insert( CNamed *cnAdd, DWORD dwID);			// insert into the tree
	void DeleteItem( DWORD dwID);						// remove an item
	void RemoveItem( DWORD dwID);						// non-destructive item removal
	void DeleteAllTemps( void);							// delete the temporary items
	CNamed *GetItem( DWORD dwID, BOOL bSubs = TRUE);	// find an item by ID, return ptr
	CNamed *GetItemByName( LPCSTR lpszName, BOOL bSubs = TRUE);	// find an item by name, return ptr
	CNamed *GetItemAt( int nPos);						// get item from list
	int	 GetSize( bool bSubs);
	CNamedArray *GetItemList();
	CFolder *GetParent(DWORD dwID);							// get the parent folder
	void	SetDocument( CDocument *pDoc)			{ m_pcDoc = pDoc; }
	bool	ReplacePointer( CNamed *pNew, DWORD dwID);			// use this guy's pointer for a replacement

	virtual CDocument *GetDocument( void)					{ if ( m_pcDoc) return m_pcDoc; return ((CFolder *)GetRootObject())->GetDocument(); }

// Implementation
public:
	int GetCount( NAMETYPES nType);
	virtual DWORD GetObjectSize( BOOL bDive);
	virtual ~CFolder();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

	virtual CNamed *Duplicate();				// make a duplicate object (different id)
	CNamed &operator=(const CNamed &cIn);
	CFolder &operator=(const CFolder &cIn);

	virtual NAMETYPES GetType(void) const		{ return ntFolder; }

#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif

protected:

};


#define CFOLDER

#endif
