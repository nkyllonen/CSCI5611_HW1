#ifdef __APPLE__
#include "include/Emitter.h"
#else
#include "Emitter.h"
#endif

using namespace std;

/*----------------------------*/
// CONSTRUCTORS AND DESTRUCTORS
/*----------------------------*/
Emitter::Emitter()
{
	origin = Vec3D(0, 5, 0);
	gen_rate = 0.1; //1 particle every gen_rate seconds
}

Emitter::Emitter(Vec3D o)
{
	origin = o;
	gen_rate = 0.1;
}

Emitter::Emitter(Vec3D o, float rate)
{
	origin = o;
	gen_rate = rate;
}

Emitter::~Emitter()
{
}

/*----------------------------*/
// SETTERS
/*----------------------------*/
void Emitter::setOrigin(Vec3D o)
{
	origin = o;
}

void Emitter::setGenRate(float g)
{
	gen_rate = g;
}

/*----------------------------*/
// GETTERS
/*----------------------------*/
Vec3D Emitter::getOrigin()
{
	return origin;
}

float Emitter::getGenRate()
{
	return gen_rate;
}

/*----------------------------*/
// VIRTUAL
/*----------------------------*/
Vec3D Emitter::generateRandomPos()
{
	return origin;
}

/*----------------------------*/
// OTHERS
/*----------------------------*/
Particle * Emitter::generateParticle(int model_start, int model_verts)
{
	//~hardcoded particle information~
	//will later add switch statement between different enums.
	//i realize having model_start and model_verts as inputs probably isn't the best solution;
	//maybe Emitter should save cube and sphere indices as member variables instead of world.
	//but for now i'm sick and am just pushing what i have.
	//[delete this message later]

	Particle * p = new Particle();

	//green sphere
	Material mat = Material();
	mat.setAmbient(glm::vec3(0, 1, 0));
	mat.setDiffuse(glm::vec3(0, 1, 0));
	mat.setSpecular(glm::vec3(0.75, 0.75, 0.75));

	p->setPos(generateRandomPos());
	p->setVel(Vec3D(1, 5, 0) + Vec3D(.1 * (rand()%5), 0, .1 * (rand()%5)));
	p->setAcc(Vec3D(0.0, -9.8, 0.0));
	p->setLifespan(5 + (.1 * (rand()%5)));
	p->setMaterial(mat);
	p->setSize(Vec3D(.1, .1, .1));
	p->setVertexInfo(model_start, model_verts);

	return p;
}
