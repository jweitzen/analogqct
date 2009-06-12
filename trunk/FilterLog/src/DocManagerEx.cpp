// DocManagerEx.cpp : implementation file
//
// this function comed from the article "Changing default file open/save dialogs"
// Basically it is copied from MFC function

#include "stdafx.h"
//#include "PreviewFileDlg.h"
#include "DocManagerEx.h" // the header with the class declaration

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static void AppendFilterSuffix(CString& filter, OPENFILENAME& ofn,
	CDocTemplate* pTemplate, CString* pstrDefaultExt)
{
	ASSERT_VALID(pTemplate);
	ASSERT_KINDOF(CDocTemplate, pTemplate);

	CString strFilterExt, strFilterName;
	if (pTemplate->GetDocString(strFilterExt, CDocTemplate::filterExt) &&
	 !strFilterExt.IsEmpty() &&
	 pTemplate->GetDocString(strFilterName, CDocTemplate::filterName) &&
	 !strFilterName.IsEmpty())
	{
		// a file based document template - add to filter list
#ifndef _MAC
		ASSERT(strFilterExt[0] == '.');
#endif
		if (pstrDefaultExt != NULL)
		{
			// set the default extension
#ifndef _MAC
			*pstrDefaultExt = ((LPCTSTR)strFilterExt) + 1;  // skip the '.'
#else
			*pstrDefaultExt = strFilterExt;
#endif
			ofn.lpstrDefExt = (LPTSTR)(LPCTSTR)(*pstrDefaultExt);
			ofn.nFilterIndex = ofn.nMaxCustFilter + 1;  // 1 based number
		}

		// add to filter
		filter += strFilterName;
		ASSERT(!filter.IsEmpty());  // must have a file type name
		filter += (TCHAR)'\0';  // next string please
#ifndef _MAC
		filter += (TCHAR)'*';
#endif
		filter += strFilterExt;
		filter += (TCHAR)'\0';  // next string please
		ofn.nMaxCustFilter++;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDocManagerEx

IMPLEMENT_DYNAMIC(CDocManagerEx, CDocManager)

CDocManagerEx::CDocManagerEx()
{
}

CDocManagerEx::~CDocManagerEx()
{
}

BOOL CDocManagerEx::DoPromptFileName(CString& fileName, UINT nIDSTitle, DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate)
{
	CFileDialog dlgFile(bOpenFileDialog); // this is the only modified line!

	CString title;
	VERIFY(title.LoadString(nIDSTitle));

	dlgFile.m_ofn.Flags |= lFlags;

	CString strFilter;
	CString strDefault;
	if (pTemplate != NULL)
	{
		ASSERT_VALID(pTemplate);
		AppendFilterSuffix(strFilter, dlgFile.m_ofn, pTemplate, &strDefault);
	}
	else
	{
		// do for all doc template
		POSITION pos = m_templateList.GetHeadPosition();
		BOOL bFirst = TRUE;
		while (pos != NULL)
		{
			CDocTemplate* pTemplate = (CDocTemplate*)m_templateList.GetNext(pos);
			AppendFilterSuffix(strFilter, dlgFile.m_ofn, pTemplate,
				bFirst ? &strDefault : NULL);
			bFirst = FALSE;
		}
	}
/*
	// append the "*.*" all files filter
	CString allFilter;
	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
	strFilter += allFilter;
	strFilter += (TCHAR)'\0';   // next string please
#ifndef _MAC
	strFilter += _T("*.*");
#else
	strFilter += _T("****");
#endif
	strFilter += (TCHAR)'\0';   // last string
	dlgFile.m_ofn.nMaxCustFilter++;
*/
	dlgFile.m_ofn.lpstrFilter = strFilter;
#ifndef _MAC
	dlgFile.m_ofn.lpstrTitle = title;
#else
	dlgFile.m_ofn.lpstrPrompt = title;
#endif
	dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

	BOOL bResult = dlgFile.DoModal() == IDOK ? TRUE : FALSE;
	fileName.ReleaseBuffer();
/*
	 CString strFilterExt;
	ASSERT_VALID(pTemplate);
	//Get the file extension of the template
	pTemplate->GetDocString(strFilterExt, CDocTemplate::filterExt);

	//Get the file extension of the selected file
	CString cstrSelFileExt = fileName.Right(fileName.GetLength() - fileName.ReverseFind('.'));
	cstrSelFileExt.MakeLower();
	strFilterExt.MakeLower();

	//compare both if not the same extension then return false
	if(strFilterExt.Find(cstrSelFileExt) == -1)
	{
		AfxMessageBox("Invalid extension", MB_OK | MB_ICONHAND);
		return FALSE;
	}
*/
	return bResult;
}