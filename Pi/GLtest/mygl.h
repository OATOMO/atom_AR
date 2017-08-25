#ifndef MYGL_H
#define MYGL_H
#include <QGLWidget>
#include <QWidget>
#include <QtWidgets>




class myGL:public QGLWidget
{
	Q_OBJECT
public:
	myGL(QWidget * parent = 0);
	~myGL(){};
protected:
	void initializeGL();
	void initWidget();
	void paintGL();
	void resizeGL(int width, int height);
};

#endif // MYGL_H
