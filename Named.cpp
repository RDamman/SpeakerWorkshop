// speaker.cpp : implementation of the CNamedArray classes
//


#include "stdafx.h"
#include "audtest.h"

//#include "named.h"

#include "opcode.h"

#include "audtedoc.h"
#include "folder.h"
#include "generat.h"
#include "dataset.h"
#include "chart.h"
#include "enclosur.h"
#include "network.h"
#include "Room.h"
#include "Driver.h"

#include "utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNamedArray

IMPLEMENT_SERIAL(CNamedArray, CObArray, VERSIONABLE_SCHEMA | 300)


/////////////////////////////////////////////////////////////////////////////
// CNamedArray construction/destruction

CNamedArray::CNamedArray()
{
	// TODO: add one-time construction code here

}

CNamedArray::~CNamedArray()
{
}

#if 0
CNamedArray &CNamedArray::operator=(CNamedArray &cIn)
{
int i,nmax;

	DeleteEntire();			// get rid of current contents
	
	nmax = cIn.GetSize();
	for ( i=0; i < nmax; i++)
		{
		Add( cIn.GetNamedAt(i)->Duplicate());
		}
		
	return *this;
}
#endif

void CNamedArray::Serialize(CArchive& ar)
{

		CObArray::Serialize( ar);

}


/////////////////////////////////////////////////////////////////////////////
// CNamedArray diagnostics

#ifdef _DEBUG
void CNamedArray::AssertValid() const
{
	CObject::AssertValid();
}

void CNamedArray::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNamedArray commands

void CNamedArray::DeleteEntire()
{

	::KillArray( this);

}


void CNamedArray::FillList( CListBox &cList)
{
int i,nmax;
int npos;
							// these are all inherited from CObArray
	if ( GetSize())
		{
		nmax = GetSize();
		for ( i=0; i<nmax; i++)
			{
			npos = cList.AddString( GetNamedAt( i)->GetName());
			cList.SetItemData( npos, i);
			}
		}

}


CNamed *CNamedArray::GetNamedAt( int i)
{
	return ( (CNamed *)GetAt(i));
}


																									  // speaker.cpp : implementation of the CNamed classes
//

/////////////////////////////////////////////////////////////////////////////
// CNamed

IMPLEMENT_SERIAL(CNamed, CObject, VERSIONABLE_SCHEMA | 220)
IMPLEMENT_SERIAL(CGraphed, CNamed, VERSIONABLE_SCHEMA | 230)


static DWORD dw_IDs = 0;

// -----------------------------------------------------------------------
//		GetNextID
//			Get the next available id and increment
// -----------------------------------------------------------------------
DWORD CNamed::GetNextID( void)
{
	return ++dw_IDs;
}


/////////////////////////////////////////////////////////////////////////////
// CNamed construction/destruction

CNamed::CNamed() : m_szName(cNullString), m_szDescription(cNullString)
{
	// TODO: add one-time construction code here
	m_dwID = GetNextID();
	m_dwAttributes = 0;		// not read-only, not system
	m_cRoot = NULL;
	time( &m_tCreated);
	m_tLastEdit = m_tCreated;
#if _DEBUG
	{
	SetDescription( CString( cNullString));
	}
#endif


	if ( ! m_dwID)
		m_dwID++;

}

CNamed::~CNamed()
{
}

void CNamed::CheckID(DWORD dwNew)
{
  if ( dwNew > dw_IDs)
  	dw_IDs = 1 + dwNew;
}


CNamed *CNamed::Duplicate(void )
{
	ASSERT( 0);
	return NULL;
}


				// operators
CNamed &CNamed::operator=(const CNamed &cIn)
{
	ASSERT ( GetType() == cIn.GetType() );
 	m_szName = cIn.m_szName;
	SetDescription( cIn.m_szDescription);
	m_cRoot = cIn.m_cRoot;			// use the same parent for now
	m_tCreated = cIn.m_tCreated;
	m_tLastEdit = cIn.m_tLastEdit;
	m_dwAttributes = cIn.m_dwAttributes;
 					// don't copy the id # or date
 	return *this;
}

CDocument *CNamed::GetDocument( void)
{
CFolder *croot = (CFolder *)m_cRoot;

	if ( croot && croot != this)		// should be calling someone else!
		return croot->GetDocument();

	{
	CString csz;
	csz.Format("Invalid Named Object Reference: %s", GetName());
	AfxMessageBox(csz);
	}

	return NULL;
}

CString CNamed::GetFullName()
{
CString cout;
CFolder *croot = (CFolder *)m_cRoot;

	if ( ! m_cRoot)
		return m_szName;

	if ( ! GetID())				// we're a root...!
		return m_szName;

	if ( ! CAudtestApp::GetShowPath())
		return m_szName;		// user wants short names

	cout = m_szName;

CNamed *cnam;

	cnam = croot->GetParent( GetID());		// get my parent
	while( cnam && cnam->GetID())
		{
		cout = cnam->GetName() + "\\" + cout;
		cnam = croot->GetParent( cnam->GetID());
		}

	return cout;

}




/////////////////////////////////////////////////////////////////////////////
// CNamed serialization

void CNamed::Serialize(CArchive& ar)
{

	if ( ! ar.IsStoring())
		m_nSchema = ar.GetObjectSchema();

	CObject::Serialize(ar);

	if (ar.IsStoring())
	{					// storing code here
		ar << m_szName;
#if _DEBUG
		{			// strip off the ID number
		int idx;
		CString strdesc;

			idx = m_szDescription.ReverseFind( '@');		// find the )
			if ( idx > 0)
			{
			strdesc = m_szDescription.Right( m_szDescription.GetLength() - idx - 1);
			ar << strdesc;
			}
			else
				ar << m_szDescription;
		}
#else
		ar << m_szDescription;
#endif
		ar << m_dwID;
		ar << m_tCreated;			// date and time created
		ar << m_tLastEdit;			// date and time of last edit
		ar << m_dwAttributes;
	}
	else
	{					// loading code here 
		ar >> m_szName;
		ar >> m_szDescription;
		ar >> m_dwID;
		ar >> m_tCreated;			// date and time created
		ar >> m_tLastEdit;			// date and time of last edit
		ar >> m_dwAttributes;
		CheckID( m_dwID);			// make it unique
		if ( ar.m_pDocument)		// from file open or save
			{
			CAudtestDoc *pdoc = (CAudtestDoc *)(ar.m_pDocument);
			SetRootObject( pdoc->GetRoot());
			}
		{
		CString strdesc = m_szDescription;
			SetDescription( strdesc);		// add id if in debug mode
		}
	}
}

// ----------------------------------------------------------------------------

int	CNamed::Import( LPCSTR )								// import some data
{
	return 0;			// didn't do anything
}

int CNamed::Export( LPCSTR )								// export some data
{
	return 0;			// didn't do anything
}

void CNamed::GetFilter( CString&, CString& )
{
}


// ----------------------------------------------------------------------------

void CNamed::SetName( const CString &szIn)
{

 	m_szName = szIn;
}


void CNamed::SetDescription( const CString &szIn)
{
#if _DEBUG
	m_szDescription.Format("ID (%d) @", (int )GetID());
	m_szDescription += szIn;
#else
 	m_szDescription = szIn;
#endif
}


CNamed  *CNamed::FindByID( DWORD dwID)		// look through the tree for this one...
{
CFolder *pfold = (CFolder *)GetRootObject();

	ASSERT( pfold != NULL);

	return pfold->GetItem( dwID, TRUE);
}

// use this pointer with this id
bool	CNamed::SetPointerByID( CNamed *pNew)
{
CFolder *pfold = (CFolder *)GetRootObject();

	ASSERT( pfold != NULL);

	return pfold->ReplacePointer( pNew, GetID());
}


CFolder  *CNamed::FindParent( void)		// look through the tree for this one...
{
CFolder *proot = (CFolder *)GetRootObject();

	ASSERT( proot != NULL);

	return proot->GetParent( m_dwID);
}


CNamed  *CNamed::FindByName( LPCSTR lpszName, BOOL bAll)		// look through the tree for this one...
{
CFolder *pfold = (CFolder *)GetRootObject();
CFolder *pparent;

	ASSERT( pfold != NULL);

	if ( bAll)
		return pfold->GetItemByName( lpszName, TRUE);

	if ( ntFolder == GetType())								// i'm a folder
		pparent = (CFolder *)this;
	else
		pparent = pfold->GetParent( GetID());					// get my parent

	return pparent->GetItemByName( lpszName, FALSE);
}

CNamed  *CNamed::CreateByName( LPCSTR lpszName, NAMETYPES nType)		// look through the tree for this one...
{
CNamed *cnam;
CFolder *cparent;

	if ( ntFolder != GetType() )
		{
		cparent = (CFolder *)GetRootObject();
		cparent = cparent->GetParent( GetID() );
		}
	else
		cparent = (CFolder *)this;

	cnam = cparent->GetItemByName( lpszName, FALSE);		// don't look through subdirectories

	if( cnam && nType == cnam->GetType())
		return cnam;
					// we need to build one
	switch( nType)
		{
		case ntGenerator : 
			cnam = new CGenerator();
			break;
		case ntDataSet : 
			cnam = new CDataSet();
			break;
		case ntChart : 
			cnam = new CChart();
			break;
		case ntEnclosure : 
			cnam = new CEnclosure();
			break;
		case ntNetwork : 
			cnam = new CNetwork();
			break;
		case ntRoom : 
			cnam = new CRoom();
			break;
		case ntFolder : 
			cnam = new CFolder();
			break;
		case ntDriver : 
			cnam = new CDriver();
			break;
		default:
			ASSERT(0);			// shouldn't be here...
			break;
		}

	cnam->SetName( lpszName);

	cparent->AddItem( cnam);

	return cnam;
}



void CNamed::DialogInit( CDialog *)			// initialize the dialog (callback when windows are built)
{

}


#if 0
BOOL CNamed::GetHighlight()
{
	return m_bHighlight;
	
}

void CNamed::SetHighlight( BOOL bHighlight)
{

 	m_bHighlight = bHighlight;
}
#endif

CDialog *CNamed::GetDialog()		// get the properties dialog
{
	ASSERT(0);				// this should never be called!
	return NULL;
}

NAMETYPES CNamed::GetType(void) const
{
	ASSERT(0);				// this should never be called!
	return (NAMETYPES )0;

}

int   CNamed::EditProperties(CWnd *, CObject *)	// bring up properties dbox
{
	ASSERT(0);				// this should never be called!
	return (0);

}

void CNamed::SetLastEdit( void)
{
	m_tLastEdit = time( &m_tLastEdit);
	if ( m_cRoot && (this != m_cRoot))		// if we're not the root, set the root time
		m_cRoot->SetLastEdit();
}

void	CNamed::SetDateStrings( CString& csCreated, CString &csLastEdit)
{
//	CString csfmt = "%A, %B %d, %Y at %H:%M";
CString csfmt = "%#c";
// CString csfmt = "%#x %#I:%M %p";

	{
	CTime ct( GetCreated());

		csCreated = ct.Format( csfmt);
	}

	{
	CTime ct( GetLastEdit());

		csLastEdit = ct.Format( csfmt);
	}

}


void CNamed::UpdateViews(void)
{
CFolder *croot = (CFolder *)GetRootObject();

	if ( croot)			// we have a root for this guy
		{
		CAudtestDoc *cdoc = (CAudtestDoc *)croot->GetDocument();

		if ( cdoc)			// and we have a document
			cdoc->UpdateAll( NULL, GetID());
		}

}




/////////////////////////////////////////////////////////////////////////////
// CNamed diagnostics

#ifdef _DEBUG
void CNamed::AssertValid() const
{
	CObject::AssertValid();
}

void CNamed::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}

#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
// CGraphed construction/destruction

CGraphed::CGraphed() : CNamed()
{

	m_cChart = NULL;
}

CGraphed::~CGraphed()
{
	if ( m_cChart)
		delete m_cChart;
}

CNamed *CGraphed::Duplicate(void )
{
	ASSERT( 0);
	return NULL;
}


				// operators
CGraphed &CGraphed::operator=(const CGraphed &cIn)
{
CNamed &cin = (CNamed &)cIn;

	*this = cin;
 	return *this;
}



CNamed &CGraphed::operator=(const CNamed &cIn)
{
CGraphed &cin = (CGraphed &)cIn;

	CNamed::operator=( cIn);

	if ( cin.m_cChart)
		SetChart( cin.m_cChart);
	else
		SetChart( NULL);
 					// don't copy the id #
 	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// CGraphed diagnostics

#ifdef _DEBUG
void CGraphed::AssertValid() const
{
	CObject::AssertValid();
}

void CGraphed::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}

#endif //_DEBUG



void CGraphed::Serialize(CArchive& ar)
{

	CNamed::Serialize(ar);

	if (ar.IsStoring())
	{					// storing code here
	}
	else
	{					// loading code here 
	}

}

BOOL CGraphed::CreateChart(CNamed *)
{
	ASSERT(0);
	return FALSE;			// failed
}

void CGraphed::SetChart( CSubChart *cNew)
{
	if ( ! cNew)			// remove existing chart definition
		{
		if ( m_cChart)
			delete m_cChart;
		m_cChart = NULL;
		return;				// that's all
		}

	if (! m_cChart) 
		m_cChart = (CSubChart *)(cNew->Duplicate());
	else
		*m_cChart = *cNew;
}



BOOL CNamed::IsType( NAMETYPES ntType, UNITMSR nUom)
{
	if ( ntType == ntDataSet)
		{
		if (ntDataSet != GetType())
			return FALSE;
		else if ( nUom == uomAny)
			return TRUE;
		else
			return nUom == ((CDataSet *)this)->GetUOM();
		}
	else
		return ntType == GetType();
}

bool CNamed::IsReadOnly( void)
{
	return (0 != (m_dwAttributes & ATTRIB_READONLY));
}

bool CNamed::IsSystem( void)
{
	return (0 != (m_dwAttributes & ATTRIB_SYSTEM));

}

bool CNamed::IsTemporary( void)
{
	return (0 != (m_dwAttributes & ATTRIB_TEMPORARY));
}

void CNamed::SetTemporary( bool bNew)
{
	if ( bNew)
		m_dwAttributes |= ATTRIB_TEMPORARY;
	else
		(m_dwAttributes &= ~ATTRIB_TEMPORARY);
}


DWORD CNamed::GetObjectSize( BOOL )
{
	return (DWORD )(GetRuntimeClass()->m_nObjectSize );

}
