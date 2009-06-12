// FilterLogDoc.h : interface of the CFilterLogDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILTERLOGDOC_H__E28B0D6B_94F7_41AF_9394_FD4A2294E337__INCLUDED_)
#define AFX_FILTERLOGDOC_H__E28B0D6B_94F7_41AF_9394_FD4A2294E337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fstream.h>
#include "FilterInfo.h"
#define NoStringArrayElements 6
#define StringLength 1000
#define NoFilterInfoElements 8

class CFilterLogDoc : public CDocument
{
protected: // create from serialization only
	CFilterLogDoc();
	DECLARE_DYNCREATE(CFilterLogDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilterLogDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool m_Updating;
	CStringArray m_FilterInfo;
	CString m_ExecutablePath;
	bool m_DisableProgram;
	CString m_DayOfExpiry;
	CMapStringToString m_ColorMap,m_CodeMap;
	virtual ~CFilterLogDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

CObArray FilterData;

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFilterLogDoc)
	afx_msg void OnViewFilterinformation();
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILTERLOGDOC_H__E28B0D6B_94F7_41AF_9394_FD4A2294E337__INCLUDED_)
