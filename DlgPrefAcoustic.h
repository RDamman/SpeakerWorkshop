#if !defined(AFX_DLGPREFACOUSTIC_H__75522041_CC30_11D4_BBF9_00A0C9923AAC__INCLUDED_)
#define AFX_DLGPREFACOUSTIC_H__75522041_CC30_11D4_BBF9_00A0C9923AAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPrefAcoustic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPrefAcoustic dialog

class CDlgPrefAcoustic : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgPrefAcoustic)

// Construction
public:
	CDlgPrefAcoustic();
	~CDlgPrefAcoustic();

// Dialog Data
	//{{AFX_DATA(CDlgPrefAcoustic)
	enum { IDD = IDD_PREFACOUSTIC };
	int		m_nMicChannel;
	int		m_nRefChannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgPrefAcoustic)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPrefAcoustic)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPREFACOUSTIC_H__75522041_CC30_11D4_BBF9_00A0C9923AAC__INCLUDED_)
