#include "grab_info.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

Grab_Rect::Grab_Rect(cv::Mat & src){
	this->src = src;	
}


/* 多边形近似条件:
 *	1.只有4个顶点
 *	2.一定是凸多边形
 *	3.每一个边长度不能过小
 * */
void Grab_Rect::proc(){
	cv::cvtColor(src,dst,cv::COLOR_BGR2GRAY);	
	cv::threshold(dst,dst,100,255,cv::THRESH_BINARY_INV);
	cv::imwrite("/home/atom/Desktop/proc/th.png",dst);	
#if 0
	cv::blur(dst,dst,cv::Size(3,3));//模糊,去除毛刺
	cv::imwrite("/home/atom/Desktop/proc/blur.png",dst);	
#endif
	//形态学开运算
	cv::Mat element = cv::getStructuringElement(
					cv::MORPH_RECT, cv::Size(3, 3));	
	cv::morphologyEx(dst,dst,cv::MORPH_OPEN,element);	
	cv::imwrite("/home/atom/Desktop/proc/morph_open.png",dst);	

	//轮廓
	std::vector<std::vector<cv::Point> > all_contours;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(dst,all_contours,hierarchy,
					cv::RETR_TREE,cv::CHAIN_APPROX_NONE,cv::Point(0,0));	

	for (unsigned int i = 0;i < all_contours.size();i++){
		if(all_contours[i].size() > min_size){
			contours.push_back(all_contours[i]);			
		}
	}

	//4边形逼近
	std::vector<cv::Point> approx_poly;//polygon
	for (unsigned int i  = 0;i << contours.size();i++){
		double eps = contours[i].size() * APPROX_POLY_EPS;
		approxPolyDP(contours[i], approx_poly, eps, true);
	}
	
}
