// FilterLog.h : main header file for the FILTERLOG application
//

#if !defined(AFX_FILTERLOG_H__DA0748A2_8264_45DB_AC96_F5713C97C360__INCLUDED_)
#define AFX_FILTERLOG_H__DA0748A2_8264_45DB_AC96_F5713C97C360__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "DocManagerEx.h"

/////////////////////////////////////////////////////////////////////////////
// CFilterLogApp:
// See FilterLog.cpp for the implementation of this class
//

class CFilterLogApp : public CWinApp
{
public:
	CFilterLogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilterLogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFilterLogApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILTERLOG_H__DA0748A2_8264_45DB_AC96_F5713C97C360__INCLUDED_)
