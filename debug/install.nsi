; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "My application"
!define PRODUCT_VERSION "1.0"
!define PRODUCT_PUBLISHER "My company, Inc."
!define PRODUCT_WEB_SITE "http://www.mycompany.com"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\facePvms.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_STARTMENU_REGVAL "NSIS:StartMenuDir"

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "..\icon.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Language Selection Dialog Settings
!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "SoftwareLicence.txt"
; Components page
!insertmacro MUI_PAGE_COMPONENTS
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Start menu page
var ICONS_GROUP
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "My application"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${PRODUCT_STARTMENU_REGVAL}"
!insertmacro MUI_PAGE_STARTMENU Application $ICONS_GROUP
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\facePvms.exe"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "SimpChinese"

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
InstallDir "$PROGRAMFILES\My application"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Function .onInit
  !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

Section "MainSection" SEC01
  SetOutPath "$INSTDIR\config"
  SetOverwrite try
  File "config\config.ini"
  SetOutPath "$INSTDIR"
  File "DefDateTimeEdit.o"
  File "DefineCalendar.o"
  File "designer.ico"
  File "facePvms.exe"
  File "facepvms.o"
  File "facePvms_resource_res.o"
  File "facerecognize.o"
  File "global.o"
  File "HCCore.dll"
  File "HCCoreDevCfg.dll"
  File "HCNetSDK.dll"
  File "HCPreview.dll"
  File "HKVS_play.o"
  File "HWDecode.dll"
  File "libfacea_lib.dll"
  File "libfaced_lib.dll"
  File "libfacev_lib.dll"
  File "libgcc_s_dw2-1.dll"
  File "libgomp-1.dll"
  File "libopencv_core2413.dll"
  File "libopencv_highgui2413.dll"
  File "libopencv_imgproc2413.dll"
  File "libstdc++-6.dll"
  File "libwinpthread-1.dll"
  File "main.o"
  File "mainwindow.o"
  File "moc_DefDateTimeEdit.cpp"
  File "moc_DefDateTimeEdit.o"
  File "moc_DefineCalendar.cpp"
  File "moc_DefineCalendar.o"
  File "moc_facepvms.cpp"
  File "moc_facepvms.o"
  File "moc_HKVS_play.cpp"
  File "moc_HKVS_play.o"
  File "moc_mainwindow.cpp"
  File "moc_mainwindow.o"
  SetOutPath "$INSTDIR\models"
  File "models\face_fa.bin"
  File "models\face_fd.bin"
  File "models\face_fr.bin"
  SetOutPath "$INSTDIR\platforms"
  File "platforms\qwindows.dll"
  SetOutPath "$INSTDIR"
  File "qrc_resources.cpp"
  File "qrc_resources.o"
  File "Qt5Core.dll"
  File "Qt5Gui.dll"
  File "Qt5OpenGL.dll"
  File "Qt5Sql.dll"
  File "Qt5Test.dll"
  File "Qt5Widgets.dll"
  SetOutPath "$INSTDIR\resources"
  File "resources\ad.png"
  File "resources\al.png"
  File "resources\ar.png"
  File "resources\au.png"
  File "resources\calendar.png"
  File "resources\icon.ico"
  File "resources\icon.rc"
  File "resources\resources.qrc"
  SetOutPath "$INSTDIR"
  File "SoftwareLicence.txt"

; Shortcuts
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  CreateDirectory "$SMPROGRAMS\$ICONS_GROUP"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\My application.lnk" "$INSTDIR\facePvms.exe"
  CreateShortCut "$DESKTOP\My application.lnk" "$INSTDIR\facePvms.exe"
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section -AdditionalIcons
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk" "$INSTDIR\uninst.exe"
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\facePvms.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\facePvms.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

; Section descriptions
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC01} ""
!insertmacro MUI_FUNCTION_DESCRIPTION_END


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) �ѳɹ��ش���ļ�����Ƴ���"
FunctionEnd

Function un.onInit
!insertmacro MUI_UNGETLANGUAGE
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "��ȷʵҪ��ȫ�Ƴ� $(^Name) ���估���е������" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  !insertmacro MUI_STARTMENU_GETFOLDER "Application" $ICONS_GROUP
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\SoftwareLicence.txt"
  Delete "$INSTDIR\resources\resources.qrc"
  Delete "$INSTDIR\resources\icon.rc"
  Delete "$INSTDIR\resources\icon.ico"
  Delete "$INSTDIR\resources\calendar.png"
  Delete "$INSTDIR\resources\au.png"
  Delete "$INSTDIR\resources\ar.png"
  Delete "$INSTDIR\resources\al.png"
  Delete "$INSTDIR\resources\ad.png"
  Delete "$INSTDIR\Qt5Widgets.dll"
  Delete "$INSTDIR\Qt5Test.dll"
  Delete "$INSTDIR\Qt5Sql.dll"
  Delete "$INSTDIR\Qt5OpenGL.dll"
  Delete "$INSTDIR\Qt5Gui.dll"
  Delete "$INSTDIR\Qt5Core.dll"
  Delete "$INSTDIR\qrc_resources.o"
  Delete "$INSTDIR\qrc_resources.cpp"
  Delete "$INSTDIR\platforms\qwindows.dll"
  Delete "$INSTDIR\models\face_fr.bin"
  Delete "$INSTDIR\models\face_fd.bin"
  Delete "$INSTDIR\models\face_fa.bin"
  Delete "$INSTDIR\moc_mainwindow.o"
  Delete "$INSTDIR\moc_mainwindow.cpp"
  Delete "$INSTDIR\moc_HKVS_play.o"
  Delete "$INSTDIR\moc_HKVS_play.cpp"
  Delete "$INSTDIR\moc_facepvms.o"
  Delete "$INSTDIR\moc_facepvms.cpp"
  Delete "$INSTDIR\moc_DefineCalendar.o"
  Delete "$INSTDIR\moc_DefineCalendar.cpp"
  Delete "$INSTDIR\moc_DefDateTimeEdit.o"
  Delete "$INSTDIR\moc_DefDateTimeEdit.cpp"
  Delete "$INSTDIR\mainwindow.o"
  Delete "$INSTDIR\main.o"
  Delete "$INSTDIR\libwinpthread-1.dll"
  Delete "$INSTDIR\libstdc++-6.dll"
  Delete "$INSTDIR\libopencv_imgproc2413.dll"
  Delete "$INSTDIR\libopencv_highgui2413.dll"
  Delete "$INSTDIR\libopencv_core2413.dll"
  Delete "$INSTDIR\libgomp-1.dll"
  Delete "$INSTDIR\libgcc_s_dw2-1.dll"
  Delete "$INSTDIR\libfacev_lib.dll"
  Delete "$INSTDIR\libfaced_lib.dll"
  Delete "$INSTDIR\libfacea_lib.dll"
  Delete "$INSTDIR\HWDecode.dll"
  Delete "$INSTDIR\HKVS_play.o"
  Delete "$INSTDIR\HCPreview.dll"
  Delete "$INSTDIR\HCNetSDK.dll"
  Delete "$INSTDIR\HCCoreDevCfg.dll"
  Delete "$INSTDIR\HCCore.dll"
  Delete "$INSTDIR\global.o"
  Delete "$INSTDIR\facerecognize.o"
  Delete "$INSTDIR\facePvms_resource_res.o"
  Delete "$INSTDIR\facepvms.o"
  Delete "$INSTDIR\facePvms.exe"
  Delete "$INSTDIR\designer.ico"
  Delete "$INSTDIR\DefineCalendar.o"
  Delete "$INSTDIR\DefDateTimeEdit.o"
  Delete "$INSTDIR\config\config.ini"

  Delete "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\Website.lnk"
  Delete "$DESKTOP\My application.lnk"
  Delete "$SMPROGRAMS\$ICONS_GROUP\My application.lnk"

  RMDir "$SMPROGRAMS\$ICONS_GROUP"
  RMDir "$INSTDIR\resources"
  RMDir "$INSTDIR\platforms"
  RMDir "$INSTDIR\models"
  RMDir "$INSTDIR\config"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd