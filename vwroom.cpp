// audtevw.cpp : implementation of the CAudRoomView class
//

#include "stdafx.h"
#include "audtest.h"

#include "audtedoc.h"
#include "vwRoom.h"


#include "generat.h"
#include "dataset.h"

#include "dlgrenam.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudRoomView

IMPLEMENT_DYNCREATE(CAudRoomView, CAudtestView)

BEGIN_MESSAGE_MAP(CAudRoomView, CAudtestView)
	//{{AFX_MSG_MAP(CAudRoomView)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CAudtestView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CAudtestView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudRoomView construction/destruction

CAudRoomView::CAudRoomView()
{
	// TODO: add construction code here

}

CAudRoomView::~CAudRoomView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CAudRoomView drawing

void CAudRoomView::OnDraw(CDC* )
{
CAudtestDoc* pDoc = GetDocument();

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CAudRoomView printing

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CAudRoomView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CAudRoomView diagnostics

#ifdef _DEBUG
void CAudRoomView::AssertValid() const
{
	CAudtestView::AssertValid();
}

void CAudRoomView::Dump(CDumpContext& dc) const
{
	CAudtestView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAudRoomView message handlers

void CAudRoomView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CAudtestView::OnUpdate(pSender, lHint, pHint);
}

