#ifndef CAMARA_H_
#define CAMARA_H_
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>

using namespace std;

typedef struct {
	GLdouble eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ;
} TCamara;


typedef struct {
	GLdouble fovy, aspect, zNear, zFar;
} TFrustrum;


class Camara {
	TCamara camara[5];
	TFrustrum frustrum;

public:
	Camara();
	Camara(int index, GLdouble eyeX,GLdouble eyeY,GLdouble eyeZ,GLdouble centerX,GLdouble centerY,GLdouble centerZ,GLdouble upX,GLdouble upY,GLdouble upZ);
	void activarCamara(int index);
	void modificarEyeX(int index, GLfloat valor);
	void modificarEyeY(int index, GLfloat valor);
	void modificarEyeZ(int index, GLfloat valor);
	void setCamara(int index, GLdouble eyeX,GLdouble eyeY,GLdouble eyeZ,GLdouble centerX,GLdouble centerY,GLdouble centerZ,GLdouble upX,GLdouble upY,GLdouble upZ);
	void setFrustrum(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
	void activarFrustrum();
	~Camara();
};

#endif /* CAMARA_H_ */
