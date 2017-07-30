/* @file : grab_info.hpp
 * @func : 本类设计为获取图片的各种信息:
 *				(轮廓,角点)
 * -之后还需要一个类来进行透视变换
 * */
#ifndef __GRAB_INFO_H
#define __GRAB_INFO_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>

#define __DEBUG

#ifdef __DEBUG
#define Dbug(format,...) printf(format,##__VA_ARGS__)
#else
#define Dbug(format,...)
#endif

#define APPROX_POLY_EPS (0.08)

class Grab_Info{
/*暂时没用*/
private:
	cv::Mat src;
	
public:

};//end Grab_Info class


/***********************************************************
 *	Marker class
 * */
class Marker{
/*用来表示Marker码的4个顶点*/
public:
	int m_id;//第几个marker码
	std::vector<cv::Point2f> m_corners;
	/*	c0------c3
	 *	|		|
	 *  |       |
	 *  |       |
	 *  c1------c2  (c -> corners)
	 * */
	Marker();
	Marker(int _id,cv::Point2f _c0,cv::Point2f _c1,cv::Point2f _c2,cv::Point2f _c3);
	void sort(void);
	void printPoint(cv::Mat & image);
	void estimateTransformToCamera(std::vector<cv::Point3f> corners_3d,cv::Mat & camera_matrix,cv::Mat & dist_coeff,cv::Mat & rmat,cv::Mat & tvec);
	void drawToImage(cv::Mat & image,cv::Scalar color,float thickness);
};//end Marker class

#define MARKER_CELL_SIZE 10
#define MARKER_SIZE (7*MARKER_CELL_SIZE)

class Grab_Rect{
/*从不规则的投影中找到二维码*/
private:
	cv::Mat src;
	cv::Mat dst;
	std::vector<cv::Point2f> m_marker_coords; //透视变换后的点集
	std::vector<Marker> m_markers;
	unsigned int min_size;   //最小轮廓
	unsigned int min_side_length;  //最小矩形边长
public:
	Grab_Rect(cv::Mat & src,unsigned int min_size = 5,unsigned int min_side_length = 5);
	void markerDetect(std::vector<Marker> & possible_marker);
	void markerRecognize(cv::Mat& img_gray,std::vector<Marker>& possible_markers,std::vector<Marker>& final_markers);
};


/***********************************************************
 *	Parallel_Line class
 * */
class Parallel_rect{
public:
	cv::Point2f c0,c1,c2,c3;
public:
	Parallel_rect(cv::Point p1_1,cv::Point p1_2,cv::Point p2_1,cv::Point p2_2);
	bool isParallel();
};
#endif 
