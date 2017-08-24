// DlgCVR.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCVR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCVR dialog




CDlgCVR::CDlgCVR(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCVR::IDD, pParent)
    , m_iPicQuota(0)
{
	//{{AFX_DATA_INIT(CDlgCVR)
	m_strStatus = _T("");
	m_dwMaxPCNum = 0;
	m_bDelData = FALSE;
	m_bEnableDataCallback = FALSE;
	m_strIP = _T("");
	m_strCardSN = _T("");
	m_strClientIP = _T("");
	m_iFCChannel = 0;
	m_dwFCID = 0;
	m_dwLunIDFC = 0;
	m_dwLunIDIscsi = 0;
	m_dwTargetID = 0;
	m_dwLunIDNas = 0;
	m_strPassword = _T("");
	m_bDisableBackup = FALSE;
    m_csRelocationAddr = _T("");
    m_wRelocationPort = 0;
    m_csStreamIDN0 = _T("");
	m_dwN0Chan = 0;
	m_nOnlineUserNum = 0;
	//}}AFX_DATA_INIT
	m_lUserID = -1;
	m_iDevIndex = 0;
	m_bFCGeting = FALSE;
	m_bAddedMachineGeting = FALSE;
	m_hRemoteConfig = -1;
	m_hAddedMachineRemoteConfig = -1;
	m_hThread = NULL;
	m_hAddedMachineThread = NULL;
	m_iFCNum = 0;
	m_iMachineNum = 0;
}

inline BOOL CDlgCVR::ValidIPv6(BYTE *ip)
{
	if (strlen((char *)ip) > 2 && strchr((char *)ip, ':') != NULL)
	{
		return TRUE;
	}
	return FALSE;
}


void CDlgCVR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCVR)
	DDX_Control(pDX, IDC_COMBO_WORK_MODE, m_cmbWorkMode);
	DDX_Control(pDX, IDC_LIST_ADDED_MACHINE, m_lstAddedMachine);
	DDX_Control(pDX, IDC_LIST_FC, m_lstFC);
	DDX_Control(pDX, IDC_COMBO_ACCESS_MODE_ISCSI, m_cmbAccModeIscsi);
	DDX_Control(pDX, IDC_COMBO_ACCESS_MODE_FC, m_cmbFCAccMode);
	DDX_Control(pDX, IDC_COMBO_DEL_TYPE, m_cmbDelType);
	DDX_Control(pDX, IDC_COMBO_ADD_TYPE, m_cmbAddType);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_strStatus);
	DDX_Text(pDX, IDC_EDIT_MAX_WORK_PC_NUM, m_dwMaxPCNum);
	DDX_Check(pDX, IDC_CHECK_DEL_DATA, m_bDelData);
	DDX_Check(pDX, IDC_CHECK_ENABLE_DATA_CALLBACK, m_bEnableDataCallback);
	DDX_Text(pDX, IDC_EDIT_IP_ADDR, m_strIP);
	DDX_Text(pDX, IDC_EDIT_CARD_SN, m_strCardSN);
	DDX_Text(pDX, IDC_EDIT_CLIENT_IP, m_strClientIP);
	DDX_Text(pDX, IDC_EDIT_FC_CHANNEL, m_iFCChannel);
	DDX_Text(pDX, IDC_EDIT_FC_ID, m_dwFCID);
	DDX_Text(pDX, IDC_EDIT_LUN_ID_FC, m_dwLunIDFC);
	DDX_Text(pDX, IDC_EDIT_LUN_ID_ISCSI, m_dwLunIDIscsi);
	DDX_Text(pDX, IDC_EDIT_TARGET_ID, m_dwTargetID);
	DDX_Text(pDX, IDC_EDIT_LUN_ID_NAS, m_dwLunIDNas);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPassword);
	DDX_Check(pDX, IDC_CHECK_BACKUP, m_bDisableBackup);
    DDX_Text(pDX, IDC_EDIT_RELOCATION_ADDR, m_csRelocationAddr);
    DDX_Text(pDX, IDC_EDIT_RELOCATION_PORT, m_wRelocationPort);
    DDX_Text(pDX, IDC_EDIT_STREAMID_N0, m_csStreamIDN0);
	DDX_Text(pDX, IDC_EDIT_CHAN_N0, m_dwN0Chan);
	DDX_Text(pDX, IDC_EDIT_ONLINE_USER_NUM, m_nOnlineUserNum);
	//}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_RAID_TYPE, m_cmbRAIDType);
    DDX_Control(pDX, IDC_COMBO_SPARE_RAID_PROPORTION, m_cmbSpareRAIDProportion);
    DDX_Text(pDX, IDC_EDIT_PIC_QUOTA, m_iPicQuota);
    DDV_MinMaxInt(pDX, m_iPicQuota, 0, 100);
}


BEGIN_MESSAGE_MAP(CDlgCVR, CDialog)
	//{{AFX_MSG_MAP(CDlgCVR)
	ON_BN_CLICKED(IDC_BUTTON_RESTART_SERVICE, OnButtonRestartService)
	ON_BN_CLICKED(IDC_BUTTON_ONE_KEY_CFG, OnButtonOneKeyCfgCVR)
	ON_BN_CLICKED(IDC_BUTTON_OKC_SAN, OnButtonOneKeyCfgSAN)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_GET_MAX_PC_NUM, OnButtonGetMaxPcNum)
	ON_BN_CLICKED(IDC_BUTTON_SET_MAX_PC_NUM, OnButtonSetMaxPcNum)
	ON_BN_CLICKED(IDC_BUTTON_GET_DATA_CALLBACK, OnButtonGetDataCallback)
	ON_BN_CLICKED(IDC_BUTTON_SET_DATA_CALLBACK, OnButtonSetDataCallback)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_ISCSI, OnButtonOpenIscsi)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_ISCSI, OnButtonCloseIscsi)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FC, OnButtonOpenFc)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_FC, OnButtonCloseFc)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_NAS, OnButtonCreateNas)
	ON_BN_CLICKED(IDC_BUTTON_DEL_NAS, OnButtonDelNas)
	ON_BN_CLICKED(IDC_BUTTON_GET_FC, OnButtonGetFc)
	ON_BN_CLICKED(IDC_BUTTON_GET_ADDED_MACHINE, OnButtonGetAddedMachine)
	ON_BN_CLICKED(IDC_BUTTON_GET_WORK_MODE, OnButtonGetWorkMode)
	ON_BN_CLICKED(IDC_BUTTON_SET_WORK_MODE, OnButtonSetWorkMode)
    ON_BN_CLICKED(IDC_BTN_GET_RELOCATE, OnBtnGetRelocate)
	ON_BN_CLICKED(IDC_BTN_GET_ONLINE_USER_NUM, OnBtnGetOnlineUserCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCVR message handlers

BOOL CDlgCVR::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbAddType.SetCurSel(0);
	m_cmbDelType.SetCurSel(0);
	m_cmbFCAccMode.SetCurSel(0);
	m_cmbAccModeIscsi.SetCurSel(0);
	m_cmbWorkMode.SetCurSel(0);

	m_lstFC.SetExtendedStyle(m_lstFC.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_lstAddedMachine.SetExtendedStyle(m_lstFC.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	char szLan[128] = {0};
	char szLanMachine[128] = {0};
	int iIndex = 0;
	g_StringLanType(szLan, "序号", "Serial No.");
	m_lstFC.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 50, -1);

	m_lstAddedMachine.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 50, -1);
	iIndex++;
	
	g_StringLanType(szLan, "逻辑卷ID", "LUN ID");
	m_lstFC.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLanMachine, "N+1类型", "N+1Type");
	m_lstAddedMachine.InsertColumn(iIndex, szLanMachine, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "光纤ID", "FC ID");
	m_lstFC.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLanMachine, "IP", "IP");
	m_lstAddedMachine.InsertColumn(iIndex, szLanMachine, LVCFMT_LEFT, 100, -1);
	iIndex++;
	
	g_StringLanType(szLan, "光纤通道号", "HBA ID");
	m_lstFC.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLanMachine, "工作机连接状态", "WD Link Status");
	m_lstAddedMachine.InsertColumn(iIndex, szLanMachine, LVCFMT_LEFT, 150, -1);
	iIndex++;
	
	g_StringLanType(szLan, "读写模式", "Mode");
	m_lstFC.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 100, -1);

	g_StringLanType(szLanMachine, "工作机工作状态", "WD Work Status");
	m_lstAddedMachine.InsertColumn(iIndex, szLanMachine, LVCFMT_LEFT, 150, -1);
	iIndex++;
	
	g_StringLanType(szLan, "客户光纤卡", "Client card");
	m_lstFC.InsertColumn(iIndex, szLan, LVCFMT_LEFT, 150, -1);

	g_StringLanType(szLanMachine, "工作机备份状态", "WD Backup Status");
	m_lstAddedMachine.InsertColumn(iIndex, szLanMachine, LVCFMT_LEFT, 150, -1);
	iIndex++;

	g_StringLanType(szLanMachine, "工作机录像同步进度", "WD Sync Progress");
	m_lstAddedMachine.InsertColumn(iIndex, szLanMachine, LVCFMT_LEFT, 150, -1);
	iIndex++;

	g_StringLanType(szLanMachine, "工作机同步开始时间", "WD Sync Begin Time");
	m_lstAddedMachine.InsertColumn(iIndex, szLanMachine, LVCFMT_LEFT, 150, -1);
	iIndex++;

	
	g_StringLanType(szLanMachine, "工作机同步结束时间", "WD Sync End Time");
	m_lstAddedMachine.InsertColumn(iIndex, szLanMachine, LVCFMT_LEFT, 150, -1);
	iIndex++;

	g_StringLanType(szLanMachine, "工作机序列号", "WD Serial No");
	m_lstAddedMachine.InsertColumn(iIndex, szLanMachine, LVCFMT_LEFT, 150, -1);
	iIndex++;

	g_StringLanType(szLanMachine, "工作机软件版本", "WD Software Version");
	m_lstAddedMachine.InsertColumn(iIndex, szLanMachine, LVCFMT_LEFT, 150, -1);
	iIndex++;

	g_StringLanType(szLanMachine, "工作机设备类型值", "WD Device Type");
	m_lstAddedMachine.InsertColumn(iIndex, szLanMachine, LVCFMT_LEFT, 150, -1);
	iIndex++;


	g_StringLanType(szLanMachine, "设备类型名", "Device Name");
	m_lstAddedMachine.InsertColumn(iIndex, szLanMachine, LVCFMT_LEFT, 150, -1);
	iIndex++;
	
	g_StringLanType(szLanMachine, "GUID", "GUID");
	m_lstAddedMachine.InsertColumn(iIndex, szLanMachine, LVCFMT_LEFT, 150, -1);
	iIndex++;

	g_StringLanType(szLanMachine, "备机工作状态", "RD Work Status");
	m_lstAddedMachine.InsertColumn(iIndex, szLanMachine, LVCFMT_LEFT, 150, -1);
	iIndex++;

	g_StringLanType(szLanMachine, "备机备份状态", "RD Backup Status");
	m_lstAddedMachine.InsertColumn(iIndex, szLanMachine, LVCFMT_LEFT, 150, -1);
	iIndex++;

	g_StringLanType(szLanMachine, "备机备份端口", "RD Backup Port");
	m_lstAddedMachine.InsertColumn(iIndex, szLanMachine, LVCFMT_LEFT, 150, -1);

	OnButtonGetWorkMode();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCVR::OnButtonRestartService() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};

	BOOL bRet = NET_DVR_RemoteControl(m_lUserID, NET_DVR_RESTART_SERVICE, NULL, 0);
	if (bRet)
	{
		g_StringLanType(szLan,"操作成功","Succeed to control");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl");
		AfxMessageBox(szLan);
	}
	else
	{        
		g_StringLanType(szLan,"操作失败","Fail to control");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl");
		AfxMessageBox(szLan);
	}
}

void CDlgCVR::OnButtonOneKeyCfgCVR() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	char szLan[128] = {0};

    NET_DVR_ONE_KEY_CFG_V50 struOneKeyCfgV50 = { 0 };
    struOneKeyCfgV50.dwSize = sizeof(NET_DVR_ONE_KEY_CFG_V50);
    struOneKeyCfgV50.byRaidType = m_cmbRAIDType.GetCurSel();
    struOneKeyCfgV50.bySpareRaidProportion = m_cmbSpareRAIDProportion.GetCurSel();
    struOneKeyCfgV50.byPicQuota = m_iPicQuota;

    m_lOneKeyCfgCVRHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_ONE_KEY_CONFIG_V50, &struOneKeyCfgV50, sizeof(struOneKeyCfgV50), NULL, NULL);
	if (m_lOneKeyCfgCVRHandle == -1)
	{
		g_StringLanType(szLan,"启动失败","Fail to start");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_StringLanType(szLan,"启动成功","Succeed to start");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StartRemoteConfig");
	}
	m_lOneKeyCfgTimer = SetTimer(ONE_KEY_CONFIG_CVR_TIMER, 500, NULL);
	GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(FALSE);
    UpdateData(FALSE);
}



void CDlgCVR::OnButtonOneKeyCfgSAN() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	
	m_lOneKeyCfgSANHandle = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_ONE_KEY_CONFIG_SAN, NULL, 0, NULL, NULL);
	if (m_lOneKeyCfgSANHandle == -1)
	{
		g_StringLanType(szLan,"启动失败","Fail to start");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_StringLanType(szLan,"启动成功","Succeed to start");
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StartRemoteConfig");
	}
	m_lOneKeyCfgTimer = SetTimer(ONE_KEY_CONFIG_SAN_TIMER, 500, NULL);
	GetDlgItem(IDC_BUTTON_OKC_SAN)->EnableWindow(FALSE);
}

#if (_MSC_VER >= 1500)	//vs2008
void CDlgCVR::OnTimer(UINT_PTR nIDEvent)
#else
void CDlgCVR::OnTimer(UINT nIDEvent)
#endif
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == ONE_KEY_CONFIG_CVR_TIMER)
    {
        DWORD dwState = 0;
        char szLan[128] = {0};
        NET_DVR_GetRemoteConfigState(m_lOneKeyCfgCVRHandle, &dwState);
        if (dwState == NET_SDK_OKC_STATUS_SUCCESS)
        {
			g_StringLanType(szLan, "配置成功", "Config success");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
			KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
        else if (dwState == NET_SDK_OKC_STATUS_START_CONFIG)
        {
			g_StringLanType(szLan, "开始配置", "Start config");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
		else if (dwState == NET_SDK_OKC_CHECK_HD)
        {
			g_StringLanType(szLan, "检测磁盘", "Check disk");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
		else if (dwState == NET_SDK_OKC_INIT_HD)
        {
			g_StringLanType(szLan, "初始化磁盘", "Init disk");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
		else if (dwState == NET_SDK_OKC_CREATE_RAID_OR_SINGLE_DISK)
        {
			g_StringLanType(szLan, "创建阵列或者单盘模式", "Create raid or single disk");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
		else if (dwState == NET_SDK_OKC_INIT_CVR_SERVICE)
        {
			g_StringLanType(szLan, "初始化CVR服务", "Init CVR Service");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
		else if (dwState == NET_SDK_OKC_CREATE_RECORD_VOLUME)
        {
			g_StringLanType(szLan, "创建录像卷", "Create Record volume");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
        else if (dwState == NET_SDK_OKC_STATUS_FAILED)
        {
			g_StringLanType(szLan, "配置失败", "Config failed");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_LOAD_CONF_FAILED)
        {
			g_StringLanType(szLan, "加载配置文件失败", "LOAD_CONF_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_NOT_SUPPORT_RAID_LEVLE)
        {
			g_StringLanType(szLan, "不支持此种类型的raid", "NOT_SUPPORT_RAID_LEVLE");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_CONFIGURATION_CONFLICT)
        {
			g_StringLanType(szLan, "系统已经存在riad或存储池", "CONFIGURATION_CONFLICT");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_GET_DISK_INFO_FAILED)
        {
			g_StringLanType(szLan, "获取磁盘信息失败", "GET_DISK_INFO_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_CHECK_DISK_FAILED)
        {
			g_StringLanType(szLan, "检测磁盘失败", "CHECK_DISK_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_INIT_DISK_FAILED)
        {
			g_StringLanType(szLan, "初始化磁盘失败", "INIT_DISK_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_DISK_CAPACITY_SMALL)
        {
			g_StringLanType(szLan, "磁盘总容量不足", "DISK_CAPACITY_SMALL");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_BOTH_SV_NS)
        {
			g_StringLanType(szLan, "同时存在SV盘和NS盘", "BOTH_SV_NS");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_CREATE_RAID_FAILED)
        {
			g_StringLanType(szLan, "创建raid失败", "CREATE_RAID_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_GET_RAID_FAILED)
        {
			g_StringLanType(szLan, "获取raid失败", "GET_RAID_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_CREATE_SPARE_FAILED)
        {
			g_StringLanType(szLan, "创建热备盘失败", "CREATE_SPARE_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_CREATE_STORAGE_POOL_FAILED)
        {
			g_StringLanType(szLan, "创建存储池失败", "CREATE_STORAGE_POOL_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_GET_POOL_INFO_FAILED)
        {
			g_StringLanType(szLan, "获取存储池信息失败", "GET_POOL_INFO_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_CREATE_LUN_FAILED)
        {
			g_StringLanType(szLan, "创建lun卷失败", "Config failed");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_GET_LUN_INFO_FAILED)
        {
			g_StringLanType(szLan, "获取lun信息失败", "GET_LUN_INFO_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_CREATE_BACKUP_FAILED)
        {
			g_StringLanType(szLan, "创建预留卷失败", "CREATE_BACKUP_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_GET_BACKUP_FAILED)
        {
			g_StringLanType(szLan, "获取预留卷失败", "GET_BACKUP_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_CREATE_PRIVATE_LUN_FAILED)
        {
			g_StringLanType(szLan, "创建私有卷失败", "CREATE_PRIVATE_LUN_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_CREATE_RV_FAILED)
        {
			g_StringLanType(szLan, "创建录像卷失败", "CREATE_RV_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_CREATE_ARCH_RV_FAILED)
        {
			g_StringLanType(szLan, "创建存档卷失败", "CREATE_ARCH_RV_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_START_CVR_SERVICE_FAILED)
        {
			g_StringLanType(szLan, "开启CVR服务失败", "START_CVR_SERVICE_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
        else if (dwState == NET_SDK_OKC_ERR_SAPRE_NUM_EXCEED)
        {
            g_StringLanType(szLan, "热备盘个数过多", "SAPRE_NUM_EXCEED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
            m_lOneKeyCfgCVRHandle = -1;
            GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
        else if (dwState == NET_SDK_OKC_ERR_CREATE_PIC_VOLUME_FAILED)
        {
            g_StringLanType(szLan, "创建图片卷失败", "CREATE_PIC_VOLUME_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
            NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
            m_lOneKeyCfgCVRHandle = -1;
            GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
        else
        {
            g_StringLanType(szLan, "配置失败", "Config failed");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
    }
	else if (nIDEvent == ONE_KEY_CONFIG_SAN_TIMER)
    {
        DWORD dwState = 0;
        char szLan[128] = {0};
        NET_DVR_GetRemoteConfigState(m_lOneKeyCfgSANHandle, &dwState);
        if (dwState == NET_SDK_OKC_STATUS_SUCCESS)
        {
			g_StringLanType(szLan, "配置成功", "Config success");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgSANHandle);
			m_lOneKeyCfgSANHandle = -1;
			GetDlgItem(IDC_BUTTON_OKC_SAN)->EnableWindow(TRUE);
			KillTimer(ONE_KEY_CONFIG_SAN_TIMER);
        }
		else if (dwState == NET_SDK_OKC_CHECK_HD)
        {
			g_StringLanType(szLan, "检测磁盘", "Check disk");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
		else if (dwState == NET_SDK_OKC_INIT_HD)
        {
			g_StringLanType(szLan, "初始化磁盘", "Init disk");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
		else if (dwState == NET_SDK_OKC_CREATING_ARRAY)
        {
			g_StringLanType(szLan, "创建阵列阶段", "Create raid");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
		else if (dwState == NET_SDK_OKC_CREATING_STORAGE_POOL)
        {
			g_StringLanType(szLan, "创建存储池阶段", "Create storage pool");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
		else if (dwState == NET_SDK_OKC_CREATING_LUN_VOL)
        {
			g_StringLanType(szLan, "创建逻辑卷阶段", "Create LUN volume");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
		else if (dwState == NET_SDK_OKC_CREATING_ISCSI)
        {
			g_StringLanType(szLan, "创建ISCSI阶段", "Create ISCSI");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
        }
        else if (dwState == NET_SDK_OKC_STATUS_FAILED)
        {
			g_StringLanType(szLan, "配置失败", "Config failed");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgSANHandle);
			m_lOneKeyCfgSANHandle = -1;
			GetDlgItem(IDC_BUTTON_OKC_SAN)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_SAN_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_CHECK_DISK_FAILED)
        {
			g_StringLanType(szLan, "检测磁盘失败", "CHECK_DISK_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgSANHandle);
			m_lOneKeyCfgSANHandle = -1;
			GetDlgItem(IDC_BUTTON_OKC_SAN)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_SAN_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_INIT_DISK_FAILED)
        {
			g_StringLanType(szLan, "初始化磁盘失败", "INIT_DISK_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgSANHandle);
			m_lOneKeyCfgSANHandle = -1;
			GetDlgItem(IDC_BUTTON_OKC_SAN)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_SAN_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_CREATE_RAID_FAILED)
        {
			g_StringLanType(szLan, "创建raid失败", "CREATE_RAID_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgSANHandle);
			m_lOneKeyCfgSANHandle = -1;
			GetDlgItem(IDC_BUTTON_OKC_SAN)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_SAN_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_CREATE_STORAGE_POOL_FAILED)
        {
			g_StringLanType(szLan, "创建存储池失败", "CREATE_STORAGE_POOL_FAILED");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgSANHandle);
			m_lOneKeyCfgSANHandle = -1;
			GetDlgItem(IDC_BUTTON_OKC_SAN)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_SAN_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_CREATE_LUN_FAILED)
        {
			g_StringLanType(szLan, "创建lun卷失败", "Config failed");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgSANHandle);
			m_lOneKeyCfgSANHandle = -1;
			GetDlgItem(IDC_BUTTON_OKC_SAN)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_SAN_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_HOT_SPARE_CONFICT)
        {
			g_StringLanType(szLan, "已存在热备盘", "Hot spare conflict");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgSANHandle);
			m_lOneKeyCfgSANHandle = -1;
			GetDlgItem(IDC_BUTTON_OKC_SAN)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_SAN_TIMER);
        }
		else if (dwState == NET_SDK_OKC_ERR_STORAGE_POOL_CONFICT)
        {
			g_StringLanType(szLan, "已存在存储池", "Storage pool conflict");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgSANHandle);
			m_lOneKeyCfgSANHandle = -1;
			GetDlgItem(IDC_BUTTON_OKC_SAN)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_SAN_TIMER);
        }
        else
        {
            g_StringLanType(szLan, "配置失败", "Config failed");
            GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(szLan);
			NET_DVR_StopRemoteConfig(m_lOneKeyCfgCVRHandle);
			m_lOneKeyCfgCVRHandle = -1;
			GetDlgItem(IDC_BUTTON_ONE_KEY_CFG)->EnableWindow(TRUE);
            KillTimer(ONE_KEY_CONFIG_CVR_TIMER);
        }
    }
	

	//UpdateData(FALSE);

	

	CDialog::OnTimer(nIDEvent);
}


void CDlgCVR::OnButtonGetMaxPcNum() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	DWORD dwReturned = 0;

	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_MAX_MACHINE_NUM_CFG, 0, &m_struMachineMaxNum, sizeof(NET_DVR_MACHINE_MAX_NUM_CFG), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MAX_MACHINE_NUM_CFG");
		g_StringLanType(szLan, "获取失败", "Get failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MAX_MACHINE_NUM_CFG");
	}

	m_dwMaxPCNum = m_struMachineMaxNum.dwMaxNum;

	UpdateData(FALSE);
	
}

void CDlgCVR::OnButtonSetMaxPcNum() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};

	m_struMachineMaxNum.dwSize = sizeof(NET_DVR_MACHINE_MAX_NUM_CFG);
	m_struMachineMaxNum.dwMaxNum = m_dwMaxPCNum;
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_MAX_MACHINE_NUM_CFG, 0, &m_struMachineMaxNum, sizeof(NET_DVR_MACHINE_MAX_NUM_CFG)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MAX_MACHINE_NUM_CFG");
		g_StringLanType(szLan, "设置失败", "Set failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MAX_MACHINE_NUM_CFG");
	}
	
}

void CDlgCVR::OnButtonGetDataCallback() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	DWORD dwReturned = 0;
	
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_DATA_CALLBACK_CFG, 0, &m_struDataCallback, sizeof(NET_DVR_DATA_CALLBACK_CFG), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_DATA_CALLBACK_CFG");
		g_StringLanType(szLan, "获取失败", "Get failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_DATA_CALLBACK_CFG");
	}
	
	m_bEnableDataCallback = m_struDataCallback.byEnable;
	m_bDelData = m_struDataCallback.byDelData;
	
	UpdateData(FALSE);
}

void CDlgCVR::OnButtonSetDataCallback() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	
	m_struDataCallback.dwSize = sizeof(NET_DVR_DATA_CALLBACK_CFG);
	m_struDataCallback.byEnable = m_bEnableDataCallback;
	m_struDataCallback.byDelData = m_bDelData;
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_DATA_CALLBACK_CFG, 0, &m_struDataCallback, sizeof(NET_DVR_DATA_CALLBACK_CFG)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_DATA_CALLBACK_CFG");
		g_StringLanType(szLan, "设置失败", "Set failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_DATA_CALLBACK_CFG");
	}
}

void CDlgCVR::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_N_PLUS_ONE_DEVICE_PARAM struSpareMachine;
	memset(&struSpareMachine, 0, sizeof(NET_DVR_N_PLUS_ONE_DEVICE_PARAM));
	struSpareMachine.dwSize = sizeof(NET_DVR_N_PLUS_ONE_DEVICE_PARAM);
	struSpareMachine.byType = 0;
	struSpareMachine.unionParam.struAddParam.byAddType = m_cmbAddType.GetCurSel();
	struSpareMachine.unionParam.struAddParam.byDisableBackup = m_bDisableBackup;
	strcpy(struSpareMachine.unionParam.struAddParam.szPassword, m_strPassword.GetBuffer(0));
	if (ValidIPv6((unsigned char*)m_strIP.GetBuffer(0)))
	{
		strncpy((char*)struSpareMachine.unionParam.struAddParam.struIP.byIPv6, m_strIP, 127);
	}
	else
	{
		strncpy(struSpareMachine.unionParam.struAddParam.struIP.sIpV4, m_strIP, 15);
	}
	
	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_ADD_DEVICE, &struSpareMachine, sizeof(NET_DVR_N_PLUS_ONE_DEVICE_PARAM)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_ADD_DEVICE ");
		g_StringLanType(szLan, "操作失败", "control failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_ADD_DEVICE");
	}
}

void CDlgCVR::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_N_PLUS_ONE_DEVICE_PARAM struSpareMachine;
	memset(&struSpareMachine, 0, sizeof(NET_DVR_N_PLUS_ONE_DEVICE_PARAM));
	struSpareMachine.dwSize = sizeof(NET_DVR_N_PLUS_ONE_DEVICE_PARAM);
	struSpareMachine.byType = 1;
	struSpareMachine.unionParam.struDelParam.byDelType = m_cmbDelType.GetCurSel();

	if (ValidIPv6((unsigned char*)m_strIP.GetBuffer(0)))
	{
		strncpy((char*)struSpareMachine.unionParam.struDelParam.struIP.byIPv6, m_strIP, 127);
	}
	else
	{
		strncpy(struSpareMachine.unionParam.struDelParam.struIP.sIpV4, m_strIP, 15);
	}

	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_DEL_DEVICE, &struSpareMachine, sizeof(NET_DVR_N_PLUS_ONE_DEVICE_PARAM)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_N_PLUS_ONE_DEVICE_PARAM ");
		g_StringLanType(szLan, "操作失败", "control failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_N_PLUS_ONE_DEVICE_PARAM");
	}
}

void CDlgCVR::OnButtonOpenIscsi() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_ISCSI_PARAM struIscsiParam;
	memset(&struIscsiParam, 0, sizeof(NET_DVR_ISCSI_PARAM));
	struIscsiParam.dwSize = sizeof(NET_DVR_ISCSI_PARAM);
	struIscsiParam.dwLunID = m_dwLunIDIscsi;
	struIscsiParam.dwTargetID = m_dwTargetID;
	struIscsiParam.dwAccessMode = m_cmbAccModeIscsi.GetCurSel();
	
	if (ValidIPv6((unsigned char*)m_strClientIP.GetBuffer(0)))
	{
		strncpy((char*)struIscsiParam.struClientIP.byIPv6, m_strClientIP, 127);
	}
	else
	{
		strncpy(struIscsiParam.struClientIP.sIpV4, m_strClientIP, 15);
	}
	
	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_OPEN_ISCSI, &struIscsiParam, sizeof(NET_DVR_ISCSI_PARAM)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_OPEN_ISCSI ");
		g_StringLanType(szLan, "操作失败", "control failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_OPEN_ISCSI");
	}
}

void CDlgCVR::OnButtonCloseIscsi() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_ISCSI_PARAM struIscsiParam;
	memset(&struIscsiParam, 0, sizeof(NET_DVR_ISCSI_PARAM));
	struIscsiParam.dwSize = sizeof(NET_DVR_ISCSI_PARAM);
	struIscsiParam.dwLunID = m_dwLunIDIscsi;
	struIscsiParam.dwTargetID = m_dwTargetID;
	struIscsiParam.dwAccessMode = m_cmbAccModeIscsi.GetCurSel();
	
	if (ValidIPv6((unsigned char*)m_strClientIP.GetBuffer(0)))
	{
		strncpy((char*)struIscsiParam.struClientIP.byIPv6, m_strClientIP, 127);
	}
	else
	{
		strncpy(struIscsiParam.struClientIP.sIpV4, m_strClientIP, 15);
	}
	
	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_CLOSE_ISCSI, &struIscsiParam, sizeof(NET_DVR_ISCSI_PARAM)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_CLOSE_ISCSI ");
		g_StringLanType(szLan, "操作失败", "control failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_CLOSE_ISCSI");
	}
}

void CDlgCVR::OnButtonOpenFc() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_FC_PARAM struFCParam;
	memset(&struFCParam, 0, sizeof(NET_DVR_FC_PARAM));
	struFCParam.dwSize = sizeof(NET_DVR_FC_PARAM);
	struFCParam.dwStoreLunID = m_dwLunIDFC;
	struFCParam.dwLogicLunID = m_dwFCID;
	struFCParam.dwHbaID = (DWORD)m_iFCChannel;
	struFCParam.dwAccessMode = m_cmbFCAccMode.GetCurSel();
	memcpy(struFCParam.szClientWWWPN, m_strCardSN, 32);
	
	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_OPEN_FC, &struFCParam, sizeof(NET_DVR_FC_PARAM)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_OPEN_FC ");
		g_StringLanType(szLan, "操作失败", "control failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_OPEN_FC");
	}
}

void CDlgCVR::OnButtonCloseFc() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_FC_PARAM struFCParam;
	memset(&struFCParam, 0, sizeof(NET_DVR_FC_PARAM));
	struFCParam.dwSize = sizeof(NET_DVR_FC_PARAM);
	struFCParam.dwStoreLunID = m_dwLunIDFC;
	struFCParam.dwLogicLunID = m_dwFCID;
	struFCParam.dwAccessMode = m_cmbFCAccMode.GetCurSel();
	memcpy(struFCParam.szClientWWWPN, m_strCardSN, 32);
	
	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_CLOSE_FC, &struFCParam, sizeof(NET_DVR_FC_PARAM)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_CLOSE_FC ");
		g_StringLanType(szLan, "操作失败", "control failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_CLOSE_FC");
	}
}

void CDlgCVR::OnButtonCreateNas() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_NAS_PARAM struNASParam;
	memset(&struNASParam, 0, sizeof(NET_DVR_NAS_PARAM));
	struNASParam.dwSize = sizeof(NET_DVR_NAS_PARAM);
	struNASParam.dwLunID = m_dwLunIDNas;

	
	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_CREATE_NAS, &struNASParam, sizeof(NET_DVR_NAS_PARAM)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_CREATE_NAS ");
		g_StringLanType(szLan, "操作失败", "control failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_CREATE_NAS");
	}
}

void CDlgCVR::OnButtonDelNas() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_NAS_PARAM struNASParam;
	memset(&struNASParam, 0, sizeof(NET_DVR_NAS_PARAM));
	struNASParam.dwSize = sizeof(NET_DVR_NAS_PARAM);
	struNASParam.dwLunID = m_dwLunIDNas;
	
	
	if (!NET_DVR_RemoteControl(m_lUserID, NET_DVR_DELETE_NAS, &struNASParam, sizeof(NET_DVR_NAS_PARAM)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_DELETE_NAS ");
		g_StringLanType(szLan, "操作失败", "control failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_DELETE_NAS");
	}
}

/*********************************************************
Function:	GetFCThread
Desc:		get fc thread
Input:		pParam,pointer to parameters
Output:	
Return:	
**********************************************************/
UINT GetFCThread(LPVOID pParam)
{
	LONG lRet = -1;
	NET_DVR_FC_PARAM struFCInfo = {0};
	CString csTmp;
	char szLan[128] = {0};

	CDlgCVR *pThis = (CDlgCVR*)pParam;

	pThis->m_iFCNum = 0;

	while (1)
	{
		lRet = NET_DVR_GetNextRemoteConfig(pThis->m_hRemoteConfig, &struFCInfo, sizeof(NET_DVR_FC_PARAM));
		if (lRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{	
			int iIndex = 1;
			csTmp.Format("%d", pThis->m_iFCNum+1);
			pThis->m_lstFC.InsertItem(pThis->m_iFCNum, csTmp);
			csTmp.Format("%d", struFCInfo.dwStoreLunID);
			pThis->m_lstFC.SetItemText(pThis->m_iFCNum, iIndex, csTmp);
			iIndex++;
			
			csTmp.Format("%d", struFCInfo.dwLogicLunID); 
			pThis->m_lstFC.SetItemText(pThis->m_iFCNum, iIndex, csTmp);
			iIndex++;

			csTmp.Format("%d", struFCInfo.dwHbaID);
			pThis->m_lstFC.SetItemText(pThis->m_iFCNum, iIndex, csTmp);
			iIndex++;

			csTmp.Format("%d", struFCInfo.dwAccessMode);
			pThis->m_lstFC.SetItemText(pThis->m_iFCNum, iIndex, csTmp);
			iIndex++;

			pThis->m_lstFC.SetItemText(pThis->m_iFCNum, iIndex, struFCInfo.szClientWWWPN);
			pThis->m_iFCNum++;
		}
		else if(lRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
		{
			
			Sleep(5);
			continue;
		}
		else if (lRet == NET_SDK_GET_NEXT_STATUS_FINISH) 
		{
			g_StringLanType(szLan, "获取光纤信息", "Get FC info");
			pThis->GetDlgItem(IDC_BUTTON_GET_FC)->SetWindowText(szLan);
			pThis->m_bFCGeting = FALSE;
			pThis->m_iFCNum = 0;
			break;
		}
		else
		{
			g_StringLanType(szLan, "获取光纤信息", "Get FC info");
			pThis->GetDlgItem(IDC_BUTTON_GET_FC)->SetWindowText(szLan);
			pThis->m_bFCGeting = FALSE;
			g_StringLanType(szLan, "由于服务器忙,或网络故障,获取光纤信息异常终止", "Since the server is busy, or network failure, abnormal termination of access to the fc info");
			AfxMessageBox(szLan);
			pThis->m_iFCNum = 0;
			break;
		}
	}

	CloseHandle(pThis->m_hThread);
	pThis->m_hThread = NULL;
	NET_DVR_StopRemoteConfig(pThis->m_hRemoteConfig);
	pThis->m_hRemoteConfig = -1;
	pThis->m_bFCGeting = FALSE;
	return 0;
}

void CDlgCVR::OnButtonGetFc() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (!m_bFCGeting)
	{
		
		m_hRemoteConfig = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_FC, NULL, 0, NULL, NULL);
		if (m_hRemoteConfig < 0)
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig NET_DVR_GET_FC");
			g_StringLanType(szLan, "获取光纤列表失败!", "Fail to get fc list");
			AfxMessageBox(szLan);
			return;
		}
		m_lstFC.DeleteAllItems();
		DWORD dwThreadId;
		if (m_hThread == NULL)
		{
			m_hThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetFCThread),this,0,&dwThreadId);		
		}

		if (m_hThread == NULL)
		{
			g_StringLanType(szLan, "打开线程失败!", "Fail to open thread!");
			AfxMessageBox(szLan);
			return;
		}

		g_StringLanType(szLan, "停止获取", "Stop Getting");
		GetDlgItem(IDC_BUTTON_GET_FC)->SetWindowText(szLan);
		m_bFCGeting = TRUE;
	}
	else
	{
		if (m_hThread)
		{
			TerminateThread(m_hThread, 0);
		}
		CloseHandle(m_hThread);
		m_hThread = NULL;
		NET_DVR_StopRemoteConfig(m_hRemoteConfig);
		g_StringLanType(szLan, "获取光纤信息", "Get FC info");
		GetDlgItem(IDC_BUTTON_GET_FC)->SetWindowText(szLan);
		m_bFCGeting = FALSE;
	}
}

/*********************************************************
Function:	GetAddMachineThread
Desc:		get added machine thread
Input:		pParam,pointer to parameters
Output:	
Return:	
**********************************************************/
UINT GetAddMachineThread(LPVOID pParam)
{
	LONG lRet = -1;
	NET_DVR_N_PLUS_ONE_DEVICE_INFO struAddedMachine = {0};
	CString csTmp;
	char szLan[128] = {0};

	CDlgCVR *pThis = (CDlgCVR*)pParam;

	pThis->m_iFCNum = 0;

	while (1)
	{
		lRet = NET_DVR_GetNextRemoteConfig(pThis->m_hAddedMachineRemoteConfig, &struAddedMachine, sizeof(NET_DVR_N_PLUS_ONE_DEVICE_INFO));
		if (lRet == NET_SDK_GET_NEXT_STATUS_SUCCESS)
		{	
			int iIndex = 1;
			csTmp.Format("%d", pThis->m_iMachineNum+1);
			pThis->m_lstAddedMachine.InsertItem(pThis->m_iMachineNum, csTmp);
			
			csTmp.Format("%d", struAddedMachine.byType);
			pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, iIndex, csTmp);


			if (0 == struAddedMachine.byType)
			{
				csTmp.Format("%s", struAddedMachine.unionDevInfo.struWorkingDeviceInfo.struIP.sIpV4);
				pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, 2, csTmp);

				csTmp.Format("%d", struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byLinkStatus); 
				pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, 3, csTmp);

				
				csTmp.Format("%d", struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkStatus); 
				pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, 4, csTmp);

				
				csTmp.Format("%d", struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byBacupStatus); 
				pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, 5, csTmp);

				
				csTmp.Format("%d", struAddedMachine.unionDevInfo.struWorkingDeviceInfo.bySyncProgress); 
				pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, 6, csTmp);

				
				csTmp.Format("%d-%d-%d %d:%d:%d", struAddedMachine.unionDevInfo.struWorkingDeviceInfo.struSyncBeginTime.wYear,
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.struSyncBeginTime.byMonth, 
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.struSyncBeginTime.byDay,
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.struSyncBeginTime.byHour,
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.struSyncBeginTime.byMinute,
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.struSyncBeginTime.bySecond); 
				pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, 7, csTmp);

				
				csTmp.Format("%d-%d-%d %d:%d:%d", struAddedMachine.unionDevInfo.struWorkingDeviceInfo.struSyncEndTime.wYear,
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.struSyncEndTime.byMonth, 
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.struSyncEndTime.byDay,
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.struSyncEndTime.byHour,
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.struSyncEndTime.byMinute,
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.struSyncEndTime.bySecond); 
				pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, 8, csTmp);

				
				csTmp.Format("%s", struAddedMachine.unionDevInfo.struWorkingDeviceInfo.szSerialNumber);
				pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, 9, csTmp);

				
			//	csTmp.Format("%d", struAddedMachine.unionDevInfo.struWorkingDeviceInfo.dwSoftwareVersion); 
				

				if (((struAddedMachine.unionDevInfo.struWorkingDeviceInfo.dwSoftwareVersion>>24)&0xFF) > 0)
				{
					csTmp.Format("V%d.%d.%d",\
						(struAddedMachine.unionDevInfo.struWorkingDeviceInfo.dwSoftwareVersion>>24)&0xFF, 
						(struAddedMachine.unionDevInfo.struWorkingDeviceInfo.dwSoftwareVersion>>16)&0xFF, 
						struAddedMachine.unionDevInfo.struWorkingDeviceInfo.dwSoftwareVersion&0xFFFF); 
				}
				else
				{
					csTmp.Format("V%d.%d",\
						(struAddedMachine.unionDevInfo.struWorkingDeviceInfo.dwSoftwareVersion>>16)&0xFFFF, 
						struAddedMachine.unionDevInfo.struWorkingDeviceInfo.dwSoftwareVersion&0xFFFF);
				}	
				pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, 10, csTmp);

				csTmp.Format("%d", struAddedMachine.unionDevInfo.struWorkingDeviceInfo.wDevType); 
				pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, 11, csTmp);

				csTmp.Format("%s", struAddedMachine.unionDevInfo.struWorkingDeviceInfo.szDevTypeName); 
				pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, 12, csTmp);


				csTmp.Format("%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d", 
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkingDeviceGUID[0],
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkingDeviceGUID[1],
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkingDeviceGUID[2],
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkingDeviceGUID[3],
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkingDeviceGUID[4],
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkingDeviceGUID[5],
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkingDeviceGUID[6],
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkingDeviceGUID[7],
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkingDeviceGUID[8],
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkingDeviceGUID[9],
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkingDeviceGUID[10],
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkingDeviceGUID[11],
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkingDeviceGUID[12],
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkingDeviceGUID[13],
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkingDeviceGUID[14],
					struAddedMachine.unionDevInfo.struWorkingDeviceInfo.byWorkingDeviceGUID[15]); 
				pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, 13, csTmp);
			}
			else
			{

				csTmp.Format("%s", struAddedMachine.unionDevInfo.struRedundantDeviceInfo.struIP.sIpV4);
				pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, 2, csTmp);

				csTmp.Format("%d", struAddedMachine.unionDevInfo.struRedundantDeviceInfo.byWorkStatus); 
				pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, 14, csTmp);

				csTmp.Format("%d", struAddedMachine.unionDevInfo.struRedundantDeviceInfo.byBackupStatus); 
				pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, 15, csTmp);

				csTmp.Format("%d", struAddedMachine.unionDevInfo.struRedundantDeviceInfo.wBackupPort); 
				pThis->m_lstAddedMachine.SetItemText(pThis->m_iMachineNum, 16, csTmp);
			}

			pThis->m_iMachineNum++;
		}
		else if(lRet == NET_SDK_GET_NETX_STATUS_NEED_WAIT)
		{
			
			Sleep(5);
			continue;
		}
		else if (lRet == NET_SDK_GET_NEXT_STATUS_FINISH) 
		{
			g_StringLanType(szLan, "获取已添加机器", "Get Added machine");
			pThis->GetDlgItem(IDC_BUTTON_GET_ADDED_MACHINE)->SetWindowText(szLan);
			pThis->m_bAddedMachineGeting = FALSE;
			pThis->m_iMachineNum = 0;
			break;
		}
		else
		{
			g_StringLanType(szLan, "获取已添加机器", "Get Added machine");
			pThis->GetDlgItem(IDC_BUTTON_GET_ADDED_MACHINE)->SetWindowText(szLan);
			pThis->m_bAddedMachineGeting = FALSE;
			g_StringLanType(szLan, "由于服务器忙,或网络故障,获取设备信息异常终止", "Since the server is busy, or network failure, abnormal termination of access to the machine info");
			AfxMessageBox(szLan);
			pThis->m_iMachineNum = 0;
			break;
		}
	}

	CloseHandle(pThis->m_hAddedMachineThread);
	pThis->m_hAddedMachineThread = NULL;
	NET_DVR_StopRemoteConfig(pThis->m_hAddedMachineRemoteConfig);
	pThis->m_hAddedMachineRemoteConfig = -1;
	pThis->m_hAddedMachineThread = FALSE;
	return 0;
}

void CDlgCVR::OnButtonGetAddedMachine() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (!m_bAddedMachineGeting)
	{
		
		m_hAddedMachineRemoteConfig = NET_DVR_StartRemoteConfig(m_lUserID, NET_DVR_GET_N_PLUS_ONE_DEVICE_INFO, NULL, 0, NULL, NULL);
		if (m_hAddedMachineRemoteConfig < 0)
		{
			g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StartRemoteConfig NET_DVR_GET_N_PLUS_ONE_DEVICE_INFO");
			g_StringLanType(szLan, "获取N+1设备列表失败!", "Fail to get add machine list");
			AfxMessageBox(szLan);
			return;
		}
		m_lstAddedMachine.DeleteAllItems();
		DWORD dwThreadId;
		if (m_hAddedMachineThread == NULL)
		{
			m_hAddedMachineThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetAddMachineThread),this,0,&dwThreadId);		
		}
		
		if (m_hAddedMachineThread == NULL)
		{
			g_StringLanType(szLan, "打开线程失败!", "Fail to open thread!");
			AfxMessageBox(szLan);
			return;
		}
		
		g_StringLanType(szLan, "停止获取", "Stop Getting");
		GetDlgItem(IDC_BUTTON_GET_ADDED_MACHINE)->SetWindowText(szLan);
		m_bFCGeting = TRUE;
	}
	else
	{
		if (m_hAddedMachineThread)
		{
			TerminateThread(m_hAddedMachineThread, 0);
		}
		CloseHandle(m_hAddedMachineThread);
		m_hAddedMachineThread = NULL;
		NET_DVR_StopRemoteConfig(m_hAddedMachineRemoteConfig);
		g_StringLanType(szLan, "获取已添加机器", "Get Added machine");
		GetDlgItem(IDC_BUTTON_GET_ADDED_MACHINE)->SetWindowText(szLan);
		m_bAddedMachineGeting = FALSE;
	}
}

void CDlgCVR::OnButtonGetWorkMode() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_N_PLUS_ONE_WORK_MODE_CFG struWorkMode = {0};
	DWORD dwReturned = 0;
	char szLan[128] = {0};
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_N_PLUS_ONE_WORK_MODE, 0, &struWorkMode, sizeof(NET_DVR_N_PLUS_ONE_WORK_MODE_CFG), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_N_PLUS_ONE_WORK_MODE"); 
		g_StringLanType(szLan, "获取参数失败", "Get parameter failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_N_PLUS_ONE_WORK_MODE");	
	}

	m_cmbWorkMode.SetCurSel(struWorkMode.byWorkMode);
	UpdateData(FALSE);
}

void CDlgCVR::OnButtonSetWorkMode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_N_PLUS_ONE_WORK_MODE_CFG struWorkMode = {0};
	struWorkMode.dwSize = sizeof(NET_DVR_N_PLUS_ONE_WORK_MODE_CFG);
	struWorkMode.byWorkMode = m_cmbWorkMode.GetCurSel();
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_N_PLUS_ONE_WORK_MODE, 0, &struWorkMode, sizeof(NET_DVR_N_PLUS_ONE_WORK_MODE_CFG)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_N_PLUS_ONE_WORK_MODE"); 
		g_StringLanType(szLan, "设置参数失败", "Set parameter failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_N_PLUS_ONE_WORK_MODE"); 
		g_StringLanType(szLan, "设置参数成功, 请重启设备!", "Set parameter successfully, please reboot!");
		AfxMessageBox(szLan);
	}
}



void CDlgCVR::OnBtnGetRelocate() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    NET_DVR_RELOCATE_INFO struDevInfo = {0};
    NET_DVR_STREAM_INFO struStreamInfo = {0};
    struStreamInfo.dwSize = sizeof(struStreamInfo);
    struStreamInfo.dwChannel = m_dwN0Chan;
    strncpy((char*)struStreamInfo.byID, m_csStreamIDN0, m_csStreamIDN0.GetLength());
    DWORD dwRet = 0;
    if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_RELOCATE_INFO,1,&struStreamInfo,sizeof(struStreamInfo),&dwRet,&struDevInfo,sizeof(struDevInfo)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_RELOCATION_DEV_INFO"); 
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_RELOCATION_DEV_INFO"); 
    }
    
    m_csRelocationAddr = struDevInfo.byTakeOverAddr;
    m_wRelocationPort = struDevInfo.wPort;
    
    NET_DVR_DEVICEINFO_V30 struDev = {0};
    g_struDeviceInfo[m_iDevIndex].lLoginID = NET_DVR_Login_V30((char*)struDevInfo.byTakeOverAddr,struDevInfo.wPort,"admin","12345",&struDev);
    
    UpdateData(FALSE);
    
}

void CDlgCVR::OnBtnGetOnlineUserCfg()
{
	DWORD dwReturn = 0;
    char szLan[128];

	NET_DVR_ONLINE_USER_INFO struOnlineUserInfo = {0};
	struOnlineUserInfo.dwSize = sizeof(NET_DVR_ONLINE_USER_INFO);
	
    if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ONLINE_USER_CFG, 0, &struOnlineUserInfo, sizeof(NET_DVR_ONLINE_USER_INFO), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ONLINE_USER_CFG Failed");
        g_StringLanType(szLan, "获取失败", "get Failed");
        MessageBox(szLan);
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ONLINE_USER_CFG SUCC");
		
		m_nOnlineUserNum = struOnlineUserInfo.wOnlineUserCount;

        UpdateData(FALSE);
    }
}
