#include "CCamera.hpp"


void CCameraFPS::move(glm::vec3 v) {
  m_Pos += v;
  fetchLook();
}


void CCameraFPS::rotate(glm::vec3 v) {
  glm::quat xrot = glm::angleAxis(v.x, glm::vec3(1.0f, 0.0f, 0.0f));
  glm::quat yrot = glm::angleAxis(v.y, glm::vec3(0.0f, 1.0f, 0.0f));
  glm::quat zrot = glm::angleAxis(v.z, glm::vec3(0.0f, 0.0f, 1.0f));

  
  m_Direction *= zrot;
  m_Right *= xrot;
  m_Up *= yrot;


  m_View = m_View * glm::mat4_cast(xrot * yrot * zrot);
  // glm::quat_cast(glm::yawPitchRoll(v.x, v.y, v.z));
  // glm::mat4_cast(glm::quat(...));
  // fetchLook(true);
  calcVecs();
}

void CCameraFPS::setTarget(glm::vec3 v) {
  m_Target = v;
  fetchLook();
}