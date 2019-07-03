#include "Camara.h"

Camara::Camara() {

	// camara 0
	camara[0].eyeX=5;
	camara[0].eyeY=5;
	camara[0].eyeZ=5;
	camara[0].centerX=0;
	camara[0].centerY=0;
	camara[0].centerZ=0;
	camara[0].upX=0;
	camara[0].upY=1;
	camara[0].upZ=0;

	// camara 1
	camara[1].eyeX=0;
	camara[1].eyeY=10;
	camara[1].eyeZ=0;
	camara[1].centerX=0;
	camara[1].centerY=0;
	camara[1].centerZ=0;
	camara[1].upX=1;
	camara[1].upY=0;
	camara[1].upZ=1;

	// camara 2
	camara[2].eyeX=-5;
	camara[2].eyeY=10;
	camara[2].eyeZ=10;
	camara[2].centerX=0;
	camara[2].centerY=0;
	camara[2].centerZ=0;
	camara[2].upX=0;
	camara[2].upY=1;
	camara[2].upZ=1;

}


////////////////////////////////////////////////////////////////////////////////
Camara::Camara (int index, GLdouble eyeX,GLdouble eyeY,GLdouble eyeZ,GLdouble centerX,GLdouble centerY,GLdouble centerZ,GLdouble upX,GLdouble upY,GLdouble upZ){
	setCamara(index, eyeX,eyeY,eyeZ,centerX,centerY,centerZ,upX,upY,upZ);
}


////////////////////////////////////////////////////////////////////////////////
void Camara::setCamara(int index, GLdouble eyeX,GLdouble eyeY,GLdouble eyeZ,GLdouble centerX,GLdouble centerY,GLdouble centerZ,GLdouble upX,GLdouble upY,GLdouble upZ){
	camara[index].eyeX=eyeX;
	camara[index].eyeY=eyeY;
	camara[index].eyeZ=eyeZ;
	camara[index].centerX=centerX;
	camara[index].centerY=centerY;
	camara[index].centerZ=centerZ;
	camara[index].upX=upX;
	camara[index].upY=upY;
	camara[index].upZ=upZ;
}


////////////////////////////////////////////////////////////////////////////////
void Camara::activarCamara(int index){
	//cout << "activarCamara " << index << endl;
	gluLookAt(camara[index].eyeX, camara[index].eyeY, camara[index].eyeZ,
			camara[index].centerX, camara[index].centerY, camara[index].centerZ,
			camara[index].upX, camara[index].upY,camara[index].upZ);
}


////////////////////////////////////////////////////////////////////////////////
void Camara::modificarEyeX(int index, GLfloat valor){
	camara[index].eyeX=valor;
}


////////////////////////////////////////////////////////////////////////////////
void Camara::modificarEyeY(int index, GLfloat valor){
	camara[index].eyeY=valor;
}


////////////////////////////////////////////////////////////////////////////////
void Camara::modificarEyeZ(int index, GLfloat valor){
	camara[index].eyeZ=valor;
}


////////////////////////////////////////////////////////////////////////////////
void Camara::setFrustrum(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar){
	frustrum.fovy=fovy;
	frustrum.aspect=aspect;
	frustrum.zNear=zNear;
	frustrum.zFar=zFar;
}


////////////////////////////////////////////////////////////////////////////////
void Camara::activarFrustrum(){
	gluPerspective(frustrum.fovy,frustrum.aspect,frustrum.zNear,frustrum.zFar);
}


Camara::~Camara() {
}
