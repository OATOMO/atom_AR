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
GLfloat vertex[][3] = {
	{-1.0,-1.0,1.0},{-1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,-1.0,1.0},
	{-1.0,-1.0,-1.0},{-1.0,1.0,-1.0},{1.0,1.0,-1.0},{1.0,-1.0,-1.0},
};

GLfloat colors[][3] = {
	{1.0,0.0,0.0},{0.0,1.0,1.0},{1.0,1.0,0.0},{0.0,1.0,0.0},
	{0.0,0.0,1.0},{1.0,1.0,1.0}
};

void polygon(int a,int b,int c,int d){
	glBegin(GL_POLYGON);
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
void reshape(void){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);
}

void glInit(void){
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(1.0,1.0,1.0);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.0,4.0,-4.0,4.0,-4.0,4.0);//正交视域体
}


void drawAR(void * param){
	glInit();	
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);   //消隐
	cube();
	//glutWireCube(0.5); //绘制立方体,设置立方体的变长
	//glutSolidCube(0.5); //绘制立方体,设置立方体的变长
	//glutSwapBuffers();//双缓冲模式,替代glFlush();
	glFlush();
	reshape();
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
	
	cv::updateWindow(ARWindowName);

	cv::waitKey();

return 0;
}
