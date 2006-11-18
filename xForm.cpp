// speaker.cpp : implementation of the CDataSetArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include "xform.h"
#include "xformall.h"

#include "Audtedoc.h"
#include "Dataset.h"
#include "Enclosur.h"
#include "Driver.h"

#include "zFormEdt.h"

#include "dlgxflim.h"
#include "dlgxfsca.h"
#include "dlgxftru.h"
#include "dlgxfsmo.h"
#include "dlgxfdel.h"
#include "dlgxcadd.h"
#include "dlgXcImp.h"
#include "dlgXfCor.h"
#include "dlgXfInv.h"			// invert
#include "dlgCalcMerge.h"

#include "opitem.h"
#include "Utils.h"

#include "Complex.h"
#include "math.h"

#include "mmwave.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
//				CXcalc
/////////////////////////////////////////////////////////////////////////////

CXcalc::CXcalc( CObject *cTarget) : COpMulti( cTarget)		// must be named and in the tree
{

	m_cOldObject = NULL;
	m_cNewObject = NULL;

}

CXcalc::~CXcalc()
{
	if ( m_cOldObject)
		delete m_cOldObject;
	if ( m_cNewObject)
		delete m_cNewObject;

}

UINT CXcalc::GetNameID(void)
{
	return IDOP_CHANGE;
}


int CXcalc::DoExe( bool bRedo)
{
CNamed *cf = (CNamed *)FindTargetObject();

	if ( bRedo)
		m_cOldObject = cf->Duplicate();

	if ( DoOperation())			// do the work on cf
		{
		return 2;
		}

	cf = (CNamed *)FindTargetObject();	// in case it moved
	if ( bRedo)
		m_cNewObject = cf->Duplicate();

	cf->UpdateViews();

	return 0;

}

int CXcalc::DoUndo( void)
{

	COpMulti::DoUndo();

CNamed *cf = (CNamed *)FindTargetObject();

	if ( cf)
		{
		*cf = *m_cOldObject;
		cf->UpdateViews();
		}

	return 0;

}


int CXcalc::DoRedo( void)
{

	COpMulti::DoRedo();

CNamed *cf = (CNamed *)FindTargetObject();

	if ( cf)
		{
		*cf = *m_cNewObject;
		cf->UpdateViews();
		}

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
//				CXunary
/////////////////////////////////////////////////////////////////////////////

CXunary::CXunary( CObject *cTarget) : CXcalc( cTarget)		// must be named and in the tree
{

}

CXunary::~CXunary()
{

}


/////////////////////////////////////////////////////////////////////////////
//				CXbinary
/////////////////////////////////////////////////////////////////////////////

CXbinary::CXbinary( CObject *cTarget, CObject *cOther) : CXunary( cTarget)		// must be named and in the tree
{
	m_cOther = (CNamed *)cOther;
}

CXbinary::~CXbinary()
{

}

/////////////////////////////////////////////////////////////////////////////
//				CXtransform
/////////////////////////////////////////////////////////////////////////////

CXtransform::CXtransform( CObject *cTarget) : COpMulti( cTarget)
{
	m_dwDestination = 0;
	m_pBase = NULL;
}

CXtransform::~CXtransform()
{
}


int CXtransform::DoExe( bool bRedo)
{

	{					// build the new dataset
	COpFindOrCreate *cop;
	CString cs;
	CNamed *cbase;

	if ( m_pBase)
		cbase = m_pBase;
	else
		cbase = (CNamed *)FindTargetObject();

	cs.LoadString( GetSuffix());
	cs = cbase->GetName() + "." + cs;

	cop = new COpFindOrCreate( cbase, cs, ntDataSet);
	if ( ! PrivateQueue( cop))				// build it
		m_dwDestination = cop->GetFound()->GetID();
	else
		return 1;				// uh oh
	}

CNamed *cf = GetDestination();

	if ( ! cf)
		return 1;			// oooops

				// if cf is in the system directory, don't do an undo!!!!!!!!
	{
	CFolder *croot = cf->GetRootObject();						// get root object
	CNamed *pparent = croot->GetParent( cf->GetID());			// now find our parent
	CAudtestDoc *pdoc = (CAudtestDoc *)croot->GetDocument();	// get current doc
	if ( (!bRedo) || (pparent && (pparent == pdoc->GetSystem())) )			// is parent==system folder?
		{				// then don't allow undo
		DoOperation( cf);
		cf->SetLastEdit();
		}
	else
		{			// not in the system folder, get ready for undo
		CNamed *cfnew;
		cfnew = cf->Duplicate();			// make a new one

		if ( ! cfnew)
			return 1;

		if ( DoOperation( cfnew))
			{
			delete cfnew;
			return 2;
			}
		cfnew->SetLastEdit();
		COpCode *cop = new COpChange( cf, cfnew);
		PrivateQueue( cop);
		}
	}


	m_cDocument->UpdateAll( NULL, cf->GetID() );
	return 0;

}

CNamed *CXtransform::GetDestination( void)
{
 	if ( ! m_dwDestination)
		return NULL;

	return ((CNamed *)FindTargetObject())->FindByID( m_dwDestination);

}





/////////////////////////////////////////////////////////////////////////////
//				CXtBinary
/////////////////////////////////////////////////////////////////////////////

CXtBinary::CXtBinary( CObject *cTarget, CObject *cOther) : CXtransform( cTarget)
{
	m_cOther = (CNamed *)cOther;
}

CXtBinary::~CXtBinary()
{
}


/////////////////////////////////////////////////////////////////////////////
//				CXform
/////////////////////////////////////////////////////////////////////////////

CXform::CXform( CObject *cTarget) : CXcalc( cTarget), m_cDatasets()
{
	m_cDatasets.SetSize(0,100);
}

CXform::~CXform()
{
}


/////////////////////////////////////////////////////////////////////////////
//				CXformLimit
//					perform a limit operation
/////////////////////////////////////////////////////////////////////////////
CXformLimit::CXformLimit( CObject *cTarget) : CXunary( cTarget)		// must be named and in the tree
{
}

CXformLimit::~CXformLimit()
{
}

UINT CXformLimit::DoDialog( )		// xeq dbox
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
CDlgXfLimit cdlg;
UINT uout;

				// fill the function with defaults for this dataset
	cdlg.m_fCurrentMin = cdSource->Minimum( dataAmp);
	cdlg.m_fCurrentMax = cdSource->Maximum( dataAmp);

	uout = cdlg.DoModal();

	if ( IDOK == uout)
		{
		m_fMin = cdlg.m_fMin;
		m_fMax = cdlg.m_fMax;
		m_bUseMin = cdlg.m_bLimitMin;
		m_bUseMax = cdlg.m_bLimitMax;
		}

	return uout;

}

int CXformLimit::DoOperation( )	// xeq xform
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
int i, ncount;
INT32 idat;
INT32 imin, imax;


	imin = FTOI( m_fMin);
	imax = FTOI( m_fMax);

	ncount = cdSource->GetCount();
	for ( i=0; i <ncount; i++)
		{
		idat = cdSource->GetDataAt( i);
		if ( m_bUseMin && idat < imin)
			idat = imin;
		else if ( m_bUseMax && idat > imax)
			idat = imax;
		cdSource->SetDataAt(i, idat);
		}

	return 0;
}

UINT CXformLimit::GetDialog(void)		// get the dialog id
{
	return IDD_XFLIMIT;
}


/////////////////////////////////////////////////////////////////////////////
//				CXformCorrelate
//					perform a Correlate operation
/////////////////////////////////////////////////////////////////////////////
CXformCorrelate::CXformCorrelate( CObject *cTarget) : CXunary( cTarget)		// must be named and in the tree
{
	SetRepeatCount( 1);
}

CXformCorrelate::~CXformCorrelate()
{
}

UINT CXformCorrelate::DoDialog( )		// xeq dbox
{
CDlgXfCorrelate cdlg;
UINT uout;
CDataSet *cdSource = (CDataSet *)FindTargetObject();

				// fill the function with defaults for this dataset
	{
	int i;

		m_nSize = 1;
		for ( i=0; i<20; i++)
			{
			if ( m_nSize > cdSource->GetCount())
				break;
			m_nSize += m_nSize;
			}
		m_nSize /= 2;		// back to just below or =
	}

	cdlg.m_nSize = m_nSize;
	cdlg.m_nRepeatCount = m_nRepeatCount;

	uout = cdlg.DoModal();

	if ( IDOK == uout)
		{
		m_nSize = cdlg.m_nSize;
		m_nRepeatCount = cdlg.m_nRepeatCount;
		}

	return uout;

}


UINT CXformCorrelate::GetDialog(void)		// get the dialog id
{
	return IDD_XFCORRELATE;
}


/////////////////////////////////////////////////////////////////////////////
//				CXformScale
//					perform a scaling operation
/////////////////////////////////////////////////////////////////////////////
CXformScale::CXformScale( CObject *cTarget) : CXunary( cTarget)		// must be named and in the tree
{
}
CXformScale::~CXformScale()
{
}

void CXformScale::SetVars( float fdB, float fFactor, int nMethod, BOOL bUseDb)
{
	m_fdB = fdB;
	m_fFactor = fFactor;
	m_bUseDb = bUseDb;
	m_nMethod = nMethod;

}


UINT CXformScale::DoDialog( )		// xeq dbox
{
CDlgXfScale cdlg;
UINT uout;

				// fill the function with defaults for this dataset
	cdlg.m_cdSource = (CNamed *)FindTargetObject();

	uout = cdlg.DoModal();

	if ( IDOK == uout)
		{
		SetVars( cdlg.m_fdB, cdlg.m_fFactor, cdlg.m_nMethod, cdlg.m_bUseDb);
		}

	return uout;

}

int CXformScale::DoOperation( )	// xeq xform
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
int i, ncount;
float factor = m_fFactor;
float fdata;
int nmethod = m_nMethod;

	if ( m_bUseDb)
		{
		if ( uomDbw == cdSource->GetDOM())	// it's dbw
			factor = (float )pow(10.0f, m_fdB/20);
		else
			factor = (float )pow(10.0f, m_fdB/10);
		if ( nmethod == 0 || nmethod == 1)	// add or subtract using db???
			nmethod += 2;					// convert to multiplicative
		}
	else			// use absolute
		{
		factor = m_fFactor;
		}

	switch( nmethod)
		{
		case 0 :	// add
			break;
		case 1 :	// subtract
			factor = -factor;
			break;
		case 2 :	// multiply
			break;
		case 3 :	// divide
			if ( factor)
				factor = 1.0f / factor;
			else
				factor = .01f;		// random can't divide by 0
			break;
		default :
			break;
		}

	ncount = cdSource->GetCount();
	if ( nmethod != 4)			// not logarithm
	{
		for ( i=0; i <ncount; i++)
			{
			fdata = cdSource->DataValueAt(i, 1);		// get it in volts
			if ( nmethod == 0 || nmethod == 1)
				fdata += factor;
			else
				fdata *= factor;
		if ( ! cdSource->HasPhase())
				cdSource->SetAbsolute(i, fdata, 0.0f);
			else
				cdSource->SetAbsolute(i, fdata, ITOF(cdSource->GetPhaseAt( i)));
			}
	}
	else			// it is logarithm
	{
	CDoubleArray cdb;

		cdb.SetSize( ncount);			// this many
		for ( i=0; i<ncount; i++)
		{
			fdata = cdSource->DataValueAt(i, 1);		// get it in volts
			cdb[i] = fdata;
		}			// now we've copied it out

		cdSource->SetDOM( uomVolts);		// set dataset to volts
		for ( i=0; i<ncount; i++)
		{
			if ( ! cdSource->HasPhase())
			{
				cdSource->SetAbsolute(i, (float )log(cdb[i]), 0.0f);
			}
			else
			{
			cdSource->SetAbsolute(i, (float )log(cdb[i]), 0.0f);
			}
		}			// now we've copied it out
	}

	return 0;
}

UINT CXformScale::GetDialog(void)		// get the dialog id
{
	return IDD_XFSCALE;
}



/////////////////////////////////////////////////////////////////////////////
//				CXformInvert
//					perform a scaling operation
/////////////////////////////////////////////////////////////////////////////
CXformInvert::CXformInvert( CObject *cTarget) : CXunary( cTarget)		// must be named and in the tree
{
}

CXformInvert::~CXformInvert()
{
}

UINT CXformInvert::DoDialog( )		// xeq dbox
{
CDlgXfInvert cdlg;
UINT uout;

	uout = cdlg.DoModal();

	if ( IDOK == uout)
		{
		m_bInvertData = cdlg.m_bInvertData;
		m_bInvertPhase = cdlg.m_bInvertPhase;
		}

	return uout;

}

int CXformInvert::DoOperation( )	// xeq xform
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
int i, ncount;
INT32 idat;
BOOL bisdb;
BOOL busephase;			// in case there is none

	busephase = m_bInvertPhase && cdSource->HasPhase();

	bisdb = (uomDbw == cdSource->GetDOM() || uomDbv == cdSource->GetDOM() );

	ncount = cdSource->GetCount();
	for ( i=0; i <ncount; i++)
		{
		if ( m_bInvertData)
			{
			idat = cdSource->GetDataAt( i);
			if ( bisdb)
				idat = -idat;
			else
				if ( idat)
					idat = FTOI( 1 / ITOF( idat));
			cdSource->SetDataAt(i, idat);
			}
		if ( busephase)
			{
			idat = cdSource->GetPhaseAt( i);
//			if ( idat < 0)
//				idat += FTOI(180);
//			else
//				idat -= FTOI(180);
			idat = -idat;
			cdSource->SetPhaseAt(i, idat);
			}
		}

	return 0;
}

UINT CXformInvert::GetDialog(void)		// get the dialog id
{
	return IDD_XFINVERT;
}


/////////////////////////////////////////////////////////////////////////////
//				CXformTruncate
//					perform a scaling operation
/////////////////////////////////////////////////////////////////////////////
CXformTruncate::CXformTruncate( CObject *cTarget) : CXunary( cTarget)		// must be named and in the tree
{
}
CXformTruncate::~CXformTruncate()
{
}

UINT CXformTruncate::DoDialog( )		// xeq dbox
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
CDlgXfTruncate cdlg;
UINT uout;

				// fill the function with defaults for this dataset

	{
	TESTMARK tm;
		switch( cdSource->GetUOM())
			{
			case uomTime :
				tm = *CAudtestApp::GetMarker( 0);	// get the time markers
				break;
			case uomFreq :
				tm = *CAudtestApp::GetMarker( 1);	// get the freq markers
				break;
			case uomOhms :
				tm = *CAudtestApp::GetMarker( 2);	// get the ohms markers
				break;
			default:
				_ASSERT(0);
				return 0;
			}
		cdlg.m_fStartMarker = tm.fStart;
		cdlg.m_fEndMarker = tm.fEnd;
	}

	uout = cdlg.DoModal();

	if ( IDOK == uout)
		{
		if ( cdlg.m_bUseMarker)
			{
			m_fMin = cdlg.m_fStartMarker;
			m_fMax = cdlg.m_fEndMarker;
			}
		else
			{
			m_fMin = cdlg.m_fStart;
			m_fMax = cdlg.m_fEnd;
			}
		}

	return uout;

}

int CXformTruncate::DoOperation( )	// xeq xform
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
int i, ncount;
INT32 idat, iphase;
float fnow, fstart, fdelta;
int j;


	fstart = cdSource->GetStart();
	fdelta = cdSource->GetDelta();

	ncount = cdSource->GetCount();
	for ( j=i=0; i <ncount; i++)
		{
		fnow = cdSource->DataAt(dataFreq, i);
		if ( m_fMin >= (fnow+fdelta) )
			continue;
		if ( m_fMax < fnow )
			break;
		idat = cdSource->GetDataAt( i);
		if ( cdSource->HasPhase())
			{
			iphase = cdSource->GetPhaseAt(i);
			cdSource->SetDataAt(j, idat, iphase);
			}
		else
			cdSource->SetDataAt(j, idat);
		j++;
		}

	cdSource->SetSize( j, cdSource->HasPhase() ? j : 0);

	if ( m_fMin > fstart)
		{
		cdSource->SetStart( fstart + fdelta * (int )((m_fMin - fstart)/fdelta) );
		}

	return 0;
}

UINT CXformTruncate::GetDialog(void)		// get the dialog id
{
	return IDD_XFTRUNCATE;
}


/////////////////////////////////////////////////////////////////////////////
//				CXformExtend
//					perform a scaling operation
/////////////////////////////////////////////////////////////////////////////
CXformExtend::CXformExtend( CObject *cTarget) : CXunary( cTarget)		// must be named and in the tree
{
}
CXformExtend::~CXformExtend()
{
}

UINT CXformExtend::DoDialog( )		// xeq dbox
{
	return IDOK;
}

#if 0
int CXformExtend::DoOperation( )	// xeq xform
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
int i;
INT32 idat, iphase;
int ncount;


	ncount = cdSource->GetCount();
	cdSource->SetSize( 3*ncount, cdSource->HasPhase() ? 3*ncount : 0);

	if ( cdSource->HasPhase())
		{
		for ( i=0; i <ncount; i++)
			{
			idat = cdSource->GetDataAt( i);
			iphase = cdSource->GetPhaseAt( i);
			cdSource->SetDataAt( i+ncount, idat, iphase);
			}
		for ( i=0; i <ncount; i++)
			{
			cdSource->SetDataAt( i, 0,0);
			cdSource->SetDataAt( i+ncount+ncount, 0,0);
			}
		}
	else
		{
		for ( i=0; i <ncount; i++)
			{
			idat = cdSource->GetDataAt( i);
			cdSource->SetDataAt( i+ncount, idat);
			}
		for ( i=0; i <ncount; i++)
			{
			cdSource->SetDataAt( i, 0);
			cdSource->SetDataAt( i+ncount+ncount, 0);
			}
		}


	return 0;
}
#endif

int CXformExtend::DoOperation( )	// xeq xform
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
int i;
INT32 idat, iphase;
int ncount;
int nmin, nmax;
INT32 icomp;
BOOL bphase = cdSource->HasPhase();


	ncount = cdSource->GetCount();
	icomp = FTOI( cdSource->Maximum( dataAmp) / 3 );

	if ( m_nMin == m_nMax)
		{
		for ( i=0; i <ncount; i++)
			{
			idat = cdSource->GetDataAt( i);
			idat = abs( idat);
			if ( idat > icomp)
				break;
			}
		nmin = i;

		for ( i=ncount-1; i > 0; i--)
			{
			idat = cdSource->GetDataAt( i);
			idat = abs( idat);
			if ( idat > icomp)
				break;
			}
		nmax = i;
		}
	else
		{
		nmin = m_nMin;
		nmax = m_nMax;
		}

	for ( i = nmin; i <= nmax; i++)
		{
		idat = cdSource->GetDataAt( i);
		if ( bphase)
			{
			iphase = cdSource->GetPhaseAt(i);
			cdSource->SetDataAt(i-nmin, idat, iphase);
			}
		else
			cdSource->SetDataAt(i-nmin, idat);
		}
	nmax = i + 1;
						// shrink it

	int npow2 = 1;
	for ( npow2 = 1; npow2 < (1+nmax-nmin); npow2 *= 2);
	npow2 /= 2;		// get back below

	if ( 1.1 > (1+nmax-nmin)/(float )npow2)		// make power of 2 if possible
		nmax = nmin + npow2 - 1;

	cdSource->SetSize( 1 + nmax - nmin, bphase ? (1 + nmax-nmin) : 0);

	m_nMin = nmin;
	m_nMax = nmax;

	return 0;
}

UINT CXformExtend::GetDialog(void)		// get the dialog id
{
	return IDD_XFTRUNCATE;
}


/////////////////////////////////////////////////////////////////////////////
//				CXformSmooth
//					perform a scaling operation
/////////////////////////////////////////////////////////////////////////////
CXformSmooth::CXformSmooth( CObject *cTarget) : CXunary( cTarget)		// must be named and in the tree
{
	m_fCustom = 0.0f;
	m_nMethod = 0;
	m_nStyle = 0;
}
CXformSmooth::~CXformSmooth()
{
}

UINT CXformSmooth::DoDialog( )		// xeq dbox
{
CDlgXfSmooth cdlg;
UINT uout;

				// fill the function with defaults for this dataset
	m_nStyle = 0;
	m_nMethod = 0;

	cdlg.m_nStyle = m_nStyle;
	cdlg.m_nMethod = m_nMethod;
	cdlg.m_fCustom = m_fCustom;
	cdlg.m_cdSource = (CNamed *)FindTargetObject();

	uout = cdlg.DoModal();

	if ( IDOK == uout)
		{
		m_nStyle = cdlg.m_nStyle;
		m_nMethod = cdlg.m_nMethod;
		m_fCustom = cdlg.m_fCustom;
		}

	return uout;

}

int CXformSmooth::DoOperation( void )	// xeq xform
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
int i, ncount;
double dsumx, dsumy;
float *hpw, *hpi;
double dwidth;					// window width based on m_nStyle
int nstart, nend;
double dfmax, dfmin, dfreq;
int j;
float ffreq;
BOOL	bhasphase;

static const double dws[8] = { 1.0, 0.5, (1/3.0), 0.25, (1/6.0), 0.125, 0.1, (1/16.0) };

	CreateProgressBar( IDS_STATSMOOTH, 100);

	if ( m_nStyle <= 7)
		dwidth = pow(2.0, dws[m_nStyle] / 2);		// the multiplier
	else
		if ( m_fCustom > 0)
			dwidth = pow(2.0, (double )(m_fCustom / 2));
		else
			dwidth = pow(2.0, 0.5);

	ncount = cdSource->GetCount();
	bhasphase = cdSource->HasPhase();

	hpw = new float[ncount];
	hpi = new float[ncount];

	for ( i=0; i <ncount; i++)
		{
		ffreq = cdSource->DataAt( dataFreq, i);
		switch( m_nMethod)
			{
			case 0 :	// absolute averaging
			case 2 :	// RMS averaging
				hpw[i] = cdSource->DataValueAt( i, 1);	// convert to absolute
				if ( bhasphase)
					hpi[i] = cdSource->PhaseValueAt( i);
				else
					hpi[i] = 0.0f;
				break;
			case 1 :	// arithmetic averaging
				if ( bhasphase)
					cdSource->GetRectangularAt( ffreq, hpw+i, hpi+i);
				else
					{
					hpw[i] = cdSource->DataValueAt( i, 1);	// convert to absolute
					hpi[i] = 0.0f;
					}
				break;
			default:	// shouldn't be here...
				ASSERT(0);
				break;
			}
		}

	for ( i=0; i <ncount; i++)
		{
		if ( 0 == ( i % 100))
			ShowProgressBar( (100 * i) / ncount);
		dfreq = cdSource->DataAt( dataFreq, i);		// get the frequency
		dfmin = dfreq / dwidth;
		dfmax = dfreq * dwidth;
		if ( dfmin < cdSource->Minimum( dataFreq))
			{
			dfmin = cdSource->Minimum( dataFreq);
			dfmax = dfreq * dfreq / dfmin;
			}
		if ( dfmax > cdSource->Maximum( dataFreq))
			{
			dfmax = cdSource->Maximum( dataFreq);
			dfmin = dfreq * dfreq / dfmax;				// equal left/right window sizes
			}

		nstart = cdSource->FreqToIndex( (float )dfmin);
		nend = cdSource->FreqToIndex( (float )dfmax);

		dsumx = dsumy = 0;
		for ( j=nstart; j<=nend; j++)
			{
			switch( m_nMethod)
				{
				case 0 :	// absolute averaging
					dsumx += hpw[j];
					dsumy += hpi[j];
					break;
				case 1 :	// arithmetic averaging
					dsumx += hpw[j];
					dsumy += hpi[j];
					break;
				case 2 :
					dsumx += hpw[j] * hpw[j];
					dsumy += hpi[j];
					break;
				default:	// shouldn't be here...
					ASSERT(0);
					break;
				}
			}
		if ( m_nMethod != 2)		// not RMS
			{
			dsumx /= (1 + nend - nstart);
			dsumy /= (1 + nend - nstart);
			}
		else
			{
			dsumx = sqrt( dsumx / (1 + nend - nstart) );
			dsumy /= (1 + nend - nstart);
			}
		if ( m_nMethod == 1)
			cdSource->SetRectangular(i,(float )dsumx, (float )dsumy );
		else
			cdSource->SetAbsolute(i,(float )dsumx, (float )dsumy );
		}

	delete [] hpw;
	delete [] hpi;

	CloseProgressBar( );

	return 0;
}

UINT CXformSmooth::GetDialog(void)		// get the dialog id
{
	return IDD_XFSMOOTH;
}


/////////////////////////////////////////////////////////////////////////////
//				CXformDelay
//					Delay a dataset.....
/////////////////////////////////////////////////////////////////////////////
CXformDelay::CXformDelay( CObject *cTarget) : CXunary( cTarget)		// must be named and in the tree
{
	m_bRemoveExcess = false;
	m_fTime = 1.0f;
}
CXformDelay::~CXformDelay()
{
}

UINT CXformDelay::DoDialog( void )		// xeq dbox
{
CDlgXfDelay cdlg;
UINT uout;

	cdlg.SetSource( (CNamed *)FindTargetObject());		// set the dialog's source object
				// fill the function with defaults for this dataset
	uout = cdlg.DoModal();

	if ( IDOK == uout)
		{
		m_fTime = cdlg.m_fFactor;
		m_bRemoveExcess = cdlg.m_bRemoveExcess;
		}

	return uout;

}

int CXformDelay::DoOperation( void )	// xeq xform
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
int i, ncount;
float fphase;
double dtime;
double dtotphase;


	ncount = cdSource->GetCount();

	if ( ! ncount)
		return 0;

#if 1
	if ( m_bRemoveExcess && ncount > 5)
		{
		float flastphase = cdSource->DataAt(dataPhase, 9);
		dtime = 0;
		dtotphase = 0;
		for ( i=10; i <ncount; i++)
			{
			fphase = cdSource->DataAt(dataPhase, i) - flastphase;	// get delta
			flastphase += fphase;			// new phase

			if ( fphase > 240)
				fphase -= 360;
			else if (fphase < -240)
				fphase += 360;
			dtotphase += fphase;			// new total phase
				
			}
		dtime = -dtotphase / (cdSource->DataAt(dataFreq, i) * 360);			// average phase change *delta
//		dtime /= ncount-10;
		m_fTime = -(float )(dtime * 1000);				// save it for others to see
		}
	else
		dtime = m_fTime / 1000;

	for ( i=0; i <ncount; i++)
		{
						// now add in the new amount of phase (time * frequency == total cycles)
		fphase = (float )(360 * dtime * cdSource->DataAt( dataFreq, i) );
		fphase += cdSource->DataAt(dataPhase, i);
		fphase -= 360 * (int )( fphase / 360);
		if ( fphase > 180)
			fphase -= 360;
		else
		if ( fphase < -180)
			fphase += 360;

		cdSource->SetPhaseAt( i, FTOI(fphase));
		}

#else
	if ( m_bRemoveExcess && ncount > 5)
	{						// void hilbert(int n, double delta[], double kappa[])
	double kappa;
	double d1, d2, d3, d4;
	int i1, i2;
	CDoubleArray cda;
	double dmax;
	float fr, fi;

		cda.SetSize( ncount);

		d1 = -100;
		d2 = 100;

		for (i1 = 0; i1 < ncount; i1++)
		{
			cdSource->GetRectangular( i1, &fr, &fi);
			cda[i1] = fr;			// get the real data values
			if ( d1 < cda[i1])
				d1 = cda[i1];
			if ( d2 > cda[i1])
				d2 = cda[i1];		// get min and max values
		}
		if ( d1 < -d2)
			d1 = -d2;			// if min < 0 and better than d1
		dmax = d1;

		for (i1 = 0; i1 < ncount; i1++)
		{
			kappa = 0.;
			for (i2 = 1; i2 < ncount; i2++)
			{
				d1 = ((i1+i2)<ncount)? cda[i1+i2]: 0.;
				d2 = ((i1-i2)>=0)? cda[i1-i2]: 0.;
				d3 = ((i1+i2+1)<ncount)? cda[i1+i2+1]: 0.;
				d4 = ((i1-i2-1)>=0)? cda[i1-i2-1]: 0.;

				kappa -= 0.5 * (d1-d2) / i2 + 0.5 * (d3 - d4) / (i2 + 1);
			}
//			kappa *= 180/(ONEPI*dmax);
			kappa /= ONEPI;
//			cdSource->SetPhaseAt( i1, FTOI((float )kappa));
			cdSource->SetRectangular(i1, (float )cda[i1], (float )kappa);
		}
	}
	else
	{
		dtime = m_fTime / 1000;
		for ( i=0; i <ncount; i++)
			{
							// now add in the new amount of phase (time * frequency == total cycles)
			fphase = (float )(360 * dtime * cdSource->DataAt( dataFreq, i) );
			fphase += cdSource->DataAt(dataPhase, i);
			fphase -= 360 * (int )( fphase / 360);
			if ( fphase > 180)
				fphase -= 360;
			else
			if ( fphase < -180)
				fphase += 360;

			cdSource->SetPhaseAt( i, FTOI(fphase));
			}
	}
	if ( m_bRemoveExcess && ncount > 5)
		{
		float fr, fi;
		float fra, fia;

		for ( i=0; i <ncount; i++)
			{
			cdSource->GetRectangular( i, &fr, &fi);
			fra = -fi;
			fia = fr;			// 90 degree phase shift
			fr += fra;
			fi += fia;
			cdSource->SetRectangular( i, fr, fi);
			}
		}

#endif

	return 0;
}

UINT CXformDelay::GetDialog(void)		// get the dialog id
{
	return IDD_XCADD;
}
/////////////////////////////////////////////////////////////////////////////
//				CXformMergePort
//					MergePort two datasets.....
/////////////////////////////////////////////////////////////////////////////
CXformMergePort::CXformMergePort( CObject *cTarget) : CXtransform( cTarget)		// must be named and in the tree
{

}
CXformMergePort::~CXformMergePort()
{
}

void CXformMergePort::SetParameters( DWORD dwDriver, DWORD dwPort, float fPiston, float fPort)
{

	m_dwDriver = dwDriver;
	m_dwPort = dwPort;
	m_fPistonArea = fPiston;
	m_fPortArea = fPort;
}


int CXformMergePort::DoOperation( CNamed *cdDest )	// xeq xform
{
CDataSet *ptarget = (CDataSet *)cdDest;
CDataSet *pdriver;
CDataSet *pport;
CFolder *proot;
int i, ncount;
float freq;
ZComplex zcdriver, zcport;
double ddiv;

	proot = ptarget->GetRootObject();

	pdriver = (CDataSet *)proot->FindByID( m_dwDriver);
	pport = (CDataSet *)proot->FindByID( m_dwPort);

	ASSERT( pport && pdriver);
	if ( (! pport) || !pdriver)
		return 1;			// nothing there...

	ASSERT( pport->IsType( ntDataSet, uomFreq));
	ASSERT( pdriver->IsType( ntDataSet, uomFreq));

	if ( ! pport->IsType( ntDataSet, uomFreq))
	{
		::AfxMessageBox( IDERR_BADDATA, MB_OK);
		return 1;
	}
	if ( ! pdriver->IsType( ntDataSet, uomFreq))
	{
		::AfxMessageBox( IDERR_BADDATA, MB_OK);
		return 1;
	}

	ptarget->CopyHeader( pdriver);

	ptarget->SetUOM( uomFreq);
	ptarget->SetDOM( uomDbw);
	ptarget->SetSize( pdriver->GetCount());	// same number of points as driver

	ncount = ptarget->GetCount();

	ddiv = sqrt(m_fPortArea / m_fPistonArea);		// use effective diameter of each

	CreateProgressBar( IDS_STATCOMBINE, 100);

	for ( i=0; i <ncount; i++)
		{
		if ( 0 == ( i % 100))
			ShowProgressBar( (100 * i) / ncount);

		freq = ptarget->DataAt( dataFreq, i);		// get current freq

		pdriver->GetRectangular( i, &zcdriver);
		pport->GetRectangularAt( freq, &zcport);

		zcport *= ddiv;

		zcdriver += zcport;

		ptarget->SetRectangular( i, (float )zcdriver.XValue(), (float )zcdriver.YValue());
		}			// end of for loop

	{
	CString csform;
		csform.GetBuffer(1024);	// this could be pretty long
		csform.Format( IDS_MERGEDESC, (LPCSTR )pport->GetName(), (LPCSTR )pdriver->GetName() );
	ptarget->SetDescription( csform);
	}




	CloseProgressBar( );

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
//				CXformCombine
//					combine two datasets.....
/////////////////////////////////////////////////////////////////////////////
CXformCombine::CXformCombine( CObject *cTarget, CObject *cOther) : CXbinary( cTarget, cOther)		// must be named and in the tree
{

}
CXformCombine::~CXformCombine()
{
}

UINT CXformCombine::DoDialog( void )		// xeq dbox
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
CDlgXcAdd cdlg;
UINT uout;

				// fill the function with defaults for this dataset
	cdlg.m_dwSource = cdSource->GetID();			// so name can be filled in, and uom found
	cdlg.m_pRoot = (CFolder *)cdSource->GetRootObject();

	uout = cdlg.DoModal();

	if ( IDOK == uout)
		{
		SetOther( cdSource->FindByID(cdlg.m_dwPicked) );
		m_nOperation = cdlg.m_nOperation;
		}

	return uout;

}

// -----------------------------------------------------------------
//	ExecuteCombine	global function...
// -----------------------------------------------------------------

void	ExecuteCombine( CDataSet *cdTarget, CDataSet *cdOther, int nOperation)
{
int i, ncount;
float freq;
float fdat, fphase;
double damp, ddat, dphase;

	ncount = cdTarget->GetCount();

	CreateProgressBar( IDS_STATCOMBINE, 100);

	if ( nOperation == 0 || nOperation == 1)		// add or subtract
		{
		for ( i=0; i <ncount; i++)
			{
			if ( 0 == ( i % 100))
				ShowProgressBar( (100 * i) / ncount);

			freq = cdTarget->DataAt( dataFreq, i);		// get current freq

			ddat = cdTarget->DataValueAt( i, 1);
			dphase = cdTarget->PhaseValueAt(i);
			fdat = cdOther->DataValueAt( freq, 1);	// use freq in case of differing orgs
			fphase = cdOther->PhaseValueAt(freq );

			switch( nOperation)
				{
				case 0 :			// add
					{
					double dp1, dp2;
						dp1 = dphase * (ONEPI / 180);
						dp2 = fphase * (ONEPI / 180);
					double dx, dy;
						dx = ddat * cos(dp1) + fdat * cos(dp2);
						dy = ddat * sin(dp1) + fdat * sin(dp2);
						damp = sqrt( dx * dx + dy * dy);
						dphase = atan2( dy , dx) / (ONEPI / 180);
					}
					break;

				case 1 :			// subtract
					{
					double dp1, dp2;
						dp1 = dphase * (ONEPI / 180);
						dp2 = fphase * (ONEPI / 180);
					double dx, dy;
						dx = ddat * cos(dp1) - fdat * cos(dp2);
						dy = ddat * sin(dp1) - fdat * sin(dp2);
						damp = sqrt( dx * dx + dy * dy);
						dphase = atan2( dy , dx) / (ONEPI / 180);
					}
					break;
				default :
					_ASSERT(0);
					damp = 0.0;		// to remove the warning
					break;
				}
			cdTarget->SetAbsolute( i, (float )damp, (float )dphase);
			}			// end of for loop
		}				// endif add or subtract
	else
		{
		DATAMSR dom = cdTarget->GetDOM();	// unit of measure for source
						// if both source and other are db, use that
		if ( dom == cdOther->GetDOM() && (dom == uomDbw || dom == uomDbv) )
			{
			for ( i=0; i <ncount; i++)
				{
				if ( 0 == ( i % 100))
					ShowProgressBar( (100 * i) / ncount);
				freq = cdTarget->DataAt( dataFreq, i);		// get current freq

				ddat = cdTarget->DataValueAt( i, 0);
				dphase = cdTarget->PhaseValueAt(i, 0);
				fdat = cdOther->DataValueAt( freq, 0);		// don't use I, use frequency
				fphase = cdOther->PhaseValueAt(freq, 0 );

				switch( nOperation)
					{
					case 2 :			// multiply
						{
						ddat += fdat;
						dphase += fphase;
						}
						break;
					case 3 :			// divide
						{
						ddat -= fdat;
						dphase -= fphase;
						}
						break;
					}
				if ( dphase > 180)
					dphase -= 360;
				else if ( dphase < -180)
					dphase += 360;
				cdTarget->SetDataAt( i, FTOI(ddat), FTOI(dphase));
				}			// end of for loop
			}
		else				// not log-log
			{
			for ( i=0; i <ncount; i++)
				{
				if ( 0 == ( i % 100))
					ShowProgressBar( (100 * i) / ncount);
				freq = cdTarget->DataAt( dataFreq, i);		// get current freq

				ddat = cdTarget->DataValueAt( i, 1);
				dphase = cdTarget->PhaseValueAt(i, 0);
				fdat = cdOther->DataValueAt( freq, 1);
				fphase = cdOther->PhaseValueAt(freq, 0 );

				switch( nOperation)
					{
					case 2 :			// multiply
						{
						ddat *= fdat;
						dphase += fphase;
						}
						break;
					case 3 :			// divide
						{
						if ( fdat)
							ddat /= fdat;
						if ( fphase)
							dphase -= fphase;
						}
						break;
					}
				if ( dphase > 180)
					dphase -= 360;
				else if ( dphase < -180)
					dphase += 360;
				cdTarget->SetAbsolute( i, (float )ddat, (float )dphase);
				}			// end of for loop
			}
	}


	CloseProgressBar( );

}



int CXformCombine::DoOperation( void )	// xeq xform
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
CDataSet *cother = (CDataSet *)GetOther();

//	{
//	CString csform, cres;
//		csform.GetBuffer(1024);	// this could be pretty long
//		cres.Format( "%d", m_nOperation);
//		csform.Format( IDS_COMBINEDESC, (LPCSTR )cdSource->GetName(), (LPCSTR )cother->GetName(), (LPCSTR )cres);
//	cdnew->SetDescription( csform);
//	}

	::ExecuteCombine( cdSource, cother, m_nOperation);

	return 0;
}

UINT CXformCombine::GetDialog(void)		// get the dialog id
{
	return IDD_XCADD;
}


/////////////////////////////////////////////////////////////////////////////
//				CXformDistort
//					Calculate the distortion in cOther and place into cTarget
/////////////////////////////////////////////////////////////////////////////
CXformDistort::CXformDistort( CObject *cTarget) : CXtransform( cTarget)		// must be named and in the tree
{

}
CXformDistort::~CXformDistort()
{
}

int CXformDistort::DoOperation( CNamed *cDest )	// xeq xform
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
CDataSet *cdest = (CDataSet *)cDest;
int i, ncount;
double fdat;
double damp, ddat, dphase;
int nfinal;

	cdest->CopyHeader( cdSource);
	cdest->SetDOM( uomVolts);			// no data alteration

	ncount = cdSource->GetCount();
	nfinal = cdSource->FreqToIndex( 1.95f * m_fCenterFreq);

	fdat = cdSource->Maximum( dataAmp);		// the generator output
	fdat = cdSource->ConvertToFormat( (float )fdat, uomVolts) / 100; // in percent

	cdest->SetSize( ncount - nfinal);
	cdest->SetStart( cdSource->DataAt( dataFreq, nfinal) );

	for ( i=nfinal; i <ncount; i++)
		{
		ddat = cdSource->DataValueAt( i, 1);		// and data value (absolute)
		dphase = cdSource->PhaseValueAt(i, 0 );

		damp = ddat / fdat;

		cdest->SetAbsolute( i-nfinal, (float )damp, (float )dphase);
		}			// end of for loop

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
//				CXformIntermod
//					Calculate the Intermodion in cOther and place into cTarget
/////////////////////////////////////////////////////////////////////////////
CXformIntermod::CXformIntermod( CObject *cTarget) : CXtransform( cTarget)		// must be named and in the tree
{

}
CXformIntermod::~CXformIntermod()
{
}

int CXformIntermod::DoOperation( CNamed *cDest )	// xeq xform
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
CDataSet *cdest = (CDataSet *)cDest;

int i, ncount;
double fdat;
double damp, ddat, dphase;
int nfinal;

	cdest->CopyHeader( cdSource);
	cdest->SetDOM( uomVolts);			// no data alteration

	ncount = cdSource->GetCount();
	nfinal = cdSource->FreqToIndex( 0.98f * m_fCenterFreq);

	fdat = cdSource->Maximum( dataAmp, (float )(.9 * m_fCenterFreq), cdSource->Maximum( dataFreq) );
	fdat = cdSource->ConvertToFormat( (float )fdat, uomVolts) / 100;

	cdest->SetSize( nfinal);

	for ( i=0; i <nfinal; i++)
		{
		ddat = cdSource->DataValueAt( i, 1);
		dphase = cdSource->PhaseValueAt(i, 0 );

		damp = ddat / fdat;

		cdest->SetAbsolute( i, (float )damp, (float )dphase);
		}			// end of for loop

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
//				CXformImpedance
//					Impedance two datasets.....
/////////////////////////////////////////////////////////////////////////////
CXformImpedance::CXformImpedance( CObject *cTarget, CObject *cOther) : CXtBinary( cTarget, cOther)
{
	m_fResistor = 1.0f;
	m_fSeriesRes = 0.0f;
	m_fInputRes = 20000.0f;
	m_fInputCap = 0.0f;

}

CXformImpedance::~CXformImpedance()
{
}

void	CXformImpedance::SetParms( TESTMSR *tm)
{
	m_fResistor = tm->fResistor;
	m_fSeriesRes = tm->fSeriesRes;
	m_fInputRes = tm->fInputRes;
	m_fInputCap = tm->fInputCap;
}


int CXformImpedance::DoOperation( CNamed *cdDest )	// xeq xform
{
CDataSet *cdSource = (CDataSet *)FindTargetObject();
CDataSet *cdnew = (CDataSet *)cdDest;
int i, ncount;
float freq;
CDataSet *ccalib = (CDataSet *)GetOther();
ZComplex zc, za;
ZComplex zres, zcap;

	{
	CString csform, cres;
		csform.GetBuffer(1024);	// this could be pretty long
		cres.Format( "%f", m_fResistor);
		csform.Format( IDS_IMPEDDESC, (LPCSTR )cdSource->GetName(), (LPCSTR )ccalib->GetName(), (LPCSTR )cres);
	cdnew->SetDescription( csform);
	}

	cdnew->SetUOM( uomOhms);
	cdnew->SetDOM( uomVolts);		// 1-1
	cdnew->SetStart( cdSource->GetStart());
	cdnew->SetDelta( cdSource->GetDelta());

	CreateProgressBar( IDS_STATCALC, 100);

	ncount = cdSource->GetCount();
	cdnew->SetSize( ncount);

	zres.SetRectangular( m_fInputRes, 0.0f);

	for ( i=0; i <ncount; i++)
		{
		if ( 0 == ( i % 100))
			ShowProgressBar( (100 * i) / ncount);
		freq = cdSource->DataAt( dataFreq, i);		// get current freq

		cdSource->GetRectangularAt( freq, &zc);
		ccalib->GetRectangularAt( freq, &za);
							// perform the operation since v1 / r1 == v2 / r2 (constant current
		zc = zc / (za - zc);	// get the voltage ratios (v2 / v1 == r2 / r1)
		zc *= m_fResistor;		// now * r1
								// now remove the parallel R/C input circuit
								// x = X * Z / X + Z where Z = r,c parallel, x = measured, X = unknown
								// xX + xZ = X*Z ;  xX - ZX = -xZ ; X = -xZ / (x - Z) ; X = xZ / (Z - x)
		if ( m_fInputCap > 0.0f)
			{
			zcap.SetRectangular( 0.0f, -1 / (2 * ONEPI * freq * m_fInputCap) );
			za = zres | zcap;
			}
		else
			za = zres;
								// ... X = xZ / (Z - x)
		za = zc * za / ( za - zc);
								// remove series resistance
		zc.SetRectangular( m_fSeriesRes, 0);
		za -= zc;
								// that should be it...
		cdnew->SetRectangular( i, (float )za.XValue(), (float )za.YValue() );
		}

	CloseProgressBar();

	return 0;
}

