#include "Camara.h"

Camara::Camara() {

	ifstream ifs("parametros.json");
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	const Json::Value& characters = obj["camaras"];

	for(int i = 0; i < characters.size(); i++){
		// Ejes
		camara[i].eyeX = characters[i]["ejeX"].asFloat();
		camara[i].eyeY = characters[i]["ejeY"].asFloat();
		camara[i].eyeZ = characters[i]["ejeZ"].asFloat();

		// Center
		camara[i].centerX = characters[i]["centerX"].asFloat();
		camara[i].centerY = characters[i]["centerY"].asFloat();
		camara[i].centerZ = characters[i]["centerZ"].asFloat();

		// Up
		camara[i].upX = characters[i]["upX"].asFloat();
		camara[i].upY = characters[i]["upY"].asFloat();
		camara[i].upZ = characters[i]["upZ"].asFloat();
	}
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
void Camara::zoomIn(int index, GLfloat valor){
	if(camara[index].eyeX != 0)
		camara[index].eyeX = camara[index].eyeX + valor;
	if(camara[index].eyeY != 0)
		camara[index].eyeY = camara[index].eyeY + valor;
	if(camara[index].eyeZ != 0)
		camara[index].eyeZ = camara[index].eyeZ + valor;
}

////////////////////////////////////////////////////////////////////////////////
void Camara::zoomOut(int index, GLfloat valor){
	if(camara[index].eyeX != 0)
		camara[index].eyeX = camara[index].eyeX - valor;
	if(camara[index].eyeY != 0)
		camara[index].eyeY = camara[index].eyeY - valor;
	if(camara[index].eyeZ != 0)
		camara[index].eyeZ = camara[index].eyeZ - valor;
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
