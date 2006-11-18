// dlgselec.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgselec.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectObject dialog


CDlgSelectObject::CDlgSelectObject(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectObject::IDD, pParent), m_cTree()
{
	EnableAutomation();

	m_bAllowOK = FALSE;
	m_cRoot = NULL;
	m_dwLastSel = 0;
	m_dwSelected = 0;
	m_dwTargetID = 0;
	m_nSelect = ntAny;
	m_nUOM = uomAny;


	//{{AFX_DATA_INIT(CDlgSelectObject)
	m_csCreated = _T("");
	m_csDescript = _T("");
	m_csEdited = _T("");
	//}}AFX_DATA_INIT
}


void CDlgSelectObject::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgSelectObject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelectObject)
	DDX_Control(pDX, IDC_TREEFRAME, m_cTreeFrame);
	DDX_Text(pDX, IDC_CREATED, m_csCreated);
	DDX_Text(pDX, IDC_DESCRIPT, m_csDescript);
	DDX_Text(pDX, IDC_EDITED, m_csEdited);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelectObject, CDialog)
	//{{AFX_MSG_MAP(CDlgSelectObject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgSelectObject, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgSelectObject)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectObject message handlers

BOOL CDlgSelectObject::OnInitDialog() 
{
RECT rect;

	DBG_PRINT("[dlgSelect.Init] Begin");

	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	UpdateData( TRUE);
	m_cTreeFrame.GetWindowRect( &rect);
	ScreenToClient( &rect);
	::InflateRect(&rect, -2, -2);

	DBG_PRINT("[dlgSelect.Init] Create Tree");

	if ( m_cTree.Create( rect, this,  0x103))
		{
		DBG_PRINT("[dlgSelect.Init] Tree created");
		m_cTree.SetFilter( m_nSelect, m_nUOM);
		DBG_PRINT("[dlgSelect.Init] Rebuild Tree");
		m_cTree.RebuildTree( m_cRoot, 0);
		DBG_PRINT("[dlgSelect.Init] Tree built");
		}

	DBG_PRINT("[dlgSelect.Init] Tree done");

	{
	CString cstitle;
	CString cstype;
	UINT uitype;

		cstitle.LoadString( IDS_SELECTA);
		switch( m_nSelect)
			{
			case ntGenerator :
				uitype =IDS_RESSIGNAL;
				break;
			case ntDataSet	 :
				uitype =IDS_RESDATASET;
				break;
			case ntChart	 :
				uitype =IDS_RESCHART;
				break;
			case ntEnclosure :
				uitype =IDS_RESENCLOSURE;
				break;
			case ntNetwork	 :
				uitype =IDS_RESNETWORK;
				break;
			case ntRoom		 :
				uitype =IDS_RESROOM;
				break;
			case ntDriver	 :
				uitype =IDS_RESDRIVER;
				break;
			case ntFolder	 :
				uitype =IDS_RESFOLDER;
				break;
			case ntAny:
			default:
				uitype = 0;
				break;
			}

		if ( uitype)			// not an any
			{
			cstype.LoadString( uitype);
			SetWindowText( cstitle + " " + cstype);
			}
	}
	
	DBG_PRINT("[dlgSelect.Init] Preenable");
	{
	CWnd *pwnd = GetDlgItem( IDOK);
	if ( pwnd)
		pwnd->EnableWindow( FALSE);
	}
	DBG_PRINT("[dlgSelect.Init] Init complete");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

#if ALLOW_DBG
#include "Folder.h"
#endif

void	CDlgSelectObject::SetParms( CFolder *cRoot, DWORD dwID, NAMETYPES nSelect, UNITMSR nUom)
{
#if ALLOW_DBG
	CString csdbg;

		csdbg = "[dlgSelect.SelectObject]";

		csdbg += cRoot->GetName();
		csdbg += " : ";
		if ( cRoot && dwID)
			{
			CNamed *cnam = cRoot->GetItem( dwID);
			CString csname;
			if ( cnam)
				{
				csname = cnam->GetFullName();
				csdbg += csname;
				}
			}
		csdbg += " : ";
		switch( nSelect)
			{
			case ntAny :
				csdbg += "Type=Any";
				break;
			case ntGenerator :
				csdbg += "Type=Generator";
				break;
			case ntDataSet :
				csdbg += "Type=Dataset";
				break;
			case ntChart :
				csdbg += "Type=Chart";
				break;
			case ntEnclosure :
				csdbg += "Type=Enclosure";
				break;
			case ntNetwork :
				csdbg += "Type=Network";
				break;
			case ntRoom :
				csdbg += "Type=Room";
				break;
			case ntDriver :
				csdbg += "Type=Driver";
				break;
			case ntFolder :
				csdbg += "Type=Folder";
				break;
			default :
				break;
			}
		csdbg += " : ";
		if ( ntDataSet == nSelect)
			{
			switch( nUom)
				{
				case uomTime :
					csdbg += "uom=Time";
					break;
				case uomFreq :
					csdbg += "uom=Freq";
					break;
				case uomOhms :
					csdbg += "uom=Ohms";
					break;
				case uomAny :
					csdbg += "uom=Any";
					break;
				}
			}
		DBG_PRINT( csdbg);
#endif

	m_cRoot = cRoot;
	m_dwTargetID = dwID;
	m_nSelect = nSelect;
	m_nUOM = nUom;
}


void CDlgSelectObject::OnOK() 
{
CNamed *cname;

	cname = m_cTree.GetNextItem( NULL, TVGN_CARET);
	if ( (! cname) || ((m_nSelect != ntFolder) && (m_nSelect != ntAny) && (ntFolder == cname->GetType())) )
		return;

	m_dwSelected = cname->GetID();
			
	CDialog::OnOK();
}


LRESULT CDlgSelectObject::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{

	// TODO: Add your specialized code here and/or call the base class
	if ( m_cTree.GetSafeHwnd())
		{
		CNamed *cname;
		BOOL ballow = FALSE;

			cname = m_cTree.GetNextItem( NULL, TVGN_CARET);
			if ( cname)
				{
				if ( m_dwLastSel != cname->GetID())
					{
					time_t t;
					DBG_PRINT("[dlgSelect.WinProc] New Selection");
					m_dwLastSel = cname->GetID();

					m_csDescript = cname->GetDescription();
					t = cname->GetCreated();
					m_csCreated	 = ctime( &t);
					t = cname->GetLastEdit();
					m_csEdited = ctime( &t);

					ballow = (m_nSelect == ntAny) || cname->IsType( m_nSelect, m_nUOM);

					UpdateData( FALSE);
					}
				else ballow = m_bAllowOK;		// last one was just fine
				}
			if ( ballow != m_bAllowOK)
				{
				CWnd *pwnd = GetDlgItem( IDOK);
				if ( pwnd)
					pwnd->EnableWindow( ballow);
				m_bAllowOK = ballow;
				}
		}
	
	
	return CDialog::WindowProc(message, wParam, lParam);
}
