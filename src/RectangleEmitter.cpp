#ifdef __APPLE__
#include "include/RectangleEmitter.h"
#else
#include "RectangleEmitter.h"
#endif

using namespace std;

/*----------------------------*/
// CONSTRUCTORS AND DESTRUCTORS
/*----------------------------*/
RectangleEmitter::RectangleEmitter()
{
	length = 1;
	width = 1;
}

RectangleEmitter::RectangleEmitter(Vec3D o, float l, float w) : Emitter::Emitter(o)
{
	length = l;
	width = w;
}

RectangleEmitter::~RectangleEmitter()
{
}

/*----------------------------*/
// SETTERS
/*----------------------------*/
void RectangleEmitter::setLength(float l)
{
	length = l;
}

void RectangleEmitter::setWidth(float w)
{
	width = w;
}

/*----------------------------*/
// GETTERS
/*----------------------------*/
float RectangleEmitter::getLength()
{
	return length;
}

float RectangleEmitter::getWidth()
{
	return width;
}

/*----------------------------*/
// VIRTUAL
/*----------------------------*/
Vec3D RectangleEmitter::generateRandomPos()
{
	float pos_x = rand() / (RAND_MAX / length);
	float pos_z = rand() / (RAND_MAX / width);
	return Vec3D(getOrigin().getX() + pos_x - (length / 2), getOrigin().getY(), getOrigin().getZ() + pos_z - (width / 2)); //assumes rectangle in the y plane
}
