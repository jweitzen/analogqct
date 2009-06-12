// AnaLogDoc.h : interface of the CAnaLogDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALOGDOC_H__B79C8CCA_79AC_4520_A6B7_DB18DD203414__INCLUDED_)
#define AFX_ANALOGDOC_H__B79C8CCA_79AC_4520_A6B7_DB18DD203414__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define StringLength 1000
#define MAC_DIM					6


class CAnaLogDoc : public CDocument
{
protected: // create from serialization only
	CAnaLogDoc();
	DECLARE_DYNCREATE(CAnaLogDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnaLogDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString QCATVersion;
	CString ShowConfirmMsg;
	int FrameSplit;
	CString FilterFolder;
	CString PrefferedHTML;
	CString Extension;
	bool DisableProgram;
	CString DayOfExpiry;
	CTime Today;
	CString ExecutablePath;
	bool StartUp;
	CString CurrentFilePathName;
	virtual ~CAnaLogDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAnaLogDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANALOGDOC_H__B79C8CCA_79AC_4520_A6B7_DB18DD203414__INCLUDED_)
