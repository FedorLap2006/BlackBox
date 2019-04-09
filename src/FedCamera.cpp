#include "FedCamera.hpp"
#include <iostream>

using std::cout;
using std::endl;

void CCameraFPS::move(glm::vec3 v) {
  m_Pos += v;
  fetchLook();
}


void CCameraFPS::rotate(glm::vec3 v) {
  glm::quat xrot = glm::angleAxis(v.x, glm::vec3(1.0f, 0.0f, 0.0f));
  glm::quat yrot = glm::angleAxis(v.y, glm::vec3(0.0f, 1.0f, 0.0f));
  glm::quat zrot = glm::angleAxis(v.z, glm::vec3(0.0f, 0.0f, 1.0f));


  m_Target = m_Target * xrot * yrot * zrot;
  m_Right = m_Right * xrot * yrot * zrot;
  m_Up = m_Up * xrot * yrot * zrot;


  m_View = m_View * glm::mat4_cast(xrot * yrot * zrot);

  m_Angles.x += v.x;
  m_Angles.y += v.y;
  m_Angles.z += v.z;

  // glm::quat_cast(glm::yawPitchRoll(v.x, v.y, v.z));
  // glm::mat4_cast(glm::quat(...));
  fetchLook(true);
  // calcVecs();
}

void CCameraFPS::setTarget(glm::vec3 v) {
  m_Target = v;
  fetchLook();
}


void CCameraFPS::yawRotate(float a) {
  m_Angles.yaw += a;

  //Rotate viewdir around the up vector:
  m_Target = glm::normalize(
    m_Target*(float)cos(a*PIdiv180)
    - m_Right * (float)sin(a*PIdiv180)
  );

  //now compute the new RightVector (by cross product)
  m_Right = glm::cross(m_Target, m_Up);

  fetchLook(true);
}

void CCameraFPS::pitchRotate(float a) {
  m_Angles.pitch += a;
  //Rotate viewdir around the up vector:
  m_Target = glm::normalize(
    m_Target*(float)cos(a*PIdiv180)
    + m_Right * (float)sin(a*PIdiv180)
  );
  //now compute the new RightVector (by cross product)
  m_Right = -glm::cross(m_Target, m_Up);
  fetchLook(true);
}

void CCameraFPS::yawPitch(float yaw, float pitch) {
  yawRotate(yaw);
  pitchRotate(pitch);
}

bool CCameraFPS::OnInputEvent(sf::Event &event) {
  switch (event.type)
  {
  case sf::Event::KeyPressed:
	cout << "cam key pressed" << endl;
	switch (event.key.code)
    {
    case sf::Keyboard::Up:
      move(m_Target*(SPEED));
      return true;
    case sf::Keyboard::Down:
      move(m_Target*(-SPEED));
      return true;
    case sf::Keyboard::A:
      move(m_Right*(-SPEED));
      return true;
    case sf::Keyboard::D:
      move(m_Up*(SPEED));
      return true;
    case sf::Keyboard::W:
      move(m_Up*(SPEED));
      return true;
    case sf::Keyboard::S:
      move(m_Up*(-SPEED));
      return true;
    case sf::Keyboard::Left:
      rotate({ 0,1.0f,0 });
      return true;
    case sf::Keyboard::Right:
      rotate({ 0,-1.0f,0 });
      return true;
    }
    break;
  case sf::Event::MouseLeft:
    break;
  }
  return false;
}

//////////////// \\\\\\\\\\\\\\\\\
\\\\\\\\\\\\\\\\ /////////////////




void CCameraFly::move(glm::vec3 v) {
  m_Pos += v;
  fetchLook();
}

void CCameraFly::rotate(glm::vec3 v) {
  glm::quat xrot = glm::angleAxis(v.x, glm::vec3(1.0f, 0.0f, 0.0f));
  glm::quat yrot = glm::angleAxis(v.y, glm::vec3(0.0f, 1.0f, 0.0f));
  glm::quat zrot = glm::angleAxis(v.z, glm::vec3(0.0f, 0.0f, 1.0f));


  m_Target = m_Target * xrot * yrot * zrot;
  m_Right = m_Right * xrot * yrot * zrot;
  m_Up = m_Up * xrot * yrot * zrot;


  m_View = m_View * glm::mat4_cast(xrot * yrot * zrot);

  m_Angles.x += v.x;
  m_Angles.y += v.y;
  m_Angles.z += v.z;

  // glm::quat_cast(glm::yawPitchRoll(v.x, v.y, v.z));
  // glm::mat4_cast(glm::quat(...));
  fetchLook(true);
  // calcVecs();
}

void CCameraFly::setTarget(glm::vec3 v) {
  m_Target = v;
  fetchLook();
}

void CCameraFly::yawRotate(float yawa) {
  
  m_Angles.yaw += yawa;

  //Rotate viewdir around the up vector:
  m_Target = glm::normalize(
    m_Target*(float)cos(yawa*PIdiv180)
    - m_Right * (float)sin(yawa*PIdiv180)
  );

  //now compute the new RightVector (by cross product)
  m_Right = glm::cross(m_Target, m_Up);


}
void CCameraFly::pitchRotate(float pitcha) {

  m_Angles.pitch += pitcha;
  //Rotate viewdir around the up vector:
  m_Target = glm::normalize(
    m_Target*(float)cos(pitcha*PIdiv180)
    + m_Right * (float)sin(pitcha*PIdiv180)
  );
  //now compute the new RightVector (by cross product)
  m_Right = -glm::cross(m_Target, m_Up);


  fetchLook(true);
}

void CCameraFly::rollRotate(float rolla) {

  m_Angles.roll += rolla;
  //Rotate viewdir around the up vector:
  m_Right = glm::normalize(
    m_Right*(float)cos(rolla*PIdiv180)
    + m_Up * (float)sin(rolla*PIdiv180)
  );
  //now compute the new RightVector (by cross product)
  m_Up = -glm::cross(m_Target, m_Right);

//  m_Up = glm::rotate(m_Up, m_Angles.roll, glm::normalize(m_Target));
  m_Right = glm::cross(m_Up, m_Target);

  fetchLook(true);

}

void CCameraFly::yawPitchRoll(float yaw, float pitch, float roll) {
  // pitch - right vec
  // yaw - up vec
  // roll - viewdir vec


  // YAW
  yawRotate(yaw);
  // m_Target = glm::rotate(m_Target, m_Angles.yaw, glm::normalize(m_Up));
  // m_Right = glm::cross(m_Up, m_Target);
  // PITCH
  pitchRotate(pitch);
  // m_Target = glm::rotate(m_Target, m_Angles.pitch, glm::normalize(m_Right));
  // m_Up = glm::cross(m_Target, m_Right);
  // ROLL
  rollRotate(roll);
  // m_Up = glm::rotate(m_Up, m_Angles.roll, glm::normalize(m_Target));
  // m_Right = glm::cross(m_Up, m_Target);
  // calcVecs();

  m_Direction = glm::normalize(m_Pos - m_Target);

//  fetchLook(true);


}

bool CCameraFly::OnInputEvent(sf::Event &event) {
  switch (event.type)
  {
  case sf::Event::KeyPressed:
	cout << "cam key pressed" << endl;
    switch (event.key.code)
    {
    case sf::Keyboard::Up:
      move(m_Target*(SPEED));
      return true;
    case sf::Keyboard::Down:
      move(m_Target*(-SPEED));
      return true;
    case sf::Keyboard::A:
      move(m_Right*(-SPEED));
      return true;
    case sf::Keyboard::D:
      move(m_Up*(SPEED));
      return true;
    case sf::Keyboard::W:
      move(m_Up*(SPEED));
      return true;
    case sf::Keyboard::S:
      move(m_Up*(-SPEED));
      return true;
    case sf::Keyboard::Left:
      yawRotate(1.0f);
      return true;
    case sf::Keyboard::Right:
      yawRotate(-1.0f);
      return true;
	  case sf::Keyboard::E:
	    pitchRotate(1.0f);
	    return true;
	  case sf::Keyboard::Q:
	    pitchRotate(-1.0f);
	  case sf::Keyboard::R:
      rollRotate(1.0f);
	  case sf::Keyboard::L:
      rollRotate(-1.0f);
    }
    break;
  case sf::Event::MouseLeft:
    break;
  }
  return false;
}
