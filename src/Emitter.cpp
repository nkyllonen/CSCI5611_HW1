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
	pos = Vec3D();
	vel = Vec3D();
	acc = Vec3D(0, -9.8, 0);
	lifespan = 5; //particles live for 5 seconds
	gen_rate = 5; //1 particle every 5 seconds
	mat = Material();
	size = Vec3D(1, 1, 1);
	start_vertex_index = 0;
	total_vertices = 0;
}

Emitter::~Emitter()
{
}

/*----------------------------*/
// SETTERS
/*----------------------------*/
void Emitter::setPos(Vec3D p)
{
	pos = p;
}

void Emitter::setVel(Vec3D v)
{
	vel = v;
}

void Emitter::setAcc(Vec3D a)
{
	acc = a;
}

void Emitter::setLifespan(float l)
{
	lifespan = l;
}

void Emitter::setGenRate(float g)
{
	gen_rate = g;
}

void Emitter::setMaterial(Material m)
{
	mat = m;
}

void Emitter::setSize(Vec3D s)
{
	size = s;
}

void Emitter::setVertexInfo(int start, int total)
{
	start_vertex_index = start;
	total_vertices = total;
}

/*----------------------------*/
// GETTERS
/*----------------------------*/
Vec3D Emitter::getPos()
{
	return pos;
}

Vec3D Emitter::getVel()
{
	return vel;
}

Vec3D Emitter::getAcc()
{
	return acc;
}

float Emitter::getLifespan()
{
	return lifespan;
}

float Emitter::getGenRate()
{
	return gen_rate;
}

Vec3D Emitter::getSize()
{
	return size;
}

/*----------------------------*/
// OTHERS
/*----------------------------*/
Particle * Emitter::generateParticle()
{
	Particle * p = new Particle();

	p->setPos(pos);
	p->setVel(vel + Vec3D(.1 * (rand()%5), 0, .1 * (rand()%5)));
	p->setAcc(acc);
	p->setLifespan(lifespan + (.5 * (rand()%5)));
	p->setMaterial(mat);
	p->setSize(size);
	p->setVertexInfo(start_vertex_index, total_vertices);

	return p;
}





