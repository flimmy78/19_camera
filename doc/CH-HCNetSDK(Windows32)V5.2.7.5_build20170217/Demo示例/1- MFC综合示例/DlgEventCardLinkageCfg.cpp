// DlgEventCardLinkageCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgEventCardLinkageCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgEventCardLinkageCfg dialog


DlgEventCardLinkageCfg::DlgEventCardLinkageCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgEventCardLinkageCfg::IDD, pParent)
    , m_iLocalController(0)
    , m_dwEventID(1)
{
	//{{AFX_DATA_INIT(DlgEventCardLinkageCfg)
    m_byProMode = FALSE;
    m_byMacAddr = FALSE;
    byMainDevBuzzer = FALSE;
    m_sCardNo = _T("");
    m_sMacAddr = _T("");
    m_dwEventSourceID = 0;
	m_bLinkCapPic = FALSE;
    m_bLinkRecordVideo = FALSE;
	//}}AFX_DATA_INIT
    memset(&m_struEventCardLinkageCfgV50, 0, sizeof(m_struEventCardLinkageCfgV50));
    m_struEventCardLinkageCfgV50.dwSize = sizeof(m_struEventCardLinkageCfgV50);
    memset(&m_struEventCardLinkageCond, 0, sizeof(m_struEventCardLinkageCond));
    m_struEventCardLinkageCond.dwSize = sizeof(m_struEventCardLinkageCond);
}


void DlgEventCardLinkageCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgEventCardLinkageCfg)
    DDX_Control(pDX, IDC_TREE_OPENDOOR, m_treeDoorOpen);
    DDX_Control(pDX, IDC_TREE_CLOSEDOOR, m_treeDoorClose);
    DDX_Control(pDX, IDC_TREE_READERBUZZER, m_treeCardReaderBuzzer);
    DDX_Control(pDX, IDC_TREE_ALARMOUT, m_treeAlarmOut);
    DDX_Control(pDX, IDC_TREE_NORMALOPEN, m_treeNormalOpen);
    DDX_Control(pDX, IDC_TREE_NORMALCLOSE, m_treeNormalClose);
	DDX_Check(pDX, IDC_CHECK_PROMODE, m_byProMode);
    DDX_Check(pDX, IDC_CHECK_MAC_ADDR, m_byMacAddr);
    DDX_Check(pDX, IDC_CHECK_BUZZER, byMainDevBuzzer);
    DDX_Control(pDX, IDC_COMBO_MAIN_TYPE, m_comboMainEventType);
    DDX_Control(pDX, IDC_COMBO_OTHER_TYPE, m_comboSubEventType);
	DDX_Text(pDX, IDC_EDIT_CARD, m_sCardNo);
    DDX_Text(pDX, IDC_EDIT_MAC_ADDR, m_sMacAddr);
    DDX_Text(pDX, IDC_EDIT_EVENT_ID, m_dwEventSourceID);
	DDX_Check(pDX, IDC_CHK_LINKAGE_CAP_PIC, m_bLinkCapPic);
    DDX_Check(pDX, IDC_CHK_LINKAGE_RECORD_VIDEO, m_bLinkRecordVideo);
	//}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_EDIT_LOCAL_CONTROLLER, m_iLocalController);
    DDX_Control(pDX, IDC_TREE_ALARM_OUT_CLOSE, m_treeAlarmOutClose);
    DDX_Control(pDX, IDC_TREE_ALARM_IN_SETUP, m_treeAlarmInSetup);
    DDX_Control(pDX, IDC_TREE_ALARM_IN_CLOSE, m_treeAlarmInClose);
    DDX_Text(pDX, IDC_EDIT_EVENT, m_dwEventID);
    DDV_MinMaxUInt(pDX, m_dwEventID, 1, 500);
}


BEGIN_MESSAGE_MAP(DlgEventCardLinkageCfg, CDialog)
	//{{AFX_MSG_MAP(DlgEventCardLinkageCfg)
    ON_BN_CLICKED(IDC_BUTTON_SET, OnBtnSet)
    ON_BN_CLICKED(IDC_BUTTON_GET, OnBtnGet)
    ON_NOTIFY(NM_CLICK, IDC_TREE_READERBUZZER, OnClickTreeCardReaderBuzzer)
    ON_NOTIFY(NM_CLICK, IDC_TREE_ALARMOUT, OnClickTreeAlarmOut)
    ON_NOTIFY(NM_CLICK, IDC_TREE_OPENDOOR, OnClickTreeDoorOpen)
	ON_NOTIFY(NM_CLICK, IDC_TREE_CLOSEDOOR, OnClickTreeDoorClose)
    ON_NOTIFY(NM_CLICK, IDC_TREE_NORMALOPEN, OnClickTreeNormalOpen)
	ON_NOTIFY(NM_CLICK, IDC_TREE_NORMALCLOSE, OnClickTreeNormalClose)
    ON_CBN_SELCHANGE(IDC_COMBO_MAIN_TYPE, OnSelchangeEventMainType)
	//}}AFX_MSG_MAP
    ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT_CLOSE, &DlgEventCardLinkageCfg::OnNMClickTreeAlarmOutClose)
    ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_IN_SETUP, &DlgEventCardLinkageCfg::OnNMClickTreeAlarmInSetup)
    ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_IN_CLOSE, &DlgEventCardLinkageCfg::OnNMClickTreeAlarmInClose)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgEventCardLinkageCfg message handlers

BOOL DlgEventCardLinkageCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    
    InitMainEventType();
    SubEventTypeDev();
    CreateTree();
    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgEventCardLinkageCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetTreeSel(); 
    char szLan[1024];
    m_struEventCardLinkageCfgV50.byCapturePic = m_bLinkCapPic;
    m_struEventCardLinkageCfgV50.byRecordVideo = m_bLinkRecordVideo;
    DWORD dwStatus = 0;
    m_struEventCardLinkageCond.dwEventID = m_dwEventID;
    m_struEventCardLinkageCond.wLocalControllerID = m_iLocalController;
    if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_SET_EVENT_CARD_LINKAGE_CFG_V50, 1, &m_struEventCardLinkageCond, sizeof(m_struEventCardLinkageCond), &dwStatus, &m_struEventCardLinkageCfgV50, sizeof(m_struEventCardLinkageCfgV50)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_EVENT_CARD_LINKAGE_CFG_V50 Failed");
        g_StringLanType(szLan, "�����¼��򿨺�������������ʧ��", "Set event card linkage cfg Failed");
        MessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_EVENT_CARD_LINKAGE_CFG_V50 SUCC");
    }
}

void DlgEventCardLinkageCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    DWORD dwReturned = 0;
    char szLan[1024];
    DWORD dwStatus = 0;
    m_struEventCardLinkageCond.dwEventID = m_dwEventID;
    m_struEventCardLinkageCond.wLocalControllerID = m_iLocalController;
    if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_EVENT_CARD_LINKAGE_CFG_V50, 1, &m_struEventCardLinkageCond, sizeof(m_struEventCardLinkageCond), &dwStatus, &m_struEventCardLinkageCfgV50, sizeof(m_struEventCardLinkageCfgV50)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_EVENT_CARD_LINKAGE_CFG_V50 Failed");
        g_StringLanType(szLan, "��ȡ�¼��򿨺�������������ʧ��", "Get event card linkage cfg Failed");
        MessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_EVENT_CARD_LINKAGE_CFG_V50 SUCC");
        if (m_struEventCardLinkageCfgV50.byProMode == 1)
        {
            m_byProMode = TRUE;
        }
        if (m_struEventCardLinkageCfgV50.byProMode == 2)
        {
            m_byMacAddr = TRUE;
        }
        m_dwEventSourceID = m_struEventCardLinkageCfgV50.dwEventSourceID;
        byMainDevBuzzer = m_struEventCardLinkageCfgV50.byMainDevBuzzer;
        m_bLinkCapPic = m_struEventCardLinkageCfgV50.byCapturePic;
        m_bLinkRecordVideo = m_struEventCardLinkageCfgV50.byRecordVideo;
        if (m_byProMode)
        {
            m_sCardNo.Format("%s", m_struEventCardLinkageCfgV50.uLinkageInfo.byCardNo);
        }
        if (m_byMacAddr)
        {
            m_sMacAddr.Format("%02X:%02X:%02X:%02X:%02X:%02X", m_struEventCardLinkageCfgV50.uLinkageInfo.byMACAddr[0], m_struEventCardLinkageCfgV50.uLinkageInfo.byMACAddr[1], \
                m_struEventCardLinkageCfgV50.uLinkageInfo.byMACAddr[2], m_struEventCardLinkageCfgV50.uLinkageInfo.byMACAddr[3], m_struEventCardLinkageCfgV50.uLinkageInfo.byMACAddr[4], \
                m_struEventCardLinkageCfgV50.uLinkageInfo.byMACAddr[5]);
        }
        if (m_byProMode == FALSE && m_byMacAddr == FALSE)
        {
            m_comboMainEventType.SetCurSel(m_struEventCardLinkageCfgV50.uLinkageInfo.struEventLinkage.wMainEventType);

            DWORD dwMainEventType = m_comboMainEventType.GetCurSel();
            if (dwMainEventType == 0)
            {
                SubEventTypeDev();
            }
            else if (dwMainEventType == 1)
            {
                SubEventTypeAlarm();
            }
            else if (dwMainEventType == 2)
            {
                SubEventTypeDoor();
            }
            else if (dwMainEventType == 3)
            {
                SubEventTypeCardReader();
            }

            m_comboSubEventType.SetCurSel(m_struEventCardLinkageCfgV50.uLinkageInfo.struEventLinkage.wSubEventType);
        }
        UpdateData(FALSE);
        CreateTree();
    }
}

void DlgEventCardLinkageCfg::OnSelchangeEventMainType() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    DWORD dwMainEventType = m_comboMainEventType.GetCurSel();
    if (dwMainEventType == 0)
    {
        SubEventTypeDev();
    } 
    else if (dwMainEventType == 1)
    {
        SubEventTypeAlarm();
    }
    else if (dwMainEventType == 2)
    {
        SubEventTypeDoor();
    }
    else if (dwMainEventType == 3)
    {
        SubEventTypeCardReader();
    }

    UpdateData(FALSE);
}

void DlgEventCardLinkageCfg::CreateTree()
{
    CString strTemp =_T("");
    CString strChanTmp = _T("");
    int i = 0;
    m_treeCardReaderBuzzer.DeleteAllItems();
    m_treeAlarmOut.DeleteAllItems();
    
    HTREEITEM hChanItem = NULL;
    HTREEITEM hFirstItem = NULL;
       
    for (i = 0; i < sizeof(m_struEventCardLinkageCfgV50.byReaderBuzzer); i++)
    {
        strTemp.Format("Buzzer %d", i + 1);
        hChanItem = m_treeCardReaderBuzzer.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }

        m_treeCardReaderBuzzer.SetItemData(hChanItem, i);

        if (m_struEventCardLinkageCfgV50.byReaderBuzzer[i])
        {
            m_treeCardReaderBuzzer.SetCheck(hChanItem, TRUE);
        }
    }

    m_treeCardReaderBuzzer.SelectItem(hFirstItem);
    m_treeCardReaderBuzzer.Expand(m_treeCardReaderBuzzer.GetRootItem(), TVE_EXPAND);

    hChanItem = NULL;
    hFirstItem = NULL;

    for (i = 0; i < sizeof(m_struEventCardLinkageCfgV50.byAlarmout); i++)
    {
        strTemp.Format("AlarmOut %d", i + 1);
        hChanItem = m_treeAlarmOut.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }

        m_treeAlarmOut.SetItemData(hChanItem, i);

        if (m_struEventCardLinkageCfgV50.byAlarmout[i])
        {
            m_treeAlarmOut.SetCheck(hChanItem, TRUE);
        }
    }

    m_treeAlarmOut.SelectItem(hFirstItem);
	m_treeAlarmOut.Expand(m_treeAlarmOut.GetRootItem(),TVE_EXPAND);

    hChanItem = NULL;
    hFirstItem = NULL;
    m_treeDoorOpen.DeleteAllItems();    
    for (i = 0; i < sizeof(m_struEventCardLinkageCfgV50.byOpenDoor); i++)
    {
        strTemp.Format("Door %d", i + 1);
        hChanItem = m_treeDoorOpen.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }
        
        m_treeDoorOpen.SetItemData(hChanItem, i);
        
        if (m_struEventCardLinkageCfgV50.byOpenDoor[i])
        {
            m_treeDoorOpen.SetCheck(hChanItem, TRUE);
        }
    }
    m_treeDoorOpen.SelectItem(hFirstItem);
	m_treeDoorOpen.Expand(m_treeDoorOpen.GetRootItem(),TVE_EXPAND);


    hChanItem = NULL;
    hFirstItem = NULL;
    m_treeDoorClose.DeleteAllItems();
    for (i = 0; i < sizeof(m_struEventCardLinkageCfgV50.byCloseDoor); i++)
    {
        strTemp.Format("Door %d", i + 1);
        hChanItem = m_treeDoorClose.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }      
        m_treeDoorClose.SetItemData(hChanItem, i);
        
        if (m_struEventCardLinkageCfgV50.byCloseDoor[i])
        {
            m_treeDoorClose.SetCheck(hChanItem, TRUE);
        }
    }
    m_treeDoorClose.SelectItem(hFirstItem);
	m_treeDoorClose.Expand(m_treeDoorClose.GetRootItem(),TVE_EXPAND);

    hChanItem = NULL;
    hFirstItem = NULL;
    m_treeNormalOpen.DeleteAllItems();    
    for (i = 0; i < sizeof(m_struEventCardLinkageCfgV50.byNormalOpen); i++)
    {
        strTemp.Format("Door %d", i + 1);
        hChanItem = m_treeNormalOpen.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }
        
        m_treeNormalOpen.SetItemData(hChanItem, i);
        
        if (m_struEventCardLinkageCfgV50.byNormalOpen[i])
        {
            m_treeNormalOpen.SetCheck(hChanItem, TRUE);
        }
    }
    m_treeNormalOpen.SelectItem(hFirstItem);
	m_treeNormalOpen.Expand(m_treeNormalOpen.GetRootItem(),TVE_EXPAND);

    hChanItem = NULL;
    hFirstItem = NULL;
    m_treeNormalClose.DeleteAllItems();    
    for (i = 0; i < sizeof(m_struEventCardLinkageCfgV50.byNormalClose); i++)
    {
        strTemp.Format("Door %d", i + 1);
        hChanItem = m_treeNormalClose.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }
        
        m_treeNormalClose.SetItemData(hChanItem, i);
        
        if (m_struEventCardLinkageCfgV50.byNormalClose[i])
        {
            m_treeNormalClose.SetCheck(hChanItem, TRUE);
        }
    }
    m_treeNormalClose.SelectItem(hFirstItem);
    m_treeNormalClose.Expand(m_treeNormalClose.GetRootItem(),TVE_EXPAND);

    hChanItem = NULL;
    hFirstItem = NULL;
    m_treeAlarmOutClose.DeleteAllItems();
    for (i = 0; i < sizeof(m_struEventCardLinkageCfgV50.byAlarmOutClose); i++)
    {
        strTemp.Format("AlarmOut %d", i + 1);
        hChanItem = m_treeAlarmOutClose.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }

        m_treeAlarmOutClose.SetItemData(hChanItem, i);

        if (m_struEventCardLinkageCfgV50.byAlarmOutClose[i])
        {
            m_treeAlarmOutClose.SetCheck(hChanItem, TRUE);
        }
    }
    m_treeAlarmOutClose.SelectItem(hFirstItem);
    m_treeAlarmOutClose.Expand(m_treeAlarmOutClose.GetRootItem(), TVE_EXPAND);

    hChanItem = NULL;
    hFirstItem = NULL;
    m_treeAlarmInSetup.DeleteAllItems();
    for (i = 0; i < sizeof(m_struEventCardLinkageCfgV50.byAlarmInSetup); i++)
    {
        strTemp.Format("AlarmIn %d", i + 1);
        hChanItem = m_treeAlarmInSetup.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }

        m_treeAlarmInSetup.SetItemData(hChanItem, i);

        if (m_struEventCardLinkageCfgV50.byAlarmInSetup[i])
        {
            m_treeAlarmInSetup.SetCheck(hChanItem, TRUE);
        }
    }
    m_treeAlarmInSetup.SelectItem(hFirstItem);
    m_treeAlarmInSetup.Expand(m_treeAlarmInSetup.GetRootItem(), TVE_EXPAND);

    hChanItem = NULL;
    hFirstItem = NULL;
    m_treeAlarmInClose.DeleteAllItems();
    for (i = 0; i < sizeof(m_struEventCardLinkageCfgV50.byAlarmInClose); i++)
    {
        strTemp.Format("AlarmIn %d", i + 1);
        hChanItem = m_treeAlarmInClose.InsertItem(strTemp, 0, 0, TVI_ROOT);
        if (hFirstItem == NULL)
        {
            hFirstItem = hChanItem;
        }

        m_treeAlarmInClose.SetItemData(hChanItem, i);

        if (m_struEventCardLinkageCfgV50.byAlarmInClose[i])
        {
            m_treeAlarmInClose.SetCheck(hChanItem, TRUE);
        }
    }
    m_treeAlarmInClose.SelectItem(hFirstItem);
    m_treeAlarmInClose.Expand(m_treeAlarmInClose.GetRootItem(), TVE_EXPAND);
}

void DlgEventCardLinkageCfg::GetTreeSel()
{
	UpdateData(TRUE); 
	memset(&m_struEventCardLinkageCfgV50, 0 , sizeof(m_struEventCardLinkageCfgV50));
	m_struEventCardLinkageCfgV50.dwSize = sizeof(m_struEventCardLinkageCfgV50);
    if (m_byProMode == TRUE)
    {
        m_struEventCardLinkageCfgV50.byProMode = 1;
    }
    if (m_byMacAddr == TRUE)
    {
        m_struEventCardLinkageCfgV50.byProMode = 2;
    }
    if (m_byProMode == FALSE && m_byMacAddr == FALSE)
    {
        m_struEventCardLinkageCfgV50.byProMode = 0;
    }
	m_struEventCardLinkageCfgV50.dwEventSourceID = m_dwEventSourceID;
    m_struEventCardLinkageCfgV50.byMainDevBuzzer = byMainDevBuzzer;
    if (m_struEventCardLinkageCfgV50.byProMode == 1)
    {
        memcpy(m_struEventCardLinkageCfgV50.uLinkageInfo.byCardNo, m_sCardNo, m_sCardNo.GetLength());
    }
    if (m_struEventCardLinkageCfgV50.byProMode == 2)
    {
        char sMac[32] = { 0 };
        int iLen = m_sMacAddr.GetLength();
        memcpy(sMac, m_sMacAddr, iLen);
        StrToMac(sMac, m_struEventCardLinkageCfgV50.uLinkageInfo.byMACAddr);
    }
    if (m_struEventCardLinkageCfgV50.byProMode == 0)
    {
        m_struEventCardLinkageCfgV50.uLinkageInfo.struEventLinkage.wMainEventType = m_comboMainEventType.GetCurSel();
        m_struEventCardLinkageCfgV50.uLinkageInfo.struEventLinkage.wSubEventType = m_comboSubEventType.GetCurSel();
    }

    int i = 0; 
	HTREEITEM hTreeItem;

	BOOL bCheck;
	DWORD dwIndex;
	DWORD dwCount = 0; 
	CTreeCtrl *treeCtr = &m_treeAlarmOut; 
    dwCount = m_treeAlarmOut.GetCount(); 
	hTreeItem = m_treeAlarmOut.GetRootItem();

    for ( i=0; i<dwCount; i++)
    {
		bCheck = treeCtr->GetCheck(hTreeItem);
		dwIndex = treeCtr->GetItemData(hTreeItem);
		m_struEventCardLinkageCfgV50.byAlarmout[dwIndex] = bCheck;
		hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }

	treeCtr = &m_treeCardReaderBuzzer;
	hTreeItem = m_treeCardReaderBuzzer.GetRootItem();
	dwCount = m_treeCardReaderBuzzer.GetCount(); 
    for ( i=0; i<dwCount; i++)
    {
		bCheck = treeCtr->GetCheck(hTreeItem);
		dwIndex = treeCtr->GetItemData(hTreeItem);
		m_struEventCardLinkageCfgV50.byReaderBuzzer[dwIndex] = bCheck;
		hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }

	treeCtr = &m_treeDoorOpen;
	hTreeItem = m_treeDoorOpen.GetRootItem();
	dwCount = m_treeDoorOpen.GetCount(); 
    for ( i=0; i<dwCount; i++)
    {
		bCheck = treeCtr->GetCheck(hTreeItem);
		dwIndex = treeCtr->GetItemData(hTreeItem);
		m_struEventCardLinkageCfgV50.byOpenDoor[dwIndex] = bCheck;
		hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }

	treeCtr = &m_treeDoorClose;
	hTreeItem = m_treeDoorClose.GetRootItem();
	dwCount = m_treeDoorClose.GetCount(); 
    for ( i=0; i<dwCount; i++)
    {
		bCheck = treeCtr->GetCheck(hTreeItem);
		dwIndex = treeCtr->GetItemData(hTreeItem);
		m_struEventCardLinkageCfgV50.byCloseDoor[dwIndex] = bCheck;
		hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }

    treeCtr = &m_treeNormalOpen;
    hTreeItem = m_treeNormalOpen.GetRootItem();
    dwCount = m_treeNormalOpen.GetCount(); 
    for ( i=0; i<dwCount; i++)
    {
        bCheck = treeCtr->GetCheck(hTreeItem);
        dwIndex = treeCtr->GetItemData(hTreeItem);
        m_struEventCardLinkageCfgV50.byNormalOpen[dwIndex] = bCheck;
        hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }

    treeCtr = &m_treeNormalClose;
    hTreeItem = m_treeNormalClose.GetRootItem();
    dwCount = m_treeNormalClose.GetCount(); 
    for ( i=0; i<dwCount; i++)
    {
        bCheck = treeCtr->GetCheck(hTreeItem);
        dwIndex = treeCtr->GetItemData(hTreeItem);
        m_struEventCardLinkageCfgV50.byNormalClose[dwIndex] = bCheck;
        hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem); 
    }

    treeCtr = &m_treeAlarmOutClose;
    hTreeItem = m_treeAlarmOutClose.GetRootItem();
    dwCount = m_treeAlarmOutClose.GetCount();
    for (i = 0; i < dwCount; i++)
    {
        bCheck = treeCtr->GetCheck(hTreeItem);
        dwIndex = treeCtr->GetItemData(hTreeItem);
        m_struEventCardLinkageCfgV50.byAlarmOutClose[dwIndex] = bCheck;
        hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem);
    }

    treeCtr = &m_treeAlarmInSetup;
    hTreeItem = m_treeAlarmInSetup.GetRootItem();
    dwCount = m_treeAlarmInSetup.GetCount();
    for (i = 0; i < dwCount; i++)
    {
        bCheck = treeCtr->GetCheck(hTreeItem);
        dwIndex = treeCtr->GetItemData(hTreeItem);
        m_struEventCardLinkageCfgV50.byAlarmInSetup[dwIndex] = bCheck;
        hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem);
    }

    treeCtr = &m_treeAlarmInClose;
    hTreeItem = m_treeAlarmInClose.GetRootItem();
    dwCount = m_treeAlarmInClose.GetCount();
    for (i = 0; i < dwCount; i++)
    {
        bCheck = treeCtr->GetCheck(hTreeItem);
        dwIndex = treeCtr->GetItemData(hTreeItem);
        m_struEventCardLinkageCfgV50.byAlarmInClose[dwIndex] = bCheck;
        hTreeItem = treeCtr->GetNextSiblingItem(hTreeItem);
    }
} 

void DlgEventCardLinkageCfg::OnClickTreeCardReaderBuzzer(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);

    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeCardReaderBuzzer.ScreenToClient(&pt);
    GetDlgItem(IDC_TREE_READERBUZZER)->GetWindowRect(&rc);
    m_treeCardReaderBuzzer.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeCardReaderBuzzer.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeCardReaderBuzzer.SelectItem(hSelect);
    DWORD dwIndex = m_treeCardReaderBuzzer.GetItemData(hSelect);
    BOOL bCheck = m_treeCardReaderBuzzer.GetCheck(hSelect);
    m_treeCardReaderBuzzer.SetCheck(hSelect, !bCheck);
    m_struEventCardLinkageCfgV50.byReaderBuzzer[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)//LVHT_TOLEFT)
    {
        m_treeCardReaderBuzzer.SetCheck(hSelect, !bCheck);
        m_struEventCardLinkageCfgV50.byReaderBuzzer[dwIndex] = !bCheck;
    }
    else
    {
        m_treeCardReaderBuzzer.SetCheck(hSelect, bCheck);
        m_struEventCardLinkageCfgV50.byReaderBuzzer[dwIndex] = bCheck;
	}
    UpdateData(FALSE); 
	*pResult = 0;
}

void DlgEventCardLinkageCfg::OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeAlarmOut.ScreenToClient(&pt);
    GetDlgItem(IDC_TREE_ALARMOUT)->GetWindowRect(&rc);
    m_treeAlarmOut.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeAlarmOut.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeAlarmOut.SelectItem(hSelect);
    DWORD dwIndex = m_treeAlarmOut.GetItemData(hSelect);
    BOOL bCheck = m_treeAlarmOut.GetCheck(hSelect);
    m_treeAlarmOut.SetCheck(hSelect, !bCheck);
    m_struEventCardLinkageCfgV50.byAlarmout[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)
    {
        m_treeAlarmOut.SetCheck(hSelect, !bCheck);
        m_struEventCardLinkageCfgV50.byAlarmout[dwIndex] = !bCheck;
    }
    else
    {
        m_treeAlarmOut.SetCheck(hSelect, bCheck);
        m_struEventCardLinkageCfgV50.byAlarmout[dwIndex] = bCheck;
	}
    UpdateData(FALSE);
	*pResult = 0;
}

void DlgEventCardLinkageCfg::OnClickTreeDoorOpen(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeDoorOpen.ScreenToClient(&pt);   
    m_treeDoorOpen.GetWindowRect(&rc);
    m_treeDoorOpen.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeDoorOpen.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeDoorOpen.SelectItem(hSelect);
    DWORD dwIndex = m_treeDoorOpen.GetItemData(hSelect);
    BOOL bCheck = m_treeDoorOpen.GetCheck(hSelect);
    m_treeDoorOpen.SetCheck(hSelect, !bCheck);
    m_struEventCardLinkageCfgV50.byOpenDoor[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)
    {
		m_treeDoorOpen.SetCheck(hSelect, !bCheck);
        m_struEventCardLinkageCfgV50.byOpenDoor[dwIndex] = !bCheck;
    }
    else
    {
        m_treeDoorOpen.SetCheck(hSelect, bCheck);
        m_struEventCardLinkageCfgV50.byOpenDoor[dwIndex] = bCheck;
	}
    UpdateData(FALSE);
	*pResult = 0;
}

void DlgEventCardLinkageCfg::OnClickTreeDoorClose(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeDoorClose.ScreenToClient(&pt);
    m_treeDoorClose.GetWindowRect(&rc);
    m_treeDoorClose.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;

    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeDoorClose.HitTest(pt, &uFlag);

    if (NULL == hSelect) 
    {
        return;
    }
    m_treeDoorClose.SelectItem(hSelect);
    DWORD dwIndex = m_treeDoorClose.GetItemData(hSelect);
    BOOL bCheck = m_treeDoorClose.GetCheck(hSelect);
    m_treeDoorClose.SetCheck(hSelect, !bCheck);
    m_struEventCardLinkageCfgV50.byCloseDoor[dwIndex] = !bCheck;

    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL )
    {
        m_treeDoorClose.SetCheck(hSelect, !bCheck);
        m_struEventCardLinkageCfgV50.byCloseDoor[dwIndex] = !bCheck;
    }
    else
    {
        m_treeDoorClose.SetCheck(hSelect, bCheck);
        m_struEventCardLinkageCfgV50.byCloseDoor[dwIndex] = bCheck;
    }	
    UpdateData(FALSE);
	*pResult = 0;
}

void DlgEventCardLinkageCfg::OnClickTreeNormalOpen(NMHDR* pNMHDR, LRESULT* pResult) 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeNormalOpen.ScreenToClient(&pt);   
    m_treeNormalOpen.GetWindowRect(&rc);
    m_treeNormalOpen.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeNormalOpen.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeNormalOpen.SelectItem(hSelect);
    DWORD dwIndex = m_treeNormalOpen.GetItemData(hSelect);
    BOOL bCheck = m_treeNormalOpen.GetCheck(hSelect);
    m_treeNormalOpen.SetCheck(hSelect, !bCheck);
    m_struEventCardLinkageCfgV50.byNormalOpen[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM ||uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)
    {
        m_treeNormalOpen.SetCheck(hSelect, !bCheck);
        m_struEventCardLinkageCfgV50.byNormalOpen[dwIndex] = !bCheck;
    }
    else
    {
        m_treeNormalOpen.SetCheck(hSelect, bCheck);
        m_struEventCardLinkageCfgV50.byNormalOpen[dwIndex] = bCheck;
    }
    UpdateData(FALSE);
    *pResult = 0;
}

void DlgEventCardLinkageCfg::OnClickTreeNormalClose(NMHDR* pNMHDR, LRESULT* pResult) 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    CPoint pt(0,0);
    CRect rc(0,0,0,0);
    GetCursorPos(&pt);
    m_treeNormalClose.ScreenToClient(&pt);   
    m_treeNormalClose.GetWindowRect(&rc);
    m_treeNormalClose.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;
    
    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeNormalClose.HitTest(pt, &uFlag);
    
    if (NULL == hSelect) 
    {
        return;
    }
    m_treeNormalClose.SelectItem(hSelect);
    DWORD dwIndex = m_treeNormalClose.GetItemData(hSelect);
    BOOL bCheck = m_treeNormalClose.GetCheck(hSelect);
    m_treeNormalClose.SetCheck(hSelect, !bCheck);
    m_struEventCardLinkageCfgV50.byNormalClose[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM || uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)
    {
        m_treeNormalClose.SetCheck(hSelect, !bCheck);
        m_struEventCardLinkageCfgV50.byNormalClose[dwIndex] = !bCheck;
    }
    else
    {
        m_treeNormalClose.SetCheck(hSelect, bCheck);
        m_struEventCardLinkageCfgV50.byNormalClose[dwIndex] = bCheck;
    }
    UpdateData(FALSE);
    *pResult = 0;
}

void DlgEventCardLinkageCfg::OnNMClickTreeAlarmOutClose(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    CPoint pt(0, 0);
    CRect rc(0, 0, 0, 0);
    GetCursorPos(&pt);
    m_treeAlarmOutClose.ScreenToClient(&pt);
    m_treeAlarmOutClose.GetWindowRect(&rc);
    m_treeAlarmOutClose.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;

    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeAlarmOutClose.HitTest(pt, &uFlag);

    if (NULL == hSelect)
    {
        return;
    }
    m_treeAlarmOutClose.SelectItem(hSelect);
    DWORD dwIndex = m_treeAlarmOutClose.GetItemData(hSelect);
    BOOL bCheck = m_treeAlarmOutClose.GetCheck(hSelect);
    m_treeAlarmOutClose.SetCheck(hSelect, !bCheck);
    m_struEventCardLinkageCfgV50.byAlarmOutClose[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM || uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)
    {
        m_treeAlarmOutClose.SetCheck(hSelect, !bCheck);
        m_struEventCardLinkageCfgV50.byAlarmOutClose[dwIndex] = !bCheck;
    }
    else
    {
        m_treeAlarmOutClose.SetCheck(hSelect, bCheck);
        m_struEventCardLinkageCfgV50.byAlarmOutClose[dwIndex] = bCheck;
    }
    UpdateData(FALSE);
    *pResult = 0;
}


void DlgEventCardLinkageCfg::OnNMClickTreeAlarmInSetup(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    CPoint pt(0, 0);
    CRect rc(0, 0, 0, 0);
    GetCursorPos(&pt);
    m_treeAlarmInSetup.ScreenToClient(&pt);
    m_treeAlarmInSetup.GetWindowRect(&rc);
    m_treeAlarmInSetup.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;

    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeAlarmInSetup.HitTest(pt, &uFlag);

    if (NULL == hSelect)
    {
        return;
    }
    m_treeAlarmInSetup.SelectItem(hSelect);
    DWORD dwIndex = m_treeAlarmInSetup.GetItemData(hSelect);
    BOOL bCheck = m_treeAlarmInSetup.GetCheck(hSelect);
    m_treeAlarmInSetup.SetCheck(hSelect, !bCheck);
    m_struEventCardLinkageCfgV50.byAlarmInSetup[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM || uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)
    {
        m_treeAlarmInSetup.SetCheck(hSelect, !bCheck);
        m_struEventCardLinkageCfgV50.byAlarmInSetup[dwIndex] = !bCheck;
    }
    else
    {
        m_treeAlarmInSetup.SetCheck(hSelect, bCheck);
        m_struEventCardLinkageCfgV50.byAlarmInSetup[dwIndex] = bCheck;
    }
    UpdateData(FALSE);
    *pResult = 0;
}


void DlgEventCardLinkageCfg::OnNMClickTreeAlarmInClose(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    CPoint pt(0, 0);
    CRect rc(0, 0, 0, 0);
    GetCursorPos(&pt);
    m_treeAlarmInClose.ScreenToClient(&pt);
    m_treeAlarmInClose.GetWindowRect(&rc);
    m_treeAlarmInClose.ScreenToClient(&rc);
    pt.x = pt.x - rc.left;
    pt.y = pt.y - rc.top;

    UINT uFlag = 0;
    HTREEITEM hSelect = m_treeAlarmInClose.HitTest(pt, &uFlag);

    if (NULL == hSelect)
    {
        return;
    }
    m_treeAlarmInClose.SelectItem(hSelect);
    DWORD dwIndex = m_treeAlarmInClose.GetItemData(hSelect);
    BOOL bCheck = m_treeAlarmInClose.GetCheck(hSelect);
    m_treeAlarmInClose.SetCheck(hSelect, !bCheck);
    m_struEventCardLinkageCfgV50.byAlarmInClose[dwIndex] = !bCheck;
    //switch checkbox status on click
    if (uFlag & LVHT_ONITEM || uFlag & LVHT_TOLEFT || uFlag & LVHT_ONITEMLABEL)
    {
        m_treeAlarmInClose.SetCheck(hSelect, !bCheck);
        m_struEventCardLinkageCfgV50.byAlarmInClose[dwIndex] = !bCheck;
    }
    else
    {
        m_treeAlarmInClose.SetCheck(hSelect, bCheck);
        m_struEventCardLinkageCfgV50.byAlarmInClose[dwIndex] = bCheck;
    }
    UpdateData(FALSE);
    *pResult = 0;
}


void DlgEventCardLinkageCfg::InitMainEventType()
{
    // WORD  wMainEventType;  //�¼������ͣ�0-�豸�¼���1-���������¼���2-���¼���3-��������
	char szLan[1024] = {0};
    m_comboMainEventType.ResetContent();
	g_StringLanType(szLan, "�豸�¼�", "Device Event");
    m_comboMainEventType.InsertString(0,szLan);
	g_StringLanType(szLan, "���������¼�", "AlarmIn Event");
    m_comboMainEventType.InsertString(1,szLan);
	g_StringLanType(szLan, "���¼�", "Door Event");
    m_comboMainEventType.InsertString(2,szLan);
	g_StringLanType(szLan, "�������¼�", "CardReader Event");
    m_comboMainEventType.InsertString(3,szLan);
    m_comboMainEventType.SetCurSel(0);
}

void DlgEventCardLinkageCfg::SubEventTypeDev()
{
    // WORD  wSubEventType;  
	char szLan[1024] = {0};

    m_comboSubEventType.ResetContent();
	g_StringLanType(szLan, "�������𱨾�", "Host Tamper Alarm");
    m_comboSubEventType.InsertString(EVENT_ACS_HOST_ANTI_DISMANTLE,szLan);
	g_StringLanType(szLan, "�����¼���90%����", "Device Event");
    m_comboSubEventType.InsertString(EVENT_ACS_OFFLINE_ECENT_NEARLY_FULL,szLan);
	g_StringLanType(szLan, "����Ͽ�", "Network Disconnect");
    m_comboSubEventType.InsertString(EVENT_ACS_NET_BROKEN,szLan);
	g_StringLanType(szLan, "����ָ�", "Network Recovery");
    m_comboSubEventType.InsertString(EVENT_ACS_NET_RESUME,szLan);
	g_StringLanType(szLan, "���ص�ѹ��", "Low Battery Voltage");
    m_comboSubEventType.InsertString(EVENT_ACS_LOW_BATTERY,szLan);
	g_StringLanType(szLan, "���ص�ѹ�ָ�����", "Battery Voltage normal");
    m_comboSubEventType.InsertString(EVENT_ACS_BATTERY_RESUME,szLan);
	g_StringLanType(szLan, "������ϵ�", "AC Power Off");
    m_comboSubEventType.InsertString(EVENT_ACS_AC_OFF,szLan);
	g_StringLanType(szLan, "������ָ�", "AC Power On");
    m_comboSubEventType.InsertString(EVENT_ACS_AC_RESUME,szLan);
	g_StringLanType(szLan, "SD���洢������", "SD Card Full Alarm");
    m_comboSubEventType.InsertString(EVENT_ACS_SD_CARD_FULL,szLan);
	g_StringLanType(szLan, "����ץ���¼�����", "Linkage Capture Event Alarm");
    m_comboSubEventType.InsertString(EVENT_ACS_LINKAGE_CAPTURE_PIC,szLan);
    g_StringLanType(szLan, "����ͼ���ʵ�", "Image Quality Low");
    m_comboSubEventType.InsertString(EVENT_ACS_IMAGE_QUALITY_LOW, szLan);
    g_StringLanType(szLan, "ָ��ͼ���ʵ�", "Finger Print Quality Low");
    m_comboSubEventType.InsertString(EVENT_ACS_FINGER_PRINT_QUALITY_LOW, szLan);
    g_StringLanType(szLan, "��ص�ѹ��", "Battery Electric Low");
    m_comboSubEventType.InsertString(EVENT_ACS_BATTERY_ELECTRIC_LOW, szLan);
    g_StringLanType(szLan, "��ص�ѹ�ָ�����", "Battery Electric Resume");
    m_comboSubEventType.InsertString(EVENT_ACS_BATTERY_ELECTRIC_RESUME, szLan);
    g_StringLanType(szLan, "���������·����", "Fire import short circuit");
    m_comboSubEventType.InsertString(EVENT_ACS_FIRE_IMPORT_SHORT_CIRCUIT, szLan);
    g_StringLanType(szLan, "���������·����", "Fire import broken circuit");
    m_comboSubEventType.InsertString(EVENT_ACS_FIRE_IMPORT_BROKEN_CIRCUIT, szLan);
    g_StringLanType(szLan, "��������ָ�", "Fire import resume");
    m_comboSubEventType.InsertString(EVENT_ACS_FIRE_IMPORT_RESUME, szLan);
    g_StringLanType(szLan, "����RS485��·�ڵ�Ͽ�", "Master RS485 loop node broken");
    m_comboSubEventType.InsertString(EVENT_ACS_MASTER_RS485_LOOPNODE_BROKEN, szLan);
    g_StringLanType(szLan, "����RS485��·�ڵ�ָ�", "Master RS485 loop node resume");
    m_comboSubEventType.InsertString(EVENT_ACS_MASTER_RS485_LOOPNODE_RESUME, szLan);
    g_StringLanType(szLan, "�͵ؿ���������", "Local control offline");
    m_comboSubEventType.InsertString(EVENT_ACS_LOCAL_CONTROL_OFFLINE, szLan);
    g_StringLanType(szLan, "�͵ؿ��������߻ָ�", "Local control resume");
    m_comboSubEventType.InsertString(EVENT_ACS_LOCAL_CONTROL_RESUME, szLan);
    g_StringLanType(szLan, "�͵�����RS485��·�Ͽ�", "Local downside RS485 loopnode broken");
    m_comboSubEventType.InsertString(EVENT_ACS_LOCAL_DOWNSIDE_RS485_LOOPNODE_BROKEN, szLan);
    g_StringLanType(szLan, "�͵�����RS485��·�ָ�", "Local downside RS485 loopnode resume");
    m_comboSubEventType.InsertString(EVENT_ACS_LOCAL_DOWNSIDE_RS485_LOOPNODE_RESUME, szLan);
    g_StringLanType(szLan, "�ֿ�������", "Distract controller online");
    m_comboSubEventType.InsertString(EVENT_ACS_DISTRACT_CONTROLLER_ONLINE, szLan);
    g_StringLanType(szLan, "�ֿ�������", "Distract controller offline");
    m_comboSubEventType.InsertString(EVENT_ACS_DISTRACT_CONTROLLER_OFFLINE, szLan);
    g_StringLanType(szLan, "������ť����", "Fire button trigger");
    m_comboSubEventType.InsertString(EVENT_ACS_FIRE_BUTTON_TRIGGER, szLan);
    g_StringLanType(szLan, "������ť�ָ�", "Fire button resume");
    m_comboSubEventType.InsertString(EVENT_ACS_FIRE_BUTTON_RESUME, szLan);
    g_StringLanType(szLan, "ά����ť����", "Maintenance button trigger");
    m_comboSubEventType.InsertString(EVENT_ACS_MAINTENANCE_BUTTON_TRIGGER, szLan);
    g_StringLanType(szLan, "ά����ť�ָ�", "Maintenance button resume");
    m_comboSubEventType.InsertString(EVENT_ACS_MAINTENANCE_BUTTON_RESUME, szLan);
    g_StringLanType(szLan, "������ť����", "Emergency button trigger");
    m_comboSubEventType.InsertString(EVENT_ACS_EMERGENCY_BUTTON_TRIGGER, szLan);
    g_StringLanType(szLan, "������ť�ָ�", "Emergency button resume");
    m_comboSubEventType.InsertString(EVENT_ACS_EMERGENCY_BUTTON_RESUME, szLan);
    g_StringLanType(szLan, "MAC���", "MAC detect");
    m_comboSubEventType.InsertString(EVENT_ACS_MAC_DETECT, szLan);
    m_comboSubEventType.SetCurSel(EVENT_ACS_HOST_ANTI_DISMANTLE);
}

void DlgEventCardLinkageCfg::SubEventTypeAlarm()
{
    // WORD  wSubEventType; 
	char szLan[1024] = {0};

    m_comboSubEventType.ResetContent();
	g_StringLanType(szLan, "������·����", "Zone Short-Circuit Alarm");
    m_comboSubEventType.InsertString(EVENT_ACS_ALARMIN_SHORT_CIRCUIT,szLan);
	g_StringLanType(szLan, "������·����", "Zone Circuit Alarm");
    m_comboSubEventType.InsertString(EVENT_ACS_ALARMIN_BROKEN_CIRCUIT,szLan);
	g_StringLanType(szLan, "�����쳣����", "Abnormal Zone Alarm");
    m_comboSubEventType.InsertString(EVENT_ACS_ALARMIN_EXCEPTION,szLan);
	g_StringLanType(szLan, "���������ָ�", "Zone Alarm Recover");
    m_comboSubEventType.InsertString(EVENT_ACS_ALARMIN_RESUME,szLan);
	g_StringLanType(szLan, "�¼����뱨��", "Event Input Alarm");
    m_comboSubEventType.InsertString(EVENT_ACS_CASE_SENSOR_ALARM,szLan);
	g_StringLanType(szLan, "�¼�����ָ�", "Event Recover Alarm");
    m_comboSubEventType.InsertString(EVENT_ACS_CASE_SENSOR_RESUME,szLan);
    m_comboSubEventType.SetCurSel(EVENT_ACS_ALARMIN_SHORT_CIRCUIT);
}

void DlgEventCardLinkageCfg::SubEventTypeDoor()
{
    // WORD  wSubEventType;  
    m_comboSubEventType.ResetContent();
    m_comboSubEventType.InsertString(EVENT_ACS_LEADER_CARD_OPEN_BEGIN,"�׿����ſ�ʼ");
    m_comboSubEventType.InsertString(EVENT_ACS_LEADER_CARD_OPEN_END,"�׿����Ž���");
    m_comboSubEventType.InsertString(EVENT_ACS_ALWAYS_OPEN_BEGIN,"����״̬��ʼ");
    m_comboSubEventType.InsertString(EVENT_ACS_ALWAYS_OPEN_END,"����״̬����");
    m_comboSubEventType.InsertString(EVENT_ACS_ALWAYS_CLOSE_BEGIN,"����״̬��ʼ");
    m_comboSubEventType.InsertString(EVENT_ACS_ALWAYS_CLOSE_END,"����״̬����");
    m_comboSubEventType.InsertString(EVENT_ACS_LOCK_OPEN,"������");
    m_comboSubEventType.InsertString(EVENT_ACS_LOCK_CLOSE,"�����ر�");
    m_comboSubEventType.InsertString(EVENT_ACS_DOOR_BUTTON_PRESS,"���Ű�ť����");
    m_comboSubEventType.InsertString(EVENT_ACS_DOOR_BUTTON_RELEASE,"���Ű�ť�ſ�");
    m_comboSubEventType.InsertString(EVENT_ACS_DOOR_OPEN_NORMAL,"�������ţ��Ŵţ�");
    m_comboSubEventType.InsertString(EVENT_ACS_DOOR_CLOSE_NORMAL,"�������ţ��Ŵţ�");
    m_comboSubEventType.InsertString(EVENT_ACS_DOOR_OPEN_ABNORMAL,"���쳣�򿪣��Ŵţ�");
    m_comboSubEventType.InsertString(EVENT_ACS_DOOR_OPEN_TIMEOUT,"�Ŵ򿪳�ʱ���Ŵţ�");
    m_comboSubEventType.InsertString(EVENT_ACS_REMOTE_OPEN_DOOR,"Զ�̿���");
    m_comboSubEventType.InsertString(EVENT_ACS_REMOTE_CLOSE_DOOR,"Զ�̹���");
    m_comboSubEventType.InsertString(EVENT_ACS_REMOTE_ALWAYS_OPEN,"Զ�̳���");
    m_comboSubEventType.InsertString(EVENT_ACS_REMOTE_ALWAYS_CLOSE,"Զ�̳���");
    m_comboSubEventType.InsertString(EVENT_ACS_NOT_BELONG_MULTI_GROUP,"�������ڶ�����֤Ⱥ��");
    m_comboSubEventType.InsertString(EVENT_ACS_INVALID_MULTI_VERIFY_PERIOD,"�����ڶ�����֤ʱ�����");
    m_comboSubEventType.InsertString(EVENT_ACS_MULTI_VERIFY_SUPER_RIGHT_FAIL,"������֤ģʽ����������֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_MULTI_VERIFY_REMOTE_RIGHT_FAIL,"������֤ģʽԶ����֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_MULTI_VERIFY_SUCCESS,"������֤�ɹ�");
    m_comboSubEventType.InsertString(EVENT_ACS_MULTI_VERIFY_NEED_REMOTE_OPEN,"���ض�����֤��ҪԶ�̿���");
    m_comboSubEventType.InsertString(EVENT_ACS_MULTI_VERIFY_SUPERPASSWD_VERIFY_SUCCESS,"������֤����������֤�ɹ��¼�");
    m_comboSubEventType.InsertString(EVENT_ACS_MULTI_VERIFY_REPEAT_VERIFY_FAIL,"������֤�ظ���֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_MULTI_VERIFY_TIMEOUT,"������֤��ʱʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_REMOTE_CAPTURE_PIC,"Զ��ץ��");
    m_comboSubEventType.InsertString(EVENT_ACS_DOORBELL_RINGING,"������");
	m_comboSubEventType.InsertString(EVENT_ACS_SECURITY_MODULE_DESMANTLE_ALARM, "�ſذ�ȫģ����𱨾�");
    m_comboSubEventType.InsertString(EVENT_ACS_CALL_CENTER, "���������¼�");
    m_comboSubEventType.InsertString(EVENT_ACS_FIRSTCARD_AUTHORIZE_BEGIN, "�׿���Ȩ��ʼ");
    m_comboSubEventType.InsertString(EVENT_ACS_FIRSTCARD_AUTHORIZE_END, "�׿���Ȩ����");
    m_comboSubEventType.InsertString(EVENT_ACS_DOORLOCK_INPUT_SHORT_CIRCUIT, "���������·����");
    m_comboSubEventType.InsertString(EVENT_ACS_DOORLOCK_INPUT_BROKEN_CIRCUIT, "���������·����");
    m_comboSubEventType.InsertString(EVENT_ACS_DOORLOCK_INPUT_EXCEPTION, "���������쳣����");
    m_comboSubEventType.InsertString(EVENT_ACS_DOORCONTACT_INPUT_SHORT_CIRCUIT, "�Ŵ������·����");
    m_comboSubEventType.InsertString(EVENT_ACS_DOORCONTACT_INPUT_BROKEN_CIRCUIT, "�Ŵ������·����");
    m_comboSubEventType.InsertString(EVENT_ACS_DOORCONTACT_INPUT_EXCEPTION, "�Ŵ������쳣����");
    m_comboSubEventType.InsertString(EVENT_ACS_OPENBUTTON_INPUT_SHORT_CIRCUIT, "���Ű�ť�����·����");
    m_comboSubEventType.InsertString(EVENT_ACS_OPENBUTTON_INPUT_BROKEN_CIRCUIT, "���Ű�ť�����·����");
    m_comboSubEventType.InsertString(EVENT_ACS_OPENBUTTON_INPUT_EXCEPTION, "���Ű�ť�����쳣����");
    m_comboSubEventType.InsertString(EVENT_ACS_DOORLOCK_OPEN_EXCEPTION, "�����쳣��");
    m_comboSubEventType.InsertString(EVENT_ACS_DOORLOCK_OPEN_TIMEOUT, "�����򿪳�ʱ");
    m_comboSubEventType.InsertString(EVENT_ACS_FIRSTCARD_OPEN_WITHOUT_AUTHORIZE, "�׿�δ��Ȩ����ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_CALL_LADDER_RELAY_BREAK, "���ݼ̵����Ͽ�");
    m_comboSubEventType.InsertString(EVENT_ACS_CALL_LADDER_RELAY_CLOSE, "���ݼ̵����պ�");
    m_comboSubEventType.InsertString(EVENT_ACS_AUTO_KEY_RELAY_BREAK, "�Զ������̵����Ͽ�");
    m_comboSubEventType.InsertString(EVENT_ACS_AUTO_KEY_RELAY_CLOSE, "�Զ������̵����պ�");
    m_comboSubEventType.InsertString(EVENT_ACS_KEY_CONTROL_RELAY_BREAK, "�����ݿؼ̵����Ͽ�");
    m_comboSubEventType.InsertString(EVENT_ACS_KEY_CONTROL_RELAY_CLOSE, "�����ݿؼ̵����պ�");
    m_comboSubEventType.InsertString(EVENT_ACS_REMOTE_VISITOR_CALL_LADDER, "�ÿͺ���");
    m_comboSubEventType.InsertString(EVENT_ACS_REMOTE_HOUSEHOLD_CALL_LADDER, "ס������");
    m_comboSubEventType.InsertString(EVENT_ACS_LEGAL_MESSAGE, "�Ϸ�����");
    m_comboSubEventType.InsertString(EVENT_ACS_ILLEGAL_MESSAGE, "�Ƿ�����");
    m_comboSubEventType.SetCurSel(EVENT_ACS_LEADER_CARD_OPEN_BEGIN);
}

void DlgEventCardLinkageCfg::SubEventTypeCardReader()
{
    // WORD  wSubEventType;  
    m_comboSubEventType.ResetContent();
    m_comboSubEventType.InsertString(EVENT_ACS_STRESS_ALARM,"в�ȱ���");
    m_comboSubEventType.InsertString(EVENT_ACS_CARD_READER_DESMANTLE_ALARM,"���������𱨾�");
    m_comboSubEventType.InsertString(EVENT_ACS_LEGAL_CARD_PASS,"�Ϸ�����֤ͨ��");
    m_comboSubEventType.InsertString(EVENT_ACS_CARD_AND_PSW_PASS,"ˢ����������֤ͨ��");
    m_comboSubEventType.InsertString(EVENT_ACS_CARD_AND_PSW_FAIL,"ˢ����������֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_CARD_AND_PSW_TIMEOUT,"ˢ����������֤��ʱ");
    m_comboSubEventType.InsertString(EVENT_ACS_CARD_MAX_AUTHENTICATE_FAIL, "��������֤ʧ�ܳ���");
    m_comboSubEventType.InsertString(EVENT_ACS_CARD_NO_RIGHT,"��δ����Ȩ��");
    m_comboSubEventType.InsertString(EVENT_ACS_CARD_INVALID_PERIOD,"����ǰʱ����Ч");
    m_comboSubEventType.InsertString(EVENT_ACS_CARD_OUT_OF_DATE,"���Ź���");
    m_comboSubEventType.InsertString(EVENT_ACS_INVALID_CARD,"�޴˿���");
    m_comboSubEventType.InsertString(EVENT_ACS_ANTI_SNEAK_FAIL,"��Ǳ����֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_INTERLOCK_DOOR_NOT_CLOSE,"������δ�ر�");
    m_comboSubEventType.InsertString(EVENT_ACS_FINGERPRINT_COMPARE_PASS,"ָ�Ʊȶ�ͨ��");
    m_comboSubEventType.InsertString(EVENT_ACS_FINGERPRINT_COMPARE_FAIL,"ָ�Ʊȶ�ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_CARD_FINGERPRINT_VERIFY_PASS,"ˢ����ָ����֤ͨ��");
    m_comboSubEventType.InsertString(EVENT_ACS_CARD_FINGERPRINT_VERIFY_FAIL,"ˢ����ָ����֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_CARD_FINGERPRINT_VERIFY_TIMEOUT,"ˢ����ָ����֤��ʱ");
    m_comboSubEventType.InsertString(EVENT_ACS_CARD_FINGERPRINT_PASSWD_VERIFY_PASS,"ˢ����ָ�Ƽ�������֤ͨ��");
    m_comboSubEventType.InsertString(EVENT_ACS_CARD_FINGERPRINT_PASSWD_VERIFY_FAIL,"ˢ����ָ�Ƽ�������֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_CARD_FINGERPRINT_PASSWD_VERIFY_TIMEOUT,"ˢ����ָ�Ƽ�������֤��ʱ");
    m_comboSubEventType.InsertString(EVENT_ACS_FINGERPRINT_PASSWD_VERIFY_PASS,"ָ�Ƽ�������֤ͨ��");
    m_comboSubEventType.InsertString(EVENT_ACS_FINGERPRINT_PASSWD_VERIFY_FAIL,"ָ�Ƽ�������֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_FINGERPRINT_PASSWD_VERIFY_TIMEOUT,"ָ�Ƽ�������֤��ʱ");
    m_comboSubEventType.InsertString(EVENT_ACS_FINGERPRINT_INEXISTENCE,"ָ�Ʋ�����");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_VERIFY_PASS, "������֤ͨ��");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_VERIFY_FAIL, "������֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_AND_FP_VERIFY_PASS, "������ָ����֤ͨ��");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_AND_FP_VERIFY_FAIL, "������ָ����֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_AND_FP_VERIFY_TIMEOUT, "������ָ����֤��ʱ");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_AND_PW_VERIFY_PASS, "������������֤ͨ��");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_AND_PW_VERIFY_FAIL, "������������֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_AND_PW_VERIFY_TIMEOUT, "������������֤��ʱ");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_AND_CARD_VERIFY_PASS, "������ˢ����֤ͨ��");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_AND_CARD_VERIFY_FAIL, "������ˢ����֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_AND_CARD_VERIFY_TIMEOUT, "������ˢ����֤��ʱ");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_AND_PW_AND_FP_VERIFY_PASS, "�����������ָ����֤ͨ��");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_AND_PW_AND_FP_VERIFY_FAIL, "�����������ָ����֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_AND_PW_AND_FP_VERIFY_TIMEOUT, "�����������ָ����֤��ʱ");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_AND_CARD_AND_FP_VERIFY_PASS, "������ˢ����ָ����֤ͨ��");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_AND_CARD_AND_FP_VERIFY_FAIL, "������ˢ����ָ����֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_AND_CARD_AND_FP_VERIFY_TIMEOUT, "������ˢ����ָ����֤��ʱ");
    m_comboSubEventType.InsertString(EVENT_ACS_EMPLOYEENO_AND_FP_VERIFY_PASS, "���ż�ָ����֤ͨ��");
    m_comboSubEventType.InsertString(EVENT_ACS_EMPLOYEENO_AND_FP_VERIFY_FAIL, "���ż�ָ����֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_EMPLOYEENO_AND_FP_VERIFY_TIMEOUT, "���ż�ָ����֤��ʱ");
    m_comboSubEventType.InsertString(EVENT_ACS_EMPLOYEENO_AND_FP_AND_PW_VERIFY_PASS, "���ż�ָ�Ƽ�������֤ͨ��");
    m_comboSubEventType.InsertString(EVENT_ACS_EMPLOYEENO_AND_FP_AND_PW_VERIFY_FAIL, "���ż�ָ�Ƽ�������֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_EMPLOYEENO_AND_FP_AND_PW_VERIFY_TIMEOUT, "���ż�ָ�Ƽ�������֤��ʱ");
    m_comboSubEventType.InsertString(EVENT_ACS_EMPLOYEENO_AND_FACE_VERIFY_PASS, "���ż�������֤ͨ��");
    m_comboSubEventType.InsertString(EVENT_ACS_EMPLOYEENO_AND_FACE_VERIFY_FAIL, "���ż�������֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_EMPLOYEENO_AND_FACE_VERIFY_TIMEOUT, "���ż�������֤��ʱ");
    m_comboSubEventType.InsertString(EVENT_ACS_FACE_RECOGNIZE_FAIL, "����ʶ��ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_EMPLOYEENO_AND_PW_PASS, "���ż�������֤ͨ��");
    m_comboSubEventType.InsertString(EVENT_ACS_EMPLOYEENO_AND_PW_FAIL, "���ż�������֤ʧ��");
    m_comboSubEventType.InsertString(EVENT_ACS_EMPLOYEENO_AND_PW_TIMEOUT, "���ż�������֤��ʱ");
    m_comboSubEventType.InsertString(EVENT_ACS_HUMAN_DETECT_FAIL, "���˼��ʧ��");
    m_comboSubEventType.SetCurSel(EVENT_ACS_STRESS_ALARM);
}

UINT8 DlgEventCardLinkageCfg::charToData(const char ch)
{
    switch (ch)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    case 'a':
    case 'A':
        return 10;
    case 'b':
    case 'B':
        return 11;
    case 'c':
    case 'C':
        return 12;
    case 'd':
    case 'D':
        return 13;
    case 'e':
    case 'E':
        return 14;
    case 'f':
    case 'F':
        return 15;
    }
    return 0;
}

bool DlgEventCardLinkageCfg::StrToMac(const char * szMac, UINT8 * pMac)
{
    const char * pTemp = szMac;
    for (int i = 0; i < 6; ++i)
    {
        pMac[i] = charToData(*pTemp++) * 16;
        pMac[i] += charToData(*pTemp++);
        pTemp++;
    }
    return TRUE;
}