// FilterLogView.h : interface of the CFilterLogView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILTERLOGVIEW_H__95F45486_1274_4486_B0F4_888D46F1773F__INCLUDED_)
#define AFX_FILTERLOGVIEW_H__95F45486_1274_4486_B0F4_888D46F1773F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "InPlaceEdit.h"
#include "InPlaceList.h"

class CFilterLogView : public CListView
{
protected: // create from serialization only
	CFilterLogView();
	DECLARE_DYNCREATE(CFilterLogView)

// Attributes
public:
	CFilterLogDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilterLogView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateView();
	CComboBox* ShowInPlaceList(int nItem, int nCol, CStringList &lstItems, int nSel);
	int HitTestEx(CPoint &point, int *col) const;
	CEdit* EditSubLabel(int nItem, int nCol);
	virtual ~CFilterLogView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFilterLogView)
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditCheckall();
	afx_msg void OnEditUncheckall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FilterLogView.cpp
inline CFilterLogDoc* CFilterLogView::GetDocument()
   { return (CFilterLogDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILTERLOGVIEW_H__95F45486_1274_4486_B0F4_888D46F1773F__INCLUDED_)
