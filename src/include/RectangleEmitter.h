#ifndef RECTANGLEEMITTER_INCLUDED
#define RECTANGLEEMITTER_INCLUDED

#include "Emitter.h"
#include "Vec3D.h"
#include "Material.h"
#include "Particle.h"

#include <stdlib.h>

class RectangleEmitter : public Emitter
{
private:
	float length;
	float width;


public:
	//CONSTRUCTORS AND DESTRUCTORS
	RectangleEmitter();
	RectangleEmitter(Vec3D o);
	RectangleEmitter(Vec3D o, float l, float w);
	~RectangleEmitter();

	//SETTERS
	void setLength(float l);
	void setWidth(float w);

	//GETTERS
	float getLength();
	float getWidth();

	//VIRTUAL
	Vec3D generateRandomPos();

};
#endif