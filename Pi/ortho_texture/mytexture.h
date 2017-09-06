#ifndef MYCUBE_H
#define MYCUBE_H

#include <QTimer>
#include <QGLWidget>
#include <QWidget>
#include <cmath>

class myTexture:public QGLWidget
{
	Q_OBJECT
public:
	myTexture(QWidget * parent = 0);
	~myTexture();

	QTimer clk;
	float m_x,m_y,m_z;
	GLuint textur;
	QImage tex;
	QImage buf;

protected:
	void initializeGL();
	void initWidget();
	void paintGL();
	void resizeGL(int width,int height);
	void loadGLTextures();
private slots:
	void updateWindow();

};

#endif // MYCUBE_H
