#pragma once

#include <glm/glm.hpp>
#include <Object.hpp>

class Camera {
protected:
  struct Plane {
    glm::vec4 normal;
    glm::vec4 pos;
  };
  glm::mat4 m_ViewMatrix;
  Plane frustum[6];
public:
  glm::mat4 getViewMatrix() { return m_ViewMatrix; }
  bool checkFrustum(Object* obj);
};

/* 
*/