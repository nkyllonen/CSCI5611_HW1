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
	//this is just the generateRandomPos for a disc,
	//i haven't implemented it for sphere yet
	
	float r = rand() / (RAND_MAX / 1.0f);
	float theta = rand() / (RAND_MAX / (2 * M_PI));
	return Vec3D(r * cos(theta), getOrigin().getY(), r * sin(theta)); //assumes disc in the y plane
}
