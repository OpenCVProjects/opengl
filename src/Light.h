#ifndef LIGHT_H_
#define LIGHT_H_

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include "Cargador.h"

using namespace std;

class Light {


	// Parámetros de los focos
	GLfloat brillo[8], luzdifusa[8][4], luzambiente[8][4], luzspecular[8][4], posicion[8][4];

	bool activados[8];
	void setVector4(GLfloat *v, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

public:
	Light();
	void switchFocos(int foco);
	~Light();
};

#endif /* LIGHT_H_ */
