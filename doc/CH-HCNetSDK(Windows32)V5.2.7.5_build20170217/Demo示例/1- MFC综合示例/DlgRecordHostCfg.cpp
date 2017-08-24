// DlgRecordHostCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRecordHostCfg.h"
#include "xml/XmlBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgRecordHostCfg dialog


DlgRecordHostCfg::DlgRecordHostCfg(CWnd* pParent /*=NULL*/)
	: CDialog(DlgRecordHostCfg::IDD, pParent)
	, m_bCourseDataStorageEnabled(FALSE)
    , m_iStatureLowerLimit(0)
{
	//{{AFX_DATA_INIT(DlgRecordHostCfg)
	m_DelayTime = 0;
	//}}AFX_DATA_INIT
	m_lUserID = 0;
	m_iDeviceIndex = 0;
	memset(&m_struRecordHostCfg, 0 ,sizeof(m_struRecordHostCfg));
	m_iStartChannel = 0;
	m_iMirrorNum = 0;
}


void DlgRecordHostCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgRecordHostCfg)
	DDX_Control(pDX, IDC_COMBO_RECORD_TYPE, m_comRecordType);
	DDX_Text(pDX, IDC_DELAY_TIME, m_DelayTime);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHECK1, m_bCourseDataStorageEnabled);
    DDX_Text(pDX, IDC_EDIT_STATURE_LOWER_LIMIT, m_iStatureLowerLimit);
}


BEGIN_MESSAGE_MAP(DlgRecordHostCfg, CDialog)
	//{{AFX_MSG_MAP(DlgRecordHostCfg)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_GET_HUMAN_INFO, &DlgRecordHostCfg::OnBnClickedButtonGetHumanInfo)
    ON_BN_CLICKED(IDC_BUTTON_SET_HUMAN_INFO, &DlgRecordHostCfg::OnBnClickedButtonSetHumanInfo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgRecordHostCfg message handlers

BOOL DlgRecordHostCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	OnBtnGet();
	return TRUE;
}

void DlgRecordHostCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	m_struRecordHostCfg.byDirectedMode = m_comRecordType.GetCurSel();
	m_struRecordHostCfg.dwOneKeyDelayTime = m_DelayTime;
	m_struRecordHostCfg.byCourseDataStorageEnabled = m_bCourseDataStorageEnabled;
	if(!NET_DVR_SetDVRConfig(m_lUserID,NET_DVR_SET_RECORDINGHOST_CFG,m_iStartChannel,&m_struRecordHostCfg,sizeof(m_struRecordHostCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RECORDINGHOST_CFG,  %s", "Set Record host cfg faild");
		g_StringLanType(szLan, "����¼��������������ʧ��", "Set Record host cfg failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORDINGHOST_CFG,  %s", "Set Record host cfg success");
		g_StringLanType(szLan, "����¼�������������óɹ�", "Set Record host cfg success");
		AfxMessageBox(szLan);
	}
}

void DlgRecordHostCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturned = 0;
	char szLan[128] = {0};
	if(!NET_DVR_GetDVRConfig(m_lUserID,NET_DVR_GET_RECORDINGHOST_CFG,m_iStartChannel,&m_struRecordHostCfg,sizeof(m_struRecordHostCfg),&dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RECORDINGHOST_CFG,  %s", "Get Record host cfg faild");
		g_StringLanType(szLan, "��ȡ¼��������������ʧ��", "Get Record host cfg failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORDINGHOST_CFG,  %s", "Get Record host cfg success");
		g_StringLanType(szLan, "��ȡ¼�������������óɹ�", "Get Record host cfg success");
		AfxMessageBox(szLan);
	}
	m_DelayTime = m_struRecordHostCfg.dwOneKeyDelayTime;
	m_comRecordType.SetCurSel(m_struRecordHostCfg.byDirectedMode);
	m_bCourseDataStorageEnabled = m_struRecordHostCfg.byCourseDataStorageEnabled;
	UpdateData(FALSE);
}

BOOL DlgRecordHostCfg::CreateHumanInfoCfg(char* pBuf, DWORD dwBufLen, int &dwRet)
{
    CString strParam = _T("");
    CXmlBase xmlBase;
    xmlBase.CreateRoot("HumanInformation");
    xmlBase.SetAttribute("version", "2.0");
    strParam.Format("%d", m_iStatureLowerLimit);
    xmlBase.AddNode("statureLowerLimit", strParam.GetBuffer(0));
    xmlBase.OutOfElem();

    return xmlBase.WriteToBuf(pBuf, dwBufLen, dwRet);
}

void DlgRecordHostCfg::OnBnClickedButtonGetHumanInfo()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    char szUrl[256] = { 0 };
    sprintf(szUrl, "GET /ISAPI/ContentMgmt/RecordingHost/HumanInformation\r\n");

    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    DWORD dwOutputLen = 1024 * 1024;
    char *pOutBuf = new char[dwOutputLen];
    memset(pOutBuf, 0, dwOutputLen);
    struOuput.lpOutBuffer = pOutBuf;
    struOuput.dwOutBufferSize = dwOutputLen;

    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
        delete[]pOutBuf;
        pOutBuf = NULL;
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    BOOL bRet = FALSE;
    CXmlBase xmlBase;
    xmlBase.Parse(pOutBuf);
    if (xmlBase.FindElem("HumanInformation") && xmlBase.IntoElem())
    {
        if (xmlBase.FindElem("statureLowerLimit"))
        {
            m_iStatureLowerLimit = atoi(xmlBase.GetData().c_str());
        }
        xmlBase.OutOfElem();
    }

    if (pOutBuf != NULL)
    {
        delete[]pOutBuf;
        pOutBuf = NULL;
    }

    UpdateData(FALSE);
    return;
}


void DlgRecordHostCfg::OnBnClickedButtonSetHumanInfo()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);
    DWORD dwBufLen = 10 * 1024;
    char *pBuf = new char[dwBufLen];
    memset(pBuf, 0, dwBufLen);
    int dwXmlLen = 0;
    if (!CreateHumanInfoCfg(pBuf, dwBufLen, dwXmlLen))
    {
        delete[]pBuf;
        pBuf = NULL;
        return;
    }

    char szUrl[256] = { 0 };
    sprintf(szUrl, "PUT /ISAPI/ContentMgmt/RecordingHost/HumanInformation\r\n");
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    struInput.lpRequestUrl = szUrl;
    struInput.dwRequestUrlLen = strlen(szUrl);
    struInput.lpInBuffer = pBuf;
    struInput.dwInBufferSize = dwXmlLen;
    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInput, &struOuput))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, szUrl);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, szUrl);
    }

    if (pBuf != NULL)
    {
        delete[]pBuf;
        pBuf = NULL;
    }

    UpdateData(FALSE);
}

