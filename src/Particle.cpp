#ifdef __APPLE__
#include "include/Particle.h"
#else
#include "Particle.h"
#endif

using namespace std;


/*----------------------------*/
// CONSTRUCTORS AND DESTRUCTORS
/*----------------------------*/
Particle::Particle()
{
  pos = Vec3D();
  vel = Vec3D();
  acc = Vec3D();
  birth = 0.0;
  lifespan = 5;
  size = Vec3D(1, 1, 1);
	start_vertex_index = 0;
	total_vertices = 0;
	mat = Material();
}

Particle::Particle(Vec3D init_pos)
{
  pos = init_pos;
  vel = Vec3D();
  acc = Vec3D();
  birth = 0.0;
  lifespan = 5;
  size = Vec3D(1, 1, 1);
	start_vertex_index = 0;
	total_vertices = 0;
	mat = Material();
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

Vec3D Particle::getSize()
{
  return size;
}

/*----------------------------*/
// OTHERS
/*----------------------------*/
