// audtevw.cpp : implementation of the CAudDataView class
//

#include "stdafx.h"
#include "audtest.h"

#include "audtedoc.h"
#include "vwData.h"

#include "generat.h"
#include "dataset.h"

#include "xform.h"
#include "xformall.h"

#include "zFormEdt.h"

#include "dlgrenam.h"
#include "dlgXcImp.h"
#include "dlgXfFft.h"
#include "dlgXfIff.h"

#include "dlgXfGrp.h"		// calc group delay
#include "dlgXfFrq.h"
#include "dlgSplice.h"
#include "dlgXfWaterfall.h"

#include "complex.h"
#include "filter.h"

#include "OpItem.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudDataView

IMPLEMENT_DYNCREATE(CAudDataView, CAudchView)

BEGIN_MESSAGE_MAP(CAudDataView, CAudchView)
	//{{AFX_MSG_MAP(CAudDataView)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(ID_TRANSFORM_LIMIT, OnTransformLimit)
	ON_COMMAND(ID_TRANSFORM_SCALE, OnTransformScale)
	ON_COMMAND(ID_TRANSFORM_TRUNCATE, OnTransformTruncate)
	ON_COMMAND(ID_TRANSFORM_SMOOTH, OnTransformSmooth)
	ON_COMMAND(ID_TRANSFORM_DELAY, OnTransformDelay)
	ON_COMMAND(ID_CALCULATE_COMBINE, OnCalculateCombine)
	ON_COMMAND(ID_CALCULATE_IFFT, OnCalculateIfft)
	ON_COMMAND(ID_CALCULATE_FFT, OnCalculateFft)
	ON_COMMAND(ID_CALCULATE_IMPEDANCE, OnCalculateImpedance)
	ON_COMMAND(ID_TRANSFORM_CHART, OnEditChart)
	ON_COMMAND(ID_CALC_CORRELATE, OnCalculateCorrelation)
	ON_COMMAND(ID_TRANSFORM_INVERT, OnTransformInvert)
	ON_COMMAND(ID_TRANSFORM_FILTER, OnTransformFilter)
	ON_UPDATE_COMMAND_UI(ID_CALCULATE_FFT, OnUpdateCalculateFft)
	ON_UPDATE_COMMAND_UI(ID_CALCULATE_IFFT, OnUpdateCalculateIfft)
	ON_UPDATE_COMMAND_UI(ID_CALCULATE_IMPEDANCE, OnUpdateCalculateImpedance)
	ON_COMMAND(ID_CALCULATE_GROUPDELAY, OnCalculateGroupdelay)
	ON_UPDATE_COMMAND_UI(ID_CALCULATE_GROUPDELAY, OnUpdateCalculateGroupdelay)
	ON_COMMAND(ID_CALCULATE_FREQUENCY, OnCalculateFrequency)
	ON_COMMAND(ID_CALCULATE_SPLICE, OnCalculateSplice)
	ON_UPDATE_COMMAND_UI(ID_CALCULATE_SPLICE, OnUpdateCalculateSplice)
	ON_UPDATE_COMMAND_UI(ID_TRANSFORM_DELAY, OnUpdateTransformDelay)
	ON_COMMAND(ID_CALCULATE_WATERFALL, OnCalculateWaterfall)
	ON_UPDATE_COMMAND_UI(ID_CALCULATE_FREQUENCY, OnUpdateCalculateFft)
	ON_UPDATE_COMMAND_UI(ID_CALCULATE_WATERFALL, OnUpdateCalculateWaterfall)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CAudchView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CAudchView::OnFilePrintPreview)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
//		statics
/////////////////////////////////////////////////////////////////////////////

static void enable_MenuItem( CCmdUI* pCmdUI, CNamed *pTarget, UNITMSR uUom)
{
CDataSet *ctarg = (CDataSet *)pTarget;

	if ( ctarg)
		{
		ASSERT_KINDOF( CDataSet, pTarget);
		pCmdUI->Enable(uUom == ctarg->GetUOM());
		}
	else
		pCmdUI->Enable( FALSE);
	
	
}


/////////////////////////////////////////////////////////////////////////////
// CAudDataView construction/destruction
/////////////////////////////////////////////////////////////////////////////

CAudDataView::CAudDataView() : CAudchView()
{

}

CAudDataView::~CAudDataView()
{

}

/////////////////////////////////////////////////////////////////////////////
// CAudDataView drawing

void CAudDataView::OnDraw(CDC* pDC)
{
	CAudchView::OnDraw( pDC);
}



/////////////////////////////////////////////////////////////////////////////
// CAudDataView printing

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CAudDataView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CAudDataView diagnostics

#ifdef _DEBUG
void CAudDataView::AssertValid() const
{
	CAudchView::AssertValid();
}

void CAudDataView::Dump(CDumpContext& dc) const
{
	CAudchView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAudDataView message handlers

void CAudDataView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CAudchView::OnUpdate( pSender, lHint, pHint); 
}

void CAudDataView::OnTransformLimit() 
{
CXformLimit *cxfl = new CXformLimit ( GetTargetObject() );

	Dialog_Perform(cxfl);
}

void CAudDataView::OnTransformScale() 
{
CXformScale *cxfl = new CXformScale ( GetTargetObject() );

	Dialog_Perform(cxfl);
		
}

void CAudDataView::OnTransformInvert() 
{
CXformInvert *cxfl = new CXformInvert ( GetTargetObject() );

	Dialog_Perform(cxfl);
		
}

void CAudDataView::OnTransformTruncate() 
{
CXformTruncate *cxfl = new CXformTruncate ( GetTargetObject() );

	Dialog_Perform(cxfl);
		
		
}

// ------------------------------------------------------------------------
//	OnTransformSmooth
// ------------------------------------------------------------------------
void CAudDataView::OnTransformSmooth() 
{
CXformSmooth *cxfl = new CXformSmooth ( GetTargetObject() );

	Dialog_Perform(cxfl);
		
}

// ------------------------------------------------------------------------
//	OnTransformDelay
// ------------------------------------------------------------------------
void CAudDataView::OnTransformDelay() 
{
CXformDelay *cxfl = new CXformDelay ( GetTargetObject() );

	Dialog_Perform(cxfl);
}

// ------------------------------------------------------------------------
//	OnUpdateTransformDelay
// ------------------------------------------------------------------------
void CAudDataView::OnUpdateTransformDelay(CCmdUI* pCmdUI) 
{

	enable_MenuItem( pCmdUI, GetTargetObject(), uomFreq);
	
}


// ------------------------------------------------------------------------
//	OnCalculateIfft
// ------------------------------------------------------------------------
void CAudDataView::OnCalculateIfft() 
{
CDlgXfIfft cdlg;
float fstart, fend;
CDataSet *cdata = (CDataSet *)GetTargetObject();

				// get the markers and set them into the dbox
	{
	TESTMARK tm;
		tm = *CAudtestApp::GetMarker( 1);	// get the freq markers
		cdlg.m_fStartMarker = tm.fStart;
		cdlg.m_fEndMarker = tm.fEnd;
	}
	{
	int nt = 11025;
	float ft = 2 * cdata->Maximum( dataFreq);		// get ending frequency * 2
		if ( ft > nt)			// nope, more than 11k
			{
			nt *= 2;			// use 22k
			if ( ft > nt)
				{
				nt *= 2;		// 44k
				if ( ft > nt)
					nt = (int )ft;	// give up, use their input
				}
			}
		cdlg.m_nDefaultRate = nt;
	}


	if ( IDOK == cdlg.DoModal())
		{
		CXformIfft *cxfl = new CXformIfft ( GetTargetObject() );

			switch( cdlg.m_nStyle)		// which type is it?
				{
				case 0 :
					fstart = fend = 0.0f;		// to remove warning
					break;				// use entire
				case 1 :				// use markers
					fstart = cdlg.m_fStartMarker;
					fend = cdlg.m_fEndMarker;
					break;
				case 2 :
					fstart = cdlg.m_fStart;
					fend = cdlg.m_fEnd;
					break;
				default:
					ASSERT(0);			// not possible
					fstart = fend = 0.0f;		// to remove warning
				}

			if ( cdlg.m_nStyle)			// do something
				{
				int nstart, nend;
				nstart = cdata->FreqToIndex( fstart);
				nend = cdata->FreqToIndex( fend);

				cxfl->SetRange(nstart, nend);	// use dlgbox info
				}
			cxfl->SetSampleRate( cdlg.m_nSampleRate, cdlg.m_nSampleStyle);

			cxfl->QueueAndDo();						// do the fft
		}
		
}

// ------------------------------------------------------------------------
//	OnCalculateCombine
// ------------------------------------------------------------------------
void CAudDataView::OnCalculateCombine() 
{
CXformCombine *cxfl = new CXformCombine ( GetTargetObject(), NULL );

	Dialog_Perform(cxfl);
		
}


// ------------------------------------------------------------------------
//	OnCalculateFft
// ------------------------------------------------------------------------
void CAudDataView::OnCalculateFft() 
{
CDlgXfFft cdlg;
TESTMARK tm;
float fstart, fend;
CDataSet *cdata = (CDataSet *)GetTargetObject();

				// get the markers and set them into the dbox
	{
	tm = *CAudtestApp::GetMarker( 0);	// get the time markers
	cdlg.m_fStartMarker = tm.fStart;
	cdlg.m_fEndMarker = tm.fEnd;
	cdlg.m_pData = (CDataSet *)GetTargetObject();
	}


	if ( IDOK == cdlg.DoModal())
		{
		CXformFft *cxfl = new CXformFft ( cdlg.m_pData );

			switch( cdlg.m_nStyle)		// which type is it?
				{
				case 0 :
					fstart = fend = 0.0f;		// to remove warning
					break;				// use entire
				case 1 :				// use markers
					fstart = cdlg.m_fStartMarker;
					fend = cdlg.m_fEndMarker;
					break;
				case 2 :
					fstart = cdlg.m_fStart;
					fend = cdlg.m_fEnd;
					break;
				default:
					ASSERT(0);			// not possible
					fstart = fend = 0.0f;		// to remove warning
				}

			if ( cdlg.m_nStyle)			// do something
				{
				int nstart, nend;
				nstart = cdata->FreqToIndex( fstart);
				nend = cdata->FreqToIndex( fend);

				cxfl->SetRange(nstart, nend);	// use dlgbox info
				}


			cxfl->SetWindowing(cdlg.m_nWindow);		// set windowing from dlgbox

			cxfl->QueueAndDo();						// do the fft
		}
		
}

void CAudDataView::OnCalculateImpedance() 
{
CDlgXcImpedance cdlg;
CNamed *ctarg = GetTargetObject();

	cdlg.m_pRoot =  ctarg->GetRootObject();

	if ( IDOK == cdlg.DoModal())
		{
		CXformImpedance *cxfl = 
			new CXformImpedance ( ctarg, cdlg.m_pRoot->FindByID( cdlg.m_dwPicked) );

		{
		TESTMSR tm;
			CAudtestApp::GetMeasures( &tm);			// we want the measurement guys
			cxfl->SetParms( &tm);
		}

		cxfl->QueueAndDo();
		}
		
}

void CAudDataView::OnEditChart() 
{

	CAudchView::OnMakeChart();
	
}

void CAudDataView::OnCalculateCorrelation() 
{
CXformCorrelate *cxfl = new CXformCorrelate ( GetTargetObject() );

	Dialog_Perform(cxfl);
}

void CAudDataView::OnTransformFilter() 
{
float fPoly[21] = { .00000f, -.00031f, -.00094f,  .00271f,  .01013f,  
					.00000f, -.03858f, -.04298f,  .07944f,  .29070f,
					.40000f,  .29070f,  .07944f, -.04298f, -.03858f,
					.0000f,   .01013f,  .00271f, -.00094f, -.00031f, .00000f};

CXtFilter *cxfl = new CXtFilter ( GetTargetObject(), fPoly, sizeof(fPoly)/sizeof(float) );

	Dialog_Perform(cxfl);
}

void CAudDataView::OnUpdateCalculateFft(CCmdUI* pCmdUI) 
{

	enable_MenuItem( pCmdUI, GetTargetObject(), uomTime);

	
}

void CAudDataView::OnUpdateCalculateIfft(CCmdUI* pCmdUI) 
{

	enable_MenuItem( pCmdUI, GetTargetObject(), uomFreq);
	
}


void CAudDataView::OnUpdateCalculateImpedance(CCmdUI* pCmdUI) 
{

	enable_MenuItem( pCmdUI, GetTargetObject(), uomFreq);
	
}

void CAudDataView::OnCalculateGroupdelay() 
{
CDlgXfGrpDelay cdlg;
TESTMARK tm;
float fstart, fend;
CDataSet *cdata = (CDataSet *)GetTargetObject();

				// get the markers and set them into the dbox
	{
	tm = *CAudtestApp::GetMarker( 1);	// get the freq markers
	cdlg.m_fStartMarker = tm.fStart;
	cdlg.m_fEndMarker = tm.fEnd;
	}


	if ( IDOK == cdlg.DoModal())
		{
		CXformCalcDelay *cxfl = new CXformCalcDelay ( GetTargetObject() );

			switch( cdlg.m_nStyle)		// which type is it?
				{
				case 0 :
					fstart = fend = 0.0f;		// to remove warning
					break;				// use entire
				case 1 :				// use markers
					fstart = cdlg.m_fStartMarker;
					fend = cdlg.m_fEndMarker;
					break;
				case 2 :
					fstart = cdlg.m_fStart;
					fend = cdlg.m_fEnd;
					break;
				default:
					ASSERT(0);			// not possible
					fstart = fend = 0.0f;		// to remove warning
				}

			if ( cdlg.m_nStyle)			// do something
				{
				int nstart, nend;
				nstart = cdata->FreqToIndex( fstart);
				nend = cdata->FreqToIndex( fend);

				cxfl->SetRange(nstart, nend);	// use dlgbox info
				}

			cxfl->QueueAndDo();						// do the fft
		}
		
	
}

void CAudDataView::OnUpdateCalculateGroupdelay(CCmdUI* pCmdUI) 
{

	enable_MenuItem( pCmdUI, GetTargetObject(), uomFreq);
	
}

void CAudDataView::OnCalculateFrequency() 
{
CDlgXfCalcFrequency cdlg;
float fstart, fend;
CDataSet *cdata = (CDataSet *)GetTargetObject();

				// get the markers and set them into the dbox
	{
	TESTMARK tm;
		tm = *CAudtestApp::GetMarker( 0);	// get the time markers
		cdlg.m_fStartMarker = tm.fStart;
		cdlg.m_fEndMarker = tm.fEnd;
	}

	cdlg.SetRoot( (CFolder *)cdata->GetRootObject());


	if ( IDOK == cdlg.DoModal())
		{
		CXformCalcFrequency *cxfl = new CXformCalcFrequency ( GetTargetObject() );

			switch( cdlg.m_nStyle)		// which type is it?
				{
				case 0 :
					fstart = fend = 0.0f;		// to remove warning
					break;				// use entire
				case 1 :				// use markers
					fstart = cdlg.m_fStartMarker;
					fend = cdlg.m_fEndMarker;
					break;
				case 2 :
					fstart = cdlg.m_fStart;
					fend = cdlg.m_fEnd;
					break;
				default:
					ASSERT(0);			// not possible
					fstart = fend = 0.0f;		// to remove warning
				}

			if ( cdlg.m_nStyle)			// do something
				{
				int nstart, nend;
				nstart = cdata->FreqToIndex( fstart);
				nend = cdata->FreqToIndex( fend);

				cxfl->SetRange(nstart, nend);	// use dlgbox info
				}

			cxfl->SetCalib( cdlg.m_nCalibType);
			cxfl->SetWindow( cdlg.m_nWindow);
			cxfl->SetReference( cdlg.m_bUseReference, cdlg.m_dwReference);

			cxfl->QueueAndDo();						// do the fft
		}
		
	
}

// ------------------------------------------------------------------------
//	OnCalculateSplice
// ------------------------------------------------------------------------
void CAudDataView::OnCalculateSplice() 
{
CDlgXfSplice cdlg;
CNamed *ctarg = GetTargetObject();

	cdlg.m_pRoot =  ctarg->GetRootObject();
	cdlg.m_dwSource = ctarg->GetID();
				// get the markers and set them into the dbox
	{
	TESTMARK tm;
		tm = *CAudtestApp::GetMarker( 1);	// get the freq markers
		cdlg.m_fStartMarker = tm.fStart;
		cdlg.m_fEndMarker = tm.fEnd;
	}


	if ( IDOK == cdlg.DoModal())
		{
		CXformSplice *cxfl = 
			new CXformSplice ( ctarg, cdlg.m_pRoot->FindByID( cdlg.m_dwPicked) );

		switch( cdlg.m_nStyle)		// which style of freq?
			{
			case 0 :			// low marker
				cxfl->SetFrequency( cdlg.m_fStartMarker);
				break;
			case 1 :			// high marker
				cxfl->SetFrequency( cdlg.m_fEndMarker);
				break;
			case 2 :			// custom
				cxfl->SetFrequency( cdlg.m_fStart);
				break;
			}
		cxfl->SetUseBHigh( cdlg.m_bUseBHigh);
		cxfl->SetUseBRes( cdlg.m_bUseBRes);

		cxfl->QueueAndDo();
		}
}

// ------------------------------------------------------------------------
//	OnUpdateCalculateSplice
// ------------------------------------------------------------------------
void CAudDataView::OnUpdateCalculateSplice(CCmdUI* pCmdUI) 
{

	enable_MenuItem( pCmdUI, GetTargetObject(), uomFreq);
	
}


// define this to cause an entry in the command table, so base class gets called
void CAudDataView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CAudchView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

// ------------------------------------------------------------------------
//	OnCalculateWaterfall
// ------------------------------------------------------------------------

void CAudDataView::OnCalculateWaterfall() 
{
CDlgXfWaterfall cdlg;

CNamed *ctarg = GetTargetObject();

	cdlg.m_pRoot =		ctarg->GetRootObject();
	cdlg.m_dwSource =	ctarg->GetID();
				// get the markers and set them into the dbox
	{
	TESTMARK tm;
		tm = *CAudtestApp::GetMarker( 0);	// get the time markers
		cdlg.m_fStartMarker = tm.fStart;	// put them into the dbox
		cdlg.m_fEndMarker = tm.fEnd;
	}

	if ( IDOK == cdlg.DoModal())
	{			// do a waterfall plot
	COpWaterfall *pwater;
	SWATERFALL swf;

		swf.dwReference = cdlg.m_dwReference;
		swf.dwSource = cdlg.m_dwSource;
		swf.fStart = cdlg.m_fStart;
		swf.fEnd = cdlg.m_fEnd;
		swf.fTotalTime = cdlg.m_fTotalTime;
		swf.iSamples = cdlg.m_iSamples;
		swf.iStyle = cdlg.m_nStyle;
		swf.iWindow = cdlg.m_iWindow;
		swf.fSmooth = cdlg.m_fSmooth;

		pwater = new COpWaterfall( GetDocument(), ctarg->GetID());
		pwater->SetStruct( &swf);
		pwater->QueueAndDo();
	}
	
}

// ------------------------------------------------------------------------
//	OnUpdateCalculateWaterfall
// ------------------------------------------------------------------------
void CAudDataView::OnUpdateCalculateWaterfall(CCmdUI* pCmdUI) 
{
	enable_MenuItem( pCmdUI, GetTargetObject(), uomTime);
	
}
