#include "mygl.h"
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <QImage>

myGL::myGL(QWidget * parent):QGLWidget(parent)
{
	qDebug() << "myGL";
    initWidget();
	initializeGL();
}


void myGL::initializeGL(){
	qDebug() << "initializeGL";
	glEnable(GL_TEXTURE_2D);//启用纹理
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

void myGL::initWidget(){
	qDebug() << "initWidget";
	setGeometry( 400, 200, 640, 480 );
	setWindowTitle(tr("opengl demo"));
}
GLuint texturFrame;
void myGL::paintGL(){
	qDebug() << "paintGL";

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	/*
	glTranslatef( -1.5,  0.0, -6.0 );

	glBegin( GL_QUADS );
	glVertex3f(  -1.0,  1.0,  0.0 );
	glVertex3f(  1.0,  1.0,  0.0 );
	glVertex3f(  1.0, -1.0,  0.0 );
	glVertex3f( -1.0, -1.0,  0.0 );
	glEnd();

	glTranslatef(  3.0,  0.0,  0.0 );

	glBegin( GL_TRIANGLES );
	qDebug() << "this is a paintGL test!";
	glVertex3f(  0.0,  1.0,  0.0 );
	glVertex3f( -1.0, -1.0,  0.0 );
	glVertex3f(  1.0, -1.0,  0.0 );
glEnd();
	*/

#if 0
	cv::Mat frame = cv::imread("/home/atom/Desktop/cube.bmp");
	QImage buf, tex;
	//将Mat类型转换成QImage
	buf = QImage((const unsigned char*)frame.data, frame.cols, frame.rows, frame.cols * frame.channels(), QImage::Format_RGB888);
	tex = QGLWidget::convertToGLFormat(buf);
	glGenTextures(1, &texturFrame);//对应图片的纹理定义
	glBindTexture(GL_TEXTURE_2D, texturFrame);//进行纹理绑定
	//纹理创建
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
		GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTranslatef(3.2f, -0.6f, -100);//讲显示背景沿Z轴向后移动足够距离，防止遮挡渲染物体
//		glScalef(8.35f,8.35f,1.0f);//平移 放大 实现窗口填充-
	glBindTexture(GL_TEXTURE_2D, texturFrame);
		glBegin(GL_QUADS);//绘制图形接口，与glEnd()对应

		glTexCoord2f(0.0, 0.0); glVertex3f(-4, -3, 0);//
		glTexCoord2f(1.0, 0.0); glVertex3f(4, -3, 0);
		glTexCoord2f(1.0, 1.0); glVertex3f(4, 3, 0);
		glTexCoord2f(0.0, 1.0); glVertex3f(-4, 3, 0);

		glEnd();
#endif
}

void myGL::resizeGL(int width, int height){
	qDebug() << "resizeGL";
	if(0 == height) {
			height = 1;
	}

	glViewport(0, 0, (GLint)width, (GLint)height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	 //  gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0);

	GLdouble aspectRatio = (GLfloat)width/(GLfloat)height;
	GLdouble zNear = 0.1;
	GLdouble zFar = 100.0;

	GLdouble rFov = 45.0 * 3.14159265 / 180.0;
	 glFrustum( -zNear * tan( rFov / 2.0 ) * aspectRatio,
			   zNear * tan( rFov / 2.0 ) * aspectRatio,
			   -zNear * tan( rFov / 2.0 ),
			   zNear * tan( rFov / 2.0 ),
			   zNear, zFar );

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}
