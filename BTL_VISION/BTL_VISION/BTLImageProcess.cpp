#include "StdAfx.h"
#include "BTLImageProcess.h"

BTLImageProcess::BTLImageProcess(void)
{
}

BTLImageProcess::~BTLImageProcess(void)
{
}
int BTLImageProcess::getImageAvgValue(Mat &imageColor)
{
	Mat image;
	cv::cvtColor(imageColor,image,::CV_RGB2GRAY);
	long  sum=0;
	long  avg=0;
	if(image.isContinuous())
	{
		image.reshape(1,image.cols*image.rows);
	}
	int nl = image.rows;
	int nc = image.cols*image.channels();

	for(int j=0;j<nl;j++)
	{
		uchar *data = image.ptr<uchar>(j);
		for(int i=0;i<nc;i++)
		{
			//data[i]=data[i]+32;
			sum = sum + data[i];
		}
	}
	avg = sum/(nl*nc);
	return avg;
}

void BTLImageProcess::modifyAvgValue(Mat &imageColor,int value)
{
	Mat image;
	cv::cvtColor(imageColor,image,::CV_RGB2GRAY);
	long long sum=0;
	int  avg=0;
	if(image.isContinuous())
	{
		image.reshape(1,image.cols*image.rows);
	}
	int nl = image.rows;
	int nc = image.cols*image.channels();

	for(int j=0;j<nl;j++)
	{
		uchar *data = image.ptr<uchar>(j);
		for(int i=0;i<nc;i++)
		{
			data[i]=value;
		}
	}
}
void BTLImageProcess::preprocess(Mat &image)
{
	cv::cvtColor(image,image,CV_BGR2GRAY);//cvtColor(image,image,CV_BGR2GRAY);

	//cv::blur(refImg1,refImg1,cv::Size(5,5));
	cv::GaussianBlur(image,image,cv::Size(5,5),1.5);
	//cv::medianBlur(refImg1,refImg1,5);

	equalizeHist(image,image);

	cv::threshold(image,image,180,255,cv::THRESH_BINARY);

	//imshow("imagetest",image);
}
void BTLImageProcess::contourProcess(Mat &image)
{
	//cv::Mat element5(5,5,CV_8U,cv::Scalar(1));
	//cv::morphologyEx(result,result,cv::MORPH_CLOSE,element5);
	//cv::morphologyEx(result,result,cv::MORPH_OPEN,element5);

	std::vector<std::vector<cv::Point>>contours;

	cv::findContours(image,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);

	int cmin =80;
	int cmax =1000;
	std::vector<std::vector<cv::Point>>::const_iterator itc = contours.begin();
	while(itc!=contours.end())
	{
		if(itc->size()<cmin||itc->size()>cmax)
			itc = contours.erase(itc);
		else
			++itc;
	}

	cv::Mat result(image.size(),CV_8U,cv::Scalar(255));

	cv::drawContours(result,contours,-1,cv::Scalar(0),2);


    cv::Rect r0 =cv::boundingRect(cv::Mat(contours[1]));

	cv::rectangle(result,r0,cv::Scalar(0),2);
}

void BTLImageProcess::preprocess_1(Mat &image)
{
	cv::cvtColor(image,image,CV_BGR2GRAY);//cvtColor(image,image,CV_BGR2GRAY);

	//cv::blur(refImg1,refImg1,cv::Size(5,5));
	cv::GaussianBlur(image,image,cv::Size(5,5),1.5);
	//cv::medianBlur(refImg1,refImg1,5);

	equalizeHist(image,image);

	cv::threshold(image,image,180,255,cv::THRESH_BINARY);

	//imshow("imagetest",image);
}