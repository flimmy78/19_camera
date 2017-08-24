#pragma once
#include "afxwin.h"


// CDlgTest �Ի���

class CDlgTest : public CDialogEx
{
    DECLARE_DYNAMIC(CDlgTest)

public:
    CDlgTest(CWnd* pParent = NULL);   // ��׼���캯��
    virtual ~CDlgTest();

    // �Ի�������
    enum { IDD = IDD_DLG_TEST };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    DECLARE_MESSAGE_MAP()
public:
    DWORD m_dwChan;
    DWORD m_dwIn;
    DWORD m_dwOut;
    DWORD m_dwST;
    DWORD m_dwEt;
    DWORD m_dwEh;
    DWORD m_dwAlarm;
    LONG m_lServerID;
    int m_iDeviceIndex;
    LONG m_lChannel;
    afx_msg void OnBnClickedBtnSet();
    CComboBox m_cmbWorkMode;
    CComboBox m_cmbPreviewImageMode;

    afx_msg void OnBnClickedBtnSetCounting();
    afx_msg void OnBnClickedBtnGetCounting();
    NET_DVR_CAMERA_WORK_MODE struCameraWorkMode;
    afx_msg void OnBnClickedBtnFilePath();
    CString m_csFilePath;
    afx_msg void OnBnClickedBtnFileUpload();
    LONG    m_lUploadHandle;
    BOOL    m_bUpLoading;
    HANDLE	m_hUpLoadThread;
};
