// DlgDrvEquiv.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "Xform.h"
#include "Driver.h"

#include "DlgDrvEquiv.h"

#include "OpItem.h"
#include "Dataset.h"
#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDrvEquiv dialog


CDlgDrvEquiv::CDlgDrvEquiv(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDrvEquiv::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDrvEquiv)
	m_fFs = 0.0f;
	m_fQes = 0.0f;
	m_fQms = 0.0f;
	m_fQts = 0.0f;
	//}}AFX_DATA_INIT
}


void CDlgDrvEquiv::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgDrvEquiv)
	DDX_Text(pDX, IDC_FS, m_fFs);
	DDX_Text(pDX, IDC_QES, m_fQes);
	DDX_Text(pDX, IDC_QMS, m_fQms);
	DDX_Text(pDX, IDC_QTS, m_fQts);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDrvEquiv, CDialog)
	//{{AFX_MSG_MAP(CDlgDrvEquiv)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin)
	ON_EN_CHANGE(IDC_RE, OnChangeVar)
	ON_BN_CLICKED(IDC_CHART, OnChart)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN5, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN6, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN7, OnDeltaposSpin)
	ON_EN_CHANGE(IDC_C2, OnChangeVar)
	ON_EN_CHANGE(IDC_L1A, OnChangeVar)
	ON_EN_CHANGE(IDC_L1B, OnChangeVar)
	ON_EN_CHANGE(IDC_L2, OnChangeVar)
	ON_EN_CHANGE(IDC_R1, OnChangeVar)
	ON_EN_CHANGE(IDC_R2, OnChangeVar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDrvEquiv message handlers

// --------------------------------------------------------------------------
//			CXformCalcDriver code
// --------------------------------------------------------------------------

/// --- calculate driver parms
 
CXformCalcEquiv::CXformCalcEquiv(CObject *cTarget) : CXunary( cTarget)
{
}


CXformCalcEquiv::~CXformCalcEquiv( )
{
}

UINT CXformCalcEquiv::DoDialog( )		// xeq dbox
{
CDlgDrvEquiv cdlg;
UINT uout;

	cdlg.m_Driver = (CDriver *)FindTargetObject();

	uout = cdlg.DoModal();

	if ( IDOK == uout)
		m_DQ = cdlg.m_DQ;

	return uout;
}


int		CXformCalcEquiv::DoOperation(  )
{
CDriver *cdsource = (CDriver *)FindTargetObject();
CDataSet *cdest;
CDataSet *ccopy;
int nout;
COpFindOrCreate *ccr;
CString csuffix;

	csuffix.LoadString( IDSUF_CALCDRIVER);

	ccr = new COpFindOrCreate( cdsource,  cdsource->GetName() + "." + csuffix, ntDataSet);
	if ( ! PrivateQueue( ccr) )
		cdest = (CDataSet *)ccr->GetFound();
	else
		return 1;		// failure!

	ccopy = (CDataSet *)cdest->Duplicate();

	ASSERT( ccopy != NULL);

	nout = cdsource->UseDriverEquiv( ccopy, m_DQ);

	if ( nout)		// failure
		{
		delete ccopy;
		}
	else
		{
		COpChange *cchange;

			cchange = new COpChange( cdest, ccopy);
			PrivateQueue( cchange);
		}

	return nout;
}



UINT CXformCalcEquiv::GetDialog(void)		// get the dialog id
{
	return IDD_DRVRESTIMATE;
}


void CDlgDrvEquiv::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

BOOL CDlgDrvEquiv::OnInitDialog() 
{
	m_DQ = *m_Driver->GetDriverEquiv();
	m_DP = *m_Driver->GetDriverParameters();
	m_LastDQ = *m_Driver->GetDriverEquiv();
	m_LastDP = *m_Driver->GetDriverParameters();

	m_fRe	= (float )m_DQ.fRe;
	m_fR1	= (float )m_DQ.fR1;
	m_fR2	= (float )m_DQ.fR2;
	m_fC2	= (float )m_DQ.fC2;
	m_fL1a	= (float )m_DQ.fL1a;
	m_fL1b	= (float )m_DQ.fL1b;
	m_fL2	= (float )m_DQ.fL2;

	UpdateDP();


	{		// initialize the spinner format group
	FormatGroup cfdata[8] = { 
							{IDC_RE,	IDC_SPIN1, 0.0f, 20000.0f, &m_fRe},
							{IDC_L1A,	IDC_SPIN2, 0.0f, 20000.0f, &m_fL1a},
							{IDC_L1B,	IDC_SPIN3, 0.0f, 20000.0f, &m_fL1b},
							{IDC_R1,	IDC_SPIN4, 0.0f, 20000.0f, &m_fR1},
							{IDC_L2,	IDC_SPIN5, 0.0f, 20000.0f, &m_fL2},
							{IDC_C2,	IDC_SPIN6, 0.0f, 20000.0f, &m_fC2},
							{IDC_R2,	IDC_SPIN7, 0.0f, 20000.0f, &m_fR2},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CDialog::OnInitDialog();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDlgDrvEquiv::UpdateDP()
{
	m_Driver->ConvertDQtoDP( m_DP, m_DQ);

	m_fQts = m_DP.fQts;
	m_fQes = m_DP.fQes;
	m_fQms = m_DP.fQms;
	m_fFs = m_DP.fFs;


}

void CDlgDrvEquiv::UpdateDQ()
{
	m_DQ.fRe =	m_fRe;
	m_DQ.fR1 =	m_fR1;
	m_DQ.fR2 =	m_fR2;
	m_DQ.fC2 =	m_fC2;
	m_DQ.fL1a = m_fL1a;
	m_DQ.fL1b = m_fL1b;
	m_DQ.fL2 =	m_fL2;

}


void CDlgDrvEquiv::OnChangeVar() 
{
	if (! VerboseUpdateData( TRUE))
		return;

	UpdateDQ();
	UpdateDP();

	UpdateData( FALSE);
}

void CDlgDrvEquiv::OnChart() 
{
CString csname;
CNamed *cfound;

	if ( !VerboseUpdateData( TRUE))
		return;

	UpdateDQ();			// get new dq values

	csname.LoadString( IDSUF_CALCDRIVER);

	csname = m_Driver->GetName() + "." + csname;		// the long name

	cfound = m_Driver->FindByName( csname);

	if ( ! cfound)
	{
		::AfxMessageBox( IDERR_ESTIMATEBUILT);
		return;
	}

	m_Driver->UseDriverEquiv( (CDataSet *) cfound, m_DQ);

	cfound->UpdateViews();


}

// both ok and cancel do a cancel because the edit thing itself will make changes
void CDlgDrvEquiv::OnCancel() 
{
	ResetParms();

	CDialog::OnCancel();
}

void CDlgDrvEquiv::OnOK() 
{
	if ( ! VerboseUpdateData( TRUE))		// get latest values
		return;

	UpdateDQ();					// get new dq values

	ResetParms();
	
	CDialog::OnOK();
}

void CDlgDrvEquiv::ResetParms()
{
CString csname;
CNamed *cfound;

	csname.LoadString( IDSUF_CALCDRIVER);

	csname = m_Driver->GetName() + "." + csname;		// the long name

	cfound = m_Driver->FindByName( csname);

	if (  cfound)
	{
		m_Driver->UseDriverEquiv( (CDataSet *) cfound, m_LastDQ);
		cfound->UpdateViews();
	}

	m_Driver->SetDriverParameters( &m_LastDP);
	m_Driver->SetDriverEquiv( &m_LastDQ);

}
