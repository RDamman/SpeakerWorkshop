// speaker.cpp : implementation of the CFolderArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include "folder.h"

#include "DlgDoc.h"
#include "DlgFolder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CFolder

IMPLEMENT_SERIAL(CFolder, CNamed, VERSIONABLE_SCHEMA | 236)


/////////////////////////////////////////////////////////////////////////////
// CFolder construction/destruction

CFolder::CFolder() : m_coArray()
{
	// TODO: add one-time construction code here
	m_coArray.SetSize(0, 10);
	m_pcDoc = NULL;			// start with no doc pointer

}

CFolder::~CFolder()
{
	m_coArray.DeleteEntire();
}

/////////////////////////////////////////////////////////////////////////////
// CFolder serialization

void CFolder::Serialize(CArchive& ar)
{
	CNamed::Serialize( ar);

	if ( ar.IsStoring())
	{				// we need to remove the temps and do this one
	CNamedArray coa;
	int i;
	CNamed *pname;

		coa.Copy( m_coArray);

		for ( i=0; i<coa.GetSize(); i++)
		{			// remove the temporary items
			pname = coa.GetNamedAt( i);
			if ( pname->IsTemporary())		// it's temp
				{
				coa.RemoveAt( i);
				i--;
				}
		}
		coa.Serialize( ar);
	}
	else
		m_coArray.Serialize( ar);

}

int   CFolder::EditProperties(CWnd *pParent, CObject * )	// bring up properties dbox
{
BOOL broot = (this == GetRootObject());

	if ( broot)
	{
	CDlgDoc cdoc( broot, pParent);
	CAudtestDoc *pdoc = (CAudtestDoc *)GetDocument();

		if ( pdoc)
			{
			cdoc.PreDialog(pdoc);

			if ( IDOK == cdoc.DoModal())
				{
				cdoc.PostDialog(pdoc);
				pdoc->GetRoot()->UpdateViews();
				}

			}
	}
	else
	{
	CDlgFolder cdoc( pParent);
	CAudtestDoc *pdoc = (CAudtestDoc *)GetDocument();

		if ( pdoc)
			{
			cdoc.SetFolder( this);

//			cdoc.PreDialog(pdoc);

			if ( IDOK == cdoc.DoModal())
				{
//				cdoc.PostDialog(pdoc);
				pdoc->GetRoot()->UpdateViews();
				}

			}
	}


	return 0;
}



/////////////////////////////////////////////////////////////////////////////
// CFolder diagnostics

#ifdef _DEBUG
void CFolder::AssertValid() const
{
	CNamed::AssertValid();
}

void CFolder::Dump(CDumpContext& dc) const
{
	CNamed::Dump(dc);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CFolder operations

static int get_Pos( CNamedArray *pArray, DWORD dwID)
{
int nsize = pArray->GetSize();
int i;

	for (i=0; i<nsize; i++)
		{
		if ( dwID == (pArray->GetNamedAt(i))->GetID() )
			return i;
		}
	return -1;		// we didn't find one
}

static int get_PosByName( CNamedArray *pArray, LPCSTR lpszNewName)
{
int nsize = pArray->GetSize();
int i;
CString csname( lpszNewName);

	for (i=0; i<nsize; i++)
		{
		if ( csname == pArray->GetNamedAt(i)->GetName() )
			return i;
		}
	return -1;		// we didn't find one
}


void CFolder::Insert( CNamed *cnAdd, DWORD dwID)			// insert into the tree
{
CFolder *cdest;
CNamed *cnam;

	cnam = GetItem( dwID, TRUE);
	if ( ntFolder == cnam->GetType() )
		cdest = (CFolder *)cnam;
	else
		cdest = GetParent( dwID);

	if ( cdest)
		cdest->AddItem( cnAdd);
}


CFolder *CFolder::GetParent(DWORD dwID)
{
					// find an item by ID.  bSubs == TRUE if search subfolders
int npos = get_Pos( &m_coArray, dwID);

	if ( (-1) != npos)
		return this;

int nsize = m_coArray.GetSize();
int i;
CNamed *cnam;
CFolder *cget;

	for (i=0; i<nsize; i++)
		{
		cnam = m_coArray.GetNamedAt(i);
		if ( ntFolder == cnam->GetType())
			{
			cget = ((CFolder *)cnam)->GetParent( dwID);
			if ( cget)
				return cget;
			}
		}

	return (CFolder *)NULL;		// we didn't find one

}


CNamed *CFolder::Duplicate(void )
{
CNamed *cnew = new CFolder();

	*cnew = *this;
	return cnew;
}


				// operators
CFolder &CFolder::operator=(const CFolder &cIn)
{
CNamed &cin = (CNamed &)cIn;

	*this = cin;
 	return *this;
}


CNamed &CFolder::operator=(const CNamed &cIn)
{
CFolder &cin = (CFolder &)cIn;

	CNamed::operator=( cIn);

	m_coArray.SetSize( cin.m_coArray.GetSize());
 					// don't copy the id #
	{
	int i;

		for ( i=0; i < cin.m_coArray.GetSize(); i++)
			m_coArray.SetAt(i, cin.m_coArray.GetAt(i));
	}

 	return *this;
}


// set all roots, including subfolders
static void set_Roots( CNamed *cWho, CFolder *cRoot)
{
int ncount;

	cWho->SetRootObject( cRoot);

	if ( ntFolder == cWho->GetType())				// it's a folder, set root for subguys
		{
		CFolder *cfo = (CFolder *)cWho;

			ncount = cfo->GetSize( false);			// don't dive
			if ( ncount)
				{
				int i;

				for ( i=0; i< ncount; i++)
					set_Roots( cfo->GetItemAt(i), cRoot );
				}
		}

}


//					// add a new item
void CFolder::AddItem( CNamed *coNew)
{
CFolder *croot = (CFolder *)GetRootObject();

	m_coArray.Add( coNew);

	set_Roots( coNew, croot);

	coNew->UpdateViews();

}

//					// remove an item
void CFolder::DeleteItem( DWORD dwID)
{
int npos = get_Pos( &m_coArray, dwID);

	if ( (-1) != npos)
		{
		delete m_coArray.GetAt( npos);
		m_coArray.RemoveAt( npos, 1);		// remove 1 item
		}
	else			// it's down below somewhere
		{
		CFolder *cpa = GetParent( dwID);

		if ( cpa)
			cpa->DeleteItem( dwID);
		}
}

void CFolder::DeleteAllTemps( void)							// delete the temporary items
{
int i;
CNamed *pname;

	for ( i = m_coArray.GetSize()-1; i >=0; i--)
	{
	pname = (CNamed *)m_coArray[i];

	ASSERT( pname);

		if ( ntFolder == pname->GetType())			// it's a folder
		{
		CFolder *pfold = (CFolder *)pname;

			pfold->DeleteAllTemps();
		}
		if ( pname->IsTemporary())
		{
			((CAudtestDoc *)GetDocument())->RemoveItemView( pname->GetID());
			delete pname;
			m_coArray.RemoveAt( i);
		}

	}
}

// non-desctructive item delete
void CFolder::RemoveItem( DWORD dwID)
{
int npos = get_Pos( &m_coArray, dwID);

	if ( (-1) != npos)
		{
		m_coArray.RemoveAt( npos, 1);		// remove 1 item
		}
	else			// it's down below somewhere
		{
		CFolder *cpa = GetParent( dwID);

		if ( cpa)
			cpa->RemoveItem( dwID);
		}
}

// 			// use this guy's pointer for a replacement
bool	CFolder::ReplacePointer( CNamed *pNew, DWORD dwID)
{
int npos = get_Pos( &m_coArray, dwID);

	if ( (-1) != npos)
		{
		m_coArray.SetAt( npos, pNew);		// remove 1 item
		}
	else			// it's down below somewhere
		{
		CFolder *cpa = GetParent( dwID);

		if ( cpa)
			return cpa->ReplacePointer( pNew, dwID);
		}
	return true;

}


					// find an item by ID.  bSubs == TRUE if search subfolders
					// find an item by ID.  bSubs == TRUE if search subfolders
CNamed *CFolder::GetItem( DWORD dwID, BOOL bSubs)
{
int npos = get_Pos( &m_coArray, dwID);
int nsize = m_coArray.GetSize();
int i;
CNamed *cnam;
CNamed *cget;

	if ( dwID == GetID() )
		return this;

	if ( (-1) != npos)
		return m_coArray.GetNamedAt(npos);

	if ( (npos == -1) && !bSubs)
		return (CNamed *)NULL;			// not found

	for (i=0; i<nsize; i++)
		{
		cnam = m_coArray.GetNamedAt(i);
		if ( ntFolder == cnam->GetType())
			{
			cget = ((CFolder *)cnam)->GetItem( dwID, bSubs);
			if ( cget)
				return cget;
			}
		}

	return (CNamed *)NULL;		// we didn't find one
}


					// find an item by ID.  bSubs == TRUE if search subfolders
CNamed *CFolder::GetItemByName( LPCSTR lpszName, BOOL bSubs)
{
int npos = get_PosByName( &m_coArray, lpszName);

	if ( (-1) != npos)
		return m_coArray.GetNamedAt(npos);

	if ( (-1) == npos && !bSubs)
		return (CNamed *)NULL;			// not found

int nsize = m_coArray.GetSize();
int i;
CNamed *cnam;
CNamed *cget;

	for (i=0; i<nsize; i++)
		{
		cnam = m_coArray.GetNamedAt(i);
		if ( ntFolder == cnam->GetType())
			{
			cget = ((CFolder *)cnam)->GetItemByName( lpszName, bSubs);
			if ( cget)
				return cget;
			}
		}

	return (CNamed *)NULL;		// we didn't find one
}


//					// find an item by ID
CNamed *CFolder::GetItemAt( int nPos)
{

	if ( nPos < 0 || nPos >= m_coArray.GetSize())
		return (CNamed *)NULL;

	return m_coArray.GetNamedAt( nPos);

}


//					// find the size of the folder
int CFolder::GetSize(bool bDive)
{

	if ( ! bDive)
		return m_coArray.GetSize();

int ntotal = m_coArray.GetSize();
int nsize = ntotal;
int i;
CNamed *cnam;

	for (i=0; i<nsize; i++)
		{
		cnam = m_coArray.GetNamedAt(i);
		if ( ntFolder == cnam->GetType())
			{
			CFolder *cfo = (CFolder *)cnam;
			ntotal += cfo->GetSize( bDive );
			}
		}

	return ntotal;
}




//					// get a list of all the items
CNamedArray *CFolder::GetItemList()
{
	return &m_coArray;
}



DWORD CFolder::GetObjectSize(BOOL bDive)
{
DWORD dwsize = sizeof( CFolder);

	if ( ! bDive)
		return dwsize;			// doesn't take up any room

int ntotal = m_coArray.GetSize();
int i;
CNamed *cnam;

	for (i=0; i<ntotal; i++)
		{
		cnam = m_coArray.GetNamedAt(i);
		dwsize += cnam->GetObjectSize( bDive);
		}

	return dwsize;


}

int CFolder::GetCount(NAMETYPES nType)
{
int ntotal = m_coArray.GetSize();
int i;
CNamed *cnam;
int ncount = 0;

	for (i=0; i<ntotal; i++)
		{
		cnam = m_coArray.GetNamedAt(i);
		if ( nType == cnam->GetType())
			ncount++;
		else if ( ntFolder == cnam->GetType())
			{
			ncount += ((CFolder *)cnam)->GetCount( nType);
			}
		}

	return ncount;


}
