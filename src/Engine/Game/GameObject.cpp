#include <BlackBox/Game/GameObject.hpp>
#include <glm/gtc/matrix_transform.hpp>

void GameObject::update(float deltatime)
{
  float speed = deltatime*MOVE_SPEED;
  float rotSpeed = deltatime*5.f;//m_rotAngle;
  /*
  for (const auto &key : m_keys)
  {
    switch (key)
    {
      ;
    }
  }
  */
  if (m_transform.position.y < 0)
    velocity.y = - velocity.y*friction;
  m_transform.position += velocity * deltatime;
}

/*
glm::mat4 GameObject::getTransform()
{
  return glm::translate(m_Camera->getModelMatrix(), glm::vec3(0, -1.0f,0));
}
*/

GameObject::GameObject(const Object *obj) : Object(obj), m_Camera(nullptr)
{
}

bool GameObject::OnInputEvent(const SInputEvent& event)
{
  return false;
}
