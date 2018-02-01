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
#include "Emitter.h"
#include "Particle.h"

class World{
private:
	int width;
	int height;

	int max_num_particles;
	int cur_num_particles;

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
	float * floorData; //array of floor data
	float floor; //y value of floor
	
	Particle ** particleArray = NULL;
	Emitter * particleEmitter;

public:
	//CONSTRUCTORS AND DESTRUCTORS
	World();
	World(int max_particles);
	World(int w, int h);
	~World();

	//SETTERS
	void setCubeIndices(int start, int tris);
	void setSphereIndices(int start, int tris);
	void setFloor(float f);
	void setCurNumParticles(int num);

	//GETTERS
	int getWidth();
	int getHeight();
	int getMaxNumParticles();
	int getCurNumParticles();

	//OTHERS
	bool loadModelData();
	bool setupGraphics();
	void draw(Camera * cam);
	void createFloorData();
	void drawFloor();
	void initEmitter();
	void updateParticles(float dt);
	void spawnParticles();

};

#endif
