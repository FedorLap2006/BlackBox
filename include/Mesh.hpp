#pragma once


#include "IMesh.hpp"
#include <vector>
// #include <glm/glm.hpp>
#include <MatrixTranform.hpp>
#include <CShader.hpp>

class Mesh : public IMesh {
private:
  const CShaderProgram *m_Shader;
//  CShaderProgram *m_Shader;
  std::vector<float> m_Verts;
  glm::vec3 m_Pos;
  glm::mat4 m_WorldMatrix;

public:
  Mesh(CShaderProgram* msp) : m_Shader(msp) {}
  void draw(glm::mat4 mat) override; // -> CShaderProgram->use()


  void rotate(double angle, glm::vec3 v) { m_WorldMatrix *= glm::rotate(glm::mat4(1.0f), (float)angle, v); }
  void translate(glm::vec3 v) {  }
  void scale(glm::vec3 v) {  }

};