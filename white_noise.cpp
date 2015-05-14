//using opencv2411

#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <random>

int main()
{
	using namespace std;
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<> dis(0,255);
	using namespace cv;
	Mat workspace(500,700,CV_8UC3,Scalar(0,0,0));
	for(int i=0;i<500;i++)
	{
		for(int j=0;j<700;j++)
		{
			int c = mt();
			workspace.at<Vec3b>(i,j) = Vec3b(c,c,c);
		}

	}
	imshow("white noise",workspace);
	waitKey();
}