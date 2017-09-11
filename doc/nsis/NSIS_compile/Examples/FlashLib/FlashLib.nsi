/*
<NSIS图片Flash特效脚本>
脚本编写：zhfi
特别感谢：风铃夜思雨，Restools，X-Star
*/

Var hBitmap

!include MUI.nsh
; --------------------------------------------------
; General settings.
Name "FlashLib_Test Example"
OutFile "FlashLib_Test.exe"
SetCompressor /SOLID lzma     

ReserveFile "${NSISDIR}\Plugins\system.dll"
ReserveFile "${NSISDIR}\Plugins\FlashLib.dll"
ReserveFile "${NSISDIR}\Examples\FlashLib\1.swf"
; --------------------------------------------------
; MUI interface settings.
!define MUI_FINISHPAGE_NOAUTOCLOSE
; --------------------------------------------------
; Installer pages
!define MUI_PAGE_CUSTOMFUNCTION_PRE Pre
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE Leave
!insertmacro MUI_PAGE_WELCOME

!insertmacro MUI_PAGE_INSTFILES

!define MUI_PAGE_CUSTOMFUNCTION_Pre Pre
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE Leave
!insertmacro MUI_PAGE_FINISH
; --------------------------------------------------
; Languages.
!insertmacro MUI_LANGUAGE "SimpChinese"
; --------------------------------------------------
Section ""
SectionEnd

Function .onInit
    InitPluginsDir
    File /oname=$PLUGINSDIR\1.swf "${NSISDIR}\Examples\FlashLib\1.swf"
    File /oname=$PLUGINSDIR\FlashLib.dll "${NSISDIR}\Plugins\FlashLib.dll"
FunctionEnd

Function Pre
    System::Call 'user32::LoadImage(i,t,i,i,i,i,) i (0,"$PLUGINSDIR\modern-wizard.bmp",0,0,0,0x2010) .s'
    Pop $R0
    System::Call '$PLUGINSDIR\FlashLib::FlashLibInit(i,i,i,i,i,i,i) i (0,0,164,291,$HWNDPARENT,$R0,true) .s'
    Pop $hBitmap
    System::Call '$PLUGINSDIR\FlashLib::FlashLoadMovie(i,t) i ($hBitmap,"$PLUGINSDIR\1.swf")'
FunctionEnd

Function Leave
    System::Call '$PLUGINSDIR\FlashLib::FlashLibFree(i $hBitmap)'
FunctionEnd

Function .onGUIEnd
    System::Call 'FlashLib::FlashLibFree(i $hBitmap)'
    System::Free
    SetPluginUnload manual
    Delete /REBOOTOK $PLUGINSDIR\FlashLib.dll
    RMDIR /REBOOTOK $PLUGINSDIR
FunctionEnd
