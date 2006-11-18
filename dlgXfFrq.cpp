// dlgxfgro.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "Xform.h"
#include "XformAll.h"

#include "zFormEdt.h"
#include "dlgXfFrq.h"

#include "dlgSelec.h"

#include "AudteDoc.h"
#include "DataSet.h"
#include "Utils.h"

#include "OpItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

typedef struct tagCALCFREQINFO
	{
	float	fStart;
	float	fEnd;
	int		nStyle;
	int		nWindow;
	int		nCalibType;
	BOOL	bUseReference;
	DWORD	dwReference;		// short term use only.....
	}	CALCFREQINFO;



/////////////////////////////////////////////////////////////////////////////
// CDlgXfCalcFrequency dialog


CDlgXfCalcFrequency::CDlgXfCalcFrequency(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXfCalcFrequency::IDD, pParent), m_cfEdits()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgXfCalcFrequency)
	m_nCalibType = -1;
	m_nWindow = -1;
	m_bUseReference = FALSE;
	//}}AFX_DATA_INIT

	m_pRoot = NULL;

	{
	CALCFREQINFO fi;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		if ( capp->ReadRegistry( IDS_CALCFREQINFO, &fi, sizeof(fi)))	// success???
			{		// failure, we need to set it
			fi.fStart = 0.0f;
			fi.fEnd = 1.0f;
			fi.nStyle = 0;
			fi.nWindow = 0;
			fi.bUseReference = FALSE;
			fi.dwReference = 0;
			fi.nCalibType = 0;
			}
		m_fStart = fi.fStart;
		m_fEnd = fi.fEnd;
		m_nStyle = fi.nStyle;
		m_nWindow = fi.nWindow;
		m_bUseReference = fi.bUseReference;
		m_dwReference = fi.dwReference;
		m_nCalibType = fi.nCalibType;
	}


}


void CDlgXfCalcFrequency::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgXfCalcFrequency::DoDataExchange(CDataExchange* pDX)
{
	if ( ! pDX->m_bSaveAndValidate)		// send to dbox?
		{
		CString cs("");
		CStatic *cctrl;
			if ( m_dwReference && m_pRoot)
				{
				CNamed *crefer = m_pRoot->GetItem( m_dwReference);
				if ( crefer)
					cs = crefer->GetName();
				}
			cctrl = (CStatic *)GetDlgItem( IDC_REFERNAME);
			cctrl->SetWindowText( cs);
		}


	m_cfEdits.DDX_All( pDX);

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgXfCalcFrequency)
	DDX_CBIndex(pDX, IDC_CALIBTYPE, m_nCalibType);
	DDX_CBIndex(pDX, IDC_FFTWINDOW, m_nWindow);
	DDX_Check(pDX, IDC_USECALIB, m_bUseReference);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXfCalcFrequency, CDialog)
	//{{AFX_MSG_MAP(CDlgXfCalcFrequency)
	ON_EN_CHANGE(IDC_END, OnChangeEnd)
	ON_EN_CHANGE(IDC_START, OnChangeStart)
	ON_BN_CLICKED(IDC_SELREFER, OnSelrefer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgXfCalcFrequency, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgXfCalcFrequency)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXfCalcFrequency message handlers

void CDlgXfCalcFrequency::OnOK() 
{

	if ( ! VerboseUpdateData( TRUE))
		return;

	m_nStyle = GetCheckedRadioButton( IDC_USEENTIRE, IDC_USECUSTOM) - IDC_USEENTIRE;
	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	CALCFREQINFO fi;

		fi.fStart = m_fStart;
		fi.fEnd =	m_fEnd;
		fi.nStyle = m_nStyle;
		fi.nWindow = m_nWindow;
		fi.bUseReference = m_bUseReference;
		fi.dwReference = m_dwReference;
		fi.nCalibType = m_nCalibType;

		capp->WriteRegistry( IDS_CALCFREQINFO, &fi, sizeof(fi) );	// success???
	}

	CDialog::OnOK();
}

BOOL CDlgXfCalcFrequency::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[3] = { 
							{IDC_START,	IDC_SCRL1, 1.0f, 20000.0f, &m_fStart},
							{IDC_END,	IDC_SCRL2, 1.0f, 20000.0f, &m_fEnd},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CDialog::OnInitDialog();

	::ComboFillString( this, IDC_FFTWINDOW, IDS_XFCF_FFTWINDOW);
	::ComboFillString( this, IDC_CALIBTYPE, IDS_XFCF_CALIB);
	
CStatic *cctrl;
CString cs;

	FullFormatValue( cs, m_fStartMarker, -4);
	cctrl = (CStatic *)GetDlgItem( IDC_MARKLOW);
	cctrl->SetWindowText( cs);

	FullFormatValue( cs, m_fEndMarker, -4);
	cctrl = (CStatic *)GetDlgItem( IDC_MARKHIGH);
	cctrl->SetWindowText( cs);

	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USEENTIRE + m_nStyle);

	UpdateData( FALSE);		// set it now
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgXfCalcFrequency::OnChangeEnd() 
{

	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USECUSTOM);
	
	
}

void CDlgXfCalcFrequency::OnChangeStart() 
{

	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USECUSTOM);
	
	
}


void CDlgXfCalcFrequency::OnSelrefer() 
{
CDlgSelectObject cdlg;

	cdlg.SetParms( m_pRoot, m_dwReference, ntDataSet, uomTime);

	if ( IDOK == cdlg.DoModal())
		{
		UpdateData( TRUE);			// update the other fields
		m_dwReference = cdlg.m_dwSelected;
		UpdateData( FALSE);			// now put them back
		}
	
}


/////////////////////////////////////////////////////////////////////////////
//				CXformCalcFrequency
//					CalcFrequency two datasets.....
/////////////////////////////////////////////////////////////////////////////
CXformCalcFrequency::CXformCalcFrequency( CObject *cTarget) : CXtransform( cTarget)
{
	m_nStart = 0;
	m_nEnd = 0;			// need these defaults to indicate entire range
	m_nCalibType = 0;	// no calibration by default
	m_bUseReference = FALSE;
	m_dwReference = 0;
	m_nWindow = 0;
}

CXformCalcFrequency::~CXformCalcFrequency( void)
{
}

int CXformCalcFrequency::DoOperation( CNamed *cdDest)	// xeq xform
{
CDataSet *cdsource = (CDataSet *)FindTargetObject();
CDataSet *cdnew = (CDataSet *)cdDest;
int nstart = m_nStart;
int nend = m_nEnd + 1;	// go 1 more to be non-inclusive
CAudtestDoc *pDoc;
CFolder *proot;

	proot = (CFolder *)(cdsource->GetRootObject());

	ASSERT_KINDOF( CFolder, proot);

	pDoc = (CAudtestDoc *)(proot->GetDocument());

	ASSERT_KINDOF( CAudtestDoc,  pDoc);

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

	cdnew->SetStart( cdsource->DataAt( dataFreq, nstart));
	cdnew->SetSize( nend - nstart);

	CreateProgressBar( IDS_STATCALCFFT, 100);

// pcinput is the fft of the source time data
// pcrefer is the fft of the reference time data
CDataSet *pcinput = NULL;
CDataSet *pcrefer = NULL;

						// note that queueanddo keeps the pointer for its own
						// but it is guaranteed valid for a while....
		pcinput = new CDataSet();		// make a new one
		::ExecuteFft( pcinput, cdsource, nstart, nend, m_nWindow);
		StepProgressBar();

		if ( m_bUseReference && m_dwReference)
			{
			CDataSet *pcr = (CDataSet *)proot->GetItem( m_dwReference);
			if ( ntDataSet == pcr->GetType() && uomTime == ((CDataSet *)pcr)->GetUOM() )
				{
				pcrefer = new CDataSet();
				::ExecuteFft( pcrefer, pcr, 0, nend - nstart, m_nWindow);
				StepProgressBar();
				}
			else
				pcrefer = NULL;
			}

						// if there is calibration data, use it
//		CDataSet *ccal = pcrefer->FindItem("Calib Channels");
//		combine divide the right one ONLY
		if ( pcinput && pcrefer)			// we have a reference
			{
			::ExecuteCombine( pcinput, pcrefer, 3);		// divide
			StepProgressBar();
			}

//		 if there is calibration data, use it
		if ( pcinput && m_nCalibType)
			{
			CDataSet *pccal;
			TESTCAL tcal;

			tcal = *pDoc->GetCalib();
			if ( tcal.dwLeftRight)		// we have a cal dataset
				{
				pccal = (CDataSet *)proot->GetItem( tcal.dwLeftRight);
				if ( pccal)
					{
					ASSERT_KINDOF( CDataSet, pccal);
					::ExecuteCombine( pcinput, pccal, 3);
					StepProgressBar();
					}
				}
			if ( 2 == m_nCalibType)		// mic calibration
				{
				if ( tcal.dwMicrophone)		// we have a cal dataset
					{
					pccal = (CDataSet *)proot->GetItem( tcal.dwMicrophone);
					if ( pccal)
						{
						ASSERT_KINDOF( CDataSet, pccal);
						::ExecuteCombine( pcinput, pccal, 3);
						StepProgressBar();
						}
					}
				}
			}

// do we have an input dataset, set the name and then copy it to output
		if ( pcinput)
			{
			pcinput->SetName( cdnew->GetName());
			pcinput->SetRootObject( cdnew->GetRootObject());	// set the root object
			*cdnew = *pcinput;		// copy the data
			}

					// we're done with pcinput and pcrefer
		if ( pcinput)
			delete pcinput;
		if ( pcrefer)
			delete pcrefer;

	CloseProgressBar();

	return 0;
}



void CDlgXfCalcFrequency::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}
