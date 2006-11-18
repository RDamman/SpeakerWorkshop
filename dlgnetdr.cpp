// dlgnetdr.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgNetDr.h"

#include "Passive.h"
#include "Folder.h"

#include "Utils.h"

#include "dlgSelec.h"
#include "dlgNetLayout.h"
#include "dlgNetwo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNetDriver property page

IMPLEMENT_DYNCREATE(CDlgNetDriver, CPropertyPage)

CDlgNetDriver::CDlgNetDriver() : CPropertyPage(CDlgNetDriver::IDD), m_coNetlist(), m_cfEdits()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgNetDriver)
	m_csName = _T("");
	m_bDoChart = FALSE;
	m_bOutOfPhase = FALSE;
	//}}AFX_DATA_INIT
	m_coNetlist.SetSize(0,50);
	m_pcRoot = (CObject *)NULL;
	m_nPrior = -1;
	m_nSelect = 0;
	m_dwDriver = 0;

}

CDlgNetDriver::~CDlgNetDriver()
{

	::KillArray( &m_coNetlist);

}

void CDlgNetDriver::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgNetDriver::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgNetDriver)
	DDX_Control(pDX, IDC_STATOFFSET, m_czStatOffset);
	DDX_Control(pDX, IDC_COMPLIST, m_cComponentList);
	DDX_Text(pDX, IDC_COMPNAME, m_csName);
	DDX_Check(pDX, IDC_DOCHART, m_bDoChart);
	DDX_Check(pDX, IDC_OUTOFPHASE, m_bOutOfPhase);
	//}}AFX_DATA_MAP

	if ( pDX->m_bSaveAndValidate)
		{
		if ( m_nPrior >= 0)			// we have a prior
			{
			ZpPassive *pz;
			pz = (ZpPassive *) (m_coNetlist.GetAt(m_nPrior) );
			WriteDriver( pz);		// this needs to use getcursel et al
			m_nPrior = -1;
			}
		}
}


BEGIN_MESSAGE_MAP(CDlgNetDriver, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgNetDriver)
	ON_BN_CLICKED(IDC_ADDNEW, OnAddnew)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_LBN_SELCHANGE(IDC_COMPLIST, OnSelchangeComplist)
	ON_BN_CLICKED(IDC_LAYOUT, OnLayout)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_VERT1, OnVert1)
	ON_BN_CLICKED(IDC_VERT2, OnVert2)
	ON_BN_CLICKED(IDC_VERT3, OnVert3)
	ON_BN_CLICKED(IDC_HORZ1, OnHorz1)
	ON_BN_CLICKED(IDC_HORZ2, OnHorz2)
	ON_BN_CLICKED(IDC_HORZ3, OnHorz3)
	ON_EN_CHANGE(IDC_OFFSET, OnChangeOffset)
	ON_BN_CLICKED(IDC_DOCHART, OnDochart)
	ON_BN_CLICKED(IDC_OUTOFPHASE, OnOutofphase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgNetDriver, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgNetDriver)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNetDriver message handlers

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
void CDlgNetDriver::SetObjIcon( UINT nID, UINT nIcon)
{
CWinApp *papp = AfxGetApp();
HICON hicon;
int idr[6] = {IDR_COMPHORZ1,IDR_COMPHORZ2,IDR_COMPHORZ3,IDR_COMPVERT1,IDR_COMPVERT2,IDR_COMPVERT3};

	if ( nIcon <= 0)
		nIcon = 1;		// default to 1????
	hicon = papp->LoadIcon( idr[nIcon-1]);
	if ( hicon)			// the icon exists, at least
		{
		CButton *pbut = (CButton *)GetDlgItem( nID);
		if ( pbut)
			pbut->SetIcon( hicon);
		}
}


// ----------------------------------------------------------------------------------
//		UseDrivers
// ----------------------------------------------------------------------------------
void CDlgNetDriver::UseDrivers( CNetwork *pcNet, CObject *cSubject)
{
CObArray *pcsrc = pcNet->GetDriverArray();
int i;
ZpPassive *pin;

	for ( i=0; i<pcsrc->GetSize(); i++)
		{
		pin = (ZpPassive *)pcsrc->GetAt(i);
		if ( pin)
			{
			m_coNetlist.Add( pin->Duplicate());
			if ( pin == cSubject)		// that's our guy
				m_nSelect = i;
			}
		}

	m_pcRoot = pcNet->GetRootObject();

}

// ----------------------------------------------------------------------------------
//		SetDrivers
// ----------------------------------------------------------------------------------
void CDlgNetDriver::SetDrivers( CNetwork *pcNet)
{
CObArray *pcsrc = pcNet->GetDriverArray();

	::KillArray( pcsrc);
	::CopyArray( pcsrc, &m_coNetlist);

	m_coNetlist.RemoveAll();		// we're done. don't delete anyone

}


// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
void CDlgNetDriver::OnAddnew() 
{
	// TODO: Add your control notification handler code here
int i;

	UpdateData( TRUE);

	{
	CDlgSelectObject cdlg;
	CFolder *croot = (CFolder *)m_pcRoot;

		cdlg.SetParms( croot, m_dwDriver, ntDriver);

		if ( IDOK == cdlg.DoModal() )
			{
			ZpDriver *pdrive = new ZpDriver();
			m_dwDriver = cdlg.m_dwSelected;
			m_csName = "";
			pdrive->SetDriver( cdlg.m_dwSelected);
			pdrive->SetOutOfPhase( FALSE);
			pdrive->SetDoChart( FALSE);
			pdrive->SetOffset( 0.0f);
			if ( cdlg.m_dwSelected)
				{
				CNamed *cnam = croot->GetItem( cdlg.m_dwSelected);
				if ( cnam)
					{
					m_csName = cnam->GetFullName();
					pdrive->SetName( cnam->GetName() );
					i = m_coNetlist.Add( pdrive);
					fill_Box();
					UpdateData( FALSE);
					SetModified( TRUE);
					}
				}
			}

	}
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
void CDlgNetDriver::OnRemove() 
{
	// TODO: Add your control notification handler code here
	UpdateData( TRUE);

	{
	int i = m_cComponentList.GetCurSel();
	if ( LB_ERR != i)			// we have one to remove
		{
		i = m_cComponentList.GetItemData( i);	// get the index into netlist
		delete m_coNetlist.GetAt( i);
		m_coNetlist.RemoveAt(i);
		fill_Box();
		SetModified();
		}
	}

	UpdateData( FALSE);	
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
void CDlgNetDriver::fill_Box( )
{
int ncursel;
DWORD dwi = 0;		// just to remove initialization warning

	ncursel = m_cComponentList.GetCurSel();
	if( LB_ERR != ncursel)
		dwi = m_cComponentList.GetItemData(ncursel);

	m_cComponentList.ResetContent();		// remove all
	{
	int i = m_coNetlist.GetSize();
	int nloc;

		while( i--)
			{
			ZpPassive *pin = (ZpPassive *)m_coNetlist.GetAt(i);
			nloc = m_cComponentList.AddString( pin->GetName());
			m_cComponentList.SetItemData( nloc, i);
			}
	}

	if ( LB_ERR != ncursel)
		{
		int j;			// try to find him again, to highlight him

			for ( j=0; j<m_coNetlist.GetSize(); j++)
				if ( dwi == m_cComponentList.GetItemData(j))
					{
					m_cComponentList.SetCurSel(j);
					break;
					}
		}
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
BOOL CDlgNetDriver::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[2] = { 
							{IDC_OFFSET,	IDC_SPIN1, -100000.0f, 1000000.0f, &m_fOffset},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	GroupMetric cfgrp[2] = {
						  { IDC_OFFSET, IDC_STATOFFSET, mtCm },
						  { 0, 0, mtNone }
						  };
		m_cfEdits.AttachMetrics( cfgrp);
	}

	CPropertyPage::OnInitDialog();

	UpdateData( TRUE);			// fill m_cldatalist for once and for all

	{			// fill the list box with entries
	fill_Box( );
	}
	SetObjIcon( IDC_HORZ1, 1);
	SetObjIcon( IDC_HORZ2, 2);
	SetObjIcon( IDC_HORZ3, 3);
	SetObjIcon( IDC_VERT1, 4);
	SetObjIcon( IDC_VERT2, 5);
	SetObjIcon( IDC_VERT3, 6);

	{
	int j;

	for ( j=0; j<m_coNetlist.GetSize(); j++)
		if ( m_nSelect == (int )m_cComponentList.GetItemData(j))
			{
			m_cComponentList.SetCurSel(j);
			OnSelchangeComplist();
			break;
			}
	}

	UpdateData( FALSE);
		
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
void CDlgNetDriver::OnSelchangeComplist() 
{
int i;
ZpPassive *pcz;
BOOL bfill = FALSE;

	if ( m_nPrior >= 0)			// we have a prior
		{
		pcz = (ZpPassive *) (m_coNetlist.GetAt(m_nPrior) );
		CString cs = pcz->GetName();
		UpdateData( TRUE);		// get current showstuf and do a WriteDriver
		if ( m_csName != cs)
			bfill = TRUE;			// better do the lbox
		}

	m_nPrior = -1;
	i = m_cComponentList.GetCurSel();
	if ( LB_ERR == i)
		return;

	if ( bfill)
		{
		fill_Box();
		}

	i = m_cComponentList.GetCurSel();
	if ( LB_ERR == i)
		return;
	i = m_cComponentList.GetItemData( i);	// so we can alphabetize, the index is stored here
	m_nPrior = i;
			
	pcz = (ZpPassive *) (m_coNetlist.GetAt(i) );

	ReadDriver( pcz);

	UpdateData( FALSE);		// set current showstuf

}


		// actually ZpPassives...
// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
void 		CDlgNetDriver::ReadDriver( CObject *pSrc)
{
ZpDriver *pz = (ZpDriver *)pSrc;

   	m_csName = pz->GetName();
	m_bDoChart = pz->DoChart();
	m_bOutOfPhase = pz->IsOutOfPhase();
	m_fOffset = pz->GetOffset();

	{
	m_nLabel = pz->GetLabeling();
	if ( ! m_nLabel)
		m_nLabel = pz->GetOrientation() ? 6 : 3;		// default
	SetObjIcon( IDC_LAYOUT, m_nLabel);
	}

	m_dwDriver = pz->GetDriver();

}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
void CDlgNetDriver::WriteDriver( CObject *pDest)
{
ZpDriver *pz = (ZpDriver *)pDest;

   	pz->SetName( m_csName);
	pz->SetDoChart( m_bDoChart);
	pz->SetOutOfPhase( m_bOutOfPhase);
	pz->SetLabeling( m_nLabel);
	pz->SetOffset( m_fOffset) ;

	pz->SetDriver( m_dwDriver );
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
void CDlgNetDriver::OnLayout() 
{
CDlgNetLayout cdlg;

	{
	cdlg.m_nLayStyle = m_nLabel;
	if ( IDOK == cdlg.DoModal())
		{
		UpdateIcon( cdlg.m_nLayStyle);
		}
	}
	
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
void CDlgNetDriver::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

// ----------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------
void CDlgNetDriver::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! m_cfEdits.ProcessLeftClick( nFlags, point))
		CPropertyPage::OnLButtonUp(nFlags, point);
}

void CDlgNetDriver::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! 	m_cfEdits.ProcessRightClick( nFlags, point))
		CPropertyPage::OnRButtonUp(nFlags, point);
}

// ----------------------------------------------------------------------------------
//		UpdateIcon
// ----------------------------------------------------------------------------------
void	CDlgNetDriver::UpdateIcon( int nIcon)
{
	m_nLabel = nIcon;
	SetObjIcon( IDC_LAYOUT, m_nLabel);
	UpdateData( TRUE);		// write data to passive component
	SetModified();

}


// ----------------------------------------------------------------------------------
//		User changes orientation
// ----------------------------------------------------------------------------------
void CDlgNetDriver::OnVert1() 
{
	UpdateIcon( 4);
}

void CDlgNetDriver::OnVert2() 
{
	UpdateIcon( 5);
}

void CDlgNetDriver::OnVert3() 
{
	UpdateIcon( 6);
}

void CDlgNetDriver::OnHorz1() 
{
	UpdateIcon( 1);
}

void CDlgNetDriver::OnHorz2() 
{
	UpdateIcon( 2);
}

void CDlgNetDriver::OnHorz3() 
{
	UpdateIcon( 3);
}

// ----------------------------------------------------------------------------------
//		These just set modified to true
// ----------------------------------------------------------------------------------
void CDlgNetDriver::OnChangeOffset() 
{
	SetModified();
}

void CDlgNetDriver::OnDochart() 
{
	SetModified();
}

void CDlgNetDriver::OnOutofphase() 
{
	SetModified();
}

// ----------------------------------------------------------------------------------
//		OnApply
// ----------------------------------------------------------------------------------
BOOL CDlgNetDriver::OnApply() 
{
	UpdateData( TRUE);

	m_pParent->SetReapply( true);

	return CPropertyPage::OnApply();
}

