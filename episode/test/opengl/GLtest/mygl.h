#ifndef MYGL_H
#define MYGL_H
#include <QGLWidget>
#include <QWidget>
#include <QtWidgets>

#define MIN_LENGTH 35
#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480


class myGL:public QGLWidget
{
	Q_OBJECT
public:
	myGL(QWidget * parent = 0);
	~myGL(){};
	//cam


protected:
    virtual void initializeGL();
    void initWidget();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);
};

#endif // MYGL_H
