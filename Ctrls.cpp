// ctrls.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "ctrls.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define USE_COLORS 16

static COLORREF clr_Use[USE_COLORS] = { RGB(0,0,0), RGB(0xff,0xff,0xff),
						RGB(0xff,0,0), RGB(0,0xff,0), RGB(0,0,0xff), RGB(0xff,0xff,0), RGB(0xff,0,0xff), RGB(0,0xff,0xff),
						RGB(0x80,0,0), RGB(0,0x80,0), RGB(0,0,0x80), RGB(0x80,0x80,0), RGB(0x80,0,0x80), RGB(0,0x80,0x80),
						RGB(0x80,0x80,0x80), RGB(0x40,0x40,0x40) };

static int		style_Use[5] = { PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT };

/////////////////////////////////////////////////////////////////////////////
// CColorBox

CColorBox::CColorBox()
{
}

CColorBox::~CColorBox()
{
}


/////////////////////////////////////////////////////////////////////////////
// CColorBox message handlers
/////////////////////////////////////////////////////////////////////////////
// CLineStyleBox

CLineStyleBox::CLineStyleBox()
{
}

CLineStyleBox::~CLineStyleBox()
{
}


/////////////////////////////////////////////////////////////////////////////
// CLineStyleBox message handlers
/////////////////////////////////////////////////////////////////////////////
// CLineWidthBox

CLineWidthBox::CLineWidthBox()
{
}

CLineWidthBox::~CLineWidthBox()
{
}


/////////////////////////////////////////////////////////////////////////////
// CLineWidthBox message handlers

void CLineWidthBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if( lpDrawItemStruct->itemAction != ODA_DRAWENTIRE)
		{
		return;
		}

//	SetCurrentSel( lpDrawItemStruct->itemID);

CDC *pdc = CDC::FromHandle( lpDrawItemStruct->hDC);		// temp cdc
CRect rcr( lpDrawItemStruct->rcItem);
CBrush cblack( RGB(0,0,0));
CPen cp( PS_SOLID, lpDrawItemStruct->itemID+1, RGB(0,0,0));
CPen *coldp;
CBrush cb( RGB(0xff,0xff,0xff));			// white brush

				// code to draw the specified item
	int nmid = (rcr.top + rcr.bottom)/2;

	rcr.InflateRect(-2,-2);
	pdc->FillRect( rcr, &cb);
	pdc->FrameRect( rcr, &cblack);

	coldp = pdc->SelectObject( &cp);

	rcr.InflateRect(-4,0);
	pdc->MoveTo( rcr.left, nmid);
	pdc->LineTo( rcr.right, nmid);

	pdc->SelectObject( coldp);
	
}

void CLineWidthBox::InitDialog(CComboBox *pBox)
{
int i;
int n;

	CzComboBox::InitDialog( pBox);

		for ( i=0; i<NLINEWIDTH; i++)
			n = m_pBox->AddString(" ");
}

void CLineStyleBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if( lpDrawItemStruct->itemAction != ODA_DRAWENTIRE)
		{
		return;
		}


//	SetCurrentSel( lpDrawItemStruct->itemID);

CDC *pdc = CDC::FromHandle( lpDrawItemStruct->hDC);		// temp cdc
CRect rcr( lpDrawItemStruct->rcItem);
CBrush cblack( RGB(0,0,0));
int n = lpDrawItemStruct->itemID;
if ( n < 0)
	n = 0;			// the unselected case

CPen cp( style_Use[n], 1, RGB(0,0,0));
CPen *coldp;
CBrush cb( RGB(0xff,0xff,0xff));			// white brush

				// code to draw the specified item
	int nmid = (rcr.top + rcr.bottom)/2;

	rcr.InflateRect(-2,-2);
	pdc->FillRect( rcr, &cb);
	pdc->FrameRect( rcr, &cblack);

	coldp = pdc->SelectObject( &cp);

	int noldmode = pdc->SetBkMode( TRANSPARENT);		// so lines draw correctly
	rcr.InflateRect(-2,0);

	pdc->MoveTo( rcr.left, nmid-1);
	pdc->LineTo( rcr.right, nmid-1);
	pdc->MoveTo( rcr.left, nmid);
	pdc->LineTo( rcr.right, nmid);
	pdc->MoveTo( rcr.left, 1+nmid);
	pdc->LineTo( rcr.right, 1+nmid);

	pdc->SelectObject( coldp);
	pdc->SetBkMode( noldmode);
	
}

int  CLineWidthBox::GetSelection( void)
{
	return (1 + m_nSelection);
}


int  CLineWidthBox::SetSelection( int nNew)
{
	m_nSelection = nNew - 1;
	return m_pBox->SetCurSel( nNew-1);
}

int  CLineWidthBox::IdxToValue( int nIdx)
{
	return (1 + nIdx);
}

int  CLineWidthBox::ValueToIdx( int nValue)
{
	return nValue - 1;
}



// ---------------------------------------------------------------------------

void CLineStyleBox::InitDialog(CComboBox *pBox)
{
int i;

	CzComboBox::InitDialog( pBox);

		for ( i=0; i<NLINESTYLE; i++)
			m_pBox->AddString(" ");
}


int CLineStyleBox::SetSelection( int nStyle)
{
int i;

	for ( i=0; i < NLINESTYLE; i++)
		if ( nStyle == style_Use[i])
			break;
	if ( i == NLINECOLOR)
		i = 0;			// random choice...

	m_nSelection = i;
	return m_pBox->SetCurSel( i);
}

int  CLineStyleBox::GetSelection( void)
{
	return style_Use[m_nSelection];
}

int  CLineStyleBox::IdxToValue( int nIdx)
{
	return style_Use[nIdx];
}

int  CLineStyleBox::ValueToIdx( int nValue)
{
int i;

	for ( i=0; i < NLINESTYLE; i++)
		if ( nValue == style_Use[i])
			break;
	if ( i == NLINECOLOR)
		i = 0;			// random choice...

	return i;
}




// ---------------------------------------------------------------------------

void CColorBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if( lpDrawItemStruct->itemAction != ODA_DRAWENTIRE ||
		lpDrawItemStruct->itemID >= USE_COLORS)		// we have a ridiculous first value
		{
		return;
		}

//	SetCurrentSel( lpDrawItemStruct->itemID);

CDC *pdc = CDC::FromHandle( lpDrawItemStruct->hDC);		// temp cdc
CRect rcr( lpDrawItemStruct->rcItem);
CBrush cblack( RGB(0,0,0));

					// code to draw the specified item
	CBrush cb( clr_Use[lpDrawItemStruct->itemID]);

	rcr.InflateRect(-2,-2);
	pdc->FillRect( rcr, &cb);
	pdc->FrameRect( rcr, &cblack);
	
}

void CColorBox::InitDialog(CComboBox *pBox)
{
int i;

	CzComboBox::InitDialog( pBox);

		for ( i=0; i<NLINECOLOR; i++)
			m_pBox->AddString(" ");
}

int CColorBox::SetSelection( COLORREF rgbUse)
{
int i;

	for ( i=0; i < NLINECOLOR; i++)
		if ( rgbUse == clr_Use[i])
			break;
	if ( i == NLINECOLOR)
		i = 0;			// random choice...

	m_nSelection = i;
	return m_pBox->SetCurSel( i);
}

COLORREF  CColorBox::IdxToValue( int nIdx)
{
	return clr_Use[nIdx];
}

int  CColorBox::ValueToIdx( COLORREF nRgb)
{
int i;

	for ( i=0; i < NLINECOLOR; i++)
		if ( nRgb == clr_Use[i])
			break;
	if ( i == NLINECOLOR)
		i = 0;			// random choice...

	return i;
}


COLORREF  CColorBox::GetSelection( void)
{
	return clr_Use[m_nSelection];
}


/////////////////////////////////////////////////////////////////////////////
// CzComboBox

CzComboBox::CzComboBox()
{
	m_nSelection = 0;
	m_pBox = NULL;
}

CzComboBox::~CzComboBox()
{
}


/////////////////////////////////////////////////////////////////////////////
// CzComboBox message handlers

void CzComboBox::SetCurrentSel( int nSelection)
{
	m_nSelection = nSelection;
}


void CzComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
				// code to determine the size of specified item
	lpMeasureItemStruct->itemHeight = 20;	
	
}


//void CzComboBox::OnEditchange() 
//{
//	m_nSelection = m_pBox->GetCurSel();
	
//}

void CzComboBox::InitDialog(CComboBox *pBox)
{
	m_pBox = pBox;
}


void CzComboBox::DrawItem(LPDRAWITEMSTRUCT ) 
{

}


