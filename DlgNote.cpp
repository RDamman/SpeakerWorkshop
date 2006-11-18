// DlgNote.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "DlgNote.h"

#include "Chart.h"
#include "Dataset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNote dialog

typedef struct tagNoteinfo
	{
	bool	bDrawBox;
	bool	bDrawLine;
	bool	bFillBox;
	int		iLineWeight;
	int		iLineStyle;
	int		iDataset;
	COLORREF	rgbColor;
	}	NOTEINFO;


CDlgNote::CDlgNote(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNote::IDD, pParent), m_cfEdits()
{
	//{{AFX_DATA_INIT(CDlgNote)
	m_iDataset = -1;
	m_strText = _T("");
	m_bDrawBox = FALSE;
	m_bDrawLine = FALSE;
	m_bFillBox = FALSE;
	m_csTypeface = _T("");
	m_iLineStyle = -1;
	m_iLineWeight = -1;
	//}}AFX_DATA_INIT

	m_bNewObject = false;		// assume not new
	m_rgbFillColor = RGB(0xff,0xff,0xff);			// default to white
}


void CDlgNote::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	if ( ! pDX->m_bSaveAndValidate)	// update the display
		{
		m_cfFont.GetPrettyName( m_csTypeface);
		}

	//{{AFX_DATA_MAP(CDlgNote)
	DDX_CBIndex(pDX, IDC_DATASET, m_iDataset);
	DDX_Text(pDX, IDC_TEXT, m_strText);
	DDX_Check(pDX, IDC_DRAWBOX, m_bDrawBox);
	DDX_Check(pDX, IDC_DRAWLINE, m_bDrawLine);
	DDX_Check(pDX, IDC_FILLBOX, m_bFillBox);
	DDX_Text(pDX, IDC_TYPEFACE, m_csTypeface);
	DDX_CBIndex(pDX, IDC_LINESTYLE, m_iLineStyle);
	DDX_CBIndex(pDX, IDC_LINEWEIGHT, m_iLineWeight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNote, CDialog)
	//{{AFX_MSG_MAP(CDlgNote)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin)
	ON_BN_CLICKED(IDC_FILLCOLOR, OnFillcolor)
	ON_BN_CLICKED(IDC_SELFACE, OnSelface)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNote message handlers

BOOL CDlgNote::OnInitDialog() 
{
CComboBox *pbox;

	{		// initialize the spinner format group
	FormatGroup cfdata[2] = { 
							{IDC_VALUE, IDC_SPIN1, 0.0f, 199000.0f, &m_fValue},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);
	}

	m_clrFillColor.SubclassDlgItem( IDC_FILLCOLOR, this);

	CDialog::OnInitDialog();

	if ( m_bNewObject)			// use global default values
	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	NOTEINFO ni;

		if ( ! capp->ReadRegistry( IDS_NOTEINFO, &ni, sizeof(ni) ))
		{
		m_bDrawBox =	ni.bDrawBox;
		m_bDrawLine =	ni.bDrawLine;
		m_bFillBox =	ni.bFillBox;
		m_iLineStyle =	ni.iLineWeight;
		m_iLineWeight = ni.iLineStyle;
		m_rgbFillColor = ni.rgbColor;
		m_iDataset =	ni.iDataset;
		m_cfFont = CAudtestApp::GetAppFont( ftNotes);
		}
	}

	m_clrFillColor.SetColor( m_rgbFillColor);

	m_clsStyle.InitDialog((CComboBox *) GetDlgItem(IDC_LINESTYLE));
	m_clwWeight.InitDialog((CComboBox *) GetDlgItem(IDC_LINEWEIGHT));
	m_iLineStyle = m_clsStyle.ValueToIdx( m_iLineStyle );
	m_iLineWeight = m_clwWeight.ValueToIdx( m_iLineWeight );	// convert to other units

				// fill the dataset combo box with the datasets in the chart
	pbox = (CComboBox *)GetDlgItem( IDC_DATASET);		// get the dataset combo box
	if ( pbox && pbox->GetSafeHwnd())
	{
	CDataSet *pdata;
	int i;

		for ( i=0; i<m_pChart->GetDataCount(); i++)
		{
			pdata = m_pChart->GetDatasetAt( i);
			pbox->AddString( pdata->GetName());
		}

		if ( m_iDataset >= m_pChart->GetDataCount())
			m_iDataset = 0;
	}

	UpdateData( FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNote::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	*pResult = 0;
}


void CDlgNote::OnFillcolor() 
{
	m_rgbFillColor = m_clrFillColor.EditColor();
	m_clrFillColor.Invalidate(TRUE);

}

void CDlgNote::OnSelface() 
{
	UpdateData( TRUE);
	m_cfFont.EditProperties( this);	
	UpdateData( FALSE);
}

void CDlgNote::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	switch( nIDCtl)
		{
		case IDC_LINESTYLE :
			m_clsStyle.DrawItem( lpDrawItemStruct);
			break;
		case IDC_LINEWEIGHT :
			m_clwWeight.DrawItem( lpDrawItemStruct);
			break;
		default:
			break;
		}
	
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CDlgNote::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	switch( nIDCtl)
		{
		case IDC_LINESTYLE :
			m_clsStyle.MeasureItem( lpMeasureItemStruct);
			break;
		case IDC_LINEWEIGHT :
			m_clwWeight.MeasureItem( lpMeasureItemStruct);
			break;
		default:
			break;
		}

	CDialog::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CDlgNote::OnOK() 
{
	UpdateData( TRUE);			// get the latest data

	m_iLineStyle = m_clsStyle.IdxToValue( m_iLineStyle );
	m_iLineWeight = m_clwWeight.IdxToValue( m_iLineWeight );	// convert to other units

	if ( m_bNewObject)			// use global default values
	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	NOTEINFO ni;

		ni.bDrawBox =		m_bDrawBox ? true : false;
		ni.bDrawLine =		m_bDrawLine ? true : false;
		ni.bFillBox =		m_bFillBox ? true : false;
		ni.iLineWeight =	m_iLineStyle;
		ni.iLineStyle =		m_iLineWeight;
		ni.rgbColor =		m_rgbFillColor;
		ni.iDataset =		m_iDataset;

		capp->WriteRegistry( IDS_NOTEINFO, &ni, sizeof(ni) );	// success???
	
		CAudtestApp::GetAppFont( ftNotes) = m_cfFont;
		CAudtestApp::GetAppFont(ftNotes).WriteIni( ftNotes);
	}

	
	CDialog::OnOK();
}
