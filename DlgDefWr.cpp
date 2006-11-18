// DlgDefWr.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "DlgDefWr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDefaultWarning dialog


CDlgDefaultWarning::CDlgDefaultWarning(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDefaultWarning::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDefaultWarning)
	m_bCheckInputRes = FALSE;
	m_bCheckResistor = FALSE;
	m_bCheckSeriesRes = FALSE;
	m_bCheckInputCap = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgDefaultWarning::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDefaultWarning)
	DDX_Check(pDX, IDC_CHECKINPUTRES, m_bCheckInputRes);
	DDX_Check(pDX, IDC_CHECKRES, m_bCheckResistor);
	DDX_Check(pDX, IDC_CHECKSERIES, m_bCheckSeriesRes);
	DDX_Check(pDX, IDC_CHECKINPUTCAP, m_bCheckInputCap);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDefaultWarning, CDialog)
	//{{AFX_MSG_MAP(CDlgDefaultWarning)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDefaultWarning message handlers

BOOL CDlgDefaultWarning::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	TESTMSR deftest;

	CAudtestApp::GetMeasures( &deftest);

		if ( deftest.fResistor > 2.0f && deftest.fResistor < 20.0f &&
			 deftest.fSeriesRes < 1.0f &&
			 deftest.fInputRes > 1000.0f &&
			 deftest.fInputCap < .00001f		// 10 uf
			 )
		{			// if we get here, everything is ok
			PostMessage( WM_CLOSE);			// close the dialog
		}

	FormatStatic( IDC_SERIESRES, deftest.fSeriesRes);
	FormatStatic( IDC_RESISTOR,  deftest.fResistor);
	FormatStatic( IDC_INPUTRES,  deftest.fInputRes);
	FormatStatic( IDC_INPUTCAP,  deftest.fInputCap);
			// use the same checks as above
	m_bCheckResistor = ! ( deftest.fResistor > 2.0f && deftest.fResistor < 20.0f);
	m_bCheckInputRes = ! (deftest.fInputRes > 1000.0f);
	m_bCheckInputCap = ! (deftest.fInputCap < .00001f);
	m_bCheckSeriesRes = !(deftest.fSeriesRes < 1.0f);

	UpdateData( FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDefaultWarning::FormatStatic(UINT uID, float fValue)
{
CStatic *cst;
CString csvalue;

	cst = (CStatic *)GetDlgItem( uID);
	if ( ! cst)
		ASSERT( 0);			// whoa
	csvalue.Format( "%.1f", fValue);
	cst->SetWindowText( csvalue);

}
