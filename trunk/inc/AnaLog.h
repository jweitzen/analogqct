// AnaLog.h : main header file for the ANALOG application
//

#if !defined(AFX_ANALOG_H__2D115D0A_FD10_4FC3_A5EE_DD7E3A7862AA__INCLUDED_)
#define AFX_ANALOG_H__2D115D0A_FD10_4FC3_A5EE_DD7E3A7862AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAnaLogApp:
// See AnaLog.cpp for the implementation of this class
//

class CAnaLogApp : public CWinApp
{
public:
	CAnaLogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnaLogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CAnaLogApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANALOG_H__2D115D0A_FD10_4FC3_A5EE_DD7E3A7862AA__INCLUDED_)
