#ifndef MODELO_H_
#define MODELO_H_

#include "Cara.h"
#include "Punto3D.h"
#include <cstdio>
#include <cstring>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <jsoncpp/json/json.h>

using namespace std;

typedef vector<Cara> ListaFace;
typedef vector<Punto3D> ListaVertex;

enum tipoVista {
	wired, flat, smooth
};

class Modelo {

private:
	ListaVertex ListaPuntos3D;
	ListaFace ListaCaras;

	int _NumCaras;
	int _NumVertices;

	void setVector4(GLfloat *v, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

public:

	GLfloat material_difuso[4], material_ambiente[4], material_specular[4],
			material_emission[4];

	float alpha;
	float beta;
	float escala;

	float brillo;

	// Omega (w) para la traslación
	float omega;

	// Parametros de rotación
	float rotX;
	float rotY;
	float rotZ;

	// Parametros de la traslación
	float trasX;
	float trasY;
	float trasZ;

	// Radio de giro con respecto al sol
	float radio;

	vector<Modelo> satelites;

	Modelo();
	~Modelo();
	Modelo(const int ncaras, const int nvertices);
	void inicializarParametros();
	int getNCaras();
	void setNCaras(const int val);
	int getNVertices();
	void setNVertices(const int val);
	void Load_Model(char fileName[50]);
	void Draw_Model(tipoVista iForma, float scale_from_editor, float zoom);
	void cargarParametros(string modelName);
	float getEscala();
	float getAlpha();
	void setAlpha(float alpha);
	float getBeta();
	void setBeta(float beta);
	void getMatAmbient(GLfloat *v);
	int getBrillo();
};

#endif /* MODELO_H_ */
