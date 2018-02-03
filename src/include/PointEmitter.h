#ifndef POINTEMITTER_INCLUDED
#define POINTEMITTER_INCLUDED

#include "Emitter.h"
#include "Vec3D.h"
#include "Material.h"
#include "Particle.h"

class PointEmitter : public Emitter
{
private:


public:
	//CONSTRUCTORS AND DESTRUCTORS
	~PointEmitter();

	//VIRTUAL
	Vec3D generateRandomPos();

};
#endif
