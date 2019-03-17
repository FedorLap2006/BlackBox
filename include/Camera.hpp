#pragma once

#include <glm/glm.hpp>
#include <Object.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

class Camera {
protected:
  struct Plane {
    glm::vec4 normal;
    glm::vec4 pos;
  };
  glm::mat4 m_ViewMatrix = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f,1.0f,0.0f));
  glm::vec3 m_Target = { 0.0,0.0,0.0 };
  Plane m_Frustum[6] = { {{0.0,0.0,0.0,0.0},{0.0,0.0,0.0,1.0} } };
public:
  // Camera(double w, double h);
  Camera();
  void move(glm::vec3 v) {

    glm::mat4 tmat = glm::translate(glm::mat4(1.0f), v);
    m_ViewMatrix *= tmat;
  }
  virtual void rotate(float angle, glm::vec3 rot) = 0;

  glm::mat4 getViewMatrix() { return m_ViewMatrix; }
  bool checkFrustum(Object* obj);
};

class CameraFPS : public Camera {
public:
  CameraFPS();
  void rotate(float angle,glm::vec3 rot) {
    // m_ViewMatrix = lookAt(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 tmat = glm::rotate(glm::mat4(1.0f), angle, rot);
    m_ViewMatrix *= tmat;
  }
};

class CameraAny : public Camera {
public:
  void rotate(float angle, glm::vec3 rot) {
    glm::mat4 tmat = glm::yawPitchRoll(rot.x, rot.y, rot.z);
    m_ViewMatrix *= tmat;
  }

};

/* 
*/