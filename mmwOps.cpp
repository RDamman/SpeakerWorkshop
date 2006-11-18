// ========================================
//				MMWOPS.CPP - mm wave operations
// ========================================
	// there is no  in 32 bit
#include "stdafx.h"
#include "audtest.h"

#include "mmwave.h"

//#include "Named.h"
#include "DataSet.h"
#include "MainFrm.h"


// ----------------------------------------
//		ConvertToData
// this takes the left and right channel i/o(bIn) data and converts them
// to pcLeft and pcRight datasets (pcRight is optional)
// ----------------------------------------
void CMMWave::ConvertToData(CObject *pcLeft, CObject *pcRight, BOOL bTruncate)
{
CDataSet *pcleft = (CDataSet *)pcLeft;
CDataSet *pcright = (CDataSet *)pcRight;
DWORD dwi;

	dwi = GetCharDataSize( bTruncate);
	if ( ! dwi)
		return;

	if ( pcleft)
		{
								// now set variables based on wave data
		pcleft->SetDelta( 1000.0f / GetSamplesPerSecond() );
		pcleft->SetStart( 0.0f);
		pcleft->SetUOM( uomTime);
		pcleft->SetDOM( uomVolts);
		pcleft->SetSize( dwi, 0);
		}
	if ( pcright)
		{
							// now set variables based on wave data
		pcright->SetDelta( 1000.0f / GetSamplesPerSecond() );
		pcright->SetStart( 0.0f);
		pcright->SetUOM( uomTime);
		pcright->SetDOM( uomVolts);
		pcright->SetSize( dwi, 0);
		}
							// now fill data itself
	{
	short *pdata;
	int i, j;

		pdata = (short *)GetCharData( bTruncate);

		if (  1 == m_Format.nChannels)			// mono data
		{
			if ( pcleft)			// left channel mono
			{
				for ( i=0; i<dwi; i ++)
					pcleft->SetDataAt(i, FTOI( pdata[i]));
			}
			else if ( pcright)					// right channel mono
			{
				for ( i=0; i<dwi; i ++)
					pcright->SetDataAt(i, FTOI( pdata[i]));
			}
		}
		else			// stereo data
		{
			dwi += dwi;			// use twice the dwi

			if ( pcleft)
				for ( i=0; i<dwi; i += 2)
					pcleft->SetDataAt(i/2, FTOI( pdata[i]));
			if ( pcright)
				for ( i=1; i<dwi; i += 2)
					pcright->SetDataAt(i/2, FTOI( pdata[i]));
#if 0
						// if we want to estimate the value for 1/2 phase shift
						// use -1/16Y1 + 9/16Y2 + 9/16Y3 - 1/16Y4
				Get rid of the right shift stuff / it didn't work right anyway
			else
			{
				float ft;
				float fmat[4];
				short matrix[4];		// put the data here
				float fshift = CAudtestApp::GetRightShift() / 100.0f;
				fmat[0] = -(fshift) *  (1-fshift) * (2-fshift) / 6;
				fmat[1] = (fshift+1)* (1-fshift) * (2-fshift) / 2;
				fmat[2] = (fshift+1)*(fshift)*(2-fshift) / 2;
				fmat[3] = -(fshift) *  (1-fshift) * (1+fshift) / 6;
				matrix[0] = pdata[1];
				matrix[1] = pdata[1];
				matrix[2] = pdata[1];
				matrix[3] = pdata[3];
				for ( i=5; i<dwi; i += 2)
				{
					matrix[0] = matrix[1];
					matrix[1] = matrix[2];
					matrix[2] = matrix[3];		// move the data down 1
					matrix[3] = pdata[i];		// get the next one
					ft = 0.0f;
					for  ( j=0;j<4;j++)
						ft += fmat[j] * matrix[j];
					if ( ft >= SHRT_MAX)
						ft = SHRT_MAX-1;
					if ( ft <= SHRT_MIN)
						ft = SHRT_MIN+1;
					pcright->SetDataAt(i/2-2, FTOI((short )ft));	// put it back 1 to get the shift here
				}
				pcright->SetDataAt(i/2-2, matrix[2]);		// use the last datapoint here
				pcright->SetDataAt(i/2-1, matrix[3]);		// use the last datapoint here
			}
#endif
		}

	}

				// now find the max, min, average of the data
				// and store it into the vu meter
	if ( IsKindOf( RUNTIME_CLASS( CMMInputWave)))	// if it's input
	{
	CWnd *cmain = AfxGetMainWnd();
		if ( cmain && cmain->IsKindOf(RUNTIME_CLASS( CMainFrame))) 
		{
		CMainFrame *cframe = (CMainFrame *)cmain;
		int i, nmax;
		INT32 imin, imax, iave;
		INT32 ival;
		__int64 itotal;

			if ( pcleft)			// we have left data
			{
				imin = INT_MAX;
				imax = INT_MIN;
				itotal = 0;
				nmax = pcleft->GetCount();

				for ( i=0; i<nmax; i++)
				{
					ival = pcleft->GetDataAt( i);
					if ( imin > ival)
						imin = ival;
					if ( imax < ival)
						imax = ival;
					itotal += abs( ival);
				}
			iave = (INT32 )(itotal / nmax);
			cframe->SetLeftValues( ITOF( imax), ITOF( iave), ITOF( imin));
			}

			if ( pcright)			// we have right data
			{
				imin = INT_MAX;
				imax = INT_MIN;
				itotal = 0;
				nmax = pcright->GetCount();

				for ( i=0; i<nmax; i++)
				{
					ival = pcright->GetDataAt( i);
					if ( imin > ival)
						imin = ival;
					if ( imax < ival)
						imax = ival;
					itotal += abs( ival);
				}
			iave = (INT32 )(itotal / nmax);
			cframe->SetRightValues( ITOF( imax), ITOF( iave), ITOF( imin));
			}

		}
	}



}


// ----------------------------------------
//		ConvertToData
// this takes the left and right channel i/o(bIn) data and converts them
// to pcLeft and pcRight datasets (pcRight is optional)
// ----------------------------------------
void CMMWave::ConvertFromData(CObject *pcLeft, CObject *pcRight)
{
CDataSet *pcleft = (CDataSet *)pcLeft;
CDataSet *pcright = (CDataSet *)pcRight;
DWORD dwi;

	if ( ! pcleft)
		return;

	dwi = pcleft->GetCount();

	if ( ! dwi)
		return;

	DeleteContents();

	PrepareForm( pcright ? 2 : 1, 
				 pcleft->Maximum( dataAmp), 
				 dwi * pcleft->GetDelta() / 1000,
				 (int )(1000 / pcleft->GetDelta()) );

							// now fill data itself
	{
	short *pdata = (short *)GetCharData();
	DWORD i;

		for ( i=0; i<dwi; i++)
			{
			*pdata++ = (short )pcleft->DataAt(dataAmp, i);
			if ( 2 == GetChannels())
				*pdata++ = (short )pcright->DataAt(dataAmp, i);
			}

	}

}


