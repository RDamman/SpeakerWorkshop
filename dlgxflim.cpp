// dlgxflim.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgxflim.h"

#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

typedef struct tagLIMITINFO
	{
	float	fMin;
	float	fMax;
	BOOL	bLimitMin;
	BOOL	bLimitMax;
	} LIMITINFO;

/////////////////////////////////////////////////////////////////////////////
// CDlgXfLimit dialog


CDlgXfLimit::CDlgXfLimit(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXfLimit::IDD, pParent)
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgXfLimit)
	//}}AFX_DATA_INIT

	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	LIMITINFO fi;
	if ( capp->ReadRegistry( IDS_LIMITINFO, &fi, sizeof(fi) ))	// success???
		{
		fi.fMin = 0.0f;
		fi.fMax = 1000.0f;
		fi.bLimitMin = TRUE;
		fi.bLimitMax = TRUE;
		}
	m_fMin = fi.fMin;
	m_fMax = fi.fMax;
	m_bLimitMin = fi.bLimitMin;
	m_bLimitMax = fi.bLimitMax;
	}


}


void CDlgXfLimit::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgXfLimit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cMin.DDX_Value( pDX, m_fMin);
	m_cMax.DDX_Value( pDX, m_fMax);

	//{{AFX_DATA_MAP(CDlgXfLimit)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXfLimit, CDialog)
	//{{AFX_MSG_MAP(CDlgXfLimit)
	ON_EN_CHANGE(IDC_MAX, OnChangeMax)
	ON_EN_CHANGE(IDC_MIN, OnChangeMin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposScrl1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposScrl2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgXfLimit, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgXfLimit)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXfLimit message handlers

void CDlgXfLimit::OnChangeMax() 
{

	CheckRadioButton( IDC_RADMAX, IDC_RADMAXLIM, IDC_RADMAXLIM);
	
}

void CDlgXfLimit::OnChangeMin() 
{

	CheckRadioButton( IDC_RADMIN, IDC_RADMINLIM, IDC_RADMINLIM);
	
}

void CDlgXfLimit::OnOK() 
{
	if (! VerboseUpdateData( TRUE))
		return;

	m_bLimitMin = IsDlgButtonChecked( IDC_RADMINLIM);
	m_bLimitMax = IsDlgButtonChecked( IDC_RADMAXLIM);

	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	LIMITINFO fi;

		fi.fMin = m_fMin;
		fi.fMax = m_fMax;
		fi.bLimitMin = m_bLimitMin;
		fi.bLimitMax = m_bLimitMax;
		capp->WriteRegistry( IDS_LIMITINFO, &fi, sizeof(fi) );	// success???
	}
	
	CDialog::OnOK();
}

BOOL CDlgXfLimit::OnInitDialog() 
{

	m_cMin.Subclass( this, IDC_MIN, IDC_SCRL1);
	m_cMax.Subclass( this, IDC_MAX, IDC_SCRL2);

	CDialog::OnInitDialog();
	
	CheckRadioButton( IDC_RADMAX, IDC_RADMAXLIM, m_bLimitMax ? IDC_RADMAXLIM : IDC_RADMAX);
	CheckRadioButton( IDC_RADMIN, IDC_RADMINLIM, m_bLimitMin ? IDC_RADMINLIM : IDC_RADMIN);
	
CStatic *cctrl;
CString cs;

	FullFormatValue( cs, m_fCurrentMin, 0);
	cctrl = (CStatic *)GetDlgItem( IDC_CURMIN);
	cctrl->SetWindowText( cs);

	FullFormatValue( cs, m_fCurrentMax, 0);
	cctrl = (CStatic *)GetDlgItem( IDC_CURMAX);
	cctrl->SetWindowText( cs);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgXfLimit::OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cMin.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}

void CDlgXfLimit::OnDeltaposScrl2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cMax.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}
