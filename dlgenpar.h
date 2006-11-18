// dlgenpar.h : header file
//

#ifndef DLGENPARM

#include "folder.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgEnParms dialog

class CDlgEnParms : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgEnParms)

// Construction
public:
	CDlgEnParms(UINT nIdCaption = 0);
	~CDlgEnParms();

	void		UseObject( CEnclosure *cWho);
	void		SetObject( CEnclosure *cWho);

	DWORD	m_dwDriver;			// driver to use
 	CFolder *m_cRoot;
	int		m_nWho;				// who am i, chamber 1 or chamber 2???



// Dialog Data
	// --------------------------------
	float	m_fPHeight;
	float	m_fPLength;
	float	m_fPRadius;
	float	m_fPWidth;
	float	m_fQa;
	float	m_fQl;
	float	m_fQp;
	float	m_fVolume;
	float	m_fSeriesRes;

	CzFormatGroup		m_cfEdits;

	// --------------------------------


	//{{AFX_DATA(CDlgEnParms)
	enum { IDD = IDD_ENCLPARMS };
	CzFormatStatic	m_czStatWidth;
	CzFormatStatic	m_czStatVolume;
	CzFormatStatic	m_czStatRadius;
	CzFormatStatic	m_czStatLength;
	CzFormatStatic	m_czStatHeight;
	BOOL	m_bIsRect;
	BOOL	m_bUsePort;
	BOOL	m_bUseChamber;
	CString	m_csDriver;
	int		m_nDrivers;
	int		m_iSeriesPar;
	UINT	m_uPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgEnParms)
	public:
	virtual void OnFinalRelease();
	virtual BOOL OnApply();
	virtual void OnCancel();
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void		UpdateDriverName( void);
	// Generated message map functions
	//{{AFX_MSG(CDlgEnParms)
	afx_msg void OnHitdriver();
	afx_msg void OnChange();
	virtual BOOL OnInitDialog();
	afx_msg void OnUsechamber();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnHitnone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgEnParms)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define DLGENPARM
#endif

