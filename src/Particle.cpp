#ifdef __APPLE__
#include "include/Particle.h"
#else
#include "Particle.h"
#endif

using namespace std;


/*----------------------------*/
// CONSTRUCTORS AND DESTRUCTORS
/*----------------------------*/
Particle::Particle() : WorldObject() //call parent default
{
  birth = 0.0;
  lifespan = 5;
}

Particle::Particle(Vec3D init_pos) : WorldObject(init_pos) //call parent constructor
{
  birth = 0.0;
  lifespan = 5;
}

Particle::~Particle()
{
}

/*----------------------------*/
// SETTERS
/*----------------------------*/
void Particle::setBirth(float b)
{
	birth = b;
}

void Particle::setLifespan(float l)
{
	lifespan = l;
}

void Particle::setDamping(float d)
{
  damping = d;
}

/*----------------------------*/
// GETTERS
/*----------------------------*/
float Particle::getBirth()
{
	return birth;
}

float Particle::getLifespan()
{
	return lifespan;
}

float Particle::getDamping()
{
  return damping;
}

/*----------------------------*/
// OTHERS
/*----------------------------*/


/*----------------------------*/
// VIRTUALS
/*----------------------------*/
int Particle::getType()
{
	return PARTICLE_WOBJ;
}
