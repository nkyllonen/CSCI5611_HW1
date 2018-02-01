#ifdef __APPLE__
#include "include/Particle.h"
#else
#include "Particle.h"
#endif

using namespace std;


/*----------------------------*/
// CONSTRUCTORS AND DESTRUCTORS
/*----------------------------*/
Particle::Particle()
{
  pos = Vec3D();
  vel = Vec3D();
  acc = Vec3D();
  size = Vec3D(1, 1, 1);
	start_vertex_index = 0;
	total_vertices = 0;
	mat = Material();
}

Particle::Particle(Vec3D init_pos)
{
  pos = init_pos;
  vel = Vec3D();
  acc = Vec3D();
  size = Vec3D(1, 1, 1);
	start_vertex_index = 0;
	total_vertices = 0;
	mat = Material();
}

Particle::~Particle()
{

}

/*----------------------------*/
// SETTERS
/*----------------------------*/
void Particle::setPos(Vec3D p)
{
  pos = p;
}

void Particle::setVel(Vec3D v)
{
  vel = v;
}

void Particle::setAcc(Vec3D a)
{
  acc = a;
}

void Particle::setMaterial(Material m)
{
  mat = m;
}

void Particle::setSize(Vec3D s)
{
  size = s;
}

void Particle::setVertexInfo(int start, int total)
{
  start_vertex_index = start;
  total_vertices = total;
}

void Particle::setDamping(float d)
{
  damping = d;
}

/*----------------------------*/
// GETTERS
/*----------------------------*/
Vec3D Particle::getPos()
{
  return pos;
}

Vec3D Particle::getVel()
{
  return vel;
}

Vec3D Particle::getAcc()
{
  return acc;
}

Vec3D Particle::getSize()
{
  return size;
}

float Particle::getDamping()
{
  return damping;
}

/*----------------------------*/
// OTHERS
/*----------------------------*/
void Particle::draw(GLuint shaderProgram)
{
  GLint uniModel = glGetUniformLocation(shaderProgram, "model");

	glm::mat4 model;
	glm::vec3 size_v = util::vec3DtoGLM(size);
	glm::vec3 pos_v = util::vec3DtoGLM(pos);

	//build model matrix specific to this Particle
	model = glm::translate(model, pos_v);
	model = glm::scale(model, size_v);
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

	//fragment shader uniforms (from Material)
	GLint uniform_ka = glGetUniformLocation(shaderProgram, "ka");
	GLint uniform_kd = glGetUniformLocation(shaderProgram, "kd");
	GLint uniform_ks = glGetUniformLocation(shaderProgram, "ks");
	GLint uniform_s = glGetUniformLocation(shaderProgram, "s");

	glm::vec3 mat_AMB = mat.getAmbient();
	glUniform3f(uniform_ka, mat_AMB[0], mat_AMB[1], mat_AMB[2]);

	glm::vec3 mat_DIF = mat.getDiffuse();
	glUniform3f(uniform_kd, mat_DIF[0], mat_DIF[1], mat_DIF[2]);

	glm::vec3 mat_SPEC = mat.getSpecular();
	glUniform3f(uniform_ks, mat_SPEC[0], mat_SPEC[1], mat_SPEC[2]);

	glUniform1f(uniform_s, mat.getNS());

	//starts at an offset of start_vertex_index
	//(Primitive Type, Start Vertex, End Vertex)
	glDrawArrays(GL_TRIANGLES, start_vertex_index, total_vertices);
}
