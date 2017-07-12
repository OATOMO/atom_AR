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

#define APPROX_POLY_EPS (0.08)

class Grab_Info{
/*暂时没用*/
private:
	cv::Mat src;
	
public:

};//end Grab_Info class


class Marker{
/*用来表示Marker码的4个顶点*/
private:
	int m_id;//第几个marker码
	std::vector<cv::Point2f> m_corners;
	/*	c0------c3
	 *	|		|
	 *  |       |
	 *  |       |
	 *  c1------c2  (c -> corners)
	 * */
public:
	Marker();
	Marker(int _id,cv::Point2f _c0,cv::Point2f _c1,cv::Point2f _c2,cv::Point2f _c3);

	void estimateTransformToCamera(std::vector<cv::Point3f> corners_3d,cv::Mat & camera_matrix,cv::Mat & dist_coeff,cv::Mat & rmat,cv::Mat & tvec);
	void drawToImage(cv::Mat & image,cv::Scalar color,float thickness);
};//end Marker class


class Grab_Rect{
/*从不规则的投影中找到二维码*/
private:
	cv::Mat src;
	cv::Mat dst;
	unsigned int min_size;   //最小轮廓
	unsigned int min_side_length;  //最小矩形边长
public:
	Grab_Rect(cv::Mat & src,unsigned int min_size = 5,unsigned int min_side_length = 5);
	void proc();
};
#endif 
