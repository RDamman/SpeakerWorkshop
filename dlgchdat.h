// dlgchdat.h : header file
//

#ifndef CDLGCHDATA

#include "chart.h"

#include "ctrls.h"

#include "folder.h"


/////////////////////////////////////////////////////////////////////////////
// CDlgChData dialog

class CDlgChData : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgChData)

// Construction
public:
	CDlgChData();
	~CDlgChData();

// Dialog Data
	//{{AFX_DATA(CDlgChData)
	enum { IDD = IDD_CHDATA };
	CListBox	m_clDataList;
	BOOL	m_bShowPhase;
	BOOL	m_bShowData;
	int		m_nColor;
	int		m_nColor2;
	int		m_nLineStyle;
	int		m_nLineStyle2;
	int		m_nLineWeight;
	int		m_nLineWeight2;
	//}}AFX_DATA

							// ---------------------
	CObject			*m_cFirst;		// if we come up in datasets, the first to show

	CObArray m_cDatalines;	// the datalines we can use

	CColorBox m_cclrMajor;
	CColorBox m_cclrMinor;
	CLineStyleBox m_clsMajor;
	CLineStyleBox m_clsMinor;
	CLineWidthBox m_clwMajor;
	CLineWidthBox m_clwMinor;
	
	CFolder *m_cRoot;		// the root object for finding datasets

	int		m_nPrior;		// the prior dataset selection

 public:
   	void UseData( CNamed *cRoot, CNamed *cChart, CObArray *pcGen, CObject *cFirst);
	void SetData( CSubChart *cChart, CObArray *pcData);
	void ReadDataLine( CDataLine *pSrc);
	void WriteDataLine( CDataLine *pSrc);
	CDataSet *GetDataset( int nWhich);

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgChData)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgChData)
	afx_msg void OnRemove();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDatalist();
	afx_msg void OnAdddata();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDlgChData)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
};


#define CDLGCHDATA
#endif

