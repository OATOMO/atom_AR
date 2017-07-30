#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace cv;
using namespace std;
int main(int argc,char ** argv){
#if 0
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

	cv::Point2f p1(0.0,0.0);
	cv::Point2f p2(3.0,3.0);
	cv::Point2f p3(3.0,-2.0);

	Point2f  p1_p2 = p1-p2;
	printf("p1-p2 = (%f,%f) \n" ,p1_p2.x,p1_p2.y);

	Point2f  p2_p1 = p2-p1;
	printf("p2-p1 = (%f,%f) \n" ,p2_p1.x,p2_p1.y);
#endif
	//test perspective
	using namespace cv;
	Mat src = imread("/home/atom/Desktop/ar.jpg");
	Mat dis;
	std::vector<Point2f> m_src;
	std::vector<Point2f> m_dis;

	m_src.push_back(Point2f(0,0));
	m_src.push_back(Point2f(400,0));
	m_src.push_back(Point2f(400,400));
	m_src.push_back(Point2f(800,400));

	m_dis.push_back(Point2f(0,0));
	m_dis.push_back(Point2f(400,0));
	m_dis.push_back(Point2f(0,400));
	m_dis.push_back(Point2f(400,400));

	Mat M = cv::getPerspectiveTransform(m_src,m_dis);
	cv::warpPerspective(src,dis,M,Size(200,200));

	imshow("src",src);
	imshow("dis",dis);
	waitKey();

return 0;
}
