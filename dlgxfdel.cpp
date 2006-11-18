// dlgxfdel.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgxfdel.h"

#include "Xform.h"
#include "xformall.h"

#include "Utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


typedef struct tagDELAYINFO
	{
	BOOL	bRemoveExcess;
	float	fFactor;			// amount of delay
	} DELAYINFO;

/////////////////////////////////////////////////////////////////////////////
// CDlgXfDelay dialog


CDlgXfDelay::CDlgXfDelay(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXfDelay::IDD, pParent), m_cFactor()
{
	EnableAutomation();

	//{{AFX_DATA_INIT(CDlgXfDelay)
	m_bRemoveExcess = FALSE;
	//}}AFX_DATA_INIT

	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	DELAYINFO fi;
	if ( capp->ReadRegistry( IDS_DELAYINFO, &fi, sizeof(fi) ))	// success???
		{
		fi.fFactor = 1.0f;
		fi.bRemoveExcess = TRUE;
		}
	m_fFactor = fi.fFactor;
	m_bRemoveExcess = fi.bRemoveExcess;
	}
	m_cdSource = NULL;
	m_pCX = NULL;

}


void CDlgXfDelay::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgXfDelay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	m_cFactor.DDX_Value( pDX, m_fFactor);

	//{{AFX_DATA_MAP(CDlgXfDelay)
	DDX_Control(pDX, IDC_DELAYTIME, m_txtDelay);
	DDX_Check(pDX, IDC_REMOVE, m_bRemoveExcess);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXfDelay, CDialog)
	//{{AFX_MSG_MAP(CDlgXfDelay)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposScrl1)
	ON_BN_CLICKED(IDAPPLY, OnApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgXfDelay, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgXfDelay)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXfDelay message handlers

void CDlgXfDelay::OnOK() 
{

	if ( ! VerboseUpdateData( TRUE))
		return;
	if ( m_pCX)
	{
		m_pCX->DoUndo();			// undo it
		delete m_pCX;				// clean up
	}

	{
	CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
	DELAYINFO fi;

		fi.fFactor = m_fFactor;
		fi.bRemoveExcess = m_bRemoveExcess;
		capp->WriteRegistry( IDS_DELAYINFO, &fi, sizeof(fi) );	// success???
	}

	CDialog::OnOK();
}

BOOL CDlgXfDelay::OnInitDialog() 
{
	m_cFactor.Subclass( this, IDC_FACTOR, IDC_SCRL1);

	CDialog::OnInitDialog();

	m_txtDelay.SetWindowText("");		// turn off the display
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgXfDelay::OnDeltaposScrl1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cFactor.ProcessDelta( pNMUpDown->iDelta);		// that's it....
	
	*pResult = 0;
}


void CDlgXfDelay::OnApply() 
{
	if ( ! m_cdSource)
		return;

	if ( ! VerboseUpdateData( TRUE))
		return;

	if ( m_pCX)
	{
		m_pCX->DoUndo();			// undo it
		delete m_pCX;				// clean up
	}
	m_pCX = new CXformDelay( m_cdSource);		// input chan

	m_pCX->m_fTime = m_fFactor;
	m_pCX->m_bRemoveExcess = m_bRemoveExcess;
	m_pCX->DoExe( true);		// allow undo
	
}

void CDlgXfDelay::OnCancel() 
{
	if ( m_pCX)
	{
		m_pCX->DoUndo();			// undo it
		delete m_pCX;				// clean up
	}
	
	CDialog::OnCancel();
}
