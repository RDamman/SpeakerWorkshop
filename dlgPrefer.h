// dlgdatas.h : header file
//


#ifndef DLGPREFERENCE

#include "dlgPrTra.h"
#include "dlgPrefN.h"
#include "dlgPrCha.h"
#include "dlgPrefM.h"
#include "dlgPrefReference.h"
#include "dlgPrefMarker.h"
#include "dlgPrfIm.h"
#include "dlgPrefGe.h"
#include "dlgPrefDebug.h"
#include "dlgPrefAcoustic.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgPreference

class CDlgPreference : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgPreference)

// Construction
public:
	CDlgPreference(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
//	CDlgPrefTransform	 	m_cTransform;
	CDlgPrefNetwork		 	m_cNetwork;
	CDlgPrefChart			m_cCharts;
	CDlgPrefMeasure			m_cMeasure;
	CDlgPrefReference		m_cReference;
	CDlgPrefMarker			m_cMarker;
	CDlgPrefImpedance		m_cImpedance;
	CDlgPrefGeneral			m_cGeneral;
	CDlgPrefDebug			m_cDebug;
	CDlgPrefAcoustic		m_cAcoustic;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPreference)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgPreference();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgPreference)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgPreference)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#define DLGPREFERENCE
#endif
