; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "AnaLogQCT"
!define PRODUCT_VERSION "1.0"
!define PRODUCT_PUBLISHER "Giulio Giovannini"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define INSTALLER_NAME "${PRODUCT_NAME}_${PRODUCT_VERSION}_setup.exe"

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"
; Set the license page to display 2 radio buttons forcing the user to accept the license
!define MUI_LICENSEPAGE_RADIOBUTTONS
; Define a checkbox on the FINISH page and the file that should be invoked if the user checks the box
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\AnaLogQCT user manual.htm"
; Sets the text near the checkbox on the FINISH page
!define MUI_FINISHPAGE_SHOWREADME_TEXT "Open AnaLogQCT manual"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "License.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "${INSTALLER_NAME}" ; Name of the installer file
InstallDir "$PROGRAMFILES\${PRODUCT_NAME}" ; Sets the variable $INSTDIR. $INSTDIR can be changed by the user in DIRECTORY page. The $PROGRAMFILES contains the "C:\Program Files" path
ShowInstDetails show
ShowUnInstDetails show

Section "MainSection" SEC01

  SetOutPath "$INSTDIR" ; Sets the folder where the folder of installation to be $INSTDIR
  SetOverwrite ifnewer ; Files will be overwritten only if their modification date of the new file is more recent
  File "..\bin\AnaLogQCT.exe" ; This command actually copy the file in the argument to the $INSTDIR directory.
  File "..\FilterLog\bin\FilterLog.exe"
  File "License.txt"
  File "..\util\IndexHorizontal.html"
  File "..\util\IndexVertical.html"
  File "..\util\Initial.html"
  File "..\util\AnaLogQCT user manual.htm"
  File "..\FilterLog\util\FilterLog user manual.htm"
  File "..\util\DLF2TXT.pl"
  File "..\util\TXT2HTM.pl"
  File "..\FilterLog\util\ColourCodes.txt"
  File "..\util\QCATCodes.txt"

  ; Copy filters
  SetOverwrite off ; If user already possess filters they are not overwritten
  SetOutPath $INSTDIR\Filters
  File "..\util\Filters\Basic.flt"

SectionEnd

Section -Post ; this section is "hidden" because its name starts with a "-". It will always be executed

  WriteUninstaller "$INSTDIR\uninstall_${PRODUCT_NAME}_${PRODUCT_VERSION}.exe" ; This command will produce an uninstaller executable and copy it to the $INSTDIR folder
  
  ;Create a registry key with the required information for uninstalling the program with the Add/Remove facility of Windows XP
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninstall_${PRODUCT_NAME}_${PRODUCT_VERSION}.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  
  ; Create a right-click shortcut for DLF files
  ReadRegStr $R0 HKCR ".dlf" "" ; Reads the  description for the .dlf extension
  StrCmp $R0 "" inst_qcat_not_installed ; if the description is empty the .dlf extension does not exist on the machine. Skip the following instructions
    WriteRegStr HKCR "$R0\shell\${PRODUCT_NAME}" "" "Analyse file with AnaLogQCT" ; Adds a shell operation to the description
    WriteRegStr HKCR "$R0\shell\${PRODUCT_NAME}\command" "" '"$INSTDIR\AnaLogQCT.exe" "%1"' ; Defines the command for the operation
  inst_qcat_not_installed:

  ; Create a file-association for FilterLog files
  ReadRegStr $R1 HKCR ".flt" "" ; Check if the extension .flt already exists and associated to what
  StrCmp $R1 "" no_back_up ; If we get an empty string, then .flt did not exist
    StrCmp $R1 "FilterLogFile" no_back_up ; if the string is not empty but is already associated with FilterLog we don't need to back up anything
    WriteRegStr HKCR ".flt" "backup_val" $R1 ; Create a key "backup_val" with the .flt description set before this installer
  no_back_up:
  WriteRegStr HKCR ".flt" "" "FilterLogFile" ; write our extension description
  WriteRegStr HKCR "FilterLogFile" "" "FilterLog File"
  WriteRegStr HKCR "FilterLogFile\shell" "" "open"
  WriteRegStr HKCR "FilterLogFile\DefaultIcon" "" '"$INSTDIR\FilterLog.exe",0'
  WriteRegStr HKCR "FilterLogFile\shell\open\command" "" '"$INSTDIR\FilterLog.exe" "%1"'

  ; Inform Windows of the changes in the registry
  System::Call 'Shell32::SHChangeNotify(i 0x8000000, i 0, i 0, i 0)'
  
  ; Create a shortcuts in the start program menu
  CreateDirectory $SMPROGRAMS\${PRODUCT_NAME}
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\${PRODUCT_NAME}.lnk" "$INSTDIR\AnaLogQCT.exe" ""
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\FilterLog.lnk" "$INSTDIR\FilterLog.exe" ""
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Uninstall ${PRODUCT_NAME}.lnk " "$INSTDIR\uninstall_${PRODUCT_NAME}_${PRODUCT_VERSION}.exe" ""
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\AnaLogQCT user manual.lnk " "$INSTDIR\AnaLogQCT user manual.htm" ""
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\FilterLog user manual.lnk " "$INSTDIR\FilterLog user manual.htm" ""
  CreateShortCut "$SMPROGRAMS\${PRODUCT_NAME}\Troubleshooting info.lnk " "$INSTDIR\AnaLogQCT user manual.htm" ""

  ; Create a shortcut on the desktop
  CreateShortCut "$DESKTOP\${PRODUCT_NAME}.lnk" "$INSTDIR\AnaLogQCT.exe"

SectionEnd

Function .onInstSuccess ; Executed only if Installation was successful
  ReadRegStr $R0 HKLM Software\Perl BinDir ; read a key in the register with is associated with Perl
  StrCmp $R0 "" no_perl ; if the key is found then Perl is installed and the following message is printed to the screen
    MessageBox MB_ICONINFORMATION|MB_OK "AnaLogQCT requires Perl to be installed in order to run. $\r$\n\
      $\r$\nIt seems that Perl is installed on this computer.$\r$\n$\r$\n\
      Please be aware that AnaLogQCT has only been tested with Perl 5.8.* version. \
      Earlier version of Perl might not be suitable"
    Goto end
  no_perl: ; is the key was not found, the the following message is printed
    MessageBox MB_YESNO|MB_ICONEXCLAMATION "AnaLogQCT requires Perl to be installed in order to run. $\r$\n$\r$\n\
        The installer can not find Perl \
        on this computer! Please make sure Perl is installed before attempting to run AnaLogQCT. \
        AnaLogQCT has only been tested with Perl 5.8.* version. \
        Earlier version of Perl might not be suitable$\r$\n$\r$\n\
        Perl is a free program. Would you like the installer to open Perl's download page?" IDNO end
    ExecShell open \
	    http://www.activestate.com/Products/Download/Get.plex?id=ActivePerl ; if the user selects "yes" the Active state Perl Webpage is opned
  end:
FunctionEnd

Function un.onUninstSuccess ; This function is executed when the uninstaller is launched
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
  
  IfFileExists "$INSTDIR\*.*" 0 +2 ; warn user if the AnaLogQCT folder could not be deleted as some file he created are presnet in the folder
  MessageBox MB_ICONINFORMATION|MB_OK "The folder $INSTDIR could not be deleted as some user-owned file are present.$\r$\n$\r$\nPlease delete the folder manually if required. If you plan to re-install ${PRODUCT_NAME} you might want to keep the files"
FunctionEnd

Function un.onInit ; executed when the installer starts
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall ; this section is only performed in the uninstaller
  ; delete all files
  Delete "$INSTDIR\uninstall_${PRODUCT_NAME}_${PRODUCT_VERSION}.exe"
  Delete "$INSTDIR\AnaLogQCT.exe"
  Delete "$INSTDIR\FilterLog.exe"
  Delete "$INSTDIR\License.txt"
  Delete "$INSTDIR\IndexHorizontal.html"
  Delete "$INSTDIR\IndexVertical.html"
  Delete "$INSTDIR\Initial.html"
  Delete "$INSTDIR\AnaLogQCT user manual.htm"
  Delete "$INSTDIR\FilterLog user manual.htm"
  Delete "$INSTDIR\DLF2TXT.pl"
  Delete "$INSTDIR\HTM2HTM.pl"
  Delete "$INSTDIR\TXT2HTM.pl"
  Delete "$INSTDIR\ColourCodes.txt"
  Delete "$INSTDIR\QCATCodes.txt"
  Delete "$INSTDIR\LeftFrame.html"
  Delete "$INSTDIR\RightFrame.html"
  Delete "$INSTDIR\Temp.txt"
  Delete "$INSTDIR\TempLog.txt"

  ;Delete installation folder
  RMDir "$INSTDIR"
  
  ;Delete shortcuts
  RMDir /r $SMPROGRAMS\AnaLogQCT
  Delete "$DESKTOP\${PRODUCT_NAME}.lnk"
  
  ; Delete the the registry key creted for uninstalling the program
  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  
  ; Delete right-click shortcut for DLF files
  ReadRegStr $R0 HKCR ".dlf" "" ; Reads the  description for the .dlf extension
  StrCmp $R0 "" uninst_qcat_not_installed
    DeleteRegKey HKCR "$R0\shell\${PRODUCT_NAME}" ; Deletes the shell operation
  uninst_qcat_not_installed:
  
  ; Delete right-click shortcut for TXT files
  ReadRegStr $R0 HKCR ".txt" "" ; Reads the  description for the .dlf extension
  StrCmp $R0 "" uninst_txt_not_exist
    DeleteRegKey HKCR "$R0\shell\${PRODUCT_NAME}" ; Deletes the shell operation
  uninst_txt_not_exist:
  
  ; Restore the file association for .flt file or delete it if there didn't exist one
  ReadRegStr $R0 HKCR ".flt" "backup_val"
  StrCmp $R0 "" no_backup ; if backup="" then delete the whole key
    WriteRegStr HKCR ".flt" "" $R0 ; perform backup of previous file association
    DeleteRegValue HKCR ".flt" "backup_val"
    Goto backup_sorted
  no_backup:
  DeleteRegKey HKCR ".flt"
  backup_sorted:
  DeleteRegKey HKCR "FilterLogFile" ;Delete key with association settings

  System::Call 'Shell32::SHChangeNotify(i 0x8000000, i 0, i 0, i 0)'
  
  SetAutoClose true
SectionEnd