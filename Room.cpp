// speaker.cpp : implementation of the CRoomArray classes
//


#include "stdafx.h"
#include "audtest.h"

#include "Room.h"

#include "dlgRoom.h"

// #include "dlggener.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CRoom

IMPLEMENT_SERIAL(CRoom, CNamed, VERSIONABLE_SCHEMA | 260)


/////////////////////////////////////////////////////////////////////////////
// CRoom construction/destruction

CRoom::CRoom()
{
	// TODO: add one-time construction code here
}

CRoom::~CRoom()
{

}

/////////////////////////////////////////////////////////////////////////////
// CRoom serialization

void CRoom::Serialize(CArchive& ar)
{
	CNamed::Serialize( ar);


	if (ar.IsStoring())
	{		// storing code here
	}
	else
	{
			// loading code here 
	}
}

int   CRoom::EditProperties(CWnd *pParent, CObject * )	// bring up properties dbox
{
CDlgRoom cgen( pParent);

//	cgen.UseRoom(this);


	if ( IDOK == cgen.DoModal())
		{
//		cgen.SetRoom(this);
		}

	return 0;
}



/////////////////////////////////////////////////////////////////////////////
// CRoom diagnostics

#ifdef _DEBUG
void CRoom::AssertValid() const
{
	CNamed::AssertValid();
}

void CRoom::Dump(CDumpContext& dc) const
{
	CNamed::Dump(dc);
}

#endif //_DEBUG


CNamed *CRoom::Duplicate(void )
{
CNamed *cnew = new CRoom();

	*cnew = *this;
	return cnew;
}


				// operators
CRoom &CRoom::operator=(const CRoom &cIn)
{
CNamed &cin = (CNamed &)cIn;

	*this = cin;
 	return *this;
}



CNamed &CRoom::operator=(const CNamed &cIn)
{
	CNamed::operator=( cIn);

 					// don't copy the id #
 	return *this;
}


