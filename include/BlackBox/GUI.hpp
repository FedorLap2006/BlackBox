#ifndef GUI_H
#define GUI_H

#include <string>
#include <vector>
#include <dirent.h>
#include <BlackBox/InputHandler.hpp>

class Control;
class CGame;
class MainMenuBar;
class Menu;
class MenuItem;

class FileMenu;
class EditMenu;


class Control
{
protected:
  std::string m_Name;
public:
  //virtual ~Control();
  virtual bool Draw() = 0;
};

struct openFileDialog{
  DIR *Dir;
  dirent *entry;
  std::string file;
};
class GUI : public IInputEventListener
{
private:
  CGame *m_Game;
  bool show_player = true;
  bool show_camera = true;
  bool show_demo = false;
  bool Info = false;
  MainMenuBar *m_MainMenu;
  openFileDialog m_OpenFileDialog;
public:
  GUI();
  GUI(CGame *game);
  void Draw();
private:
  void ShowMenuFile();
  bool OpenFileDialog(char* cwd, std::string &file);

  // IInputEventListener interface
public:
  virtual bool OnInputEvent(sf::Event &event) override;
};

class MainMenuBar : public Control
{
  std::vector<Menu*> m_Menus;
public:
  MainMenuBar();
  bool Draw() override;
};

class Menu : public Control
{
public:

  // Control interface
public:
  //virtual ~Menu();
  virtual bool Draw() = 0;
};

class MenuItem : public Control
{
public:
  MenuItem(std::string name);
  bool Draw();

};

class FileMenu : protected Menu
{
public:
  FileMenu(std::string name);
  // Control interface
public:
  virtual bool Draw() override;
};

class EditMenu : protected Menu
{
  EditMenu(std::string name);
  // Control interface
public:
  virtual bool Draw() override;
};

#endif
