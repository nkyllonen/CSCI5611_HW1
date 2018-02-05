#ifndef DISCEMITTER_INCLUDED
#define DISCEMITTER_INCLUDED

#include "Emitter.h"
#include "Vec3D.h"
#include "Material.h"
#include "Particle.h"

#include <stdlib.h>
#include <cmath>

class DiscEmitter : public Emitter
{
private:
	float radius;


public:
	//CONSTRUCTORS AND DESTRUCTORS
	DiscEmitter();
	DiscEmitter(Vec3D o);
	DiscEmitter(Vec3D o, float r);
	~DiscEmitter();

	//SETTERS
	void setRadius(float r);

	//GETTERS
	float getRadius();

	//VIRTUAL
	Vec3D generateRandomPos();

};
#endif
