// dlgxfsca.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgxfsca.h"

#include "Utils.h"

#include "Xform.h"
#include "XformAll.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

typedef struct tagSCALEINFO
{
	BOOL	bUseDb;
	int		nMethod;
	float	fFactor;
	float	fdB;
} SCALEINFO;

/////////////////////////////////////////////////////////////////////////////
// CDlgXfScale dialog


CDlgXfScale::CDlgXfScale(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXfScale::IDD, pParent), m_cdB(), m_cFactor()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgXfScale)
	m_nMethod = -1;
	//}}AFX_DATA_INIT

	m_bUseDb = TRUE;
	m_pCX = NULL;
	m_cdSource = NULL;

	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	SCALEINFO fi;
	if ( capp->ReadRegistry( IDS_SCALEINFO, &fi, sizeof(fi) ))	// success???
		{
		fi.fdB = 0.0f;
		fi.fFactor = 1.0f;
		fi.nMethod = 0;
		fi.bUseDb = 1;
		}
	m_fdB	= fi.fdB;
	m_fFactor = fi.fFactor;
	m_nMethod = fi.nMethod;
	m_bUseDb = fi.bUseDb;
	}


}


void CDlgXfScale::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgXfScale::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cdB.DDX_Value( pDX, m_fdB);
	m_cFactor.DDX_Value( pDX, m_fFactor);
	
	//{{AFX_DATA_MAP(CDlgXfScale)
	DDX_CBIndex(pDX, IDC_METHOD, m_nMethod);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXfScale, CDialog)
	//{{AFX_MSG_MAP(CDlgXfScale)
	ON_EN_CHANGE(IDC_FACTOR, OnChangeFactor)
	ON_EN_CHANGE(IDC_DB, OnChangeDb)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposScrl1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposScrl2)
	ON_BN_CLICKED(IDAPPLY, OnApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgXfScale, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgXfScale)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXfScale message handlers

void CDlgXfScale::OnOK() 
{
	if ( ! VerboseUpdateData( TRUE))
		return;
	if ( m_pCX)
	{
		m_pCX->DoUndo();			// undo it
		delete m_pCX;				// clean up
	}

	m_bUseDb = IsDlgButtonChecked( IDC_RADDB);
	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	SCALEINFO fi;

		fi.fdB		= m_fdB;
		fi.fFactor	= m_fFactor;
		fi.nMethod	= m_nMethod;
		fi.bUseDb	= m_bUseDb;
		capp->WriteRegistry( IDS_SCALEINFO, &fi, sizeof(fi) );	// success???
	}
	
	CDialog::OnOK();
}

BOOL CDlgXfScale::OnInitDialog() 
{
	m_cdB.Subclass( this, IDC_DB, IDC_SCRL1);
	m_cFactor.Subclass( this, IDC_FACTOR, IDC_SCRL2);

	CDialog::OnInitDialog();

	::ComboFillString( this, IDC_METHOD, IDS_XFSCALE_METHOD);

	UpdateData( FALSE);

	CheckRadioButton( IDC_RADDB, IDC_RADFACTOR, m_bUseDb ? IDC_RADDB : IDC_RADFACTOR);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgXfScale::OnChangeFactor() 
{
	CheckRadioButton( IDC_RADDB, IDC_RADFACTOR, IDC_RADFACTOR);
	
}

void CDlgXfScale::OnChangeDb() 
{
	CheckRadioButton( IDC_RADDB, IDC_RADFACTOR, IDC_RADDB);
	
}

void CDlgXfScale::OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cdB.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}

void CDlgXfScale::OnDeltaposScrl2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	m_cFactor.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}

void CDlgXfScale::OnApply() 
{
	if ( ! m_cdSource)
		return;

	if ( ! VerboseUpdateData( TRUE))
		return;
	m_bUseDb = IsDlgButtonChecked( IDC_RADDB);

	if ( m_pCX)
	{
		m_pCX->DoUndo();			// undo it
		delete m_pCX;				// clean up
	}
	m_pCX = new CXformScale( m_cdSource);		// the transform

	m_pCX->SetVars( m_fdB, m_fFactor, m_nMethod, m_bUseDb);

	m_pCX->DoExe( true);		// allow undo
	
}

void CDlgXfScale::OnCancel() 
{
	if ( m_pCX)
	{
		m_pCX->DoUndo();			// undo it
		delete m_pCX;				// clean up
	}
	
	CDialog::OnCancel();
}
