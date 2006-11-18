// DlgVuMeter.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"
#include "DlgVuMeter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVuMeter dialog


CDlgVuMeter::CDlgVuMeter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVuMeter::IDD, pParent)
{
BOOL brslt;

	//{{AFX_DATA_INIT(CDlgVuMeter)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	brslt = Create( CDlgVuMeter::IDD, pParent);		// modeless, we're going

}


void CDlgVuMeter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVuMeter)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVuMeter, CDialog)
	//{{AFX_MSG_MAP(CDlgVuMeter)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVuMeter message handlers

void CDlgVuMeter::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
				// it's a close request
	ShowWindow( SW_HIDE);
}

void CDlgVuMeter::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();

	delete this;
}


// set the entry accordingly
void CDlgVuMeter::SetEntry( enVues enVu, float fValue)
{
UINT uid;

	switch( enVu)
	{
	case vuLeftMin :
		uid = IDC_LEFTMIN;
		m_fLMin = fValue;
		break;
	case vuLeftAve :
		uid = IDC_LEFTAVE;
		m_fLAve = fValue;
		break;
	case vuLeftMax :
		uid = IDC_LEFTMAX;
		m_fLMax = fValue;
		break;
	case vuRightMin :
		uid = IDC_RIGHTMIN;
		m_fRMax = fValue;
		break;
	case vuRightAve :
		uid = IDC_RIGHTAVE;
		m_fRAve = fValue;
		break;
	case vuRightMax :
		uid = IDC_RIGHTMAX;
		m_fRMax = fValue;
		break;
	default :
		uid = 0;
		ASSERT( 0);			// whoops
		break;
	}

	{
	CStatic *cst = (CStatic *)GetDlgItem( uid);
	CString csval;

		csval.Format( "%.0f", fValue);

		if ( cst)
			cst->SetWindowText( csval);
	}
}

void CDlgVuMeter::SetLeftEntries( float fMax, float fAve, float fMin)
{
	SetEntry( vuLeftMin, fMin);
	SetEntry( vuLeftAve, fAve);
	SetEntry( vuLeftMax, fMax);
}

void CDlgVuMeter::SetRightEntries( float fMax, float fAve, float fMin)
{
	SetEntry( vuRightMin, fMin);
	SetEntry( vuRightAve, fAve);
	SetEntry( vuRightMax, fMax);
}

void CDlgVuMeter::GetLeftEntries( float &fMax, float &fAve, float &fMin)
{
	fMin = m_fLMin;
	fAve = m_fLAve;
	fMax = m_fLMax;
}

void CDlgVuMeter::GetRightEntries( float &fMax, float &fAve, float &fMin)
{
	fMin = m_fRMin;
	fAve = m_fRAve;
	fMax = m_fRMax;
}


