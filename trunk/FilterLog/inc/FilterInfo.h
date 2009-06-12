#if !defined(AFX_FILTERINFO_H__2A6279B3_7930_44E9_89A5_97F2881433DB__INCLUDED_)
#define AFX_FILTERINFO_H__2A6279B3_7930_44E9_89A5_97F2881433DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilterInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFilterInfo dialog

class CFilterInfo : public CDialog
{
// Construction
public:
	CFilterInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFilterInfo)
	enum { IDD = IDD_FILTER_INFO };
	CString	m_Chipset;
	CString	m_Author;
	CString	m_Comments;
	CString	m_DateModified;
	CString	m_FilterName;
	CString	m_PhoneModel;
	CString	m_SWVersion;
	CString	m_QCATFilters;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilterInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFilterInfo)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILTERINFO_H__2A6279B3_7930_44E9_89A5_97F2881433DB__INCLUDED_)
