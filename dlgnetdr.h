// dlgnetdr.h : header file
//

#ifndef DLGNETDRIVER

#include "network.h"
#include "zFormEdt.h"

class	CDlgNetwork;

/////////////////////////////////////////////////////////////////////////////
// CDlgNetDriver dialog

class CDlgNetDriver : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgNetDriver)

// Construction
public:
	CDlgNetDriver();
	~CDlgNetDriver();

	CDlgNetwork		*m_pParent;

// Dialog Data
// ------------------------------------
		float	m_fOffset;

		CzFormatGroup		m_cfEdits;
// ------------------------------------
	//{{AFX_DATA(CDlgNetDriver)
	enum { IDD = IDD_NETDRIVE };
	CzFormatStatic	m_czStatOffset;
	CListBox	m_cComponentList;
	CString	m_csName;
	BOOL	m_bDoChart;
	BOOL	m_bOutOfPhase;
	//}}AFX_DATA

// local data
	CObArray	m_coNetlist;	// the array of passive components
	CObject		*m_pcRoot;		// the root object to look from
	int			m_nPrior;		// to see if we've been here
	int			m_nSelect;		// the first one to select
	DWORD		m_dwDriver;		// the driver dw
	int			m_nLabel;		// layout of the driver

public:
	void 		UseDrivers( CNetwork *pcNet, CObject *cSubject);
	void 		SetDrivers( CNetwork *pcNet);
	void 		ReadDriver( CObject *pSrc);
	void		WriteDriver( CObject *pDest);		// actually ZpPassive...
	void		UpdateIcon( int nIcon);
	void		SetObjIcon( UINT nID, UINT nIcon );

private:
	void		fill_Box();			// fill the list box
	void		set_Spin( int nID);		// set a spin button appropriately

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgNetDriver)
	public:
	virtual void OnFinalRelease();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgNetDriver)
	afx_msg void OnAddnew();
	afx_msg void OnRemove();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComplist();
	afx_msg void OnLayout();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnVert1();
	afx_msg void OnVert2();
	afx_msg void OnVert3();
	afx_msg void OnHorz1();
	afx_msg void OnHorz2();
	afx_msg void OnHorz3();
	afx_msg void OnChangeOffset();
	afx_msg void OnDochart();
	afx_msg void OnOutofphase();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgNetDriver)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define DLGNETDRIVER
#endif
