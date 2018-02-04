#ifndef EMITTER_INCLUDED
#define EMITTER_INCLUDED

#include "Vec3D.h"
#include "Material.h"
#include "Particle.h"

enum EMITTER_type
{
  WATER_EMITTER,
  FIRE_EMITTER
};

class Emitter
{
protected:
  Vec3D origin;
  float gen_rate; //number of particles to generate per second
  bool active;

public:
  Emitter();
  Emitter(Vec3D o);
  Emitter(Vec3D o, float rate);
  ~Emitter();

  //SETTERS
  void setOrigin(Vec3D o);
  void setGenRate(float g);
  void setActive(bool b);

  //GETTERS
  Vec3D getOrigin();
  float getGenRate();
  bool isActive();

  //VIRTUAL
  virtual Vec3D generateRandomPos();

  //OTHERS
  Particle * generateParticle(int model_start, int model_verts, int type);
  void changeActive();

};
#endif
