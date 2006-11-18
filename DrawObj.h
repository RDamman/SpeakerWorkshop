// Named.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CDRAWOBJ

#define DRW_INBOX 1
#define DRW_OUTBOX 2


#define odLeft 0
#define odUp   1
#define odRight 2
#define odDown 3


// ------------------------------------------------------
//		CDrawObj
// ------------------------------------------------------
class CDrawObj : public CObject
{
protected: // create from serialization only
	DECLARE_SERIAL(CDrawObj)

// Attributes
private:
	BOOL	m_bIsVisible;			// do we draw this when asked?
	BOOL	m_bIsHighlighted;		// is it selected ?
	RECT	m_rcDrawn;				// where it was drawn

	int		m_nSchema;				// not serialized!

public:
	CDrawObj();

	virtual void DoDraw( CDC *pDC, LPCRECT lpRcDraw = (LPRECT )NULL);	// draw the object
	virtual BOOL HitTest( CPoint cPt, UINT *pnFlags = NULL);	// do a hittest: type of hit -> nFlags 
	virtual	void DrawHighlight( CDC *pDC);

	BOOL	IsVisible( void)				{ return m_bIsVisible;	}
	void	SetVisible(BOOL bSet)			{ m_bIsVisible = bSet;	}
	BOOL	IsHighlighted( void)			{ return m_bIsHighlighted; }
	void	SetHighlight( BOOL bSet)		{ m_bIsHighlighted = bSet; }
	void	GetDrawRect( LPRECT lprcDest)	{ *lprcDest = m_rcDrawn; }
	void	SetDrawRect( LPRECT lprcNew)	{ m_rcDrawn = *lprcNew; }
	int		GetSchema( void)				{ return m_nSchema; }

	virtual NAMETYPES GetType(void ) const 	{ ASSERT( 0); return ntSubChart; }

// Operations
public:

// Implementation
public:
	virtual ~CDrawObj();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o
	virtual CDrawObj &operator=(const CDrawObj &cIn);

protected:

};


class CObjColor : public CObject
{
	DECLARE_SERIAL(CObjColor)
// Attributes
public:

private:
	COLORREF	m_clrRgb;			// color of pen
	int			m_nWidth;			// width of pen
	int			m_nStyle;			// pen style

// Attribute set/get
public:
	CObjColor();
	CObjColor( COLORREF clrClr, int nWidth = 1, int nStyle = PS_SOLID);
	void SetColor( COLORREF clrSet)			{ m_clrRgb = clrSet; 	}
	COLORREF GetColor( void) const 			{ return m_clrRgb;		}
	void SetWidth( int nWidth)				{ m_nWidth = nWidth; }
	int  GetWidth()	const 					{ return m_nWidth;		}
	void SetStyle( int nStyle)				{ m_nStyle = nStyle;	}
	int  GetStyle()	const 					{ return m_nStyle;		}
	ColorDefinition GetDefinition();
	void SetDefinition( ColorDefinition *pDef);

	CPen *BuildPen();	// build a pen based on this color setting

// Operations

// Implementation
public:
	virtual ~CObjColor();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o
	CObjColor &operator=(const CObjColor &cIn);

};


#define CDRAWOBJ

#endif
