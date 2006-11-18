// treectrl.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "audtedoc.h"
#include "mainfrm.h"
#include "treectrl.h"

#include "dataSet.h"

#include "ctype.h"

#include "opitem.h"
#include "Clipbd.h"

#include "dlgRenam.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static CImageList cimg_ViewList;
static CImageList cimg_SmallViewList;
static CImageList cimg_DragCursors;

static CString	  csclass_Name(cNullString);

#define IDMSG_DONERIGHT ( WM_USER + 101)

IMPLEMENT_DYNAMIC( ZcTreeCtrl, CWnd)

/////////////////////////////////////////////////////////////////////////////
// ZcTreeCtrl

ZcTreeCtrl::ZcTreeCtrl() : m_cTree()
{
COLORREF crmask = RGB(192,192,192);

	m_cTree.m_pParent = this;

	if ( ! cimg_ViewList.GetSafeHandle())
		{
		cimg_ViewList.Create( IDB_TREELIST, 22, 24, crmask);
		}

	if ( ! cimg_SmallViewList.GetSafeHandle())
		{
		cimg_SmallViewList.Create( IDB_TREELIST1, 14, 24, crmask);
		}

	if ( ! cimg_DragCursors.GetSafeHandle())
		{
		cimg_DragCursors.Create( IDB_DRAGCURSORS, 32, 3, crmask);
		}

	if ( 1 > csclass_Name.GetLength())
		{
		csclass_Name = AfxRegisterWndClass( CS_DBLCLKS | CS_PARENTDC);
		}

	m_pcRoot = NULL;
	m_pNotifyWnd = NULL;
	m_bDragging = FALSE;
	m_nSelect = ntAny;
	m_nUom = uomAny;
	m_pImageList = NULL;
	m_cTargetRoot = NULL;
	m_bInRightClick = false;

}

ZcTreeCtrl::~ZcTreeCtrl()
{
  if ( m_pImageList)
	  {
	  delete m_pImageList;
	  }
}


BEGIN_MESSAGE_MAP(ZcTreeCtrl, CWnd)
	//{{AFX_MSG_MAP(ZcTreeCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_RESOURCE_OPEN, OnResourceOpen)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PROPERTIES, OnEditProperties)
	ON_COMMAND(ID_RESOURCE_RENAME, OnResourceRename)
	ON_COMMAND(ID_EDIT_TEMP, OnEditTemp)
	ON_COMMAND(ID_RESOURCE_EXPORT, OnResourceExport)
	//}}AFX_MSG_MAP
//	ON_NOTIFY(notifycode, id, memberfxn)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// ZcTreeCtrl message handlers

BOOL ZcTreeCtrl::Create(const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
BOOL bout;
static DWORD dw_size = 0;
char szname[100];
RECT rcout;

	sprintf(szname, "zTree%d", dw_size++);

	bout = CWnd::Create(csclass_Name, szname, WS_VISIBLE | WS_CHILD, rect, pParentWnd, nID, pContext);

	if ( bout)
		{
		GetClientRect( &rcout);
		if ( m_cTree.Create( WS_VISIBLE | WS_CHILD | TVS_EDITLABELS |
							TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS, 
							rcout, this,  0x102))
			{
			if ( m_pNotifyWnd )	// it's the toolbar
				{
				if ( cimg_SmallViewList.GetSafeHandle() )
					m_cTree.SetImageList(&cimg_SmallViewList, TVSIL_NORMAL);
				m_cTree.ModifyStyleEx( 0, WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME);
				}
			else
				{
				if ( cimg_ViewList.GetSafeHandle() )
					m_cTree.SetImageList(&cimg_ViewList, TVSIL_NORMAL);
				m_cTree.ModifyStyleEx( 0, WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
				}
			}
		}

	return bout;
}

static BOOL obj_Agrees( CNamed *cObj, NAMETYPES nTest, UNITMSR nUnit)
{
	if ( ntAny == nTest)
		return TRUE;
	if ( ntFolder == cObj->GetType())
		return TRUE;					// always allow folders
	if ( nTest != cObj->GetType())
		return FALSE;
	if ( ntDataSet != nTest || uomAny == nUnit)
		return TRUE;
	CDataSet *cdata = (CDataSet *)cObj;

	return ( nUnit == cdata->GetUOM());

}


static HTREEITEM build_Tree( CTreeCtrl& pcTree, TV_INSERTSTRUCT& tvi, CFolder *pcRoot, 
							 HTREEITEM hParent, NAMETYPES nSelect, UNITMSR nUnit)
{
int i, iadd;
HTREEITEM hroot;

	tvi.hParent = hParent;
	tvi.hInsertAfter = TVI_SORT;
	tvi.item.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvi.item.pszText = (LPSTR )(LPCSTR )pcRoot->GetName();
	tvi.item.iImage = ntFolder*2;	// folder
	tvi.item.iSelectedImage = ntFolder*2;	// folder
	tvi.item.lParam = pcRoot->GetID();
	
//	if ( pcRoot->GetID() )
		hroot = pcTree.InsertItem( &tvi);
//	else
//		hroot = hParent;		// don't show the root...

	if ( ! hroot)
		return hroot;

	for ( i=0; i<pcRoot->GetSize(false); i++)
		{
		CNamed *cnam = pcRoot->GetItemAt(i);
		if ( ntFolder == cnam->GetType() )
			build_Tree( pcTree, tvi, (CFolder *)cnam, hroot, nSelect, nUnit);	// build the subtree - recurs
		else
			{
			if ( obj_Agrees( cnam, nSelect, nUnit) )			// we are selecting something
				{
				tvi.hParent = hroot;
				tvi.hInsertAfter = TVI_SORT;
				tvi.item.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
				tvi.item.pszText = (LPSTR )(LPCSTR )cnam->GetName();
				iadd = cnam->IsTemporary() ? 1 : 0;
				if ( ntDataSet == cnam->GetType() )
					{
					CDataSet *cdata = (CDataSet *)cnam;
					tvi.item.iImage = ntFolder*2 + 2 + cdata->GetUOM()*2 + iadd;
					tvi.item.iSelectedImage = ntFolder*2 + 2 + cdata->GetUOM()*2 + iadd;
					}
				else
					{
					tvi.item.iImage = cnam->GetType()*2 + iadd;
					tvi.item.iSelectedImage = cnam->GetType()*2 + iadd;	// folder
					}
				tvi.item.lParam = cnam->GetID();
				pcTree.InsertItem( &tvi);
				}
			}
		}

	return hroot;
}



HTREEITEM ZcTreeCtrl::FindItem( DWORD dwID, HTREEITEM hRoot)
{
TV_ITEM tvi;
HTREEITEM hroot;
HTREEITEM hchild;
HTREEITEM hout;

	if ( hRoot)
		hroot = hRoot;
	else
		hroot = m_cTree.GetRootItem();

	tvi.hItem = hroot;
	tvi.mask = TVIF_PARAM;
	m_cTree.GetItem( &tvi);
	if ( dwID == (DWORD )tvi.lParam)
		return hroot;

	if ( m_cTree.ItemHasChildren( hroot))
		{
		hchild = m_cTree.GetChildItem( hroot);
		while ( hchild)
			{
			hout = FindItem( dwID, hchild);
			if ( hout)
				return hout;
			hchild = m_cTree.GetNextSiblingItem( hchild);
			}
		}
	return NULL;
}




void ZcTreeCtrl::RebuildTree( CFolder *cRoot, DWORD dwID, LPARAM lHint, CObject* pHint)
{
TV_INSERTSTRUCT tvi;			// we set this here to save on stack space, since subroutine is recursive
HTREEITEM hroot;
HTREEITEM hparent;
HTREEITEM hitem;
CFolder *cdest;
CNamed *cnam;
int iadd;

	if ( ! cRoot)			// at startup there is no folder passed here...
		{
		m_cTree.DeleteAllItems();
		m_pcRoot = cRoot;
		return;
		}

	if ( ntFolder != cRoot->GetType() )		// uh oh
		{
		ASSERT(0);
		return;
		}

	if ( (! lHint ) || ! m_cTree.GetCount() )						// we need to do the whole thing
		{
		CString cs;
		m_cTree.DeleteAllItems();		// get rid of last set of data
		cdest = (CFolder *)cRoot->GetItem( dwID);
		cs = cRoot->GetDocument()->GetTitle();
		if ( cs.GetLength() > 4)			// suffix removal...
			{
			if (! cs.Right( 4).CompareNoCase( ".aud"))
				cs = cs.Left( cs.GetLength() - 4);
			}
		cRoot->SetName( cs);
		hroot = build_Tree(m_cTree, tvi, cRoot, TVI_ROOT, m_nSelect, m_nUom);
		m_cTree.Expand( hroot, TVE_EXPAND );
		}
	else
		{			// get the object and replace all of it
 		cnam = cRoot->GetItem( lHint);
		cdest = (CFolder *)cRoot->GetItem( dwID);
 		if ( cnam)
			{
			if (obj_Agrees( cnam, m_nSelect, m_nUom) )			// we are selecting something
				{
				hparent = FindItem( cRoot->GetParent( lHint)->GetID() );
				tvi.hParent = hparent;
				tvi.hInsertAfter = TVI_SORT;
				tvi.item.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
				tvi.item.pszText = (LPSTR )(LPCSTR )cnam->GetName();
				tvi.item.lParam = cnam->GetID();
				iadd = cnam->IsTemporary() ? 1 : 0;
				if ( ntDataSet == cnam->GetType() )
					{
					CDataSet *cdata = (CDataSet *)cnam;
					tvi.item.iImage = ntFolder*2 + 2 + cdata->GetUOM()*2 + iadd;
					tvi.item.iSelectedImage = ntFolder*2 + 2 + cdata->GetUOM()*2 + iadd;
					}
				else
					{
					tvi.item.iImage = cnam->GetType()*2 + iadd;
					tvi.item.iSelectedImage = cnam->GetType()*2 + iadd;	// folder
					}

				hitem = FindItem( lHint);
				if ( hitem)
					{
					tvi.item.hItem = hitem;
					m_cTree.SetItem( &tvi.item);
					}
				else							// else add a new item
					{
					m_cTree.InsertItem( &tvi);
					}
				}
			}
		else			// no lHint in current document, just delete the old one
			{
			hitem = FindItem( lHint);

			if ( hitem)			// found one
				m_cTree.DeleteItem( hitem);
			}
		}



						// set the object globals for later processing
	m_pcRoot = cRoot;
}


BOOL ZcTreeCtrl::HasFocus( void)			// do we have the focus???
{

#if 0
TV_ITEM tvi;
HTREEITEM hobj = NULL;

	if ( (!m_pcRoot) || (!GetSafeHwnd()) || ! m_cTree.GetSafeHwnd())
		return FALSE;

	hobj = m_cTree.GetNextItem( NULL, TVGN_CARET);
	if ( ! hobj)
		return FALSE;

	tvi.hItem = hobj;
	tvi.mask = TVIF_STATE;
	m_cTree.GetItem( &tvi);		// get the selected item

	return ( (tvi.state & TVIS_FOCUSED) && ( tvi.state & TVIS_SELECTED));
#endif
	return ( this == GetFocus() || (&m_cTree) == GetFocus());
}



CNamed *ZcTreeCtrl::GetNextItem( CNamed *, UINT nCode )
{
TV_ITEM tvi;
CNamed *cname;
HTREEITEM hobj = NULL;

	if ( (!m_pcRoot) || (!GetSafeHwnd()) || ! m_cTree.GetSafeHwnd())
		return NULL;

	switch( nCode)
		{
		case TVGN_NEXT :
		case TVGN_NEXTVISIBLE :
		case TVGN_PARENT :
		case TVGN_PREVIOUS :
		case TVGN_PREVIOUSVISIBLE :
			ASSERT(0);					// not yet implemented
			hobj = m_cTree.GetNextItem( NULL, nCode);
			break;
		default :
			hobj = m_cTree.GetNextItem( NULL, nCode);
			break;
		}

	if ( ! hobj)
		return NULL;

	tvi.hItem = hobj;
	tvi.mask = TVIF_PARAM;
	m_cTree.GetItem( &tvi);		// get the selected item

	cname = m_pcRoot->GetItem( tvi.lParam);	// get the pointer
	return cname;

}


void ZcTreeCtrl::BeginDrag(NM_TREEVIEW *pItem)
// void ZcTreeCtrl::BeginDrag(HTREEITEM hItem, POINT *lpPt)
{
CImageList *pIml;
RECT rcl;
BOOL brslt;

   m_hDragItem = pItem->itemNew.hItem;		// save the item for later

				// Create an image to use for dragging.
  pIml = m_cTree.CreateDragImage(m_hDragItem);

  if ( m_pImageList)
	  {
	  delete m_pImageList;
	  }
  m_pImageList = pIml;

//  int ifoo = pIml->GetImageCount();


  // Set a global flag that tells whether dragging is happening.
  m_bDragging = TRUE;

	{
	TV_ITEM tvi;

	tvi.hItem = m_hDragItem;
	tvi.mask = TVIF_PARAM;
	m_cTree.GetItem( &tvi);					// get the lparam value
	m_dwSourceID = (DWORD )tvi.lParam;
	}


  // Get the bounding rectangle of the item being dragged.
  m_cTree.GetItemRect(m_hDragItem, &rcl, TRUE);

  // Start dragging the image.
  {
  CPoint pt(0,0);
  IMAGEINFO img;
		pIml->GetImageInfo( 0, &img);
		pt.x = img.rcImage.right / 4;
		pt.y = img.rcImage.bottom - 3;
//  cimg_DragCursors.SetDragCursorImage( 0, pt);
	brslt = pIml->BeginDrag(0, pt);
  }

  // Hide the cursor.
//  ShowCursor(FALSE);

  // Capture the mouse.
  SetCapture();
  
  SetCursor( AfxGetApp()->LoadCursor( IDC_POINTER) );

  pIml->DragEnter( this, pItem->ptDrag);
  m_cWndTarget = this;
  m_bCopying = FALSE;

}

void ZcTreeCtrl::OnMouseMove(UINT nFlags, CPoint cPoint) 
{
HTREEITEM hTarget;
UINT flags;
CPoint point;
CFolder *clasttarget = m_cTargetRoot;

	if (m_bDragging)
		{
			// Drag the item to the current mouse position.
		m_pImageList->DragMove(cPoint);

		flags = TVHT_ONITEM;
			// If the cursor is on an item, hilite it as the drop target.
			// get the window the cursor is over
		point = cPoint;
		ClientToScreen( &point);
		CWnd *cwhere = WindowFromPoint( point);
		m_dwTargetID = 0;
		m_cTargetRoot = NULL;
		if ( cwhere->IsKindOf( RUNTIME_CLASS(CTreeCtrl) ) )		// is it a tree???
			{
			ZcTreeCtrl *zcnew;
			if ( cwhere->GetParent()->IsKindOf( RUNTIME_CLASS( ZcTreeCtrl)) )
				{
				zcnew = (ZcTreeCtrl *)cwhere->GetParent();

				CTreeCtrl *ctree = (CTreeCtrl *)cwhere;
					{
					ctree->ScreenToClient( &point);
					hTarget = ctree->HitTest( point, &flags);
					if (hTarget != NULL)
						{
						TV_ITEM tvi;

						m_pImageList->DragLeave( m_cWndTarget);
						ctree->SelectDropTarget(hTarget);		// highlight it
						m_cWndTarget = cwhere;
						m_pImageList->DragEnter( m_cWndTarget, point);

						 										// convert it to a root handle
						tvi.hItem = hTarget;
						tvi.mask = TVIF_PARAM;
						ctree->GetItem( &tvi);					// get the lparam value
						m_dwTargetID = (DWORD )tvi.lParam;
						m_cTargetRoot = zcnew->m_pcRoot;
						}
					}
				}
			}
		}

					// set the cursor appropriately, if necessary
	if ( m_bCopying != (0 != (nFlags & MK_CONTROL))	||	// change to copying
		 m_cTargetRoot != clasttarget)					// new target document
		{
		UINT ucursor;
		m_bCopying = (0 != (nFlags & MK_CONTROL));
		if ( ! m_cTargetRoot)
			ucursor = IDC_NODROP;
		else
			if ( m_bCopying)
				ucursor = IDC_POINTER_COPY;
			else
				ucursor = IDC_POINTER;

		SetCursor( AfxGetApp()->LoadCursor( ucursor));
		}
    
	CWnd::OnMouseMove(nFlags, cPoint);
}

// Function that processes the item drop.
VOID ZcTreeCtrl::DropItem(UINT nFlags)
{
CNamed *cobj;
CNamed *cdest;

		   // Reset the drop target to NULL.
	m_cTree.SelectDropTarget((HTREEITEM)NULL);

	if ( !m_cTargetRoot)
		return;

	if ( ! m_dwSourceID)		// trying to move the root
		{
		::AfxMessageBox(IDERR_NOROOT);
		return;
		}
   			// alter the document tree structure
	cobj = m_pcRoot->GetItem( m_dwSourceID);			// search the entire tree for it
	cdest = m_cTargetRoot->GetItem( m_dwTargetID);

	if ( ! (nFlags & MK_CONTROL))
		{
		if ( m_dwSourceID == m_dwTargetID)				// do nothing
			return;
		if ( ntFolder != cdest->GetType())				// target is not a folder, it's the parent
			{
			if ( m_pcRoot->GetParent( m_dwSourceID) == m_cTargetRoot->GetParent( m_dwTargetID) )
				return;					// still do nothing
			}
		else
			if ( cdest == m_pcRoot->GetParent( m_dwSourceID) )
				return;

		m_pcRoot->RemoveItem( m_dwSourceID);					// remove it from the tree
		m_cTargetRoot->Insert( cobj, m_dwTargetID);
		}
	else			// duplicate the object
		{
		CNamed *cnew = cobj->Duplicate();
		if ( !cnew)
			return;

		if ( m_pcRoot->GetParent( m_dwSourceID) == m_cTargetRoot->GetParent( m_dwTargetID) )
			{				// same parent, have to change the name
			int i;
			CString csnew = cnew->GetName();

			for ( i = csnew.GetLength(); i > 0; i--)
				if ( ! isdigit( csnew.GetAt(i-1)))
					break;

			if ( i == csnew.GetLength() ||		// no digits in the name
				 (!i) || 						// nothing before the i
				 '.' != csnew.GetAt(i-1) )		// not a period
				{
				csnew = csnew + ".0";		// we plan to increment this
				}

			int nout;
			char csout[50];
			CFolder *cparent = m_cTargetRoot->GetParent( m_dwTargetID);

			for ( i = csnew.GetLength(); i > 0; i--)
				if ( ! isdigit( csnew.GetAt(i-1)))
					break;
			sscanf( (LPCSTR )csnew.Right( csnew.GetLength()-i), "%d", &nout);

			do					// increment past all existing names like this
				{
				nout++;
				sprintf( csout, "%d", nout);
				csnew = csnew.Left( i) + csout;
				} while( cparent->GetItemByName( csnew, FALSE) );

			cnew->SetName( csnew);
			}

		m_cTargetRoot->Insert( cnew, m_dwTargetID);
		}


	if ( ! (nFlags & MK_CONTROL))
		((CAudtestDoc *)m_pcRoot->GetDocument())->UpdateAll(NULL);
	if ( m_pcRoot != m_cTargetRoot || (nFlags & MK_CONTROL))
		((CAudtestDoc *)m_cTargetRoot->GetDocument())->UpdateAll(NULL);

}
  



void ZcTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
      // If dragging, stop it.
      if (m_bDragging)
      {
        // Process item drop.
//        DropItem(hDragItem);

        // Inform image list that dragging has stopped.
		m_pImageList->DragLeave( this);
        m_pImageList->EndDrag();

        // Release the mouse capture.
        ::ReleaseCapture();

		DropItem( nFlags);

        // Show the cursor.
        ::ShowCursor(TRUE);

        // Reset the global Boolean flag to a non-dragging state.
        m_bDragging = FALSE;

      }
	
	CWnd::OnLButtonUp(nFlags, point);
}

void ZcTreeCtrl::OnSize(UINT nType, int cx, int cy) 
{
CRect cclient;

	CWnd::OnSize(nType, cx, cy);

	if ( IsWindow(m_cTree.m_hWnd))	 // first time this is called, there is no window
		{
		GetClientRect( cclient);
		m_cTree.MoveWindow(cclient, TRUE);
		}
}

void	ZcTreeCtrl::SetFilter( NAMETYPES nNew, UNITMSR nUom)
{
 	m_nSelect = nNew;
	m_nUom = nUom;
}

CNamed *ZcTreeCtrl::GetSelection( void)
{
DWORD dwid;
TV_ITEM tvi;

	if ( m_bInRightClick)
	{
		tvi.hItem = m_hRightSel;		// use the one we had down
	}
	else
		tvi.hItem = NULL;
	if ( ! tvi.hItem)
		tvi.hItem = m_cTree.GetDropHilightItem();
	if ( ! tvi.hItem)
		tvi.hItem = m_cTree.GetSelectedItem();
	if ( ! tvi.hItem)
		tvi.hItem = m_cTree.GetFocused();
	if ( ! tvi.hItem)
		return NULL;

	tvi.mask = TVIF_PARAM;
	m_cTree.GetItem( &tvi);					// get the lparam value

	dwid = (DWORD )tvi.lParam;
	
	if ( m_pcRoot )		// we have a root object
	{
	CNamed *dest = m_pcRoot->GetItem( dwid, TRUE);

		return dest;			// for debug
	}
		

	return NULL;
}


void ZcTreeCtrl::OnEditCut() 
{
COpCode *cop;
CNamed *cname = GetSelection();
	
	if ( cname)
		{
		cop = new COpClipCut( cname );
		cop->QueueAndDo();
		}
	
}

// -----------------------------------------------------------------------
//		OnEditTemp - make temporary or permanent
// -----------------------------------------------------------------------
void ZcTreeCtrl::OnEditTemp() 
{
COpCode *cop;
CNamed *cname = GetSelection();
bool ballow = true;

	if ( cname)
		{
		if ( ! cname->IsTemporary())
		{
			if ( ! cname->GetID())		// is it the root?
				{
				ballow = false;
				}
			else
			if ( cname->IsReadOnly())
				{
				ballow = false;
				}
			else
			if ( cname->IsSystem())
				{
				ballow = false;
				}
		}
		if ( ballow)
			{
			cop = new COpSwapTemp( cname );
			cop->QueueAndDo();
			}
		}

	if ( ! ballow)
	{
		::AfxMessageBox( IDERR_NOTEMP, MB_OK);
	}
	
	
}


// -----------------------------------------------------------------------
//		OnUpdateEditTemp - update the edit temp option
//			This is actually a callable function, not the usual onupdate...
// -----------------------------------------------------------------------
void ZcTreeCtrl::OnUpdateEditTemp(CCmdUI* pCmdUI) 
{
CString csnew;
bool ballow;

	ballow = OnMakeTempString( csnew);

	pCmdUI->SetText( csnew);
	pCmdUI->Enable( ballow);

}

// -----------------------------------------------------------------------
//		OnMakeTempString - update the edit temp option
//			This is actually a callable function, not the usual onupdate...
// -----------------------------------------------------------------------
bool ZcTreeCtrl::OnMakeTempString(CString &csNew)
{
CNamed *cname = GetSelection();
CString csmenu;
bool ballow = true;

	if ( cname)
	{
		if ( cname->IsTemporary())
		{
			csmenu.LoadString( IDS_MENU_MAKEPERM);
		}
		else
		{

			csmenu.LoadString( IDS_MENU_MAKETEMP);
			if ( ! cname->GetID())		// is it the root?
				{
				ballow = false;
				}
			else
			if ( cname->IsReadOnly())
				{
				ballow = false;
				}
			else
			if ( cname->IsSystem())
				{
				ballow = false;
				}
		}
	}

	csNew = csmenu;			// pass the string back

	return ballow;

}

// -----------------------------------------------------------------------
//		OnResourceExport - export
// -----------------------------------------------------------------------
void ZcTreeCtrl::OnResourceExport() 
{
CNamed *cname = GetSelection();
	
	if ( cname)
	{
	((CAudtestDoc *)cname->GetDocument())->ExportResource( cname);
	}

	
}

// -----------------------------------------------------------------------
//		OnEditDelete - delete
// -----------------------------------------------------------------------
void ZcTreeCtrl::OnEditDelete() 
{
COpCode *cop;
CNamed *cname = GetSelection();
	
	if ( cname)
		{
		if ( ! cname->GetID())		// is it the root?
			{
			::AfxMessageBox( IDS_ISROOT);
			}
		else
		if ( cname->IsReadOnly())
			{
			::AfxMessageBox( IDS_READONLY);
			}
		else
		if ( cname->IsSystem())
			{
			::AfxMessageBox( IDS_SYSTEM);
			}
		else
			{
			cop = new COpDelete( cname );
			cop->QueueAndDo();
			}
		}
	
}


void ZcTreeCtrl::OnEditCopy() 
{
COpCode *cop;
CNamed *cname = GetSelection();

	if ( cname)
		{
		cop = new COpClipCopy( cname);
		cop->QueueAndDo();
		}
}

void ZcTreeCtrl::OnEditPaste() 
{
COpCode *cop;
CNamed *cname;

	if ( ! m_pcRoot)
		return;			// whoa....

	cname = GetSelection();
	if ( ! cname)					// no selection
		cname = m_pcRoot;			// root is just fine

	if ( ntFolder != cname->GetType() )
		cname = m_pcRoot->GetParent( cname->GetID());	// make it a folder

	cop = new COpClipPaste( cname);
	cop->QueueAndDo();
}



void ZcTreeCtrl::OnEditProperties() 
{
CNamed *cname = GetSelection();

	if ( ! cname)
		return;

	cname->EditProperties( this);

	cname = GetSelection();			// since it could have changed in the edit properties

	cname->UpdateViews();
}

void ZcTreeCtrl::OnResourceOpen() 
{
CNamed *cname = GetSelection();

//	if ( cname && ntFolder != cname->GetType())		// target is not the root
	if ( cname)		// target is not the root
		{
		((CAudtestDoc *)m_pcRoot->GetDocument())->OpenResource( cname );
		}
	
}


void ZcTreeCtrl::OnResourceRename() 
{
CDlgRename cdlg(this);
COpRename *cop;
CNamed *cname = GetSelection();

	if ( ! cname)
		return;

	cdlg.m_csName = cname->GetName();

	if ( IDOK == cdlg.DoModal())
		{
		cop = new COpRename( cname, cdlg.m_csName);
		cop->QueueAndDo();
		}
}

BOOL ZcTreeCtrl::WantCommand(UINT uID)
{

	switch( uID)		// we'll take these
		{
		case ID_EDIT_CUT :
		case ID_EDIT_COPY :
		case ID_EDIT_PASTE :
		case ID_EDIT_DELETE :
		case ID_EDIT_TEMP :
		case ID_EDIT_PROPERTIES :
		case ID_RESOURCE_OPEN :
		case ID_RESOURCE_RENAME :
			return TRUE;
		default :
			break;
		}

	return FALSE;

}

BOOL ZcTreeCtrl::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch( LOWORD(wParam) )
		{
		case ID_RESOURCE_NEW_CHART:
		case ID_RESOURCE_NEW_ENCLOSURE:
		case ID_RESOURCE_NEW_DRIVER:
		case ID_RESOURCE_NEW_ROOM:
		case ID_RESOURCE_NEW_NETWORK:
		case ID_RESOURCE_NEW_SIGNAL:
		case ID_RESOURCE_NEW_FOLDER:
		case ID_EDIT_UNDO:
		case ID_EDIT_REDO:
		case ID_RESOURCE_IMPORT:
			if ( m_pNotifyWnd)
				m_pNotifyWnd->PostMessage( WM_COMMAND, wParam, lParam); // send it on
			break;
		case ID_SOUND_STOP :
			m_bInRightClick = false;			// we've received the end of right message
		default: break;
		}
	
	return CWnd::OnCommand(wParam, lParam);
}

BOOL ZcTreeCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
LPNMHDR pwho = (LPNMHDR)lParam;

	switch( pwho->code)
		{
		case TVN_BEGINDRAG:
			{
			NM_TREEVIEW *pview;
				pview = (NM_TREEVIEW *)lParam;
				// The user wants to drag an item. Call the drag handler.
				BeginDrag(pview);
			
				// Save off the dragged item information.
//				tvI = ((NM_TREEVIEW *)lParam)->itemNew;
			}
			return TRUE;

		case TVN_BEGINLABELEDIT :
			{
			CEdit *cedit = m_cTree.GetEditControl();
			cedit->SetFocus();
			}
			break;
		case TVN_ENDLABELEDIT :
			TV_DISPINFO *pinfo;
			COpCode *cop;
				pinfo = (TV_DISPINFO *)lParam;
				if ( pinfo && pinfo->item.pszText)
					{
					CNamed *cnam = m_pcRoot->GetItem( pinfo->item.lParam, TRUE);
					if ( cnam)
						{
						cop = new COpRename( cnam, pinfo->item.pszText);
						cop->QueueAndDo();
						}
					}
			return TRUE;
		case TVN_SELCHANGED:
			{
			CNamed *cname = GetSelection();

				if ( ! cname)
					break;

				if ( ntFolder == cname->GetType())		// target is not the root
					break;
			}
			if (! CAudtestApp::GetSingleClick())		// not use single click ??
				break;									// quit
		case NM_DBLCLK:
			if ( m_pNotifyWnd)
				{
				OnResourceOpen();
				return TRUE;
				}
			break;
		case NM_RCLICK:
			{
			POINT       pt;
			CMenu 		*cmenu;
			CMenu		cmenures;
							/*
							 * Build a popup menu for this object with Cut, Copy, Delete,
							 * and object verbs.
							 */
				if ( ! cmenures.LoadMenu(IDR_MTREEVIEW ) )
					break;

						//Resource-loaded menus don't work, so we'll copy the items.
				cmenu = cmenures.GetSubMenu(0);

						// update for maketemp/makeperm
				{
				CString csnew;
				bool benable;
				UINT nflags = MF_BYCOMMAND | MF_STRING;

					benable = OnMakeTempString( csnew);
					nflags |= benable ? MF_ENABLED : MF_GRAYED;
					cmenu->ModifyMenu( ID_EDIT_TEMP, nflags, ID_EDIT_TEMP, csnew);
				}

				::GetCursorPos( &pt);
				{
				HTREEITEM hsel;
				UINT ustate;
					hsel = m_cTree.GetFirstVisibleItem();
					ustate = TVIS_BOLD ;		// get all states
					while( hsel)
					{
						ustate = m_cTree.GetItemState( hsel, 0xff);
						if ( ustate & TVIS_DROPHILITED)			// this is the one we want
							break;
						hsel = m_cTree.GetNextVisibleItem( hsel);
					}
					if ( hsel)
						m_hRightSel =  hsel;
					else
						m_hRightSel =  m_cTree.GetSelectedItem();
				}

				m_bInRightClick = true;

				cmenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_LEFTBUTTON, pt.x, pt.y, this);

				cmenures.DestroyMenu( );

				PostMessage( WM_COMMAND, ID_SOUND_STOP);		// do this after the message handling
			}
			return TRUE;
		case NM_RDBLCLK:
		case NM_RETURN:
			return TRUE;

		default:
			break;
		}
	
	return CWnd::OnNotify(wParam, lParam, pResult);
}



/////////////////////////////////////////////////////////////////////////////
// CSubTree

CSubTree::CSubTree()
{
	m_pParent = NULL;
}

CSubTree::~CSubTree()
{
}


BEGIN_MESSAGE_MAP(CSubTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CSubTree)
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubTree message handlers



void CSubTree::OnKillFocus(CWnd* pNewWnd) 
{

	CTreeCtrl::OnKillFocus(pNewWnd);
}


HTREEITEM CSubTree::GetFocused( void)
{
	return NULL;
#if 0
HTREEITEM ht;
COLORREF clr1, clr;

	ht = GetRootItem();		// get the root item

	while ( ht)
	{
		if ( GetCheck( ht))
			break;

		ht = GetNextItem( ht, TVGN_NEXTVISIBLE);
	}

	return ht;
#endif
}



