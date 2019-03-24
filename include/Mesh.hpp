#pragma once


#include "IMesh.hpp"
#include <vector>
// #include <glm/glm.hpp>
#include <MatrixTranform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <VertexBuffer.hpp>
#include <CShader.hpp>

class Mesh : public IMesh {
private:
  CShaderProgram *m_Shader;
//  CShaderProgram *m_Shader;
  // std::vector<float> m_Verts;
  VertexBuffer *m_VertexBuf;
  std::vector<float> m_Verts;
  glm::vec3 m_Pos;
  glm::mat4 m_ModelMatrix;

public:
  Mesh(CShaderProgram* msp) : m_Shader(msp) {}
  Mesh(CShaderProgram* msp, std::vector<float> Verts) : 
      m_Shader(msp),
      m_VertexBuf(new VertexBuffer(Verts.data(), Verts.size() * sizeof(GLfloat))),
      m_Verts(Verts) {

   }
  glm::vec3 getPos() { return m_Pos; }
  void draw(glm::mat4 mat) override; // -> CShaderProgram->use()
  VertexBuffer* getVBuffer() { return m_VertexBuf; }
  std::vector<float> getVerts() { return m_Verts; }

  void rotate(double angle, glm::vec3 v) { m_ModelMatrix *= glm::rotate(glm::mat4(1.0f), (float)angle, v); }
  void translate(glm::vec3 v) { m_ModelMatrix *= glm::translate(glm::mat4(1.0f), v); m_Pos = v; }
  void scale(glm::vec3 v) { m_ModelMatrix *= glm::scale(glm::mat4(1.0f), v); }

};