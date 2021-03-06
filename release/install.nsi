; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "facePvms"
!define PRODUCT_VERSION "1.0"
!define PRODUCT_PUBLISHER "My company, Inc."
!define PRODUCT_WEB_SITE "http://www.mycompany.com"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\facePvms.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "C:\Users\xrm\Documents\GitHub\19_camera\release\resources\icon.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Language Selection Dialog Settings
!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "C:\Users\xrm\Documents\GitHub\19_camera\release\SoftwareLicence.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
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
InstallDir "$PROGRAMFILES\facePvms"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Function .onInit
  !insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite try
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\apisetschema.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\AudioIntercom.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\AudioRender.dll"
  SetOutPath "$INSTDIR\cascade"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\cascade\haarcascade_eye.xml"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\cascade\haarcascade_frontalface_alt2.xml"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\cascade\readme"
  SetOutPath "$INSTDIR\ClientDemoDll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\ClientDemoDll\calib.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\ClientDemoDll\iconv.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\ClientDemoDll\libxml2.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\ClientDemoDll\ReadMe.txt"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\ClientDemoDll\zlib1.dll"
  SetOutPath "$INSTDIR\config"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\config\config.ini"
  SetOutPath "$INSTDIR"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\C_1252.NLS"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\D3DX9_43.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\database.o"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\DefDateTimeEdit.o"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\DefineCalendar.o"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\designer.ico"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\facePvms.exe"
  CreateDirectory "$SMPROGRAMS\facePvms"
  CreateShortCut "$SMPROGRAMS\facePvms\facePvms.lnk" "$INSTDIR\facePvms.exe"
  CreateShortCut "$DESKTOP\facePvms.lnk" "$INSTDIR\facePvms.exe"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\facepvms.o"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\facePvms_resource_res.o"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\facerecognize.o"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\gdiplus.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\global.o"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCAlarm.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCCore.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCCoreDevCfg.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCGeneralCfgMgr.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDK.dll"
  SetOutPath "$INSTDIR\HCNetSDKCom"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\AnalyzeData.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\AudioIntercom.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\HCAlarm.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\HCAlarm.lib"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\HCCoreDevCfg.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\HCDisplay.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\HCGeneralCfgMgr.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\HCGeneralCfgMgr.lib"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\HCIndustry.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\HCPlayBack.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\HCPreview.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\HCPreview.lib"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\HCVoiceTalk.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\libiconv2.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\msvcr90.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\OpenAL32.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\StreamTransClient.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCNetSDKCom\SystemTransform.dll"
  SetOutPath "$INSTDIR"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HCPreview.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HKVS_play.o"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\HWDecode.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\install.nsi"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\libEGL.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\libfacea_lib.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\libfaced_lib.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\libfacev_lib.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\libface_rec.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\libgcc_s_dw2-1.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\libGLESv2.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\libgomp-1.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\libiconv2.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\libopencv_core2413.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\libopencv_highgui2413.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\libopencv_imgproc2413.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\libopencv_objdetect2413.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\libstdc++-6.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\libwinpthread-1.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\main.o"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\mainwindow.o"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\moc_DefDateTimeEdit.cpp"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\moc_DefDateTimeEdit.o"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\moc_DefineCalendar.cpp"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\moc_DefineCalendar.o"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\moc_facepvms.cpp"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\moc_facepvms.o"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\moc_HKVS_play.cpp"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\moc_HKVS_play.o"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\moc_mainwindow.cpp"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\moc_mainwindow.o"
  SetOutPath "$INSTDIR\models"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\models\face_fd.bin"
  SetOutPath "$INSTDIR"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\MP_Render.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\MP_VIE.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\msvcr90.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\OpenAL32.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\opengl32sw.dll"
  SetOutPath "$INSTDIR\platforms"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\platforms\qminimal.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\platforms\qwindows.dll"
  SetOutPath "$INSTDIR"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\PlayCtrl.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\PlayCtrl.lib"
  SetOutPath "$INSTDIR\plugins\sqldrivers"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\plugins\sqldrivers\libqsqlite4.a"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\plugins\sqldrivers\libqsqlited4.a"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\plugins\sqldrivers\libqsqlodbc4.a"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\plugins\sqldrivers\libqsqlodbcd4.a"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\plugins\sqldrivers\qsqlite4.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\plugins\sqldrivers\qsqlited4.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\plugins\sqldrivers\qsqlodbc4.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\plugins\sqldrivers\qsqlodbcd4.dll"
  SetOutPath "$INSTDIR"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\qrc_resources.cpp"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\qrc_resources.o"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\Qt5Core.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\Qt5Gui.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\Qt5OpenGL.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\Qt5PrintSupport.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\Qt5SerialPort.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\Qt5Sql.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\Qt5Test.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\Qt5Widgets.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\Qt5Xml.dll"
  SetOutPath "$INSTDIR\resources"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\resources\ad.png"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\resources\al.png"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\resources\ar.png"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\resources\au.png"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\resources\calendar.png"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\resources\icon.ico"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\resources\icon.rc"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\resources\resources.qrc"
  SetOutPath "$INSTDIR"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\SoftwareLicence.txt"
  SetOutPath "$INSTDIR\sqldrivers"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\sqldrivers\qsqlite.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\sqldrivers\qsqlited.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\sqldrivers\qsqlmysql.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\sqldrivers\qsqlmysqld.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\sqldrivers\qsqlpsql.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\sqldrivers\qsqlpsqld.dll"
  SetOutPath "$INSTDIR"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\SuperRender.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\WordStrokeHelper32.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\wow64.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\wow64cpu.dll"
  File "C:\Users\xrm\Documents\GitHub\19_camera\release\wow64win.dll"
SectionEnd

Section -AdditionalIcons
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\facePvms\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\facePvms\Uninstall.lnk" "$INSTDIR\uninst.exe"
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


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地从你的计算机移除。"
FunctionEnd

Function un.onInit
!insertmacro MUI_UNGETLANGUAGE
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "你确实要完全移除 $(^Name) ，其及所有的组件？" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\wow64win.dll"
  Delete "$INSTDIR\wow64cpu.dll"
  Delete "$INSTDIR\wow64.dll"
  Delete "$INSTDIR\WordStrokeHelper32.dll"
  Delete "$INSTDIR\SuperRender.dll"
  Delete "$INSTDIR\sqldrivers\qsqlpsqld.dll"
  Delete "$INSTDIR\sqldrivers\qsqlpsql.dll"
  Delete "$INSTDIR\sqldrivers\qsqlmysqld.dll"
  Delete "$INSTDIR\sqldrivers\qsqlmysql.dll"
  Delete "$INSTDIR\sqldrivers\qsqlited.dll"
  Delete "$INSTDIR\sqldrivers\qsqlite.dll"
  Delete "$INSTDIR\SoftwareLicence.txt"
  Delete "$INSTDIR\resources\resources.qrc"
  Delete "$INSTDIR\resources\icon.rc"
  Delete "$INSTDIR\resources\icon.ico"
  Delete "$INSTDIR\resources\calendar.png"
  Delete "$INSTDIR\resources\au.png"
  Delete "$INSTDIR\resources\ar.png"
  Delete "$INSTDIR\resources\al.png"
  Delete "$INSTDIR\resources\ad.png"
  Delete "$INSTDIR\Qt5Xml.dll"
  Delete "$INSTDIR\Qt5Widgets.dll"
  Delete "$INSTDIR\Qt5Test.dll"
  Delete "$INSTDIR\Qt5Sql.dll"
  Delete "$INSTDIR\Qt5SerialPort.dll"
  Delete "$INSTDIR\Qt5PrintSupport.dll"
  Delete "$INSTDIR\Qt5OpenGL.dll"
  Delete "$INSTDIR\Qt5Gui.dll"
  Delete "$INSTDIR\Qt5Core.dll"
  Delete "$INSTDIR\qrc_resources.o"
  Delete "$INSTDIR\qrc_resources.cpp"
  Delete "$INSTDIR\plugins\sqldrivers\qsqlodbcd4.dll"
  Delete "$INSTDIR\plugins\sqldrivers\qsqlodbc4.dll"
  Delete "$INSTDIR\plugins\sqldrivers\qsqlited4.dll"
  Delete "$INSTDIR\plugins\sqldrivers\qsqlite4.dll"
  Delete "$INSTDIR\plugins\sqldrivers\libqsqlodbcd4.a"
  Delete "$INSTDIR\plugins\sqldrivers\libqsqlodbc4.a"
  Delete "$INSTDIR\plugins\sqldrivers\libqsqlited4.a"
  Delete "$INSTDIR\plugins\sqldrivers\libqsqlite4.a"
  Delete "$INSTDIR\PlayCtrl.lib"
  Delete "$INSTDIR\PlayCtrl.dll"
  Delete "$INSTDIR\platforms\qwindows.dll"
  Delete "$INSTDIR\platforms\qminimal.dll"
  Delete "$INSTDIR\opengl32sw.dll"
  Delete "$INSTDIR\OpenAL32.dll"
  Delete "$INSTDIR\msvcr90.dll"
  Delete "$INSTDIR\MP_VIE.dll"
  Delete "$INSTDIR\MP_Render.dll"
  Delete "$INSTDIR\models\face_fd.bin"
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
  Delete "$INSTDIR\libopencv_objdetect2413.dll"
  Delete "$INSTDIR\libopencv_imgproc2413.dll"
  Delete "$INSTDIR\libopencv_highgui2413.dll"
  Delete "$INSTDIR\libopencv_core2413.dll"
  Delete "$INSTDIR\libiconv2.dll"
  Delete "$INSTDIR\libgomp-1.dll"
  Delete "$INSTDIR\libGLESv2.dll"
  Delete "$INSTDIR\libgcc_s_dw2-1.dll"
  Delete "$INSTDIR\libface_rec.dll"
  Delete "$INSTDIR\libfacev_lib.dll"
  Delete "$INSTDIR\libfaced_lib.dll"
  Delete "$INSTDIR\libfacea_lib.dll"
  Delete "$INSTDIR\libEGL.dll"
  Delete "$INSTDIR\install.nsi"
  Delete "$INSTDIR\HWDecode.dll"
  Delete "$INSTDIR\HKVS_play.o"
  Delete "$INSTDIR\HCPreview.dll"
  Delete "$INSTDIR\HCNetSDKCom\SystemTransform.dll"
  Delete "$INSTDIR\HCNetSDKCom\StreamTransClient.dll"
  Delete "$INSTDIR\HCNetSDKCom\OpenAL32.dll"
  Delete "$INSTDIR\HCNetSDKCom\msvcr90.dll"
  Delete "$INSTDIR\HCNetSDKCom\libiconv2.dll"
  Delete "$INSTDIR\HCNetSDKCom\HCVoiceTalk.dll"
  Delete "$INSTDIR\HCNetSDKCom\HCPreview.lib"
  Delete "$INSTDIR\HCNetSDKCom\HCPreview.dll"
  Delete "$INSTDIR\HCNetSDKCom\HCPlayBack.dll"
  Delete "$INSTDIR\HCNetSDKCom\HCIndustry.dll"
  Delete "$INSTDIR\HCNetSDKCom\HCGeneralCfgMgr.lib"
  Delete "$INSTDIR\HCNetSDKCom\HCGeneralCfgMgr.dll"
  Delete "$INSTDIR\HCNetSDKCom\HCDisplay.dll"
  Delete "$INSTDIR\HCNetSDKCom\HCCoreDevCfg.dll"
  Delete "$INSTDIR\HCNetSDKCom\HCAlarm.lib"
  Delete "$INSTDIR\HCNetSDKCom\HCAlarm.dll"
  Delete "$INSTDIR\HCNetSDKCom\AudioIntercom.dll"
  Delete "$INSTDIR\HCNetSDKCom\AnalyzeData.dll"
  Delete "$INSTDIR\HCNetSDK.dll"
  Delete "$INSTDIR\HCGeneralCfgMgr.dll"
  Delete "$INSTDIR\HCCoreDevCfg.dll"
  Delete "$INSTDIR\HCCore.dll"
  Delete "$INSTDIR\HCAlarm.dll"
  Delete "$INSTDIR\global.o"
  Delete "$INSTDIR\gdiplus.dll"
  Delete "$INSTDIR\facerecognize.o"
  Delete "$INSTDIR\facePvms_resource_res.o"
  Delete "$INSTDIR\facepvms.o"
  Delete "$INSTDIR\facePvms.exe"
  Delete "$INSTDIR\designer.ico"
  Delete "$INSTDIR\DefineCalendar.o"
  Delete "$INSTDIR\DefDateTimeEdit.o"
  Delete "$INSTDIR\database.o"
  Delete "$INSTDIR\D3DX9_43.dll"
  Delete "$INSTDIR\C_1252.NLS"
  Delete "$INSTDIR\config\config.ini"
  Delete "$INSTDIR\ClientDemoDll\zlib1.dll"
  Delete "$INSTDIR\ClientDemoDll\ReadMe.txt"
  Delete "$INSTDIR\ClientDemoDll\libxml2.dll"
  Delete "$INSTDIR\ClientDemoDll\iconv.dll"
  Delete "$INSTDIR\ClientDemoDll\calib.dll"
  Delete "$INSTDIR\cascade\readme"
  Delete "$INSTDIR\cascade\haarcascade_frontalface_alt2.xml"
  Delete "$INSTDIR\cascade\haarcascade_eye.xml"
  Delete "$INSTDIR\AudioRender.dll"
  Delete "$INSTDIR\AudioIntercom.dll"
  Delete "$INSTDIR\apisetschema.dll"

  Delete "$SMPROGRAMS\facePvms\Uninstall.lnk"
  Delete "$SMPROGRAMS\facePvms\Website.lnk"
  Delete "$DESKTOP\facePvms.lnk"
  Delete "$SMPROGRAMS\facePvms\facePvms.lnk"

  RMDir "$SMPROGRAMS\facePvms"
  RMDir "$INSTDIR\sqldrivers"
  RMDir "$INSTDIR\resources"
  RMDir "$INSTDIR\plugins\sqldrivers"
  RMDir "$INSTDIR\platforms"
  RMDir "$INSTDIR\models"
  RMDir "$INSTDIR\HCNetSDKCom"
  RMDir "$INSTDIR\config"
  RMDir "$INSTDIR\ClientDemoDll"
  RMDir "$INSTDIR\cascade"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd