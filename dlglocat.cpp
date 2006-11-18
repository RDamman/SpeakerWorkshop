// dlglocat.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgLocat.h"

//#include "Named.h"
#include "Chart.h"
#include "Dataset.h"

#include "TrueDialogBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLocations dialog


CDlgLocations::CDlgLocations(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLocations::IDD, pParent), m_cfList(), m_cfLast(), m_cfDelta(), m_cfDelta2(), m_cszNames()

{
BOOL brslt;

	//{{AFX_DATA_INIT(CDlgLocations)
	//}}AFX_DATA_INIT

	brslt = Create( CDlgLocations::IDD, pParent);		// modeless, we're going

	m_cfList.SetSize(0, 50);
	m_cfLast.SetSize(0, 50);
	m_cfDelta.SetSize(0, 50);
	m_cfDelta2.SetSize(0, 50);
	m_cszNames.SetSize(0, 50);

	SetLocator( NULL);
}


void CDlgLocations::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgLocations::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLocations)
	DDX_Control(pDX, IDC_LOCLIST4, m_clListDelta2);
	DDX_Control(pDX, IDC_LOCLIST1, m_clListFirst);
	DDX_Control(pDX, IDC_LOCLIST3, m_clListDelta);
	DDX_Control(pDX, IDC_LOCLIST2, m_clListLast);
	DDX_Control(pDX, IDC_LOCLIST, m_clList);
	DDX_Text(pDX, IDC_FREQ, m_csFreqFirst);
	//}}AFX_DATA_MAP

	if (! pDX->m_bSaveAndValidate)			// are we moving data to the dbox?
		{
		int i;
		char cnum[40];

			m_clList.ResetContent();
			for ( i=0; i<m_cszNames.GetSize(); i++)
				m_clList.AddString( m_cszNames.GetAt(i));

			m_clListFirst.ResetContent();
			for ( i=0; i<m_cfList.GetSize(); i++)
				{
				sprintf( cnum, "%6.2f", m_cfList.GetAt(i));
				m_clListFirst.AddString( cnum);
				}
			m_clListLast.ResetContent();
			for ( i=0; i<m_cfLast.GetSize(); i++)
				{
				sprintf( cnum, "%6.2f", m_cfLast.GetAt(i));
				m_clListLast.AddString( cnum);
				}
			m_clListDelta.ResetContent();
			for ( i=0; i<m_cfDelta.GetSize(); i++)
				{
				sprintf( cnum, "%6.2f", m_cfDelta.GetAt(i));
				m_clListDelta.AddString( cnum);
				}
			m_clListDelta2.ResetContent();
			for ( i=0; i<m_cfDelta2.GetSize(); i++)
				{
				sprintf( cnum, "%6.2f", m_cfDelta2.GetAt(i));
				m_clListDelta2.AddString( cnum);
				}
		}
}


BEGIN_MESSAGE_MAP(CDlgLocations, CDialog)
	//{{AFX_MSG_MAP(CDlgLocations)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgLocations, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgLocations)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLocations message handlers

void CDlgLocations::PostNcDestroy() 
{
	CDialog::PostNcDestroy();

	delete this;
}

void CDlgLocations::OnClose() 
{
    // This message is sent to the parent so it can enable the menu item.
    // The dialog can also do it directly but keeping the OOP methodology in 
    // mind, we will let the parent do this task.

				// it's a close request
	ShowWindow( SW_HIDE);

}

static void size_wnd( CDialog *pdlg, UINT nID, int nSize)
{
CRect cr;
CWnd *cwnd = pdlg->GetDlgItem( IDC_FREQ);	// get a 1 line high control
int nheight;

	if ( cwnd && cwnd->GetSafeHwnd())
		{
		cwnd->GetWindowRect( &cr);
		nheight = cr.Height() * nSize + 6;
		cwnd = pdlg->GetDlgItem( nID);
		cwnd->GetWindowRect( &cr);
		cwnd->SetWindowPos( NULL, 0,0, cr.Width(), nheight, SWP_NOZORDER | SWP_NOMOVE);
		}
}


static void size_mainwnd( CDialog *pdlg)
{
CRect cr, crnew;
CWnd *cwnd = pdlg->GetDlgItem( IDC_LOCLIST);	// get a bottom control

	if ( cwnd && cwnd->GetSafeHwnd())
		{
		cwnd->GetWindowRect( &cr);
		pdlg->GetWindowRect( &crnew);
		crnew.bottom = cr.bottom + 3;
		pdlg->SetWindowPos( NULL, 0,0, crnew.Width(), crnew.Height(), SWP_NOZORDER | SWP_NOMOVE);
		}
}




void CDlgLocations::UpdateLocator( CObject *cChart, CPoint& cPt)
{
int i;
float fx, fmarklow, fmarkhigh;
CFloatArray *cf = & m_cfList;
CFloatArray *cfphase = & m_cfLast;
CFloatArray *cfdelta = &m_cfDelta;
CFloatArray *cfdelta2 = &m_cfDelta2;
CSubChart *cc = (CSubChart *)cChart;
CStringArray *cs = & m_cszNames;
BOOL bstring;
int nlastsize = m_cszNames.GetSize();
CDataSet *cn;
BOOL bshowdiff;
BOOL bhasphase = FALSE;
int ndatasets = cc->GetDataCount();



	if ( (! IsWindowVisible()) || !cc)
		return ;

				// now clear the phase and value numbers
	cfphase->RemoveAll();
	cf->RemoveAll();
	cfdelta->RemoveAll();
	cfdelta2->RemoveAll();
				// bstring: redraw the strings if new ones
	bstring = ( (cChart != GetLocator()) || (nlastsize != cc->GetDataCount()) );	// set strings if new owner
	if ( bstring)
		{
		cs->RemoveAll();
		SetLocator( cChart);
		}

				// calculate the new values
	cn = cc->GetDatasetAt(0);
	if ( ! cn)		// there is no dataset yet attached to this chart
		return;

	fx = cc->ConvertXLocation( cPt.x);

				// get the marker frequency
	{			// set visibility to turn off display and mouse-hits
	UNITMSR uom = cn->GetUOM();		// since marker is a function of UOM
	int nwhich = (uomTime == uom) ? 0 : (uomFreq == uom) ? 1 : 2;
	TESTMARK tm;

		tm = *CAudtestApp::GetMarker( nwhich);
		fmarklow = tm.fStart;
		fmarkhigh = tm.fEnd;
//		bshowdiff = tm.bUse;
		bshowdiff = TRUE;			// always show difference for markers even if invisible
	}

					// for each dataset, get value and phase and delta
	for ( i=0; i<ndatasets; i++)
		{
		cn = cc->GetDatasetAt(i);
		if (cn && cn->HasPhase())
			{
			bhasphase = TRUE;
			break;
			}
		}

	for ( i=0; i<ndatasets; i++)
		{
		float f;
		cn = cc->GetDatasetAt(i);
		if ( ! cn)
			continue;			// invalid entry here
		f= cn->DataValueAt( fx); cf->Add( f);
		if ( bshowdiff)
			{
			cfdelta->Add( f - cn->DataValueAt( fmarklow));	// now delta == amp diff with marker low
			cfdelta2->Add( f - cn->DataValueAt( fmarkhigh));	// now delta == amp diff with marker low
			}
		if ( bhasphase)
			{
			f = cn->PhaseValueAt( fx); 
			cfphase->Add( f);
			}
		if ( bstring)
			cs->Add( cn->GetName());
		}

	if ( bstring && 1 < cs->GetSize())		// strings have changed
		{									// check for common suffix
		CString cbegin = cs->GetAt(0);
		int nidx = cbegin.Find('.');
		if ( nidx > 0)
			{
					// get prefix
			cbegin = cbegin.Left(nidx);
			for ( i=0; i<cs->GetSize(); i++)
				if ( cs->GetAt(i).Find(cbegin))
					break;
			if ( i == cs->GetSize())		// all have same prefix
				{
				for ( i=0; i<cs->GetSize(); i++)
					cs->SetAt( i, cs->GetAt(i).Right( cs->GetAt(i).GetLength() - nidx));
				}
			}
		}

	char ss[30];
	sprintf( ss, "%6.2f", fx);
	m_csFreqFirst = ss;

	UpdateData( FALSE);

				// now resize the window if necessary
	if ( cs->GetSize() && (nlastsize != cs->GetSize()))
		{
		int nsize = cs->GetSize();
		size_wnd( this, IDC_LOCLIST, nsize);
		size_wnd( this, IDC_LOCLIST1, nsize);
		size_wnd( this, IDC_LOCLIST2, nsize);
		size_wnd( this, IDC_LOCLIST3, nsize);
		size_wnd( this, IDC_LOCLIST4, nsize);
		size_mainwnd( this);
		CTrueDialogBar *pp = (CTrueDialogBar *)GetParent();	// !! we know we are owned by a dialog bar
		pp->RecalcSize();			// recalc its size
		if (pp->IsFloating())
			{
			// do something here to resize the world
			}
		}

}


