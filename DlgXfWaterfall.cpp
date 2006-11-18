// DlgXfWaterfall.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "DlgXfWaterfall.h"

#include "Folder.h"
#include "Utils.h"
#include "Dataset.h"
#include "DlgSelec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct tagWaterinfo
	{
	float	fStart;
	float	fEnd;
	float	fTotalTime;
	float	fSmooth;
	int		iSamples;
	int		nWindow;
	int		nStyle;
	DWORD	dwReference;
	}	WATERINFO;

/////////////////////////////////////////////////////////////////////////////
// CDlgXfWaterfall dialog


CDlgXfWaterfall::CDlgXfWaterfall(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXfWaterfall::IDD, pParent), m_cfEdits()
{
	//{{AFX_DATA_INIT(CDlgXfWaterfall)
	m_iSamples = 0;
	m_csMarkLow = _T("");
	m_csMarkHigh = _T("");
	m_iWindow = -1;
	m_csReference = _T("");
	m_csSource = _T("");
	//}}AFX_DATA_INIT

	{
	WATERINFO fi;
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();

		if ( capp->ReadRegistry( IDS_WATERINFO, &fi, sizeof(fi)))	// success???
			{
			fi.fStart = 0.0f;
			fi.fEnd = 1.0f;
			fi.nWindow = 0;
			fi.nStyle = 1;
			fi.dwReference = 0;
			fi.fTotalTime = 1.0f;
			fi.iSamples = 10;
			fi.fSmooth = 0.1f;
			}
		m_fStart = fi.fStart;
		m_fEnd = fi.fEnd;
		m_iWindow = fi.nWindow;
		m_nStyle = fi.nStyle;
		m_dwReference = fi.dwReference;
		m_iSamples = fi.iSamples;
		m_fTotalTime = fi.fTotalTime;
		m_fSmooth = fi.fSmooth;
	}

}


void CDlgXfWaterfall::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgXfWaterfall)
	DDX_Text(pDX, IDC_NUMSAMPLES, m_iSamples);
	DDX_Text(pDX, IDC_MARKLOW, m_csMarkLow);
	DDX_Text(pDX, IDC_MARKHIGH, m_csMarkHigh);
	DDX_CBIndex(pDX, IDC_WINDOW, m_iWindow);
	DDX_Text(pDX, IDC_REFERENCE, m_csReference);
	DDX_Text(pDX, IDC_SOURCE, m_csSource);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXfWaterfall, CDialog)
	//{{AFX_MSG_MAP(CDlgXfWaterfall)
	ON_EN_CHANGE(IDC_END, OnChangeEnd)
	ON_EN_CHANGE(IDC_START, OnChangeStart)
	ON_BN_CLICKED(IDC_USECUSTOM, OnUsecustom)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposScrl)
	ON_BN_CLICKED(IDC_SRCSELECT, OnSrcselect)
	ON_BN_CLICKED(IDC_REFNONE, OnRefnone)
	ON_BN_CLICKED(IDC_REFSELECT, OnRefselect)
	ON_BN_CLICKED(IDC_USEMARKER, OnUsecustom)
	ON_BN_CLICKED(IDC_USEENTIRE, OnUsecustom)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposScrl)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL3, OnDeltaposScrl)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL5, OnDeltaposScrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CDlgXfWaterfall::DrawPointsInfo() 
{
int nstyle;
int nstart, nend;
CDataSet *pdata = (CDataSet *)(m_pRoot->GetItem( m_dwSource));


	if ( ! pdata || ! pdata->IsType( ntDataSet, uomTime) )
		return;			// do nothing if we don't have a source dataset that's valid

	UpdateData( TRUE);

	nstyle = GetCheckedRadioButton( IDC_USEMARKER, IDC_USECUSTOM) - IDC_USEENTIRE;
	switch( nstyle)
		{
		case 1 :			// use markers
			nstart = pdata->FreqToIndex( m_fStartMarker);
			nend = pdata->FreqToIndex( m_fEndMarker) ;
			break;
		case 2 :			// use entries
			nstart = pdata->FreqToIndex( m_fStart);
			nend = pdata->FreqToIndex( m_fEnd) ;
			break;
		case 0 :			// use them all
		default:
			ASSERT( 0);
			nstart = nend = 0; // remove warning
			break;
		}
	
CWnd *pstat = GetDlgItem( IDC_NPOINTS);	// get the static item

CString csnum;

	csnum.Format( "%d", 1 + nend - nstart);
	pstat->SetWindowText( csnum);

}



/////////////////////////////////////////////////////////////////////////////
// CDlgXfWaterfall message handlers

BOOL CDlgXfWaterfall::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	{		// initialize the spinner format group
	FormatGroup cfdata[5] = { 
							{IDC_START,		IDC_SCRL1, 0.01f, 2000000.0f, &m_fStart},
							{IDC_END,		IDC_SCRL2, 0.01f, 2000000.0f, &m_fEnd},
							{IDC_TOTALTIME,	IDC_SCRL3, 0.01f, 2000000.0f, &m_fTotalTime},
							{IDC_SMOOTH,	IDC_SCRL5, 0.01f, 2000000.0f, &m_fSmooth},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	::ComboFillString( this, IDC_WINDOW, IDS_XFFFT_FFTWINDOW);	// fill the window options
	::SpinSetRange( this, IDC_SCRL4, 2, 100);					// set # datasets range
	FullFormatValue( m_csMarkLow, m_fStartMarker, -4);			// show current markers
	FullFormatValue( m_csMarkHigh, m_fEndMarker, -4);
	CheckRadioButton( IDC_USEMARKER, IDC_USECUSTOM, IDC_USEENTIRE + m_nStyle);

	m_csReference = _T("");
	if ( m_dwReference)
	{
		CNamed *pna = m_pRoot->FindByID( m_dwReference);
		if ( pna)
			m_csReference = pna->GetName();
	}

	m_csSource = _T("");
	if ( m_dwSource)
	{
		CNamed *pna = m_pRoot->FindByID( m_dwSource);
		if ( pna)
			m_csSource = pna->GetName();
	}

	UpdateData( FALSE);		// set it now

	DrawPointsInfo();	


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgXfWaterfall::OnChangeEnd() 
{
	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USECUSTOM);
	DrawPointsInfo();	
}

void CDlgXfWaterfall::OnChangeStart() 
{
	CheckRadioButton( IDC_USEENTIRE, IDC_USECUSTOM, IDC_USECUSTOM);
	DrawPointsInfo();	
}

void CDlgXfWaterfall::OnUsecustom() 
{
	DrawPointsInfo();	
}


void CDlgXfWaterfall::OnDeltaposScrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

static int do_HitButton( CFolder *cRoot, CString& csName, DWORD& dwID, UNITMSR uom)
{
CDlgSelectObject cdlg;
int nrslt;

	cdlg.SetParms( cRoot, dwID, ntDataSet, uom);
	
	nrslt = cdlg.DoModal();

	if ( IDOK == nrslt)
		{
		dwID = cdlg.m_dwSelected;
		csName = _T("");
		if ( dwID)
			{
			CNamed *cnam = cRoot->GetItem( dwID);
			if ( cnam && cnam->IsType( ntDataSet, uom))
				csName = cnam->GetFullName();
			else
				dwID = 0;
			}
		return IDOK;
		}

	return nrslt;
}		



void CDlgXfWaterfall::OnSrcselect() 
{
	if ( IDOK == do_HitButton( m_pRoot, m_csSource, m_dwSource, uomTime) )
		UpdateData( FALSE);
	
}

void CDlgXfWaterfall::OnRefnone() 
{
	m_csReference = _T("");
	m_dwReference = 0;
	UpdateData( FALSE);
	
}

void CDlgXfWaterfall::OnRefselect() 
{
	if ( IDOK == do_HitButton( m_pRoot, m_csReference, m_dwReference, uomTime) )
		UpdateData( FALSE);
	
}

// --------------------------------------------------------------------
//			OnOK
// --------------------------------------------------------------------
void CDlgXfWaterfall::OnOK() 
{
	if ( ! VerboseUpdateData( TRUE))
		return;
	
				// radio button we get manually
	m_nStyle = GetCheckedRadioButton( IDC_USEMARKER, IDC_USECUSTOM) - IDC_USEENTIRE;

	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	WATERINFO fi;

		fi.fStart = m_fStart;
		fi.fEnd = m_fEnd;
		fi.nWindow = m_iWindow;
		fi.nStyle = m_nStyle;
		fi.dwReference = m_dwReference;
		fi.iSamples = m_iSamples;
		fi.fTotalTime = m_fTotalTime;
		fi.fSmooth = m_fSmooth;

		capp->WriteRegistry( IDS_WATERINFO, &fi, sizeof(fi) );	// success???
	}

	CDialog::OnOK();
}
