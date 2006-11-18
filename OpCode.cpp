// speaker.cpp : implementation of the CDataSetArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include "OpCode.h"

#include "audtedoc.h"

#include "utils.h"

#include "math.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//				COpCode
/////////////////////////////////////////////////////////////////////////////

COpCode::COpCode( CObject *cTarget)
{
CNamed *ctarg = (CNamed *)cTarget;;

	SetDocument( ((CFolder *)ctarg->GetRootObject())->GetDocument() );
	m_dwTarget = ctarg->GetID();
}


COpCode::COpCode( CDocument *cDoc, DWORD dwTarget)
{
	SetDocument( cDoc);
	m_dwTarget = dwTarget;

}

COpCode::~COpCode()
{
}


/////////////////////////////////////////////////////////////////////////////
//				COpCode Operations
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//				COpCode Operators
/////////////////////////////////////////////////////////////////////////////

// -------------------------- assignment
const COpCode& COpCode::operator=(const COpCode& )
{

	ASSERT(0);

	return *this;
}


CObject *COpCode::FindTargetObject(void ) const					// perform an undo
{
CObject *ctarget;
CAudtestDoc *ndoc = (CAudtestDoc *)m_cDocument;

	ctarget = ndoc->GetByID( m_dwTarget);

	return ctarget;

}

int COpCode::QueueAndDo( void)
{
CAudtestDoc *pdoc = (CAudtestDoc *)m_cDocument;
int nout = 3;							// no document!

	if ( pdoc)
		{
		nout = DoExe();					// execute it
		if ( !nout)						// it worked
			{
			pdoc->AddOpcode( this);		// add it to the queue
			pdoc->SetModifiedFlag( TRUE);
				{
				CObject *cob = FindTargetObject();
					if ( cob)
						{
						CNamed *cnam = (CNamed *)cob;
						cnam->SetLastEdit();
						if ( ntFolder != cnam->GetType())
							cnam->FindParent()->SetLastEdit();
						}
				}
			}
		}

	return nout;						// return the result

}


/////////////////////////////////////////////////////////////////////////////
// ---------------- virtual functions
/////////////////////////////////////////////////////////////////////////////


int		COpCode::DoUndo(void )					// perform an undo
{
	return 0;			// target not found
}


int COpCode::GetUndoName(CString *csDest )				// get the name of the undo
{
	if ( GetNameID())
		{
		csDest->LoadString( GetNameID());
		return 0;
		}

	return 1;
}

int		COpCode::DoExe( bool)					// execute the operation
{
	return 0;			// target not found
}


int		COpCode::DoRedo( void)					// redo the operation
{
	return 0;			// target not found
}


UINT COpCode::GetNameID(void)
{

	return IDOP_UNKNOWN;
}


/////////////////////////////////////////////////////////////////////////////
//			COpMulti
//						multiple operations
/////////////////////////////////////////////////////////////////////////////

COpMulti::COpMulti( CDocument *cDoc, DWORD dwTarget) : COpCode( cDoc, dwTarget), m_cOpQueue()
{
	m_cOpQueue.SetSize(0, 10);
	m_pLastObj = NULL;
}

COpMulti::COpMulti( CObject *cTarget) : COpCode( cTarget), m_cOpQueue()
{
	m_cOpQueue.SetSize(0, 10);
	m_pLastObj = NULL;
}

COpMulti::~COpMulti()
{
#if _DEBUG
// verify the array is valid and killable
	{
		int i;
		int nsize;
		CObject *pobj;

			nsize = m_cOpQueue.GetSize();
			for ( i=0; i<nsize; i++)
			{
				pobj = m_cOpQueue.GetAt( i);
				pobj->AssertValid();
			}
	}
#endif

	::KillArray( &m_cOpQueue);
	if ( m_pLastObj)
		delete m_pLastObj;
}


int	COpMulti::PrivateQueue( COpCode *coNew)			// queue and do our own operation
{
int nout;

	if ( m_pLastObj)		// are we saving one???
		{
		delete m_pLastObj;	// now get rid of it
		m_pLastObj = NULL;
		}
	nout = coNew->DoExe();
	if ( ! nout)			// no problem
		{
		m_cOpQueue.Add( coNew);
		}
	else
		{
		m_pLastObj = coNew;	// so it has some persistance
		}

	return nout;
}

int COpMulti::UndoQueue( void)
{
int nout = 0;
int i;

	if ( m_cOpQueue.GetSize())
		{
		for ( i= m_cOpQueue.GetSize()-1; i>=0; i--)
			{
			nout = ((COpCode *)m_cOpQueue.GetAt(i))->DoUndo();
			if ( nout)
				break;
			}
		}

	return nout;
}


int COpMulti::RedoQueue( void)
{
int nout = 0;
int i;


	if ( m_cOpQueue.GetSize())
		{
		for ( i= 0; i < m_cOpQueue.GetSize(); i++)
			{
			nout = ((COpCode *)m_cOpQueue.GetAt(i))->DoRedo();
			if ( nout)
				break;
			}
		}
	return nout;

}


int COpMulti::ExeQueue()
{
int nout = 0;
int i;

	if ( m_cOpQueue.GetSize())
		{
		for ( i= 0; i < m_cOpQueue.GetSize(); i++)
			{
			nout = ((COpCode *)m_cOpQueue.GetAt(i))->DoExe();
			if ( nout)
				break;
			}
		}
	return nout;

}

int COpMulti::DoUndo( void)
{
	return UndoQueue();
}

int COpMulti::DoExe( bool )
{
//	return ExeQueue();
	return 0;			// worked ok
}

int COpMulti::DoRedo( void)
{
	return RedoQueue();
}


/////////////////////////////////////////////////////////////////////////////
//			COpCustom
//						multiple operations with a custom name
/////////////////////////////////////////////////////////////////////////////

COpCustom::COpCustom( CDocument *cDoc, DWORD dwTarget) : COpMulti( cDoc, dwTarget)
{
}

COpCustom::COpCustom( CObject *cTarget) : COpMulti( cTarget)
{
}

COpCustom::~COpCustom()
{
}


