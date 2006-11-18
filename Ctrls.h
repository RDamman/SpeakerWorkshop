// ctrls.h : header file
//

#ifndef CCTRLS

// ---------------------------------------------------------------------------
//			defines
// ---------------------------------------------------------------------------
#define NLINEWIDTH 4
#define NLINESTYLE 5
#define NLINECOLOR 16


/////////////////////////////////////////////////////////////////////////////
// global versions of the functions of interest


/////////////////////////////////////////////////////////////////////////////
// CzComboBox window

class CzComboBox : public CObject
{
// Construction
public:
	CzComboBox();

// Attributes
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

protected:
	int	m_nSelection;			// the current selection
	CComboBox *m_pBox;
	void SetCurrentSel( int nSelection);
	virtual void InitDialog( CComboBox *pBox);


// Operations
public:

// Overrides
// Implementation
public:
	virtual ~CzComboBox();

};



/////////////////////////////////////////////////////////////////////////////
// CColorBox window

class CColorBox : public CzComboBox
{
// Construction
public:
	CColorBox();

// Attributes
public:

// Operations
public:
	virtual void InitDialog( CComboBox *pBox);
	int SetSelection( COLORREF rgbUse);
	COLORREF GetSelection( void);

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	COLORREF  IdxToValue( int nIdx);
	int  ValueToIdx( COLORREF nRgb);

// Implementation
public:
	virtual ~CColorBox();

};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CLineStyleBox window

class CLineStyleBox : public CzComboBox
{
// Construction
public:
	CLineStyleBox();

// Attributes
public:
	int SetSelection( int nStyle);
	int GetSelection( void);

// Operations
public:
	virtual void InitDialog( CComboBox *pBox);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	int  IdxToValue( int nIdx);
	int  ValueToIdx( int nValue);

// Implementation
public:
	virtual ~CLineStyleBox();

	// Generated message map functions
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CLineWidthBox window

class CLineWidthBox : public CzComboBox
{
// Construction
public:
	CLineWidthBox();

// Attributes
public:

// Operations
public:
	virtual void InitDialog( CComboBox *pBox);
	int SetSelection( int nNew);
	int GetSelection( void);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	int  IdxToValue( int nIdx);
	int  ValueToIdx( int nValue);

// Overrides
	// ClassWizard generated virtual function overrides
// Implementation
public:
	virtual ~CLineWidthBox();

};

/////////////////////////////////////////////////////////////////////////////

#define CCTRLS
#endif
/////////////////////////////////////////////////////////////////////////////
