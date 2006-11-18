// vwdrive.h : header file
//


#ifndef VWDRIVE

#include "audtevw.h"

/////////////////////////////////////////////////////////////////////////////
// CAudDriverView view

class CAudDriverView : public CAudchView
{
protected:
	CAudDriverView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAudDriverView)

// Attributes
private:
	int		m_iRowWidth;
	int		m_iColWidth;
	int		m_iMaxHeight;

	DWORD	m_dwImpedance;
	DWORD	m_dwResponse;		// the two attached datasets
public:

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudDriverView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAudDriverView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CAudDriverView)
	afx_msg void OnCalculateDriverParameters();
	afx_msg void OnMeasureDistortion();
	afx_msg void OnMeasureImpedance();
	afx_msg void OnMeasureFreeair();
	afx_msg void OnMeasurePulseresponse();
	afx_msg void OnMeasureSealed();
	afx_msg void OnMeasureNearfield();
	afx_msg void OnMeasureFarfield();
	afx_msg void OnMsrFreqOnaxis();
	afx_msg void OnMsrFreq30();
	afx_msg void OnMsrFreq60();
	afx_msg void OnMeasureMass();
	afx_msg void OnDriverSetequivalence();
	afx_msg void OnMeasureGatefreq();
	afx_msg void OnMeasurePort();
	afx_msg void OnCalcMerge();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

				// only vwdrive.cpp needs to use these
#ifdef DRIVEUSEOPS

#include "opItem.h"
#include "opRecord.h"


class COpDriveFreeAir : public COpMsrImpedance
{

public:
	virtual int		ProcessInput( void);
public:
	COpDriveFreeAir(CNamed *cTarget, CView *cView);
	~COpDriveFreeAir();

};

class COpDriveImpedance : public COpMsrImpedance
{

public:
	virtual int		ProcessInput( void);
public:
	COpDriveImpedance(CNamed *cTarget, CView *cView);
	~COpDriveImpedance();

};

class COpDriveSealed : public COpMsrImpedance
{

public:
	virtual int		ProcessInput( void);
public:
	COpDriveSealed(CNamed *cTarget, CView *cView);
	~COpDriveSealed();

};

class COpDriveAddedMass : public COpMsrImpedance
{

public:
	virtual int		ProcessInput( void);
public:
	COpDriveAddedMass(CNamed *cTarget, CView *cView);
	~COpDriveAddedMass();

};

class COpDrivePulse : public COpMsrTime
{

public:
	virtual int		ProcessInput( void);
public:
	COpDrivePulse(CNamed *cTarget, CView *cView);
	~COpDrivePulse();

};

class COpDriveNearfield : public COpMsrMicTotal
{

public:
	virtual int		ProcessInput( void);
public:
	COpDriveNearfield(CNamed *cTarget, CView *cView);
	~COpDriveNearfield();

};

class COpDriveFarfield : public COpMsrMicTotal
{

public:
	virtual int		ProcessInput( void);
public:
	COpDriveFarfield(CNamed *cTarget, CView *cView);
	~COpDriveFarfield();

};

class COpDriveFreqOnaxis : public COpMsrMicAnechoic
{

public:
	virtual int		ProcessInput( void);
public:
	COpDriveFreqOnaxis(CNamed *cTarget, CView *cView);
	~COpDriveFreqOnaxis();

};


class COpDriveFreq30 : public COpMsrMicAnechoic
{

public:
	virtual int		ProcessInput( void);
public:
	COpDriveFreq30(CNamed *cTarget, CView *cView);
	~COpDriveFreq30();

};

class COpDriveFreq60 : public COpMsrMicAnechoic
{

public:
	virtual int		ProcessInput( void);
public:
	COpDriveFreq60(CNamed *cTarget, CView *cView);
	~COpDriveFreq60();

};

class COpDriveGated : public COpMsrMicAnechoic
{

public:
	virtual int		ProcessInput( void);
public:
	COpDriveGated(CNamed *cTarget, CView *cView);
	~COpDriveGated();

};

class COpDrivePort : public COpMsrMicTotal
{

public:
	virtual int		ProcessInput( void);
public:
	COpDrivePort(CNamed *cTarget, CView *cView);
	~COpDrivePort();

};


#endif

/////////////////////////////////////////////////////////////////////////////


#define VWDRIVE
#endif
