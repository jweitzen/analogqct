#if !defined(AFX_SETTINGSDIALOG_H__E942F441_8760_41F6_B4D1_A1BD79CB9F7B__INCLUDED_)
#define AFX_SETTINGSDIALOG_H__E942F441_8760_41F6_B4D1_A1BD79CB9F7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingsDialog.h : header file
//

#include <fstream.h>

/////////////////////////////////////////////////////////////////////////////
// CSettingsDialog dialog

class CSettingsDialog : public CDialog
{
// Construction
public:
	CString m_QCATVersion;
	int m_FrameSplitPosition;
	CString m_ExecutablePath;
	CString m_PrefferedHTML;
	CSettingsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingsDialog)
	enum { IDD = IDD_SETTINGS };
	CSliderCtrl	m_FrameSplit;
	BOOL	m_Show_Confirmation_Msg;
	int		m_QCAT_Version;
	int		m_HTML_frames;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRadioVframes();
	afx_msg void OnRadioHframes();
	afx_msg void OnReleasedcaptureFrameSplit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnQcat4();
	afx_msg void OnQcat5();
	afx_msg void OnQcat6();
	afx_msg void OnQcat7();
	afx_msg void OnApex5();
	afx_msg void OnApex6();
	afx_msg void OnApex7();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGSDIALOG_H__E942F441_8760_41F6_B4D1_A1BD79CB9F7B__INCLUDED_)
