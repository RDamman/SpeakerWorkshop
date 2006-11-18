// dlgprcha.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "dlgprcha.h"
#include "fxfont.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefChart property page

IMPLEMENT_DYNCREATE(CDlgPrefChart, CPropertyPage)

CDlgPrefChart::CDlgPrefChart() : CPropertyPage(CDlgPrefChart::IDD) , m_clrBack(), m_clrGrid()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgPrefChart)
	m_csAxisScale = _T("");
	m_csAxisTitle = _T("");
	m_csLegend = _T("");
	m_csSubTitle = _T("");
	m_csTitle = _T("");
	//}}AFX_DATA_INIT
}

CDlgPrefChart::~CDlgPrefChart()
{
}

void CDlgPrefChart::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgPrefChart::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	if ( ! pDX->m_bSaveAndValidate)	// update the display
		{
		PrettyName(0, m_csTitle);
		PrettyName(1, m_csSubTitle);
		PrettyName(2, m_csAxisTitle);
		PrettyName(3, m_csAxisScale);
		PrettyName(4, m_csLegend);
		}

	//{{AFX_DATA_MAP(CDlgPrefChart)
	DDX_Text(pDX, IDC_SHOWAXISSCALE, m_csAxisScale);
	DDX_Text(pDX, IDC_SHOWAXISTITLE, m_csAxisTitle);
	DDX_Text(pDX, IDC_SHOWLEGEND, m_csLegend);
	DDX_Text(pDX, IDC_SHOWSUBTITLE, m_csSubTitle);
	DDX_Text(pDX, IDC_SHOWTITLE, m_csTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPrefChart, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgPrefChart)
	ON_BN_CLICKED(IDC_SELAXISSCALE, OnSelaxisscale)
	ON_BN_CLICKED(IDC_SELAXISTITLE, OnSelaxistitle)
	ON_BN_CLICKED(IDC_SELLEGEND, OnSellegend)
	ON_BN_CLICKED(IDC_SELSUBTITLE, OnSelsubtitle)
	ON_BN_CLICKED(IDC_SELTITLE, OnSeltitle)
	ON_BN_CLICKED(IDC_BACKCOLOR, OnBackcolor)
	ON_BN_CLICKED(IDC_GRIDCOLOR, OnGridcolor)
	ON_BN_CLICKED(IDC_INTCOLOR, OnIntcolor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgPrefChart, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgPrefChart)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefChart message handlers



void CDlgPrefChart::PrettyName(int nFont, CString &csDest)
{
		m_sysFonts[nFont].GetPrettyName( csDest);
}

void CDlgPrefChart::EditFont(int nFont)
{
	if ( IDOK == m_sysFonts[nFont].EditProperties( this))
	{
		SetModified( TRUE);
		UpdateData ( FALSE);
	}
}


void CDlgPrefChart::OnSeltitle() 
{
	EditFont( 0);
	m_clrTitle.SetColor( m_sysFonts[ftTitle].GetColor());
	m_clrTitle.Invalidate();
}

void CDlgPrefChart::OnSelsubtitle() 
{
	EditFont( 1);
}

void CDlgPrefChart::OnSelaxistitle() 
{
	EditFont( 2);
}

void CDlgPrefChart::OnSelaxisscale() 
{
	EditFont( 3);
}

void CDlgPrefChart::OnSellegend() 
{
	EditFont( 4);
}


BOOL CDlgPrefChart::OnInitDialog() 
{
int i;

	for ( i=0; i<5; i++)
	{
		m_sysFonts[i] = CAudtestApp::GetAppFont((FONTTYPES )i);
	}

	for ( i=0; i<NUMAPPCOLORS; i++)
	{
		m_clrSystem[i] = CAudtestApp::GetAppColor( (APPCOLORS)i);
	}

	m_clrBack.SubclassDlgItem( IDC_BACKCOLOR, this);
	m_clrGrid.SubclassDlgItem( IDC_GRIDCOLOR, this);
	m_clrInterior.SubclassDlgItem( IDC_INTCOLOR, this);
	m_clrBack.SetColor( m_clrSystem[clrBackground]);
	m_clrGrid.SetColor( m_clrSystem[clrGrid]);
	m_clrInterior.SetColor( m_clrSystem[clrInterior]);

	m_clrTitle.SubclassDlgItem( IDC_SHOWTITLE, this);
	m_clrTitle.SetColor( m_sysFonts[ftTitle].GetColor());

	CPropertyPage::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgPrefChart::OnApply() 
{
int i;

	for ( i=0; i<5; i++)
	{
		CAudtestApp::GetAppFont((FONTTYPES )i) = m_sysFonts[i];
		CAudtestApp::GetAppFont((FONTTYPES )i).WriteIni( i);
	}

	for ( i=0; i<NUMAPPCOLORS; i++)
	{
		CAudtestApp::SetAppColor( (APPCOLORS)i, m_clrSystem[i]);
	}
	CAudtestApp::WriteAppColors();

	SetModified( FALSE);
	
	return CPropertyPage::OnApply();
}

void CDlgPrefChart::OnBackcolor() 
{
	m_clrSystem[clrBackground] = m_clrBack.EditColor();
	m_clrBack.Invalidate(TRUE);
	SetModified( TRUE);
}

void CDlgPrefChart::OnGridcolor() 
{

	m_clrSystem[clrGrid] = m_clrGrid.EditColor();
	m_clrGrid.Invalidate(TRUE);
	SetModified( TRUE);
	
}

void CDlgPrefChart::OnIntcolor() 
{
	m_clrSystem[clrInterior] = m_clrInterior.EditColor();
	m_clrInterior.Invalidate(TRUE);
	SetModified( TRUE);
	
}
