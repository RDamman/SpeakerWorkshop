// dlgprcha.h : header file
//

#ifndef DLGPREFCHART

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefChart dialog

#include "ColorButton.h"	// Added by ClassView
class CDlgPrefChart : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgPrefChart)

// Construction
public:
	CDlgPrefChart();
	~CDlgPrefChart();


	CFxFont		m_sysFonts[5];
	COLORREF	m_clrSystem[NUMAPPCOLORS];		// two system colors for now

// Dialog Data
	//{{AFX_DATA(CDlgPrefChart)
	enum { IDD = IDD_PREFCHART };
	CString	m_csAxisScale;
	CString	m_csAxisTitle;
	CString	m_csLegend;
	CString	m_csSubTitle;
	CString	m_csTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgPrefChart)
	public:
	virtual void OnFinalRelease();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CColorEdit m_clrTitle;
	CColorButton m_clrGrid;
	CColorButton m_clrBack;
	CColorButton m_clrInterior;
	// Generated message map functions
	//{{AFX_MSG(CDlgPrefChart)
	afx_msg void OnSelaxisscale();
	afx_msg void OnSelaxistitle();
	afx_msg void OnSellegend();
	afx_msg void OnSelsubtitle();
	afx_msg void OnSeltitle();
	virtual BOOL OnInitDialog();
	afx_msg void OnBackcolor();
	afx_msg void OnGridcolor();
	afx_msg void OnIntcolor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgPrefChart)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
private:
	void PrettyName( int i, CString &csDest);
	void EditFont( int nFont);
};

#define DLGPREFCHART
#endif

