// AnaLogDoc.cpp : implementation of the CAnaLogDoc class
//

#include "stdafx.h"
#include "AnaLog.h"

#include <fstream.h>
#include "AnaLogDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnaLogDoc

IMPLEMENT_DYNCREATE(CAnaLogDoc, CDocument)

BEGIN_MESSAGE_MAP(CAnaLogDoc, CDocument)
	//{{AFX_MSG_MAP(CAnaLogDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnaLogDoc construction/destruction

CAnaLogDoc::CAnaLogDoc()
{
	//Define the day of expiry of the program
	DayOfExpiry = "2009/06/21";
	DisableProgram = false;
	Today = CTime::GetCurrentTime(); //Get today's date
	CString TodayString = Today.Format("%Y/%m/%d");
	if (TodayString > DayOfExpiry)
	{
		DisableProgram = true; //Disale program if license expired
		CString ExpiryNotice = "Hi,\n\nthis program has expired. If you intend to keep using it in\nthe future please contact me at:\n\ngiulio2000@bifgoot.com\n\nCiao,\nGiulio";
		AfxMessageBox(ExpiryNotice);
        PostQuitMessage(0);
	}

	//Use GetModuleFileName in prder to get the full path to this program
	char modulename[_MAX_PATH] ; 
	GetModuleFileName(NULL, modulename, MAX_PATH) ;
	ExecutablePath = modulename; //This is the full path to this program
	ExecutablePath.Replace("AnaLogQCT.exe",""); //remove the program name so that only the path is left

	PrefferedHTML = "Horizontal";
	QCATVersion = "QCAT5";
	FrameSplit = 65;
	ShowConfirmMsg = "yes";
	FilterFolder = "C:\\Program Files\\AnaLogQCT\\Filters";

	//Read the use settings
	char InString[StringLength];
	ifstream InSettingsFile(ExecutablePath + "Settings.cfg",ios::nocreate);
	if (InSettingsFile.is_open())
	{
		if(!InSettingsFile.eof())
		{
			InSettingsFile.getline(InString,StringLength);
			PrefferedHTML = InString; //Defines if vertical or hirizontal frames are preferred
		}
		if(!InSettingsFile.eof())
		{
			InSettingsFile.getline(InString,StringLength);
			QCATVersion = InString; //Defines the frame division between links and text
		}
		if(!InSettingsFile.eof())
		{
			InSettingsFile.getline(InString,StringLength);
			FrameSplit = atoi(InString); //Defines the frame division between links and text
		}
		if(!InSettingsFile.eof())
		{
			InSettingsFile.getline(InString,StringLength);
			ShowConfirmMsg = InString; //Defines whether to show the settings saving message
		}
		InSettingsFile.close();
	}

	CurrentFilePathName = "";
	Extension = "";
}

CAnaLogDoc::~CAnaLogDoc()
{
}

BOOL CAnaLogDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAnaLogDoc serialization

void CAnaLogDoc::Serialize(CArchive& ar)
{
	//The serialize function is called if the program is opened with a right-click
	//Read the command line to extract the arguments passed to the program
	CCommandLineInfo cmdInfo;
	AfxGetApp()->ParseCommandLine(cmdInfo);
	CurrentFilePathName = cmdInfo.m_strFileName; //if program is opened with a right-click this is the full path to the log
	Extension = CurrentFilePathName.Right(CurrentFilePathName.GetLength()-CurrentFilePathName.ReverseFind('.')-1); //Extract the extension in order to establish the type of log in use
	Extension.MakeLower();

	StartUp = true; //This is useful open the file in case of right-click opening

	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAnaLogDoc diagnostics

#ifdef _DEBUG
void CAnaLogDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAnaLogDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnaLogDoc commands


