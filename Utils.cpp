// speaker.cpp : implementation of the CDataSetArray classes
//

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


#include "stdafx.h"
#include "audtest.h"

#include "Utils.h"

#include "MainFrm.h"

#include <math.h>


// ----------------------------------------------------------------
// the null strings to save on global storage

const char * const cNullString = "";
const char * const cNullUnicode = _T("");

// ----------------------------------------------------------------

CTempStorage cTempStore;			// public to everyone

CTempStorage::CTempStorage(void )
{
	dSine = NULL;
	dCosine = NULL;
	nPower = 0;
}

CTempStorage::~CTempStorage()
{
	if ( dSine)
		delete [] dSine;
	if ( dCosine)
		delete [] dCosine;
}


void CommaFormat( CString &csDest, int nValue)
{
BOOL bsign = nValue < 0;

	if ( bsign)
		nValue = -nValue;

	if ( nValue > 1000000)		// million
		csDest.Format( "%d,%03d,%03d", nValue/1000000, (nValue % 1000000) / 1000, nValue % 1000);
	else if ( nValue > 1000)
		csDest.Format( "%d,%03d", nValue/1000, nValue % 1000);
	else
		csDest.Format( "%d", nValue);

}

// ----------------------------------------------------------------------------
// FullFormatValue ( CString &csDest, float fValue, int nDecimal )
//		Format a floating point value using nDecimal decimal places
//			if nDecimal >= 0 use that many decimal points
//			if nDecimal < 0 use that many significant digits
// ----------------------------------------------------------------------------

void  FullFormatValue( CString &csDest, float fValue, int nDecimal)
{
CString csunit;
float fsub;
char szout[100];
char szform[100];;
const char *szdigit = "0123456789";

	if ( fValue == 0.0f)			// value is 00000
		{
		csDest = "0";
		return;
		}

	fsub = FormatValue( fValue, csunit);
	if ( ! nDecimal)			// no decimal places
		{
		fsub = fValue;
		csunit = cNullString;
		strcpy( szform,"%.0f ");
		}
	else if ( nDecimal > 0)		// # of decimal places
		{
		strcpy( szform,"%.2f ");
		szform[2] = (char )(nDecimal + '0');
		}
	else						// number of digits
		{
		float fab = (float )fabs( fsub);
		int ndigits;

		ndigits = -nDecimal;		// put into > 0
		strcpy( szform,"%.3f ");		// 3 isn't retained

		if ( fab > 100)
			{
			if ( ndigits > 3)
				szform[2] = szdigit[ndigits - 3];
			else
				szform[2] = '0';
			}
		else if ( fab > 10)
			{
			if ( ndigits > 2)
				szform[2] = szdigit[ndigits - 2];
			else
				szform[2] = '0';
			}
		else if ( fab > 1)
			{
			if ( ndigits > 1)
				szform[2] = szdigit[ndigits - 1];
			else
				szform[2] = '0';
			}
		else 
			{
			szform[2] = szdigit[ndigits];
			}
		}

	sprintf( szout, szform, fsub);
	csDest = szout + csunit;		// append the unit of measure (K, m, ...)
}


float FormatValue( float fValue, CString& csUnit)
{
double dv = fabs( fValue);

	if ( dv > 1000000)			// a meg
		{
		csUnit = "M";
		dv /= 1000000;
		}
	else
	if ( dv > 1000)
		{
		csUnit = "K";
		dv /= 1000;
		}
	else
	if ( dv > .5)
		{
		csUnit = "";
		}
	else
	if ( dv > .000999)
		{
		csUnit = "m";
		dv *= 1000;
		}
	else
	if ( dv > .000000999)
		{
		csUnit = "u";
		dv *= 1000000;
		}
	else
	if ( dv >= 1.0e-9)
		{
		csUnit = "n";
		dv *= 1e9;
		}
	else
		{
		csUnit = "p";
		dv *= 1e12;
		}

	if ( fValue < 0)
		dv = -dv;			// make sign correct;
	return (float )dv;
}


float UnformatValue( float fValue, CString& csUnit)
{
double dval;
char c;

	csUnit.TrimLeft();

	if ( csUnit.GetLength())
		c = csUnit[0];
	else
		c = ' ';
	switch( c)
		{
		case 'M' :
			dval = fValue * 1000000;
			break;
		case 'k' :		// allow k
		case 'K' :
			dval = fValue * 1000;
			break;
		case 'm' :
			dval = fValue / 1000;
			break;
		case 'U' :		// allow U
		case 'u' :
			dval = fValue / 1000000;
			break;
		case 'N' :
		case 'n' :
			dval = fValue / 1.0e9;
			break;
		case 'P' :
		case 'p' :
			dval = fValue / 1.0e12;
			break;
		default :
			dval = fValue;
			break; // who knows
		}

	return (float )dval;
}

BOOL IsValidString( CString& csValue)
{
CString csdigit;
CString csc;
CString csout;
TCHAR c;

	csdigit.Format("%.9f", 1.023456789);		// all of the digits and the (possibly localized) decimal point
	csdigit += ".,";		// allow both period and comma always

	csc = csValue;

	csc.TrimRight();
	csc.TrimLeft();

	if ( csc.IsEmpty())
		return FALSE;			// not ok (?)

	c = csc.GetAt(csc.GetLength()-1);

	if ( -1 == csdigit.Find( c))
	{
		csc = csc.Left( csc.GetLength()-1);		// trim the last char if not a digit
		csc.TrimRight();						// and remove any more spaces
	}

	if ( csc.IsEmpty())							// empty string is valid?
		return true;

	if ( TCHAR('-') == csc.GetAt(0))				// leading - sign ?
	{
		csc = csc.Right( csc.GetLength() - 1);	// trim it
		csc.TrimLeft();
	}

	csout = csc.SpanIncluding( csdigit);		// get all the digits

	return ( csout == csc);					// they should be the same

}



float UnformatValue(CString& csValue)
{
double dval;
char c;
float fvalue;

	csValue.TrimRight();

	if ( csValue.GetLength())
		c = csValue[csValue.GetLength()-1];
	else
		c = ' ';
	if ( ! isdigit(c))		// truncate the last char???
		csValue = csValue.Left( csValue.GetLength()-1);
	{		// convert . to , or vice versa if needed
	CString csdigit;
	int i = -1;

		csdigit.Format("%.9f", 1.023456789);		// all of the digits and the (possibly localized) decimal point
		if ( TCHAR(',') == csdigit[1])				// use a comma
			i = csValue.Find( TCHAR('.'));			// found a .
		else if ( TCHAR('.') == csdigit[1])			// use a .
			i = csValue.Find( TCHAR(','));			// found a ,

		if ( i >= 0)								// found it
			csValue.SetAt(i, csdigit[1]);				// move it in there
	}

	sscanf( (LPCSTR )csValue, "%f", &fvalue);
	switch( c)
		{
		case 'M' :
			dval = fvalue * 1000000;
			break;
		case 'k' :		// allow k
		case 'K' :
			dval = fvalue * 1000;
			break;
		case 'm' :
			dval = fvalue / 1000;
			break;
		case 'U' :		// allow U
		case 'u' :
			dval = fvalue / 1000000;
			break;
		case 'N' :
		case 'n' :
			dval = fvalue / 1.0e9;
			break;
		case 'P' :
		case 'p' :
			dval = fvalue / 1.0e12;
			break;
		default :
			dval = fvalue;
			break; // who knows
		}

	return (float )dval;
}


void	CopyArray( CObArray *pcDest, CObArray *pcSource)
{
int i, nsize;

	pcDest->RemoveAll();
	nsize = pcSource->GetSize();
	pcDest->SetSize( nsize);
	for ( i=0; i < nsize; i++)
		pcDest->SetAt(i, pcSource->GetAt(i) );

}


void	KillArray( CObArray *cKill)
{
int i;

	for ( i=cKill->GetSize(); i; i--)
	{
		CObject *pobj = cKill->GetAt(i-1);
		ASSERT( pobj != NULL);
#if _DEBUG
		pobj->AssertValid();
#endif
	}

	for ( i=cKill->GetSize(); i; i--)
	{
		CObject *pobj = cKill->GetAt(i-1);
		ASSERT( pobj != NULL);
#if _DEBUG
		pobj->AssertValid();
#endif
		delete pobj;
	}
	cKill->RemoveAll();

}


void CreateProgressBar( UINT uidCaption, UINT uMax)
{
CMainFrame *cw = (CMainFrame *)AfxGetMainWnd();

	if ( cw && cw->IsKindOf(RUNTIME_CLASS( CMainFrame)))
		{
		cw->CreateProgressBar( uidCaption, uMax);
		}
}

void CreateProgressBar( CString& csCaption, UINT uMax)
{
CMainFrame *cw = (CMainFrame *)AfxGetMainWnd();

	if ( cw && cw->IsKindOf(RUNTIME_CLASS( CMainFrame)))
		{
		cw->CreateProgressBar( csCaption, uMax);
		}
}


void ShowProgressBar( UINT uCurrent)
{
CMainFrame *cw = (CMainFrame *)AfxGetMainWnd();

	if ( cw && cw->IsKindOf(RUNTIME_CLASS( CMainFrame)))
		{
		cw->ShowProgressBar( uCurrent);
		}
}

void StepProgressBar( void)
{
CMainFrame *cw = (CMainFrame *)AfxGetMainWnd();

	if ( cw && cw->IsKindOf(RUNTIME_CLASS( CMainFrame)))
		{
		cw->StepProgressBar();
		}
}

void IncProgressBar( void)
{
CMainFrame *cw = (CMainFrame *)AfxGetMainWnd();

	if ( cw && cw->IsKindOf(RUNTIME_CLASS( CMainFrame)))
		{
		cw->IncProgressBar();
		}
}

void CloseProgressBar( void)
{
CMainFrame *cw = (CMainFrame *)AfxGetMainWnd();

	if ( cw && cw->IsKindOf(RUNTIME_CLASS( CMainFrame)))
		{
		cw->CloseProgressBar();
		}
}


/////////////////////////////////////////////////////////////////////////////
// combo box to channel adjustments
/////////////////////////////////////////////////////////////////////////////

enChannel ComboToChannel( int nChannel)
{
	switch ( nChannel)
	{
	case 0 :
		return chLeft;
	case 1 :
		return chRight;
	case 2 :
		return chNone;
	case 3 :
		return chBoth;
	default :
		return chNone;
	}
}

int ComboFromChannel( int nChannel)
{
	switch ( nChannel)
	{
	case chLeft :
		return 0;
	case chRight :
		return 1;
	case chNone :
		return 2;
	case chBoth :
		return 3;
	default :
		return 2;
	}
}

/////////////////////////////////////////////////////////////////////////////
// crossover to combobox adjustments
/////////////////////////////////////////////////////////////////////////////

// this is the styles in the combobox and equals the list in the list of styles
// in the dialog
static XOVERSTYLE xo1[] = { xoButterworth, xoNone };
static XOVERSTYLE xo2[] = { xoBessel, xoButterworth, xoChebychev, xoLinkwitz, xoNone };
static XOVERSTYLE xo3[] = { xoButterworth, xoNone };
static XOVERSTYLE xo4[] = { xoBessel, xoButterworth, xoGaussian, xoLegendre, xoLinear, xoLinkwitz, xoNone };


// ----------------------------------------------------------
//		XoverToCombo
// find the crossover in the list and return the index
// ----------------------------------------------------------
int XoverToCombo( int nOrder, XOVERSTYLE xStyle)
{
int i;
XOVERSTYLE *pstyle = xo1;

	switch( nOrder)
	{
	case 1 :
		pstyle = xo1;
		break;
	case 2 :
		pstyle = xo2;
		break;
	case 3 :
		pstyle = xo3;
		break;
	case 4 :
		pstyle = xo4;
		break;
	default :
		ASSERT(0);
		break;
	}

	for ( i=0; xoNone != pstyle[i]; i++)
		if ( pstyle[i] == xStyle)
			return i;

	ASSERT(0);
	return -1;
}

// ----------------------------------------------------------
//		ComboToXover
// given a combo index, return the xover style
// ----------------------------------------------------------
XOVERSTYLE ComboToXover( int nOrder, int nIndex)
{
XOVERSTYLE *pstyle = xo1;

	if ( ! nOrder)
		return xo1[0];		// random butterworth result

	switch( nOrder)
	{
	case 1 :
		pstyle = xo1;
		break;
	case 2 :
		pstyle = xo2;
		break;
	case 3 :
		pstyle = xo3;
		break;
	case 4 :
		pstyle = xo4;
		break;
	default :
		ASSERT(0);
		break;
	}

	return pstyle[ nIndex];

}


// ----------------------------------------------------------
//		SpinSetRange( CDialog *pDlg, UINT uidSpin, int iLow, int iHigh)
// given an int spin button, set the range on it
// ----------------------------------------------------------
int SpinSetRange( CDialog *pDlg, UINT uidSpin, int iLow, int iHigh)
{
CWnd *cwnd;

	cwnd = pDlg->GetDlgItem( uidSpin);		// the numdriver updown control
	if ( cwnd && cwnd->GetSafeHwnd())
	{
	CSpinButtonCtrl *pwnd;

		pwnd = (CSpinButtonCtrl *)cwnd;
		pwnd->SetRange( iLow, iHigh);
		return 0;
	}

	return 1;			// failure

}


// ----------------------------------------------------------
//		ComboFillString( CDialog *pDlg, UINT uidCombo, UINT uidStrings)
// given a combo box, fill it with strings delimited by "|"
// ----------------------------------------------------------

int ComboFillString( CDialog *pDlg, UINT uidCombo, UINT uidStrings)
{
CComboBox *pcombo = (CComboBox *)pDlg->GetDlgItem( uidCombo);
int is, ilast;

	ASSERT ( pcombo && pcombo->GetSafeHwnd());
	if ( ! (pcombo && pcombo->GetSafeHwnd()))
		return 1;			// failure

	{
	CString strin;
	CString struse;

		pcombo->ResetContent();
		strin.LoadString( uidStrings);
		ASSERT( ! strin.IsEmpty());

		ilast = -1;
		for ( is = strin.Find( _T("=")); is >=0; is = strin.Find( _T("="), is+1) )
		{
			struse = strin.Left( is);		// get up to the bar
			struse = struse.Right( is - ilast - 1);		// remove the preceding stuff
			pcombo->AddString( struse);
			ilast = is;
		}
					// we have one string left
		struse = strin.Right( strin.GetLength() - ilast - 1);
		pcombo->AddString( struse);

	}
	return 0;
}


// ----------------------------------------------------------
//		VerbalUpdateData( pWnd, bool)
// do an updatedata and squawk if necessary
// ----------------------------------------------------------

int VerbalUpdateData( CWnd *pWnd, BOOL bSave)
{
	ASSERT( bSave);			// only way this should get called
	if ( pWnd->UpdateData( bSave))
		return TRUE;

	return FALSE;

}

// ----------------------------------------------------------
//		AddStringSuffx( CString, UINT)
// ----------------------------------------------------------
void AddStringSuffix( CString &csSource, UINT uidSuffix, bool bSpace)
{
CString csuffix;

	if ( bSpace)
		csSource += _T(" ");

	csuffix.LoadString( uidSuffix);
	csSource += csuffix;

}
