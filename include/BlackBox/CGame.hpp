#pragma once
#include <BlackBox/CInputHandler.hpp>
#include <BlackBox/CPlayer.h>
#include <BlackBox/CShader.hpp>
#include <BlackBox/CameraController.hpp>
#include <BlackBox/GUI.hpp>
#include <BlackBox/IEngine.hpp>
#include <BlackBox/IGame.hpp>
#include <BlackBox/IRender.hpp>
#include <BlackBox/IWindow.hpp>
#include <BlackBox/MusicList.hpp>
#include <BlackBox/Triangle.hpp>
#include <BlackBox/World.hpp>
#include <BlackBox/common.h>

#include <map>
#include <memory>
#include <stack>
#include <string>
#include <vector>


using string = std::string;
class EventListener; 

class CGame : public IGame, public IInputEventListener{
private:
  class GameState;
  class EventListener;
  friend class GUI;
  class GameState;

  IEngine *m_pSystem;
  IRender *m_pRender;
  IInputHandler *m_inputHandler;
  World *m_World;
  CCamera *m_camera1, *m_camera2, *m_active_camera;
  CPlayer *m_player;
	CameraController *camControl;
  MusicList m_PlayList;
  GUI *m_Gui;
  EventListener *listener;
  sf::Clock deltaClock;
  std::string m_Title;

  bool isDrawingGui = false;
  bool m_InGame = false;
  bool m_InMenu = false;
  bool m_isPaused = false;
  bool isWireFrame = false;
  bool m_isMusicPlaying = false;
  bool m_running = true;
  float m_deltaTime;
  float m_lastTime;

  enum State
  {
    INIT,
    MENU,
    RUN,
    RELASE
  };
  std::stack<GameState*> states;

public:
  CGame(std::string title);
  ~CGame();
  // IGame interface
  bool init(IEngine *pSystem) override;
  bool update() override;
  bool run() override;
  virtual void release() override;
  void input();

  bool init_object();
  void setRenderState();
  void render();

  // IInputEventListener interface
  virtual bool OnInputEvent(sf::Event &event) override;

  // IGame interface
public:
  virtual IInputHandler *getInputHandler() override;
private:
	void gotoMenu();
	void gotoGame();


public:

};


class CGame::GameState
{
  EventListener *m_eventListener;
public:
};
