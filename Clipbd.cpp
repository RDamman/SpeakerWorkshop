// speaker.cpp : implementation of the CDataSetArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include "audtedoc.h"
//#include "folder.h"

//#include "opcode.h"

#include "ClipBd.h"

#include "utils.h"

#include "math.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include "AFXPRIV.H"

static UINT ui_ClipFormat = 0;		// will be our clip format

// ///////////////////////////////////////////////////////
//				Opcode Stuff
// ///////////////////////////////////////////////////////

static UINT get_Format()
{
 	if ( ui_ClipFormat)
		return ui_ClipFormat;

	ui_ClipFormat = RegisterClipboardFormat("Speaker Workshop Resource");

	return ui_ClipFormat;
}

UINT COpClipPaste::GetFormat()
{
	return get_Format();
}


static int copy_Object( CNamed *ctarg, CDocument *pDoc)
{
    CSharedFile mf (GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);
    CArchive ar(&mf, CArchive::store);
	ar.m_pDocument = pDoc;
	ar << (DWORD )ctarg->GetType();		// save the data type
	ar << ctarg;		// we must do this to maintain the schema
    ar.Close(); // Flush and close.
    HGLOBAL hMem = mf.Detach();
    if (!hMem) return 1;
    if ( ::OpenClipboard( NULL))
		{
	    ::EmptyClipboard();
	    ::SetClipboardData(get_Format(), hMem);
	    ::CloseClipboard();
		return 0;
		}
	else ::GlobalFree( hMem);

	return 1;
}

// ///////////////////////////////////////////////////////
//				Opcode Copy
// ///////////////////////////////////////////////////////

COpClipCopy::COpClipCopy( CNamed *cTarget) : COpCode( cTarget)
{

}

COpClipCopy::~COpClipCopy()
{

}


UINT COpClipCopy::GetNameID(void)
{
	return IDOP_COPY;
}

int COpClipCopy::DoUndo( void)
{
	return 0;
}

int COpClipCopy::DoExe( bool )
{
CNamed *ctarg = (CNamed *)FindTargetObject();

	if ( ctarg)
		{
		copy_Object( ctarg, m_cDocument);
		}
	return 1;		// don't put it in the queue

}

int COpClipCopy::DoRedo( void)
{
	return DoExe();			// do it again

}


// ///////////////////////////////////////////////////////
//				Opcode Cut
// ///////////////////////////////////////////////////////
COpClipCut::COpClipCut( CNamed *cTarget) : COpCode( cTarget)
{
	m_cOldObject = NULL;
	m_dwParent = 0;
}

COpClipCut::~COpClipCut()
{
	if ( m_cOldObject)
		delete m_cOldObject;
}


UINT COpClipCut::GetNameID(void)
{
	return IDOP_CUT;
}

int COpClipCut::DoUndo( void)
{

	if ( ! m_cOldObject)
		return 3;					// nothing to undo???

CAudtestDoc *pdoc = (CAudtestDoc *)m_cDocument;
CFolder *pparent;

	if ( ! pdoc)
		return 2;

	pparent = (CFolder *)pdoc->GetByID( m_dwParent);

	if ( pparent)
		{
		pparent->AddItem( m_cOldObject);
		m_cOldObject = NULL;
		}
	else
		return 1;

	m_cDocument->UpdateAll( NULL, GetTarget() );

	return 0;
}

int COpClipCut::DoExe( bool )
{
CNamed *ctarg = (CNamed *)FindTargetObject();
CAudtestDoc *pdoc = (CAudtestDoc *)m_cDocument;
CFolder *proot;

	if ( (! pdoc) || !ctarg)
		return 1;

	proot = pdoc->GetRoot();			// go straight to the source
	m_cOldObject = ctarg;					// save the old guy
	m_dwParent = proot->GetParent( ctarg->GetID() )->GetID();

	copy_Object( ctarg, m_cDocument);		// put it on the clipboard
											// now remove, don't delete it
	proot->RemoveItem( ctarg->GetID() );

	m_cDocument->UpdateAll( NULL, ctarg->GetID() );

	return 0;
}

int COpClipCut::DoRedo( void)
{

	return DoExe();

}


// ///////////////////////////////////////////////////////
//				Opcode Paste
// ///////////////////////////////////////////////////////
COpClipPaste::COpClipPaste( CNamed *cTarget) : COpCode( cTarget)
{
	m_dwNewID = 0;
	m_cPasted = NULL;		// during a redo cycle contains the pasted object
}

COpClipPaste::~COpClipPaste()
{
	if ( m_cPasted)
		delete m_cPasted;
}


UINT COpClipPaste::GetNameID(void)
{
	return IDOP_PASTE;
}

int COpClipPaste::DoUndo( void)
{
	if ( m_cPasted)
		return 1;

CAudtestDoc *pdoc = (CAudtestDoc *)m_cDocument;
CFolder *proot = pdoc->GetRoot();

	if ( pdoc->GetByID( m_dwNewID))
		{
		m_cPasted = pdoc->GetByID( m_dwNewID);		// get it then remove it
		proot->RemoveItem( m_dwNewID);
		m_cDocument->UpdateAll( NULL, m_dwNewID );
		return 0;
		}


	return 2;

}

int COpClipPaste::DoExe( bool )
{
CNamed *cnew;
CNamed *ctarg = (CNamed *)FindTargetObject();
CFolder *pparent;

	if ( ntFolder == ctarg->GetType() )
		pparent = (CFolder *)ctarg;
	else
		{
		pparent = ((CAudtestDoc *)m_cDocument)->GetRoot();
		pparent = pparent->GetParent( ctarg->GetID() );
		}

	if ( ! OpenClipboard( NULL))
		return 1;

    HGLOBAL hMem = ::GetClipboardData(get_Format() );
    if (!hMem)
    	{
        ::CloseClipboard();
        return 1;
    	}
    // Create a mem file.
    CSharedFile mf;
    mf.SetHandle(hMem);
							    // Create the archive and get the data.
    CArchive ar(&mf, CArchive::load);
	DWORD dwnew;

	ar.m_pDocument = m_cDocument;
	ar >> dwnew;			// get the type (stored as a dword)
	ar >> cnew;				// if we use serialize we don't get the schema!

		{
		CString cname = cnew->GetName();
		CString ctest = cname;
		char szout[20];
		int i;

			cnew->SetName("absolute gibberish");
			for ( i=1; pparent->FindByName( cname); i++)		// we have one!
				{
				sprintf(szout, ".%d", i);
				cname = ctest + szout;
				}
			cnew->SetName(cname);
		}
	cnew->SetID( cnew->GetNextID());			// !!! since it was serialized
    ar.Close();
    mf.Detach();
    CloseClipboard();

	pparent->AddItem( cnew);
	m_dwNewID = cnew->GetID();
	m_cDocument->UpdateAll( NULL, m_dwNewID );

	return 0;

}

int COpClipPaste::DoRedo( void)
{
DWORD dwid;
CAudtestDoc *pdoc = (CAudtestDoc *)m_cDocument;
CFolder *pparent = (CFolder *)FindTargetObject();

	if ( (! m_cPasted) || (! pdoc) || !pparent)
		return 3;					// nothing to undo???

	dwid = m_cPasted->GetID();

	pparent->AddItem( m_cPasted);
	m_cPasted = NULL;

	m_cDocument->UpdateAll( NULL, dwid );

	return 0;

}


