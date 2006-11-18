// Complex.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CNETCLIPBD

					// generic operations for any named object
class COpNetClipboard : public COpCode
{
protected:
	CNamed    		*m_cOldObject;
public:
	virtual int		DoUndo(void );					// perform an undo
	virtual int		DoRedo( void);					// redo the operation
					// ---------------- operators
	const COpCode& operator= (const COpCode& cIn);
public:
	COpNetClipboard(CNamed *cTarget);
	~COpNetClipboard();

};

class COpNetClipCut : public COpNetClipboard
{
public:
	virtual UINT	GetNameID(void );
	virtual int		DoExe( bool bRedo = true);		// execute the operation
public:
	COpNetClipCut(CNamed *cTarget);
	~COpNetClipCut();

};

					// generic operations for any named object
class COpNetClipDelete : public COpNetClipboard
{
public:
	virtual UINT	GetNameID(void );
	virtual int		DoExe( bool bRedo = true);		// execute the operation
public:
	COpNetClipDelete(CNamed *cTarget);
	~COpNetClipDelete();

};

class COpNetClipCopy : public COpNetClipboard
{
public:
	virtual UINT	GetNameID(void );
	virtual int		DoExe( bool bRedo = true);		// execute the operation
									// implementation
public:
	COpNetClipCopy(CNamed *cTarget);
	~COpNetClipCopy();

};

class COpNetClipPaste : public COpNetClipboard
{
public:
	virtual UINT	GetNameID(void );
	virtual int		DoExe( bool bRedo = true);		// execute the operation
						// return the clipboard format number
	static  UINT    GetFormat(void );
public:
	COpNetClipPaste(CNamed *cTarget);
	~COpNetClipPaste();

};


#define CNETCLIPBD

#endif

