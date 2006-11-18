// speaker.cpp : implementation of the CEnclosureArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include "Enclosur.h"

#include "Audtedoc.h"
#include "DataSet.h"
#include "Driver.h"
#include "Chart.h"

#include "zFormEdt.h"
#include "dlgEnclo.h"

#include "complex.h"
#include "math.h"

#include "opitem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define NRESPONSES 5

/////////////////////////////////////////////////////////////////////////////
// CEnclosure

IMPLEMENT_SERIAL(CEnclosure, CGraphed, VERSIONABLE_SCHEMA | 232)


/////////////////////////////////////////////////////////////////////////////
// CEnclosure construction/destruction

static  void init_Chamber(CHAMBER* pCh)
{
	pCh->bUseChamber = FALSE;

	pCh->bPIsCircle = TRUE;
	pCh->bUsePort = FALSE;

	pCh->wDrivers = 1;
	pCh->bParallel = TRUE;
	pCh->fDriverRes = 0.0f;			// no resistance, parallel, 1 driver
	pCh->wPorts = 1;				// and 1 port
        
	pCh->fVolume = 0.01f;
	pCh->fPLength = .03f;
	pCh->fPRadius = .03f;
	pCh->fPHeight = .02f;
	pCh->fPWidth = .02f;
	pCh->fQLeak = 7.0f;
	pCh->fQDamp = 100.0f;
	pCh->fQPort = 100.0f;
	pCh->fSeriesRes = 0.0f;

	pCh->dwDriver = 0;
}

CEnclosure::CEnclosure() : m_cCham1(), m_cCham2()
{
	m_dwResponse = 0;
	m_bInherit = FALSE;
	m_fStart = 20.0f;
	m_fDelta = 1.0f;
	m_nPoints = 980;		// to end at 1k

	m_pTrial = NULL;

	init_Chamber( &m_cCham1);
	m_cCham1.bUseChamber = TRUE;
	init_Chamber( &m_cCham2);
	m_cCham2.bUseChamber = FALSE;

}

CEnclosure::~CEnclosure()
{

}

/////////////////////////////////////////////////////////////////////////////
// CEnclosure serialization

static void serial_Chamber( CArchive& ar, CHAMBER *pCh, int nSchema)
{
	if (ar.IsStoring())
		{		// storing code here
		ar <<	(WORD )pCh->bUseChamber;
		ar <<	(WORD )pCh->bPIsCircle;
		ar <<	(WORD )pCh->bUsePort;

		ar <<	pCh->wDrivers;
		ar <<	(WORD )pCh->bParallel;
		ar <<	pCh->fDriverRes;

		ar <<	pCh->wPorts;
            
		ar <<	pCh->fVolume;
		ar <<	pCh->fPLength;	
		ar <<	pCh->fPRadius;
		ar <<	pCh->fPHeight;
		ar <<	pCh->fPWidth;
		ar <<	pCh->fQLeak;
		ar <<	pCh->fQDamp;
		ar <<	pCh->fQPort;
		ar <<	pCh->fSeriesRes;

		ar << 	pCh->dwDriver;
		}
	else
	{
	WORD w;
			// loading code here 
		ar >>	w; pCh->bUseChamber = w ? true : false;
		ar >>	w; pCh->bPIsCircle = w ? true : false;
		ar >>	w; pCh->bUsePort = w ? true : false;
            
		if ( 231 <=  nSchema)			// with 231 add # of drivers
		{
			ar >> pCh->wDrivers;
			ar >> w; pCh->bParallel = w ? true : false;
			ar >>	pCh->fDriverRes;
		}
		else
		{
			pCh->wDrivers = 1;
			pCh->bParallel = TRUE;
			pCh->fDriverRes = 0.0f;
		}

		if ( 232 <= nSchema)
		{
			ar >> pCh->wPorts;
		}
		else
		{
			pCh->wPorts = 1;
		}

		ar >>	pCh->fVolume;
		ar >>	pCh->fPLength;	
		ar >>	pCh->fPRadius;
		ar >>	pCh->fPHeight;
		ar >>	pCh->fPWidth;
		ar >>	pCh->fQLeak;
		ar >>	pCh->fQDamp;
		ar >>	pCh->fQPort;
		ar >>	pCh->fSeriesRes;

		ar >> 	pCh->dwDriver;
	}
}

// ---------------------------------------------------------------------------------------
// ---------		Serialize
// ---------------------------------------------------------------------------------------

void CEnclosure::Serialize(CArchive& ar)
{
DWORD dw;

	CGraphed::Serialize( ar);

	serial_Chamber( ar, &m_cCham1, GetSchema());
	serial_Chamber( ar, &m_cCham2, GetSchema());

	if (ar.IsStoring())
		{		// storing code here
		dw = m_bInherit; ar << dw;
		ar << m_fStart;

		ar << m_fDelta;
		dw = m_nPoints; ar << dw;
		}
	else			// loading
	{
		if ( 230 <=  GetSchema())
			{								// loading code here 
			ar >> dw; m_bInherit = dw ? true : false;
			ar >> m_fStart;
			ar >> m_fDelta;
			ar >> dw; m_nPoints = dw; 
			}
		else
			{		// default for old datasets
			m_bInherit = FALSE;
			m_fStart = 20.0f;
			m_fDelta = 1.0f;
			m_nPoints = 980;		// to end at 1k
			}
	}


}

// ---------------------------------------------------------------------------------------
// ---------		EditProperties
// ---------------------------------------------------------------------------------------

int CEnclosure::EditProperties(CWnd *pParent, CObject *cSubject)	// bring up properties dbox
{
CDlgEnclosure cgen( pParent);


	cgen.UseObject( this);

	if ( IDOK == cgen.DoModal())
		{
		CEnclosure *cnew = (CEnclosure *)this->Duplicate();
		cgen.SetObject( cnew);
		SetNewProperties( cnew);
		}

	return 0;		
}

 // ---------------------------------------------------------------------------------------
// ---------		SetNewProperties
// ---------------------------------------------------------------------------------------

int CEnclosure::SetNewProperties(CNamed *cNewObject)	// bring up properties dbox
{
COpCustom *copmain = new COpCustom( this);
CEnclosure *penc;

		copmain->SetNameID( IDOP_CHANGE);
		copmain->QueueAndDo( );

		COpChange *cop = new COpChange( this, cNewObject);
		copmain->PrivateQueue( cop);	// this changes the tree and so OpBuild fails

		penc = (CEnclosure *)cop->GetTreedObject();		// get the object in the tree

		penc->OpBuildDataSets( copmain);

		penc->UpdateViews();

	return 0;		
}



/////////////////////////////////////////////////////////////////////////////
// CEnclosure diagnostics

#ifdef _DEBUG
void CEnclosure::AssertValid() const
{
	CGraphed::AssertValid();
}

void CEnclosure::Dump(CDumpContext& dc) const
{
	CGraphed::Dump(dc);
}

#endif //_DEBUG


// ---------------------------------------------------------------------------------------
// ---------		Duplicate
// ---------------------------------------------------------------------------------------

CNamed *CEnclosure::Duplicate(void )
{
CEnclosure *cn = new CEnclosure();

	*cn = *this;
	return cn;
}


				// operators
// ---------------------------------------------------------------------------------------
// ---------		operator=
// ---------------------------------------------------------------------------------------

CEnclosure &CEnclosure::operator=(const CEnclosure &cIn)
{
CNamed &cin = (CNamed &)cIn;

	*this = cin;
 	return *this;
}

CNamed &CEnclosure::operator=(const CNamed &cIn)
{
CEnclosure &cin = (CEnclosure &)cIn;

	CGraphed::operator=( cIn);

	m_dwResponse = cin.m_dwResponse;

	m_cCham1 = cin.m_cCham1;
	m_cCham2 = cin.m_cCham2;
	m_fDelta = cin.m_fDelta;
	m_fStart = cin.m_fStart;
	m_nPoints = cin.m_nPoints;
					// don't copy the id #
 	return *this;
}

// ---------------------------------------------------------------------------------------
// ---------		ConvertMultiple
// ---------------------------------------------------------------------------------------
void CEnclosure::ConvertMultiple( DRIVEPARM &dP, DRIVEEQUIV &dQ, int iDrive, bool bParallel)
{

	if ( iDrive == 1)
		return;			// do nothing if single driver

	dP.fPistonArea *= iDrive;	// effective piston area
	dP.fVas *= iDrive;					// effective compliance

	if ( bParallel)
	{
		dP.fLe /= iDrive;		// inductance
		dP.fRe /= iDrive;		// dc resistance
		dP.fSensitivity *= iDrive;	// sensitivity in w/m
		dP.fDCRes /= iDrive;		// DC resistance???

		dQ.fRe /= iDrive;
		dQ.fL1a /= iDrive;
		dQ.fR1 /= iDrive;
		dQ.fL1b /= iDrive;
		dQ.fR2 /= iDrive;
		dQ.fL2 /= iDrive;
		dQ.fC2 *= iDrive;
	}
	else
	{
		dP.fLe *= iDrive;		// inductance
		dP.fRe *= iDrive;		// dc resistance
		dP.fSensitivity /= iDrive;	// sensitivity in w/m
		dP.fDCRes *= iDrive;		// DC resistance???
		dP.fPe *= iDrive * iDrive;		// maximum power input

		dQ.fRe *= iDrive;
		dQ.fL1a *= iDrive;
		dQ.fR1 *= iDrive;
		dQ.fL1b *= iDrive;
		dQ.fR2 *= iDrive;
		dQ.fL2 *= iDrive;
		dQ.fC2 /= iDrive;
	}

}



// ---------------------------------------------------------------------------------------
// ---------		CalcResponse
// ---------------------------------------------------------------------------------------

BOOL CEnclosure::CalcResponse( CNamed **cDests)
{

	if ( ! m_cCham1.dwDriver)
		return FALSE;

CDataSet *cData = (CDataSet *)cDests[0];
CDataSet *cCone = (CDataSet *)cDests[1];
CDataSet *cDelay = (CDataSet *)cDests[2];
CDataSet *cTransient = (CDataSet *)cDests[3];
CDataSet *cImpedance = (CDataSet *)cDests[4];
int ncount;
int i;
ZComplex zcalc, ztest;
ZComplex zc;
ZComplex ztemp;
float fstart;
double dfreq;
float fdelta;
double drat, dlmas, dccas;
double dral, drab, dccab, dlmap, drap;
double dmaximp = 0.0;
// double c = 345;
// double p0 = 1.18;
double c = 344.6690;		// speed of sound in air, per JBL SpeakerShop
double p0 = 1.1955;
CHAMBER *pCh = &m_cCham1;
double dlastamp;
CDriver *cdrive = (CDriver *)FindByID( pCh->dwDriver);

	if ( ! cdrive)
		return FALSE;

	ASSERT ( ntDriver == cdrive->GetType());

DRIVEPARM dp = *cdrive->GetDriverParameters();
DRIVEEQUIV dq = *cdrive->GetDriverEquiv();

						// if we have multiple drivers, convert this (chamber 1)
	ConvertMultiple( dp, dq, pCh->wDrivers, pCh->bParallel);

	fstart = m_fStart;
	fdelta = m_fDelta;
	ncount = m_nPoints;
	if ( m_bInherit)
		{				// modify if we have a dataset
		DWORD dw = cdrive->GetFreeAir();
			if ( ! dw)
				dw = cdrive->GetImpedance();
			if ( ! dw)
				dw = cdrive->GetResponse();
			if ( dw)
				{
				CDataSet *cdata = (CDataSet *)FindByID( dw);
				if ( cdata)
					{
					fstart = cdata->Minimum( dataFreq);
					ncount = cdata->GetCount();
					fdelta = cdata->GetDelta();
					}
				}
		}

	dccas = (dp.fVas / (p0*c*c));
	drat = 1 / (2 * ONEPI * dp.fFs * dp.fQts * (dp.fRe + pCh->fSeriesRes) * dccas / dp.fRe);
	dlmas = 1 / ( 4 * ONEPI * ONEPI * dp.fFs * dp.fFs * dccas);
	dccab = pCh->fVolume / (p0*c*c);
	if ( pCh->bUsePort && pCh->fPRadius > 0)
		{
		dlmap = p0 * ( pCh->fPLength + 1.46 * pCh->fPRadius) / (ONEPI * pCh->fPRadius * pCh->fPRadius * pCh->wPorts);
		double dsq = sqrt( dccab / dlmap);		// square root of Ccab / Lmap
		drab = 1 / (pCh->fQDamp * dsq );
		dral = pCh->fQLeak / dsq;
		drap = 1 / (pCh->fQPort * dsq);
		}
	else
		{
		drab = 0;
		dral = 1000000000;
		drap = 0;
		dlmap = 100000000;			// very large...
		}

	if ( cData)
		{
		cData->SetStart( fstart);
		cData->SetDelta( fdelta);
		cData->SetUOM( uomFreq);
		cData->SetDOM( uomDbw);		// this will cause calculation of dbw for setrectangular
		cData->SetSize( ncount);
		}

	if ( cCone)
		{
		cCone->SetStart( fstart);
		cCone->SetDelta( fdelta);
		cCone->SetUOM( uomFreq);
		cCone->SetDOM( uomVolts);		// this will cause calculation of dbw for setrectangular
	 	cCone->SetSize( ncount);
		}

	if ( cDelay)
		{
		cDelay->SetStart( fstart);
		cDelay->SetDelta( fdelta);
		cDelay->SetUOM( uomFreq);
		cDelay->SetDOM( uomVolts);		// this will cause calculation of dbw for setrectangular
		cDelay->SetSize( ncount);
		}

	if ( cImpedance)
		{
		cImpedance->SetStart( fstart);
		cImpedance->SetDelta( fdelta);
		cImpedance->SetUOM( uomOhms);
		cImpedance->SetDOM( uomVolts);		// this will cause calculation of dbw for setrectangular
		cImpedance->SetSize( ncount);
 		}

	if ( cTransient)
		{
		cTransient->SetStart( fstart);
		cTransient->SetDelta( fdelta);
		cTransient->SetUOM( uomTime);
		cTransient->SetDOM( uomVolts);		// this will cause calculation of dbw for setrectangular
		cTransient->SetSize( ncount, 0);
 		}


	dlastamp = 0;

double dentry = 0.0;
double dstartphase = 0.0;
double dlastphase = 0.0;
double daddon = 0;

	for ( i=0; i<ncount; i++)
		{
		dfreq = 2 * ONEPI * (fstart + fdelta * i);
									// ccab group
		zcalc.SetRectangular( drab, -1 / (dfreq * dccab) );

		if ( pCh->bUsePort)
			{						// lmap group
			zc.SetRectangular( drap, dfreq * dlmap);
			zc = zc | zcalc;
			zcalc.SetRectangular( dral, 0);	// ral
			zcalc = zc | zcalc;
			}
									// now zcalc is the impedance of the three
		ztest = zcalc;					// save it
									// Rat + Lmas + Ccas
		zcalc.SetRectangular( drat, dfreq * dlmas - 1 / (dfreq * dccas) );
		zc = ztest + zcalc;			// this is the total effective impedance

		if ( cImpedance)
			{
			zcalc.SetRectangular( - drat * (1 - dp.fQes / dp.fQms), 0); // subtract off the imp
			zcalc = zcalc + zc;
			ztemp.SetRectangular( 1,0);
			ztemp = ztemp / zcalc;
			ztemp *= (100 * drat);		// make it within ranges?
			if ( dmaximp < ztemp.XValue())
				dmaximp = ztemp.XValue();			// get maximum impedance value
			cImpedance->SetRectangular( i, ztemp.XValue(), ztemp.YValue());		// current ~ reflected impedance
			}
		zcalc.SetRectangular( 1, 0);
		zcalc = zcalc / zc;			// current through the network
									// cone excursion is i(Rat)
		if ( cCone)
			{
			dentry = zcalc.Amplitude() / dfreq / dccas;	// normalize by dccas so in limit is 1
			cCone->SetRectangular( i, dentry, 0.0f);
			}

		zcalc *= ztest;				// voltage across ccab and lmap etc

		ztest.SetRectangular( drab, -1 / (dfreq * dccab) );		// ccab group again
		zcalc /= ztest;				// current through ccab group

									// transient response, derivate of current...
		if ( cTransient)
			{
			if ( i )
				{
				dentry = zcalc.Amplitude() - dlastamp;
				cTransient->SetDataAt( i, FTOI(10000 * drat * dentry));
				if ( i == 1)	// special case this
					{
					cTransient->SetDataAt( 0, FTOI(10000 * drat * dentry)); // repeat the result once
					}
				}

			dlastamp = zcalc.Amplitude();
			}

					// now - amp = i * f
					//		 phase = ip(i) + 90
					//		 cone excursion - i(Rat)/f

		dentry = zcalc.Amplitude() * dfreq * dlmas;		// normalize by dlmas so in limit is 1
		zcalc.SetPolar( dentry, zcalc.Phase() + 90 );
		if ( cData)
			cData->SetRectangular( i, zcalc.XValue(), zcalc.YValue());

					// now - amp = i * f
					//		 phase = ip(i) + 90
					//		 cone excursion - i(Rat)/f

					// now - amp = i * f
					//		 phase = ip(i) + 90
					//		 cone excursion - i(Rat)/f
		if ( i)
			{				// use daddon to handle abrupt phase jumps due to +- 180 stuff
			dentry = (zcalc.Phase() - dstartphase) + daddon;
			if ( (dentry - dlastphase) > 180 || (dentry-dlastphase) < 180)	// major shift
				{
				int j = (int )((dlastphase - dentry) / 180);	// # of cycles to add on
				daddon += 360 * j;
				dentry += 360 * j;
				}
			dlastphase = dentry;
			dentry /= fdelta * i;		// divide by delta frequency
			}
		else
			{
			dentry = 0;
			dstartphase = zcalc.Phase();
			dlastphase = dentry;
			}

		if ( cDelay)
			cDelay->SetRectangular( i, dentry, 0.0f);
		}

	if ( cImpedance)
	{			// adjust the impedance appropriately
		double dmult;
		double dfreq;

		dmult = (dq.fR2) / dmaximp;
		for ( i=0; i<ncount; i++)
			{
			dfreq = 2 * ONEPI * (fstart + fdelta * i);
			cImpedance->GetRectangular( i, &ztemp);

			ztemp *= dmult;
			zcalc.SetRectangular( dp.fRe + pCh->fSeriesRes, 0);
			ztemp += zcalc;

			zcalc.SetRectangular( 0, dfreq * dq.fL1a);
			zc.SetRectangular( dq.fR1, 0);
			zcalc = zc | zcalc;		// parallel them
			zc.SetRectangular( 0, dfreq * dq.fL1b);
			zcalc += zc;
//			dfreq = zc.XValue();
						// this is the inductive impedance
			ztemp += zcalc;		// add it to the estimate

			cImpedance->SetRectangular( i, ztemp.XValue(), ztemp.YValue());		// current ~ reflected impedance
			}
	}


	if ( cDelay && 1 < cDelay->GetCount() )
		cDelay->SetDataAt( 0, cDelay->GetDataAt(1));

	return TRUE;
}


// ---------------------------------------------------------------------------------------
// ---------		GetSuffix
// ---------------------------------------------------------------------------------------

void	CEnclosure::GetSuffix(CString& csDest, int nSuffix)	// get the filename suffix for building
{
char *suffix[NRESPONSES] = { ".Frequency Response", ".Cone Excursion", ".Group Delay", 
							 ".Transient Response", ".Impedance" };

	ASSERT( 0 <= nSuffix && nSuffix < NRESPONSES);
	csDest = suffix[nSuffix];
}

static void create_Datasets( CEnclosure *pSource, CDataSet *pData[])
{
CString suffix;
short i;
ENCLINFO enclose;

	CAudtestApp::GetEnclosureInfo( enclose);

	for ( i=0; i<NRESPONSES; i++)
		{

		BOOL bdo = FALSE;

		switch( i)
			{
			case 0 :		// frequency response
				bdo = enclose.bFreqResponse;
				break;
			case 1 :		// cone excursion
				bdo = enclose.bConeExcursion;
				break;
			case 2 :		// group delay
				bdo = enclose.bGroupDelay;
				break;
			case 3 :		// transient
				bdo = enclose.bTransient;
				break;
			case 4 :		// impedance
				bdo = enclose.bImpedance;
				break;
			default:
				ASSERT(0);
				break;
			}
		if ( bdo)
			{
			pSource->GetSuffix( suffix, i);
			CString csname = pSource->GetName() + suffix;
			pData[i] = (CDataSet *)pSource->CreateByName( csname, ntDataSet);
			}
		else
			pData[i] = NULL;
		}

}



// ---------------------------------------------------------------------------------------
// ---------		BuildTrialData
// ---------------------------------------------------------------------------------------

int	CEnclosure::BuildTrialData()
{
CEnclosure *cenc;

	{
	CAudtestDoc *pdoc = (CAudtestDoc *)GetDocument();		// get the current doc
	CFolder *pbase = pdoc->GetSystem();		// find the system folder
	if ( ! pbase)
		return 1;

	cenc = (CEnclosure *)pbase->CreateByName( "Compare", ntEnclosure);	// build compare enclosure
	if ( ! cenc)
		return 2;

	m_pTrial = cenc;						// save it for a while
	*m_pTrial = *this;						// make it a dup of this one, for now
	m_pTrial->SetName( "Compare");			// but name it compare
	m_pTrial->SetLastEdit();				// and it's new
	}

CDataSet *pcdata[NRESPONSES];

	create_Datasets( m_pTrial, pcdata);

	m_pTrial->m_dwResponse = 0;
	if ( m_pTrial->CalcResponse( (CNamed **)pcdata))			// we did it
		{
		if ( pcdata[0])
			m_pTrial->m_dwResponse = pcdata[0]->GetID();
		}

CSubChart *cch = (CSubChart *)GetChart();	// use this chart!

	if ( cch && pcdata[0] && ! cch->GetMember( pcdata[0]->GetID()) )		// we have a chart, but he isn't in it
		{
		cch->Attach( pcdata[0]->GetID(), TRUE);			// use the phase for this guy
		}

	return 0;

}

// ---------------------------------------------------------------------------------------
// ---------		ChangeTrialData
// ---------------------------------------------------------------------------------------

int	CEnclosure::ChangeTrialData()
{
CDataSet *pcdata[NRESPONSES];
int i;

	if ( ! m_pTrial)
		return 1;

	create_Datasets( m_pTrial, pcdata);

	m_pTrial->m_dwResponse = 0;
	if ( m_pTrial->CalcResponse( (CNamed **)pcdata))			// we did it
		{
		if ( pcdata[0])
			{
			m_pTrial->m_dwResponse = pcdata[0]->GetID();
			}
		}

	m_pTrial->UpdateViews();
	for ( i=0; i<NRESPONSES; i++)
		if ( pcdata[i])
			pcdata[i]->UpdateViews();

	UpdateViews();

	return 0;
}

// ---------------------------------------------------------------------------------------
// ---------		DeleteTrialData
// ---------------------------------------------------------------------------------------

void CEnclosure::DeleteTrialData()
{

}


// ---------------------------------------------------------------------------------------
// ---------		BuildDataSets
// ---------------------------------------------------------------------------------------

void	CEnclosure::BuildDataSets()
{
CDataSet *pcdata[NRESPONSES];
CSubChart *cch = (CSubChart *)GetChart();	// use this chart!
int i;

	create_Datasets( this, pcdata);

	if ( cch && pcdata[0] && ! cch->GetMember( pcdata[0]->GetID()) )		// we have a chart, but he isn't in it
		{
		cch->Attach( pcdata[0]->GetID(), TRUE);			// use the phase for this guy
		}

	m_dwResponse = 0;
	if ( CalcResponse( (CNamed **)pcdata))			// we did it
		{
		if ( pcdata[0])
			m_dwResponse = pcdata[0]->GetID();
		for ( i=0; i<NRESPONSES; i++)
			{
			if ( pcdata[i])
				pcdata[i]->UpdateViews();			// update anyone directly showing this
			}
		}

}

// undoable version of BuildDataSets()
// ---------------------------------------------------------------------------------------
// ---------		OpBuildDataSets
// ---------------------------------------------------------------------------------------

void	CEnclosure::OpBuildDataSets( void *cOpMain)	
{
CDataSet *pcdata[NRESPONSES];
CDataSet *pcnew[NRESPONSES];
CSubChart *cch = (CSubChart *)GetChart();
CString suffix;
short i;
COpMulti *copmain = (COpMulti *)cOpMain;
ENCLINFO enclose;
COpFindOrCreate *cop;

	CAudtestApp::GetEnclosureInfo( enclose);

	for ( i=0; i<NRESPONSES; i++)
		{

		BOOL bdo = FALSE;

		switch( i)
			{
			case 0 :		// frequency response
				bdo = enclose.bFreqResponse;
				break;
			case 1 :		// cone excursion
				bdo = enclose.bConeExcursion;
				break;
			case 2 :		// group delay
				bdo = enclose.bGroupDelay;
				break;
			case 3 :		// transient
				bdo = enclose.bTransient;
				break;
			case 4 :		// impedance
				bdo = enclose.bImpedance;
				break;
			default:
				ASSERT(0);
				break;
			}

		pcdata[i] = NULL;
		if ( bdo)
			{
			GetSuffix( suffix, i);
			cop = new COpFindOrCreate( this, GetName() + suffix, ntDataSet);
			if ( ! copmain->PrivateQueue( cop))
				pcdata[i] = (CDataSet *)cop->GetFound();
			}

		if ( pcdata[i])
			pcnew[i] = (CDataSet *)pcdata[i]->Duplicate();
		else
			pcnew[i] = NULL;
		}


	if ( cch && pcdata[0] && ! cch->GetMember( pcdata[0]->GetID()) )		// we have a chart, but he isn't in it
		{
		cch->Attach( pcdata[0]->GetID(), TRUE);			// use the phase for this guy
		}

	m_dwResponse = 0;
	if ( CalcResponse( (CNamed **)pcnew))			// we did it
		{
		COpCode *cop;
		if ( pcdata[0])
			m_dwResponse = pcdata[0]->GetID();
		for ( i=0; i<NRESPONSES; i++)
			{
			if ( pcdata[i])
				{
				cop = new COpChange( pcdata[i], pcnew[i]);		// old and new
				copmain->PrivateQueue( cop);
				pcdata[i]->UpdateViews();			// update anyone directly showing this
				}
			}
		}

}

// ---------------------------------------------------------------------------------------
// ---------		CreateChart
// ---------------------------------------------------------------------------------------

BOOL	CEnclosure::CreateChart( CNamed *cBase)			// build a new chart object to be graphed
{
CSubChart *cch;
					// ensure the response is still valid
	if ( m_dwResponse)
	{
		if ( ! GetRootObject()->FindByID( m_dwResponse))
			m_dwResponse = 0;		// nope start over
	}

					// build the chart
//	if ( m_dwResponse) 
		{				// we need some data
		BuildDataSets();
		}

	if ( m_dwResponse)
		{
		cch = new CSubChart();
		cch->SetRootObject( GetRootObject());			// since it doesn't get added to the tree
		cch->CreateDefault( GetName(), uomFreq);
		if ( m_dwResponse)
			cch->Attach( m_dwResponse, FALSE);			// use the phase for this guy
		SetChart( cch);
		delete cch;
		}
	else
		SetChart( NULL);		// delete any old chart

	return TRUE;
}



