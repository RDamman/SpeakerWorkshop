// SplitBar.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "SplitBar.h"

#include "TrueDialogBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CString	  cssplit_Name("");

/////////////////////////////////////////////////////////////////////////////
// CSplitterBar

CSplitterBar::CSplitterBar()
{
	m_bDragging = FALSE;
}

CSplitterBar::~CSplitterBar()
{
}


BEGIN_MESSAGE_MAP(CSplitterBar, CWnd)
	//{{AFX_MSG_MAP(CSplitterBar)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSplitterBar message handlers

void	CSplitterBar::Create(CWnd *pParent, RECT& rcout, int nID)
{
	if ( 1 > cssplit_Name.GetLength())
		{
		HCURSOR hsplit = AfxGetApp()->LoadCursor( IDC_SPLIT);
		cssplit_Name = AfxRegisterWndClass( CS_PARENTDC, hsplit);
		}

	CWnd::Create(cssplit_Name, "zSplitBar", WS_VISIBLE | WS_CHILD, rcout, pParent, nID, NULL);
}

void CSplitterBar::OnPaint() 
{
CPaintDC dc(this); // device context for painting
CRect rc;
int nstart;

	GetClientRect( rc);	

CGdiObject *coldbrush = dc.SelectStockObject( LTGRAY_BRUSH);

	dc.PatBlt( rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);

	nstart = rc.left + 2;

	dc.SelectStockObject( WHITE_BRUSH);
	dc.PatBlt( nstart++, rc.top, 1, rc.Height(), PATCOPY);

	dc.SelectStockObject( LTGRAY_BRUSH);
	dc.PatBlt( nstart++, rc.top, 1, rc.Height(), PATCOPY);

	nstart += 2;

	dc.SelectStockObject( DKGRAY_BRUSH);
	dc.PatBlt( nstart++, rc.top, 1, rc.Height(), PATCOPY);

	dc.SelectStockObject( BLACK_BRUSH);
	dc.PatBlt( nstart, rc.top, 1, rc.Height(), PATCOPY);

	dc.SelectObject( coldbrush);

	// Do not call CWnd::OnPaint() for painting messages
}

void CSplitterBar::draw_SplitBar( CPoint& cPoint)
{
CRect rcsplit;
CControlBar *pparent = (CControlBar *)GetParent();
CDC *pdc;
CPoint cp = cPoint;
CWnd *pframe = pparent->GetDockingFrame();
CBrush pbrush;
CGdiObject *poldbrush;

	ASSERT_KINDOF( CControlBar, pparent);
	ASSERT_KINDOF( CFrameWnd, pframe);

	pdc = pframe->GetDC();			// use the parent to draw into
	ClientToScreen( &cp);
	pframe->ScreenToClient( &cp);	// convert the X location to parent coords

					// make rcsplit the current client rect in parent coords
	GetClientRect( rcsplit);		// what size to draw
	ClientToScreen( rcsplit);
	pframe->ScreenToClient( rcsplit);

					// draw it
	pbrush.CreateStockObject( GRAY_BRUSH);
	poldbrush = pdc->SelectObject( &pbrush);
	pdc->PatBlt( cp.x-1, rcsplit.top, 3, rcsplit.Height(), PATINVERT);
	pdc->SelectObject( poldbrush);
	pframe->ReleaseDC( pdc);
	pbrush.DeleteObject();


}


void CSplitterBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
				// start the drag operation
	SetCapture();

	m_bDragging = TRUE;

	m_pLast = point;
	m_pFirst = point;

	draw_SplitBar( point);
	
	CWnd::OnLButtonDown(nFlags, point);
}



void CSplitterBar::OnMouseMove(UINT nFlags, CPoint point) 
{
					// if we're dragging, rubber band the splitbar
	if ( m_bDragging)
		{
		draw_SplitBar( m_pLast);
		m_pLast = point;
		draw_SplitBar( point);
		}
	
	CWnd::OnMouseMove(nFlags, point);
}

void CSplitterBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
CTrueDialogBar *pparent = (CTrueDialogBar *)GetParent();

				// if we're dragging, resize the window
	if ( m_bDragging)
		{
		ReleaseCapture();
		draw_SplitBar( m_pLast);
		m_bDragging = FALSE;
		CSize cs = pparent->GetSize();
		if ( IsLeft())
			cs.cx += point.x - m_pFirst.x;
		else
			cs.cx -= point.x - m_pFirst.x;
		pparent->SetSize( cs);
		}
	
	CWnd::OnLButtonUp(nFlags, point);
}



BOOL	CSplitterBar::IsVertical( void)
{
RECT rc;

	GetClientRect( &rc);
	return ( rc.right > rc.bottom);
}

BOOL	CSplitterBar::IsLeft( void)
{
CControlBar *pparent;

	pparent = (CControlBar *)GetParent();
	return ( CBRS_ALIGN_LEFT == (CBRS_ALIGN_LEFT & pparent->GetBarStyle()) );

}

BOOL	CSplitterBar::IsTop( void)
{
CControlBar *pparent;

	pparent = (CControlBar *)GetParent();
	return ( CBRS_ALIGN_TOP == (CBRS_ALIGN_TOP & pparent->GetBarStyle()) );

}


int CSplitterBar::GetWidth()
{
	return 11;
}
