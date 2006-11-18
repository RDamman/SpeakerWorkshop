// dlggrid.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "chart.h"

#include "ctrls.h"

#include "zFormEdt.h"
#include "dlggrid.h"


#include "fxFont.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGrid property page

IMPLEMENT_DYNCREATE(CDlgGridX, CDlgGrid)
IMPLEMENT_DYNCREATE(CDlgGridY, CDlgGrid)
IMPLEMENT_DYNCREATE(CDlgGridY2, CDlgGrid)
IMPLEMENT_DYNCREATE(CDlgGrid, CPropertyPage)


CDlgGrid::CDlgGrid(void ) : CPropertyPage( CDlgGrid::IDD, 0), m_cfEdits()
{
}



CDlgGrid::CDlgGrid(int nIdCaption) : CPropertyPage( CDlgGrid::IDD, nIdCaption), m_cfEdits()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgGrid)
	m_bAutoScale = FALSE;
	m_bAutoTic = FALSE;
	m_bIsLog = FALSE;
	m_bShowGrid = FALSE;
	m_bShowTic = FALSE;
	m_bDrawMajor = FALSE;
	m_bDrawMinor = FALSE;
	m_nColor = -1;
	m_nColor2 = -1;
	m_nLineStyle = -1;
	m_nLineStyle2 = -1;
	m_nLineWeight = -1;
	m_nLineWeight2 = -1;
	m_szGridTitle = _T("");
	m_bShowGTitle = FALSE;
	//}}AFX_DATA_INIT


	m_pcGrid = NULL;

}

CDlgGrid::~CDlgGrid()
{
}

void CDlgGrid::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgGrid::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgGrid)
	DDX_Check(pDX, IDC_AUTOBND, m_bAutoScale);
	DDX_Check(pDX, IDC_AUTOTIC, m_bAutoTic);
	DDX_Check(pDX, IDC_LOG, m_bIsLog);
	DDX_Check(pDX, IDC_SHOWGRID, m_bShowGrid);
	DDX_Check(pDX, IDC_SHOWTIC, m_bShowTic);
	DDX_Check(pDX, IDC_BMAJOR, m_bDrawMajor);
	DDX_Check(pDX, IDC_BMINOR, m_bDrawMinor);
	DDX_CBIndex(pDX, IDC_COLOR, m_nColor);
	DDX_CBIndex(pDX, IDC_COLOR2, m_nColor2);
	DDX_CBIndex(pDX, IDC_LINESTYLE, m_nLineStyle);
	DDX_CBIndex(pDX, IDC_LINESTYLE2, m_nLineStyle2);
	DDX_CBIndex(pDX, IDC_LINEWEIGHT, m_nLineWeight);
	DDX_CBIndex(pDX, IDC_LINEWEIGHT2, m_nLineWeight2);
	DDX_Text(pDX, IDC_GTITLE, m_szGridTitle);
	DDX_Check(pDX, IDC_SHOWTITLE, m_bShowGTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGrid, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgGrid)
	ON_BN_CLICKED(IDC_SELFONT, OnSelfont)
	ON_BN_CLICKED(IDC_SELTITLEFONT, OnSeltitlefont)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINMAJOR, OnDeltaposSpin)
	ON_EN_CHANGE(IDC_MAJOR, OnChangeMaxGrid)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINMINOR, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINMAX, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINMIN, OnDeltaposSpin)
	ON_EN_CHANGE(IDC_MINOR, OnChangeMinGrid)
	ON_EN_CHANGE(IDC_MAX, OnChangeScale)
	ON_EN_CHANGE(IDC_MIN, OnChangeScale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgGrid, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgGrid)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGrid message handlers

void CDlgGrid::UseGrid( CGrid *pcGrid)
{
	m_pcGrid = pcGrid;

	m_bIsLog = pcGrid->IsLog();
	m_fMax = pcGrid->GetMax();
	m_fMin = pcGrid->GetMin();

	m_bAutoScale = 	pcGrid->m_bAutoScale;
	m_bAutoTic = 	pcGrid->m_bAutoTic;
	m_bShowGrid = 	pcGrid->m_bShowGrid;
	m_bShowTic = 	pcGrid->m_bShowTic;
	m_bShowGTitle =	pcGrid->m_bShowTitle;
	m_bDrawMajor = 	pcGrid->m_bDrawMajor;
	m_fMajor = 		pcGrid->m_fMajor;
	m_bDrawMinor = 	pcGrid->m_bDrawMinor;
	m_fMinor = 		pcGrid->m_fMinor;

	m_szGridTitle =		pcGrid->GetTitle();

	m_cMajor = pcGrid->m_ccMajor;
	m_cMinor = pcGrid->m_ccMinor;

	m_nColor	  = m_cclrMajor.ValueToIdx( m_cMajor.GetColor());
	m_nColor2	  = m_cclrMinor.ValueToIdx( m_cMinor.GetColor());
	m_nLineStyle  = m_clsMajor.ValueToIdx( m_cMajor.GetStyle());
	m_nLineStyle2  = m_clsMinor.ValueToIdx( m_cMinor.GetStyle());
	m_nLineWeight = m_clwMajor.ValueToIdx( m_cMajor.GetWidth());
	m_nLineWeight2 = m_clwMinor.ValueToIdx( m_cMinor.GetWidth());

}


void CDlgGrid::SetGrid( CGrid *pcGrid)
{
	pcGrid->SetLog( m_bIsLog);
	pcGrid->SetMax( m_fMax);
	pcGrid->SetMin( m_fMin);
	pcGrid->SetTitle( m_szGridTitle);
	pcGrid->m_bAutoScale = 	m_bAutoScale;
	pcGrid->m_bAutoTic = 	m_bAutoTic;
	pcGrid->m_bShowGrid = 	m_bShowGrid;
	pcGrid->m_bShowTic = 	m_bShowTic;
	pcGrid->m_bShowTitle =	m_bShowGTitle;
	pcGrid->m_bDrawMajor = 	m_bDrawMajor;
	pcGrid->m_fMajor = 		m_fMajor;
	pcGrid->m_bDrawMinor = 	m_bDrawMinor;
	pcGrid->m_fMinor = 		m_fMinor;

	m_cMajor.SetColor( m_cclrMajor.IdxToValue( m_nColor));
	m_cMinor.SetColor( m_cclrMinor.IdxToValue( m_nColor2));
	m_cMajor.SetStyle( m_clsMajor.IdxToValue( m_nLineStyle));
	m_cMinor.SetStyle( m_clsMinor.IdxToValue( m_nLineStyle2));
	m_cMajor.SetWidth( m_clwMajor.IdxToValue( m_nLineWeight));
	m_cMinor.SetWidth( m_clwMinor.IdxToValue( m_nLineWeight2));
	
	pcGrid->m_ccMajor = m_cMajor;
	pcGrid->m_ccMinor = m_cMinor;

	pcGrid->SetVisible( m_bShowGrid);	// set visibility up
}

// ----------------------------------------------
//	X,Y,Y2 customization
// -----------------------------------------------

	CDlgGridX::CDlgGridX() : CDlgGrid( IDS_XAXIS)
{
}

	CDlgGridY::CDlgGridY() : CDlgGrid( IDS_YAXIS)
{
}

	CDlgGridY2::CDlgGridY2() : CDlgGrid( IDS_Y2AXIS)
{
}


BOOL CDlgGrid::OnInitDialog() 
{

	{		// initialize the spinner format group
		FormatGroup cfdata[5] = { 
							{IDC_MAJOR,		IDC_SPINMAJOR,	0.0f, 10000000.0f, &m_fMajor},
							{IDC_MINOR,		IDC_SPINMINOR,	0.0f, 10000000.0f, &m_fMinor},
							{IDC_MIN,		IDC_SPINMIN,	-10000000.0f, 10000000.0f, &m_fMin},
							{IDC_MAX,		IDC_SPINMAX,	-10000000.0f, 10000000.0f, &m_fMax},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	CPropertyPage::OnInitDialog();
	
	m_cclrMajor.InitDialog((CComboBox *) GetDlgItem(IDC_COLOR));
	m_cclrMinor.InitDialog((CComboBox *) GetDlgItem(IDC_COLOR2));
	m_clsMajor.InitDialog((CComboBox *) GetDlgItem(IDC_LINESTYLE));
	m_clsMinor.InitDialog((CComboBox *) GetDlgItem(IDC_LINESTYLE2));
	m_clwMajor.InitDialog((CComboBox *) GetDlgItem(IDC_LINEWEIGHT));
	m_clwMinor.InitDialog((CComboBox *) GetDlgItem(IDC_LINEWEIGHT2));

	m_nColor	  = m_cclrMajor.ValueToIdx( m_cMajor.GetColor());
	m_nColor2	  = m_cclrMinor.ValueToIdx( m_cMinor.GetColor());
	m_nLineStyle  = m_clsMajor.ValueToIdx( m_cMajor.GetStyle());
	m_nLineStyle2  = m_clsMinor.ValueToIdx( m_cMinor.GetStyle());
	m_nLineWeight = m_clwMajor.ValueToIdx( m_cMajor.GetWidth());
	m_nLineWeight2 = m_clwMinor.ValueToIdx( m_cMinor.GetWidth());

	UpdateData( FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgGrid::OnSelfont() 
{
	CAudtestApp::EditAppFont( ftScale);

}

void CDlgGrid::OnSeltitlefont() 
{
	CAudtestApp::EditAppFont( ftAxisTitle);
}


void CDlgGrid::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default

	switch( nIDCtl)
		{
		case IDC_COLOR :
			m_cclrMajor.DrawItem( lpDrawItemStruct);
			break;
		case IDC_COLOR2 :
			m_cclrMinor.DrawItem( lpDrawItemStruct);
			break;
		case IDC_LINESTYLE :
			m_clsMajor.DrawItem( lpDrawItemStruct);
			break;
		case IDC_LINESTYLE2 :
			m_clsMinor.DrawItem( lpDrawItemStruct);
			break;
		case IDC_LINEWEIGHT :
			m_clwMajor.DrawItem( lpDrawItemStruct);
			break;
		case IDC_LINEWEIGHT2 :
			m_clwMinor.DrawItem( lpDrawItemStruct);
			break;
		default:
			break;
		}
	
	
	CPropertyPage::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CDlgGrid::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
		switch( nIDCtl)
		{
		case IDC_COLOR :
			m_cclrMajor.MeasureItem( lpMeasureItemStruct);
			break;
		case IDC_COLOR2 :
			m_cclrMinor.MeasureItem( lpMeasureItemStruct);
			break;
		case IDC_LINESTYLE :
			m_clsMajor.MeasureItem( lpMeasureItemStruct);
			break;
		case IDC_LINESTYLE2 :
			m_clsMinor.MeasureItem( lpMeasureItemStruct);
			break;
		case IDC_LINEWEIGHT :
			m_clwMajor.MeasureItem( lpMeasureItemStruct);
			break;
		case IDC_LINEWEIGHT2 :
			m_clwMinor.MeasureItem( lpMeasureItemStruct);
			break;
		default:
			break;
		}
	

	
	CPropertyPage::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}



void CDlgGrid::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}

void CDlgGrid::OnChangeMaxGrid() 
{
	if ( IsDlgButtonChecked( IDC_AUTOTIC) || ! IsDlgButtonChecked( IDC_BMAJOR))
		{
		UpdateData( TRUE);
		m_bAutoTic = FALSE;
		m_bDrawMajor = TRUE;
		UpdateData( FALSE);
		}
}

void CDlgGrid::OnChangeMinGrid() 
{
	if ( IsDlgButtonChecked( IDC_AUTOTIC) || ! IsDlgButtonChecked( IDC_BMINOR))
		{
		UpdateData( TRUE);
		m_bAutoTic = FALSE;
		m_bDrawMinor = TRUE;
		UpdateData( FALSE);
		}
}

void CDlgGrid::OnChangeScale() 
{
	if ( IsDlgButtonChecked( IDC_AUTOBND))
		{
		UpdateData( TRUE);
		m_bAutoScale = FALSE;
		UpdateData( FALSE);
		}	
}

