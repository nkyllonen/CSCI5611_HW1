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
	objArray = new WorldObject*[100];
	particleEmitter = new Emitter();
	total_verts = 0;
	max_num_particles = 100;
	cur_num_particles = 0;
	setUpFloor();
}

World::World(int max_particles)
{
	width = 0;
	height = 0;
	objArray = new WorldObject*[max_particles];
	particleEmitter = new Emitter();
	total_verts = 0;
	max_num_particles = max_particles;
	cur_num_particles = 0;
	setUpFloor();
}

World::World(int w, int h)
{
	width = w;
	height = h;
	objArray = new WorldObject*[100];
	particleEmitter = new Emitter();
	total_verts = 0;
	max_num_particles = 100;
	cur_num_particles = 0;
	setUpFloor();
}

World::~World()
{
	delete[] modelData;
	for (int i = 0; i < cur_num_particles; i++)
	{
		delete objArray[i];
	}
	delete[] objArray;
	particleEmitter->~Emitter();
	delete floor;
}

/*----------------------------*/
// SETTERS
/*----------------------------*/
void World::setCurNumParticles(int num)
{
	cur_num_particles = num;
}

void World::setEmitterGenRate(float rate)
{
	particleEmitter->setGenRate(rate);
}

void World::setEmitterOrigin(Vec3D o)
{
	particleEmitter->setOrigin(o);
}

void World::setEmitterType(int num)
{
	particleEmitter->setType(num);
}

void World::setEmitterToPoint()
{
	float rate = particleEmitter->getGenRate();
	bool act = particleEmitter->isActive();
	int type = particleEmitter->getType();
	particleEmitter = new PointEmitter(particleEmitter->getOrigin());
	particleEmitter->setGenRate(rate);
	particleEmitter->setActive(act);
	particleEmitter->setType(type);
}

void World::setEmitterToDisc()
{
	float rate = particleEmitter->getGenRate();
	bool act = particleEmitter->isActive();
	int type = particleEmitter->getType();
	particleEmitter = new DiscEmitter(particleEmitter->getOrigin());
	particleEmitter->setGenRate(rate);
	particleEmitter->setActive(act);
	particleEmitter->setType(type);
}

void World::setEmitterToSphere()
{
	float rate = particleEmitter->getGenRate();
	bool act = particleEmitter->isActive();
	int type = particleEmitter->getType();
	particleEmitter = new SphereEmitter(particleEmitter->getOrigin());
	particleEmitter->setGenRate(rate);
	particleEmitter->setActive(act);
	particleEmitter->setType(type);
}

void World::setEmitterToRectangle()
{
	float rate = particleEmitter->getGenRate();
	bool act = particleEmitter->isActive();
	int type = particleEmitter->getType();
	particleEmitter = new RectangleEmitter(particleEmitter->getOrigin());
	particleEmitter->setGenRate(rate);
	particleEmitter->setActive(act);
	particleEmitter->setType(type);
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

float World::getEmitterGenRate()
{
	return particleEmitter->getGenRate();
}

Vec3D World::getEmitterOrigin()
{
	return particleEmitter->getOrigin();
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
	CUBE_START = 0;
	CUBE_VERTS = 0;
	#ifdef __APPLE__
	float* cubeData = util::loadModel("../models/cube.txt", CUBE_VERTS);
	#else
	float* cubeData = util::loadModel("models/cube.txt", CUBE_VERTS);
	#endif
	cout << "\nNumber of vertices in cube model : " << CUBE_VERTS << endl;
	total_verts += CUBE_VERTS;

	//QUAD
	QUAD_START = CUBE_VERTS;
	QUAD_VERTS = 0;
	float * quadData = createQuadData(QUAD_VERTS);
	cout << "\nNumber of vertices in quad model : " << QUAD_VERTS << endl << endl;
	total_verts += QUAD_VERTS;

	//SPHERE
	SPHERE_START = QUAD_VERTS;
	SPHERE_VERTS = 0;
	#ifdef __APPLE__
	float* sphereData = util::loadModel("../models/sphere.txt", SPHERE_VERTS);
	#else
	float* sphereData = util::loadModel("models/sphere.txt", SPHERE_VERTS);
	#endif
	cout << "\nNumber of vertices in sphere model : " << SPHERE_VERTS << endl;
	total_verts += SPHERE_VERTS;

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
	//each vertex has pos (3f) + norm (3) + texture coords (u,v) = 8 floats
	modelData = new float[total_verts * 8];

	//copy data into modelData array
	copy(cubeData, cubeData + CUBE_VERTS * 8, modelData);
	copy(quadData, quadData + QUAD_VERTS * 8, modelData + (CUBE_VERTS * 8));
	copy(sphereData, sphereData + SPHERE_VERTS * 8, modelData + (QUAD_VERTS * 8));
	delete[] cubeData;
	delete[] sphereData;
	delete[] quadData;
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
	tex2 = util::LoadTexture("../textures/uniformclouds.bmp");
	#else
	tex0 = util::LoadTexture("textures/wood.bmp");
	tex1 = util::LoadTexture("textures/grey_stones.bmp");
	tex2 = util::LoadTexture("textures/uniformclouds.bmp");
	#endif

	if (tex0 == -1 || tex1 == -1 || tex2 == -1 || shaderProgram == -1)
	{
		cout << "\nERROR. Failed to load texture(s)" << endl;
		printf(strerror(errno));
		return false;
	}

	//Tell OpenGL how to set fragment shader input
	//first 3 floats are position coords
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	//Attribute, vals/attrib., type, normalized?, stride, offset
	//Binds to VBO current GL_ARRAY_BUFFER
	glEnableVertexAttribArray(posAttrib);

	//next 2 floats are texture coords (u,v)
	GLint texAttrib = glGetAttribLocation(shaderProgram, "inTexcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	//last 3 floats are normal coords
	GLint normAttrib = glGetAttribLocation(shaderProgram, "inNormal");
	glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(normAttrib);

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

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex2);
	glUniform1i(glGetUniformLocation(shaderProgram, "tex2"), 2);

	glBindVertexArray(vao);

	glUniform1i(uniTexID, -1); //Set texture ID to use (0 = wood texture, -1 = no texture)

	for (int i = 0; i < cur_num_particles; i++)
	{
		objArray[i]->draw(shaderProgram);
	}

	//draw floor
	glUniform1i(uniTexID, -1);
	floor->draw(shaderProgram);
}

//
void World::updateParticles(float dt, float cur_time)
{
	Vec3D pos, vel, acc;
	Vec3D temp_pos, temp_vel;
	float damping = 0.0, error = 0.02;
	Vec3D newColor;

	for (int i = 0; i < cur_num_particles; i++)
	{
		WorldObject * p = objArray[i]; //ith particle
		Particle* pp = (Particle *) p;

		if ((cur_time - pp->getBirth()) / 1000.0 >= pp->getLifespan())
		{
			//kill the particle
			objArray[i] = objArray[cur_num_particles-1]; //set ith spot in array as last particle in the array
			objArray[cur_num_particles-1] = NULL;
			cur_num_particles--;
		}
		else
		{
			//move the particle
			pos = pp->getPos();
			vel = pp->getVel();
			acc = pp->getAcc();
			damping = pp->getDamping();

			//temp
			temp_pos = pos + (dt*vel);

			//for color changing
			float age = (cur_time - pp->getBirth()) / 1000.0 / pp->getLifespan();
			newColor = particleEmitter->generateNewColor(age);

			if (temp_pos.getY() > floor->getPos().getY())
			{
				temp_vel = vel + (dt * acc);
			}
			else
			{
				if (abs(temp_pos.getY() - pos.getY()) > error)
				{
					temp_vel = Vec3D(vel.getX() * -1 * damping, vel.getY() * damping, vel.getZ() * -1 * damping);
				}
				else //kill tiny bounces
				{
					temp_vel = Vec3D(vel.getX() * -0.5 * damping, vel.getY() * 0.5 * damping, vel.getZ() * -0.5 * damping);
				}
				temp_pos = pos + (dt*temp_vel);
			}

			pp->setPos(temp_pos);
			pp->setVel(temp_vel);
			pp->setColor(newColor);

			objArray[i] = pp;
		}
	}
}

//
void World::spawnParticles(int num_to_emit, float cur_time, Camera * cam, float mouse_x, float mouse_y)
{
	if (particleEmitter->isActive())
	{
		for (int i = 0; i < num_to_emit; i++)
		{
			if (cur_num_particles < max_num_particles)
			{
				WorldObject * p = new Particle();
				Particle* pp = (Particle *) p;
				switch (particleEmitter->getType())
				{
					case BALL_EMITTER:
						pp = particleEmitter->generateParticle(SPHERE_START, SPHERE_VERTS, cam, mouse_x, mouse_y);
						break;
					case WATER_EMITTER:
						pp = particleEmitter->generateParticle(CUBE_START, CUBE_VERTS, cam, mouse_x, mouse_y);
						break;
					case FIRE_EMITTER:
						pp = particleEmitter->generateParticle(CUBE_START, CUBE_VERTS, cam, mouse_x, mouse_y);
						break;
					case SPELL_EMITTER:
						pp = particleEmitter->generateParticle(CUBE_START, CUBE_VERTS, cam, mouse_x, mouse_y);
						break;
					case DEFAULT_EMITTER:
						pp = particleEmitter->generateParticle(CUBE_START, CUBE_VERTS, cam, mouse_x, mouse_y);
						break;
					default:
						pp = particleEmitter->generateParticle(CUBE_START, CUBE_VERTS, cam, mouse_x, mouse_y);
						break;
				}
				pp->setBirth(cur_time);
				objArray[cur_num_particles] = pp;
				cur_num_particles++;
			}
		}
	}
}

void World::turnEmitterOnOff()
{
	particleEmitter->changeActive();
}

void World::deleteParticles()
{
	for (int i = 0; i < cur_num_particles; i++)
	{
		delete objArray[i];
	}
	cur_num_particles = 0;
}

/*----------------------------*/
// PRIVATE FUNCTIONS
/*----------------------------*/
//
float* World::createQuadData(int& verts)
{
	verts = 48 / 8;
	//1x1 quad in the xy plane centered on origin
	//3 pos + (u,v) + 3 norm coords
	return new float[48] {
			-0.5f, 0.0f,-0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //1
			-0.5f, 0.0f,0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,  //2
			0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  //3
			0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  //3
			0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //4
			-0.5f, 0.0f,-0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f  //1
		};
}

//
void World::setUpFloor()
{
	floor = new WorldObject(Vec3D(0,-5,0));
	floor->setVertexInfo(CUBE_START, CUBE_VERTS);
	floor->setSize(Vec3D(100,0.1,100));

	Material mat;
	mat.setAmbient(glm::vec3(0.7, 0.7, 0.7));
	mat.setDiffuse(glm::vec3(0.7, 0.7, 0.7));
	mat.setSpecular(glm::vec3(0, 0, 0));

	floor->setMaterial(mat);
}
