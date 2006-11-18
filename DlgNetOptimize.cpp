// DlgNetOptimize.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "xform.h"
#include "DlgNetOptimize.h"
#include "Network.h"
#include "DataSet.h"
#include "DlgSelec.h"

#include "NetOptimize.h"
#include "Passive.h"
#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


typedef struct tagOptiminfo
	{
	float	fStart;
	float	fEnd;
	int		nPoints;
	DWORD	dwTarget;
	}	OPTIMINFO;


/////////////////////////////////////////////////////////////////////////////
// CDlgNetOptimize dialog
/////////////////////////////////////////////////////////////////////////////


CDlgNetOptimize::CDlgNetOptimize(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNetOptimize::IDD, pParent), m_cfEdits()
{
	//{{AFX_DATA_INIT(CDlgNetOptimize)
	m_iPoints = 0;
	m_csTarget = _T("");
	//}}AFX_DATA_INIT

	m_pNetwork = NULL;

	{
	OPTIMINFO fi;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		if ( capp->ReadRegistry( IDS_OPTIMINFO, &fi, sizeof(fi)))	// success???
			{
			fi.fStart = 500.0f;
			fi.fEnd = 5000.0f;
			fi.nPoints = 100;
			fi.dwTarget = 0;
			}
		m_fStart = fi.fStart;
		m_fEnd = fi.fEnd;
		m_iPoints = fi.nPoints;
		m_dwTarget = fi.dwTarget;
	}

}


// --------------------------------------------------------------------
//		DoDataExchange
// --------------------------------------------------------------------
void CDlgNetOptimize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgNetOptimize)
	DDX_Text(pDX, IDC_NUMPOINTS, m_iPoints);
	DDX_Text(pDX, IDC_TARGET, m_csTarget);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNetOptimize, CDialog)
	//{{AFX_MSG_MAP(CDlgNetOptimize)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin)
	ON_BN_CLICKED(IDC_SELTARGET, OnSeltarget)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
//			Methods
///////////////////////////////////////////////////////////////////////////////

void CDlgNetOptimize::UseTarget( void)
{
CNamed *cout;

	if ( m_dwTarget)
		{
		cout = m_pNetwork->FindByID( m_dwTarget);
		if ( cout && cout->IsType(ntDataSet, uomFreq))
			m_csTarget = cout->GetFullName();
		else
			{
			m_dwTarget = 0;
			m_csTarget = _T("");
			}
		}
	else
		{
		m_csTarget = _T("");
		}
	UpdateData( FALSE);		// update the string
}


/////////////////////////////////////////////////////////////////////////////
// CDlgNetOptimize message handlers
//////////////////////////////////////////////////////////////////////////////


// --------------------------------------------------------------------
//			OnInitDialog
// --------------------------------------------------------------------
BOOL CDlgNetOptimize::OnInitDialog() 
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
	
	{					// the spin button for the # of points
	CSpinButtonCtrl *pbutton;
	pbutton = (CSpinButtonCtrl *)GetDlgItem( IDC_SPIN3);
	if ( pbutton)
		pbutton->SetRange(5,1000);
	}

	{
	CWnd *pwnd = GetDlgItem( IDC_CFRAME);			// get the frame

		if ( pwnd && pwnd->GetSafeHwnd())
		{
		CRect rc;

			pwnd->GetWindowRect( rc);
			ScreenToClient( rc);				// put it in parent client coords
			m_cComponentList.Create( 0, rc, this, IDC_CFRAME+0x101);

			pwnd = GetDlgItem( IDC_TOVARY);		// get a static for text height
			m_cComponentList.SetVariables( pwnd);

			{
			int i;
			int imax = m_pNetwork->GetDiscreteArray()->GetSize();
			int indx;
			int iwho = 0;


				for ( i=0; i<imax; i++)
				{
				ZpPassive *zp;
				CString strname;
				CString valname;

					zp = (ZpPassive *)m_pNetwork->GetDiscrete( i);
					if ( ptGenerator != zp->GetType())
					{
					double dvalue = zp->GetValue();
						::FullFormatValue( valname, (float )dvalue, -3);
						strname = " " + zp->GetName() + "  " + valname + zp->GetValueSuffix();
						indx = m_cComponentList.AddString( strname);
						m_cComponentList.SetItemData( indx, iwho);		// set the index
						m_cComponentList.SetCheck( indx, true);
						iwho++;		// index of item in discretes - generators
					}
				}
			}

		}

	}
	
	
	UseTarget();		// this does an updatedata(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// --------------------------------------------------------------------
//		SpinButton
// --------------------------------------------------------------------
void CDlgNetOptimize::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}



// --------------------------------------------------------------------
//			OnSelTarget
// --------------------------------------------------------------------
void CDlgNetOptimize::OnSeltarget() 
{
CDlgSelectObject cdlg;
CFolder *m_pRoot = m_pNetwork->GetRootObject();

	cdlg.SetParms( (CFolder *)m_pRoot, m_dwTarget, ntDataSet, uomFreq);

	if ( IDOK == cdlg.DoModal())
		{
		m_dwTarget = cdlg.m_dwSelected;
		UseTarget();
		}
}

// --------------------------------------------------------------------
//			OnOK
// --------------------------------------------------------------------
void CDlgNetOptimize::OnOK() 
{
	if (! VerboseUpdateData( TRUE))
		return;

	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	OPTIMINFO fi;

		if ( ! m_dwTarget)
		{
			AfxMessageBox(IDERR_NOGOAL, MB_OK);
			return;
		}

		fi.fStart = m_fStart;
		fi.fEnd =	m_fEnd;
		fi.nPoints = m_iPoints;
		fi.dwTarget = m_dwTarget;

		capp->WriteRegistry( IDS_OPTIMINFO, &fi, sizeof(fi) );	// success???
	}

	m_cVary.SetSize(0,10);			// items to vary
	{
	int i, imax;
		imax = m_cComponentList.GetCount();			// # of strings

		for ( i=0; i<imax; i++)
		{
			if ( m_cComponentList.GetCheck( i))		// ith is checked
				m_cVary.Add( m_cComponentList.GetItemData( i));
		}
	}
	
	CDialog::OnOK();
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


// -------------------------------------------------------------------------------------
//		the crossover operation
// -------------------------------------------------------------------------------------
CXtNetOptimize::CXtNetOptimize( CObject *cTarget) : CXunary( cTarget)
{
}

CXtNetOptimize::~CXtNetOptimize()
{
}


UINT CXtNetOptimize::DoDialog( )		// xeq dbox
{
CDlgNetOptimize cdlg;
CNetwork *cname;
UINT uout;

	cname = (CNetwork *)FindTargetObject();

	if ( ! cname)
		return IDCANCEL;

	cdlg.m_pNetwork = cname;

	uout = cdlg.DoModal();
	if ( IDOK == uout)
		{
		m_fStart = cdlg.m_fStart;
		m_fEnd = cdlg.m_fEnd;
		m_iPoints = cdlg.m_iPoints;
		m_dwTarget = cdlg.m_dwTarget;
		m_cuVary.Copy( cdlg.m_cVary);		// get the list of items to vary
		}

	return uout;

}

int CXtNetOptimize::DoOperation( )	// xeq xform
{
CNetwork *cname;

	cname = (CNetwork *)FindTargetObject();

	if ( ! cname)
		return 1;

	{
	CNetOptimize copt;			// the optimization class
	CDataSet *pgoal;

		pgoal = (CDataSet *)cname->FindByID( m_dwTarget);
		if ( pgoal && pgoal->IsType( ntDataSet, uomFreq))
		{
			copt.SetRange( m_fStart, m_fEnd, m_iPoints);
			if ( copt.SetNetwork( cname))			// network is validated
			{
				copt.SetGoal( pgoal);
				copt.SetVariables( m_cuVary);
				copt.Optimize();			// do it
			}
		}
	}

	return 0;
}

UINT CXtNetOptimize::GetDialog(void)		// get the dialog id
{
	return IDD_NETOPTIMIZE;
}


/////////////////////////////////////////////////////////////////////////////
// CCheckList

void CCheckList::SetVariables( CWnd *pBasis)
{
CRect rc;

	pBasis->GetClientRect( rc);
	SetItemHeight(0, rc.Height());
	SetFont( pBasis->GetFont());

}

BOOL CCheckList::Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	BOOL brslt = CCheckListBox::Create( WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP | LBS_SORT | 
					LBS_OWNERDRAWFIXED | LBS_HASSTRINGS | WS_BORDER | LBS_NOINTEGRALHEIGHT |
					dwStyle, rect, pParentWnd, nID);
	return brslt;
}


CCheckList::CCheckList() : CCheckListBox()
{
}

CCheckList::~CCheckList()
{
}


BEGIN_MESSAGE_MAP(CCheckList, CCheckListBox )
	//{{AFX_MSG_MAP(CCheckList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckList message handlers
