#pragma once

#include <BlackBox/IEngine.hpp>
#include <BlackBox/IRender.hpp>
#include <BlackBox/IWindow.hpp>
#include <BlackBox/InputHandler.hpp>

class CEngine : public IEngine, IInputEventListener
{
private:
  IShaderManager *m_pShaderManager;
  IRender *m_pIRender;
  IInputHandler *m_pIInputHandler;
  IWindow *m_Window;
  IGame *m_Game;

  bool m_running = true;
  // IEngine interface
public:
  virtual bool Init() override;
  virtual void Start() override;
  virtual void Release() override;
  virtual void Update() override;

  virtual IShaderManager * getShaderManager() override;
  virtual IRender * getIRender() override;
  virtual IInputHandler *getIInputHandler() override;

  // IInputEventListener interface
public:
  virtual bool OnInputEvent(sf::Event &event) override;
};
