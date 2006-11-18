// speaker.cpp : implementation of the CNetworkArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include "audtedoc.h"

#include "Network.h"

#include "NetClip.h"

#include "AfxPriv.h"

#include "passive.h"
#include "Folder.h"

#include "opItem.h"
#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CNetwork COpCode operations
/////////////////////////////////////////////////////////////////////////////
static UINT ui_NetClipFormat = 0;		// will be our clip format

// ///////////////////////////////////////////////////////
//				Opcode Stuff
// ///////////////////////////////////////////////////////

static UINT get_Format()
{
 	if ( ui_NetClipFormat)
		return ui_NetClipFormat;

	ui_NetClipFormat = ::RegisterClipboardFormat("Speaker Workshop Network");

	return ui_NetClipFormat;
}

UINT COpNetClipPaste::GetFormat()
{
	return get_Format();
}


static int copy_Object( CNetwork *cNet, CDocument *pDoc)
{
CObArray cSource;
HGLOBAL hMemPrivate;
HENHMETAFILE hmf;

	{				// -- build the private data format
	CSharedFile mf (GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);
	CArchive ar(&mf, CArchive::store);

		ar.m_pDocument = pDoc;
		ar << (DWORD )cNet->GetType();		// network
		cNet->Serialize( ar);
	    ar.Close(); // Flush and close.
	    hMemPrivate = mf.Detach();
	    if (!hMemPrivate) return 1;
	}
					// -- build the metafile
	{
	CRect rcdraw( 0,0,20000,20000);					// 8" square
	char csname[150] = "SpkrWork\0Metafile\0\0";
	HDC hdcMeta = CreateEnhMetaFile ((HDC )NULL, NULL, (LPCRECT )rcdraw, csname) ;			// build a memory metafile
	CDC *pdc = CDC::FromHandle( hdcMeta);
 
	pdc->SetWindowExt (2000,2000) ;
	pdc->SetWindowOrg (0,0) ;

	rcdraw.SetRect( 0,0,2000,2000);

	cNet->DoDraw( pdc, rcdraw);

	hmf = CloseEnhMetaFile (hdcMeta) ;
	}

    if ( ::OpenClipboard( NULL))
		{
	    ::EmptyClipboard();
	    ::SetClipboardData( get_Format(), hMemPrivate);
		::SetClipboardData( CF_ENHMETAFILE	, hmf); 
	    ::CloseClipboard();
		return 0;
		}
	else 
		{
		::GlobalFree( hMemPrivate);
		::DeleteEnhMetaFile( hmf);
		}

	return 1;
}

// ///////////////////////////////////////////////////////
//				Opcode Copy
// ///////////////////////////////////////////////////////

COpNetClipboard::COpNetClipboard( CNamed *cTarget) : COpCode( cTarget)
{
	m_cOldObject = NULL;
}

COpNetClipboard::~COpNetClipboard()
{
	if ( m_cOldObject)
		delete m_cOldObject;
}


int COpNetClipboard::DoUndo( void)
{

	if ( ! m_cOldObject)
		return 3;					// nothing to undo???

CNetwork *ctarg = (CNetwork *)FindTargetObject();

CNetwork *cnew = (CNetwork *)ctarg->Duplicate();		// save the data

	*ctarg = *m_cOldObject;
	*m_cOldObject = *cnew;
	delete cnew;					// now coldobject is the redo...

	ctarg->UpdateViews();

	return 0;
}

int COpNetClipboard::DoRedo( void)
{

	return DoUndo();			// switch them back

}

					// ---------------- operators
const COpCode& COpNetClipboard::operator= (const COpCode& cIn)
{
	COpCode::operator=(cIn);
	m_cOldObject = ((COpNetClipboard &)cIn).m_cOldObject->Duplicate();

	return *this;
}


// ///////////////////////////////////////////////////////
//				Opcode Copy
// ///////////////////////////////////////////////////////

COpNetClipCopy::COpNetClipCopy( CNamed *cTarget) : COpNetClipboard( cTarget)
{
}

COpNetClipCopy::~COpNetClipCopy()
{
}


UINT COpNetClipCopy::GetNameID(void)
{
	return IDOP_COPY;
}

int COpNetClipCopy::DoExe( bool )
{
CNetwork *ctarg = (CNetwork *)FindTargetObject();
CObArray cdata;

	if ( ctarg)
		{
		CNetwork *cnew = (CNetwork *)ctarg->CreateSubCopy( TRUE, FALSE);
		copy_Object( cnew, m_cDocument);			// copy the network to the clipboard
		delete cnew;			// sigh
		}
	return 1;		// don't put it in the queue

}

// ///////////////////////////////////////////////////////
//				Opcode Delete
// ///////////////////////////////////////////////////////
COpNetClipDelete::COpNetClipDelete( CNamed *cTarget) : COpNetClipboard( cTarget)
{
}

COpNetClipDelete::~COpNetClipDelete()
{
}


UINT COpNetClipDelete::GetNameID(void)
{
	return IDOP_DELETE;
}

int COpNetClipDelete::DoExe( bool )
{
CNetwork *ctarg = (CNetwork *)FindTargetObject();
CNetwork *cclip;

	if ( ! ctarg)
		return 1;

	m_cOldObject = ctarg->Duplicate();	// save the old guy

	cclip = (CNetwork *)ctarg->CreateSubCopy( FALSE, TRUE);		// get the remainder
	*ctarg = *cclip;			// copy it over to the old document
	delete cclip;				// don't need this anymore

	ctarg->UpdateViews();

	return 0;
}

// ///////////////////////////////////////////////////////
//				Opcode Cut
// ///////////////////////////////////////////////////////
COpNetClipCut::COpNetClipCut( CNamed *cTarget) : COpNetClipboard( cTarget)
{
}

COpNetClipCut::~COpNetClipCut()
{
}


UINT COpNetClipCut::GetNameID(void)
{
	return IDOP_CUT;
}

int COpNetClipCut::DoExe( bool )
{
CNetwork *ctarg = (CNetwork *)FindTargetObject();
CNetwork *cclip;

	if ( ! ctarg)
		return 1;

	m_cOldObject = ctarg->Duplicate();	// save the old guy

	cclip = (CNetwork *)ctarg->CreateSubCopy( TRUE, FALSE);
	copy_Object( cclip, m_cDocument);		// put it on the clipboard
	delete cclip;

	cclip = (CNetwork *)ctarg->CreateSubCopy( FALSE, TRUE);		// get the remainder
	*ctarg = *cclip;			// copy it over to the old document
	delete cclip;				// don't need this anymore

	ctarg->UpdateViews();

	return 0;
}

// ///////////////////////////////////////////////////////
//				Opcode Paste
// ///////////////////////////////////////////////////////
COpNetClipPaste::COpNetClipPaste( CNamed *cTarget) : COpNetClipboard( cTarget)
{
}

COpNetClipPaste::~COpNetClipPaste()
{
}


UINT COpNetClipPaste::GetNameID(void)
{
	return IDOP_PASTE;
}

int COpNetClipPaste::DoExe( bool )
{
CNetwork *cnew = NULL;
CNetwork *ctarg = (CNetwork *)FindTargetObject();
DWORD dwnew;

	if ( !ctarg)
		return 2;

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

	ar.m_pDocument = m_cDocument;
	ar >> dwnew;			// get the type (stored as a dword)
	if ( ctarg->GetType() == (NAMETYPES )dwnew)
		{
		cnew = new CNetwork();
		cnew->Serialize( ar);
		}
    ar.Close();
    mf.Detach();
    CloseClipboard();

	if ( cnew)
		{
		m_cOldObject = ctarg->Duplicate();
		ctarg->AppendNet( cnew);
		delete cnew;
		}

	ctarg->UpdateViews();

	return 0;

}


/////////////////////////////////////////////////////////////////////////////
//			GetHighlighted - get the first highlighted object
/////////////////////////////////////////////////////////////////////////////
int CNetwork::CutObjects( BOOL bOnlyHighlight)
{
COpCode *cop;

	cop = new COpNetClipCut( this);
	return cop->QueueAndDo();
}


/////////////////////////////////////////////////////////////////////////////
//			GetHighlighted - get the first highlighted object
/////////////////////////////////////////////////////////////////////////////
int CNetwork::PasteObjects( void)
{
COpCode *cop;

	cop = new COpNetClipPaste( this);
	return cop->QueueAndDo();
}


/////////////////////////////////////////////////////////////////////////////
//			CopyObjects - copy all of the highlighted objects to the clipboard
/////////////////////////////////////////////////////////////////////////////
int CNetwork::CopyObjects( BOOL bOnlyHighlight)
{
COpCode *cop;

	cop = new COpNetClipCopy( this);
	return cop->QueueAndDo();
}


/////////////////////////////////////////////////////////////////////////////
//			GetHighlighted - get the first highlighted object
/////////////////////////////////////////////////////////////////////////////
int CNetwork::DeleteObjects( BOOL bOnlyHighlight)
{
COpCode *cop;

	cop = new COpNetClipDelete( this);
	return cop->QueueAndDo();

}


