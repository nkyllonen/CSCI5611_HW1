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
#include <sstream>
#include <string>
#include <cmath>

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

//other globals
const float mouse_speed = 0.05f;
const float step_size = 0.15f;

/*=============================*/
// Helper Functions
/*=============================*/
void onKeyDown(SDL_KeyboardEvent & event, Camera* cam, World* myWorld);
void mouseMove(SDL_MouseMotionEvent & event, Camera * player, float horizontal_angle, float vertical_angle);

/*==============================================================*/
//							  MAIN
/*==============================================================*/
int main(int argc, char *argv[]) {
	/////////////////////////////////
	//SOLICIT USER INPUT
	/////////////////////////////////
	int max_num_particles;
	cout << "Please enter a maximum number of particles: ";
	cin >> max_num_particles;

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

	World* myWorld = new World(max_num_particles);

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
	cam->setPos(Vec3D(0,1,-5));						//start
	cam->setUp(Vec3D(0, 1, 0));						//map is in xz plane
	cam->setRight(Vec3D(1, 0, 0));				//look along +z

	/////////////////////////////////
	//SETUP MOUSE INITIAL STATE
	/////////////////////////////////
	float horizontal_angle = 0.0f;
	float vertical_angle = 0.0f;

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
	bool mouse_active = false;
	bool recentering = true;
	float last_time = SDL_GetTicks(),	delta_time = 0,	new_time = 0;

	int num_to_emit = 0;
	float last_emission = SDL_GetTicks();

	//FPS calculations
	float framecount = 0;
	float fps = 0, last_fps_print = 0.0;

	while (!quit)
	{
		while (SDL_PollEvent(&windowEvent)) {
			switch (windowEvent.type) //event type -- key up or down
			{
			case SDL_QUIT:
				quit = true; //Exit event loop
				break;
			case SDL_KEYDOWN:
				//check for escape or fullscreen before checking other commands
				if (windowEvent.key.keysym.sym == SDLK_ESCAPE) quit = true; //Exit event loop
				else if (windowEvent.key.keysym.sym == SDLK_f) fullscreen = !fullscreen;
				onKeyDown(windowEvent.key, cam, myWorld);
				break;
			case SDL_MOUSEMOTION:
				if (recentering)
				{
					SDL_WarpMouseInWindow(window, screen_width / 2, screen_height / 2);
					mouse_active = true;
				}
				else if (mouse_active && !recentering)
				{
					mouseMove(windowEvent.motion, cam, horizontal_angle, vertical_angle);
					// recentering = true;
				}
			default:
				break;
			}//END polling switch
			SDL_SetWindowFullscreen(window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0); //Set to full screen
		}//END polling while

		if (mouse_active)
		{
			recentering = false;
		}

		//draw entire world
		myWorld->draw(cam);

		//delta_time is in seconds so convert ticks (ms) by * 1000
		new_time = SDL_GetTicks();
		delta_time = (new_time - last_time) / 1000.0;
		last_time = new_time;
		myWorld->updateParticles(delta_time, new_time);

		num_to_emit = floor(((new_time - last_emission) / 1000.0) / myWorld->getEmitterGenRate());

		if (num_to_emit > 0)
		{
			myWorld->spawnParticles(num_to_emit, new_time);
			last_emission = new_time;
		}

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
// onKeyDown : determine which key was pressed and how to edit
//				current translation or rotation parameters
/*--------------------------------------------------------------*/
void onKeyDown(SDL_KeyboardEvent & event, Camera* cam, World* myWorld)
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
	//TRANSLATION WITH WASD
	/////////////////////////////////
	case SDLK_w:
		//printf("W key pressed - step forward\n");
		temp_pos = pos + (step_size*dir);
		break;
	case SDLK_s:
		//printf("S key pressed - step backward\n");
		temp_pos = pos - (step_size*dir);
		break;
	case SDLK_d:
		//printf("D key pressed - step to the right\n");
		temp_pos = pos + (step_size*right);
		break;
	case SDLK_a:
		//printf("A key pressed - step to the left\n");
		temp_pos = pos - (step_size*right);
		break;
	/////////////////////////////////
	//ACTIVATE/DEACTIVATE EMITTER WITH SPACEBAR
	/////////////////////////////////
	case SDLK_SPACE:
		myWorld->turnEmitterOnOff();
		break;
	/////////////////////////////////
	//INCREASE/DECREASE EMITTER GENRATE WITH UP/DOWN
	/////////////////////////////////
	case SDLK_UP:
		myWorld->setEmitterGenRate(myWorld->getEmitterGenRate() * 0.5);
		break;
	case SDLK_DOWN:
		myWorld->setEmitterGenRate(myWorld->getEmitterGenRate() * 2);
		break;
	/////////////////////////////////
	//CHANGE PARTICLE TYPE WITH #S
	/////////////////////////////////
	case SDLK_1:
	case SDLK_KP_1:
		//default emitter type
		myWorld->setEmitterType(DEFAULT_EMITTER);
		break;
	case SDLK_2:
	case SDLK_KP_2:
		//water emitter type
		myWorld->setEmitterType(WATER_EMITTER);
		break;
	case SDLK_3:
	case SDLK_KP_3:
		//fire emitter type
		myWorld->setEmitterType(FIRE_EMITTER);
		break;
	/////////////////////////////////
	case SDLK_u:
		myWorld->setEmitterToPoint();
		break;
	case SDLK_i:
		myWorld->setEmitterToDisc();
		break;
	case SDLK_o:
		myWorld->setEmitterToSphere();
		break;
	case SDLK_p:
		myWorld->setEmitterToRectangle();
		break;
	default:
		printf("ERROR: Invalid key pressed (%s)\n", SDL_GetKeyName(event.keysym.sym));
		break;
	}//END switch key press

	cam->setDir(temp_dir);
	cam->setRight(temp_right);
	cam->setPos(temp_pos);
	return;
}//END onKeyUp

/*--------------------------------------------------------------*/
// mouseMove : change the view accordingly when the mouse moves!
/*--------------------------------------------------------------*/

void mouseMove(SDL_MouseMotionEvent & event, Camera * cam, float horizontal_angle, float vertical_angle)
{
	Vec3D dir = cam->getDir();
	Vec3D right = cam->getRight();
	Vec3D up = cam->getUp();

	//temps to be modified
	Vec3D temp_dir = dir;
	Vec3D temp_right = right;
	Vec3D temp_up = up;

	horizontal_angle += mouse_speed * step_size * float(screen_width / 2 - event.x);
	vertical_angle += mouse_speed * step_size * float(screen_height / 2 - event.y);

	temp_dir = dir + (Vec3D(cos(vertical_angle) * sin(horizontal_angle), sin(vertical_angle), cos(vertical_angle) * cos(horizontal_angle)));
	temp_right = right + (Vec3D(sin(horizontal_angle - 3.14f / 2.0f), 0, cos(horizontal_angle - 3.14f / 2.0f)));
	temp_up = cross(temp_dir, -1 * temp_right);

	cam->setDir(temp_dir);
	cam->setRight(temp_right);
	cam->setUp(temp_up);
}
