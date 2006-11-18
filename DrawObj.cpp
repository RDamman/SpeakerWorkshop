
// chart.cpp : implementation of the CSubChartArray classes
//


#include "stdafx.h"
#include "audtest.h"

//#include "named.h"
//#include "audtedoc.h"

#include "DrawObj.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CDrawObj, CObject, VERSIONABLE_SCHEMA | 222)


/////////////////////////////////////////////////////////////////////////////
// CDrawObj construction/destruction

CDrawObj::CDrawObj()
{

	m_bIsVisible = TRUE;					// do we draw this when asked?
	m_bIsHighlighted = FALSE;				// is it selected ?
	::SetRect(&m_rcDrawn, 0,0,1,1);			// where it was drawn
}

CDrawObj::~CDrawObj()
{

}

/////////////////////////////////////////////////////////////////////////////
// CDrawObj serialization

void CDrawObj::Serialize(CArchive& ar)
{
WORD w;

	if (! ar.IsStoring())
		m_nSchema = ar.GetObjectSchema();

	CObject::Serialize( ar);

	if (ar.IsStoring())
		{
		w = (WORD )IsVisible();
		ar << w;
		}
	else
		{
		ar >> w;
		SetVisible( w);
		}
}


CDrawObj &CDrawObj::operator=(const CDrawObj &cIn)
{
	m_bIsVisible = cIn.m_bIsVisible;
	m_bIsHighlighted = cIn.m_bIsHighlighted;
	m_rcDrawn = cIn.m_rcDrawn;

	return *this;
}


/////////////////////////////////////////////////////////////////////////////
// CDrawObj operations


void CDrawObj::DoDraw( CDC *, LPCRECT )
{

}


void CDrawObj::DrawHighlight( CDC *pDC)
{

	if ( IsHighlighted() )			// highlighted....draw a box
		{
		pDC->DrawFocusRect( &m_rcDrawn);
		}

}


BOOL CDrawObj::HitTest( CPoint cPt, UINT *pnFlags)
{
	if ( ::PtInRect( &m_rcDrawn, cPt) )
		{
		if ( pnFlags)
			*pnFlags = DRW_INBOX;
		return TRUE;
		}

	if ( pnFlags)
		*pnFlags = DRW_OUTBOX;
	return FALSE;

}

IMPLEMENT_SERIAL(CObjColor, CObject, VERSIONABLE_SCHEMA | 223)


/////////////////////////////////////////////////////////////////////////////
// CObjColor construction/destruction
/////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
CObjColor::CObjColor()
{
	// TODO: add one-time construction code here
	m_clrRgb = RGB(0,0,0);
	m_nWidth = 1;
	m_nStyle = PS_SOLID;
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
CObjColor::CObjColor( COLORREF dwRgb, int nWidth, int nStyle)
{
	// TODO: add one-time construction code here
	m_clrRgb = dwRgb;
	m_nWidth = nWidth;
	m_nStyle = nStyle;
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
CObjColor::~CObjColor()
{

}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
CObjColor &CObjColor::operator=(const CObjColor &cIn)
{
	m_clrRgb = cIn.m_clrRgb;
	m_nWidth = cIn.m_nWidth;
	m_nStyle = cIn.m_nStyle;

 	return *this;
}



/////////////////////////////////////////////////////////////////////////////
// CObjColor serialization

void CObjColor::Serialize(CArchive& ar)
{
WORD w;

	CObject::Serialize( ar);

	if (ar.IsStoring())
		{						// storing code here
		ar << m_clrRgb;
		w = (WORD )m_nWidth;  ar << w;
		w = (WORD )m_nStyle;  ar << w;
		}
	else
		{						// loading code here 
		ar >> m_clrRgb;
		ar >> w; m_nWidth = (int )w;
		ar >> w; m_nStyle = (int )w;
		}
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
CPen *CObjColor::BuildPen()
{
CPen *cp = new CPen( m_nStyle, m_nWidth, m_clrRgb);

	return cp;
}

// ------------------------------------------------------------------------
//	Get the color definition
// ------------------------------------------------------------------------
ColorDefinition CObjColor::GetDefinition()
{
ColorDefinition cdef;

	cdef.m_clrRgb = GetColor();
	cdef.m_nStyle = GetStyle();
	cdef.m_nWidth = GetWidth();
	return cdef;
}

// ------------------------------------------------------------------------
//	SetDefinition - use a struct to set everything
// ------------------------------------------------------------------------
void CObjColor::SetDefinition( ColorDefinition *pDef)
{
	SetColor( pDef->m_clrRgb);
	SetStyle( pDef->m_nStyle);
	SetWidth( pDef->m_nWidth);
}


