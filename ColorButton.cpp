// ColorButton.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "ColorButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorButton

CColorButton::CColorButton()
{
}

CColorButton::~CColorButton()
{
}


BEGIN_MESSAGE_MAP(CColorButton, CButton)
	//{{AFX_MSG_MAP(CColorButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorButton message handlers

void CColorButton::SetColor(COLORREF clrSet)
{
	m_rgbColor = clrSet;
}

void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	CBrush cbr( m_rgbColor);
	CDC *pdc;
	pdc = CDC::FromHandle( lpDrawItemStruct->hDC);		// make the cdc appropriate

	pdc->FillRect(&lpDrawItemStruct->rcItem, &cbr);
	
}

COLORREF CColorButton::EditColor()
{
CColorDialog cdlg( m_rgbColor, CC_FULLOPEN, this);

	if ( IDOK == cdlg.DoModal())
		m_rgbColor = cdlg.GetColor();

	return m_rgbColor;

}

COLORREF CColorButton::GetColor()
{
	return m_rgbColor;
}
/////////////////////////////////////////////////////////////////////////////
// CColorStatic

CColorStatic::CColorStatic()
{
}

CColorStatic::~CColorStatic()
{
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	//{{AFX_MSG_MAP(CColorStatic)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorStatic message handlers
void CColorStatic::SetColor(COLORREF clrSet)
{
	m_rgbColor = clrSet;
}

#if 0
void CColorStatic::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	CBrush cbr( m_rgbColor);
	CDC *pdc;
	pdc = CDC::FromHandle( lpDrawItemStruct->hDC);		// make the cdc appropriate

	pdc->FillRect(&lpDrawItemStruct->rcItem, &cbr);
	
}
#endif

COLORREF CColorStatic::EditColor()
{
CColorDialog cdlg( m_rgbColor, CC_FULLOPEN, this);

	if ( IDOK == cdlg.DoModal())
		m_rgbColor = cdlg.GetColor();

	return m_rgbColor;

}

COLORREF CColorStatic::GetColor()
{
	return m_rgbColor;
}

HBRUSH CColorStatic::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CStatic::OnCtlColor(pDC, pWnd, nCtlColor);
	
	pDC->SetTextColor( m_rgbColor);	

	return hbr;
}

void CColorStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CString csout;
	
	dc.SetBoundsRect( &dc.m_ps.rcPaint, DCB_ACCUMULATE | DCB_ENABLE);
	dc.SetTextColor( m_rgbColor);
	GetWindowText( csout);
	dc.TextOut( 0, 0, csout);
	
	// Do not call CStatic::OnPaint() for painting messages
}

/////////////////////////////////////////////////////////////////////////////
// CColorEdit

CColorEdit::CColorEdit()
{
}

CColorEdit::~CColorEdit()
{
}


BEGIN_MESSAGE_MAP(CColorEdit, CEdit)
	//{{AFX_MSG_MAP(CColorEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorEdit message handlers
void CColorEdit::SetColor(COLORREF clrSet)
{
	m_rgbColor = clrSet;
}

COLORREF CColorEdit::EditColor()
{
CColorDialog cdlg( m_rgbColor, CC_FULLOPEN, this);

	if ( IDOK == cdlg.DoModal())
		m_rgbColor = cdlg.GetColor();

	return m_rgbColor;

}

COLORREF CColorEdit::GetColor()
{
	return m_rgbColor;
}


