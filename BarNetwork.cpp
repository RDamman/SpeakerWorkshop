// BarNetwork.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "BarNetwork.h"
#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

bool CBarNetwork::m_bIsShowing = false;			// is it showing????
static WINDOWPLACEMENT g_wpWindowPlace = {0,0};



/////////////////////////////////////////////////////////////////////////////
// CBarNetwork dialog


CBarNetwork::CBarNetwork(CWnd* pParent /*=NULL*/)
	: CDialog(CBarNetwork::IDD, pParent), m_cfEdits()
{
	//{{AFX_DATA_INIT(CBarNetwork)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bIsShowing = true;			// we have it now
}


void CBarNetwork::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CBarNetwork)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBarNetwork, CDialog)
	//{{AFX_MSG_MAP(CBarNetwork)
	ON_WM_CLOSE()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN, OnDeltaposSpin)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBarNetwork message handlers

BOOL CBarNetwork::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[2] = { 
							{IDC_VALUE,	IDC_SPIN, 0.0f, 19900000.0f, &m_fValue},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CDialog::OnInitDialog();
	
	if ( g_wpWindowPlace.length == sizeof( g_wpWindowPlace))		// it's not empty, set back there
		SetWindowPlacement( &g_wpWindowPlace);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBarNetwork::OnClose() 
{
	g_wpWindowPlace.length = sizeof( g_wpWindowPlace);
	GetWindowPlacement( & g_wpWindowPlace);

	CDialog::OnClose();

//	DestroyWindow();
}

void CBarNetwork::PostNcDestroy() 
{
	CDialog::PostNcDestroy();

	m_bIsShowing = false;

	delete this;			// per microsoft, kill us here
}

void CBarNetwork::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

float CBarNetwork::GetValue( void)
{
	if ( VerboseUpdateData( TRUE))
		return m_fValue;
	return 0.0;
}


void CBarNetwork::SetValue( float fValue)
{
	m_fValue = fValue;
	UpdateData( FALSE);			// put it into the system
}


void CBarNetwork::OnApply() 
{
	PostMessage( WM_COMMAND, ID_CALCULATE_FREQUENCYRESPONSE);	
}


void CBarNetwork::SetSelected(CObject *pSel)
{
	m_pSelected = pSel;
	{
	CWnd *pwnd = GetDlgItem( IDC_VALUE);
		ASSERT( pwnd && pwnd->GetSafeHwnd());
		pwnd->EnableWindow( NULL != m_pSelected);
	}
	

}

CObject * CBarNetwork::GetSelected()
{
	return m_pSelected;
}
