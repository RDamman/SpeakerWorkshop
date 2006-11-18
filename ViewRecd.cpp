// audtevw.cpp : implementation of the CAudtestView class
//

#include "stdafx.h"
#include "audtest.h"

#include "audtedoc.h"
#include "audtevw.h"

#include "generat.h"
#include "dataset.h"

#include "opItem.h"
#include "opRecord.h"

#include "xform.h"


// =================================================================
// ------------- StdOperation
// =================================================================
void CAudtestView::StdOperation(void *pOpcode )
{
	if ( ! pOpcode)
		return;

COpCode *cop = (COpCode *)pOpcode;

	SetCurrentOperation( cop);

	if ( cop->QueueAndDo())				// execute the first part and check for success
		SetCurrentOperation( NULL);		// failure condition, reset the pointer

}





// =================================================================
// ------------- message handlers
// =================================================================

LRESULT CAudtestView::OnWimData( WPARAM, LPARAM)
{

	FinishInput();
	return 0L;
}

LRESULT CAudtestView::OnWomDone( WPARAM, LPARAM)
{
	FinishPlay();
	return 0L;
}


// =================================================================
// ------------- Finish Input - the end of a record session
// =================================================================
void CAudtestView::FinishInput(void )
{
COpRecord *cop = (COpRecord *)GetCurrentOperation();

	if ( ! cop)
		return;

	cop->ProcessInput();

	if ( ! cop->IsRecording())
		SetCurrentOperation( NULL);			// we're done with it

	CAudtestApp::SetIsWorking( FALSE);

}


// =================================================================
// ------------- Finish Play
// =================================================================
void CAudtestView::FinishPlay(void )
{

}


// =================================================================
// ------------- Operations
// =================================================================

// -----------------------------------------------------------------
// ------------- On Sound Stop
// -----------------------------------------------------------------
void CAudtestView::OnSoundStop() 
{
COpRecord *cop = (COpRecord *)GetCurrentOperation();

	if ( cop)
		cop->StopSound();

}

