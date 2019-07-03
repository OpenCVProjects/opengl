#include "Light.h"


////////////////////////////////////////////////////////////////////////////////
// Definimos los diferentes focos.
Light::Light() {

	// Foco 1.
	brillo[1]=10;
	setVector4(luzdifusa[1], 1.0, 1.0, 1.0, 1.0);
	setVector4(luzambiente[1], 0.0, 0.0, 0.0, 1.0);
	setVector4(luzspecular[1], 1.0, 1.0, 1.0, 1.0);
	setVector4(posicion[1], 10.0, 20.0, 20.0, 0.0);


	// Foco 2.
	brillo[2]=20;
	setVector4(luzdifusa[2], 0.5, 0.8, 0.0, 1.0);
	setVector4(luzambiente[2], 0.50, 0.50, 0.50, 1.0);
	setVector4(luzspecular[2], 0.20, 0.20, 0.20, 1.0);
	setVector4(posicion[2], 2.0,1.0,-6.0, 0.0);


	// Foco 3.
	brillo[3]=20;
	setVector4(luzdifusa[3], 0.5, 0.8, 0.0, 1.0);
	setVector4(luzambiente[3], 0.50, 0.50, 0.50, 1.0);
	setVector4(luzspecular[3], 0.20, 0.20, 0.20, 1.0);
	setVector4(posicion[3], 2.0,1.0,-6.0, 0.0);

	// Foco 4.
	brillo[4]=20;
	setVector4(luzdifusa[4], 0.5, 0.8, 0.0, 1.0);
	setVector4(luzambiente[4], 0.50, 0.50, 0.50, 1.0);
	setVector4(luzspecular[4], 0.20, 0.20, 0.20, 1.0);
	setVector4(posicion[4], 2.0,1.0,-6.0, 0.0);

	// Foco 5.
	brillo[5]=20;
	setVector4(luzdifusa[5], 0.5, 0.8, 0.0, 1.0);
	setVector4(luzambiente[5], 0.50, 0.50, 0.50, 1.0);
	setVector4(luzspecular[5], 0.20, 0.20, 0.20, 1.0);
	setVector4(posicion[5], 2.0,1.0,-6.0, 0.0);

	// Foco 6.
	brillo[6]=20;
	setVector4(luzdifusa[6], 0.5, 0.8, 0.0, 1.0);
	setVector4(luzambiente[6], 0.50, 0.50, 0.50, 1.0);
	setVector4(luzspecular[6], 0.20, 0.20, 0.20, 1.0);
	setVector4(posicion[6], 2.0,1.0,-6.0, 0.0);

	// Foco 7.
	brillo[7]=20;
	setVector4(luzdifusa[7], 0.5, 0.8, 0.0, 1.0);
	setVector4(luzambiente[7], 0.50, 0.50, 0.50, 1.0);
	setVector4(luzspecular[7], 0.20, 0.20, 0.20, 1.0);
	setVector4(posicion[7], 2.0,1.0,-6.0, 0.0);

	for (int var = 0; var < 8; ++var) {
		activados[var]=false;
	}
	glEnable(GL_LIGHTING);
	switchFocos(0);

}


////////////////////////////////////////////////////////////////////////////////
void Light::setVector4(GLfloat *v, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	v[0] = v0;
	v[1] = v1;
	v[2] = v2;
	v[3] = v3;
}


////////////////////////////////////////////////////////////////////////////////
void Light::switchFocos(int light){
	
	if (!activados[light]){
		if (light>0){
			glLightfv(GL_LIGHT0+light, GL_DIFFUSE, luzdifusa[light]);
			glLightfv(GL_LIGHT0+light, GL_AMBIENT, luzambiente[light]);
			glLightfv(GL_LIGHT0+light, GL_SPECULAR, luzspecular[light]);
			glLightfv(GL_LIGHT0+light, GL_POSITION, posicion[light]);
		}

		glEnable(GL_LIGHT0+light);
		activados[light]=true;
	}
	else{
		activados[light]=false;
		glDisable(GL_LIGHT0+light);
	}

}


Light::~Light() {
}
