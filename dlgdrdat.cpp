// dlgdrdat.cpp : implementation file
//

#include "stdafx.h"
#include "audtest.h"

#include "zFormEdt.h"
#include "dlgdrdat.h"

#include "folder.h"

#include "dlgselec.h"
#include "audtedoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDrData property page

IMPLEMENT_DYNCREATE(CDlgDrData, CPropertyPage)

CDlgDrData::CDlgDrData() : CPropertyPage(CDlgDrData::IDD), m_cfEdits()
{
	EnableAutomation();
	//{{AFX_DATA_INIT(CDlgDrData)
	m_csFrequency = _T("");
	m_csImpedance = _T("");
	m_csSealed = _T("");
	m_csFreeAir = _T("");
	m_bUseDC = FALSE;
	m_csFreq30 = _T("");
	m_csFreq60 = _T("");
	m_csNearField = _T("");
	m_csTimeRes = _T("");
	m_csAddMass = _T("");
	m_csGated = _T("");
	m_csPort = _T("");
	//}}AFX_DATA_INIT
}

CDlgDrData::~CDlgDrData()
{
}

void CDlgDrData::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}

void CDlgDrData::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	m_cfEdits.DDX_All( pDX);

	//{{AFX_DATA_MAP(CDlgDrData)
	DDX_Control(pDX, IDC_PORT, m_cPort);
	DDX_Control(pDX, IDC_GATED, m_cGated);
	DDX_Control(pDX, IDC_STATVOLUME, m_czStatVolume);
	DDX_Control(pDX, IDC_STATMASS, m_czStatMass);
	DDX_Control(pDX, IDC_SEALED, m_cSealed);
	DDX_Control(pDX, IDC_HITSEAL, m_cHitSeal);
	DDX_Control(pDX, IDC_DELSEAL, m_cDelSeal);
	DDX_Control(pDX, IDC_DELMASS, m_cDelMass);
	DDX_Control(pDX, IDC_SCRL3, m_cScrlMass);
	DDX_Control(pDX, IDC_SCRL2, m_cScrlVolume);
	DDX_Control(pDX, IDC_VOLUME, m_cVolume);
	DDX_Control(pDX, IDC_MASS, m_cMass);
	DDX_Control(pDX, IDC_IMPEDANCE, m_cImpedance);
	DDX_Control(pDX, IDC_HITMASS, m_cHitMass);
	DDX_Control(pDX, IDC_ADDMASS, m_cAddMass);
	DDX_Text(pDX, IDC_FREQ, m_csFrequency);
	DDX_Text(pDX, IDC_IMPEDANCE, m_csImpedance);
	DDX_Text(pDX, IDC_SEALED, m_csSealed);
	DDX_Text(pDX, IDC_FREEAIR, m_csFreeAir);
	DDX_Check(pDX, IDC_DCRESIST, m_bUseDC);
	DDX_Text(pDX, IDC_FREQ30, m_csFreq30);
	DDX_Text(pDX, IDC_FREQ60, m_csFreq60);
	DDX_Text(pDX, IDC_NEARFREQ, m_csNearField);
	DDX_Text(pDX, IDC_PULSERES, m_csTimeRes);
	DDX_Text(pDX, IDC_ADDMASS, m_csAddMass);
	DDX_Text(pDX, IDC_GATED, m_csGated);
	DDX_Text(pDX, IDC_PORT, m_csPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDrData, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgDrData)
	ON_BN_CLICKED(IDC_HITFREQ, OnHitfreq)
	ON_BN_CLICKED(IDC_HITIMP, OnHitimp)
	ON_BN_CLICKED(IDC_HITSEAL, OnHitseal)
	ON_BN_CLICKED(IDC_HITFREE, OnHitfree)
	ON_BN_CLICKED(IDC_HITFREQ30, OnHitfreq30)
	ON_BN_CLICKED(IDC_HITNEAR, OnHitnear)
	ON_BN_CLICKED(IDC_HITPULSE, OnHitpulse)
	ON_BN_CLICKED(IDC_HITFREQ60, OnHitfreq60)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL1, OnDeltaposSpin)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_DELFREE, OnDelfree)
	ON_BN_CLICKED(IDC_DELFREQ, OnDelfreq)
	ON_BN_CLICKED(IDC_DELFREQ30, OnDelfreq30)
	ON_BN_CLICKED(IDC_DELFREQ60, OnDelfreq60)
	ON_BN_CLICKED(IDC_DELIMP, OnDelimp)
	ON_BN_CLICKED(IDC_DELNEAR, OnDelnear)
	ON_BN_CLICKED(IDC_DELPULSE, OnDelpulse)
	ON_BN_CLICKED(IDC_DELSEAL, OnDelseal)
	ON_BN_CLICKED(IDC_DELMASS, OnDelmass)
	ON_BN_CLICKED(IDC_HITMASS, OnHitmass)
	ON_BN_CLICKED(IDC_RADIO1, OnRadioButton)
	ON_BN_CLICKED(IDC_DELGATE, OnDelgate)
	ON_BN_CLICKED(IDC_DELPORT, OnDelport)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL2, OnDeltaposSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SCRL3, OnDeltaposSpin)
	ON_BN_CLICKED(IDC_RADIO2, OnRadioButton)
	ON_BN_CLICKED(IDC_HITPORT, OnHitport)
	ON_BN_CLICKED(IDC_HITGATE, OnHitgate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDlgDrData, CDialog)
	//{{AFX_DISPATCH_MAP(CDlgDrData)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDrData message handlers

static void use_Vars( CFolder *cRoot, CString& csOut, DWORD& dwOut, DWORD dwIn, UNITMSR nUom)
{
CNamed *cout;

	dwOut = dwIn;

	if ( dwIn)
		{
		cout = cRoot->GetItem( dwIn, TRUE);
		if ( cout && cout->IsType(ntDataSet, nUom))
			csOut = cout->GetFullName();
		else
			{
			dwOut = 0;
			csOut = _T("");
			}
		}
	else
		{
		csOut = _T("");
		}
}


// disable or enable windows based on added mass versus delta compliance method
void CDlgDrData::set_MassMethod( void)
{
	m_cDelSeal.EnableWindow( !m_bUseMass);
	m_cHitSeal.EnableWindow( !m_bUseMass);
	m_cVolume.EnableWindow( !m_bUseMass);
	m_cScrlVolume.EnableWindow( !m_bUseMass);
	m_cSealed.EnableWindow( !m_bUseMass);
	m_cDelMass.EnableWindow( m_bUseMass);
	m_cHitMass.EnableWindow( m_bUseMass);
	m_cMass.EnableWindow( m_bUseMass);
	m_cScrlMass.EnableWindow( m_bUseMass);
	m_cAddMass.EnableWindow( m_bUseMass);
}


//	Use the existing data to set things up
void CDlgDrData::UseDatas( CFolder *cRoot, CDriver *pcDriver)
{
DRIVEPARM dp;

	m_cRoot = cRoot;

	dp = *pcDriver->GetDriverParameters();
	use_Vars( cRoot, m_csFrequency, m_dwFrequency, dp.dwResponse, uomFreq);
	use_Vars( cRoot, m_csImpedance, m_dwImpedance, dp.dwImpedance, uomOhms);
	use_Vars( cRoot, m_csAddMass, m_dwAddMass, dp.dwAddMass, uomOhms);
	use_Vars( cRoot, m_csSealed, m_dwSealed, dp.dwSealed, uomOhms);
	use_Vars( cRoot, m_csFreeAir, m_dwFreeAir, dp.dwFreeAir, uomOhms);
	use_Vars( cRoot, m_csTimeRes, m_dwTimeRes, dp.dwTimeRes, uomTime);
	use_Vars( cRoot, m_csNearField, m_dwNearField, dp.dwNearField, uomFreq);
	use_Vars( cRoot, m_csFreq30, m_dwFreq30, dp.dwFreq30, uomFreq);
	use_Vars( cRoot, m_csFreq60, m_dwFreq60, dp.dwFreq60, uomFreq);
	use_Vars( cRoot, m_csGated, m_dwGated, dp.dwGated, uomFreq);
	use_Vars( cRoot, m_csPort, m_dwPort, dp.dwPort, uomFreq);
	m_fVolume = dp.fVolume * 1000;			// convert to litres
	m_fMass = dp.fMass;			// convert to litres
	m_bUseDC = dp.bUseDC;
	m_bUseMass = dp.bUseMass;
	m_fDCResistance = dp.fDCRes;
}

static void set_Vars( DWORD& dwOut, CString& csIn, DWORD dwIn)
{
	if ( csIn.GetLength())
		dwOut = dwIn;
	else
		dwOut = 0;
}

// set the driver parameters based on the dialog data
void CDlgDrData::SetDatas( CDriver *pcDriver)
{
DRIVEPARM dp;

	dp = *pcDriver->GetDriverParameters();

	set_Vars( dp.dwResponse, m_csFrequency, m_dwFrequency);
	set_Vars( dp.dwImpedance, m_csImpedance, m_dwImpedance);
	set_Vars( dp.dwAddMass, m_csAddMass, m_dwAddMass);
	set_Vars( dp.dwSealed, m_csSealed, m_dwSealed);
	set_Vars( dp.dwFreeAir, m_csFreeAir, m_dwFreeAir);
	set_Vars( dp.dwTimeRes, m_csTimeRes, m_dwTimeRes);
	set_Vars( dp.dwNearField, m_csNearField, m_dwNearField);
	set_Vars( dp.dwFreq30, m_csFreq30, m_dwFreq30);
	set_Vars( dp.dwFreq60, m_csFreq60, m_dwFreq60);
	set_Vars( dp.dwGated, m_csGated, m_dwGated);
	set_Vars( dp.dwPort, m_csPort, m_dwPort);

	dp.fVolume = m_fVolume / 1000;			// convert to m**3
	dp.fMass = m_fMass;
	dp.bUseDC = m_bUseDC;
	dp.bUseMass = m_bUseMass;
	dp.fDCRes = m_fDCResistance;

	pcDriver->SetDriverParameters( &dp);
}


static int do_HitButton( CFolder *cRoot, CString& csName, DWORD& dwID, UNITMSR uom)
{
CDlgSelectObject cdlg;
int nrslt;

	DBG_PRINT("[DlgDrDat.doHit] Select built...");

#if ALLOW_DBG
	if ( dwID)
		{
		CNamed *cnam = cRoot->GetItem( dwID);
		CString csname;
		if ( cnam && cnam->IsType( ntDataSet, uomAny))
			{
			csname = cnam->GetFullName();
			DBG_TWO("Dataset named %s", (LPCSTR )csname);
			}
		else
			if ( ! cnam)
				DBG_PRINT("[DlgDrDat.doHit] Item not found");
			else
				DBG_PRINT("[DlgDrDat.doHit] Not a dataset");
		switch( uom)
			{
			case uomTime :
				DBG_PRINT("[DlgDrDat.doHit] Using time");
				break;
			case uomFreq :
				DBG_PRINT("[DlgDrDat.doHit] Using frequency");
				break;
			case uomOhms :
				DBG_PRINT("[DlgDrDat.doHit] Using ohms");
				break;
			}
		}
	else
		DBG_PRINT("[DlgDrDat.doHit] Null item id");
	DBG_TWO("[DlgDrDat.doHit] Root Object: %s", cRoot->GetName());
#endif

	cdlg.SetParms( cRoot, dwID, ntDataSet, uom);
	
	DBG_PRINT("[DlgDrDat.doHit] Parameters set");

	nrslt = cdlg.DoModal();

	DBG_PRINT("[DlgDrDat.doHit] SelectObject dialog executed");

	if ( IDOK == nrslt)
		{
		dwID = cdlg.m_dwSelected;
		csName = _T("");
		if ( dwID)
			{
			CNamed *cnam = cRoot->GetItem( dwID);
			if ( cnam && cnam->IsType( ntDataSet, uom))
				csName = cnam->GetFullName();
			else
				dwID = 0;
			}
		return IDOK;
		}

	return nrslt;
		
}

void CDlgDrData::OnHitfreq() 
{
	if ( IDOK == do_HitButton( m_cRoot, m_csFrequency, m_dwFrequency, uomFreq) )
		UpdateData( FALSE);
}

void CDlgDrData::OnHitimp() 
{
	if ( IDOK == do_HitButton( m_cRoot, m_csImpedance, m_dwImpedance, uomOhms) )
		UpdateData( FALSE);
}

void CDlgDrData::OnHitseal() 
{
	if ( IDOK == do_HitButton( m_cRoot, m_csSealed, m_dwSealed, uomOhms) )
		UpdateData( FALSE);
}


void CDlgDrData::OnHitfree() 
{
	if ( IDOK == do_HitButton( m_cRoot, m_csFreeAir, m_dwFreeAir, uomOhms) )
		UpdateData( FALSE);
}

void CDlgDrData::OnHitmass() 
{
	if ( IDOK == do_HitButton( m_cRoot, m_csAddMass, m_dwAddMass, uomOhms) )
		UpdateData( FALSE);
}

void CDlgDrData::OnHitfreq30() 
{
	if ( IDOK == do_HitButton( m_cRoot, m_csFreq30, m_dwFreq30, uomFreq) )
		UpdateData( FALSE);
}

void CDlgDrData::OnHitnear() 
{
	if ( IDOK == do_HitButton( m_cRoot, m_csNearField, m_dwNearField, uomFreq) )
		UpdateData( FALSE);
}

void CDlgDrData::OnHitpulse() 
{
	if ( IDOK == do_HitButton( m_cRoot, m_csTimeRes, m_dwTimeRes, uomTime) )
		UpdateData( FALSE);
}

void CDlgDrData::OnHitfreq60() 
{
	if ( IDOK == do_HitButton( m_cRoot, m_csFreq60, m_dwFreq60, uomFreq) )
		UpdateData( FALSE);
}

void CDlgDrData::OnHitport() 
{
	if ( IDOK == do_HitButton( m_cRoot, m_csPort, m_dwPort, uomFreq) )
		UpdateData( FALSE);

}

void CDlgDrData::OnHitgate() 
{
	if ( IDOK == do_HitButton( m_cRoot, m_csGated, m_dwGated, uomFreq) )
		UpdateData( FALSE);
}


BOOL CDlgDrData::OnInitDialog() 
{
	{		// initialize the spinner format group
	FormatGroup cfdata[4] = { 
							{IDC_DCRES,	IDC_SCRL1, 0.0f, 100.0f, &m_fDCResistance},
							{IDC_VOLUME,IDC_SCRL2, 0.0f, 2000.0f, &m_fVolume},
							{IDC_MASS,	IDC_SCRL3, 0.0f, 2000.0f, &m_fMass},
							{0,0,0.0f,0.0f,NULL}
							};

		m_cfEdits.AttachGroup( this, cfdata);

	GroupMetric cfgrp[3] = {
						  { IDC_VOLUME, IDC_STATVOLUME, mtLitre },
						  { IDC_MASS, IDC_STATMASS, mtGram },
						  { 0, 0, mtNone }
						  };
		m_cfEdits.AttachMetrics( cfgrp);
	}

	CPropertyPage::OnInitDialog();

	UpdateData( TRUE);			// get the window handles

	CheckRadioButton( IDC_RADIO1, IDC_RADIO2, m_bUseMass ? IDC_RADIO2 : IDC_RADIO1);

	set_MassMethod();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgDrData::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_cfEdits.ProcessAllDelta( pNMHDR);
	
	*pResult = 0;
}


void CDlgDrData::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! m_cfEdits.ProcessLeftClick( nFlags, point))
		CPropertyPage::OnLButtonUp(nFlags, point);
}

void CDlgDrData::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if ( ! 	m_cfEdits.ProcessRightClick( nFlags, point))
		CPropertyPage::OnRButtonUp(nFlags, point);
}

void CDlgDrData::OnDelfree() 
{
	m_csFreeAir = _T("");
	UpdateData( FALSE);
}

void CDlgDrData::OnDelfreq() 
{
	m_csFrequency = _T("");
	UpdateData( FALSE);
	
}

void CDlgDrData::OnDelfreq30() 
{
	m_csFreq30 = _T("");
	UpdateData( FALSE);
	
}

void CDlgDrData::OnDelfreq60() 
{
	m_csFreq60 = _T("");
	UpdateData( FALSE);
	
}

void CDlgDrData::OnDelimp() 
{
	m_csImpedance = _T("");
	UpdateData( FALSE);
	
}

void CDlgDrData::OnDelnear() 
{
	m_csNearField = _T("");
	UpdateData( FALSE);
	
}

void CDlgDrData::OnDelpulse() 
{
	m_csTimeRes = _T("");
	UpdateData( FALSE);
	
}

void CDlgDrData::OnDelseal() 
{
	m_csSealed = _T("");
	UpdateData( FALSE);
	
}

void CDlgDrData::OnDelmass() 
{
	m_csAddMass = _T("");
	UpdateData( FALSE);
	
	
}

void CDlgDrData::OnDelgate() 
{
	m_csGated = _T("");
	UpdateData( FALSE);
	
}

void CDlgDrData::OnDelport() 
{
	m_csPort = _T("");
	UpdateData( FALSE);
	
}

void CDlgDrData::OnRadioButton() 
{
	m_bUseMass = ! IsDlgButtonChecked( IDC_RADIO1);
				// temporarily
	set_MassMethod();
}


