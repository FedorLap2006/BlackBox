#pragma once
#include <BlackBox/InputHandler.hpp>
#include <BlackBox/CWindow.hpp>
#include <SFML/System.hpp>

#include <map>
#include <list>

class CInputHandler : public IInputHandler
{
  sf::Window *m_Window;
  std::list<IInputEventListener*> listeners; 
  struct
  {
    sf::Vector2i prev_pos;
    sf::Vector2i curr_pos;
		bool x_wraped;
		bool y_wraped;
    bool keeped;
  }Mouse;

public:
  CInputHandler(IWindow *window);
  virtual ICommand *handleInput() override;

  virtual void PushEventListener(IInputEventListener * pListener) override;

  // IInputHandler interface
public:
  virtual sf::Vector2i getDeltaMouse() override;
  virtual void keepMouseInCenter(bool keep) override;

  // IInputHandler interface
public:
  virtual void PopEventListener() override;
};
