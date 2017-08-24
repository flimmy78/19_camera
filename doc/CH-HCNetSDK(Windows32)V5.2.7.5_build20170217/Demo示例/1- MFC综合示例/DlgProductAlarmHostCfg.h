#if !defined(AFX_DLGPRODUCTALARMHOSTCFG_H__A2225D42_339C_42D9_B7A3_E080E53F15C6__INCLUDED_)
#define AFX_DLGPRODUCTALARMHOSTCFG_H__A2225D42_339C_42D9_B7A3_E080E53F15C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProductAlarmHostCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProductAlarmHostCfg dialog

class CDlgProductAlarmHostCfg : public CDialog
{
// Construction
public:
	CDlgProductAlarmHostCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProductAlarmHostCfg)
	enum { IDD = IDD_SUBDLG_PRODUCT_ALARMHOST };
	CComboBox	m_cmbZoneResistor;
	CComboBox	m_cmSensitivity;
	CComboBox	m_comboCopyTime;
	CComboBox	m_comboWeekday;
	CListCtrl	m_listSirenOut;
	CComboBox	m_comboDetector;
	CComboBox	m_comboDefenseType;
	CListCtrl	m_listAlarmIn;
	CListCtrl	m_listAlarmOut;
	CComboBox	m_comboAlarmIn;
	CString	m_csAlarmInName;
    CString m_csVoiceFileName;
	int		m_iDelayTime;
	int		m_iHour11;
	int		m_iHour12;
	int		m_iHour21;
	int		m_iHour22;
	int		m_iMin11;
	int		m_iMin12;
	int		m_iMin21;
	int		m_iMin22;
	int		m_iMin31;
	int		m_iMin32;
	int		m_iMin41;
	int		m_iMin42;
	int		m_iHour31;
	int		m_iHour32;
	int		m_iHour41;
	int		m_iHour42;
	BOOL	m_bGroupBypass;
	BOOL	m_chUploadReport;
	int		m_iInDelay;
	int		m_iOutDelay;
	float	m_fZoneResistorManual;
    BOOL    m_bLampOut[8];
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProductAlarmHostCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProductAlarmHostCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetAlarmInParam();
	afx_msg void OnSelchangeComboAlarmIn();
	afx_msg void OnBtnSetAlarmChan();
	afx_msg void OnBtnCloseAlarmChan();
	afx_msg void OnBtnStatusQuery();
	afx_msg void OnBtnAlarmoutCfg();
	afx_msg void OnBtnAlarmhostAbility();
	afx_msg void OnBtnSensorCfg();
	afx_msg void OnBtnRs485Cfg();
	afx_msg void OnBtnNetUser();
	afx_msg void OnBtnKeyboardUser();
	afx_msg void OnBtnOperatorUser();
	afx_msg void OnBtnBattaryVoltage();
	afx_msg void OnBtnBypass();
	afx_msg void OnBtnUnBypass();
	afx_msg void OnBtnAlarmhostEnablecfg();
	afx_msg void OnRclickListAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuSelectAll();
	afx_msg void OnMenuCancelAll();
	afx_msg void OnTimeOk();
	afx_msg void OnTimeCopy();
	afx_msg void OnSelchangeComboweekday();
	afx_msg void OnSelchangeCombocopytime();
	afx_msg void OnSelchangeComboDefenseType();
	afx_msg void OnBtnGatewayCfg();
	afx_msg void OnButtonDialparam();
	afx_msg void OnBtnBypasssetup();
	afx_msg void OnBtnBypassStopsetup();
	afx_msg void OnBtnSubsystemCfg();
	afx_msg void OnBtnReportmode();
	afx_msg void OnBtnGprspara();
	afx_msg void OnBtnNetcfg();
	afx_msg void OnBtnZoomCode();
	afx_msg void OnBtnTriggerCode();
	afx_msg void OnBtnFaultProcess();
	afx_msg void OnBtnEventTrigger();
	afx_msg void OnBtnExternModule();
	afx_msg void OnBtnLed();
	afx_msg void OnBtnAudioAssociate();
	afx_msg void OnBtnSafetyCabin();
	afx_msg void OnBtnModuleCfg();
	afx_msg void OnBtnExternalDeviceState();
	afx_msg void OnBtnExternalDeviceLimitValue();
	afx_msg void OnBtnSensorLinkage();
	afx_msg void OnBtnPointCfg();
	afx_msg void OnBtnUploadMode();
	afx_msg void OnBtnHistoryData();
	afx_msg void OnBtnPrinter();
	afx_msg void OnButAlarmLogSearch();
	afx_msg void OnBtnDh3();
	afx_msg void OnBtnScaleOutCfg();
	afx_msg void OnBtnAlarmChanAblitity();
	afx_msg void OnBtnAlarmCenter();
	afx_msg void OnBtnIDSMainBorad();
	afx_msg void OnSelchangeCmbZoneResistor();
	afx_msg void OnBtnTamper();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    int     m_iDevIndex;
    LONG    m_lServerID;
    LONG    m_lStartChan;
    LONG    m_lChannel;
	char    m_szLan[128];
	BOOL	m_bInit;

    NET_DVR_ALARMHOST_ABILITY   m_struAlarmHostAbility;
    NET_DVR_ALARMIN_PARAM_V50       m_struAlarmInParam;
    NET_DVR_ALARMIN_SETUP       m_struAlarmInSetup;
    
    float m_fBatteryVoltage;
public:
    void InitWnd();
    void InitAlarmInCombo();
    void InitAlarmOutList();
    void InitAlarmInList();
    void InitSirenOutList();
//    void InitAlarmOutCombo();
    void InitAlarmInDetectorCombo();
    void IninAlarmInDefenseTypeCombo();
	void InitWeekdayCombo();
	void InitSensitivityCombo();
    void InitZoneSignalTypeCombo();

    BOOL GetAlarmHostAbility(NET_DVR_ALARMHOST_ABILITY& struAlarmHostAbility);
    BOOL SetAlarmInParam(NET_DVR_ALARMIN_PARAM_V50& struAlarmInParam);
    BOOL GetAlarmInParam(NET_DVR_ALARMIN_PARAM_V50& struAlarmInParam);
    BOOL AlarmHostSetAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup);
    BOOL AlarmHostCloseAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup);
    BOOL GetBatteryVoltage();
    BOOL BypassAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup);
    BOOL UnBypassAlarmChan(NET_DVR_ALARMIN_SETUP &struAlarmInSetup);

    void SetAlarmInParamToWnd(NET_DVR_ALARMIN_PARAM_V50& struAlarmInParam);
    void GetAlarmInParamFromWnd(NET_DVR_ALARMIN_PARAM_V50& struAlarmInParam);

    void GetAlarmInSetupFromWnd(NET_DVR_ALARMIN_SETUP &struAlarmInSetup);

    BOOL F_TimeTest();
    void SetAlarmTimeToWnd(NET_DVR_SCHEDTIME const *pAlarmTime, int nDay);
    void GetAlarmTimeFromWnd(NET_DVR_SCHEDTIME *pAlarmTime, int nDay);

    void UpdatePapam(); 
    afx_msg void OnBnClickedBtnAlarmOneKey();
	afx_msg void OnBnClickedBtnNetcardCfg();
    afx_msg void OnBnClickedBtnStdXmlConfig();
    CString m_csDetectorSerialNo;
    CComboBox m_cmbZoneSignalType;
    BOOL m_bChkEnableDetetorTypeCfg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPRODUCTALARMHOSTCFG_H__A2225D42_339C_42D9_B7A3_E080E53F15C6__INCLUDED_)
