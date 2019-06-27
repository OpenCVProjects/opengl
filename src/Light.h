/*
 * Light.h
 *
 *  Created on: 21 jun. 2019
 *      Author: estevez
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

class Light {

	private:
	//SCALAR PROPERTIES
		int gl_spot_exponent;
		int gl_spot_cutoff;

	//VECTOR PROPERTIES
		void setVector4(GLfloat *v, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

		GLfloat brillo;


public:
	Light();
	GLfloat getBrillo();

	void setBrillo(GLfloat brillo);

	virtual ~Light();


};

#endif /* LIGHT_H_ */


