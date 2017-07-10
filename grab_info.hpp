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

class Grab_Info{
private:
	cv::Mat src;
	
public:

};//end Grab_Info class


class Grab_Rect{
/*从不规则的投影中找到二维码*/
private:
	cv::Mat src;
	cv::Mat dst;
	unsigned int min_size;
public:
	Grab_Rect(cv::Mat & src,min_size = 5);
	void proc();
};
#endif 
