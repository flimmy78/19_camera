// DlgBvCalibParamCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgBvCalibParamCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBvCalibParamCfg dialog


CDlgBvCalibParamCfg::CDlgBvCalibParamCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBvCalibParamCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBvCalibParamCfg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lLoginID  = -1;
	m_iDevIndex = -1;
	m_lChannel  = -1;
    
	memset(m_fReprojectMatrix,   0,sizeof(m_fReprojectMatrix));
	memset(m_fLCamInternalMatrix,0,sizeof(m_fLCamInternalMatrix));
	memset(m_fLDistCoeffs,       0,sizeof(m_fLDistCoeffs));
	memset(m_fLRotateMatrix,     0,sizeof(m_fLRotateMatrix));
	memset(m_fLProjectMatrix,    0,sizeof(m_fLProjectMatrix));
	memset(m_fRCamInternalMatrix,0,sizeof(m_fRCamInternalMatrix));
	memset(m_fRDistCoeffs,       0,sizeof(m_fRDistCoeffs));
	memset(m_fRRotateMatrix,     0,sizeof(m_fRRotateMatrix));
	memset(m_fRProjectMatrix,    0,sizeof(m_fRProjectMatrix));
	memset(&m_struBvCalibParam,  0,sizeof(m_struBvCalibParam));

	m_struBvCalibParam.dwSize = sizeof(m_struBvCalibParam);
}


void CDlgBvCalibParamCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBvCalibParamCfg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_1_1,m_fReprojectMatrix[0][0]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_1_2,m_fReprojectMatrix[0][1]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_1_3,m_fReprojectMatrix[0][2]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_1_4,m_fReprojectMatrix[0][3]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_2_1,m_fReprojectMatrix[1][0]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_2_2,m_fReprojectMatrix[1][1]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_2_3,m_fReprojectMatrix[1][2]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_2_4,m_fReprojectMatrix[1][3]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_3_1,m_fReprojectMatrix[2][0]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_3_2,m_fReprojectMatrix[2][1]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_3_3,m_fReprojectMatrix[2][2]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_3_4,m_fReprojectMatrix[2][3]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_4_1,m_fReprojectMatrix[3][0]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_4_2,m_fReprojectMatrix[3][1]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_4_3,m_fReprojectMatrix[3][2]);
	DDX_Text(pDX,IDC_EDIT_REPROJECT_MATRIX_4_4,m_fReprojectMatrix[3][3]);


	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_1_1,m_fLCamInternalMatrix[0][0]);
	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_1_2,m_fLCamInternalMatrix[0][1]);
	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_1_3,m_fLCamInternalMatrix[0][2]);
	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_2_1,m_fLCamInternalMatrix[1][0]);
	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_2_2,m_fLCamInternalMatrix[1][1]);
	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_2_3,m_fLCamInternalMatrix[1][2]);
	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_3_1,m_fLCamInternalMatrix[2][0]);
	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_3_2,m_fLCamInternalMatrix[2][1]);
	DDX_Text(pDX,IDC_EDIT_L_INTER_MATRIX_3_3,m_fLCamInternalMatrix[2][2]);

	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_1_1,m_fRCamInternalMatrix[0][0]);
	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_1_2,m_fRCamInternalMatrix[0][1]);
	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_1_3,m_fRCamInternalMatrix[0][2]);
	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_2_1,m_fRCamInternalMatrix[1][0]);
	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_2_2,m_fRCamInternalMatrix[1][1]);
	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_2_3,m_fRCamInternalMatrix[1][2]);
	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_3_1,m_fRCamInternalMatrix[2][0]);
	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_3_2,m_fRCamInternalMatrix[2][1]);
	DDX_Text(pDX,IDC_EDIT_R_INTER_MATRIX_3_3,m_fRCamInternalMatrix[2][2]);

	DDX_Text(pDX,IDC_EDIT_L_DIST_COEFFS_1,m_fLDistCoeffs[0]);
	DDX_Text(pDX,IDC_EDIT_L_DIST_COEFFS_2,m_fLDistCoeffs[1]);
	DDX_Text(pDX,IDC_EDIT_L_DIST_COEFFS_3,m_fLDistCoeffs[2]);
	DDX_Text(pDX,IDC_EDIT_L_DIST_COEFFS_4,m_fLDistCoeffs[3]);
	DDX_Text(pDX,IDC_EDIT_L_DIST_COEFFS_5,m_fLDistCoeffs[4]);
	DDX_Text(pDX,IDC_EDIT_L_DIST_COEFFS_6,m_fLDistCoeffs[5]);
	DDX_Text(pDX,IDC_EDIT_L_DIST_COEFFS_7,m_fLDistCoeffs[6]);
	DDX_Text(pDX,IDC_EDIT_L_DIST_COEFFS_8,m_fLDistCoeffs[7]);

	DDX_Text(pDX,IDC_EDIT_R_DIST_COEFFS_1,m_fRDistCoeffs[0]);
	DDX_Text(pDX,IDC_EDIT_R_DIST_COEFFS_2,m_fRDistCoeffs[1]);
	DDX_Text(pDX,IDC_EDIT_R_DIST_COEFFS_3,m_fRDistCoeffs[2]);
	DDX_Text(pDX,IDC_EDIT_R_DIST_COEFFS_4,m_fRDistCoeffs[3]);
	DDX_Text(pDX,IDC_EDIT_R_DIST_COEFFS_5,m_fRDistCoeffs[4]);
	DDX_Text(pDX,IDC_EDIT_R_DIST_COEFFS_6,m_fRDistCoeffs[5]);
	DDX_Text(pDX,IDC_EDIT_R_DIST_COEFFS_7,m_fRDistCoeffs[6]);
	DDX_Text(pDX,IDC_EDIT_R_DIST_COEFFS_8,m_fRDistCoeffs[7]);

	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_1_1,m_fLRotateMatrix[0][0]);
	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_1_2,m_fLRotateMatrix[0][1]);
	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_1_3,m_fLRotateMatrix[0][2]);
	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_2_1,m_fLRotateMatrix[1][0]);
	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_2_2,m_fLRotateMatrix[1][1]);
	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_2_3,m_fLRotateMatrix[1][2]);
	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_3_1,m_fLRotateMatrix[2][0]);
	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_3_2,m_fLRotateMatrix[2][1]);
	DDX_Text(pDX,IDC_EDIT_L_ROTATE_MATRIX_3_3,m_fLRotateMatrix[2][2]);

	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_1_1,m_fRRotateMatrix[0][0]);
	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_1_2,m_fRRotateMatrix[0][1]);
	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_1_3,m_fRRotateMatrix[0][2]);
	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_2_1,m_fRRotateMatrix[1][0]);
	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_2_2,m_fRRotateMatrix[1][1]);
	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_2_3,m_fRRotateMatrix[1][2]);
	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_3_1,m_fRRotateMatrix[2][0]);
	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_3_2,m_fRRotateMatrix[2][1]);
	DDX_Text(pDX,IDC_EDIT_R_ROTATE_MATRIX_3_3,m_fRRotateMatrix[2][2]);

	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_1_1,m_fLProjectMatrix[0][0]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_1_2,m_fLProjectMatrix[0][1]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_1_3,m_fLProjectMatrix[0][2]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_1_4,m_fLProjectMatrix[0][3]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_2_1,m_fLProjectMatrix[1][0]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_2_2,m_fLProjectMatrix[1][1]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_2_3,m_fLProjectMatrix[1][2]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_2_4,m_fLProjectMatrix[1][3]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_3_1,m_fLProjectMatrix[2][0]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_3_2,m_fLProjectMatrix[2][1]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_3_3,m_fLProjectMatrix[2][2]);
	DDX_Text(pDX,IDC_EDIT_L_REPROJECT_MATRIX_3_4,m_fLProjectMatrix[2][3]);

	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_1_1,m_fRProjectMatrix[0][0]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_1_2,m_fRProjectMatrix[0][1]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_1_3,m_fRProjectMatrix[0][2]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_1_4,m_fRProjectMatrix[0][3]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_2_1,m_fRProjectMatrix[1][0]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_2_2,m_fRProjectMatrix[1][1]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_2_3,m_fRProjectMatrix[1][2]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_2_4,m_fRProjectMatrix[1][3]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_3_1,m_fRProjectMatrix[2][0]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_3_2,m_fRProjectMatrix[2][1]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_3_3,m_fRProjectMatrix[2][2]);
	DDX_Text(pDX,IDC_EDIT_R_REPROJECT_MATRIX_3_4,m_fRProjectMatrix[2][3]);

	DDX_Control(pDX, IDC_COMBO_LENS_TYPE, m_comLensType);
}


BEGIN_MESSAGE_MAP(CDlgBvCalibParamCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgBvCalibParamCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBvCalibParamCfg message handlers
BOOL CDlgBvCalibParamCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_comLensType.SetCurSel(0);
    if (GetBvCalibParam())
	{
		LoadWndContent();
	}
	else
	{   
		char szError[32] = "\0";
		g_StringLanType(szError, "获取图像校正参数失败","Get bv calib param failed");
		AfxMessageBox(szError);
	}
	return TRUE;
}

void CDlgBvCalibParamCfg::OnOK() 
{   
	if (!UpdateData(TRUE))
	{
		return;
	}
	SaveWndContent();
	char szError[32] = "\0";
	if (SetBvCalibParam())
	{
		g_StringLanType(szError, "保存成功","Saved successfully");
	}
	else
	{
		g_StringLanType(szError, "保存失败","Save failed");
	}
	AfxMessageBox(szError);
}


BOOL CDlgBvCalibParamCfg::GetBvCalibParam()
{   
	DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_BV_CORRECT_PARAM, m_lChannel, &m_struBvCalibParam, sizeof(m_struBvCalibParam), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_BV_CORRECT_PARAM Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {   
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_BV_CORRECT_PARAM Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgBvCalibParamCfg::SetBvCalibParam()
{
	BOOL bRet = FALSE;
    if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_BV_CORRECT_PARAM, m_lChannel, &m_struBvCalibParam, sizeof(m_struBvCalibParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_BV_CORRECT_PARAM Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_BV_CORRECT_PARAM Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

void CDlgBvCalibParamCfg::LoadWndContent()
{   
	memcpy(m_fReprojectMatrix,   m_struBvCalibParam.fReprojectMatrix                ,sizeof(m_fReprojectMatrix));
	memcpy(m_fLCamInternalMatrix,m_struBvCalibParam.struLCamParam.fCamInternalMatrix,sizeof(m_fLCamInternalMatrix));
	memcpy(m_fLDistCoeffs,       m_struBvCalibParam.struLCamParam.fDistCoeffs       ,sizeof(m_fLDistCoeffs));
	memcpy(m_fLRotateMatrix,     m_struBvCalibParam.struLCamParam.fRotateMatrix     ,sizeof(m_fLRotateMatrix));
	memcpy(m_fLProjectMatrix,    m_struBvCalibParam.struLCamParam.fProjectMatrix    ,sizeof(m_fLProjectMatrix));
	memcpy(m_fRCamInternalMatrix,m_struBvCalibParam.struRCamParam.fCamInternalMatrix,sizeof(m_fRCamInternalMatrix));
	memcpy(m_fRDistCoeffs,       m_struBvCalibParam.struRCamParam.fDistCoeffs       ,sizeof(m_fRDistCoeffs));
	memcpy(m_fRRotateMatrix,     m_struBvCalibParam.struRCamParam.fRotateMatrix     ,sizeof(m_fRRotateMatrix));
	memcpy(m_fRProjectMatrix,    m_struBvCalibParam.struRCamParam.fProjectMatrix    ,sizeof(m_fRProjectMatrix));
	m_comLensType.SetCurSel(m_struBvCalibParam.byLensType);
	UpdateData(FALSE);
}

void CDlgBvCalibParamCfg::SaveWndContent()
{   
	UpdateData(TRUE);
	memcpy(m_struBvCalibParam.fReprojectMatrix                ,m_fReprojectMatrix    ,sizeof(m_fReprojectMatrix));
	memcpy(m_struBvCalibParam.struLCamParam.fCamInternalMatrix,m_fLCamInternalMatrix ,sizeof(m_fLCamInternalMatrix));
	memcpy(m_struBvCalibParam.struLCamParam.fDistCoeffs       ,m_fLDistCoeffs        ,sizeof(m_fLDistCoeffs));
	memcpy( m_struBvCalibParam.struLCamParam.fRotateMatrix    ,m_fLRotateMatrix      ,sizeof(m_fLRotateMatrix));
	memcpy(m_struBvCalibParam.struLCamParam.fProjectMatrix    ,m_fLProjectMatrix     ,sizeof(m_fLProjectMatrix));
	memcpy(m_struBvCalibParam.struRCamParam.fCamInternalMatrix,m_fRCamInternalMatrix ,sizeof(m_fRCamInternalMatrix));
	memcpy(m_struBvCalibParam.struRCamParam.fDistCoeffs       ,m_fRDistCoeffs        ,sizeof(m_fRDistCoeffs));
	memcpy(m_struBvCalibParam.struRCamParam.fRotateMatrix     ,m_fRRotateMatrix      ,sizeof(m_fRRotateMatrix));
	memcpy(m_struBvCalibParam.struRCamParam.fProjectMatrix    ,m_fRProjectMatrix     ,sizeof(m_fRProjectMatrix));
	m_struBvCalibParam.byLensType = m_comLensType.GetCurSel();
}
