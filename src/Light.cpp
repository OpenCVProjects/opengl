#include "Light.h"

Light::Light() {
	ifstream ifs("parametros.json");
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	const Json::Value& characters = obj["focos"];

	for (int i = 0; i < characters.size(); i++) {
		brillo[i] = characters[i + 1]["brillo"].asInt();

		setVector4(luzdifusa[i + 1], characters[i]["luzdifusa"][0].asFloat(),
				characters[i]["luzdifusa"][1].asFloat(),
				characters[i]["luzdifusa"][2].asFloat(),
				characters[i]["luzdifusa"][3].asFloat());

		setVector4(luzambiente[i + 1],
				characters[i]["luzambiente"][0].asFloat(),
				characters[i]["luzambiente"][1].asFloat(),
				characters[i]["luzambiente"][2].asFloat(),
				characters[i]["luzambiente"][3].asFloat());

		setVector4(luzspecular[i + 1],
				characters[i]["luzspecular"][0].asFloat(),
				characters[i]["luzspecular"][1].asFloat(),
				characters[i]["luzspecular"][2].asFloat(),
				characters[i]["luzspecular"][3].asFloat());

		setVector4(luzspecular[i + 1], characters[i]["posicion"][0].asFloat(),
				characters[i]["posicion"][1].asFloat(),
				characters[i]["posicion"][2].asFloat(),
				characters[i]["posicion"][3].asFloat());
	}

	for (int var = 0; var < 8; ++var) {
		activados[var] = false;
	}
	glEnable(GL_LIGHTING);
}

////////////////////////////////////////////////////////////////////////////////
void Light::setVector4(GLfloat *v, GLfloat v0, GLfloat v1, GLfloat v2,
		GLfloat v3) {
	v[0] = v0;
	v[1] = v1;
	v[2] = v2;
	v[3] = v3;
}

////////////////////////////////////////////////////////////////////////////////
void Light::switchFocos(int foco) {
	if (!activados[foco]) {
		if (foco > 0) {
			glLightfv(GL_LIGHT0 + foco, GL_DIFFUSE, luzdifusa[foco]);
			glLightfv(GL_LIGHT0 + foco, GL_AMBIENT, luzambiente[foco]);
			glLightfv(GL_LIGHT0 + foco, GL_SPECULAR, luzspecular[foco]);
			glLightfv(GL_LIGHT0 + foco, GL_POSITION, posicion[foco]);
		}

		glEnable(GL_LIGHT0 + foco);
		activados[foco] = true;
	} else {
		activados[foco] = false;
		glDisable(GL_LIGHT0 + foco);
	}
}

void Light::activarFoco(int foco) {
	if (!activados[foco]) {
		if (foco > 0) {
			glLightfv(GL_LIGHT0 + foco, GL_DIFFUSE, luzdifusa[foco]);
			glLightfv(GL_LIGHT0 + foco, GL_AMBIENT, luzambiente[foco]);
			glLightfv(GL_LIGHT0 + foco, GL_SPECULAR, luzspecular[foco]);
			glLightfv(GL_LIGHT0 + foco, GL_POSITION, posicion[foco]);
		}
		glEnable(GL_LIGHT0 + foco);
		activados[foco] = true;
	}
}

Light::~Light() {
}
