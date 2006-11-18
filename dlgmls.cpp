// dlgmls.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgmls.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static DWORD dw_Sizes[9] = { 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144 };

/////////////////////////////////////////////////////////////////////////////
// CDlgMls property page

IMPLEMENT_DYNCREATE(CDlgMls, CPropertyPage)

CDlgMls::CDlgMls() : CPropertyPage(CDlgMls::IDD)
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgMls)
	m_bEmphasis = FALSE;
	m_csSize = _T("");
	m_bCorrelate = FALSE;
	//}}AFX_DATA_INIT
}

CDlgMls::~CDlgMls()
{
}

void CDlgMls::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgMls::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	if ( ! pDX->m_bSaveAndValidate )
		m_csSize.Format( "%d", (int )m_dwNumber);
	
	//{{AFX_DATA_MAP(CDlgMls)
	DDX_Control(pDX, IDC_SAMPLESIZE, m_clSize);
	DDX_Check(pDX, IDC_EMPHASIS, m_bEmphasis);
	DDX_Text(pDX, IDC_SHOWSIZE, m_csSize);
	DDX_Check(pDX, IDC_CORRELATE, m_bCorrelate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMls, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgMls)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgMls, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgMls)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMls message handlers

BOOL CDlgMls::OnInitDialog() 
{
int i;

	CPropertyPage::OnInitDialog();

	UpdateData( TRUE);			// get m_clSize

	m_clSize.SetTicFreq( 1);
	m_clSize.SetRange(1,9);	// 1k,2,4,8,16,32,64,128

	for ( i=0; i<9; i++)
		if ( dw_Sizes[i] == m_dwNumber)
			{
			m_clSize.SetPos(i+1);
			break;
			}


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMls::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
 	switch(nSBCode)
		{
		case TB_ENDTRACK:
		case TB_LINEDOWN:
		case TB_LINEUP:
		case TB_PAGEDOWN:
		case TB_PAGEUP:
		case TB_TOP:
		case TB_BOTTOM:
			nPos = ((CSliderCtrl *)pScrollBar)->GetPos();
		case TB_THUMBTRACK:
			switch( pScrollBar->GetDlgCtrlID() )
				{
				case IDC_SAMPLESIZE :
					UpdateData( TRUE);		// get any existing data...
					m_dwNumber = dw_Sizes[nPos-1];
					UpdateData( FALSE);
					break;
				default :
					break;
				}

			break;

		default:
			break;

		}

	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}
