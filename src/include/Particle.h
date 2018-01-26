#ifndef PARTICLE_INCLUDED
#define PARTICLE_INCLUDED

#include "Vec3D.h"
#include "Util.h"

class Particle
{
private:
  Vec3D pos;
  Vec3D vel;
  Vec3D acc;
  Vec3D color;

public:
  Particle();
  Particle(Vec3D init_pos);
  ~Particle();

  //SETTERS
  void setPos(Vec3D p);
  void setVel(Vec3D v);
  void setAcc(Vec3D a);
  void setColor(Vec3D c);

  //GETTERS
  Vec3D getPos();
  Vec3D getVel();
  Vec3D getAcc();
  Vec3D getColor();

};

#endif
