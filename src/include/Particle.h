#ifndef PARTICLE_INCLUDED
#define PARTICLE_INCLUDED

#include "Vec3D.h"
#include "Util.h"
#include "Camera.h"
#include "Material.h"

class Particle
{
private:
  Vec3D pos;
  Vec3D vel;
  Vec3D acc;

  //model information
  Material mat;
  Vec3D size;
  int start_vertex_index;
  int total_vertices;

public:
  Particle();
  Particle(Vec3D init_pos);
  ~Particle();

  //SETTERS
  void setPos(Vec3D p);
  void setVel(Vec3D v);
  void setAcc(Vec3D a);
  void setMaterial(Material m);
  void setSize(Vec3D s);
  void setVertexInfo(int start, int total);

  //GETTERS
  Vec3D getPos();
  Vec3D getVel();
  Vec3D getAcc();
  Vec3D getSize();

  //OTHERS
  void draw(Camera* cam, GLuint shaderProgram);

};

#endif
