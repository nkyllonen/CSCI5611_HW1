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
	active = true;
	type = DEFAULT_EMITTER;
}

Emitter::Emitter(Vec3D o)
{
	origin = o;
	gen_rate = 0.1;
	active = true;
	type = DEFAULT_EMITTER;
}

Emitter::Emitter(Vec3D o, float rate)
{
	origin = o;
	gen_rate = rate;
	active = true;
	type = DEFAULT_EMITTER;
}

Emitter::~Emitter()
{
}

/*----------------------------*/
// PROTECTED
/*----------------------------*/
void Emitter::resetColors()
{
	switch (type) {
		case WATER_EMITTER:
		color1 = Vec3D(1.0,1.0,1.0);
		color2 = Vec3D(0.0,0.1,0.8);
		color3 = Vec3D();
		break;
		case FIRE_EMITTER:
		color1 = Vec3D(1.0,1.0,1.0);
		color2 = Vec3D(0.5,0.5,0.0);
		color3 = Vec3D(1.0,0.0,0.0);
		break;
		case DEFAULT_EMITTER:
		color1 = Vec3D();
		color2 = Vec3D();
		color3 = Vec3D();
		break;
		default:
		cout << "ERROR: reached default case in Emitter::resetColors()" << endl;
		color1 = Vec3D();
		color2 = Vec3D();
		color3 = Vec3D();
	}
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

void Emitter::setType(int num)
{
	type = num;
	resetColors();
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

bool Emitter::isActive()
{
	return active;
}

int Emitter::getType()
{
	return type;
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
	p->setDamping(-0.7);

	return p;
}

void Emitter::changeActive()
{
	active = !active;
}

Vec3D Emitter::generateNewColor(float t)
{
	switch (type) {
		case WATER_EMITTER:
		return util::colorInterp2(color1, color2, t);
		case FIRE_EMITTER:
		return util::colorInterp3(color1, color2, color3, t);
		case DEFAULT_EMITTER:
		return color1;
		default:
		cout << "ERROR: reached default case in Emitter::generateNewColor()" << endl;
		return color1;
	}
}
