#ifndef WORLD_INCLUDED
#define WORLD_INCLUDED

#include "glad.h"  //Include order can matter here

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#elif __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#else
#include <SDL.h>
#include <SDL_opengl.h>
#endif

#define GLM_FORCE_RADIANS
#ifdef __APPLE__
#include "../../ext/glm/glm.hpp"
#include "../../ext/glm/gtc/matrix_transform.hpp"
#include "../../ext/glm/gtc/type_ptr.hpp"
#else
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#endif

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

#include "Vec3D.h"
#include "Camera.h"
#include "Util.h"
#include "Particle.h"

class World{
private:
	int width;
	int height;

	int total_verts;
	float* modelData;

	//modelData indices
	int CUBE_START = 0;
	int CUBE_VERTS = 0;
	int SPHERE_START = 0;
	int SPHERE_VERTS = 0;

	//VAO and VBO GLuints
	GLuint vao;
	GLuint vbo[1];

	//Shader and Texture GLuints
	GLuint shaderProgram;
	GLuint tex0;
	GLuint tex1;

	//what lives in this world
	float* floorData; //array of floor data
	float floor_y; 		//y value of floor

	//Particle array
	Particle** p_array;//dynamic array of Particle ptrs
	int MAX_NUM_P;		//length of p_array
	int CUR_NUM_P;		//how many currently populate p_array (-1 = index of last filled index)

public:
	//CONSTRUCTORS AND DESTRUCTORS
	World();
	World(int w, int h, int max);
	~World();

	//SETTERS
	void setCubeIndices(int start, int tris);
	void setSphereIndices(int start, int tris);
	void setFloor(float f);

	//GETTERS
	int getWidth();
	int getHeight();

	//OTHERS
	bool loadModelData();
	bool setupGraphics();
	void draw(Camera * cam);
	void createFloorData();
	void drawFloor();
	void initParticle(int index);
	void updateParticles(float dt);
	void spawnParticle();

};

#endif
