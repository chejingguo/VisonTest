#pragma once

class ColorHistogram
{
public:
	ColorHistogram(void);
	~ColorHistogram(void);
private:
	int histSize[3];
	float hranges[2];
	const float* ranges[3];
	int channels[3];

public:
	cv::MatND getHistogram(const cv::Mat &image);
	Mat colorReduce(Mat &image,int div);
};
