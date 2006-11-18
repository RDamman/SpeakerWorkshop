// speaker.cpp : implementation of the CNetworkArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include <math.h>

#include "Network.h"
#include "DataSet.h"
#include "Driver.h"

#include "zFormEdt.h"
#include "dlgNetwo.h"
#include "passive.h"
#include "Folder.h"

#include "opItem.h"
#include "Utils.h"

#include "Xform.h"

#include "SetLocale.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CNetwork
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CNetwork, CNamed, VERSIONABLE_SCHEMA | 250)

static DWORD get_Line( CFile& cIn, LPSTR szBuf, DWORD dwAvail)
{
	while( dwAvail && 1 != *szBuf)		// data left and not end of buffer
		{
		cIn.Read(szBuf,1);
		dwAvail--;
		if ( '\n' ==  *szBuf)
			{
			*szBuf = '\0';
			return dwAvail;
			}
		szBuf++;
		}

	*szBuf = '\0';
	return dwAvail;			// sb 0

}

static int get_MaxNode( CNetwork *pNet)
{
int i,ntotal;
int nnext = 0;
ZpPassive *pcpassive;

		ntotal = pNet->GetDriverArray()->GetSize();
		for ( i=0; i<ntotal; i++)
			{
			pcpassive = (ZpPassive *)pNet->GetDriver(i);
			nnext = max( nnext, pcpassive->GetNode(0));
			nnext = max( nnext, pcpassive->GetNode(1));
			}
		ntotal = pNet->GetDiscreteArray()->GetSize();
		for ( i=0; i<ntotal; i++)
			{
			pcpassive = (ZpPassive *)pNet->GetDiscrete(i);
			nnext = max( nnext, pcpassive->GetNode(0));
			nnext = max( nnext, pcpassive->GetNode(1));
			}

	return nnext;
}


/////////////////////////////////////////////////////////////////////////////
// CNetwork construction/destruction
/////////////////////////////////////////////////////////////////////////////

CNetwork::CNetwork() : m_cDrivers(), m_cDiscretes()
{
	m_bIsDragging = FALSE;
	m_bAutoChart = FALSE;

	m_cDrivers.SetSize(0, 5);
	m_cDiscretes.SetSize(0, 100);
	GenResponse( TRUE);
	GenImpedance( FALSE);

ZpGenerator *zpgen = new ZpGenerator();
CString cssource;

	zpgen->SetNode(0,1);
	zpgen->SetNode(1,0);
	cssource.LoadString( IDS_SOURCE);
	zpgen->SetName(cssource);
	zpgen->SetValue(1);
	m_cDiscretes.Add( zpgen);		// we always have a generator

}

CNetwork::~CNetwork()
{
	::KillArray( &m_cDrivers);
	::KillArray( &m_cDiscretes);
}

/////////////////////////////////////////////////////////////////////////////
// CNetwork serialization
/////////////////////////////////////////////////////////////////////////////

void CNetwork::Serialize(CArchive& ar)
{
	if ( ar.IsLoading())
		{
		::KillArray( &m_cDiscretes);
		::KillArray( &m_cDrivers);		// remove the source
		}

	CNamed::Serialize( ar);

	m_cDiscretes.Serialize( ar);
	m_cDrivers.Serialize( ar);

	if (ar.IsStoring())
		{				// storing code here
		ar << (WORD )(HasResponse() ? 1 : 0);
		ar << (WORD )(HasImpedance() ? 1 : 0);
		ar << (WORD )(HasAutoChart() ? 1 : 0);
		}
	else
		{				// loading code here 
		WORD w;
		ar >> w; GenResponse( w != 0);
		ar >> w; GenImpedance( w != 0);
		ar >> w; GenAutoChart( w != 0);
		}
}

int   CNetwork::EditProperties(CWnd *pParent, CObject *cSubject )	// bring up properties dbox
{
COpCode *cop;
CNetwork *cgnew;
UINT ipage = 0;

	if ( cSubject)
		{
		ZpPassive *zp = (ZpPassive *)cSubject;
		if ( ptDriver == zp->GetType() )
			ipage = 2;
		else
			ipage = 1;
		}

	{
	CDlgNetwork cgen( pParent, ipage);

		cgen.UseNetwork(this, cSubject);

		if ( IDOK == cgen.DoModal())
			{
			cgnew = (CNetwork *)Duplicate();		// make a copy of "this"
			if ( cgnew)
				{
				cgen.SetNetwork( cgnew);
				cop = new COpChange( this, cgnew);
				cop->QueueAndDo( );
				return 0;
				}
			}
	}

	return 1;
}



/////////////////////////////////////////////////////////////////////////////
// CNetwork diagnostics
/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
void CNetwork::AssertValid() const
{
	CNamed::AssertValid();
}

void CNetwork::Dump(CDumpContext& dc) const
{
	CNamed::Dump(dc);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------
//	
// ------------------------------------------------------------------------

CObject		*CNetwork::GetDiscrete( int nWhich)
{
	if ( nWhich >= 0 && nWhich < GetDiscreteArray()->GetSize())
		return GetDiscreteArray()->GetAt( nWhich);
	return NULL;
}

// ------------------------------------------------------------------------
//	SetDiscrete
// ------------------------------------------------------------------------
void		CNetwork::SetDiscrete( int nWhich, CObject *pNew)
{
	if ( nWhich >= 0 && nWhich < GetDiscreteArray()->GetSize())
		GetDiscreteArray()->SetAt( nWhich, pNew);
}

// ------------------------------------------------------------------------
//	GetDriver
// ------------------------------------------------------------------------
CObject		*CNetwork::GetDriver( int nWhich)
{
	if ( nWhich >= 0 && nWhich < GetDriverArray()->GetSize())
		return GetDriverArray()->GetAt( nWhich);
	return NULL;
}

// ------------------------------------------------------------------------
//	SetDriver
// ------------------------------------------------------------------------
void		CNetwork::SetDriver( int nWhich, CObject *pNew)
{
	if ( nWhich >= 0 && nWhich < GetDriverArray()->GetSize())
		GetDriverArray()->SetAt( nWhich, pNew);
}

// ------------------------------------------------------------------------
//			GetTotalCount
//				return total number of objects
// ------------------------------------------------------------------------
int		CNetwork::GetTotalCount( void)
{
	return ( GetDriverArray()->GetSize() + GetDiscreteArray()->GetSize() );
}


// ------------------------------------------------------------------------
//		GetPassive( int nWhich)
//			return drivers then passive components
// ------------------------------------------------------------------------
CObject	*CNetwork::GetPassive( int nWhich)
{
	if ( nWhich >= 0 && nWhich < GetDriverArray()->GetSize())
		return GetDriverArray()->GetAt( nWhich);
	nWhich -= GetDriverArray()->GetSize();
	if ( nWhich >= 0 && nWhich < GetDiscreteArray()->GetSize())
		return GetDiscreteArray()->GetAt( nWhich);
	return NULL;
}

// build a combined array for those guys who just want passives
CObArray *CNetwork::GetTotalArray( void)
{
CObArray *parray = new CObArray;
int ndisc = GetDiscreteArray()->GetSize();
int ntotal =  ndisc + GetDriverArray()->GetSize();
int i;

	parray->SetSize( ntotal);
	for ( i=0; i < ndisc; i++)
		parray->SetAt(i, GetDiscrete( i));
	ntotal = GetDriverArray()->GetSize();
	for ( i=0; i < ntotal; i++)
		parray->SetAt( ndisc + i, GetDriver( i));

	return parray;
}

int		CNetwork::AddDiscrete( CObject *pNew)
{
		return GetDiscreteArray()->Add( pNew);
}

int		CNetwork::AddDriver( CObject *pNew)
{
		return GetDriverArray()->Add( pNew);
}


/////////////////////////////////////////////////////////////////////////////
//			Calculations
/////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------
//		RenumberNodes
//	This renumbers the nodes setting each component to (n1,n2) where n1 < n2
//	And setting the voltage source to nodes 0,1
// --------------------------------------------------------------------------

int CNetwork::RenumberNodes()
{
ZpPassive *zp;
int i,j;
int ncur, nt;
int nlistsize = 2;
CObArray *ptotal = GetTotalArray();
int ntotal = ptotal->GetSize();
int *nlist = new int[2 * ntotal];				// max possible size of nodes
												// read the node values into an array
					// find the generator
	for ( i=0; i<ntotal; i++)
		{
		zp = (ZpPassive *)ptotal->GetAt(i);
		if ( ptGenerator == zp->GetType() )
			{
			nlist[0] = zp->GetNode(1);
			nlist[1] = zp->GetNode(0);
			break;
			}
		}
					// find the driver
	for ( i=0; i<ntotal; i++)
		{
		zp = (ZpPassive *)ptotal->GetAt(i);
		if ( ptDriver == zp->GetType() )
			{
			if ( zp->GetNode(0) == nlist[0] || zp->GetNode(1) == nlist[0])
				break;			// that's ok
			int n = nlist[0];	// swap 0 and 1
			nlist[0] = nlist[1];
			nlist[1] = n;
			break;
			}
		}
						// now node 0 is ground (connection between driver and generator)

						// find all of the different node values
	for ( i=0; i<ntotal; i++)
		{
		zp = (ZpPassive *)ptotal->GetAt(i);

		ncur = zp->GetNode(0);
		for ( j=0; j<nlistsize; j++)
			if ( nlist[j] == ncur)
				break;
		if ( j == nlistsize)		// we didn't find it
			nlist[nlistsize++] = ncur;

		ncur = zp->GetNode(1);
		for ( j=0; j<nlistsize; j++)
			if ( nlist[j] == ncur)
				break;
		if ( j == nlistsize)		// we didn't find it
			nlist[nlistsize++] = ncur;
		}

					// now nlist contains all node values
					// now renumber the array...

	for ( nt=0; nt<ntotal; nt++)
	{
		int n1 = 0;
		int n2 = 0;		// init them to avoid a compiler warning
		zp = (ZpPassive *)ptotal->GetAt(nt);

		ncur = zp->GetNode(0);
		for ( i=0; i<nlistsize; i++)
			if ( ncur == nlist[i])
				{
				n1 = i;
				break;
				}
		ncur = zp->GetNode(1);
		for ( i=0; i<nlistsize; i++)
			if ( ncur == nlist[i])
				{
				n2 = i;
				break;
				}
		zp->SetNode(0, n1);
		zp->SetNode(1, n2);
	}

	delete [] nlist;

					// move everyone inside
	{
	int nminx = 1000000;
	int nminy = 1000000;
	POINT pt;
					// find the min locations
		for ( nt = 0; nt < ntotal; nt++)
			{
			zp = (ZpPassive *)ptotal->GetAt(nt);
			zp->GetPosition( &pt);
			if ( nminx > pt.x)
				nminx = pt.x;
			if ( nminy > pt.y)
				nminy = pt.y;
			}
					// move if necessary
		nminx -= 20;
		nminy -= 20;		// give us a 20,20 border

		if ( nminx < 0 || nminy < 0)
			{
			nminx = min( 0, nminx);	// don't move if min > 0
			nminy = min( 0, nminy);
			for ( nt = 0; nt < ntotal; nt++)
				{
				zp = (ZpPassive *)ptotal->GetAt(nt);
				zp->GetPosition( &pt);
				pt.x -= nminx;
				pt.y -= nminy;
				zp->SetPosition( &pt);
				}
			}
	}

	delete ptotal;			// just toss the array, not the objects

	return nlistsize;
}

/////////////////////////////////////////////////////////////////////////////
//			GetHighlighted - get the first highlighted object
/////////////////////////////////////////////////////////////////////////////
CObject *CNetwork::GetHighlighted( void)
{
int i;
int ntotal;
ZpPassive *pcpassive;

	ntotal = GetDriverArray()->GetSize();
	for ( i=0; i<ntotal; i++)
		{
		pcpassive = (ZpPassive *)GetDriver(i);
		if ( pcpassive->IsHighlighted())
			return pcpassive;
		}
	ntotal = GetDiscreteArray()->GetSize();
	for ( i=0; i<ntotal; i++)
		{
		pcpassive = (ZpPassive *)GetDiscrete(i);
		if ( pcpassive->IsHighlighted())
			return pcpassive;
		}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
//			SetHighlighted - set the highlighted object
/////////////////////////////////////////////////////////////////////////////
void CNetwork::SetHighlighted( CObject *cNew, BOOL bOnly)
{
int i;
int ntotal;
ZpPassive *pcpassive;

	if ( bOnly)
		{
		ntotal = GetDriverArray()->GetSize();
		for ( i=0; i<ntotal; i++)
			{
			pcpassive = (ZpPassive *)GetDriver(i);
			pcpassive->SetHighlight( FALSE);
			}
		ntotal = GetDiscreteArray()->GetSize();
		for ( i=0; i<ntotal; i++)
			{
			pcpassive = (ZpPassive *)GetDiscrete(i);
			pcpassive->SetHighlight( FALSE);
			}
		}

	if ( cNew)
		{
		CDrawObj *cdraw = (CDrawObj *)cNew;
		cdraw->SetHighlight( TRUE);
		}

	return;
}



/////////////////////////////////////////////////////////////////////////////
//			CreateSubCopy - make a copy from the highlighted or unhighlighted guys
/////////////////////////////////////////////////////////////////////////////
CNamed *CNetwork::CreateSubCopy(BOOL bHighlight, BOOL bUnHighlight )
{
CNetwork *cnew = new CNetwork();

	*cnew = *this;

int i;
int ntotal;
ZpPassive *pcpassive;

	ntotal = GetDriverArray()->GetSize();
	for ( i=ntotal-1; i >= 0; i--)
		{
		pcpassive = (ZpPassive *)cnew->GetDriver(i);
		if ( pcpassive->IsHighlighted() )
			{
			if ( ! bHighlight)
				{
				delete pcpassive;
				cnew->GetDriverArray()->RemoveAt(i);
				}
			else
				pcpassive->SetHighlight( FALSE);		// turn it off
			}
		else if ( ! bUnHighlight)
			{
			delete pcpassive;
			cnew->GetDriverArray()->RemoveAt(i);
			}
		}
	ntotal = GetDiscreteArray()->GetSize();
	for ( i=ntotal-1; i >= 0; i--)
		{
		pcpassive = (ZpPassive *)cnew->GetDiscrete(i);
		if ( pcpassive->IsHighlighted() )
			{
			if ( ! bHighlight)
				{
				delete pcpassive;
				cnew->GetDiscreteArray()->RemoveAt(i);
				}
			else
				pcpassive->SetHighlight( FALSE);		// turn it off
			}
		else if ( ! bUnHighlight)
			{
			delete pcpassive;
			cnew->GetDiscreteArray()->RemoveAt(i);
			}
		}

	return cnew;
}


				// operators
/////////////////////////////////////////////////////////////////////////////
//			FillObjArray - get the first highlighted object
/////////////////////////////////////////////////////////////////////////////
int CNetwork::FillObjArray( CObArray& cDest, BOOL bHighlight)
{
int i;
int ntotal;
ZpPassive *pcpassive;

	ntotal = GetDriverArray()->GetSize();
	for ( i=0; i<ntotal; i++)
		{
		pcpassive = (ZpPassive *)GetDriver(i);
		if ( (!bHighlight) || pcpassive->IsHighlighted())
			cDest.Add( pcpassive);
		}
	ntotal = GetDiscreteArray()->GetSize();
	for ( i=0; i<ntotal; i++)
		{
		pcpassive = (ZpPassive *)GetDiscrete(i);
		if ( (!bHighlight) || pcpassive->IsHighlighted())
			cDest.Add( pcpassive);
		}

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
//			AppendNet - Add objects from one to the other
/////////////////////////////////////////////////////////////////////////////
int CNetwork::AppendNet( CNetwork *pSource)
{
int nmax = 1 + get_MaxNode( this);
int i,ntotal;
ZpPassive *pcpassive;
int noff;

	noff = 10;

	SetHighlighted( NULL, TRUE);		// turn off all highlights

	ntotal = pSource->GetDriverArray()->GetSize();
	for ( i=0; i<ntotal; i++)
		{
		pcpassive = (ZpPassive *)pSource->GetDriver(i);
		pcpassive = (ZpPassive *)pcpassive->Duplicate();
		pcpassive->SetNode(0, nmax + pcpassive->GetNode(0) );
		pcpassive->SetNode(1, nmax + pcpassive->GetNode(1) );
		pcpassive->SetPosition(0, noff + pcpassive->GetPosition(0) );
		pcpassive->SetPosition(1, noff + pcpassive->GetPosition(1) );
		pcpassive->SetHighlight( TRUE);
		GetDriverArray()->Add( pcpassive);
		}
	ntotal = pSource->GetDiscreteArray()->GetSize();
	for ( i=0; i<ntotal; i++)
		{
		pcpassive = (ZpPassive *)pSource->GetDiscrete(i);
		pcpassive = (ZpPassive *)pcpassive->Duplicate();
		pcpassive->SetNode(0, nmax + pcpassive->GetNode(0) );
		pcpassive->SetNode(1, nmax + pcpassive->GetNode(1) );
		pcpassive->SetPosition(0, noff + pcpassive->GetPosition(0) );
		pcpassive->SetPosition(1, noff + pcpassive->GetPosition(1) );
		pcpassive->SetHighlight( TRUE);
		GetDiscreteArray()->Add( pcpassive);
		}

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
//			MoveObjects - move all selected objects by an offset
/////////////////////////////////////////////////////////////////////////////
POINT CNetwork::MoveObjects( POINT ptMove)
{
int i;
int ntotal;
ZpPassive *pcpassive;
POINT ptgrid = CAudtestApp::GetNetGrid();
POINT ptnew;
POINT ptamt = {0,0};		// amount moved
bool bdone = false;		// we just move one item

	ntotal = GetDriverArray()->GetSize();

	for ( i=0; i<ntotal; i++)
		{
		pcpassive = (ZpPassive *)GetDriver(i);
		if ( pcpassive->IsHighlighted())
			{
			ptnew.x = ptMove.x + pcpassive->GetPosition(0);
			ptnew.y = ptMove.y + pcpassive->GetPosition(1);

			ptnew.x = max(0, ptnew.x);
			ptnew.y = max(0, ptnew.y);

			if ( ptgrid.x )
				ptnew.x = ptgrid.x * (int )(ptnew.x / ptgrid.x);
			if ( ptgrid.y )
				ptnew.y = ptgrid.y * (int )(ptnew.y / ptgrid.y);

			if ( ! bdone)
			{
				ptamt.x = ptnew.x - pcpassive->GetPosition(0);
				ptamt.y = ptnew.y - pcpassive->GetPosition(1);
				bdone = true;		// we did one
			}

			pcpassive->SetPosition( 0, ptnew.x);
			pcpassive->SetPosition( 1, ptnew.y);
			}
		}

	ntotal = GetDiscreteArray()->GetSize();
	for ( i=0; i<ntotal; i++)
		{
		pcpassive = (ZpPassive *)GetDiscrete(i);
		if ( pcpassive->IsHighlighted())
			{
			ptnew.x = ptMove.x + pcpassive->GetPosition(0);
			ptnew.y = ptMove.y + pcpassive->GetPosition(1);

			ptnew.x = max(0, ptnew.x);
			ptnew.y = max(0, ptnew.y);

			if ( ptgrid.x )
				ptnew.x = ptgrid.x * (int )(ptnew.x / ptgrid.x);
			if ( ptgrid.y )
				ptnew.y = ptgrid.y * (int )(ptnew.y / ptgrid.y);

			if ( ! bdone)
			{
				ptamt.x = ptnew.x - pcpassive->GetPosition(0);
				ptamt.y = ptnew.y - pcpassive->GetPosition(1);
				bdone = true;		// we did one
			}
			pcpassive->SetPosition( 0, ptnew.x);
			pcpassive->SetPosition( 1, ptnew.y);
			}
		}

	return ptamt;
}


/////////////////////////////////////////////////////////////////////////////
//			GetBounds()
//	How big is the network?
//		If bSelected then only use the selected objects
/////////////////////////////////////////////////////////////////////////////
void  CNetwork::GetBounds( CRect& rcBound, BOOL bSelected)
{
int i;
int ntotal;
ZpPassive *pcpassive;
CRect rc(0,0,0,0);		// left and top are always 0,0 or less
POINT pt;
RECT rcdrew;

	ntotal = GetTotalCount();

	for ( i=0; i<ntotal; i++)
		{
		pcpassive = (ZpPassive *)GetPassive( i);
		if ( (!bSelected) || pcpassive->IsHighlighted())
			{
#if 0
			pcpassive->GetPosition( &pt);
			if ( rc.left > pt.x)
				rc.left = pt.x;
			if ( rc.right < pt.x)
				rc.right = pt.x;
			if ( rc.top > pt.y)
				rc.top = pt.y;
			if ( rc.bottom < pt.y)
				rc.bottom = pt.y;
			pcpassive->GetEndPosition( &pt);
			if ( rc.left > pt.x)
				rc.left = pt.x;
			if ( rc.right < pt.x)
				rc.right = pt.x;
			if ( rc.top > pt.y)
				rc.top = pt.y;
			if ( rc.bottom < pt.y)
				rc.bottom = pt.y;
#endif
			pcpassive->GetDrawRect( &rcdrew);
			rc.UnionRect( &rc, &rcdrew);
			}
		}

	rcBound = rc;

}


/////////////////////////////////////////////////////////////////////////////
//			GetClosest()
/////////////////////////////////////////////////////////////////////////////
CObject *CNetwork::GetClosest( LPPOINT pcPos)
{
int i;
int ntotal;
ZpPassive *pcpassive;
CPoint pt = *pcPos;

	ntotal = GetTotalCount();
	for ( i=0; i<ntotal; i++)
		{
		pcpassive = (ZpPassive *)GetPassive(i);
		if ( pcpassive->HitTest( pt ))
			return pcpassive;
		}

	return NULL;
}

// ------------------------------------------------------------------------
//		GetObjByName( csName)
// ------------------------------------------------------------------------
CObject *CNetwork::GetObjByName( CString &csName)
{
int i;
int ntotal;
ZpPassive *pcpassive;

	ntotal = GetTotalCount();
	for ( i=0; i<ntotal; i++)
		{
		pcpassive = (ZpPassive *)GetPassive(i);
		if ( csName == pcpassive->GetName())
			return pcpassive;
		}

	return NULL;
}

// ------------------------------------------------------------------------
//		SetObjNodes
// ------------------------------------------------------------------------
void CNetwork::SetObjNodes( CObject *cWho, int nNode, CObject *cOther, int nOther, BOOL bAdd)
{
ZpPassive *pcpassive;
int nnext = 0;
int nfirst;
int i,j,ntotal;

	if ( ! bAdd)
		{
		ntotal = GetDriverArray()->GetSize();
		for ( i=0; i<ntotal; i++)
			{
			pcpassive = (ZpPassive *)GetDriver(i);
			nnext = max( nnext, pcpassive->GetNode(0));
			nnext = max( nnext, pcpassive->GetNode(1));
			}
		ntotal = GetDiscreteArray()->GetSize();
		for ( i=0; i<ntotal; i++)
			{
			pcpassive = (ZpPassive *)GetDiscrete(i);
			nnext = max( nnext, pcpassive->GetNode(0));
			nnext = max( nnext, pcpassive->GetNode(1));
			}

		nnext++;

		pcpassive = (ZpPassive *)cWho;
		if ( pcpassive)
			pcpassive->SetNode( nNode, nnext);
		pcpassive = (ZpPassive *)cOther;
		if ( pcpassive)
			pcpassive->SetNode( nOther, nnext);
		}
	else				// add them together
		{
		if ( (!cWho) || !cOther)
			return;

		pcpassive = (ZpPassive *)cWho;
		nnext = pcpassive->GetNode( nNode);
		pcpassive = (ZpPassive *)cOther;
		nfirst = pcpassive->GetNode( nOther);

		ntotal = GetDriverArray()->GetSize();
		for ( i=0; i<ntotal; i++)
			{
			pcpassive = (ZpPassive *)GetDriver(i);
			for ( j=0; j<2; j++)
				if ( nnext == pcpassive->GetNode(j) )
					pcpassive->SetNode(j, nfirst);
			}
		ntotal = GetDiscreteArray()->GetSize();
		for ( i=0; i<ntotal; i++)
			{
			pcpassive = (ZpPassive *)GetDiscrete(i);
			for ( j=0; j<2; j++)
				if ( nnext == pcpassive->GetNode(j) )
					pcpassive->SetNode(j, nfirst);
			}
		}

}

// ------------------------------------------------------------------------
//	SetRectHighlight
// ------------------------------------------------------------------------
void	CNetwork::SetRectHighlight( POINT ptStart, POINT ptEnd)
{
int i,ntotal;
ZpPassive *pcpassive;
CRect rctotal;
CRect rcpass;

	SetHighlighted( NULL);			// turn off all highlights

	rctotal.left = ptStart.x;
	rctotal.right = ptEnd.x;
	rctotal.top = ptStart.y;
	rctotal.bottom = ptEnd.y;
	if ( rctotal.left > rctotal.right)
		{
		i = rctotal.left;
		rctotal.left = rctotal.right;
		rctotal.right = i;
		}
	if ( rctotal.top > rctotal.bottom)
		{
		i = rctotal.top;
		rctotal.top = rctotal.bottom;
		rctotal.bottom = i;
		}

		ntotal = GetDriverArray()->GetSize();
		for ( i=0; i<ntotal; i++)
			{
			pcpassive = (ZpPassive *)GetDriver(i);
			pcpassive->GetDrawRect( (LPRECT )rcpass);
			if ( rcpass == (rctotal & rcpass))
				pcpassive->SetHighlight( TRUE);
			}
		ntotal = GetDiscreteArray()->GetSize();
		for ( i=0; i<ntotal; i++)
			{
			pcpassive = (ZpPassive *)GetDiscrete(i);
			pcpassive->GetDrawRect( (LPRECT )rcpass);
			if ( rcpass == (rctotal & rcpass))
				pcpassive->SetHighlight( TRUE);
			}

}




void CNetwork::GetObjEndLocation( CObject *cWho, LPPOINT lpptWhere)
{
ZpPassive *pcpassive = (ZpPassive *)cWho;

	pcpassive->GetEndPosition( lpptWhere);

}

void CNetwork::GetObjLocation( CObject *cWho, LPPOINT lpptWhere)
{
ZpPassive *pcpassive = (ZpPassive *)cWho;

	pcpassive->GetPosition( lpptWhere);

}

void CNetwork::SetObjLocation( CObject *cWho, LPPOINT lpptWhere)
{
ZpPassive *pcpassive = (ZpPassive *)cWho;

	 pcpassive->SetPosition( 0, lpptWhere->x);
	 pcpassive->SetPosition( 1, lpptWhere->y);

}

void CNetwork::SetObjValue( CObject *cWho, float fNewValue)
{
ZpPassive *pcpassive = (ZpPassive *)cWho;

	 pcpassive->SetValue( fNewValue);

}

float CNetwork::GetObjValue( CObject *cWho)
{
ZpPassive *pcpassive = (ZpPassive *)cWho;

	 return (float )( pcpassive->GetValue( ) );

}

int CNetwork::EditComponent( CWnd *pParent, CObject *cWho)
{
ZpPassive *pcpassive = (ZpPassive *)cWho;

	if ( ! pcpassive)
		{
		ASSERT(0);
		return 0;
		}

	return EditProperties(pParent, cWho);
}


CNamed *CNetwork::Duplicate(void )
{
CNamed *cnew = new CNetwork();

	*cnew = *this;
	return cnew;
}


				// operators
CNetwork &CNetwork::operator=(const CNetwork &cIn)
{
CNamed &cin = (CNamed &)cIn;

	*this = cin;
 	return *this;
}



CNamed &CNetwork::operator=(const CNamed &cIn)
{
CNetwork &cin = (CNetwork &)cIn;

int i,nsize;
ZpPassive *zp;

	CNamed::operator=( cin);

 					// don't copy the id #
	GenAutoChart( cin.HasAutoChart() );
	GenResponse( cin.HasResponse() );
	GenImpedance( cin.HasImpedance() );

	::KillArray( &m_cDiscretes);
	::KillArray( &m_cDrivers);

	nsize = cin.GetDiscreteArray()->GetSize();
	for ( i=0; i < nsize; i++)
		{
		zp = (ZpPassive *)cin.GetDiscrete( i);
		m_cDiscretes.Add( zp->Duplicate() );
		}

	nsize = cin.GetDriverArray()->GetSize();
	for ( i=0; i < nsize; i++)
		{
		zp = (ZpPassive *)cin.GetDriver( i);
		m_cDrivers.Add( zp->Duplicate() );
		}

 	return *this;
}


// --------------------------------------------------------------
//					Import
// read a network from a file
// --------------------------------------------------------------
int CNetwork::Import( LPCSTR szFileName)
{
CFile file;
CFileException fe;
DWORD dwleft;
char szbuf[200];

	memset( szbuf, 0, 200);
	szbuf[199] = (char)1;		// flag byte

	if (!file.Open(szFileName, 
					CFile::modeRead | CFile::shareDenyNone,
					&fe))
		{
		return 1;
		}


	TRY
	{						// for a circuit file
	ZpPassive *pcpassive;
	CSetLocale csl( LC_ALL, 0);		// set to ansi

	::KillArray( &m_cDiscretes);
	::KillArray( &m_cDrivers);

	dwleft = file.GetLength();

	while( dwleft)
		{
		dwleft = get_Line( file, szbuf, dwleft);
		switch( szbuf[0])
			{
			case 'R' :
				pcpassive = new ZpResistor;
				break;
			case 'C' :
				pcpassive = new ZpCapacitor;
				break;
			case 'L' :
				pcpassive = new ZpInductor;
				break;
			case 'D' :
				pcpassive = new ZpDriver;
				break;
			case 'V' :
				pcpassive = new ZpGenerator;
				break;
			default :			// comments and other suchlike
				pcpassive = NULL;
				break;
			}
		if ( pcpassive)
			{
			if ( ! pcpassive->ImportLine( szbuf))
				{		// import worked, add the item
				if ( ptDriver != pcpassive->GetType())
					AddDiscrete( pcpassive);
				else
					AddDriver( pcpassive);
				}
			else			// import failed
				delete pcpassive;
			}
		}
	}
	CATCH_ALL(e)
	{
		file.Abort(); // will not throw an exception
		::KillArray( &m_cDiscretes);
		::KillArray( &m_cDrivers);
		return 2;		// return an error, however
	}
	END_CATCH_ALL

				// it all worked, so continue
	file.Close();	

	 					// header elements common to all imports
	SetLastEdit();
	{
	CString csimp;
	time_t tt;

		tt = GetLastEdit();

		csimp.Format( IDS_IMPORTED, szFileName, ctime( &tt) );

		SetDescription( csimp);
	}

						// get file write time
	{
	CFileStatus cfs;

		CFile::GetStatus( szFileName, cfs);
		SetCreated( cfs.m_ctime.GetTime() );			// creation date and time
	}

	return 0;
}

// --------------------------------------------------------------
//					Export
// write a network into a file
// --------------------------------------------------------------
int CNetwork::Export( LPCSTR szFileName)
{
CStdioFile file;
CFileException fe;
char szbufr[200];
int nsize;
int i;

	if (!file.Open(szFileName, 
					CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive,
					&fe))
		{
		return 1;
		}

	TRY
	{
	ZpPassive *pcpassive;
	CSetLocale( LC_ALL, 0);

	nsize = m_cDiscretes.GetSize();
	for ( i=0; i<nsize; i++)
		{
		pcpassive = (ZpPassive *)GetDiscrete(i);

		if ( ! pcpassive->ExportLine( szbufr))
			file.WriteString( szbufr);
		}
	
	ZpDriver *pcdriver;

	nsize = m_cDrivers.GetSize();
	for ( i=0; i<nsize; i++)
		{
		pcdriver = (ZpDriver *)GetDriver(i);

		if ( ! pcdriver->ExportLine( szbufr))
			file.WriteString( szbufr);
		}
	
	}
	CATCH_ALL(e)
	{
		file.Abort(); // will not throw an exception
		return 2;		// return an error, however
	}
	END_CATCH_ALL

	file.Close();

	return 0;

}

// --------------------------------------------------------------
//					GetFilter
// get the export filter stuff
// --------------------------------------------------------------
void CNetwork::GetFilter( CString& csExt, CString& csFilter)
{
	csExt = "CIR";
	csFilter = "Network Files (*.CIR)|*.CIR|All Files (*.*)|*.*||";
}


// --------------------------------------------------------------------------------
//					Stock Crossover Calculations
// --------------------------------------------------------------------------------
static void calc_FirstHigh( ZpPassive *pPas[4], int nStyle, float fFs, float fRe)
{
	pPas[0]->SetValue(1.0 / (2 * ONEPI * fRe * fFs));
}

static void calc_FirstLow( ZpPassive *pPas[4], int nStyle, float fFs, float fRe)
{
	pPas[0]->SetValue(fRe / (2 * ONEPI * fFs) );
}

static void calc_SecondLow( ZpPassive *pPas[4], int nStyle, float fFs, float fRe)
{
float fl, fc;

	switch( nStyle)
		{
		case xoBessel :				// bessel
			fl = .2756f;
			fc = .0912f;
			break;
		case xoButterworth :				// butterworth
			fl = .2251f;
			fc = .1125f;
			break;
		case xoChebychev :				// cheby
			fl = .1592f;
			fc = .1592f;
			break;
		case xoLinkwitz :				// L-R
			fl = .3183f;
			fc = .0796f;
			break;
		default :
			_ASSERT(0);
			fl = fc = 0.0f;		// remove warning
			break;
		}
	pPas[0]->SetValue( (fl * fRe) / fFs);
	pPas[1]->SetValue( fc / (fRe * fFs));
}

static void calc_SecondHigh( ZpPassive *pPas[4], int nStyle, float fFs, float fRe)
{
float fl, fc;

	switch( nStyle)
		{
		case xoButterworth :				// butterworth
			fl = .2251f;
			fc = .1125f;
			break;
		case xoLinkwitz :				// L-R
			fl = .3183f;
			fc = .0796f;
			break;
		case xoBessel :				// bessel
			fl = .2756f;
			fc = .0912f;
			break;
		case xoChebychev :				// cheby
			fl = .1592f;
			fc = .1592f;
			break;
		default :
			_ASSERT(0);
			fl = fc = 0.0f;		// remove warning
			break;
		}
	pPas[0]->SetValue( fc / (fRe * fFs));
	pPas[1]->SetValue( (fl * fRe) / fFs);
}

static void calc_ThirdLow( ZpPassive *pPas[4], int nStyle, float fFs, float fRe)
{
	pPas[0]->SetValue(.2387f * fRe / fFs);
	pPas[1]->SetValue(.2122f / (fRe * fFs));
	pPas[2]->SetValue(.0796 * fRe / fFs);
}

static void calc_ThirdHigh( ZpPassive *pPas[4], int nStyle, float fFs, float fRe)
{
	pPas[0]->SetValue(.1061f / (fRe * fFs));
	pPas[1]->SetValue(.1194f * fRe / fFs);
	pPas[2]->SetValue(.3183 / (fRe * fFs));
}

static void calc_FourthLow( ZpPassive *pPas[4], int nStyle, float fFs, float fRe)
{
float fl, fc, fl2, fc2;

	switch( nStyle)
		{
		case xoButterworth :				// Butterworth
			fl  = .2437f;
			fl2 = .1723f;
			fc  = .2509f;
			fc2 = .0609f;
			break;
		case xoLinkwitz :				// L-R
			fl  = .3000f;
			fl2 = .1500f;
			fc  = .2533f;
			fc2 = .0563f;
			break;
		case xoBessel :				// Bessel
			fl  = .3583f;
			fl2 = .1463f;
			fc  = .2336f;
			fc2 = .0504f;
			break;
		case xoLegendre :				// Legendre
			fl  = .2294f;
			fl2 = .2034f;
			fc  = .2365f;
			fc2 = .0910f;
			break;
		case xoGaussian :				// Gaussian
			fl  = .3253f;
			fl2 = .1674f;
			fc  = .2235f;
			fc2 = .0768f;
			break;
		case xoLinear :				// Linear-Phase
			fl  = .3285f;
			fl2 = .1578f;
			fc  = .2255f;
			fc2 = .0632f;
			break;
		default :
			_ASSERT(0);
			fl = fc = fl2 = fc2 = 0.0f;		// remove warning
			break;
		}
	pPas[0]->SetValue( (fl * fRe) / fFs);
	pPas[1]->SetValue( fc / (fRe * fFs));
	pPas[2]->SetValue( (fl2 * fRe) / fFs);
	pPas[3]->SetValue( fc2 / (fRe * fFs));
}
static void calc_FourthHigh( ZpPassive *pPas[4], int nStyle, float fFs, float fRe)
{
float fl, fc, fl2, fc2;

	switch( nStyle)
		{
		case xoButterworth :				// Butterworth
			fl  = .1009f;
			fl2 = .4159f;
			fc  = .1040f;
			fc2 = .1470f;
			break;
		case xoLinkwitz :				// L-R
			fl  = .1000f;
			fl2 = .4501f;
			fc  = .0844f;
			fc2 = .1688f;
			break;
		case xoBessel :				// Bessel
			fl  = .0862f;
			fl2 = .4983f;
			fc  = .0702f;
			fc2 = .0719f;
			break;
		case xoLegendre :				// Legendre
			fl  = .1073f;
			fl2 = .2783f;
			fc  = .1104f;
			fc2 = .1246f;
			break;
		case xoGaussian :				// Gaussian
			fl  = .1116f;
			fl2 = .3251f;
			fc  = .0767f;
			fc2 = .1491f;
			break;
		case xoLinear :				// Linear-Phase
			fl  = .1079f;
			fl2 = .3853f;
			fc  = .0741f;
			fc2 = .1524f;
			break;
		default :
			_ASSERT(0);
			fl = fc = fl2 = fc2 = 0.0f;		// remove warning
			break;
		}
	pPas[0]->SetValue( fc / (fRe * fFs));
	pPas[1]->SetValue( (fl * fRe) / fFs);
	pPas[2]->SetValue( fc2 / (fRe * fFs));
	pPas[3]->SetValue( (fl2 * fRe) / fFs);
}

// --------------------------------------------------------------------------------
//					Stock Crossover Calculations
// --------------------------------------------------------------------------------
int CNetwork::AddCrossover( int nWhich, int nType, int nStyle, int nOrder, float fFS, float fDCRes)
{
ZpPassive *car[4];
ZpPassive *pnew;
ZpPassive *psource = (ZpPassive *)GetDiscrete(0);
int i;
CPoint cp;
CPoint ptend;
int ntotal;

						// -----------------------------------------------------
						// construct the crossover
						// -----------------------------------------------------
	if ( !psource)
		return 1;			// !!!!!!


	if ( ! nType)			// highpass
		{
		switch( nOrder)
			{
			case 4 :
				pnew = new ZpInductor;
				pnew->SetName("L2");
				car[3] = pnew;
			case 3 :
				pnew = new ZpCapacitor;
				pnew->SetName("C2");
				car[2] = pnew;
			case 2 :
				pnew = new ZpInductor;
				pnew->SetName("L1");
				car[1] = pnew;
			case 1 :
				pnew = new ZpCapacitor;
				pnew->SetName("C1");
				car[0] = pnew;
				break;
			default:
				break;
			}
		}
	else				// lowpass
		{
		switch( nOrder)
			{
			case 4 :
				pnew = new ZpCapacitor;
				pnew->SetName("C2");
				car[3] = pnew;
			case 3 :
				pnew = new ZpInductor;
				pnew->SetName("L2");
				car[2] = pnew;
			case 2 :
				pnew = new ZpCapacitor;
				pnew->SetName("C1");
				car[1] = pnew;
			case 1 :
				pnew = new ZpInductor;
				pnew->SetName("L1");
				car[0] = pnew;
				break;
			default:
				break;
			}
		}

						// -----------------------------------------------------
						// setup the connections
						// -----------------------------------------------------
						// make the odd number guys vertical
						// and to ground
	for ( i=0; i<nOrder; i += 2)
		car[i]->SetLabeling( 3);		// make it horizontal
	for ( i=1; i<nOrder; i += 2)
		{
		car[i]->SetLabeling( 6);		// make it vertical
		car[i]->SetNode( 1, 0);			// make it to ground
		}
							// connect them together
	int nsrc = psource->GetNode(0);		// get the node #

	ntotal = GetDriverArray()->GetSize();
	for ( i=0; i<ntotal; i++)
		{
		pnew = (ZpPassive *)GetDriver(i);
		if ( nsrc == pnew->GetNode(0))
			pnew->SetNode(0, 1002);
		if ( nsrc == pnew->GetNode(1))
			pnew->SetNode(1, 1002);
		}
	ntotal = GetDiscreteArray()->GetSize();
	for ( i=0; i<ntotal; i++)
		{
		pnew = (ZpPassive *)GetDiscrete(i);
		if ( pnew == psource)
			continue;
		if ( nsrc == pnew->GetNode(0))
			pnew->SetNode(0, 1002);
		if ( nsrc == pnew->GetNode(1))
			pnew->SetNode(1, 1002);
		}

	car[0]->SetNode(0, nsrc);

	switch( nOrder)
		{
		case 1 :
			car[0]->SetNode(1, 1002);
			break;
		case 2 :
			car[0]->SetNode(1, 1002);
			car[1]->SetNode(0, 1002);
			car[1]->SetNode(1, psource->GetNode(1));
			break;
		case 3 :
			car[0]->SetNode(1, 1001);
			car[1]->SetNode(0, 1001);
			car[1]->SetNode(1, psource->GetNode(1));
			car[2]->SetNode(0, 1001);
			car[2]->SetNode(1, 1002);
			break;
		case 4 :
			car[0]->SetNode(1, 1001);
			car[1]->SetNode(0, 1001);
			car[1]->SetNode(1, psource->GetNode(1));
			car[2]->SetNode(0, 1001);
			car[2]->SetNode(1, 1002);
			car[3]->SetNode(0, 1002);
			car[3]->SetNode(1, psource->GetNode(1));
			break;
		}

						// -----------------------------------------------------
						// set values based on crossover
						// -----------------------------------------------------
	if ( ! nType)
		{
		switch( nOrder)
			{
			case 1 :
				calc_FirstHigh( car, nStyle, fFS, fDCRes);
				break;
			case 2 :
				calc_SecondHigh( car, nStyle, fFS, fDCRes);
				break;
			case 3 :
				calc_ThirdHigh( car, nStyle, fFS, fDCRes);
				break;
			case 4 :
				calc_FourthHigh( car, nStyle, fFS, fDCRes);
				break;
			}
		}
	else
		{
		switch( nOrder)
			{
			case 1 :
				calc_FirstLow( car, nStyle, fFS, fDCRes);
				break;
			case 2 :
				calc_SecondLow( car, nStyle, fFS, fDCRes);
				break;
			case 3 :
				calc_ThirdLow( car, nStyle, fFS, fDCRes);
				break;
			case 4 :
				calc_FourthLow( car, nStyle, fFS, fDCRes);
				break;
			}
		}

						// -----------------------------------------------------
						// set positioning
						// -----------------------------------------------------
					// get the source object...
	{
	POINT ptoff;

		pnew = new ZpInductor();		// temp to get size
		ptoff = pnew->GetDrawSize( );
		delete pnew;
		ptoff.y = ptoff.x / 2;
		ptoff.x /= 2;			// now ptoff is the offsets to use

		pnew = (ZpPassive *)GetDiscrete(0);			// the source
		if ( pnew)
			{
			pnew->GetPosition( &cp);	// get 0th entry

			cp.x += ptoff.x;			// move over and up
			cp.y -= ptoff.y;

			car[0]->SetPosition( &cp);	// set first guy here.....
			if ( nOrder > 1)
				{
				car[0]->GetEndPosition( &cp);
				cp += ptoff;
				car[1]->SetPosition( &cp);
				}
			if ( nOrder > 2)
				{
				cp.y -= ptoff.y;
				cp.x += ptoff.x;
				car[2]->SetPosition( &cp);
				}
			if ( nOrder == 4)
				{
				car[2]->GetEndPosition( &cp);
				cp += ptoff;
				car[3]->SetPosition( &cp);
				}
			if ( nOrder <= 2)
				car[0]->GetEndPosition( &ptend);
			else
				car[2]->GetEndPosition( &ptend);
			pnew->GetPosition( &cp);
			ptend -= cp;				// amount to move everyone
			ptend.x += ptoff.x;			// and over
			}
	}
										// move everyone
	ntotal = GetDriverArray()->GetSize();
	for ( i=0; i<ntotal; i++)
		{
		pnew = (ZpPassive *)GetDriver(i);
		pnew->GetPosition( &cp);
		cp.x += ptend.x;
		pnew->SetPosition( &cp);
		}
	ntotal = GetDiscreteArray()->GetSize();
	for ( i=0; i<ntotal; i++)
		{
		pnew = (ZpPassive *)GetDiscrete(i);
		if ( pnew == psource)
			continue;
		pnew->GetPosition( &cp);
		cp.x += ptend.x;
		pnew->SetPosition( &cp);
		}

						// -----------------------------------------------------
						// put it in the network
						// -----------------------------------------------------

	for ( i=0; i<nOrder; i++)
		AddDiscrete( car[i]);

	RenumberNodes();

	return 0;			// worked ok
}

// --------------------------------------------------------------------------------
//					LPad Calculations
// --------------------------------------------------------------------------------
int CNetwork::AddLPad( float fLevel, float fDCRes)
{
ZpPassive *car[2];
ZpPassive *pnew;
ZpPassive *psource = (ZpPassive *)GetDiscrete(0);
int i;
CPoint cp;
CPoint ptend;
int ntotal;

						// -----------------------------------------------------
						// construct the crossover
						// -----------------------------------------------------
	if ( !psource)
		return 1;			// !!!!!!

	double r2;

	r2 = pow(10.0, (double)-fLevel / 20);
	r2 = r2 * fDCRes / (1 - r2);		// the actual formula (see p118 in LDC)

	pnew = new ZpResistor;		// first part of lpad
	pnew->SetName("Rp1");
	pnew->SetValue( fDCRes - 1 / ( 1/r2 + 1/fDCRes));
	pnew->SetLabeling( 3);
	car[0] = pnew;
	pnew = new ZpResistor;		// first part of lpad
	pnew->SetName("Rp2");
	pnew->SetLabeling( 6);
	pnew->SetNode(1,0);			// make it to ground
	pnew->SetValue( r2);
	car[1] = pnew;


						// -----------------------------------------------------
						// setup the connections
						// -----------------------------------------------------

	int nsrc = psource->GetNode(0);		// get the node #

	ntotal = GetDriverArray()->GetSize();
	for ( i=0; i<ntotal; i++)
		{
		pnew = (ZpPassive *)GetDriver(i);
		if ( nsrc == pnew->GetNode(0))
			pnew->SetNode(0, 1002);
		if ( nsrc == pnew->GetNode(1))
			pnew->SetNode(1, 1002);
		}
	ntotal = GetDiscreteArray()->GetSize();
	for ( i=0; i<ntotal; i++)
		{
		pnew = (ZpPassive *)GetDiscrete(i);
		if ( pnew == psource)
			continue;
		if ( nsrc == pnew->GetNode(0))
			pnew->SetNode(0, 1002);
		if ( nsrc == pnew->GetNode(1))
			pnew->SetNode(1, 1002);
		}

	car[0]->SetNode(0, nsrc);
	car[0]->SetNode(1, 1002);

	car[1]->SetNode(0, 1002);
	car[1]->SetNode(1, psource->GetNode(1));

						// -----------------------------------------------------
						// set positioning
						// -----------------------------------------------------
					// get the source object...
	{
	POINT ptoff;

		pnew = new ZpInductor();		// temp to get size
		ptoff = pnew->GetDrawSize( );
		delete pnew;
		ptoff.y = ptoff.x / 2;
		ptoff.x /= 2;			// now ptoff is the offsets to use

		pnew = (ZpPassive *)GetDiscrete(0);			// the source
		if ( pnew)
			{
			pnew->GetPosition( &cp);	// get 0th entry

			cp.x += ptoff.x;			// move over and up
			cp.y -= ptoff.y;

			car[0]->SetPosition( &cp);	// set first guy here.....
			car[0]->GetEndPosition( &cp);
			cp += ptoff;
			car[1]->SetPosition( &cp);
			car[0]->GetEndPosition( &ptend);
			pnew->GetPosition( &cp);
			ptend -= cp;				// amount to move everyone
			ptend.x += ptoff.x;			// and over
			}
	}
										// move everyone
	ntotal = GetDriverArray()->GetSize();
	for ( i=0; i<ntotal; i++)
		{
		pnew = (ZpPassive *)GetDriver(i);
		pnew->GetPosition( &cp);
		cp.x += ptend.x;
		pnew->SetPosition( &cp);
		}
	ntotal = GetDiscreteArray()->GetSize();
	for ( i=0; i<ntotal; i++)
		{
		pnew = (ZpPassive *)GetDiscrete(i);
		if ( pnew == psource)
			continue;
		pnew->GetPosition( &cp);
		cp.x += ptend.x;
		pnew->SetPosition( &cp);
		}

						// -----------------------------------------------------
						// put it in the network
						// -----------------------------------------------------

	AddDiscrete( car[0]);
	AddDiscrete( car[1]);

	RenumberNodes();

	return 0;			// worked ok
}


static void average_Data( ZComplex& zCout, CDataSet *pIn, int nStart, int nCount)
{
double dtotalamp = 0.0;
double dtotalphase = 0;
int i;

	for ( i=0; i<nCount; i++)
		{
		INT32 imp = pIn->GetDataAt( i + nStart);
		dtotalamp += pIn->ConvertToFormat( ITOF(imp), uomVolts);
		dtotalphase += ITOF(pIn->GetPhaseAt( i + nStart));
		}
	dtotalamp /= nCount;
	dtotalphase /= nCount;
	zCout.SetPolar( dtotalamp, dtotalphase);
}

static int calc_InductivePeak( ZpPassive *pArr[4], float fFrequency, CDataSet *pImped)
{
ZComplex zc;
int ntotal = min( 20, pImped->GetCount() / 40);		// actually half the range
int nbegin = pImped->FreqToIndex( fFrequency) - ntotal;

		average_Data( zc, pImped, nbegin, ntotal * 2);

			// now zc is the average impedance at this point
		if ( zc.YValue())
			pArr[1]->SetValue(1/ (2 * ONEPI * fFrequency * zc.YValue()) );
		else
			pArr[1]->SetValue( 0 );
		pArr[0]->SetValue( zc.XValue());

		return 0;
}


double calc_Error( float fR, float fL, float fC, 
				  CFloatArray *pFreq, CFloatArray *pX, CFloatArray *pY)
{
ZComplex zc, zczobel;
double derror = 0.0;
float freq;
int i;
double dmin = 1000000;
double damp;

	for ( i=0; i<100; i++)
		{
		zc.SetRectangular( pX->GetAt(i), pY->GetAt(i) );	// get the input z
		damp = zc.Amplitude();
		if ( dmin > damp)
			dmin = damp;
		}
	for ( i=0; i<100; i++)
		{
		freq = pFreq->GetAt( i); // set the zobel impedance at this frequency
		zczobel.SetRectangular( fR, freq * fL - 1 / ( freq * fC) );
		zc.SetRectangular( pX->GetAt(i), pY->GetAt(i) );	// get the input z
				// parallel them and subtract original
		zc = zc | zczobel;
		derror += fabs( zc.Amplitude() - dmin);
		}

	return derror;
}

static int calc_ResonantPeak( ZpPassive *pArr[4], float fFrequency, CDataSet *pImped)
{
int i;
ZComplex zc, zczobel;
float freq;
float fre = 5;
float fqes = 1;
float fqms = 2;
CFloatArray *px = new CFloatArray();
CFloatArray *py = new CFloatArray();
CFloatArray *pfreq = new CFloatArray();
int ns;
float fC;
float fR;
float fL;
double derror, derror2;

			// we want to store about 100 values and their weights
		if ( fFrequency == 0.0 )
			 return 3;			// invalid values

		px->SetSize(100, 10);
		py->SetSize(100, 10);
		pfreq->SetSize(100, 10);

		freq = fFrequency;
		for ( i=0; i<50; i++)
			{
			ns = pImped->FreqToIndex( freq);
			average_Data( zc, pImped, ns-4, 9);
			px->SetAt( 49-i, zc.XValue() );
			py->SetAt( 49-i, zc.YValue() );
			pfreq->SetAt( 49-i, 2 * ONEPI * freq);
			freq = freq * .98f;		// get the next one down
			}
		freq = fFrequency * 1.02f;
		for ( i=0; i<50; i++)
			{
			ns = pImped->FreqToIndex( freq);
			average_Data( zc, pImped, ns-4, 9);
			px->SetAt( 50+i, zc.XValue() );
			py->SetAt( 50+i, zc.YValue() );
			pfreq->SetAt( 50+i, 2 * ONEPI * freq);
			freq = 1.02f * freq;
			}

		fR = fre + fqes * fre / fqms;
		fL = fqes * fre / ( 2 * ONEPI * fFrequency);
		fC = 1 / (2 * ONEPI * fFrequency * fre * fqes);

		float frd = fR / 10;
		float fqd = 2;

				// do a trial run to see if this works
		derror = calc_Error( fR, fL, fC, pfreq, px, py);

		do
			{
			derror = calc_Error( fR, fL, fC, pfreq, px, py);
			derror2 = calc_Error( fR + frd, fL, fC, pfreq, px, py);
			if ( derror2 < derror)
				{
				fR += frd;
				derror = derror2;
				}
			else
				{
				derror2 = calc_Error( fR - frd, fL, fC, pfreq, px, py);
				if ( derror2 < derror)
					{
					fR -= frd;
					fR = max(0, fR);
					derror = derror2;
					}
				else frd /= 2;		// cut the delta
				}
			derror2 = calc_Error( fR, fL * fqd, fC / fqd, pfreq, px, py);
			if ( derror2 < derror)
				{
				fL *= fqd;
				fC /= fqd;
				derror = derror2;
				}
			else
				{
				derror2 = calc_Error( fR, fL / fqd, fC * fqd, pfreq, px, py);
				if ( derror2 < derror)
					{
					fL /= fqd;
					fC *= fqd;
					derror = derror2;
					}
				else fqd = 1 + (fqd - 1)/2;		// cut the delta
				}
/*
			derror2 = calc_Error( fR, fL + fld, fC, pfreq, px, py);
			if ( derror2 < derror)
				{
				fL += fld;
				derror = derror2;
				}
			else
				{
				derror2 = calc_Error( fR, fL - fld, fC, pfreq, px, py);
				if ( derror2 < derror)
					{
					fL -= fld;
					fL = max(0, fL);
					derror = derror2;
					}
				else fld /= 2;		// cut the delta
				}
			derror2 = calc_Error( fR, fL, fC + fcd, pfreq, px, py);
			if ( derror2 < derror)
				{
				fC += fcd;
				derror = derror2;
				}
			else
				{
				derror2 = calc_Error( fR, fL, fC - fcd, pfreq, px, py);
				if ( derror2 < derror)
					{
					fC -= fcd;
					fC = max(0, fC);
					derror = derror2;
					}
				else fcd /= 2;		// cut the delta
				}
*/
			} while( ! (fqd < 1.001 && (fR / frd) > 1000) );

		pArr[0]->SetValue( fR);
		pArr[1]->SetValue( fC);
		pArr[2]->SetValue( fL);

		delete px;
		delete py;
		delete pfreq;

		return 0;

}

// --------------------------------------------------------------------------------
//					Stock Crossover Calculations
// --------------------------------------------------------------------------------
int CNetwork::AddZobel( DWORD dwDriver, int nType, float fFrequency, BOOL bUseDriver)
{
ZpPassive *car[4];
ZpPassive *pnew;
int i;
CPoint cp;
CPoint ptend;
int ntotal;
ZpPassive *pdrive;
CDataSet *pimped = NULL;		// init it to remove warning
int nerr;

	if ( ! bUseDriver)			// see if there's a current impedance
		{
		CString cs;

			cs.LoadString( IDS_IMPEDANCE);
			cs = GetName() + "." + cs;		// the built impedance name
			pimped = (CDataSet *)FindByName( cs, FALSE);	// find only mine
			if ( (! pimped) || ntDataSet != pimped->GetType())	// no current impedance curve!
				{
				return 2;
				}
		pdrive = (ZpPassive *)GetDiscrete( 0);			// use the generator
		ASSERT_KINDOF( ZpGenerator, pdrive);
		}
	else						// use driver as source
		{						// find the source
		ZpDriver *zp = NULL;	// init to remove warning
		ntotal = GetDriverArray()->GetSize();
		for ( i=0; i<ntotal; i++)
			{
			zp = (ZpDriver *)GetDriver(i);
			if ( dwDriver == zp->GetDriver())
				break;
			}
		if ( i == ntotal)
			return 1;			// couldn't find the driver
		zp->InitPointers( GetRootObject());		// do this before checking for valid impedance data
		if ( ! zp->GetImpedance())
			return 4;			// no impedance chart
		pdrive = zp;
		}

						// -----------------------------------------------------
						// construct the crossover
						// -----------------------------------------------------

	if ( nType)			// resonant peak rlc circuit
		{
		pnew = new ZpInductor;
		pnew->SetName("Lz1");
		car[2] = pnew;
		car[3] = NULL;
		}
	else
		{
		car[2] = NULL;
		}

	pnew = new ZpCapacitor;
	pnew->SetName("Cz1");
	car[1] = pnew;
	pnew = new ZpResistor;
	pnew->SetName("Rz1");
	car[0] = pnew;


						// -----------------------------------------------------
						// setup the connections
						// -----------------------------------------------------
						// make them all vertical and connected in a row
	for ( i=0; car[i]; i++)
		{
		car[i]->SetLabeling( 6);		// make it vertical
		}

							// connect them together
	car[0]->SetNode(1, pdrive->GetNode(1));
	car[0]->SetNode(0, 1001);
	car[1]->SetNode(1, 1001);
	if (car[2])
		{
		car[1]->SetNode( 0, 1002);
		car[2]->SetNode( 1, 1002);
		car[2]->SetNode(0, pdrive->GetNode(0));
		}
	else
		{
		car[1]->SetNode( 0, pdrive->GetNode(0));
		}


						// -----------------------------------------------------
						// set values based on driver impedance and frequency
						// -----------------------------------------------------

	{
	CDataSet *cdr;
		if ( bUseDriver)			// use the driver impedance
			{
			ZpDriver *pdr = (ZpDriver *)pdrive;
			pdr->InitPointers( GetRootObject());	// init driver pointers
			cdr = pdr->GetImpedance();			// get the impedance curve
			}
		else						// find the created network impedance
			cdr = pimped;			// use the impedance curve
		if ( ! car[2])		// impedance rise due to inductance...
			{
			nerr = calc_InductivePeak( car, fFrequency, cdr);
			}
		else				// resonant peak
			{
			nerr = calc_ResonantPeak( car, fFrequency, cdr);
			}
		if ( nerr)		// something failed in the calculation
			return nerr;
	}
						// -----------------------------------------------------
						// set positioning
						// -----------------------------------------------------
					// get the source object...
	{
		pdrive->GetEndPosition( &cp);	// get 1st entry
		ptend = car[0]->GetDrawSize( );
		cp.y -= ptend.x;
		car[0]->SetPosition( &cp);		// put it where driver was

		ptend = car[1]->GetDrawSize( );
		car[0]->GetPosition( &cp);
		cp.y -= ptend.x;
		car[1]->SetPosition( &cp);			// put it above the first

		if ( car[2] )						// put possible last entry above 2nd
			{
			ptend = car[2]->GetDrawSize( );
			car[1]->GetPosition( &cp);
			cp.y -= ptend.x;
			car[2]->SetPosition( &cp);			// put it above the first
			}
											// move the driver over some
		pnew = new ZpInductor();			// temp to get size
		ptend = pnew->GetDrawSize( );
		delete pnew;
		pdrive->GetPosition( &cp);
		if ( bUseDriver)
			cp.x += ptend.x;				// move the driver to the right
		else
			cp.x -= ptend.x;				// move the source to the left
		pdrive->SetPosition( &cp);
	}
						// -----------------------------------------------------
						// put it in the network
						// -----------------------------------------------------

	for ( i=0; car[i]; i++)
		AddDiscrete( car[i]);

	RenumberNodes();

	return 0;			// worked ok
}

// --------------------------------------------------------------------------------
//					Validate the Network
//		bShow == do we show an error box on errors
// --------------------------------------------------------------------------------


int CNetwork::ValidateNet( BOOL bShow)
{
						// make sure we have a driver
	if ( ! GetDriver(0))
		{
		if ( bShow)
			{
			::AfxMessageBox( IDS_NODRIVER);
			}
		return 1;			// woops, no drivers
		}

int i;

	for ( i=0; i<m_cDrivers.GetSize(); i++)
		{
		ZpDriver *pdr = (ZpDriver *)m_cDrivers.GetAt(i);
		if ( pdr->IsNotValid( (CFolder *)GetRootObject(), bShow))
			return 2;
		}

	return 0;
}



DWORD CNetwork::GetObjectSize(BOOL)
{
DWORD dwsize;

	dwsize = m_cDrivers.GetSize() * sizeof( CDriver);
//	dwsize += m_cDiscretes.GetSize() * sizeof( ZpPassive);

	{
	int ntotal, i;
	ZpPassive *pcpassive;

		ntotal = GetDiscreteArray()->GetSize();
		for ( i=0; i<ntotal; i++)
			{
			pcpassive = (ZpPassive *)GetDiscrete(i);
			dwsize += pcpassive->GetRuntimeClass()->m_nObjectSize;
			}
	}



	return ( dwsize);
}
