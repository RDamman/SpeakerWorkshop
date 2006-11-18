// Complex.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef COPCODE

// standard transformation. same as base class
class COpCode : public CObject				// not serializable
{
protected:

					// ----------------attributes
protected:
	CAudtestDoc		*m_cDocument;				// the root object for the tree we're changing
	DWORD			m_dwTarget;					// the target object

public:
	void 		SetDocument(CDocument *cNew)	{ m_cDocument = (CAudtestDoc *)cNew; }
	CDocument *	GetDocument(void ) const		{ return (CDocument *)m_cDocument; }
	void 		SetTarget( DWORD dwNew)			{ m_dwTarget = dwNew; }
	DWORD 		GetTarget(void ) const			{ return m_dwTarget; }

protected:

					// ---------------- operations
public:
	CObject 	   *FindTargetObject(void) const;	// find the target object
	int				QueueAndDo(void );
	virtual int		GetUndoName(CString *csDest);			// get the name of the undo

	virtual UINT	GetNameID(void );
	virtual int		DoUndo(void );					// perform an undo
	virtual int		DoExe( bool bRedo = true);		// execute the operation
	virtual int		DoRedo( void);					// redo the operation

					// ---------------- operators
	const COpCode& operator= (const COpCode& cIn);

					// ----------------implementation
public:
	COpCode( CDocument *cDoc, DWORD dwTarget);
	COpCode( CObject *cTarget);
	~COpCode();

};


// this performs multiple opcodes
class COpMulti : public COpCode
{
 				// attributes
protected:
		CObArray	m_cOpQueue;							// our own op queue
		COpCode		*m_pLastObj;						// so getfound will work, save last one for a bit
public:													// these are used to do the copcode stuff
														// by private callers
		int		PrivateQueue( COpCode *coNew);			// queue and do our own operation
		int		UndoQueue( void);						// undo the queue
		int		ExeQueue( void);						// exe the queue
		int		RedoQueue( void);						// redo the queue
														// the standard stuff
		virtual int		DoUndo(void );					// perform an undo
		virtual int		DoExe( bool bRedo = true);		// execute the operation
		virtual int		DoRedo( void);					// redo the operation

public:
	COpMulti( CDocument *cDoc, DWORD dwTarget);
	COpMulti( CObject *cTarget);
	~COpMulti();
};


class COpCustom : public COpMulti
{
private:
		UINT			m_nNameID;							// the name of the custom operation
public:													// these are used to do the copcode stuff
		virtual int DoExe( bool )						{ return 0; }		// do nothing
		virtual UINT GetNameID( void )					{ return m_nNameID; }
		virtual	int SetNameID( UINT uNew)				{ m_nNameID = uNew; return 0; }
public:
	COpCustom( CDocument *cDoc, DWORD dwTarget);
	COpCustom( CObject *cTarget);
	~COpCustom();
};

#define COPCODE

#endif
