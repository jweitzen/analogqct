// FilterLogDoc.cpp : implementation of the CFilterLogDoc class
//

#include "stdafx.h"
#include "FilterLog.h"

#include "FilterLogDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilterLogDoc

IMPLEMENT_DYNCREATE(CFilterLogDoc, CDocument)

BEGIN_MESSAGE_MAP(CFilterLogDoc, CDocument)
	//{{AFX_MSG_MAP(CFilterLogDoc)
	ON_COMMAND(ID_VIEW_FILTERINFORMATION, OnViewFilterinformation)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilterLogDoc construction/destruction

CFilterLogDoc::CFilterLogDoc()
{
	//Define the day of expiry of the program
	m_DayOfExpiry = "2009/06/21";
	m_DisableProgram = false;
	CTime Today = CTime::GetCurrentTime(); //Get today's date
	CString TodayString = Today.Format("%Y/%m/%d");
	if (TodayString > m_DayOfExpiry)
	{
		m_DisableProgram = true; //Disale program if license expired
		CString ExpiryNotice = "Hi,\n\nthis program has expired. If you intend to keep using it in\nthe future please contact me at:\n\ngiulio2000@bifgoot.com\n\nCiao,\nGiulio";
		AfxMessageBox(ExpiryNotice);
        PostQuitMessage(0);
	}

	//This variable is set to true when the UpdateView() function is called in order to
	// disbale OnItemChanged in the view during view updating
	m_Updating = false;

	//Use GetModuleFileName in prder to get the full path to this program
	char modulename[_MAX_PATH] ; 
	GetModuleFileName(NULL, modulename, MAX_PATH) ;
	m_ExecutablePath = modulename; //This is the full path to this program
	m_ExecutablePath.Replace("FilterLog.exe",""); //remove the program name so that only the path is left

	//Open the colour codes file and load the colours and the code in a MAP array
	ifstream InColorCodes(m_ExecutablePath + "ColourCodes.txt");
	char InString[StringLength];
	while(!InColorCodes.eof())
	{
		InColorCodes.getline(InString,StringLength);
		CString str1 = InString;
		if (!str1.IsEmpty())
		{
			CString str2 = str1.Left(str1.Find(" CODE:"));
			str1.Replace(str2 + " CODE:","");
			m_ColorMap.SetAt(str2,str1); //load the color name and codes in a MAP structure
			m_CodeMap.SetAt(str1,str2); //load the color name and codes in a MAP structure
		}
	}
	InColorCodes.close();

	m_FilterInfo.SetSize(NoFilterInfoElements,1);
}

CFilterLogDoc::~CFilterLogDoc()
{
}

BOOL CFilterLogDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	FilterData.RemoveAll();
	m_FilterInfo.RemoveAll();
	m_FilterInfo.SetSize(NoFilterInfoElements,1);

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFilterLogDoc serialization

void CFilterLogDoc::Serialize(CArchive& ar)
{
	if (m_DisableProgram) //If license has expired log analysis is disabled
	{
		return;
	}

	if (ar.IsStoring())
	{
		CString FilterListStart = "\n\nSTRING LIST STARTS HERE\n";
		CString str, value;
		int NoItems = FilterData.GetSize();
		m_FilterInfo.Serialize(ar);
		ar << NoItems;
		ar << FilterListStart;
		for (int i = 0; i < NoItems; i++)
		{
			CStringArray *Temp = reinterpret_cast<CStringArray *>(FilterData[i]);
			m_ColorMap.Lookup(Temp->GetAt(2),value); 
			str.Format(_T("STRING:%s STATE:%s COL:%s COM:%s REPLACE:%s WITH:%s ENDOFLINE\n"), Temp->GetAt(1), Temp->GetAt(0), value, Temp->GetAt(3), Temp->GetAt(4), Temp->GetAt(5));
			ar << str;
		}
	}
	else
	{
 		FilterData.RemoveAll();
		int NoItems;
		CString str1, value;
		m_FilterInfo.Serialize(ar);
		ar >> NoItems;
		ar >> str1;
		for (int i = 0; i < NoItems; i++)
		{
			ar >> str1;
			CStringArray *Row = new CStringArray;
			str1.Replace("STRING:","");
			Row->SetSize(NoStringArrayElements,1);
			CString str2 = str1.Left(str1.Find(" STATE:"));
			Row->SetAt(1,str2);
			str1.Replace(str2 + " STATE:","");
			str2 = str1.Left(str1.Find(" COL:"));
			Row->SetAt(0,str2);
			str1.Replace(str2 + " COL:","");
			str2 = str1.Left(str1.Find(" COM:"));
			m_CodeMap.Lookup(str2,value); 
			Row->SetAt(2,value);
			str1.Replace(str2 + " COM:","");
			str2 = str1.Left(str1.Find(" REPLACE:"));
			Row->SetAt(3,str2);
			str1.Replace(str2 + " REPLACE:","");
			str2 = str1.Left(str1.Find(" WITH:"));
			Row->SetAt(4,str2);
			str1.Replace(str2 + " WITH:","");
			str2 = str1.Left(str1.Find(" ENDOFLINE"));
			Row->SetAt(5,str2);
			FilterData.Add(Row);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFilterLogDoc diagnostics

#ifdef _DEBUG
void CFilterLogDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFilterLogDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFilterLogDoc commands



void CFilterLogDoc::OnViewFilterinformation() 
{
	CFilterInfo FilterInfoDlg;

	FilterInfoDlg.m_FilterName = m_FilterInfo[0];
	FilterInfoDlg.m_Chipset = m_FilterInfo[1];
	FilterInfoDlg.m_PhoneModel = m_FilterInfo[2];
	FilterInfoDlg.m_SWVersion = m_FilterInfo[3];
	FilterInfoDlg.m_Author = m_FilterInfo[4];
	FilterInfoDlg.m_DateModified = m_FilterInfo[5];
	FilterInfoDlg.m_QCATFilters = m_FilterInfo[6];
	FilterInfoDlg.m_Comments = m_FilterInfo[7];

	if( FilterInfoDlg.DoModal() == IDOK )
	{
		m_FilterInfo[0] = FilterInfoDlg.m_FilterName;
		m_FilterInfo[1] = FilterInfoDlg.m_Chipset;
		m_FilterInfo[2] = FilterInfoDlg.m_PhoneModel;
		m_FilterInfo[3] = FilterInfoDlg.m_SWVersion;
		m_FilterInfo[4] = FilterInfoDlg.m_Author;
		m_FilterInfo[5] = FilterInfoDlg.m_DateModified;
		m_FilterInfo[6] = FilterInfoDlg.m_QCATFilters;
		m_FilterInfo[7] = FilterInfoDlg.m_Comments;
		SetModifiedFlag(); 
	}	
}

void CFilterLogDoc::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	if (m_DisableProgram)
	{
		pCmdUI->Enable(false);
	}
}

void CFilterLogDoc::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	if (m_DisableProgram)
	{
		pCmdUI->Enable(false);
	}
}

void CFilterLogDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	if (m_DisableProgram)
	{
		pCmdUI->Enable(false);
	}
}

void CFilterLogDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	if (m_DisableProgram)
	{
		pCmdUI->Enable(false);
	}
}
