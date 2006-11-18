// SetLocale.cpp: implementation of the CSetLocale class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "audtest.h"
#include "SetLocale.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSetLocale::CSetLocale(int category, LCID lcid) : m_iCategory(category)
{
TCHAR* tbuf;
CString locale;
int ilength;

	m_lastLocale = CString(_tsetlocale(m_iCategory, NULL));

	if ( lcid)			// we don't want just "C"
	{
	// get the language

		ilength = GetLocaleInfo(lcid, LOCALE_SENGLANGUAGE , NULL, 0);

		tbuf = new TCHAR[ilength + 1];

		if (!tbuf)
			return;
		tbuf[ilength] = NULL;
		ilength = GetLocaleInfo(lcid, LOCALE_SENGLANGUAGE , tbuf, ilength);
		locale = CString(tbuf) + _T("_");
		delete []tbuf;

		// Get the country.
		ilength = GetLocaleInfo(lcid,  LOCALE_SENGCOUNTRY, NULL, 0);
		tbuf = new TCHAR[ilength + 1];
		if (!tbuf)
			return;
		tbuf[ilength] = NULL;
		ilength = GetLocaleInfo(lcid,  LOCALE_SENGCOUNTRY, tbuf, ilength);
		locale +=tbuf;
		delete []tbuf;

		_tsetlocale(m_iCategory, locale);
	}
	else
		setlocale( m_iCategory, "C");


}

CSetLocale::~CSetLocale()
{
	_tsetlocale(m_iCategory, m_lastLocale);
} 

