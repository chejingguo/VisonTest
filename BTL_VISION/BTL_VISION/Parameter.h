#pragma once

class Parameter
{
public:
	Parameter(void);
	~Parameter(void);
private:
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	int wide;
	int high;
	int startRange;
	int endRange;
public:
	int getStart_X(){return start_x;}
	int getStart_Y(){return start_y;}
	int getEnd_X(){return end_x;}
	int getEnd_Y(){return end_y;}

	int getWide(){return wide;}
	int getHigh(){return high;}

	int getStartRange(){return startRange;}
	int getEndRange(){return endRange;}

	void setStart_X(int x){start_x=x;}
	void setStart_Y(int y){start_y=y;}
	void setEnd_X(int x){end_x=x;}
	void setEnd_Y(int y){end_y=y;}

	void setWide(int newwide){wide = newwide;}
	void setHigh(int newhigh){high = newhigh;}
	void setStartRange(int newRange1){startRange = newRange1;}
	void setEndRange(int newRange2){endRange = newRange2;}
};
