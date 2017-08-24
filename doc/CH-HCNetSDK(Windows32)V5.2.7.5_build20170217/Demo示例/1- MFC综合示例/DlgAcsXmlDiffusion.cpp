// DlgAcsXmlDiffusion.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgAcsXmlDiffusion.h"
#include "afxdialogex.h"
#include "xml/XmlBase.h"


// CDlgAcsXmlDiffusion �Ի���

IMPLEMENT_DYNAMIC(CDlgAcsXmlDiffusion, CDialog)

CDlgAcsXmlDiffusion::CDlgAcsXmlDiffusion(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAcsXmlDiffusion::IDD, pParent)
{
    m_csCommandStr = "/ISAPI/AccessControl/AttendanceEffectiveID";
    m_csInputParam = _T("");
    m_csOutputParam = _T("");
}

CDlgAcsXmlDiffusion::~CDlgAcsXmlDiffusion()
{
}

void CDlgAcsXmlDiffusion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_OPERATE_TYPE, m_cmbOperateType);
    DDX_Control(pDX, IDC_COMBO_COMMAND, m_cmbCommand);
    DDX_Text(pDX, IDC_EDIT_COMMAND, m_csCommandStr);
    DDX_Text(pDX, IDC_EDIT_PARAM_INPUT, m_csInputParam);
    DDX_Text(pDX, IDC_EDIT_PARAM_OUTPUT, m_csOutputParam);
}

BOOL CDlgAcsXmlDiffusion::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_cmbOperateType.SetCurSel(0);
    m_cmbCommand.SetCurSel(0);

    return TRUE;
}

BEGIN_MESSAGE_MAP(CDlgAcsXmlDiffusion, CDialog)
    ON_BN_CLICKED(IDC_BTN_GET, &CDlgAcsXmlDiffusion::OnBnClickedBtnGet)
    ON_BN_CLICKED(IDC_BTN_EXIT, &CDlgAcsXmlDiffusion::OnBnClickedBtnExit)
    ON_CBN_SELCHANGE(IDC_COMBO_OPERATE_TYPE, &CDlgAcsXmlDiffusion::OnCbnSelchangeComboOperateType)
    ON_CBN_SELCHANGE(IDC_COMBO_COMMAND, &CDlgAcsXmlDiffusion::OnCbnSelchangeComboCommand)
END_MESSAGE_MAP()


// CDlgAcsXmlDiffusion ��Ϣ�������


void CDlgAcsXmlDiffusion::OnBnClickedBtnGet()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);

    char szUrl[256] = { 0 };
    CString csCommand = _T("");
    NET_DVR_XML_CONFIG_INPUT    struInput = { 0 };
    NET_DVR_XML_CONFIG_OUTPUT   struOuput = { 0 };
    struInput.dwSize = sizeof(struInput);
    struOuput.dwSize = sizeof(struOuput);
    DWORD dwBufferLen = 1024 * 1024;
    char *pBuffer = new char[dwBufferLen];
    memset(pBuffer, 0, dwBufferLen);
    CXmlBase xmlOutput;

    if (m_cmbOperateType.GetCurSel() == 0)  //GET
    {
        csCommand = "GET " + m_csCommandStr;
        memcpy(szUrl, csCommand.GetBuffer(), csCommand.GetLength());

        struInput.lpRequestUrl = szUrl;
        struInput.dwRequestUrlLen = strlen(szUrl);
        struOuput.lpOutBuffer = pBuffer;
        struOuput.dwOutBufferSize = dwBufferLen;

        if (!NET_DVR_STDXMLConfig(m_lServerID, &struInput, &struOuput))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, szUrl);
            if (pBuffer != NULL)
            {
                delete[]pBuffer;
                pBuffer = NULL;
            }
            return;
        }
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, szUrl);

        xmlOutput.Parse((char *)struOuput.lpOutBuffer);
    }
    else   //PUT
    {
        csCommand = "PUT " + m_csCommandStr;
        memcpy(szUrl, csCommand.GetBuffer(), csCommand.GetLength());

        struInput.lpRequestUrl = szUrl;
        struInput.dwRequestUrlLen = strlen(szUrl);

        DWORD dwInBufferLen = 1024 * 1024;
        char *pInBuffer = new char[dwInBufferLen];
        memset(pInBuffer, 0, dwInBufferLen);
        memcpy(pInBuffer, m_csInputParam.GetBuffer(), m_csInputParam.GetLength());

        struInput.lpInBuffer = pInBuffer;
        struInput.dwInBufferSize = m_csInputParam.GetLength();
        int iLength = 0;
        for (int i = 0; i < struInput.dwInBufferSize; i++)
        {
            //�˴���Ϊ�˱��⴫�ݿո�ͻ��з�
            if (*((char*)struInput.lpInBuffer + i) != 10 && *((char*)struInput.lpInBuffer + i) != 32)
            {
                *((char*)struInput.lpInBuffer + iLength) = *((char*)struInput.lpInBuffer + i);
                iLength += 1;
            }
        }
        struInput.dwInBufferSize = iLength;
        struOuput.lpStatusBuffer = pBuffer;
        struOuput.dwStatusSize = dwBufferLen;

        if (!NET_DVR_STDXMLConfig(m_lServerID, &struInput, &struOuput))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, szUrl);
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, szUrl);
        }

        xmlOutput.Parse((char *)struOuput.lpStatusBuffer);

        if (pInBuffer != NULL)
        {
            delete[]pInBuffer;
            pInBuffer = NULL;
        }
    }

    xmlOutput.SetRoot();
    m_csOutputParam = xmlOutput.GetChildren().c_str();
    m_csOutputParam.Replace("\n", "\r\n");

    if (pBuffer != NULL)
    {
        delete[]pBuffer;
        pBuffer = NULL;
    }

    UpdateData(FALSE);
}


void CDlgAcsXmlDiffusion::OnBnClickedBtnExit()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    CDialog::OnOK();
}


void CDlgAcsXmlDiffusion::OnCbnSelchangeComboOperateType()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);

    switch (m_cmbOperateType.GetCurSel())
    {
    case 0: //GET
        m_csInputParam = _T("");
        break;
    case 1: //PUT
        GetCommandStrAndInputParam();
        break;
    default:
        break;
    }

    UpdateData(FALSE);
}


void CDlgAcsXmlDiffusion::OnCbnSelchangeComboCommand()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    UpdateData(TRUE);

    GetCommandStrAndInputParam();

    UpdateData(FALSE);
}

void CDlgAcsXmlDiffusion::GetCommandStrAndInputParam()
{
    CXmlBase xmlInput;
    switch (m_cmbCommand.GetCurSel())
    {
    case 0: //������ЧID��ȡ
        m_csCommandStr = "/ISAPI/AccessControl/AttendanceEffectiveID";
        /*xmlInput.Parse("<DepartmentParam>\
                            <departmentName>department1</departmentName>\
                       </DepartmentParam>");*/
        break;
    case 1: //�豸����ģʽ����
        m_csCommandStr = "/ISAPI/VideoIntercom/workMode";
        xmlInput.Parse("<WorkMode>\
                          <deviceWorkMode>ipcMode</deviceWorkMode>\
                        </WorkMode>");
        break;
    case 2: //�ݿؼ̵�������
        m_csCommandStr = "/ISAPI/AccessControl/LadderControlRelay/FloorNo/1";
        xmlInput.Parse("<LadderControlRelay>\
                            <CallLadder>\
                                <distractControlNo>3</distractControlNo>\
                                <relayNo>1</relayNo>\
                            </CallLadder>\
                            <KeyControl>\
                                <distractControlNo>3</distractControlNo>\
                                <relayNo>1</relayNo>\
                            </KeyControl>\
                            <AutoKey>\
                                <distractControlNo>3</distractControlNo>\
                                <relayNo>1</relayNo>\
                            </AutoKey>\
                       </LadderControlRelay>");
        break;
    case 3: //�������ʶ���ն˲�������
        m_csCommandStr = "/ISAPI/AccessControl/IdentityTerminal";
        xmlInput.Parse("<IdentityTerminal>\
                       <terminalMode>registerMode</terminalMode>\
                       <videoStorageTime>8</videoStorageTime>\
                       <twoDimensionCode>enable</twoDimensionCod>\
                       <blackListCheck>enable</blackListCheck>\
                       <faceAlgorithm>HIK-Z</faceAlgorithm>\
                       </IdentityTerminal>");
    default:
        break;
    }
    if (m_cmbOperateType.GetCurSel() == 1)
    {
        xmlInput.SetRoot();
        m_csInputParam = xmlInput.GetChildren().c_str();
        m_csInputParam.Replace("\n", "\r\n");
    }
    else
    {
        m_csInputParam = _T("");
    }
    m_csOutputParam = _T("");
    return;
}
