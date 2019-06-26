/*
 * Light.cpp
 *
 *  Created on: 21 jun. 2019
 *      Author: estevez
 */

#include "Light.h"

Light::Light() {
	gl_spot_exponent = 1;
	gl_spot_cutoff = 1;
//	at = GL_CONSTANT_ATTENUATION;
	brillo = 10;
}

Light::~Light() {
	// TODO Auto-generated destructor stub
}

GLfloat Light::getBrillo() {
	return brillo;
}

void Light::setBrillo(GLfloat brillo) {
	this->brillo = brillo;
}

void Light::setVector4(GLfloat *v, GLfloat v0, GLfloat v1, GLfloat v2,
		GLfloat v3) {
	v[0] = v0;
	v[1] = v1;
	v[2] = v2;
	v[3] = v3;
}
