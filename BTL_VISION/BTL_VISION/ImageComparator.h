#pragma once
#include "ColorHistogram.h"
class ImageComparator
{
public:
	ImageComparator(void);
	~ImageComparator(void);
private:
	Mat reference;
	Mat input;
	MatND refH;
	MatND inputH;
	ColorHistogram hist;
	int div;

public:
	void setColorReduction(int factor)
	{
		div=factor;
	}
	int getColorReduction()
	{
		return div;
	}
	void setReferenceImage(Mat& image)
	{
		reference = hist.colorReduce(image,div);
		refH = hist.getHistogram(reference);
	}

	double compare(Mat &image)
	{
		input = hist.colorReduce(image,div);
		inputH = hist.getHistogram(input);
		return cv::compareHist(
			refH,inputH,CV_COMP_BHATTACHARYYA);
	}

};
