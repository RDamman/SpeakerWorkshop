#if !defined(AFX_COLORBUTTON_H__8B3566C7_83E1_11D4_BBF9_00A0C9923AAC__INCLUDED_)
#define AFX_COLORBUTTON_H__8B3566C7_83E1_11D4_BBF9_00A0C9923AAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorButton window

class CColorButton : public CButton
{
// Construction
public:
	CColorButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	COLORREF GetColor( void);
	COLORREF EditColor();
	void SetColor( COLORREF clrSet);
	virtual ~CColorButton();

	// Generated message map functions
protected:
	COLORREF m_rgbColor;
	//{{AFX_MSG(CColorButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CColorStatic window

class CColorStatic : public CStatic
{
// Construction
public:
	CColorStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	COLORREF GetColor( void);
	COLORREF EditColor();
	void SetColor( COLORREF clrSet);
	virtual ~CColorStatic();

	// Generated message map functions
protected:
	COLORREF m_rgbColor;

	//{{AFX_MSG(CColorStatic)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CColorEdit window

class CColorEdit : public CEdit
{
// Construction
public:
	CColorEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	COLORREF GetColor( void);
	COLORREF EditColor();
	void SetColor( COLORREF clrSet);
	virtual ~CColorEdit();

	// Generated message map functions
protected:
	COLORREF m_rgbColor;

	//{{AFX_MSG(CColorEdit)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORBUTTON_H__8B3566C7_83E1_11D4_BBF9_00A0C9923AAC__INCLUDED_)
