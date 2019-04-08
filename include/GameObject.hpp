#pragma once
#include "Primitives.hpp"
#include "InputHandler.hpp"

class GameObject : public Object, public IInputEventListener
{
private:
	const float MOVE_SPEED = 0.50f;
  Object *m_obj;

public:
	virtual bool OnInputEvent(sf::Event &event) override;
	static GameObject *create(Primitive::Type type);
};
