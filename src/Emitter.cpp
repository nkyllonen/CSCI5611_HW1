#ifdef __APPLE__
#include "include/Emitter.h"
#else
#include "Emitter.h"
#endif

using namespace std;

/*----------------------------*/
// CONSTRUCTORS AND DESTRUCTORS
/*----------------------------*/
Emitter::Emitter()
{
	origin = Vec3D(0, 5, 0);
	gen_rate = 0.1; //1 particle every gen_rate seconds
	active = true;
}

Emitter::Emitter(Vec3D o)
{
	origin = o;
	gen_rate = 0.1;
	active = true;
}

Emitter::Emitter(Vec3D o, float rate)
{
	origin = o;
	gen_rate = rate;
	active = true;
}

Emitter::~Emitter()
{
}

/*----------------------------*/
// SETTERS
/*----------------------------*/
void Emitter::setOrigin(Vec3D o)
{
	origin = o;
}

void Emitter::setGenRate(float g)
{
	gen_rate = g;
}

void Emitter::setActive(bool b)
{
	active = b;
}

/*----------------------------*/
// GETTERS
/*----------------------------*/
Vec3D Emitter::getOrigin()
{
	return origin;
}

float Emitter::getGenRate()
{
	return gen_rate;
}

bool Emitter::isActive()
{
	return active;
}

/*----------------------------*/
// VIRTUAL
/*----------------------------*/
Vec3D Emitter::generateRandomPos()
{
	return origin;
}

/*----------------------------*/
// OTHERS
/*----------------------------*/
Particle * Emitter::generateParticle(int model_start, int model_verts, int type)
{
	//~hardcoded particle information~
	//will later add switch statement between different enums.
	//i realize having model_start and model_verts as inputs probably isn't the best solution;
	//maybe Emitter should save cube and sphere indices as member variables instead of world.
	//but for now i'm sick and am just pushing what i have.
	//[delete this message later]

	Particle * p = new Particle();

	Material mat = Material();
	Vec3D vel;
	Vec3D acc;
	float lifespan;

	if (type == WATER_EMITTER)
	{
		mat.setAmbient(glm::vec3(0, 0, 1));
		mat.setDiffuse(glm::vec3(0, 0, 1));
		mat.setSpecular(glm::vec3(0.75, 0.75, 0.75));
		vel = Vec3D(1 + .1 * (rand()%5), 5, .1 * (rand()%5));
		acc = Vec3D(0.0, -9.8, 0.0);
		lifespan = 5 + (.1 * (rand()%5));
	}
	else if (type == FIRE_EMITTER)
	{
		mat.setAmbient(glm::vec3(1, 0, 0));
		mat.setDiffuse(glm::vec3(1, 0, 0));
		mat.setSpecular(glm::vec3(0.75, 0.75, 0.75));
		vel = Vec3D(0.0, 5.0, 0.0);
		acc = Vec3D();
		lifespan = 1 + (.1 * (rand()%5));
	}

	p->setPos(generateRandomPos());
	p->setVel(vel);
	p->setAcc(acc);
	p->setLifespan(lifespan);
	p->setMaterial(mat);
	p->setSize(Vec3D(.1, .1, .1));
	p->setVertexInfo(model_start, model_verts);

	return p;
}

void Emitter::changeActive()
{
	active = !active;
}
