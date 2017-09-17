#include "myglload3ds.h"

myGLLoad3ds::myGLLoad3ds(QWidget * parent):QGLWidget(parent)
{
	try{
				monkey = new CModel3DS("monkey.3ds");
		}
	catch(std::string error_str){
				std::cerr;
				exit(1);
		}
}

// Initialize some OpenGL settings
void myGLLoad3ds::initializeGL()
{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glShadeModel(GL_SMOOTH);

		// Enable lighting and set the position of the light
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		GLfloat pos[] = { 0.0, 4.0, 4.0 };
		glLightfv(GL_LIGHT0, GL_POSITION, pos);

		// Generate Vertex Buffer Objects
		monkey->CreateVBO();
}


// Reset viewport and projection matrix after the window was resized
void myGLLoad3ds::resizeGL(int width, int height)
{
		// Reset the viewport
		glViewport(0, 0, width, height);
		// Reset the projection and modelview matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// 10 x 10 x 10 viewing volume
		glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
}

// Do all the OpenGL rendering
void myGLLoad3ds:: paintGL()
{
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw our model
		monkey->Draw();

		// We don't need to swap the buffers, because QT does that automaticly for us
}
