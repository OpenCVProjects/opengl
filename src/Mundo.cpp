#include "Mundo.h"

Mundo::Mundo() {
	tiempoSintetico = 0.0;
	width = 800;
	height = 800;
	aspect = width / height;
	angulo = 0;
	window = 0;
	tamanio = 100;

	// Factor para el tamaño del modelo.
	escalaGeneral = 0.005;

	// Rotación del ratón
	alpha = 0;
	beta = 0;

	// Variables para la gestion del ratón.
	xold = 0;
	yold = 0;
	zoom = 1.0;

	iDibujo = 4;
	iFondo = 0;

	loadFocos();
	loadCamaras();

}

void Mundo::drawAxis(void) {

	// Inicializamos
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glClearColor(0.f, 0.f, 0.0f, 0.f);

	// Eje X Rojo
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	// Eje Y Verde
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	// Eje Z Azul
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);

	glClearColor(0.f, 0.f, 0.0f, 0.f);

	glEnd();
	glEnable(GL_LIGHTING);
}

void Mundo::drawModel(Modelo modelo) {
	glDisable(GL_LIGHTING);
	drawAxis();

	glMaterialfv(GL_FRONT, GL_AMBIENT, modelo.material_ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, modelo.material_difuso);
	glMaterialfv(GL_FRONT, GL_SPECULAR, modelo.material_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, modelo.brillo);

	modelo.Draw_Model(getIForma(), modelo.getEscala(), zoom);
	glEnable(GL_LIGHTING);
}

void Mundo::pintarOribta(float radio) {
	glDisable(GL_LIGHTING);
	glColor3f(colores[getIDibujo()][0], colores[getIDibujo()][1],
			colores[getIDibujo()][2]);
	glBegin(GL_LINE_STRIP);
	for (float angle = 0; angle < 360; angle += 0.1f)
		glVertex3f(cosf(angle) * radio, 0, sinf(angle) * radio);
	glEnd();
	glEnable(GL_LIGHTING);
}

void Mundo::display(void) {

	glClearDepth(1.0);
	glClearColor(colores[getIFondo()][0], colores[getIFondo()][1],
			colores[getIFondo()][2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// elegimos la proyección
	gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 2000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* Colocamos la camara en el punto deseado */
	camaras->activarCamara(activeCamera);

	// Manejo del raton
	glRotatef(alpha, 1.0f, 0.0f, 0.0f);
	glRotatef(beta, 0.0f, 1.0f, 0.0f);

	// Establecemos el color del Modelo.
	glColor3f(colores[getIDibujo()][0], colores[getIDibujo()][1],
			colores[getIDibujo()][2]);

	// Recorremos el vector de modelos pintando en cada caso
	for (itModelos = 0; itModelos < modelos.size(); itModelos++) {

		pintarOribta(modelos[itModelos].radio);
		glPushMatrix();
		glRotatef((tiempoSintetico * 360 / 10), modelos[itModelos].rotX,
				modelos[itModelos].rotY, modelos[itModelos].rotZ);
		glTranslatef(
				(modelos[itModelos].radio
						* cos(modelos[itModelos].omega * tiempoSintetico)),
				0.0f,
				(modelos[itModelos].radio
						* sin(modelos[itModelos].omega * tiempoSintetico)));

		// Pintamos el modelo.
		drawModel(modelos[itModelos]);

		for (int itSatelites = 0;
				itSatelites < modelos[itModelos].satelites.size();
				itSatelites++) {

			pintarOribta(modelos[itModelos].satelites[itSatelites].radio);
			glPushMatrix();
			glRotatef((tiempoSintetico * 360 / 10),
					modelos[itModelos].satelites[itSatelites].rotX,
					modelos[itModelos].satelites[itSatelites].rotY,
					modelos[itModelos].satelites[itSatelites].rotZ);
			glTranslatef(
					(modelos[itModelos].satelites[itSatelites].radio
							* cos(
									modelos[itModelos].satelites[itSatelites].omega
											* tiempoSintetico)), 0.0f,
					(modelos[itModelos].satelites[itSatelites].radio
							* sin(
									modelos[itModelos].satelites[itSatelites].omega
											* tiempoSintetico)));

			drawModel(modelos[itModelos].satelites[itSatelites]);
			glPopMatrix();
		}
		glPopMatrix();
	}

	glFlush();
	glutSwapBuffers();

	tiempoSintetico = tiempoSintetico + 0.08;
}

////////////////////////////////////////////////////////////////////////////////
// Funcion para gestionar los movimientos del raton.
void Mundo::onMouse(int button, int state, int x, int y) {
	if ((button == 3) || (button == 4)) {
		if (state == GLUT_UP)
			return;
		if (button == 3) {
			camaras->zoomOut(activeCamera, 2.5);
		} else {
			camaras->zoomIn(activeCamera, 2.5);
		}
	} else {
		// Actualizamos los valores de x, y.
		xold = x;
		yold = y;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Funcion que actualiza la posicion de los modelos en la pantalla segun los movimientos del raton.
void Mundo::onMotion(int x, int y) {
	alpha = (alpha + (y - yold));
	beta = (beta + (x - xold));
	xold = x;
	yold = y;
	glutPostRedisplay();
}

// Funcion que gestiona las pulsaciones en el teclado.
void Mundo::keyPressed(unsigned char key, int x, int y) {

	switch (key) {

	case 27: // Tecla Esc.
		// Cerramos la ventana y salimos.
		glutDestroyWindow(window);
		exit(0);
		break;

	case 32: // Tecla espacio
		if (getIForma() == wired) {
			setIForma(flat);
		} else {
			if (getIForma() == flat) {
				setIForma(smooth);
			} else {
				setIForma(wired);
			}
		}

		break;

	case 'q': // elegimos camara 0
		activeCamera = 0;
		break;

	case 'w': // elegimos camara 1
		activeCamera = 1;
		break;

	case 'e': // elegimos camara 2
		activeCamera = 2;
		break;

	case 'r': // elegimos camara 3
		activeCamera = 3;
		break;

	case 't': // elegimos camara 4
		activeCamera = 4;
		break;

	case 'y': // elegimos camara 5
		activeCamera = 5;
		break;

	default: // Numeros del 0 al 7
		if (key >= 48 && key <= 55) {
			focos->switchFocos(key - 48);
		}
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////
void Mundo::setVector4(GLfloat *v, GLfloat v0, GLfloat v1, GLfloat v2,
		GLfloat v3) {
	v[0] = v0;
	v[1] = v1;
	v[2] = v2;
	v[3] = v3;
}

////////////////////////////////////////////////////////////////////////////////
// Funcion para activar las distintas opciones que permite el menu.
void Mundo::onMenu(int opcion) {
	switch (opcion) {
	case FONDO_1:
		setIFondo(0);
		break;
	case FONDO_2:
		setIFondo(1);
		break;
	case FONDO_3:
		setIFondo(2);
		break;
	case DIBUJO_1:
		setIDibujo(3);
		break;
	case DIBUJO_2:
		setIDibujo(4);
		break;
	case DIBUJO_3:
		setIDibujo(5);
		break;
	case FORMA_1:
		setIForma(wired);
		break;
	case FORMA_2:
		focos->activarFoco(0);
		setIForma(flat);
		break;
	case FORMA_3:
		focos->activarFoco(0);
		setIForma(smooth);
		break;
	}
	glutPostRedisplay();
}

////////////////////////////////////////////////////////////////////////////////
void Mundo::cargarModelo(char *nombre) {

	ifstream ifs("parametros.json");
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	const Json::Value& characters = obj["modelos"];

	for (int i = 0; i < characters.size(); i++) {

		Modelo modelo;

		modelo.escala = characters[i]["escala"].asFloat();
		modelo.alpha = characters[i]["alpha"].asFloat();
		modelo.beta = characters[i]["beta"].asFloat();
		modelo.omega = characters[i]["omega"].asFloat();

		// Parámetros de rotación
		modelo.rotX = characters[i]["rotX"].asFloat();
		modelo.rotY = characters[i]["rotY"].asFloat();
		modelo.rotZ = characters[i]["rotZ"].asFloat();

		// Parámetros de traslación
		modelo.trasX = characters[i]["trasX"].asFloat();
		modelo.trasY = characters[i]["trasY"].asFloat();
		modelo.trasZ = characters[i]["trasZ"].asFloat();

		modelo.radio = characters[i]["radio"].asFloat();

		// Cargamos los materiales ambiente
		modelo.material_ambiente[0] =
				characters[i]["material"]["ambient"][0].asFloat();
		modelo.material_ambiente[1] =
				characters[i]["material"]["ambient"][1].asFloat();
		modelo.material_ambiente[2] =
				characters[i]["material"]["ambient"][2].asFloat();
		modelo.material_ambiente[3] =
				characters[i]["material"]["ambient"][3].asFloat();

		// difuso
		modelo.material_difuso[0] =
				characters[i]["material"]["diffuse"][0].asFloat();
		modelo.material_difuso[1] =
				characters[i]["material"]["diffuse"][1].asFloat();
		modelo.material_difuso[2] =
				characters[i]["material"]["diffuse"][2].asFloat();
		modelo.material_difuso[3] =
				characters[i]["material"]["diffuse"][3].asFloat();

		// specular
		modelo.material_specular[0] =
				characters[i]["material"]["specular"][0].asFloat();
		modelo.material_specular[1] =
				characters[i]["material"]["specular"][1].asFloat();
		modelo.material_specular[2] =
				characters[i]["material"]["specular"][2].asFloat();
		modelo.material_specular[3] =
				characters[i]["material"]["specular"][3].asFloat();
		// brillo
		modelo.brillo = characters[i]["material"]["shininess"].asFloat();

		// Cargamos la esfera
		modelo.Load_Model("Esfera.asc");

		// Cargamos los satelites del planeta (si existen)
		if (characters[i]["satelites"].size() > 0) {

			// Cargamos los satélites
			for (int j = 0; j < characters[i]["satelites"].size(); j++) {
				Modelo satelite;

				satelite.escala =
						characters[i]["satelites"][j]["escala"].asFloat();
				satelite.alpha =
						characters[i]["satelites"][j]["alpha"].asFloat();
				satelite.beta = characters[i]["satelites"][j]["beta"].asFloat();
				satelite.omega =
						characters[i]["satelites"][j]["omega"].asFloat();

				// Parámetros de rotación
				satelite.rotX = characters[i]["satelites"][j]["rotX"].asFloat();
				satelite.rotY = characters[i]["satelites"][j]["rotY"].asFloat();
				satelite.rotZ = characters[i]["satelites"][j]["rotZ"].asFloat();

				// Parámetros de traslación
				satelite.trasX =
						characters[i]["satelites"][j]["trasX"].asFloat();
				satelite.trasY =
						characters[i]["satelites"][j]["trasY"].asFloat();
				satelite.trasZ =
						characters[i]["satelites"][j]["trasZ"].asFloat();

				satelite.radio =
						characters[i]["satelites"][j]["radio"].asFloat();

				// Cargamos los materiales ambiente
				satelite.material_ambiente[0] =
						characters[i]["satelites"][j]["material"]["ambient"][0].asFloat();
				satelite.material_ambiente[1] =
						characters[i]["satelites"][j]["material"]["ambient"][1].asFloat();
				satelite.material_ambiente[2] =
						characters[i]["satelites"][j]["material"]["ambient"][2].asFloat();
				satelite.material_ambiente[3] =
						characters[i]["satelites"][j]["material"]["ambient"][3].asFloat();

				// difuso
				satelite.material_difuso[0] =
						characters[i]["satelites"][j]["material"]["diffuse"][0].asFloat();
				satelite.material_difuso[1] =
						characters[i]["satelites"][j]["material"]["diffuse"][1].asFloat();
				satelite.material_difuso[2] =
						characters[i]["satelites"][j]["material"]["diffuse"][2].asFloat();
				satelite.material_difuso[3] =
						characters[i]["satelites"][j]["material"]["diffuse"][3].asFloat();
				// specular
				satelite.material_specular[0] =
						characters[i]["satelites"][j]["material"]["specular"][0].asFloat();
				satelite.material_specular[1] =
						characters[i]["satelites"][j]["material"]["specular"][1].asFloat();
				satelite.material_specular[2] =
						characters[i]["satelites"][j]["material"]["specular"][2].asFloat();
				satelite.material_specular[3] =
						characters[i]["satelites"][j]["material"]["specular"][3].asFloat();

				// brillo
				satelite.brillo =
						characters[i]["material"]["satelites"][j]["shininess"].asFloat();

				// Dibujamos el satelite
				satelite.Load_Model(nombre);

				// Añadimos el satelite recien cargado a los satelites del modelo
				modelo.satelites.push_back(satelite);
			}
		}
		modelos.push_back(modelo);
	}
}

////////////////////////////////////////////////////////////////////////////////
int Mundo::getWidth() {
	return width;
}

////////////////////////////////////////////////////////////////////////////////
int Mundo::getHeight() {
	return height;
}

////////////////////////////////////////////////////////////////////////////////
void Mundo::setIFondo(int iFondo) {
	this->iFondo = iFondo;
}

////////////////////////////////////////////////////////////////////////////////
int Mundo::getIFondo() {
	return iFondo;
}

////////////////////////////////////////////////////////////////////////////////
void Mundo::setIDibujo(int iDibujo) {
	this->iDibujo = iDibujo;
}

////////////////////////////////////////////////////////////////////////////////
int Mundo::getIDibujo() {
	return iDibujo;
}

void Mundo::setIForma(tipoVista iForma) {
	this->iForma = iForma;
}
tipoVista Mundo::getIForma() {
	return iForma;
}

void Mundo::loadFocos() {
	focos = new Light;
}

void Mundo::loadCamaras() {
	camaras = new Camara;
}

Mundo::~Mundo() {
}
