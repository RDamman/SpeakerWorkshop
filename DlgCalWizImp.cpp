// DlgCalWizImp.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "audtedoc.h"
#include "audtevw.h"

#include "Generat.h"
#include "MainFrm.h"

#include "zFormEdt.h"
#include "DlgCalWizImp.h"
#include "DlgDefWr.h"

#include "OpRecord.h"
#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define TIMER_ID	0x123195



static void enable_Cancel( CPropertySheet *pSheet, BOOL bEnable)
{
	{
	CWnd *pwnd;
	pwnd = pSheet->GetDlgItem( IDCANCEL);
	if ( pwnd)
		{
		pwnd->EnableWindow( bEnable);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizImpBegin property page

IMPLEMENT_DYNCREATE(CDlgCalWizImpBegin, CPropertyPage)

CDlgCalWizImpBegin::CDlgCalWizImpBegin() : CPropertyPage(CDlgCalWizImpBegin::IDD)
{
	//{{AFX_DATA_INIT(CDlgCalWizImpBegin)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgCalWizImpBegin::~CDlgCalWizImpBegin()
{
}

void CDlgCalWizImpBegin::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalWizImpBegin)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalWizImpBegin, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCalWizImpBegin)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizImpBegin message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizEnd property page

IMPLEMENT_DYNCREATE(CDlgCalWizImpEnd, CPropertyPage)

CDlgCalWizImpEnd::CDlgCalWizImpEnd() : CPropertyPage(CDlgCalWizImpEnd::IDD)
{
	//{{AFX_DATA_INIT(CDlgCalWizEnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgCalWizImpEnd::~CDlgCalWizImpEnd()
{
}

void CDlgCalWizImpEnd::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalWizImpEnd)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalWizImpEnd, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCalWizImpEnd)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MEASURED, OnMeasured)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizImpEnd message handlers
/////////////////////////////////////////////////////////////////////////////

void CDlgCalWizImpEnd::OnMeasured() 
{
CDlgCalWizImpList cdlg(this);

	{					// get the original values
	TESTMSR deftest;

		CAudtestApp::GetMeasures( &deftest);
		cdlg.m_fRefOld = deftest.fResistor;
		cdlg.m_fSeriesOld = deftest.fSeriesRes;
	}
						// get the current values
	{
	CDlgCalWizImpedance *cwnd = (CDlgCalWizImpedance *)GetParent();

		cdlg.m_fRefNew = m_fResistor;
		cdlg.m_fSeriesNew = m_fSeriesRes;
		cdlg.m_pKnown = & cwnd->m_ArKnown;
		cdlg.m_pMeasured = & cwnd->m_ArMeasure;
	}


	cdlg.DoModal();
	
}


void CDlgCalWizImpEnd::enable_Measured( BOOL bOn)
{
CWnd *pwnd;

	pwnd = GetDlgItem( IDC_MEASURED);
	if ( pwnd)
		{
		pwnd->EnableWindow( bOn);
		}
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizImpJig1 dialog
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CDlgCalWizImpJig1, CPropertyPage)

CDlgCalWizImpJig1::CDlgCalWizImpJig1() : CPropertyPage(CDlgCalWizImpJig1::IDD), m_cfEdits()
{
	//{{AFX_DATA_INIT(CDlgCalWizImpJig1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_fResistor = 0.0f;
}


CDlgCalWizImpJig1::~CDlgCalWizImpJig1()
{
}

void CDlgCalWizImpJig1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgCalWizImpJig1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalWizImpJig1, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCalWizImpJig1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizImpJig1 message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizImpJig2 property page

IMPLEMENT_DYNCREATE(CDlgCalWizImpJig2, CPropertyPage)

CDlgCalWizImpJig2::CDlgCalWizImpJig2() : CPropertyPage(CDlgCalWizImpJig2::IDD), m_cfEdits()
{
	//{{AFX_DATA_INIT(CDlgCalWizImpJig2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_fResistor = 0.0f;
}

CDlgCalWizImpJig2::~CDlgCalWizImpJig2()
{
}

void CDlgCalWizImpJig2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgCalWizImpJig2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalWizImpJig2, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCalWizImpJig2)
	ON_WM_TIMER()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizImpJig2 message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizImpedance

IMPLEMENT_DYNAMIC(CDlgCalWizImpedance, CPropertySheet)

CDlgCalWizImpedance::CDlgCalWizImpedance(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDS_CALIBRATION, pParentWnd, iSelectPage), m_ArKnown(), m_ArMeasure()
{
	AddPage( &m_dlgBegin);
	AddPage( &m_dlgJig1);
	AddPage( &m_dlgJig2);
	AddPage( &m_dlgEnd);

	SetWizardMode();

	{
	TESTMSR deftest;

	CAudtestApp::GetMeasures( &deftest);
	m_fOriginalRes = deftest.fSeriesRes;		// the original series resistance
	}
}


CDlgCalWizImpedance::~CDlgCalWizImpedance()
{
}


BEGIN_MESSAGE_MAP(CDlgCalWizImpedance, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgCalWizImpedance)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizImpedance message handlers

BOOL CDlgCalWizImpJig2::OnSetActive() 
{
CDlgCalWizImpedance *cwnd = (CDlgCalWizImpedance *)GetParent();

	if ( 2 > cwnd->m_ArKnown.GetSize())		// we got here from jig1
		{
		enable_Cancel( cwnd, FALSE);
		SetTimer( TIMER_ID, 250, NULL);		// 250 milliseconds
		cwnd->SetWizardButtons( NULL);
		}
	else
		{
		cwnd->SetWizardButtons( PSWIZB_NEXT | PSWIZB_BACK);
		}
	
	return CPropertyPage::OnSetActive();
}

BOOL CDlgCalWizImpJig1::OnSetActive() 
{
CDlgCalWizImpedance *cwnd = (CDlgCalWizImpedance *)GetParent();

	cwnd->SetWizardButtons( PSWIZB_NEXT | PSWIZB_BACK);
	cwnd->m_ArKnown.SetSize( 0, 5);
	cwnd->m_ArMeasure.SetSize( 0, 5);		// clean them out
	
	return CPropertyPage::OnSetActive();
}

BOOL CDlgCalWizImpBegin::OnSetActive() 
{
CPropertySheet *cwnd = (CPropertySheet *)GetParent();

	cwnd->SetWizardButtons( PSWIZB_NEXT);

			// validate the input values
	{
	CDlgDefaultWarning cdlg;

		cdlg.DoModal();
	}
	
	return CPropertyPage::OnSetActive();
}

BOOL CDlgCalWizImpEnd::OnSetActive() 
{
CPropertySheet *cwnd = (CPropertySheet *)GetParent();

	cwnd->SetWizardButtons( PSWIZB_DISABLEDFINISH);
	enable_Cancel( cwnd, FALSE);
	enable_Measured( FALSE);

	SetTimer( TIMER_ID, 250, NULL);		// 250 milliseconds
	
	return CPropertyPage::OnSetActive();
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


LRESULT CDlgCalWizImpJig1::OnWizardNext() 
{
CDlgCalWizImpedance *cwnd = (CDlgCalWizImpedance *)GetParent();
CAudtestView *pView;			// the parent view
COpCode *cop;
CNamed *pcgen;

	if ( ! VerboseUpdateData( TRUE))			// get m_fresist
		return -1;

	cwnd->m_ArKnown.Add( m_fResistor);

	pView = (CAudtestView *)cwnd->GetView();
	pcgen = ((CAudtestDoc *)pView->GetDocument() )->GetDefaultGenerator();
	cop = new COpMsrCalJig1( pcgen, pView);

	pView->SetCurrentOperation( cop);

	if ( cop->QueueAndDo())
		pView->SetCurrentOperation( NULL);		// nope
	
	return CPropertyPage::OnWizardNext();
}

LRESULT CDlgCalWizImpJig2::OnWizardNext() 
{
CDlgCalWizImpedance *cwnd = (CDlgCalWizImpedance *)GetParent();
CAudtestView *pView;			// the parent view
COpCode *cop;
CNamed *pcgen;

	if ( ! VerboseUpdateData( TRUE))			// get m_fresist
		return -1;

	cwnd->m_ArKnown.Add( m_fResistor);

	pView = (CAudtestView *)cwnd->GetView();
	pcgen = ((CAudtestDoc *)pView->GetDocument() )->GetDefaultGenerator();
	cop = new COpMsrCalJig1( pcgen, pView);

	pView->SetCurrentOperation( cop);

	if ( cop->QueueAndDo())
		pView->SetCurrentOperation( NULL);		// nope
	
	return CPropertyPage::OnWizardNext();
}

void CDlgCalWizImpJig2::OnTimer(UINT nIDEvent) 
{
CDlgCalWizImpedance *cwnd = (CDlgCalWizImpedance *)GetParent();

	if ( ! CAudtestApp::GetIsWorking() )
		{
		KillTimer( nIDEvent);
					// check for valid readings
			{
			CWnd *cmain = AfxGetMainWnd();
			VuValues vuleft;
			VuValues vuright;

				if ( cmain && cmain->IsKindOf(RUNTIME_CLASS( CMainFrame))) 
				{
				CMainFrame *cframe = (CMainFrame *)cmain;

					vuleft = cframe->GetVuValues( false);		// get left channel
					vuright =  cframe->GetVuValues( true);		// get right channel
					{					// see if flipped
					TESTMSR deftest;
					VuValues vutemp;

						CAudtestApp::GetMeasures( &deftest);
						if ( deftest.bReverseChannel)			// reverse the channels
						{
							vutemp = vuleft;
							vuleft = vuright;
							vuright = vutemp;
						}
					}

					if ( (1.1 * vuleft.fMax) < vuright.fMax)		// left way less than right!
					{
						AfxMessageBox( IDERR_JIG_BACKWARDS, MB_OK);
					}
					else
					if ( vuleft.fMax <= (1.05 * vuright.fMax))		// left about == right
					{
						AfxMessageBox( IDERR_JIG_OPEN, MB_OK);
					}
				}
			}
					// end of validity check

		cwnd->SetWizardButtons( PSWIZB_NEXT | PSWIZB_BACK);
		enable_Cancel( cwnd, TRUE);
					// the timer is done, store the saved value
		TESTMSR deftest;

		CAudtestApp::GetMeasures( &deftest);
		cwnd->m_ArMeasure.Add( deftest.fSeriesRes);		// the value we measured
		deftest.fSeriesRes = cwnd->m_fOriginalRes;
		CAudtestApp::SetMeasures( &deftest);			// put the original value back

		}
	
	CPropertyPage::OnTimer(nIDEvent);
}

void CDlgCalWizImpEnd::OnTimer(UINT nIDEvent) 
{
CDlgCalWizImpedance *cwnd = (CDlgCalWizImpedance *)GetParent();

	if ( ! CAudtestApp::GetIsWorking() )
		{
		cwnd->SetWizardButtons( PSWIZB_FINISH | PSWIZB_BACK);
		enable_Cancel( cwnd, TRUE);
		KillTimer( nIDEvent);
					// the timer is done, store the saved value
		TESTMSR deftest;

		CAudtestApp::GetMeasures( &deftest);
		cwnd->m_ArMeasure.Add( deftest.fSeriesRes);		// the value we measured
		deftest.fSeriesRes = cwnd->m_fOriginalRes;
		CAudtestApp::SetMeasures( &deftest);			// put the original value back
					// --------------------------------------------------------
					// now do the arithmetic and store the values in the dialog
					// --------------------------------------------------------
			{
			double s, sx, sy, sxx, sxy;		// see doc
			CFloatArray *pknow = &cwnd->m_ArKnown;
			CFloatArray *pmsr = &cwnd->m_ArMeasure;
			int nsize = pknow->GetSize();
			int i;

				s = sx = sy = sxx = sxy = 0;
				for ( i=0; i<nsize; i++)
					{
					double dx = pknow->GetAt(i);
					double dy = pmsr->GetAt(i);
					double dsigma;			// std deviation is 1% percent of actual

						dsigma = .01 * dx + .01 * deftest.fResistor;	// 1 % of each
						dsigma *= dsigma;			// squared

					s += 1 / dsigma;
					sx += dx / dsigma;
					sy += dy / dsigma;
					sxx += dx * dx / dsigma;
					sxy += dx * dy / dsigma;
					}
							// now the variables are calculated
			double delta = s * sxx - sx * sx;
			m_fSeriesRes = (float )((sxx * sy - sx * sxy) / delta);
			m_fResistor = (float )((s * sxy - sx * sy) / delta);

							// these are the a,b values for the linear regression
							// where measure = a + b * true
							// now convert to real resistances
			m_fSeriesRes /= m_fResistor;
			m_fResistor = deftest.fResistor / m_fResistor;
							// format to the screen
			CString csout;

			::FullFormatValue( csout, m_fResistor, 2);
			CWnd *pwnd = GetDlgItem( IDC_RESISTOR);
			if ( pwnd)
				pwnd->SetWindowText( csout);
			::FullFormatValue( csout, m_fSeriesRes, 2);
			pwnd = GetDlgItem( IDC_SERIESRES);
			if ( pwnd)
				pwnd->SetWindowText( csout);

			}

		enable_Measured( TRUE);	// turn on the Measured button
		}
	
	CPropertyPage::OnTimer(nIDEvent);
}

BOOL CDlgCalWizImpJig1::OnInitDialog() 
{
	
		{		// initialize the spinner format group
		FormatGroup cfdata[2] = { 
							{IDC_RESIST,	IDC_SPIN1, 0.0f, 1000.0f, &m_fResistor},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);

		}
	
	CPropertyPage::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgCalWizImpJig2::OnInitDialog() 
{
	
		{		// initialize the spinner format group
		FormatGroup cfdata[2] = { 
							{IDC_RESIST,	IDC_SPIN1, 0.0f, 1000.0f, &m_fResistor},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);

		}
	
	CPropertyPage::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCalWizImpJig1::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

void CDlgCalWizImpJig2::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}


BOOL CDlgCalWizImpEnd::OnWizardFinish() 
{
CDlgCalWizImpedance *cwnd = (CDlgCalWizImpedance *)GetParent();

	cwnd->m_fResistor = m_fResistor;
	cwnd->m_fSeriesRes = m_fSeriesRes;
	
	return CPropertyPage::OnWizardFinish();
}
/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizImpList property page

CDlgCalWizImpList::CDlgCalWizImpList(CWnd* pParent /*=NULL*/) : CDialog(CDlgCalWizImpList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCalWizImpList)
	m_fRefNew = 0.0f;
	m_fRefOld = 0.0f;
	m_fSeriesNew = 0.0f;
	m_fSeriesOld = 0.0f;
	//}}AFX_DATA_INIT
}

CDlgCalWizImpList::~CDlgCalWizImpList()
{
}

void CDlgCalWizImpList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalWizImpList)
	DDX_Control(pDX, IDC_MSROLD, m_cMsrOld);
	DDX_Control(pDX, IDC_MEASURED, m_cMsrNew);
	DDX_Control(pDX, IDC_KNOWN, m_cKnown);
	DDX_Text(pDX, IDC_REFNEW, m_fRefNew);
	DDX_Text(pDX, IDC_REFOLD, m_fRefOld);
	DDX_Text(pDX, IDC_SERIESNEW, m_fSeriesNew);
	DDX_Text(pDX, IDC_SERIESOLD, m_fSeriesOld);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalWizImpList, CDialog)
	//{{AFX_MSG_MAP(CDlgCalWizImpList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalWizImpList message handlers

BOOL CDlgCalWizImpList::OnInitDialog() 
{
float f;

	CDialog::OnInitDialog();
	
	UpdateData( TRUE);		// get the class values in

		{
		int i;
		CString cs;

		for ( i=0; i<m_pKnown->GetSize(); i++)
			{
			f = m_pKnown->GetAt(i);
			cs.Format("%.3f", (double )f);
			m_cKnown.AddString( cs);
			}

		for ( i=0; i<m_pMeasured->GetSize(); i++)
			{	// calculations are based on 0.0 series res (see COpMsrJig1)
			f = m_pMeasured->GetAt(i) - m_fSeriesOld;
			cs.Format("%.3f", (double )f);
			m_cMsrOld.AddString( cs);
			}
					// now convert from old measurements to new
		for ( i=0; i<m_pMeasured->GetSize(); i++)
			{
			f = m_pMeasured->GetAt(i);		// measured resistance
//			f += m_fSeriesOld;				// add in old series res
			if ( m_fRefOld > .001)
				f *= m_fRefNew / m_fRefOld;
			else
				f *= m_fRefNew;
			f -= m_fSeriesNew;				// remove new series res
			cs.Format("%.3f", (double )f);
			m_cMsrNew.AddString( cs);
			}

		}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
