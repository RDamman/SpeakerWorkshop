// childfrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "audtest.h"

#include "childfrm.h"

//#include "named.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	SetTarget( 0, ":Root");
}

CChildFrame::~CChildFrame()
{
}

//BOOL CChildFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/,	CCreateContext* pContext)
//{
//	return m_wndSplitter.Create( this,
//		2, 2,                 // TODO: adjust the number of rows, columns
//		CSize( 10, 10 ),      // TODO: adjust the minimum pane size
//		pContext );
//}

/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

/////////////////////////////////////////////////////////////////////////////
// CChildFrame custom operations

DWORD CChildFrame::GetTarget()
{
	return m_dwTarget;
}

void CChildFrame::SetTarget( DWORD dwNew, LPCSTR lpszTitle)
{
	m_dwTarget = dwNew;
	m_csTitle = lpszTitle;
	if ( GetSafeHwnd())
		SetWindowText( m_csTitle);	
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class

	cs.style &= ~FWS_ADDTOTITLE;			// let me create the window titles
	cs.lpszName = (LPCSTR )m_csTitle;		// ???

	return CMDIChildWnd::PreCreateWindow(cs);
}

