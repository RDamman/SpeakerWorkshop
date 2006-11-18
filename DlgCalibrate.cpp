// DlgCalibrate.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "audtedoc.h"
#include "audtevw.h"

#include "DlgCalibrate.h"

#include "DlgSelec.h"

#include "OpRecord.h"

#include "DlgCalWizLp.h"
#include "DlgCalWizAmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCalibrate dialog


CDlgCalibrate::CDlgCalibrate(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCalibrate::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgCalibrate)
	m_csChannelDiff = _T("");
	m_csMicResponse = _T("");
	m_csAmpResponse = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCalibrate::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CDlgCalibrate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	if ( ! pDX->m_bSaveAndValidate)		// from user to dlg
		{
		CNamed *cnam;
		if ( m_dwChannelDiff)
			{
			cnam = m_pDocument->GetByID( m_dwChannelDiff);
			if ( cnam)
				m_csChannelDiff = cnam->GetFullName();
			else
				m_csChannelDiff = "???";
			}
		else
			m_csChannelDiff = cNullString;

		if ( m_dwMicResponse)
			{
			cnam = m_pDocument->GetByID( m_dwMicResponse);
			if ( cnam)
				m_csMicResponse = cnam->GetFullName();
			else
				m_csMicResponse = "???";
			}
		else
			m_csMicResponse = cNullString;

		if ( m_dwAmpResponse)
			{
			cnam = m_pDocument->GetByID( m_dwAmpResponse);
			if ( cnam)
				m_csAmpResponse = cnam->GetFullName();
			else
				m_csAmpResponse = "???";
			}
		else
			m_csAmpResponse = cNullString;
		}

	//{{AFX_DATA_MAP(CDlgCalibrate)
	DDX_Text(pDX, IDC_CHANNELDIFF, m_csChannelDiff);
	DDX_Text(pDX, IDC_MICRESPONSE, m_csMicResponse);
	DDX_Text(pDX, IDC_AMPRESPONSE, m_csAmpResponse);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalibrate, CDialog)
	//{{AFX_MSG_MAP(CDlgCalibrate)
	ON_BN_CLICKED(IDC_BROWSECHAN, OnBrowseChan)
	ON_BN_CLICKED(IDC_BROWSEMIC, OnBrowseMic)
	ON_BN_CLICKED(IDC_TESTCHAN, OnTestChan)
	ON_BN_CLICKED(IDC_TESTMIC, OnTestMic)
	ON_BN_CLICKED(IDC_BROWSEAMP, OnBrowseAmp)
	ON_BN_CLICKED(IDC_TESTAMP, OnTestAmp)
	ON_BN_CLICKED(IDC_HITNOAMP, OnHitnoamp)
	ON_BN_CLICKED(IDC_HITNOMIC, OnHitnomic)
	ON_BN_CLICKED(IDC_HITNONE, OnHitnone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgCalibrate, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgCalibrate)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgCalibrate to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {235663A0-7627-11CF-AA04-444553540000}
static const IID IID_IDlgCalibrate =
{ 0x235663a0, 0x7627, 0x11cf, { 0xaa, 0x4, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgCalibrate, CDialog)
	INTERFACE_PART(CDlgCalibrate, IID_IDlgCalibrate, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalibrate message handlers
static int do_HitButton( CAudtestDoc *pDoc, CString& csName, DWORD& dwID, UNITMSR uom)
{
CDlgSelectObject cdlg;
int nrslt;

	cdlg.SetParms( pDoc->GetRoot(), dwID, ntDataSet, uom);

	nrslt = cdlg.DoModal();
	if ( IDOK == nrslt)
		{
		dwID = cdlg.m_dwSelected;
		csName = cNullString;
		if ( cdlg.m_dwSelected)
			{
			CNamed *cnam = pDoc->GetByID( cdlg.m_dwSelected);
			if ( cnam)
				csName = cnam->GetFullName();
			}
		return IDOK;
		}

	return nrslt;
		
}


void CDlgCalibrate::OnBrowseChan() 
{
	// TODO: Add your control notification handler code here
	
	if ( IDOK == do_HitButton( m_pDocument, m_csChannelDiff, m_dwChannelDiff, uomFreq) )
		UpdateData( FALSE);
		
	
}

void CDlgCalibrate::OnBrowseMic() 
{
	// TODO: Add your control notification handler code here
	
	if ( IDOK == do_HitButton( m_pDocument, m_csMicResponse, m_dwMicResponse, uomFreq) )
		UpdateData( FALSE);
		
	
}

void CDlgCalibrate::OnBrowseAmp() 
{
	// TODO: Add your control notification handler code here
	if ( IDOK == do_HitButton( m_pDocument, m_csAmpResponse, m_dwAmpResponse, uomTime) )
		UpdateData( FALSE);
		
}


// test channel difference and set impedance jig variables
void CDlgCalibrate::OnTestChan() 
{
CDlgCalWizLoop	cdlg( this);

	cdlg.SetView( m_pView);

	cdlg.DoModal();

TESTCAL tcal;

	tcal = *m_pDocument->GetCalib();

	m_dwChannelDiff = tcal.dwLeftRight;

	UpdateData( FALSE);
}

// calibrate the microphone
void CDlgCalibrate::OnTestMic() 
{
COpCode *cop = new COpMsrFrequency( m_pView->GetTargetObject(), m_pView);

	m_pView->SetCurrentOperation( cop);

	if ( cop->QueueAndDo())
		m_pView->SetCurrentOperation( NULL);		// nope

TESTCAL tcal;

	tcal = *m_pDocument->GetCalib();

	m_dwMicResponse = tcal.dwMicrophone;

	UpdateData( FALSE);
	
}

// calibrate the microphone
void CDlgCalibrate::OnTestAmp() 
{
CDlgCalWizAmp	cdlg( this);

	cdlg.SetView( m_pView);

	cdlg.DoModal();

	m_dwAmpResponse = cdlg.m_dwReferID;

	UpdateData( FALSE);
}

void CDlgCalibrate::OnHitnoamp() 
{
	m_dwAmpResponse = 0;

	UpdateData( FALSE);
	
}

void CDlgCalibrate::OnHitnomic() 
{
	m_dwMicResponse = 0;

	UpdateData( FALSE);
	
}

void CDlgCalibrate::OnHitnone() 
{
	m_dwChannelDiff = 0;

	UpdateData( FALSE);
	
}
