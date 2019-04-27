#pragma once
#include <BlackBox/CEngine.hpp>
#include <BlackBox/CWindow.hpp>
#include <BlackBox/CInputHandler.hpp>
#include <BlackBox/IGame.hpp>

#include <iostream>
using namespace std;

bool CEngine::Init()
{
  m_pIRender = CreateIRender(nullptr);
  m_Window = m_pIRender->Init({0,0}, {1366,768});
  if (m_Window == nullptr )
      return false;
  m_Window->showCursor(false);
  m_pIRender->SetClearColor({0.5,0.5,0.5});
  if ((m_pIInputHandler = new CInputHandler(m_Window)) == nullptr)
    return false;
  m_Game = CreateIGame("MyGame");
  cout << "IGame created" << endl;

  if (m_Game->init(this)) {
    cout << "IGame inited" << endl;
    m_Game->run();
  }
  return true;
}

void CEngine::Start()
{
  m_Game->run();

  while(m_running)
  {
    Update();
  }
  m_Game->release();
}

void CEngine::Release()
{
}

void CEngine::Update()
{
  m_running = m_Game->update();
}

IShaderManager * CEngine::getShaderManager()
{
  return nullptr;
}

IRender * CEngine::getIRender()
{
  return m_pIRender;
}

IInputHandler *CEngine::getIInputHandler()
{
  return m_pIInputHandler;
}

bool CEngine::OnInputEvent(sf::Event &event)
{
  switch (event.type)
  {
  case sf::Event::Closed:
  {
    m_running = false;
    return true;
  }
  default:
    return false;
  }

}

SYSTEM_API IEngine * CreateIEngine(void *)
{
  IEngine *system = new CEngine();
  return system;
}
