#pragma once
#include <BlackBox/IGame.hpp>
#include <BlackBox/IEngine.hpp>
//#include <BlackBox/IWindow.hpp>
#include <BlackBox/CWindow.hpp>
#include <BlackBox/CInputHandler.hpp>
#include <BlackBox/Resources/ShaderManager.hpp>
#include <BlackBox/Triangle.hpp>
#include <BlackBox/World.hpp>
#include <BlackBox/Game/CPlayer.h>
#include <BlackBox/CameraController.hpp>
#include <BlackBox/MusicList.hpp>
#include <BlackBox/ILog.hpp>
#include <BlackBox/Render/PostProcessor.hpp>
#include <BlackBox/Render/FreeTypeFont.hpp>
#include <BlackBox/CConsole.hpp>

#include <BlackBox/common.h>


#include <map>
#include <string>
#include <vector>
#include <memory>
#include <stack>

using string = std::string;
class EventListener; 
class GameGUI;
class Scene;
class SceneManager;

class CGame : public IGame, public IInputEventListener, public IPostRenderCallback, public IPreRenderCallback
{
  class GameState;
  class EventListener;
  friend class GameGUI;
  friend class CPlayer;
private:
  IEngine *m_pSystem;
  IWindow *m_Window;
  IInputHandler *m_inputHandler;
  World *m_World;
  CCamera *m_camera1, *m_camera2, *m_active_camera;
  CPlayer *m_player = nullptr;
	CameraController *camControl;
  Scene *m_scene;
  SceneManager *m_sceneManager;
  ILog *m_Log;
  bool isWireFrame = false;
  bool isFullScreen = false;

  MusicList m_PlayList;
  bool m_isMusicPlaying = false;
	bool m_isPaused = false;
	bool m_InMenu = false;
	bool m_InGame = false;

  std::string m_Title;
  bool m_running = true;
  float m_lastTime;
  sf::Clock deltaClock;
  EventListener *listener;
	bool isDrawingGui = false;
  class GameState; 
  //GUI
  ImVec2 cp_size; //Control panel size
  GameGUI *gui;
	CShaderProgram *m_ScreenShader;
	FreeTypeFont* m_Font;
	//EDIT MODE
	//==========
	IConsole* m_Console;
	// Render states
	bool culling = true;
	glm::vec2 viewPort = glm::vec2(1366.0f,768.0f);

  //
  ShaderManager *shaderManager;
	std::vector<IPostProcessor*> postProcessors;
	int currPP = 0;
	//=======================

  enum Mode
  {
    FPS,
    MENU,
    FLY,
		EDIT
    
  }m_Mode = FPS;
  std::stack<GameState*> states;

public:
  float m_deltaTime;
public:
  CGame(std::string title);
  ~CGame() = default;
  bool init(IEngine *pSystem) override;
  bool update() override;
	void execScripts();
	void drawHud(float fps);
  bool run() override;
  void input();

  bool loadScene();
  void setRenderState();
  void render();
  void setPlayer(CPlayer *player);
  void setCamera(CCamera *camera);

  // IInputEventListener interface
public:
  virtual bool OnInputEvent(sf::Event &event) override;

  // IGame interface
public:
  virtual IInputHandler *getInputHandler() override;
  void Stop();
	void gotoMenu();
	void gotoFullscreen();
	void gotoGame();
	void gotoFly();
	void gotoEdit();
  void showMenu();
	IWindow* getWindow();
private:

  bool initPlayer();

  bool FpsInputEvent(sf::Event& event);
  bool FlyInputEvent(sf::Event& event);
  bool MenuInputEvent(sf::Event& event);
  bool DefaultInputEvent(sf::Event& event);
  bool EditInputEvent(sf::Event& event);

  // IGame interface
public:
  virtual float getDeltaTime() override;

  // ������������ ����� IPostRenderCallback
  virtual void PostRender() override;
  World *getWorld() const;

	void drawHud();
	void initCommands();

	// Inherited via IPreRenderCallback
	virtual void PreRender() override;
};



class CGame::GameState
{
  EventListener *m_eventListener;
public:
};
