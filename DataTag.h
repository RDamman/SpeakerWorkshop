// DataTag.h: interface for the CDataTag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATATAG_H__ACCD7D0B_B2FB_4379_8D28_B1C7C0CFEE3C__INCLUDED_)
#define AFX_DATATAG_H__ACCD7D0B_B2FB_4379_8D28_B1C7C0CFEE3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObj.h"

class CDataTag;

typedef CArray< CDataTag, CDataTag>	CTagArray;		// array of DataTags


class CDataTag : public CDrawObj  
{
	DECLARE_SERIAL(CDataTag)
	// ---------------  private variables
private:
	int		m_iDataset;			// which dataset to apply the tag to
	float	m_fXValue;			// frequency or time coordinate
	CString	m_strText;			// text to put there
	CSubChart *m_pParent;		// the chart parent
								// -------- drawing stuff
	bool	m_bDrawLine;		// draw the line?
	int		m_iLineWeight;		// weight
	int		m_iLineStyle;		// style
	bool	m_bDrawBox;			// draw the box outline?
	bool	m_bFillBox;			// fill the box
	COLORREF m_rgbBoxColor;		// the fill color for the box
	CFxFont	m_cfFont;			// the font to use
	CPoint	m_cpTextOffset;		// where to put the text box
								//

	// ---------------  Virtual Methods
public:
	virtual void DoDraw( CDC *pDC, LPCRECT lpRcDraw = (LPRECT )NULL);	// draw the dataline object

	virtual NAMETYPES GetType(void) const	 { return ntDataTag; }
	virtual BOOL HitTest( CPoint cPt, UINT *pnFlags);
	virtual int EditProperties(CWnd *pWnd);		// bring up properties dbox

	// ---------------  Attribute set/get
public:
	CSubChart *GetParent( void) const		 { return m_pParent; }
	void	SetParent( CSubChart *pParent);			// set the parent
	int		GetDataset( void)	const		 { return m_iDataset; }
	void	SetDataset( int iNew);
	void	GetText( CString &strText) const { strText = m_strText; }
	void	SetText( LPCSTR strText);
	float	GetValue( void)	const			 { return m_fXValue; }
	void	SetValue( float fNew);
	void	SetTextOffset( const CPoint &cPoint);	// set the text offset 
	void	GetTextOffset( CPoint &cPoint)		 { cPoint = m_cpTextOffset; }
	CDataSet *GetDataPointer( void);

private:
	void	ParseString( CString &strOut, LPCSTR strIn);	// parse the input string

	// --------------- construction
public:
	CDataTag();
	CDataTag( CDataTag &cTag);
	virtual ~CDataTag();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

	CDataTag &operator=(const CDataTag &cIn);

	// ---------------  debug
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif


};

#endif // !defined(AFX_DATATAG_H__ACCD7D0B_B2FB_4379_8D28_B1C7C0CFEE3C__INCLUDED_)
