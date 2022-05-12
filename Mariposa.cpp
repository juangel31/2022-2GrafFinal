#include "Mariposa.h"

Mariposa::Mariposa(float x, float y, float z) {
	posx = x;
	posy = y;
	posz = z;
	mariposa_cuerpo = Model();
	mariposa_cuerpo.LoadModel("Models/mariposa/cuerpo.obj");
	mariposa_ala1 = Model();
	mariposa_ala1.LoadModel("Models/mariposa/ala1.obj");
	mariposa_ala2 = Model();
	mariposa_ala2.LoadModel("Models/mariposa/ala2.obj");
}

void Mariposa:: aleteo() {
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
	anguloy = anguloy + 0.6f;
	angulo_trayecto = angulo_trayecto + 0.6f;
	plusym = 5 * sin(anguloy*toRadians);
	plusxm = 10 * cos(angulo_trayecto*toRadians);
	pluszm = 5 * sin(angulo_trayecto*toRadians);
	if (angulo_trayecto < 180 && angulo_trayecto>0) {
		round = 0;
	}
	else round = 180;
	if (angulo_trayecto > 360) angulo_trayecto = 0.0;
}
void Mariposa::dibujar(GLuint uniformModel) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posx + plusxm, posy + plusym, posz + pluszm));
	model = glm::rotate(model,round*toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	mariposa_cuerpo.RenderModel();

	modelaux = glm::translate(model, glm::vec3(0.0f, 0.736f, 0.38f));
	modelaux = glm::rotate(modelaux, -rotacion_ala * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelaux));
	mariposa_ala1.RenderModel();

	modelaux = glm::translate(model, glm::vec3(0.0f, 0.736f, -0.38f));
	modelaux = glm::rotate(modelaux, rotacion_ala*toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelaux));
	mariposa_ala2.RenderModel();
}