// Named.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "DrawObj.h"
#include "Grid.h"
#include "DataTag.h"

typedef enum tagenuCoord
{
	ecXCoord = 0,
	ecYCoord = 1,
	ecY2Coord = 2,
	ecZCoord = 3
} eCoord;

class CDataLine : public CDrawObj
{
	DECLARE_SERIAL(CDataLine)
// Attributes
public:
	virtual void DoDraw( CDC *pDC, LPCRECT lpRcDraw = (LPRECT )NULL);	// draw the dataline object

private:
	CObjColor	m_ccLine;		// line color
	CObjColor	m_ccPhase;		// phase color
	DWORD		m_dwID;			// id of the line to draw
	BOOL		m_bShowPhase;	// show the phase of this guy (if he has one)
	BOOL		m_bShowAmp;		// show the amplitude of this guy (if he has one)
	BOOL		m_bShow3d;		// show 3d or not (not serialized)

	CNamed		*m_pParent;		// parent chart object

// Attribute set/get
public:
	CObjColor *GetColor()					{ return &m_ccLine;	}
	CObjColor *GetPhaseColor()				{ return &m_ccPhase; }
	DWORD	 GetDataID()					{ return m_dwID; }
	void	 SetDataID(DWORD dwNew)			{ m_dwID = dwNew; }
	void	 ShowPhase(BOOL bNew)			{ m_bShowPhase = bNew; }
	BOOL	 IsShowingPhase()				{ return m_bShowPhase;	}
	void	 ShowAmp(BOOL bNew)				{ m_bShowAmp = bNew; }
	BOOL	 IsShowingAmp()					{ return m_bShowAmp;	}
	void	 SetParent( CNamed *cNew)		{ m_pParent = cNew; }
	void	 SetShow3d( BOOL bNew)			{ m_bShow3d = bNew; }
	BOOL	 GetShow3d( void)				{ return m_bShow3d; }

// Operations
	virtual BOOL HitTest( CPoint cPt, UINT *pnFlags);
	virtual void DrawHighlight( CDC *pDC);
	virtual NAMETYPES GetType(void) const 	{ return ntDataLine; }

private:
	int		CreateDrawing( LPPOINT ptDraw, CDataSet *pData, DATASEL dtType, LPCRECT prcDraw);

// Implementation
protected:
	CDataLine();
public:
	CDataLine( CNamed *pParent);			// our parent object
	virtual ~CDataLine();
	CDataLine &operator=(const CDataLine &cIn);
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif

};

class CLegend : public CDrawObj
{
	DECLARE_SERIAL(CLegend)
// Attributes
public:
	virtual void DoDraw( CDC *pDC, LPCRECT lpRcDraw = (LPRECT )NULL);	// draw the dataline object

private:
	WORD	m_wShape;			// number of items in a column
	CStringArray m_pcNames;		// the set of data lines
	CDWordArray	 m_pcColors;	// the colors to draw

// Attribute set/get
public:
	void	AddStringData( LPCSTR lpNew, COLORREF rgbNew);
	void	ClearStringData( void)		{ m_pcNames.RemoveAll(); m_pcColors.RemoveAll(); }

// Operations
	virtual NAMETYPES GetType(void) const 	{ return ntLegend; }

// Implementation
public:
	CLegend();
	virtual ~CLegend();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

	CLegend &operator=(const CLegend &cIn);

#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif

};

class CBorder : public CDrawObj
{
	DECLARE_SERIAL(CBorder)
// Attributes
public:
	virtual void DoDraw( CDC *pDC, LPCRECT lpRcDraw = (LPRECT )NULL);	// draw the dataline object

// Attribute set/get
public:
// Operations
	virtual NAMETYPES GetType(void) const  	{ return ntBorder; }
	virtual BOOL HitTest( CPoint cPt, UINT *pnFlags);

// Implementation
public:
	CBorder();
	virtual ~CBorder();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

	CBorder &operator=(const CBorder &cIn);

#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif

};

class CInside : public CDrawObj
{
	DECLARE_SERIAL(CInside)
// Attributes
public:
	virtual void DoDraw( CDC *pDC, LPCRECT lpRcDraw = (LPRECT )NULL);	// draw the dataline object

// Attribute set/get
public:
// Operations
	virtual NAMETYPES GetType(void) const  	{ return ntInside; }
	virtual BOOL HitTest( CPoint cPt, UINT *pnFlags);

// Implementation
public:
	CInside();
	virtual ~CInside();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

	CInside &operator=(const CInside &cIn);

#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif

};



class CMarker : public CDrawObj
{
	DECLARE_SERIAL(CMarker)
// Attributes
public:
	virtual void DoDraw( CDC *pDC, LPCRECT lpRcDraw = (LPRECT )NULL);	// draw the dataline object

private:
	float	m_fLocation;
	CGrid	*m_pGrid;			// who to draw from

// Attribute set/get
public:
	void	SetLocation(float fNew)		{ m_fLocation = fNew; }
	float	GetLocation(void)			{ return m_fLocation; }
	void	SetGrid( CGrid *pNew)		{ m_pGrid = pNew; }

// Operations
	virtual NAMETYPES GetType(void) const 	{ return ntMarker; }

// Implementation
public:
	CMarker();
	virtual ~CMarker();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

	CMarker &operator=(const CMarker &cIn);

#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif

};


class CMiniChart : public CObject
{
protected: // create from serialization only
	DECLARE_SERIAL(CMiniChart)

public:
	CGrid		m_cGridX;		// the bottom grid
	CGrid		m_cGridY;		// the left hand side grid
	CGrid		m_cGridY2;		// the right hand side grid
public:
	CMiniChart();
	virtual ~CMiniChart();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o
};

class CSubChart : public CNamed
{

	friend class CDlgChart;
	friend class CDlgChGen;

protected: // create from serialization only
	DECLARE_SERIAL(CSubChart)

// Attributes
public:
	int GetDataCount( void);
	CSubChart();
	virtual int EditProperties(CWnd *pWnd, CObject *cSubject = NULL);	// bring up properties dbox

protected:
					// grid
	CString		m_csTitle;		// the title
	CGrid		m_cGridX;		// the bottom grid
	CGrid		m_cGridY;		// the left hand side grid
	CGrid		m_cGridY2;		// the right hand side grid
	CGridZ		m_cGridZ;		// the z-axis for 3d grids
	CObArray 	m_cDataLines;	// the set of data lines
	CLegend		m_cLegend;		// the legend if any
	CBorder		m_cBorder;		// the border (no need to serialize)
	CInside		m_cInside;		// inside the border (no need to serialize)
	CMarker		m_cMarker1;		// marker #1
	CMarker		m_cMarker2;		// second marker
	float		m_fMin;			// minimum X value - not serialized
	float		m_fMax;			// maximum X value - not serialized
	CTagArray	m_cTags;		// list of data tags - serialized

	void 		DrawBorder( CDC *pDC, CRect& crTotal);
	
// Operations
public:
	void		ToMiniChart( CMiniChart *pMini);
	void		FromMiniChart( CMiniChart *pMini);
	CString		&GetTitle()					{ return m_csTitle;	}
	void		SetTitle(LPCSTR lpSet)		{ m_csTitle = lpSet; }
	void		SetTitle(CString &csSet)	{ m_csTitle = csSet; }
	CDataLine  *GetDataAt( int i);
	CDataSet   *GetDatasetAt( int i);
	CGrid	   *GetGrid( eCoord ecGrid);
	CDataTag	*AddNote( CDataTag &cTag);			// add a new note
	void		DeleteNote( CDataTag *pTag);		// delete a note
	void		CreateDefault(LPCSTR szName, UNITMSR uUom );	// for a single object qk chart
	int			Attach( DWORD dwID, BOOL bUsePhase = FALSE);		// attach a dataset
	void		Detach( DWORD dwID);		// detach a dataset
	void		DetachAll( void);			// detach all datasets
	int	 		GetMember( DWORD dwID);		// find this dataset if it's attached and return Pos+1 or 0
	float		ConvertXLocation( int nIn);	// given an X location, return the float value...
	float		ConvertLocation( eCoord eCo, int nIn);	// given an xyy2 coord get value
	int			ConvertCoord( eCoord eCo, float fValue);	// given an xyy2 coord get value
	void		GetBorder( LPRECT lprcDest);
	void		SetMarkerLocation( CMarker *pMarker, int nNew);
	void		InheritDefault( CSubChart *pDefault);
	void		MakeDefault( int nDefault, CSubChart *pSource);
	UNITMSR		GetUom( void);

	int			Zoom( void );				// zoom back to 1:1
	int			Zoom( CPoint cPoint);		// zoom in on a point
	int			Zoom( CRect cRange);		// zoom into a box
	int			ZoomOut( CPoint cPoint);	// zoom out at a point


				// draw subsection function

	CDrawObj   *GetHitObject( CPoint cPt);					// did we hit anyone?
	void		SetHitObject( CDrawObj *cNew, BOOL bAdd);	// add (?) select an object
	CDrawObj   *GetHighlighted( void);						// get the first highlighted object
private:
	void		BuildDrawList( CObArray& cList);			// build the draw object list
	void		SetDefaultColor( CDataLine *cDestLine, UNITMSR uUom, int iIndex);	// get the default line color

// Implementation
public:
	float GetMaximum( void)	{ return m_fMax; }
	float GetMinimum( void)	{ return m_fMin; }
	virtual ~CSubChart();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o
	virtual void DoDraw( CDC *pDC, LPCRECT lpRcDraw = (LPRECT )NULL);	// draw the chart

	virtual CNamed *Duplicate();				// make a duplicate object (different id)
	CNamed &operator=(const CNamed &cIn);
	CSubChart &operator=(const CSubChart &cIn);

	virtual NAMETYPES GetType(void) const		{ return ntSubChart; }

#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:

};



class CChart : public CGraphed
{

//	friend class CDlgGenerator;

protected: // create from serialization only
	DECLARE_SERIAL(CChart)

// Attributes
protected:

public:

// Operations
public:
 	CChart();
	enum { USCHEMA = 241 };
	virtual int EditProperties(CWnd *pWnd, CObject *cSubject = NULL);	// bring up properties dbox

	virtual BOOL CreateChart( CNamed *cBase = NULL);		// build a new chart object to be graphed

// Implementation
public:
	virtual ~CChart();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

	virtual NAMETYPES GetType(void)	const	{ return ntChart; }

	virtual CNamed *Duplicate();				// make a duplicate object (different id)
	CNamed &operator=(const CNamed &cIn);
	CChart &operator=(const CChart &cIn);

#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:

};
