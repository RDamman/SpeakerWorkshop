// Named.h : Named Components Class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef CROOM

class CRoom : public CNamed
{

//	friend class CDlgGenerator;

protected: // create from serialization only
	DECLARE_SERIAL(CRoom)

// Attributes
protected:
			// dialog info

// Operations
public:
 	CRoom();
	virtual int EditProperties(CWnd *pWnd, CObject *cSubject = NULL);	// bring up properties dbox

// Implementation
public:
	virtual ~CRoom();
	virtual void Serialize(CArchive& ar);	// overridden for Named i/o

	virtual NAMETYPES GetType(void)	const	{ return ntRoom; }

	virtual CNamed *Duplicate();				// make a duplicate object (different id)
	virtual CNamed &operator=(const CNamed &cIn);
	CRoom &operator=(const CRoom &cIn);

#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:

};


#define CROOM

#endif
