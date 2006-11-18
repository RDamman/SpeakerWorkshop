// dlgnetli.h : header file
//

#ifndef DLGNETLIST

#include "zFormEdt.h"

#include "Network.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgNetList dialog

class	CDlgNetwork;

class CDlgNetList : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgNetList)

// Construction
public:
	CDlgNetList();
	~CDlgNetList();

	CDlgNetwork		*m_pParent;

// Dialog Data
	//{{AFX_DATA(CDlgNetList)
	enum { IDD = IDD_NETLIST };
	CListBox	m_cComponentList;
	CString	m_csName;
	int		m_nType;
	CString	m_csCompUnit;
	//}}AFX_DATA

// local data
	int			m_nLabel;		// the label orientation for the component
	float		m_fMultip;		// the value multiplier

// ------
	CObArray	m_coNetlist;	// the array of passive components
	CFolder		*m_pcRoot;		// the root object to look from
	int			m_nPrior;		// to see if we've been here
	int			m_nSelect;		// the first one to select

// ------------------------------------
		float	m_fValue;		// the value of the object
		float	m_fResist;		// the internal resistance of the object

		CzFormatGroup		m_cfEdits;
// ------------------------------------

public:
	void		SetNetlist( CNetwork *pcNet);
	void		UseNetlist( CNetwork *pcNet, CObject *cSubject);	
	void 		ReadPassive( CObject *pSrc);
	CObject		*WritePassive( CObject *pDest);		// actually ZpPassives...
	void		UpdateIcon( int nIcon);
	void		SetObjIcon( UINT nID, UINT nIcon );

private:
	void		fill_Box();			// fill the list box
	void		set_Spin( int nID);		// set a spin button appropriately

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgNetList)
	public:
	virtual void OnFinalRelease();
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgNetList)
	afx_msg void OnAddnew();
	afx_msg void OnRemove();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComplist();
	afx_msg void OnLayout();
	afx_msg void OnSelchangeComptype();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHorz1();
	afx_msg void OnHorz2();
	afx_msg void OnHorz3();
	afx_msg void OnVert1();
	afx_msg void OnVert2();
	afx_msg void OnVert3();
	afx_msg void OnChangeValue();
	afx_msg void OnChangeResistance();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgNetList)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define DLGNETLIST
#endif
