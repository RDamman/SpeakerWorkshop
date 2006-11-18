// Complex.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef COPITEM

#include "OpCode.h"


					// generic operations for any named object
class COpRename : public COpCode
{
private:
		CString		m_csOldName;
		CString		m_csNewName;
public:
	virtual UINT	GetNameID(void );
	virtual int		DoUndo(void );					// perform an undo
	virtual int		DoExe( bool bRedo = true);		// execute the operation
	virtual int		DoRedo( void);					// redo the operation
public:
	COpRename(CNamed *cTarget, LPCSTR lpszNewName);
	~COpRename();

};

class COpDelete : public COpCode
{
private:
		CNamed    * m_cOldObject;
		DWORD		m_dwParent;		// parent object
									// operations
public:
	virtual UINT	GetNameID(void );
	virtual int		DoUndo(void );					// perform an undo
	virtual int		DoExe( bool bRedo = true);		// execute the operation
	virtual int		DoRedo( void);					// redo the operation

									// implementation
public:
	COpDelete(CNamed *cTarget);
	~COpDelete();

};

class COpSwapTemp : public COpCode
{
private:
	bool		m_bWasTemp;		// was it temporary?
									// operations
public:
	virtual UINT	GetNameID(void );
	virtual int		DoUndo(void );					// perform an undo
	virtual int		DoExe( bool bRedo = true);		// execute the operation
	virtual int		DoRedo( void);					// redo the operation

									// implementation
public:
	COpSwapTemp(CNamed *cTarget);
	~COpSwapTemp();

};

class COpInsert : public COpCode
{
private:
		CNamed    * m_cOldObject;
		DWORD		m_dwID;
									// operations
public:
	virtual UINT	GetNameID(void );
	virtual int		DoUndo(void );					// perform an undo
	virtual int		DoExe( bool bRedo = true);		// execute the operation
	virtual int		DoRedo( void);					// redo the operation

									// implementation
public:
	COpInsert(CNamed *cTarget, CNamed *cNewObject);
	~COpInsert();

};

class COpChange : public COpCode
{
private:
		CNamed    * m_cOldObject;
		CNamed    * m_cNewObject;
		bool		m_bSwapped;		// were they swapped already?
public:
	virtual UINT	GetNameID(void );
	virtual int		DoUndo(void );					// perform an undo
	virtual int		DoExe( bool bRedo = true);				// execute the operation
	virtual int		DoRedo( void);					// redo the operation
	CNamed *		GetTreedObject( void);			// the object in the tree at this point
public:
	COpChange(CNamed *cTarget, CNamed *cNew);
	~COpChange();

};

					// make the trails (do renames and deletes)
class COpNameTrails : public COpCode
{
private:
		bool		m_bSwapped;		// were they swapped already?
		bool		m_bEndOfTrail;	// we have as many as we need, keep the last to delete
		CString		m_csName;
		CNamed    * m_cOldObject;
		CNamed    * m_cNewObject;
		CDWordArray	m_dwIDs;		// the list of ids
		DWORD		m_dwNewID;		// id of the new object

public:
	virtual int		DoUndo(void );					// perform an undo
	virtual int		DoExe( bool bRedo = true);				// execute the operation
	virtual int		DoRedo( void);					// redo the operation
	CNamed *		GetTreedObject( void);			// the object in the tree at this point
public:
	COpNameTrails(CNamed *cTarget, CNamed *pNew);
	~COpNameTrails();

};


class COpCheckpoint : public COpCode
{
private:
		CNamed    * m_cOldObject;
public:
	virtual UINT	GetNameID(void );
	virtual int		DoUndo(void );					// perform an undo
	virtual int		DoExe( bool bRedo = true);		// execute the operation
	virtual int		DoRedo( void);					// redo the operation
public:
	COpCheckpoint(CNamed *cTarget);
	~COpCheckpoint();

};


class COpFindOrCreate : public COpMulti
{
private:
		CString		m_csName;
		NAMETYPES	m_ntType;
		DWORD		m_dwFound;
public:
	virtual int		DoExe( bool bRedo = true);	// execute the operation
		CNamed		*GetFound();				// who did you find/build?
public:
	COpFindOrCreate(CNamed *cTarget, LPCSTR lpszNewName, NAMETYPES ntNewType);
	~COpFindOrCreate();

};


class COpMakeChart : public COpCustom
{
public:
	COpMakeChart( CDocument *cDoc, DWORD dwTarget);
	COpMakeChart( CObject *cTarget);
	~COpMakeChart();
public:
	virtual int		DoExe( bool bRedo = true);	// execute the operation
	CChart			*GetChart()		{ return m_pChart; }
private:
	CChart		*m_pChart;						// the chart we built
};

typedef struct	tagSWaterfall
	{
	float	fStart;
	float	fEnd;
	float	fTotalTime;
	float	fSmooth;		// smoothing
	int		iSamples;
	int		iWindow;
	int		iStyle;
	DWORD	dwSource;
	DWORD	dwReference;
	}	SWATERFALL;


class COpWaterfall : public COpCustom
{
public:
	COpWaterfall( CDocument *cDoc, DWORD dwTarget);
	COpWaterfall( CObject *cTarget);
	~COpWaterfall();
public:
	virtual int		DoExe( bool bRedo = true);	// execute the operation
	SWATERFALL		&GetStruct( void)					{ return m_sWater; }
	void			SetStruct( SWATERFALL *pWater)		{ m_sWater = *pWater; }
private:
	SWATERFALL		m_sWater;						// the waterfall data

};




#define COPITEM

#endif
