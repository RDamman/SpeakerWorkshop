// XformGoal.h: interface for the CXformGoal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XFORMGOAL_H__D4ED4DDB_3D76_4FE4_9D20_0BAF8BEE72DF__INCLUDED_)
#define AFX_XFORMGOAL_H__D4ED4DDB_3D76_4FE4_9D20_0BAF8BEE72DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xform.h"
#include "DlgCreateGoal.h"

class CXformGoal : public CXtransform  
{
public:
		selGoalType	m_isUseWhich;
		int			m_nHighLow;
		int			m_nOrder;
		int			m_nType;
		DWORD		m_dwDriver;
		DWORD		m_dwDataset;
		float		m_fFS;
		float		m_fValue;
		float		m_fStart;
		float		m_fEnd;			// for approximating

public:
	virtual	int		DoOperation( CNamed *cdDest);

	virtual UINT GetNameID()				{ return IDOP_GOAL; }
	virtual UINT GetSuffix(void ) 			{ return IDSUF_GOAL; }

private:
	void	GenPoly( double *pPoly);	// create the crossover polynomial

public:
	CXformGoal( CObject *cTarget);		// must be named and in the tree
	virtual ~CXformGoal();

};

#endif // !defined(AFX_XFORMGOAL_H__D4ED4DDB_3D76_4FE4_9D20_0BAF8BEE72DF__INCLUDED_)
