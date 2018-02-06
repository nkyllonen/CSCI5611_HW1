#ifdef __APPLE__
#include "include/Quad.h"
#else
#include "Quad.h"
#endif

using namespace std;

/*----------------------------*/
// CONSTRUCTORS AND DESTRUCTORS
/*----------------------------*/
Quad::Quad() : WorldObject()
{
  normal = Vec3D(1,0,0);
}

Quad::Quad(Vec3D init_pos, Vec3D init_n) : WorldObject(init_pos)
{
  normal = init_n;
}

Quad::~Quad()
{

}

/*----------------------------*/
// SETTERS
/*----------------------------*/
void Quad::setNormal(Vec3D n)
{
  normal = n;
}

/*----------------------------*/
// GETTERS
/*----------------------------*/
Vec3D Quad::getNormal()
{
  return normal;
}

/*----------------------------*/
// VIRTUALS
/*----------------------------*/
int Quad::getType()
{
	return QUAD_WOBJ;
}
