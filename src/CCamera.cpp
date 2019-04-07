#include "CCamera.hpp"


void CCameraFPS::move(glm::vec3 v) {
  m_Pos += v;
  fetchLook();
}


void CCameraFPS::rotate(glm::vec3 v) {
  if (v.x != 0) {
    
    glm::mat4 rmat = glm::mat4_cast(glm::angleAxis(v.y, glm::vec3(0, 1, 0)));
  }
  // glm::quat_cast(glm::yawPitchRoll(v.x, v.y, v.z));
  // glm::mat4_cast(glm::quat(...));
  fetchLook(true);
}

void CCameraFPS::setTarget(glm::vec3 v) {

}