// dlgenclo.h : header file
//

#ifndef DLGENCLOSE

#include "dlgenGen.h"
#include "dlgEnPar.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgEnclosure

class CDlgEnclosure : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgEnclosure)

// Construction
public:
	CDlgEnclosure( CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CDlgEnGeneral		 	m_cGeneral;
	CDlgEnParms			 	m_cParms;
	CDlgEnParms			 	m_cParms2;	// parms for chamber 2

	CEnclosure *m_cWho;			// the base object ( enclosure)
	CEnclosure *m_cDupe;			// a duplicate of the object ( for cancel)
	BOOL	m_bWasApplied;		// did we do an apply


// Operations
public:
	void		UseObject( CEnclosure *cWho);
	void		SetObject( CEnclosure *cWho);

	void ProcessApply();
					// we have to do these manually because classwizard is hozed
	void ProcessCancel();
	void ProcessOk();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEnclosure)
	public:
	virtual void OnFinalRelease();
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgEnclosure();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgEnclosure)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

					// we have to manually do this using the ID_APPLY_NOW command
					// after reading the source for propertypage
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgEnclosure)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#define DLGENCLOSE
#endif
