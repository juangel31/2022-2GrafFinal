#pragma once
#include"Model.h"
#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
class Mariposa
{
public:
	const float toRadians = 3.14159265f / 180.0f;
	Mariposa(float x,float y, float z);
	void aleteo();
	 void dibujar(GLuint uniformModel);
private:
	float rotacion_ala = 0.0f, anguloy = 0.0f, angulo_trayecto = 0.0f;
	bool direccion_aleteo = true;
	float plusxm, plusym, pluszm,posx,posy,posz;
	float round;
	Model mariposa_cuerpo;
	Model mariposa_ala1;
	Model mariposa_ala2;
	glm::mat4 model, modelaux;

};

