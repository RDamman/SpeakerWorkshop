// dlgrmwal.h : header file
//

#ifndef ROOMWALL

/////////////////////////////////////////////////////////////////////////////
// CDlgRoomWall dialog

class CDlgRoomWall : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgRoomWall)

// Construction
public:
	CDlgRoomWall();
	~CDlgRoomWall();

// Dialog Data
	//{{AFX_DATA(CDlgRoomWall)
	enum { IDD = IDD_ROOMWALL };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgRoomWall)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRoomWall)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgRoomWall)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};

#define ROOMWALL
#endif
