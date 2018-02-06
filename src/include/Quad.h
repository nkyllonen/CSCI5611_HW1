#ifndef QUAD_INCLUDED
#define QUAD_INCLUDED

#include "WorldObject.h"

class Quad : public WorldObject
{
private:
  Vec3D normal;

public:
  Quad();
  Quad(Vec3D init_pos, Vec3D init_n);
  ~Quad();

  //SETTERS
  void setNormal(Vec3D n);

  //GETTERS
  Vec3D getNormal();

  //VIRTUALS
  int getType();

  //OTHERS

};

#endif
