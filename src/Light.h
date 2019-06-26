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

//enum atenuacion{ 	GL_CONSTANT_ATTENUATION,
//		GL_LINEAR_ATTENUATION, GL_QUADRATIC_ATTENUATION
//				} ;


class Light {

	private:
	//SCALAR PROPERTIES
		int gl_spot_exponent;
		int gl_spot_cutoff;
//	atenuacion at;

	//VECTOR PROPERTIES
//	float gl_ambient[4];
//	float gl_diffuse[4];
//	float gl_specular[4];
//	float gl_position[4];
//	float gl_spot_direction[3];

	GLfloat brillo;
		void setVector4(GLfloat *v, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

public:
	Light();
	GLfloat getBrillo();
//	GLfloat getMaterialDifuso();
//	GLfloat getLuzDifusa();
	void setBrillo(GLfloat brillo);

	virtual ~Light();


};

#endif /* LIGHT_H_ */


