#pragma once
#include "IGame.hpp"
#include "ISystem.hpp"
#include "IWindow.hpp"
#include "CInputHandler.hpp"
#include "CShader.hpp"
#include "Triangle.hpp"
#include "World.hpp"
#include "CPlayer.h"
#include "CameraController.hpp"
#include <MusicList.hpp>

#include <common.h>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <stack>


using string = std::string;
class EventListener; 

class CGame : public IGame, public IInputEventListener{
  class GameState;
  class EventListener;
private:
  ISystem *m_pSystem;
  IWindow *m_Window;
  IInputHandler *m_inputHandler;
  World *m_World;
  CCamera *m_camera1, *m_camera2, *m_active_camera;
  CPlayer *m_player;
	CameraController *camControl;
  bool isWireFrame = false;

  MusicList m_PlayList;
  bool m_isMusicPlaying = false;
	bool m_isPaused = false;
	bool m_InMenu = false;
	bool m_InGame = false;

  std::string m_Title;
  bool m_running = true;
  float m_deltaTime;
  float m_lastTime;
  sf::Clock deltaClock;
  EventListener *listener;
	bool isDrawingGui = false;
  class GameState; 
  class GameState;
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
  ~CGame() = default;
  bool init(ISystem *pSystem);
  bool update();
  bool run();
  void input();

  bool init_opbject();
  void setRenderState();
  void render();
	void guiControls();

  // IInputEventListener interface
public:
  virtual bool OnInputEvent(sf::Event &event);

  // IGame interface
public:
  virtual IInputHandler *getInputHandler() override;
private:
	void gotoMenu();
	void gotoGame();
};


class CGame::GameState
{
  EventListener *m_eventListener;
public:
};
