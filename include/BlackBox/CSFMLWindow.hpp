#pragma once
#include <BlackBox/IWindow.hpp>
#include <BlackBox/InputHandler.hpp>
#include <BlackBox/Opengl.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <glm/glm.hpp>
#include <imgui-SFML.h>

class CSFMLWindow :
  public IWindow
{
  static constexpr int DEFAULT_WIDTH = 1024;
  static constexpr int DEFAULT_HEIGHT = 768;
  static constexpr char *DEFAULT_TITLE = "SFML Window";

  sf::RenderWindow* m_window;
  std::string m_Title;
  glm::vec4 m_BackColor = { 0.5f, 0.5f, 0.5f, 1.0f };
  sf::Clock deltaClock;

  bool m_bClose;
  int m_Height;
  int m_Width;
  int m_flags = 0;
public:
	enum FLAGS
	{
		DRAW_GUI
	};
  CSFMLWindow(std::string = DEFAULT_TITLE, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT);
  ~CSFMLWindow();
  virtual bool init(unsigned int width, unsigned int height, unsigned int cbpp, unsigned int zbpp, unsigned int sbits, bool fullscreen) override;
  virtual void update() override;
  virtual void clear() override;
  virtual bool closed() override;
  virtual void swap() override;
  virtual void setTitle(const char *) override;
  virtual void show(bool show) override;

  // IWindow interface
public:
  virtual void *getHandle() override;
  virtual int getWidth() override;
  virtual int getHeight() override;
	virtual void setFlags(int flags) override;
private:
  void glInit();


  // IWindow interface
public:
  virtual void showCursor(bool show) override;
};

