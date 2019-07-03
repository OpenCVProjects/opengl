#include "Mundo.h"

Mundo::Mundo() {

	// Inicializamos todo:

	width=800;
	height=800;
	aspect = width/height;
	angulo = 0;
	window=0;
	tamanio = 100;

	// Factor para el tamaño del modelo.
	escalaGeneral = 0.005;

	// Rotacion de los modelos.
	alpha=0;
	beta=0;

	// Variables para la gestion del ratón.
	xold=0;
	yold=0;
	zoom=1.0;

	iDibujo=4;
	iFondo=0;

	// TODO cargar los focos del json
	loadFocos();
	// TODO cargar las camaras del json
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
	glVertex3f((float) tamanio, 0.0f, 0.0f);

	// Eje Y Verde
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, (float) tamanio, 0.0f);

	// Eje Z Azul
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, (float) tamanio);

	glClearColor(0.f, 0.f, 0.0f, 0.f);

	glEnd();
	glEnable(GL_LIGHTING);
}


void Mundo::drawModel(Modelo modelo,float escala) {

		glDisable(GL_LIGHTING);
		drawAxis();
		modelo.Draw_Model(getIForma(),escala,zoom);
		glEnable(GL_LIGHTING);
}

void Mundo::display(void) {

	glClearDepth(1.0);
	glClearColor(colores[getIFondo()][0], colores[getIFondo()][1], colores[getIFondo()][2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Cargamos la entidad

	// elegimos la proyección
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
	//glPushMatrix(); // Guardamos la matriz del model
	glLoadIdentity();

	/* Colocamos la camara en el punto deseado */
	camaras->activarCamara(activeCamera);



	// Manejo del raton
	glRotatef(alpha, 1.0f, 0.0f, 0.0f);
	glRotatef(beta, 0.0f, 1.0f, 0.0f);

	// Establecemos el color del Modelo.
	glColor3f(colores[getIDibujo()][0], colores[getIDibujo()][1], colores[getIDibujo()][2]);
	GLfloat mat_ambient[] = {0.1, 0.1, 0.1, 1.0f};

	GLfloat mat_diffuse[] = {0.0, 0.0, 0.8, 1.0f};

	GLfloat mat_specular[] = {0.9, 0.9, 0.9, 1.0f};



	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf (GL_FRONT, GL_SHININESS, 100.0f);


	// Pintamos el modelo.
	drawModel(Sol,escalaGeneral);

	glFlush();
	glutSwapBuffers();
}


////////////////////////////////////////////////////////////////////////////////
// Funcion para gestionar los movimientos del raton.
void Mundo::onMouse(int button, int state, int x, int y) {
	if ((button == 3) || (button == 4)){
		if (state == GLUT_UP)
			return;
		if(button==3)
                    {zoom=zoom-0.1;cout<<"Zoom negativo...."<<zoom<<endl;}
		else
                    {zoom=zoom+0.1;cout<<"Zoom positivo...."<<zoom<<endl;}
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

		switch (key){

			case 27: // Tecla Esc.
				// Cerramos la ventana y salimos.
				glutDestroyWindow(window);
				exit(0);
				break;

			case 32: // Tecla espacio
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
				cout << activeCamera << endl;
			break;

			case 'y': // elegimos camara 5
				activeCamera = 5;
			break;

			default: // Numeros del 0 al 7
				if(key>=48 && key<=55){
					cout << key << endl;
					lights->switchFocos(key-48);
				}
				break;
		}
}


////////////////////////////////////////////////////////////////////////////////
void Mundo::setVector4(GLfloat *v, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
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
		setIForma(flat);
		break;
	case FORMA_3:
		setIForma(smooth);
		break;
	}
	glutPostRedisplay();
}


////////////////////////////////////////////////////////////////////////////////
void Mundo::cargarModelo(char nombre[50] ){
	Sol.Load_Model(nombre);
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

void Mundo::setIForma(tipoVista iForma){
	this->iForma = iForma;
}
tipoVista Mundo::getIForma(){
	return iForma;
}

void Mundo::loadFocos(){
	lights = new Light;
}

void Mundo::loadCamaras(){
	camaras = new Camara;
}


Mundo::~Mundo() {
}
