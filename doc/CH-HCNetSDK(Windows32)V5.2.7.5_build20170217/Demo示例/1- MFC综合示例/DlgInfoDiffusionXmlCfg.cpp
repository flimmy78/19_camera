// DlgInfoDiffusionXmlCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgInfoDiffusionXmlCfg.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionXmlCfg dialog


CDlgInfoDiffusionXmlCfg::CDlgInfoDiffusionXmlCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInfoDiffusionXmlCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInfoDiffusionXmlCfg)
	m_szCommandStr = _T("");
	m_szInputParam = _T("");
	m_szOutputParam = _T("");
	//}}AFX_DATA_INIT
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	memset(m_szCommandBuf, 0, sizeof(m_szCommandBuf));
	m_lpOutputXml = new char[MAX_LEN_XML];
	memset(m_lpOutputXml, 0, MAX_LEN_XML);
}


void CDlgInfoDiffusionXmlCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfoDiffusionXmlCfg)
	DDX_Control(pDX, IDC_COMBO_OPERATE_TYPE, m_cmbOperateType);
	DDX_Text(pDX, IDC_EDIT_COMMAND, m_szCommandStr);
	DDX_Text(pDX, IDC_EDIT_PARAM_INPUT, m_szInputParam);
	DDX_Text(pDX, IDC_EDIT_PARAM_OUTPUT, m_szOutputParam);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInfoDiffusionXmlCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgInfoDiffusionXmlCfg)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInfoDiffusionXmlCfg message handlers

void CDlgInfoDiffusionXmlCfg::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgInfoDiffusionXmlCfg::OnBtnGet() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    
    NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
    struInputParam.dwSize = sizeof(struInputParam);
    int nSel = m_cmbOperateType.GetCurSel();
    if (nSel == CB_ERR)
    {
        return;
    }
    CString szCommand = _T("");
    m_cmbOperateType.GetLBText(nSel, szCommand);
    
    szCommand = szCommand + _T(" ") + m_szCommandStr;
    memset(m_szCommandBuf, 0, sizeof(m_szCommandBuf));
    sprintf(m_szCommandBuf, "%s", szCommand);
    struInputParam.lpRequestUrl = m_szCommandBuf;
    struInputParam.dwRequestUrlLen = strlen(m_szCommandBuf);
    
    char szStatusBuff[1024] = {0};
    NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
    struOutputParam.dwSize = sizeof(struOutputParam);
    struInputParam.lpInBuffer = m_szInputParam.GetBuffer(0);
    struInputParam.dwInBufferSize = m_szInputParam.GetLength();
    memset(m_lpOutputXml, 0, MAX_LEN_XML);
    struOutputParam.lpOutBuffer = m_lpOutputXml;
    struOutputParam.dwOutBufferSize = MAX_LEN_XML;
    struOutputParam.lpStatusBuffer = szStatusBuff;
    struOutputParam.dwStatusSize = sizeof(szStatusBuff);
    
    if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
        return;
    }
    g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
    m_szOutputParam = m_lpOutputXml;
    
	UpdateData(FALSE);
}

void CDlgInfoDiffusionXmlCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	NET_DVR_XML_CONFIG_INPUT struInputParam = {0};
	struInputParam.dwSize = sizeof(struInputParam);
	int nSel = m_cmbOperateType.GetCurSel();
	if (nSel == CB_ERR)
	{
		return;
	}
	CString szCommand = _T("");
	m_cmbOperateType.GetLBText(nSel, szCommand);
	if (0 == strcmp(szCommand, _T("GET")))
	{
		return;
	}
	else if (strcmp(szCommand, _T("DELETE")))
	{
		struInputParam.lpInBuffer = m_szInputParam.GetBuffer(0);
		struInputParam.dwInBufferSize = m_szInputParam.GetLength();
	}
	szCommand = szCommand + _T(" ") + m_szCommandStr + _T("\r\n");
	memset(m_szCommandBuf, 0, sizeof(m_szCommandBuf));
	sprintf(m_szCommandBuf, "%s", szCommand);
	struInputParam.lpRequestUrl = m_szCommandBuf;
	struInputParam.dwRequestUrlLen = strlen(m_szCommandBuf);
	
	char szStatusBuff[1024] = {0};
	NET_DVR_XML_CONFIG_OUTPUT struOutputParam = {0};
	struOutputParam.dwSize = sizeof(struOutputParam);
	struOutputParam.lpStatusBuffer = szStatusBuff;
	struOutputParam.dwStatusSize = sizeof(szStatusBuff);
	
	if (!NET_DVR_STDXMLConfig(m_lUserID, &struInputParam, &struOutputParam))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_STDXMLConfig");
		return;
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_STDXMLConfig");
	
	UpdateData(FALSE);
}

BOOL CDlgInfoDiffusionXmlCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbOperateType.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
