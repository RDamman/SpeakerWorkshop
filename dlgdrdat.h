// dlgdrdat.h : header file
//

#ifndef DLGDRDAT

#include "driver.h"
#include "folder.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDrData dialog

class CDlgDrData : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgDrData)

// Construction
public:
	CDlgDrData();
	~CDlgDrData();


	void SetDatas( CDriver *pData);
	void UseDatas( CFolder *cRoot, CDriver *pData);

	DWORD	m_dwFrequency;
	DWORD	m_dwImpedance;
	DWORD	m_dwAddMass;
	DWORD	m_dwSealed;
	DWORD	m_dwFreeAir;
	DWORD	m_dwTimeRes;
	DWORD	m_dwNearField;
	DWORD	m_dwFreq30;
	DWORD	m_dwFreq60;
	DWORD	m_dwGated;
	DWORD	m_dwPort;

	CFolder *m_cRoot;
	BOOL	m_bUseMass;

	// ------------------------ formatted edits
		float	m_fVolume;
		float	m_fDCResistance;
		float	m_fMass;

		CzFormatGroup		m_cfEdits;
	// ------------------------

// Dialog Data
	//{{AFX_DATA(CDlgDrData)
	enum { IDD = IDD_DRDATAS };
	CEdit	m_cPort;
	CEdit	m_cGated;
	CzFormatStatic	m_czStatVolume;
	CzFormatStatic	m_czStatMass;
	CEdit	m_cSealed;
	CButton	m_cHitSeal;
	CButton	m_cDelSeal;
	CButton	m_cDelMass;
	CSpinButtonCtrl	m_cScrlMass;
	CSpinButtonCtrl	m_cScrlVolume;
	CEdit	m_cVolume;
	CEdit	m_cMass;
	CEdit	m_cImpedance;
	CButton	m_cHitMass;
	CEdit	m_cAddMass;
	CString	m_csFrequency;
	CString	m_csImpedance;
	CString	m_csSealed;
	CString	m_csFreeAir;
	BOOL	m_bUseDC;
	CString	m_csFreq30;
	CString	m_csFreq60;
	CString	m_csNearField;
	CString	m_csTimeRes;
	CString	m_csAddMass;
	CString	m_csGated;
	CString	m_csPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgDrData)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	void set_MassMethod(void);

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgDrData)
	afx_msg void OnHitfreq();
	afx_msg void OnHitimp();
	afx_msg void OnHitseal();
	afx_msg void OnHitfree();
	afx_msg void OnHitfreq30();
	afx_msg void OnHitnear();
	afx_msg void OnHitpulse();
	afx_msg void OnHitfreq60();
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDelfree();
	afx_msg void OnDelfreq();
	afx_msg void OnDelfreq30();
	afx_msg void OnDelfreq60();
	afx_msg void OnDelimp();
	afx_msg void OnDelnear();
	afx_msg void OnDelpulse();
	afx_msg void OnDelseal();
	afx_msg void OnDelmass();
	afx_msg void OnHitmass();
	afx_msg void OnRadioButton();
	afx_msg void OnDelgate();
	afx_msg void OnDelport();
	afx_msg void OnHitport();
	afx_msg void OnHitgate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgDrData)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define DLGDRDAT
#endif

