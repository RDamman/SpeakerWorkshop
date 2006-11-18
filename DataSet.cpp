// speaker.cpp : implementation of the CDataSetArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dataset.h"
#include "dlgdatas.h"

#include "Chart.h"

#include "OpItem.h"
#include "complex.h"
#include "Folder.h"

#include "mmwave.h"
#include "math.h"
#include "time.h"

#include "SetLocale.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDataSet

IMPLEMENT_SERIAL(CDataSet, CGraphed,VERSIONABLE_SCHEMA |  226)


static int convert_FreqToIdx( float fFreq, float fStart, float fDelta, int nSize)
{
int i;

	if ( fFreq < fStart)		// not here
		i = 0;
	else if ( fFreq > (fStart + fDelta*(nSize-1)) )
		i = nSize - 1;
	else
		i = (int )floor( (fDelta/100 + fFreq - fStart) / fDelta);	// the fdelta/100 is for rounding errors

	return i;
}

/////////////////////////////////////////////////////////////////////////////
// CDataSet construction/destruction

CDataSet::CDataSet()   : m_ciData(), m_ciPhase()
{
	// TODO: add one-time construction code here
	SetSize(0, 1000);
	m_nDataUnit = uomDbw;
	m_nBaseUnit = uomTime;
	m_fDelta = 0.0f;
	m_fStart = 0.0f;
	m_nIdGenerator = 0;
	::time(&m_tTime);
}

// --------------------------------------------------------------
// --------------------------------------------------------------
CDataSet::~CDataSet()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDataSet serialization

void CDataSet::Serialize(CArchive& ar)
{
DWORD dw;
WORD w;

	CGraphed::Serialize( ar);
	m_ciData.Serialize(ar);		// the data itself
	m_ciPhase.Serialize(ar);		// the data itself

	if (ar.IsStoring())
	{								// storing code here
		ar << m_tTime;
		dw = (DWORD )m_nIdGenerator; ar << dw;
		ar << m_fStart;
		ar << m_fDelta;
		w = (WORD )GetUOM(); ar << w;
		w = (WORD )GetDOM(); ar << w;
	}
	else
	{								// loading code here 
		ar >>  m_tTime;
		ar >>  dw; m_nIdGenerator = (int )dw;
		ar >> m_fStart;
		ar >> m_fDelta;
		ar >> w; SetUOM( (UNITMSR )w);
		ar >> w; SetDOM( (DATAMSR )w);
	}
}

// --------------------------------------------------------------
// --------------------------------------------------------------
int   CDataSet::EditProperties(CWnd *pParent, CObject *  )	// bring up properties dbox
{
CDlgDataset cdlg( pParent);
int nresult;

	DialogInit( (CDialog *) &cdlg);

	cdlg.PreDialog( this);

	nresult = cdlg.DoModal();
	if ( IDOK == nresult)
		{
		COpCode *cop;
		CDataSet *cgnew = (CDataSet *)Duplicate();		// make a copy of "this"
		if ( cgnew)
			{
			cdlg.PostDialog( cgnew);
			cop = new COpChange( this, cgnew);
			cop->QueueAndDo( );
			return 0;
			}
		}

	return nresult;
		
}

void CDataSet::DialogInit( CDialog *pcDlg)			// initialize the dialog (callback when windows are built)
{
CDlgDataset *cdlg = (CDlgDataset *)pcDlg;

	cdlg->m_pcCaller = this;
}


/////////////////////////////////////////////////////////////////////////////
// CDataSet diagnostics

#ifdef _DEBUG
void CDataSet::AssertValid() const
{
	CGraphed::AssertValid();
}

void CDataSet::Dump(CDumpContext& dc) const
{
	CGraphed::Dump(dc);
}

#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
//			commands

// --------------------------------------------------------------
//		SetAbsolute
//			this assumes the input data is non-logarithmic and
//			converts it if necessary to the current DOM
// --------------------------------------------------------------
void CDataSet::SetAbsolute( int nCoord, float fAmp, float fPhase)
{
INT32 dwamp, dwphase;
float fd;
ZComplex zc;

	switch( GetDOM())
		{
		case uomDbw :
			if ( fAmp > 0)
				fd = (float )(20 * log10( fAmp));
			else
				fd = 0.0f;
			break;
		case uomDbv :
			if ( fAmp > 0)
				fd = (float )(10 * log10( fAmp));
			else
				fd = 0.0f;
			break;
		default:
			fd = fAmp;
			break;
		}
	dwamp = FTOI( fd);
	m_ciData.SetAt( nCoord, dwamp);

	if ( nCoord < m_ciPhase.GetSize())
		{
		fd = fPhase;
		dwphase = FTOI( fd);
		m_ciPhase.SetAt( nCoord, dwphase);
		}
}

// --------------------------------------------------------------
//		ConvertToFormat
//			this converts data to the desired DOM
//			from the current DOM
// --------------------------------------------------------------
double CDataSet::ConvertToFormat( float fAmp, DATAMSR nNewMsr)
{
double dd;

	dd = fAmp;
	switch( GetDOM())
		{
		case uomDbw :
			dd = pow(10.0, dd / 20);
			break;
		case uomDbv :
			dd = pow(10.0, dd / 10);
			break;
		default:
			break;
		}

	switch( nNewMsr)
		{
		case uomDbw :
			if ( dd > 0)
				dd = 20 * log10( dd);
			else
				dd = 0;
			break;
		case uomDbv :
			if ( dd > 0)
				dd = 10 * log10( dd);
			else
				dd = 0;
			break;
		default:
			break;
		}

	return dd;
}

// --------------------------------------------------------------
//		ConvertToFormat
//			this converts data to the desired DOM
//			from the current DOM
// --------------------------------------------------------------
int CDataSet::FreqToIndex( float fFreq)
{
	return convert_FreqToIdx( fFreq, GetStart(), GetDelta(), GetCount());
}

// --------------------------------------------------------------
//		SetRectangular
//			this assumes the input data is non-logarithmic and
//			converts it if necessary to the current DOM
// --------------------------------------------------------------
void CDataSet::SetRectangular( int nCoord, float fX, float fY)
{
INT32 dwamp, dwphase;
double fd;
ZComplex zc( fX, fY);

	fd = zc.Amplitude();
	switch( GetDOM())
		{
		case uomDbw :
			if ( fd > 0)
				fd = 20 * log10( fd);
			else
				fd = 0.0f;
			break;
		case uomDbv :
			if ( fd > 0)
				fd = 10 * log10( fd);
			else
				fd = 0.0f;
			break;
		default:
			break;
		}
	dwamp = FTOI( (float )fd);

	fd = zc.Phase();
	dwphase = FTOI( (float )fd);

	m_ciData.SetAt( nCoord, dwamp);
	if ( nCoord < m_ciPhase.GetSize())
		m_ciPhase.SetAt( nCoord, dwphase);
}

// --------------------------------------------------------------
//		GetRectangular
//			this assumes the input data is non-logarithmic and
//			converts it if necessary to the current DOM
// --------------------------------------------------------------
void CDataSet::GetRectangular( int nCoord, float *fX, float *fY)
{
INT32 dwamp, dwphase;
double fd, fangle;

	dwamp = m_ciData.GetAt( nCoord);
	dwphase = m_ciPhase.GetAt( nCoord);

	fd = ITOF( dwamp);			// get it in floating point

	switch( GetDOM())
		{
		case uomDbw :
			fd = pow(10.0, (fd / 20));
			break;
		case uomDbv :
			fd = pow(10.0, (fd / 10));
			break;
		default:
			break;
		}

				// now fd is in linear terms (e.g. volts)
	fangle = (ONEPI / 180) * ITOF ( dwphase);
	*fX = (float )(fd * cos( fangle));
	*fY = (float )(fd * sin( fangle));
}

void CDataSet::GetRectangular( int nCoord, ZComplex *zcDest)
{
float fx, fy;

	GetRectangular( nCoord, &fx, &fy);
	zcDest->SetRectangular( fx, fy);

}

// --------------------------------------------------------------
//		GetRectangularAt
//			this assumes the input data is non-logarithmic and
//			converts it if necessary to the current DOM
// --------------------------------------------------------------
void CDataSet::GetRectangularAt( float fFreq, float *fX, float *fY)
{
INT32 dwamp, dwphase;
float fd, fangle;
int ncoord;
float fdif;

	ncoord = convert_FreqToIdx( fFreq, GetStart(), GetDelta(), GetCount() );

	fdif = (fFreq - GetStart() - ncoord * GetDelta() ) / GetDelta();	// amount in between

	if ( (fdif <= 0) || ncoord == (GetCount()-1) )
		{
		dwamp = m_ciData.GetAt( ncoord);
		dwphase = m_ciPhase.GetAt( ncoord);
		fd = ITOF( dwamp);			// get it in floating point
		}
	else
		{  	// linearly interpolate to at least get close
		dwamp = (INT32 )(m_ciData.GetAt( ncoord) * ( 1 - fdif) + m_ciData.GetAt( ncoord+1) * fdif);
		fd = ITOF( m_ciPhase.GetAt( ncoord+1) - m_ciPhase.GetAt( ncoord) );
		if ( (fd > 180) || (fd < -180) )		// gone over 360 boundary, don't interpolate
			dwphase = m_ciPhase.GetAt( ncoord);
		else
			dwphase = (INT32 )(m_ciPhase.GetAt( ncoord) * ( 1 - fdif) + m_ciPhase.GetAt( ncoord+1) * fdif);
		fd = ITOF( dwamp);			// get it in floating point
		}

	switch( GetDOM())
		{
		case uomDbw :
			fd = pow(10.0f, (fd / 20));
			break;
		case uomDbv :
			fd = pow(10.0f, (fd / 10));
			break;
		default:
			break;
		}

				// now fd is in linear terms (e.g. volts)
	fangle = (ONEPI / 180) * ITOF ( dwphase);
	*fX = fd * cos( fangle);
	*fY = fd * sin( fangle);
}

void CDataSet::GetRectangularAt( float fFreq, ZComplex *zcDest)
{
float fx, fy;

	GetRectangularAt( fFreq, &fx, &fy);
	zcDest->SetRectangular( fx, fy);

}

// --------------------------------------------------------------
// --------------------------------------------------------------
void CDataSet::SetDataAt( int nCoord, INT32 dwAmp, INT32 dwPhase)
{
	m_ciData.SetAt( nCoord, dwAmp);
	m_ciPhase.SetAt( nCoord, dwPhase);
}


// --------------------------------------------------------------
// --------------------------------------------------------------
void CDataSet::SetDataAt( int nCoord, INT32 dwAmp)
{
	m_ciData.SetAt( nCoord, dwAmp);
}

// --------------------------------------------------------------
// --------------------------------------------------------------
void CDataSet::SetPhaseAt( int nCoord, INT32 dwAmp)
{
	m_ciPhase.SetAt( nCoord, dwAmp);
}


void  CDataSet::SetDataEasy( float fFreq, float fAmp, float fPhase)	// set it to a freq
{
int nindex;
int nc;
float fause, fpuse;

	nindex = (int )floor( (GetDelta()/100 + fFreq - GetStart()) / GetDelta());
	nc = GetCount();
	if ( nindex >= nc)					// it's a new one
	{
		int i;
		float fa = DataValueAt( nc-1, 0);		// get the data value
		float fp = PhaseValueAt( nc-1, 0);	// get the phase value

		for ( i=nc; i<nindex; i++)
		{
			fause = (fAmp - fa) / (1 + nindex - nc);
			fause *= 1 + i - nc;			// scale it
			fause += fa;

			fpuse = (fPhase - fp) / (1 + nindex - nc);
			fpuse *= 1 + i - nc;			// scale it
			fpuse += fp;

			AddData( FTOI( fause), FTOI( fpuse));
		}
		AddData( FTOI( fAmp), FTOI( fPhase));
	}
	else
	{
		SetDataAt( nindex, FTOI( fAmp), FTOI( fPhase));
	}

}



// --------------------------------------------------------------
// --------------------------------------------------------------
INT32 CDataSet::GetDataAt( int nCoord)
{
	if ( nCoord >= 0 && nCoord < m_ciData.GetSize())
		return m_ciData.GetAt( nCoord);

	return 0;
}

// --------------------------------------------------------------
//					GetPhaseAt
// --------------------------------------------------------------
INT32 CDataSet::GetPhaseAt( int nCoord)
{
	if ( nCoord >= 0 && nCoord < m_ciPhase.GetSize())
		return m_ciPhase.GetAt( nCoord);

	return 0;
}


// --------------------------------------------------------------
//					GetPhaseAt
// --------------------------------------------------------------
BOOL CDataSet::HasPhase( void)
{
	return ( 0 != m_ciPhase.GetSize() );
}

// --------------------------------------------------------------
//					DeleteLeft
// remove data from the left
// --------------------------------------------------------------
bool	CDataSet::DeleteLeft( int iCount)
{
float fstart = DataAt( dataFreq, iCount);
	SetStart( fstart);		// set it

	m_ciData.RemoveAt( 0, iCount);
	if ( m_ciPhase.GetSize())
	{
		m_ciPhase.RemoveAt( 0, iCount);
	}
	return true;
}

// --------------------------------------------------------------
//					DataValueAt
// --------------------------------------------------------------
float CDataSet::DataValueAt( int nCoord, int nMethod)		// extrapolate to a value
{
INT32 dw;
float fout;

	dw = GetDataAt( nCoord);
	fout = ITOF( dw);
	if ( nMethod & 1)			// use DOM to convert
		{
		switch( GetDOM() )
			{
			case uomDbw :
				fout = pow(10.0f, fout / 20);
				break;
			case uomDbv :
				fout = pow(10.0f, fout / 10);
				break;
			case uomVolts :
				break;
			case uomWatts :
				break;
			}
		}

 	return fout;
}

float CDataSet::DataValueAt( float fCoord, int nMethod)		// extrapolate to a value
{
int i;

	i = convert_FreqToIdx( fCoord, GetStart(), GetDelta(), GetCount() );

	return DataValueAt( i, nMethod);
}


// --------------------------------------------------------------
//					PhaseValueAt
// --------------------------------------------------------------
float CDataSet::PhaseValueAt( int nCoord, int nMethod)		// extrapolate to a value
{
INT32 dw;
float fout;

	dw = GetPhaseAt( nCoord);
	fout = ITOF( dw);
 	return fout;
}

float CDataSet::PhaseValueAt( float fCoord, int nMethod)		// extrapolate to a value
{
int i;

	i = convert_FreqToIdx( fCoord, GetStart(), GetDelta(), GetCount() );

	return PhaseValueAt( i, nMethod);

}

// --------------------------------------------------------------
//					Minimum( which)
// read a dataset from a file
// --------------------------------------------------------------
float CDataSet::Minimum(DATASEL ndWhich)
{
	if ( dataFreq == ndWhich)		// frequency
		return GetStart();
	else
		{
		INT32 imin, inow;
		int j;
		imin = INT_MAX;
		if ( GetCount())
			{
			for ( j=0; j < GetCount(); j++)
				{
				inow = ( ( dataAmp == ndWhich) ? m_ciData.GetAt(j) : m_ciPhase.GetAt(j) );
				if ( imin > inow)
					imin = inow;
				}

			return ITOF(imin);
			}	// endif getcount

		}

	return (float )0;
}


float CDataSet::Minimum(DATASEL ndWhich, float fStart, float fEnd)
{
int jmin, jmax;

	if ( dataFreq == ndWhich)		// frequency
		return GetStart();
	else
		{
		INT32 imin, inow;
		int j;

		jmin = convert_FreqToIdx( fStart, GetStart(), GetDelta(), GetCount() );
		jmax = convert_FreqToIdx( fEnd, GetStart(), GetDelta(), GetCount() );
		imin = INT_MAX;		// a big number

		if ( GetCount())
			{
			for ( j=jmin; j <= jmax; j++)
				{
				inow = ( ( dataAmp == ndWhich) ? m_ciData.GetAt(j) : m_ciPhase.GetAt(j) );
				if ( imin > inow)
					imin = inow;
				}

			return ITOF(imin);
			}	// endif getcount

		}

	return (float )0;
}


float CDataSet::Maximum(DATASEL ndWhich, float fStart, float fEnd)
{
int jmin, jmax;

	if ( ! GetCount())
		{
		if ( dataFreq == ndWhich)		// frequency
			return GetStart();
		else
			return (float )0;
		}

	if ( dataFreq == ndWhich)		// frequency
		return GetStart() + (GetCount()-1) * GetDelta();
	else
		{
		INT32 imax, inow;
		int j;
		imax = INT_MIN;		// a small number

		jmin = convert_FreqToIdx( fStart, GetStart(), GetDelta(), GetCount() );
		jmax = convert_FreqToIdx( fEnd, GetStart(), GetDelta(), GetCount() );

		for ( j=jmin; j <= jmax; j++)
			{
			inow = ( ( dataAmp == ndWhich) ? m_ciData.GetAt(j) : m_ciPhase.GetAt(j) );
			if ( imax < inow)
				imax = inow;
			}

		return ITOF(imax);
		}
}




// --------------------------------------------------------------
//					Maximum
// get max value
// --------------------------------------------------------------
float CDataSet::Maximum(DATASEL ndWhich)
{
	if ( ! GetCount())
		{
		if ( dataFreq == ndWhich)		// frequency
			return GetStart();
		else
			return (float )0;
		}

	if ( dataFreq == ndWhich)		// frequency
		return GetStart() + (GetCount()-1) * GetDelta();
	else
		{
		INT32 imax, inow;
		int j;
		imax = INT_MIN;

		for ( j=0; j < GetCount(); j++)
			{
			inow = ( ( dataAmp == ndWhich) ? m_ciData.GetAt(j) : m_ciPhase.GetAt(j) );
			if ( imax < inow)
				imax = inow;
			}

		return ITOF(imax);
		}
}

// --------------------------------------------------------------
// --------------------------------------------------------------
float CDataSet::DataAt( DATASEL ndWhich, int nCoord)
{
INT32 dw;

	switch( ndWhich)
		{
		case dataFreq:
			return GetStart() + nCoord * GetDelta();
		case dataAmp:
			dw = GetDataAt( nCoord);
			return ITOF(dw);
		case dataPhase:
			dw = GetPhaseAt( nCoord);
			return ITOF(dw);
		}
	return (float )0;
}



static DWORD get_Line( CFile& cIn, LPSTR szBuf, DWORD dwAvail)
{
int noff = 0;

	while( dwAvail && 1 != *szBuf)		// data left and not end of buffer
		{
			cIn.Read(szBuf,1);
			dwAvail--;
			if ( '\n' ==  *szBuf)
				{
				*szBuf = '\0';
				return dwAvail;
				}
			if ( noff || ! isspace( *szBuf))			// remove leading white space
			{
				szBuf++;
				noff = 1;			// we have a non-blank
			}
		}

	*szBuf = '\0';
	return dwAvail;			// sb 0

}

int CDataSet::AddData( INT32 nAmp, INT32 nPhase)
{

	m_ciData.Add( nAmp);
	return m_ciPhase.Add( nPhase);
}


int CDataSet::AddData( INT32 nAmp)
{
	return m_ciData.Add( nAmp);
}

void CDataSet::CopyHeader( CDataSet *cdSource)
{
	 m_fDelta = cdSource->m_fDelta;
	 m_fStart = cdSource->m_fStart;
	 m_nIdGenerator = cdSource->m_nIdGenerator;
	 m_tTime = cdSource->m_tTime;
	 m_nDataUnit = cdSource->m_nDataUnit;
	 m_nBaseUnit = cdSource->m_nBaseUnit;
}


// --------------------------------------------------------------
//					Import
// read a dataset from a file
// --------------------------------------------------------------
int CDataSet::Import( LPCSTR szFileName)
{
CFile file;
CFileException fe;
float fdelta = (float)-1;
float fstart = (float)-1;
DWORD dwleft;
char szbuf[200];
const char *szext;
int nread;

	memset( szbuf, 0, 200);
	szbuf[199] = (char)1;		// flag byte

	if (!file.Open(szFileName, 
					CFile::modeRead | CFile::shareDenyNone,
					&fe))
		{
		return 1;
		}


	if ( 3 < strlen( szFileName))
		szext = szFileName + strlen(szFileName) - 3;
	else
		szext = szFileName;

	TRY
	{						// for an frd file
	float freq, famp, fphase;
	CSetLocale csl( LC_ALL, 0);

	m_ciData.RemoveAll();
	m_ciPhase.RemoveAll();
	dwleft = file.GetLength();

	if ( ! stricmp( "imp", szext))		// imp time file
		{
		int ntotal;
		float fsample;
						// read line 1
		dwleft = get_Line( file, szbuf, dwleft);			// # of data points
		sscanf( szbuf, "%d", &ntotal);
		dwleft = get_Line( file, szbuf, dwleft);			// same as # data pts ???
		dwleft = get_Line( file, szbuf, dwleft);			// sampling freq
		sscanf( szbuf, "%f", &fsample);
		dwleft = get_Line( file, szbuf, dwleft);			// random "1"??

		while( dwleft && ntotal--)
			{
			dwleft = get_Line( file, szbuf, dwleft);
			if ( 1 == sscanf( szbuf, "%f", &famp))
				{
				famp *= 16384;			// make it more appropriate for us
				m_ciData.Add( FTOI(famp));
				}
			}
		file.Close();

		SetUOM(uomTime);
		SetDOM(uomVolts);			// absolute data
		SetStart( (float)0);
		SetDelta( (float )(1000 / fsample));	// ??? 1000 / fsample?
		}
	else
	if ( (! stricmp( "frd", szext))	||	// frd (frequency) file
		 (! stricmp( "zma", szext))  )	// zma (impedance)
		{	
		freq = 10.0f;
		famp = 1.0f;
		fphase = 0.0f;			// default if no data ever entered
						// read line 1
		for ( nread = 0; nread != 3; )
		{
			dwleft = get_Line( file, szbuf, dwleft);
			if ( dwleft)
			{
				if ( '*' != szbuf[0])		// it's not a comment
					nread = sscanf( szbuf, "%f %f %f", &freq, &famp, &fphase);
			}
			else
				nread =  3;		// abrupt stop
		}
		fstart = freq;
		m_ciData.Add( FTOI(famp));
		m_ciPhase.Add( FTOI(fphase));
		for ( nread = 0; nread != 3; )
		{
			dwleft = get_Line( file, szbuf, dwleft);
			if ( dwleft)
			{
				if ( '*' != szbuf[0])		// it's not a comment
					nread = sscanf( szbuf, "%f %f %f", &freq, &famp, &fphase);
			}
			else
				nread =  3;		// abrupt stop
			if (dwleft && ( freq == fstart))
				nread = 0;			// don't use it if it's the same dataline
		}

		fdelta = freq - fstart;
		SetStart( fstart);
		SetDelta( fdelta);

		SetDataEasy( freq, famp, fphase);

		while( dwleft && freq < 22050.0f)		// if it goes past 22k skip it
			{
			dwleft = get_Line( file, szbuf, dwleft);
			if ( 3 == sscanf( szbuf, "%f %f %f", &freq, &famp, &fphase))
				SetDataEasy( freq, famp, fphase);
			}
		file.Close();


		if ( ! stricmp( "frd", szext))		// frd (frequency) file
			{
//			float fmin, fmax, fact;
//			int i, ncount;
//				fmin = Minimum( dataAmp);
//				fmax = Maximum( dataAmp);	// get min-max to start changing
//				ncount = GetCount();
//			for (i=0; i<ncount; i++)
//				{
//				fact = ITOF( GetDataAt(i));
//				fact = 65536 * pow(10, (fact - fmax) / 20);		// convert to absolute data
//				SetDataAt( i, FTOI( fact));
//				}
			SetDOM(uomDbw);					// db power data
			SetUOM(uomFreq);
			}
		else
			{
			SetDOM(uomVolts);			// absolute data
			SetUOM(uomOhms);
			}
		}
	}
	CATCH_ALL(e)
	{
		file.Abort(); // will not throw an exception
		m_ciData.RemoveAll();
		m_ciPhase.RemoveAll();
		return 2;		// return an error, however
	}
	END_CATCH_ALL

				// it all worked, so continue


	 					// header elements common to all imports
	::time(&m_tTime);
	{
	CString csimp;

		csimp.Format( IDS_IMPORTED, szFileName, ctime( &m_tTime) );
		SetDescription( csimp);
	}

						// get file write time
	{
	CFileStatus cfs;

		CFile::GetStatus( szFileName, cfs);
		m_tTime = cfs.m_ctime.GetTime();			// creation date and time
	}

	return 0;

}

// --------------------------------------------------------------
//					Import
// read a dataset from a file
// --------------------------------------------------------------
int CDataSet::Export( LPCSTR szFileName)
{
CStdioFile file;
CFileException fe;
char szbufr[200];
int nsize;
int i;
CSetLocale csl( LC_ALL, 0);

	if (!file.Open(szFileName, 
					CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive,
					&fe))
		{
		return 1;
		}



	nsize = GetCount();

	TRY
	{						// for an frd file
	float freq, famp, fphase;

	switch( GetUOM())
		{
		case uomFreq :					// frequency file (frd)
			for ( i=0; i<nsize; i++)
				{
				famp = DataAt( dataAmp, i);
				freq = DataAt( dataFreq, i);
				fphase = DataAt( dataPhase, i);
				sprintf( szbufr, "%f %f %f\n", freq, famp, fphase);
				file.WriteString( szbufr);
				}
			break;
		case uomTime :					// time file (imp)
			if ( 4096 <= nsize)
				nsize = 4096;
			else
			if ( 2048 <= nsize)
				nsize = 2048;
			else
			if ( 1024 <= nsize)
				nsize = 1024;
			else
			if ( 512 <= nsize)
				nsize = 512;
			sprintf( szbufr, "%d\n", nsize);
			file.WriteString( szbufr);
			file.WriteString( szbufr);		// ?????
			sprintf( szbufr, "%15.12f\n", 1 / (GetDelta()/1000) );	// sampling rate
			file.WriteString( szbufr);
			sprintf( szbufr, "1\n");		// ????
			file.WriteString( szbufr);
			for ( i=0; i<nsize; i++)
				{
				INT32 in = GetDataAt( i);
				famp = ITOF( in );
					famp /= 32767;			// put it back into +-2 terms
				sprintf( szbufr, "%15.12f\n", famp);
				file.WriteString( szbufr);
				}
			strcpy( szbufr, GetName()+"\n" );
			file.WriteString( szbufr);
			sprintf( szbufr, "1\n");
			file.WriteString( szbufr);
			sprintf( szbufr, "          12:12:12  01/02/95\n");
			file.WriteString( szbufr);		// this should be date and time
			sprintf( szbufr, "0\n");		// now the starting marker			
			file.WriteString( szbufr);		// this should be date and time
			sprintf( szbufr, "%d\n", nsize-1);		// now the ending marker
			file.WriteString( szbufr);		// this should be date and time
			sprintf( szbufr, "1.0000000E+00\n");		// u must be kidding
			file.WriteString( szbufr);		// 
			break;
		case uomOhms :					// impedance file
			for ( i=0; i<nsize; i++)
				{
				famp = DataAt( dataAmp, i);
				freq = DataAt( dataFreq, i);
				fphase = DataAt( dataPhase, i);
				sprintf( szbufr, "%f %f %f\n", freq, famp, fphase);
				file.WriteString( szbufr);
				}
			break;
		default :
			break;						// ???
		}
	}
	CATCH_ALL(e)
	{
		file.Abort(); // will not throw an exception
		return 2;		// return an error, however
	}
	END_CATCH_ALL

	file.Close();

	return 0;

}



void CDataSet::GetFilter( CString& csExt, CString& csFilter)
{
	switch( GetUOM())
		{
		case uomFreq :
			csExt = "FRD";
			csFilter = "Freq Files (*.FRD)|*.FRD|All Files (*.*)|*.*||";
			break;
		case uomTime :
			csExt = "IMP";
			csFilter = "Time Files (*.IMP)|*.IMP|All Files (*.*)|*.*||";
			break;
		case uomOhms :
			csExt = "ZMA";
			csFilter = "Impedance Files (*.ZMA)|*.ZMA|All Files (*.*)|*.*||";
			break;
		default :
			csExt = "HUH";
			csFilter = "Impedance Files (*.ZMA)|*.ZMA|All Files (*.*)|*.*||";
			break;
		}
}



CNamed *CDataSet::Duplicate(void )
{
CNamed *cnew = new CDataSet();

	*cnew = *this;
	return cnew;
}


				// operators
CDataSet &CDataSet::operator=(const CDataSet &cIn)
{
CNamed &cin = (CNamed &)cIn;

	*this = cin;
 	return *this;
}


CNamed &CDataSet::operator=(const CNamed &cIn)
{
int i, nsize;
CDataSet &cin = (CDataSet &)cIn;

	CGraphed::operator=( cIn);

 					// don't copy the id #
	CopyHeader( &cin);

	nsize = cin.m_ciData.GetSize();
	if ( ! SetSize( nsize, cin.m_ciPhase.GetSize()))	// setsize worked
		{
		for ( i=0; i<nsize; i++)
			{
			m_ciData.SetAt( i, cin.m_ciData.GetAt(i) );
			}
		nsize = cin.m_ciPhase.GetSize();
		for ( i=0; i<nsize; i++)
			{
			m_ciPhase.SetAt(i, cin.m_ciPhase.GetAt(i) );
			}
		}

 	return *this;
}

#define NDETAIL 3

// --------------------------------------------------------------------
//		WalkValue
//				fOut is the frquency at which we're found
//			nChannel - which channel to walk
//			fValue - value to look for
//			fStart - starting frequency / time
//			fDelta - step size for searching
// --------------------------------------------------------------------
BOOL	CDataSet::WalkValue( float& fOut, DATASEL nChannel, float fValue, float fStart, float fDelta)
{
int i, ntotal;
int nsel;
int ndetail;
BOOL bup;
INT32 nvalue = FTOI( fValue);
CInt32Array *carray;
int ndelta;

	ndelta = (fDelta > 0) ? 1 : -1;

	ntotal = GetCount();			// get the size of this guy
	if ( fStart < GetStart())		// not here
		nsel = 0;
	else if ( fStart > (GetStart() + GetDelta()*(GetCount()-1)) )
		nsel = GetCount() - 1;
	else
		nsel = (int )((fStart - GetStart()) / GetDelta());

	if ( ndelta > 0)			// counting upwards
		ntotal -= nsel;			// that's what we have to handle
	else
		ntotal = nsel+1;

	if ( nChannel == dataAmp)			// amplitude?
		carray = &m_ciData;
	else
		carray = &m_ciPhase;				// phase

	bup = nvalue > 	carray->GetAt(nsel);			// is the first one bigger or smaller?? bup=TRUE if smaller
	for ( i = ndetail = 0; (i<ntotal) && (ndetail<NDETAIL); nsel += ndelta, i++)
		{
		if ( bup != (nvalue > carray->GetAt(nsel)) )
			{
			ndetail++;				// we found another one that fits
			}
		else
			ndetail = 0;			// start counting again
		}

	if ( i < ntotal)				// we found a series
		{
		nsel -= ndelta * NDETAIL;			// go back to the center point
		fOut = DataAt( dataFreq, nsel);	// set the frequency of the location
		return TRUE;					// we found one...
		}

	return FALSE;

}

BOOL	CDataSet::CreateChart( CNamed *cBase)			// build a new chart object to be graphed
{
CSubChart *cch;


					// build the chart
	if ( GetCount())
		{
		cch = new CSubChart();
		cch->SetRootObject( GetRootObject());						// since it doesn't get added to the tree
		cch->CreateDefault( cNullString, GetUOM());
		cch->Attach( GetID(), uomTime != GetUOM());			// use the phase for this guy
		SetChart( cch);
		delete cch;
		}
	else
		SetChart( NULL);		// delete any old chart

	return TRUE;
}


int	CDataSet::SetSize( int nNewSize)
{
	return SetSize( nNewSize, nNewSize);
}


int	CDataSet::SetSize( int nNewSize, int nNewPhase)
{
int noldd = m_ciData.GetSize();
int noldp = m_ciPhase.GetSize();

	try
		{
		m_ciData.SetSize(nNewSize, 1000);
		m_ciPhase.SetSize(nNewPhase, 1000);
		}
	catch( CException *e)
		{
		    // Handle the exception locally
		AfxMessageBox("Insufficient Memory");
		e->Delete();
		if ( noldd != nNewSize || noldp != nNewPhase)
			SetSize( noldd, noldp);
		return 1;
		}

	return 0;

}



DWORD CDataSet::GetObjectSize(BOOL)
{
	return (sizeof(INT32) * m_ciData.GetSize() + sizeof(INT32) * m_ciPhase.GetSize() + sizeof( CDataSet) );
}
