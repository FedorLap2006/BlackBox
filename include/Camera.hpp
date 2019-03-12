#pragma once

#include <glm/glm.hpp>
#include <Object.hpp>

class Camera {
protected:
  glm::mat4 m_ViewMatrix;
  glm::vec3 frustum[2][4];
public:
  glm::mat4 getViewMatrix() { return m_ViewMatrix; }
  bool checkFrustum(Object* obj);
};