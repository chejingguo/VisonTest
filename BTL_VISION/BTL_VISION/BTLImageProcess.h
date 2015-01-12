#pragma once

class BTLImageProcess
{
public:
	BTLImageProcess(void);
	~BTLImageProcess(void);
public:
	int getImageAvgValue(Mat &imageColor);
	void modifyAvgValue(Mat &imageColor,int value);
	void preprocess(Mat &image);
	void preprocess_1(Mat &image);
	void contourProcess(Mat &image);
};
