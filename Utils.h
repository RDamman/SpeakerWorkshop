
/////////////////////////////////////////////////////////////////////////////
// Utils.h -- the global program utilities
//
/////////////////////////////////////////////////////////////////////////////

#ifndef ZUTILS

void CommaFormat( CString &csDest, int nValue);
void  FullFormatValue( CString &csDest, float fValue, int nDecimal = 2);
float FormatValue( float fValue, CString& csUnit);
BOOL IsValidString( CString& csValue);
float UnformatValue( float fValue, CString& csUnit);
float UnformatValue( CString& csValue);

void	CopyArray( CObArray *pcDest, CObArray *pcSource);
void	KillArray( CObArray *pcKill);

void CreateProgressBar( UINT uidCaption, UINT uMax);
void CreateProgressBar( CString& csCaption, UINT uMax);
void ShowProgressBar( UINT uCurrent);
void StepProgressBar( void);
void IncProgressBar( void);
void CloseProgressBar( void);

enChannel ComboToChannel( int nChannel);
int ComboFromChannel( int nChannel);

// Crossover Style to Combo Box conversion
int XoverToCombo( int nOrder, XOVERSTYLE xStyle);
XOVERSTYLE ComboToXover( int nOrder, int nIndex);
int ComboFillString( CDialog *pDlg, UINT uidCombo, UINT uidStrings);
int SpinSetRange( CDialog *pDlg, UINT uidSpin, int iLow, int iHigh);


// this is a simple class to allow for simple deletion on program exit
class	CTempStorage
	{
	public:
						// used by fft and ifft
		double *dSine;
		double *dCosine;
		int		nPower;	// power used for these guys
public:
	CTempStorage();
	~CTempStorage();
	};

extern CTempStorage cTempStore;

int VerbalUpdateData( CWnd *pWnd, BOOL bSave);					// do an updatedata(TRUE) and squawk if errors

void AddStringSuffix( CString &csSource, UINT uidSuffix, bool bSpace = TRUE);		// add a suffix to a string


#define ZUTILS

#endif
