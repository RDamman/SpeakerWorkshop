// audtest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "audtest.h"

#include "Winreg.h"

#include "mainfrm.h"
#include "childfrm.h"
#include "ipframe.h"
#include "audtedoc.h"

#include <afxadv.h>

#include "audtevw.h"

#include "vwChart.h"
#include "vwData.h"
#include "vwDrive.h"
#include "vwEncl.h"
#include "vwGen.h"
#include "vwNet.h"
#include "vwRoom.h"
#include "vwTree.h"

#include "Chart.h"

#include "fxFont.h"

#include "dlgprefer.h"
#include "dlglocat.h"
#include "dlgAudioCheck.h"

#include "dibapi.h"
#include "Splash.h"
#include <dos.h>

#include "SetLocale.h"

#include <direct.h>
#include <locale.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// the stock default color definitions
static COLORREF c_Lines[8] = { RGB(0,0,0), RGB(0xff,0,0), RGB(0,0, 0xff), RGB(0xff,0, 0xff),
							 RGB(0,0x80,0x80), RGB(0x80,0,0x80), RGB(0,0x80,0x80), RGB(0xff,0xff,0xff) };
static COLORREF c_PhaseLines[8] = { RGB(0x80,0x80,0x80), RGB(0x80,0,0), RGB(0,0, 0x80), RGB(0x80,0x80,0x80),
							 RGB(0,0x40,0x40), RGB(0x40,0,0x40), RGB(0,0x40,0x40), RGB(0x40,0x40,0x40) };


/////////////////////////////////////////////////////////////////////////////
// CAudtestApp

BEGIN_MESSAGE_MAP(CAudtestApp, CWinApp)
	//{{AFX_MSG_MAP(CAudtestApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_OPTIONS_PREFERENCES, OnOptionsPreferences)
	ON_COMMAND(ID_WIZARD_CHECKSOUNDCARD, OnWizardChecksoundcard)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_OPTIONS_SAVEREGISTRY, OnOptionsSaveregistry)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudtestApp construction

static char *strDisplay = "Display";
static char *strTransform = "Transform";
static char *strNetwork = "Network";
static char *strInterface = "Interface";
static char *strColorDef = "ColorDefinitions";

			// the dialog we communicate with to show coordinates
static CDlgLocations *dlg_Location = NULL;

CAudtestApp::CAudtestApp()
{
	m_iDocCounter = 0;					// start with no documents
	// Place all significant initialization in InitInstance
	m_nFftWindow = 0;					// the fft windowing
	m_nResistorType = 0;				// squiggles
	m_nDrawEndpoints = 1;				// start drawing them
	m_bUnaryInPlace = TRUE;				// do these in-place?
	m_bUnaryIncrement = FALSE;			// autoincrement if not in-place?
	m_bBinaryInPlace = TRUE;
	m_bBinaryIncrement = FALSE;
	m_bShowLongTitle = FALSE;
	m_bShowPath = FALSE;
	m_bIsMetric = FALSE;
	m_ptNetGrid.x = m_ptNetGrid.y = 0;
	m_bLongStatus = TRUE;
	m_fRightShift = 0.0f;
	m_bSingleClick = FALSE;
	m_pCurrentView = NULL;
	m_iMeasureTrails = 0;
	m_iAllowedLocale = 0;

	m_pTreeView = NULL;
	m_pcslLocale = NULL;

	m_CChartDefaults[uomTime] = NULL;
	m_CChartDefaults[uomFreq] = NULL;
	m_CChartDefaults[uomOhms] = NULL;
	
}

static CMultiDocTemplate *doc_Template( UINT iType, CRuntimeClass *cNew)
{
 CMultiDocTemplate *pDocTemplate;

	pDocTemplate = new CMultiDocTemplate(
		iType,
		RUNTIME_CLASS(CAudtestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		cNew);
	pDocTemplate->SetServerInfo(
		IDR_AUDTESTYPE_SRVR_EMB, IDR_AUDTESTYPE_SRVR_IP,
		RUNTIME_CLASS(CInPlaceFrame));
	return pDocTemplate;
}



/////////////////////////////////////////////////////////////////////////////
// The one and only CAudtestApp object

CAudtestApp theApp;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.
static const CLSID BASED_CODE clsid =
{ 0x18fc420, 0x7ee6, 0x11ce, { 0xbc, 0x27, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

/////////////////////////////////////////////////////////////////////////////
// CAudtestApp initialization

static void get_MostRecent( CString &csFile)
{
const TCHAR szFileSection[] = _T("Recent File List");
const TCHAR szFileEntry[] = _T("File%d");
int nmaxmru = 1;
CRecentFileList recent( 0, szFileSection, szFileEntry, nmaxmru);
	recent.ReadList();
	if ( recent.GetSize() && recent[0].GetLength())
	{
		csFile = recent[0];
	}
	else
		csFile = "";
}

BOOL CAudtestApp::InitInstance()
{
	// CG: The following block was added by the Splash Screen component.
#ifdef _DEBUG
				// this exercises ram severely
	afxMemDF |= checkAlwaysMemDF;
#endif
	
	{
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);

		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
	}

	{
					// TEMPORARY RESET HELP FILE NAME
	free( (void *)m_pszHelpFilePath);
	m_pszHelpFilePath = _tcsdup("SpkrWork.Hlp");
	}

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	SetRegistryKey( "Audua");			// !!!!

	FixRegistry();						// make sure valid registry

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
#ifdef _DEBUG
	{
		CString ctext;
		char c;
			ctext.LoadString ( AFX_IDS_OPENFILE);
			c = ctext[0];
	}
#endif

				// --------------------- tree
	m_pTreeView = doc_Template( IDR_AUDTREETYPE, RUNTIME_CLASS(CAudTreeView));
	AddDocTemplate(m_pTreeView);
	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, m_pTreeView, FALSE);

	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleTemplateServer::RegisterAll();
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes();	// do this before adding the rest of the file types

	// ---------------- mz initialization -----------
				// --------------------- gen
	m_pGenView = doc_Template( IDR_AUDGENTYPE,  RUNTIME_CLASS(CAudGenView));
	AddDocTemplate(m_pGenView);
				// --------------------- chart
	m_pChartView = doc_Template( IDR_AUDCHARTTYPE,  RUNTIME_CLASS(CAudChartView));
	AddDocTemplate(m_pChartView);
				// --------------------- data
	m_pDataView = doc_Template( IDR_AUDDATATYPE,  RUNTIME_CLASS(CAudDataView));
	AddDocTemplate(m_pDataView);
				// --------------------- network
	m_pNetView = doc_Template( IDR_AUDNETTYPE,  RUNTIME_CLASS(CAudNetView));
	AddDocTemplate(m_pNetView);
				// --------------------- enclosure
	m_pEnclView = doc_Template( IDR_AUDENCLTYPE,  RUNTIME_CLASS(CAudEnclView));
	AddDocTemplate(m_pEnclView);

				// --------------------- room
	m_pRoomView = doc_Template( IDR_AUDROOMTYPE,  RUNTIME_CLASS(CAudRoomView));
	AddDocTemplate(m_pRoomView);

				// --------------------- Driver
	m_pDriverView = doc_Template( IDR_AUDDRIVETYPE,  RUNTIME_CLASS(CAudDriverView));
	AddDocTemplate(m_pDriverView);

				// --------------------------------------------------------------------
				// get and then set the locale early so we interpret floats right
				// when reading from the registry
	m_iAllowedLocale	= GetProfileInt( strInterface,	"AllowedLocale", 0);
	{
	char *locl;

		if ( m_iAllowedLocale)
		{
			if ( 1 == m_iAllowedLocale)
				m_pcslLocale = new CSetLocale( LC_ALL);			// set default locale
			else
			{
				m_pcslLocale = new CSetLocale( LC_ALL, MAKELCID( m_iAllowedLocale, SORT_DEFAULT));
			}

		}
		locl = setlocale(LC_ALL,NULL);	// get it	just fyi for debugging
	}
				// --------------------------------------------------------------------

	m_nFftWindow		= GetProfileInt( strTransform, "FftWindow", 0);
	m_bUnaryInPlace		= GetProfileInt( strTransform, "UnaryInPlace", 1);
	m_bUnaryIncrement	= GetProfileInt( strTransform, "UnaryIncrement", 0);
	m_bBinaryInPlace	= GetProfileInt( strTransform, "BinaryIncrement", 0);
	m_bBinaryIncrement	= GetProfileInt( strTransform, "BinaryInPlace", 0);

	m_bShowLongTitle	= GetProfileInt( strDisplay,	"ShowLongTitle", 0);
	m_bShowPath			= GetProfileInt( strDisplay,	"ShowPath", 0);
	m_bIsMetric			= GetProfileInt( strDisplay,	"IsMetric", 0);
	m_bLongStatus		= GetProfileInt( strDisplay,	"LongStatus", 1);
	m_fRightShift		= GetProfileFloat( strDisplay,	"RightShift", 0);

	m_ptNetGrid.x		= GetProfileInt( strNetwork,	"NetGridX", 0);
	m_ptNetGrid.y		= GetProfileInt( strNetwork,	"NetGridY", 0);
	m_nResistorType		= GetProfileInt( strNetwork,	"ResistorType", 0);
	m_nDrawEndpoints	= GetProfileInt( strNetwork,	"DrawEndpoints", 1);

	m_bSingleClick		= GetProfileInt( strInterface,	"SingleClick", 0);
	m_nLastPreference	= GetProfileInt( strInterface,	"LastPreference", 0);
	m_iMeasureTrails	= GetProfileInt( strInterface,	"MeasureTrails", 0);
	m_bDisable48K		= 0 != GetProfileInt( strInterface,	"Disable48K", 0);
	m_bDisable96K		= 0 != GetProfileInt( strInterface,	"Disable96K", 1);
	m_iAutoSaveTime		= GetProfileInt( strInterface,	"AutoSaveTime", 10);
	m_bAutoSave			= GetProfileInt( strInterface,  "AutoSave", 0);

	m_csLastImport		= GetProfileString( strInterface, "ImportFile");
	m_csLastExport		= GetProfileString( strInterface, "ExportFile");
	m_csLastFile		= GetProfileString( strInterface, "DocFile");

	{			// set up the default colors
	int i;
	int jphase;
	int iuom;
	ColorDefinition cdef;
	COLORREF *psrc;

		for ( iuom = 0; iuom < uomNone; iuom++)
			for ( jphase = 0; jphase < 2; jphase++)
			{
			cdef.m_nWidth = 1;
			cdef.m_nStyle = (jphase ? PS_DOT : PS_SOLID);
			psrc = (jphase ? c_PhaseLines : c_Lines);

				for ( i=0; i<NUMCOLORDEF; i++)
				{
					cdef.m_clrRgb = psrc[i];
					m_ColorDefs[iuom][i + jphase * NUMCOLORDEF] = cdef;
				}
			}
	}

	ReadRegistry( strColorDef, m_ColorDefs, sizeof( m_ColorDefs));

	m_bUseLast			= GetProfileInt( "Startup",		"UseLast", 1);

	m_bIsWorking		= FALSE;			// not loaded, but set

	m_nPrecisions[0] = GetProfileInt( strNetwork, "Precision", 3);

	m_nShowChannels  = (enChannel )GetProfileInt("Signal", "ShowChannels", chMono);

	// ---------------- ---------------- ---------------- ---------------- 
	// ---------------- Measurement Preferences
	// ---------------- ---------------- ---------------- ---------------- 
	if (  ReadRegistry( "Measure", &m_Measures, sizeof( m_Measures) ))
		{			// not yet saved a change...
		m_Measures.nSampleRate = 44100;
		m_Measures.nSampleSize = 2048;
		m_Measures.nNumberSamples = 1;
		m_Measures.bEmphasis = 	FALSE;
		m_Measures.bReverseChannel = FALSE;
		m_Measures.fResistor = 	10.0f;
		m_Measures.fSeriesRes = 0.2f;
		m_Measures.fInputRes = 1000000.0f;
		m_Measures.fInputCap = 0.0f;
		m_Measures.fPlayVolume = 50.0f;
		}

	// ---------------- ---------------- ---------------- ---------------- 
	// ---------------- Latency Preferences
	// ---------------- ---------------- ---------------- ---------------- 
	if (  ReadRegistry( "Latency", &m_fLatency, sizeof( float) ))
		{			// not yet saved a change...
		m_fLatency = 0.0f;
		}

	if (  ReadRegistry( "Warmup", &m_iWarmup, sizeof( int) ))
		{			// not yet saved a change...
		m_iWarmup = 100;
		}

	// ---------------- ---------------- ---------------- ---------------- 
	// ---------------- Marker Preferences
	// ---------------- ---------------- ---------------- ---------------- 
	if (  ReadRegistry( "Marker", &m_Markers, sizeof( m_Markers) ))
		{			// not yet saved a change...
		m_Markers.tmTime.bUse = FALSE;		// use time markers
		m_Markers.tmFreq.bUse = FALSE;		// use frequency markers
		m_Markers.tmOhms.bUse = FALSE;
		m_Markers.tmFreq.fStart = 20.0f;
		m_Markers.tmFreq.fEnd = 1000.0f;
		m_Markers.tmOhms.fStart = 20.0f;
		m_Markers.tmOhms.fEnd = 1000.0f;
		m_Markers.tmTime.fStart = 0.0f;
		m_Markers.tmTime.fEnd = 10.0f;
		}

	{
	short i;

		for ( i=0; i<NUMFONTTYPES; i++)
			{
			m_cfAppFonts[i].ReadIni( i);
			}

	}

	ReadAppColors();

	// ---------------- ---------------- ---------------- ---------------- 
	// ---------------- Enclosure Preferences
	// ---------------- ---------------- ---------------- ---------------- 
	if (  ReadRegistry( "EnclosureInfo", &m_EnclosureInfo, sizeof( m_EnclosureInfo) ))
		{
		m_EnclosureInfo.bConeExcursion = 1;
		m_EnclosureInfo.bFreqResponse = 1;
		m_EnclosureInfo.bGroupDelay = 1;
		m_EnclosureInfo.bImpedance = 1;
		m_EnclosureInfo.bTransient = 1;
		}

	// ---------------- ---------------- ---------------- ---------------- 
	// ---------------- mz initialization -----------
	// ---------------- ---------------- ---------------- ---------------- 

	// Parse the command line to see if launched as OLE server
	if (RunEmbedded() || RunAutomated())
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
	m_server.UpdateRegistry(OAT_INPLACE_SERVER);
	COleObjectFactory::UpdateRegistryAll();

	m_CChartDefaults[uomTime] = new CSubChart();
	m_CChartDefaults[uomTime]->CreateDefault("xxx", uomTime);

	m_CChartDefaults[uomFreq] = new CSubChart();
	m_CChartDefaults[uomFreq]->CreateDefault("xxx", uomFreq);

	m_CChartDefaults[uomOhms] = new CSubChart();
	m_CChartDefaults[uomOhms]->CreateDefault("xxx", uomOhms);

	// simple command line parsing
	if (m_lpCmdLine[0] == '\0')
	{
		// create a new (empty) document
		if ( m_bUseLast)	// default to no last document
			{				// create file MRU since nMaxMRU not zero
			CString csfile;

			get_MostRecent( csfile);
			if (! csfile.IsEmpty())
			{
				OpenDocumentFile( csfile);
				SetLastFile( csfile);			// last opened
			}
			else
				OnFileNew();
			}
		else
			OnFileNew();
	}
	else
	{
		// open an existing document
		OpenDocumentFile(m_lpCmdLine);
	}

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

				// set window size
	{
	WINDOWPLACEMENT wp;

		if ( ! ReadRegistry( "WindowPlace", &wp, sizeof( wp) ))	// it worked
			{
			wp.length = sizeof( wp);
			wp.flags = 0;
			pMainFrame->SetWindowPlacement( &wp);
			}
	}

	CTopDebug::GetDebugObj()->Init( m_pMainWnd);

	return TRUE;
}

// --------------------------------------------------------------------------------
//		WriteBigRegEntries
//			write the big stuff (usually on an exit)
// --------------------------------------------------------------------------------
void CAudtestApp::WriteBigRegEntries( void)
{
	WriteRegistry( strColorDef, m_ColorDefs, sizeof( m_ColorDefs));
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// Implementation
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CAudtestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CAudtestApp commands

CMultiDocTemplate *CAudtestApp::GetTemplate( int nType)
{
	switch( nType)
		{
		case ntGenerator:
			return m_pGenView;
		case ntDataSet:
			return m_pDataView;
		case ntChart:
			return m_pChartView;
		case ntEnclosure:
			return m_pEnclView;
		case ntNetwork:
			return m_pNetView;
		case ntRoom:
			return m_pRoomView;
		case ntDriver:
			return m_pDriverView;
		case ntFolder:
			return m_pTreeView;
		}

	ASSERT(0);			// uh oh
	return m_pTreeView;
}

void CAudtestApp::OnOptionsPreferences() 
{
CDlgPreference cdlg;

	if ( IDOK == cdlg.DoModal( ) )
		{
		CAudtestView *pview = (CAudtestView *)GetCurrentView();
		if ( pview)
			pview->GetDocument()->UpdateAll( NULL, 0);
		}

}

void CAudtestApp::SetDisable48K( bool bNew)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	capp->m_bDisable48K = bNew;
	capp->WriteProfileInt( strInterface, "Disable48K", bNew ? 1 : 0);
}

bool CAudtestApp::GetDisable96K()
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_bDisable96K;
}

void CAudtestApp::SetDisable96K( bool bNew)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	capp->m_bDisable96K = bNew;
	capp->WriteProfileInt( strInterface, "Disable96K", bNew ? 1 : 0);
}

bool CAudtestApp::GetDisable48K()
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_bDisable48K;
}

void 	CAudtestApp::SetFftWindow(int nNew)
{
	m_nFftWindow = nNew;
	WriteProfileInt( strTransform, "FftWindow", m_nFftWindow);
}

void	CAudtestApp::GetLastImport( CString &csImport)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	csImport = capp->m_csLastImport;
}

void	CAudtestApp::SetLastImport( LPCTSTR csImport)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	capp->m_csLastImport = csImport;
	capp->WriteProfileString( strInterface, "ImportFile", csImport);
}

void	CAudtestApp::GetLastExport( CString &csExport)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	csExport = capp->m_csLastExport;
}

void	CAudtestApp::SetLastExport( LPCTSTR csExport)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	capp->m_csLastExport = csExport;
	capp->WriteProfileString( strInterface, "ExportFile", csExport);
}

void	CAudtestApp::GetLastFile( CString &csFile)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	csFile = capp->m_csLastFile;
}

void	CAudtestApp::SetLastFile( LPCTSTR csFile)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	capp->m_csLastFile = csFile;
	capp->WriteProfileString( strInterface, "DocFile", csFile);
}


void CAudtestApp::SetMeasures( LPTESTMSR lpSource)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
TESTMSR tm;

	capp->m_Measures = *lpSource;
	tm = *lpSource;
	capp->WriteRegistry( "Measure", &tm, sizeof( tm));
}

void CAudtestApp::GetMeasures( LPTESTMSR lpDest)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	*lpDest = capp->m_Measures;
}

void CAudtestApp::SetLatency( float fNew)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	capp->m_fLatency = fNew;
	capp->WriteRegistry( "Latency", &fNew, sizeof( float));
}

void CAudtestApp::GetLatency( float *fGot)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	*fGot = capp->m_fLatency;
}

// ------------------------------------------------------------------
//			Warmup
// ------------------------------------------------------------------
void CAudtestApp::SetWarmup( int iNew)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	capp->m_iWarmup = iNew;
	capp->WriteRegistry( "Warmup", &iNew, sizeof( int));

}

int CAudtestApp::GetWarmup( void)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_iWarmup;
}

// ------------------------------------------------------------------
//			ColorDefinitions
// ------------------------------------------------------------------
ColorDefinition CAudtestApp::GetColorDefinition(bool bPhase, UNITMSR uUom, int iIndex)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	ASSERT( uUom < uomNone);			// make sure it fits
	iIndex = iIndex % NUMCOLORDEF;		// rotate through the list
	if ( bPhase)
		iIndex += NUMCOLORDEF;			// go to next group if phase
	return capp->m_ColorDefs[(int )uUom][iIndex];
}

void CAudtestApp::SetColorDefinition( bool bPhase, UNITMSR uUom, int iIndex, ColorDefinition *pNew)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	ASSERT( uUom < uomNone);			// make sure it fits
	iIndex = iIndex % NUMCOLORDEF;		// rotate through the list
	if ( bPhase)
		iIndex += NUMCOLORDEF;			// go to next group if phase
	capp->m_ColorDefs[(int )uUom][iIndex] = *pNew;

}

// ------------------------------------------------------------------
//			DocCounter
// ------------------------------------------------------------------
void CAudtestApp::SetDocCounter( int iNew)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	capp->m_iDocCounter += iNew;
			// this doesn't get written to the registry
}

int CAudtestApp::GetDocCounter( void)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_iDocCounter;
}

// ------------------------------------------------------------------
//			Trails
// ------------------------------------------------------------------

int		CAudtestApp::GetTrails( void)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_iMeasureTrails;

}

void	CAudtestApp::SetTrails( int nType)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( nType != capp->m_iMeasureTrails)
		{
		capp->m_iMeasureTrails = nType;
		capp->WriteProfileInt( strInterface, "MeasureTrails", nType);
		}

}

// ------------------------------------------------------------------
//			AllowedLocale
// ------------------------------------------------------------------

int		CAudtestApp::GetAllowedLocale( void)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_iAllowedLocale;

}

void	CAudtestApp::SetAllowedLocale( int nType)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( nType != capp->m_iAllowedLocale)
		{
			capp->m_iAllowedLocale = nType;
			capp->WriteProfileInt( strInterface, "AllowedLocale", nType);
			if (capp->m_pcslLocale)
				delete capp->m_pcslLocale;		// delete the locale guy
			capp->m_pcslLocale = NULL;
			if ( 0 == nType)		// turn it off
			{
				setlocale(LC_ALL, "C");			// set to off
			}
			else if ( 1 == nType)
			{
				capp->m_pcslLocale = new CSetLocale( LC_ALL);
			}
			else
				capp->m_pcslLocale = new CSetLocale( LC_ALL, MAKELCID( nType, SORT_DEFAULT));
		}

}


// ------------------------------------------------------------------
//			AutoSave
// ------------------------------------------------------------------

BOOL CAudtestApp::GetAutoSave( void)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_bAutoSave;

}


void CAudtestApp::SetAutoSave( BOOL bNew)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( bNew != capp->m_bAutoSave)
		{
		capp->m_bAutoSave = bNew;
		capp->WriteProfileInt( strInterface, "AutoSave", bNew);
		}

}

int  CAudtestApp::GetAutoSaveTime( void)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_iAutoSaveTime;

}

void CAudtestApp::SetAutoSaveTime( int iNew)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( iNew != capp->m_iAutoSaveTime)
		{
		capp->m_iAutoSaveTime = iNew;
		capp->WriteProfileInt( strInterface, "AutoSaveTime", iNew);
		}


}



// ------------------------------------------------------------------
//		EnclosureInfo
// ------------------------------------------------------------------
void CAudtestApp::SetEnclosureInfo( ENCLINFO& cNew)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	capp->m_EnclosureInfo = cNew;
	capp->WriteRegistry( "EnclosureInfo", &cNew, sizeof( cNew));
}

void CAudtestApp::GetEnclosureInfo( ENCLINFO& nDest)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	nDest = capp->m_EnclosureInfo;
}

// ------------------------------------------------------------------
//		--- RecordingInfo functions
// ------------------------------------------------------------------

void CAudtestApp::SetRecordingInfo( RECORDINGINFO *pNew)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	capp->WriteRegistry( IDS_RECORDINFO, pNew, sizeof( RECORDINGINFO));
}

void CAudtestApp::GetRecordingInfo( RECORDINGINFO *pDest)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( capp->ReadRegistry(IDS_RECORDINFO, pDest, sizeof( RECORDINGINFO)))
		{
		pDest->m_bOutput = TRUE;			// --- test specific
		pDest->m_fDataAmplitude = 100.0f;	// amplitude of wave
		pDest->m_nDataChannel = chRight;		// channel to use for data
		pDest->m_nCalibChannel = chLeft;	// calibration channel
		pDest->m_nOutChannel = chBoth;
		pDest->m_fInLeftVolume = 100.0f;
		pDest->m_fInRightVolume = 100.0f;		// left and right input volume settings
		pDest->m_fPlayTime = 0.1f;
		pDest->m_fRecordTime = 0.1f;
		pDest->m_nDataType = 0;		// type of data to generate (freq/time/impedance)
		}

	pDest->m_bIsRecording = FALSE;		// type of data to generate (freq/time/impedance)
	pDest->m_bLoopRecord = FALSE;		// type of data to generate (freq/time/impedance)
	pDest->m_bLoopPlay = FALSE;		// type of data to generate (freq/time/impedance)
}


// ------------------------------------------------------------------
//		--- AcousticInfo functions
// ------------------------------------------------------------------

void CAudtestApp::SetAcousticInfo( ACOUSTICINFO *pNew)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	capp->WriteRegistry( IDS_ACOUSTICINFO, pNew, sizeof( ACOUSTICINFO));
}

void CAudtestApp::GetAcousticInfo( ACOUSTICINFO *pDest)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( capp->ReadRegistry(IDS_ACOUSTICINFO, pDest, sizeof( ACOUSTICINFO)))
		{
		pDest->m_nMicChannel = chRight;
		pDest->m_nRefChannel = chLeft;		// default to right and left
		}

}


// ------------------------------------------------------------------
//		--- marker functions
// ------------------------------------------------------------------

void CAudtestApp::ShowMarker( int nMarker, BOOL bNewValue)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
LPMARKERINFO lpmark = capp->GetMarkerInfo();

	switch( nMarker)
		{
		case 0 :
			lpmark->tmTime.bUse = bNewValue;
			break;
		case 1 :
			lpmark->tmFreq.bUse = bNewValue;
			break;
		case 2 :
			lpmark->tmOhms.bUse = bNewValue;
			break;
		}

	capp->WriteRegistry( "Marker", lpmark, sizeof( MARKERINFO));
}

BOOL CAudtestApp::IsMarkerShown( int nMarker)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
LPMARKERINFO lpmark = capp->GetMarkerInfo();

	switch( nMarker)
		{
		case 0 :
			return lpmark->tmTime.bUse;
		case 1 :
			return lpmark->tmFreq.bUse;
		case 2 :
			return lpmark->tmOhms.bUse;
		}
	return FALSE;
}

LPTESTMARK CAudtestApp::GetMarker(int nMarker )
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
LPMARKERINFO lpmark = capp->GetMarkerInfo();

	switch( nMarker)
		{
		case 0 :
			return &lpmark->tmTime;
		case 1 :
			return &lpmark->tmFreq;
		case 2 :
			return &lpmark->tmOhms;
		}
	return NULL;

}

void	CAudtestApp::SetMarker( int nMarker, LPTESTMARK lpInput)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
LPMARKERINFO lpmark = capp->GetMarkerInfo();

	switch( nMarker)
		{
		case 0 :
			lpmark->tmTime = *lpInput;
			break;
		case 1 :
			lpmark->tmFreq = *lpInput;
			break;
		case 2 :
			lpmark->tmOhms = *lpInput;
			break;
		}

	capp->WriteRegistry( "Marker", lpmark, sizeof( MARKERINFO));
}


void	CAudtestApp::SetInPlace( BOOL bBinary, BOOL bNew)
{
	if ( bBinary)
		{
		m_bBinaryInPlace = bNew;
		WriteProfileInt( strTransform, "BinaryIncrement", m_bBinaryInPlace);
		}
	else
		{
		m_bUnaryInPlace = bNew;
		WriteProfileInt( strTransform, "UnaryInPlace", m_bUnaryInPlace);
		}
}

void	CAudtestApp::SetIncrement( BOOL bBinary, BOOL bNew)
{
	if ( bBinary)
		{
		m_bBinaryIncrement = bNew;
	 	WriteProfileInt( strTransform, "BinaryInPlace", m_bBinaryIncrement);
		}
	else
		{
		m_bUnaryIncrement = bNew;
		WriteProfileInt( strTransform, "UnaryIncrement", m_bUnaryIncrement);
		}
}

CFxFont &CAudtestApp::GetAppFont( FONTTYPES ftSelect)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
int ntype = (int )ftSelect;

	if ( ntype < NUMFONTTYPES)
		return capp->m_cfAppFonts[ntype];

	ASSERT(0);
	return capp->m_cfAppFonts[ftTitle]; 
}

void	CAudtestApp::EditAppFont( FONTTYPES ftSelect)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
int ntype = (int )ftSelect;

	if ( ntype < NUMFONTTYPES)
		capp->m_cfAppFonts[ntype].EditProperties();
}

COLORREF  CAudtestApp::GetAppColor( APPCOLORS clrSelect)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
int ntype = (int )clrSelect;

	if ( ntype < NUMAPPCOLORS)
		return capp->m_clrAppColors[ntype];

	ASSERT(0);
	return capp->m_clrAppColors[ntype];
}

void CAudtestApp::SetAppColor( APPCOLORS clrSelect, COLORREF clrSet)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
int ntype = (int )clrSelect;

	if ( ntype < NUMAPPCOLORS)
		capp->m_clrAppColors[ntype] = clrSet;
}

void CAudtestApp::ReadAppColors()
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	capp->m_clrAppColors[0] = RGB(0xff,0xff,0xff);		// background color
	capp->m_clrAppColors[1] = RGB(0x40,0x40,0x40);		// grid color
	capp->m_clrAppColors[2] = RGB(0xc0,0xc0,0xc0);		// ingraph color

	capp->ReadRegistry( IDS_CHARTDEF, capp->m_clrAppColors, sizeof( capp->m_clrAppColors));
}

void	CAudtestApp::WriteAppColors()
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	capp->WriteRegistry( IDS_CHARTDEF, capp->m_clrAppColors, sizeof( capp->m_clrAppColors));
}

void CAudtestApp::ClearAllPrinterFonts( void)
{
int i;
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	for ( i=0; i<NUMFONTTYPES; i++)
		capp->m_cfAppFonts[i].ClearPrinterFonts();

}

// ------------------------------------------------------------------
//			Precision
// ------------------------------------------------------------------

int		CAudtestApp::GetPrecision( int nType)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( nType < NUMPRECISIONS)
		return capp->m_nPrecisions[nType];
	else
		ASSERT(0);
	return 0;

}

void	CAudtestApp::SetPrecision( int nType, int nNewPrecision)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( nType < NUMPRECISIONS)
		{
		capp->m_nPrecisions[nType] = nNewPrecision;
		capp->WriteProfileInt( strNetwork, "Precision", nNewPrecision);
		}
	else
		ASSERT(0);

}

// ------------------------------------------------------------------
//			Resistor Type
// ------------------------------------------------------------------

int		CAudtestApp::GetResistorType( void)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_nResistorType;

}

void	CAudtestApp::SetResistorType( int nType)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( nType != capp->m_nResistorType)
		{
		capp->m_nResistorType = nType;
		capp->WriteProfileInt( strNetwork, "ResistorType", nType);
		}

}

// ------------------------------------------------------------------
//			DrawEndpoints
// ------------------------------------------------------------------

int		CAudtestApp::GetDrawEndpoints( void)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_nDrawEndpoints;

}

void	CAudtestApp::SetDrawEndpoints( int nType)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( nType != capp->m_nDrawEndpoints)
		{
		capp->m_nDrawEndpoints = nType;
		capp->WriteProfileInt( strNetwork, "DrawEndpoints", nType);
		}

}


// ------------------------------------------------------------------
// ------------------------------------------------------------------

BOOL		CAudtestApp::GetShowLongTitle()
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_bShowLongTitle;
}

BOOL		CAudtestApp::GetShowPath()
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_bShowPath;
}

// ---------------------------------------------------------------------
//			IsMetric
// ---------------------------------------------------------------------
BOOL		CAudtestApp::GetIsMetric()
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_bIsMetric;
}

void		CAudtestApp::SetIsMetric( BOOL bIsMetric)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( bIsMetric != capp->m_bIsMetric)
		{
		capp->m_bIsMetric = bIsMetric;
		capp->WriteProfileInt( strDisplay, "IsMetric", bIsMetric);
		}
}


// ---------------------------------------------------------------------
//			NetGrid
// ---------------------------------------------------------------------
POINT	CAudtestApp::GetNetGrid()
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_ptNetGrid;
}

void		CAudtestApp::SetNetGrid( POINT &ptNew)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( capp->m_ptNetGrid.x != ptNew.x || capp->m_ptNetGrid.y != ptNew.y)
		{
		capp->m_ptNetGrid = ptNew;
		capp->WriteProfileInt( strNetwork, "NetGridX", ptNew.x);
		capp->WriteProfileInt( strNetwork, "NetGridY", ptNew.y);
		}
}


// ---------------------------------------------------------------------
//			LongStatus
// ---------------------------------------------------------------------
BOOL		CAudtestApp::GetLongStatus()
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_bLongStatus;
}

void		CAudtestApp::SetLongStatus( BOOL bLongStatus)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( bLongStatus != capp->m_bLongStatus)
		{
		capp->m_bLongStatus = bLongStatus;
		capp->WriteProfileInt( strDisplay, "LongStatus", bLongStatus);
		}
}


// ---------------------------------------------------------------------
//			RightShift
// ---------------------------------------------------------------------
float		CAudtestApp::GetRightShift()
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_fRightShift;
}

void		CAudtestApp::SetRightShift( float fRightShift)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( fRightShift != capp->m_fRightShift)
		{
		capp->m_fRightShift = fRightShift;
		capp->WriteProfileFloat( strDisplay, "RightShift", fRightShift);
		}
}

// ---------------------------------------------------------------------
//			SingleClick
// ---------------------------------------------------------------------
BOOL		CAudtestApp::GetSingleClick()
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_bSingleClick;
}

void		CAudtestApp::SetSingleClick( BOOL bSingleClick)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( bSingleClick != capp->m_bSingleClick)
		{
		capp->m_bSingleClick = bSingleClick;
		capp->WriteProfileInt( strInterface, "SingleClick", bSingleClick);
		}
}

// ---------------------------------------------------------------------
//			LastPreference
// ---------------------------------------------------------------------
BOOL		CAudtestApp::GetLastPreference()
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_nLastPreference;
}

void		CAudtestApp::SetLastPreference( int nLastPreference)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( nLastPreference != capp->m_nLastPreference)
		{
		capp->m_nLastPreference = nLastPreference;
		capp->WriteProfileInt( strInterface, "LastPreference", nLastPreference);
		}
}

// ---------------------------------------------------------------------
//			UseLast
// ---------------------------------------------------------------------
BOOL		CAudtestApp::GetUseLast()
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_bUseLast;
}

void		CAudtestApp::SetUseLast( BOOL bUseLast)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( bUseLast != capp->m_bUseLast)
		{
		capp->m_bUseLast = bUseLast;
		capp->WriteProfileInt( "Startup", "UseLast", bUseLast);
		}
}


// ---------------------------------------------------------------------
//			CurrentView
// ---------------------------------------------------------------------
CView *CAudtestApp::GetCurrentView()
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_pCurrentView;
}

void		CAudtestApp::SetCurrentView( CView *pNewView)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		capp->m_pCurrentView = pNewView;
}

// ---------------------------------------------------------------------
//			IsWorking
// ---------------------------------------------------------------------
BOOL		CAudtestApp::GetIsWorking()
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_bIsWorking;
}

void		CAudtestApp::SetIsWorking( BOOL bIsWorking)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( bIsWorking != capp->m_bIsWorking)
		{
		capp->m_bIsWorking = bIsWorking;
//		capp->WriteProfileInt( strDisplay, "IsWorking", bIsWorking);
		}
}


void	CAudtestApp::SetShowPrefs( BOOL bLongTitle, BOOL bShowPath)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	if ( bLongTitle != capp->m_bShowLongTitle)
		{
		capp->m_bShowLongTitle = bLongTitle;
		capp->WriteProfileInt( strDisplay, "ShowLongTitle", bLongTitle);
		}

	if ( bShowPath != capp->m_bShowPath)
		{
		capp->m_bShowPath = bShowPath;
		capp->WriteProfileInt( strDisplay, "ShowPath", bShowPath);
		}
}

// ------------------------------------------------------------------

enChannel CAudtestApp::GetShowChannels( void)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_nShowChannels;

}

void	CAudtestApp::SetShowChannels( enChannel nNewShowChannels)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	capp->m_nShowChannels = nNewShowChannels;
	capp->WriteProfileInt( "Signal", "ShowChannels", nNewShowChannels);

}


CWnd *CAudtestApp::GetLocationWindow()
{
CWnd *dlgloc;

	dlgloc = ((CMainFrame *)AfxGetMainWnd())->LocationWindow();

	if ( dlgloc && dlgloc->GetSafeHwnd() )
		return dlgloc;
	return NULL;
}


//BOOL CAudtestApp::PreTranslateMessage(MSG* pMsg)
//{
	// CG: The following line was added by the Splash Screen component.
//	CSplashWnd::PreTranslateAppMessage(pMsg);

//	return CWinApp::PreTranslateMessage(pMsg);
//}

int		CAudtestApp::WriteRegistry( LPCSTR lpszName, const void *pStruct, int nStructSize)
{
HKEY hmain;
HKEY hrslt;
CString csname = "Software\\";

	csname += m_pszRegistryKey;
	csname += "\\";
	csname += m_pszAppName;

	LONG lrslt = ::RegOpenKeyEx( HKEY_CURRENT_USER, csname, 0, KEY_ALL_ACCESS, &hmain);

	if ( lrslt == ERROR_SUCCESS)
		{
		DWORD dwout;

		lrslt = ::RegCreateKeyEx(
				hmain,	// HKEY  hKey,	// handle of an open key 
				"Structures", // LPCTSTR  lpSubKey,	// address of subkey name 
				0,		 // DWORD  Reserved,	// reserved 
				NULL,	// LPTSTR  lpClass,	// address of class string 
				REG_OPTION_NON_VOLATILE, 	// DWORD  dwOptions,	// special options flag 
			    KEY_ALL_ACCESS, // REGSAM  samDesired,	// desired security access 
			    NULL,	// LPSECURITY_ATTRIBUTES  lpSecurityAttributes,	// address of key security structure 
				&hrslt,	    // PHKEY  phkResult,	// address of buffer for opened handle  
			    &dwout// LPDWORD  lpdwDisposition 	// address of disposition value buffer 
			   );

		if ( lrslt == ERROR_SUCCESS)
			{
			lrslt = ::RegSetValueEx( hrslt, lpszName, 0, REG_BINARY, (const BYTE *)pStruct, nStructSize);
			::RegCloseKey( hrslt);
			}
		
		::RegCloseKey( hmain);
		}


	return ((lrslt == ERROR_SUCCESS) ? 0 : 1);
}

int		CAudtestApp::ReadRegistry( UINT uidName, void *pStruct, int nStructSize)
{
CString csn;
int nout;

	csn.LoadString( uidName);

	nout = ReadRegistry( csn, pStruct, nStructSize);

	return nout;
}


int		CAudtestApp::WriteRegistry( UINT uidName, CObject *pObject)
{
CString csn;
int nout;
CMemFile pfile(20);		// grow by 20 bytes at a time
CArchive carc( &pfile, CArchive::store);
BYTE *ploc;				// where the memfile is
int nsize;
CRuntimeClass *pcl;

	pcl = pObject->GetRuntimeClass();

	carc << pcl->m_wSchema;		// save the schema number

	pObject->Serialize( carc);	// and the object

	carc.Close();
	csn.LoadString( uidName);		// get the reg name

	{
		nsize = pfile.GetLength();
		ploc = pfile.Detach();		// this closes the memfile
		nout = WriteRegistry( csn, ploc, nsize);
		free( ploc);
	}

	return nout;
}

float		CAudtestApp::GetProfileFloat( LPCSTR lpszAppName, LPCSTR lpszName, float fDefault)
{
CString str;


	str = GetProfileString( lpszAppName, lpszName, "");
	str.TrimLeft();
	str.TrimRight();
	if ( str.IsEmpty())
		return fDefault;

	return (float )atof( str);

}


int		CAudtestApp::WriteProfileFloat( LPCSTR lpszAppName, LPCSTR lpszName, float fData)
{
	CString strf;

	strf.Format("%f", fData);
	return WriteProfileString( lpszAppName, lpszName, strf);
}

#define BUFDEFAULT 2000

int		CAudtestApp::ReadRegistry( UINT uidName, CObject *pObject)
{
BYTE *pbuffer;
int nrslt = 0;
CRuntimeClass *pcl;
UINT wschema;

	pcl = pObject->GetRuntimeClass();

	pbuffer = (BYTE *)malloc( BUFDEFAULT);				// random BUFDEFAULT size

	memset( pbuffer, 0, BUFDEFAULT);						// clear the buffer so readreg works right

	ReadRegistry( uidName, pbuffer, BUFDEFAULT);

	{
		CMemFile pfile;
		pfile.Attach( pbuffer, BUFDEFAULT);
		CArchive carc( &pfile, CArchive::load);

		carc >> wschema;			// the stored schema

		if ( wschema != pcl->m_wSchema)		// nope
		{
			nrslt = 1;
		}
		else
		{
			carc.SetObjectSchema( wschema);
			pObject->Serialize( carc);
		}

		carc.Close();
		pfile.Close();

	}
	free( pbuffer);


	return (nrslt);
}

int		CAudtestApp::WriteRegistry( UINT uidName, const void *pStruct, int nStructSize)
{
CString csn;
int nout;

	csn.LoadString( uidName);

	nout = WriteRegistry( csn, pStruct, nStructSize);

	return nout;
}


int		CAudtestApp::ReadRegistry( LPCSTR lpszName, void *pStruct, int nStructSize)
{
HKEY hmain;
HKEY hrslt;
CString csname = "Software\\";

	csname += m_pszRegistryKey;
	csname += "\\";
	csname += m_pszAppName;
//		HKEY_CURRENT_USER\Software\<company name>\<application name>\<section 

LONG lrslt = RegOpenKeyEx( HKEY_CURRENT_USER, csname, 0, KEY_READ, &hmain);

	if ( lrslt == ERROR_SUCCESS)
		{
		lrslt = RegOpenKeyEx(
				hmain,	// HKEY  hKey,	// handle of an open key 
				"Structures", // LPCTSTR  lpSubKey,	// address of subkey name 
				0, 	// DWORD  ulOptions,	// special options flag 
			    KEY_ALL_ACCESS, // REGSAM  samDesired,	// desired security access 
				&hrslt	    // PHKEY  phkResult,	// address of buffer for opened handle  
			   );

		if ( lrslt == ERROR_SUCCESS)
			{
			DWORD dwtype;
			DWORD dwsize = (DWORD )nStructSize;
			lrslt = RegQueryValueEx( hrslt, lpszName, 0, &dwtype, (BYTE *)pStruct, &dwsize);
			RegCloseKey( hrslt);
			if ( dwsize != (DWORD )nStructSize)
				lrslt = ERROR_INVALID_DATA;
			}
		
		RegCloseKey( hmain);
		}


	return ((lrslt == ERROR_SUCCESS) ? 0 : 1);
}

void		CAudtestApp::FixRegistry( void)
{
HKEY hmain;
CString csname = "Software\\";
LONG lrslt;
DWORD dwDummy;

	csname += m_pszRegistryKey;
	csname += "\\";
	csname += m_pszAppName;
//		HKEY_CURRENT_USER\Software\<company name>\<application name>\<section 

	lrslt = RegOpenKeyEx( HKEY_CURRENT_USER, csname, 0, KEY_READ, &hmain);

	if ( lrslt != ERROR_SUCCESS)
		{
		lrslt = RegCreateKeyEx( HKEY_CURRENT_USER, csname, 0, "", REG_OPTION_NON_VOLATILE, 
								KEY_ALL_ACCESS,  NULL, &hmain, &dwDummy);
		if ( lrslt == ERROR_SUCCESS)
			RegCloseKey( hmain);
		}


}

static void to_hex( TCHAR *pBuffer, int iCount)
{
TCHAR *pend;
int i;

	pBuffer[ iCount*3 ] = '\0';		// null terminate

	for ( i = iCount-1; i >= 0; i--)
	{
		pend = pBuffer + i * 3;			// 3 bytes per entry
		unsigned char c = pend[i];

			pend[0] = "0123456789ABCDEF"[(c / 16)];
			pend[1] = "0123456789ABCDEF"[(c % 16)];
			pend[2] = ' ';
	}
}

void		CAudtestApp::DumpRegistry( LPCSTR lpszFileName)
{
HKEY hmain;
HKEY hsub;
CString cregname = "Software\\";
LONG lrslt;
CString filename("");

	cregname += m_pszRegistryKey;
	cregname += "\\";
	cregname += m_pszAppName;
//		HKEY_CURRENT_USER\Software\<company name>\<application name>\<section 
	lrslt = RegOpenKeyEx( HKEY_CURRENT_USER, cregname, 0, KEY_READ | KEY_ENUMERATE_SUB_KEYS, &hmain);

	if ( ERROR_SUCCESS != lrslt)
		{
		return;
		}

	ASSERT( ERROR_SUCCESS == lrslt);

	if ( lpszFileName)
		filename = lpszFileName;
	else
	{
	CString csext = "RDP";			// reg dump
	CString csfilter = _T("Registry Dump Files (*.rdp)||*.RDP|All Files (*.*)||*.*||");
	CFileDialog cdlg( FALSE, csext, NULL, OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, 
						csfilter, AfxGetMainWnd() );
	CString cstitle;

		cstitle.LoadString( IDS_SAVEREGISTRY);

		cdlg.m_ofn.lpstrTitle = (LPCSTR )cstitle;

		if ( IDOK == cdlg.DoModal())
			{					// import cdlg.GetPathname();
			filename = cdlg.GetPathName();
			}
		else
		{
			RegCloseKey( hmain);
			return;
		}
	}

#if 1
	{
	CStdioFile file;
	CFileException fe;
	DWORD dwindex = 0;
	bool berror = false;
	TCHAR szname[1024];
	TCHAR szclass[4096];
	TCHAR szvalue[1024];
	DWORD dwname;
	DWORD dwclass;
	DWORD dwvalue;
	DWORD dwtype;
	FILETIME ftlastwrite;
	bool bcontinue;
	LONG lrslt;
	CString csout;

		if (file.Open(filename, 
						CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive,
						&fe))
		{
			TRY
			{
				bcontinue = true;
				for ( dwindex = 0; bcontinue; dwindex++)
				{
					dwname = sizeof( szname) / sizeof( TCHAR);
					dwclass = sizeof( szclass) / sizeof( TCHAR);
					lrslt = RegEnumKeyEx(
								   hmain,               // handle to key to enumerate
								   dwindex,             // subkey index
								   szname,              // subkey name
								   &dwname,				// size of subkey buffer
								   NULL,				// reserved
								   szclass,				// class string buffer
								   &dwclass,			// size of class string buffer
								   &ftlastwrite );		// last write time
					if ( ERROR_SUCCESS != lrslt)		// we're done
						bcontinue = false;
					else
					{
						csout.Format(":: %s\n", szname);
						file.WriteString( csout);
						csout = cregname;
						csout += "\\";
						csout += szname;
						lrslt = RegOpenKeyEx( HKEY_CURRENT_USER, csout, 0, KEY_READ | KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE , &hsub);
						if ( ERROR_SUCCESS == lrslt)		// we got the key
						{
						bool bmore = true;
						DWORD dwix;

							for ( dwix = 0; bmore; dwix++)
							{
								dwclass = sizeof( szclass) / sizeof( TCHAR);
								dwvalue = sizeof( szvalue) / sizeof( TCHAR);
								lrslt = RegEnumValue(
										  hsub,             // handle to key to query
										  dwix,         // index of value to query
										  szvalue,    // value buffer
										  &dwvalue,  // size of value buffer
										  NULL,    // reserved
										  &dwtype,        // type buffer
										  (unsigned char *)szclass,         // data buffer
										  &dwclass);       // size of data buffer
								if ( ERROR_SUCCESS != lrslt)
									bmore = false;
								else
								{
									switch( dwtype)
									{
									case REG_BINARY :
										to_hex( szclass, dwclass);			// convert to hex
										csout.Format("%s = %s\n", szvalue, szclass);
										file.WriteString( csout);
										break;
									case REG_DWORD :
										dwvalue = *(DWORD *)szclass;
										csout.Format("%s = %d\n", szvalue, dwvalue);
										file.WriteString( csout);
										break;
									case REG_DWORD_BIG_ENDIAN :
										dwvalue = *(DWORD *)szclass;
										csout.Format("%s = %d\n", szvalue, dwvalue);
										file.WriteString( csout);
										break;
									case REG_SZ :
										csout.Format("%s = %s\n", szvalue, szclass);
										file.WriteString( csout);
										break;
									default:
										break;
									}
								}
							}
						}
					}
				}

			}
			CATCH_ALL(e)
			{
				file.Abort(); // will not throw an exception
				berror = true;

			}
			END_CATCH_ALL

			if ( ! berror)
				file.Close();
		}
	}
#else

	RegSaveKey(hmain, (LPCTSTR )szname, NULL );		// get the information
#endif
//	RegCloseKey( hmain);		// close it

}



// ========================================================

typedef WINBASEAPI BOOL WINAPI DISKFREE( LPCSTR, PULARGE_INTEGER, PULARGE_INTEGER, PULARGE_INTEGER);
// typedef FARPROC DISKFREE;

BOOL CAboutDlg::OnInitDialog()
{
	// CG: Folowing code is added by System Info Component
	{
	CDialog::OnInitDialog();
#ifndef _MAC
	CString strFreeDiskSpace;
	CString strFreeMemory;
	CString strFmt;

	// Fill available memory
	MEMORYSTATUS MemStat;
	MemStat.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&MemStat);
	strFmt.LoadString(CG_IDS_PHYSICAL_MEM);
	strFreeMemory.Format(strFmt, MemStat.dwTotalPhys / 1024L);

	//TODO: Add a static control to your About Box to receive the memory
	//      information.  Initialize the control with code like this:
	SetDlgItemText(IDC_PHYSICAL_MEM, strFreeMemory);

	// Fill disk free information
	int nDrive = _getdrive(); // use current default drive
	{
	ULARGE_INTEGER FreeBytesAvailable;
	ULARGE_INTEGER TotalNumberOfBytes;
	ULARGE_INTEGER TotalNumberOfFreeBytes;
	DWORD dwtotal;
	BOOL fResult;
	HMODULE hkernel = GetModuleHandle("kernel32.dll");
	DISKFREE *pGetDiskFreeSpaceEx = NULL;
	FARPROC pdiskfree = NULL;

		if ( hkernel)
		{
			pdiskfree = GetProcAddress( hkernel, "GetDiskFreeSpaceExA");
			pGetDiskFreeSpaceEx = (DISKFREE *)pdiskfree;
		}

		if (pdiskfree)
		{
		   fResult = (*pGetDiskFreeSpaceEx)(NULL, &FreeBytesAvailable, &TotalNumberOfBytes, &TotalNumberOfFreeBytes);
		}
		else 
		{
		DWORD dwSectPerClust;
		DWORD dwBytesPerSect;
		DWORD dwFreeClusters;
		DWORD dwTotalClusters;

		   fResult = GetDiskFreeSpace (NULL, 
						&dwSectPerClust, 
						&dwBytesPerSect,
						&dwFreeClusters, 
						&dwTotalClusters);

		   TotalNumberOfFreeBytes.QuadPart = dwFreeClusters * dwSectPerClust;
		   TotalNumberOfFreeBytes.QuadPart *= dwBytesPerSect;
		}

		if ( 0 != fResult)
		{
			dwtotal = (DWORD )(TotalNumberOfFreeBytes.QuadPart / (1024*1024));

			strFmt.LoadString(CG_IDS_DISK_SPACE);
			strFreeDiskSpace.Format(strFmt, dwtotal, nDrive-1 + _T('A'));
		}
	 	else
 			strFreeDiskSpace.LoadString(CG_IDS_DISK_SPACE_UNAVAIL);
	}

	SetDlgItemText(IDC_DISK_SPACE, strFreeDiskSpace);

#endif //_MAC
	}

	CString csout = "Warning: this computer program is protected by copyright law and international treaties. ";
	csout += "Unauthorized reproduction or distribution of this program, or any portion of it, ";
	csout += "may result in severe criminal and civil penalties, ";
	csout += "and will be prosecuted to the maximum extent possible under the law.";

	SetDlgItemText( IDC_WARNING, (LPCSTR )csout);

	return TRUE;
}

int CAudtestApp::ExitInstance() 
{
	WriteBigRegEntries();

	if ( m_CChartDefaults[uomTime])
	{
		delete m_CChartDefaults[uomTime];
		m_CChartDefaults[uomTime] = NULL;
	}
	if ( m_CChartDefaults[uomFreq])
	{
		delete m_CChartDefaults[uomFreq];
		m_CChartDefaults[uomFreq] = NULL;
	}
	if ( m_CChartDefaults[uomOhms])
	{
		delete m_CChartDefaults[uomOhms];
		m_CChartDefaults[uomOhms] = NULL;
	}

	if ( m_pcslLocale)
	{
		delete m_pcslLocale;
		m_pcslLocale = NULL;
	}

	return CWinApp::ExitInstance();
}

void CAudtestApp::OnWizardChecksoundcard() 
{
CDlgAudioCheck cdlg;

	cdlg.DoModal();
	
}

void CAudtestApp::OnFileNew() 
{
	// TODO: Add your command handler code here
	if ( m_pTreeView)
		m_pTreeView->OpenDocumentFile(NULL);
}


CSubChart *CAudtestApp::GetDefaultChart( int nChart)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	return capp->m_CChartDefaults[nChart];
}


void	CAudtestApp::SetDefaultChart( int nChart, CSubChart *pChart)
{
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
CMiniChart cmini;
UINT uid;

	capp->m_CChartDefaults[nChart]->InheritDefault( pChart);

	switch( nChart)
	{
	case 0 :
		uid = IDS_DEFCHARTTIME;
		break;
	case 1 :
		uid = IDS_DEFCHARTFREQ;
		break;
	case 2 :
		uid = IDS_DEFCHARTOHM;
		break;
	default:
		uid = 0;
		break;		// not going to happen
	}
	capp->m_CChartDefaults[nChart]->ToMiniChart( &cmini);

	capp->WriteRegistry( uid, &cmini);

			// get the colors and save them
	{
	int i;
	int imax;
	CDataLine *cnew;
	CObjColor *cclr;
	ColorDefinition cdef;
	UNITMSR uuom;

		imax = min( NUMCOLORDEF, pChart->GetDataCount());		// # to handle
		uuom = pChart->GetUom();

		for ( i=0; i<imax; i++)
		{
			cnew = pChart->GetDataAt( i);		// get the dataline

			if ( cnew->IsShowingAmp())
			{
				cclr = cnew->GetColor();			// get the color
				cdef = cclr->GetDefinition();
				SetColorDefinition( false, uuom, i, &cdef);
			}
			if ( cnew->IsShowingPhase())
			{
				cclr = cnew->GetPhaseColor();			// get the color
				cdef = cclr->GetDefinition();
				SetColorDefinition( true, uuom, i, &cdef);
			}
		}
	}
}




void CAudtestApp::OnOptionsSaveregistry() 
{
	DumpRegistry();	
}

// ----------------------------------------------------------------------------
// OnIdle time processing
// ----------------------------------------------------------------------------

BOOL CAudtestApp::OnIdle(LONG lCount) 
{

	if ( lCount  && GetAutoSave() && GetDocCounter())			// lCount of 0 could be at exit - crash
	{
	CFrameWnd * pFrame = (CFrameWnd *)m_pMainWnd;

		if ( pFrame && pFrame->GetSafeHwnd())
		{
			ASSERT_KINDOF( CFrameWnd, pFrame);		// cframe better be a framewnd
													// Get the active MDI child window.
		CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();

			if ( pChild && pChild->GetSafeHwnd() && (pChild != pFrame))	// frame == child on exit
			{
			ASSERT_KINDOF( CMDIChildWnd, pChild);		// cframe better be a framewnd
			CAudtestDoc *pdoc = (CAudtestDoc *)pChild->GetActiveDocument();

				if ( pdoc && pdoc->IsKindOf( RUNTIME_CLASS( CDocument)))
					pdoc->QueryAutoSave();
			}
		}
	}
	
	return CWinApp::OnIdle(lCount);
}

void CAudtestApp::OnFileOpen() 
{
CString csfile;
CString csuffix;
CString cstitle;

CFileDialog cdlg( TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, 
		"Speaker Workshop Files (*.SWD)|*.SWD|All Files (*.*)|*.*||",
		 NULL );

	CAudtestApp::GetLastFile( csfile);			// get last file imported

	{			// get the initial directory
	CString csdir;

		if ( !csfile.IsEmpty())
		{
		int islash = csfile.ReverseFind(TCHAR('\\'));		// find the last slash
			if ( islash >= 0)
				csfile = csfile.Left( islash);			// up to the last slash is the directory
			else
				csfile = "";			// empty it
		}
		cdlg.m_ofn.lpstrInitialDir = csfile;
	}

	if ( IDOK == cdlg.DoModal())
	{					// import cdlg.GetPathname();
		csfile = cdlg.GetPathName();
		CAudtestApp::SetLastFile( csfile);

		OpenDocumentFile(csfile);
	}

}
