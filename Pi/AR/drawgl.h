#ifndef DRAWGL_H
#define DRAWGL_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLWindow>

class drawGL:public QOpenGLWidget,protected QOpenGLFunctions
{
	Q_OBJECT
public:
	drawGL(QWidget * parent = 0);
	~drawGL();
protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
};

#endif // DRAWGL_H
