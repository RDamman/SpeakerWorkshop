// dlgnetli.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "dlgnetli.h"
#include "Utils.h"

#include "passive.h"

#include "dlgNetLayout.h"
#include "dlgNetwo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDlgNetList property page

IMPLEMENT_DYNCREATE(CDlgNetList, CPropertyPage)

CDlgNetList::CDlgNetList() : CPropertyPage(CDlgNetList::IDD), m_coNetlist(), m_cfEdits()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgNetList)
	m_csName = _T("");
	m_nType = -1;
	m_csCompUnit = _T("");
	//}}AFX_DATA_INIT

	m_coNetlist.SetSize(0,50);
	m_pcRoot = NULL;
	m_nPrior = -1;
	m_nSelect = 0;
	m_fValue = 0.0f;
	m_fResist = 0.0f;
}

CDlgNetList::~CDlgNetList()
{
	::KillArray( &m_coNetlist);
}

void CDlgNetList::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

// this converts between the "GetType" and the combo box entries
static int alter_Type( int nType)
{
	switch( nType)
		{
		case ptResistor :
			return 0;
		case ptCapacitor :
			return 1;
		case ptInductor :
			return 2;
		case ptDriver :
			return 4;
		case ptGenerator :
			return 3;
		default:
			return 0;
		}
}

static NAMETYPES realter_Type( int nType)
{
NAMETYPES ntypes[5] = { ptResistor, ptCapacitor, ptInductor, ptGenerator, ptDriver };
	
	if ( nType < 0)
		return ptResistor;		//	???

	return ntypes[nType];

}

void CDlgNetList::DoDataExchange(CDataExchange* pDX)
{
int ntype = alter_Type( m_nType);

	CPropertyPage::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgNetList)
	DDX_Control(pDX, IDC_COMPLIST, m_cComponentList);
	DDX_Text(pDX, IDC_COMPNAME, m_csName);
	DDX_Text(pDX, IDC_COMPUNIT, m_csCompUnit);
	DDX_CBIndex(pDX, IDC_COMPTYPE, ntype);
	//}}AFX_DATA_MAP

	m_nType = realter_Type( ntype);

	if ( pDX->m_bSaveAndValidate)
		if ( m_nPrior >= 0)			// we have a prior
			{
			ZpPassive *pz;
			pz = (ZpPassive *) (m_coNetlist.GetAt(m_nPrior) );
			m_coNetlist.SetAt(m_nPrior, WritePassive( pz));	// this may change to a different object
			m_nPrior = -1;
			}


}


BEGIN_MESSAGE_MAP(CDlgNetList, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgNetList)
	ON_BN_CLICKED(IDC_ADDNEW, OnAddnew)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_LBN_SELCHANGE(IDC_COMPLIST, OnSelchangeComplist)
	ON_BN_CLICKED(IDC_LAYOUT, OnLayout)
	ON_CBN_SELCHANGE(IDC_COMPTYPE, OnSelchangeComptype)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_BN_CLICKED(IDC_HORZ1, OnHorz1)
	ON_BN_CLICKED(IDC_HORZ2, OnHorz2)
	ON_BN_CLICKED(IDC_HORZ3, OnHorz3)
	ON_BN_CLICKED(IDC_VERT1, OnVert1)
	ON_BN_CLICKED(IDC_VERT2, OnVert2)
	ON_BN_CLICKED(IDC_VERT3, OnVert3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin1)
	ON_EN_CHANGE(IDC_VALUE, OnChangeValue)
	ON_EN_CHANGE(IDC_RESISTANCE, OnChangeResistance)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgNetList, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgNetList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNetList message handlers


void CDlgNetList::UseNetlist( CNetwork *pcNet, CObject *cSubject)
{
CObArray *pcsrc = pcNet->GetDiscreteArray();
int i;
ZpPassive *pin;

	for ( i=0; i<pcsrc->GetSize(); i++)
		{
		pin = (ZpPassive *)pcsrc->GetAt(i);
		if ( pin)
			{
			m_coNetlist.Add( pin->Duplicate());
			if ( pin == cSubject)			// this is our subject
				m_nSelect = i;
			}
		}

	m_pcRoot = pcNet->GetRootObject();

}

void CDlgNetList::SetNetlist( CNetwork *pcNet)
{
CObArray *pcsrc = pcNet->GetDiscreteArray();

	::KillArray( pcsrc);
	::CopyArray( pcsrc, &m_coNetlist);

	m_coNetlist.RemoveAll();		// we're done. don't delete anyone

}

void CDlgNetList::OnAddnew() 
{
	// TODO: Add your control notification handler code here
ZpPassive *pnew = new ZpResistor();
int i;
CString csname;

	UpdateData( TRUE);
	pnew->SetValue( 10);
	csname.LoadString( IDS_NEWITEM);
	pnew->SetName(csname);
	i = m_coNetlist.Add( pnew);
	fill_Box();
		{
		int j;			// try to find him again, to highlight him

			for ( j=0; j<m_coNetlist.GetSize(); j++)
				if ( i == (int )m_cComponentList.GetItemData(j))
					{
					m_cComponentList.SetCurSel(j);
					break;
					}
		}
//	UpdateData( FALSE);
	OnSelchangeComplist();
	GotoDlgCtrl( GetDlgItem( IDC_COMPNAME));
	SetModified();	

}

void CDlgNetList::OnRemove() 
{
	UpdateData( TRUE);

	{
	int i = m_cComponentList.GetCurSel();
	if ( LB_ERR != i)			// we have one to remove
		{
		i = m_cComponentList.GetItemData( i);	// get the index into netlist
		if ( ! i)			// it's the source
			{
			AfxMessageBox( IDS_ERR_SRCDELETE);
			}
		else
			{
			delete m_coNetlist.GetAt( i);
			m_coNetlist.RemoveAt(i);
			fill_Box();
			SetModified();	
			}
		}
	}

	UpdateData( FALSE);

}

void CDlgNetList::fill_Box( )
{
int ncursel;
DWORD dwi = 0;		// initialize to remove warnings

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

void CDlgNetList::set_Spin( int nID)
{
CSpinButtonCtrl *cspin;

	cspin = (CSpinButtonCtrl *)GetDlgItem( nID);

	cspin->SetRange(0,10000);
}



BOOL CDlgNetList::OnInitDialog() 
{

	{		// initialize the spinner format group
	FormatGroup cfdata[3] = { 
							{IDC_VALUE,	IDC_SPIN1, 0.0f, 2000000.0f, &m_fValue},
							{IDC_RESISTANCE,	IDC_SPIN2, 0.0f, 2000000.0f, &m_fResist},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CPropertyPage::OnInitDialog();
	
	UpdateData( TRUE);			// fill m_cldatalist for once and for all

	::ComboFillString( this, IDC_COMPTYPE, IDS_NETLIST_COMPTYPE);

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
			break;
	if ( j == m_coNetlist.GetSize())		// not found
		j = 0;
	if ( j < m_coNetlist.GetSize())			// there are some...
		m_cComponentList.SetCurSel(j);

	}

	OnSelchangeComplist();			// pretend we changed the list (we did)
	UpdateData( FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNetList::OnSelchangeComplist() 
{
	// TODO: Add your control notification handler code here
int i;
ZpPassive *pcz;
BOOL bfill = FALSE;

	if ( m_nPrior >= 0)			// we have a prior
		{
		pcz = (ZpPassive *) (m_coNetlist.GetAt(m_nPrior) );
		CString cs = pcz->GetName();
		UpdateData( TRUE);		// get current showstuf do SaveAndValidate - writepassive
		if ( m_csName != cs)
			bfill = TRUE;			// better do the lbox
		}

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

	ReadPassive( pcz);

	UpdateData( FALSE);		// set current showstuf
}

// --------------------------------------------------------------------------
//		SetObjIcon
// --------------------------------------------------------------------------
void CDlgNetList::SetObjIcon( UINT nID, UINT nIcon)
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

// --------------------------------------------------------------------------
//	 actually ZpPassives...
// --------------------------------------------------------------------------
void 		CDlgNetList::ReadPassive( CObject *pSrc)
{
ZpPassive *pz = (ZpPassive *)pSrc;
UINT uids[] = { IDC_RESSTATIC, IDC_RESSUFFIX, IDC_SPIN2, IDC_RESISTANCE };

   	m_csName = pz->GetName();
	m_nType = pz->GetType();
	m_fValue = (float )pz->GetValue();
	m_csCompUnit = "";
	switch( pz->GetType())
		{
		case ptResistor :
			m_csCompUnit.LoadString(IDS_OHM);
			m_fMultip = 1.0f;
			break;
		case ptCapacitor :
			m_csCompUnit.LoadString(IDS_UFARAD);
			m_fMultip = 1000000.0f;
			break;
		case ptInductor :
			m_csCompUnit.LoadString(IDS_MHENRY);
			m_fMultip = 1000.0f;
			break;
		case ptDriver :
			m_fMultip = 1.0f;
			break;
		case ptGenerator :
			m_fMultip = 1.0f;
			break;
		default:
			ASSERT(0);
			m_fMultip = 1.0f;
			break;
		}

	m_fValue *= m_fMultip;		// put the units right


	{			// enable the inductor fields
	int i, imax;
	CWnd *pwnd;

		imax = sizeof( uids) / sizeof( UINT);

		for ( i=0; i<imax; i++)
		{
			pwnd = GetDlgItem( uids[i]);
			if ( pwnd && pwnd->GetSafeHwnd())
				pwnd->EnableWindow( ptInductor == pz->GetType());
		}
	}

	if ( ptInductor == pz->GetType())
	{
		if ( pz->GetQ() >= 99999)		// our default nothing is 1,000,000
			m_fResist = 0.0f;
		else
			m_fResist = (float )( m_fValue * ONEPI * 2000 / (pz->GetQ() * m_fMultip) );
	}
	else
		m_fResist = 0.0f;

	{
		m_nLabel = pz->GetLabeling();
		if ( ! m_nLabel)
			m_nLabel = pz->GetOrientation() ? 6 : 3;		// default
		SetObjIcon( IDC_LAYOUT, m_nLabel);
	}

}

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
CObject *CDlgNetList::WritePassive( CObject *pDest)
{
ZpPassive *pz = (ZpPassive *)pDest;
double dq;

	if ( pz->GetType() != m_nType)			// we've changed data types!
		{
		delete pz;
		SetModified();	
		switch( m_nType)
			{
			default:
			case ptResistor :
				pz = new ZpResistor();
				break;
			case ptCapacitor :
				pz = new ZpCapacitor();
				break;
			case ptInductor :
				pz = new ZpInductor();
				break;
			case ptDriver :
				pz = new ZpDriver();
				break;
			case ptGenerator :
				pz = new ZpGenerator();
				break;
			}
		}

   	pz->SetName( m_csName);
	pz->SetValue(m_fValue / m_fMultip);
	if ( ptInductor == pz->GetType())
	{
		if ( m_fResist > 0)
			dq = (m_fValue * 2 * ONEPI * 1000) / (m_fResist * m_fMultip);
		else
			dq = 1000000;			// default to 1000000
		pz->SetQ( dq);
	}
	pz->SetLabeling( m_nLabel);

	return pz;

}

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
void CDlgNetList::OnLayout() 
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

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
void CDlgNetList::OnSelchangeComptype() 
{
	// TODO: Add your control notification handler code here
int nprev = m_nType;		// before updating

	// TODO: Add your control notification handler code here
	UpdateData( TRUE);
	{
	int i = m_cComponentList.GetCurSel();
	if ( LB_ERR != i)			// we have one to remove
		{
		i = m_cComponentList.GetItemData( i);	// get the index into netlist
		if ( ! i)			// it's the source
			{
			AfxMessageBox( IDS_ERR_SRCCHANGE);
			m_nType = nprev;		// reset it
			SetModified();	
			}
		}
	}

	UpdateData( FALSE);

	
}

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
void CDlgNetList::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
void	CDlgNetList::UpdateIcon( int nIcon)
{
	m_nLabel = nIcon;
	SetObjIcon( IDC_LAYOUT, m_nLabel);
	UpdateData( TRUE);		// write data to passive component
	SetModified();
}

void CDlgNetList::OnVert1() 
{
	UpdateIcon( 4);
}

void CDlgNetList::OnVert2() 
{
	UpdateIcon( 5);
}

void CDlgNetList::OnVert3() 
{
	UpdateIcon( 6);
}

void CDlgNetList::OnHorz1() 
{
	UpdateIcon( 1);
}

void CDlgNetList::OnHorz2() 
{
	UpdateIcon( 2);
}

void CDlgNetList::OnHorz3() 
{
	UpdateIcon( 3);
}

void CDlgNetList::OnChangeValue() 
{
	SetModified();	
}

void CDlgNetList::OnChangeResistance() 
{
	SetModified();	
}

// ----------------------------------------------------------------------------------
//		OnApply
// ----------------------------------------------------------------------------------
BOOL CDlgNetList::OnApply() 
{
	UpdateData( TRUE);
	m_pParent->SetReapply( true);

	return CPropertyPage::OnApply();
}
