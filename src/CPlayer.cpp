#include "CPlayer.h"
#include "Primitives.hpp"

CPlayer::CPlayer() : GameObject(*Primitive::create(Primitive::CUBE, "vertex.glsl", "fragment.glsl"))
{
  m_type = OBJType::TPRIMITIVE;
  move({0,0,0});
}

bool CPlayer::OnInputEvent(sf::Event &event)
{
  GameObject::OnInputEvent(event);
  return true;
}

void CPlayer::draw()
{
  getShaderProgram()->setUniformValue("color", glm::vec3(0,0,0));
  Object::draw();
}
