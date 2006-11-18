// speaker.cpp : implementation of the CDataSetArray classes
//


#include "stdafx.h"
#include "audtest.h"
#include "Utils.h"

#include "Passive.h"

#include "Folder.h"
#include "DataSet.h"
#include "Driver.h"

#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define TWOPI	(2 * ONEPI)

// in thousandth's of an inch
#define DRES 7
#define TDRES 14
#define FHEIGHT TDRES
#define FWIDTH TDRES

/////////////////////////////////////////////////////////////////////////////
//				local functions
/////////////////////////////////////////////////////////////////////////////


// move_Poly
//		move and possibly rotate a polygon for drawing into the dc
static void move_Poly( POINT *poly, int nCount, POINT& poffset, BYTE byOrient)
{
int i;
int ntemp;
									// build the first point in the dataset
		switch( byOrient)
			{
			case 0 :			// data as is
				poly[0].x += poffset.x;
				poly[0].y += poffset.y;
				break;
			case 1 :			// data rotated 90
				ntemp = poly[0].x;
				poly[0].x = poffset.x - poly[0].y;
				poly[0].y = poffset.y + ntemp;
				break;
			case 2 :			// data flipped
				poly[0].x = poffset.x - poly[0].x;
				poly[0].y = poffset.y - poly[0].y;
				break;
			case 3 :			// data rotated 270
				ntemp = poly[0].x;
				poly[0].x = poffset.x + poly[0].y;
				poly[0].y = poffset.y - ntemp;
				break;
			}
									// build the rest of the points
		for ( i=1; i<nCount; i++)
			{
			switch( byOrient)
				{
				case 0 :			// data as is
					poly[i].x += poly[i-1].x;
					poly[i].y += poly[i-1].y;
					break;
				case 1 :			// data rotated 90
					ntemp = poly[i].x;
					poly[i].x = poly[i-1].x - poly[i].y;
					poly[i].y = poly[i-1].y + ntemp;
					break;
				case 2 :			// data flipped
					poly[i].x = poly[i-1].x - poly[i].x;
					poly[i].y = poly[i-1].y - poly[i].y;
					break;
				case 3 :			// data rotated 270
					ntemp = poly[i].x;
					poly[i].x = poly[i-1].x + poly[i].y;
					poly[i].y = poly[i-1].y - ntemp;
					break;
				}
			}

}


/////////////////////////////////////////////////////////////////////////////
//				ZpPassive
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(ZpPassive, CDrawObj, VERSIONABLE_SCHEMA | 283)


ZpPassive::ZpPassive( ) : CDrawObj(), m_csName(cNullString) 
{
	SetNode(1, 1);
	SetNode(0, 0);
	SetPosition(0, 10);
	SetPosition(1, 10);
	SetOrientation( 0);
	SetLabeling( 1);
	m_dQ = 1000000.0;
	m_dValue = 0.0;
					// use default
}

ZpPassive::ZpPassive(const ZpPassive &cIn ) : CDrawObj(), m_csName(cNullString)
{
	m_byOrient = cIn.m_byOrient;
	m_dValue = cIn.m_dValue;
	m_dQ = cIn.m_dQ;
	m_nLabelWhere = cIn.m_nLabelWhere;
	m_nPosition[0] = cIn.m_nPosition[0];
	m_nPosition[1] = cIn.m_nPosition[1];
	m_wNode[0] = cIn.m_wNode[0];
	m_wNode[1] = cIn.m_wNode[1];
	m_csName = cIn.m_csName;
}

ZpPassive::~ZpPassive()
{

}


void ZpPassive::Serialize(CArchive& ar)
{
	CDrawObj::Serialize(ar);

	if (ar.IsStoring())
	{					// storing code here
		ar << m_csName;
		ar << m_dValue;
		ar << m_dQ;
		ar << m_wNode[0];
		ar << m_wNode[1];
		ar << (DWORD )m_nPosition[0];
		ar << (DWORD )m_nPosition[1];
		ar << m_byOrient;
		ar << (DWORD )m_nLabelWhere;
	}
	else
	{					// loading code here 
	DWORD dwin;

		ar >> m_csName;
		ar >> m_dValue;
		ar >> m_dQ;
		ar >> m_wNode[0];
		ar >> m_wNode[1];
		ar >> dwin; m_nPosition[0] = (int )dwin;
		ar >> dwin; m_nPosition[1] = (int )dwin;
		ar >> m_byOrient;
		ar >> dwin; m_nLabelWhere = (int )dwin;
	}

}

static int parse_String( CString& cIn, CString& cParse, LPCSTR szCompare)
{
CString cs;
int nf;

	nf = cIn.Find( szCompare);

	if ( 0 < nf)		// found it
		{
		cParse = cIn.Mid( 0, nf - 0);
		cIn = cIn.Right( cIn.GetLength() - nf );
		return 1;
		}

					// failed to find the string
	cParse = "";
	return 0;

}

int		ZpPassive::ImportLine( LPCSTR szLine)
{
CString cin = szLine;
CString cs;
int nout;

	cin = cin.Right( cin.GetLength() - 2);
	if ( parse_String( cin, cs, "$N_"))
		{
		cs.TrimRight();					// null this out
		SetName( cs);
		}

	cin = cin.Right( cin.GetLength() - 3);
	if ( parse_String( cin, cs, "$N_"))
		{
		sscanf( (LPCSTR )cs, "%d", &nout);
		SetNode( 0, nout);
		}

	cin = cin.Right( cin.GetLength() - 3);
		{
		int np1, np2, nor;
		char csval[40];

		sscanf( (LPCSTR )cin, "%d %s %d %d %d", &nout, csval, &np1, &np2, &nor);
		SetNode( 1, nout);
		cs = csval;
		SetValue( UnformatValue( cs));
		SetPosition( 0, np1);
		SetPosition( 1, np2);
		SetOrientation( (BYTE )nor );
		}




	return 0;
}

int		ZpPassive::ExportLine( LPSTR szLine)
{
float fval;
CString csval;

	fval = FormatValue((float )GetValue(), csval);
	sprintf( szLine, "X_%s $N_%04d $N_%04d %.2f%s %d %d %d\n", 
		GetName(), GetNode(0), GetNode(1),
		fval, (LPCSTR )csval, GetPosition(0), GetPosition(1),
		GetOrientation() ? 1 : 0);
	switch( GetType() )
		{
		case ptResistor :
			szLine[0] = 'R';
			break;
		case ptCapacitor :
			szLine[0] = 'C';
			break;
		case ptInductor :
			szLine[0] = 'L';
			break;
		default :
			ASSERT(0);
		}

	return 0;
}

// make a duplicate of this one and return its address
ZpPassive *ZpPassive::Duplicate()
{
ZpPassive *pnew;

	switch( GetType())
		{
		case ptResistor :
			pnew = new ZpResistor();
			break;
		case ptCapacitor :
			pnew = new ZpCapacitor();
			break;
		case ptInductor :
			pnew = new ZpInductor();
			break;
		case ptDriver :
			pnew = new ZpDriver();
			break;
		case ptGenerator :
			pnew = new ZpGenerator();
			break;
		default:
			pnew = (ZpPassive *)NULL;
			break;
		}

	if ( pnew)
		*pnew = *this;

	return pnew;
}

/////////////////////////////////////////////////////////////////////////////
//				ZpPassive Operations
/////////////////////////////////////////////////////////////////////////////

double	ZpPassive::Amplitude(double dFreq)
{
ZComplex Zc;

	Impedance( Zc, dFreq);

	return Zc.Amplitude();
}

double	ZpPassive::Phase(double dFreq)
{
ZComplex Zc;

	Impedance( Zc, dFreq);

	return Zc.Phase();
}

double ZpPassive::XValue( double dFreq)
{
ZComplex Zc;

	Impedance( Zc, dFreq);

	return Zc.XValue();

}

double ZpPassive::YValue( double dFreq)
{
ZComplex Zc;

	Impedance( Zc, dFreq);

	return Zc.YValue();

}

/////////////////////////////////////////////////////////////////////////////
//				ZpPassive Operators
/////////////////////////////////////////////////////////////////////////////

// -------------------------- assignment
const ZpPassive& ZpPassive::operator=(const ZpPassive& cIn)
{
	CDrawObj::operator=((CDrawObj &)cIn);

	m_dValue = 			cIn.m_dValue;
	m_dQ = 				cIn.m_dQ;
	m_wNode[0] = 		cIn.m_wNode[0];
	m_wNode[1] = 		cIn.m_wNode[1];
	m_nPosition[0] = 	cIn.m_nPosition[0];
	m_nPosition[1] = 	cIn.m_nPosition[1];
	m_csName = 			cIn.m_csName;
	m_byOrient = 		cIn.m_byOrient;
	m_nLabelWhere =		cIn.m_nLabelWhere;

	return *this;
}


/////////////////////////////////////////////////////////////////////////////
//				ZpPassive Virtuals
/////////////////////////////////////////////////////////////////////////////
void ZpPassive::Impedance(ZComplex&, double )
{
	ASSERT(0);
}


NAMETYPES ZpPassive::GetType(void ) const		// type of passive object
{
	ASSERT(0);
	return ptResistor;
}

void ZpPassive::DoDraw( CDC *, LPCRECT )
{
	ASSERT(0);

}



// this just draws the labels and stuff
void ZpPassive::DrawLabels( CDC *pcDC, LPCRECT lpcDraw)
{
POINT ptcenter;
CRect rcdraw;
CString csdraw;
CRect rcobj;
CString csvalue;
int ndigits;
#define DT_NORM (DT_SINGLELINE | DT_NOPREFIX)

	GetDrawRect( rcobj);
	ptcenter.x = lpcDraw->left + (rcobj.right + rcobj.left) / 2;
	ptcenter.y = lpcDraw->top + (rcobj.top + rcobj.bottom) / 2;
	if ( ptResistor == GetType() || ptCapacitor == GetType() || ptInductor == GetType())
		{
		ndigits = CAudtestApp::GetPrecision( 0);
		switch( ndigits)	// respond to precision request
			{
			case -1 :		// never been set
				ndigits = -3;		// 3 digits then
				break;
			case 0 :
			case 1 :
			case 2 :
			case 3 :
				ndigits = -(1 + ndigits);		// total # of digits
				break;
			case 4 :
			case 5 :
				ndigits = ndigits - 3;			// # of decimal places
				break;
			default :
				ASSERT(0);
				break;
			}
		FullFormatValue(csvalue, (float )GetValue(), ndigits);
		csvalue += GetValueSuffix();
		}
	else
		csvalue = _T("");	// it's a driver or signal without a value

	csdraw = GetName();

	if ( 0 == GetOrientation() || 2 == GetOrientation())	// horizontal
		{
		rcdraw.SetRect( ptcenter.x-100,rcobj.top-100,ptcenter.x+100,rcobj.top-1);
		switch( GetLabeling())
			{
			case 1 :		// both top
				if ( ! csvalue.IsEmpty())
					csdraw = csdraw + "\n" + csvalue;	// two lines of data
				{
				CRect rctest = rcdraw;
				rcdraw.top = rcdraw.bottom - 
							 pcDC->DrawText( (LPCSTR )csdraw, -1, rctest, DT_NOPREFIX | DT_CENTER | DT_CALCRECT);
				}
				pcDC->DrawText( (LPCSTR )csdraw, -1, rcdraw, DT_NOPREFIX | DT_CENTER);
				break;
			case 2 :		// both bottom
				if ( ! csvalue.IsEmpty())
					csdraw = csdraw + "\n" + csvalue;	// two lines of data
				rcdraw.top = rcobj.bottom;
				rcdraw.bottom = rcdraw.top + 300;
				pcDC->DrawText( csdraw, -1, rcdraw, DT_NOPREFIX | DT_TOP | DT_CENTER);
				break;
			default :
				pcDC->DrawText( csdraw, -1, rcdraw, DT_NORM | DT_BOTTOM | DT_CENTER);
				if ( ! csvalue.IsEmpty())
					{
					rcdraw.top = rcobj.bottom;
					rcdraw.bottom = rcdraw.top + 300;
					pcDC->DrawText( csvalue, -1, rcdraw, DT_NORM | DT_TOP | DT_CENTER);
					}
				break;
			}
		}
	else
		{						// vertical
		rcdraw.SetRect( rcobj.left-300,ptcenter.y-50,rcobj.left-1,ptcenter.y+50);
		switch( GetLabeling())
			{
			case 4 :		// both left
				if ( ! csvalue.IsEmpty())
					csdraw = csdraw + "\n" + csvalue;	// two lines of data
				rcdraw.bottom = ptcenter.y;
				{
				CRect rctest = rcdraw;
				rcdraw.top = rcdraw.bottom - 
							 pcDC->DrawText( (LPCSTR )csdraw, -1, rctest, DT_NOPREFIX | DT_RIGHT | DT_CALCRECT) / 2;
				rcdraw.bottom = rcdraw.top + 100;
				}
				pcDC->DrawText( csdraw, -1, rcdraw, DT_NOPREFIX | DT_RIGHT);
				break;
			case 5 :		// both right
				if ( ! csvalue.IsEmpty())
					csdraw = csdraw + "\n" + csvalue;	// two lines of data
				rcdraw.left = rcobj.right + 4;
				rcdraw.right = rcdraw.left + 300;
				rcdraw.bottom = ptcenter.y;
				{
				CRect rctest = rcdraw;
				rcdraw.top = rcdraw.bottom - 
							 pcDC->DrawText( (LPCSTR )csdraw, -1, rctest, DT_NOPREFIX | DT_LEFT | DT_CALCRECT) / 2;
				rcdraw.bottom = rcdraw.top + 100;
				}
				pcDC->DrawText( (LPCSTR )csdraw, -1, rcdraw, DT_NOPREFIX | DT_LEFT);
				break;
			default :		// split
				pcDC->DrawText( (LPCSTR )csdraw, -1, rcdraw, DT_NORM | DT_VCENTER | DT_RIGHT); 
				if ( ! csvalue.IsEmpty())
					{
					rcdraw.left = rcobj.right + 4;
					rcdraw.right = rcdraw.left + 300;
					pcDC->DrawText( csvalue, -1, rcdraw, DT_NORM | DT_VCENTER | DT_LEFT);
					}
				break;
			}
		}


}

void ZpPassive::GetEndPosition( LPPOINT lpPt)
{
	lpPt->x = GetEndPosition(0);
	lpPt->y = GetEndPosition(1);
}

int ZpPassive::GetEndPosition( int nWhich)
{
POINT ptpoly[2];
POINT ptstart;

	ptpoly[0].x = ptpoly[0].y = 0;
	ptpoly[1] = GetDrawSize();

	GetPosition( &ptstart);

	move_Poly( ptpoly, 2, ptstart, GetOrientation());

	return ( nWhich ? ptpoly[1].y : ptpoly[1].x );
}

POINT ZpPassive::GetDrawSize()
{
	ASSERT(0);
	return CPoint(0,0);
}

// ----------------------------------------------------------------------
//		GetValueSuffix
//			default to nothing
// ----------------------------------------------------------------------
LPCSTR	ZpPassive::GetValueSuffix( void)	// get the label suffix
{
	return "";
}


// ----------------------------------------------------------------------
//		GetOrientation
// ----------------------------------------------------------------------
BYTE ZpPassive::GetOrientation( int nWhich)
{
	if ( ! nWhich)				// the left hand side, use the object orientation
		return GetOrientation();

	return ((BYTE )( ( GetOrientation() + 2) % 4) );
}

void ZpPassive::SetLabeling( int nDirection)
{
	m_nLabelWhere = nDirection;
	if ( m_nLabelWhere > 3)		// vertical
		{
		SetOrientation( 1);
		}
	else if ( m_nLabelWhere)	// not default/0
		{
		SetOrientation( 0);
		}
				// else 0 --> leave it alone
}

// perform the orientation adjustments
void ZpPassive::AdjustDrawRect( LPCRECT lprcOut, LPCRECT lpStart)
{
POINT pts;
RECT rcdraw = *lprcOut;

	::OffsetRect( &rcdraw, lpStart->left, lpStart->top);		// move it

	GetPosition( &pts);
	move_Poly( (POINT *)&rcdraw, 2, pts, GetOrientation());
	if ( rcdraw.left > rcdraw.right)
		{
		int n = rcdraw.left;
			rcdraw.left = rcdraw.right;
			rcdraw.right = n;
		}
	if ( rcdraw.top > rcdraw.bottom)
		{
		int n = rcdraw.top;
			rcdraw.top = rcdraw.bottom;
			rcdraw.bottom = n;
		}

	SetDrawRect( &rcdraw);
}


/////////////////////////////////////////////////////////////////////////////
//				ZpPassive EditProperties
/////////////////////////////////////////////////////////////////////////////
int		ZpPassive::EditProperties()
{
	return 0;

#if 0
CDlgPassiveProp	cdlg;
int nout;

	cdlg.m_csName = GetName();
	cdlg.m_nType = GetType();
	cdlg.m_nNode1 = GetNode(0);
	cdlg.m_nNode2 = GetNode(1);
	cdlg.m_fValue = (float )GetValue();
	cdlg.m_bVertical = (1 == GetOrientation());
	cdlg.m_nXpos = GetPosition(0);
	cdlg.m_nYpos = GetPosition(1);
	cdlg.m_fValue = ::FormatValue( cdlg.m_fValue, cdlg.m_csUnit);

	switch( GetType())
		{
		case ptResistor :
			cdlg.m_csUnit += "Ohm";
			break;
		case ptCapacitor :
			cdlg.m_csUnit += "F";
			break;
		case ptInductor :
			cdlg.m_csUnit += "H";
			break;
		case ptDriver :
			break;
		case ptGenerator :
			break;
		default:
			break;
		}

	nout = cdlg.DoModal();

	if ( IDOK == nout)
		{
		SetValue( ::UnformatValue( cdlg.m_fValue, cdlg.m_csUnit));
		SetName( cdlg.m_csName);
		SetNode(0, cdlg.m_nNode1);
		SetNode(1, cdlg.m_nNode2);
		SetPosition(0, cdlg.m_nXpos);
		SetPosition(1, cdlg.m_nYpos);
		SetOrientation( (BYTE )(cdlg.m_bVertical ? 1 : 0) );
		}
	return nout;
#endif

}

BOOL ZpPassive::HitTest( CPoint cPt, UINT *pnFlags)		// do a hittest: type of hit -> nFlags 
{
BOOL bhit;

	bhit = CDrawObj::HitTest( cPt, pnFlags);					// nope

POINT pt;


	GetPosition( &pt);
	pt.x -= cPt.x;
	pt.y -= cPt.y;								// here's the difference
	if ( (pt.x * pt.x + pt.y * pt.y) < 40)
		{
		bhit = TRUE;
		if ( pnFlags)
			*pnFlags |= TVHT_TOLEFT;
		}

	pt.x = GetEndPosition( 0);
	pt.y = GetEndPosition( 1);
	pt.x -= cPt.x;
	pt.y -= cPt.y;								// here's the difference
	if ( (pt.x * pt.x + pt.y * pt.y) < 40)
		{
		bhit = TRUE;
		if ( pnFlags)
			*pnFlags |= TVHT_TORIGHT;
		}


	return bhit;

}


void ZpPassive::DrawHighlight( CDC *pDC)
{
POINT pt;
int ntotal;
CGdiObject *pbrush;

	if ( IsHighlighted())
	{
		CDrawObj::DrawHighlight( pDC);
		ntotal = 6;
		pbrush = pDC->SelectStockObject( NULL_BRUSH);
	}
	else
	{
		if ( ! CAudtestApp::GetDrawEndpoints())
			return;			// don't draw endpoints
		ntotal = 2;
		pbrush = pDC->SelectStockObject( BLACK_BRUSH);
	}


	GetPosition( &pt);

	pDC->Ellipse( pt.x-ntotal, pt.y-ntotal, pt.x+ntotal+1, pt.y+ntotal+1);
	pt.x = GetEndPosition( 0);
	pt.y = GetEndPosition( 1);
	pDC->Ellipse( pt.x-ntotal, pt.y-ntotal, pt.x+ntotal+1, pt.y+ntotal+1);

	pDC->SelectObject( pbrush);



}

void ZpPassive::DrawSubHighlight( CDC *pDC)
{
POINT pt;
CGdiObject *poldbrush;

	if ( IsHighlighted())
		return;

	GetPosition( &pt);

	poldbrush = pDC->SelectStockObject( GRAY_BRUSH);

	pDC->Ellipse( pt.x-6, pt.y-6, pt.x+7, pt.y+7);
	pt.x = GetEndPosition( 0);
	pt.y = GetEndPosition( 1);
	pDC->Ellipse( pt.x-6, pt.y-6, pt.x+7, pt.y+7);

	if ( poldbrush)
		pDC->SelectObject( poldbrush);
}


#ifdef _DEBUG
void ZpPassive::AssertValid() const
{
	CDrawObj::AssertValid();
}

void ZpPassive::Dump(CDumpContext& dc) const
{
	CDrawObj::Dump(dc);
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
//				ZpPassive Ends
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//				ZpResistor
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(ZpResistor, ZpPassive, VERSIONABLE_SCHEMA | 284)


ZpResistor::ZpResistor( ) 
{
}

ZpResistor::ZpResistor(const ZpResistor &cIn )  : ZpPassive( cIn)
{
}

ZpResistor::~ZpResistor()
{
}


void ZpResistor::Serialize(CArchive& ar)
{
	ZpPassive::Serialize(ar);

}

#ifdef _DEBUG
void ZpResistor::AssertValid() const
{
	ZpPassive::AssertValid();
}

void ZpResistor::Dump(CDumpContext& dc) const
{
	ZpPassive::Dump(dc);
	dc << "Resistor";
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
//				ZpPassive Virtuals
/////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------------------------
//		Impedance
// --------------------------------------------------------------------------
void ZpResistor::Impedance(ZComplex& ZcOut, double )
{
	ZcOut.SetRectangular( GetValue(), 0);			// easy for resistor
}

// --------------------------------------------------------------------------
//		DoDraw
// --------------------------------------------------------------------------
void ZpResistor::DoDraw( CDC *pcDC, LPCRECT lpcrWhere)
{
CGdiObject *poldpen = pcDC->SelectStockObject( BLACK_PEN);
POINT ptstart;
POINT ptpoly[] = { {0,0}, {DRES,0}, {DRES/2,-DRES}, 
					{DRES,TDRES}, {DRES,-TDRES}, {DRES,TDRES}, {DRES,-TDRES}, 
					{DRES/2,DRES}, {DRES+1,0} };
POINT ptpolyrec[] = { {0,0}, {DRES+DRES/2,0}, { 0, DRES }, {2*TDRES, 0 }, {0 , -TDRES }, 
					{ -2*TDRES, 0}, {0, DRES }, {0, -DRES }, {2*TDRES, 0 }, 
					{0, DRES }, {DRES+DRES/2+1,0} };
int npoints;
POINT *ptdraw;

	if ( CAudtestApp::GetResistorType() )			// boxes == 1
	{
		ptdraw = ptpolyrec;
		npoints = sizeof( ptpolyrec) / sizeof( POINT);
	}
	else
	{
		ptdraw = ptpoly;
		npoints = sizeof( ptpoly) / sizeof( POINT);
	}


	{
	CRect rcdraw( 0,  -DRES, 3*TDRES + DRES, TDRES);

		AdjustDrawRect( rcdraw, lpcrWhere);
	}

	ptstart.x = lpcrWhere->left + GetPosition(0);
	ptstart.y = lpcrWhere->top + GetPosition(1);

	move_Poly( ptdraw, npoints, ptstart, GetOrientation());
	pcDC->Polyline( ptdraw,  npoints);

	DrawLabels( pcDC, lpcrWhere);

	DrawHighlight( pcDC);

	pcDC->SelectObject( poldpen);


}

// --------------------------------------------------------------------------
//		GetDrawSize
// --------------------------------------------------------------------------
POINT ZpResistor::GetDrawSize()
{
	return CPoint(3*TDRES + DRES, 0);
}


/////////////////////////////////////////////////////////////////////////////
//				ZpResistor Ends
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//				ZpCapacitor
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(ZpCapacitor, ZpPassive, VERSIONABLE_SCHEMA | 285)


ZpCapacitor::ZpCapacitor( ) 
{
}

ZpCapacitor::ZpCapacitor(const ZpCapacitor &cIn )  : ZpPassive( cIn) 
{
}

ZpCapacitor::~ZpCapacitor()
{
}


void ZpCapacitor::Serialize(CArchive& ar)
{
	ZpPassive::Serialize(ar);

}

#ifdef _DEBUG
void ZpCapacitor::AssertValid() const
{
	ZpPassive::AssertValid();
}

void ZpCapacitor::Dump(CDumpContext& dc) const
{
	ZpPassive::Dump(dc);
	dc << "Capacitor";
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
//				ZpPassive Virtuals
/////////////////////////////////////////////////////////////////////////////
void ZpCapacitor::Impedance(ZComplex& ZcOut, double dFreq)
{
	ZcOut.SetRectangular( 0, -1/(TWOPI*dFreq*GetValue()));			// easy for cap

}

void ZpCapacitor::DoDraw( CDC *pcDC, LPCRECT lpcrWhere)
{
CGdiObject *poldpen = pcDC->SelectStockObject( BLACK_PEN);
POINT ptstart;
POINT ptpoly[8] = { {0,0}, {TDRES,0}, {0,-DRES-DRES/2}, { 0,3*DRES}, 	 // make sure we draw the lines the same way
					{ TDRES+DRES, -DRES-DRES/2-1}, {-TDRES, 0}, { 0, -DRES-DRES/2}, { 0, 3*DRES} };
int npoints = sizeof( ptpoly) / sizeof( POINT);

	{
	CRect rcdraw( 0, -DRES-DRES/2, 2*TDRES+DRES, 3*DRES);

		AdjustDrawRect( rcdraw, lpcrWhere);
	}

	ptstart.x = lpcrWhere->left + GetPosition(0);
	ptstart.y = lpcrWhere->top + GetPosition(1);


	move_Poly( ptpoly, npoints, ptstart, GetOrientation());
	pcDC->Polyline( ptpoly,  npoints/2);
	pcDC->Polyline( ptpoly+4,  npoints/2);

	DrawLabels( pcDC, lpcrWhere);

	DrawHighlight( pcDC);

	pcDC->SelectObject( poldpen);
}

POINT ZpCapacitor::GetDrawSize()
{
	return CPoint(2*TDRES+DRES, 0);
}


/////////////////////////////////////////////////////////////////////////////
//				ZpCapacitor Ends
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//				ZpInductor
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(ZpInductor, ZpPassive, VERSIONABLE_SCHEMA | 286)


ZpInductor::ZpInductor( ) 
{
}

ZpInductor::ZpInductor(const ZpInductor &cIn )  : ZpPassive( cIn) 
{
}

ZpInductor::~ZpInductor()
{
}


void ZpInductor::Serialize(CArchive& ar)
{
	ZpPassive::Serialize(ar);

}
#ifdef _DEBUG
void ZpInductor::AssertValid() const
{
	ZpPassive::AssertValid();
}

void ZpInductor::Dump(CDumpContext& dc) const
{
	ZpPassive::Dump(dc);
	dc << "Inductor";
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
//				ZpPassive Virtuals
/////////////////////////////////////////////////////////////////////////////
void ZpInductor::Impedance(ZComplex& ZcOut, double dFreq)
{
double dval = GetValue() * TWOPI * dFreq;

	if ( GetQ() >= 1000.0)									// default or really big Q
		ZcOut.SetRectangular( 0, dval);						// use 0,2piL
	else
	{
		double rval = dval * 1000.0 / ( dFreq * GetQ());	// the actual resistance value
		ZcOut.SetRectangular( rval, dval);					// use 1000X/fQ,2piL
	}

}

void ZpInductor::DoDraw( CDC *pcDC, LPCRECT lpcrWhere)
{
int i;
CGdiObject *poldpen = pcDC->SelectStockObject( BLACK_PEN);
POINT ptstart;
POINT ptpoly[12] = { {0,0}, {DRES+1,0}, {4*TDRES-1,0}, {DRES+1,0}, 
					{-4*TDRES-DRES-1,0}, { TDRES,0}, {0,0}, {TDRES,0},
					 {0,0}, {TDRES,0},  {0,0}, {TDRES,0} };
CRect rcbound;

	{
	CRect rcdraw(  0, -TDRES, 5*TDRES, TDRES);

		AdjustDrawRect( rcdraw, lpcrWhere);
	}

	ptstart.x = lpcrWhere->left + GetPosition(0);
	ptstart.y = lpcrWhere->top + GetPosition(1);

	move_Poly( ptpoly, 12, ptstart, GetOrientation());
	pcDC->Polyline( ptpoly, 2);			// endline A
	pcDC->Polyline( ptpoly+2,2);		// endline B
	if ( ptpoly[4].x == ptpoly[5].x)		// did we flip vertically???
		{					// yes
		for ( i=0; i<8; i += 2)
			{
			rcbound.SetRect( ptpoly[4+i].x-TDRES, ptpoly[4+i].y, ptpoly[5+i].x+TDRES, ptpoly[5+i].y);
			pcDC->Arc( rcbound, ptpoly[5+i], ptpoly[4+i]);
			}
		}
	else
		{					// no
		for ( i=0; i<8; i += 2)
			{
			rcbound.SetRect( ptpoly[4+i].x, ptpoly[4+i].y-TDRES, ptpoly[5+i].x, ptpoly[5+i].y+TDRES);
			pcDC->Arc( rcbound, ptpoly[5+i], ptpoly[4+i]);
			}
		}

	DrawLabels( pcDC, lpcrWhere);

	DrawHighlight( pcDC);

	pcDC->SelectObject( poldpen);

}

POINT ZpInductor::GetDrawSize()
{
	return CPoint(5*TDRES, 0);
}


/////////////////////////////////////////////////////////////////////////////
//				ZpInductor Ends
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//				ZpGenerator
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(ZpGenerator, ZpPassive, VERSIONABLE_SCHEMA | 287)


ZpGenerator::ZpGenerator( ) 
{
	SetOrientation(1);			// we start out vertically
}

ZpGenerator::ZpGenerator(const ZpGenerator &cIn )  : ZpPassive( cIn) 
{
}

ZpGenerator::~ZpGenerator()
{
}


void ZpGenerator::Serialize(CArchive& ar)
{
	ZpPassive::Serialize(ar);

}

#ifdef _DEBUG
void ZpGenerator::AssertValid() const
{
	ZpPassive::AssertValid();
}

void ZpGenerator::Dump(CDumpContext& dc) const
{
	ZpPassive::Dump(dc);
	dc << "Generator";
}
#endif //_DEBUG




BYTE ZpGenerator::GetOrientation( int nWhich)
{
	return ( (BYTE )(GetOrientation() ? 
		(nWhich ? 3 : 1) : (nWhich ?  2 : 0)));		// only has two directions, both left and/or both up
}


BYTE ZpGenerator::GetOrientation( void)
{
	return ZpPassive::GetOrientation();
}


int		ZpGenerator::ImportLine( LPCSTR szLine)
{

	return ZpPassive::ImportLine( szLine);

}

int		ZpGenerator::ExportLine( LPSTR szLine)
{
float fval;
CString csval;

	fval = FormatValue((float )GetValue(), csval);

	sprintf( szLine, "X_%s $N_%04d $N_%04d %.2f%s %d %d %d\n", 
		GetName(), GetNode(0), GetNode(1),
		fval, (LPCSTR )csval, GetPosition(0), GetPosition(1),
		GetOrientation() ? 1 : 0);

	szLine[0] = 'V';

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
//				ZpPassive Virtuals
/////////////////////////////////////////////////////////////////////////////
void ZpGenerator::Impedance(ZComplex& ZcOut, double )
{
	ZcOut.SetRectangular(0,0);		// no impedance

}

void ZpGenerator::DoDraw( CDC *pcDC, LPCRECT lpcrWhere)
{
CGdiObject *poldpen = pcDC->SelectStockObject( BLACK_PEN);
POINT ptstart;
POINT ptpoly[6] = { {0,0}, {TDRES,0},	// first line
					{0,-TDRES}, {2*TDRES,2*TDRES}, 	// ellipse boundaries
					 {0,-TDRES}, {TDRES,0} };		// last line

	{
	CRect rcdraw(  0, -TDRES, 4*TDRES, 2*TDRES);

		AdjustDrawRect( rcdraw, lpcrWhere);
	}

	ptstart.x = lpcrWhere->left + GetPosition(0);
	ptstart.y = lpcrWhere->top + GetPosition(1);

	move_Poly( ptpoly, 6, ptstart, GetOrientation());
	pcDC->Polyline( ptpoly,  2);
	pcDC->Polyline( ptpoly+4,  2);
	pcDC->Ellipse( ptpoly[2].x,ptpoly[2].y,ptpoly[3].x,ptpoly[3].y);

	DrawHighlight( pcDC);

	DrawLabels( pcDC, lpcrWhere);

	pcDC->SelectObject( poldpen);
}

POINT ZpGenerator::GetDrawSize()
{
	return CPoint(4*TDRES, 0);
}



/////////////////////////////////////////////////////////////////////////////
//				ZpGenerator Ends
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//				ZpDriver
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(ZpDriver, ZpPassive, 2 | VERSIONABLE_SCHEMA )


ZpDriver::ZpDriver( ) 
{

	m_bChart = FALSE;
	m_bOutOfPhase = FALSE;
	m_dwDriver = 0;
	m_fOffset = 0.0f;
	m_pDriver = NULL;
	m_pResponse = NULL;
	m_pImpedance = NULL;
	SetLabeling( 5);
//	SetOrientation(1);			// we start out vertically

}

ZpDriver::ZpDriver(const ZpDriver &cIn )  : ZpPassive( cIn) 
{
	m_bChart = cIn.m_bChart;
	m_bOutOfPhase = cIn.m_bOutOfPhase;
	m_dwDriver = cIn.m_dwDriver;
	m_fOffset = cIn.m_fOffset;
	m_pDriver = NULL;
	m_pResponse = NULL;
	m_pImpedance = NULL;

}

ZpDriver::~ZpDriver()
{
}

#ifdef _DEBUG
void ZpDriver::AssertValid() const
{
	ZpPassive::AssertValid();
}

void ZpDriver::Dump(CDumpContext& dc) const
{
	ZpPassive::Dump(dc);
	dc << "Driver";
}
#endif //_DEBUG



void ZpDriver::Serialize(CArchive& ar)
{

	ZpPassive::Serialize(ar);

	if ( ar.IsStoring())
		{
		ar << GetDriver();
		ar << (WORD )DoChart();
		ar << (WORD )IsOutOfPhase();
		ar << GetOffset();
		}
	else
		{
		DWORD dw;
		ar >> dw; SetDriver( dw);
		WORD w;
		ar >> w; SetDoChart( w);
		ar >> w; SetOutOfPhase( w);
		if ( 288 != GetSchema())
			{
			ar >> m_fOffset;
			}
		else
			m_fOffset = 0.0f;

		m_pImpedance = NULL;
		m_pResponse = NULL;

		}

}

int		ZpDriver::ImportLine( LPCSTR /* szLine */)
{
	return 0;
}

int		ZpDriver::ExportLine( LPSTR szLine)
{
float fval;
CString csval;

	fval = FormatValue((float )GetValue(), csval);
	sprintf( szLine, "X_%s $N_%04d $N_%04d %.2f%s %d %d %d\n", 
		GetName(), GetNode(0), GetNode(1),
		fval, (LPCSTR )csval, GetPosition(0), GetPosition(1),
		GetOrientation() ? 1 : 0);

	szLine[0] = 'D';

	return 0;
}



void ZpDriver::InitPointers( CObject *pcSource)
{
CFolder *pcs = (CFolder *)pcSource;

	if ( m_dwDriver)
		{
		m_pDriver = (CDriver *)pcs->GetItem( m_dwDriver);
		if ( m_pDriver)
			{
			m_pResponse = (CDataSet *)pcs->GetItem( m_pDriver->GetResponse());
			m_pImpedance = (CDataSet *)pcs->GetItem( m_pDriver->GetImpedance());
			}
		}
}


/////////////////////////////////////////////////////////////////////////////
//				ZpPassive Virtual Overrides by ZpDriver
/////////////////////////////////////////////////////////////////////////////

ZpPassive *ZpDriver::Duplicate()
{
ZpDriver *pnew = (ZpDriver *)ZpPassive::Duplicate();

	if ( pnew)
		{
		pnew->SetDriver( GetDriver());
		pnew->SetDoChart(	DoChart() );
		pnew->SetOutOfPhase( IsOutOfPhase());
		pnew->SetOffset( GetOffset());
		}

	return pnew;
}

void ZpDriver::GetRange(CNamed *pInfo,  float *pfStart, float *pfDelta)
{
	if ( m_dwDriver)
		{
		CDriver *pdrive = (CDriver *)pInfo->FindByID( m_dwDriver);
		if ( pdrive)
			{
			CDataSet *pRes = (CDataSet *)pInfo->FindByID( pdrive->GetResponse());

			if ( pRes)
				{
				*pfStart = pRes->GetStart();
				*pfDelta = pRes->GetDelta();
				return;
				}
			}
		}


	*pfStart = 10.0f;
	*pfDelta = 1.0f;

}

int ZpDriver::GetCount( CNamed *pInfo )
{
	if ( m_dwDriver)
		{
		CDriver *pdrive = (CDriver *)pInfo->FindByID( m_dwDriver);
		if ( pdrive)
			{
			CDataSet *pRes = (CDataSet *)pInfo->FindByID( pdrive->GetResponse());
			if ( pRes)
				return pRes->GetCount();
			}
		}

	return 0;

}

BOOL ZpDriver::IsNotValid( CFolder *pRoot, BOOL bShow)
{
	if ( ! m_dwDriver)
		return 1;

CDriver *pdrive = (CDriver *)pRoot->FindByID( m_dwDriver);
CString cserr;

		if ( ! pdrive)
			return 2;			// ?????

		if ( (!pdrive->GetResponse()) || pdrive->ValidateResponse(rsResponse))
			{
			if ( bShow)
				{
				AfxFormatString1( cserr, IDS_NOFREQ, pdrive->GetName());
				AfxMessageBox( (LPCSTR )cserr);
				}
			return 3;
			}
		if ( (!pdrive->GetImpedance()) || pdrive->ValidateResponse(rsImpedance))
			{
			if ( bShow)
				{
				AfxFormatString1( cserr, IDS_NOIMP, pdrive->GetName());
				AfxMessageBox( (LPCSTR )cserr);
				}
			return 4;
			}

	return 0;

}

void ZpDriver::Impedance(ZComplex& ZcOut, double dFreq)
{
float fphase, famp;
float ffreq = (float )dFreq;
CDataSet *cdr = (CDataSet *)m_pImpedance;

	if( ! cdr)
		return;

	fphase = cdr->PhaseValueAt( ffreq);
	famp = cdr->DataValueAt( ffreq, 1);

	ZcOut.SetPolar( famp, fphase);
}

double ZpDriver::ResponseDb( double dFreq)
{
CDataSet *cdr = (CDataSet *)m_pResponse;

	return cdr->DataValueAt( (float )dFreq, 0);		// in dB
}


void ZpDriver::Response(ZComplex& ZcOut, double dFreq)
{
float fphase, famp;
float ffreq = (float )dFreq;
CDataSet *cdr = (CDataSet *)m_pResponse;

	if( ! cdr)
		return;

	fphase = cdr->PhaseValueAt( ffreq);
	famp = cdr->DataValueAt( ffreq, 1);

	if ( IsOutOfPhase())
		{
		if ( fphase > 0)
			fphase -= 180.0f;
		else
			fphase += 180.0f;
		}

	{						//		delay the response by appropriate angle for offset
	double c = 34466.90;		// speed of sound in air, per JBL SpeakerShop (cm/s)
							// now add in the new amount of phase (time * frequency == total cycles)
	fphase += (float )(360 * (GetOffset() / c) * dFreq );
	
	}

	ZcOut.SetPolar( famp, fphase);

}



void ZpDriver::DoDraw( CDC *pcDC, LPCRECT lpcrWhere)
{
CGdiObject *poldpen = pcDC->SelectStockObject( BLACK_PEN);
POINT ptstart;
POINT ptpoly[8] = { {0,0}, {0,-TDRES}, {TDRES,0}, 
					{-TDRES,-TDRES}, {2*TDRES,0}, {-TDRES,TDRES}, {TDRES,0}, 
					{0, TDRES+1} };
			// the plus/minus signs
int ndres = (DRES+1)/2;		// a half size guy
int ndr2 = 2 * ndres;
POINT ptpolyplus[5] = { {TDRES,-DRES}, {0,ndr2}, {0,-ndres}, {-ndres,0}, {ndr2+1,0} };

	{
	CRect rcdraw(  0, -2*TDRES, 2*TDRES, 2*TDRES);

		AdjustDrawRect( rcdraw, lpcrWhere);
	}

	ptstart.x = lpcrWhere->left + GetPosition(0);
	ptstart.y = lpcrWhere->top + GetPosition(1);

	move_Poly( ptpoly, 8, ptstart, GetOrientation());
	pcDC->Polyline( ptpoly,  8);
				// draw the plus-minus
	move_Poly( ptpolyplus, 5, ptstart, GetOrientation());

	if ( m_bOutOfPhase)			// draw a minus
		pcDC->Polyline( ptpolyplus, 2);
	else
		pcDC->Polyline( ptpolyplus, 5);
				// draw the highlight
	DrawHighlight( pcDC);

	DrawLabels( pcDC, lpcrWhere);

	pcDC->SelectObject( poldpen);

}


POINT ZpDriver::GetDrawSize()
{
	return CPoint(2*TDRES,0);
}


/////////////////////////////////////////////////////////////////////////////
//				ZpDriver Ends
/////////////////////////////////////////////////////////////////////////////

