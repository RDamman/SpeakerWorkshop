// DlgSplice.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "Xform.h"
#include "zFormEdt.h"

#include "DlgSplice.h"

#include "DataSet.h"
#include "Folder.h"
#include "Utils.h"

#include "DlgSelec.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct tagSPLICEINFO
	{
	BOOL	bUseBHigh;
	BOOL	bUseBRes;
	DWORD	dwPicked;
	float	fStart;
	int		nStyle;
	} SPLICEINFO;

/////////////////////////////////////////////////////////////////////////////
// CDlgXfSplice dialog


CDlgXfSplice::CDlgXfSplice(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXfSplice::IDD, pParent), m_cStart()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgXfSplice)
	m_bUseBHigh = FALSE;
	m_bUseBRes = FALSE;
	//}}AFX_DATA_INIT

	{
	SPLICEINFO fi;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		if ( capp->ReadRegistry( IDS_SPLICEINFO, &fi, sizeof(fi)))	// success???
			{		// failure, we need to set it
			fi.bUseBHigh = FALSE;
			fi.bUseBRes = FALSE;
			fi.dwPicked = 0;
			fi.nStyle = 0;
			fi.fStart = 500.0f;
			}
		m_bUseBHigh= fi.bUseBHigh;
		m_bUseBRes = fi.bUseBRes;	
		m_dwPicked = fi.dwPicked;	
		m_nStyle  = fi.nStyle; 	
		m_fStart  = fi.fStart; 	
	}

}


void CDlgXfSplice::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialog::OnFinalRelease();
}

void CDlgXfSplice::DoDataExchange(CDataExchange* pDX)
{
	if ( ! pDX->m_bSaveAndValidate)
		{
		CString cs(cNullString);
		CStatic *cctrl;
			if ( m_dwPicked)
				{
				CNamed *cnam = ((CFolder *)m_pRoot)->GetItem( m_dwPicked);
				if ( cnam)
					cs = cnam->GetFullName();
				}
			cctrl = (CStatic *)GetDlgItem( IDC_OTHER);
			cctrl->SetWindowText( cs);
			cs = cNullString;		// reset to nothing
			if ( m_dwSource)
				{
				CNamed *cnam = ((CFolder *)m_pRoot)->GetItem( m_dwSource);
				if ( cnam)
					cs = cnam->GetFullName();
				}
			cctrl = (CStatic *)GetDlgItem( IDC_TARGET);
			cctrl->SetWindowText( cs);
		}

	m_cStart.DDX_Value( pDX, m_fStart);

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgXfSplice)
	DDX_Check(pDX, IDC_USEBHIGH, m_bUseBHigh);
	DDX_Check(pDX, IDC_USEBRES, m_bUseBRes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXfSplice, CDialog)
	//{{AFX_MSG_MAP(CDlgXfSplice)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_EN_CHANGE(IDC_START, OnChangeStart)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposScrl1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgXfSplice, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgXfSplice)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDlgXfSplice to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {86088380-A862-11CF-AA03-444553540000}
static const IID IID_IDlgXfSplice =
{ 0x86088380, 0xa862, 0x11cf, { 0xaa, 0x3, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CDlgXfSplice, CDialog)
	INTERFACE_PART(CDlgXfSplice, IID_IDlgXfSplice, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXfSplice message handlers

void CDlgXfSplice::OnBrowse() 
{
CDlgSelectObject cdlg;
CDataSet *cdsrc = (CDataSet *)m_pRoot->GetItem( m_dwSource);

	cdlg.SetParms( m_pRoot, m_dwPicked, ntDataSet, cdsrc->GetUOM());

	if ( IDOK == cdlg.DoModal())
		{
		UpdateData( TRUE);			// update the other fields
		m_dwPicked = cdlg.m_dwSelected;
		UpdateData( FALSE);
		}
	
	
}

void CDlgXfSplice::OnChangeStart() 
{

	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USECUSTOM);
	
}

BOOL CDlgXfSplice::OnInitDialog() 
{
	m_cStart.Subclass( this, IDC_START, IDC_SCRL1);

	CDialog::OnInitDialog();
	
CStatic *cctrl;
CString cs;

	FullFormatValue( cs, m_fStartMarker, 0);
	cctrl = (CStatic *)GetDlgItem( IDC_MARKLOW);
	cctrl->SetWindowText( cs);

	FullFormatValue( cs, m_fEndMarker, 0);
	cctrl = (CStatic *)GetDlgItem( IDC_MARKHIGH);
	cctrl->SetWindowText( cs);

	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USEENTIRE + m_nStyle);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgXfSplice::OnOK() 
{
BOOL bok = FALSE;

	m_nStyle = GetCheckedRadioButton( IDC_USEENTIRE, IDC_USECUSTOM) - IDC_USEENTIRE;
	if ( m_dwPicked)
		{
		CNamed *cnam = ((CFolder *)m_pRoot)->GetItem( m_dwPicked);
		if ( ntDataSet == cnam->GetType())
			{
			CDataSet *cdr = (CDataSet *)cnam;
			if ( uomFreq== cdr->GetUOM())
				bok = TRUE;
			}
		}
	if ( ! bok)
		{
		AfxMessageBox( IDS_ERR_VALIDDATA);
		return;			// don't do an OK
		}
	
	if (! VerboseUpdateData( TRUE))
		return;

	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	SPLICEINFO fi;

		fi.bUseBHigh= m_bUseBHigh;
		fi.bUseBRes = m_bUseBRes;	
		fi.dwPicked = m_dwPicked;	
		fi.nStyle   = m_nStyle; 	
		fi.fStart   = m_fStart; 	
		capp->WriteRegistry( IDS_SPLICEINFO, &fi, sizeof(fi) );	// success???
	}

	CDialog::OnOK();
}



// -------------------------------------

/////////////////////////////////////////////////////////////////////////////
//				CXformSplice
//					Splice two datasets.....
/////////////////////////////////////////////////////////////////////////////
CXformSplice::CXformSplice( CObject *cTarget, CObject *cOther) : CXtBinary( cTarget, cOther)
{

}

CXformSplice::~CXformSplice()
{
}

int CXformSplice::DoOperation( CNamed *cdDest )	// xeq xform
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
CDataSet *cother = (CDataSet *)GetOther();
CDataSet *cdnew = (CDataSet *)cdDest;
CDataSet *pref;
float fmin, fmax;
float fdelta;
int ntotal;
float ffreq;
int i;
CDataSet *plow, *phigh;
float fdata, fphase;

	{
	CString csform, cres;
		cres.Format( "%f", m_fFreq);
		csform.Format( IDS_SPLICEDESC, (LPCSTR )cdSource->GetName(), (LPCSTR )cother->GetName(), (LPCSTR )cres);
	cdnew->SetDescription( csform);
	}

	if ( m_bUseBHigh)
		{
		plow = cdSource;		// use our source for the low frequency
		phigh = cother;
		}
	else
		{
		plow = cother;			// use the B dataset for the low frequencies
		phigh = cdSource;
		}

	fmin = plow->Minimum( dataFreq);
	fmax = phigh->Maximum( dataFreq);

			// which one is the frequency reference
	if ( m_bUseBRes)
		pref = cother;
	else
		pref = cdSource;

	fdelta = pref->GetDelta();

	ntotal = (int )((fmax - fmin) / fdelta);

	cdnew->SetUOM( uomFreq);
	cdnew->SetDOM( uomDbw);		// same as source data???

	cdnew->SetStart( fmin);
	cdnew->SetDelta( fdelta);
	cdnew->SetSize( ntotal);

	CreateProgressBar( IDS_STATCALC, 100);


	for ( i=0; i<ntotal; i++)
		{
		if ( 0 == ( i % 100))
			ShowProgressBar( (100 * i) / ntotal);
		ffreq = fdelta * i + fmin;
		if ( ffreq > m_fFreq)		// copy the high freq guy
			{
			fdata = phigh->DataValueAt( ffreq, 1);
			fphase = phigh->PhaseValueAt( ffreq);
			}
		else						// copy the low freq guy
			{
			fdata = plow->DataValueAt( ffreq, 1);
			fphase = plow->PhaseValueAt( ffreq);
			}
		cdnew->SetAbsolute(i, fdata, fphase);
		}

	CloseProgressBar();

	return 0;
}


void CDlgXfSplice::OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	m_cStart.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}
