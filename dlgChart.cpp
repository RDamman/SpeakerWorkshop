// dlgchart.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgchart.h"
#include "dataset.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgChart

IMPLEMENT_DYNAMIC(CDlgChart, CPropertySheet)

CDlgChart::CDlgChart(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(IDS_CHART, pParentWnd, iSelectPage), m_cGridX(), m_cGridY(), m_cGridY2()
{
	EnableAutomation();

	AddPage( &m_cGeneral);
	AddPage( &m_cData);
	AddPage( &m_cGridX);
	AddPage( &m_cGridY);
	AddPage( &m_cGridY2);

}

CDlgChart::~CDlgChart()
{
}

void CDlgChart::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgChart::UseChart(CNamed *pcRoot, CSubChart *pcChart, CObject *cFirst)
{
	m_cData.UseData( pcRoot, pcChart, &pcChart->m_cDataLines, cFirst);	// the cdatachart object copies this

			// now the do the rest of the init
	m_cGridX.UseGrid( &pcChart->m_cGridX);
	m_cGridY.UseGrid( &pcChart->m_cGridY);
	m_cGridY2.UseGrid( &pcChart->m_cGridY2);
	m_cGeneral.UseGeneral( pcChart);
}


void CDlgChart::SetChart( CSubChart *pcChart)
{
CDataSet *pold, *pnew;

	m_cGridX.SetGrid( &pcChart->m_cGridX);
	m_cGridY.SetGrid( &pcChart->m_cGridY);
	m_cGridY2.SetGrid( &pcChart->m_cGridY2);
	m_cGeneral.SetGeneral( pcChart);

	pnew = m_cData.GetDataset(0);
	if ( pnew)			// we mus thave data to worry about this
		{
		pold = pcChart->GetDatasetAt(0);
		if ( (!pold) || (pold->GetUOM() != pnew->GetUOM()) )		// change in context
			{
			pcChart->CreateDefault( pcChart->GetTitle(), pnew->GetUOM());
			}
		}
	m_cData.SetData( pcChart, &pcChart->m_cDataLines);
		
}



BEGIN_MESSAGE_MAP(CDlgChart, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgChart)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgChart, CPropertySheet)
	//{{AFX_DISPATCH_MAP(CDlgChart)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgChart message handlers
