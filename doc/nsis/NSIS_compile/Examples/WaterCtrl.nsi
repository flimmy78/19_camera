/*
<NSISͼƬˮ����Ч�ű�>
�ű���д��zhfi
�ر��л��Restools��X-Star

��ʾ:ˮ�Ƶ�ͼ�����Ƿ�ת��ͼƬ����ʾ��ʱ��ᷭתͼƬ����ʾ��
*/

!include MUI.nsh
; --------------------------------------------------
; General settings.

Name "WaterCtrl_Test Example"
OutFile "WaterCtrl_Test.exe"
SetCompressor /SOLID lzma     

ReserveFile "${NSISDIR}\Plugins\system.dll"
ReserveFile "${NSISDIR}\Plugins\waterctrl.dll"

; --------------------------------------------------
; MUI interface settings.
!define MUI_FINISHPAGE_NOAUTOCLOSE
; --------------------------------------------------
; Insert MUI pages.
!define MUI_WELCOMEFINISHPAGE_BITMAP  "${NSISDIR}\Contrib\Graphics\Wizard\win.bmp"

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

Section ""
SectionEnd

Function .onInit
    InitPluginsDir
    File /oname=$PLUGINSDIR\waterctrl.dll "${NSISDIR}\Plugins\waterctrl.dll"
FunctionEnd

Function .onGUIEnd
    waterctrl::disablewater
    System::Free
    SetPluginUnload manual
FunctionEnd

Function Pre
    System::Call 'user32::LoadImage(i,t,i,i,i,i,) i (0,"$PLUGINSDIR\modern-wizard.bmp",0,0,0,0x2010) .s'
    Pop $R0
    System::Call '$PLUGINSDIR\waterctrl::enablewater(i,i,i,i,i,i) i ($HWNDPARENT,0,0,$R0,3,50)'
    System::Call '$PLUGINSDIR\waterctrl::setwaterparent(i $HWNDPARENT)'
    System::Call '$PLUGINSDIR\waterctrl::flattenwater()'
    System::Call '$PLUGINSDIR\waterctrl::waterblob(i,i,i,i) i (70,198,10,1000)'
FunctionEnd

Function Leave
    System::Call '$PLUGINSDIR\waterctrl::disablewater()'
FunctionEnd
