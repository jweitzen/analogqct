; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSettingsDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "AnaLog.h"
LastPage=0

ClassCount=7
Class1=CAnaLogApp
Class2=CAnaLogDoc
Class3=CAnaLogView
Class4=CMainFrame

ResourceCount=8
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_ABOUTBOX (English (U.S.))
Resource4=IDD_SETTINGS (English (U.K.))
Class6=CFilterDialog
Resource5=IDR_MAINFRAME (English (U.S.))
Class7=CSettingsDialog
Resource6=IDD_FILTERING_OPTIONS
Resource7=IDD_FILTERING_OPTIONS (English (U.K.))
Resource8=IDD_SETTINGS

[CLS:CAnaLogApp]
Type=0
HeaderFile=AnaLog.h
ImplementationFile=AnaLog.cpp
Filter=N

[CLS:CAnaLogDoc]
Type=0
HeaderFile=AnaLogDoc.h
ImplementationFile=AnaLogDoc.cpp
Filter=N

[CLS:CAnaLogView]
Type=0
HeaderFile=AnaLogView.h
ImplementationFile=AnaLogView.cpp
Filter=C
BaseClass=CHtmlView
VirtualFilter=7VWC
LastObject=CAnaLogView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_VIEW_SETTINGS
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=AnaLog.cpp
ImplementationFile=AnaLog.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
CommandCount=16
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command16=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_SETUP
Command7=ID_FILE_MRU_FILE1
Command8=ID_APP_EXIT
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_VIEW_TOOLBAR
Command14=ID_VIEW_STATUS_BAR
Command15=ID_VIEW_SETTINGS
Command16=ID_GO_BACK
Command17=ID_GO_FORWARD
Command18=ID_ANALYSE_ANALYSELOG
Command19=ID_FILTERS_EDITFILTERS
Command20=ID_APP_ABOUT
CommandCount=20

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_GO_BACK
Command2=ID_GO_FORWARD
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_VIEW_SETTINGS
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_ANALYSE_ANALYSELOG
Command10=ID_FILTERS_EDITFILTERS
Command11=ID_FILE_PRINT
Command12=ID_APP_ABOUT
CommandCount=12

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_FILTERING_OPTIONS]
Type=1
Class=CFilterDialog
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_QCAT_FILTERS,SysListView32,1350631424
Control6=IDC_STRING_FILTERS,SysListView32,1350631424
Control7=IDC_CASE_SENSITIVE,button,1342242819
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_FILTERS_PATH,edit,1350631552
Control10=IDC_BUTTON_FILTERS,button,1342242816

[CLS:CFilterDialog]
Type=0
HeaderFile=FilterDialog.h
ImplementationFile=FilterDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CFilterDialog
VirtualFilter=dWC

[CLS:CSettingsDialog]
Type=0
HeaderFile=SettingsDialog.h
ImplementationFile=SettingsDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CSettingsDialog
VirtualFilter=dWC

[DLG:IDD_FILTERING_OPTIONS (English (U.K.))]
Type=1
Class=CFilterDialog
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_QCAT_FILTERS,SysListView32,1350631424
Control6=IDC_STRING_FILTERS,SysListView32,1350631424
Control7=IDC_CASE_SENSITIVE,button,1342242819
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_FILTERS_PATH,edit,1350631552
Control10=IDC_BUTTON_FILTERS,button,1342242816

[DLG:IDD_SETTINGS (English (U.K.))]
Type=1
Class=CSettingsDialog
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RRC_HTML_PATH,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_BUTTON_RRC_HTML,button,1342242816
Control6=IDC_STATIC,button,1342177287
Control7=IDC_RADIO_MSLOG,button,1342177289
Control8=IDC_RADIO_QXDM,button,1342177289
Control9=IDC_STATIC,button,1342177287
Control10=IDC_RADIO_VFRAMES,button,1342177289
Control11=IDC_RADIO_HFRAMES,button,1342177289
Control12=IDC_FRAME_SPLIT,msctls_trackbar32,1342242825
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308353
Control15=IDC_SHOW_CONFIRM_MSG,button,1342242819
Control16=IDC_QCAT_VERSION,button,1342177287
Control17=IDC_QCAT_4,button,1342177289
Control18=IDC_QCAT_5,button,1342177289
Control19=IDC_QCAT_6,button,1342177289
Control20=IDC_QCAT_7,button,1342177289

[DLG:IDD_SETTINGS]
Type=1
Class=CSettingsDialog
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_HTML_LAYOUT,button,1342177287
Control4=IDC_FRAME_SPLIT,msctls_trackbar32,1342242825
Control5=IDC_HTML_Vert,button,1342308361
Control6=IDC_HTML_Horz,button,1342177289
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308353
Control9=IDC_SHOW_CONFIRM_MSG,button,1342242819
Control10=IDC_QCAT_VERS,button,1342177287
Control11=IDC_QCAT4,button,1342308361
Control12=IDC_QCAT5,button,1342177289
Control13=IDC_QCAT6,button,1342177289
Control14=IDC_QCAT7,button,1342177289
Control15=IDC_APEX5,button,1342177289
Control16=IDC_APEX6,button,1342177289
Control17=IDC_APEX7,button,1342177289

