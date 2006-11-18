// DlgPrefMarker.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "DlgPrefMarker.h"

#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefMarker property page

IMPLEMENT_DYNCREATE(CDlgPrefMarker, CPropertyPage)

CDlgPrefMarker::CDlgPrefMarker() : CPropertyPage(CDlgPrefMarker::IDD), 
			m_cFreq1(), m_cFreq2(), m_cTime1(), m_cTime2(), m_cOhms1(), m_cOhms2()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgPrefMarker)
	m_bUseFreq = FALSE;
	m_bUseOhms = FALSE;
	m_bUseTime = FALSE;
	//}}AFX_DATA_INIT
}

CDlgPrefMarker::~CDlgPrefMarker()
{
}

void CDlgPrefMarker::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CPropertyPage::OnFinalRelease();
}

void CDlgPrefMarker::DoDataExchange(CDataExchange* pDX)
{
	m_cFreq1.DDX_Value( pDX, m_fFreq1);
	m_cFreq2.DDX_Value( pDX, m_fFreq2);
	m_cTime1.DDX_Value( pDX, m_fTime1);
	m_cTime2.DDX_Value( pDX, m_fTime2);
	m_cOhms1.DDX_Value( pDX, m_fOhms1);
	m_cOhms2.DDX_Value( pDX, m_fOhms2);

	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPrefMarker)
	DDX_Check(pDX, IDC_USEFREQ, m_bUseFreq);
	DDX_Check(pDX, IDC_USEOHMS, m_bUseOhms);
	DDX_Check(pDX, IDC_USETIME, m_bUseTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPrefMarker, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgPrefMarker)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, OnDeltaposSpin3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, OnDeltaposSpin4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN5, OnDeltaposSpin5)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN6, OnDeltaposSpin6)
	ON_BN_CLICKED(IDC_USEFREQ, OnUseIt)
	ON_BN_CLICKED(IDC_USEOHMS, OnUseIt)
	ON_BN_CLICKED(IDC_USETIME, OnUseIt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgPrefMarker, CPropertyPage)
	//{{AFX_DISPATCH_MAP(CDlgPrefMarker)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgPrefMarker to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {F0549AC0-7EC4-11CF-AA04-444553540000}
static const IID IID_IDlgPrefMarker =
{ 0xf0549ac0, 0x7ec4, 0x11cf, { 0xaa, 0x4, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgPrefMarker, CPropertyPage)
	INTERFACE_PART(CDlgPrefMarker, IID_IDlgPrefMarker, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefMarker message handlers

BOOL CDlgPrefMarker::OnInitDialog() 
{

	m_cTime1.Subclass( this, IDC_TIME1, IDC_SPIN1);
	m_cTime2.Subclass( this, IDC_TIME2, IDC_SPIN2);
	m_cOhms1.Subclass( this, IDC_OHMS1, IDC_SPIN3);
	m_cOhms2.Subclass( this, IDC_OHMS2, IDC_SPIN4);
	m_cFreq1.Subclass( this, IDC_FREQ1, IDC_SPIN5);
	m_cFreq2.Subclass( this, IDC_FREQ2, IDC_SPIN6);

TESTMARK tm;
int i;

	for ( i=0; i<3; i++)
		{
		tm = *CAudtestApp::GetMarker( i);
		switch( i)
			{
			case 0 :
				m_bUseTime	= tm.bUse;
				m_fTime1	= tm.fStart;
				m_fTime2	= tm.fEnd;
				break;
			case 1 :
				m_bUseFreq	= tm.bUse;
				m_fFreq1	= tm.fStart;
				m_fFreq2	= tm.fEnd;
				break;
			case 2 :
				m_bUseOhms	= tm.bUse;
				m_fOhms1	= tm.fStart;
				m_fOhms2	= tm.fEnd;
				break;
			}
		}

	CPropertyPage::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPrefMarker::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cTime1.ProcessDelta( pNMUpDown->iDelta);		// that's it....

	SetModified( TRUE);
	
	*pResult = 0;
}

void CDlgPrefMarker::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cTime2.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	SetModified( TRUE);
	*pResult = 0;
}

void CDlgPrefMarker::OnDeltaposSpin3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cOhms1.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	SetModified( TRUE);
	*pResult = 0;
}

void CDlgPrefMarker::OnDeltaposSpin4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cOhms2.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	SetModified( TRUE);
	*pResult = 0;
}

void CDlgPrefMarker::OnDeltaposSpin5(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cFreq1.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	SetModified( TRUE);
	*pResult = 0;
}

void CDlgPrefMarker::OnDeltaposSpin6(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cFreq2.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	SetModified( TRUE);
	*pResult = 0;
}

BOOL CDlgPrefMarker::OnApply() 
{
	if ( ! VerboseUpdateData( TRUE))
		return 0;

	{
	TESTMARK tm;
	int i;

	for ( i=0; i<3; i++)
		{
		switch( i)
			{
			case 0 :
				tm.bUse =	m_bUseTime;
				tm.fStart =	m_fTime1;
				tm.fEnd =	m_fTime2;
				break;
			case 1 :
				tm.bUse =	m_bUseFreq;
				tm.fStart =	m_fFreq1;
				tm.fEnd =	m_fFreq2;
				break;
			case 2 :
				tm.bUse =	m_bUseOhms;
				tm.fStart =	m_fOhms1;
				tm.fEnd =	m_fOhms2;
				break;
			}
		CAudtestApp::SetMarker( i, &tm);
		}
	}
	
	return CPropertyPage::OnApply();
}

void CDlgPrefMarker::OnUseIt() 
{
	SetModified( TRUE);	
}
