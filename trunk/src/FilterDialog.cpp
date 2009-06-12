// FilterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "AnaLog.h"
#include "FilterDialog.h"
#include "AnaLogDoc.h"
#include "FolderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilterDialog dialog


CFilterDialog::CFilterDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFilterDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFilterDialog)
	m_check_case = FALSE;
	m_FiltersPath = _T("");
	//}}AFX_DATA_INIT
}


void CFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilterDialog)
	DDX_Control(pDX, IDC_STRING_FILTERS, m_String_Filters);
	DDX_Control(pDX, IDC_QCAT_FILTERS, m_QCAT_Filters);
	DDX_Check(pDX, IDC_CASE_SENSITIVE, m_check_case);
	DDX_Text(pDX, IDC_EDIT_FILTERS_PATH, m_FiltersPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilterDialog, CDialog)
	//{{AFX_MSG_MAP(CFilterDialog)
	ON_BN_CLICKED(IDC_BUTTON_FILTERS, OnButtonFilters)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilterDialog message handlers

BOOL CFilterDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//Read user selections from the Usersel.
	CString QCATFilterSel = "";
	CString MatchCaseState = "";
	CString StringFiterSel = "";
	m_check_case = true;

	char InString[StringLength];
	CString UserSelectionFilePathName = ExecutablePath + "UserSelection.cfg";
	ifstream InUserSel(UserSelectionFilePathName,ios::nocreate);
	if (InUserSel.is_open())
	{
		InUserSel.getline(InString,StringLength);
		QCATFilterSel = InString;
		InUserSel.getline(InString,StringLength);
		MatchCaseState = InString;
		if (MatchCaseState == "ON")
			m_check_case = true;
		else 
			m_check_case = false;
		InUserSel.getline(InString,StringLength);
		m_FiltersPath = InString;
		InUserSel.getline(InString,StringLength);
		StringFiterSel = InString;
	}
	InUserSel.close();

	//Read the "QCATCodes.txt" file in order to extract the QCAT filtre codes
	CString QCATCodesFilePathName = ExecutablePath + "QCATCodes.txt";
	ifstream InFile(QCATCodesFilePathName);
	while(!InFile.eof())
	{
		InFile.getline(InString,StringLength);
		CString str1 = InString;
		if (!str1.IsEmpty())
		{
			CString str2 = str1.Left(str1.Find(" CODE:"));
			str1.Replace(str2 + " CODE:","");
			m_QCATCodeaMap.SetAt(str2,str1); //load the QCAT filter name and code in a MAP structure
		}
	}
		//Fill the QCAT list control wiht the CODES names
	m_QCAT_Filters.InsertColumn(0, "String", LVCFMT_LEFT, 400); //Set 1 column for the list control
	m_QCAT_Filters.ModifyStyle(NULL, LVS_REPORT | LVS_NOCOLUMNHEADER); //Set the list control to report style without column header
	m_QCAT_Filters.SetExtendedStyle(LVS_EX_CHECKBOXES); //Use the check boxes with list control

	m_QCATFilters = "";
	POSITION pos = m_QCATCodeaMap.GetStartPosition();
	int nItem;
	CString key, value;
	int count = 0;
	CString str = QCATFilterSel.Left(QCATFilterSel.Find(';')); //QCATFilterSel conatins the least of the filter the user selected last time
	QCATFilterSel.Replace(str + "; ",""); //Extract the left-most filter name from QCATFilterSel
	while (pos != NULL)
	{
		m_QCATCodeaMap.GetNextAssoc(pos, key, value);
		nItem = m_QCAT_Filters.InsertItem(count, key); //Add the filter name to the list control
		if (str == key) //If the filter name is one the user had selected last time...
		{
			m_QCAT_Filters.SetCheck(count,true); //Set it checked
			str = QCATFilterSel.Left(QCATFilterSel.Find(';')); //Extract the next filter name the user had selected last time from QCATFilterSel
			QCATFilterSel.Replace(str + "; ","");
		}
		count++;
	}

	//This bit of code reads the files names from a folder and put it in a list structure
	WIN32_FIND_DATA ff;
//	HANDLE findhandle = FindFirstFile( FilterFolder + "\\*.flt", &ff ); //FilterFolder conatins the user selected folder with the strings
	HANDLE findhandle = FindFirstFile( m_FiltersPath + "\\*.flt", &ff ); //FilterFolder conatins the user selected folder with the strings
	if( findhandle != INVALID_HANDLE_VALUE )
	{
		BOOL res = TRUE;
		while( res )
		{
			// We only want files
			if( !( ff.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
			{
				BOOL    added = FALSE;
				CString file;
				file = ff.cFileName;

				// Return the array alphabetically ordered
				for( int i = 0; i < m_FilterList.GetSize(); i++ )
				{
					if ( m_FilterList.GetAt( i ) > file )
					{
						m_FilterList.InsertAt( i, file );
						added = TRUE;
						break;
					}
				}
				if ( !added )
				{
					m_FilterList.Add( file );
				}
			}

			res = FindNextFile( findhandle, &ff );
		}

		FindClose( findhandle );
	}

	//Fill the string list control wiht the filter names
	m_String_Filters.InsertColumn(0, "String", LVCFMT_LEFT, 400);
	m_String_Filters.ModifyStyle(NULL, LVS_REPORT | LVS_NOCOLUMNHEADER);
	m_String_Filters.SetExtendedStyle(LVS_EX_CHECKBOXES);

	m_StringFilters = "";
	CString StrTemp = StringFiterSel.Left(StringFiterSel.Find(';')); //Extarct from StringFiterSel the first filter the user selected last time
	StringFiterSel.Replace(StrTemp + "; ","");
	for ( count = 0; count < m_FilterList.GetSize(); count++)
	{
		int nItem = m_String_Filters.InsertItem(count, m_FilterList.GetAt( count ));
		if (StrTemp == m_FilterList.GetAt( count )) //If the filter was used last time as well...
		{
			m_String_Filters.SetCheck(count,true); //set it cheked
			StrTemp = StringFiterSel.Left(StringFiterSel.Find(';')); //Extract the next filter used last time
			StringFiterSel.Replace(StrTemp + "; ","");
		}
	}

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFilterDialog::OnOK() 
{
	UpdateData(true);

	bool QCAT_Filters = false;
	bool UserSelectionIsEmpty = false;

	int NoItems = m_QCAT_Filters.GetItemCount();
	CString value;

	CString UserSelectionFilePathName = ExecutablePath + "UserSelection.cfg";
	ofstream OutUserSel(UserSelectionFilePathName); //Open the output file fo rwriting the new user selections

	for (int count = 0; count < NoItems; count++)
	{
		if (m_QCAT_Filters.GetCheck(count)) //If the QCAT filter has been checked...
		{
			//Build up the output string used for launch the shell command
			m_QCATCodeaMap.Lookup(m_QCAT_Filters.GetItemText(count,0),value); 
			m_QCATFilters += "\"" + value + "\" ";
//			m_QCATFilters += " ";
			OutUserSel << m_QCAT_Filters.GetItemText(count,0) << "; ";
			QCAT_Filters = true;
		}
	}

	OutUserSel << endl;

	if(!QCAT_Filters)
	{
		AfxMessageBox("No QCAT filter was selected!");
		UserSelectionIsEmpty = true;
	}

	if (m_check_case)
		OutUserSel << "ON" << endl;
	else
		OutUserSel << "OFF" << endl;

	OutUserSel << m_FiltersPath << endl;

	bool Filters = false;

	NoItems = m_String_Filters.GetItemCount();

	for (count = 0; count < NoItems; count++)
	{
		if (m_String_Filters.GetCheck(count))
		{
			//Build up the output string used for launch the shell command
			m_StringFilters += "\"" + m_String_Filters.GetItemText(count,0) + "\" ";
			OutUserSel << m_String_Filters.GetItemText(count,0) << "; ";
			Filters = true;
		}
	}	

	OutUserSel << endl;

	if(!Filters)
	{
		AfxMessageBox("No string filter was selected!");
		UserSelectionIsEmpty = true;
	}

	OutUserSel.close();

	if(!UserSelectionIsEmpty) //If the user has left empty any of the list control boxes...
	{
		CDialog::OnOK(); //Do nothing so the dialog box will not be closed and the user will be forced to select something
	}
}

void CFilterDialog::OnCancel() 
{

	CDialog::OnCancel();
}


void CFilterDialog::OnButtonFilters() 
{
	//When the user wants to select the folder for the string filters the CFolderDialog box is used
	CFolderDialog dlg( _T( "" ), m_FiltersPath, this );
	CString RootFolder = "Desktop";
    dlg.SetRootFolder( _T( RootFolder )); //Sets the initial folder to select from (the user can't navigate above outside this folder
    
	CString OldFiltersPath = m_FiltersPath;
    if( dlg.DoModal() == IDOK  )
    {       
        m_FiltersPath = dlg.GetFolderPath(); //Get the folder selected by the user
		if (m_FiltersPath != OldFiltersPath)
			RefreshStringSelection();
		UpdateData(false);
    }	
}

void CFilterDialog::RefreshStringSelection()
{
	m_FilterList.RemoveAll();
	WIN32_FIND_DATA ff;
//	HANDLE findhandle = FindFirstFile( FilterFolder + "\\*.flt", &ff ); //FilterFolder conatins the user selected folder with the strings
	HANDLE findhandle = FindFirstFile( m_FiltersPath + "\\*.flt", &ff ); //FilterFolder conatins the user selected folder with the strings
	if( findhandle != INVALID_HANDLE_VALUE )
	{
		BOOL res = TRUE;
		while( res )
		{
			// We only want files
			if( !( ff.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
			{
				BOOL    added = FALSE;
				CString file;
				file = ff.cFileName;

				// Return the array alphabetically ordered
				for( int i = 0; i < m_FilterList.GetSize(); i++ )
				{
					if ( m_FilterList.GetAt( i ) > file )
					{
						m_FilterList.InsertAt( i, file );
						added = TRUE;
						break;
					}
				}
				if ( !added )
				{
					m_FilterList.Add( file );
				}
			}

			res = FindNextFile( findhandle, &ff );
		}

		FindClose( findhandle );
	}

	m_String_Filters.DeleteAllItems();

	//Fill the string list control wiht the filter names
	m_String_Filters.InsertColumn(0, "String", LVCFMT_LEFT, 400);
	m_String_Filters.ModifyStyle(NULL, LVS_REPORT | LVS_NOCOLUMNHEADER);
	m_String_Filters.SetExtendedStyle(LVS_EX_CHECKBOXES);

	for (int count = 0; count < m_FilterList.GetSize(); count++)
	{
		int nItem = m_String_Filters.InsertItem(count, m_FilterList.GetAt( count ));
	}
}
