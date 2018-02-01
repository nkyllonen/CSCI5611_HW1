#ifndef EMITTER_INCLUDED
#define EMITTER_INCLUDED

#include "Vec3D.h"
#include "Material.h"
#include "Particle.h"

class Emitter
{
private:
  Vec3D pos;
  Vec3D vel;
  Vec3D acc;
  float lifespan;
  float gen_rate; //number of particles to generate per second

  //model information
  Material mat;
  Vec3D size;
  int start_vertex_index;
  int total_vertices;

public:
  Emitter();
  ~Emitter();

  //SETTERS
  void setPos(Vec3D p);
  void setVel(Vec3D v);
  void setAcc(Vec3D a);
  void setLifespan(float l);
  void setGenRate(float g);
  void setMaterial(Material m);
  void setSize(Vec3D s);
  void setVertexInfo(int start, int total);

  //GETTERS
  Vec3D getPos();
  Vec3D getVel();
  Vec3D getAcc();
  float getLifespan();
  float getGenRate();
  Vec3D getSize();

  //OTHERS
  Particle * generateParticle();

};
#endif
