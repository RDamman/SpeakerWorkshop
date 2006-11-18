// audtevw.h : interface of the CAudGenView class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CGENVW

#include "audtevw.h"

class CAudGenView : public CAudchView
{
protected: // create from serialization only
	CAudGenView();
	DECLARE_DYNCREATE(CAudGenView)

// Attributes
// Operations

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAudGenView)
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAudGenView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAudGenView)
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnSoundRecord();
	afx_msg void OnSoundLoop();
	afx_msg void OnSoundLooprecord();
	afx_msg void OnSoundPlay();
	afx_msg void OnSoundPlayagain();
	afx_msg void OnSoundRecordagain();
	afx_msg void OnSoundStop();
	afx_msg void OnSoundConverttodata();
	afx_msg void OnMeasureDistortion();
	afx_msg void OnMeasureFrequencyresponse();
	afx_msg void OnMeasureImpedance();
	afx_msg void OnMeasureIntermodulationdistortion();
	afx_msg void OnMeasureMicrophoneresponse();
	afx_msg void OnMeasurePassivecomponent();
	afx_msg void OnMeasureTimeresponse();
	afx_msg void OnMeasureGated();
	afx_msg void OnUpdateShowLeftinput(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowOutput(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowRightinput(CCmdUI* pCmdUI);
	afx_msg void OnShowLeftinput();
	afx_msg void OnShowOutput();
	afx_msg void OnShowRightinput();
	afx_msg void OnShowBothinput();
	afx_msg void OnUpdateShowBothinput(CCmdUI* pCmdUI);
	//}}AFX_MSG

private:
	void execute_Play( RECORDINGINFO *pRec);
	void execute_Record( RECORDINGINFO *pRec);

protected:

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#define CGENVW
#endif

