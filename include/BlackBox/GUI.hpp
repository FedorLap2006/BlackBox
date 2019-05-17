#pragma once
#include <BlackBox/CGame.hpp>
#include <BlackBox/InputHandler.hpp>

// Std inc
#include <vector>

struct BaseLight;

struct IGuiElement
{
  virtual void execute() = 0;
};

struct GuiElement : public IGuiElement
{
  const char* name;
  ImVec2 pos;
  ImVec2 size;
};

struct MenuItem : public GuiElement
{
  const char* short_cut;
  bool selected = false;
  bool enabled = true;

  // ������������ ����� IGuiElement
  virtual void execute() override;
};

struct Menu : public GuiElement
{
  std::vector<MenuItem*> items;

  // ������������ ����� IGuiElement
  virtual void execute() override;
};

struct MainMenu : public GuiElement
{
  std::vector<Menu*> menus;

  // ������������ ����� IGuiElement
  virtual void execute() override;
};

class GameGUI : public IInputEventListener
{
  friend class CGame;
  CGame *game;
  bool editing = false;
  //Menu
  float MainMenuHeight;
  MainMenu mainMenu;

public:
  GameGUI();
  ~GameGUI();

  void Draw();
  void objectInfo(Object *obj, std::string);
  void musiListController();
  void cameraController();
  void showLights(BaseLight* light, const char *name);

  // ������������ ����� IInputEventListener
  virtual bool OnInputEvent(sf::Event& event) override;
};
