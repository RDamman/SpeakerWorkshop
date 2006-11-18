#if !defined(AFX_DLGNOTE_H__FF3E033E_9B8D_453A_9737_D2684E2C8367__INCLUDED_)
#define AFX_DLGNOTE_H__FF3E033E_9B8D_453A_9737_D2684E2C8367__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNote.h : header file
//

#include "zFormEdt.h"
#include "ColorButton.h"	// Added by ClassView
#include "Ctrls.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgNote dialog

class CDlgNote : public CDialog
{
// variables
private:
	CSubChart *m_pChart;				// pointer to the chart

// Construction
public:
	CDlgNote(CWnd* pParent = NULL);   // standard constructor

	void	SetChart( CSubChart *pChart)	{ m_pChart = pChart; }

// Dialog Data
	// -----------------------------------------------
	float	m_fValue;

	CzFormatGroup		m_cfEdits;
	// -----------------------------------------------
	//{{AFX_DATA(CDlgNote)
	enum { IDD = IDD_ANNOTATE };
	int		m_iDataset;
	CString	m_strText;
	BOOL	m_bDrawBox;
	BOOL	m_bDrawLine;
	BOOL	m_bFillBox;
	CString	m_csTypeface;
	int		m_iLineStyle;
	int		m_iLineWeight;
	//}}AFX_DATA

	COLORREF		m_rgbFillColor;			// the fill color
	CFxFont			m_cfFont;				// the font to use
	CColorButton	m_clrFillColor;		// the fill color control
	CLineStyleBox	m_clsStyle;
	CLineWidthBox	m_clwWeight;
	bool			m_bNewObject;		// it's new, fill in defaults


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNote)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNote)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFillcolor();
	afx_msg void OnSelface();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNOTE_H__FF3E033E_9B8D_453A_9737_D2684E2C8367__INCLUDED_)
