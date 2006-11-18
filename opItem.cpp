// speaker.cpp : implementation of the CDataSetArray classes
//


#include "stdafx.h"
#include "audtest.h"

//#include "named.h"
#include "folder.h"
#include "Chart.h"

#include "opcode.h"

#include "OpItem.h"
#include "Xform.h"
#include "XformAll.h"
#include "Dataset.h"

#include "audtedoc.h"
#include "audtevw.h"

#include "utils.h"

#include "math.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// ///////////////////////////////////////////////////////
//				Opcode Stuff
// ///////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////
//				Opcode Rename
// ///////////////////////////////////////////////////////

COpRename::COpRename( CNamed *cTarget, LPCSTR lpNew) : COpCode( cTarget), m_csOldName(), m_csNewName() 
{
	m_csOldName = cTarget->GetName();
	m_csNewName = lpNew;
	cTarget->SetLastEdit();
}

COpRename::~COpRename()
{

}


UINT COpRename::GetNameID(void)
{
	return IDOP_RENAME;
}

int COpRename::DoUndo( void)
{
CNamed *ctarg = (CNamed *)FindTargetObject();

	if ( ctarg)
		{
		ctarg->SetName( m_csOldName);
		m_cDocument->UpdateAll( NULL, ctarg->GetID() );
		}

	return 0;
}

int COpRename::DoExe( bool )
{
CNamed *ctarg = (CNamed *)FindTargetObject();

	if ( ctarg)
		{
		ctarg->SetName( m_csNewName);
		m_cDocument->UpdateAll( NULL, ctarg->GetID() );
		}
	return 0;

}

int COpRename::DoRedo( void)
{
	return DoExe();			// do it again

}

// ///////////////////////////////////////////////////////
//				Opcode Swap Temporary status
// ///////////////////////////////////////////////////////
COpSwapTemp::COpSwapTemp( CNamed *cTarget) : COpCode( cTarget)
{
	m_bWasTemp = cTarget->IsTemporary();
}

COpSwapTemp::~COpSwapTemp()
{
}


UINT COpSwapTemp::GetNameID(void)
{
	if ( m_bWasTemp)
		return IDOP_MAKEPERM;
	else
		return IDOP_MAKETEMP;
}

int COpSwapTemp::DoUndo( void)
{
CNamed *ctarg = (CNamed *)FindTargetObject();

	if ( ctarg)
	{
		ctarg->SetTemporary( m_bWasTemp);
		ctarg->UpdateViews();
	}

	return 0;
}

int COpSwapTemp::DoExe( bool)
{
CNamed *ctarg = (CNamed *)FindTargetObject();

	if ( ctarg)
	{
		ctarg->SetTemporary( ! m_bWasTemp);
		ctarg->UpdateViews();
	}


	return 0;
}

int COpSwapTemp::DoRedo( void)
{

	return DoExe();

}



// ///////////////////////////////////////////////////////
//				Opcode Delete
// ///////////////////////////////////////////////////////
COpDelete::COpDelete( CNamed *cTarget) : COpCode( cTarget)
{
	m_cOldObject = NULL;
	m_dwParent = 0;
}

COpDelete::~COpDelete()
{
	if ( m_cOldObject)
		delete m_cOldObject;
}


UINT COpDelete::GetNameID(void)
{
	return IDOP_DELETE;
}

int COpDelete::DoUndo( void)
{
	if ( ! m_cOldObject)
		return 3;					// nothing to undo???

CAudtestDoc *pdoc = (CAudtestDoc *)m_cDocument;
CFolder *pparent;

	if ( ! pdoc)
		return 2;

	pparent = (CFolder *)pdoc->GetByID( m_dwParent);

	if ( pparent)
		{
		pparent->AddItem( m_cOldObject);
		m_cOldObject = NULL;
		}
	else
		return 1;

	m_cDocument->UpdateAll( NULL, GetTarget() );

	return 0;
}

int COpDelete::DoExe( bool)
{
CNamed *ctarg = (CNamed *)FindTargetObject();
CAudtestDoc *pdoc = (CAudtestDoc *)m_cDocument;
CFolder *proot;

	if ( (! pdoc) || !ctarg)
		return 1;

	proot = pdoc->GetRoot();			// go straight to the source
	m_cOldObject = ctarg;					// save the old guy
	m_dwParent = proot->GetParent( ctarg->GetID() )->GetID();
											// now remove, don't delete it
	proot->RemoveItem( ctarg->GetID() );
	pdoc->RemoveItemView( ctarg->GetID());

	pdoc->UpdateAll( NULL, ctarg->GetID() );

	return 0;
}

int COpDelete::DoRedo( void)
{

	return DoExe();

}


// ///////////////////////////////////////////////////////
//				Opcode Insert
//						here cTarget is the parent!
// ///////////////////////////////////////////////////////
COpInsert::COpInsert( CNamed *cTarget, CNamed *cNew) : COpCode( cTarget)
{
	m_cOldObject = cNew;
}

COpInsert::~COpInsert()
{
	if ( m_cOldObject)
		delete m_cOldObject;
}


UINT COpInsert::GetNameID(void)
{
	return IDOP_INSERT;
}

int COpInsert::DoUndo( void)
{
CAudtestDoc *pdoc = (CAudtestDoc *)m_cDocument;
CFolder *pparent;

	if ( ! pdoc)
		return 2;

	pparent = (CFolder *)pdoc->GetRoot();

	if ( pparent)
		{
		m_cOldObject = pparent->GetItem( m_dwID, TRUE);	// get it back
		pparent->RemoveItem( m_cOldObject->GetID());
		}
	else
		return 1;

	if ( m_cOldObject)
	{
		CAudtestDoc *pdoc = (CAudtestDoc *)(pparent->GetDocument());
		ASSERT( pdoc);
		pdoc->RemoveItemView( m_cOldObject->GetID());
		m_cDocument->UpdateAll( NULL, m_cOldObject->GetID() );
	}

	return 0;
}

int COpInsert::DoExe( bool)
{
CNamed *ctarg = (CNamed *)FindTargetObject();
CAudtestDoc *pdoc = (CAudtestDoc *)m_cDocument;
CFolder *proot;
CFolder *pparent;

	if ( (! pdoc) || (!ctarg) || !m_cOldObject)
		return 1;

	proot = pdoc->GetRoot();			// go straight to the source

	if ( ntFolder == ctarg->GetType())
		pparent = (CFolder *)ctarg;
	else
		pparent = proot->GetParent( ctarg->GetID() );

											// now remove, don't Insert it
	pparent->AddItem( m_cOldObject );
	m_dwID = m_cOldObject->GetID();			// get the id for later

	m_cOldObject = NULL;					// we're done with it

	m_cDocument->UpdateAll( NULL, m_dwID);

	return 0;
}

int COpInsert::DoRedo( void)
{
	return DoExe();
}


// ///////////////////////////////////////////////////////
//				Opcode Change
// ///////////////////////////////////////////////////////

// cNew is ours to keep, ctarget is not
COpChange::COpChange( CNamed *cTarget, CNamed *cNew) : COpCode( cTarget)
{
	m_cOldObject = cTarget;
	m_cNewObject = cNew;			// we keep this one
	cNew->SetLastEdit();
	m_bSwapped = false;
}

COpChange::~COpChange()
{
	if ( m_cOldObject && m_bSwapped)
		delete m_cOldObject;
	if ( m_cNewObject && !m_bSwapped)
		delete m_cNewObject;
}


UINT COpChange::GetNameID(void)
{
	return IDOP_CHANGE;
}

static swap_ID( CNamed *cThere, CNamed *cNew)
{
DWORD dwid, dwid2;
CNamed *pname;

	cThere->SetPointerByID( cNew);
	dwid = cNew->GetID();
	pname = cThere->GetRootObject()->GetParent( dwid);	// debug
	dwid2 = cThere->GetID();		// just for debug
	pname = cThere->GetRootObject()->GetParent( dwid2);	// debug
	cNew->SetID( dwid2);
	cThere->SetID( dwid);			// swap the id's

}

int COpChange::DoUndo( void)
{
CNamed *cf = (CNamed *)FindTargetObject();

	if ( cf && m_bSwapped)
		{
		m_cNewObject = cf;		// in case the new object pointer changed
		swap_ID(  m_cNewObject, m_cOldObject);
		m_cDocument->UpdateAll( NULL, m_cOldObject->GetID() );
		m_bSwapped = false;
		}

	return 0;

}

int COpChange::DoExe( bool )
{
CNamed *cf = (CNamed *)FindTargetObject();

	if ( (!m_cOldObject) || !m_cNewObject )
		return 1;			// fail miserably

	if ( m_bSwapped)
		return 0;			// we're done already

	if ( cf)
		{
		ASSERT( ! strcmp(cf->GetRuntimeClass()->m_lpszClassName, m_cNewObject->GetRuntimeClass()->m_lpszClassName));
		m_cNewObject->SetRootObject( cf->GetRootObject());
#if 0
		*cf = *m_cNewObject;
#else
		m_cNewObject->SetRootObject( cf->GetRootObject());

		swap_ID( cf, m_cNewObject);
#endif
		m_bSwapped = true;
		m_cDocument->UpdateAll( NULL, m_cNewObject->GetID() );
		m_cOldObject = cf;		// in case pointer changed
		}
	return 0;

}

int COpChange::DoRedo( void)
{

	return DoExe();

}

CNamed *COpChange::GetTreedObject( void)
{
	return (m_bSwapped ? m_cNewObject : m_cOldObject);
}


// ///////////////////////////////////////////////////////
//				Opcode Name Trails
// ///////////////////////////////////////////////////////

#define STRTRAILS _T("%s.trl%d")


COpNameTrails::COpNameTrails(CNamed *cTarget, CNamed *pNew) : COpCode( cTarget)
{
int itrails = CAudtestApp::GetTrails();
CNamed *cfind = NULL;				// the ones we find
CString csname;
CString csoriginal;

	m_cNewObject = pNew;			// we keep this one
	m_cOldObject = NULL;

	m_csName = pNew->GetName();		// get the name of the original guy
	m_dwNewID = pNew->GetID();
	m_cNewObject->SetRootObject( cTarget->GetRootObject());

	pNew->SetLastEdit();

	m_bSwapped = false;

	m_dwIDs.SetSize(0, 10);
	m_dwIDs.Add( cTarget->GetID());		// first element is our guy

	csoriginal = cTarget->GetName();

	{
	int i;
		for ( i=1; i<=itrails; i++)
		{
			csname.Format(STRTRAILS, csoriginal, i);		// name.td
			cfind = cTarget->FindByName( csname, FALSE);		// look only in his tree
			if ( cfind)					// queue up nothing, just find it
				m_dwIDs.Add( cfind->GetID());			// save the id for later
			else
				break;			// we're done if we didn't find this one
		}
	}

	m_bEndOfTrail = (cfind != NULL);		// if cfind, we are at the end

}



COpNameTrails::~COpNameTrails()
{
	if ( m_cOldObject && m_bSwapped)
		delete m_cOldObject;
	if ( m_cNewObject && !m_bSwapped)
		delete m_cNewObject;
}


int COpNameTrails::DoExe( bool bRedo)
{
CNamed *ctarg = (CNamed *)FindTargetObject();
CNamed *cfind;				// the ones we find
CDWordArray cids;
CString csname;
int i;
CFolder *pparent = ctarg->FindParent();	// this guy doesn't change no matter what
CNamed *cf2;
CDWordArray dwchartids;

	if ( m_bSwapped)
		return 0;			// we're done already
							// now go through and rename everyone

	cf2 = m_cNewObject;
	for ( i=0; i<m_dwIDs.GetSize(); i++)
	{
		cfind = pparent->FindByID( m_dwIDs[i]);		// get the first guy
		cfind->SetTemporary( true);					// set them to temporary
		ASSERT( cfind);
		csname = cfind->GetName();
		cf2->SetName( csname);
		cf2 = cfind;		// now it's the last one
	}
				// now we're at the end of the line
	csname.Format(STRTRAILS, m_cNewObject->GetName(), i);		// name.td
	cf2->SetName( csname);			// set his name
				// now go through, swapping ids

	cf2 = m_cNewObject;

	for ( i=0; i<m_dwIDs.GetSize(); i++)
	{
		cfind = pparent->FindByID( m_dwIDs[i]);		// get the first guy
		ASSERT( cfind);
		swap_ID( cfind, cf2);
		cf2 = cfind;		// now it's the last one
	}

	if ( m_bEndOfTrail)				// we were at the end of the line
		m_cOldObject = cf2;			// we'll delete this one
	else
	{
		pparent->AddItem( cf2);		// add the last one back in
		m_cOldObject = NULL;		// no one to delete
	}

	{
	CNamed *pchart;
	CString csname;
		ctarg = (CNamed *)FindTargetObject();
		csname.Format(_T("%s.Chart"), ctarg->GetName());
		dwchartids.Copy( m_dwIDs);
		if ( ! m_bEndOfTrail)
			dwchartids.Add( cf2->GetID());		// chart the latest one also
		pchart = m_cDocument->BuildBaseChart( ctarg, csname, dwchartids);
		if ( pchart)
			pchart->SetTemporary( true);
	}

	for ( i=0; i<m_dwIDs.GetSize(); i++)
		m_cDocument->UpdateAll( NULL, m_dwIDs[i] );
	m_bSwapped = true;

	return 0;

}

int COpNameTrails::DoUndo( )
{
CNamed *ctarg = (CNamed *)FindTargetObject();
CNamed *cfind;				// the ones we find
CDWordArray cids;
CString csname;
int i;
CFolder *pparent = ctarg->FindParent();	// this guy doesn't change no matter what

	if ( ! m_bSwapped)
		return 0;			// we're done already

	m_cNewObject = ctarg;	// in case pointer changed

							// now go through and rename everyone
	{
		CNamed *cf2;

		if ( m_cOldObject)
			cf2 = m_cOldObject;		// it's not in the tree
		else
			cf2 = pparent->FindByID( m_dwNewID);		// get the last guy
		ASSERT(cf2);
		for ( i=m_dwIDs.GetSize()-1; i >= 0; i--)
		{
			cfind = pparent->FindByID( m_dwIDs[i]);		// get the first guy
			ASSERT( cfind);
			csname = cfind->GetName();
			cf2->SetName( csname);
			cf2 = cfind;		// now it's the last one
		}
					// now we're at the end of the line
		m_cNewObject->SetName( m_csName);
	}
				// now go through, swapping ids
	{
		CNamed *cf2;

		if ( m_cOldObject)
			cf2 = m_cOldObject;
		else
		{
			cf2 = pparent->FindByID( m_dwNewID);		// get the last guy
			pparent->RemoveItem( m_dwNewID);	// remove the new guy
		}
		ASSERT(cf2);
		for ( i=m_dwIDs.GetSize()-1; i >= 0; i--)
		{
			cfind = pparent->FindByID( m_dwIDs[i]);		// get the first guy
			ASSERT( cfind);
			swap_ID( cfind, cf2);
			cf2 = cfind;		// now it's the last one
		}
					// now we're at the end of the line
	}

	cfind = pparent->FindByID( m_dwIDs[0]);			// get the very first one
	cfind->SetTemporary( false);					// make him permanent

	for ( i=0; i<m_dwIDs.GetSize(); i++)
		m_cDocument->UpdateAll( NULL, m_dwIDs[i] );
	m_cDocument->UpdateAll( NULL, m_dwNewID );

	m_bSwapped = false;

	return 0;

}

int COpNameTrails::DoRedo( )
{
	return DoExe();			// just do it again

}

CNamed *COpNameTrails::GetTreedObject( void)
{
	return (CNamed *)FindTargetObject();
}


// ///////////////////////////////////////////////////////
//				Opcode Checkpoint
// ///////////////////////////////////////////////////////

// cNew is ours to keep, ctarget is not
COpCheckpoint::COpCheckpoint( CNamed *cTarget) : COpCode( cTarget)
{
	m_cOldObject = cTarget->Duplicate();
}

COpCheckpoint::~COpCheckpoint()
{
	if ( m_cOldObject)
		delete m_cOldObject;
}


UINT COpCheckpoint::GetNameID(void)
{
	return IDOP_CHANGE;			// irrelevant
}

int COpCheckpoint::DoUndo( void)
{
CNamed *cf = (CNamed *)FindTargetObject();

	if ( cf)
		{
		*cf = *m_cOldObject;
		m_cDocument->UpdateAll( NULL, cf->GetID() );
		}

	return 0;

}

int COpCheckpoint::DoExe( bool)
{
CNamed *cf = (CNamed *)FindTargetObject();

	if ( !m_cOldObject)
		return 1;			// fail miserably

	if ( cf)
		{
		*cf = *m_cOldObject;		// do nothing actually the first time
		m_cDocument->UpdateAll( NULL, cf->GetID() );
		}
	return 0;

}

int COpCheckpoint::DoRedo( void)
{

	return DoExe();

}

// ///////////////////////////////////////////////////////
//				Opcode Find or Create
// ///////////////////////////////////////////////////////


COpFindOrCreate::COpFindOrCreate(CNamed *cTarget, LPCSTR lpszNewName, NAMETYPES ntNewType) : COpMulti( cTarget), m_csName()
{

	m_csName = lpszNewName;
	m_ntType = ntNewType;
	m_dwFound = 0;

}



COpFindOrCreate::~COpFindOrCreate()
{
}


int COpFindOrCreate::DoExe( bool)
{
CNamed *ctarg = (CNamed *)FindTargetObject();

	ASSERT( ctarg);

CNamed *cfind = ctarg->FindByName( m_csName, FALSE);		// look only in his tree
COpCode *cop;
CFolder *proot;

	if ( cfind && m_ntType == cfind->GetType() )		// queue up nothing, just find it
		{
		m_dwFound = cfind->GetID();
//		cop = new COpCheckpoint( cfind);
//		return PrivateQueue( cop);
		return 0;
		}

	cfind = ctarg->CreateByName( m_csName, m_ntType);		// this adds it to the tree
	m_dwFound = cfind->GetID();
	proot = (CFolder *)ctarg->GetRootObject();
	proot->RemoveItem( cfind->GetID());							// remove it...

	cop = new COpInsert( ctarg, cfind);
	return PrivateQueue( cop);

}

CNamed *COpFindOrCreate::GetFound()
{
	return ((CAudtestDoc *)m_cDocument)->GetRoot()->FindByID( m_dwFound);
}

// ---------------------------------------------------------------------------

// ///////////////////////////////////////////////////////
//				Opcode Make Chart
// ///////////////////////////////////////////////////////


COpMakeChart::COpMakeChart(CDocument *cDoc, DWORD dwTarget) : COpCustom( cDoc, dwTarget)
{
	SetNameID(IDS_MAKECHART);
	m_pChart = NULL;
}



// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
COpMakeChart::~COpMakeChart()
{
}


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
int COpMakeChart::DoExe( bool bRedo)
{
CNamed *cf = (CNamed *)FindTargetObject();
COpFindOrCreate *ccr;
CChart *cchart;

	if ( !cf)
		return 1;			// fail miserably

	ccr = new COpFindOrCreate( cf, cf->GetName() + ".Chart", ntChart);
	if ( bRedo)
	{
		if ( PrivateQueue( ccr))					// queue the find
			return 1;
	}
	else
	{
		if ( ccr->DoExe( bRedo))
			return 1;
	}
	cchart = (CChart *)ccr->GetFound();
	if ( cchart)
	{
		cchart->CreateChart( cf);
		cchart->UpdateViews();
		m_pChart = cchart;
		return 0;
	}

	return 1;

}


// ///////////////////////////////////////////////////////
//				Opcode Waterfall
// ///////////////////////////////////////////////////////


COpWaterfall::COpWaterfall(CDocument *cDoc, DWORD dwTarget) : COpCustom( cDoc, dwTarget)
{
	SetNameID(IDS_MAKEWATER);
	m_sWater.fStart = 0.0f;
	m_sWater.fEnd = 1.0f;
	m_sWater.iWindow = 0;
	m_sWater.iStyle = 0;
	m_sWater.dwReference = 0;
	m_sWater.fTotalTime = 1.0f;
	m_sWater.iSamples = 10;
	m_sWater.fSmooth = 0.1f;

}



// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
COpWaterfall::~COpWaterfall()
{
}

#define  HLSMAX   240	 /* H,L, and S vary over 0-HLSMAX */ 
#define  RGBMAX   255   /* R,G, and B vary over 0-RGBMAX */ 
                           /* HLSMAX BEST IF DIVISIBLE BY 6 */ 
                           /* RGBMAX, HLSMAX must each fit in a byte. */ 

   /* Hue is undefined if Saturation is 0 (grey-scale) */ 
   /* This value determines where the Hue scrollbar is */ 
   /* initially set for achromatic colors */ 
#define UNDEFINED (HLSMAX*2/3)


  /* utility routine for HLStoRGB */ 
static   WORD HueToRGB(WORD n1,WORD n2,WORD hue)
{
  /* range check: note values passed add/subtract thirds of range */ 
	if (hue < 0)
		hue += HLSMAX;

	if (hue > HLSMAX)
		hue -= HLSMAX;

	/* return r,g, or b value from this tridrant */ 
	if (hue < (HLSMAX/6))
		return (WORD )( n1 + (((n2-n1)*hue+(HLSMAX/12))/(HLSMAX/6)) );
	if (hue < (HLSMAX/2))
		return ( n2 );
	if (hue < ((HLSMAX*2)/3))
		return (WORD )( n1 +    (((n2-n1)*(((HLSMAX*2)/3)-hue)+(HLSMAX/12))/(HLSMAX/6)) );
	else
		return ( n1 );
}

static DWORD HLStoRGB(WORD hue,WORD lum,WORD sat)
{
WORD R,G,B;                /* RGB component values */ 
WORD  Magic1,Magic2;       /* calculated magic numbers (really!) */ 

	if (sat == 0)
	{            /* achromatic case */ 
		R=G=B=(WORD )((lum*RGBMAX)/HLSMAX);
		if (hue != UNDEFINED)
		{		/* ERROR */ 
		}
	}
	else
	{                    /* chromatic case */ 
							/* set up magic numbers */ 
		if (lum <= (HLSMAX/2))
			Magic2 = (WORD )((lum*(HLSMAX + sat) + (HLSMAX/2))/HLSMAX);
		else
			Magic2 = (WORD )(lum + sat - ((lum*sat) + (HLSMAX/2))/HLSMAX);
		Magic1 = (WORD )(2*lum-Magic2);

		/* get RGB, change units from HLSMAX to RGBMAX */ 
		R = (WORD )((HueToRGB(Magic1,Magic2,hue+(HLSMAX/3))*RGBMAX + (HLSMAX/2))/HLSMAX);
		G = (WORD )((HueToRGB(Magic1,Magic2,hue)*RGBMAX + (HLSMAX/2)) / HLSMAX);
		B = (WORD )((HueToRGB(Magic1,Magic2,hue-(HLSMAX/3))*RGBMAX + (HLSMAX/2))/HLSMAX);
	}
	return(RGB(R,G,B));
}

			// these values were arrived at arbitrarily
static WORD g_lumin = (WORD )160;		// the luminance
static WORD g_satur = (WORD )120;		// the saturation
static double g_octave = 1.5;


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
int COpWaterfall::DoExe( bool bRedo)
{
CNamed *cf = (CNamed *)FindTargetObject();
COpFindOrCreate *ccr;
CFolder *pfolder;
CDataSet *pcinput;
CDataSet *pcrefer;
CDataSet *preferfft;
CChart *pchart;
CDWordArray dwids;			// array of ids we build
CAudtestDoc *pdoc = (CAudtestDoc *)GetDocument();
float fstart, fend;

	pcinput = (CDataSet *)cf->FindByID( m_sWater.dwSource);		// get the source data
	ASSERT( pcinput->IsType( ntDataSet, uomTime));				// must be a time dataset
	if ( !  pcinput->IsType( ntDataSet, uomTime))
	{
		::AfxMessageBox( IDERR_NOTTIME);
		return 1;
	}
	if ( 0 == m_sWater.iStyle)			// all
		return 2;						// we can't do this


	{
	TESTMARK tm;
		switch( m_sWater.iStyle)			// all, window, or markers
		{
		case 1 :
			tm = *CAudtestApp::GetMarker( 0);		// time markers
			fstart = tm.fStart;
			fend = tm.fEnd;
			break;
		case 2 :				// given data
			fstart = m_sWater.fStart;
			fend   = m_sWater.fEnd;
			break;
		case 0 :					// all data????
		default :
			ASSERT( 0);
			fstart = fend = 0.0f;		// to avoid a warning
			break;
		}
	}


	if ( (fstart + m_sWater.fTotalTime) >= fend)
	{
		::AfxMessageBox( IDERR_TOOMUCHTIME);
		return 3;
	}

	if ( m_sWater.dwReference)
	{
		pcrefer = (CDataSet *)cf->FindByID( m_sWater.dwReference);		// get the source data
		if ( pcrefer)
		{
			ASSERT( pcrefer->IsType( ntDataSet, uomTime));				// must be a time dataset
			if ( !  pcrefer->IsType( ntDataSet, uomTime))
				return 1;
		}
	}
	else
		pcrefer = NULL;

			// start by creating a folder to put everything in
	ccr = new COpFindOrCreate( cf, cf->GetName() + ".Water", ntFolder);
	if ( PrivateQueue( ccr))					// queue the find
		return 1;
	pfolder = (CFolder *)ccr->GetFound();

	ASSERT( pfolder->IsType( ntFolder));

	CreateProgressBar( IDS_STATCALC, 100);

			// now create the datasets to hold the data
	{
	int i;
	int nstart, nend;				// the indices
	CString csname;
	CDataSet *pdata;				// dest dataset
	CXformSmooth *cxs;

		if ( pcrefer)		// do the same processing with the reference set
		{
			csname.Format( "%s.fft", pcrefer->GetName());
			ccr = new COpFindOrCreate( pfolder, csname, ntDataSet);
			PrivateQueue( ccr);			// do it
			preferfft = (CDataSet *)ccr->GetFound();
			nstart = pcinput->FreqToIndex( fstart);
			nend   = pcinput->FreqToIndex( fend);
			::ExecuteFft( preferfft, pcrefer, 0, nend-nstart, m_sWater.iWindow);		// do the fft
			if ( m_sWater.fSmooth > 0.0f)
			{
				cxs = new CXformSmooth( preferfft);			// data to smooth
				cxs->SetCustom( m_sWater.fSmooth);			// 1/10th octave smoothing
				cxs->DoExe( false);				// just do it
				delete cxs;
			}
		}
		else
			preferfft = NULL;

			// take an fft for each shot
		for ( i=0; i<m_sWater.iSamples; i++)
		{
			ShowProgressBar( (100 * i) / m_sWater.iSamples);
			csname.Format( "%s.W.%d", pcinput->GetName(), i+1);
			ccr = new COpFindOrCreate( pfolder, csname, ntDataSet);
			PrivateQueue( ccr);			// do it
			pdata = (CDataSet *)ccr->GetFound();
			nstart = pcinput->FreqToIndex(fstart + i * m_sWater.fTotalTime / m_sWater.iSamples);
//			nend   = pcinput->FreqToIndex(fend + i * m_sWater.fTotalTime / m_sWater.iSamples );
			nend   = pcinput->FreqToIndex(fend  );
			::ExecuteFft( pdata, pcinput, nstart, nend, m_sWater.iWindow);		// do the fft
			if ( m_sWater.fSmooth > 0.0f)
			{
				cxs = new CXformSmooth( pdata);			// data to smooth
				cxs->SetCustom( m_sWater.fSmooth);		// 1/10th octave smoothing
				cxs->SetMethod( 0);						// absolute smoothing
				cxs->DoExe( false);				// just do it
				delete cxs;
			}
			if ( preferfft)				// we have a reference
			{
				::ExecuteCombine( pdata, preferfft, 3);			// divide one by the otehr
			}
			{
				int j;
				for ( j=0; j<pdata->GetCount(); j++)
				{
				float ffreq = pdata->DataAt( dataFreq, j);
				float ffreq2 = pdata->DataAt( dataFreq, j+1);
					if ( (ffreq2 / ffreq) < g_octave)
						break;
				}
				pdata->DeleteLeft( j);			// remove them
			}
			dwids.Add( pdata->GetID());
		}
	}

	CloseProgressBar( );

			// also make a chart to hold the data
	{
	COpMakeChart *cpm;
	CString csname;

		csname = cf->GetName() + ".Waterfall";
		pchart = (CChart *)cf->FindByName( csname);			// do we already have one?
		if ( (! pchart) || ! pchart->IsType( ntChart))
		{
			cpm = new COpMakeChart( GetDocument(), dwids[0]);		// make a new chart based on this guy
			if ( PrivateQueue( cpm))
				return 1;
			pchart = cpm->GetChart();
			pchart->SetName( csname);
		}
	}

	{
	CSubChart *psub;
	int i;
	CString cstitle;

		pdoc->OpenResource( pchart);		// open the chart
		{
		CAudchView *pview = (CAudchView *)pdoc->FindItemView( pchart->GetID());		// get the view
			if ( pview)
			{
				pview->MakeViewChart();		// make the view if there isn't one already
				psub = pview->GetViewChart();
			}
			else
				psub = NULL;
		}

		if ( ! psub)			// use the subchart
			return 1;

		cstitle.Format( IDS_WATERTITLE, cf->GetName());
		psub->SetTitle( cstitle);
		psub->GetDataAt(0)->ShowPhase( false);			// don't display phase

		for ( i=1; i<m_sWater.iSamples; i++)
		{
			psub->Attach( dwids[i]);
		}

		for ( i=0; i<m_sWater.iSamples; i++)			// set the colors
		{
		CDataLine *pdata = psub->GetDataAt( i);			// get the dataline
		CObjColor *pclr = pdata->GetColor();			// get the color
		double dclr = 200.0 / m_sWater.iSamples;			// go from 0...50 ???
		int iclr = (int )(i * dclr);					// convert to int
		COLORREF rclr = HLStoRGB( (WORD )iclr, g_lumin, g_satur);

			pclr->SetColor( rclr);				// use blackish
		}

		{
		CGridZ *cgr = (CGridZ *)psub->GetGrid( ecZCoord);		// get the Z grid
			cgr->SetSlope( 110.0f);		// go at 45 degrees
			cgr->SetTotal( 1.0f);		// 1 pixel at a time
		}


	}




	return 0;

}

