#pragma once


#include <InputHandler.hpp>

#include <glm/gtx/quaternion.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
// #include <glm/gtx/rotate_normalized_axis.hpp>

#define PI 3.1415926535897932384626433832795
#define PIdiv180 (PI/180.0)


class ICamera {
protected:
  const float SPEED = 0.50f;

  glm::mat4 m_View = glm::lookAt(glm::vec3(0.0f,0.0f,3.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0,1.0f,0.0f));
  glm::mat4 m_Proj = glm::perspective(45.0f, 16 / 9.0f, 0.1f, 100.0f);

  // glm::vec3 m_Angles = { 0,0,0 };
  glm::vec3 m_Pos = { 0,0,3 };
  // Vecs
  glm::vec3 m_Up = { 0,1,0 };
  glm::vec3 m_Right = { 1,0,0 };
  glm::vec3 m_Direction = { 0,0,0 };
  glm::vec3 m_Target = -glm::normalize(m_Pos - glm::vec3(0, 0, 0));
public:
  /*
  virtual void yaw(float angle) = 0;
  virtual void pitch(float angle) = 0;
  virtual void roll(float angle) = 0;
  */
  
  virtual inline void fetchLook(bool manual=false) { 
    if (!manual) {
      calcVecs();
    }
    m_View = glm::lookAt(m_Pos, m_Target, m_Up); 
  }

  virtual inline void calcVecs() {
    // glm::vec3 up = { 0,1,0 };
    m_Direction = glm::normalize(m_Pos - m_Target);
    // m_Right = glm::cross(up, m_Direction);
    m_Right = glm::cross(m_Up, m_Direction);
    m_Up = glm::cross(m_Direction, m_Right);
  }

  virtual void move(glm::vec3 v) = 0;
  virtual void rotate(glm::vec3 v) = 0;
  virtual void setTarget(glm::vec3 t) = 0;
  glm::mat4 getProj() { return m_Proj; }
  glm::mat4 getView() { return m_View; }
  float* getProjRef() { return glm::value_ptr(m_Proj); }
  float* getViewRef() { return glm::value_ptr(m_View); }
};

class CCameraFPS : public ICamera, public IInputEventListener {
public:
  struct {
    float yaw = 0;
    float pitch = 0;
    // float roll = 0;
    float x = 0;
    float y = 0;
    float z = 0;
  }m_Angles;

  void move(glm::vec3 v) override;
  void rotate(glm::vec3 v) override;
  void yawRotate(float a);
  void pitchRotate(float a);

  void yawPitch(float yaw,float pitch);

  void setTarget(glm::vec3 t) override;
  bool OnInputEvent(sf::Event &event) override;
};

class CCameraFly : public ICamera, public IInputEventListener {
public:
  struct {
    float yaw = 0;
    float pitch = 0;
    float roll = 0;
    float x = 0;
    float y = 0;
    float z = 0;
  }m_Angles;
  void move(glm::vec3 v) override;
  void rotate(glm::vec3 v) override;
  void setTarget(glm::vec3 t) override;
  void yawRotate(float yawa);
  void pitchRotate(float pitcha);
  void rollRotate(float rolla);
  void yawPitchRoll(float yaw, float pitch, float roll);
  bool OnInputEvent(sf::Event &event) override;
};
