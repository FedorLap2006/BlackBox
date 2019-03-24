#include "Triangle.hpp"
#include "VertexBuffer.hpp"
#include <iostream>

#include <MatrixTranform.hpp>

using namespace std;

Triangle::Triangle(CShaderProgram *program) :
  m_Shader(program)
{
  // ty = OBJType::TPRIMITIVE;
  m_Vertices = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
  };

  // glm::mat4 rot = glm::rotate(glm::mat4(1.0f),rotAngle,glm::vec3(1.0, 0.0, 0.0)); 
  glm::mat4 rot = glm::scale(glm::vec3(1.0f, 2.0f, 1.0f));

  m_Vertices = m_Vertices * rot;

  addMesh({ 0.0,0.0,0.0 }, m_Vertices);

  // VertexBuffer *vb = new VertexBuffer(m_Vertices.data(),m_Vertices.size()*sizeof(GLfloat));



  // m_Geom = new Geometry(vb, nullptr);
}


Triangle::~Triangle() 
{
  
}

void Triangle::draw() {
  Mesh* m = getMesh(0);

  m->rotate(102.0, { 0,1,2 });

  m->draw(m_WorldMatrix);
  // VertexBuffer *vb = m_Geom->getVertexBuffer();
  /*void *d = vb->GetGLarray();
  std::vector<float> *v = reinterpret_cast<std::vector<float>*>(d);
  *v = *v * glm::mat4(0.0f);
*/
  // m_Shader->use();
  // vb->draw();
}

void Triangle::move(glm::vec3 m)
{
  Mesh* mesh = getMesh(0);
  // if (!mesh) return;
  mesh->translate(m);
}

void Triangle::rotate(double angle,glm::vec3 m)
{
  Mesh* mesh = getMesh(0);
  mesh->rotate(angle, m);
}
