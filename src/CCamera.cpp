//<<<<<<< HEAD
//#include "CCamera.hpp"
//
//
//void CCameraFPS::move(glm::vec3 v) {
//  m_Pos += v;
//  fetchLook();
//}
//
//
//void CCameraFPS::rotate(glm::vec3 v) {
//  glm::quat xrot = glm::angleAxis(v.x, glm::vec3(1.0f, 0.0f, 0.0f));
//  glm::quat yrot = glm::angleAxis(v.y, glm::vec3(0.0f, 1.0f, 0.0f));
//  glm::quat zrot = glm::angleAxis(v.z, glm::vec3(0.0f, 0.0f, 1.0f));
//
//  
//  m_Direction *= zrot;
//  m_Right *= xrot;
//  m_Up *= yrot;
//
//
//  m_View = m_View * glm::mat4_cast(xrot * yrot * zrot);
//  // glm::quat_cast(glm::yawPitchRoll(v.x, v.y, v.z));
//  // glm::mat4_cast(glm::quat(...));
//  // fetchLook(true);
//  calcVecs();
//}
//
//void CCameraFPS::setTarget(glm::vec3 v) {
//  m_Target = v;
//  fetchLook();
//}
//=======
#include <CCamera.hpp>
#include <Opengl.hpp>
#include <glm/gtc/matrix_transform.hpp>

CCamera::CCamera() :
  m_pos(0,0,3), m_target(0,0,-1), m_right(1,0,0), m_up(0,1,0),
  m_angles(0,0,0), m_view(1.0f)
{

}

CCamera::CCamera(glm::vec3 pos, glm::vec3 target, glm::vec3 up) :
  m_pos(pos), m_target(target), m_up(up)
{
}

CCamera::~CCamera()
{
}

void CCamera::update(float deltatime)
{
}

void CCamera::move(glm::vec3 pos)
{
  m_pos = m_pos + pos;
}

void CCamera::moveForward(float speed)
{
  move(m_target*(speed));
}

void CCamera::moveLeft(float speed)
{
  move(glm::normalize(m_right)*(-speed));
}

void CCamera::moveRight(float speed)
{
  move(glm::normalize(m_right)*(speed));
}

void CCamera::moveBackward(float speed)
{
  move(m_target*(-speed));
}

void CCamera::moveUp(float speed)
{
  move(m_up*(speed));
}

void CCamera::moveDown(float speed)
{
  move(m_up*(-speed));
}

void CCamera::strafeLeft(float speed)
{
  move(glm::normalize(m_right)*speed);
}

void CCamera::strafeRight(float speed)
{
  move(glm::normalize(m_right)*(-speed));
}

void CCamera::rotateY(float angle)
{
  m_angles.y += angle;

  //Rotate viewdir around the up vector:
  m_target = glm::normalize(
    m_target*(float)cos(angle*PIdiv180)
    - m_right * (float)sin(angle*PIdiv180)
  );

  //now compute the new RightVector (by cross product)
  m_right = glm::cross(m_target, m_up);
}

void CCamera::rotateX(float angle)
{
  m_angles.y += angle;
  //Rotate viewdir around the up vector:
  m_up = glm::normalize(
    m_up*(float)cos(angle*PIdiv180)
    + m_target * (float)sin(angle*PIdiv180)
  );
  //now compute the new RightVector (by cross product)
  m_target = -glm::cross(m_right, m_up);
}

void CCamera::rotateZ(float angle)
{
  m_angles.y += angle;
  //Rotate viewdir around the up vector:
  m_right = glm::normalize(
    m_right*(float)cos(angle*PIdiv180)
    + m_up * (float)sin(angle*PIdiv180)
  );
  //now compute the new RightVector (by cross product)
  m_up = -glm::cross(m_target, m_right);
}

void CCamera::rotateAroundTarget(float angle)
{
  this->m_angles.y += angle;
  //m_pos.x = (float)sin(m_angles.y)*10;
  //m_pos.z = (float)cos(m_angles.y)*10;

  m_pos.x = m_pos.x*(float)cos(angle*PIdiv180)
  - m_pos.z * (float)sin(angle*PIdiv180);
  m_pos.z = m_pos.x*(float)sin(angle*PIdiv180)
  + m_pos.z * (float)cos(angle*PIdiv180);
  //m_target = { 0,0,0 };

}

glm::mat4 CCamera::getViewMatrix()
{
  return glm::lookAt(
    glm::vec3(m_pos),
    glm::vec3(m_pos + m_target),
    glm::vec3(m_up)
  );
}

glm::mat4 CCamera::getProjectionMatrix()
{
  return glm::perspective(glm::radians(m_fov), m_ratio, 0.1f, 100.0f);
}

void CCamera::reset()
{
  m_pos = {0,0,3}, 
  m_target = {-glm::normalize(m_pos - glm::vec3(0,0,0))}, 
  m_right = {1,0,0}, 
  m_up = {0,1,0}; 
}

void CCamera::setView(int x, int y, int w, int h)
{
  m_ratio = (float)w/h;
  glViewport(x,y,w,h);
}

bool CCamera::OnInputEvent(sf::Event & event)
{
  return false;

}
// >>>>>>> 4ee289218448351af2f3976559c841116c6211e6
