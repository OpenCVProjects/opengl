#ifndef CARGADOR_H_
#define CARGADOR_H_

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <jsoncpp/json/json.h>

using namespace std;

static const string JSONFILE = "Parametros.json";

class Cargador{

  Json::Reader reader;
  Json::Value obj;


public:
  Cargador();
  void cargarFocos(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
  ~Cargador();

};

#endif /* CARGADOR_H_ */
