// dlgpertu.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgpertu.h"

#include "passive.h"
#include "network.h"

#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

typedef struct tagPERTURBINFO
{
	float	fStart;
	float	fEnd;
	int		nPoints;
	BOOL	bLog;
} PERTURBINFO;

/////////////////////////////////////////////////////////////////////////////
// CDlgPerturb dialog


CDlgPerturb::CDlgPerturb(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPerturb::IDD, pParent), m_cfEdits()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgPerturb)
	m_nPoints = 0;
	m_csObjName = _T("");
	m_bLog = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgPerturb::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgPerturb::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgPerturb)
	DDX_Control(pDX, IDC_COMPONENT, m_cComponent);
	DDX_Text(pDX, IDC_NPOINTS, m_nPoints);
	DDV_MinMaxInt(pDX, m_nPoints, 2, 20);
	DDX_CBString(pDX, IDC_COMPONENT, m_csObjName);
	DDX_Check(pDX, IDC_DOLOG, m_bLog);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPerturb, CDialog)
	//{{AFX_MSG_MAP(CDlgPerturb)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC1, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC2, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgPerturb, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgPerturb)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPerturb message handlers

void CDlgPerturb::fill_Combo( CComboBox& pList)
{
CObject *cob;
int i = 0;
int nloc;

	pList.ResetContent();			// remove all

	for ( i=0; cob = m_pNet->GetDiscrete(i); i++)
		{
		ZpPassive *pin = (ZpPassive *)cob;
		if ( ptGenerator != pin->GetType())		// don't include sources
			{
			nloc = pList.AddString( pin->GetName());
			pList.SetItemData( nloc, i);
			}
		}

	pList.SetCurSel( 0);
}

BOOL CDlgPerturb::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[3] = { 
							{IDC_VALUE,	IDC_GENERIC1, 0.0f, 1000000.0f, &m_fStart},
							{IDC_VALUE2,IDC_GENERIC2, 0.0f, 1000000.0f, &m_fEnd},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CDialog::OnInitDialog();
	
			   // fill the combo boxes with their entries
	{
//	m_cComponent = GetDlgItem( IDC_COMPONENT);
//	if ( m_cComponent)
		fill_Combo( m_cComponent);
	}

	{				// get the default values from the registry
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	PERTURBINFO pf;

		if ( (!capp) || capp->ReadRegistry( IDS_PERTURBINFO, &pf, sizeof( pf)) )
			{
			pf.fStart = 0.0f;
			pf.fEnd = 0.0f;
			pf.nPoints = 1;
			pf.bLog = 0;
			}

		m_fStart = pf.fStart;
		m_fEnd = pf.fEnd;
		m_bLog = pf.bLog;
		m_nPoints = pf.nPoints;
	}

	{					// update the spinner range for npoints
	CSpinButtonCtrl *pslide = (CSpinButtonCtrl *)GetDlgItem( IDC_GENERIC3);
	if ( pslide)		// got a slider there
		{
		pslide->SetRange( 2, 20);
		m_nPoints = max(2, min( m_nPoints, 20));
		}
	}

	UpdateData( FALSE);		// save all data

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgPerturb::OnOK() 
{
	if ( ! VerboseUpdateData( TRUE))
		return;

	{				// set the default values
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	PERTURBINFO pf;

		pf.fStart = m_fStart;	
		pf.fEnd = m_fEnd;	
		pf.bLog = m_bLog;	
		pf.nPoints = m_nPoints;	

		if ( capp)
			capp->WriteRegistry( IDS_PERTURBINFO, &pf, sizeof( pf));
	}


	
	CDialog::OnOK();
}

void CDlgPerturb::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}
