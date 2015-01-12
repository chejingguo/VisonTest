// BTL_VISIONDlg.h : header file
//

#pragma once
#include "mscomm1.h"


// CBTL_VISIONDlg dialog
class CBTL_VISIONDlg : public CDialog
{
// Construction
public:
	CBTL_VISIONDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BTL_VISION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	int g_receive_data;
	Mat g_image;
	CMscomm1 m_Mscomm;
	void OpenMscomm(int icom);
	void SendDataTo(CString szdata);
	void CloseMscomm();
	void ReceiveDataProcess(int idata);
	void DrawPicToHDC(IplImage *img, UINT ID);
	void DrawPicToHDC(Mat img, UINT ID);
	void InitializeComponent();
	void ShowParameter();

	void CaptureImageA1();
	bool ProcessImageA1();
	bool ProcessImageA1_1();
	bool ProcessImageA1_2();
	bool ProcessImageA1_3();
	bool ProcessImageA2();
	bool ProcessImageA3_1();
	bool ProcessImageA3_2();

	void ShowMessage(int index,bool blnFlag);

public:  
	afx_msg void OnSize(UINT nType, int cx, int cy);  
	void ReSize(void);  
	POINT old;  


	int ImageStretchByHistogram(IplImage *src1,IplImage *dst1);  
	bool ProcessImageSubA1(Mat &img);

public:
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedShow();
	afx_msg void OnBnClickedA1();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedA2();
	afx_msg void OnEnChangeLightValueA1();
	afx_msg void OnBnClickedA5();
	afx_msg void OnBnClickedA6();
	afx_msg void OnBnClickedA7();
	afx_msg void OnBnClickedA8();
	afx_msg void OnClose();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedA3();
	afx_msg void OnBnClickedA4();
	afx_msg void OnBnClickedButtonSa2();
	afx_msg void OnBnClickedButtonSa3();
	afx_msg void OnBnClickedButtonSa4();
	afx_msg void OnBnClickedButtonSa5();
	afx_msg void OnBnClickedButtonSa6();
	afx_msg void OnBnClickedButtonSa7();
};
