#ifndef CMODEL3DS_H
#define CMODEL3DS_H

#include <unistd.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>

#include <lib3ds/file.h>
#include <lib3ds/mesh.h>
#include <QGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLWidget>
#include <QGLFunctions>
//#include <GL/glew.h>
#include <GL/gl.h>


class CModel3DS
{
public:
	CModel3DS();
	CModel3DS(std:: string filename);
	virtual void Draw() const;
	virtual void CreateVBO();
	virtual ~CModel3DS();
protected:
	void GetFaces();
	unsigned int m_TotalFaces;
	Lib3dsFile * m_model;
	GLuint m_VertexVBO, m_NormalVBO;
};

#endif // CMODEL3DS_H
