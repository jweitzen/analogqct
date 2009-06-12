// AnaLogView.h : interface of the CAnaLogView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALOGVIEW_H__0938216A_F634_4CE2_97FC_1670055398AB__INCLUDED_)
#define AFX_ANALOGVIEW_H__0938216A_F634_4CE2_97FC_1670055398AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define StringLength 1000

//#include <Shellapi.h>

class CAnaLogView : public CHtmlView
{
protected: // create from serialization only
	CAnaLogView();
	DECLARE_DYNCREATE(CAnaLogView)

// Attributes
public:
	CAnaLogDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnaLogView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAnaLogView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAnaLogView)
	afx_msg void OnGoBack();
	afx_msg void OnAnalyseAnalyselog();
	afx_msg void OnFileOpen();
	afx_msg void OnGoForward();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateAnalyseAnalyselog(CCmdUI* pCmdUI);
	afx_msg void OnViewSettings();
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintSetup(CCmdUI* pCmdUI);
	afx_msg void OnFiltersEditfilters();
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AnaLogView.cpp
inline CAnaLogDoc* CAnaLogView::GetDocument()
   { return (CAnaLogDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANALOGVIEW_H__0938216A_F634_4CE2_97FC_1670055398AB__INCLUDED_)
