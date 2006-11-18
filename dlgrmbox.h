// dlgrmbox.h : header file
//

#ifndef ROOMBOX

/////////////////////////////////////////////////////////////////////////////
// CDlgRoomBoxes dialog

class CDlgRoomBoxes : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgRoomBoxes)

// Construction
public:
	CDlgRoomBoxes();
	~CDlgRoomBoxes();

// Dialog Data
	//{{AFX_DATA(CDlgRoomBoxes)
	enum { IDD = IDD_ROOMLIST };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgRoomBoxes)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRoomBoxes)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgRoomBoxes)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};


#define ROOMBOX
#endif
