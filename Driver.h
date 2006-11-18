// Named.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CDRIVERH

#include "Xform.h"

typedef enum tagenResponse
	{
	rsResponse = 0,				// response curve
	rsImpedance = 1,			// impedance
	rsFreeAir = 2,				// impedance in free air
	rsSealed = 3,				// sealed box impedance
	rsAddMass = 4,				// added mass method
	rsTimeRes = 5,				// time/pulse response (not required)
	rsNearField = 6,			// nearfield response
	rsFreq30 = 7,				// 30 degrees response
	rsFreq60 = 8,				// 60 degrees response
	rsGated = 9,				// gated
	rsPort = 10					// port response
	} enResponse;


typedef struct tagDriveparm
	{
					// ----------- calculated
	float	fFs;					// Resonant frequency
	float	fLe;					// inductance
	float	fQms;					// mechanical Q
	float	fQes;					// electrical Q
	float	fQts;					// total Q
	float	fRe;					// dc resistance
	float	fVas;					// effective compliance
					// ----------- provided
//	float	fDiameter;				// diameter
	float	fPistonArea;			// effective piston area
	float	fXmax;					// maximum excursion
	float	fSensitivity;			// sensitivity in w/m
	float	fVolume;				// volume of sealed box
	float	fMass;					// added mass
	float	fDCRes;					// DC resistance???
	BOOL	bUseDC;					// user has supplied DC resistance
	BOOL	bUseMass;				// use added mass method
	float	fBL;					// motor strength of driver
	float	fPe;					// maximum power input
					// ----------- now the datasets
	DWORD	dwResponse;				// response curve
	DWORD	dwImpedance;			// impedance
	DWORD	dwFreeAir;				// impedance in free air
	DWORD	dwSealed;				// sealed box impedance
	DWORD	dwAddMass;				// added mass method
	DWORD	dwTimeRes;				// time/pulse response (not required)
	DWORD	dwNearField;			// nearfield response
	DWORD	dwFreq30;				// 30 degrees response
	DWORD	dwFreq60;				// 60 degrees response
	DWORD	dwGated;				// gated frequency response
	DWORD	dwPort;					// the port frequency response
	}	DRIVEPARM;


// driver equivalent circuit
//		see speaker builder 5/94
//		-Re-+-L1a--+-L1b--+--+--+
//			|-R1---|      |  |  |
//					      R2 L2 C2
//					      |  |  |
//		------------------+--+--+
typedef struct tagDriveequiv
	{
	double	fRe;
	double	fL1a;
	double	fR1;
	double	fL1b;
	double	fR2;
	double	fL2;
	double	fC2;
	}  DRIVEEQUIV;

class CDriver : public CGraphed
{

protected: // create from serialization only
	DECLARE_SERIAL(CDriver)

// Attributes
protected:
	DRIVEPARM		m_DP;
	DRIVEEQUIV		m_DEq;

			// dialog info

// Operations
public:
 	CDriver();
	virtual int EditProperties(CWnd *pWnd, CObject *cSubject = NULL);	// bring up properties dbox

	virtual BOOL CreateChart( CNamed *cBase = NULL);	// build a new chart object to be graphed
	const DRIVEPARM	*GetDriverParameters()					{ return &m_DP; }
	void	SetDriverParameters( DRIVEPARM *pDP)		{ m_DP = *pDP; }
	const DRIVEEQUIV	*GetDriverEquiv()					{ return &m_DEq; }
	void	SetDriverEquiv( DRIVEEQUIV *pDP)		{ m_DEq = *pDP; }
	DWORD	GetImpedance()									{ return m_DP.dwImpedance; }
	DWORD	GetResponse()									{ return m_DP.dwResponse; }
	DWORD	GetResponse(int nWhich);
	void	SetResponse( int nWhich, DWORD dwNew);
	int		ValidateResponse( int nWhich);				// make sure response is valid
	void	ValidateCurves(void );						// make sure all curves are valid
	DWORD	GetSealed()										{ return m_DP.dwSealed; }
	DWORD	GetAddMass()									{ return m_DP.dwAddMass; }
	DWORD	GetFreeAir()									{ return m_DP.dwFreeAir; }
	DWORD	GetTimeResponse()								{ return m_DP.dwTimeRes; }
	int		CalculateDriverParameters(CDataSet *cDest, bool bDoFree );	// calc thiele stuff and return .estimate
	int		CalculateDriverParameters(CDataSet *cDest, bool bDoFree , float fStart, float fEnd ); // windowed
	void	ConvertDQtoDP( DRIVEPARM &DP, DRIVEEQUIV &DQ);
	int		UseDriverEquiv(CDataSet *cDest, DRIVEEQUIV &DQ );			// calc thiele stuff and return .estimate

private:

// Implementation
public:
	virtual ~CDriver();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

	virtual NAMETYPES GetType(void) const		{ return ntDriver; }

	virtual CNamed *Duplicate();				// make a duplicate object (different id)
	CNamed &operator=(const CNamed &cIn);
	CDriver &operator=(const CDriver &cIn);

#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:

};


#define CDRIVERH

#endif
