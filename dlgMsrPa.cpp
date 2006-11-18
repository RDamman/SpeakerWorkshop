// dlgmsrpa.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgmsrpa.h"

#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMsrPassive dialog

// the statics used by the modeless dbox
bool CDlgMsrPassive::m_bIsShowing = false;		// is it showing?
CDlgMsrPassive *CDlgMsrPassive::m_pThis = NULL;	// who it is
static WINDOWPLACEMENT g_wpWindowPlace = {0,0};

CDlgMsrPassive::CDlgMsrPassive(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMsrPassive::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgMsrPassive)
	m_csOValue = _T("");
	m_csValue = _T("");
	m_csType = _T("");
	//}}AFX_DATA_INIT

	m_nType = 0;
	m_pThis = this;
	m_bIsShowing = true;
}


void CDlgMsrPassive::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgMsrPassive::DoDataExchange(CDataExchange* pDX)
{
CWnd *pwnd;
CString csuffix;

	CDialog::DoDataExchange(pDX);

	if ( ! pDX->m_bSaveAndValidate)
		{
		CWnd *cwnd;
		FullFormatValue( m_csValue, m_fValue, 3);
		FullFormatValue( m_csOValue, m_fOther, 3);
		pwnd = GetDlgItem( IDC_OVALUE);
		if ( pwnd && pwnd->GetSafeHwnd())
			pwnd->EnableWindow( m_nType != 2);
		pwnd = GetDlgItem( IDC_STATICRES);
		if ( pwnd && pwnd->GetSafeHwnd())
			pwnd->EnableWindow( m_nType != 2);
		switch( m_nType)
			{
			case 0 :		// cap
				AddStringSuffix( m_csValue, IDS_FARAD, false);
				AddStringSuffix( m_csOValue, IDS_OHM, false);
				break;
			case 1 :		// inductor
				AddStringSuffix( m_csValue, IDS_HENRY, false);
				AddStringSuffix( m_csOValue, IDS_OHM, false);
				break;
			case 2 :		// res
				AddStringSuffix( m_csValue, IDS_OHM, false);
				break;
			}
						// we use an invisible combo box to store the strings
						// resistor/capacitor/inductor
		cwnd = GetDlgItem( IDC_COMBTYPE);
		if ( cwnd && cwnd->GetSafeHwnd() && (m_nType >= 0))
			{
			CComboBox *cb = (CComboBox *)cwnd;
			cb->GetLBText( m_nType, m_csType);
			}
		}

	//{{AFX_DATA_MAP(CDlgMsrPassive)
	DDX_Text(pDX, IDC_OVALUE, m_csOValue);
	DDX_Text(pDX, IDC_VALUE, m_csValue);
	DDX_Text(pDX, IDC_TYPE, m_csType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMsrPassive, CDialog)
	//{{AFX_MSG_MAP(CDlgMsrPassive)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgMsrPassive, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgMsrPassive)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMsrPassive message handlers


BOOL CDlgMsrPassive::OnInitDialog() 
{
	CDialog::OnInitDialog();

	::ComboFillString( this, IDC_COMBTYPE, IDS_PASS_COMBTYPE);
	
	if ( g_wpWindowPlace.length == sizeof( g_wpWindowPlace))		// it's not empty, set back there
		SetWindowPlacement( &g_wpWindowPlace);

	UpdateData( FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgMsrPassive::OnClose() 
{

	g_wpWindowPlace.length = sizeof( g_wpWindowPlace);
	GetWindowPlacement( & g_wpWindowPlace);

	CDialog::OnClose();		// although the doc says this does a destroy, apparently it doesn't for modeless guys

	DestroyWindow();
}

void CDlgMsrPassive::PostNcDestroy() 
{

	CDialog::PostNcDestroy();

	m_bIsShowing = false;

	delete this;			// per microsoft, kill us here

}
