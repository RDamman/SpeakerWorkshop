// Complex.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CLIPBD


					// generic operations for any named object
class COpClipCut : public COpCode
{
private:
		CNamed    * m_cOldObject;
		DWORD		m_dwParent;		// parent object
public:
	virtual UINT	GetNameID(void );
	virtual int		DoUndo(void );					// perform an undo
	virtual int		DoExe( bool bRedo = true);		// execute the operation
	virtual int		DoRedo( void);					// redo the operation
public:
	COpClipCut(CNamed *cTarget);
	~COpClipCut();

};

class COpClipCopy : public COpCode
{
private:
									// operations
public:
	virtual UINT	GetNameID(void );
	virtual int		DoUndo(void );					// perform an undo
	virtual int		DoExe( bool bRedo = true);		// execute the operation
	virtual int		DoRedo( void);					// redo the operation

									// implementation
public:
	COpClipCopy(CNamed *cTarget);
	~COpClipCopy();

};

class COpClipPaste : public COpCode
{
private:
	DWORD		m_dwNewID;
	CNamed		*m_cPasted;		// during a redo cycle contains the pasted object
public:
	virtual UINT	GetNameID(void );
	virtual int		DoUndo(void );					// perform an undo
	virtual int		DoExe( bool bRedo = true);		// execute the operation
	virtual int		DoRedo( void);					// redo the operation
						// return the clipboard format number
	static  UINT    GetFormat(void );
public:
	COpClipPaste(CNamed *cTarget);
	~COpClipPaste();

};



#define CLIPBD

#endif
