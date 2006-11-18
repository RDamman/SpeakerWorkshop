#if !defined(AFX_DLGVUMETER_H__DBC692C1_D28E_11D4_BBF9_00A0C9923AAC__INCLUDED_)
#define AFX_DLGVUMETER_H__DBC692C1_D28E_11D4_BBF9_00A0C9923AAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVuMeter.h : header file
//

typedef enum tagenVues
	{
	vuLeftMin = 0,
	vuLeftAve = 1,
	vuLeftMax = 2,
	vuRightMin = 3,
	vuRightAve = 4,
	vuRightMax = 5
	} enVues;

/////////////////////////////////////////////////////////////////////////////
// CDlgVuMeter dialog

class CDlgVuMeter : public CDialog
{
// Construction
private:
	float	m_fRMax;
	float	m_fRAve;
	float	m_fRMin;
	float	m_fLMax;
	float	m_fLAve;
	float	m_fLMin;
public:
	CDlgVuMeter(CWnd* pParent = NULL);   // standard constructor

	void SetEntry( enVues enVu, float fValue);
	void SetLeftEntries( float fMax, float fAve, float fMin);
	void SetRightEntries( float fMax, float fAve, float fMin);
	void GetLeftEntries( float &fMax, float &fAve, float &fMin);
	void GetRightEntries( float &fMax, float &fAve, float &fMin);

// Dialog Data
	//{{AFX_DATA(CDlgVuMeter)
	enum { IDD = IDD_VUMETER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVuMeter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVuMeter)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVUMETER_H__DBC692C1_D28E_11D4_BBF9_00A0C9923AAC__INCLUDED_)
