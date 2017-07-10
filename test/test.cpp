#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;
int main(int argc,char ** argv){
	if(argc < 2){
		cout <<	"usage error " << endl;
	}
	Mat src = imread(argv[1],0);
	Mat image = src.clone();

	cv::resize(image,image,cv::Size(800,800));//标准大小
	cv::blur(image,image,cv::Size(3,3));//模糊,去除毛刺
	cv::threshold(image,image,100,255,cv::THRESH_OTSU);
	
	vector<vector<cv::Point> > contour ,contour2;
	vector<Vec4i> hierarchy;
	//@3:层级 @4:采用树形结构 @5:寻找全部
	cv::findContours(image,contour,hierarchy,
					cv::RETR_TREE,cv::CHAIN_APPROX_NONE,Point(0,0));
	cout << "contour.size  = "<< contour.size() << endl;
	cout << "hierarchy.size  = "<< hierarchy.size() << endl;

	Mat C(Size(800,800),CV_8UC1);
	cv::drawContours(C,contour,-1,cv::Scalar(255,0,0));
	imshow("contour",C);
	
#if 0
	//轮廓筛选
	int c = 0,ic = 0,area = 0;
	int parentIdx = -1;
	for (int i = 0; i < contour.size();i++){
		
	}
#endif

	waitKey();

return 0;
}
