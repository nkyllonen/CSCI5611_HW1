#ifndef PARTICLE_INCLUDED
#define PARTICLE_INCLUDED

#include "WorldObject.h"

class Particle : public WorldObject
{
private:
  float birth;
  float lifespan;
  float damping;

public:
  Particle();
  Particle(Vec3D init_pos);
  ~Particle();

  //SETTERS
  void setBirth(float b);
  void setLifespan(float l);

  //GETTERS
  float getBirth();
  float getLifespan();
  float getDamping();

  //OTHERS

};

#endif
