// Named.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CENCLOSURE

#include "Driver.h"

typedef struct tagCHAMBER
{
	bool		bUseChamber;			// are we using this chamber?

	bool		bPIsCircle;				// is the port a tube?
	bool		bUsePort;				// use a port??

	WORD		wDrivers;				// number of drivers
	bool		bParallel;				// drivers in parallel or series?
	float		fDriverRes;				// resistance in front of drivers
	WORD		wPorts;					// # of ports

	float		fVolume;				// volume of the box
	float		fPLength;				// length of the port
	float		fPRadius;				// radius of the port
	float		fPHeight;
	float		fPWidth;				// size of the rectangular port
	float		fQLeak;					// leakage losses (rAB)
	float		fQDamp;					// internal damping (rAL)
	float		fQPort;					// port losses for ported (rAP)
	float		fSeriesRes;				// series resistance before the driver

	DWORD		dwDriver;				// the driver associated with this enclosure
} CHAMBER;



class CEnclosure : public CGraphed
{

//	friend class CDlgGenerator;

protected: // create from serialization only
	DECLARE_SERIAL(CEnclosure)

	friend class CDlgEnParms;
	friend class CDlgEnGeneral;

// Attributes
public:
	CEnclosure *m_pTrial;				// the comparison enclosure, not serialized

protected:
	DWORD		m_dwResponse;			// for charting - not serialized?

	CHAMBER		m_cCham1;				// the two chambers
	CHAMBER		m_cCham2;

	bool		m_bInherit;				// frequency response range
	float		m_fStart;				// start frequency
	float		m_fDelta;				// delta
	int			m_nPoints;				// number of points in range



public:
	DWORD		GetDriver(int nWho = 1)		{ return ( (nWho == 1) ? m_cCham1.dwDriver : m_cCham2.dwDriver); }
	CHAMBER		*GetChamber( int nWho = 1)	{ return ( (nWho == 1) ? &m_cCham1 : &m_cCham2); }
			// dialog info

// Operations
public:
 	CEnclosure();
	virtual int EditProperties(CWnd *pWnd, CObject *cSubject = NULL);	// bring up properties dbox

			int SetNewProperties(CNamed *cNewObject);					// change the enclosure correctly

	virtual	void BuildDataSets( void);
	virtual	void OpBuildDataSets( void *);
	virtual BOOL CreateChart( CNamed *cBase = NULL);					// build a new chart object to be graphed
	void	GetSuffix(CString& csDest, int nSuffix);	// get the filename suffix for building
	int			BuildTrialData( void);						// set up encl and datasets for trial
	CEnclosure *GetTrial( void)			{ return m_pTrial; }
	int			ChangeTrialData( void);		// alter encl and datasets for trial
	void		DeleteTrialData( void);						// set up encl and datasets for trial
	void		ConvertMultiple( DRIVEPARM &dP, DRIVEEQUIV &dQ, int iDrive, bool bParallel);	// convert to multiple drivers

// Implementation
public:
	virtual ~CEnclosure();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

	virtual NAMETYPES GetType(void)	const 	{ return ntEnclosure; }

	virtual CNamed *Duplicate();				// make a duplicate object (different id)
	CEnclosure &operator=(const CEnclosure &cIn);
	CNamed &operator=(const CNamed &cIn);

	BOOL CalcResponse( CNamed **cDests);


#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:

};


#define CENCLOSURE

#endif
