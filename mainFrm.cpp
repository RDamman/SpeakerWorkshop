// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "audtest.h"

#include "afxadv.h"

#include "mainfrm.h"

#include "audtedoc.h"
#include "audtevw.h"
#include "chart.h"
#include "dataset.h"

#include "mmwave.h"
#include "dibapi.h"
#include "Splash.h"

#include "clipbd.h"

#include "Utils.h"

#include "math.h"

#include "BarNetwork.h"			// network dialog

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEdits)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEdits)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEdits)
	ON_UPDATE_COMMAND_UI(ID_RESOURCE_OPEN, OnUpdateEdits)
	ON_UPDATE_COMMAND_UI(ID_EDIT_TEMP, OnUpdateEditTemp)
	//}}AFX_MSG_MAP
				// handle control bars
	ON_COMMAND_EX(CG_ID_VIEW_VUMETER, OnSubBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_VUMETER, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_ID_VIEW_LOCATIONS, OnSubBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_LOCATIONS, OnUpdateControlBarMenu)
	ON_COMMAND_EX(CG_ID_VIEW_TREE, OnSubBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_TREE, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_RESOURCEBAR, OnSubBarCheck)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RESOURCEBAR, OnUpdateControlBarMenu)
			// Global help commands
	ON_COMMAND(ID_HELP_INDEX, CMDIFrameWnd::OnHelpIndex)
	ON_COMMAND(ID_HELP_USING, CMDIFrameWnd::OnHelpUsing)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpIndex)
		// mmio stuff
	ON_MESSAGE( MM_WIM_DATA, OnWimData)
	ON_MESSAGE( MM_WOM_DONE, OnWomDone)
		// indicators
	ON_UPDATE_COMMAND_UI(IDINDIC_FREQ, OnUpdateStatusValues)
	ON_UPDATE_COMMAND_UI(IDINDIC_AMPLITUDE, OnUpdateStatusValues)
	ON_UPDATE_COMMAND_UI(IDINDIC_PHASE, OnUpdateStatusValues)
	ON_UPDATE_COMMAND_UI(IDINDIC_VALUE, OnUpdateStatusValues)
	ON_UPDATE_COMMAND_UI(IDINDIC_RESIST, OnUpdateStatusValues)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars
	
static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	IDINDIC_FREQ,
	IDINDIC_AMPLITUDE,
	IDINDIC_PHASE,
	IDINDIC_POSTPHASE,		// text only
	IDINDIC_VALUE,
	IDINDIC_RESIST
};


static int find_Indicator( UINT idInd)
{
int i;

	for ( i=0; i < sizeof(indicators)/sizeof(UINT); i++)
		if ( indicators[i] == idInd)
			break;

	ASSERT( i != sizeof(indicators)/sizeof(UINT));

	return i;
}



LRESULT CMainFrame::OnWimData( WPARAM, LPARAM)
{
//	PostMessage( WM_COMMAND, ID_SOUND_LOOP, 0L);

	return 0L;
}

LRESULT CMainFrame::OnWomDone( WPARAM, LPARAM)
{
//	PostMessage( WM_COMMAND, ID_SOUND_LOOP, 0L);

	return 0L;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame() : m_wndTree(), m_wndToolBar(), m_wndStatusBar(), m_wndProgress(), 
							m_wndLocations(), m_wndResourceBar(), m_wndVuMeter()
{
	m_nProgressDepth = 0;	
	m_idRestype = 0;
	m_wndResourceDialog = NULL;
}

CMainFrame::~CMainFrame()
{
}

static int build_Bar( CMainFrame *pParent, CToolBar *pWnd, UINT id, UINT menuID)
{
	if (  (!pWnd->Create(pParent, WS_CHILD | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY, menuID)) 
		|| !pWnd->LoadToolBar(id))
		{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
		}

	pWnd->EnableDocking(CBRS_ALIGN_ANY);
	pWnd->SetWindowText( _T("Resource Tools"));

//	pWnd->SetWindowPos( &CWnd::wndTop, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW);
	pParent->DockControlBar( pWnd);

	return 0;
}

static CDialog *build_DialogBar( CMainFrame *pParent, UINT uID)
{
CDialog *pdlg = NULL;

	switch( uID)
	{
	case 0 :			// nothing to do
		break;
	case IDD_NETBAR :
		pdlg = new CBarNetwork( pParent);
		break;
	default :
		ASSERT(0);			// not possible
		break;
	}

	if ( pdlg)
	{
		pdlg->Create( uID);
		pdlg->ShowWindow( SW_SHOW );
	}


	return pdlg;
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	EnableDocking(CBRS_ALIGN_ANY);

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.SetWindowText( _T("General Tools"));
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	if (build_Bar( this, &m_wndResourceBar, IDR_TOOLCHART, ID_VIEW_RESOURCEBAR) )
		return -1;      // fail to create

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
						// now build the progress bar (rather permanently)
	{
	RECT rc;
	::SetRect( &rc, 50,0,50,10);	// arbitrary for now
	m_wndProgress.Create( WS_CHILDWINDOW, rc, &m_wndStatusBar, 12344 );
	}

	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);

	// CG: The following block was inserted by the 'Dialog Bar' component
	// Initialize dialog bar m_wndTree
	if (!m_wndTree.Create(this,	CBRS_LEFT | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE | CBRS_SIZE_DYNAMIC ,
		CG_ID_VIEW_TREE))
	{
		TRACE0("Failed to create dialog bar m_wndTree\n");
		return -1;		// fail to create
	}

	DockControlBar(&m_wndTree);

	// CG: The following block was inserted by the 'Dialog Bar' component
	// Initialize dialog bar m_wndLocations
	if (!m_wndLocations.Create(this, CBRS_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
		CG_ID_VIEW_LOCATIONS))
	{
		TRACE0("Failed to create dialog bar m_wndLocations\n");
		return -1;		// fail to create
	}
	DockControlBar(&m_wndLocations);

	// CG: The following block was inserted by the 'Dialog Bar' component
	// Initialize dialog bar m_wndVuMeter
	if (!m_wndVuMeter.Create(this, CBRS_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
		CG_ID_VIEW_VUMETER))
	{
		TRACE0("Failed to create dialog bar m_wndVuMeter\n");
		return -1;		// fail to create
	}
	DockControlBar(&m_wndVuMeter);

		// put this after the tree bar in Z-order

	m_wndTree.SetWindowPos( &wndTop, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW);
	m_wndToolBar.SetWindowPos( &wndTop, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW);
	m_wndStatusBar.SetWindowPos( &wndTop, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW);
	m_wndStatusBar.SetPaneStyle( find_Indicator( IDINDIC_POSTPHASE), SBPS_NOBORDERS);

	ShowControlBar(&m_wndLocations, FALSE, FALSE);
	ShowControlBar(&m_wndVuMeter, FALSE, FALSE);

			// loadbarstate fails miserably when you get different bars
			//	LoadBarState( _T("SpkrWorkState" ));
	TRY
	{
	LoadBarState(_T("SpkrWorkState" ));
	}
	CATCH_ALL(e)
	{
		// if bar state crashed this should catch it?
	}
	END_CATCH_ALL

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::UpdateTree( CView* , LPARAM lHint, CObject* pHint)
{
CFrameWnd *cframe;
CDocument *pdoc;

	cframe = GetActiveFrame();
	if ( cframe)
		{
		pdoc = cframe->GetActiveDocument();
		if ( pdoc)
			m_wndTree.UpdateTree( pdoc, lHint, pHint);
		}
}

void CMainFrame::CreateProgressBar( UINT uidCaption, UINT uMax)
{
CString cs;

	if ( 1 < m_nProgressDepth)
	{
		m_nProgressDepth++;			// still the next depth
		return;						// do nothing
	}

	cs.LoadString( uidCaption);
	CreateProgressBar( cs, uMax);
}

void CMainFrame::CreateProgressBar( CString& csCaption, UINT uMax)
{
CString cs;
RECT rc;

	if ( 1 < ++m_nProgressDepth)
		return;			// do nothing

	m_wndStatusBar.GetClientRect( &rc);
	cs = csCaption;
	m_wndProgress.SetWindowPos( NULL, 100, rc.top+1, 150, rc.bottom-2, SWP_NOZORDER | SWP_SHOWWINDOW );
	m_wndProgress.SetRange( 0, (WORD )uMax);
	m_wndProgress.SetPos( 0);
	m_wndStatusBar.SetPaneText( 0, (LPCTSTR )cs);
	m_wndStatusBar.UpdateWindow();
}


void CMainFrame::ShowProgressBar( UINT uCurrent)
{
	if ( 1 != m_nProgressDepth)
		return;			// do nothing

	m_wndProgress.SetPos( uCurrent);
}

void CMainFrame::StepProgressBar( void)
{
	if ( 1 != m_nProgressDepth)
		return;			// do nothing

	m_wndProgress.StepIt( );
}

void CMainFrame::IncProgressBar( void)
{
	if ( 1 != m_nProgressDepth)
		return;			// do nothing

	{
	int nlow, nhigh;

		m_wndProgress.GetRange( nlow, nhigh);
		if ( (m_wndProgress.GetPos() + 10 ) > nhigh)		// rollover
			{
			CString cs = m_wndStatusBar.GetPaneText( 0);
			int nlength = cs.GetLength();

				_ASSERT(nlength > 0);

				if ( ')' == cs[nlength-1])	// already have a (x)
					{
					cs.SetAt(nlength-2, (char )(1 + cs[nlength-2]));
					}
				else
					cs += " (1)";
			m_wndStatusBar.SetPaneText( 0, (LPCTSTR )cs);
			m_wndStatusBar.UpdateWindow();
			}

	}

	m_wndProgress.StepIt( );
}

void CMainFrame::CloseProgressBar( void)
{
	if ( (!m_nProgressDepth) || --m_nProgressDepth)
		return;			// do nothing

	m_wndProgress.ShowWindow( SW_HIDE);
	m_wndStatusBar.SetPaneText(0, "");
	m_wndStatusBar.UpdateWindow();
}



// on close, we save the state of all of the toolbars....
void CMainFrame::OnClose() 
{
	SaveBarState(_T("SpkrWorkState" ));

	{
	WINDOWPLACEMENT wp;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		GetWindowPlacement( &wp);

		capp->WriteRegistry( "WindowPlace", &wp, sizeof( wp));

	}

	CMMWave::TurnOffRecording();
	CMMWave::TurnOffSound();

	CMDIFrameWnd::OnClose();

}


BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ( m_wndTree.WantCommand( LOWORD( wParam)) )
		if ( m_wndTree.HasFocus() && m_wndTree.GetCurrentSelection())
			{
					// note, if he has no handler this goes forever....
			m_wndTree.PostMessage( WM_COMMAND, wParam, lParam);
			return TRUE;
			}

	return CMDIFrameWnd::OnCommand(wParam, lParam);
}

void CMainFrame::OnUpdateEdits(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_wndTree.HasFocus() && m_wndTree.GetCurrentSelection());
	
}

void CMainFrame::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	    // See if there is a list available.
    if ( ::OpenClipboard( NULL))
		{
		UINT uiFmt = EnumClipboardFormats(0);

		while (uiFmt)
			{
			if (uiFmt == COpClipPaste::GetFormat())
				{
				CloseClipboard();
				pCmdUI->Enable(TRUE);
				return;
				}
			uiFmt = EnumClipboardFormats( uiFmt);
			}
	    pCmdUI->Enable(FALSE);
    	::CloseClipboard();    
		}
	
}



void CMainFrame::OnUpdateStatusValues(CCmdUI* pCmdUI)
{
static float freq = 0.0f;
static float fdata = 0.0f;
static float fphase = 0.0f;
static float fvalue = 0.0f;
static float fresist = 0.0f;
CString cs;
static bool busedb = FALSE;
static bool busehz = FALSE;

	if ( ! CAudtestApp::GetDocCounter())		// no documents in the workspace, bye
		return;

	switch (pCmdUI->m_nID)
	{
		case IDINDIC_FREQ:
		{
		CFrameWnd *cframe;
		CView *pview = NULL;
		POINT pt;

			cframe = GetActiveFrame();
			if ( cframe)
			{
				pview = cframe->GetActiveView();
			}
			if ( pview && pview->IsKindOf( RUNTIME_CLASS(CAudchView)))
			{
			CAudchView *pch = (CAudchView *)pview;
			CSubChart *cc = (CSubChart *)pch->GetViewChart();

				if ( cc)			// we have a chart view on top
				{
					CDataSet *cn;
					GetCursorPos( &pt);
					if ( pview == WindowFromPoint( pt))	// it is in the point
					{		// we're here, now update the info
						pview->ScreenToClient( &pt);
						cn = cc->GetDatasetAt(0);
						float f = cc->ConvertXLocation( pt.x);
						if ( cn && f >= cn->Minimum(dataFreq) && f <= cn->Maximum( dataFreq))
						{
							{	// convert to actual frequency
							int i = cn->FreqToIndex( f);
							f = cn->DataAt( dataFreq, i);
							}
							freq = f;
							fdata = cn->DataValueAt( freq);
							fphase = cn->PhaseValueAt( freq);
							busedb = (uomOhms != cn->GetUOM()) && (uomTime != cn->GetUOM());		// db for everything else
							busehz = uomTime != cn->GetUOM();
							if ( freq && fdata && uomOhms == cn->GetUOM())
							{		// calculate the relative RLC
								cn->GetRectangularAt(freq, &fresist, &fvalue);
								if ( fvalue < 0)		// capacitor
									fvalue = (float )(1 / (2 * ONEPI * freq * fvalue));
								else					// inductor
									fvalue = (float )(fvalue / (2 * ONEPI * freq));
							}
							else
							{
								fvalue = 0.0f;
								fresist = 0.0f;
							}
						}
					}
				}

			}
			if ( m_wndStatusBar.GetSafeHwnd())
			{
				::FullFormatValue(cs, freq, ( freq > 1000) ? 0 : -4);
				if ( CAudtestApp::GetLongStatus())
				{
					if ( busehz)
						AddStringSuffix( cs, IDS_HERTZ, false);
					else
						AddStringSuffix( cs, IDS_MSEC);
				}
				m_wndStatusBar.SetPaneText( find_Indicator(pCmdUI->m_nID) , cs);
			}

		}
		break;

		case IDINDIC_AMPLITUDE:
			if ( m_wndStatusBar.GetSafeHwnd())
			{
				::FullFormatValue(cs, fdata, -5);
				if ( CAudtestApp::GetLongStatus())
					if ( busedb)
						AddStringSuffix(cs, IDS_DB, false);
					else
						if ( busehz)
							AddStringSuffix(cs, IDS_OHM, false);
				m_wndStatusBar.SetPaneText( find_Indicator(pCmdUI->m_nID) , cs);
			}
			break;

		case IDINDIC_PHASE:
			if ( m_wndStatusBar.GetSafeHwnd())
				{
				::FullFormatValue(cs, fphase, -3);
				if ( cs.GetLength() && CAudtestApp::GetLongStatus())
					AddStringSuffix(cs, IDS_DEGREE ,false);
				m_wndStatusBar.SetPaneText( find_Indicator(pCmdUI->m_nID) , cs);
				}
			break;

		case IDINDIC_VALUE:
			if ( m_wndStatusBar.GetSafeHwnd())
				{
				::FullFormatValue(cs, (float )fabs(fvalue), -5);
				if ( fvalue < 0)			// capacitor
					AddStringSuffix(cs, IDS_FARAD, false);
				else if ( fvalue > 0)
					AddStringSuffix(cs, IDS_HENRY, false);
				m_wndStatusBar.SetPaneText( find_Indicator(pCmdUI->m_nID) , cs);
				}
			break;

		case IDINDIC_RESIST:
			if ( m_wndStatusBar.GetSafeHwnd())
				{
				::FullFormatValue(cs, fresist, -3);
				if ( cs.GetLength() && CAudtestApp::GetLongStatus())
					AddStringSuffix(cs, IDS_OHM, false);
				m_wndStatusBar.SetPaneText( find_Indicator(pCmdUI->m_nID) , cs);
				}
			break;

		default:
			TRACE1("Warning: OnUpdateStatusValue - unknown indicator 0x%04X.\n", pCmdUI->m_nID);
			pCmdUI->ContinueRouting();
			return; // not for us
		}

}


void CMainFrame::ResetToolbar( CView *pNewView)
{
CAudtestView *pview = (CAudtestView *)pNewView;
UINT idres;
UINT idbar;

	if ( pview)			// when shutting down, pview is null
	{
	CNamed *pobj = pview->GetTargetObject();

		if ( pobj)			// there is a target
		{
			switch( pobj->GetType())
				{
				case ntChart :
					idres = IDR_TOOLCHART;
					idbar = 0;
					break;
				case ntDriver :
					idres = IDR_TOOLDRIVER;
					idbar = 0;
					break;
				case ntEnclosure :
					idres = IDR_TOOLENCL;
					idbar = 0;
					break;
				case ntNetwork :
					idbar = IDD_NETBAR;
					idres = IDR_TOOLNETWORK;
					break;
				case ntGenerator :
					idres = IDR_TOOLSIGNAL;
					idbar = 0;
					break;
				default :
					idbar = 0;
					idres = IDR_TOOLCHART;
					break;
				}

			if ( idres != m_idRestype)
				{
				m_wndResourceBar.LoadToolBar( idres);	// new toolbar
				m_idRestype = idres;					// save the id
				if ( (m_idResDialog != idbar) || idbar)
				{
					if ( m_wndResourceDialog)
					{
						if ( m_wndResourceDialog->GetSafeHwnd())
							m_wndResourceDialog->SendMessage( WM_CLOSE);		// close it
						m_wndResourceDialog = NULL;
					}
					m_wndResourceDialog = build_DialogBar( this, idbar);
				}

			RecalcLayout();
			}
		}
	}

}

VuValues CMainFrame::GetVuValues( bool bRight)
{
VuValues vnew;

	if ( bRight)
	{
		m_wndVuMeter.GetRightEntries( vnew.fMax, vnew.fAve, vnew.fMin);
	}
	else
		m_wndVuMeter.GetLeftEntries( vnew.fMax, vnew.fAve, vnew.fMin);

	return vnew;
}


void	CMainFrame::SetVuValues( VuValues &vuNew, bool bRight)
{
	if ( bRight)
	{
		SetRightValues( vuNew.fMax, vuNew.fAve, vuNew.fMin);
	}
	else
		SetLeftValues( vuNew.fMax, vuNew.fAve, vuNew.fMin);

}


void CMainFrame::SetLeftValues( float fMax, float fAve, float fMin)
{
	m_wndVuMeter.SetLeftEntries( fMax, fAve, fMin);
}



void CMainFrame::SetRightValues( float fMax, float fAve, float fMin)
{
	m_wndVuMeter.SetRightEntries( fMax, fAve, fMin);
}


// this calls the mainframe standard barcheck routine

BOOL CMainFrame::OnSubBarCheck(UINT nID)
{
	return OnBarCheck( nID);
}

// this is currently not being used, but it we put maketemp into a 
// make menu it will run correctly
void CMainFrame::OnUpdateEditTemp(CCmdUI* pCmdUI) 
{
	TreeBar()->GetControl()->OnUpdateEditTemp( pCmdUI);
	
}

CDialog * CMainFrame::GetDialogBar()
{
	return m_wndResourceDialog;
}
