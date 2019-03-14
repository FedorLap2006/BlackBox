#include "Mesh.hpp"

void Mesh::draw(glm::mat4 mat) { // MVP

  // ...
  const GLuint msp = m_Shader->get();

  m_Shader->use();

  // GLuint VarID = glGetUniformLocation(msp, "...");
  GLuint MVP = glGetUniformLocation(msp, "mvp");
  // GLuint Mloc = glGetUniformLocation(msp, "lcmesh");
  mat *= m_ModelMatrix;

  glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(mat));
  m_VertexBuf->draw();
  
}
