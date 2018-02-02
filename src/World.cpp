#ifdef __APPLE__
#include "include/World.h"
#else
#include "World.h"
#endif

using namespace std;


/*----------------------------*/
// CONSTRUCTORS AND DESTRUCTORS
/*----------------------------*/
World::World()
{
	width = 0;
	height = 0;
	floor = 0.0f;
	particleArray = new Particle*[100];
	particleEmitter = new Emitter();
	total_verts = 0;
	max_num_particles = 100;
	cur_num_particles = 0;
}

World::World(int max_particles)
{
	width = 0;
	height = 0;
	floor = 0.0f;
	particleArray = new Particle*[max_particles];
	particleEmitter = new Emitter();
	total_verts = 0;
	max_num_particles = max_particles;
	cur_num_particles = 0;
}

World::World(int w, int h)
{
	width = w;
	height = h;
	floor = 0.0f;
	particleArray = new Particle*[100];
	particleEmitter = new Emitter();
	total_verts = 0;
	max_num_particles = 100;
	cur_num_particles = 0;
}

World::~World()
{
	delete[] modelData;
	for (int i = 0; i < cur_num_particles; i++)
	{
		delete particleArray[i];
	}
	delete[] particleArray;
	particleEmitter->~Emitter();
	//delete floor;
}

/*----------------------------*/
// SETTERS
/*----------------------------*/
void World::setCubeIndices(int start, int tris)
{
	CUBE_START = start;
	CUBE_VERTS = tris;
}

void World::setSphereIndices(int start, int tris)
{
	SPHERE_START = start;
	SPHERE_VERTS = tris;
}

void World::setFloor(float f)
{
	floor = f;
}

void World::setCurNumParticles(int num)
{
	cur_num_particles = num;
}

/*----------------------------*/
// GETTERS
/*----------------------------*/
int World::getWidth()
{
	return width;
}

int World::getHeight()
{
	return height;
}

int World::getMaxNumParticles()
{
	return max_num_particles;
}

int World::getCurNumParticles()
{
	return cur_num_particles;
}

int World::getEmitterGenRate()
{
	return particleEmitter->getGenRate();
}

/*----------------------------*/
// OTHERS
/*----------------------------*/
//load in all models and store data into the modelData array
bool World::loadModelData()
{
	/////////////////////////////////
	//LOAD IN MODELS
	/////////////////////////////////
	//CUBE
	int CUBE_VERTS = 0;
	#ifdef __APPLE__
	float* cubeData = util::loadModel("../models/cube.txt", CUBE_VERTS);
	#else
	float* cubeData = util::loadModel("models/cube.txt", CUBE_VERTS);
	#endif
	cout << "\nNumber of vertices in cube model : " << CUBE_VERTS << endl;
	total_verts += CUBE_VERTS;
	setCubeIndices(0, CUBE_VERTS);

	//SPHERE
	int SPHERE_VERTS = 0;
	#ifdef __APPLE__
	float* sphereData = util::loadModel("../models/sphere.txt", SPHERE_VERTS);
	#else
	float* sphereData = util::loadModel("models/sphere.txt", SPHERE_VERTS);
	#endif
	cout << "\nNumber of vertices in sphere model : " << SPHERE_VERTS << endl;
	total_verts += SPHERE_VERTS;
	setSphereIndices(CUBE_VERTS, SPHERE_VERTS);

	/////////////////////////////////
	//BUILD MODELDATA ARRAY
	/////////////////////////////////
	if (!(cubeData != nullptr && sphereData != nullptr))
	{
		cout << "ERROR. Failed to load model(s)" << endl;
		delete[] cubeData;
		delete[] sphereData;
		return false;
	}
	modelData = new float[total_verts * 8];
	//copy data into modelData array
	copy(cubeData, cubeData + CUBE_VERTS * 8, modelData);
	copy(sphereData, sphereData + SPHERE_VERTS * 8, modelData + (CUBE_VERTS * 8));
	delete[] cubeData;
	delete[] sphereData;
	return true;
}

//
bool World::setupGraphics()
{
	/////////////////////////////////
	//BUILD VERTEX ARRAY OBJECT
	/////////////////////////////////
	//This stores the VBO and attribute mappings in one object
	glGenVertexArrays(1, &vao); //Create a VAO
	glBindVertexArray(vao); //Bind the above created VAO to the current context
	cout << "VAO bound to current context" << endl;

	/////////////////////////////////
	//BUILD VERTEX BUFFER OBJECT
	/////////////////////////////////
	//Allocate memory on the graphics card to store geometry (vertex buffer object)
	glGenBuffers(1, vbo);  //Create 1 buffer called vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); //Set the vbo as the active array buffer (Only one buffer can be active at a time)
	glBufferData(GL_ARRAY_BUFFER, total_verts * 8 * sizeof(float), modelData, GL_STATIC_DRAW); //upload vertices to vbo
	cout << "VBO setup with model data" << endl;

	/////////////////////////////////
	//SETUP SHADERS
	/////////////////////////////////
	#ifdef __APPLE__
	shaderProgram = util::LoadShader("../Shaders/phongTex.vert", "../Shaders/phongTex.frag");
	#else
	shaderProgram = util::LoadShader("Shaders/phongTex.vert", "Shaders/phongTex.frag");
	#endif

	//load in textures
	#ifdef __APPLE__
	tex0 = util::LoadTexture("../textures/wood.bmp");
	tex1 = util::LoadTexture("../textures/grey_stones.bmp");
	#else
	tex0 = util::LoadTexture("textures/wood.bmp");
	tex1 = util::LoadTexture("textures/grey_stones.bmp");
	#endif

	if (tex0 == -1 || tex1 == -1 || shaderProgram == -1)
	{
		cout << "\nERROR. Failed to load texture(s)" << endl;
		printf(strerror(errno));
		return false;
	}

	//Tell OpenGL how to set fragment shader input
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	//Attribute, vals/attrib., type, normalized?, stride, offset
	//Binds to VBO current GL_ARRAY_BUFFER
	glEnableVertexAttribArray(posAttrib);

	GLint normAttrib = glGetAttribLocation(shaderProgram, "inNormal");
	glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(normAttrib);

	GLint texAttrib = glGetAttribLocation(shaderProgram, "inTexcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0); //Unbind the VAO in case we want to create a new one

	glEnable(GL_DEPTH_TEST);
	return true;
}

//loops through WObj array and draws each
//also draws floor
void World::draw(Camera * cam)
{
	glClearColor(.2f, 0.4f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgram); //Set the active shader (only one can be used at a time)

	//vertex shader uniforms
	GLint uniView = glGetUniformLocation(shaderProgram, "view");
	GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
	GLint uniTexID = glGetUniformLocation(shaderProgram, "texID");

	//build view matrix from Camera
	glm::mat4 view = glm::lookAt(
		util::vec3DtoGLM(cam->getPos()),
		util::vec3DtoGLM(cam->getPos() + cam->getDir()),  //Look at point
		util::vec3DtoGLM(cam->getUp()));

	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 proj = glm::perspective(3.14f / 4, 800.0f / 600.0f, 0.1f, 100.0f); //FOV, aspect, near, far
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex0);
	glUniform1i(glGetUniformLocation(shaderProgram, "tex0"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex1);
	glUniform1i(glGetUniformLocation(shaderProgram, "tex1"), 1);

	glBindVertexArray(vao);

	/*for (int i = 0; i < width*height; i++)
	{
			glUniform1i(uniTexID, 0); //Set texture ID to use (0 = wood texture)
			objects_array[i]->draw(cam, shaderProgram);
	}//END for loop

	glUniform1i(uniTexID, 1); //Set texture ID to use for floor (1 = brick texture)
	floor->draw(cam, shaderProgram);*/

	//draw floor
	drawFloor();

	glUniform1i(uniTexID, -1); //Set texture ID to use (0 = wood texture, -1 = no texture)

	for (int i = 0; i < cur_num_particles; i++)
	{
		particleArray[i]->draw(shaderProgram);
	}
}

//
void World::createFloorData()
{
	/*floorData = new float[48] {-100.0, 0.0, -100.0, 0.0, 0.0, 0.0, 0.0, 0.0,
								-100.0, 0.0, 100.0, 1.0, 0.0, 0.0, 0.0, 0.0,
								100.0, 0.0, 100.0, 1.0, 1.0, 0.0, 0.0, 0.0,
								100.0, 0.0, 100.0, 1.0, 1.0, 0.0, 0.0, 0.0,
								100.0, 0.0, -100.0, 0.0, 1.0, 0.0, 0.0, 0.0,
								-100.0, 0.0, -100.0, 0.0, 0.0, 0.0, 0.0, 0.0}; //array of floor data
								*/

	//1x1 quad in the xy plane centered on origin
	/*floorData = new float[12] {
							-0.5f,0.0f,-0.5f,
							-0.5f,0.0f,0.5f,
							0.5f, 0.0f, 0.5f,
							0.5f, 0.0f, -0.5f
						}*/
}

//
void World::drawFloor()
{
	//Not sure how to make this function, should be similar in effect
	//to draw function in particle class

	// GLuint vbo;
	// glGenBuffers(1, &vbo);
	// glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(floorData), floorData, GL_STATIC_DRAW);

}

//
void World::initEmitter()
{
	particleEmitter->setPos(Vec3D(0, 5, 0));

	particleEmitter->setGenRate(3);

	//green sphere
	Material mat = Material();
	mat.setAmbient(glm::vec3(0, 1, 0));
	mat.setDiffuse(glm::vec3(0, 1, 0));
	mat.setSpecular(glm::vec3(0.75, 0.75, 0.75));
	particleEmitter->setMaterial(mat);

	particleEmitter->setVertexInfo(CUBE_START, CUBE_VERTS);
}

//
void World::updateParticles(float dt, float cur_time)
{
	for (int i = 0; i < cur_num_particles; i++)
	{
		Particle * p = particleArray[i]; //ith particle

		if ((cur_time - p->getBirth()) / 1000.0 >= p->getLifespan())
		{
			//kill the particle
			particleArray[i] = particleArray[cur_num_particles-1]; //set ith spot in array as last particle in the array
			particleArray[cur_num_particles-1] = NULL;
			cur_num_particles--;
		}
		else
		{
			//move the particle
			Vec3D pos = p->getPos();
			Vec3D vel = p->getVel();
			Vec3D acc = p->getAcc();

			//cout << "\tdt = " << dt << "\t pos: ";
			//pos.print();

			//temp
			Vec3D temp_pos = pos + (dt*vel);
			Vec3D temp_vel;

			float error = 0.02, damping = -0.70;

			if (temp_pos.getY() > floor)
			{
				temp_vel = vel + (dt * acc);
			}
			else
			{
				if (abs(temp_pos.getY() - pos.getY()) > error)
				{
					temp_vel = damping * vel;
				}
				else //kill tiny bounces
				{
					temp_vel = 0.5*damping * vel;
				}
				temp_pos = pos + (dt*temp_vel);
			}

			p->setPos(temp_pos);
			p->setVel(temp_vel);

			particleArray[i] = p;
		}
	}
}

//
void World::spawnParticle(float cur_time)
{
	if (cur_num_particles < max_num_particles)
	{
		Particle * p;
		p = particleEmitter->generateParticle();
		p->setBirth(cur_time);
		particleArray[cur_num_particles] = p;
		cur_num_particles++;
	}
}

/*----------------------------*/
// PRIVATE FUNCTIONS
/*----------------------------*/
