#if !defined(AFX_DLGAREAMONITORCFG_H__D692C9BB_9C86_4E0B_922A_77796E59C237__INCLUDED_)
#define AFX_DLGAREAMONITORCFG_H__D692C9BB_9C86_4E0B_922A_77796E59C237__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAreaMonitorCfg.h : header file
//

#include "./xml/XmlBase.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgAreaMonitorCfg dialog

typedef enum
{
	NODE_STRING_TO_BOOL = 0,    //stringתbool(0,1)
		NODE_STRING_TO_INT  = 1,    //stringתint(HPR_UINT32)
		NODE_STRING_TO_ARRAY = 2,   //stringת����(HPR_UINT8[],char[])
		NODE_STRING_TO_BYTE = 3,    //stringתHPR_UINT8,HPR_UINT8��Ϊ����ʱ
		NODE_STRING_TO_WORD = 4,    //stringתHPR_UINT16
		NODE_STRING_TO_FLOAT = 5,    //stringתFLOAT
		
		NODE_TYPE_REVERSE   = 64,   //���ͷ�ת,��������ת������   
		NODE_BOOL_TO_STRING =  65,  //bool(0,1)תstring
		NODE_INT_TO_STRING  =  66,  //int(HPR_UINT32)תstring
		NODE_ARRAY_TO_STRING = 67,  //����(HPR_UINT8[],char[])תstring
		NODE_BYTE_TO_STRING = 68,   //HPR_UINT8תstring,HPR_UINT8��Ϊ����ʱ
		NODE_WORD_TO_STRING = 69 ,   //HPR_UINT16תstring
        NODE_DWORD_TO_STRING = 71,  //HPR_UINT32תstring
}XML_NODE_TYPE;

typedef enum
{
	NODE_STRING_TO_BYTE_DETECTION_TARGET = 0,    //string(detectionTarget)תBYTE(byDetectionTarget)
		
		NODE_BYTE_TO_STRING_DETECTION_TARGET = 100,  //BYTE(byDetectionTarget)תstring(detectionTarget)
}XML_STRING_NODE_TYPE;

typedef enum
{
	INTERFACE_STD_GET		= 0,
	INTERFACE_STD_SET		= 1,
	INTERFACE_STD_CTRL		= 2,
	INTERFACE_REMOTE_CONFIG =3

};
class CDlgAreaMonitorCfg : public CDialog
{
// Construction
public:
	CDlgAreaMonitorCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAreaMonitorCfg)
	enum { IDD = IDD_DLG_AREAMONITOR };
	CComboBox	m_cmbType;
	CString	m_csInputCond;
	CString	m_csConfigParam;
	CString	m_csLastError;
	CString	m_csReturnValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAreaMonitorCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAreaMonitorCfg)
	afx_msg void OnBtnSet();
	afx_msg void OnBtnProcess();
	afx_msg void OnSelchangeCmbCfgType();
	afx_msg void OnBtnDetect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG m_lUserID;
    int m_iDevIndex;
protected:
    char m_szStatusBuf[ISAPI_STATUS_LEN];
	char	*m_pOutBuf;
	DWORD	m_dwCfgType;
public:
	//void	ParseAbility();
	//void	ParseSimpleAbility(CXmlBase &xmlAll, char* szAbilityName);
	//void	ParseAbilityRecursive(CXmlBase &xmlAll, CXmlBase &xmlDev);
	BOOL    ParseAreaMonitorCond(NET_DVR_AREA_MONITOR_COND* pStruCond);
	BOOL    ConvertSingleNodeData(void *pStructVale, CXmlBase &struXml, const char* pNodeName, BYTE byDataType, DWORD nArrayLen = 0);
	BOOL	ConvertSingleNodeStringData(void *pStructVale, CXmlBase &struXml, const char* pNodeName, BYTE byDataType);
	BOOL    ParseSetAreaMonitorCond(DWORD* pData);
	BOOL    ParseSetAreaMonitorParam();
	BOOL    ParseGetStorageResourceCond(NET_DVR_STORAGE_RESOURCE_COND* pData);
	BOOL    ParseGetBlackListGroupInfoCond(NET_DVR_BLACKLIST_GROUP_COND* pData);
	BOOL    LoadRetrievalSnapRecordPicData(DWORD* dwAllDataLen, char* &pAllData);
	BOOL    LoadDetectImagePicData(DWORD* dwAllDataLen, char* &pAllData);
	DWORD  m_dwInterfaceType;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAREAMONITORCFG_H__D692C9BB_9C86_4E0B_922A_77796E59C237__INCLUDED_)
