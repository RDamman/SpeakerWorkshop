// Debug.cpp: implementation of the CDebug class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "audtest.h"
#include "Debug.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CString ctDebug = "Debug";
CString ctLevel = "Level";
CString ctWindow = "Window";
int cdID = 12323;

static CTopDebug m_DebugObj;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDebug::CDebug()
{
	m_nLine = 0;
}

CDebug::~CDebug()
{
}

BEGIN_MESSAGE_MAP(CDebug, CEdit)
	//{{AFX_MSG_MAP(CDebug)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDebug message handlers

/////////////////////////////////////////////////////////////////////////////
// CTopDebug

CTopDebug::CTopDebug() : m_wDebug()
{
	m_nDebugLevel = 0;
}

CTopDebug::~CTopDebug()
{
}


BEGIN_MESSAGE_MAP(CTopDebug, CWnd)
	//{{AFX_MSG_MAP(CTopDebug)
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTopDebug message handlers

CTopDebug * CTopDebug::GetDebugObj()
{
	return &m_DebugObj;
}

void CTopDebug::Init(CWnd *pParent)
{
CRect crbuild;
CString csw;
WINDOWPLACEMENT wndpl;

					// don't call SetDebugLevel, use the direct = assignment
					// we don't want the 0->Non-zero processing of the function
	m_nDebugLevel = AfxGetApp()->GetProfileInt( ctDebug, ctLevel, 0);
	m_pParent = pParent;

	if ( 0 == GetDebugLevel())		// are we debugging??
		return;						// nope, do nothing

	crbuild.SetRect( 0,0,100,100);
	if ( ! GetSafeHwnd())
		{
		Create( NULL, "Debugger", WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW, 
			crbuild, pParent, cdID);
		m_wDebug.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL, 
			crbuild, this, cdID+1);
		}
	csw = AfxGetApp()->GetProfileString( ctDebug, ctWindow, "");
	if ( csw && csw.GetLength())		// we have some
		{
		if ( 11 == sscanf( csw, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
			&wndpl.flags, &wndpl.length, 
			&wndpl.ptMinPosition.x, &wndpl.ptMinPosition.y, 
			&wndpl.ptMaxPosition.x, &wndpl.ptMaxPosition.y,
			&wndpl.rcNormalPosition.bottom, &wndpl.rcNormalPosition.top,
			&wndpl.rcNormalPosition.left, &wndpl.rcNormalPosition.right,
			&wndpl.showCmd))
			{
			wndpl.showCmd = SW_SHOWNORMAL;
			SetWindowPlacement( &wndpl);
			}
		}

	SetWindowText("Debug output");
	m_wDebug.SetWindowText("");
	BringWindowToTop();
	
}

int CTopDebug::GetDebugLevel()
{
	return m_nDebugLevel;
}

void CTopDebug::SetDebugLevel(int nNewLevel)
{
	AfxGetApp()->WriteProfileInt( ctDebug, ctLevel, nNewLevel);
	if ( m_nDebugLevel && !nNewLevel)
		DestroyWindow();			// we're gone
	else
	if ( nNewLevel && !m_nDebugLevel)
		Init( m_pParent);			// re init
	m_nDebugLevel = nNewLevel;
}


void CTopDebug::PrintString(LPCSTR lpcsOut)
{
CString csout;

	if ( ! GetSafeHwnd())
		return;				// no window to print to

	m_wDebug.AddLine( lpcsOut);

}

void CTopDebug::PrintTwo(LPCSTR lpcsOut, LPCSTR lpcsO2)
{
CString csout;
CString css;

	if ( ! GetSafeHwnd())
		return;				// no window to print to

	css.Format(lpcsOut, lpcsO2);

	m_wDebug.AddLine( css);		// print it

}

void CTopDebug::PrintInt(LPCSTR lpcsOut, int nOut)
{
CString csout;
CString css;

	if ( ! GetSafeHwnd())
		return;				// no window to print to

	css.Format(lpcsOut, nOut);

	m_wDebug.AddLine( css);		// print it

}

void CTopDebug::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
CRect crc;

	CWnd::OnWindowPosChanged(lpwndpos);
	if ( ! m_wDebug.GetSafeHwnd())
		return;
	
	// TODO: Add your message handler code here
	GetClientRect( crc);
	m_wDebug.SetWindowPos( &wndTop, 0, 0, crc.right, crc.bottom, SWP_SHOWWINDOW);
	
}

void CDebug::AddLine(LPCSTR lpNew)
{
CString csout;
CString csnew;
int nlength;

	if ( ! GetSafeHwnd())
		return;

	m_nLine++;

	GetWindowText( csout);		// get current text
	csnew.Format("\r\n%5d: %s", m_nLine, lpNew);
	csout += csnew;
	SetWindowText( csout);

	nlength = csout.GetLength() - 1;

	UpdateWindow();

	SetSel( nlength-1, nlength, FALSE);
//	SetSel( nlength-1, nlength, FALSE);
}

void CTopDebug::OnDestroy() 
{
	if ( GetSafeHwnd())
		{
		CString csout;
		WINDOWPLACEMENT wndpl;

			GetWindowPlacement( &wndpl);
			csout.Format( "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", 
				wndpl.flags, wndpl.length, 
				wndpl.ptMinPosition.x, wndpl.ptMinPosition.y, 
				wndpl.ptMaxPosition.x, wndpl.ptMaxPosition.y,
				wndpl.rcNormalPosition.bottom, wndpl.rcNormalPosition.top,
				wndpl.rcNormalPosition.left, wndpl.rcNormalPosition.right,
				wndpl.showCmd);
		AfxGetApp()->WriteProfileString( ctDebug, ctWindow, csout);
		}

	CWnd::OnDestroy();
	
}
