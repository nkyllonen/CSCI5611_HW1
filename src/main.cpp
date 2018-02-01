//////////////////////////////////
//CSCI 5611 HW1 - Particle System
//Nikki Kyllonen - kyllo089
//Emma Lacroix - lacro058
//////////////////////////////////

#ifdef __APPLE__
#include "include/glad.h"
#else
#include "glad.h"
#endif  //Include order can matter here

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
#include "../ext/glm/glm.hpp"
#include "../ext/glm/gtc/matrix_transform.hpp"
#include "../ext/glm/gtc/type_ptr.hpp"
#else
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#endif

#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

//MY CLASSES
#ifdef __APPLE__
#include "include/Util.h"
#include "include/World.h"
#else
#include "Util.h"
#include "World.h"
#endif

using namespace std;

/*=============================*/
// Global Default Parameters
/*=============================*/
bool fullscreen = false;
int screen_width = 800;
int screen_height = 600;

//shader globals
#ifdef __APPLE__
string vertFile = "../Shaders/phong.vert";
string fragFile = "../Shaders/phong.frag";
#else
string vertFile = "Shaders/phong.vert";
string fragFile = "Shaders/phong.frag";
#endif

const float step_size = 0.25f;

/*=============================*/
// Helper Functions
/*=============================*/
void onKeyUp(SDL_KeyboardEvent & event, Camera* cam, World* myWorld);

/*==============================================================*/
//							  MAIN
/*==============================================================*/
int main(int argc, char *argv[]) {
	srand(time(0));

	//CHECK FOR MAX_NUM_P VALUE
	if (argc != 2)
	{
		cout << "\nERROR: Incorrect usage. Expected ./a.out MAX_NUM_P\n";
		exit(0);
	}

	int max_p = atoi(argv[1]);
	printf("max_p entered : %i\n", max_p);

	/////////////////////////////////
	//INITIALIZE SDL WINDOW
	/////////////////////////////////
	SDL_GLContext context;
	SDL_Window* window = util::initSDL(context, screen_width, screen_height);

	if (window == NULL)
	{
		cout << "ERROR: initSDL() failed." << endl;
		SDL_GL_DeleteContext(context);
		SDL_Quit();
		exit(0);
	}

	World* myWorld = new World(10,10,max_p);
	myWorld->createFloorData();

	/////////////////////////////////
	//LOAD MODEL DATA INTO WORLD
	/////////////////////////////////
	if (!myWorld->loadModelData())
	{
		cout << "ERROR. Unable to load model data." << endl;
		//Clean up
		myWorld->~World();
		SDL_GL_DeleteContext(context);
		SDL_Quit();
		exit(0);
	}

	/////////////////////////////////
	//SETUP CAMERA
	/////////////////////////////////
	Camera* cam = new Camera();
	cam->setDir(Vec3D(0, 0, 1));					//look along +z
	cam->setPos(Vec3D(0,1,-10));						//start
	cam->setUp(Vec3D(0, 1, 0));						//map is in xz plane
	cam->setRight(Vec3D(1, 0, 0));				//look along +z

	/////////////////////////////////
	//VAO + VBO + SHADERS + TEXTURES
	/////////////////////////////////
	if (!myWorld->setupGraphics())
	{
		cout << "ERROR. Unable to setup Graphics." << endl;
		//Clean Up
		SDL_GL_DeleteContext(context);
		SDL_Quit();
		myWorld->~World();
		cam->~Camera();
	}

	/*===========================================================================================
	* EVENT LOOP (Loop forever processing each event as fast as possible)
	* List of keycodes: https://wiki.libsdl.org/SDL_Keycode - You can catch many special keys
	* Scancode referes to a keyboard position, keycode referes to the letter (e.g., EU keyboards)
	===========================================================================================*/
	SDL_Event windowEvent;
	bool quit = false;
	float last_time = SDL_GetTicks(),	delta_time = 0,	new_time = 0;

	//FPS calculations
	float framecount = 0;
	float fps = 0, last_fps_print = 0.0;

	while (!quit)
	{
		if (SDL_PollEvent(&windowEvent)) {
			switch (windowEvent.type) //event type -- key up or down
			{
			case SDL_QUIT:
				quit = true; //Exit event loop
				break;
			case SDL_KEYUP:
				//check for escape or fullscreen before checking other commands
				if (windowEvent.key.keysym.sym == SDLK_ESCAPE) quit = true; //Exit event loop
				else if (windowEvent.key.keysym.sym == SDLK_f) fullscreen = !fullscreen;
				onKeyUp(windowEvent.key, cam, myWorld);
				break;
			default:
				break;
			}//END polling switch
			SDL_SetWindowFullscreen(window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0); //Set to full screen
		}//END polling If

		//draw entire world
		myWorld->draw(cam);

		//delta_time is in seconds so convert ticks (ms) by * 1000
		new_time = SDL_GetTicks();
		delta_time = (new_time - last_time) / 1000.0;
		last_time = new_time;
		myWorld->updateParticles(delta_time);

		if ((new_time - last_fps_print) / 1000.0 >= 1.0) //only print every 1+ seconds
		{
			fps = framecount;
			last_fps_print = new_time;
			printf("FPS: %f\n", fps);
			framecount = 0;
		}

		SDL_GL_SwapWindow(window);
		framecount++;
	}//END looping While

	//Clean Up
	SDL_GL_DeleteContext(context);
	SDL_Quit();
	myWorld->~World();
	cam->~Camera();

	return 0;
}//END MAIN

/*--------------------------------------------------------------*/
// onKeyUp : determine which key was pressed and how to edit
//				current translation or rotation parameters
/*--------------------------------------------------------------*/
void onKeyUp(SDL_KeyboardEvent & event, Camera* cam, World* myWorld)
{
	Vec3D pos = cam->getPos();
	Vec3D dir = cam->getDir();
	Vec3D right = cam->getRight();
	Vec3D up = cam->getUp();

	//temps to be modified in switch
	Vec3D temp_pos = pos;
	Vec3D temp_dir = dir;
	Vec3D temp_right = right;

	switch (event.keysym.sym)
	{
	/////////////////////////////////
	//TRANSLATION WITH ARROW KEYS
	/////////////////////////////////
	case SDLK_UP:
		//printf("Up arrow pressed - step forward\n");
		temp_pos = pos + (step_size*dir);
		break;
	case SDLK_DOWN:
		//printf("Down arrow pressed - step backward\n");
		temp_pos = pos - (step_size*dir);
		break;
	case SDLK_RIGHT:
		//printf("Right arrow pressed - step to the right\n");
		temp_pos = pos + (step_size*right);
		break;
	case SDLK_LEFT:
		//printf("Left arrow pressed - step to the left\n");
		temp_pos = pos - (step_size*right);
		break;
	////////////////////////////////
	//TURNING WITH A/D KEYS
	////////////////////////////////
	case SDLK_d:
		//printf("D key pressed - turn to the right\n");
		temp_dir = dir + (step_size*right);
		temp_right = cross(temp_dir, up); //calc new right using new dir
		break;
	case SDLK_a:
		//printf("A key pressed - turn to the left\n");
		temp_dir = dir - (step_size*right);
		temp_right = cross(temp_dir, up); //calc new right using new dir
		break;
	////////////////////////////////
	//SPACEBAR PRESS
	////////////////////////////////
	case SDLK_SPACE:
	{
		printf("Spacebar pressed - spawned new particle\n");
		myWorld->spawnParticle();
		break;
	}
	default:
		break;
	}//END switch key press

	cam->setDir(temp_dir);
	cam->setRight(temp_right);
	cam->setPos(temp_pos);
	return;
}//END onKeyUp
