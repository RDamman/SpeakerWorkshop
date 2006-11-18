// dlgxfgro.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "Xform.h"
#include "zFormEdt.h"

#include "dlgXfGrp.h"

#include "DataSet.h"
#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

typedef struct tagGrpDelayinfo
	{
	float	fStart;
	float	fEnd;
	int		nStyle;
	}	GRPDELAYINFO;



/////////////////////////////////////////////////////////////////////////////
// CDlgXfGrpDelay dialog


CDlgXfGrpDelay::CDlgXfGrpDelay(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXfGrpDelay::IDD, pParent), m_cfEdits()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgXfGrpDelay)
	//}}AFX_DATA_INIT

	{
	GRPDELAYINFO fi;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		if ( capp->ReadRegistry( IDS_GRPDELAYINFO, &fi, sizeof(fi)))	// success???
			{
			fi.fStart = 0.0f;
			fi.fEnd = 1.0f;
			fi.nStyle = 0;
			}
		m_fStart = fi.fStart;
		m_fEnd = fi.fEnd;
		m_nStyle = fi.nStyle;
	}


}


void CDlgXfGrpDelay::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgXfGrpDelay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgXfGrpDelay)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXfGrpDelay, CDialog)
	//{{AFX_MSG_MAP(CDlgXfGrpDelay)
	ON_EN_CHANGE(IDC_END, OnChangeEnd)
	ON_EN_CHANGE(IDC_START, OnChangeStart)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgXfGrpDelay, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgXfGrpDelay)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXfGrpDelay message handlers

void CDlgXfGrpDelay::OnOK() 
{
	if ( ! VerboseUpdateData( TRUE))
		return;

	m_nStyle = GetCheckedRadioButton( IDC_USEENTIRE, IDC_USECUSTOM) - IDC_USEENTIRE;
	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	GRPDELAYINFO fi;

		fi.fStart = m_fStart;
		fi.fEnd =	m_fEnd;
		fi.nStyle = m_nStyle;

		capp->WriteRegistry( IDS_GRPDELAYINFO, &fi, sizeof(fi) );	// success???
	}
	
	CDialog::OnOK();
}

BOOL CDlgXfGrpDelay::OnInitDialog() 
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
	
CStatic *cctrl;
CString cs;

	FullFormatValue( cs, m_fStartMarker, 0);
	cctrl = (CStatic *)GetDlgItem( IDC_MARKLOW);
	cctrl->SetWindowText( cs);

	FullFormatValue( cs, m_fEndMarker, 0);
	cctrl = (CStatic *)GetDlgItem( IDC_MARKHIGH);
	cctrl->SetWindowText( cs);

	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USEENTIRE + m_nStyle);

	UpdateData( FALSE);		// set it now
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgXfGrpDelay::OnChangeEnd() 
{

	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USECUSTOM);
	
	
}

void CDlgXfGrpDelay::OnChangeStart() 
{

	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USECUSTOM);
	
	
}


/////////////////////////////////////////////////////////////////////////////
//				CXformCalcDelay
//					CalcDelay two datasets.....
/////////////////////////////////////////////////////////////////////////////
CXformCalcDelay::CXformCalcDelay( CObject *cTarget) : CXtransform( cTarget)
{
	m_nStart = 0;
	m_nEnd = 0;			// need these defaults to indicate entire range
}

CXformCalcDelay::~CXformCalcDelay( void)
{
}

static void do_GroupDelay( CDataSet *cdDest, CDataSet *cdSource, int nStart, int nEnd)
{
double dstartphase;
double daddon = 0;
double ddelta = cdSource->GetDelta();
double dentry;
double dlastphase;
int i;

	dentry = 0;
	dlastphase = dentry;
	dstartphase = ITOF( cdSource->GetPhaseAt( nStart) );
	cdDest->SetRectangular( 0, 0.0f, 0.0f);		// start at 0???

	for ( i = (nStart+1); i < nEnd; i++)
		{
		dentry = (ITOF(cdSource->GetPhaseAt( i)) - dstartphase) + daddon;
		if ( (dentry - dlastphase) > 180 || (dentry-dlastphase) < 180)	// major shift
			{
			int j = (int )((dlastphase - dentry) / 180);
			daddon += 360 * j;
			dentry += 360 * j;
			}
//		dlastphase = dentry;
//		dentry /= ddelta * (i-nStart);		// divide by delta frequency
		cdDest->SetRectangular( i-nStart, 1000*ONEPI * (dentry - dlastphase)/(ddelta*180), 0.0f);
		dlastphase = dentry;
		}

				// duplicate the 1th entry to the 0th entry for continuity
	cdDest->SetDataAt( 0, cdDest->GetDataAt(1), cdDest->GetPhaseAt(1));
}


int CXformCalcDelay::DoOperation( CNamed *cdDest)	// xeq xform
{
CDataSet *cdsource = (CDataSet *)FindTargetObject();
CDataSet *cdnew = (CDataSet *)cdDest;
int nstart = m_nStart;
int nend = m_nEnd + 1;	// go 1 more to be non-inclusive

	cdnew->CopyHeader( cdsource);
	cdnew->SetDOM( uomVolts);			// absolute numbers, not logs

	if ( nstart == 0 && nend == 1)		// means use entire sample
		{
		nstart = 0;
		nend = cdsource->GetCount();
		}

	if ( nstart >= nend)
		return 1;			// couldn't do it! bad data

	if ( nstart < 0)
		nstart = 0;
	if ( nend > cdsource->GetCount())
		nend = cdsource->GetCount();

	{
	CString csform, cstart, cend;
		csform.GetBuffer(1024);	// this could be pretty long
		cstart.Format( "%f", cdsource->DataAt( dataFreq, nstart));
		cend.Format( "%f", cdsource->DataAt( dataFreq, nend-1));
		csform.Format( IDS_GRPDDESC, (LPCSTR )cdsource->GetName(), (LPCSTR )cstart, (LPCSTR )cend);
	cdnew->SetDescription( csform);
	}

	cdnew->SetStart( cdsource->DataAt( dataFreq, nstart));
	cdnew->SetSize( nend - nstart);

	CreateProgressBar( IDS_STATCALCFFT, 100);

	do_GroupDelay( cdnew, cdsource, nstart, nend);

	CloseProgressBar();

	return 0;
}




void CDlgXfGrpDelay::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}
