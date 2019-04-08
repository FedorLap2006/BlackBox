#pragma once
//<<<<<<< HEAD
//
//#include <glm/gtx/quaternion.hpp>
//#include <glm/glm.hpp>
//#include <glm/gtx/transform.hpp>
//#include <glm/gtx/euler_angles.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/rotate_vector.hpp>
//// #include <glm/gtx/rotate_normalized_axis.hpp>
//
//
//class ICamera {
//protected:
//  glm::mat4 m_View;
//  glm::mat4 m_Proj;
//
//  glm::vec3 m_Angles;
//  glm::vec3 m_Pos;
//  // Vecs
//  glm::vec3 m_Up;
//  glm::vec3 m_Right;
//  glm::vec3 m_Direction;
//  glm::vec3 m_Target;
//public:
//  /*
//  virtual void yaw(float angle) = 0;
//  virtual void pitch(float angle) = 0;
//  virtual void roll(float angle) = 0;
//  */
//  
//  virtual inline void fetchLook(bool manual=false) { 
//    if (!manual) {
//      calcVecs();
//    }
//    m_View = glm::lookAt(m_Pos, m_Target, m_Up); 
//  }
//
//  virtual inline void calcVecs() {
//    // glm::vec3 up = { 0,1,0 };
//    m_Direction = glm::normalize(m_Pos - m_Target);
//    // m_Right = glm::cross(up, m_Direction);
//    m_Right = glm::cross(m_Up, m_Direction);
//    m_Up = glm::cross(m_Direction, m_Right);
//  }
//
//  virtual void move(glm::vec3 v) = 0;
//  virtual void rotate(glm::vec3 v) = 0;
//  virtual void setTarget(glm::vec3 t) = 0;
//  glm::mat4 getProj() { return m_Proj; }
//  glm::mat4 getView() { return m_View; }
//  float* getProjRef() { return glm::value_ptr(m_Proj); }
//  float* getViewRef() { return glm::value_ptr(m_View); }
//};
//
//class CCameraFPS : public ICamera {
//public:
//  void move(glm::vec3 v) override;
//  void rotate(glm::vec3 v) override;
//  void setTarget(glm::vec3 t) override;
//};
// =======
#include <InputHandler.hpp>
#include <glm/glm.hpp>
#define PI 3.1415926535897932384626433832795
#define PIdiv180 (PI/180.0)

class CCamera : public IInputEventListener
{
private:
  const float MOVE_SPEED = 0.50f;
  glm::vec3 m_pos; 
  glm::vec3 m_target;
  glm::vec3 m_right;
  glm::vec3 m_up;
  glm::vec3 m_angles;

public:
  CCamera(glm::vec3 pos);
  CCamera();
  ~CCamera();

  void update();
  void move(glm::vec3 pos);
  void strafe(glm::vec3 pos);
  void rotateY(float angle);
  void rotateX(float angle);
  void rotateZ(float angle);
  glm::mat4 getViewMatrix();
  glm::mat4 getProjectionMatrix();

  bool OnInputEvent(sf::Event &event);


};
// >>>>>>> 4ee289218448351af2f3976559c841116c6211e6
