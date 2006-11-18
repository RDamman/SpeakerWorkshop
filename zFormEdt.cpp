// zFormEdt.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "zFormEdt.h"

#include <Math.h>
#include "Utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LIMIT_NONE	-12545628.314f

		// inches to cm
#define METRICINCM	2.54f
		// ounces to grams
#define METRICOZGM	28.349500581023015f



/////////////////////////////////////////////////////////////////////////////
//	static helper conversion functions

// celsius to fahrenheit
static float conv_CelsiusToFahr( float fValue)
{
		return 32.0f + fValue * (9.0f/5.0f);
}

static float conv_ToCelsius( float fValue, METRICS mMetric)
{
	switch( mMetric)
	{
	case mtCelsius :
		return fValue;
	case mtFahrenheit :
		return ( fValue - 32.0f) * ( 5.0f / 9.0f);
	default:
		ASSERT(0);
		return 0;
	}
}

static float conv_InchtoCM( float fValue)
{
	return fValue * METRICINCM;
}

static float conv_CMtoInch( float fValue)
{
	return fValue / METRICINCM;
}

static float conv_SqInchtoCM( float fValue)
{
	return fValue * (METRICINCM * METRICINCM);
}

static float conv_SqCMtoInch( float fValue)
{
	return fValue / (METRICINCM * METRICINCM);
}
static float conv_CuInchtoCM( float fValue)
{
	return fValue * (METRICINCM * METRICINCM * METRICINCM);
}

static float conv_CuCMtoInch( float fValue)
{
	return fValue / (METRICINCM * METRICINCM * METRICINCM);
}

static float conv_ToInch( float fValue, METRICS mMetric)
{
float fnew;

	switch( mMetric)
		{
		case mtInch :
			fnew = fValue;
			break;
		case mtFoot :
			fnew = fValue * 12.0f;
			break;
		case mtMm :
			fnew = conv_CMtoInch( fValue / 10.0f);
			break;
		case mtCm :
			fnew = conv_CMtoInch( fValue);
			break;
		case mtMeter :
			fnew = conv_CMtoInch( fValue * 100.0f);
			break;
		default :
			ASSERT( 0);
			fnew = 0.0f;		// to avoid warning
			break;
		}

	return fnew;
}

static float conv_ToCm( float fValue, METRICS mMetric)
{
float fnew;

	switch( mMetric)
		{
		case mtInch :
			fnew = conv_InchtoCM( fValue);
			break;
		case mtFoot :
			fnew = conv_InchtoCM( 12.0f * fValue);
			break;
		case mtMm :
			fnew = fValue / 10.0f;
			break;
		case mtCm :
			fnew = fValue;
			break;
		case mtMeter :
			fnew = fValue * 100.0f;
			break;
		default :
			ASSERT( 0);
			fnew = 0.0f;		// to avoid warning
			break;
		}

	return fnew;
}

static float conv_ToSqInch( float fValue, METRICS mMetric)
{
float fnew;

	switch( mMetric)
		{
		case mtSqInch :
			fnew = fValue;
			break;
		case mtSqFoot :
			fnew = fValue * 144.0f;
			break;
		case mtSqMm :
			fnew = conv_SqCMtoInch( fValue / 100.0f);
			break;
		case mtSqCm :
			fnew = conv_SqCMtoInch( fValue);
			break;
		case mtSqMeter :
			fnew = conv_SqCMtoInch( fValue * 10000.0f);
			break;
		default :
			ASSERT( 0);
			fnew = 0.0f;		// to avoid warning
			break;
		}

	return fnew;
}

static float conv_ToSqCm( float fValue, METRICS mMetric)
{
float fnew;

	switch( mMetric)
		{
		case mtSqInch :
			fnew = conv_SqInchtoCM( fValue);
			break;
		case mtSqFoot :
			fnew = conv_SqInchtoCM( 144.0f * fValue);
			break;
		case mtSqMm :
			fnew = fValue / 100.0f;
			break;
		case mtSqCm :
			fnew = fValue;
			break;
		case mtSqMeter :
			fnew = fValue * 10000.0f;
			break;
		default :
			ASSERT( 0);
			fnew = 0.0f;		// to avoid warning
			break;
		}

	return fnew;
}

static float conv_ToCuInch( float fValue, METRICS mMetric)
{
float fnew;

	switch( mMetric)
		{
		case mtCuInch :
			fnew = fValue;
			break;
		case mtCuFoot :
			fnew = fValue * 1728.0f;			//	12*12*12 = 144*12 = 1728
			break;
		case mtCuMm :
			fnew = conv_CuCMtoInch( fValue / 1000.0f);
			break;
		case mtCuCm :
			fnew = conv_CuCMtoInch( fValue);
			break;
		case mtLitre :
			fnew = conv_CuCMtoInch( fValue * 1000.0f);
			break;
		case mtCuMeter :
			fnew = conv_CuCMtoInch( fValue * 1000000.0f);
			break;
		default :
			ASSERT( 0);
			fnew = 0.0f;		// to avoid warning
			break;
		}

	return fnew;
}

static float conv_ToCuCm( float fValue, METRICS mMetric)
{
float fnew;

	switch( mMetric)
		{
		case mtCuInch :
			fnew = conv_CuInchtoCM( fValue);
			break;
		case mtCuFoot :
			fnew = conv_CuInchtoCM( 1728.0f * fValue);
			break;
		case mtCuMm :
			fnew = fValue / 1000.0f;
			break;
		case mtCuCm :
			fnew = fValue;
			break;
		case mtLitre :
			fnew = fValue * 1000.0f;
			break;
		case mtCuMeter :
			fnew = fValue * 1000000.0f;
			break;
		default :
			ASSERT( 0);
			fnew = 0.0f;		// to avoid warning
			break;
		}

	return fnew;
}

static float conv_ToGram( float fValue, METRICS mMetric)
{
float fnew;

	switch( mMetric)
		{
		case mtGram :
			fnew = fValue;
			break;
		case mtKGram :
			fnew = fValue * 1000.0f;			//	12*12*12 = 144*12 = 1728
			break;
		case mtOz :
			fnew = fValue * METRICOZGM;
			break;
		case mtLb :
			fnew = fValue * METRICOZGM * 16.0f;
			break;
		default :
			ASSERT( 0);
			fnew = 0.0f;		// to avoid warning
			break;
		}

	return fnew;
}

static float conv_ToOunce( float fValue, METRICS mMetric)
{
float fnew;

	switch( mMetric)
		{
		case mtGram :
			fnew = fValue / METRICOZGM;
			break;
		case mtKGram :
			fnew = (fValue / METRICOZGM) * 1000.0f;			//	
			break;
		case mtOz :
			fnew = fValue;
			break;
		case mtLb :
			fnew = fValue * 16;
			break;
		default :
			ASSERT( 0);
			fnew = 0.0f;		// to avoid warning
			break;
		}

	return fnew;
}




static float conv_BaseToBase( float fValue, METRICS mDest, METRICS mSource)		// convert to base metric
{
float fnew;

	switch( mDest)
		{
		case mtNone :
			fnew = fValue;
			break;
		case mtInch :
			fnew = conv_ToInch( fValue, mSource);
			break;
		case mtFoot :
			fnew = conv_ToInch( fValue, mSource) / 12.0f;
			break;
		case mtMm :
			fnew = 10.0f * conv_ToCm( fValue, mSource);
			break;
		case mtCm :
			fnew = conv_ToCm( fValue, mSource);
			break;
		case mtMeter :
			fnew = conv_ToCm( fValue, mSource) / 100.0f;
			break;
		case mtCuInch :
			fnew = conv_ToCuInch( fValue, mSource);
			break;
		case mtCuFoot :
			fnew = conv_ToCuInch( fValue, mSource) / 1728.0f;
			break;
		case mtCuMm :
			fnew = conv_ToCuCm( fValue, mSource) * 1000.0f;
			break;
		case mtCuCm :
			fnew = conv_ToCuCm( fValue, mSource);
			break;
		case mtLitre :
			fnew = conv_ToCuCm( fValue, mSource) / 1000.0f;
			break;
		case mtCuMeter :
			fnew = conv_ToCuCm( fValue, mSource) / 1000000.0f;
			break;
		case mtSqInch :
			fnew = conv_ToSqInch( fValue, mSource);
			break;
		case mtSqFoot :
			fnew = conv_ToSqInch( fValue, mSource) / 144.0f;
			break;
		case mtSqMm :
			fnew = conv_ToSqCm( fValue, mSource) * 100.0f;
			break;
		case mtSqCm :
			fnew = conv_ToSqCm( fValue, mSource);
			break;
		case mtSqMeter :
			fnew = conv_ToSqCm( fValue, mSource) / 10000.0f;
			break;
		case mtGram :
			fnew = conv_ToGram( fValue, mSource);
			break;
		case mtKGram :
			fnew = conv_ToGram( fValue, mSource) / 1000.0f;
			break;
		case mtOz :
			fnew = conv_ToOunce( fValue, mSource);
			break;
		case mtLb :
			fnew = conv_ToOunce( fValue, mSource) / 16.0f;
			break;
		case mtFahrenheit :
			fnew = conv_ToCelsius( fValue, mSource);
			fnew = conv_CelsiusToFahr( fValue);
			break;
		case mtCelsius :
			fnew = conv_ToCelsius( fValue, mSource);
			break;
		default:
			ASSERT( 0);
			fnew = 0.0f;		// to avoid warning
			break;
		}

	return fnew;
}

/////////////////////////////////////////////////////////////////////////////
// CzFormatEdit

CzFormatEdit::CzFormatEdit()
{
	m_fValue = -12345.0f;		// some random number
	m_uEdit = 0;
	m_uSpin = 0;
	m_uStatic = 0;
	m_fMin = LIMIT_NONE;
	m_fMax = LIMIT_NONE;
	m_Metric = mtNone;
	m_BaseMetric = mtNone;
	m_nDigits = -4;				// default to 4 decimal places

}

CzFormatEdit::~CzFormatEdit()
{
//	Detach();
}

// ------------------------------------------------------------------
//		SetLimits( fMin, fMax)
//			set the range of possible data entry
//			often 0...100 for volume control stuff
// ------------------------------------------------------------------
void CzFormatEdit::SetLimits( float fMin, float fMax)
{
	if ( fMin > fMax)			// if min > max set them just to no limits
		{
		m_fMin = LIMIT_NONE;
		m_fMax = LIMIT_NONE;
		}
	else						// set the limits
		{
		m_fMin = fMin;
		m_fMax = fMax;
		if ( m_fValue > fMax)	// set the value to be within limits
			m_fValue = fMax;
		if ( m_fValue < fMin)
			m_fValue = fMin;
		}

}


/////////////////////////////////////////////////////////////////////////////
// CzFormatEdit message handlers

// -------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void CzFormatEdit::Subclass( CWnd *pParent, UINT nID, UINT uBuddy)
{
CEdit			*pedit;				// the base window
CSpinButtonCtrl *pspin;				// the associated spin control

	m_pParent = pParent;

	m_uEdit = nID;
	m_uSpin = uBuddy;

	pedit = (CEdit *)pParent->GetDlgItem( nID);
	ASSERT( pedit != NULL);
	ASSERT( pedit->GetSafeHwnd());

	if ( uBuddy)
		{
		pspin = (CSpinButtonCtrl *)pParent->GetDlgItem( uBuddy);
		if ( pspin && pspin->GetSafeHwnd())
			{
			pspin->SetRange(0, 1000);
			}
		}
}


// -------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
UINT CzFormatEdit::GetEditID( void)
{
	return m_uEdit;
}

// -------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
UINT CzFormatEdit::GetStaticID( void)
{
	return m_uStatic;
}


// -------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
UINT CzFormatEdit::GetBuddyID( void)
{
	return m_uSpin;
}


// -------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void CzFormatEdit::ProcessDelta( int iDelta)
{
float fvalue = GetDisplayValue();
float fdel = fvalue / 10;		// the delta to be used

	if ( fdel < 0)
		fdel = -fdel;

	if ( fdel == 0.0f)
		fdel = 1.0f;
	else
		fdel = pow( 10.0f, floor(log10( fdel)));

	SetDisplayValue( fvalue + fdel * iDelta);
}



// -------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void CzFormatEdit::DDX_Value( CDataExchange *pDX, float& fValue)
{
	if ( pDX->m_bSaveAndValidate )
	{
		if ( ! IsValid())
		{
			pDX->PrepareEditCtrl( GetEditID());
			AfxMessageBox( IDERR_INVALIDENTRY, MB_OK);
			pDX->Fail();
		}
		fValue = GetValue();
	}
	else
		SetValue( fValue);
}

// -------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void CzFormatEdit::SetValue( float fNew)
{
CEdit *pedit;

	pedit = (CEdit *)m_pParent->GetDlgItem( m_uEdit);
	ASSERT( pedit != NULL);

	if ( LIMIT_NONE != m_fMin)	// limit the input data appropriately
		if ( fNew < m_fMin)
			fNew = m_fMin;
	if ( LIMIT_NONE != m_fMax)
		if ( fNew > m_fMax)
			fNew = m_fMax;

	if ( (m_fValue != fNew) || (m_fValue == m_fMin))	// at init this is often true
		{
		if ( pedit->GetSafeHwnd())
			{
			CString cs;

				m_fValue = fNew;
				fNew = XfromBase( fNew);			// convert to our # system
				::FullFormatValue( cs, fNew, m_nDigits);
				pedit->SetWindowText( cs);
			}
		}

}

// -------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
bool CzFormatEdit::IsValid( void)
{
CString cs;
CEdit *pedit;

	pedit = (CEdit *)m_pParent->GetDlgItem( m_uEdit);
	ASSERT( pedit != NULL);

	if ( ! pedit->GetSafeHwnd())
		return false;

	pedit->GetWindowText( cs);
	if ( ! ::IsValidString( cs))
		return false;

	return true;

}

// -------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
float CzFormatEdit::GetValue( void)
{
CString cs;
CEdit *pedit;

	pedit = (CEdit *)m_pParent->GetDlgItem( m_uEdit);
	ASSERT( pedit != NULL);

	if ( ! pedit->GetSafeHwnd())
		return m_fValue;

	pedit->GetWindowText( cs);

	if ( ::IsValidString( cs))
		{
		float fv = ::UnformatValue ( cs);
		fv = XtoBase( fv);			// convert from our # system to base system
		m_fValue = fv;
		}
	return m_fValue;
}


// -------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void	CzFormatEdit::BaseMetric( METRICS mBase, CStatic *pStatic)	// set the base metric and static field
{
	m_BaseMetric = mBase;
	m_Metric = mBase;			// set them both to base metric for now
	m_uStatic = pStatic->GetDlgCtrlID();
	DrawMetric();
}

// -------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void	CzFormatEdit::SetMetric( METRICS mNew)		// set a new metric
{
	m_Metric = mNew;
	{
	float fvalue = GetValue();			// get the current value
		SetValue( m_fMin);				// make it draw
		SetValue( fvalue);				// set it for good
	}
	DrawMetric();
						// do the data conversion
}

// -------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void	CzFormatEdit::SetMetricType( BOOL bIsMetric)		// set a new metric base on Metric/English
{
METRICS metric;

	switch( m_BaseMetric)
		{
		case mtNone :
			metric = mtInch;
			break;
		case mtInch :
			metric = (bIsMetric ? mtCm : mtInch);
			break;
		case mtFoot :
			metric = (bIsMetric ? mtMeter : mtFoot);
			break;
		case mtMm :
			metric = (bIsMetric ? mtMm : mtInch);
			break;
		case mtCm :
			metric = (bIsMetric ? mtCm : mtInch);
			break;
		case mtMeter :
			metric = (bIsMetric ? mtMeter : mtFoot);
			break;
		case mtCuInch :
			metric = (bIsMetric ? mtLitre : mtCuInch);
			break;
		case mtCuFoot :
			metric = (bIsMetric ? mtLitre : mtCuFoot);
			break;
		case mtCuMm :
			metric = (bIsMetric ? mtCuMm : mtCuInch);
			break;
		case mtCuCm :
			metric = (bIsMetric ? mtCuCm : mtCuInch);
			break;
		case mtLitre :
			metric = (bIsMetric ? mtLitre : mtCuFoot);
			break;
		case mtCuMeter :
			metric = (bIsMetric ? mtCuMeter : mtCuFoot);
			break;
		case mtSqInch :
			metric = (bIsMetric ? mtCm : mtSqInch);
			break;
		case mtSqFoot :
			metric = (bIsMetric ? mtCm : mtSqFoot);
			break;
		case mtSqMm :
			metric = (bIsMetric ? mtSqMm : mtSqInch);
			break;
		case mtSqCm :
			metric = (bIsMetric ? mtSqCm : mtSqInch);
			break;
		case mtSqMeter :
			metric = (bIsMetric ? mtSqMeter : mtSqInch);
			break;
		case mtGram :
			metric = (bIsMetric ? mtGram : mtOz);
			break;
		case mtKGram :
			metric = (bIsMetric ? mtKGram : mtLb);
			break;
		case mtOz :
			metric = (bIsMetric ? mtGram : mtOz);
			break;
		case mtLb :
			metric = (bIsMetric ? mtKGram : mtLb);
			break;
		case mtFahrenheit :
		case mtCelsius :
			metric = (bIsMetric ? mtCelsius : mtFahrenheit);
			break;

		default:
			ASSERT( 0);
			metric = mtSqMeter;			// to avoid warning
			break;
		}

	SetMetric( metric);
}

// -------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
METRICS	CzFormatEdit::GetNextMetric(METRICS metStart)		// get the next metric
{
METRICS metric;

	switch( metStart)
		{
		case mtNone :
			metric = mtNone;
			break;
		case mtInch :
			metric = mtFoot;
			break;
		case mtFoot :
			metric = mtMm;
			break;
		case mtMm :
			metric = mtCm;
			break;
		case mtCm :
			metric = mtMeter;
			break;
		case mtMeter :
			metric = mtInch;
			break;
		case mtCuInch :
			metric = mtCuFoot;
			break;
		case mtCuFoot :
			metric = mtCuMm;
			break;
		case mtCuMm :
			metric = mtCuCm;
			break;
		case mtCuCm :
			metric = mtLitre;
			break;
		case mtLitre :
			metric = mtCuMeter;
			break;
		case mtCuMeter :
			metric = mtCuInch;
			break;
		case mtSqInch :
			metric = mtSqFoot;
			break;
		case mtSqFoot :
			metric = mtSqMm;
			break;
		case mtSqMm :
			metric = mtSqCm;
			break;
		case mtSqCm :
			metric = mtSqMeter;
			break;
		case mtSqMeter :
			metric = mtSqInch;
			break;
		case mtGram :
			metric = mtKGram;
			break;
		case mtKGram :
			metric = mtOz;
			break;
		case mtOz :
			metric = mtLb;
			break;
		case mtLb :
			metric = mtGram;
			break;
		case mtFahrenheit :
			metric = mtCelsius;
			break;
		case mtCelsius :
			metric = mtFahrenheit;
			break;
		default:
			ASSERT( 0);
			metric = mtSqMeter;			// to avoid warning
			break;
		}

	return metric;
}

// -------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void	CzFormatEdit::CycleMetric( void)		// set a new metric
{
METRICS metric;

	metric = GetNextMetric( m_Metric);

	SetMetric( metric);
}

// -------------------------------------------------------------------------------
//		XtoBase - convert floating value in current metric to base metric
// --------------------------------------------------------------------------------
float	CzFormatEdit::XtoBase( float fValue)			// convert to base metric
{
	return conv_BaseToBase( fValue, m_BaseMetric, m_Metric);
}

// -------------------------------------------------------------------------------
//		XfromoBase - convert floating value in base metric to current metric
// --------------------------------------------------------------------------------
float	CzFormatEdit::XfromBase( float fValue)		// convert to current metric
{
	return conv_BaseToBase( fValue, m_Metric, m_BaseMetric);
}

float CzFormatEdit::ConvertBaseToBase( float fValue, METRICS mDest, METRICS mSource)
{
	return conv_BaseToBase( fValue, mDest, mSource);
}



// -------------------------------------------------------------------------------
//	GetDisplayValue get the value displayed
// --------------------------------------------------------------------------------
float	CzFormatEdit::GetDisplayValue( void)		// convert to current metric
{
	return XfromBase( GetValue());
}


// -------------------------------------------------------------------------------
//	SetDisplayValue set the value displayed
// --------------------------------------------------------------------------------
void	CzFormatEdit::SetDisplayValue( float fValue)		// convert to current metric
{
	SetValue( XtoBase( fValue));
}

// -------------------------------------------------------------------------------
//	DrawMetric draw a text string in the static field
// --------------------------------------------------------------------------------
void	CzFormatEdit::DrawMetric( void)
{
CString cstext;
CWnd *pstatic;

	if ( ! m_uStatic)			// no static field attached
		return;

	if ( mtNone == m_BaseMetric)		// no metric assoicated with this
		return;

	pstatic = m_pParent->GetDlgItem( m_uStatic);
	ASSERT( pstatic && pstatic->GetSafeHwnd());

	switch( m_Metric)			// draw it based on current metric
		{
		case mtNone :
			ASSERT( 0);
			return;				// booo hiss
		case mtInch :
			cstext.LoadString( IDS_UNIT_IN);
			break;
		case mtFoot :
			cstext.LoadString( IDS_UNIT_FT);
			break;
		case mtMm :
			cstext.LoadString( IDS_UNIT_MM);
			break;
		case mtCm :
			cstext.LoadString( IDS_UNIT_CM);
			break;
		case mtMeter :
			cstext.LoadString( IDS_UNIT_M);
			break;
		case mtCuInch :
			cstext.LoadString( IDS_UNIT_IN3);
			break;
		case mtCuFoot :
			cstext.LoadString( IDS_UNIT_FT3);
			break;
		case mtCuMm :
			cstext.LoadString( IDS_UNIT_MM3);
			break;
		case mtCuCm :
			cstext.LoadString( IDS_UNIT_CM3);
			break;
		case mtLitre :
			cstext.LoadString( IDS_UNIT_LITERS);
			break;
		case mtCuMeter :
			cstext.LoadString( IDS_UNIT_M3);
			break;
		case mtSqInch :
			cstext.LoadString( IDS_UNIT_IN2);
			break;
		case mtSqFoot :
			cstext.LoadString( IDS_UNIT_FT2);
			break;
		case mtSqMm :
			cstext.LoadString( IDS_UNIT_MM2);
			break;
		case mtSqCm :
			cstext.LoadString( IDS_UNIT_CM2);
			break;
		case mtSqMeter :
			cstext.LoadString( IDS_UNIT_M2);
			break;
		case mtGram :
			cstext.LoadString( IDS_UNIT_GM);
			break;
		case mtKGram :
			cstext.LoadString( IDS_UNIT_KG);
			break;
		case mtOz :
			cstext.LoadString( IDS_UNIT_OZ);
			break;
		case mtLb :
			cstext.LoadString( IDS_UNIT_LB);
			break;
		case mtFahrenheit :
			cstext.LoadString( IDS_UNIT_DEGF);
			break;
		case mtCelsius :
			cstext.LoadString( IDS_UNIT_DEGC);
			break;
		default:
			ASSERT( 0);
			break;
		}

	pstatic->SetWindowText( cstext);

}

// Right Click - cycle metric backwards
void CzFormatEdit::RightClick( void)
{
METRICS mlast = m_Metric;		// get the current metric
METRICS mttest;

	for ( mttest = mtNone; mttest <= mtLast; mttest = (METRICS )(1 + mttest))
	{
		if ( mlast == GetNextMetric( mttest))
			break;
	}
				// now mttest is the prior metric
	SetMetric( mttest);

}


// -------------------------------------------------------------------------------
// --------------------------------------------------------------------------------


/////////////////////////////////////////////////////////////////////////////
// CzFormatGroup
/////////////////////////////////////////////////////////////////////////////

// this is a higher level version of CzFormatEdit that takes an array of data
// and creates a bunch of CzFormatEdit objects to handle that stuff

// ---------- creation
CzFormatGroup::CzFormatGroup()
{
	m_pControls.SetSize(0,10);
	m_pValues.SetSize(0, 10);
}

// ---------- deletion
CzFormatGroup::~CzFormatGroup()
{
	DetachGroup();
}

// ---------- find a control
CzFormatEdit *CzFormatGroup::GetControl( UINT uID)
{
CzFormatEdit *pedit;

	if ( m_pControls.GetSize())
		{
		int i;
		for ( i=0; i<m_pControls.GetSize(); i++)
			{
			pedit = (CzFormatEdit *)m_pControls.GetAt(i);
			if ( uID == pedit->GetEditID())
				return pedit;
			}
		}

	return NULL;
}

CzFormatEdit *CzFormatGroup::GetBuddy( UINT uID)
{
CzFormatEdit *pedit;

	if ( m_pControls.GetSize())
		{
		int i;
		for ( i=0; i<m_pControls.GetSize(); i++)
			{
			pedit = (CzFormatEdit *)m_pControls.GetAt(i);
			if ( uID == pedit->GetBuddyID())
				return pedit;
			}
		}

	return NULL;
}



// ---------- attach an array of data to this object
int CzFormatGroup::AttachGroup( CWnd *pParent, const FormatGroup pNewGroup[])
{
int i;

	DetachGroup();			// remove any prior stuff

	m_pParent = pParent;	// set the parent handle

	for ( i=0; pNewGroup[i].idControl; i++)
		{
		if ( pNewGroup[i].idControl)		// it's real
			{
			CzFormatEdit *cz = new CzFormatEdit;

				cz->Subclass( pParent, pNewGroup[i].idControl, pNewGroup[i].idBuddy);
				cz->SetLimits( pNewGroup[i].fMin, pNewGroup[i].fMax);
				m_pControls.Add( cz);
				m_pValues.Add( pNewGroup[i].pfValue);
			}
		}

	pParent->UpdateData( FALSE);		// init anything we need to here

	return 0;
}

// ---------- attach an array of data to this object
int CzFormatGroup::AttachMetrics(  const GroupMetric pBaseMetrics[])
{
int i, j;
BOOL bmetric = CAudtestApp::GetIsMetric();

	for ( j=0; pBaseMetrics[j].idControl; j++)		// for each in basemetrics
		{			// find the control and set its base metric
		for ( i=0; i<m_pControls.GetSize(); i++)
			{
			CzFormatEdit *cz = (CzFormatEdit *)m_pControls[i];		// just for readability
			if ( cz->GetEditID() == pBaseMetrics[j].idControl)		// found it
				{
				CStatic *pstatic;

					if ( pBaseMetrics[j].idStatic)		// if a static is specified, use it
						pstatic = (CStatic *) m_pParent->GetDlgItem( pBaseMetrics[j].idStatic);
					else
						pstatic = NULL;

					cz->BaseMetric( pBaseMetrics[j].mBase, pstatic); // set it
					cz->SetMetricType( bmetric);
				}
			}
		}

	return 0;
}

// detach the current data
void CzFormatGroup::DetachGroup( void)
{
int i;

	for ( i=0; i<m_pControls.GetSize(); i++)
		{
		delete m_pControls.GetAt(i);
		}
	m_pControls.RemoveAll();
	m_pValues.RemoveAll();
}

void CzFormatGroup::DDX_All( CDataExchange *pDX)
{
CzFormatEdit *pedit;
int i;

	for ( i=0; i<m_pControls.GetSize(); i++)
		{
		float *pf = (float *)m_pValues.GetAt(i);
		pedit = (CzFormatEdit *)m_pControls.GetAt(i);
		if ( pDX->m_bSaveAndValidate )
		{
			if ( ! pedit->IsValid())
			{
				pDX->PrepareEditCtrl( pedit->GetEditID());
				AfxMessageBox( IDERR_INVALIDENTRY, MB_OK);
				pDX->Fail();
			}
			*pf = pedit->GetValue();
		}
		else
			pedit->SetValue( *pf);
		}
}

void CzFormatGroup::ProcessAllDelta( NMHDR* pNMHDR)
{
CzFormatEdit *cz;

	cz = GetBuddy( pNMHDR->idFrom);
	if ( cz)			// we have it
		{
		NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
		cz->ProcessDelta( pNMUpDown->iDelta);
		}

}

// comment - for this to work, the static fields must be first in the list!

int	CzFormatGroup::ProcessLeftClick( UINT , CPoint point)	// switch units if allowed
{
	if ( m_pParent)
		{					// find who we touched
		CWnd *ptarget = m_pParent->ChildWindowFromPoint( point);
						// which target is it????
		if ( ptarget)
			{
			CzFormatEdit *pedit;
			int i;
			UINT id = ptarget->GetDlgCtrlID();

				for ( i=0; i<m_pControls.GetSize(); i++)
					{
					pedit = (CzFormatEdit *)m_pControls.GetAt(i);
					if ( id == pedit->GetStaticID())		// found it
						{
						float fvalue = pedit->GetValue();
						pedit->CycleMetric();
						pedit->SetValue( fvalue);			// just redraw it
						return 1;
						}
					}
			}
		}

	return 0;				// didn't do anything
}

// ------------------------------------------------------------------------------------
// comment - for this to work, the static fields must be first in the list!
// ------------------------------------------------------------------------------------
int	CzFormatGroup::ProcessRightClick( UINT , CPoint point)	// switch units if allowed
{
	if ( m_pParent)
		{					// find who we touched
		CWnd *ptarget = m_pParent->ChildWindowFromPoint( point);
						// which target is it????
		if ( ptarget)
			{
			CzFormatEdit *pedit;
			int i;
			UINT id = ptarget->GetDlgCtrlID();

				for ( i=0; i<m_pControls.GetSize(); i++)
					{
					pedit = (CzFormatEdit *)m_pControls.GetAt(i);
					if ( id == pedit->GetStaticID())		// found it
						{
						float fvalue = pedit->GetValue();
						pedit->RightClick();
						pedit->SetValue( fvalue);			// just redraw it
						return 1;
						}
					}
			}
		}

	return 0;				// didn't do anything
}

/////////////////////////////////////////////////////////////////////////////
// CzFormatStatic

CzFormatStatic::CzFormatStatic()
{
}

CzFormatStatic::~CzFormatStatic()
{
}


BEGIN_MESSAGE_MAP(CzFormatStatic, CStatic)
	//{{AFX_MSG_MAP(CzFormatStatic)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CzFormatStatic message handlers

// ------------------------------------------------------------------------------------
//		Set the text color
// ------------------------------------------------------------------------------------
HBRUSH CzFormatStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
HBRUSH hbrush;
LOGBRUSH lbr;

	ASSERT( CTLCOLOR_STATIC == nCtlColor);		// we better see this

	pDC->SetTextColor( RGB(0,0,166));		// dark blue
			// we also have to set the background color because if we return a null brush
			// the system will reset the text color for us (duh)
	hbrush = GetSysColorBrush(COLOR_BTNFACE);		// get the brush we need
	GetObject( hbrush, sizeof( lbr), &lbr);			// get the brush color
	pDC->SetBkColor( lbr.lbColor);					// set the background using the system background color
	
	// Return a non-NULL brush if the parent's handler should not be called
	return hbrush;
}


