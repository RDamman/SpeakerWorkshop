// dlgroom.h : header file
//
#ifndef DLGROOM

#include "dlgRmBox.h"
#include "dlgRmGen.h"
#include "dlgRmWal.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgRoom

class CDlgRoom : public CPropertySheet
{
	DECLARE_DYNAMIC(CDlgRoom)

// Construction
public:
	CDlgRoom(CWnd* pParentWnd, UINT iSelectPage = 0);

// Attributes
public:
	CDlgRoomWall	m_cWalls;
	CDlgRoomBoxes	m_cBoxes;
	CDlgRoomGeneral	m_cGeneral;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRoom)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgRoom();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDlgRoom)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgRoom)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#define DLGROOM
#endif
