#include "StdAfx.h"
#include "ColorHistogram.h"

ColorHistogram::ColorHistogram(void)
{
	histSize[0]=histSize[1]=histSize[2]=256;
	hranges[0]=0.0;
	hranges[1]=256.0;
	ranges[0]=hranges;
	ranges[1]=hranges;
	ranges[2]=hranges;
	channels[0]=0;
	channels[1]=1;
	channels[2]=2;
}

ColorHistogram::~ColorHistogram(void)
{
}
cv::MatND ColorHistogram::getHistogram(const cv::Mat &image)
{
	cv::MatND hist;
	cv::calcHist(&image,
		1,
		channels,
		cv::Mat(),
		hist,
		3,
		histSize,
		ranges
		);
	return hist;
}

Mat ColorHistogram::colorReduce(Mat &image,int div)
{
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
			data[i]=data[i]/div*div +div/2;
		}
	}
	return image;
}