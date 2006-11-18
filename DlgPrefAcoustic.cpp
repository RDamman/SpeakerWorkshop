// DlgPrefAcoustic.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "DlgPrefAcoustic.h"

#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefAcoustic property page

IMPLEMENT_DYNCREATE(CDlgPrefAcoustic, CPropertyPage)

CDlgPrefAcoustic::CDlgPrefAcoustic() : CPropertyPage(CDlgPrefAcoustic::IDD)
{
	//{{AFX_DATA_INIT(CDlgPrefAcoustic)
	m_nMicChannel = -1;
	m_nRefChannel = -1;
	//}}AFX_DATA_INIT
}

CDlgPrefAcoustic::~CDlgPrefAcoustic()
{
}

void CDlgPrefAcoustic::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPrefAcoustic)
	DDX_CBIndex(pDX, IDC_MICCHANNEL, m_nMicChannel);
	DDX_CBIndex(pDX, IDC_REFCHANNEL, m_nRefChannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPrefAcoustic, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgPrefAcoustic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefAcoustic message handlers

BOOL CDlgPrefAcoustic::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	::ComboFillString( this, IDC_MICCHANNEL, IDS_PREFA_MIC);
	::ComboFillString( this, IDC_REFCHANNEL, IDS_PREFA_REF);
	
	{
		ACOUSTICINFO iaco;

		CAudtestApp::GetAcousticInfo( &iaco);

		m_nMicChannel = ComboFromChannel(iaco.m_nMicChannel);
		m_nRefChannel = ComboFromChannel(iaco.m_nRefChannel);
	}
	
	UpdateData( FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgPrefAcoustic::OnApply() 
{
	if ( ! VerboseUpdateData( TRUE))
		return 0;

	{
		ACOUSTICINFO iaco;

		 iaco.m_nMicChannel = ComboToChannel( m_nMicChannel);
		 iaco.m_nRefChannel = ComboToChannel( m_nRefChannel);

		CAudtestApp::SetAcousticInfo( &iaco);
	}
	
	SetModified( FALSE);

	return CPropertyPage::OnApply();
}
