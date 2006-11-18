// audtest.h : main header file for the AUDTEST application
//

#ifndef CAUDTESTHEAD


#include "FxFont.h"

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern const char * const cNullString;
extern const char * const cNullUnicode;

#define VerboseUpdateData( x)	VerbalUpdateData( this, x)


#include "Debug.h"
#define ALLOW_DBG 1
#define DBG_PRINT(x) CTopDebug::GetDebugObj()->PrintString(x)
#define DBG_TWO(x,y) CTopDebug::GetDebugObj()->PrintTwo(x,y)
#define DBG_INT(x,y) CTopDebug::GetDebugObj()->PrintInt(x,y)

//		forward class references for use as pointers
// ---------------------------------- resources
class	CNamed;
class	CEnclosure;
class	CChart;
class	CDataSet;
class	CDriver;
class	CSubChart;
class	CFolder;
class	CNetwork;
class	CRoom;
// ---------------------------------- others
class	CAudtestDoc;
class	CFxFont;
class	ZComplex;
class	ZpPassive;
class	CSetLocale;				// set the locale function


#include "Named.h"

typedef CArray<float,float> CFloatArray;		// float array
typedef CArray<double,double&> CDoubleArray;	// double array
typedef CArray<ZComplex, ZComplex&> ZComplexArray;	// complexes
typedef CTypedPtrArray< CPtrArray, ZpPassive *> ZPassiveArray;	// passive array

typedef enum tagMetrics
	{
	mtNone = 0,			// no metric associated with this
	mtInch = 1,
	mtFoot = 2,
	mtMm = 3,
	mtCm = 4,
	mtMeter = 5,
	mtCuInch = 6,
	mtCuFoot = 7,
	mtCuMm = 8,
	mtCuCm = 9,
	mtLitre = 10,
	mtCuMeter = 11,
	mtSqInch = 12,
	mtSqFoot = 13,
	mtSqMm = 14,
	mtSqCm = 15,
	mtSqMeter = 16,
	mtGram = 17,
	mtKGram = 18,
	mtOz = 19,
	mtLb = 20,
	mtFahrenheit = 21,
	mtCelsius = 22,
	mtLast = mtCelsius			// the last one in the list
	} METRICS;

typedef enum tagFonttypes
	{
	ftTitle = 0,
	ftSubTitle = 1,
	ftAxisTitle = 2,
	ftScale = 3,
	ftLegend = 4,
	ftNetData = 5,
	ftNetLabels = 6,
	ftStatus = 7,		// the status display for drivers and enclosures
	ftNotes = 8			// the note default font
	} FONTTYPES;

typedef enum tagXoverstyle
{
	xoNone = -1,			// none
	xoBessel = 0,			// bessel
	xoButterworth = 1,		// butterworth
	xoChebychev = 2,		// chebychev
	xoLegendre = 3,			// legendre
	xoGaussian = 4,			// Gaussian
	xoLinkwitz = 5,			// Linkwitz, reilly
	xoLinear = 6			// Linear Phase
} XOVERSTYLE;

typedef enum tagAppcolors
{
	clrBackground = 0,
	clrGrid = 1,
	clrInterior = 2
} APPCOLORS;

#define NUMAPPCOLORS 3

typedef enum tagEnchannel
	{
	chNone = 0,
	chLeft = 1,
	chRight = 2,
	chBoth = 3,
	chMono = 4
	} enChannel;

// ------------------------------------------------------
//		ColorDefinition structure
// ------------------------------------------------------
typedef struct tagColorDef
{
	COLORREF	m_clrRgb;			// color of pen
	int			m_nWidth;			// width of pen
	int			m_nStyle;			// pen style
} ColorDefinition;


// ------------------------------------------------------
//		RecordingInfo
// ------------------------------------------------------
typedef struct	impRECORDINGINFO
	{
	BOOL		m_bIsRecording;		// is it currently recording???
	BOOL		m_bLoopRecord;
	BOOL		m_bLoopPlay;
	BOOL		m_bOutput;			// do we want output???

	int			m_nDataType;		// type of data to generate (freq/time/impedance)
								// --- test specific
	float		m_fDataAmplitude;	// amplitude of wave
	int			m_nDataChannel;		// channel to use for data (vs reference)
	int			m_nCalibChannel;	// calibration channel
	int			m_nOutChannel;		// not in use
	float		m_fInLeftVolume;	// not in use
	float		m_fInRightVolume;	// not in use
	float		m_fPlayTime;		// play time in sec
	float		m_fRecordTime;		// record time in sec
	} RECORDINGINFO;

typedef struct impACOUSTICINFO
{
	enChannel	m_nMicChannel;		// the mic channel
	enChannel	m_nRefChannel;		// the reference channel (in any)
} ACOUSTICINFO;

typedef struct tagTESTMSR
	{
	int 	nSampleRate;
	int 	nSampleSize;
	int 	nNumberSamples;
	BOOL	bEmphasis;			// use pre-emphasis
	BOOL	bReverseChannel;	// reverse input channels
	float	fResistor;			// sample resistor
	float	fSeriesRes;			// "lead" resistance during testing
	float	fInputRes;			// input resistance
	float	fInputCap;			// input capacitance???
	float	fPlayVolume;		// volume for measurements
	} TESTMSR;

typedef struct tagENCLINFO
	{
	unsigned bConeExcursion : 1;
	unsigned bFreqResponse : 1;
	unsigned bGroupDelay : 1;
	unsigned bImpedance : 1;
	unsigned bTransient : 1;
	} ENCLINFO;

typedef struct tagTESTMRKER
	{
	BOOL	bUse;
	float	fStart;
	float	fEnd;				// starting and ending points
	} TESTMARK;

typedef struct tagMARKERINFO
	{
	TESTMARK	tmTime;
	TESTMARK	tmFreq;
	TESTMARK	tmOhms;
	} MARKERINFO;

typedef TESTMSR far *LPTESTMSR;
typedef MARKERINFO far *LPMARKERINFO;
typedef TESTMARK far *LPTESTMARK;

					// important constant linked to above enum
#define NUMFONTTYPES 9
#define NUMPRECISIONS 1
#define NUMCOLORDEF 8

/////////////////////////////////////////////////////////////////////////////
// CAudtestApp:
// See audtest.cpp for the implementation of this class
//

class CAudtestApp : public CWinApp
{
						// mz stuff
private:
	int		m_iDocCounter;					// # of documents in the workspace
											// transforms
	int 	m_nFftWindow;					// the fft windowing
	int		m_nLastPreference;				// the last preference window we had open
	int		m_nResistorType;				// 0 == squiggles, 1 == boxes
	int		m_nDrawEndpoints;				// do we draw endpoints?
	int		m_iMeasureTrails;				// trails for measurements
	int		m_iAllowedLocale;				// the locale we allow used
	int		m_iAutoSaveTime;				// time between autosaves
	BOOL	m_bAutoSave;					// allow autosave?
	BOOL	m_bUnaryInPlace;				// do these in-place?
	BOOL	m_bUnaryIncrement;				// autoincrement if not in-place?
	BOOL	m_bBinaryInPlace;
	BOOL	m_bBinaryIncrement;
	BOOL	m_bShowLongTitle;				// use file:names in window
	BOOL	m_bShowPath;					// use long names in datasets et al
	BOOL	m_bSingleClick;					// open resources with a single click
	BOOL	m_bUseLast;						// open last document at startup
	BOOL	m_bIsMetric;					// do we use metric data?
	BOOL	m_bLongStatus;					// put lots of stuff in the status bar
	BOOL	m_bIsWorking;					// is it working????
	bool	m_bDisable48K;					// should we check for 48K?
	bool	m_bDisable96K;					// should we check for 48K?
	POINT	m_ptNetGrid;					// the network grid
	CView	*m_pCurrentView;				// to make it easy to get at the current view
	CSetLocale	*m_pcslLocale;				// the set locale guy

	float	m_fRightShift;					// shift the right channel data in time?
											// networks
	int			m_nPrecisions[NUMPRECISIONS];	// currently one precision
	enChannel	m_nShowChannels;

	CString		m_csLastImport;				// name of last file imported
	CString		m_csLastExport;				// name of last file exported
	CString		m_csLastFile;				// name of last file loaded/saved

											// chart specific fonts to use
	CFxFont		m_cfAppFonts[NUMFONTTYPES];
	COLORREF	m_clrAppColors[NUMAPPCOLORS];	// and colors

	TESTMSR		m_Measures;
	MARKERINFO	m_Markers;					// the marker data
	ENCLINFO	m_EnclosureInfo;				// enclosure switches
	float		m_fLatency;					// latency value
	int			m_iWarmup;					// # of warmup samples sent

	CSubChart	*m_CChartDefaults[uomNone];		// 3 different default charts
	ColorDefinition m_ColorDefs[uomNone][2*NUMCOLORDEF];	// we have 8 default color defs for all 3 types

public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int 	FftWindow()						{ return m_nFftWindow; }
	BOOL	InPlace( BOOL bBinary)			{ return (bBinary ? m_bBinaryInPlace : m_bUnaryInPlace); }	
	BOOL	Increment( BOOL bBinary)		{ return (bBinary ? m_bBinaryIncrement : m_bUnaryIncrement); }	
	void 	SetFftWindow(int nNew);
	void	SetInPlace( BOOL bBinary, BOOL bNew);
	void	SetIncrement( BOOL bBinary, BOOL bNew);
	static void	GetLastImport( CString &csImport);
	static void	SetLastImport( LPCTSTR csImport);
	static void	GetLastExport( CString &csImport);
	static void	SetLastExport( LPCTSTR csImport);
	static void	GetLastFile( CString &csFile);
	static void	SetLastFile( LPCTSTR csFile);
	static void	SetMeasures( LPTESTMSR lpInput);
	static void	GetMeasures( LPTESTMSR lpInput);
	static void SetRecordingInfo( RECORDINGINFO *pNew);
	static void GetRecordingInfo( RECORDINGINFO *pDest);
	static void	SetEnclosureInfo( ENCLINFO& cNew);
	static void GetEnclosureInfo( ENCLINFO& cNew);
	static void	SetLatency( float fNew);
	static void	GetLatency( float *fGot);
	static bool	GetDisable48K( );
	static void	SetDisable48K( bool bDisable);
	static bool	GetDisable96K( );
	static void	SetDisable96K( bool bDisable);
	static void	SetWarmup( int iNew);
	static int	GetWarmup( void);
	static void	SetTrails( int iNew);
	static int	GetTrails( void);
	static int	GetAllowedLocale( void);
	static void SetAllowedLocale( int nNew);

	static void GetAcousticInfo( ACOUSTICINFO *pDest);
	static void SetAcousticInfo( ACOUSTICINFO *pNew);

	static ColorDefinition GetColorDefinition( bool bPhase, UNITMSR uUom, int iIndex);
	static void SetColorDefinition( bool bPhase, UNITMSR uUom, int iIndex, ColorDefinition *pNew);

	static BOOL GetAutoSave( void);
	static void SetAutoSave( BOOL bNew);
	static int  GetAutoSaveTime( void);
	static void SetAutoSaveTime( int iNew);

	static void SetShowPrefs( BOOL bLongTitle, BOOL bShowPath);
	static BOOL GetShowLongTitle( void);
	static BOOL GetShowPath( void);
	static BOOL GetIsMetric( void);
	static void SetIsMetric( BOOL bIsMetric);
	static POINT GetNetGrid( void);
	static void SetNetGrid( POINT &ptNew);
	static BOOL GetLongStatus( void);
	static void SetLongStatus( BOOL bIsMetric);
	static float GetRightShift( void);
	static void SetRightShift( float fRightShift);
	static BOOL GetSingleClick( void);
	static void SetSingleClick( BOOL bSingleClick);
	static int  GetLastPreference( void);
	static void SetLastPreference( int nNewPref);
	static int  GetResistorType( void);
	static void SetResistorType( int nNewPref);
	static int  GetDrawEndpoints( void);
	static void SetDrawEndpoints( int nNewPref);
	static BOOL GetUseLast( void);
	static void SetUseLast( BOOL bSingleClick);
	static BOOL GetIsWorking( void);
	static void SetIsWorking( BOOL bIsWorking);
	static CView *GetCurrentView( void);
	static void SetCurrentView( CView *pNewView);

	static void	ShowMarker( int nMarker, BOOL bNewValue);
	static BOOL	IsMarkerShown( int nMarker);
	static LPTESTMARK GetMarker(int nMarker );
	static void	SetMarker( int nMarker, LPTESTMARK lpInput);
	LPMARKERINFO GetMarkerInfo( void)		{ return &m_Markers; }

	static CSubChart *GetDefaultChart( int nChart);
	static void	SetDefaultChart( int nChart, CSubChart *pChart);

	static void SetDocCounter( int nChange);
	static int	GetDocCounter( void);

	void	FixRegistry( void);
	void	DumpRegistry( LPCSTR lpszFileName = (LPCSTR )NULL);
	int		WriteProfileFloat( LPCSTR lpszAppName, LPCSTR lpszName, float fData);
	float	GetProfileFloat( LPCSTR lpszAppName, LPCSTR lpszName, float fDefault );
	int		WriteRegistry( UINT lpszName, CObject *pSource);
	int		ReadRegistry( UINT uidName, CObject *pDest);
	int		WriteRegistry( LPCSTR lpszName, const void *pStruct, int nStructSize);
	int		ReadRegistry( LPCSTR lpszName, void *pStruct, int nStructSize);
	int		WriteRegistry( UINT uidName, const void *pStruct, int nStructSize);
	int		ReadRegistry( UINT uidName, void *pStruct, int nStructSize);

	static CFxFont &GetAppFont( FONTTYPES ftSelect);
	static void EditAppFont( FONTTYPES ftSelect);
	static COLORREF GetAppColor( APPCOLORS clrID);
	static void SetAppColor( APPCOLORS clrID, COLORREF clrSelect);
	static void ReadAppColors( void);
	static void WriteAppColors( void);
	static void ClearAllPrinterFonts( void);
	static int  GetPrecision( int nType);
	static void	SetPrecision( int nType, int nNew);
	static enChannel GetShowChannels( void);
	static void	SetShowChannels( enChannel enNew);	// use chMono to mean all three

	static CWnd *GetLocationWindow( void);

public:
	CAudtestApp();

	void WriteBigRegEntries( void);			// write the big stuff (usually on a save)

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudtestApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

	 CMultiDocTemplate *GetTemplate( int nType);
				// -------------------------------- mz stuff
private:
	CMultiDocTemplate *m_pTreeView;
	CMultiDocTemplate *m_pGenView;
	CMultiDocTemplate *m_pChartView;
	CMultiDocTemplate *m_pDataView;
	CMultiDocTemplate *m_pEnclView;
	CMultiDocTemplate *m_pRoomView;
	CMultiDocTemplate *m_pNetView;
	CMultiDocTemplate *m_pDriverView;

				// -------------------------------- mz stuff
// Implementation
	COleTemplateServer m_server;
		// Server object for document creation

	//{{AFX_MSG(CAudtestApp)
	afx_msg void OnAppAbout();
	afx_msg void OnOptionsPreferences();
	afx_msg void OnWizardChecksoundcard();
	afx_msg void OnFileNew();
	afx_msg void OnOptionsSaveregistry();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

						

// typedef __int32 INT32;
#define  ONEPI	(3.141592653589793238462644)

#define CAUDTESTHEAD
#endif
