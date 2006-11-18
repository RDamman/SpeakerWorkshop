// CG: This file was added by the Splash Screen component.
// Splash.cpp : implementation file
//

#include "stdafx.h"			// e. g. stdafx.h
#include "resource.h"		// e.g. resource.h

#include "dibapi.h"			// here's the dib code from diblook sample

#include "Splash.h"			// e.g. splash.h

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


HDIB LoadResourceBitmap(UINT idBitmap, CPalette& cPalette)
{
HRSRC  hRsrc;
HGLOBAL hGlobal, hTemp;
DWORD dwSize;
LPSTR lpRes, lpNew;
HINSTANCE hinst = AfxGetInstanceHandle();
 
    hRsrc = FindResource(hinst, MAKEINTRESOURCE( idBitmap), RT_BITMAP);

    if ( !hRsrc)
		return NULL;

	hTemp = LoadResource(hinst, hRsrc);
	dwSize = SizeofResource(hinst, hRsrc);
	lpRes = (LPSTR )LockResource(hTemp);

	hGlobal = GlobalAlloc(GHND, dwSize);
	lpNew = (LPSTR )GlobalLock(hGlobal);
	memcpy(lpNew, lpRes, dwSize);
	UnlockResource(hTemp);

	GlobalUnlock( hGlobal);

	::CreateDIBPalette( (HDIB )hGlobal, &cPalette);
    return ( (HDIB )hGlobal);
}



/////////////////////////////////////////////////////////////////////////////
//   Splash Screen class

BOOL CSplashWnd::c_bShowSplashWnd = FALSE;
CSplashWnd* CSplashWnd::c_pSplashWnd = NULL;


CSplashWnd::CSplashWnd() : m_cPalette()
{
}

CSplashWnd::~CSplashWnd()
{
	// Clear the static window pointer.
	ASSERT(c_pSplashWnd == this);
	c_pSplashWnd = NULL;
	if ( m_hSplashDib)
		{
		GlobalFree( m_hSplashDib);
		m_hSplashDib = NULL;
		}
}

BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	//{{AFX_MSG_MAP(CSplashWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSplashWnd::EnableSplashScreen(BOOL bEnable /*= TRUE*/)
{
	c_bShowSplashWnd = bEnable;
}

void CSplashWnd::ShowSplashScreen(CWnd* pParentWnd /*= NULL*/)
{
	if (!c_bShowSplashWnd || c_pSplashWnd != NULL)
		return;

	// Allocate a new splash screen, and create the window.
	c_pSplashWnd = new CSplashWnd;
	if (!c_pSplashWnd->Create(pParentWnd))
		delete c_pSplashWnd;
	else
		c_pSplashWnd->UpdateWindow();
}

void CSplashWnd::PreTranslateAppMessage(MSG* pMsg)
{
	if (c_pSplashWnd == NULL)
		return;

	// If we get a keyboard or mouse message, hide the splash screen.
	if (pMsg->message == WM_KEYDOWN ||
	    pMsg->message == WM_SYSKEYDOWN ||
	    pMsg->message == WM_LBUTTONDOWN ||
	    pMsg->message == WM_RBUTTONDOWN ||
	    pMsg->message == WM_MBUTTONDOWN ||
	    pMsg->message == WM_NCLBUTTONDOWN ||
	    pMsg->message == WM_NCRBUTTONDOWN ||
	    pMsg->message == WM_NCMBUTTONDOWN)
	{
		c_pSplashWnd->HideSplashScreen();
	}
}

BOOL CSplashWnd::Create(CWnd* pParentWnd /*= NULL*/)
{
int nwidth, nheight;

	m_hSplashDib = LoadResourceBitmap(IDB_SPLASH256, m_cPalette);

	if (! m_hSplashDib)
		return FALSE;

	{
	LPSTR lpb = (LPSTR )GlobalLock( m_hSplashDib);

		if ( lpb)
			{
			nwidth = ::DIBWidth( lpb);
			nheight = ::DIBHeight( lpb);
			GlobalUnlock( m_hSplashDib);
			}
		else 
			{
			GlobalFree( m_hSplashDib);
			return FALSE;
			}
	}

	return CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, nwidth, nheight, pParentWnd->GetSafeHwnd(), NULL);
}

void CSplashWnd::HideSplashScreen()
{
	// Destroy the window, and update the mainframe.
	DestroyWindow();
//	if ( IsWindow(AfxGetMainWnd()->m_hWnd))
//		AfxGetMainWnd()->UpdateWindow();
}

void CSplashWnd::PostNcDestroy()
{
	// Free the C++ class.
	delete this;
}

int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Center the window.
	CenterWindow( GetDesktopWindow());

	// Set a timer to destroy the splash screen.
	// very short if debug
#ifdef _DEBUG
	SetTimer(1, 100, NULL);
#else
	SetTimer(1, 1500, NULL);
#endif

	return 0;
}

void CSplashWnd::OnPaint()
{
CPaintDC dc(this);

//	BITMAP bm;
//	m_bitmap.GetBitmap(&bm);

	// Paint the image.
//	CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
//	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
//	dcImage.SelectObject(pOldBitmap);


   {
   HDIB hdib = m_hSplashDib;
   RECT rcdraw;

	rcdraw.left = rcdraw.top = 0;

	if (hdib != NULL)
		{
		LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) hdib);
		rcdraw.right = (int) ::DIBWidth(lpDIB);         // Size of DIB - x
		rcdraw.bottom = (int) ::DIBHeight(lpDIB);        // Size of DIB - y
		::GlobalUnlock((HGLOBAL) hdib);
		}
 

   ::PaintDIB( dc.m_hDC, &rcdraw, hdib, &rcdraw, &m_cPalette);
//   ::PaintDIB( dc.m_hDC, &rcdraw, hdib, &rcdraw, NULL);

   }
 
}

void CSplashWnd::OnTimer(UINT nIDEvent)
{
	// Destroy the splash screen window.
	HideSplashScreen();
}



