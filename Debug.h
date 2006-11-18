// Debug.h: interface for the CDebug class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEBUG_H__BB2CE263_ED3B_11D2_AAC8_00A0C9923AAC__INCLUDED_)
#define AFX_DEBUG_H__BB2CE263_ED3B_11D2_AAC8_00A0C9923AAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDebug window

class CDebug : public CEdit
{
// Construction
public:
	CDebug();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDebug)
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_nLine;
	void AddLine( LPCSTR lpNew);
	virtual ~CDebug();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDebug)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTopDebug window

class CTopDebug : public CWnd
{
// Construction
public:
	CTopDebug();

// Attributes
public:
	CDebug	m_wDebug;

// Operations
public:
	static CTopDebug * GetDebugObj( void);
	void PrintTwo(LPCSTR lpcsOut, LPCSTR lpcsO2);
	void PrintInt(LPCSTR lpcsOut, int nOut);
	void PrintString( LPCSTR lpcsOut);
	void SetDebugLevel( int nNewLevel);
	int GetDebugLevel( void);
	void Init(CWnd *pParent);

private:
	CWnd * m_pParent;
	int m_nDebugLevel;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTopDebug)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTopDebug();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTopDebug)
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_DEBUG_H__BB2CE263_ED3B_11D2_AAC8_00A0C9923AAC__INCLUDED_)
