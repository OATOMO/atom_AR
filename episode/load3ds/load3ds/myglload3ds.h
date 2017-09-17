#ifndef MYGLLOAD3DS_H
#define MYGLLOAD3DS_H

#include "cmodel3ds.h"
#include <QGLWidget>

class myGLLoad3ds:public QGLWidget
{
	Q_OBJECT
public:
	myGLLoad3ds();
	myGLLoad3ds(QWidget * parent = 0);
protected:
	virtual void initializeGL();
	virtual void resizeGL(int width, int height);
	virtual void paintGL();
private:
	CModel3DS * monkey;
};

#endif // MYGLLOAD3DS_H
