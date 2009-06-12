// CDocManagerEx class declaration
//

class CDocManagerEx : public CDocManager
{
	DECLARE_DYNAMIC(CDocManagerEx)

// Construction
public:
	CDocManagerEx();

// Attributes
public:

// Operations
public:

// Overrides
	// helper for standard commdlg dialogs
	virtual BOOL DoPromptFileName(CString& fileName, UINT nIDSTitle,
			DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate);

// Implementation
public:
	virtual ~CDocManagerEx();
};