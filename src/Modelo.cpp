#include "Modelo.h"

Modelo::Modelo() {
	_NumCaras = 0;
	_NumVertices = 0;
	inicializarParametros();
}

////////////////////////////////////////////////////////////////////////////////
Modelo::Modelo(const int ncaras, const int nvertices) {
	_NumCaras = ncaras;
	_NumVertices = nvertices;
}

////////////////////////////////////////////////////////////////////////////////
void Modelo::setVector4(GLfloat *v, GLfloat v0, GLfloat v1, GLfloat v2,
		GLfloat v3) {
	v[0] = v0;
	v[1] = v1;
	v[2] = v2;
	v[3] = v3;
}

////////////////////////////////////////////////////////////////////////////////
void Modelo::inicializarParametros() {
// Cargamos los parámetros del json

}

////////////////////////////////////////////////////////////////////////////////
int Modelo::getNCaras() {
	return _NumCaras;
}

////////////////////////////////////////////////////////////////////////////////
void Modelo::setNCaras(const int val) {
	_NumCaras = val;
}

////////////////////////////////////////////////////////////////////////////////
int Modelo::getNVertices() {
	return _NumVertices;
}

////////////////////////////////////////////////////////////////////////////////
void Modelo::setNVertices(const int val) {
	_NumVertices = val;
}

////////////////////////////////////////////////////////////////////////////////
// Función para cargar el modelo.
void Modelo::Load_Model(char fileName[50]) {
	FILE *fich;
	int NVertex, NFaces, VertexNumber, FaceNumber, N, A, B, C;
	float X, Y, Z, ax, ay, az, bx, by, bz, len;
	TNormal Normal;
	char cad1[20], cad2[20], cad3[20], cad4[20];
	char cadena[100];

	// Apertura para lectura.
	if ((fich = fopen("Esfera.asc", "r")) == NULL) {
		cout << " Error en la apertura. Es posible que el fichero no exista \n "
				<< endl;
		exit(1);
	}

	while (fgets(cadena, 100, fich) != NULL) {
		if (strncmp(cadena, "Named", 5) == 0) // Nvertex and NFaces in file
				{
			fscanf(fich, "%[Tri-mesh A-Za-z:-,: ]%d%[ ]%[Faces]:%d\n", cad1,
					&NVertex, cad2, cad3, &NFaces);
			setNCaras(NFaces);
			setNVertices(NVertex);
		}
		ListaCaras.resize(getNCaras());
		ListaPuntos3D.resize(getNVertices());
		if (strncmp(cadena, "Vertex list:", 12) == 0) // Vertex List in file
			for (N = 1; N <= NVertex; N++) {
				fscanf(fich, "%[A-Za-z ]%d: %[X:] %f %[Y:] %f %[Z:] %f    \n",
						cad1, &VertexNumber, cad2, &X, cad3, &Y, cad4, &Z);
				ListaPuntos3D[VertexNumber] = Punto3D(X, Y, Z);

			}
		if (strncmp(cadena, "Face list:", 10) == 0) // Face List in model file
			for (N = 0; N < NFaces; N++) {
				fscanf(fich, "%[Face]%d: %[A:]%d %[B:]%d %[C:]%d\n", cad1,
						&FaceNumber, cad2, &A, cad3, &B, cad4, &C);
				fgets(cadena, 100, fich);

				// Cálculo del vector normal a cada cara (Nx,Ny,Nz).
				ListaCaras[FaceNumber] = Cara(A, B, C, Normal);
				ax = ListaPuntos3D[ListaCaras[FaceNumber].getA()].getX()
						- ListaPuntos3D[ListaCaras[FaceNumber].getB()].getX(); //  X[A] - X[B];
				ay = ListaPuntos3D[ListaCaras[FaceNumber].getA()].getY()
						- ListaPuntos3D[ListaCaras[FaceNumber].getB()].getY(); //  Y[A] - Y[B];
				az = ListaPuntos3D[ListaCaras[FaceNumber].getA()].getZ()
						- ListaPuntos3D[ListaCaras[FaceNumber].getB()].getZ(); //  Z[A] - Z[B];
				bx = ListaPuntos3D[ListaCaras[FaceNumber].getB()].getX()
						- ListaPuntos3D[ListaCaras[FaceNumber].getC()].getX(); //  X[B] - X[C];
				by = ListaPuntos3D[ListaCaras[FaceNumber].getB()].getY()
						- ListaPuntos3D[ListaCaras[FaceNumber].getC()].getY(); //  Y[B] - Y[C];
				bz = ListaPuntos3D[ListaCaras[FaceNumber].getB()].getZ()
						- ListaPuntos3D[ListaCaras[FaceNumber].getC()].getZ(); //  Z[B] - Z[C];
				Normal.x = (ay * bz) - (az * by);
				Normal.y = (az * bx) - (ax * bz);
				Normal.z = (ax * by) - (ay * bx);
				len = sqrt(
						(Normal.x * Normal.x) + (Normal.y * Normal.y)
								+ (Normal.z * Normal.z));
				Normal.x = Normal.x / len;
				Normal.y = Normal.y / len;
				Normal.z = Normal.z / len;
				ListaCaras[FaceNumber] = Cara(A, B, C, Normal);
			}
	}
	fclose(fich);

}

////////////////////////////////////////////////////////////////////////////////
void Modelo::Draw_Model(tipoVista iForma, float scale_from_editor, float zoom) {

	switch (iForma) {
	case wired:
		glDisable(GL_LIGHTING);
		for (int FaceNumber = 0; FaceNumber < _NumCaras; FaceNumber++) {
			glBegin(GL_LINES);
			glVertex3f(
					ListaPuntos3D[ListaCaras[FaceNumber].getA()].getX()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getA()].getY()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getA()].getZ()
							* scale_from_editor * zoom);
			glVertex3f(
					ListaPuntos3D[ListaCaras[FaceNumber].getB()].getX()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getB()].getY()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getB()].getZ()
							* scale_from_editor * zoom);
			glVertex3f(
					ListaPuntos3D[ListaCaras[FaceNumber].getC()].getX()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getC()].getY()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getC()].getZ()
							* scale_from_editor * zoom);
			glVertex3f(
					ListaPuntos3D[ListaCaras[FaceNumber].getA()].getX()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getA()].getY()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getA()].getZ()
							* scale_from_editor * zoom);
			glEnd();

		}

		break;

	case flat:
		glShadeModel(GL_FLAT);
		glEnable(GL_LIGHTING);

		for (int FaceNumber = 0; FaceNumber < _NumCaras; FaceNumber++) {
			glBegin(GL_TRIANGLES);

			// Ajustamos la normal de la cara
			glNormal3f(ListaCaras[FaceNumber].getNormalX(),
					ListaCaras[FaceNumber].getNormalY(),
					ListaCaras[FaceNumber].getNormalZ());

			glVertex3f(
					ListaPuntos3D[ListaCaras[FaceNumber].getA()].getX()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getA()].getY()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getA()].getZ()
							* scale_from_editor * zoom);
			glVertex3f(
					ListaPuntos3D[ListaCaras[FaceNumber].getB()].getX()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getB()].getY()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getB()].getZ()
							* scale_from_editor * zoom);
			glVertex3f(
					ListaPuntos3D[ListaCaras[FaceNumber].getC()].getX()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getC()].getY()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getC()].getZ()
							* scale_from_editor * zoom);

			glEnd();
		}
		break;

	case smooth:
		glShadeModel(GL_SMOOTH);
		glEnable(GL_LIGHTING);

		for (int FaceNumber = 0; FaceNumber < _NumCaras; FaceNumber++) {
			glBegin(GL_TRIANGLES);

			// Ajustamos la normal para cada punto
			glNormal3f(
					ListaPuntos3D[ListaCaras[FaceNumber].getA()].getX()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getA()].getY()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getA()].getZ()
							* scale_from_editor * zoom);
			glVertex3f(
					ListaPuntos3D[ListaCaras[FaceNumber].getA()].getX()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getA()].getY()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getA()].getZ()
							* scale_from_editor * zoom);

			glNormal3f(
					ListaPuntos3D[ListaCaras[FaceNumber].getB()].getX()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getB()].getY()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getB()].getZ()
							* scale_from_editor * zoom);
			glVertex3f(
					ListaPuntos3D[ListaCaras[FaceNumber].getB()].getX()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getB()].getY()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getB()].getZ()
							* scale_from_editor * zoom);

			glNormal3f(
					ListaPuntos3D[ListaCaras[FaceNumber].getC()].getX()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getC()].getY()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getC()].getZ()
							* scale_from_editor * zoom);
			glVertex3f(
					ListaPuntos3D[ListaCaras[FaceNumber].getC()].getX()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getC()].getY()
							* scale_from_editor * zoom,
					ListaPuntos3D[ListaCaras[FaceNumber].getC()].getZ()
							* scale_from_editor * zoom);
			glEnd();
		}
		break;
	}
}

void Modelo::cargarParametros(string modelName) {
	cout << "Cargar parámetros de " << modelName << endl;
	int i = 0;

	ifstream ifs("parametros.json");
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);
	const Json::Value& characters = obj[modelName];

	this->escala = characters["escala"].asFloat();
	this->alpha = characters["alpha"].asFloat();
	this->beta = characters["beta"].asFloat();

	// Cargamos los materiales ambiente
	this->material_ambiente[0] = characters["material"]["ambient"][0].asFloat();
	this->material_ambiente[1] = characters["material"]["ambient"][1].asFloat();
	this->material_ambiente[2] = characters["material"]["ambient"][2].asFloat();
	this->material_ambiente[3] = characters["material"]["ambient"][3].asFloat();

	// difuso
	this->material_difuso[0] = characters["material"]["diffuse"][0].asFloat();
	this->material_difuso[1] = characters["material"]["diffuse"][1].asFloat();
	this->material_difuso[2] = characters["material"]["diffuse"][2].asFloat();
	this->material_difuso[3] = characters["material"]["diffuse"][3].asFloat();

	// specular
	this->material_specular[0] =
			characters["material"]["specular"][0].asFloat();
	this->material_specular[1] =
			characters["material"]["specular"][1].asFloat();
	this->material_specular[2] =
			characters["material"]["specular"][2].asFloat();
	this->material_specular[3] =
			characters["material"]["specular"][3].asFloat();

	// brillo
	this->brillo = characters["material"]["shininess"].asFloat();

	// Asuntos de rotación y traslación
	this->omega = characters["omega"].asFloat();

	this->rotX = characters["rotX"].asFloat();
	this->rotY = characters["rotY"].asFloat();
	this->rotZ = characters["rotZ"].asFloat();

	this->radio = characters["radio"].asFloat();
}

float Modelo::getEscala() {
	return this->escala;
}

float Modelo::getAlpha() {
	return this->alpha;
}

float Modelo::getBeta() {
	return this->beta;
}

void Modelo::setAlpha(float alpha) {
	this->alpha = alpha;
}

void Modelo::setBeta(float beta) {
	this->beta = beta;
}

void Modelo::getMatAmbient(GLfloat *v) {
	v = material_difuso;
}

int Modelo::getBrillo() {
	return this->brillo;
}

Modelo::~Modelo() {
}
