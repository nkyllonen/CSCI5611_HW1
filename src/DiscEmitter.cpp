#ifdef __APPLE__
#include "include/DiscEmitter.h"
#else
#include "DiscEmitter.h"
#endif

using namespace std;

/*----------------------------*/
// CONSTRUCTORS AND DESTRUCTORS
/*----------------------------*/
DiscEmitter::DiscEmitter()
{
	radius = 1;
}

DiscEmitter::DiscEmitter(Vec3D o, float r) : Emitter::Emitter(o)
{
	radius = r;
}

DiscEmitter::~DiscEmitter()
{
}

/*----------------------------*/
// SETTERS
/*----------------------------*/
void DiscEmitter::setRadius(float r)
{
	radius = r;
}

/*----------------------------*/
// GETTERS
/*----------------------------*/
float DiscEmitter::getRadius()
{
	return radius;
}

/*----------------------------*/
// VIRTUAL
/*----------------------------*/
Vec3D DiscEmitter::generateRandomPos()
{
	float r = rand() / (RAND_MAX / 1.0f);
	float theta = rand() / (RAND_MAX / (2 * M_PI));
	return Vec3D(r * cos(theta), getOrigin().getY(), r * sin(theta)); //assumes disc in the y plane
}
