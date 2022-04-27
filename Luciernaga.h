#pragma once

#include"Model.h"
#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
class Luciernaga
{
public:
	const float toRadians = 3.14159265f / 180.0f;
	Luciernaga(float x, float y, float z);
	void aleteo();
	void trayectoria1(GLfloat deltaTime,float despx);
	void trayectoria2(GLfloat deltaTime, float despx);

	void dibujar(GLuint uniformModel);
	glm::vec3 getPos();
private:
	float rotacion_ala = 0.0f, anguloy = 0.0f, angulo_trayecto = 0.0f;
	bool direccion_aleteo = true;
	float plusxm, plusym, pluszm, posx, posy, posz,plusxAux;
	int estado_anim;
	float tiempo;
	Model mariposa_cuerpo;
	Model mariposa_ala1;
	Model mariposa_ala2;
	glm::mat4 model, modelaux;

};


