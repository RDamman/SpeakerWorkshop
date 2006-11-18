// dlgdsdat.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dataset.h"

#include "dlgdsdat.h"

#include "math.h"
#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDsDataset property page

IMPLEMENT_DYNCREATE(CDlgDsDataset, CPropertyPage)

CDlgDsDataset::CDlgDsDataset() : CPropertyPage(CDlgDsDataset::IDD), m_cfEdits()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgDsDataset)
	m_nUom = -1;
	m_nDom = -1;
	//}}AFX_DATA_INIT

	m_bUsePoints = TRUE;
}

CDlgDsDataset::~CDlgDsDataset()
{
}

void CDlgDsDataset::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgDsDataset::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	
	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgDsDataset)
	DDX_CBIndex(pDX, IDC_UOM, m_nUom);
	DDX_CBIndex(pDX, IDC_DOM, m_nDom);
	//}}AFX_DATA_MAP

	m_bUsePoints = IsDlgButtonChecked( IDC_RADIO1);
}


BEGIN_MESSAGE_MAP(CDlgDsDataset, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgDsDataset)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposSpin)
	ON_EN_CHANGE(IDC_START, OnChangeStart)
	ON_EN_CHANGE(IDC_NPOINTS, OnChangeNpoints)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_GENERIC1, OnDeltaposSpin)
	ON_EN_CHANGE(IDC_END, OnChangeStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgDsDataset, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgDsDataset)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDsDataset message handlers

// called before the dialog is shown
void CDlgDsDataset::PreDialog( CDataSet *pcData)
{
	m_fPoints = (float )pcData->GetCount();
	m_fStart = pcData->GetStart();
	m_fEnd = pcData->Maximum( dataFreq);
	m_nUom = pcData->GetUOM();
	m_nDom = pcData->GetDOM();

}

static void re_Sample( CDataSet *pcData, int nPoints)
{
CDataSet *cd = (CDataSet *)pcData->Duplicate();
int i, nin;
float ffreq;
double dlow, dtotal;
//double dhigh
float flow, fhigh;
float fx, fy;
double dx, dy;
				// resize the dataset to be ready for new data
	pcData->SetSize( nPoints, pcData->HasPhase() ? nPoints : 0);
	pcData->SetDelta( cd->GetDelta() * cd->GetCount() / nPoints);
				// calculate the new data
		for ( i=0; i<nPoints; i++)
			{
			ffreq = pcData->DataAt( dataFreq, i);		// what frequency is that?
			nin = cd->FreqToIndex( ffreq);				// what index is that in the original?
			if ( nin == (cd->GetCount()-1))
				nin--;			// point to second last if it is the last one
			flow  = cd->DataAt( dataFreq, nin);		// get lower freq
			fhigh = cd->DataAt( dataFreq, nin+1);		// get upper freq
			dtotal = fhigh - flow;				// freq difference
			dlow  = (ffreq - flow )/ dtotal;	// low weight
//			dhigh = (fhigh - ffreq)/ dtotal;	// high weight
			if ( cd->HasPhase())
				{
				cd->GetRectangularAt( flow, &fx, &fy);
				dx = fx * (1-dlow);
				dy = fy * (1-dlow);
				cd->GetRectangularAt( fhigh, &fx, &fy);
				dx += fx * dlow;
				dy += fy * dlow;
				pcData->SetRectangular( i, (float )dx, (float )dy);
				}
			else			// no phase, just data
				{
				fx = cd->DataValueAt( nin, 1);
				dx = fx * (1-dlow);
				fx = cd->DataValueAt( nin+1, 1);
				dx += fx * dlow;
				pcData->SetAbsolute( i, (float )dx, 0.0f);
				}
			}
	delete cd;
}


// called after ok is pressed
void CDlgDsDataset::PostDialog( CDataSet *pcData)
{
	if ( m_nUom != pcData->GetUOM())
		{
		pcData->SetSize( pcData->GetCount(), (uomTime == m_nUom) ? 0 : pcData->GetCount() );
		if ( uomTime == pcData->GetUOM())		// had no phase, now it does...
			{
			int i, nlim;
			nlim = pcData->GetCount();
			for ( i=0; i<nlim; i++)
				{
				pcData->SetPhaseAt( i, FTOI(0));
				}
			}
		pcData->SetUOM( (UNITMSR )m_nUom);
		}


	if ( m_bUsePoints)
		{
		int npoints = m_fPoints;
		if ( npoints != pcData->GetCount())	// count has changed
			{
											// resample
			re_Sample( pcData, npoints);
			}
		}
	else
		{
		if ( (m_fStart != pcData->GetStart()) || (m_fEnd != pcData->Maximum( dataFreq)))	// new freq range
			{
			int i, nlim;
			double drange = (m_fEnd - m_fStart) / pcData->GetDelta();	// get range in counts...
			CDataSet *cd = (CDataSet *)pcData->Duplicate();				// use the copy as the source data
			float famp;
			float fphase = 0;
			float freq;

			pcData->SetSize( ceil(drange), pcData->HasPhase() ? ceil(drange) : 0);
			pcData->SetStart( m_fStart);

			nlim = pcData->GetCount();

			for ( i=0; i<nlim; i++)
				{
				freq = pcData->DataAt( dataFreq, i);
				famp = cd->DataValueAt( freq , 1);	// get data at this freq
				if ( pcData->HasPhase())
					fphase = cd->PhaseValueAt( freq , 1);
				pcData->SetAbsolute(i, famp, fphase);
				}

			delete cd;

			}
		}
	if ( m_nDom != pcData->GetDOM())		// change to data measure???
		{
		int i, nlim;
		float famp, fphase;
		CDataSet *cd = (CDataSet *)pcData->Duplicate();				// use the copy as the source data
		nlim = pcData->GetCount();

		pcData->SetDOM( (DATAMSR )m_nDom );		// set the thing

		for ( i=0; i<nlim; i++)
			{
			famp = cd->DataValueAt( i, 1);		// convert to float
			fphase = cd->PhaseValueAt( i, 1);	// similarly
			pcData->SetAbsolute( i, famp, fphase);	// set it with new DOM
			}

		delete cd;
		}

}



BOOL CDlgDsDataset::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[4] = { 
							{IDC_START,	IDC_SCRL1, 0.0f, 2000000.0f, &m_fStart},
							{IDC_END,	IDC_SCRL2, 0.0f, 2000000.0f, &m_fEnd},
							{IDC_NPOINTS, IDC_GENERIC1, 2.0f, 500000.0f, &m_fPoints},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CPropertyPage::OnInitDialog();

	CheckRadioButton( IDC_RADIO1, IDC_RADIO2, m_bUsePoints ? IDC_RADIO1 : IDC_RADIO2);
	{
	CzFormatEdit *cz = m_cfEdits.GetControl( IDC_NPOINTS);	// get the format control
		if ( cz)
			cz->SetDigits( -6);			// set to 6 digits?
	}

	::ComboFillString( this, IDC_UOM, IDS_DSDATA_UOM);
	::ComboFillString( this, IDC_DOM, IDS_DSDATA_DOM);

	UpdateData( FALSE);		// set it now

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDsDataset::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;

}

void CDlgDsDataset::OnChangeStart() 
{
	CheckRadioButton( IDC_RADIO1, IDC_RADIO2, m_bUsePoints ? IDC_RADIO1 : IDC_RADIO2);
	
}

void CDlgDsDataset::OnChangeNpoints() 
{
	CheckRadioButton( IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);

}
