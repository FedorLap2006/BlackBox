#include <BlackBox/CInputHandler.hpp>
#include <iostream>

using namespace std;

CInputHandler::CInputHandler(IWindow * window) : m_Window(reinterpret_cast<sf::Window*>(window->getHandle()))
{
  Mouse.curr_pos = Mouse.curr_pos = sf::Mouse::getPosition(*m_Window);
  Mouse.x_wraped = Mouse.y_wraped = false;
}

ICommand * CInputHandler::handleInput()
{
	int offset = 5;
  sf::Event event;
  while (m_Window->pollEvent(event))
  {
    if (event.type == sf::Event::MouseMoved)
    {
      Mouse.prev_pos = Mouse.curr_pos;
      Mouse.curr_pos = sf::Vector2i(event.mouseMove.x,event.mouseMove.y);
    }
    for (const auto &listener : listeners)
    {
        if (listener->OnInputEvent(event))
          break;
    }
  }
  return nullptr;
}

void CInputHandler::PushEventListener(IInputEventListener * pListener)
{
  listeners.push_front(pListener);
}

sf::Vector2i CInputHandler::getDeltaMouse()
{
	sf::Vector2i windowCenter(m_Window->getSize() / 2u);
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_Window);
	sf::Vector2i delta = windowCenter - mousePosition;
  if (Mouse.keeped)
    sf::Mouse::setPosition(windowCenter, *m_Window);

  return delta;
}

void CInputHandler::keepMouseInCenter(bool keep)
{
  Mouse.keeped = keep;
}

void CInputHandler::PopEventListener()
{
  listeners.pop_front();
}
