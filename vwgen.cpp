// audtevw.cpp : implementation of the CAudGenView class
//

#include "stdafx.h"
#include "Audtest.h"

#include "audtedoc.h"
#include "vwGen.h"
#include "Chart.h"

#include "xform.h"
#include "xformall.h"

#include "generat.h"
#include "dataset.h"

#include "zFormEdt.h"

#include "dlgRenam.h"
#include "dlgRecor.h"
#include "dlgPlayS.h"
#include "dlgMsrDistort.h"
#include "dlgMsrIn.h"

#include "opItem.h"

#include "opRecord.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudGenView

IMPLEMENT_DYNCREATE(CAudGenView, CAudchView)

BEGIN_MESSAGE_MAP(CAudGenView, CAudchView)
	//{{AFX_MSG_MAP(CAudGenView)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_COMMAND(ID_SOUND_RECORD, OnSoundRecord)
	ON_COMMAND(ID_SOUND_LOOP, OnSoundLoop)
	ON_COMMAND(ID_SOUND_LOOPRECORD, OnSoundLooprecord)
	ON_COMMAND(ID_SOUND_PLAY, OnSoundPlay)
	ON_COMMAND(ID_SOUND_PLAYAGAIN, OnSoundPlayagain)
	ON_COMMAND(ID_SOUND_RECORDAGAIN, OnSoundRecordagain)
	ON_COMMAND(ID_SOUND_STOP, OnSoundStop)
	ON_COMMAND(ID_SOUND_CONVERTTODATA, OnSoundConverttodata)
	ON_COMMAND(ID_MEASURE_DISTORTION, OnMeasureDistortion)
	ON_COMMAND(ID_MEASURE_FREQUENCYRESPONSE, OnMeasureFrequencyresponse)
	ON_COMMAND(ID_MEASURE_IMPEDANCE, OnMeasureImpedance)
	ON_COMMAND(ID_MEASURE_INTERMODULATIONDISTORTION, OnMeasureIntermodulationdistortion)
	ON_COMMAND(ID_MEASURE_MICROPHONERESPONSE, OnMeasureMicrophoneresponse)
	ON_COMMAND(ID_MEASURE_PASSIVECOMPONENT, OnMeasurePassivecomponent)
	ON_COMMAND(ID_MEASURE_TIMERESPONSE, OnMeasureTimeresponse)
	ON_COMMAND(ID_MEASURE_GATED, OnMeasureGated)
	ON_UPDATE_COMMAND_UI(ID_SHOW_LEFTINPUT, OnUpdateShowLeftinput)
	ON_UPDATE_COMMAND_UI(ID_SHOW_OUTPUT, OnUpdateShowOutput)
	ON_UPDATE_COMMAND_UI(ID_SHOW_RIGHTINPUT, OnUpdateShowRightinput)
	ON_COMMAND(ID_SHOW_LEFTINPUT, OnShowLeftinput)
	ON_COMMAND(ID_SHOW_OUTPUT, OnShowOutput)
	ON_COMMAND(ID_SHOW_RIGHTINPUT, OnShowRightinput)
	ON_COMMAND(ID_SHOW_BOTHINPUT, OnShowBothinput)
	ON_UPDATE_COMMAND_UI(ID_SHOW_BOTHINPUT, OnUpdateShowBothinput)
	ON_COMMAND(ID_GEN_MEASURE_IMPEDANCE, OnMeasureImpedance)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CAudchView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CAudchView::OnFilePrintPreview)

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAudGenView construction/destruction

CAudGenView::CAudGenView()
{
	// TODO: add construction code here

}

CAudGenView::~CAudGenView()
{
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CAudGenView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CAudGenView diagnostics

#ifdef _DEBUG
void CAudGenView::AssertValid() const
{
	CAudchView::AssertValid();
}

void CAudGenView::Dump(CDumpContext& dc) const
{
	CAudchView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAudGenView message handlers

// -----------------------------------------------------------------
// ------------- the local functions to play and record
// -----------------------------------------------------------------

void CAudGenView::execute_Play( RECORDINGINFO *pRec)
{
COpPlayStd *cop = new COpPlayStd( GetTargetObject(), this);

	cop->SetRecordInfo( pRec);

	if ( ! cop->QueueAndDo())
		SetCurrentOperation( cop);

}

void CAudGenView::execute_Record( RECORDINGINFO *pRec)
{
COpRecordStd *cop = new COpRecordStd( GetTargetObject(), this);

	cop->SetRecordInfo( pRec);

	if ( ! cop->QueueAndDo())
		SetCurrentOperation( cop);

}

// -----------------------------------------------------------------
// ------------- OnSoundRecord
// -----------------------------------------------------------------
void CAudGenView::OnSoundRecord() 
{
CNamed *cname;
CAudtestDoc* pDoc = GetDocument();
int nout;
CDlgRecord dlgrecord;

	cname = pDoc->GetByID( GetTarget());
	if ( ! cname)
		return;

	dlgrecord.UseDocument( pDoc);			// use the document settings
	nout = dlgrecord.DoModal();

	if ( IDOK == nout)
		{
		dlgrecord.SetDocument( pDoc);

		OnSoundRecordagain();
		}

}

// -----------------------------------------------------------------
// ------------- OnSoundLoop
// -----------------------------------------------------------------
void CAudGenView::OnSoundLoop() 
{
RECORDINGINFO rec;

	CAudtestApp::GetRecordingInfo( &rec);
	rec.m_bLoopPlay = TRUE;
	execute_Play( &rec);

}

// -----------------------------------------------------------------
// ------------- OnSoundLooprecord
// -----------------------------------------------------------------
void CAudGenView::OnSoundLooprecord() 
{
RECORDINGINFO rec;

		CAudtestApp::GetRecordingInfo( &rec);
		rec.m_bLoopRecord = TRUE;
		rec.m_bLoopPlay = TRUE;
		execute_Record( &rec);
	
}

// -----------------------------------------------------------------
// ------------- OnSoundPlay
// -----------------------------------------------------------------
void CAudGenView::OnSoundPlay() 
{
CAudtestDoc* pDoc = GetDocument();
CDlgPlaySound	dlgplay;
int nout;

CGenerator *pcgen = (CGenerator *)GetTargetObject();

	if ( ! pcgen)
		return;

	dlgplay.UseDocument( pDoc);			// use the document settings
	nout = dlgplay.DoModal();

	if ( IDOK == nout)
		{
		dlgplay.SetDocument( pDoc);
		OnSoundPlayagain();
		}

}

// -----------------------------------------------------------------
// ------------- OnSoundPlayagain
// -----------------------------------------------------------------
void CAudGenView::OnSoundPlayagain() 
{
RECORDINGINFO rec;

	CAudtestApp::GetRecordingInfo( &rec);
	rec.m_bLoopPlay = FALSE;
	execute_Play( &rec);

}

// -----------------------------------------------------------------
// ------------- OnSoundRecordagain
// -----------------------------------------------------------------
void CAudGenView::OnSoundRecordagain() 
{
RECORDINGINFO rec;

		CAudtestApp::GetRecordingInfo( &rec);
		rec.m_bLoopRecord = FALSE;
		rec.m_bLoopPlay = FALSE;
		execute_Record( &rec);
}

// =================================================================
// ------------- Measure and Play functions
// =================================================================
// -----------------------------------------------------------------
// ------------- On Sound Convert To Data - convert play data to a dataset
// -----------------------------------------------------------------
void CAudGenView::OnSoundConverttodata() 
{
CNamed *cname;
CAudtestDoc* pDoc = GetDocument();

	cname = pDoc->GetByID( GetTarget());
	if ( ! cname)
		return;

	CGenerator *pcgen = (CGenerator *)cname;

	pcgen->CreateWave(4096000 / 44142);

	CDataSet *pcdata;
	{
	CString csname = cname->GetName() + ".out";
	CNamed *cnam = pDoc->GetRoot()->GetItemByName( csname);

		if ( cnam && ntDataSet == cnam->GetType())
			pcdata = (CDataSet *)cnam;
		else
			{
			pcdata = new CDataSet();
			pcdata->SetName( csname);
			pDoc->GetRoot()->AddItem( pcdata);
			}
	}
	pcgen->MakeDatasets( FALSE, pcdata, NULL);
	pDoc->UpdateAll(this, pcdata->GetID());
		
}


// -----------------------------------------------------------------
// -------------  OnMeasureDistortion
// -----------------------------------------------------------------
void CAudGenView::OnMeasureDistortion() 
{
CDlgMsrDistort cdlg;
COpMsrDistortion *cop = new COpMsrDistortion( GetTargetObject(), this);
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
MSRDISTORTINFO cinfo;

					// is there a registry entry???
	if ( capp->ReadRegistry( IDS_KEYDISTINFO, &cinfo, sizeof( cinfo)))
		{			// failed, set default values
		cinfo.fFreq = 100.0f;
		cinfo.fFreq1 = 20.0f;
		cinfo.fFreq2 = 1000.0f;
		cinfo.fPower = 1.0f;
		cinfo.fPower1 = 1.0f;
		cinfo.fPower2 = 10.0f;
		cinfo.bLogRange = TRUE;
		cinfo.fWatt = 50;
		cinfo.nStyle = 0;
		cinfo.nPoints = 5;
		}
	cdlg.m_fFreq		= cinfo.fFreq;
	cdlg.m_fFreqStart   = cinfo.fFreq1;
	cdlg.m_fFreqEnd		= cinfo.fFreq2;
	cdlg.m_fPower	= cinfo.fPower;
	cdlg.m_fPowerStart	= cinfo.fPower1;
	cdlg.m_fPowerEnd	= cinfo.fPower2;
	cdlg.m_bLogRange	= cinfo.bLogRange;
	cdlg.m_fEquate		= cinfo.fWatt;
	cdlg.m_nStyle		= cinfo.nStyle;
	cdlg.m_nPoints		= cinfo.nPoints;

	if ( IDOK == cdlg.DoModal())
		{
		cinfo.fFreq		= cdlg.m_fFreq;
		cinfo.fFreq1	= cdlg.m_fFreqStart;
		cinfo.fFreq2	= cdlg.m_fFreqEnd;
		cinfo.fPower	= cdlg.m_fPower;
		cinfo.fPower1	= cdlg.m_fPowerStart;
		cinfo.fPower2	= cdlg.m_fPowerEnd;
		cinfo.bLogRange = cdlg.m_bLogRange;
		cinfo.fWatt		= cdlg.m_fEquate;
		cinfo.nStyle	= cdlg.m_nStyle;
		cinfo.nPoints	= cdlg.m_nPoints;

		capp->WriteRegistry( IDS_KEYDISTINFO, &cinfo, sizeof( cinfo));

		cop->SetParms( &cinfo);

		StdOperation( cop );
		}
	
}

// -----------------------------------------------------------------
// -------------  OnMeasureFrequencyresponse
// -----------------------------------------------------------------
void CAudGenView::OnMeasureFrequencyresponse() 
{
	StdOperation( new COpMsrFrequency( GetTargetObject(), this) );
	
	
}

// -----------------------------------------------------------------
// -------------  OnMeasureImpedance
// -----------------------------------------------------------------
void CAudGenView::OnMeasureImpedance() 
{
	StdOperation( new COpMsrImpedance( GetTargetObject(), this) );
	
}

// -----------------------------------------------------------------
// -------------  OnMeasureIntermodulationdistortion
// -----------------------------------------------------------------
void CAudGenView::OnMeasureIntermodulationdistortion() 
{
CDlgMsrIntermod cdlg;
COpMsrIntermod *cop = new COpMsrIntermod( GetTargetObject(), this);
CAudtestApp *capp = (CAudtestApp *)AfxGetApp();
MSRINTERMODINFO cinfo;

					// is there a registry entry???
	if ( capp->ReadRegistry( IDS_KEYINTERINFO, &cinfo, sizeof( cinfo)))
		{			// failed, set default values
		cinfo.fFreq1 = 19000.0f;
		cinfo.fFreq2 = 20000.0f;
		cinfo.fPower = 50.0f;
		}
	cdlg.m_fFreqStart   = cinfo.fFreq1;
	cdlg.m_fFreqEnd		= cinfo.fFreq2;
	cdlg.m_fPower		= cinfo.fPower;

	if ( IDOK == cdlg.DoModal())
		{
		cinfo.fFreq1	= cdlg.m_fFreqStart;
		cinfo.fFreq2	= cdlg.m_fFreqEnd;
		cinfo.fPower	= cdlg.m_fPower;

		capp->WriteRegistry( IDS_KEYINTERINFO, &cinfo, sizeof( cinfo));

		cop->SetParms( &cinfo);

		StdOperation( cop );
		}
	
}

// -----------------------------------------------------------------
// -------------  OnMeasureMicrophoneresponse
// -----------------------------------------------------------------
void CAudGenView::OnMeasureMicrophoneresponse() 
{
	StdOperation( new COpMsrMicTotal( GetTargetObject(), this) );
	
}

// -----------------------------------------------------------------
// -------------  OnMeasureMicGated
// -----------------------------------------------------------------
void CAudGenView::OnMeasureGated() 
{
	StdOperation( new COpMsrMicAnechoic( GetTargetObject(), this) );


}
// -----------------------------------------------------------------
// -------------  OnMeasurePassivecomponent
// -----------------------------------------------------------------
void CAudGenView::OnMeasurePassivecomponent() 
{
	StdOperation( new COpMsrPassive( GetTargetObject(), this) );
	
}

// -----------------------------------------------------------------
// -------------  OnMeasureTimeresponse
// -----------------------------------------------------------------
void CAudGenView::OnMeasureTimeresponse() 
{
	StdOperation( new COpMsrTime( GetTargetObject(), this) );
	
}

// -----------------------------------------------------------------
// -------------  OnMeasureTransferfunction
// -----------------------------------------------------------------
//void CAudGenView::OnMeasureTransferfunction() 
//{
//	StdOperation( new COpMsrTransfer( GetTargetObject(), this) );
//}


// -----------------------------------------------------------------
// ------------- On Sound Stop
// -----------------------------------------------------------------
void CAudGenView::OnSoundStop() 
{
	CAudtestView::OnSoundStop();
}



void CAudGenView::OnUpdateShowLeftinput(CCmdUI* pCmdUI) 
{
enChannel enshow = CAudtestApp::GetShowChannels();

	pCmdUI->SetRadio ( chLeft == enshow);
	
}

void CAudGenView::OnUpdateShowOutput(CCmdUI* pCmdUI) 
{
enChannel enshow = CAudtestApp::GetShowChannels();

	pCmdUI->SetRadio ( chMono == enshow);
	
}

void CAudGenView::OnUpdateShowRightinput(CCmdUI* pCmdUI) 
{
enChannel enshow = CAudtestApp::GetShowChannels();

	pCmdUI->SetRadio ( chRight == enshow);

}

void CAudGenView::OnUpdateShowBothinput(CCmdUI* pCmdUI) 
{
enChannel enshow = CAudtestApp::GetShowChannels();

	pCmdUI->SetRadio ( chBoth == enshow);
	
}

void CAudGenView::OnShowLeftinput() 
{
enChannel enshow = chLeft;

	CAudtestApp::SetShowChannels( enshow);

CAudtestDoc* pDoc = GetDocument();

	pDoc->UpdateAllViews( NULL);

}

void CAudGenView::OnShowOutput() 
{
enChannel enshow = chMono;

	CAudtestApp::SetShowChannels( enshow);

CAudtestDoc* pDoc = GetDocument();

	pDoc->UpdateAllViews( NULL);

}

void CAudGenView::OnShowRightinput() 
{
enChannel enshow = chRight;

	CAudtestApp::SetShowChannels( enshow);

CAudtestDoc* pDoc = GetDocument();

	pDoc->UpdateAllViews( NULL);

}

void CAudGenView::OnShowBothinput() 
{
enChannel enshow = chBoth;

	CAudtestApp::SetShowChannels( enshow);

CAudtestDoc* pDoc = GetDocument();

	pDoc->UpdateAllViews( NULL);

}


void CAudGenView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
CGenerator *pcgen = (CGenerator *)GetTargetObject();
DWORD dwl, dwr, dwo;		// left, right, out
DWORD dwme;

	if ( ! pcgen)
		return;

	// here's where we determine who is in the chart for this guy
	if ( (!lHint) || (DWORD )lHint == GetTarget())
		{
		CSubChart *cchart = (CSubChart *)GetViewChart();
		CNamed *cdata;
		CString csn;

		if ( cchart)			// we have a chart, do it
			{

			CString csr = ".in.r";
			CString csl = ".in.l";
			RECORDINGINFO rec;

			CAudtestApp::GetRecordingInfo( &rec);
			csn = pcgen->GetName();
			if ( rtTime != rec.m_nDataType)			// measuring frequency
				{
				csr += ".Fft";
				csl += ".Fft";
				}
			if ( rtImpedance == rec.m_nDataType)			// measuring frequency
				{
				csr += ".Z";
				csl += ".Z";
				}

			cdata = pcgen->FindByName( csn + csr);
			dwl = (cdata ? cdata->GetID() : 0);
			cdata = pcgen->FindByName( csn + csl);
			dwr = (cdata ? cdata->GetID() : 0);
			cdata = pcgen->FindByName( csn + ".Output");
			dwo = (cdata ? cdata->GetID() : 0);

						// remove all the datalines
			CDataLine *cp = cchart->GetDataAt(0);
			if ( cp)
				dwme = cp->GetDataID();
			else
				dwme = 0;


			switch( CAudtestApp::GetShowChannels())
				{
				case chLeft:	// left
					if ( dwl && dwl != dwme)
						{
						cchart->DetachAll();
						cchart->Attach( dwl);
						}
					break;
				case chRight:	// right
					if ( dwr && dwr != dwme)
						{
						cchart->DetachAll();
						cchart->Attach( dwr);
						}
					break;
				case chBoth:	// both
					if ( dwl && dwl != dwme)
						{
						cchart->DetachAll();
						cchart->Attach( dwl);
						}
					if ( dwr)
						cchart->Attach( dwr);
					break;
				default:		// ?????
				case chMono:	// output
					if ( dwo && dwo != dwme)
						{
						cchart->DetachAll();
						cchart->Attach( dwo);
						}
					break;
				}
			}

		}

	CAudchView::OnUpdate( pSender, lHint, pHint);
	
}
