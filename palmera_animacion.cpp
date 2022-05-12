#include "palmera_animacion.h"
palmera_animacion::palmera_animacion(float x, float y, float z) {
	posx = x;
	posy = y;
	posz = z;
	sillon = Model();
	sillon.LoadModel("Models/sillon/sillon_optimizado.obj");
	palmera = Model();
	palmera.LoadModel("Models/palmera/palmera_final.obj");
	wumpa_palmera = Model();
	wumpa_palmera.LoadModel("Models/wumpa/wumpa_optimizada.obj");
}
void palmera_animacion::animacion(bool *activar) {
	if (activar && edo == 0) {
		edo = 1;
		*activar = false;
	}
	else if (*activar && edo == 6) {
		edo = 0;
		*activar = false;
	}
	else
		*activar = false;
	switch (edo)
	{
	case 0:// inicializa
		plusy = 0;
		plusz = 0;
		rot_wumpa = 0;
		break;

	case 1://cae la manzana
		plusy = plusy - 0.3f;
		if (plusy <= -35.8f)
			edo = 2;
		break;

	case 2://se eleva
		plusy = plusy + 0.3f;
		if (plusy >= -24.93)
			edo = 3;
		break;
	case 3://vuelve a caer
		plusy = plusy - 0.3f;
		if (plusy <= -33.8f)
			edo = 4;
		break;
	case 4://gira al borde
		plusz = plusz - 0.3f;
		rot_wumpa--;
		if (plusz <= -30.53)
			edo = 5;
		break;
	case 5://cae del sillon
		plusz = plusz - 0.3f;
		plusy = plusy - 0.3f;
		rot_wumpa++;
		if (plusy <= -56.3)
			edo = 6;
		break;
	default:
		break;
	}
}
void palmera_animacion::dibujar(GLuint uniformModel) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posx, posy, posz));
	model = glm::rotate(model, 180*toRadians, glm::vec3(0.0, 1.0, 0.0));//rotacion caminar
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	palmera.RenderModel();

	modelaux = glm::translate(model, glm::vec3(0.0f, 3.17f, -16.72f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelaux));
	sillon.RenderModel();
	modelaux = glm::translate(model, glm::vec3(0.0f + plusx, 52.852f + plusy, -14.126f + plusz));
	modelaux = glm::rotate(modelaux, rot_wumpa*toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelaux));
	wumpa_palmera.RenderModel();
	
}
void palmera_animacion::dibujar_palmera(float x, float y, float z, GLuint uniformModel) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(x, y, z));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	palmera.RenderModel();
	
}

void palmera_animacion::dibujar_wumpa(float x, float y, float z, GLuint uniformModel) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(x, y + 2 * sin(levitacion*toRadians), z));
	model = glm::rotate(model, rot_manzana*toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	wumpa_palmera.RenderModel();
	rot_manzana=rot_manzana+0.1f;
	levitacion = levitacion + 0.1;
	if (levitacion > 369)
		levitacion = 0.0;
	if (rot_manzana > 360)
		rot_manzana = 0.0;
}