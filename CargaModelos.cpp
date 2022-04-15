/*
Semestre 2022-2
Práctica 5: Carga de Modelos
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"
#include "Mariposa.h"
#include "palmera_animacion.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture crashTexture;
bool activar = false;

////////////////////////////////////////////////////Variable crash
int orientacion = 0,edoataque=4; // 0->+z	1->-z	2->x	3->-x
float rotCaminar = 0,posxCrash=0.0f,posyCrash=0.0f,rotPiernas=0.0f,rotBrazoz=0.0f;
float rotPiernaAtaque = 0.0f, rotBrazosAtaque = 0.0f,rotAtaque=0.0f;
bool animCaminar = false, direccionBP = false,ataque=false;
///////////////////////////////////////////////////Variables y modelos temporales pre clases
Model pulpo_bajo;
Model pulpo_medio_bajo;
Model pulpo_medio_alto;
Model pulpo_alto;
float rot_baja, rot_medio, rot_alto;
Skybox skybox;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";
void teclado(bool* keys);



void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


}
void cuerpoCrash() {
	unsigned int indices_Cabeza[] = {
		//front
		2,4,1,
		3,4,2,

		//back
		5,6,8,
		8,7,5,

		//top
		10,12,11,
		11,9,10,

		//bottom
		13,14,16,
		13,15,16,

		//rigth
		17,19,20,
		20,18,17,

		//left
		21,23,24,
		24,22,21,

	};

	GLfloat cabeza[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			0.0f,0.0f,0.0f	,	0.0f,0.0f,	0.0f,0.0f,0.0f,
		//front
		   -3.0f, -3.0f,  3.0f,     0.123f,1-0.24f,  0.0f,0.0f,1.0f,
		    3.0f, -3.0f,  3.0f,     0.247f,1-0.24f,  0.0f,0.0f,1.0f,
		    3.0f,  3.0f,  3.0f,     0.247f,1-0.12f,  0.0f,0.0f,1.0f,
		   -3.0f,  3.0f,  3.0f,     0.123f,1-0.12f,  0.0f,0.0f,1.0f,
		//back
		   -3.0f,  3.0f,  -3.0f,     0.124f,1-0.37f,  0.0f,0.0f,-1.0f,
			3.0f,  3.0f,  -3.0f,     0.247f,1-0.37f,  0.0f,0.0f,-1.0f,
		   -3.0f, -3.0f,  -3.0f,     0.124f,1-0.49f,  0.0f,0.0f,-1.0f,
		    3.0f,  -3.0f,  -3.0f,     0.247f,1-0.49f,  0.0f,0.0f,-1.0f,
		//top
		   -3.0f,  3.0f,  3.0f,     0.125f,1-0.12f,  0.0f,1.0f,0.0f,
			3.0f,  3.0f,  3.0f,     0.247f,1-0.12f,  0.0f,1.0f,0.0f,
			-3.0f,  3.0f,  -3.0f,     0.125f,1-0.0f,  0.0f,1.0f,0.0f,
		    3.0f,  3.0f,  -3.0f,     0.247f,1-0.0f,  0.0f,1.0f,0.0f,

		//bottom
		   -3.0f, -3.0f,  3.0f,     0.125f,1-0.24f,  0.0f,-1.0f,0.0f,
		    3.0f, -3.0f,  3.0f,     0.247f,1-0.24f,  0.0f,-1.0f,0.0f,
		   -3.0f,  -3.0f,  -3.0f,     0.125f,1-0.37f,  0.0f,-1.0f,0.0f,
		    3.0f,  -3.0f,  -3.0f,     0.247f,1-0.37f,  0.0f,-1.0f,0.0f,
		//rigth
		    3.0f,  3.0f,  3.0f,     0.25f,1-0.125f,  1.0f,0.0f,0.0f,
			3.0f, -3.0f,  3.0f,     0.25f,1-0.248f,  1.0f,0.0f,0.0f,
			3.0f,  3.0f,  -3.0f,     0.37f,1-0.125f,  1.0f,0.0f,0.0f,
		    3.0f, -3.0f,  -3.0f,     0.37f,1-0.248f,  1.0f,0.0f,0.0f,
		//left
		    -3.0f,  3.0f,  3.0f,     0.124f,1-0.125f,  1.0f,0.0f,0.0f,
			-3.0f, -3.0f,  3.0f,     0.124f,1-0.248f,  1.0f,0.0f,0.0f,
			-3.0f,  3.0f,  -3.0f,     0.0f,1-0.125f,  1.0f,0.0f,0.0f,
			-3.0f, -3.0f,  -3.0f,     0.0f,1-0.248f,  1.0f,0.0f,0.0f,
	};


	GLfloat cuello[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			0.0f,0.0f,0.0f	,	0.0f,0.0f,	0.0f,0.0f,0.0f,
		//front
		   -1.0f, -1.5f,  1.0f,     0.82f,0.89f,  0.0f,0.0f,1.0f,
			1.0f, -1.5f,  1.0f,     0.88f,0.89f,  0.0f,0.0f,1.0f,
			1.0f,  1.5f,  1.0f,     0.88f,0.94f,  0.0f,0.0f,1.0f,
		   -1.0f,  1.5f,  1.0f,     0.82f,0.94f,  0.0f,0.0f,1.0f,
		//back
		   -1.0f,  1.5f,  -1.0f,     0.82f,0.94f,  0.0f,0.0f,-1.0f,
			1.0f,  1.5f,  -1.0f,     0.88f,0.94f,  0.0f,0.0f,-1.0f,
		   -1.0f, -1.5f,  -1.0f,     0.82f,0.89f,  0.0f,0.0f,-1.0f,
			1.0f,  -1.5f,  -1.0f,     0.88f,0.89f,  0.0f,0.0f,-1.0f,
		//top
		   -1.0f,  1.5f,  1.0f,     0.82f,0.89f,  0.0f,1.0f,0.0f,
			1.0f,  1.5f,  1.0f,     0.88f,0.89f,  0.0f,1.0f,0.0f,
			-1.0f,  1.5f,  -1.0f,     0.82f,0.94f,  0.0f,1.0f,0.0f,
			1.0f,  1.5f,  -1.0f,     0.88f,0.94f,  0.0f,1.0f,0.0f,

		//bottom
		   -1.0f, -1.5f,  1.0f,     0.82f,0.89f,  0.0f,-1.0f,0.0f,
			1.0f, -1.5f,  1.0f,     0.88f,0.89f,  0.0f,-1.0f,0.0f,
		   -1.0f,  -1.5f,  -1.0f,     0.82f,0.94f,  0.0f,-1.0f,0.0f,
			1.0f,  -1.5f,  -1.0f,     0.88f,0.94f,  0.0f,-1.0f,0.0f,
		//rigth
			1.0f,  1.5f,  1.0f,     0.82f,0.94f,  1.0f,0.0f,0.0f,
			1.0f, -1.5f,  1.0f,     0.82f,0.89f,  1.0f,0.0f,0.0f,
			1.0f,  1.5f,  -1.0f,     0.88f,0.94f,  1.0f,0.0f,0.0f,
			1.0f, -1.5f,  -1.0f,     0.88f,0.89f,  1.0f,0.0f,0.0f,
		//left
		    -1.0f,  1.5f,  1.0f,     0.82f,0.94f,  1.0f,0.0f,0.0f,
			-1.0f, -1.5f,  1.0f,     0.82f,0.89f,  1.0f,0.0f,0.0f,
			-1.0f,  1.5f,  -1.0f,     0.88f,0.94f,  1.0f,0.0f,0.0f,
			-1.0f, -1.5f,  -1.0f,     0.88f,0.89f,  1.0f,0.0f,0.0f,
	};
	GLfloat torzo[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			0.0f,0.0f,0.0f	,	0.0f,0.0f,	0.0f,0.0f,0.0f,
		//front
		   -3.0f, -4.5f,  1.5f,     0.359f,0.28f,  0.0f,0.0f,1.0f,
			3.0f, -4.5f,  1.5f,     0.545f,0.28f,  0.0f,0.0f,1.0f,
			3.0f,  4.5f,  1.5f,     0.545f,0.63f,  0.0f,0.0f,1.0f,
		   -3.0f,  4.5f,  1.5f,     0.359f,0.63f,  0.0f,0.0f,1.0f,
		//back
		   -3.0f,  4.5f,  -1.5f,     0.641f,0.63f,  0.0f,0.0f,-1.0f,
			3.0f,  4.5f,  -1.5f,     0.826f,0.63f,  0.0f,0.0f,-1.0f,
		   -3.0f, -4.5f,  -1.5f,     0.641f,0.28f,  0.0f,0.0f,-1.0f,
			3.0f,  -4.5f,  -1.5f,     0.826f,0.28f,  0.0f,0.0f,-1.0f,
		//top
		   -3.0f,  4.5f,  1.5f,     0.368f,0.644f,  0.0f,1.0f,0.0f,
			3.0f,  4.5f,  1.5f,     0.368f,0.644f,  0.0f,1.0f,0.0f,
			-3.0f,  4.5f,  -1.5f,     0.544f,0.70f,  0.0f,1.0f,0.0f,
			3.0f,  4.5f,  -1.5f,     0.544f,0.70f,  0.0f,1.0f,0.0f,

		//bottom
		   -3.0f, -4.5f,  1.5f,     0.65f,0.28f,  0.0f,-1.0f,0.0f,
			3.0f, -4.5f,  1.5f,     0.82f,0.28f,  0.0f,-1.0f,0.0f,
		   -3.0f,  -4.5f,  -1.5f,     0.65f,0.22f,  0.0f,-1.0f,0.0f,
			3.0f,  -4.5f,  -1.5f,     0.82f,0.22f,  0.0f,-1.0f,0.0f,
		//rigth
			3.0f,  4.5f,  1.5f,     0.54f,0.63f,  1.0f,0.0f,0.0f,
			3.0f, -4.5f,  1.5f,     0.54f,0.28f,  1.0f,0.0f,0.0f,
			3.0f,  4.5f,  -1.5f,     0.637f,0.63f,  1.0f,0.0f,0.0f,
			3.0f, -4.5f,  -1.5f,     0.637f,0.28f,  1.0f,0.0f,0.0f,
		//left
		    -3.0f,  4.5f,  1.5f,     0.887f,0.63f,  1.0f,0.0f,0.0f,
			-3.0f, -4.5f,  1.5f,     0.887f,0.28f,  1.0f,0.0f,0.0f,
			-3.0f,  4.5f,  -1.5f,     0.83f,0.63f,  1.0f,0.0f,0.0f,
			-3.0f, -4.5f,  -1.5f,     0.83f,0.28f,  1.0f,0.0f,0.0f,
	};
	GLfloat pierna[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			0.0f,0.0f,0.0f	,	0.0f,0.0f,	0.0f,0.0f,0.0f,
		//front
		   -1.3f, -2.5f,  1.5f,     0.752f,0.01f,  0.0f,0.0f,1.0f,
			1.3f, -2.5f,  1.5f,     0.815f,0.01f,  0.0f,0.0f,1.0f,
			1.3f,  2.5f,  1.5f,     0.815f,0.166f,  0.0f,0.0f,1.0f,
		   -1.3f,  2.5f,  1.5f,     0.752f,0.166f,  0.0f,0.0f,1.0f,
		//back
		   -1.3f,  2.5f,  -1.5f,     0.939f,0.166f,  0.0f,0.0f,-1.0f,
			1.3f,  2.5f,  -1.5f,     0.875f,0.166f,  0.0f,0.0f,-1.0f,
		   -1.3f, -2.5f,  -1.5f,     0.939f,0.01f,  0.0f,0.0f,-1.0f,
			1.3f,  -2.5f,  -1.5f,     0.875f,0.01f,  0.0f,0.0f,-1.0f,
		//top
		   -1.3f,  2.5f,  1.5f,     0.65f,0.22f,  0.0f,1.0f,0.0f,
			1.3f,  2.5f,  1.5f,     0.71f,0.22f,  0.0f,1.0f,0.0f,
			-1.3f,  2.5f,  -1.5f,     0.65f,0.341f,  0.0f,1.0f,0.0f,
			1.3f,  2.5f,  -1.5f,     0.71f,0.341f,  0.0f,1.0f,0.0f,

		//bottom
		   -1.3f, -2.5f,  1.5f,     0.82f,0.01f,  0.0f,-1.0f,0.0f,
			1.3f, -2.5f,  1.5f,     0.88f,0.01f,  0.0f,-1.0f,0.0f,
		   -1.3f,  -2.5f,  -1.5f,     0.82f,0.15f,  0.0f,-1.0f,0.0f,
			1.3f,  -2.5f,  -1.5f,     0.88f,0.15f,  0.0f,-1.0f,0.0f,
		//rigth
			1.3f,  2.5f,  1.5f,     0.815f,0.166f,  1.0f,0.0f,0.0f,
			1.3f, -2.5f,  1.5f,     0.815f,0.01f,  1.0f,0.0f,0.0f,
			1.3f,  2.5f,  -1.5f,     0.875f,0.166f,  1.0f,0.0f,0.0f,
			1.3f, -2.5f,  -1.5f,     0.875f,0.01f,  1.0f,0.0f,0.0f,
		//left
		    -1.3f,  2.5f,  1.5f,     0.999f,0.166f,  1.0f,0.0f,0.0f,
			-1.3f, -2.5f,  1.5f,     0.999f,0.01f,  1.0f,0.0f,0.0f,
			-1.3f,  2.5f,  -1.5f,     0.939f,0.166f,  1.0f,0.0f,0.0f,
			-1.3f, -2.5f,  -1.5f,     0.939f,0.01f,  1.0f,0.0f,0.0f,
	};
	GLfloat zapato[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			0.0f,0.0f,0.0f	,	0.0f,0.0f,	0.0f,0.0f,0.0f,
		//front
		   -1.3f, -1.0f,  2.5f,     0.08f,0.206f,  0.0f,0.0f,1.0f,
			1.3f, -1.0f,  2.5f,     0.154f,0.206f,  0.0f,0.0f,1.0f,
			1.3f,  1.0f,  2.5f,     0.154f,0.248f,  0.0f,0.0f,1.0f,
		   -1.3f,  1.0f,  2.5f,     0.08f,0.248f,  0.0f,0.0f,1.0f,
		//back
		   -1.3f,  1.0f,  -2.5f,     0.25f,0.248f,  0.0f,0.0f,-1.0f,
			1.3f,  1.0f,  -2.5f,     0.310f,0.248f,  0.0f,0.0f,-1.0f,
		   -1.3f, -1.0f,  -2.5f,     0.25f,0.206f,  0.0f,0.0f,-1.0f,
			1.3f,  -1.0f,  -2.5f,     0.310f,0.206f,  0.0f,0.0f,-1.0f,
		//top
		   -1.3f,  1.0f,  2.5f,     0.142f,0.310f,  0.0f,1.0f,0.0f,
			1.3f,  1.0f,  2.5f,     0.142f,0.250f,  0.0f,1.0f,0.0f,
			-1.3f,  1.0f,  -2.5f,     0.246f,0.310f,  0.0f,1.0f,0.0f,
			1.3f,  1.0f,  -2.5f,     0.246f,0.250f,  0.0f,1.0f,0.0f,

		//bottom
		   -1.3f, -1.0f,  2.5f,     0.158f,0.199f,  0.0f,-1.0f,0.0f,
			1.3f, -1.0f,  2.5f,     0.158f,0.199f,  0.0f,-1.0f,0.0f,
		   -1.3f,  -1.0f,  -2.5f,     0.246f,0.143f,  0.0f,-1.0f,0.0f,
			1.3f,  -1.0f,  -2.5f,     0.246f,0.143f,  0.0f,-1.0f,0.0f,
		//rigth
			1.3f,  1.0f,  2.5f,     0.142f,0.248f,  1.0f,0.0f,0.0f,
			1.3f, -1.0f,  2.5f,     0.142f,0.206f,  1.0f,0.0f,0.0f,
			1.3f,  1.0f,  -2.5f,     0.246f,0.248f,  1.0f,0.0f,0.0f,
			1.3f, -1.0f,  -2.5f,     0.246f,0.206f,  1.0f,0.0f,0.0f,
		//left
		    -1.3f,  1.0f,  2.5f,     0.417f,0.248f,  1.0f,0.0f,0.0f,
			-1.3f, -1.0f,  2.5f,     0.417f,0.206f,  1.0f,0.0f,0.0f,
			-1.3f,  1.0f,  -2.5f,     0.313f,0.248f,  1.0f,0.0f,0.0f,
			-1.3f, -1.0f,  -2.5f,     0.313f,0.206f,  1.0f,0.0f,0.0f,
	};
	GLfloat brazo[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			0.0f,0.0f,0.0f	,	0.0f,0.0f,	0.0f,0.0f,0.0f,
		//front
		   -1.5f, -5.0f,  1.5f,     0.699f,0.907f,  0.0f,0.0f,1.0f,
			1.5f, -5.0f,  1.5f,     0.699f,0.966f,  0.0f,0.0f,1.0f,
			1.5f,  5.0f,  1.5f,     0.439f,0.966f,  0.0f,0.0f,1.0f,
		   -1.5f,  5.0f,  1.5f,     0.439f,0.907f,  0.0f,0.0f,1.0f,
		//back
		   -1.5f,  5.0f,  -1.5f,     0.439f,0.799f,  0.0f,0.0f,-1.0f,
			1.5f,  5.0f,  -1.5f,     0.439f,0.842f,  0.0f,0.0f,-1.0f,
		   -1.5f, -5.0f,  -1.5f,     0.699f,0.799f,  0.0f,0.0f,-1.0f,
			1.5f,  -5.0f,  -1.5f,     0.699f,0.842f,  0.0f,0.0f,-1.0f,
		//top
		   -1.5f,  5.0f,  1.5f,     0.816f,0.88f,  0.0f,1.0f,0.0f,
			1.5f,  5.0f,  1.5f,     0.887f,0.88f,  0.0f,1.0f,0.0f,
			-1.5f,  5.0f,  -1.5f,     0.816f,0.94f,  0.0f,1.0f,0.0f,
			1.5f,  5.0f,  -1.5f,     0.887f,0.94f,  0.0f,1.0f,0.0f,

		//bottom
		   -1.5f, -5.0f,  1.5f,     0.816f,0.88f,  0.0f,-1.0f,0.0f,
			1.5f, -5.0f,  1.5f,     0.887f,0.88f,  0.0f,-1.0f,0.0f,
		   -1.5f,  -5.0f,  -1.5f,     0.816f,0.94f,  0.0f,-1.0f,0.0f,
			1.5f,  -5.0f,  -1.5f,     0.887f,0.94f,  0.0f,-1.0f,0.0f,
		//rigth
			1.5f,  5.0f,  1.5f,     0.439f,0.903f,  1.0f,0.0f,0.0f,
			1.5f, -5.0f,  1.5f,     0.699f,0.903f,  1.0f,0.0f,0.0f,
			1.5f,  5.0f,  -1.5f,     0.439f,0.846f,  1.0f,0.0f,0.0f,
			1.5f, -5.0f,  -1.5f,     0.699f,0.846f,  1.0f,0.0f,0.0f,
		//left
		    -1.5f,  5.0f,  1.5f,     0.439f,0.705f,  1.0f,0.0f,0.0f,
			-1.5f, -5.0f,  1.5f,     0.699f,0.705f,  1.0f,0.0f,0.0f,
			-1.5f,  5.0f,  -1.5f,     0.439f,0.764f,  1.0f,0.0f,0.0f,
			-1.5f, -5.0f,  -1.5f,     0.699f,0.764f,  1.0f,0.0f,0.0f,
	};
	Mesh *cabezaM =new Mesh();
	cabezaM->CreateMesh(cabeza, indices_Cabeza, 200,36);
	meshList.push_back(cabezaM);
	Mesh *cuelloM = new Mesh();
	cuelloM->CreateMesh(cuello, indices_Cabeza, 200, 36);
	meshList.push_back(cuelloM);
	Mesh *torzoM = new Mesh();
	torzoM->CreateMesh(torzo, indices_Cabeza, 200, 36);
	meshList.push_back(torzoM);
	Mesh *piernaM = new Mesh();
	piernaM->CreateMesh(pierna, indices_Cabeza, 200, 36);
	meshList.push_back(piernaM);
	Mesh *zapatoM = new Mesh();
	zapatoM->CreateMesh(zapato, indices_Cabeza, 200, 36);
	meshList.push_back(zapatoM);
	Mesh *brazoM = new Mesh();
	brazoM->CreateMesh(brazo, indices_Cabeza, 200, 36);
	meshList.push_back(brazoM);
}
void caminarCrash() {
	if (animCaminar && !ataque) {
		if (direccionBP) {
			rotBrazoz++;
			rotPiernas++;
			if (rotBrazoz >= 45)
				direccionBP = false;
		}
		else {
			rotBrazoz--;
			rotPiernas--;
			if (rotBrazoz <= -45)
				direccionBP = true;
		}
	}
	else {
		rotBrazoz = 0.0f;
		rotPiernas = 0.0f;
	}
}
void giroAtaque() {
	if (ataque) {
		switch (edoataque)
		{
		case 0://ponemos recto al personaje
			if (rotBrazoz > 0) {
				rotBrazoz--;
				rotPiernas--;
			}
			else if (rotBrazoz < 0) {
				rotBrazoz++;
				rotPiernas++;
			}
			else
				edoataque = 1;
			break;

		case 1://Ponemos extremidades en posicion
			rotBrazosAtaque++;
			rotPiernaAtaque++;
			if (rotBrazosAtaque >= 90)
				edoataque = 2;
			break;
		case 2://realizamos el giro
			rotAtaque = rotAtaque + 3;
			if (rotAtaque >= 360 * 3) {
				rotAtaque = 0.0f;
				edoataque = 3;
			}
			break;
		case 3://Ponemos extremidades en origen
			rotBrazosAtaque--;
			rotPiernaAtaque--;
			if (rotBrazosAtaque <= 0) {
				edoataque = 4;
				ataque = false;
			}
			break;
		default://No hacemos nada
			break;
		}
	}
}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 1.0f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	crashTexture = Texture("Textures/crash_textura1024.tga");
	crashTexture.LoadTextureA();

	pulpo_bajo = Model();
	pulpo_bajo.LoadModel("Models/pulpo/pulpo_bajo.obj");
	pulpo_medio_bajo = Model();
	pulpo_medio_bajo.LoadModel("Models/pulpo/pulpo_medio_bajo.obj");
	pulpo_medio_alto = Model();
	pulpo_medio_alto.LoadModel("Models/pulpo/pulpo_medio_alto.obj");
	pulpo_alto = Model();
	pulpo_alto.LoadModel("Models/pulpo/pulpo_alto.obj");
	

	//////////////////////////////////////////////////////////Carda de modelos animación
	Mariposa mariposa1 = Mariposa(0.0f, 5.0f, 0.0f);
	palmera_animacion palmeraAnimada = palmera_animacion(0.0f,0.f,0.f);



	/////////////////////////////////////////////////////////Creación de crash
	cuerpoCrash();

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		teclado(mainWindow.getsKeys());
		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		meshList[2]->RenderMesh();

		///////////////////////////////////////////////////////////////////////////////////////////////Pruebas
		/*model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-400.0f, 0.0f, -100.00f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pulpo_bajo.RenderModel();


		model = glm::translate(model, glm::vec3(0.0f, 20.854f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pulpo_medio_bajo.RenderModel();


		model = glm::translate(model, glm::vec3(0.0f, 19.6f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pulpo_medio_alto.RenderModel();

		model = glm::translate(model, glm::vec3(0.0f, 10.69f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pulpo_alto.RenderModel();
*/
		////////////////////////////////////////////////////////////////////////////////////////////////Construcción crash
		model = glm::translate(glm::mat4(1.0f), glm::vec3(posxCrash, 0.0f, posyCrash));
		model = glm::translate(model, glm::vec3(0.0f, 25.0f, 0.0f));
		model = glm::rotate(model,rotCaminar*toRadians,glm::vec3(0.0,1.0,0.0));//rotacion caminar
		model = glm::rotate(model, rotAtaque*toRadians, glm::vec3(0.0, 1.0, 0.0));//rotacion caminar
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		crashTexture.UseTexture();
		meshList[3]->RenderMesh();
		model = glm::translate(model, glm::vec3(0.0f,-4.5f,0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[4]->RenderMesh();
		modelaux=model = glm::translate(model, glm::vec3(0.0f, -4.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[5]->RenderMesh();


		//pierna izquierda
		model = glm::translate(model, glm::vec3(-1.7f, -4.5f, 0.0f));
		model = glm::rotate(model, rotPiernas*toRadians, glm::vec3(1.0, 0.0, 0.0));
		model = glm::rotate(model, -rotPiernaAtaque*toRadians, glm::vec3(1.0, 0.0, 0.0));//rotacion caminar
		model = glm::translate(model, glm::vec3(-0.0f, -2.5f, 0.0f));//traslación de la pierna
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[6]->RenderMesh();
		model = glm::translate(model, glm::vec3(-0.0f, -3.5f, 1.0f));//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[7]->RenderMesh();
		//pierna derecha
		model = glm::translate(modelaux, glm::vec3(1.7f, -4.5f, 0.0f));
		model = glm::rotate(model, -rotPiernas*toRadians, glm::vec3(1.0, 0.0, 0.0));
		model = glm::translate(model, glm::vec3(-0.0f, -2.5f, 0.0f));//traslación de la pierna
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[6]->RenderMesh();
		model = glm::translate(model, glm::vec3(-0.0f, -3.5f, 1.0f));//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[7]->RenderMesh();

		//brazo izquierdo
		model = glm::translate(modelaux, glm::vec3(-3.0f, +4.5f, 0.0f));
		model = glm::rotate(model, -rotBrazoz*toRadians, glm::vec3(1.0, 0.0, 0.0));
		model = glm::rotate(model, -rotBrazosAtaque*toRadians, glm::vec3(0.0, 0.0, 1.0));//rotacion caminar
		model = glm::translate(model, glm::vec3(-1.5f, -5.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[8]->RenderMesh();

		//brazo derecho
		model = glm::translate(modelaux, glm::vec3(3.0f, +4.5f, 0.0f));
		model = glm::rotate(model, +rotBrazoz*toRadians, glm::vec3(1.0, 0.0, 0.0));
		model = glm::rotate(model, rotBrazosAtaque * toRadians, glm::vec3(0.0, 0.0, 1.0));
		model = glm::translate(model, glm::vec3(1.5f, -5.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[8]->RenderMesh();
		caminarCrash();
		giroAtaque();
		///////////////////////////////////////////////////////////////////////////////////////////////Carga de dibujo y animación por clases
		
		//palmeraAnimada.dibujar(uniformModel);
		//palmeraAnimada.animacion(&activar);
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
void teclado(bool* keys) {
	if (keys[GLFW_KEY_G]) {
		activar = true;
	}
	if (keys[GLFW_KEY_J]) {
			rotCaminar = -90.0f;
			animCaminar = true;
			posxCrash = posxCrash - 0.1f;
	}
	 else if (keys[GLFW_KEY_L]) {
			rotCaminar = 90.0f;
			animCaminar = true;
			posxCrash = posxCrash + 0.1f;
	}
	else if (keys[GLFW_KEY_K]) {
			rotCaminar = 0.0f;
			animCaminar = true;
			posyCrash = posyCrash + 0.1f;
	}
	else if (keys[GLFW_KEY_I]) {
			rotCaminar = 180.0f;
			animCaminar = true;
			posyCrash = posyCrash - 0.1f;
	}
	else
	{
		animCaminar = false;
	}
	if (keys[GLFW_KEY_U]) {
		if (edoataque == 4 && !ataque) {
			ataque = true;
			edoataque = 0;
		}
	}
}
