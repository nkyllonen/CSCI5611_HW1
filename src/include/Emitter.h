#ifndef EMITTER_INCLUDED
#define EMITTER_INCLUDED

#include "Vec3D.h"
#include "Material.h"
#include "Particle.h"
#include "Util.h"

enum EMITTER_type
{
  BALL_EMITTER,
  WATER_EMITTER,
  FIRE_EMITTER,
  SPELL_EMITTER,
  DEFAULT_EMITTER
};

class Emitter
{
protected:
  Vec3D origin;
  float gen_rate; //number of particles to generate per second
  bool active;

  //for color changing
  Vec3D color1;
  Vec3D color2;
  Vec3D color3;
  int particle_type;

  //PRIVATE
  void resetColors();

public:
  Emitter();
  Emitter(Vec3D o);
  Emitter(Vec3D o, float rate);
  ~Emitter();

  //SETTERS
  void setOrigin(Vec3D o);
  void setGenRate(float g);
  void setType(int num);
  void setActive(bool b);

  //GETTERS
  Vec3D getOrigin();
  float getGenRate();
  bool isActive();
  int getType();

  //VIRTUAL
  //child classes will have different pos generation algorithms
  virtual Vec3D generateRandomPos();

  //OTHERS
  Particle * generateParticle(int model_start, int model_verts, Camera * cam, float mouse_x, float mouse_y);
  void changeActive();
  Vec3D generateNewColor(float t);

};
#endif
