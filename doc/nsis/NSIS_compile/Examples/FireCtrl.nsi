/*
<NSIS图片火焰特效脚本>
脚本编写：zhfi
特别感谢：Restools，X-Star

提示:火焰底图必须是翻转的图片，显示的时候会翻转图片来显示。
*/

!include MUI.nsh
; --------------------------------------------------
; General settings.
Name "Firectrl_Test Example"
OutFile "Firectrl_Test.exe"
SetCompressor /SOLID lzma     

ReserveFile "${NSISDIR}\Plugins\system.dll"
ReserveFile "${NSISDIR}\Plugins\Firectrl.dll"

SetFont Tahoma 8
; --------------------------------------------------
; MUI interface settings.
!define MUI_FINISHPAGE_NOAUTOCLOSE
; --------------------------------------------------
; Insert MUI pages.
!define MUI_WELCOMEFINISHPAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Wizard\win.bmp"

; Installer pages
!define MUI_PAGE_CUSTOMFUNCTION_PRE pre
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE Leave
!insertmacro MUI_PAGE_WELCOME

!insertmacro MUI_PAGE_INSTFILES

!define MUI_PAGE_CUSTOMFUNCTION_Pre pre
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE Leave
!insertmacro MUI_PAGE_FINISH
; --------------------------------------------------
; Languages.
!insertmacro MUI_LANGUAGE "SimpChinese"

Section ""
SectionEnd

Function .onInit
    InitPluginsDir
    File /oname=$PLUGINSDIR\Firectrl.dll "${NSISDIR}\Plugins\Firectrl.dll"
FunctionEnd

Function .onGUIEnd
    Firectrl::disablefire
    System::Free
    SetPluginUnload manual
FunctionEnd

Function Pre
    System::Call 'user32::LoadImage(i,t,i,i,i,i,) i (0,"$PLUGINSDIR\modern-wizard.bmp",0,0,0,0x2010) .s'
    Pop $R0
    System::Call '$PLUGINSDIR\Firectrl::enablefire(i,i,i,i,i) i ($HWNDPARENT,0,0,$R0,50)'
FunctionEnd

Function Leave
    System::Call '$PLUGINSDIR\Firectrl::disablefire()'
FunctionEnd
