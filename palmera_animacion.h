#pragma once
#include"Model.h"
#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
class palmera_animacion
{
public:
	const float toRadians = 3.14159265f / 180.0f;

	palmera_animacion( float x, float y, float z);
	void animacion(bool *activar);
	void dibujar(GLuint uniformModel);
	void dibujar_wumpa(float x, float y, float z, GLuint uniformModel);
	void dibujar_palmera(float x, float y, float z, GLuint uniformModel);
private:
	Model sillon;
	Model palmera;
	Model wumpa_palmera;

	float plusx = 0.0f, plusy = 0.0f, plusz = 0.0f, rot_wumpa = 0.0f;
	float posx, posy, posz;
	int edo = 0;
	float rot_manzana = 0.0f, levitacion = 0.0f;
	glm::mat4 model, modelaux;

};

