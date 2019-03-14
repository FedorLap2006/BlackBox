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
  glm::vec3 m_CurPurpose = { 0.0,0.0,0.0 };
  Plane m_Frustum[6] = { {{0.0,0.0,0.0,0.0},{0.0,0.0,0.0,1.0} } };
public:
  Camera(double w, double h);

  void move(glm::vec3 v) {
    m_ViewMatrix = glm::lookAt(v, m_CurPurpose, glm::vec3(0.0, 1.0, 0.0) );
  }
  void rotate(double angle) {
    m_ViewMatrix = lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
  }
  void setPurpose(glm::vec3 v) {
    m_CurPurpose = v;
  }
  glm::mat4 getViewMatrix() { return m_ViewMatrix; }
  bool checkFrustum(Object* obj);
};

/* 
*/