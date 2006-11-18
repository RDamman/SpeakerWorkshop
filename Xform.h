// Xform.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CXFORM

#include "Opcode.h"

// the base class for dataset transformation that are often dialog based

class CXcalc : public COpMulti
{
 				// attributes
protected:
		CNamed    * m_cOldObject;
		CNamed    * m_cNewObject;

public:
		virtual UINT DoDialog( void) = NULL;			// xeq dbox
		virtual UINT GetDialog( void) = NULL;		// get the dialog id
		virtual int  DoOperation( void) = NULL;		// do it
		virtual UINT	GetNameID(void );

public:													// these are used to do the copcode stuff
		virtual int		DoUndo(void );					// perform an undo
		virtual int		DoRedo(void );					// perform an undo
		virtual int		DoExe( bool bRedo = true);		// execute the operation

public:
		CXcalc( CObject *cTarget);		// must be named and in the tree
		~CXcalc();
};



// unary operations of the form X = f(X)
// where X is the target object
class CXunary : public CXcalc
{

public:
		CXunary( CObject *cTarget);		// must be named and in the tree
		~CXunary();
};


// binary operations of the form X = f(X, Y)
class CXbinary : public CXunary
{
private:
		CNamed *m_cOther;			// the other guy...
public:
		CNamed *GetOther(void) const		{ return m_cOther; }
		void	SetOther( CNamed *cOther)	{ m_cOther = cOther; }

public:
		CXbinary( CObject *cTarget, CObject *cOther);		// must be named and in the tree
		~CXbinary();
};


// operations of the form Z = f(X)
class CXtransform : public COpMulti
{
private:
		DWORD		m_dwDestination;
		CNamed		*m_pBase;			// the base object if different

public:
		CNamed 		*GetDestination( void);

public:
		virtual UINT 	GetSuffix(void )					{ return IDOP_UNKNOWN; }
		virtual int		DoExe( bool bRedo = true);
		virtual	int		DoOperation( CNamed *cdDest) = 0;
				void	SetBase( CNamed *pNew)	{ m_pBase = pNew; }

public:
		CXtransform( CObject *cTarget);		// the parent object
		~CXtransform();
};


// operations of the form Z = f(X, Y)
class CXtBinary : public CXtransform
{
private:
		CNamed *m_cOther;			// the second argument (only used on DoExe, hence stored as ptr)
public:
		virtual CNamed *GetOther( void)				{ return m_cOther; }
		virtual void   SetOther( CNamed *cNew)		{ m_cOther = cNew; }
public:
		CXtBinary( CObject *cTarget, CObject *cOther);		// the parent objects
		~CXtBinary();
};


// non-standard transformation
//	this has a list of datasets to be used for arithmetic purposes
class CXform : public CXcalc
{

	protected:
		CNamedArray m_cDatasets;	// the datasets we can use

	public:
		CNamed *GetAt(int i)			{ return m_cDatasets.GetNamedAt(i); }
		CNamedArray *Datasets(void)		{ return &m_cDatasets; }

	protected:
		CXform( CObject *cTarget);		// must be named and in the tree
		~CXform();
};


#define CXFORM

#endif
