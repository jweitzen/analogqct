// AnaLogView.cpp : implementation of the CAnaLogView class
//

#include "stdafx.h"
//#include <Windows.h>
#include "AnaLog.h"

#include "AnaLogDoc.h"
#include "AnaLogView.h"

#include "FilterDialog.h"
#include "SettingsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnaLogView

IMPLEMENT_DYNCREATE(CAnaLogView, CHtmlView)

BEGIN_MESSAGE_MAP(CAnaLogView, CHtmlView)
	//{{AFX_MSG_MAP(CAnaLogView)
	ON_COMMAND(ID_GO_BACK, OnGoBack)
	ON_COMMAND(ID_ANALYSE_ANALYSELOG, OnAnalyseAnalyselog)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_GO_FORWARD, OnGoForward)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_ANALYSE_ANALYSELOG, OnUpdateAnalyseAnalyselog)
	ON_COMMAND(ID_VIEW_SETTINGS, OnViewSettings)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_SETUP, OnUpdateFilePrintSetup)
	ON_COMMAND(ID_FILTERS_EDITFILTERS, OnFiltersEditfilters)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnaLogView construction/destruction

CAnaLogView::CAnaLogView()
{
}

CAnaLogView::~CAnaLogView()
{
}

BOOL CAnaLogView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAnaLogView drawing

void CAnaLogView::OnDraw(CDC* pDC)
{
	CAnaLogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void CAnaLogView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	CAnaLogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	ifstream InSettingsFile(pDoc->ExecutablePath + "Settings.cfg",ios::nocreate);
	if (!InSettingsFile.is_open())
	{
		AfxMessageBox("It seems that this is the first time you use AnalogQCT\n\nSome basic settings are required before you can start using it. Please take a moment to fill in the following dialog box.");
		OnViewSettings();
	}

	Navigate2(pDoc->ExecutablePath+"Initial.html",NULL,NULL);

	if (pDoc->CurrentFilePathName.IsEmpty())
	{
		Navigate2(pDoc->ExecutablePath+"Initial.html",NULL,NULL);
	}
	else
	{
		if (pDoc->StartUp)
		{
			OnAnalyseAnalyselog();
		}
		pDoc->StartUp = false;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAnaLogView printing


/////////////////////////////////////////////////////////////////////////////
// CAnaLogView diagnostics

#ifdef _DEBUG
void CAnaLogView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CAnaLogView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CAnaLogDoc* CAnaLogView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnaLogDoc)));
	return (CAnaLogDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnaLogView message handlers

void CAnaLogView::OnGoBack() 
{
	GoBack();
}

void CAnaLogView::OnAnalyseAnalyselog() 
{
	CAnaLogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (pDoc->DisableProgram) //If license has expired log analysis is disabled
	{
		return;
	}

	if (pDoc->CurrentFilePathName.IsEmpty()) //If no log is open analisys is not possible
	{
		AfxMessageBox("Can't perform analysis as no file is opened. Select \"open\" from menu");
		return;
	}

	ifstream InSettingsFile(pDoc->ExecutablePath + "UserSelection.cfg",ios::nocreate);
	if (!InSettingsFile.is_open())
	{
		AfxMessageBox("It seems that this is the first time you analyse a log with Analog.\n\nPlease select the folder contaning your filters on the next dialog box before clicking \"OK\".");
	}

	CFilterDialog FilterDialog; //This is the dialog box for selecting filte

	//Pass to the dialog box the required variable for its operation
	FilterDialog.ExecutablePath = pDoc->ExecutablePath;
	FilterDialog.Extension = pDoc->Extension; 
	FilterDialog.m_FiltersPath = pDoc->FilterFolder;

	if (FilterDialog.DoModal() == IDOK)
	{
		CString CaseSensitive; //Used to write to file the user selection for cases 
		if (FilterDialog.m_check_case)
			CaseSensitive = "CaseIsON";
		else
			CaseSensitive = "CaseIsOFF";

		pDoc->FilterFolder = FilterDialog.m_FiltersPath;
		
		//Build up the command that deletes the left HTML frame
		CString DELLeftCommand;
		DELLeftCommand = "del \"" + pDoc->ExecutablePath + "LeftFrame.html\"";

		//Build up the command that deletes the Right HTML frame
		CString DELRightCommand;
		DELRightCommand = "del \"" + pDoc->ExecutablePath + "RightFrame.html\"";

		//Build up the command that deletes the Temp.txt file
		CString DELTemp;
		DELTemp = "del \"" + pDoc->ExecutablePath + "Temp.txt\"";

		//Build up the command that deletes the TempLog.txt file
		CString DELTempLog;
		DELTempLog = "del \"" + pDoc->ExecutablePath + "TempLog.txt\"";

		//Build up the command that saves a TXT file from the DLF file
		CString DLF2TXTCommand; 
		if (!FilterDialog.m_QCATFilters.IsEmpty()) //m_QCATFilters conains the QCAT filers selected by the user
		{
			DLF2TXTCommand = "perl -w \"" + pDoc->ExecutablePath + "DLF2TXT.pl\" ";
			DLF2TXTCommand += "\"" + pDoc->QCATVersion + "\" "; //QCAT version
			DLF2TXTCommand += "\"" + pDoc->CurrentFilePathName + "\" "; //First argument is the log full path
			DLF2TXTCommand += FilterDialog.m_QCATFilters; //Second argument is the list of QCAT filter codes (in decimal)
		}
		
		//BUild up the command to launch the Perl script that converts the TXT into a HTML file
		CString TXT2HTMCommand;
		if (!FilterDialog.m_StringFilters.IsEmpty()) //m_StringFilters conains the string filers selected by the user
		{
			TXT2HTMCommand = "perl -w \"" + pDoc->ExecutablePath + "TXT2HTM.pl\" ";
			TXT2HTMCommand += "\"" + FilterDialog.m_FiltersPath + "\" "; //First argument is the relative path to the folder containing the filters
			TXT2HTMCommand += CaseSensitive + " "; //Second argument is the Case sensitivity setting
			TXT2HTMCommand += FilterDialog.m_StringFilters; //Last argument is the list of string filters to be used
		}

		//Build up the command that deletes ANALYSE.bat the TempLog.txt file
		CString DELAnlyse;
		DELAnlyse = "del \"" + pDoc->ExecutablePath + "ANALYSE.bat\"";

		//Write all commands in the batch "Analyse.bat"
		ofstream OutBatchFile(pDoc->ExecutablePath + "ANALYSE.bat");
		OutBatchFile << DELLeftCommand << endl;
		OutBatchFile << DELRightCommand << endl;
		OutBatchFile << DELTemp << endl;
		OutBatchFile << DELTempLog << endl;
		OutBatchFile << DLF2TXTCommand << endl;
		OutBatchFile << TXT2HTMCommand << endl;
		OutBatchFile << DELAnlyse << endl;
		OutBatchFile.close();
		CString LaunchBatch = "\"" + pDoc->ExecutablePath + "ANALYSE.bat\"";

		//Lanch the Analyse.bat batch file
		STARTUPINFO          si = { sizeof(si) };
		PROCESS_INFORMATION  pi;

		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );

		const char *temp = LPCTSTR(LaunchBatch);
		char *szExe = new char[strlen(temp)];
		strcpy(szExe,temp);

		if(CreateProcess(0, szExe, 0, 0, FALSE, CREATE_NO_WINDOW, 0, 0, &si, &pi))
		{
		   // optionally wait for process to finish
		   WaitForSingleObject(pi.hProcess, INFINITE);

		   CloseHandle(pi.hProcess);
		   CloseHandle(pi.hThread);
		}
		else
		{
			AfxMessageBox("problem");

		}

		CString HTMLFilePathName; //This is the full path to the HTML file to be opened

		//Check the user preference on the layout of the HTML file and navigate to the corresponding file
		if (pDoc->PrefferedHTML == "Vertical")
		{
			HTMLFilePathName = pDoc->ExecutablePath + "IndexVertical.html";
		}
		if (pDoc->PrefferedHTML == "Horizontal")
		{
			HTMLFilePathName = pDoc->ExecutablePath + "IndexHorizontal.html";
		}
		Navigate2(HTMLFilePathName,NULL,NULL); //Open the HTML file 
	}	
}

void CAnaLogView::OnFileOpen() 
{
	CAnaLogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//These are the two possible filters for the "Open" dialog box
	char strFilter[] = { "QCAT file (*.dlf)|*.dlf||" };

    //Create the "Open" dialog Box using the Microsoft CFileDialog
	CFileDialog FileDlg(TRUE, ".dlf", NULL, 0, strFilter, this);

	if( FileDlg.DoModal() == IDOK )
	{
		pDoc->CurrentFilePathName = FileDlg.GetPathName(); //This is the full path chosen by the user
		pDoc->Extension = pDoc->CurrentFilePathName.Right(pDoc->CurrentFilePathName.GetLength()-pDoc->CurrentFilePathName.ReverseFind('.')-1); //Extract the type of file
		
		//Update the main window title
		CString title = pDoc->GetTitle(); 
		pDoc->SetTitle(FileDlg.GetFileName());

		//Once the user has chosen a log, analyse it!
		OnAnalyseAnalyselog();
	}
}

void CAnaLogView::OnGoForward() 
{
	GoForward();
}

void CAnaLogView::OnEditCopy() 
{
	ExecWB(OLECMDID_COPY, OLECMDEXECOPT_DONTPROMPTUSER, NULL, NULL); //This line copies the selection in the HTML view to the clipboard	
}

void CAnaLogView::OnUpdateAnalyseAnalyselog(CCmdUI* pCmdUI) 
{
	CAnaLogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//If license has expired diable this menu entry
	if (pDoc->DisableProgram)
	{
		pCmdUI->Enable(false);
	}
}

//Open the Setting dialog box
void CAnaLogView::OnViewSettings() 
{
	CAnaLogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CSettingsDialog SettingsDialog;
	//Pass to the dialog box all the needed variables
	SettingsDialog.m_ExecutablePath = pDoc->ExecutablePath;
	SettingsDialog.m_PrefferedHTML = pDoc->PrefferedHTML;
	SettingsDialog.m_QCATVersion = pDoc->QCATVersion;
	SettingsDialog.m_FrameSplitPosition = pDoc->FrameSplit;
	if (pDoc->ShowConfirmMsg == "yes") //If user doesn' want to see the Setting savings message...
		SettingsDialog.m_Show_Confirmation_Msg = false;
	else
		SettingsDialog.m_Show_Confirmation_Msg = true;

	if( SettingsDialog.DoModal() == IDOK )
	{
		//Copy the settings chosen by the user into the 
		pDoc->PrefferedHTML = SettingsDialog.m_PrefferedHTML;
		pDoc->QCATVersion = SettingsDialog.m_QCATVersion;
		pDoc->FrameSplit = SettingsDialog.m_FrameSplitPosition;
		if (SettingsDialog.m_Show_Confirmation_Msg)
			pDoc->ShowConfirmMsg = "no";
		else
			pDoc->ShowConfirmMsg = "yes";

		//Write to the Setting.cfg file the new user settings
		ofstream OutSettingsFile(pDoc->ExecutablePath + "Settings.cfg");
		OutSettingsFile << pDoc->PrefferedHTML << endl;
		OutSettingsFile << pDoc->QCATVersion << endl;
		OutSettingsFile << pDoc->FrameSplit << endl;
		OutSettingsFile << pDoc->ShowConfirmMsg << endl;

		OutSettingsFile.close();

		if (pDoc->ShowConfirmMsg == "yes")
		{	AfxMessageBox("Settings have been saved.\n\nNew settings will take effect only after log is re-analised\n\nTo avoid seeing this message again tick checkbox in Settings dialog box");}
	}
}

void CAnaLogView::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(false);
}

void CAnaLogView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(false);
}

void CAnaLogView::OnUpdateFilePrintSetup(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(false);
}

void CAnaLogView::OnFiltersEditfilters() 
{

	CAnaLogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	STARTUPINFO          si = { sizeof(si) };
	PROCESS_INFORMATION  pi;

	CString FilterLogCommand = "\"" +pDoc->ExecutablePath + "FilterLog.exe\" ";
	FilterLogCommand += "\"" + pDoc->FilterFolder + "\\Basic.flt\"";

	FilterLogCommand.Replace('\\','/');

	const char *temp = LPCTSTR(FilterLogCommand);
	char *szExe = new char[strlen(temp)];
	strcpy(szExe,temp);

	
	if(CreateProcess(0, szExe, 0, 0, FALSE, 0, 0, 0, &si, &pi))
	{
	   // optionally wait for process to finish
//	   WaitForSingleObject(pi.hProcess, INFINITE);

	   CloseHandle(pi.hProcess);
	   CloseHandle(pi.hThread);
	}
}

void CAnaLogView::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(false);
}

void CAnaLogView::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(false);
}
