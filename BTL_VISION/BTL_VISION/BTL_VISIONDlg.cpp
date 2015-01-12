// BTL_VISIONDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BTL_VISION.h"
#include "BTL_VISIONDlg.h"
#include "Resource.h"

// CBTL_VISIONDlg dialog
#include "BTLFlyCapture.h"
#include "BTLImageProcess.h"
#include "Parameter.h"

#include "ColorHistogram.h"
#include "ImageComparator.h"
//

BTLFlyCapture    btlFlyCapture;
BTLImageProcess  btlImageProcess;
Parameter        parameter;

ColorHistogram colorHistogram;
ImageComparator imageComparator;
//
enum DisplayMessage{ProcessA1=1,ProcessA2=2,ProcessA3_1=3,ProcessA3_2=4,ProcessA3_3=5};
//

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBTL_VISIONDlg dialog

BEGIN_MESSAGE_MAP(CBTL_VISIONDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SHOW, &CBTL_VISIONDlg::OnBnClickedShow)
	ON_BN_CLICKED(IDC_A1, &CBTL_VISIONDlg::OnBnClickedA1)
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_A2, &CBTL_VISIONDlg::OnBnClickedA2)
ON_EN_CHANGE(IDC_LIGHT_VALUE_A1, &CBTL_VISIONDlg::OnEnChangeLightValueA1)
ON_BN_CLICKED(IDC_A5, &CBTL_VISIONDlg::OnBnClickedA5)
ON_BN_CLICKED(IDC_A6, &CBTL_VISIONDlg::OnBnClickedA6)
ON_BN_CLICKED(IDC_A7, &CBTL_VISIONDlg::OnBnClickedA7)
ON_BN_CLICKED(IDC_A8, &CBTL_VISIONDlg::OnBnClickedA8)
//ON_BN_CLICKED(IDC_BUTTON3, &CBTL_VISIONDlg::OnBnClickedButton3)
ON_WM_CLOSE()
ON_BN_CLICKED(IDC_SAVE, &CBTL_VISIONDlg::OnBnClickedSave)
ON_BN_CLICKED(IDC_A3, &CBTL_VISIONDlg::OnBnClickedA3)
ON_BN_CLICKED(IDC_A4, &CBTL_VISIONDlg::OnBnClickedA4)
ON_BN_CLICKED(IDC_BUTTON_SA2, &CBTL_VISIONDlg::OnBnClickedButtonSa2)
ON_BN_CLICKED(IDC_BUTTON_SA3, &CBTL_VISIONDlg::OnBnClickedButtonSa3)
ON_BN_CLICKED(IDC_BUTTON_SA4, &CBTL_VISIONDlg::OnBnClickedButtonSa4)
ON_BN_CLICKED(IDC_BUTTON_SA5, &CBTL_VISIONDlg::OnBnClickedButtonSa5)
ON_BN_CLICKED(IDC_BUTTON_SA6, &CBTL_VISIONDlg::OnBnClickedButtonSa6)
ON_BN_CLICKED(IDC_BUTTON_SA7, &CBTL_VISIONDlg::OnBnClickedButtonSa7)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CBTL_VISIONDlg, CDialog)
	ON_EVENT(CBTL_VISIONDlg, IDC_MSCOMM1, 1, CBTL_VISIONDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


CBTL_VISIONDlg::CBTL_VISIONDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBTL_VISIONDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


int CBTL_VISIONDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	SetTimer(TIMER1,300,0);
	//SetTimer(TIMER2,2000,0);

	return 0;
}
// CBTL_VISIONDlg message handlers

BOOL CBTL_VISIONDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitializeComponent();
	//
	OpenMscomm(2);
	//
	//此处代码  
    CRect rect;      
    GetClientRect(&rect);     //取客户区大小    
    old.x=rect.right-rect.left;  
    old.y=rect.bottom-rect.top;  
    int cx = GetSystemMetrics(SM_CXFULLSCREEN);  
    int cy = GetSystemMetrics(SM_CYFULLSCREEN);  
    CRect rt;  
    SystemParametersInfo(SPI_GETWORKAREA,0,&rt,0);  
    cy = rt.bottom;  
    MoveWindow(0, 0, cx, cy);  
	//
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBTL_VISIONDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM1, m_Mscomm);
}
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBTL_VISIONDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//
        // 给窗体添加背景
        //
        CPaintDC dc(this);
        CRect rc;
        GetClientRect(&rc);
        CDC dcMem;
        dcMem.CreateCompatibleDC(&dc);
        CBitmap bmpBackground;
        bmpBackground.LoadBitmap(IDB_BITMAP2);

        BITMAP bitmap;
        bmpBackground.GetBitmap(&bitmap);
        CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
        dc.StretchBlt(0,0,rc.Width(), rc.Height(), &dcMem,0,0,bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		CDialog::OnPaint();
	}
}

void CBTL_VISIONDlg::ReSize(void)  
{  
    float fsp[2];  
    POINT Newp; //获取现在对话框的大小  
    CRect recta;      
    GetClientRect(&recta);     //取客户区大小    
    Newp.x=recta.right-recta.left;  
    Newp.y=recta.bottom-recta.top;  
    fsp[0]=(float)Newp.x/old.x;  
    fsp[1]=(float)Newp.y/old.y;  
    CRect Rect;  
    int woc;  
    CPoint OldTLPoint,TLPoint; //左上角  
    CPoint OldBRPoint,BRPoint; //右下角  
    HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //列出所有控件    
    while(hwndChild)      
    {      
        woc=::GetDlgCtrlID(hwndChild);//取得ID  
        GetDlgItem(woc)->GetWindowRect(Rect);    
        ScreenToClient(Rect);    
        OldTLPoint = Rect.TopLeft();    
        TLPoint.x = long(OldTLPoint.x*fsp[0]);    
        TLPoint.y = long(OldTLPoint.y*fsp[1]);    
        OldBRPoint = Rect.BottomRight();    
        BRPoint.x = long(OldBRPoint.x *fsp[0]);    
        BRPoint.y = long(OldBRPoint.y *fsp[1]);    
        Rect.SetRect(TLPoint,BRPoint);    
        GetDlgItem(woc)->MoveWindow(Rect,TRUE);  
        hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);      
    }  
    old=Newp;  
}
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBTL_VISIONDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBTL_VISIONDlg::OnCommMscomm1()
{
	// TODO: Add your message handler code here
	VARIANT input1=m_Mscomm.get_Input();
	BSTR str = (BSTR)input1.pbstrVal;
	CString strData = str;
	SetDlgItemText(IDC_EDIT1,strData);

	//接收数据处理
	g_receive_data  = _ttoi(strData);

	ReceiveDataProcess(g_receive_data);
	//MessageBoxW(_T("串口1收到消息！"));
}
void CBTL_VISIONDlg::ReceiveDataProcess(int idata)
{
	
	CaptureImageA1();
	switch(idata)
	{
	case 1:
		{
			bool flagA1_1 = ProcessImageA1_1();
			bool flagA1_2 = ProcessImageA1_2();
			bool flagA1_3 = ProcessImageA1_3();
			bool flag = flagA1_1&flagA1_2&flagA1_3;
			ShowMessage(ProcessA1,flag);
			
			/*
			bool flag = ProcessImageA1();
			ShowMessage(ProcessA1,flag);
			*/
			if(flag)
				SendDataTo(_T("1"));
			else
				SendDataTo(_T("0"));
			break;
		}
	case 2:
		{
			bool flag = ProcessImageA2();
			ShowMessage(ProcessA2,flag);
			if(flag)
				SendDataTo(_T("1"));
			else
				SendDataTo(_T("0"));
			break;
		}
	case 3:
		{
			bool flagA3_1 = ProcessImageA3_1();
			bool flagA3_2 = ProcessImageA3_2();
			bool flag = flagA3_1&flagA3_2;
			ShowMessage(ProcessA3_3,flag);
			if(flag)
			if(flag)
				SendDataTo(_T("1"));
			else
				SendDataTo(_T("0"));
			break;
		}
	default:
		break;

	}
}
void CBTL_VISIONDlg::OpenMscomm(int icom)
{
	m_Mscomm.put_CommPort(icom);
	m_Mscomm.put_InputMode(0);
	m_Mscomm.put_Settings(_T("9600,n,8,1"));
	m_Mscomm.put_RThreshold(1);
	m_Mscomm.put_InputLen(0);
	if(!m_Mscomm.get_PortOpen())
	{
		m_Mscomm.put_PortOpen(true);
		//MessageBoxW(_T("打开串口1成功！"));
	}
	else
	{
		MessageBoxW(_T("打开串口1失败！"));
	}
}
void CBTL_VISIONDlg::SendDataTo(CString szdata)
{
	int i,Count;
	Count = szdata.GetLength();
	CByteArray m_Array;
	m_Array.RemoveAll();
	m_Array.SetSize(Count);
	for(i=0;i<Count;i++)
	{
		m_Array.SetAt(i,szdata[i]);
	}
	m_Mscomm.put_Output(COleVariant(m_Array));
}
void CBTL_VISIONDlg::CloseMscomm()
{
	m_Mscomm.put_PortOpen(false);
}


void CBTL_VISIONDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case TIMER1:
	{ 
		//AfxMessageBox(_T("定时器1!"));
		//从摄像机获取图像
		Mat img =btlFlyCapture.flyCapColor();

		CString strTopA1,strLeftA1,strHighA1,strWideA1;

		GetDlgItemText(IDC_TOP_VALUE_A1,strTopA1);
		GetDlgItemText(IDC_LEFT_VALUE_A1,strLeftA1);
		GetDlgItemText(IDC_HIGH_VALUE_A1,strHighA1);
		GetDlgItemText(IDC_WIDE_VALUE_A1,strWideA1);
		int iTopA1  = _ttoi(strTopA1);
		int iLeftA1 = _ttoi(strLeftA1);
		int iHighA1 = _ttoi(strHighA1);
		int iWideA1 = _ttoi(strWideA1);
		rectangle(img,Point( iLeftA1,iTopA1),Point(iLeftA1+iWideA1,iTopA1+iHighA1),Scalar( 0,255,0),2,8,0); 
		if(img.empty())
			return;
		else
			DrawPicToHDC(img, IDC_IMG);
		break;
	}
	case TIMER2:
	{ 
		 //AfxMessageBox(_T("定时器2!"));
		 break;
	}
	default:
		 break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CBTL_VISIONDlg::OnBnClickedA1()
{
	// TODO: Add your control notification handler code here
	CaptureImageA1();
}
void CBTL_VISIONDlg::CaptureImageA1()
{
	CString strTop,strLeft,strHigh,strWide;

	GetDlgItemText(IDC_TOP_VALUE_A1,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A1,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A1,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A1,strWide);
	int iTop  = _ttoi(strTop);
	int iLeft = _ttoi(strLeft);
	int iHigh = _ttoi(strHigh);
	int iWide = _ttoi(strWide);

	Mat img =btlFlyCapture.flyCapColor();
	//
	//g_image=cv::imread("1.bmp");
	//img=cv::imread("1.bmp");
	//
	if(img.empty())
		return;
	else
	{
		g_image = img(Rect(iLeft,iTop,iWide,iHigh));
		DrawPicToHDC(g_image,IDC_IMG_ROI);
	}

}
void CBTL_VISIONDlg::OnBnClickedA2()
{
	// TODO: Add your control notification handler code here
	bool flag =ProcessImageA1_1();
	ShowMessage(ProcessA1,flag);

	//bool flag = ProcessImageA1();
	//ShowMessage(ProcessA1,flag);
}
bool CBTL_VISIONDlg::ProcessImageA1()
{
	CString strTop,strLeft,strHigh,strWide;//,strStartRange,strEndRange;

	GetDlgItemText(IDC_TOP_VALUE_A2,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A2,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A2,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A2,strWide);
	//GetDlgItemText(IDC_RANGE_VALUE1_A2,strStartRange);
	//GetDlgItemText(IDC_RANGE_VALUE2_A2,strEndRange);
	int iTop  = _ttoi(strTop);
	int iLeft = _ttoi(strLeft);
	int iHigh = _ttoi(strHigh);
	int iWide = _ttoi(strWide);
	//int iStartRange = _ttoi(strStartRange);
	//int iEndRange = _ttoi(strEndRange);

	Mat img_roi;
	//
	if(g_image.empty())
		return false;
	else
	{
		
		rectangle(g_image,Point( iLeft,iTop),Point(iLeft+iWide,iTop+iHigh),Scalar( 0,255,0 ),2,8,0); 

		DrawPicToHDC(g_image,IDC_IMG_ROI);

		img_roi = g_image(Rect(iLeft,iTop,iWide,iHigh));
		DrawPicToHDC(img_roi,IDC_IMG_ROI2);

		bool IsGood = ProcessImageSubA1(img_roi);
		//btlImageProcess.modifyAvgValue(img_roi,btlImageProcess.getImageAvgValue(img_roi));
		//DrawPicToHDC(img_roi,IDC_IMG_ROI2);
		return IsGood;

	}
}
bool CBTL_VISIONDlg::ProcessImageSubA1(Mat &img)
{
	std::vector<Mat>  mv;
	split(img, mv);
	//imshow("RGB",img);
	//imshow("B",mv[0]);
	//imshow("G",mv[1]);
	//imshow("R",mv[2]);
	//Mat gray;
	//cv::cvtColor(img,gray,::CV_BGR2GRAY);
	//imshow("gray",mat1);

	Mat matFliter;
	::GaussianBlur(mv[1],matFliter,cv::Size(5,5),1.5);//
	//imshow("G",mv[1]);
	//imshow("matFliter",matFliter);

	Mat matHist;
	cv::equalizeHist(matFliter,matHist);
	//imshow("matFliter",matHist);
	//ImageStretchByHistogram(matFliter,matFliter);//直方图增强

	Mat matBinary;
	cv::threshold(matHist,matBinary,220,255,cv::THRESH_BINARY);
	//imshow("matBinary",matBinary);

	Mat materoded;
	cv::erode(matBinary,materoded,Mat());
	//Mat matopened;
	//cv::Mat element3(3,3,CV_8U,cv::Scalar(1));
	//cv::morphologyEx(matBinary,matopened,cv::MORPH_OPEN,element3);

	std::vector<std::vector<cv::Point>>contours;

	cv::findContours(materoded,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);


	int cmin =30;
	int cmax =500;
	int iContours=0;
	std::vector<std::vector<cv::Point>>::const_iterator itc = contours.begin();
	while(itc!=contours.end())
	{
		if(itc->size()<cmin||itc->size()>cmax)
			itc = contours.erase(itc);
		else
		{
			++itc;
			iContours++;
		}
	}

	cv::Mat result(matBinary.size(),CV_8U,cv::Scalar(255));

	cv::drawContours(result,contours,-1,cv::Scalar(0),2);
	//imshow("result",result);
	DrawPicToHDC(result,IDC_IMG_ROI3);

	if(iContours==3)
		return true;
	else
		return false;
}
bool CBTL_VISIONDlg::ProcessImageA1_1()
{
	CString strTop,strLeft,strHigh,strWide,strStartRange,strEndRange;

	GetDlgItemText(IDC_TOP_VALUE_A2,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A2,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A2,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A2,strWide);
	GetDlgItemText(IDC_RANGE_VALUE1_A2,strStartRange);
	GetDlgItemText(IDC_RANGE_VALUE2_A2,strEndRange);
	int iTop  = _ttoi(strTop);
	int iLeft = _ttoi(strLeft);
	int iHigh = _ttoi(strHigh);
	int iWide = _ttoi(strWide);
	int iStartRange = _ttoi(strStartRange);
	int iEndRange = _ttoi(strEndRange);

	Mat img_roi;
	Mat refImg = cv::imread("imgA1_1.bmp");
	//
	if(g_image.empty())
		return 0;
	else
	{
		img_roi = g_image(Rect(iLeft,iTop,iWide,iHigh));
		//
		rectangle(g_image,Point( iLeft,iTop),Point(iLeft+iWide,iTop+iHigh),Scalar( 0,255,0 ),2,8,0); 

		DrawPicToHDC(g_image,IDC_IMG_ROI);

		DrawPicToHDC(refImg,IDC_IMG_ROI2);

		DrawPicToHDC(img_roi,IDC_IMG_ROI3);
	}
	//
	//图像颜色降维
	refImg=colorHistogram.colorReduce(refImg,64);
	img_roi=colorHistogram.colorReduce(img_roi,64);
	MatND refH=colorHistogram.getHistogram(refImg);
	MatND hist1=colorHistogram.getHistogram(img_roi);
	double resultValue;
	resultValue=compareHist(refH,hist1,::CV_COMP_CORREL)*255;

	CString strResult;
	strResult.Format(_T("%f"),resultValue); 
	SetDlgItemText(IDC_RESULT_VALUE_A2,strResult);

	if((iStartRange<=resultValue)&&(resultValue<=iEndRange))
	{
		SetDlgItemText(IDC_FLAG,_T("合格"));
		return 1;
	}
	else
	{
		SetDlgItemText(IDC_FLAG,_T("不合格"));
		return 0;
	}
}

void CBTL_VISIONDlg::OnBnClickedA3()
{
	// TODO: Add your control notification handler code here
	bool flag =ProcessImageA1_2();
	ShowMessage(ProcessA1,flag);
}
//A1_2
bool CBTL_VISIONDlg::ProcessImageA1_2()
{
	CString strTop,strLeft,strHigh,strWide,strStartRange,strEndRange;

	GetDlgItemText(IDC_TOP_VALUE_A3,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A3,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A3,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A3,strWide);
	GetDlgItemText(IDC_RANGE_VALUE1_A3,strStartRange);
	GetDlgItemText(IDC_RANGE_VALUE2_A3,strEndRange);
	int iTop  = _ttoi(strTop);
	int iLeft = _ttoi(strLeft);
	int iHigh = _ttoi(strHigh);
	int iWide = _ttoi(strWide);
	int iStartRange = _ttoi(strStartRange);
	int iEndRange = _ttoi(strEndRange);

	Mat img_roi;
	Mat refImg = cv::imread("imgA1_2.bmp");
	//
	if(g_image.empty())
		return 0;
	else
	{
		img_roi = g_image(Rect(iLeft,iTop,iWide,iHigh));
		//
		rectangle(g_image,Point( iLeft,iTop),Point(iLeft+iWide,iTop+iHigh),Scalar( 0,255,0 ),2,8,0); 

		DrawPicToHDC(g_image,IDC_IMG_ROI);

		DrawPicToHDC(refImg,IDC_IMG_ROI2);

		DrawPicToHDC(img_roi,IDC_IMG_ROI3);
	}
	//
	//图像颜色降维
	refImg=colorHistogram.colorReduce(refImg,64);
	img_roi=colorHistogram.colorReduce(img_roi,64);
	MatND refH=colorHistogram.getHistogram(refImg);
	MatND hist1=colorHistogram.getHistogram(img_roi);
	double resultValue;
	resultValue=compareHist(refH,hist1,::CV_COMP_CORREL)*255;

	CString strResult;
	strResult.Format(_T("%f"),resultValue); 
	SetDlgItemText(IDC_RESULT_VALUE_A3,strResult);

	if((iStartRange<=resultValue)&&(resultValue<=iEndRange))
	{
		SetDlgItemText(IDC_FLAG,_T("合格"));
		return 1;
	}
	else
	{
		SetDlgItemText(IDC_FLAG,_T("不合格"));
		return 0;
	}
}
void CBTL_VISIONDlg::OnBnClickedA4()
{
	// TODO: Add your control notification handler code here
	bool flag =ProcessImageA1_3();
	ShowMessage(ProcessA1,flag);
}
//A1_2
bool CBTL_VISIONDlg::ProcessImageA1_3()
{
	CString strTop,strLeft,strHigh,strWide,strStartRange,strEndRange;

	GetDlgItemText(IDC_TOP_VALUE_A4,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A4,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A4,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A4,strWide);
	GetDlgItemText(IDC_RANGE_VALUE1_A4,strStartRange);
	GetDlgItemText(IDC_RANGE_VALUE2_A4,strEndRange);
	int iTop  = _ttoi(strTop);
	int iLeft = _ttoi(strLeft);
	int iHigh = _ttoi(strHigh);
	int iWide = _ttoi(strWide);
	int iStartRange = _ttoi(strStartRange);
	int iEndRange = _ttoi(strEndRange);

	Mat img_roi;
	Mat refImg = cv::imread("imgA1_3.bmp");
	//
	if(g_image.empty())
		return 0;
	else
	{
		img_roi = g_image(Rect(iLeft,iTop,iWide,iHigh));
		//
		rectangle(g_image,Point( iLeft,iTop),Point(iLeft+iWide,iTop+iHigh),Scalar( 0,255,0 ),2,8,0); 

		DrawPicToHDC(g_image,IDC_IMG_ROI);

		DrawPicToHDC(refImg,IDC_IMG_ROI2);

		DrawPicToHDC(img_roi,IDC_IMG_ROI3);
	}
	//
	//图像颜色降维
	refImg=colorHistogram.colorReduce(refImg,64);
	img_roi=colorHistogram.colorReduce(img_roi,64);
	MatND refH=colorHistogram.getHistogram(refImg);
	MatND hist1=colorHistogram.getHistogram(img_roi);
	double resultValue;
	resultValue=compareHist(refH,hist1,::CV_COMP_CORREL)*255;

	CString strResult;
	strResult.Format(_T("%f"),resultValue); 
	SetDlgItemText(IDC_RESULT_VALUE_A4,strResult);

	if((iStartRange<=resultValue)&&(resultValue<=iEndRange))
	{
		SetDlgItemText(IDC_FLAG,_T("合格"));
		return 1;
	}
	else
	{
		SetDlgItemText(IDC_FLAG,_T("不合格"));
		return 0;
	}
}

void CBTL_VISIONDlg::OnBnClickedA5()
{
	// TODO: Add your control notification handler code here
	bool flag =ProcessImageA2();
	ShowMessage(ProcessA2,flag);
}

bool CBTL_VISIONDlg::ProcessImageA2()
{
	CString strTop,strLeft,strHigh,strWide,strStartRange,strEndRange;

	GetDlgItemText(IDC_TOP_VALUE_A5,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A5,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A5,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A5,strWide);
	GetDlgItemText(IDC_RANGE_VALUE1_A5,strStartRange);
	GetDlgItemText(IDC_RANGE_VALUE2_A5,strEndRange);
	int iTop  = _ttoi(strTop);
	int iLeft = _ttoi(strLeft);
	int iHigh = _ttoi(strHigh);
	int iWide = _ttoi(strWide);
	int iStartRange = _ttoi(strStartRange);
	int iEndRange = _ttoi(strEndRange);

	Mat img_roi;
	Mat refImg = cv::imread("imgA2_0.bmp");
	//
	if(g_image.empty())
		return 0;
	else
	{
		img_roi = g_image(Rect(iLeft,iTop,iWide,iHigh));
		//
		rectangle(g_image,Point( iLeft,iTop),Point(iLeft+iWide,iTop+iHigh),Scalar( 0,255,0 ),2,8,0); 

		DrawPicToHDC(g_image,IDC_IMG_ROI);

		DrawPicToHDC(refImg,IDC_IMG_ROI2);

		DrawPicToHDC(img_roi,IDC_IMG_ROI3);
	}
	//
	//图像颜色降维
	refImg=colorHistogram.colorReduce(refImg,64);
	img_roi=colorHistogram.colorReduce(img_roi,64);
	MatND refH=colorHistogram.getHistogram(refImg);
	MatND hist1=colorHistogram.getHistogram(img_roi);
	double resultValue;
	resultValue=compareHist(refH,hist1,::CV_COMP_CORREL)*255;

	CString strResult;
	strResult.Format(_T("%f"),resultValue); 
	SetDlgItemText(IDC_RESULT_VALUE_A5,strResult);

	if((iStartRange<=resultValue)&&(resultValue<=iEndRange))
	{
		SetDlgItemText(IDC_FLAG,_T("合格"));
		return 1;
	}
	else
	{
		SetDlgItemText(IDC_FLAG,_T("不合格"));
		return 0;
	}
}

void CBTL_VISIONDlg::OnBnClickedA6()
{
	// TODO: Add your control notification handler code here
	bool flag =ProcessImageA3_1();
	ShowMessage(ProcessA3_1,flag);
}
//A1_2
bool CBTL_VISIONDlg::ProcessImageA3_1()
{
	CString strTop,strLeft,strHigh,strWide,strStartRange,strEndRange;

	GetDlgItemText(IDC_TOP_VALUE_A6,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A6,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A6,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A6,strWide);
	GetDlgItemText(IDC_RANGE_VALUE1_A6,strStartRange);
	GetDlgItemText(IDC_RANGE_VALUE2_A6,strEndRange);
	int iTop  = _ttoi(strTop);
	int iLeft = _ttoi(strLeft);
	int iHigh = _ttoi(strHigh);
	int iWide = _ttoi(strWide);
	int iStartRange = _ttoi(strStartRange);
	int iEndRange = _ttoi(strEndRange);

	Mat img_roi;
	Mat refImg = cv::imread("imgA3_1.bmp");
	//
	if(g_image.empty())
		return 0;
	else
	{
		img_roi = g_image(Rect(iLeft,iTop,iWide,iHigh));
		//
		rectangle(g_image,Point( iLeft,iTop),Point(iLeft+iWide,iTop+iHigh),Scalar( 0,255,0 ),2,8,0); 

		DrawPicToHDC(g_image,IDC_IMG_ROI);

		DrawPicToHDC(refImg,IDC_IMG_ROI2);

		DrawPicToHDC(img_roi,IDC_IMG_ROI3);
	}
	//
	//图像颜色降维
	refImg=colorHistogram.colorReduce(refImg,64);
	img_roi=colorHistogram.colorReduce(img_roi,64);
	MatND refH=colorHistogram.getHistogram(refImg);
	MatND hist1=colorHistogram.getHistogram(img_roi);
	double resultValue;
	resultValue=compareHist(refH,hist1,::CV_COMP_CORREL)*255;

	CString strResult;
	strResult.Format(_T("%f"),resultValue); 
	SetDlgItemText(IDC_RESULT_VALUE_A6,strResult);

	if((iStartRange<=resultValue)&&(resultValue<=iEndRange))
	{
		SetDlgItemText(IDC_FLAG,_T("合格"));
		return 1;
	}
	else
	{
		SetDlgItemText(IDC_FLAG,_T("不合格"));
		return 0;
	}
}
void CBTL_VISIONDlg::OnBnClickedA7()
{
	// TODO: Add your control notification handler code here
	bool flag =ProcessImageA3_2();
	ShowMessage(ProcessA3_2,flag);
}
//A1_2
bool CBTL_VISIONDlg::ProcessImageA3_2()
{
	CString strTop,strLeft,strHigh,strWide,strStartRange,strEndRange;

	GetDlgItemText(IDC_TOP_VALUE_A7,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A7,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A7,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A7,strWide);
	GetDlgItemText(IDC_RANGE_VALUE1_A7,strStartRange);
	GetDlgItemText(IDC_RANGE_VALUE2_A7,strEndRange);
	int iTop  = _ttoi(strTop);
	int iLeft = _ttoi(strLeft);
	int iHigh = _ttoi(strHigh);
	int iWide = _ttoi(strWide);
	int iStartRange = _ttoi(strStartRange);
	int iEndRange = _ttoi(strEndRange);

	Mat img_roi;
	Mat refImg = cv::imread("imgA3_2.bmp");
	//
	if(g_image.empty())
		return 0;
	else
	{
		img_roi = g_image(Rect(iLeft,iTop,iWide,iHigh));
		//
		rectangle(g_image,Point( iLeft,iTop),Point(iLeft+iWide,iTop+iHigh),Scalar( 0,255,0 ),2,8,0); 

		DrawPicToHDC(g_image,IDC_IMG_ROI);

		DrawPicToHDC(refImg,IDC_IMG_ROI2);

		DrawPicToHDC(img_roi,IDC_IMG_ROI3);
	}
	//
	//图像颜色降维
	refImg=colorHistogram.colorReduce(refImg,64);
	img_roi=colorHistogram.colorReduce(img_roi,64);
	MatND refH=colorHistogram.getHistogram(refImg);
	MatND hist1=colorHistogram.getHistogram(img_roi);
	double resultValue;
	resultValue=compareHist(refH,hist1,::CV_COMP_CORREL)*255;

	CString strResult;
	strResult.Format(_T("%f"),resultValue); 
	SetDlgItemText(IDC_RESULT_VALUE_A7,strResult);

	if((iStartRange<=resultValue)&&(resultValue<=iEndRange))
	{
		SetDlgItemText(IDC_FLAG,_T("合格"));
		return 1;
	}
	else
	{
		SetDlgItemText(IDC_FLAG,_T("不合格"));
		return 0;
	}
}

void CBTL_VISIONDlg::OnBnClickedA8()
{
	// TODO: Add your control notification handler code here
	bool flag=0;
	flag =ProcessImageA3_1();
	ShowMessage(ProcessA3_1,flag);

	flag =ProcessImageA3_2();
	ShowMessage(ProcessA3_2,flag);
}
void CBTL_VISIONDlg::OnBnClickedShow()
{
	// TODO: Add your control notification handler code here
	ShowParameter();
}
void CBTL_VISIONDlg::ShowParameter()
{
	// TODO: Add your control notification handler code here
	CWnd* pWnd = GetDlgItem(IDC_IMG_PAR);

	//判断控件窗口是否可见
	if (pWnd->IsWindowVisible())	
	{
		//
		SetDlgItemText(IDC_SHOW, _T("SHOW"));
		//隐藏控件窗口
		pWnd->ShowWindow(SW_HIDE);
		//A1
		GetDlgItem(IDC_TOP_A1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LEFT_A1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TOP_VALUE_A1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LEFT_VALUE_A1)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_HIGH_A1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_WIDE_A1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_HIGH_VALUE_A1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_WIDE_VALUE_A1)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_LIGHT_A1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LIGHT_VALUE_A1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESULT_A1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESULT_VALUE_A1)->ShowWindow(SW_HIDE);
		//A2
		GetDlgItem(IDC_TOP_A2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LEFT_A2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TOP_VALUE_A2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LEFT_VALUE_A2)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_HIGH_A2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_WIDE_A2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_HIGH_VALUE_A2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_WIDE_VALUE_A2)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_RANGE_A2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESULT_A2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RANGE_VALUE1_A2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RANGE_VALUE2_A2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESULT_VALUE_A2)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUTTON_SA2)->ShowWindow(SW_HIDE);
		//A3
		GetDlgItem(IDC_TOP_A3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LEFT_A3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TOP_VALUE_A3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LEFT_VALUE_A3)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_HIGH_A3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_WIDE_A3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_HIGH_VALUE_A3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_WIDE_VALUE_A3)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_RANGE_A3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESULT_A3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RANGE_VALUE1_A3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RANGE_VALUE2_A3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESULT_VALUE_A3)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUTTON_SA3)->ShowWindow(SW_HIDE);
		//A4
		GetDlgItem(IDC_TOP_A4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LEFT_A4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TOP_VALUE_A4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LEFT_VALUE_A4)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_HIGH_A4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_WIDE_A4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_HIGH_VALUE_A4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_WIDE_VALUE_A4)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_RANGE_A4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESULT_A4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RANGE_VALUE1_A4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RANGE_VALUE2_A4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESULT_VALUE_A4)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUTTON_SA4)->ShowWindow(SW_HIDE);
		//A5
		GetDlgItem(IDC_TOP_A5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LEFT_A5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TOP_VALUE_A5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LEFT_VALUE_A5)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_HIGH_A5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_WIDE_A5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_HIGH_VALUE_A5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_WIDE_VALUE_A5)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_RANGE_A5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESULT_A5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RANGE_VALUE1_A5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RANGE_VALUE2_A5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESULT_VALUE_A5)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUTTON_SA5)->ShowWindow(SW_HIDE);

		//A6
		GetDlgItem(IDC_TOP_A6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LEFT_A6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TOP_VALUE_A6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LEFT_VALUE_A6)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_HIGH_A6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_WIDE_A6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_HIGH_VALUE_A6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_WIDE_VALUE_A6)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_RANGE_A6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESULT_A6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RANGE_VALUE1_A6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RANGE_VALUE2_A6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESULT_VALUE_A6)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUTTON_SA6)->ShowWindow(SW_HIDE);

		//A7
		GetDlgItem(IDC_TOP_A7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LEFT_A7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TOP_VALUE_A7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LEFT_VALUE_A7)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_HIGH_A7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_WIDE_A7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_HIGH_VALUE_A7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_WIDE_VALUE_A7)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_RANGE_A7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESULT_A7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RANGE_VALUE1_A7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RANGE_VALUE2_A7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RESULT_VALUE_A7)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUTTON_SA7)->ShowWindow(SW_HIDE);
		
	}
	else
	{
		//
		SetDlgItemText(IDC_SHOW, _T("HIDE"));
		//显示控件窗口
		pWnd->ShowWindow(SW_SHOW);
		//A1
		GetDlgItem(IDC_TOP_A1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LEFT_A1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TOP_VALUE_A1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LEFT_VALUE_A1)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_HIGH_A1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_WIDE_A1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_HIGH_VALUE_A1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_WIDE_VALUE_A1)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_LIGHT_A1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LIGHT_VALUE_A1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RESULT_A1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RESULT_VALUE_A1)->ShowWindow(SW_SHOW);
		//A2
		GetDlgItem(IDC_TOP_A2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LEFT_A2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TOP_VALUE_A2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LEFT_VALUE_A2)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_HIGH_A2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_WIDE_A2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_HIGH_VALUE_A2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_WIDE_VALUE_A2)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_RANGE_A2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RESULT_A2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RANGE_VALUE1_A2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RANGE_VALUE2_A2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RESULT_VALUE_A2)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BUTTON_SA2)->ShowWindow(SW_SHOW);
		//A3
		GetDlgItem(IDC_TOP_A3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LEFT_A3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TOP_VALUE_A3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LEFT_VALUE_A3)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_HIGH_A3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_WIDE_A3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_HIGH_VALUE_A3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_WIDE_VALUE_A3)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_RANGE_A3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RESULT_A3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RANGE_VALUE1_A3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RANGE_VALUE2_A3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RESULT_VALUE_A3)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BUTTON_SA3)->ShowWindow(SW_SHOW);
		//A4
		GetDlgItem(IDC_TOP_A4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LEFT_A4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TOP_VALUE_A4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LEFT_VALUE_A4)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_HIGH_A4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_WIDE_A4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_HIGH_VALUE_A4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_WIDE_VALUE_A4)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_RANGE_A4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RESULT_A4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RANGE_VALUE1_A4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RANGE_VALUE2_A4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RESULT_VALUE_A4)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BUTTON_SA4)->ShowWindow(SW_SHOW);
		//A5
		GetDlgItem(IDC_TOP_A5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LEFT_A5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TOP_VALUE_A5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LEFT_VALUE_A5)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_HIGH_A5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_WIDE_A5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_HIGH_VALUE_A5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_WIDE_VALUE_A5)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_RANGE_A5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RESULT_A5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RANGE_VALUE1_A5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RANGE_VALUE2_A5)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RESULT_VALUE_A5)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BUTTON_SA5)->ShowWindow(SW_SHOW);

		//A6
		GetDlgItem(IDC_TOP_A6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LEFT_A6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TOP_VALUE_A6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LEFT_VALUE_A6)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_HIGH_A6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_WIDE_A6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_HIGH_VALUE_A6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_WIDE_VALUE_A6)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_RANGE_A6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RESULT_A6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RANGE_VALUE1_A6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RANGE_VALUE2_A6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RESULT_VALUE_A6)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BUTTON_SA6)->ShowWindow(SW_SHOW);

		//A7
		GetDlgItem(IDC_TOP_A7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LEFT_A7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TOP_VALUE_A7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LEFT_VALUE_A7)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_HIGH_A7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_WIDE_A7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_HIGH_VALUE_A7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_WIDE_VALUE_A7)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_RANGE_A7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RESULT_A7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RANGE_VALUE1_A7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RANGE_VALUE2_A7)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RESULT_VALUE_A7)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BUTTON_SA7)->ShowWindow(SW_SHOW);

		//SetDlgItemText(IDC_TOP_A1, _T("隐藏控件"));
	}

}

void CBTL_VISIONDlg::InitializeComponent()
{
	// TODO: Add your message handler code here and/or call default

	CString strLeft,strTop,strHigh,strWide,strStartRange,strEndRange,strLight;
	GetPrivateProfileStringW(_T("A1"),_T("x"),_T("0") ,strLeft.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A1"),_T("y"),_T("0") ,strTop.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A1"),_T("high"),_T("0") ,strHigh.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A1"),_T("wide"),_T("0") ,strWide.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));

	GetPrivateProfileStringW(_T("A1"),_T("light"),_T("0") ,strLight.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	//A1
	SetDlgItemText(IDC_TOP_A1,_T("A1 Top:"));
	SetDlgItemText(IDC_LEFT_A1,_T("A1 Left:"));
	SetDlgItemText(IDC_TOP_VALUE_A1,strTop);
	SetDlgItemText(IDC_LEFT_VALUE_A1,strLeft);

	SetDlgItemText(IDC_HIGH_A1,_T("High:"));
	SetDlgItemText(IDC_WIDE_A1,_T("Wide:"));
	SetDlgItemText(IDC_HIGH_VALUE_A1,strHigh);
	SetDlgItemText(IDC_WIDE_VALUE_A1,strWide);

	SetDlgItemText(IDC_LIGHT_A1,_T("Light:"));
	SetDlgItemText(IDC_LIGHT_VALUE_A1,strLight);


	//A2
	GetPrivateProfileStringW(_T("A2"),_T("x"),_T("0") ,strLeft.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A2"),_T("y"),_T("0") ,strTop.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A2"),_T("high"),_T("0") ,strHigh.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A2"),_T("wide"),_T("0") ,strWide.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A2"),_T("startRange"),_T("0") ,strStartRange.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A2"),_T("endRange"),_T("255") ,strEndRange.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));

	SetDlgItemText(IDC_TOP_A2,_T("A2 Top:"));
	SetDlgItemText(IDC_LEFT_A2,_T("A2 Left:"));
	SetDlgItemText(IDC_TOP_VALUE_A2,strTop);
	SetDlgItemText(IDC_LEFT_VALUE_A2,strLeft);

	SetDlgItemText(IDC_HIGH_A2,_T("High:"));
	SetDlgItemText(IDC_WIDE_A2,_T("Wide:"));
	SetDlgItemText(IDC_HIGH_VALUE_A2,strHigh);
	SetDlgItemText(IDC_WIDE_VALUE_A2,strWide);

	SetDlgItemText(IDC_RANGE_A2,_T("Range:"));
	SetDlgItemText(IDC_RESULT_A2,_T("Result:"));
	SetDlgItemText(IDC_RANGE_VALUE1_A2,strStartRange);
	SetDlgItemText(IDC_RANGE_VALUE2_A2,strEndRange);


	//A3
	GetPrivateProfileStringW(_T("A3"),_T("x"),_T("0") ,strLeft.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A3"),_T("y"),_T("0") ,strTop.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A3"),_T("high"),_T("0") ,strHigh.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A3"),_T("wide"),_T("0") ,strWide.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A3"),_T("startRange"),_T("0") ,strStartRange.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A3"),_T("endRange"),_T("255") ,strEndRange.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));

	SetDlgItemText(IDC_TOP_A3,_T("A3 Top:"));
	SetDlgItemText(IDC_LEFT_A3,_T("A3 Left:"));
	SetDlgItemText(IDC_TOP_VALUE_A3,strTop);
	SetDlgItemText(IDC_LEFT_VALUE_A3,strLeft);

	SetDlgItemText(IDC_HIGH_A3,_T("High:"));
	SetDlgItemText(IDC_WIDE_A3,_T("Wide:"));
	SetDlgItemText(IDC_HIGH_VALUE_A3,strHigh);
	SetDlgItemText(IDC_WIDE_VALUE_A3,strWide);

	SetDlgItemText(IDC_RANGE_A3,_T("Range:"));
	SetDlgItemText(IDC_RESULT_A3,_T("Result:"));
	SetDlgItemText(IDC_RANGE_VALUE1_A3,strStartRange);
	SetDlgItemText(IDC_RANGE_VALUE2_A3,strEndRange);


	//A4
	GetPrivateProfileStringW(_T("A4"),_T("x"),_T("0") ,strLeft.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A4"),_T("y"),_T("0") ,strTop.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A4"),_T("high"),_T("0") ,strHigh.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A4"),_T("wide"),_T("0") ,strWide.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A4"),_T("startRange"),_T("0") ,strStartRange.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A4"),_T("endRange"),_T("255") ,strEndRange.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	SetDlgItemText(IDC_TOP_A4,_T("A4 Top:"));
	SetDlgItemText(IDC_LEFT_A4,_T("A4 Left:"));
	SetDlgItemText(IDC_TOP_VALUE_A4,strTop);
	SetDlgItemText(IDC_LEFT_VALUE_A4,strLeft);

	SetDlgItemText(IDC_HIGH_A4,_T("High:"));
	SetDlgItemText(IDC_WIDE_A4,_T("Wide:"));
	SetDlgItemText(IDC_HIGH_VALUE_A4,strHigh);
	SetDlgItemText(IDC_WIDE_VALUE_A4,strWide);

	SetDlgItemText(IDC_RANGE_A4,_T("Range:"));
	SetDlgItemText(IDC_RESULT_A4,_T("Result:"));
	SetDlgItemText(IDC_RANGE_VALUE1_A4,strStartRange);
	SetDlgItemText(IDC_RANGE_VALUE2_A4,strEndRange);

	//A5
	GetPrivateProfileStringW(_T("A5"),_T("x"),_T("0") ,strLeft.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A5"),_T("y"),_T("0") ,strTop.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A5"),_T("high"),_T("0") ,strHigh.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A5"),_T("wide"),_T("0") ,strWide.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A5"),_T("startRange"),_T("0") ,strStartRange.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A5"),_T("endRange"),_T("255") ,strEndRange.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	SetDlgItemText(IDC_TOP_A5,_T("A5 Top:"));
	SetDlgItemText(IDC_LEFT_A5,_T("A5 Left:"));
	SetDlgItemText(IDC_TOP_VALUE_A5,strTop);
	SetDlgItemText(IDC_LEFT_VALUE_A5,strLeft);

	SetDlgItemText(IDC_HIGH_A5,_T("High:"));
	SetDlgItemText(IDC_WIDE_A5,_T("Wide:"));
	SetDlgItemText(IDC_HIGH_VALUE_A5,strHigh);
	SetDlgItemText(IDC_WIDE_VALUE_A5,strWide);

	SetDlgItemText(IDC_RANGE_A5,_T("Range:"));
	SetDlgItemText(IDC_RESULT_A5,_T("Result:"));
	SetDlgItemText(IDC_RANGE_VALUE1_A5,strStartRange);
	SetDlgItemText(IDC_RANGE_VALUE2_A5,strEndRange);


	//A6
	GetPrivateProfileStringW(_T("A6"),_T("x"),_T("0") ,strLeft.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A6"),_T("y"),_T("0") ,strTop.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A6"),_T("high"),_T("0") ,strHigh.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A6"),_T("wide"),_T("0") ,strWide.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A6"),_T("startRange"),_T("0") ,strStartRange.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A6"),_T("endRange"),_T("255") ,strEndRange.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	SetDlgItemText(IDC_TOP_A6,_T("A6 Top:"));
	SetDlgItemText(IDC_LEFT_A6,_T("A6 Left:"));
	SetDlgItemText(IDC_TOP_VALUE_A6,strTop);
	SetDlgItemText(IDC_LEFT_VALUE_A6,strLeft);

	SetDlgItemText(IDC_HIGH_A6,_T("High:"));
	SetDlgItemText(IDC_WIDE_A6,_T("Wide:"));
	SetDlgItemText(IDC_HIGH_VALUE_A6,strHigh);
	SetDlgItemText(IDC_WIDE_VALUE_A6,strWide);

	SetDlgItemText(IDC_RANGE_A6,_T("Range:"));
	SetDlgItemText(IDC_RESULT_A6,_T("Result:"));
	SetDlgItemText(IDC_RANGE_VALUE1_A6,strStartRange);
	SetDlgItemText(IDC_RANGE_VALUE2_A6,strEndRange);


	//A7
	GetPrivateProfileStringW(_T("A7"),_T("x"),_T("0") ,strLeft.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A7"),_T("y"),_T("0") ,strTop.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A7"),_T("high"),_T("0") ,strHigh.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A7"),_T("wide"),_T("0") ,strWide.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A7"),_T("startRange"),_T("0") ,strStartRange.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	GetPrivateProfileStringW(_T("A7"),_T("endRange"),_T("255") ,strEndRange.GetBuffer(MAX_PATH),MAX_PATH,_T("c:\\Windows\\vision.ini"));
	SetDlgItemText(IDC_TOP_A7,_T("A7 Top:"));
	SetDlgItemText(IDC_LEFT_A7,_T("A7 Left:"));
	SetDlgItemText(IDC_TOP_VALUE_A7,strTop);
	SetDlgItemText(IDC_LEFT_VALUE_A7,strLeft);

	SetDlgItemText(IDC_HIGH_A7,_T("High:"));
	SetDlgItemText(IDC_WIDE_A7,_T("Wide:"));
	SetDlgItemText(IDC_HIGH_VALUE_A7,strHigh);
	SetDlgItemText(IDC_WIDE_VALUE_A7,strWide);

	SetDlgItemText(IDC_RANGE_A7,_T("Range:"));
	SetDlgItemText(IDC_RESULT_A7,_T("Result:"));
	SetDlgItemText(IDC_RANGE_VALUE1_A7,strStartRange);
	SetDlgItemText(IDC_RANGE_VALUE2_A7,strEndRange);


	/*
	int nTop   = 0; 
	int nLeft  = 0;
	int nHigh  = 0; 
	int nWide  = 0;
	CString strTop,strLeft;
	CString strHigh,strWide;

	nTop  = parameter.getStart_Y(); 
	nLeft = parameter.getStart_X();
	nHigh  = parameter.getHigh(); 
	nWide = parameter.getWide();

	strTop.Format(_T("%d"),nTop); 
	strLeft.Format(_T("%d"),nLeft);
	strHigh.Format(_T("%d"),nHigh); 
	strWide.Format(_T("%d"),nWide);

	//A1
	SetDlgItemText(IDC_TOP_A1,_T("A1 Top:"));
	SetDlgItemText(IDC_LEFT_A1,_T("A1 Left:"));
	SetDlgItemText(IDC_TOP_VALUE_A1,strStudName);
	SetDlgItemText(IDC_LEFT_VALUE_A1,strLeft);

	SetDlgItemText(IDC_HIGH_A1,_T("High:"));
	SetDlgItemText(IDC_WIDE_A1,_T("Wide:"));
	SetDlgItemText(IDC_HIGH_VALUE_A1,strHigh);
	SetDlgItemText(IDC_WIDE_VALUE_A1,strWide);

	SetDlgItemText(IDC_LIGHT_A1,_T("Light:"));
	SetDlgItemText(IDC_LIGHT_VALUE_A1,_T("0"));


	//A2
	SetDlgItemText(IDC_TOP_A2,_T("A2 Top:"));
	SetDlgItemText(IDC_LEFT_A2,_T("A2 Left:"));
	SetDlgItemText(IDC_TOP_VALUE_A2,strTop);
	SetDlgItemText(IDC_LEFT_VALUE_A2,strLeft);

	SetDlgItemText(IDC_HIGH_A2,_T("High:"));
	SetDlgItemText(IDC_WIDE_A2,_T("Wide:"));
	SetDlgItemText(IDC_HIGH_VALUE_A2,strHigh);
	SetDlgItemText(IDC_WIDE_VALUE_A2,strWide);

	SetDlgItemText(IDC_RANGE_A2,_T("Range:"));
	SetDlgItemText(IDC_RESULT_A2,_T("Result:"));
	SetDlgItemText(IDC_RANGE_VALUE1_A2,_T("0"));
	SetDlgItemText(IDC_RANGE_VALUE2_A2,_T("255"));


	//A3
	SetDlgItemText(IDC_TOP_A3,_T("A3 Top:"));
	SetDlgItemText(IDC_LEFT_A3,_T("A3 Left:"));
	SetDlgItemText(IDC_TOP_VALUE_A3,strTop);
	SetDlgItemText(IDC_LEFT_VALUE_A3,strLeft);

	SetDlgItemText(IDC_HIGH_A3,_T("High:"));
	SetDlgItemText(IDC_WIDE_A3,_T("Wide:"));
	SetDlgItemText(IDC_HIGH_VALUE_A3,strHigh);
	SetDlgItemText(IDC_WIDE_VALUE_A3,strWide);

	SetDlgItemText(IDC_RANGE_A3,_T("Range:"));
	SetDlgItemText(IDC_RESULT_A3,_T("Result:"));
	SetDlgItemText(IDC_RANGE_VALUE1_A3,_T("0"));
	SetDlgItemText(IDC_RANGE_VALUE2_A3,_T("255"));


	//A4
	SetDlgItemText(IDC_TOP_A4,_T("A4 Top:"));
	SetDlgItemText(IDC_LEFT_A4,_T("A4 Left:"));
	SetDlgItemText(IDC_TOP_VALUE_A4,strTop);
	SetDlgItemText(IDC_LEFT_VALUE_A4,strLeft);

	SetDlgItemText(IDC_HIGH_A4,_T("High:"));
	SetDlgItemText(IDC_WIDE_A4,_T("Wide:"));
	SetDlgItemText(IDC_HIGH_VALUE_A4,strHigh);
	SetDlgItemText(IDC_WIDE_VALUE_A4,strWide);

	SetDlgItemText(IDC_RANGE_A4,_T("Range:"));
	SetDlgItemText(IDC_RESULT_A4,_T("Result:"));
	SetDlgItemText(IDC_RANGE_VALUE1_A4,_T("0"));
	SetDlgItemText(IDC_RANGE_VALUE2_A4,_T("255"));

	//A5
	SetDlgItemText(IDC_TOP_A5,_T("A5 Top:"));
	SetDlgItemText(IDC_LEFT_A5,_T("A5 Left:"));
	SetDlgItemText(IDC_TOP_VALUE_A5,strTop);
	SetDlgItemText(IDC_LEFT_VALUE_A5,strLeft);

	SetDlgItemText(IDC_HIGH_A5,_T("High:"));
	SetDlgItemText(IDC_WIDE_A5,_T("Wide:"));
	SetDlgItemText(IDC_HIGH_VALUE_A5,strHigh);
	SetDlgItemText(IDC_WIDE_VALUE_A5,strWide);

	SetDlgItemText(IDC_RANGE_A5,_T("Range:"));
	SetDlgItemText(IDC_RESULT_A5,_T("Result:"));
	SetDlgItemText(IDC_RANGE_VALUE1_A5,_T("0"));
	SetDlgItemText(IDC_RANGE_VALUE2_A5,_T("255"));


	//A6
	SetDlgItemText(IDC_TOP_A6,_T("A6 Top:"));
	SetDlgItemText(IDC_LEFT_A6,_T("A6 Left:"));
	SetDlgItemText(IDC_TOP_VALUE_A6,strTop);
	SetDlgItemText(IDC_LEFT_VALUE_A6,strLeft);

	SetDlgItemText(IDC_HIGH_A6,_T("High:"));
	SetDlgItemText(IDC_WIDE_A6,_T("Wide:"));
	SetDlgItemText(IDC_HIGH_VALUE_A6,strHigh);
	SetDlgItemText(IDC_WIDE_VALUE_A6,strWide);

	SetDlgItemText(IDC_RANGE_A6,_T("Range:"));
	SetDlgItemText(IDC_RESULT_A6,_T("Result:"));
	SetDlgItemText(IDC_RANGE_VALUE1_A6,_T("0"));
	SetDlgItemText(IDC_RANGE_VALUE2_A6,_T("255"));


	//A7
	SetDlgItemText(IDC_TOP_A7,_T("A7 Top:"));
	SetDlgItemText(IDC_LEFT_A7,_T("A7 Left:"));
	SetDlgItemText(IDC_TOP_VALUE_A7,strTop);
	SetDlgItemText(IDC_LEFT_VALUE_A7,strLeft);

	SetDlgItemText(IDC_HIGH_A7,_T("High:"));
	SetDlgItemText(IDC_WIDE_A7,_T("Wide:"));
	SetDlgItemText(IDC_HIGH_VALUE_A1,strHigh);
	SetDlgItemText(IDC_WIDE_VALUE_A1,strWide);

	SetDlgItemText(IDC_RANGE_A7,_T("Range:"));
	SetDlgItemText(IDC_RESULT_A7,_T("Result:"));
	SetDlgItemText(IDC_RANGE_VALUE1_A7,_T("0"));
	SetDlgItemText(IDC_RANGE_VALUE2_A7,_T("255"));

*/
	
}
void CBTL_VISIONDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	CFileFind finder;   //查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用  
	//BOOL ifFind = finder.FindFile(_T("d:\\RoadDataManagerApp.ini"));
	BOOL ifFind = finder.FindFile(_T("c:\\Windows\\vision.ini"));  
	if( !ifFind )  
	{
		//A1
		::WritePrivateProfileStringW(_T("A1"),_T("x"),_T("240"),_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A1"),_T("y"),_T("320"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A1"),_T("high"),_T("480"),_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A1"),_T("wide"),_T("640"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A1"),_T("light"),_T("0"),_T("c:\\Windows\\vision.ini"));

		//A2
		::WritePrivateProfileStringW(_T("A2"),_T("x"),_T("240"),_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A2"),_T("y"),_T("320"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A2"),_T("high"),_T("480"),_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A2"),_T("wide"),_T("640"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A2"),_T("startRange"),_T("0"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A2"),_T("endRange"),_T("255"),_T("c:\\Windows\\vision.ini"));
		//A3
		::WritePrivateProfileStringW(_T("A3"),_T("x"),_T("240"),_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A3"),_T("y"),_T("320"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A3"),_T("high"),_T("480"),_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A3"),_T("wide"),_T("640"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A3"),_T("startRange"),_T("0"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A3"),_T("endRange"),_T("255"),_T("c:\\Windows\\vision.ini"));
		//A4
		::WritePrivateProfileStringW(_T("A4"),_T("x"),_T("240"),_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A4"),_T("y"),_T("320"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A4"),_T("high"),_T("480"),_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A4"),_T("wide"),_T("640"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A4"),_T("startRange"),_T("0"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A4"),_T("endRange"),_T("255"),_T("c:\\Windows\\vision.ini"));
		//A5
		::WritePrivateProfileStringW(_T("A5"),_T("x"),_T("240"),_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A5"),_T("y"),_T("320"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A5"),_T("high"),_T("480"),_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A5"),_T("wide"),_T("640"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A5"),_T("startRange"),_T("0"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A5"),_T("endRange"),_T("255"),_T("c:\\Windows\\vision.ini"));
		//A6
		::WritePrivateProfileStringW(_T("A6"),_T("x"),_T("240"),_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A6"),_T("y"),_T("320"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A6"),_T("high"),_T("480"),_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A6"),_T("wide"),_T("640"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A6"),_T("startRange"),_T("0"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A6"),_T("endRange"),_T("255"),_T("c:\\Windows\\vision.ini"));
		//A7
		::WritePrivateProfileStringW(_T("A7"),_T("x"),_T("240"),_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A7"),_T("y"),_T("320"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A7"),_T("high"),_T("480"),_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A7"),_T("wide"),_T("640"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A7"),_T("startRange"),_T("0"),_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A7"),_T("endRange"),_T("255"),_T("c:\\Windows\\vision.ini"));
	} 
	else
	{
		CString strLeft,strTop,strHigh,strWide,strStartRange,strEndRange,strLight;
		//A1
		GetDlgItemText(IDC_LEFT_VALUE_A1,strLeft);
		GetDlgItemText(IDC_TOP_VALUE_A1,strTop);
		GetDlgItemText(IDC_HIGH_VALUE_A1,strHigh);
		GetDlgItemText(IDC_WIDE_VALUE_A1,strWide);
		GetDlgItemText(IDC_LIGHT_VALUE_A1,strLight);
		::WritePrivateProfileStringW(_T("A1"),_T("x"),strLeft,_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A1"),_T("y"),strTop,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A1"),_T("high"),strHigh,_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A1"),_T("wide"),strWide,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A1"),_T("light"),strLight,_T("c:\\Windows\\vision.ini"));

		//A2
		GetDlgItemText(IDC_LEFT_VALUE_A2,strLeft);
		GetDlgItemText(IDC_TOP_VALUE_A2,strTop);
		GetDlgItemText(IDC_HIGH_VALUE_A2,strHigh);
		GetDlgItemText(IDC_WIDE_VALUE_A2,strWide);
		GetDlgItemText(IDC_RANGE_VALUE1_A2,strStartRange);
		GetDlgItemText(IDC_RANGE_VALUE2_A2,strEndRange);
		::WritePrivateProfileStringW(_T("A2"),_T("x"),strLeft,_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A2"),_T("y"),strTop,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A2"),_T("high"),strHigh,_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A2"),_T("wide"),strWide,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A2"),_T("startRange"),strStartRange,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A2"),_T("endRange"),strEndRange,_T("c:\\Windows\\vision.ini"));
		//A3
		GetDlgItemText(IDC_LEFT_VALUE_A3,strLeft);
		GetDlgItemText(IDC_TOP_VALUE_A3,strTop);
		GetDlgItemText(IDC_HIGH_VALUE_A3,strHigh);
		GetDlgItemText(IDC_WIDE_VALUE_A3,strWide);
		GetDlgItemText(IDC_RANGE_VALUE1_A3,strStartRange);
		GetDlgItemText(IDC_RANGE_VALUE2_A3,strEndRange);
		::WritePrivateProfileStringW(_T("A3"),_T("x"),strLeft,_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A3"),_T("y"),strTop,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A3"),_T("high"),strHigh,_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A3"),_T("wide"),strWide,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A3"),_T("startRange"),strStartRange,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A3"),_T("endRange"),strEndRange,_T("c:\\Windows\\vision.ini"));
		//A4
		GetDlgItemText(IDC_LEFT_VALUE_A4,strLeft);
		GetDlgItemText(IDC_TOP_VALUE_A4,strTop);
		GetDlgItemText(IDC_HIGH_VALUE_A4,strHigh);
		GetDlgItemText(IDC_WIDE_VALUE_A4,strWide);
		GetDlgItemText(IDC_RANGE_VALUE1_A4,strStartRange);
		GetDlgItemText(IDC_RANGE_VALUE2_A4,strEndRange);
		::WritePrivateProfileStringW(_T("A4"),_T("x"),strLeft,_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A4"),_T("y"),strTop,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A4"),_T("high"),strHigh,_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A4"),_T("wide"),strWide,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A4"),_T("startRange"),strStartRange,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A4"),_T("endRange"),strEndRange,_T("c:\\Windows\\vision.ini"));
		//A5
		GetDlgItemText(IDC_LEFT_VALUE_A5,strLeft);
		GetDlgItemText(IDC_TOP_VALUE_A5,strTop);
		GetDlgItemText(IDC_HIGH_VALUE_A5,strHigh);
		GetDlgItemText(IDC_WIDE_VALUE_A5,strWide);
		GetDlgItemText(IDC_RANGE_VALUE1_A5,strStartRange);
		GetDlgItemText(IDC_RANGE_VALUE2_A5,strEndRange);
		::WritePrivateProfileStringW(_T("A5"),_T("x"),strLeft,_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A5"),_T("y"),strTop,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A5"),_T("high"),strHigh,_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A5"),_T("wide"),strWide,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A5"),_T("startRange"),strStartRange,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A5"),_T("endRange"),strEndRange,_T("c:\\Windows\\vision.ini"));
		//A6
		GetDlgItemText(IDC_LEFT_VALUE_A6,strLeft);
		GetDlgItemText(IDC_TOP_VALUE_A6,strTop);
		GetDlgItemText(IDC_HIGH_VALUE_A6,strHigh);
		GetDlgItemText(IDC_WIDE_VALUE_A6,strWide);
		GetDlgItemText(IDC_RANGE_VALUE1_A6,strStartRange);
		GetDlgItemText(IDC_RANGE_VALUE2_A6,strEndRange);
		::WritePrivateProfileStringW(_T("A6"),_T("x"),strLeft,_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A6"),_T("y"),strTop,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A6"),_T("high"),strHigh,_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A6"),_T("wide"),strWide,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A6"),_T("startRange"),strStartRange,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A6"),_T("endRange"),strEndRange,_T("c:\\Windows\\vision.ini"));
		//A7
		GetDlgItemText(IDC_LEFT_VALUE_A7,strLeft);
		GetDlgItemText(IDC_TOP_VALUE_A7,strTop);
		GetDlgItemText(IDC_HIGH_VALUE_A7,strHigh);
		GetDlgItemText(IDC_WIDE_VALUE_A7,strWide);
		GetDlgItemText(IDC_RANGE_VALUE1_A7,strStartRange);
		GetDlgItemText(IDC_RANGE_VALUE2_A7,strEndRange);
		::WritePrivateProfileStringW(_T("A7"),_T("x"),strLeft,_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A7"),_T("y"),strTop,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A7"),_T("high"),strHigh,_T("c:\\Windows\\vision.ini"));   
		::WritePrivateProfileStringW(_T("A7"),_T("wide"),strWide,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A7"),_T("startRange"),strStartRange,_T("c:\\Windows\\vision.ini"));
		::WritePrivateProfileStringW(_T("A7"),_T("endRange"),strEndRange,_T("c:\\Windows\\vision.ini"));
	}
}

void CBTL_VISIONDlg::DrawPicToHDC(IplImage *img, UINT ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC= pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf( img ); // 复制图片
	cimg.DrawToHDC( hDC, &rect ); // 将图片绘制到显示控件的指定区域内
	ReleaseDC( pDC );
}
void CBTL_VISIONDlg::DrawPicToHDC(Mat img, UINT ID)
{	
	IplImage* image=NULL; //原始图像
	if(image)
	{
		cvReleaseImage(&image);
	}

	IplImage iplimage = img;
	image = &iplimage;
	DrawPicToHDC(image, ID);
}
void CBTL_VISIONDlg::OnEnChangeLightValueA1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString strLight,strStartRange,strEndRange;
	GetDlgItemText(IDC_LIGHT_VALUE_A1,strLight);
	int iLight  = _ttoi(strLight);

	GetDlgItemText(IDC_RANGE_VALUE1_A2,strStartRange);
	GetDlgItemText(IDC_RANGE_VALUE2_A2,strEndRange);
	int iStartRange =_ttoi(strStartRange);
	int iEndRange   =_ttoi(strEndRange);

	iStartRange = iStartRange*iLight;
	iEndRange   = iEndRange*iLight;

	strStartRange.Format(_T("%d"),iStartRange); 
	strEndRange.Format(_T("%d"),iEndRange); 

	SetDlgItemText(IDC_RANGE_VALUE1_A2,strStartRange);
	SetDlgItemText(IDC_RANGE_VALUE2_A2,strEndRange);



}

//void CBTL_VISIONDlg::OnBnClickedButton3()
//{
//	// TODO: Add your control notification handler code here
//	Mat mat = imread("a1.bmp");
//	DrawPicToHDC(mat,IDC_DISPLAY);
//}
void CBTL_VISIONDlg::ShowMessage(int index,bool blnFlag)
{
	// TODO: Add your control notification handler code here
	Mat mat; 
	if(blnFlag)
	{
		switch(index)
		{
		case ProcessA1:
			{
				mat= imread("BMP\\a1.bmp");
				DrawPicToHDC(mat,IDC_DISPLAY);
				break;
			}
		case ProcessA2:
			{
				mat= imread("BMP\\a3.bmp");
				DrawPicToHDC(mat,IDC_DISPLAY);
				break;
			}
		case ProcessA3_1:
			{
				mat= imread("BMP\\a5.bmp");
				DrawPicToHDC(mat,IDC_DISPLAY);
				break;
			}
		case ProcessA3_2:
			{
				mat= imread("BMP\\a7.bmp");
				DrawPicToHDC(mat,IDC_DISPLAY);
				break;
			}
		case ProcessA3_3:
			{
				mat= imread("BMP\\a9.bmp");
				DrawPicToHDC(mat,IDC_DISPLAY);
				break;
			}
		default:
			break;
		}
	}
	else
	{
		switch(index)
		{
		case ProcessA1:
			{
				mat= imread("BMP\\a2.bmp");
				DrawPicToHDC(mat,IDC_DISPLAY);
				break;
			}
		case ProcessA2:
			{
				mat= imread("BMP\\a4.bmp");
				DrawPicToHDC(mat,IDC_DISPLAY);
				break;
			}
		case ProcessA3_1:
			{
				mat= imread("BMP\\a6.bmp");
				DrawPicToHDC(mat,IDC_DISPLAY);
				break;
			}
		case ProcessA3_2:
			{
				mat= imread("BMP\\a8.bmp");
				DrawPicToHDC(mat,IDC_DISPLAY);
				break;
			}
		case ProcessA3_3:
			{
				mat= imread("BMP\\a10.bmp");
				DrawPicToHDC(mat,IDC_DISPLAY);
				break;
			}
		default:
			break;
		}
	}
}
void CBTL_VISIONDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CloseMscomm();
	CDialog::OnClose();
}

void CBTL_VISIONDlg::OnBnClickedSave()
{
	// TODO: Add your control notification handler code here
/*
	if(g_image.empty())
	{
		AfxMessageBox(_T("图片为空！!"));
		return;
	}
	CString strTop,strLeft,strHigh,strWide;//,strStartRange,strEndRange;

	GetDlgItemText(IDC_TOP_VALUE_A2,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A2,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A2,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A2,strWide);

	int iTop  = _ttoi(strTop);
	int iLeft = _ttoi(strLeft);
	int iHigh = _ttoi(strHigh);
	int iWide = _ttoi(strWide);

	Mat imgA1_1 = g_image(Rect(iLeft,iTop,iWide,iHigh));
	cv::imwrite("imgA1_1.bmp",imgA1_1);

	//A3
	GetDlgItemText(IDC_TOP_VALUE_A3,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A3,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A3,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A3,strWide);

	iTop  = _ttoi(strTop);
	iLeft = _ttoi(strLeft);
	iHigh = _ttoi(strHigh);
	iWide = _ttoi(strWide);

	Mat imgA1_2 = g_image(Rect(iLeft,iTop,iWide,iHigh));
	cv::imwrite("imgA1_2.bmp",imgA1_2);

	//A4
	GetDlgItemText(IDC_TOP_VALUE_A4,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A4,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A4,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A4,strWide);

	iTop  = _ttoi(strTop);
	iLeft = _ttoi(strLeft);
	iHigh = _ttoi(strHigh);
	iWide = _ttoi(strWide);

	Mat imgA1_3 = g_image(Rect(iLeft,iTop,iWide,iHigh));
	cv::imwrite("imgA1_3.bmp",imgA1_3);
	//A5
	GetDlgItemText(IDC_TOP_VALUE_A5,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A5,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A5,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A5,strWide);

	iTop  = _ttoi(strTop);
	iLeft = _ttoi(strLeft);
	iHigh = _ttoi(strHigh);
	iWide = _ttoi(strWide);

	Mat imgA2_0 = g_image(Rect(iLeft,iTop,iWide,iHigh));
	cv::imwrite("imgA2_0.bmp",imgA2_0);

	//A6
	GetDlgItemText(IDC_TOP_VALUE_A6,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A6,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A6,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A6,strWide);

	iTop  = _ttoi(strTop);
	iLeft = _ttoi(strLeft);
	iHigh = _ttoi(strHigh);
	iWide = _ttoi(strWide);

	Mat imgA3_1 = g_image(Rect(iLeft,iTop,iWide,iHigh));
	cv::imwrite("imgA3_1.bmp",imgA3_1);
	//A7
	GetDlgItemText(IDC_TOP_VALUE_A7,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A7,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A7,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A7,strWide);

	iTop  = _ttoi(strTop);
	iLeft = _ttoi(strLeft);
	iHigh = _ttoi(strHigh);
	iWide = _ttoi(strWide);

	Mat imgA3_2 = g_image(Rect(iLeft,iTop,iWide,iHigh));
	cv::imwrite("imgA3_2.bmp",imgA3_2);
	AfxMessageBox(_T("保存成功!"));
	*/
}

void CBTL_VISIONDlg::OnBnClickedButtonSa2()
{
	// TODO: Add your control notification handler code here
	if(g_image.empty())
	{
		AfxMessageBox(_T("图片为空！!"));
		return;
	}
	CString strTop,strLeft,strHigh,strWide;//,strStartRange,strEndRange;

	GetDlgItemText(IDC_TOP_VALUE_A2,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A2,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A2,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A2,strWide);

	int iTop  = _ttoi(strTop);
	int iLeft = _ttoi(strLeft);
	int iHigh = _ttoi(strHigh);
	int iWide = _ttoi(strWide);

	Mat imgA1_1 = g_image(Rect(iLeft,iTop,iWide,iHigh));
	cv::imwrite("imgA1_1.bmp",imgA1_1);
	AfxMessageBox(_T("保存成功!"));
}

void CBTL_VISIONDlg::OnBnClickedButtonSa3()
{
	// TODO: Add your control notification handler code here
	if(g_image.empty())
	{
		AfxMessageBox(_T("图片为空！!"));
		return;
	}
	CString strTop,strLeft,strHigh,strWide;//,strStartRange,strEndRange;

	GetDlgItemText(IDC_TOP_VALUE_A3,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A3,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A3,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A3,strWide);

	int iTop  = _ttoi(strTop);
	int iLeft = _ttoi(strLeft);
	int iHigh = _ttoi(strHigh);
	int iWide = _ttoi(strWide);

	Mat imgA1_2 = g_image(Rect(iLeft,iTop,iWide,iHigh));
	cv::imwrite("imgA1_2.bmp",imgA1_2);
	AfxMessageBox(_T("保存成功!"));
}

void CBTL_VISIONDlg::OnBnClickedButtonSa4()
{
	// TODO: Add your control notification handler code here
	if(g_image.empty())
	{
		AfxMessageBox(_T("图片为空！!"));
		return;
	}
	CString strTop,strLeft,strHigh,strWide;//,strStartRange,strEndRange;

	GetDlgItemText(IDC_TOP_VALUE_A4,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A4,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A4,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A4,strWide);

	int iTop  = _ttoi(strTop);
	int iLeft = _ttoi(strLeft);
	int iHigh = _ttoi(strHigh);
	int iWide = _ttoi(strWide);

	Mat imgA1_3 = g_image(Rect(iLeft,iTop,iWide,iHigh));
	cv::imwrite("imgA1_3.bmp",imgA1_3);
	AfxMessageBox(_T("保存成功!"));
}

void CBTL_VISIONDlg::OnBnClickedButtonSa5()
{
	// TODO: Add your control notification handler code here
	if(g_image.empty())
	{
		AfxMessageBox(_T("图片为空！!"));
		return;
	}
	CString strTop,strLeft,strHigh,strWide;//,strStartRange,strEndRange;

	GetDlgItemText(IDC_TOP_VALUE_A5,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A5,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A5,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A5,strWide);

	int iTop  = _ttoi(strTop);
	int iLeft = _ttoi(strLeft);
	int iHigh = _ttoi(strHigh);
	int iWide = _ttoi(strWide);

	Mat imgA2_0 = g_image(Rect(iLeft,iTop,iWide,iHigh));
	cv::imwrite("imgA2_0.bmp",imgA2_0);
	AfxMessageBox(_T("保存成功!"));
}

void CBTL_VISIONDlg::OnBnClickedButtonSa6()
{
	// TODO: Add your control notification handler code here
	if(g_image.empty())
	{
		AfxMessageBox(_T("图片为空！!"));
		return;
	}
	CString strTop,strLeft,strHigh,strWide;//,strStartRange,strEndRange;

	GetDlgItemText(IDC_TOP_VALUE_A6,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A6,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A6,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A6,strWide);

	int iTop  = _ttoi(strTop);
	int iLeft = _ttoi(strLeft);
	int iHigh = _ttoi(strHigh);
	int iWide = _ttoi(strWide);

	Mat imgA3_1 = g_image(Rect(iLeft,iTop,iWide,iHigh));
	cv::imwrite("imgA3_1.bmp",imgA3_1);
	AfxMessageBox(_T("保存成功!"));
}

void CBTL_VISIONDlg::OnBnClickedButtonSa7()
{
	// TODO: Add your control notification handler code here
	if(g_image.empty())
	{
		AfxMessageBox(_T("图片为空！!"));
		return;
	}
	CString strTop,strLeft,strHigh,strWide;//,strStartRange,strEndRange;

	GetDlgItemText(IDC_TOP_VALUE_A7,strTop);
	GetDlgItemText(IDC_LEFT_VALUE_A7,strLeft);
	GetDlgItemText(IDC_HIGH_VALUE_A7,strHigh);
	GetDlgItemText(IDC_WIDE_VALUE_A7,strWide);

	int iTop  = _ttoi(strTop);
	int iLeft = _ttoi(strLeft);
	int iHigh = _ttoi(strHigh);
	int iWide = _ttoi(strWide);

	Mat imgA3_2 = g_image(Rect(iLeft,iTop,iWide,iHigh));
	cv::imwrite("imgA3_2.bmp",imgA3_2);
	AfxMessageBox(_T("保存成功!"));
}
