// dlgchdat.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "dlgchdat.h"

#include "dlgSelec.h"
#include "dataset.h"

#include "utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgChData property page

IMPLEMENT_DYNCREATE(CDlgChData, CPropertyPage)

CDlgChData::CDlgChData() : CPropertyPage(CDlgChData::IDD), m_cDatalines()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgChData)
	m_bShowPhase = FALSE;
	m_bShowData = FALSE;
	m_nColor = -1;
	m_nColor2 = -1;
	m_nLineStyle = -1;
	m_nLineStyle2 = -1;
	m_nLineWeight = -1;
	m_nLineWeight2 = -1;
	//}}AFX_DATA_INIT
	m_nPrior = -1;
	m_cDatalines.SetSize(0, 10);
	m_cFirst = NULL;			// the default is no first choice
}

CDlgChData::~CDlgChData()
{

	::KillArray( &m_cDatalines);

}

void CDlgChData::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgChData::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChData)
	DDX_Control(pDX, IDC_DATALIST, m_clDataList);
	DDX_Check(pDX, IDC_SHOWPHASE, m_bShowPhase);
	DDX_Check(pDX, IDC_SHOWDATA, m_bShowData);
	DDX_CBIndex(pDX, IDC_COLOR, m_nColor);
	DDX_CBIndex(pDX, IDC_COLOR2, m_nColor2);
	DDX_CBIndex(pDX, IDC_LINESTYLE, m_nLineStyle);
	DDX_CBIndex(pDX, IDC_LINESTYLE2, m_nLineStyle2);
	DDX_CBIndex(pDX, IDC_LINEWEIGHT, m_nLineWeight);
	DDX_CBIndex(pDX, IDC_LINEWEIGHT2, m_nLineWeight2);
	//}}AFX_DATA_MAP

	if ( pDX->m_bSaveAndValidate)
		{
		if ( m_nPrior >= 0)			// we have a prior
			{
			CDataLine *pcdl;
				pcdl = (CDataLine *) (m_cDatalines.GetAt(m_nPrior) );
				WriteDataLine( pcdl);
			}
		}
}


BEGIN_MESSAGE_MAP(CDlgChData, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgChData)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_LBN_SELCHANGE(IDC_DATALIST, OnSelchangeDatalist)
	ON_BN_CLICKED(IDC_ADDDATA, OnAdddata)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgChData, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgChData)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChData message handlers


void CDlgChData::UseData( CNamed *cRoot, CNamed *cChart, CObArray *pcGen, CObject *cFirst)
{
CDataLine *cd;
int i;
CDataLine *cfirst;

	for ( i=0; i<pcGen->GetSize(); i++)
		{
		cd = new CDataLine( cChart);
		cfirst = (CDataLine *)pcGen->GetAt(i);
		*cd = *cfirst;
		if ( cfirst == cFirst)			// we were passed someone here
			m_cFirst = cd;				// match to our guy
		m_cDatalines.Add( cd);
		}
	m_cRoot = (CFolder *)cRoot;

}

CDataSet *CDlgChData::GetDataset( int nWhich)
{
CDataLine *cdl;
int nsize = m_cDatalines.GetSize();

	if ( nsize <= nWhich)
		return NULL;

	cdl = (CDataLine *)m_cDatalines.GetAt( nWhich);
	DWORD dwi = cdl->GetDataID();
	CNamed *cna = m_cRoot->GetItem( dwi, TRUE);	// look through all folders
	return (CDataSet *)cna;

}


void CDlgChData::SetData(  CSubChart *cChart, CObArray *pcData)
{
int i;
CDataLine *cdl;

	::KillArray( pcData);

			// get the last set of data from the dbox
	for ( i=0; i<m_cDatalines.GetSize(); i++)
		{
		cdl = (CDataLine *)m_cDatalines.GetAt(i);
		cdl->SetParent( cChart);
		pcData->Add( cdl);
		}

	m_cDatalines.RemoveAll();			// now get rid of them so we don't delete them
}


void CDlgChData::OnRemove() 
{
int i, j;
int nsel, nnew;

	// TODO: Add your control notification handler code here
	UpdateData( TRUE);			// get current settings

	nsel = m_clDataList.GetCurSel();
	if ( LB_ERR == nsel)
		return;

	m_clDataList.SetCurSel( -1);
	i = m_clDataList.GetItemData( nsel);	// so we can alphabetize, the index is stored here
	delete m_cDatalines.GetAt(i);			// toss the dataline
	m_cDatalines.RemoveAt(i);				// remove it from the list
	m_clDataList.DeleteString( nsel);		// remove the string from the listbox
	if ( m_cDatalines.GetSize() > nsel)		// reset the selection to a viable one near the old one
		m_clDataList.SetCurSel( nsel);
	else
		if ( m_cDatalines.GetSize())
			m_clDataList.SetCurSel( m_cDatalines.GetSize() - 1);

	for ( j=0; j<m_cDatalines.GetSize(); j++)
		{
		nnew = m_clDataList.GetItemData( j);
		if ( i < nnew)
			{
			nnew--;
			m_clDataList.SetItemData( j, nnew);
			}
		}

	i = m_clDataList.GetCurSel();		// get the current one
	if ( LB_ERR != i)					// read the current data
		{
		CDataLine *pcdl;
		m_nPrior = m_clDataList.GetItemData( i);
		pcdl = (CDataLine *)m_cDatalines.GetAt(m_nPrior);

		ReadDataLine( pcdl);
		}
	else
		m_nPrior = LB_ERR;

	UpdateData( FALSE);

}

BOOL CDlgChData::OnInitDialog() 
{
int ninitial = 0;

	CPropertyPage::OnInitDialog();
	
	UpdateData( TRUE);			// fill m_cldatalist for once and for all

	{
	int i, j;

		for ( i=0; i<m_cDatalines.GetSize(); i++)
			{
			CDataLine *cpdl = (CDataLine *)m_cDatalines.GetAt(i);
			DWORD dwi = cpdl->GetDataID();
			CNamed *cna = m_cRoot->GetItem( dwi, TRUE);	// look through all folders
			if ( cna)
				{
				j = m_clDataList.AddString( cna->GetFullName());
				if ( cpdl == m_cFirst)		// the one we were passed
					ninitial = i;			// start here
				m_clDataList.SetItemData(j, i);
				}
			}
					// convert that index into a datalist index
		for ( j=0; j<m_cDatalines.GetSize(); j++)
			if ( ninitial == (int )m_clDataList.GetItemData( j))
				{
				ninitial = j;
				break;
				}
	}
	

	m_cclrMajor.InitDialog((CComboBox *) GetDlgItem(IDC_COLOR));
	m_cclrMinor.InitDialog((CComboBox *) GetDlgItem(IDC_COLOR2));
	m_clsMajor.InitDialog((CComboBox *) GetDlgItem(IDC_LINESTYLE));
	m_clsMinor.InitDialog((CComboBox *) GetDlgItem(IDC_LINESTYLE2));
	m_clwMajor.InitDialog((CComboBox *) GetDlgItem(IDC_LINEWEIGHT));
	m_clwMinor.InitDialog((CComboBox *) GetDlgItem(IDC_LINEWEIGHT2));

	m_clDataList.SetCurSel( ninitial);
	OnSelchangeDatalist();			// we'll call this to init stuff

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// this transfer data from the dataline to the dbox entries
void CDlgChData::ReadDataLine( CDataLine *pSrc)
{
CObjColor *pz;

	pz = pSrc->GetColor();
	m_nColor = m_cclrMajor.ValueToIdx( pz->GetColor() );
	m_nLineStyle = m_clsMajor.ValueToIdx( pz->GetStyle() );
	m_nLineWeight = m_clwMajor.ValueToIdx( pz->GetWidth() );
		
	pz = pSrc->GetPhaseColor();
	m_nColor2 = m_cclrMinor.ValueToIdx( pz->GetColor() );
	m_nLineStyle2 = m_clsMinor.ValueToIdx( pz->GetStyle() );
	m_nLineWeight2 = m_clwMinor.ValueToIdx( pz->GetWidth() );

	m_bShowData  = pSrc->IsShowingAmp();
	m_bShowPhase = pSrc->IsShowingPhase();
}


// this transfer data from the dbox entries to the dataline
void CDlgChData::WriteDataLine( CDataLine *pSrc)
{
CObjColor *pz;

		pz = pSrc->GetColor();
		pz->SetColor( m_cclrMajor.IdxToValue(m_nColor));
		pz->SetStyle( m_clsMajor.IdxToValue(m_nLineStyle));
		pz->SetWidth( m_clwMajor.IdxToValue(m_nLineWeight));

		pz = pSrc->GetPhaseColor();
		pz->SetColor( m_cclrMinor.IdxToValue(m_nColor2));
		pz->SetStyle( m_clsMinor.IdxToValue(m_nLineStyle2));
		pz->SetWidth( m_clwMinor.IdxToValue(m_nLineWeight2));

		pSrc->ShowAmp(m_bShowData);
		pSrc->ShowPhase(m_bShowPhase);
}




void CDlgChData::OnSelchangeDatalist() 
{
int i;
CDataLine *pcdl;

	UpdateData( TRUE);		// get current showstuf and possibly change m_nPrior to -1

	i = m_clDataList.GetCurSel();
	if ( LB_ERR == i)
		{
		m_nPrior = i;
		return;
		}

	i = m_clDataList.GetItemData( i);	// so we can alphabetize, the index is stored here
	m_nPrior = i;
			
	pcdl = (CDataLine *) (m_cDatalines.GetAt(i) );

	ReadDataLine( pcdl);

	UpdateData( FALSE);		// set current showstuf

}

void CDlgChData::OnAdddata() 
{
CDlgSelectObject cdlg;
CDataLine *cdl;
UNITMSR nuom = uomAny;

	// TODO: Add your control notification handler code here
	UpdateData( TRUE);			// get current settings

	if ( m_cDatalines.GetSize())			// get the first uom and force it on the search
		{
		cdl = (CDataLine *)m_cDatalines.GetAt(0);
		CDataSet *cdata = (CDataSet *)m_cRoot->GetItem(cdl->GetDataID());
		if ( cdata)
			nuom = cdata->GetUOM();
		}

	cdlg.SetParms( m_cRoot, 0, ntDataSet, nuom);

	if ( IDOK == cdlg.DoModal())
		{
		int j;
		CDataLine *pnew = new CDataLine( NULL);		// we won't be drawing this (yet)
		CNamed *cna = m_cRoot->GetItem( cdlg.GetSelected());

			pnew->SetDataID( cna->GetID() );
			pnew->ShowPhase( FALSE);
			pnew->ShowAmp( TRUE);

			m_cDatalines.Add( pnew);
			j = m_clDataList.AddString( cna->GetFullName());
			m_clDataList.SetItemData(j, m_cDatalines.GetSize()-1);
			m_clDataList.SetCurSel( j);		// and go there...
		}
}

void CDlgChData::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default

	switch( nIDCtl)
		{
		case IDC_COLOR :
			m_cclrMajor.DrawItem( lpDrawItemStruct);
			break;
		case IDC_COLOR2 :
			m_cclrMinor.DrawItem( lpDrawItemStruct);
			break;
		case IDC_LINESTYLE :
			m_clsMajor.DrawItem( lpDrawItemStruct);
			break;
		case IDC_LINESTYLE2 :
			m_clsMinor.DrawItem( lpDrawItemStruct);
			break;
		case IDC_LINEWEIGHT :
			m_clwMajor.DrawItem( lpDrawItemStruct);
			break;
		case IDC_LINEWEIGHT2 :
			m_clwMinor.DrawItem( lpDrawItemStruct);
			break;
		default:
			break;
		}
	
	CPropertyPage::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CDlgChData::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	switch( nIDCtl)
		{
		case IDC_COLOR :
			m_cclrMajor.MeasureItem( lpMeasureItemStruct);
			break;
		case IDC_COLOR2 :
			m_cclrMinor.MeasureItem( lpMeasureItemStruct);
			break;
		case IDC_LINESTYLE :
			m_clsMajor.MeasureItem( lpMeasureItemStruct);
			break;
		case IDC_LINESTYLE2 :
			m_clsMinor.MeasureItem( lpMeasureItemStruct);
			break;
		case IDC_LINEWEIGHT :
			m_clwMajor.MeasureItem( lpMeasureItemStruct);
			break;
		case IDC_LINEWEIGHT2 :
			m_clwMinor.MeasureItem( lpMeasureItemStruct);
			break;
		default:
			break;
		}
	
	
	CPropertyPage::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

