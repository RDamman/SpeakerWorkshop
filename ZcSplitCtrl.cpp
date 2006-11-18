// ZcSplitCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "ZcSplitCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static CString	  csclass_Name(cNullString);


/////////////////////////////////////////////////////////////////////////////
// ZcSplitCtrl

ZcSplitCtrl::ZcSplitCtrl()
{
	m_nOrient = 0;		// vertical by default
	if ( 1 > csclass_Name.GetLength())
		{
		csclass_Name = AfxRegisterWndClass( CS_PARENTDC, LoadCursor(NULL,IDC_SIZEWE), (HBRUSH )GetStockObject( GRAY_BRUSH));
		}

}

ZcSplitCtrl::~ZcSplitCtrl()
{
}


BEGIN_MESSAGE_MAP(ZcSplitCtrl, CWnd)
	//{{AFX_MSG_MAP(ZcSplitCtrl)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZcSplitCtrl message handlers

void ZcSplitCtrl::OnPaint() 
{
CPaintDC dc(this); // device context for painting
RECT rcclient;
int xsize, ysize;

	GetClientRect( &rcclient);
	xsize = rcclient.right - rcclient.left;
	ysize = rcclient.bottom - rcclient.top;
	
	// TODO: Add your message handler code here
CPen *cpen = new CPen( PS_SOLID, 1, RGB(0,0,0));
CPen *pold;
		pold = dc.SelectObject( cpen);
		dc.MoveTo(0,0);
		dc.LineTo(0,ysize);
		dc.SelectObject( pold);
		delete cpen;
		cpen = new CPen( PS_SOLID, 1, RGB(0xff,0xff,0xff));
		dc.SelectObject( cpen);
		dc.MoveTo(xsize-1,0);
		dc.LineTo(xsize-1,ysize);
		dc.SelectObject( pold);
		delete cpen;

	// Do not call CWnd::OnPaint() for painting messages
}

void ZcSplitCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnMouseMove(nFlags, point);
}

void ZcSplitCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnLButtonUp(nFlags, point);
}

void ZcSplitCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnLButtonDown(nFlags, point);
}

BOOL ZcSplitCtrl::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
char szname[100];
static DWORD dw_size = 0;

	sprintf(szname, "zSplit%d", dw_size++);

	return CWnd::Create(csclass_Name, szname, WS_VISIBLE | WS_CHILD, rect, pParentWnd, nID, pContext);
}
