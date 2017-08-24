#if !defined(AFX_DLGBVCALIBPARAMCFG_H__59F187A7_D556_4FFA_9DD6_79FAC18140A8__INCLUDED_)
#define AFX_DLGBVCALIBPARAMCFG_H__59F187A7_D556_4FFA_9DD6_79FAC18140A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBvCalibParamCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBvCalibParamCfg dialog

class CDlgBvCalibParamCfg : public CDialog
{
// Construction
public:
	CDlgBvCalibParamCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBvCalibParamCfg)
	enum { IDD = IDD_DLG_BV_CALIB_PARAM_CFG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBvCalibParamCfg)
	protected:
	CComboBox	m_comLensType;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBvCalibParamCfg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	LONG    m_lLoginID;
    int     m_iDevIndex;
    LONG    m_lChannel;
protected:
	BOOL    GetBvCalibParam();
    BOOL    SetBvCalibParam();

	void    LoadWndContent();
	void    SaveWndContent();
private:
	float   m_fReprojectMatrix[4][4];  

	float   m_fLCamInternalMatrix[3][3]; 
	float   m_fLDistCoeffs[8];           
	float   m_fLRotateMatrix[3][ 3];      
	float   m_fLProjectMatrix[3][4];     

	float   m_fRCamInternalMatrix[3][3]; 
	float   m_fRDistCoeffs[8];           
	float   m_fRRotateMatrix[3][ 3];      
	float   m_fRProjectMatrix[3][4]; 

	NET_DVR_BV_CORRECT_PARAM m_struBvCalibParam;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBVCALIBPARAMCFG_H__59F187A7_D556_4FFA_9DD6_79FAC18140A8__INCLUDED_)
