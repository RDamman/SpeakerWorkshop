// audtedoc.h : interface of the CAudtestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CAUDTEDOC

#include "folder.h"
#include "opcode.h"



typedef struct tagTESTCAL
	{
	DWORD		dwLeftRight;	// convert left to right channel
	DWORD		dwMicrophone;			// mic response
	DWORD		dwAmplifier;	// amp reference response
	} TESTCAL;

typedef TESTMARK far *LPTESTMARK;

class CAudtestSrvrItem;
class CAudtestView;

class CAudtestDoc : public COleServerDoc
{
protected: // create from serialization only
	CAudtestDoc();														  
	DECLARE_DYNCREATE(CAudtestDoc)

// Attributes
public:
	void FlushUndo( BOOL bRedo = TRUE);
	CAudtestSrvrItem* GetEmbeddedItem()
		{ return (CAudtestSrvrItem*)COleServerDoc::GetEmbeddedItem(); }

	void UpdateAll( CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL );
	void UpdateAllCharts( void);

protected:
	CFolder 			m_cRoot;
	DWORD				m_dwSystem;		// the system id (usually 1?)
	CObArray			m_cOpcodeQueue;
	int					m_nUndoLocation;
	DWORD				m_dwGenerator;	// the default generator
	TESTCAL				m_cCalib;		// the calibration curves for the system
	time_t				m_tLastSaveTime;	// when last autosaved

// Operations
public:
// -----------------------------------------------------------------------
						// tree operations
	CNamed 			*GetByID( DWORD dwID);
	CFolder 		*GetRoot()						{ return &m_cRoot;	}
	CFolder			*GetSystem()					{ return (CFolder *)m_cRoot.GetItem( m_dwSystem); }

	void 			OpenResource( CNamed *cSource);
	void			ExportResource( CNamed *pName);
	CString			GetFullTextName( CNamed *pTarget);
// -----------------------------------------------------------------------
						// document global stuff
	TESTCAL			*GetCalib(void )							{ return &m_cCalib; }
	CDataSet		*GetMicResponse( void);
	CDataSet		*GetAmpResponse( void);
	void			SetCalib( TESTCAL *pCalib)					{ m_cCalib = *pCalib; }

	CNamed			*GetDefaultGenerator(void);			// return the default generator
	int				QueryAutoSave( void);				// do an autosave if it's time

// -----------------------------------------------------------------------
	void			InsertNewObject(CFolder *pParent, CNamed *pNew);
								// undo/redo queue operations
	CObArray&		GetOpcodeQueue()		{ return m_cOpcodeQueue; }
	void			AddOpcode(COpCode *cNew);
	COpCode			*GetCurrentUndo();
	COpCode			*GetCurrentRedo();
	void			PerformUndo( void);
	void			PerformRedo( void);
// -----------------------------------------------------------------------
								// Attributes
	DWORD			GetSize( void);		// size of the document
	CAudtestView	*FindItemView(DWORD dwID);	// find a view by item
	void			DeleteTheTemps( void);		// delete the temporary items
								// Methods
						//create a new chart in the tree near pparent using name szname with the list of ids
	CNamed			*BuildBaseChart(CNamed *pParent, LPCSTR szName, CDWordArray &cdwIDs);

// -----------------------------------------------------------------------

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudtestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	//}}AFX_VIRTUAL

// Implementation
public:
	void RemoveItemView( DWORD dwID);
	int GetObjectCount( NAMETYPES nType);
	virtual ~CAudtestDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAudtestDoc)
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnResourceNewChart();
	afx_msg void OnResourceNewDriver();
	afx_msg void OnResourceNewEnclosure();
	afx_msg void OnResourceNewFolder();
	afx_msg void OnResourceNewNetwork();
	afx_msg void OnResourceNewSignal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CAudtestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#define CAUDTEDOC
#endif

