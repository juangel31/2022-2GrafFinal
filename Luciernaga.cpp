#include "Luciernaga.h"
#include <glfw3.h>
Luciernaga::Luciernaga(float x, float y, float z) {
	posx = x;
	posy = y;
	posz = z;
	mariposa_cuerpo = Model();
	mariposa_cuerpo.LoadModel("Models/luciernaga/cuerpo.obj");
	mariposa_ala1 = Model();
	mariposa_ala1.LoadModel("Models/luciernaga/ala1.obj");
	mariposa_ala2 = Model();
	mariposa_ala2.LoadModel("Models/luciernaga/ala2.obj");
	estado_anim = 0;
	tiempo = 0.0f;
}

void Luciernaga::aleteo() {
	if (direccion_aleteo) {
		rotacion_ala = rotacion_ala - 0.6f;
		if (rotacion_ala <= -35.0f)
			direccion_aleteo = false;
	}
	else {
		rotacion_ala = rotacion_ala + 0.6f;
		if (rotacion_ala >= -0.0f)
			direccion_aleteo = true;
	}
	
}
glm::vec3 Luciernaga::getPos() {
	return glm::vec3(posx+plusxm,posy+plusym,posz+pluszm);
}
void Luciernaga::trayectoria1(GLfloat deltaTime,float despx) {
	switch (estado_anim)
	{
	case 0:
		plusxm = despx;
		plusym = 0.0;
		pluszm = 0.0;
		tiempo = 0.0f;
		estado_anim = 1;
		break;
	case 1:
		plusxm = plusxm - 0.1;
		if (plusxm < -60.5-despx) {
			estado_anim = 2;
			angulo_trayecto = -90.0;
			plusxAux = plusxm;
		}
		break;
	case 2:
		tiempo = tiempo + 0.6f;
		plusxm = -60.5-despx-52.66+52.66*cos(tiempo*toRadians);
		angulo_trayecto = angulo_trayecto + 0.6f;
		pluszm = 0.0 -52.66*sin(tiempo*toRadians);
		if (tiempo >= 180) {
			estado_anim = 3;
			plusxAux = plusxm;
			angulo_trayecto = 0.0f;
		}
		break;
	case 3:
		plusxm = plusxm - 0.1;
		if (plusxm< plusxAux-60.0) {
			estado_anim = 4;
			angulo_trayecto = 180.0;
			plusxAux = plusxm;
		}
		break;
	case 4:
		plusxm = plusxm + 0.1;
		if (plusxm > plusxAux + 60.0) {
			estado_anim = 5;
			plusxAux = plusxm;
		}
		break;
	case 5:
		tiempo = tiempo + 0.6f;
		plusxm = plusxAux + 52.66 + 52.66*cos(tiempo*toRadians);
		angulo_trayecto = angulo_trayecto + 0.6f;
		pluszm = 0.0 - 52.66*sin(tiempo*toRadians);
		if (tiempo >= 360) {
			estado_anim = 6;
			angulo_trayecto = -180.f;
			plusxAux = plusxm;
		}
		break;
	case 6:
		plusxm = plusxm + 0.1;
		if (plusxm > -despx) {
			estado_anim = 7;
			angulo_trayecto = 0.0;
			plusxAux = plusxm;
		}
		break;
	case 7:
		plusxm = -despx;
		plusym = 0.0;
		pluszm = 0.0;
		tiempo = 0.0f;
		estado_anim = 1;
		break;

	default:
		break;
	}
}
void Luciernaga::trayectoria2(GLfloat deltaTime, float despx) {
	switch (estado_anim)
	{
	case 0:
		plusxm = despx;
		plusym = 0.0;
		pluszm = 0.0;
		tiempo = 0.0f;
		estado_anim = 1;
		tiempo = 180;
		angulo_trayecto = 180.0;
		break;
	case 1:
		plusxm = plusxm + 0.1;
		if (plusxm > 60.5 - despx) {
			estado_anim = 2;
			angulo_trayecto = 90.0;
			plusxAux = plusxm;
		}
		break;
	case 2:
		tiempo = tiempo + 0.6f;
		plusxm = 60.5 - despx + 52.66 + 52.66*cos(tiempo*toRadians);
		angulo_trayecto = angulo_trayecto + 0.6f;
		pluszm = 0.0 - 52.66*sin(tiempo*toRadians);
		if (tiempo >= 360) {
			estado_anim = 3;
			plusxAux = plusxm;
			angulo_trayecto = 180.0;
			tiempo = 0;
		}
		break;
	case 3:
		plusxm = plusxm + 0.1;
		if (plusxm > plusxAux + 60.0) {
			estado_anim = 4;
			angulo_trayecto = -0.0;
			plusxAux = plusxm;
		}
		break;
	case 4:
		plusxm = plusxm - 0.1;
		if (plusxm < plusxAux - 60.0) {
			estado_anim = 5;
			plusxAux = plusxm;
		}
		break;
	case 5:
		tiempo = tiempo + 0.6f;
		plusxm = plusxAux - 52.66 + 52.66*cos(tiempo*toRadians);
		angulo_trayecto = angulo_trayecto + 0.6f;
		pluszm = 0.0 - 52.66*sin(tiempo*toRadians);
		if (tiempo >= 180) {
			estado_anim = 6;
			angulo_trayecto = 0.0;
			plusxAux = plusxm;
		}
		break;
	case 6:
		plusxm = plusxm - 0.1;
		if (plusxm < -despx) {
			estado_anim = 7;
			angulo_trayecto = 180.0;
			plusxAux = plusxm;
		}
		break;
	case 7:
		plusxm = -despx;
		plusym = 0.0;
		pluszm = 0.0;
		tiempo = 0.0f;
		estado_anim = 1;
		tiempo = 180;
		break;

	default:
		break;
	}
}

void Luciernaga::dibujar(GLuint uniformModel) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posx + plusxm, posy + plusym, posz + pluszm));
	model = glm::rotate(model,angulo_trayecto*toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	mariposa_cuerpo.RenderModel();

	modelaux = glm::translate(model, glm::vec3(0.0f, 0.538f, 0.731f));
	modelaux = glm::rotate(modelaux, -rotacion_ala * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelaux));
	mariposa_ala1.RenderModel();

	modelaux = glm::translate(model, glm::vec3(0.0f, 0.538f, -0.731f));
	modelaux = glm::rotate(modelaux, rotacion_ala*toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelaux));
	mariposa_ala2.RenderModel();
}