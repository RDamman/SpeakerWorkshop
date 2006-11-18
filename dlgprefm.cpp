// dlgprefm.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgprefm.h"

#include "mmwave.h"

#include "Utils.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

static int n_Sizes[9] = { 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144 };

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefMeasure property page

IMPLEMENT_DYNCREATE(CDlgPrefMeasure, CPropertyPage)

CDlgPrefMeasure::CDlgPrefMeasure() : CPropertyPage(CDlgPrefMeasure::IDD), m_cVolume()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgPrefMeasure)
	m_bEmphasis = FALSE;
	m_csRate = _T("");
	m_csSize = _T("");
	m_csShowFreq = _T("");
	m_bReverse = FALSE;
	m_nRepCount = 0;
	m_csMaxRate = _T("");
	//}}AFX_DATA_INIT

	m_nRepCount = 1;
	m_nRate = 0;
	m_nSize = 0;

}

CDlgPrefMeasure::~CDlgPrefMeasure()
{
}

void CDlgPrefMeasure::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgPrefMeasure::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cVolume.DDX_Value( pDX, m_fVolume);

	if ( ! pDX->m_bSaveAndValidate )
		{
		char csout[100];
		int nstart, nend;		// start and end freqs
		float foffset;			// delta
		CString csformat;

			nend = m_nRate / 2;
			foffset = (float )(m_nRate / (double )m_nSize);
			nstart = (int )foffset;

			csformat.LoadString( IDS_RANGESHOW);
			sprintf( csout, (LPCSTR )csformat, nstart, nend, foffset);
			m_csShowFreq = csout;

			sprintf( csout, "%d", m_nSize);
			m_csSize = csout;
			sprintf( csout, "%d", m_nRate);
			m_csRate = csout;

		}

	//{{AFX_DATA_MAP(CDlgPrefMeasure)
	DDX_Control(pDX, IDC_SPINCNT, m_cSpinCount);
	DDX_Control(pDX, IDC_SAMPLERATE, m_clRate);
	DDX_Control(pDX, IDC_SAMPLESIZE, m_clSize);
	DDX_Check(pDX, IDC_PREEMPHASIS, m_bEmphasis);
	DDX_Text(pDX, IDC_SHOWRATE, m_csRate);
	DDX_Text(pDX, IDC_SHOWSIZE, m_csSize);
	DDX_Text(pDX, IDC_SHOWFREQ, m_csShowFreq);
	DDX_Check(pDX, IDC_REVERSE, m_bReverse);
	DDX_Text(pDX, IDC_REPCOUNT, m_nRepCount);
	DDX_Text(pDX, IDC_STATMAXRATE, m_csMaxRate);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CDlgPrefMeasure, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgPrefMeasure)
	ON_WM_HSCROLL()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINVOLUME, OnDeltaposSpinvolume)
	ON_EN_CHANGE(IDC_VOLUME, OnChangeVolume)
	ON_BN_CLICKED(IDC_PREEMPHASIS, OnPreemphasis)
	ON_BN_CLICKED(IDC_REVERSE, OnReverse)
	ON_EN_CHANGE(IDC_REPCOUNT, OnChangeRepcount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgPrefMeasure, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgPrefMeasure)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefMeasure message handlers


BOOL CDlgPrefMeasure::OnInitDialog() 
{
int i;
const CDWordArray *parray = CMMWave::GetRateArray();

	m_cVolume.Subclass( this, IDC_VOLUME, IDC_SPINVOLUME);
	m_cVolume.SetLimits( 0.0f, 100.0f);

	CPropertyPage::OnInitDialog();
	
	UpdateData( TRUE);				// get slider control handles
	
	Initial();						// get initial values into the controls

	m_clRate.SetTicFreq( 1);

	m_clRate.SetRange(1,parray->GetSize());

	m_cSpinCount.SetRange( 1, 100);

	{
	const CDWordArray *parray = CMMWave::GetRateArray();
	int nmax = parray->GetAt( parray->GetSize()-1);
	CString cs;

		cs.Format( "%d", nmax);
		m_csMaxRate = cs;
	}


	for ( i=0; i<parray->GetSize(); i++)
		{
		if ( m_nRate == (int )parray->GetAt(i) )
			{
			m_clRate.SetPos(i+1);
			break;
			}
		}
	m_clSize.SetTicFreq( 1);
	m_clSize.SetRange(1,9);	// 1k,2,4,8,16,32,64,128,256

	for ( i=0; i<9; i++)
		if ( n_Sizes[i] == m_nSize)
			{
			m_clSize.SetPos(i+1);
			break;
			}

	SetModified( FALSE);
	UpdateData( FALSE);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPrefMeasure::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
int mrate, msize;

	mrate = m_nRate;
	msize = m_nSize;

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
 				case IDC_SAMPLERATE :
					UpdateData( TRUE);		// get any existing data...
					m_nRate = (int )(CMMWave::GetRateArray()->GetAt(nPos-1));
					UpdateData( FALSE);
					break;
				case IDC_SAMPLESIZE :
					UpdateData( TRUE);		// get any existing data...
					m_nSize = n_Sizes[nPos-1];
					UpdateData( FALSE);
					break;
				default :
					break;
				}

			break;

		default:
			break;

		}

	if ( (mrate != m_nRate) || (msize != m_nSize))
			SetModified( TRUE);

	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDlgPrefMeasure::OnDeltaposSpinvolume(NMHDR* pNMHDR, LRESULT* pResult) 
{
NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	m_cVolume.ProcessDelta( pNMUpDown->iDelta);		// that's it....

	SetModified( TRUE);

	*pResult = 0;
}

void CDlgPrefMeasure::Initial()
{
TESTMSR deftest;

	CAudtestApp::GetMeasures( &deftest);

	m_nRate = deftest.nSampleRate;
	m_nSize = deftest.nSampleSize;
	m_nRepCount = deftest.nNumberSamples;
	m_bEmphasis = deftest.bEmphasis;
	m_bReverse = deftest.bReverseChannel;
	m_fVolume = deftest.fPlayVolume;
	m_nRepCount = deftest.nNumberSamples;

}

void CDlgPrefMeasure::Apply()
{
TESTMSR deftest;

	UpdateData( TRUE);

	CAudtestApp::GetMeasures( &deftest);

	deftest.nSampleRate =     m_nRate;
	deftest.nSampleSize =     m_nSize;
	deftest.nNumberSamples =  m_nRepCount;
	deftest.bEmphasis =  	  m_bEmphasis;
	deftest.bReverseChannel = m_bReverse;
	deftest.fPlayVolume =	  m_fVolume;

	CAudtestApp::SetMeasures( &deftest);

}

BOOL CDlgPrefMeasure::OnApply() 
{

	if ( ! VerboseUpdateData( TRUE))
		return 0;

	Apply();
	SetModified( FALSE);
	
	return CPropertyPage::OnApply();
}

void CDlgPrefMeasure::OnChangeVolume() 
{
	SetModified( TRUE);
}

void CDlgPrefMeasure::OnPreemphasis() 
{
	SetModified( TRUE);
	
}

void CDlgPrefMeasure::OnReverse() 
{
	SetModified( TRUE);

}


void CDlgPrefMeasure::OnChangeRepcount() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	SetModified( TRUE);
}
