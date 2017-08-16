#include "drawgl.h"
#include <QWidget>


drawGL::drawGL(QWidget * parent)
	:QOpenGLWidget(parent)
{
}

drawGL::~drawGL(){

}

void drawGL::initializeGL(){
	//初始化OpenGL函数
	initializeOpenGLFunctions();

	//设置全局变量
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void drawGL::resizeGL(int width, int height){
	//未使用
	Q_UNUSED(width);
	Q_UNUSED(height);
}

void drawGL::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);
		glVertex2f(0,0);
		glVertex2f(1,0);
		glVertex2f(1,1);
		glVertex2f(0,1);
	glEnd();
	glFlush();
}


