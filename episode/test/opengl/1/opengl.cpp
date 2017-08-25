#include <opencv2/opencv.hpp>
#include <GL/glut.h>
#include <GL/glu.h>
#define ARWindowName "ARWindowName"


/*void drawAR(void * param){
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
		glVertex2f(-0.5,-0.5);
		glVertex2f(0.5,-0.5);
		glVertex2f(0.5,0.5);
		glVertex2f(-0.5,0.5);
	glEnd();

	glFlush();
}
*/
void glInit(void){
	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(1.0,1.0,1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);//正交视域体
}

void drawAR(void * param){
	glInit();	
	glClear(GL_COLOR_BUFFER_BIT);
	glutWireCube(0.5); //绘制立方体,设置立方体的变长
	//glutSolidCube(0.5); //绘制立方体,设置立方体的变长
//	glutSwapBuffers();//双缓冲模式,替代glFlush();
	glFlush();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);
}



int main(int argc,char ** argv){
	glutInit(&argc,argv);
	
	
	//要在创建的窗口中使用OPENGL
	cv::namedWindow(ARWindowName,cv::WINDOW_OPENGL);
	//
	cv::resizeWindow(ARWindowName,640,480);
	//为窗口设置绘图上下文
	cv::setOpenGlContext(ARWindowName);

	
	//注册画图回调函数
	cv::setOpenGlDrawCallback(ARWindowName,drawAR,NULL);
	
	//cv::updateWindow(ARWindowName);

	cv::waitKey();

return 0;
}
