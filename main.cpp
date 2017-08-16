#include <iostream>
#include <opencv2/opencv.hpp>
#include "grab_info.hpp"
#include <GL/glut.h>

#define ARWindowName "AR"


void intrinsicMatrix2ProjectionMatrix(cv::Mat& camera_matrix, float width, float height, float near_plane, float far_plane, float* projection_matrix);
void extrinsicMatrix2ModelViewMatrix(cv::Mat& rotation, cv::Mat& translation, float* model_view_matrix);


GLfloat vertex_old[][3] = {
	{-1.0,-1.0,1.0},{-1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,-1.0,1.0},
	{-1.0,-1.0,-1.0},{-1.0,1.0,-1.0},{1.0,1.0,-1.0},{1.0,-1.0,-1.0},
};


GLfloat vertex[][3] = {
	{-1.0,-1.0,2.0},{-1.0,1.0,2.0},{1.0,1.0,2.0},{1.0,-1.0,2.0},
	{-1.0,-1.0,0.0},{-1.0,1.0,0.0},{1.0,1.0,0.0},{1.0,-1.0,0.0},
};

GLfloat colors[][3] = {
	{1.0,0.0,0.0},{0.0,1.0,1.0},{1.0,1.0,0.0},{0.0,1.0,0.0},
	{0.0,0.0,1.0},{1.0,1.0,1.0}
};

void polygon(int a,int b,int c,int d){
	//glBegin(GL_POLYGON);
	glBegin(GL_LINE_LOOP);
	glVertex3fv(vertex[a]);	
	glVertex3fv(vertex[b]);	
	glVertex3fv(vertex[c]);	
	glVertex3fv(vertex[d]);	
	glEnd();
}

void cube(){
	glColor3fv(colors[0]);
	polygon(0,3,2,1);
	glColor3fv(colors[2]);
	polygon(2,3,7,6);
	glColor3fv(colors[3]);
	polygon(3,0,4,7);
	glColor3fv(colors[1]);
	polygon(1,2,6,5);
	glColor3fv(colors[4]);
	polygon(4,5,6,7);
	glColor3fv(colors[5]);
	polygon(5,4,0,1);
											
}
/*
cv::Point3f corners_3d[] = {
	cv::Point3f(-0.5f, -0.5f, 0),
	cv::Point3f(-0.5f,  0.5f, 0),
	cv::Point3f( 0.5f,  0.5f, 0),
	cv::Point3f( 0.5f, -0.5f, 0)
};
*/
cv::Point3f corners_3d[] = {
	cv::Point3f(-0.5f,  0.5f, 0),
	cv::Point3f(-0.5f, -0.5f, 0),
	cv::Point3f( 0.5f, -0.5f, 0),
	cv::Point3f( 0.5f,  0.5f, 0)
};
/*
float camera_matrix[] = 
	{
		1176.7492f, 0.0f,  -85.214721704f,
		0.0f, 1176.7492f, 278.66902219f,
		0.0f, 0.0f, 1.0f
	};
*/

float camera_matrix[] = 
	{
		1112.75949f, 0.0f,284.84473f,
		0.0f, 1112.75949f, -100.38948f,
		0.0f, 0.0f, 1.0f
	};
/*
float dist_coeff[] = {
		-0.560164f, 0.565883f,
		-0.009810f, 0.040420f,
		-0.538803f
	};
*/
float dist_coeff[] = {
		-0.823854f, 2.014462f,
		 0.050665f, 0.006921f,
		-3.729648f
	};
std::vector<cv::Point3f> m_corners_3d;

cv::Mat m_camera_matrix;
cv::Mat m_dist_coeff;
float m_projection_matrix[16];
float m_model_view_matrix[16];

using namespace std;


void drawAR(void * param){

	std::vector<Marker> possible_markers;
	std::vector<Marker> final_markers;
	m_corners_3d = vector<cv::Point3f>(corners_3d, corners_3d + 4);
	m_camera_matrix = cv::Mat(3, 3, CV_32FC1, camera_matrix).clone();
	m_dist_coeff = cv::Mat(1, 4, CV_32FC1, dist_coeff).clone();	

	cv::Mat image = cv::imread("/opt/git_Atom/atom_AR/img/img_8_12/ar.jpg");
//	image.resize(640,480);
	Grab_Rect GRect(image,90,30);	
	GRect.markerDetect(possible_markers);
	GRect.markerRecognize(image,possible_markers,final_markers);
	
//-----------------drawBackground
	cv::Mat image1 = cv::imread("/opt/git_Atom/atom_AR/img/img_8_12/ar.jpg");
	cv::flip(image1,image1,0);
	glDrawPixels(image1.cols,image1.rows,GL_BGR_EXT,GL_UNSIGNED_BYTE,image1.data);
	glFlush();

	cv::waitKey();

	static const GLfloat proj[] = {
		0,-2.0f/640,0,0,
		-2.0f/480,0,0,0,
		0,0,1,0,
		1,1,0,1
	};
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(proj);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//------------------

	intrinsicMatrix2ProjectionMatrix(m_camera_matrix, 640, 480, 0.01f, 100.0f, m_projection_matrix);


	printf("m_projection_matrix = ");
	printf("{\n");
	for(int i = 0;i < 16;i++){
		printf("%f,",m_projection_matrix[i]);
	}
	printf("\n}\n");
	
	glMatrixMode(GL_PROJECTION);	
	static float reflect[] = 
	{
		1,  0, 0, 0,	
		0,  1, 0, 0,
		0,  0, 1, 0,
		0,  0, 0, 1
	};

	glLoadMatrixf(reflect);
	glLoadMatrixf(m_projection_matrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glPushMatrix();
	glLineWidth(3.0f);
	
	float lineX[] = {0,0,0,1,0,0};
	float lineY[] = {0,0,0,0,1,0};
	float lineZ[] = {0,0,0,0,0,2};
	float lineT[] = {0,0,2,1,0,2};
	const GLfloat squareVertices[] = {
		-0.5f,-0.5f,
		0.5f,-0.5f,
		-0.5f,0.5f,
		0.5f,0.5f,
	};

	const GLubyte squareColors[] = {
		255,255,0,255,
		0,255,255,255,
		0,0,0,0,
		255,0,255,255,
	};
	cv::Mat r, t;
	//Marker::Marker  m = final_markers.pop_back();
		
       //Marker * Mtest = final_markers.data();
	//Mtest->estimateTransformToCamera(m_corners_3d, m_camera_matrix, m_dist_coeff, r, t);
	
	
	int i,markers_num = final_markers.size();
	
	for(i = 0;i < markers_num;i++){
	printf("m_id = %d\n",final_markers[i].m_id);
	final_markers[i].estimateTransformToCamera(m_corners_3d, m_camera_matrix, m_dist_coeff, r, t);

	extrinsicMatrix2ModelViewMatrix(r, t, m_model_view_matrix);
	

	printf("m_model_view_matrix = ");
	printf("{\n");
	for(int i = 0;i < 16;i++){
		printf("%f,",m_model_view_matrix[i]);
	}
	printf("\n}\n");

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m_model_view_matrix);
#if 0
	glVertexPointer(2,GL_FLOAT,0,squareVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4,GL_UNSIGNED_BYTE,0,squareColors);
	glEnableClientState(GL_COLOR_ARRAY);
	glDrawArrays(GL_TRIANGLE_STRIP,0,4);
#endif
//	glDisableClientState(GL_COLOR_ARRAY);

//	glDisableClientState(GL_VERTEX_ARRAY);

#if 1
	float scale = 0.5;
	glScalef(scale,scale,scale);

	glColor4f(1.0f,0.0f,0.0f,1.0f);
	glVertexPointer(3,GL_FLOAT,0,lineX);
	glDrawArrays(GL_LINES,0,2);

	glColor4f(0.0f,1.0f,0.0f,1.0f);
	glVertexPointer(3,GL_FLOAT,0,lineY);
	glDrawArrays(GL_LINES,0,2);


	glColor4f(0.0f,0.0f,1.0f,1.0f);
	glVertexPointer(3,GL_FLOAT,0,lineZ);
	glDrawArrays(GL_LINES,0,2);

	glColor4f(0.0f,0.0f,1.0f,1.0f);
	glVertexPointer(3,GL_FLOAT,0,lineT);
	glDrawArrays(GL_LINES,0,2);
#endif
#if 1
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);   //消隐
	cube();
	glFlush();
#endif
	}//markers_num (for)
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
}




int main(int argc,char ** argv){
	if (argc < 2){
		cout << "usage error" << endl;
		return 0;
	}
	cv::namedWindow(ARWindowName,cv::WINDOW_OPENGL);
	cv::resizeWindow(ARWindowName,640,480);
	cv::setOpenGlContext(ARWindowName);

	cv::setOpenGlDrawCallback(ARWindowName,drawAR,NULL);
	cv::updateWindow(ARWindowName);

	cv::waitKey();


return 0;
}


void intrinsicMatrix2ProjectionMatrix(cv::Mat& camera_matrix, float width, float height, float near_plane, float far_plane, float* projection_matrix)
{
	float f_x = camera_matrix.at<float>(0,0);
	float f_y = camera_matrix.at<float>(1,1);

	float c_x = camera_matrix.at<float>(0,2);
	float c_y = camera_matrix.at<float>(1,2);
	
	projection_matrix[0] = 2*f_x/width;
	projection_matrix[1] = 0.0f;
	projection_matrix[2] = 0.0f;
	projection_matrix[3] = 0.0f;

	projection_matrix[4] = 0.0f;
	projection_matrix[5] = 2*f_y/height;
	projection_matrix[6] = 0.0f;
	projection_matrix[7] = 0.0f;

	projection_matrix[8] = 1.0f - 2*c_x/width;
	projection_matrix[9] = 2*c_y/height - 1.0f;
	projection_matrix[10] = -(far_plane + near_plane)/(far_plane - near_plane);
	projection_matrix[11] = -1.0f;

	projection_matrix[12] = 0.0f;
	projection_matrix[13] = 0.0f;
	projection_matrix[14] = -2.0f*far_plane*near_plane/(far_plane - near_plane);
	projection_matrix[15] = 0.0f;
}


void extrinsicMatrix2ModelViewMatrix(cv::Mat& rotation, cv::Mat& translation, float* model_view_matrix)
{
	//绕X轴旋转180度，从OpenCV坐标系变换为OpenGL坐标系
#if 1
	static double d[] = 
	{
		1, 0, 0,
		0, -1, 0,
		0, 0, -1
	};
#endif
#if 0
	static double d[] = 
	{
		1, 0, 0,
		0, 1, 0,
		0, 0, -1
	};
#endif

	cv::Mat_<double> rx(3, 3, d);

	rotation = rx*rotation;
	translation = rx*translation;

	model_view_matrix[0] = rotation.at<double>(0,0);
	model_view_matrix[1] = rotation.at<double>(1,0);
	model_view_matrix[2] = rotation.at<double>(2,0);
	model_view_matrix[3] = 0.0f;

	model_view_matrix[4] = rotation.at<double>(0,1);
	model_view_matrix[5] = rotation.at<double>(1,1);
	model_view_matrix[6] = rotation.at<double>(2,1);
	model_view_matrix[7] = 0.0f;

	model_view_matrix[8] = rotation.at<double>(0,2);
	model_view_matrix[9] = rotation.at<double>(1,2);
	model_view_matrix[10] = rotation.at<double>(2,2);
	model_view_matrix[11] = 0.0f;

	model_view_matrix[12] = translation.at<double>(0, 0);
	model_view_matrix[13] = translation.at<double>(1, 0);
	model_view_matrix[14] = translation.at<double>(2, 0);
	model_view_matrix[15] = 1.0f;
}
