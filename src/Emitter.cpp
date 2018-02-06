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
	particle_type = DEFAULT_EMITTER;
}

Emitter::Emitter(Vec3D o)
{
	origin = o;
	gen_rate = 0.1;
	active = true;
	particle_type = DEFAULT_EMITTER;
}

Emitter::Emitter(Vec3D o, float rate)
{
	origin = o;
	gen_rate = rate;
	active = true;
	particle_type = DEFAULT_EMITTER;
}

Emitter::~Emitter()
{
}

/*----------------------------*/
// PROTECTED
/*----------------------------*/
void Emitter::resetColors()
{
	switch (particle_type) {
		case BALL_EMITTER:
			color1 = Vec3D(1,0,0);
			color2 = Vec3D();
			color3 = Vec3D();
			break;
		case WATER_EMITTER:
			color1 = Vec3D(0.1,0.3,1.0);
			color2 = Vec3D();
			color3 = Vec3D();
			break;
		case FIRE_EMITTER:
			color1 = Vec3D(1.0,1.0,1.0);
			color2 = Vec3D(1.0,0.9,0.0);
			color3 = Vec3D(1.0,0.3,0.0);
			break;
		case SPELL_EMITTER:
			color1 = Vec3D(0.0,1.0,0.0);
			color2 = Vec3D(1.0,.08,.58);
			color3 = Vec3D();
			break;
		case SNOW_EMITTER:
			color1 = Vec3D(1,1,1);
			color2 = Vec3D();
			color3 = Vec3D();
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
	particle_type = num;
	resetColors();
}

void Emitter::setActive(bool b)
{
	active = b;
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
	return particle_type;
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
Particle * Emitter::generateParticle(int model_start, int model_verts, Camera * cam, float mouse_x, float mouse_y)
{
	Particle * p = new Particle();

	Material mat = Material();
	Vec3D pos, vel, acc, size;
	float lifespan, damping;

	switch (particle_type) {
		case BALL_EMITTER:
			pos = generateRandomPos();
			vel = Vec3D(-1 + .1 * (rand()%10), 0, -1 + .1 * (rand()%10));
			lifespan = 10;
			acc = Vec3D(0,-9.8,0);
			size = Vec3D(1.0,1.0,1.0);
			damping = -0.7;
			break;
		case WATER_EMITTER:
			pos = generateRandomPos();
			vel = Vec3D(1 + .1 * (rand()%5), 5, .1 * (rand()%5));
			lifespan = 5 + (.1 * (rand()%5));
			acc = Vec3D(0,-9.8,0);
			size = Vec3D(.1,.1,.1);
			damping = -0.7;
			break;
		case FIRE_EMITTER:
			pos = generateRandomPos();
			vel = Vec3D(0.0, 1.0, 0.0);
			lifespan = 5 + (.1 * (rand()%5));
			acc = Vec3D((rand()%20 - 10)/50.0, 1.0e-4,(rand()%20 - 10)/50.0);
			size = Vec3D(.1,.1,.1);
			damping = -0.7;
			break;
		case SPELL_EMITTER:
			pos = cam->getPos() + cam->getDir() + .0014 * mouse_x * cam->getRight() - .0014 * mouse_y * cam->getUp();
			vel = 2 * cam->getDir() + (-.25 + .025 * (rand()%20)) * cam->getRight() + (-.25 + .025 * (rand()%20)) * cam->getUp();
			vel = vel + .003 * mouse_x * cam->getRight() - .003 * mouse_y * cam->getUp();
			lifespan = 5 + (.1 * (rand()%5));
			acc = 0.1 * cam->getDir();
			size = Vec3D(.05,.05,.05);
			damping = -0.7;
			break;
		case SNOW_EMITTER:
			pos = generateRandomPos();
			vel = Vec3D(-1 + .1 * (rand()%20), -2, -1 + .1 * (rand()%20));
			vel.normalize();
			lifespan = 10 + (.1 * (rand()%5));
			acc = Vec3D(0,0,0);
			size = Vec3D(.1,.1,.1);
			damping = 0.0;
			break;
		case DEFAULT_EMITTER:
			pos = generateRandomPos();
			vel = Vec3D(1 + .1 * (rand()%5), 5, .1 * (rand()%5));
			lifespan = 5 + (.1 * (rand()%5));
			acc = Vec3D(0,-9.8,0);
			size = Vec3D(.1,.1,.1);
			damping = -0.7;
			break;
		default:
			break;
	}

	//change mat properties
	resetColors();
	mat.setAmbient(util::vec3DtoGLM(color1));
	mat.setDiffuse(util::vec3DtoGLM(color1));
	mat.setSpecular(glm::vec3(0.75, 0.75, 0.75));

	p->setPos(pos);
	p->setVel(vel);
	p->setAcc(acc);
	p->setLifespan(lifespan);
	p->setMaterial(mat);
	p->setSize(size);
	p->setVertexInfo(model_start, model_verts);
	p->setDamping(damping);

	return p;
}

void Emitter::changeActive()
{
	active = !active;
}

Vec3D Emitter::generateNewColor(float t)
{
	switch (particle_type) {
		case BALL_EMITTER:
			return color1;
		case WATER_EMITTER:
			return color1;
		case FIRE_EMITTER:
			return util::colorInterp3(color1, color2, color3, t, 0.1);
		case SPELL_EMITTER:
			return util::colorInterp2(color1, color2, t);
		case SNOW_EMITTER:
			return color1;
		case DEFAULT_EMITTER:
			return color1;
		default:
			cout << "ERROR: reached default case in Emitter::generateNewColor()" << endl;
			return color1;
	}
}
