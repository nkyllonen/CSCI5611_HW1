#ifndef SPHEREEMITTER_INCLUDED
#define SPHEREEMITTER_INCLUDED

#include "Emitter.h"
#include "Vec3D.h"
#include "Material.h"
#include "Particle.h"

#include <stdlib.h>
#include <cmath>

class SphereEmitter : public Emitter
{
private:
	float radius;


public:
	//CONSTRUCTORS AND DESTRUCTORS
	SphereEmitter();
	SphereEmitter(Vec3D o);
	SphereEmitter(Vec3D o, float r);
	~SphereEmitter();

	//SETTERS
	void setRadius(float r);

	//GETTERS
	float getRadius();

	//VIRTUAL
	Vec3D generateRandomPos();

};
#endif
