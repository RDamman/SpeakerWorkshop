// Named.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef FXFONT

typedef struct inFxFontInfo
{
	LOGFONT		m_lFont;			// the font descriptor
	COLORREF	m_rgbFont;			// the font color
	WORD		m_wEffect;
	int			m_nHeight;			// height in 10ths of a point
	char		cStyleName[50];		// 50 character style name
} FxFontInfo;

class CFxFont : public CObject
{
			// attributes
protected:
	LOGFONT		m_lFont;			// the font descriptor
	COLORREF	m_rgbFont;			// the font color
	WORD		m_wEffect;
	int			m_nHeight;			// height in 10ths of a point
	CString		m_csStyleName;		// name of the style

									// -- don't serialize and don't copy during an = operation
	CFont		*m_cfCurrent;		// the normal font
	CFont		*m_cfCurrentPrint;	// during printing this may be valid
	CFont		*m_cfCurrentVert;		// the normal font
	CFont		*m_cfCurrentPrintVert;	// during printing this may be valid

protected: // create from serialization only
	DECLARE_SERIAL(CFxFont)

public:
							// ------------------operations
	int 		DrawString( CDC *pDC, LPCTSTR lpszString, LPRECT lpRect, UINT nFormat );
	int 		DrawStringVertical( CDC *pDC, LPCTSTR lpszString, LPRECT lpRect, UINT nFormat );
	virtual int EditProperties(CWnd *pWnd = (CWnd *)NULL);		// bring up properties dbox

	CFont  *GetCurrentFont(CDC *pDC);			// caller must delete the CFont when appropriate
	CFont  *GetCurrentVert(CDC *pDC);			// caller must delete the CFont when appropriate
	void 	SetCurrentFont( CFont *cfNew);		// caller keeps the cfNew
	void	ClearPrinterFonts( void);

							// ------------------attributes
	void 	GetPrettyName(CString& csDest);
	void 	GetFontName(CString& csDest);
	void 	GetFontStyle(CString& csDest);
	int	 	GetFontSize();
	void	SetColor( COLORREF rgbColor)		{ m_rgbFont = rgbColor; }
	COLORREF GetColor( void)					{ return m_rgbFont; }
	void	SetEffect( WORD wEffect)			{ m_wEffect = wEffect; }
	WORD	GetEffect( void)					{ return m_wEffect;		}

							// ------------------implementation
	virtual void ReadIni( UINT nName);			// since fonts don't have names, caller provides it
	virtual void WriteIni( UINT nName);			// nName is actually an index into the resource file
	virtual void Serialize(CArchive& ar);
	CFxFont & operator=(const CFxFont &cIn);

private:
	void	clear_Fonts( void);			// delete the gdi fonts

public:
	CFxFont();
	virtual ~CFxFont();
};

#define FXFONT

#endif

