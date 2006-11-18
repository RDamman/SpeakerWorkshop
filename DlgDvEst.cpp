// DlgDvEst.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "Xform.h"

#include "zFormEdt.h"
#include "DlgDvEst.h"

#include "Driver.h"
#include "OpItem.h"
#include "Dataset.h"
#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


typedef struct tagDRVRESTIMATEINFO
	{
	float fStart;
	float fEnd;
	int	  nStyle;		// the three things we set in the dialog
	int	  nRecalc;		// the four things we now set in the dialog
	} DRVRESTIMATEINFO;

/////////////////////////////////////////////////////////////////////////////
// CDlgDriverEstimate dialog


CDlgDriverEstimate::CDlgDriverEstimate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDriverEstimate::IDD, pParent), m_cfEdits()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgDriverEstimate)
	m_bNoRecalc = FALSE;
	//}}AFX_DATA_INIT

	m_nStyle = 0;
	m_fStart = 0.0f;
	m_fEnd = 0.0f;

}


void CDlgDriverEstimate::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CDlgDriverEstimate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgDriverEstimate)
	DDX_Check(pDX, IDC_NORECALC, m_bNoRecalc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDriverEstimate, CDialog)
	//{{AFX_MSG_MAP(CDlgDriverEstimate)
	ON_EN_CHANGE(IDC_END, OnChangeEnd)
	ON_EN_CHANGE(IDC_START, OnChangeStart)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgDriverEstimate, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgDriverEstimate)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgDriverEstimate to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {2D835140-A4CF-11CF-AA03-444553540000}
static const IID IID_IDlgDriverEstimate =
{ 0x2d835140, 0xa4cf, 0x11cf, { 0xaa, 0x3, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgDriverEstimate, CDialog)
	INTERFACE_PART(CDlgDriverEstimate, IID_IDlgDriverEstimate, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDriverEstimate message handlers

BOOL CDlgDriverEstimate::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[3] = { 
							{IDC_START,	IDC_SPIN1, 1.0f, 20000.0f, &m_fStart},
							{IDC_END,	IDC_SPIN2, 1.0f, 20000.0f, &m_fEnd},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CDialog::OnInitDialog();
	
CStatic *cctrl;
CString cs;
DRVRESTIMATEINFO def;
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

	cs.Format( "%d", (int )m_fStartMarker);
	cctrl = (CStatic *)GetDlgItem( IDC_MARKLOW);
	cctrl->SetWindowText( cs);
	cs.Format( "%d", (int )m_fEndMarker);
	cctrl = (CStatic *)GetDlgItem( IDC_MARKHIGH);
	cctrl->SetWindowText( cs);

					// use defaults if there isn't one
	if ( capp->ReadRegistry( IDS_DRVRESTIMATEINFO, &def, sizeof( def)) )
		{
		def.fStart = 20.0f;
		def.fEnd = 1000.0f;
		def.nStyle = 0;
		def.nRecalc = 0;			// default to TRUE
		}

	m_fStart = def.fStart;
	m_fEnd = def.fEnd;
	m_nStyle =def.nStyle;
	m_bNoRecalc = (def.nRecalc != 0);

	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USEENTIRE + m_nStyle);

	UpdateData( FALSE);		// set it now
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgDriverEstimate::OnOK() 
{

	m_nStyle = GetCheckedRadioButton( IDC_USEENTIRE, IDC_USECUSTOM) - IDC_USEENTIRE;

	if (! VerboseUpdateData ( TRUE))
		return;

	{
	DRVRESTIMATEINFO def;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		def.fStart = m_fStart;
		def.fEnd = m_fEnd;
		def.nStyle = m_nStyle;
		def.nRecalc = (m_bNoRecalc ? 1 : 0);
						// use defaults if there isn't one
		capp->WriteRegistry( IDS_DRVRESTIMATEINFO, &def, sizeof( def) );
	}

	
	CDialog::OnOK();
}

void CDlgDriverEstimate::OnChangeEnd() 
{

	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USECUSTOM);
	
}

void CDlgDriverEstimate::OnChangeStart() 
{
	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USECUSTOM);
	
}


// --------------------------------------------------------------------------
//			CXformCalcDriver code
// --------------------------------------------------------------------------

/// --- calculate driver parms
 
CXformCalcDriver::CXformCalcDriver(CObject *cTarget) : CXunary( cTarget)
{
}


CXformCalcDriver::~CXformCalcDriver( )
{
}

UINT CXformCalcDriver::DoDialog( )		// xeq dbox
{
CDlgDriverEstimate cdlg;
UINT uout;
TESTMARK tm;

	tm = *CAudtestApp::GetMarker( 2);	// get the impedance markers

	cdlg.m_fStartMarker = tm.fStart;
	cdlg.m_fEndMarker = tm.fEnd;

	uout = cdlg.DoModal();

	if ( IDOK == uout)
		{
		m_bRecalcFree = ! cdlg.m_bNoRecalc;
		switch( cdlg.m_nStyle)
			{
			case 0 :			// use entire
				m_bUseFreq = FALSE;
				break;
			case 1 :			// use markers
				m_bUseFreq = TRUE;
				m_fStart = cdlg.m_fStartMarker;
				m_fEnd = cdlg.m_fEndMarker;
				break;
			case 2 :
				m_bUseFreq = TRUE;
				m_fStart = cdlg.m_fStart;
				m_fEnd = cdlg.m_fEnd;
				break;
			default:
				ASSERT(0);		// how did we get here???
			}
		}

	return uout;
}


int		CXformCalcDriver::DoOperation(  )
{
CDriver *cdsource = (CDriver *)FindTargetObject();
CDataSet *cdest;
CDataSet *ccopy;
int nout;
COpFindOrCreate *ccr;
CString csuffix;

	csuffix.LoadString( IDSUF_CALCDRIVER);

	ccr = new COpFindOrCreate( cdsource,  cdsource->GetName() + "." + csuffix, ntDataSet);
	if ( ! PrivateQueue( ccr) )
		cdest = (CDataSet *)ccr->GetFound();
	else
		return 1;		// failure!

	ccopy = (CDataSet *)cdest->Duplicate();

	ASSERT( ccopy != NULL);

	if ( ! m_bUseFreq)
		nout = cdsource->CalculateDriverParameters( ccopy, m_bRecalcFree);
	else
		nout = cdsource->CalculateDriverParameters( ccopy, m_bRecalcFree, m_fStart, m_fEnd);

	if ( nout)		// failure
		{
		delete ccopy;
		}
	else
		{
		COpChange *cchange;

			cchange = new COpChange( cdest, ccopy);
			PrivateQueue( cchange);
		}

	return nout;
}



UINT CXformCalcDriver::GetDialog(void)		// get the dialog id
{
	return IDD_DRVRESTIMATE;
}


void CDlgDriverEstimate::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}
