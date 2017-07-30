#include "grab_info.hpp"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <string>
inline float min(float a,float b){
	return  (a < b ? a : b);
}

inline int min(int a,int b){
	return  (a < b ? a : b);
}


/***********************************************************
 *	Marker class
 * */
Marker::Marker()
{
	m_id = -1;
	m_corners.resize(4, cv::Point2f(0.0,0.0));
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
				
	cv::Point text_point = m_corners[0] + m_corners[2];
	text_point.x /= 2;
	text_point.y /= 2;

	std::stringstream ss;
	ss << m_id;

	putText(image, ss.str(), text_point, cv::FONT_HERSHEY_SIMPLEX, 0.5, color);
}

void Marker::estimateTransformToCamera(std::vector<cv::Point3f> corners_3d, cv::Mat& camera_matrix, cv::Mat& dist_coeff, cv::Mat& rmat, cv::Mat& tvec)
{
	cv::Mat rot_vec;
	/*bool res = */solvePnP(corners_3d, m_corners, camera_matrix, dist_coeff, rot_vec, tvec);
	Rodrigues(rot_vec, rmat);
}

void Marker::sort(void){
	//c0  -- -- c3
	std::vector<cv::Point2i> tmp;
	tmp.resize(0);
	std::vector<cv::Point2i> up;
	up.resize(0);
	std::vector<cv::Point2i> down;
	down.resize(0);
	for (int i = 0;i < (int)m_corners.size();i++){
		printf("*****\tm_corners[%d] = (%d,%d)\n",i,m_corners[i].x,m_corners[i].y);
	}

	int min1 = 1000;
	int min2 = 1000;	
	unsigned int p1 = 0;
	unsigned int p2 = 0;
	unsigned int p3 = 0;
	unsigned int p4 = 0;
	for(unsigned int i = 0;i < m_corners.size();i++){
		if(m_corners[i].y < min1){
			min1 = m_corners[i].y;		
			p1 = i;
		}		
	}
	for(unsigned int i = 0;i < m_corners.size();i++){
		if(i == p1)
			continue;
		if(m_corners[i].y < min2){
			min2 = m_corners[i].y;		
			p2 = i;
		}		
	}
	printf("min1 = %d.min2 = %d\n",min1,min2);

	// -----^  y
	if(m_corners[p1].x < m_corners[p2].x){
			printf("what?\n");
		up.push_back(m_corners[p1]);
		up.push_back(m_corners[p2]);
	}	
	else if(m_corners[p1].x > m_corners[p2].x){
		up.push_back(m_corners[p2]);
		up.push_back(m_corners[p1]);
	}
	printf("up[0] = (%d,%d)\n",up[0].x,up[0].y);
	printf("up[1] = (%d,%d)\n",up[1].x,up[1].y);
	//---^   y
	// c1 ---- c2 
	p3 = 0;
	p4 = 0;
	for(;(p3 == p1) || (p3 == p2);p3++){
	}	
	for(;(p4 == p1) || (p4 == p2) || (p4 == p3);p4++){
	}	

	if(m_corners[p3].x < m_corners[p4].x){
		down.push_back(m_corners[p3]);
		down.push_back(m_corners[p4]);
	}
	else if(m_corners[p3].x > m_corners[p4].x){
		down.push_back(m_corners[p4]);
		down.push_back(m_corners[p3]);
	}
	//swap(m_corners[0],up[0]);
	m_corners[0] = up[0];
	//swap(m_corners[1],down[0]);
	m_corners[1] = down[0];
	//swap(m_corners[2],down[1]);
	m_corners[2] = down[1];
	//swap(m_corners[0],up[1]);
	m_corners[3] = up[1];

}

void Marker::printPoint(cv::Mat & image){
	for(unsigned int i = 0;i < m_corners.size();i++){
	char  buf[15];
	sprintf(buf,"(%d,%d)",(int)m_corners[i].x,(int)m_corners[i].y);
	std::string s = buf;
	cv::putText(image,s,m_corners[i],cv::FONT_HERSHEY_PLAIN,0.5,cv::Scalar(100,100,255));
	}
}
/***********************************************************
 *	Grab_Rect class
 * */
Grab_Rect::Grab_Rect(cv::Mat & src,unsigned int min_size,unsigned int min_side_length){
	this->src = src;
	this->min_size = min_size;	
	this->min_side_length = min_side_length;
	m_marker_coords.push_back(cv::Point2f(0,0));
	m_marker_coords.push_back(cv::Point2f(0,MARKER_SIZE-1));
	m_marker_coords.push_back(cv::Point2f(MARKER_SIZE-1,MARKER_SIZE-1));
	m_marker_coords.push_back(cv::Point2f(MARKER_SIZE-1,0));
	
}


/* 多边形近似条件:
 *	1.只有4个顶点
 *	2.一定是凸多边形
 *	3.每一个边长度不能过小
 * */
void Grab_Rect::markerDetect(std::vector<Marker> & possible_marker){
	/*"AR码检测"*/	
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

	Dbug("all_contours.size() -> %ld\n",all_contours.size());
	for (unsigned int i = 0;i < all_contours.size();i++){
		if(all_contours[i].size() > min_size){
			Dbug("\tall_contours[%d] = %ld\n",i,all_contours[i].size());			
			contours.push_back(all_contours[i]);			
			//hierarchy.push_back(all_hierarchy[i]);
		}
	}
	
	Dbug("contours.size() = %ld \n",contours.size());

	//4边形逼近
	std::vector<cv::Point> approx_poly;//polygon
	for (unsigned int i  = 0;i < contours.size();i++){    //遍历大小足够的每一个轮廓
		double eps = contours[i].size() * APPROX_POLY_EPS;
		approxPolyDP(contours[i], approx_poly, eps, true); //矩形拟合

		if(approx_poly.size() != 4)
			continue; //只要4边型

		Dbug("\tapprox_poly.size() = %ld\n",approx_poly.size());

		if(!cv::isContourConvex(approx_poly))
			continue; //只要凸多边形

		//确保两连点之间的距离足够大
		float min_side = FLT_MAX;
		for (int j = 0;j < 4;j++){
			cv::Point side = approx_poly[j] - approx_poly[(j+1)%4];
			min_side = min((float)min_side,(float)side.dot(side));
		}		
		if (min_side < min_side_length * min_side_length)  //求出的最小边长不能小于min_side_length
			continue;
		
		Marker marker = Marker(0,approx_poly[0],approx_poly[1],approx_poly[2],approx_poly[3]);
		cv::Point2f v1 = marker.m_corners[1] - marker.m_corners[0];
		cv::Point2f v2 = marker.m_corners[2] - marker.m_corners[0];
		if(v1.cross(v2) > 0){
			swap(marker.m_corners[1],marker.m_corners[3]);
		}
		marker.sort();
#if 1
		//判断是否平行
		Parallel_rect Para(marker.m_corners[0],marker.m_corners[1],marker.m_corners[2],marker.m_corners[3]);
		if(!Para.isParallel())
			continue;
#endif
		possible_marker.push_back(marker);
		cv::line(src,marker.m_corners[0],marker.m_corners[1],cv::Scalar(0,100,255));	
		cv::line(src,marker.m_corners[1],marker.m_corners[2],cv::Scalar(0,100,255));	
		cv::line(src,marker.m_corners[2],marker.m_corners[3],cv::Scalar(0,100,255));	
		cv::line(src,marker.m_corners[3],marker.m_corners[0],cv::Scalar(0,100,255));	
		//marker.printPoint(src);
	}//end 遍历
	cv::imshow("maker",src);
	cv::waitKey();
}

/*
 * @possible_marker :可能是AR码的点集
 * @final_marker    :确定是AR码的点集
 * */
void Grab_Rect::markerRecognize(cv::Mat& img_gray, std::vector<Marker>& possible_markers, std::vector<Marker>& final_markers){
	final_markers.clear();	
	if(img_gray.channels() != 1){
		cv::cvtColor(img_gray,img_gray,cv::COLOR_BGR2GRAY);
	}


	cv::Mat marker_image;  //存放提取出来的单个MARKER码
	cv::Mat bit_matrix(5,5,CV_8UC1); //用来存放AR码中的信息

	cv::imshow("img_gray",img_gray);
	cv::waitKey();

	for (int i = 0;i < (int)possible_markers.size();i++){
		//透视变换
			//先通过(变换前的坐标点和 变换后的坐标点)来得到一个变换矩阵
		cv::Mat M = cv::getPerspectiveTransform(possible_markers[i].m_corners,m_marker_coords);	
			//透视变换 @1:输入图片 @2:输出图片 @3:变换矩阵 @4:输出图片大小 
		cv::warpPerspective(img_gray,marker_image,M,cv::Size(MARKER_SIZE,MARKER_SIZE));
		cv::imshow("marker_image",marker_image);
		cv::waitKey();
		cv::threshold(marker_image,marker_image,125,255,cv::THRESH_BINARY | cv::THRESH_OTSU);

		//Dbug("marker_image (%d,%d)",marker_image.cols,marker_image.rows);

			////A marker must has a whole black border.一个MARKER必须有完整的黑色边界
		for (int y = 0;y < 7;y++){ //因为AR码是7x7
			int inc = ((y == 0 || y == 6) ? 1 : 6);  //因为第一行和第7行有7各黑色块
			int cell_y = y*MARKER_CELL_SIZE;  //黑块的起始y
			for (int x = 0;x < 7;x+=inc){
				int cell_x = x*MARKER_CELL_SIZE; //黑块的起始x
				int none_zero_count = cv::countNonZero(marker_image(cv::Rect(cell_x,cell_y,MARKER_CELL_SIZE,MARKER_CELL_SIZE)));
				if(none_zero_count > MARKER_CELL_SIZE*MARKER_CELL_SIZE/2)
						goto __wrongMarker;
			}
		}//end AR边界确认

		//Decode the Marker 解码,读取1010值
		for (int y = 0;y < 5;y++){
			int cell_y = (y+1)*MARKER_CELL_SIZE;
			for(int x = 0;x < 5;x++){ //AR码数据仅为5x5
				int cell_x = (x+1) * MARKER_CELL_SIZE;	
				int none_zero_count = cv::countNonZero(marker_image(cv::Rect(cell_x,cell_y,MARKER_CELL_SIZE,MARKER_CELL_SIZE)));
				if(none_zero_count > MARKER_CELL_SIZE*MARKER_CELL_SIZE/2)
						bit_matrix.at<uchar>(y,x) = 1;
				else
						bit_matrix.at<uchar>(y,x) = 0;
			}
		}
		for(int i = 0;i < 25;i++)
		Dbug("%d",bit_matrix.data[i]);	
		Dbug("\n");

	__wrongMarker:
		printf("pass\n");
		continue;
	}//end for 
}
/***********************************************************
 *	Parallel_rect class
 *	这个类有bug                  -x
 * */	
Parallel_rect::Parallel_rect(cv::Point c0,cv::Point c1,
						cv::Point c2,cv::Point c3){
	this->c0 = c0;
	this->c1 = c1;
	this->c2 = c2;
	this->c3 = c3;
}

bool Parallel_rect::isParallel(){
	//#define LIMIT (1.1547 / 3) 
	#define LIMIT (0.5 / 3) 
	cv::Point2i v1,v2;
	double Tan1,Tan2;
	int dis_x1,dis_x2;
	/*	c0---------c3
	 *		
	 *  c1---------c2
	 * */	
	v1 = c3-c0;
	v2 = c2-c1;
	dis_x1 = v1.x;
	dis_x2 = v2.x;
	if((dis_x1 != 0) && (dis_x2 != 0)){
		Tan1 = (double)v1.y/v1.x;
		Tan2 = (double)v2.y/v2.x;
		if(fabs(Tan1-Tan2) < (double)LIMIT){
			return true;
		}
		else
			return false;
	}
	/*	c0|        |c3 
	 *	  |        |
	 *	c1|        |c2
	 * */
return false;
}
