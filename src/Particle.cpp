#include "Particle.h"

using namespace std;


/*----------------------------*/
// CONSTRUCTORS AND DESTRUCTORS
/*----------------------------*/
Particle::Particle()
{
  pos = Vec3D();
  vel = Vec3D();
  acc = Vec3D();
  color = Vec3D();
}

Particle::Particle(Vec3D init_pos)
{
  pos = init_pos;
  vel = Vec3D();
  acc = Vec3D();
  color = Vec3D();
}

Particle::~Particle()
{
  
}

/*----------------------------*/
// SETTERS
/*----------------------------*/
void Particle::setPos(Vec3D p)
{
  pos = p;
}

void Particle::setVel(Vec3D v)
{
  vel = v;
}

void Particle::setAcc(Vec3D a)
{
  acc = a;
}

void Particle::setColor(Vec3D c)
{
  color = c;
}

/*----------------------------*/
// GETTERS
/*----------------------------*/
Vec3D Particle::getPos()
{
  return pos;
}

Vec3D Particle::getVel()
{
  return vel;
}

Vec3D Particle::getAcc()
{
  return acc;
}

Vec3D Particle::getColor()
{
  return color;
}
