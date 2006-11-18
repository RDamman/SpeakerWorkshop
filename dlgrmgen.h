// dlgrmgen.h : header file
//

#ifndef ROOMGENERAL

/////////////////////////////////////////////////////////////////////////////
// CDlgRoomGeneral dialog

class CDlgRoomGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgRoomGeneral)

// Construction
public:
	CDlgRoomGeneral();
	~CDlgRoomGeneral();

// Dialog Data
	//{{AFX_DATA(CDlgRoomGeneral)
	enum { IDD = IDD_ROOMGENERAL };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgRoomGeneral)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRoomGeneral)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgRoomGeneral)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define ROOMGENERAL
#endif
