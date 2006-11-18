// dlggener.h : header file
//

 #include "generat.h"

 #include "dlgMls.h"
 #include "dlgNoise.h"
 #include "dlgPulse.h"
 #include "dlgSawto.h"
 #include "dlgSine.h"
 #include "dlgSquar.h"
 #include "dlgSweep.h"
 #include "dlgTones.h"
 #include "dlgGenGe.h"
 #include "dlgGenUs.h"	// both userdef and warble
 #include "dlgBurst.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgGenerator

class CDlgGenerator : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgGenerator)

// Construction
public:
	CDlgGenerator(CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
private:
	CDlgGenGeneral	m_cGeneral;
	CDlgBurst		m_cBurst;
	CDlgMls 		m_cMls;
	CDlgNoise		m_cNoise;
	CDlgPulse 		m_cPulse;
	CDlgSawtooth	m_cSawtooth;
	CDlgSine 		m_cSine;
	CDlgSquare		m_cSquare;
	CDlgSweep 		m_cSweep;
	CDlgTones		m_cTones;
	CDlgGenUserDef	m_cUserDef;
	CDlgGenWarble	m_cWarble;

	int				m_iLastPage;		// last page in use

// Operations
private:
	CPropertyPage *GetTypePage( GENTYPES nType);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGenerator)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

public:
	void SetGenerator( CGenerator *);
	void UseGenerator( CGenerator *);

// Implementation
public:
	virtual ~CDlgGenerator();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgGenerator)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgGenerator)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

/////////////////////////////////////////////////////////////////////////////
