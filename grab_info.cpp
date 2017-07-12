#include "grab_info.hpp"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

/***********************************************************
 *	Marker class
 * */
Marker::Marker()
{
	m_id = -1;
	m_corners.resize(4, Point2f(0.f,0.f));
}

Marker::Marker(int _id, cv::Point2f _c0, cv::Point2f _c1, cv::Point2f _c2, cv::Point2f _c3)
{
	m_id = _id;

	m_corners.reserve(4);
	m_corners.push_back(_c0);
	m_corners.push_back(_c1);
	m_corners.push_back(_c2);
	m_corners.push_back(_c3);
}

void Marker::drawToImage(cv::Mat& image, cv::Scalar color, float thickness)
{
	circle(image, m_corners[0], thickness*2, color, thickness);
	circle(image, m_corners[1], thickness, color, thickness);
	line(image, m_corners[0], m_corners[1], color, thickness, CV_AA);
    line(image, m_corners[1], m_corners[2], color, thickness, CV_AA);
    line(image, m_corners[2], m_corners[3], color, thickness, CV_AA);
    line(image, m_corners[3], m_corners[0], color, thickness, CV_AA);
				
	Point text_point = m_corners[0] + m_corners[2];
	text_point.x /= 2;
	text_point.y /= 2;

	stringstream ss;
	ss << m_id;

	putText(image, ss.str(), text_point, FONT_HERSHEY_SIMPLEX, 0.5, color);
}

void Marker::estimateTransformToCamera(vector<Point3f> corners_3d, cv::Mat& camera_matrix, cv::Mat& dist_coeff, cv::Mat& rmat, cv::Mat& tvec)
{
	Mat rot_vec;
	bool res = solvePnP(corners_3d, m_corners, camera_matrix, dist_coeff, rot_vec, tvec);
	Rodrigues(rot_vec, rmat);
}

/***********************************************************
 *	Grab_Rect class
 * */
Grab_Rect::Grab_Rect(cv::Mat & src,unsigned int min_size,unsigned int min_side_length){
	this->src = src;
	this->min_size = min_size;	
	this->min_side_length = min_side_length;
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
	std::vector<cv::Vec4i> all_hierarchy;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(dst,all_contours,hierarchy,
					cv::RETR_TREE,cv::CHAIN_APPROX_NONE,cv::Point(0,0));	

	for (unsigned int i = 0;i < all_contours.size();i++){
		if(all_contours[i].size() > min_size){
			printf("all_contours.size() -> %d\n,\tall_contours[%d] = %d\n",
							all_contours.size(),i,all_contours[i].size());			
			contours.push_back(all_contours[i]);			
			//hierarchy.push_back(all_hierarchy[i]);
		}
	}

	//4边形逼近
	std::vector<cv::Point> approx_poly;//polygon
	for (unsigned int i  = 0;i < contours.size();i++){    //遍历大小足够的每一个轮廓
		double eps = contours[i].size() * APPROX_POLY_EPS;
		printf(" contours.size() = %d \n",contours.size());
		approxPolyDP(contours[i], approx_poly, eps, true); //矩形拟合

		printf("approx_poly.size() = %d\n",approx_poly.size());
		if(approx_poly.size() != 4)
			continue; //只要4边型

		if(!cv::isContourConvex(approx_poly))
			continue; //只要凸多边形

		//确保两连点之间的距离足够大
		float min_side = FLT_MAX;
		for (int j = 0;j < 4;j++){
			cv::Point side = approx_poly[j] - approx_poly[(j+1)%4];
			min_side = min(min_side,side.dot(side));
		}		
		if (min_side < min_side_length/* * min_side_length*/)  //求出的最小边长不能小于min_side_length
			continue;
		
		Marker marker = Marker(0,approx_poly[1],approx_poly[2],approx_poly[3]);
		Point2f v1 = marker.m_corners[1] - marker.m_corners[0];
		Point2f v1 = marker.m_corners[2] - marker.m_corners[0];
		if(v1.cross(v2) > 0){
			swap(marker.m_corners[1],marker.m_corners[3]);
		}
		possible_marker.push_back(marker);
	}//end 遍历
	
}
