// speaker.cpp : implementation of the CNetworkArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include "Network.h"

#include "zFormEdt.h"
#include "Dataset.h"
#include "dlgNetwo.h"
#include "passive.h"
#include "Folder.h"

#include "fxFont.h"

#include "opItem.h"
#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


typedef struct tagNODELOC
	{
	int 	nNode;
	POINT 	ptLoc;
//	int		nDirection;		// which direction this node is pointing
	BYTE	byOrient;	// orientation
	} NODELOC;


#define NODESIZE 2

/////////////////////////////////////////////////////////////////////////////
// CNetwork Operations
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//			matrix-Invert
/////////////////////////////////////////////////////////////////////////////
static BOOL matrix_Invert( ZComplex *zMatrix, ZComplex *zVector, int nCount)
{
							// this uses arithmetic reduction
int nrow, ncol;
int i, j, k;
int nin;
ZComplex zc;
CWordArray cwrows;

				// this keeps track of which row we can use
	cwrows.SetSize( nCount, nCount);
	for ( i = 0; i<nCount; i++)
		cwrows.SetAt( i, (short )i);

	for ( ncol=0; ncol<nCount; ncol++)			// get a 1 in the row
		{
		for ( j=0; j<cwrows.GetSize(); j++)
			{
			if ( ! zMatrix[ncol + cwrows.GetAt(j) * nCount].IsZero() )		// found a non-zero
				break;
			}
		if ( j == cwrows.GetSize())						// whoops, singular matrix
			return FALSE;								// couldn't do it

		nrow = cwrows.GetAt(j);							// source row for math
		cwrows.RemoveAt(j);								// and use it no more
		nin = nrow * nCount;							// start of the row
		zc = zMatrix[nin + ncol];

		for ( j=0; j<nCount; j++)				// normalize a row
			{
			if ( ! zMatrix[nin+j].IsZero() )
				zMatrix[nin+j] /= zc;
			}

		zVector[nrow] /= zc;

		for ( j=0; j<nCount; j++)				// normalize all rows
			{
			if ( j == nrow)
				continue;
			nin = j * nCount;					// start index of row
			zc = zMatrix[nin + ncol];
			if ( ! zc.IsZero() )				// this row has a non-zero entry at that column
				{
				for ( k=0; k<nCount; k++)
					{
					zMatrix[nin + k] -= zMatrix[nrow * nCount + k] * zc;
					}
				zVector[j] -= zVector[nrow] * zc;
				}
			}
		}

	return TRUE;
}

static CDataSet *find_OrBuild( COpMulti *pOpCode, CNetwork *pNet, ZpPassive *cSub, UINT uidName)
{
CDataSet *pf = NULL;
COpFindOrCreate *ccr;
CString csname;

		csname.LoadString( uidName);
		if ( cSub)		// there is a subobject to add to the name
			csname = pNet->GetName() + "." + cSub->GetName() + "." + csname;
		else
			csname = pNet->GetName() + "." + csname;
		ccr = new COpFindOrCreate( pNet, csname, ntDataSet);
		if ( ! pOpCode->PrivateQueue( ccr) )	// we found/built it
			{
			pf = (CDataSet *)ccr->GetFound();	// our correctly named guy
			pf->SetUOM( uomFreq);
			pf->SetDOM( uomDbw);
			}

	return pf;
}

//	alter_Node			used by CalculateResponse
// this alters the node value to remove any secondary generators
// it returns 1,0 (source,ground) if attached to a generator, else
// it returns altered based on removing generators
static UINT alter_Node( CUIntArray& pSource, CUIntArray& pGround, UINT nLook)
{
int n = pSource.GetSize();
int i;
int nabove = 0;

	if ( nLook <= 1)
		return nLook;

	for ( i=0; i<n; i++)
		{
		if ( pSource[i] == nLook)
			return 1;
		if ( pSource[i] < nLook)
			nabove ++;
		}

	n = pGround.GetSize();
	for ( i=0; i<n; i++)
		{
		if ( pGround[i] == nLook)
			return 0;
		if ( pGround[i] < nLook)
			nabove ++;
		}

	return nLook + 2 - nabove;		// always have 0,1
}



/////////////////////////////////////////////////////////////////////////////
//			CalculateResponse
/////////////////////////////////////////////////////////////////////////////
void	CNetwork::CalculateResponse(COpMulti *pOpCode, CObArray& cData)
{
float fstart, fdelta;
int ncount;
int nfreq;
ZComplex *zmatrix;
ZComplex *zdest;
int nnodes;
ZComplex zvalue;
ZComplex zone(1,0);
CDataSet *pmain = NULL;
CDataSet *pimped = NULL;
CDataSet *pf;
CString  csname;
int i;
CObArray pdatasets;
CObArray *ptotal;
CUIntArray pgenSource;	// these keep track of the generator nodes
CUIntArray pgenGround;

	if ( ValidateNet( TRUE))			// something failed
		return;

	nnodes = RenumberNodes();			// makes it easier to work on this stuff
	if ( nnodes <= 1)
		return;

	ptotal = GetTotalArray();			// get drivers + passives

	pgenSource.SetSize( 0,20 );
	pgenGround.SetSize( 0,20 );			// get the generator node list
	for ( i = 0; i < ptotal->GetSize(); i++)			// init the driver pointers
		{
		ZpPassive *zp = (ZpPassive *)ptotal->GetAt(i);
		if ( ptGenerator == zp->GetType())
			{
			pgenSource.Add( zp->GetNode(0));
			pgenGround.Add( zp->GetNode(1));
			}
		}

	nnodes -= 2 * pgenSource.GetSize() - 1;				// remove duplicate nodes

	for ( i = 0; i < m_cDrivers.GetSize(); i++)			// init the driver pointers
		{
		ZpDriver *zp = (ZpDriver *)m_cDrivers.GetAt(i);
		zp->InitPointers( GetRootObject());		// we will need their datasets soon
		if ( zp->DoChart())
			{
			pf = find_OrBuild( pOpCode, this, zp, IDS_FREQUENCY);
			if ( pf)
				cData.Add( pf);
			}
		}

	if ( HasResponse() )
		{
		pf = find_OrBuild( pOpCode, this, NULL, IDS_TOTALFREQ);
		if ( pf)
			cData.Add( pf);
		else
			GenResponse( FALSE);
		}

	if ( HasImpedance() )
		{
		pf = find_OrBuild( pOpCode, this, NULL, IDS_IMPEDANCE);
		if ( pf)
			{
			pf->SetUOM( uomOhms);	// reset to ohms uom, rather than find_'s default
			pf->SetDOM( uomVolts);
			cData.Add( pf);
			}
		else
			GenImpedance( FALSE);
		}

					// now copy the datasets so we can edit the copies, not the orig.
	for ( i=0; i<cData.GetSize(); i++)
		{
		pdatasets.Add( ((CNamed *)cData.GetAt(i))->Duplicate() );
		}

	if ( HasResponse())
		pmain = (CDataSet *)pdatasets.GetAt( pdatasets.GetSize()-1-(HasImpedance()?1:0));
	if ( HasImpedance() )
		pimped = (CDataSet *)pdatasets.GetAt( pdatasets.GetSize()-1);

					// find the frequency range based on all drivers
	{
	float fend = 0.0f;
	fstart = 100000.0f;
	fdelta = 0.0f;
	for ( i=0; i<m_cDrivers.GetSize(); i++)
		{
		float fs, fd, fe;
		int ncount;
		ZpDriver *zp = (ZpDriver *)m_cDrivers.GetAt(i);		// get the first one...
		zp->GetRange( this, &fs, &fd);
		ncount = zp->GetCount( this);
		fe = fs + fd * (ncount - 1);
		if ( fs < fstart)			// use the lowest starting point
			fstart = fs;
		if ( fd > fdelta)			// use the largest delta
			fdelta = fd;
		if ( fe > fend)
			fend = fe;
		}
	ncount = 1 + (int )((fend - fstart) / fdelta);
	}

										// find the frequency range and count
	for ( i=0; i<pdatasets.GetSize(); i++)
		{
		CDataSet *pf = (CDataSet *)( pdatasets.GetAt(i) );

			pf->SetStart( fstart);
			pf->SetDelta( fdelta);
			pf->SetSize( ncount);		// set the vector sizes
		}

	zmatrix = new ZComplex[nnodes*nnodes];
	zdest   = new ZComplex[nnodes];

	::CreateProgressBar( IDS_STATCALC, 100);

	for ( nfreq=0; nfreq<ncount; nfreq++) 						// for each frequency, do all this work
		{
		float freq = fstart + fdelta * nfreq;		// frequency at this spot
		int ni, nj;
		int ki, kj;
		ZpPassive *zp;

			if ( 0 == ( nfreq % 100))
				ShowProgressBar( (100 * nfreq) / ncount);
					// zero out the source matrix
			for ( ni = 0; ni < (nnodes * nnodes); ni++)
				zmatrix[ni].SetRectangular( 0,0);

					// now insert each impedance into the transform matrix
			for ( ni = 0; ni < ptotal->GetSize(); ni++)
				{			// each component has four references
				zp = (ZpPassive *) (ptotal->GetAt(ni));
				if ( ptGenerator == zp->GetType())
					continue;		// skip this one
				ki = zp->GetNode(0);
				kj = zp->GetNode(1);
				ki = alter_Node( pgenSource, pgenGround, ki);
				kj = alter_Node( pgenSource, pgenGround, kj);
				zp->Impedance(zvalue, freq);
				zvalue = zone / zvalue;
				if ( ki)
					{
					ki--;
					zmatrix[ki * nnodes + ki] += zvalue;
					if ( kj)
						zmatrix[ki * nnodes + kj-1] -= zvalue;
					ki++;
					}
				if ( kj)
					{
					kj--;
					zmatrix[kj * nnodes + kj] += zvalue;
					if ( ki)
						zmatrix[kj * nnodes + ki-1] -= zvalue;
					}
				}


			for ( ni = 1; ni < nnodes; ni++)
				zmatrix[ni].SetRectangular( 0,0);
			zmatrix[0].SetRectangular(1,0);				// first one is a singleton

			zdest[0].SetRectangular(1,0);
			for ( ni = 1; ni < nnodes; ni++)
				zdest[ni].SetRectangular(0,0);
			matrix_Invert( zmatrix, zdest, nnodes);

			ZComplex ztotal(0,0);
			for ( nj = ni = 0; ni < m_cDrivers.GetSize(); ni++)
				{
				ZComplex zc;
				ZpDriver *zpd;

				zpd = (ZpDriver *) (m_cDrivers.GetAt(ni));
				ki = zpd->GetNode(0);
				kj = zpd->GetNode(1);
				ki = alter_Node( pgenSource, pgenGround, ki);
				kj = alter_Node( pgenSource, pgenGround, kj);
				if ( ki && kj)
					zc = zdest[ki-1] - zdest[kj-1];
				else
				if ( ki)
					zc = zdest[ki - 1];
				else
					zc = -zdest[kj - 1];
													// zc is the voltage across the driver
													// zvalue is the response at this freq
				zpd->Response(zvalue, freq);		// gets it in absolute terms

				zvalue *= zc;
				ztotal += zvalue;

				if ( zpd->DoChart() )				// we are charting this guy
					{
					CDataSet *pf = (CDataSet *)(pdatasets.GetAt(nj));
					pf->SetRectangular( nfreq, zvalue.XValue(), zvalue.YValue());
					nj++;			// next chart
					}
				}
									// after calculating each individual response
			if ( pmain)				// total response?
				{
				pmain->SetRectangular( nfreq, (float )ztotal.XValue(), (float )ztotal.YValue());
				}

			if ( pimped)					// calculate input impedance
				{							// get current into node 1 (voltage source)
				ztotal.SetRectangular(0,0);		// zero out the total
				for ( nj = ni = 0; ni < ptotal->GetSize(); ni++)
					{
					ZComplex zc;
					ZpPassive *zpd;

					zpd = (ZpPassive *) (ptotal->GetAt(ni));
					if ( ptGenerator == zpd->GetType())
						continue;
					ki = zpd->GetNode(0);
					kj = zpd->GetNode(1);
					ki = alter_Node( pgenSource, pgenGround, ki);
					kj = alter_Node( pgenSource, pgenGround, kj);
					if ( ki != 1 && kj != 1)
						continue;				// we don't care, then
					if ( ki && kj)
						zc = zdest[ki-1] - zdest[kj-1];
					else
					if ( ki)
						zc = zdest[ki - 1];
					else
						zc = -zdest[kj - 1];
					if ( kj == 1)
						zc = -zc;						// invert the voltage if node x..1
														// zc is the voltage across the driver
														// zvalue is the impedance at this freq
					zpd->Impedance(zvalue, freq);		// gets it in absolute terms
					ztotal += zc / zvalue;				// add in the current for this guy
					}

				ztotal = zone / ztotal;					// this is the input impedance (V/I)
				pimped->SetRectangular( nfreq, ztotal.XValue(), ztotal.YValue());
				}
		}

	delete [] zmatrix;
	delete [] zdest;
	delete	ptotal;

	::CloseProgressBar( );
				// do the change order
	for ( i=0; i<pdatasets.GetSize(); i++)
		{
			if ( CAudtestApp::GetTrails())					// no trails ??
			{
			COpNameTrails *cpt;
				cpt = new COpNameTrails( (CNamed *)cData.GetAt(i), (CNamed *)pdatasets.GetAt(i));			// we did find it, make the trails
				pOpCode->PrivateQueue( cpt);									// queue it up
				cData.SetAt( i, cpt->GetTreedObject());		// set the right pointer here
			}
			else
			{
			COpChange *cop = new COpChange( (CNamed *)cData.GetAt(i), (CNamed *)pdatasets.GetAt(i));
				pOpCode->PrivateQueue( cop);
				cData.SetAt( i, cop->GetTreedObject());		// set the right pointer here
			}
		}
				// we don't need to do anything special for pdatasets here

}


static void draw_Lines( CDC *pDC, NODELOC *NodeA, NODELOC *NodeB)
{
POINT ptA, ptB;
int ndx, ndy;
BOOL bdrawy = FALSE;					// draw the first dimension first
BOOL btriple = FALSE;

	ndx = NodeB->ptLoc.x - NodeA->ptLoc.x;

				// put it in order
	if ( (ndx < 0) ||		// not in order
		  ((ndx == 0) && ( NodeB->ptLoc.y < NodeA->ptLoc.y)) )
		{
		NODELOC *nnew;
			nnew = NodeA;
			NodeA = NodeB;
			NodeB = nnew;
		}

	ptA = NodeA->ptLoc;
	ptB = NodeB->ptLoc;
											// calculate the deltas
	ndx = ptB.x - ptA.x;
	ndy = ptB.y - ptA.y;

	switch( NodeA->byOrient)
		{
		case odLeft :			// left pointing
			bdrawy = TRUE;
			switch( NodeB->byOrient)			// other guy???
				{
				case 0 :
					if ( ndy < 20)		// sb size of object
						btriple = TRUE;
					break;				// nothing interesting
				case 1 :				// left to up 
					break;
				case 2 :				// left to right, must be triple
					btriple = TRUE;
					break;
				case 3 :
					break;
				}
			break;
		case odUp :			// up pointing
			if ( ndy < 0)
				bdrawy = TRUE;
			switch( NodeB->byOrient)			// other guy???
				{
				case 0 :		// up to left
					break;
				case 1 :		// up to up
					if ( ndy < 0)
						{
						bdrawy = TRUE;
						}
					break;
				case 2 :		// up to right
					bdrawy = FALSE;
					break;
				case 3 :		// up to down
					btriple = TRUE;
					break;
				}
			break;
		case odRight :				// right pointing
			switch( NodeB->byOrient)			// other guy???
				{
				case 0 :		// left pointing
					if ( ndy)
						btriple = TRUE;		// both need a y component
					break;
				case 1 :		// right to up
					if ( ndy < 0)
						{
						bdrawy = TRUE;
						}
					break;
				case 2 :		// right to right
					bdrawy = FALSE;
					btriple = FALSE;
					break;
				case 3 :		// right to down
					if ( ndy > 0)
						{
						btriple = TRUE;
						}
					break;
				}
			break;
		case odDown :				// down pointing
			if ( ndy > 0)
				bdrawy = TRUE;
			switch( NodeB->byOrient)			// other guy???
				{
				case 0 :		// down to left
					if ( ndy < 0)
						btriple = TRUE;
					break;
				case 1 :		// down to up
					btriple = TRUE;
					break;
				case 2 :		// down to right
					if ( ndy > 0)
						btriple = TRUE;
					break;
				case 3 :		// down to down
					break;
				}
			break;
		}

	pDC->MoveTo( ptA);
	if ( ! btriple)
		{
		if ( bdrawy)
			{
			pDC->LineTo( ptA.x, ptB.y);
			}
		else
			{
			pDC->LineTo( ptB.x, ptA.y);
			}
		}
	else
		{
		if ( bdrawy)
			{
			pDC->LineTo( ptA.x, (ptB.y + ptA.y)/2);
			pDC->LineTo( ptB.x, (ptB.y + ptA.y)/2);
			}
		else
			{
			pDC->LineTo( (ptA.x + ptB.x)/2, ptA.y);
			pDC->LineTo( (ptA.x + ptB.x)/2, ptB.y);
			}
		}
	pDC->LineTo( ptB);

}

static void draw_Multi( CDC *pDC, CPtrArray& cDraw)
{
RECT rcforce[4];
int  nmany[4];
BYTE ndir;
int i;
NODELOC *nl, *nu;
NODELOC node;

	for ( ndir = 0; ndir <= 3; ndir++)			// for each direction, get a bounding box
		{
		nmany[ndir] = 0;
		::SetRect( &rcforce[ndir], 10000, 10000, -10000, -10000);
		for (i=0; i<cDraw.GetSize(); i++)
			{
			nu = (NODELOC *)cDraw.GetAt(i);
			if ( nu->byOrient == ndir)
				{
				nmany[ndir]++;
				if ( nu->ptLoc.x < rcforce[ndir].left)
					rcforce[ndir].left = nu->ptLoc.x;
				if ( nu->ptLoc.x > rcforce[ndir].right)
					rcforce[ndir].right = nu->ptLoc.x;
				if ( nu->ptLoc.y < rcforce[ndir].top)
					rcforce[ndir].top = nu->ptLoc.y;
				if ( nu->ptLoc.y > rcforce[ndir].bottom)
					rcforce[ndir].bottom = nu->ptLoc.y;
				}
			}
		}
								// now rcforce contains the bounding boxes
								// and nmany contains the count
				// simple case where the rectangles don't overlap
	if ( (((!nmany[odLeft]) || !nmany[odRight])	|| 
				(rcforce[odRight].right  <= rcforce[odLeft].left) ) &&
		 (((!nmany[odUp]) || !nmany[odDown]) || 
				(rcforce[odDown].bottom <= rcforce[odUp].top ) ) )
		{
		int nhorz = nmany[odLeft] + nmany[odRight];
		int nvert = nmany[odUp] + nmany[odDown];	// number in each direction
		if ( nvert >= nhorz)					// more in this dimension
			{		// find a horizontal bus bar
			int nmin = (nmany[odDown] ? rcforce[odDown].bottom : -10000);
			int nmax = (nmany[odUp] ?  rcforce[odUp].top : 10000);
			int ntry;
				if ( nmany[odLeft] && nmany[odRight])
					{
					ntry = ( min( rcforce[odLeft].top, rcforce[odRight].top) +
						     max( rcforce[odLeft].bottom, rcforce[odRight].bottom) ) /2;
					}
				else if ( nmany[odLeft])
					ntry = (rcforce[odLeft].top + rcforce[odLeft].bottom) / 2;
				else if ( nmany[odRight])
					ntry = (rcforce[odRight].top + rcforce[odRight].bottom) / 2;
				else ntry = (nmany[odDown] && nmany[odUp]) ? (nmin + nmax)/2 : (nmany[odDown] ? nmin : nmax);
			if ( ntry < nmin)
				ntry = nmin;
			if ( ntry > nmax)
				ntry = nmax;
							// now ntry is the busbar Y location 
							// set nmin and nmax anew
			nmin = 10000;
			nmax = -10000;
			for ( i = 0; i<cDraw.GetSize(); i++)
				{
				nu = (NODELOC *)cDraw.GetAt(i);
				nmin = min( nmin, nu->ptLoc.x);
				nmax = max( nmax, nu->ptLoc.x);
				}
			for ( i = 0; i<cDraw.GetSize(); i++)
				{
				nu = (NODELOC *)cDraw.GetAt(i);
				node.ptLoc.x = nu->ptLoc.x;
				node.ptLoc.y = ntry;
				node.byOrient = (ntry > nu->ptLoc.y) ? odDown : odUp;	// the other one
				draw_Lines( pDC, &node, nu);
				if ( node.ptLoc.x != nmin && node.ptLoc.x != nmax)
					{
					CGdiObject *cold = pDC->SelectStockObject( BLACK_BRUSH);
					pDC->Ellipse( node.ptLoc.x-NODESIZE, node.ptLoc.y-NODESIZE, 
								  node.ptLoc.x+NODESIZE+1,node.ptLoc.y+NODESIZE+1);
					if ( cold)
						pDC->SelectObject( cold);
					}
				}
			pDC->MoveTo( nmin, ntry);
			pDC->LineTo( nmax, ntry);
			}
		else					// more in the other dimension
			{		// find a horizontal bus bar
			int nmin = (nmany[odRight] ? rcforce[odRight].right : -10000);
			int nmax = (nmany[odLeft] ?  rcforce[odLeft].left : 10000);
			int ntry;
				if ( nmany[odUp] && nmany[odDown])
					{
					ntry = ( min( rcforce[odUp].left, rcforce[odDown].left) +
						     max( rcforce[odUp].right, rcforce[odDown].right) ) /2;
					}
				else if ( nmany[odUp])
					ntry = (rcforce[odUp].left + rcforce[odUp].right) / 2;
				else if ( nmany[odDown])
					ntry = (rcforce[odDown].left + rcforce[odDown].right) / 2;
				else ntry = (nmany[odRight] && nmany[odLeft]) ? (nmin + nmax)/2 : (nmany[odRight] ? nmin : nmax);
			if ( ntry < nmin)
				ntry = nmin;
			if ( ntry > nmax)
				ntry = nmax;
							// now ntry is the busbar Y location 
							// set nmin and nmax anew
			nmin = 10000;
			nmax = -10000;
			for ( i = 0; i<cDraw.GetSize(); i++)
				{
				nu = (NODELOC *)cDraw.GetAt(i);
				nmin = min( nmin, nu->ptLoc.y);
				nmax = max( nmax, nu->ptLoc.y);
				}
			for ( i = 0; i<cDraw.GetSize(); i++)
				{
				nu = (NODELOC *)cDraw.GetAt(i);
				node.ptLoc.y = nu->ptLoc.y;
				node.ptLoc.x = ntry;
				node.byOrient = (ntry < nu->ptLoc.x) ? odRight : odLeft;	// the other one
				draw_Lines( pDC, &node, nu);
				if ( node.ptLoc.y != nmin && node.ptLoc.y != nmax)
					{
					CGdiObject *cold = pDC->SelectStockObject( BLACK_BRUSH);
					pDC->Ellipse( node.ptLoc.x-NODESIZE, node.ptLoc.y-NODESIZE, 
								  node.ptLoc.x+NODESIZE+1,node.ptLoc.y+NODESIZE+1);
					if ( cold)
						pDC->SelectObject( cold);
					}
				}
			pDC->MoveTo( ntry, nmin);
			pDC->LineTo( ntry, nmax);
			}
		}			// endif simple
	else					// we have at least one in each horiz/vert direction
		{
		nl = (NODELOC *)cDraw.GetAt(0);

		for (i=1; i<cDraw.GetSize(); i++)
			{
			nu = (NODELOC *)cDraw.GetAt(i);
			draw_Lines( pDC, nl, nu);
			}
		}
}


/////////////////////////////////////////////////////////////////////////////
//			DoDraw
/////////////////////////////////////////////////////////////////////////////
void CNetwork::DoDraw( CDC *pDC, LPCRECT lpWhere)
{
int i;
int ntotal;
ZpPassive *pcpassive;
CPtrArray cnew;
CPtrArray cdraw;
NODELOC *nl, *nu;
int noldmode = pDC->SetBkMode( TRANSPARENT);
CFont *cfont;
CFont *cfold;
CObArray *pall = GetTotalArray();

	cfont = CAudtestApp::GetAppFont( ftNetData).GetCurrentFont( pDC);
	cfold = pDC->SelectObject( cfont);

	cnew.SetSize(0,100);
	cdraw.SetSize(0,40);

	ntotal = pall->GetSize();
	for ( i=0; i<ntotal; i++)
		{
		pcpassive = (ZpPassive *)pall->GetAt(i);
		pcpassive->DoDraw( pDC, lpWhere);
		if ( IsDragging())		// draw nodes if we're drawing a rubber band line
			pcpassive->DrawSubHighlight( pDC);
		nl = new NODELOC;
		nl->nNode = pcpassive->GetNode(0);
		pcpassive->GetPosition( &nl->ptLoc);
		nl->byOrient = pcpassive->GetOrientation( 0);
		cnew.Add( nl);
		nl = new NODELOC;
		nl->nNode = pcpassive->GetNode(1);
		nl->ptLoc.x = pcpassive->GetEndPosition(0);
		nl->ptLoc.y = pcpassive->GetEndPosition(1);
		nl->byOrient = pcpassive->GetOrientation( 1);
		cnew.Add( nl);
		}
	delete pall;							// we're done with the list

  while( cnew.GetSize() )					// -- get all nodes connected to the first one
  	{										// --- shuffle them off to cdraw
	nl = (NODELOC *)cnew.GetAt(0);			// get the first one
	cnew.RemoveAt(0);
	cdraw.Add( nl);							// and save it here... first draw object
	for ( i=0; i < cnew.GetSize(); i++)		// find others with same node
		{
		nu = (NODELOC *)cnew.GetAt(i);
		if ( nu->nNode == nl->nNode)		// we're connected
			{
			cdraw.Add( nu);					// add it to the node draw list
			cnew.RemoveAt( i);				// remove it from the tbd list
			i--;							// alter the counter to pick the ith again
			}
		}
											// now cdraw has all of the nodes we want to draw...
	switch( cdraw.GetSize())
		{
		case 1 :			// just one guy..., draw no lines
			break;
		case 2 :			// two of them... draw a single line, appropriately(?)
			nu = (NODELOC *)cdraw.GetAt(0);
			nl = (NODELOC *)cdraw.GetAt(1);
			draw_Lines( pDC, nl, nu);
			break;
		default :			// more than 2
			draw_Multi( pDC, cdraw);
			break;
		}

	for ( i=cdraw.GetSize()-1; i >=0; i--)
		delete (NODELOC *)cdraw.GetAt(i);
	cdraw.RemoveAll();
	}

	pDC->SetBkMode( noldmode);
	pDC->SelectObject( cfold);
}

