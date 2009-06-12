#if !defined(AFX_FILTERDIALOG_H__9794775C_DF5F_4D19_8BEA_6245B3700536__INCLUDED_)
#define AFX_FILTERDIALOG_H__9794775C_DF5F_4D19_8BEA_6245B3700536__INCLUDED_

#include "AnaLogDoc.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilterDialog.h : header file
//

#include <fstream.h>
#define StringLength 1000

/////////////////////////////////////////////////////////////////////////////
// CFilterDialog dialog

class CFilterDialog : public CDialog
{
// Construction
public:
	void RefreshStringSelection();
	CString FilterFolder;
	CString Extension;
	CString ExecutablePath;
	CMapStringToString m_QCATCodeaMap;
	CStringArray m_FilterList;
	CString m_StringFilters;
	CString m_QCATFilters;
	CFilterDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFilterDialog)
	enum { IDD = IDD_FILTERING_OPTIONS };
	CListCtrl	m_String_Filters;
	CListCtrl	m_QCAT_Filters;
	BOOL	m_check_case;
	CString	m_FiltersPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilterDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFilterDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonFilters();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILTERDIALOG_H__9794775C_DF5F_4D19_8BEA_6245B3700536__INCLUDED_)
