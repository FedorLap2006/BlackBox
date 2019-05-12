#pragma once
#include <BlackBox/Primitives.hpp>
#include <BlackBox/InputHandler.hpp>
#include <BlackBox/CCamera.hpp>
#include <set>

class GameObject : public Object, public IInputEventListener
{
protected:
  const float MOVE_SPEED = 0.5f;
  CCamera *m_Camera;

  GameObject(const Object *obj);
  GameObject(Primitive::Type type);
public:
	virtual bool OnInputEvent(sf::Event &event) override;
	static GameObject *create(Primitive::Type type);

  // IObject interface
public:
  virtual void update(float deltatime) override;

  // IObject interface
public:
  //virtual glm::mat4 getTransform() override;
};
