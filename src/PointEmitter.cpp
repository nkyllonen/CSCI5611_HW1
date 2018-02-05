#ifdef __APPLE__
#include "include/PointEmitter.h"
#else
#include "PointEmitter.h"
#endif

using namespace std;

/*----------------------------*/
// VIRTUAL
/*----------------------------*/
PointEmitter::PointEmitter(Vec3D o) : Emitter::Emitter(o)
{
}

PointEmitter::~PointEmitter()
{
}

/*----------------------------*/
// VIRTUAL
/*----------------------------*/
Vec3D PointEmitter::generateRandomPos()
{
	return origin;
}
