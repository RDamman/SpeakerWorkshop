// dlgdrpar.h : header file
//

#ifndef DLGDRPARMS

#include "Driver.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDrParms dialog

class CDlgDrParms : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgDrParms)

// Construction
public:
	CDlgDrParms();
	~CDlgDrParms();

	void SetParms( CDriver *pData);
	void UseParms( CDriver *pData);

	// --------------------------------------------------------
	float	m_fL1;
	float	m_fR1;
	float	m_fBL;		// motor strength
	float	m_fPe;		// power limit
	float	m_fSense;	// sensitivity

	float	m_fRe;
	float	m_fDiameter;	// in cm**2
	float	m_fFs;
	float	m_fLe;
	float	m_fQes;
	float	m_fQms;
	float	m_fQts;
	float	m_fVas;		// Vas in litres
	float	m_fXmax;	// Xmax in centimeters

	CzFormatGroup		m_cfEdits;
	// --------------------------------------------------------

// Dialog Data
	//{{AFX_DATA(CDlgDrParms)
	enum { IDD = IDD_DRPARMS };
	CzFormatStatic	m_czStatVas;
	CzFormatStatic	m_czStatMax;
	CzFormatStatic	m_czStatDiam;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgDrParms)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgDrParms)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposAll(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgDrParms)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define DLGDRPARMS
#endif
