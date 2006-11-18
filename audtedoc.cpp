// audtedoc.cpp : implementation of the CAudtestDoc class
//

#include "stdafx.h"
#include "audtest.h"

#include "MainFrm.h"
#include "childfrm.h"

#include "audtedoc.h"
#include "audtevw.h"
#include "srvritem.h"

#include "utils.h"


#include "dlgRenam.h"

#include "opItem.h"

#include "generat.h"
#include "chart.h"
#include "dataset.h"
#include "driver.h"
#include "network.h"
// #include "room.h"
#include "enclosur.h"



#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define FILE_VERSION 1235

/////////////////////////////////////////////////////////////////////////////
// CAudtestDoc

IMPLEMENT_DYNCREATE(CAudtestDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CAudtestDoc, COleServerDoc)
	//{{AFX_MSG_MAP(CAudtestDoc)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_COMMAND(ID_RESOURCE_NEW_CHART, OnResourceNewChart)
	ON_COMMAND(ID_RESOURCE_NEW_DRIVER, OnResourceNewDriver)
	ON_COMMAND(ID_RESOURCE_NEW_ENCLOSURE, OnResourceNewEnclosure)
	ON_COMMAND(ID_RESOURCE_NEW_FOLDER, OnResourceNewFolder)
	ON_COMMAND(ID_RESOURCE_NEW_NETWORK, OnResourceNewNetwork)
	ON_COMMAND(ID_RESOURCE_NEW_SIGNAL, OnResourceNewSignal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAudtestDoc, COleServerDoc)
	//{{AFX_DISPATCH_MAP(CAudtestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudtestDoc construction/destruction

CAudtestDoc::CAudtestDoc()	: m_cRoot(), m_cOpcodeQueue()
{
	// TODO: add one-time construction code here

	m_nUndoLocation = 0;

	m_cRoot.SetID(0);
	m_cRoot.SetRootObject( &m_cRoot);
	m_cRoot.SetDocument( this);
	m_cRoot.SetAttributes( ATTRIB_READONLY | ATTRIB_SYSTEM);
	m_cRoot.SetName("Root");

	{
	CFolder *psys = new CFolder();
		if ( psys)
			{
			CString csi;
			csi.LoadString( IDS_SYSDESCRIPT);
			psys->SetName("System");
			psys->SetDescription( csi);
			psys->SetAttributes( ATTRIB_READONLY | ATTRIB_SYSTEM);
			m_cRoot.AddItem( psys);
			m_dwSystem = psys->GetID();
			}
		else m_dwSystem = 0;
	}

	m_cCalib.dwLeftRight = 0;
	m_cCalib.dwMicrophone = 0;
	m_cCalib.dwAmplifier = 0;

	m_dwGenerator = 0;
	m_tLastSaveTime = 0;			// no last save yet
	
	EnableAutomation();

	AfxOleLockApp();

	CAudtestApp::SetDocCounter( 1);				// increment doc counter
}

CAudtestDoc::~CAudtestDoc()
{
	::KillArray( &m_cOpcodeQueue);

	AfxOleUnlockApp();
}

BOOL CAudtestDoc::OnNewDocument()
{
	if (!COleServerDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAudtestDoc server implementation

COleServerItem* CAudtestDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CAudtestSrvrItem* pItem = new CAudtestSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

/////////////////////////////////////////////////////////////////////////////
// CAudtestDoc serialization

void CAudtestDoc::Serialize(CArchive& ar)
{
WORD w = FILE_VERSION;

	if (ar.IsStoring())
		{
		UpdateAllCharts();
//		DeleteTheTemps();
			// storing code here
		ar << w;

//		w = (WORD )m_cRecording.m_nDataType;	ar << w;		// type of data to generate (freq/time/impedance)
						// --- test specific
//		ar << m_cRecording.m_fDataAmplitude;			// amplitude of wave
//		w = (WORD )m_cRecording.m_nDataChannel;	ar << w;	// channel to use for data
//		w = (WORD )m_cRecording.m_nCalibChannel;	ar << w;	// calibration channel
//		w = (WORD )m_cRecording.m_nOutChannel;		ar << w;
//		ar << m_cRecording.m_fInLeftVolume;
//		ar << m_cRecording.m_fInRightVolume;			// left and right input volume settings
//		ar << m_cRecording.m_fPlayTime;
//		ar << m_cRecording.m_fRecordTime;

		ar << m_cCalib.dwLeftRight;
		ar << m_cCalib.dwMicrophone;
		ar << m_cCalib.dwAmplifier;
		}
	else
		{
			// loading code here
		ar >> w;
		if ( w < (FILE_VERSION-1) || w > FILE_VERSION)
			return;

		if ( m_dwSystem)			// we have built a system folder...
			{
			m_cRoot.DeleteItem( m_dwSystem);
			m_dwSystem = 0;
			}
//		ar >> w; m_cRecording.m_nDataType = (int )w;		// type of data to generate (freq/time/impedance)
						// --- test specific
//		ar >> m_cRecording.m_fDataAmplitude;			// amplitude of wave
//		ar >> w;	m_cRecording.m_nDataChannel = (int )w;	// channel to use for data
//		ar >> w;	m_cRecording.m_nCalibChannel = (int )w;	// calibration channel
//		ar >> w;	m_cRecording.m_nOutChannel = (int )w;
//		ar >> m_cRecording.m_fInLeftVolume;
//		ar >> m_cRecording.m_fInRightVolume;			// left and right input volume settings
//		ar >> m_cRecording.m_fPlayTime;
//		ar >> m_cRecording.m_fRecordTime;

		ar >> m_cCalib.dwLeftRight;
		ar >> m_cCalib.dwMicrophone;
		if ( w > 1234)		// switch to add dwamplifier
			ar >> m_cCalib.dwAmplifier;
		else
			m_cCalib.dwAmplifier = 0;
		}

	m_cRoot.Serialize(ar);

	if ( ! ar.IsStoring())			// loading code, update the system variable
		{
		CNamed *psys;
		psys = m_cRoot.GetItemByName("System", FALSE);
		if ( psys && (ntFolder == psys->GetType()) )
			m_dwSystem = psys->GetID();
		}

}

/////////////////////////////////////////////////////////////////////////////
// CAudtestDoc diagnostics

#ifdef _DEBUG
void CAudtestDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CAudtestDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAudtestDoc commands

static CString get_NewObjName(CDocument *pDoc, UINT iType)
{
char sz[100];			// the output string
CString cstitle;
CString csobj;
CWnd *cParent;

	{
	POSITION pos = pDoc->GetFirstViewPosition();
	cParent = pDoc->GetNextView( pos);
	}

	cstitle.LoadString( IDS_NEWRESOURCE);
	csobj.LoadString( iType);

	sprintf( sz, (LPCSTR )cstitle, (LPCSTR )csobj);

	{
	CDlgRename cdlg( cParent);

	cdlg.m_csTitle = sz;
	cdlg.m_csName.LoadString( IDS_DEFAULTNEW);

	if ( IDOK == cdlg.DoModal())
		return cdlg.m_csName;
	else
		{
		csobj = cNullString;			//  .LoadString( IDS_DEFAULTNEW);
		return csobj;
		}
	}
}

void CAudtestDoc::InsertNewObject( CFolder *pParent, CNamed *pNew)
{
COpInsert *cop;

	cop = new COpInsert( pParent, pNew);				// now insert it into the tree
	if ( ! cop->QueueAndDo())							// via undoable stuff
		pNew->UpdateViews();
}



void CAudtestDoc::OnResourceNewChart() 
{
CChart *newobj;
CString csname;

	csname = get_NewObjName( this, IDS_RESCHART);		// get the object name from dbox
	if ( ! csname.GetLength())
		return;
	newobj = new CChart();								// create a new object
	newobj->SetName( csname);							// with this name
	InsertNewObject( &m_cRoot, newobj);
	OpenResource( newobj);
}

void CAudtestDoc::OnResourceNewSignal() 
{
CGenerator *newobj;
CString csname;

	csname = get_NewObjName( this, IDS_RESSIGNAL);
	if ( ! csname.GetLength())
		return;
	newobj = new CGenerator();
	newobj->SetName( csname);
	InsertNewObject( &m_cRoot, newobj);
	OpenResource( newobj);
}

void CAudtestDoc::UpdateAllCharts( void)
{
POSITION pos = GetFirstViewPosition();
DWORD dwid;
CNamed *pname;
CAudtestView* pView;

	while (pos != NULL)
		{
			pView = (CAudtestView *)GetNextView(pos);
			dwid = pView->GetTarget();
			pname = GetByID( dwid);
			if ( pname && ntChart == pname->GetType())
			{
				UpdateAll( NULL, dwid);
			}
		}   
}


void CAudtestDoc::UpdateAll( CView* pSender, LPARAM lHint, CObject* pHint )
{
	{
	CWnd *cmain = AfxGetMainWnd();
	if ( cmain && cmain->IsKindOf(RUNTIME_CLASS( CMainFrame))) 
		((CMainFrame *)cmain)->UpdateTree( pSender, lHint, pHint);
	}
	DBG_PRINT("Did Update Tree");

	COleServerDoc::UpdateAllViews( pSender, lHint, pHint);
}


CNamed *CAudtestDoc::GetByID( DWORD dwID)
{

	if ( dwID == m_cRoot.GetID())
		return &m_cRoot;
	return m_cRoot.GetItem( dwID, TRUE);	// dive

}


void CAudtestDoc::OnResourceNewFolder() 
{
CFolder *newobj;
CString csname;

	csname = get_NewObjName( this, IDS_RESFOLDER);
	if ( ! csname.GetLength())
		return;
	newobj = new CFolder();
	newobj->SetName( csname);
	InsertNewObject( &m_cRoot, newobj);
	OpenResource( newobj);
	
}


void CAudtestDoc::OnResourceNewNetwork() 
{
CNetwork *newobj;
CString csname;

	csname = get_NewObjName( this, IDS_RESNETWORK);
	if ( ! csname.GetLength())
		return;
	newobj = new CNetwork();
	newobj->SetName( csname);
	InsertNewObject( &m_cRoot, newobj);
	OpenResource( newobj);
}

void CAudtestDoc::OnResourceNewEnclosure() 
{
CEnclosure *newobj;
CString csname;

	csname = get_NewObjName( this, IDS_RESENCLOSURE);
	if ( ! csname.GetLength())
		return;
	newobj = new CEnclosure();
	newobj->SetName( csname);
	InsertNewObject( &m_cRoot, newobj);
	OpenResource( newobj);
}

void CAudtestDoc::OnResourceNewDriver() 
{
CDriver *newobj;
CString csname;

	csname = get_NewObjName( this, IDS_RESDRIVER);
	if ( ! csname.GetLength())
		return;
	newobj = new CDriver();
	newobj->SetName( csname);
	InsertNewObject( &m_cRoot, newobj);
	OpenResource( newobj);
}

// --------------------------------------------------------------
CDataSet *CAudtestDoc::GetAmpResponse( void)
{
TESTCAL tcal;

	tcal = *GetCalib();

	if ( ! tcal.dwAmplifier)
		return NULL;
	return (CDataSet *)(m_cRoot.GetItem( tcal.dwAmplifier));
}

// --------------------------------------------------------------
CDataSet *CAudtestDoc::GetMicResponse( void)
{
TESTCAL tcal;

	tcal = *GetCalib();

	if ( ! tcal.dwMicrophone)
		return NULL;
	return (CDataSet *)(m_cRoot.GetItem( tcal.dwMicrophone));
}

// --------------------------------------------------------------
CNamed *CAudtestDoc::GetDefaultGenerator(void )
{
CNamed *pout= NULL;
char *szm = "Measurement";

	if ( m_dwGenerator)
		pout = GetByID( m_dwGenerator);

	if ( pout)
		return pout;

					// look to see if the database has one already...
	{
	CFolder *pbase = GetSystem();
	if ( pbase)
		{
		pout = pbase->GetItemByName( szm, FALSE);		// look for it
		if ( pout)
			{
			m_dwGenerator = pout->GetID();
			return pout;
			}
		}
	}

	pout = new CGenerator();
	pout->SetName( szm);
	m_dwGenerator = pout->GetID();
	GetSystem()->AddItem( pout);
	UpdateAll(NULL, m_dwGenerator);

	return pout;
		
}

CString CAudtestDoc::GetFullTextName( CNamed *cTarget)
{				// for debug, let's see the string
CString cs = GetTitle();
CString cs2;					// type name

	if (! cs.Right(4).CompareNoCase(".swd") )		// it is an swd file
		cs = cs.Left( cs.GetLength() - 4);			// strip the suffix
	if ( CAudtestApp::GetShowLongTitle())
		cs += ":" + cTarget->GetName();						// name
	else
		cs = cTarget->GetName();						// name

	if ( cTarget->GetID())			// not the root
		{
		switch( cTarget->GetType())
			{
			case ntGenerator:
				cs2.LoadString( IDS_RESSIGNAL);
				break;
			case ntDataSet:
				cs2.LoadString( IDS_RESDATASET);
				break;
			case ntChart:
				cs2.LoadString( IDS_RESCHART);
				break;
			case ntEnclosure:
				cs2.LoadString( IDS_RESENCLOSURE);
				break;
			case ntNetwork:
				cs2.LoadString( IDS_RESNETWORK);
				break;
			case ntRoom:
				cs2.LoadString( IDS_RESROOM);
				break;
			case ntDriver:
				cs2.LoadString( IDS_RESDRIVER);
				break;
			case ntFolder:
				cs2.LoadString( IDS_RESFOLDER);
				break;
			default :
				break;
			}
		cs += " (" + cs2 + ")";
		}

	return cs;
}



// --------------------------------------------------------------
void CAudtestDoc::OpenResource( CNamed *cSource) 
{
CMultiDocTemplate *pTemplate;
DWORD dwid;

	if ( ! GetByID( cSource->GetID()))				 // check for validity of input
		{
		ASSERT(0);
		return;
		}

	{
	POSITION pos = GetFirstViewPosition();
	CAudtestView* pView;
	while (pos != NULL)
		{
		pView = (CAudtestView *)GetNextView(pos);
		if ( cSource->GetID() == pView->GetTarget() )
			{
			CWnd *cmain = AfxGetMainWnd();
				if ( cmain && cmain->IsKindOf(RUNTIME_CLASS( CMDIFrameWnd))) 
					((CMDIFrameWnd *)cmain)->MDIActivate( pView->GetParent());
				return;
			}
		}   
	}

	pTemplate = ((CAudtestApp *)AfxGetApp())->GetTemplate(cSource->GetType());

	// Create a new view window containing the resource
    CChildFrame* pNewFrame
        = (CChildFrame*)(pTemplate->CreateNewFrame(this, NULL));

    if (pNewFrame == NULL)
        return;     // not created

	ASSERT_KINDOF( CChildFrame, pNewFrame);

				// now set the id for the selected object
	dwid = cSource->GetID();

	pNewFrame->SetTarget( dwid, GetFullTextName( cSource));

    pTemplate->InitialUpdateFrame(pNewFrame, this);
					// set the window title to match this guy
	pNewFrame->SetTarget( dwid, GetFullTextName( cSource));
	
}



// --------------------------------------------------------
//			the OpCode queue stuff
// --------------------------------------------------------
void			CAudtestDoc::AddOpcode(COpCode *cNew)
{
	if ( m_nUndoLocation < m_cOpcodeQueue.GetSize())	// hmm, truncate the queue
		{
		int i;

			for ( i=m_cOpcodeQueue.GetSize()-1; i >= m_nUndoLocation; i--)
				{
				delete m_cOpcodeQueue.GetAt(i);
				m_cOpcodeQueue.RemoveAt(i);
				}
		}

	m_cOpcodeQueue.Add( cNew);
	m_nUndoLocation = m_cOpcodeQueue.GetSize();

}


COpCode			*CAudtestDoc::GetCurrentUndo()
{
	if ( (! m_cOpcodeQueue.GetSize() ) || 			// nothing to undo
		 ( m_nUndoLocation > m_cOpcodeQueue.GetSize() ) ||	// invalid data
		 ( ! m_nUndoLocation) )						// have undone everything
		return NULL;

	return (COpCode *)m_cOpcodeQueue.GetAt( m_nUndoLocation-1);

}


COpCode			*CAudtestDoc::GetCurrentRedo()
{
	if ( (! m_cOpcodeQueue.GetSize() ) || ( m_nUndoLocation >= m_cOpcodeQueue.GetSize() ) )
		return NULL;

	return (COpCode *)m_cOpcodeQueue.GetAt( m_nUndoLocation);

}

void			CAudtestDoc::PerformUndo()
{
COpCode *cuse;

	cuse = GetCurrentUndo();
	if ( cuse)
		{
		cuse->DoUndo();
		m_nUndoLocation--;
		}
}

void			CAudtestDoc::PerformRedo()
{
COpCode *cuse;

	cuse = GetCurrentRedo();
	if ( cuse)
		{
		cuse->DoRedo();
		m_nUndoLocation++;
		}

}


// --------- themainline undo redo stuff
void CAudtestDoc::OnEditRedo() 
{
	// TODO: Add your command handler code here
	PerformRedo();	
}

void CAudtestDoc::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
COpCode *redo;
CString csout;

	// TODO: Add your command update UI handler code here
	redo = GetCurrentRedo();
	if ( redo)
		{
		redo->GetUndoName( &csout);
		pCmdUI->Enable( TRUE);
		pCmdUI->SetText( "&Redo " + csout+ "\tCtrl+Y" );
		}
	else
		{
		pCmdUI->Enable( FALSE);
		pCmdUI->SetText( "&Redo");
		}	
}

void CAudtestDoc::OnEditUndo() 
{
	// TODO: Add your command handler code here
	PerformUndo();
	
}

void CAudtestDoc::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
COpCode *undo;
CString csout;

	// TODO: Add your command update UI handler code here
	undo = GetCurrentUndo();
	if ( undo)
		{
		undo->GetUndoName( &csout);
		pCmdUI->Enable( TRUE);
		pCmdUI->SetText( "&Undo " + csout+ "\tCtrl+Z" );
		}
	else
		{
		pCmdUI->Enable( FALSE);
		pCmdUI->SetText( "&Undo");
		}	
	
}



BOOL CAudtestDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
BOOL bout;

		// clean up the document undo stack
	FlushUndo();

	bout = COleServerDoc::OnSaveDocument(lpszPathName);

	if ( ! bout)
		return FALSE;

	CAudtestApp::SetLastFile( lpszPathName);		// update the doc file name

		// update each view with the correct file name
	{
	POSITION i;
	CView *cview;
    CChildFrame* pframe;
	CNamed *ctarg;

		SetPathName( lpszPathName);

		for ( i = GetFirstViewPosition(); NULL != i; ) 
			{
			cview = GetNextView(i);
			pframe = (CChildFrame *)cview->GetParent();
			ctarg = GetByID( pframe->GetTarget() );
			if ( ctarg)
				pframe->SetTarget( pframe->GetTarget(), GetFullTextName( ctarg));
			}
	}

	return bout;	

}



void CAudtestDoc::FlushUndo( BOOL )
{			// ignore redo flag for now
	::KillArray( &m_cOpcodeQueue);

	m_nUndoLocation = 0;

}


DWORD CAudtestDoc::GetSize( void)
{

	return m_cRoot.GetObjectSize( TRUE);

}

int CAudtestDoc::GetObjectCount(NAMETYPES nType)
{
	return m_cRoot.GetCount( nType);
}

// -------------------------------------------------------------------------
//		DeleteTheTemps
// -------------------------------------------------------------------------
void	CAudtestDoc::DeleteTheTemps( void)		// delete the temporary items
{
	m_cRoot.DeleteAllTemps();
	UpdateAll( NULL);
}

// -------------------------------------------------------------------------
//		FindItemView
// -------------------------------------------------------------------------

CAudtestView *CAudtestDoc::FindItemView(DWORD dwID)
{
POSITION pos = GetFirstViewPosition();

	while (pos != NULL)
		{
		CAudtestView* pView = (CAudtestView *)GetNextView(pos);

		if ( dwID == pView->GetTarget())
			{
			return pView;
			}
		}   

	return NULL;
}



// -------------------------------------------------------------------------
//		RemoveItemView
// -------------------------------------------------------------------------

void CAudtestDoc::RemoveItemView(DWORD dwID)
{
CAudtestView *pView;

	pView = FindItemView( dwID);

	if ( pView)
		pView->GetParent()->DestroyWindow();

}

static bool find_DWIn( CDWordArray &pLook, DWORD dwID)
{
int i;

	for ( i=0; i<pLook.GetSize(); i++)
		if ( dwID == pLook[i])
			return true;
	return false;
}

// -------------------------------------------------------------------------
//		BuildBaseChart
// -------------------------------------------------------------------------
CNamed *CAudtestDoc::BuildBaseChart(CNamed *pParent, LPCSTR szName, CDWordArray &cdwIDs)
{
CChart *pchart;
CString csname;
CFolder *ptop;
CSubChart *psub;
CDWordArray cdwchart;
int i;

	ptop = pParent->FindParent();						// get the folder parent
	ASSERT(ptop);

	pchart = (CChart *)ptop->FindByName( szName, FALSE);

	if (! pchart )				// look here only
	{
		pchart = new CChart();								// create a new object
		pchart->SetName( szName);							// with this name
		pchart->SetTemporary( true);
		ptop->AddItem( pchart);
		pchart->CreateChart( pParent);
		OpenResource( pchart);
	}

	{
	CAudchView *pview = (CAudchView *)FindItemView( pchart->GetID());		// get the view
		if ( pview)
		{
			pview->MakeViewChart();		// make the view if there isn't one already
			psub = pview->GetViewChart();
		}
		else
			psub = NULL;
	}

	if ( ! psub)			// use the subchart
		return NULL;

	{
	DWORD dw;

		cdwchart.SetSize( 0, cdwIDs.GetSize());
		for ( i=0; i<psub->GetDataCount(); i++)
		{
			dw = psub->GetDatasetAt(i)->GetID();
			cdwchart.Add( dw);
		}
		for ( i=0; i< cdwchart.GetSize(); i++)
		{
			dw = cdwchart[i];
			if ( ! find_DWIn( cdwIDs, dw))
				psub->Detach( dw);			// get rid of it, it's not in the list
		}
		for ( i=0; i< cdwIDs.GetSize(); i++)
		{
			dw = cdwIDs[i];
			if ( ! find_DWIn( cdwchart, dw))
				psub->Attach( dw);			// get rid of it, it's not in the list
		}

	}

	return psub;

}


// -------------------------------------------------------------------------
//		QueryAutoSave
// -------------------------------------------------------------------------

int CAudtestDoc::QueryAutoSave( void)
{
	if ( ! CAudtestApp::GetAutoSave())
	{
		m_tLastSaveTime = 0;
		return 0;			// nothing to do
	}

	if ( ! m_tLastSaveTime)			// not autosaved yet
	{
		time( &m_tLastSaveTime);	// now we have a time
		return 1;					// just starting up
	}

	if ( ! IsModified())
	{
		m_tLastSaveTime = 0;
		return 0;			// nothing to do
	}
		
	if ( CAudtestApp::GetIsWorking())
		return 0;					// don't worry about it

	{
	time_t tt;						// new time
	int iwait;						// time to wait
	BOOL bout;
	CString szpath = GetPathName();			// get our name
	int iext;					// where the extension is
	BOOL bflag;

		time( &tt);					// get the new time
		tt -= m_tLastSaveTime;		// minus when last saved

		iwait = CAudtestApp::GetAutoSaveTime();

		if ( iwait <= 0)
			return 2;				// this is weird???

		if ( iwait > (tt / 60))		// time to do a save
			return 0;				// nope

		if ( szpath.IsEmpty())
			return 3;				// not yet saved, do nothing

		{
		CString szup = szpath;
			szup.MakeUpper();
		iext = szup.Find( _T(".SWD"));		// fin dit
		}

		if ( -1 != iext)		// use our own
			szpath = szpath.Left( iext);

		szpath += _T(".$.swd");

		bflag = IsModified();		// make sure we keep the modified flag intact

		bout = COleServerDoc::OnSaveDocument(szpath);

		SetModifiedFlag( bflag);

		time( & m_tLastSaveTime);			// update our saved time

		return bout ? 0 : 4;

	}

}


void CAudtestDoc::OnCloseDocument() 
{
	CAudtestApp::SetDocCounter( -1);				// decrement doc counter

	COleServerDoc::OnCloseDocument();
}


// -----------------------------------------------------------------
// -------------  OnResourceExport
// -----------------------------------------------------------------
void	CAudtestDoc::ExportResource( CNamed *pName)
{
CString csext;
CString csfilter;
CString csexport;

		if ( ! pName)
		return;

	pName->GetFilter( csext, csfilter);

	if ( ! csext.GetLength())
		return;			// nothing to do

CFileDialog cdlg( FALSE, csext, NULL, OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, 
					csfilter, NULL );
CString cstitle;

	cstitle.LoadString( IDS_EXPORT);

    cdlg.m_ofn.lpstrTitle = (LPCSTR )cstitle;

	CAudtestApp::GetLastExport( csexport);			// get last file imported
	{			// get the initial directory
	CString csdir;

		if ( !csexport.IsEmpty())
		{
		int islash = csexport.ReverseFind(TCHAR('\\'));		// find the last slash
			if ( islash >= 0)
				csexport = csexport.Left( islash);			// up to the last slash is the directory
			else
				csexport = "";			// empty it
		}
		cdlg.m_ofn.lpstrInitialDir = csexport;
	}

	if ( IDOK == cdlg.DoModal())
		{					// import cdlg.GetPathname();
		csexport = cdlg.GetPathName();
		CAudtestApp::SetLastExport( csexport);
		BeginWaitCursor();
		pName->Export( cdlg.GetPathName());
		EndWaitCursor();
		}

}
