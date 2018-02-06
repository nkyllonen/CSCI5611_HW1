#ifdef __APPLE__
#include "include/SphereEmitter.h"
#else
#include "SphereEmitter.h"
#endif

using namespace std;

/*----------------------------*/
// CONSTRUCTORS AND DESTRUCTORS
/*----------------------------*/
SphereEmitter::SphereEmitter()
{
	radius = 1;
}

SphereEmitter::SphereEmitter(Vec3D o) : Emitter::Emitter(o)
{
	radius = 1;
}

SphereEmitter::SphereEmitter(Vec3D o, float r) : Emitter::Emitter(o)
{
	radius = r;
}

SphereEmitter::~SphereEmitter()
{
}

/*----------------------------*/
// SETTERS
/*----------------------------*/
void SphereEmitter::setRadius(float r)
{
	radius = r;
}

/*----------------------------*/
// GETTERS
/*----------------------------*/
float SphereEmitter::getRadius()
{
	return radius;
}

/*----------------------------*/
// VIRTUAL
/*----------------------------*/
Vec3D SphereEmitter::generateRandomPos()
{
	float u = rand() / (RAND_MAX / 1.0f);
	float v = rand() / (RAND_MAX / 1.0f);
	float phi = 2 * M_PI * u;
	float theta = acos(2 * v - 1);
	return Vec3D(getOrigin().getX() + radius * sin(theta) * cos(phi), getOrigin().getY() + radius * sin(theta) * sin(phi), getOrigin().getZ() + radius * cos(theta)); //assumes disc in the y plane
}

void SphereEmitter::changeSize(float multiplier)
{
	radius = radius * multiplier;
}
