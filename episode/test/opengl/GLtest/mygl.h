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
    virtual void initializeGL();
    void initWidget();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);
};

#endif // MYGL_H
