// DlgCalcMerge.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "Folder.h"
#include "DlgCalcMerge.h"
#include "dlgselec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcMerge dialog


CDlgCalcMerge::CDlgCalcMerge(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCalcMerge::IDD, pParent), m_cfEdits()
{
	//{{AFX_DATA_INIT(CDlgCalcMerge)
	m_csDriver = _T("");
	m_csPort = _T("");
	//}}AFX_DATA_INIT

	m_dwDriver = 0;
	m_dwPort = 0;
}


void CDlgCalcMerge::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgCalcMerge)
	DDX_Control(pDX, IDC_PORTUNITS, m_czPortUnits);
	DDX_Control(pDX, IDC_PISTONUNITS, m_czPistonUnits);
	DDX_Text(pDX, IDC_DRIVER, m_csDriver);
	DDX_Text(pDX, IDC_PORT, m_csPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCalcMerge, CDialog)
	//{{AFX_MSG_MAP(CDlgCalcMerge)
	ON_BN_CLICKED(IDC_HITDRIVER, OnHitdriver)
	ON_BN_CLICKED(IDC_HITPORT, OnHitport)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin)
	ON_WM_LBUTTONUP()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin)
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcMerge message handlers

static int do_HitButton( CFolder *pRoot, CString& csName, DWORD& dwID, UNITMSR uom)
{
CDlgSelectObject cdlg;
int nrslt;

	cdlg.SetParms( pRoot, dwID, ntDataSet, uom);
	
	nrslt = cdlg.DoModal();

	if ( IDOK == nrslt)
		{
		dwID = cdlg.m_dwSelected;
		csName = _T("");
		if ( dwID)
			{
			CNamed *cnam = pRoot->GetItem( dwID);
			if ( cnam && cnam->IsType( ntDataSet, uom))
				csName = cnam->GetFullName();
			else
				dwID = 0;
			}
		return IDOK;
		}

	return nrslt;
		
}



BOOL CDlgCalcMerge::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[3] = { 
							{IDC_PISTON,	IDC_SPIN1, 0.0f, 2000000.0f, &m_fPistonArea},
							{IDC_PORTAREA,	IDC_SPIN2, 0.0f, 2000000.0f, &m_fPortArea},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}
	GroupMetric cfgrp[3] = {
						  { IDC_PISTON,		IDC_PISTONUNITS,	mtSqMeter },
						  { IDC_PORTAREA,	IDC_PORTUNITS,	mtSqMeter },
						  { 0, 0, mtNone }
						  };
		m_cfEdits.AttachMetrics( cfgrp);

	CDialog::OnInitDialog();

	if ( m_dwDriver)
		m_csDriver = m_pRoot->FindByID( m_dwDriver)->GetName();		// the source nearfield response
	else
		m_csDriver.LoadString( IDS_UNKNOWN);
	if ( m_dwPort)
		m_csPort = m_pRoot->FindByID( m_dwPort)->GetName();		// the source nearfield response
	else
		m_csPort.LoadString( IDS_UNKNOWN);

	UpdateData( FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCalcMerge::OnHitdriver() 
{

	if ( IDOK == do_HitButton( m_pRoot, m_csDriver, m_dwDriver, uomFreq) )
		UpdateData( FALSE);
		
	
}

void CDlgCalcMerge::OnHitport() 
{

	if ( IDOK == do_HitButton( m_pRoot, m_csPort, m_dwPort, uomFreq) )
		UpdateData( FALSE);
	
}



void CDlgCalcMerge::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

void CDlgCalcMerge::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! m_cfEdits.ProcessLeftClick( nFlags, point))
		CDialog::OnLButtonUp(nFlags, point);
}

void CDlgCalcMerge::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! 	m_cfEdits.ProcessRightClick( nFlags, point))
		CDialog::OnRButtonUp(nFlags, point);
}

