/////////////////////////////////////////////////////////////////////////////
//
// Grid.h : The chart grid object
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CGRIDOBJECT
#define CGRIDOBJECT

#include "DrawObj.h"

class CGrid : public CDrawObj
{

	DECLARE_SERIAL(CGrid)

	friend class CDlgGrid;
	friend class CSubChart;
// Attributes
public:
	CGrid();

	virtual int  CalcDraw( CDC *pDC, CRect& rcDraw);

	virtual void DoDraw( CDC *pDC, LPCRECT lpRcDraw = (LPRECT )NULL);	// draw the grid object
	virtual void CalcAutoTic( void);									// set up auto tics
	virtual void DrawScale( CDC *pDC, LPRECT lpRcDraw);

	virtual NAMETYPES GetType(void) const  	{ return ntGrid; }

	void	CopyFormat( CGrid *pDest);	// copy this format to the pDest
	void	SetZOffset( float fNew)		{ m_fZOffset = fNew; }
	float	GetZOFfset( void)			{ return m_fZOffset; }

protected:
	BOOL		m_bAutoScale;
	BOOL		m_bAutoTic;
	BOOL		m_bIsLog;		// is it logarithmic
	BOOL		m_bIsVertical;	// is it vertical???
	BOOL		m_bIsTopLeft;	// is it top/left????
	BOOL		m_bShowGrid;	// draw the grid lines
	BOOL		m_bShowTic;		// draw the tic marks
	BOOL		m_bShowTitle;	// draw the tic marks
	float		m_fMin;			// min value
	float		m_fMax;			// max value
	BOOL		m_bDrawMajor;	// show the grid lines???
	float		m_fMajor;		// major tic distance
	BOOL		m_bDrawMinor;	// show the grid lines???
	float		m_fMinor;		// minor tic distance

	CObjColor	m_ccMajor;		// grid color & style
	CObjColor	m_ccMinor;		// grid color & style

	CString		m_szTitle;		// title for the axis

				// storage for use by internals, not serialized
	CRect		m_rcDrew;		// where we drew to...
	float		m_fZOffset;		// the Z offset value to use

// Attribute set/get
public:
	float	GetMin(void)				{ return m_fMin;	}
	float	GetMax(void)				{ return m_fMax;	}
	void	SetMin(float fSet)			{ m_fMin = fSet;	}
	void	SetMax(float fSet)			{ m_fMax = fSet;	}
	BOOL	IsLog(void)					{ return m_bIsLog;	}
	void	SetLog(BOOL bSet)			{ m_bIsLog = bSet;	}
	BOOL	IsVertical(void)			{ return m_bIsVertical;	}
	void	SetVertical(BOOL bSet)		{ m_bIsVertical = bSet;	}
	void	SetTopLeft( BOOL bSet)		{ m_bIsTopLeft = bSet; }
	BOOL	IsTopLeft(void )			{ return m_bIsTopLeft; }
	void	SetTitle( LPCSTR lpszNew)	{ m_szTitle = lpszNew;	}
	CString &GetTitle()					{ return m_szTitle;		}
	BOOL	GetAuto( int nWhich)		{ return ( nWhich ? m_bAutoScale : m_bAutoTic); }
	void	SetAuto( int nWhich, BOOL bNew)		{ if ( nWhich) m_bAutoScale =bNew; else m_bAutoTic = bNew; }

// Operations
	void	FixLog( void);						// if log, make sure inbound
	int		ConvertCoord( float fIn);			// convert data value to location
	float	ConvertLocation( int nIn);			// given an X location, return the float value...

// Implementation
public:
	void SetColor( int nID, COLORREF clrNew);
	virtual ~CGrid();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

	CGrid &operator=(const CGrid &cIn);

#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif

protected:

private:
	void BuildLogGrid(CDC *pDC,  CFloatArray &faMajor, CFloatArray &faMinor);
	void BuildLinearGrid(CDC *pDC,  CFloatArray &faMajor, CFloatArray &faMinor);
	void DrawHLines(CDC *pDC, CFloatArray &fLines);
	void DrawVLines(CDC *pDC, CFloatArray &fLines);

};

// this is specifically for waterfall charts
class CGridZ : public CGrid
{
	DECLARE_SERIAL(CGridZ)

// attributes
protected:
	float	m_fSlope;		// slope as dy / dx (in screen coords!)
	float	m_fTotal;		// total length as a percent of the screen

public:
	float	GetSlope( void)		{ return m_fSlope; }
	void	SetSlope( float fNew)	{ m_fSlope = fNew; }
	float	GetTotal( void)		{ return m_fTotal; }
	void	SetTotal( float fNew)	{ m_fTotal = fNew; }

// Implementation
public:
	CGridZ();
	virtual ~CGridZ();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

	CGridZ &operator=(const CGridZ &cIn);
	CGridZ &operator=(const CGrid &cIn);

#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
};


#endif

