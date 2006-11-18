// audtevw.cpp : implementation of the CAudEnclView class
//

#include "stdafx.h"
#include "audtest.h"

#include "audtedoc.h"
#include "vwEncl.h"

#include "xform.h"
#include "xformall.h"


#include "generat.h"
#include "dataset.h"
#include "Enclosur.h"
#include "driver.h"

#include "DlgCalcMerge.h"

#include "dlgrenam.h"

#include "zFormEdt.h"
#include "dlgCBox.h"		// all the calc box stuff

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudEnclView

IMPLEMENT_DYNCREATE(CAudEnclView, CAudchView)

BEGIN_MESSAGE_MAP(CAudEnclView, CAudchView)
	//{{AFX_MSG_MAP(CAudEnclView)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(ID_CALC_SEALED, OnCalcSealed)
	ON_COMMAND(ID_CALC_VENTED, OnCalcVented)
	ON_COMMAND(ID_CALC_BANDCHAMBER, OnCalcBandchamber)
	ON_COMMAND(ID_CALC_BANDAIR, OnCalcBandair)
	ON_COMMAND(ID_CALCULATE_FREQUENCYRESPONSE, OnCalculateFrequencyresponse)
	ON_COMMAND(ID_CALCULATE_IMPEDANCE, OnCalculateImpedance)
	ON_COMMAND(ID_CALCULATE_GROUPDELAY, OnCalculateGroupdelay)
	ON_COMMAND(ID_CALCULATE_CONEEXCURSION, OnCalculateConeexcursion)
	ON_COMMAND(ID_CALCULATE_TRANSIENTRESPONSE, OnCalculateTransientresponse)
	ON_UPDATE_COMMAND_UI(ID_CALCULATE_CONEEXCURSION, OnUpdateCalculateConeexcursion)
	ON_UPDATE_COMMAND_UI(ID_CALCULATE_GROUPDELAY, OnUpdateCalculateGroupdelay)
	ON_UPDATE_COMMAND_UI(ID_CALCULATE_IMPEDANCE, OnUpdateCalculateImpedance)
	ON_UPDATE_COMMAND_UI(ID_CALCULATE_TRANSIENTRESPONSE, OnUpdateCalculateTransientresponse)
	ON_UPDATE_COMMAND_UI(ID_CALCULATE_FREQUENCYRESPONSE, OnUpdateCalculateFrequencyresponse)
	ON_COMMAND(ID_CALC_MERGE, OnCalcMerge)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CAudchView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CAudchView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudEnclView construction/destruction

CAudEnclView::CAudEnclView()
{
	// TODO: add construction code here

}

CAudEnclView::~CAudEnclView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CAudEnclView drawing

static enum	formVar
{
	frm_Name,
	frm_Descript,
	frm_Driver,
	frm_Volume,
	frm_QLeak,
	frm_QDamp,
	frm_QPort,
	frm_UsePort,
	frm_PIsCircle,
	frm_PLength,
	frm_PRadius,
	frm_PHeight,
	frm_PWidth,
	frm_UseChamber,
	frm_Drivers,
	frm_Parallel,
	frm_DriverRes,
	frm_AVolume,
	frm_APLength,
	frm_APRadius,
	frm_APHeight,
	frm_APWidth
};

static sFormField	form_Entries[] =
{ 
	{10,  0,   IDS_ENC_NAME		,IDS_FRM_NULL} ,
	{10,  1,   IDS_ENC_DESCRIPT	,IDS_FRM_NULL} ,
	{ 1,  2,   IDS_ENC_DRIVER	,IDS_FRM_NULL} ,
	{ 1,  5,   IDS_ENC_VOL		,IDS_FRM_LITER} ,
	{ 1,  6,   IDS_ENC_QLEAK	,IDS_FRM_NULL} ,
	{ 1,  7,   IDS_ENC_QDAMP	,IDS_FRM_NULL} ,
	{ 1,  8,   IDS_ENC_QPORT	,IDS_FRM_NULL} ,
	{ 40,  3,   IDS_ENC_USEPORT	,IDS_FRM_NULL} ,
	{ 40,  4,   IDS_ENC_ISCIRCULAR	,IDS_FRM_NULL} ,
	{ 40,  5,   IDS_ENC_PLENGTH	,IDS_FRM_CM} ,
	{ 40,  6,  IDS_ENC_PRADIUS	,IDS_FRM_CM} ,
	{ 40,  6,	IDS_ENC_PHEIGHT	,IDS_FRM_CM} ,
	{ 40,  7,	IDS_ENC_PWIDTH		,IDS_FRM_CM} ,
	{ 1,  3,	IDS_ENC_USECHAMBER	,IDS_FRM_NULL} ,
	{ 40,   8,	IDS_ENC_DRIVERS	,IDS_FRM_NULL} ,
	{ 40,  9,	IDS_ENC_PARALLEL,IDS_FRM_NULL} ,
	{ 1,  9,	IDS_ENC_DRVRES	,IDS_FRM_OHMS},
				// american units
	{ 1,  5,   IDS_ENC_VOL		,IDS_FRM_CUFT} ,
	{ 40,  5,   IDS_ENC_PLENGTH	,IDS_FRM_INCH} ,
	{ 40,  6,  IDS_ENC_PRADIUS	,IDS_FRM_INCH} ,
	{ 40,  6,	IDS_ENC_PHEIGHT	,IDS_FRM_INCH} ,
	{ 40,  7,	IDS_ENC_PWIDTH		,IDS_FRM_INCH} ,

};

void CAudEnclView::OnDraw(CDC* pDC)
{
CHAMBER	chdata;
CEnclosure *cenc = (CEnclosure *)GetTargetObject();
CFont *cfont;
CFont *cfold;

	cfont = CAudtestApp::GetAppFont( ftStatus).GetCurrentFont( pDC);
	cfold = pDC->SelectObject( cfont);

	SetFloatFormat( 8, 3);
	SetIntFormat( 5);

	{
	int i;
	int iwidth;
	CSize csmax(0,0);

		for ( i=0; i< frm_DriverRes; i++)
		{
			iwidth = FormExtent( pDC, &form_Entries[i]);
			if ( csmax.cx < iwidth)
				csmax.cx = iwidth;
			if ( csmax.cy < form_Entries[i].iY)
				csmax.cy = form_Entries[i].iY;
		}

		m_iRowWidth = csmax.cx + 7 * CharWidth( pDC);			// add in space for 10 chars
		m_iMaxHeight = csmax.cy * CharHeight( pDC);

		for ( i=0; i< frm_PWidth; i++)
		{
			if ( form_Entries[i].iX > 20)		// it's column 2
			{
				form_Entries[i].iX = 15 + m_iRowWidth / CharWidth( pDC);
			}
		}
	}


				// format the variables for on-screen display


	{
	CString stryes;
	CString strno;

		stryes.LoadString( IDS_YES);
		strno.LoadString( IDS_NO);

		chdata = *cenc->GetChamber( 1);

		DrawVariable( pDC, 	&form_Entries[ frm_Name], cenc->GetName());
		DrawVariable( pDC, 	&form_Entries[ frm_Descript], cenc->GetDescription());
		if ( chdata.dwDriver)
		{
		CNamed *pname = cenc->FindByID( chdata.dwDriver);
			if ( pname)
				DrawVariable( pDC, &form_Entries[ frm_Driver], pname->GetName());
		}
		else
		{
			DrawVariable( pDC, &form_Entries[ frm_Driver], false);
		}

		DrawVariable( pDC, &form_Entries[ frm_DriverRes], chdata.fSeriesRes, m_iRowWidth);
		if ( CAudtestApp::GetIsMetric())
			DrawVariable( pDC, &form_Entries[ frm_Volume],  chdata.fVolume*1000.0f, m_iRowWidth);
		else
		{
		float fo;
			fo = CzFormatEdit::ConvertBaseToBase( chdata.fVolume, mtCuFoot, mtCuMeter);
			DrawVariable( pDC, &form_Entries[ frm_AVolume],  fo, m_iRowWidth);

		}
		DrawVariable( pDC, &form_Entries[ frm_QLeak],  chdata.fQLeak, m_iRowWidth);
		DrawVariable( pDC, &form_Entries[ frm_QDamp], chdata.fQDamp, m_iRowWidth);
		DrawVariable( pDC, &form_Entries[ frm_QPort], chdata.fQPort, m_iRowWidth);
		DrawVariable( pDC, &form_Entries[ frm_UsePort], chdata.bUsePort);
		if ( chdata.bUsePort)
		{
			DrawVariable( pDC, &form_Entries[ frm_PIsCircle], chdata.bPIsCircle);
			if ( CAudtestApp::GetIsMetric())
			{
				if ( chdata.bPIsCircle)
				{
					DrawVariable( pDC, &form_Entries[ frm_PRadius], chdata.fPRadius * 100.0f, m_iRowWidth);	// m**2 to cm**2
				}
				else
				{
					DrawVariable( pDC, &form_Entries[ frm_PHeight], chdata.fPHeight * 100.0f, m_iRowWidth);
					DrawVariable( pDC, &form_Entries[ frm_PWidth], chdata.fPWidth * 100.0f, m_iRowWidth);
				}
				DrawVariable( pDC, &form_Entries[ frm_PLength], chdata.fPLength * 100.0f, m_iRowWidth);
			}
			else
			{
			float fo;
				if ( chdata.bPIsCircle)
				{
					fo = CzFormatEdit::ConvertBaseToBase( chdata.fPRadius, mtInch, mtMeter);
					DrawVariable( pDC, &form_Entries[ frm_APRadius], fo, m_iRowWidth);	// m**2 to cm**2
				}
				else
				{
					fo = CzFormatEdit::ConvertBaseToBase( chdata.fPHeight, mtInch, mtMeter);
					DrawVariable( pDC, &form_Entries[ frm_APHeight], fo, m_iRowWidth);
					fo = CzFormatEdit::ConvertBaseToBase( chdata.fPWidth, mtInch, mtMeter);
					DrawVariable( pDC, &form_Entries[ frm_APWidth], fo, m_iRowWidth);
				}
				fo = CzFormatEdit::ConvertBaseToBase( chdata.fPLength, mtInch, mtMeter);
				DrawVariable( pDC, &form_Entries[ frm_APLength], fo, m_iRowWidth);
			}
		}
		DrawVariable( pDC, &form_Entries[ frm_Drivers], (int )chdata.wDrivers, m_iRowWidth);
		if ( chdata.wDrivers > 1)
		{
			DrawVariable( pDC, &form_Entries[ frm_Parallel], chdata.bParallel);
		}

		chdata = *cenc->GetChamber( 2);
		DrawVariable( pDC, &form_Entries[ frm_UseChamber], chdata.bUseChamber);
	}

#if 0
	if ( ! GetViewChart())						// does this view have a chart???
	{
		CString csi;
		csi.LoadString( IDERR_DRVCHART);
		pDC->TextOut( 10, 10, csi);
	}
#endif

	{
	RECT rccl;

		::SetRect( &rccl, CharWidth( pDC) * 4, m_iMaxHeight + CharHeight( pDC) * 2, 
						  CharWidth( pDC) * 4, CharHeight( pDC) * 2);		// set width in %
		SetSubView( &rccl);
	}

	pDC->SelectObject( cfold);		// reset the font

	CAudchView::OnDraw( pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CAudEnclView printing

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CAudEnclView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CAudEnclView diagnostics

#ifdef _DEBUG
void CAudEnclView::AssertValid() const
{
	CAudchView::AssertValid();
}

void CAudEnclView::Dump(CDumpContext& dc) const
{
	CAudchView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAudEnclView message handlers

void CAudEnclView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
CEnclosure *cenc = (CEnclosure *)GetTargetObject();
DWORD dwh = (DWORD )lHint;

	if ( cenc)		// we have a target, and we have changed a single object
		{
		if( (!dwh) || dwh == cenc->GetID() || dwh == cenc->GetDriver())	// it's ours
			{
			SyncDataSets();
			}
		}

	CAudchView::OnUpdate(pSender, lHint, pHint);
}


void CAudEnclView::calc_Dialog( CDialog *cWho) 
{
int nout;
CNamed *cname;
CAudtestDoc* pDoc = GetDocument();
CDlgCalcBase *cme = (CDlgCalcBase *)cWho;


	cname = pDoc->GetByID( GetTarget());
	if ( ! cname)
		return;

	cme->UseObject( (CFolder *)cname->GetRootObject(), cname);			// use the document settings
	nout = cme->DoModal();

	if ( IDOK == nout)
		{
		CNamed *cnew = cname->Duplicate();
		cme->SetObject((CFolder *)cname->GetRootObject(), cnew);
		}

	
	
}

void CAudEnclView::OnCalcSealed() 
{
CDlgCalcSealed cdlg;

	calc_Dialog( &cdlg);
}

void CAudEnclView::OnCalcVented() 
{
CDlgCalcVented cdlg;

	calc_Dialog( &cdlg);
}

void CAudEnclView::OnCalcBandchamber() 
{
CDlgCalcBandChamber cdlg;

	calc_Dialog( &cdlg);
}

void CAudEnclView::OnCalcBandair() 
{
CDlgCalcBandAir cdlg;

	calc_Dialog( &cdlg);
	
}

void CAudEnclView::OnCalculateFrequencyresponse() 
{				// flip polarity of this flag
ENCLINFO enclose;

	CAudtestApp::GetEnclosureInfo( enclose);
	enclose.bFreqResponse = ! enclose.bFreqResponse;
	CAudtestApp::SetEnclosureInfo( enclose);
	
}

void CAudEnclView::OnCalculateImpedance() 
{				// flip polarity of this flag
ENCLINFO enclose;

	CAudtestApp::GetEnclosureInfo( enclose);
	enclose.bImpedance = ! enclose.bImpedance;
	CAudtestApp::SetEnclosureInfo( enclose);
	
}

void CAudEnclView::OnCalculateGroupdelay() 
{				// flip polarity of this flag
ENCLINFO enclose;

	CAudtestApp::GetEnclosureInfo( enclose);
	enclose.bGroupDelay = ! enclose.bGroupDelay;
	CAudtestApp::SetEnclosureInfo( enclose);
	
}

void CAudEnclView::OnCalculateConeexcursion() 
{				// flip polarity of this flag
ENCLINFO enclose;

	CAudtestApp::GetEnclosureInfo( enclose);
	enclose.bConeExcursion = ! enclose.bConeExcursion;
	CAudtestApp::SetEnclosureInfo( enclose);
}

void CAudEnclView::OnCalculateTransientresponse() 
{				// flip polarity of this flag
ENCLINFO enclose;

	CAudtestApp::GetEnclosureInfo( enclose);
	enclose.bTransient = ! enclose.bTransient;
	CAudtestApp::SetEnclosureInfo( enclose);
	
}

void CAudEnclView::OnUpdateCalculateConeexcursion(CCmdUI* pCmdUI) 
{
ENCLINFO enclose;

	CAudtestApp::GetEnclosureInfo( enclose);
	pCmdUI->SetCheck( enclose.bConeExcursion);
	
}

void CAudEnclView::OnUpdateCalculateGroupdelay(CCmdUI* pCmdUI) 
{
ENCLINFO enclose;

	CAudtestApp::GetEnclosureInfo( enclose);
	pCmdUI->SetCheck( enclose.bGroupDelay);
	
	
}

void CAudEnclView::OnUpdateCalculateImpedance(CCmdUI* pCmdUI) 
{
ENCLINFO enclose;

	CAudtestApp::GetEnclosureInfo( enclose);
	pCmdUI->SetCheck( enclose.bImpedance);
	
	
}

void CAudEnclView::OnUpdateCalculateTransientresponse(CCmdUI* pCmdUI) 
{
ENCLINFO enclose;

	CAudtestApp::GetEnclosureInfo( enclose);
	pCmdUI->SetCheck( enclose.bTransient);
	
	
}

void CAudEnclView::OnUpdateCalculateFrequencyresponse(CCmdUI* pCmdUI) 
{
ENCLINFO enclose;

	CAudtestApp::GetEnclosureInfo( enclose);
	pCmdUI->SetCheck( enclose.bFreqResponse);
	
	
}

// define this to cause an entry in the command table, so base class gets called
void CAudEnclView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CAudchView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CAudEnclView::OnCalcMerge() 
{
CEnclosure *cdSource = (CEnclosure *)GetTargetObject();
CDlgCalcMerge cdlg;
UINT uout;
DWORD dwdriver;
CDriver *pdrive;

				// fill the function with defaults for this dataset
	dwdriver = cdSource->GetDriver();			// so name can be filled in, and uom found

	if ( ! dwdriver)
	{
		AfxMessageBox( IDERR_NODRIVER, MB_OK);
		return;
	}

	cdlg.m_pRoot = (CFolder *)cdSource->GetRootObject();

	pdrive = (CDriver *)cdlg.m_pRoot->FindByID( dwdriver);	// so name can be filled in, and uom found

	{			// calculate port area
	CHAMBER	*pcham = cdSource->GetChamber();

		if ( pcham->bPIsCircle)
			cdlg.m_fPortArea = (float )(pcham->fPRadius * pcham->fPRadius * ONEPI);
		else
			cdlg.m_fPortArea = pcham->fPHeight * pcham->fPWidth;

	}

	{			// get piston area
	const DRIVEPARM *pparm = pdrive->GetDriverParameters();

		cdlg.m_fPistonArea = pparm->fPistonArea;
	}

	{		// get driver nearfield response
	const DRIVEPARM *pparm = pdrive->GetDriverParameters();

		cdlg.m_dwDriver = pparm->dwNearField;		// so name can be filled in, and uom found
		cdlg.m_dwPort = pparm->dwPort;				// port response
	}

	uout = cdlg.DoModal();

	if ( IDOK == uout)
		{
		CXformMergePort *cxfl = new CXformMergePort ( cdSource );
				// set the parameters for the merge
			cxfl->SetParameters( cdlg.m_dwDriver, cdlg.m_dwPort, cdlg.m_fPistonArea, cdlg.m_fPortArea);
				// do the merge
			if ( cxfl->QueueAndDo())						// do the fft
				delete cxfl;			// we failed this
		}

}
