// SetLocale.h: interface for the CSetLocale class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETLOCALE_H__5A69B3C1_D9A7_4FCA_9B6D_184E4C523817__INCLUDED_)
#define AFX_SETLOCALE_H__5A69B3C1_D9A7_4FCA_9B6D_184E4C523817__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <locale.h>

class CSetLocale  
{
private:
	int m_iCategory;
	CString m_lastLocale;
public:
	CSetLocale(int iCategory, LCID lcid = LOCALE_USER_DEFAULT);
	virtual ~CSetLocale();

};

#endif // !defined(AFX_SETLOCALE_H__5A69B3C1_D9A7_4FCA_9B6D_184E4C523817__INCLUDED_)
