#include "mytexture.h"
#include <opencv2/opencv.hpp>
#include <QDebug>

myTexture::myTexture(QWidget * parent):QGLWidget(parent){
//	initWidget();
	initializeGL();
	clk.start(30);
	QObject::connect(&clk,SIGNAL(timeout()),this,SLOT(updateWindow()));
}

myTexture::~myTexture(){
}

void myTexture::initializeGL(){
	loadGLTextures();
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0,0.0,0.0,0.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
}

void myTexture::initWidget(){
	setGeometry(0,200, 640, 480);
	setWindowTitle(tr("opengl demo"));
}

void myTexture::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();

//	glTranslatef(10,10,0);
	glTranslatef(0,0,-1.0);
//	glScalef(8.35f,8.35f,1.0f);//平移 放大 实现窗口填充-


#if 0
	glBindTexture(GL_TEXTURE_2D, textur);
		glBegin(GL_QUADS);//绘制图形接口，与glEnd()对应
//		glTexCoord2f(0.0, 0.0); glVertex3f(-4, -3, 0);//
//		glTexCoord2f(1.0, 0.0); glVertex3f(4, -3, 0);
//		glTexCoord2f(1.0, 1.0); glVertex3f(4, 3, 0);
//		glTexCoord2f(0.0, 1.0); glVertex3f(-4, 3, 0);
		glTexCoord2f(0.0, 0.0); glVertex3f(-1, -1, 0);//
		glTexCoord2f(1.0, 0.0); glVertex3f(1, -1, 0);
		glTexCoord2f(1.0, 1.0); glVertex3f(1, 1, 0);
		glTexCoord2f(0.0, 1.0); glVertex3f(-1, 1, 0);
	glEnd();
#endif

	GLfloat w = 640;
	GLfloat h = 480;
#if 1
	const GLfloat bgTextureVertices[] = { 0, 0, w, 0, 0, h, w, h };
	const GLfloat bgTextureCoords[]   = { 1, 0, 1, 1, 0, 0, 0, 1 };
	const GLfloat proj[] = { 0, -2.f/w, 0, 0, -2.f/h, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1 };
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(proj);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textur);

	// Update attribute values.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	  glVertexPointer(2, GL_FLOAT, 0, bgTextureVertices);
	  glTexCoordPointer(2, GL_FLOAT, 0, bgTextureCoords);

	  glColor4f(1,1,1,1);
	  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	  glDisableClientState(GL_VERTEX_ARRAY);
	  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
#endif

//	cv::Mat image1 = cv::imread("/opt/git_Atom/atom_AR/img/img_8_12/arok2.jpg");
//	qDebug() << image1.channels();
//	cv::flip(image1,image1,0);
//	glDrawPixels(image1.cols,image1.rows,GL_BGR_EXT,GL_UNSIGNED_BYTE,image1.data);
//	cv::imshow("1",image1);
//	cv::waitKey();

}


void myTexture::resizeGL(int width, int height){
	if (0 == height) {
	   height = 1;
	}

	glViewport(0, 0, (GLint)width, (GLint)height);

//	glMatrixMode(GL_PROJECTION);

//	glLoadIdentity();

//	gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0);

//	static const GLfloat proj[] = {
//			0,-2.0f/640,0,0,
//			-2.0f/480,0,0,0,
//			0,0,1,0,
//			1,1,0,1
//		};
//		glMatrixMode(GL_PROJECTION);
//		glLoadMatrixf(proj);

//	cv::Mat backImage =


	//text
//		GLfloat buffer[16];
//		glGetFloatv( GL_PROJECTION_MATRIX, buffer);
//		for(int i = 0;i < 16;i++)
//			qDebug() << buffer[i];
	//

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myTexture::updateWindow()
{
	m_x += 1;
	m_y += 2;
	m_z += 2;
	updateGL();//刷新界面
}


void myTexture::loadGLTextures()
{

//	if (!buf.load("/home/atom/Desktop/cube.bmp"))
	if (!buf.load("/opt/git_Atom/atom_AR/img/img_8_12/arok2.jpg"))
	{
		qWarning("load image failed!");
		QImage dummy(640, 480, QImage::Format_RGB32);
		dummy.fill(Qt::red);
		buf = dummy;

	}


	tex = QGLWidget::convertToGLFormat(buf);
	glGenTextures(1, &textur);
	glBindTexture(GL_TEXTURE_2D, textur);

	cv::Mat new_back =	cv::imread("/opt/git_Atom/atom_AR/img/img_8_12/arok2.jpg");
	qDebug() << "new_back.channels() = " << new_back.channels();
	glTexImage2D(GL_TEXTURE_2D, 0, 3, /*new_back.rows*/640, /*new_back.cols*/480, 0,
		GL_RGB, GL_UNSIGNED_BYTE, new_back.data);
//	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
//		GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

