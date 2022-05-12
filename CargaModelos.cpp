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
//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"


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
#include "Luciernaga.h"

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
bool camaraT = true;
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


///////////////////////////////////////////////////////////////Models importados directamente
Model suelo;
Model tv;
Model totem;
Model caja_clasica;
Model tnt;
Model jump;
Model aku;
Model interrogacion;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";
void teclado(bool* keys);
// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[5];
SpotLight spotLights[1];


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
bool parabolico;
float xp, yp,zp;
float t;
int edoParabolico=0.0;
void parabolico_wumpa() {
	
		switch (edoParabolico)
		{
		case 0://inicializacion
			xp = 0;
			yp = 0;
			t = 0;
			break;
		case 1:
			if (yp >= 0) {
				xp = 15.0f*t;
				yp = (-0.5*9.8*t*t) + 35.0*t;
				t += 0.09;
			}
			else
		default:
			break;
		}
	
	
}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}
float dirx, diry,tiempo;
bool dia;
void cicloDia() {
	tiempo += 0.2*deltaTime;
	dirx = -sin(tiempo *toRadians);
	diry = -cos(tiempo* toRadians);
	if (tiempo > 90 &&tiempo<270) 
		dia = false;
	else
		dia = true;

	if (tiempo >= 360) {
		tiempo = 0.0f;
	}
}
bool tv_encendido;
bool control=true;
bool tiki=true;

unsigned int spotLightCount = 0;
unsigned int pointLightCount = 0;
void reordenar_luces(Luciernaga *luciernaga1, Luciernaga *luciernaga2, Luciernaga *luciernaga3, Luciernaga *luciernaga4) {
	if (dia) {
		pointLights[0] = PointLight(1.0f, 0.5f, 0.0f,
			9.0f, 30.0f,
			82.95f, 15.0f, -120.84f,
			0.8f, 0.1f, 0.1f);
		
		//luces pala las luciernagas
		pointLights[1] = PointLight(1.0f, 0.5f, 0.3f,
			9.0f, 30.0f,
			82.95f, 15.0f, -120.84f,
			0.8f, 0.1f, 0.1f);
	
		pointLights[2] = PointLight(0.113f, 0.81f, 0.8f,
			9.0f, 30.0f,
			82.95f, 15.0f, -120.84f,
			0.8f, 0.1f, 0.1f);
		
		pointLights[3] = PointLight(0.58, 0.023f, 0.26f,
			9.0f, 30.0f,
			82.95f, 15.0f, -120.84f,
			0.8f, 0.1f, 0.1f);
		

		pointLights[4] = PointLight(0.22f, 0.698f, 0.29f,
			9.0f, 30.0f,
			82.95f, 15.0f, -120.84f,
			0.8f, 0.1f, 0.1f);
		if (tiki)
			pointLightCount = 1.0;
		else
			pointLightCount = 0.0;
	}
	else {
		pointLights[4] = PointLight(1.0f, 0.5f, 0.0f,
			9.0f, 30.0f,
			82.95f, 15.0f, -120.84f,
			0.8f, 0.1f, 0.1f);
		
		//luces pala las luciernagas
		pointLights[1] = PointLight(1.0f, 0.5f, 0.3f,
			9.0f, 30.0f,
			82.95f, 15.0f, -120.84f,
			0.8f, 0.1f, 0.1f);
	
		pointLights[2] = PointLight(0.113f, 0.81f, 0.8f,
			9.0f, 30.0f,
			82.95f, 15.0f, -120.84f,
			0.8f, 0.1f, 0.1f);
		
		pointLights[3] = PointLight(0.58, 0.023f, 0.26f,
			9.0f, 30.0f,
			82.95f, 15.0f, -120.84f,
			0.8f, 0.1f, 0.1f);
		

		pointLights[0] = PointLight(0.22f, 0.698f, 0.29f,
			9.0f, 30.0f,
			82.95f, 15.0f, -120.84f,
			0.8f, 0.1f, 0.1f);
		pointLights[0].setPosition(luciernaga1->getPos());
		pointLights[1].setPosition(luciernaga2->getPos());
		pointLights[2].setPosition(luciernaga3->getPos());
		pointLights[3].setPosition(luciernaga4->getPos());
		if (tiki)
			pointLightCount = 5.0;
		else
			pointLightCount = 4.0;
	}
}
int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(posxCrash, 25.0f, posyCrash), -60.0f, 0.0f, 1.0f, 0.5f);

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
	

	suelo = Model();
	suelo.LoadModel("Models/suelo/suelo_optimizado.obj");
	totem = Model();
	totem.LoadModel("Models/totem/totem_optimizado.obj");
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.5f, 0.0f,
		9.0f, 30.0f,
		82.95f, 15.0f, -120.84f,
		0.8f, 0.1f, 0.1f);
	pointLightCount++;
	//luces pala las luciernagas
	pointLights[1] = PointLight(1.0f, 0.5f, 0.3f,
		9.0f, 30.0f,
		82.95f, 15.0f, -120.84f,
		0.8f, 0.1f, 0.1f);
	pointLightCount++;

	pointLights[2] = PointLight(0.113f, 0.81f, 0.8f,
		9.0f, 30.0f,
		82.95f, 15.0f, -120.84f,
		0.8f, 0.1f, 0.1f);
	pointLightCount++;
	pointLights[3] = PointLight(0.58, 0.023f, 0.26f,
		9.0f, 30.0f,
		82.95f, 15.0f, -120.84f,
		0.8f, 0.1f, 0.1f);
	pointLightCount++;

	pointLights[4] = PointLight(0.22f, 0.698f, 0.29f,
		9.0f, 30.0f,
		82.95f, 15.0f, -120.84f,
		0.8f, 0.1f, 0.1f);
	pointLightCount++;


	tv = Model();
	tv.LoadModel("Models/tv/tv_optimizado.obj");
	//linterna
	spotLights[0] = SpotLight(0.3f, 0.3f, 0.3f,
		1.0f, 1.0f,
		190.72f, 10.0f, -10.0f,
		-1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		10.0f);
	spotLightCount++;


	tnt = Model();
	tnt.LoadModel("Models/cajas/tnt_optimizado.obj");
	jump = Model();
	jump.LoadModel("Models/cajas/jump_optimizado.obj");
	caja_clasica = Model();
	caja_clasica.LoadModel("Models/cajas/caja_basica_optimizado.obj");
	aku = Model();
	aku.LoadModel("Models/cajas/aku_aku_optimizado.obj");
	interrogacion = Model();
	interrogacion.LoadModel("Models/cajas/interrogacion_optimizado.obj");
	//////////////////////////////////////////////////////////Carda de modelos animación
	Mariposa mariposa1 = Mariposa(50.0f, 10.0f, 50.0f);
	Mariposa mariposa2 = Mariposa(50.0f, 20.0f, 50.0f);
	Mariposa mariposa3 = Mariposa(70.0f, 10.0f, 70.0f);
	palmera_animacion palmeraAnimada = palmera_animacion(-114.0f,-4.0f,-119.f);
	//Luciernaga luciernaga1 = Luciernaga(102.84, 26.0, -266.0);
	Luciernaga luciernaga1 = Luciernaga(102.6, 26.0, -254.9);
	Luciernaga luciernaga2 = Luciernaga(-120.8, 26.0, -254.9);
	Luciernaga luciernaga3 = Luciernaga(102.6+25.0, 26.0, -254.9);
	Luciernaga luciernaga4 = Luciernaga(-120.8-25.0, 26.0, -254.9);

	/////////////////////////////////////////////////////////Creación de crash
	cuerpoCrash();

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.6f, 0.9f,
		0.0f, -1.0f, 0.0f);

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1500.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		mainLight.setDir(dirx, diry, 0.0f);
		cicloDia();
		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		teclado(mainWindow.getsKeys());
		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(camaraT), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix(camaraT)));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		
		////////////////////////////////////////////ILUMINACION
		reordenar_luces(&luciernaga1, &luciernaga2, &luciernaga3, &luciernaga4);
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);
		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		suelo.RenderModel();
		//meshList[2]->RenderMesh();

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





		////////////////////////////////////////////////////////////////////////////////////////////////Carga elementos decorativos y de iluminacion
		model = glm::translate(glm::mat4(1.0f), glm::vec3(82.95f,0.0f,-116.84f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		totem.RenderModel();

		model = glm::translate(glm::mat4(1.0f), glm::vec3(115.72f, 0.0f, -7.15f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tv.RenderModel();

		palmeraAnimada.dibujar_wumpa(0.0f,4.0f,-46.6f,uniformModel);
		palmeraAnimada.dibujar_wumpa(0.0f, 4.0f, -96.6f, uniformModel);
		palmeraAnimada.dibujar_wumpa(0.0f, 4.0f, -146.6f, uniformModel);
		palmeraAnimada.dibujar_wumpa(0.0f, 4.0f, -196.6f, uniformModel);

		palmeraAnimada.dibujar_palmera(-114.0,-4.0,-214.0,uniformModel);
		palmeraAnimada.dibujar_palmera(-181.0, -4.0, -214.0, uniformModel);
		palmeraAnimada.dibujar_palmera(-181.0, -4.0, -78.0, uniformModel);
		palmeraAnimada.dibujar_palmera(-89.0, -4.0, -306.0, uniformModel);
		palmeraAnimada.dibujar_palmera(-228.0, -4.0, -306.0, uniformModel);

		palmeraAnimada.dibujar_palmera(114.0, -4.0, -214.0, uniformModel);
		palmeraAnimada.dibujar_palmera(181.0, -4.0, -214.0, uniformModel);
		palmeraAnimada.dibujar_palmera(181.0, -4.0, -78.0, uniformModel);
		palmeraAnimada.dibujar_palmera(89.0, -4.0, -306.0, uniformModel);
		palmeraAnimada.dibujar_palmera(228.0, -4.0, -306.0, uniformModel);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(159.72f, 0.0f, -2.054f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tnt.RenderModel();
		model = glm::translate(glm::mat4(1.0f), glm::vec3(114.72f, 0.0f, -70.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		aku.RenderModel();

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-95.0f, 0.0f, -2.054f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		caja_clasica.RenderModel();
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-132.72f, 0.0f, -2.054f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		caja_clasica.RenderModel();

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-132.72f, 52.0f, -52.054f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		caja_clasica.RenderModel();

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-132.72f, 0.0f, -52.054f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		jump.RenderModel();

		////////////////////////////////////////////////////////////////////////////////////////////////Construcción crash
		camera.setOrientation(glm::vec3(posxCrash, 25.0f, posyCrash));
		camera.setPosicionBase(glm::vec3(posxCrash, 25.0f, posyCrash));
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
		
		palmeraAnimada.dibujar(uniformModel);
		palmeraAnimada.animacion(&activar);
		mariposa1.aleteo();
		mariposa1.dibujar(uniformModel);

		mariposa2.aleteo();
		mariposa2.dibujar(uniformModel);

		mariposa3.aleteo();
		mariposa3.dibujar(uniformModel);

		luciernaga1.dibujar(uniformModel);
		luciernaga1.aleteo();
		luciernaga1.trayectoria1(deltaTime,0.0);
		luciernaga2.dibujar(uniformModel);
		luciernaga2.aleteo();
		luciernaga2.trayectoria2(deltaTime, 0.0);
		luciernaga3.dibujar(uniformModel);
		luciernaga3.aleteo();
		luciernaga3.trayectoria1(deltaTime, 25.0);
		luciernaga4.dibujar(uniformModel);
		luciernaga4.aleteo();
		luciernaga4.trayectoria2(deltaTime, -25.0);
		/////////////////////////////////////////////////////////////
		palmeraAnimada.dibujar_wumpa(0.0f+xp, 4.0f+yp, -0.0f+zp, uniformModel);
		parabolico_wumpa();
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
			posxCrash = posxCrash - 0.4f;
	}
	 else if (keys[GLFW_KEY_L]) {
			rotCaminar = 90.0f;
			animCaminar = true;
			posxCrash = posxCrash + 0.4f;
	}
	else if (keys[GLFW_KEY_K]) {
			rotCaminar = 0.0f;
			animCaminar = true;
			posyCrash = posyCrash + 0.4f;
	}
	else if (keys[GLFW_KEY_I]) {
			rotCaminar = 180.0f;
			animCaminar = true;
			posyCrash = posyCrash - 0.4f;
	}
	else
	{
		animCaminar = false;
	}
	if (keys[GLFW_KEY_1]) {
		camaraT = true;
	}
	if (keys[GLFW_KEY_2]) {
		camaraT = false;
	}
	if (keys[GLFW_KEY_U]) {
		if (edoataque == 4 && !ataque) {
			ataque = true;
			edoataque = 0;
			control = true;
		}
		
		if (posxCrash >= -15.0 &&posxCrash <= 15.0 && posyCrash >= -15.0 && posyCrash <= 15.0) {
			edoParabolico = 1.0;
		}

		if (posxCrash <= 130.0 &&posxCrash >= 105.0 && posyCrash >= -20.0 && posyCrash <= -.0 &&control) {
			if (tv_encendido) {
				spotLightCount = 1;
				tv_encendido = false;
			}
			else {
				spotLightCount = 0;
				tv_encendido = true;
			}
			control = false;
		}
		
	}
	if (keys[GLFW_KEY_O]) {
		tiki = true;
	}
	if (keys[GLFW_KEY_P]) {
		tiki = false;
	}
	if (keys[GLFW_KEY_3]) {
		edoParabolico = 0.0;

	}
}
