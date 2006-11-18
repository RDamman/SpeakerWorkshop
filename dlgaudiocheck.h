// DlgAudioCheck.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAudioCheck dialog

#ifndef DLGAUDIOCHECK

#ifndef _INC_MMSYSTEM
#include "mmsystem.h"
#endif

class CDlgAudioCheck : public CDialog
{
// Construction
public:
	static int CheckOutput( void);
	static int CheckInput( void);
	static int CheckDuplex( void);
	CDlgAudioCheck(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAudioCheck)
	enum { IDD = IDD_AUDIOCHECK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAudioCheck)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetIDText( int nID, UINT uidString);
	// Generated message map functions
	//{{AFX_MSG(CDlgAudioCheck)
	virtual BOOL OnInitDialog();
	afx_msg void OnMoreinput();
	afx_msg void OnMoreoutput();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void check_All( int nTxt, int nInStat, int nOutStat, int nDupStat);
	void check_Duplex( int nTxt, int nStyle);
	void check_Fill( int nTxt, int nStyle);
};

#define CHECK_SUCCESS 0
#define CHECK_FAILED  1
#define CHECK_PARTIAL 2


#define DLGAUDIOCHECK 1
#endif
/////////////////////////////////////////////////////////////////////////////
// CDlgAudchkInput dialog

class CDlgAudchkInput : public CDialog
{
// Construction
public:
	CDlgAudchkInput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAudchkInput)
	enum { IDD = IDD_AUDCHKIN };
	CListBox	m_cFormats;
	CButton	m_cPrevious;
	CButton	m_cNext;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAudchkInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetIDText( int nID, UINT uidString);

	// Generated message map functions
	//{{AFX_MSG(CDlgAudchkInput)
	virtual BOOL OnInitDialog();
	afx_msg void OnNext();
	afx_msg void OnPrevious();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void fill_Dialog( int nDevice);
	int m_nDevice;
	int m_nMaxDev;
	WAVEINCAPS m_Caps;

};
/////////////////////////////////////////////////////////////////////////////
// CDlgAudchkOutput dialog

class CDlgAudchkOutput : public CDialog
{
// Construction
public:
	CDlgAudchkOutput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAudchkOutput)
	enum { IDD = IDD_AUDCHKOUT };
	CListBox	m_cFormats;
	CListBox	m_cSpecials;
	CButton	m_cPrevious;
	CButton	m_cNext;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAudchkOutput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetIDText( int nID, UINT uidString);

	// Generated message map functions
	//{{AFX_MSG(CDlgAudchkOutput)
	virtual BOOL OnInitDialog();
	afx_msg void OnPrevious();
	afx_msg void OnNext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void fill_Dialog( int nDevice);
	int m_nDevice;
	int m_nMaxDev;
	WAVEOUTCAPS m_Caps;

};
