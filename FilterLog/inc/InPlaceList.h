#if !defined(AFX_INPLACELIST_H__9BA95CC3_363C_4018_A417_2725DFAAEB71__INCLUDED_)
#define AFX_INPLACELIST_H__9BA95CC3_363C_4018_A417_2725DFAAEB71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InPlaceList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInPlaceList window

class CInPlaceList : public CComboBox
{
// Construction
public:
	CInPlaceList(int iItem, int iSubItem, CStringList *plstItems, int nSel);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInPlaceList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceList)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnNcDestroy();
	afx_msg void OnCloseup();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int 	m_iItem;
	int 	m_iSubItem;
	CStringList m_lstItems;
	int 	m_nSel;
	BOOL	m_bESC;				// To indicate whether ESC key was pressed
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPLACELIST_H__9BA95CC3_363C_4018_A417_2725DFAAEB71__INCLUDED_)
