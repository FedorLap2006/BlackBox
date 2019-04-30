#include <BlackBox/CSFMLWindow.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/System/Vector2.hpp>
#include <iostream>
using namespace std;

CSFMLWindow::CSFMLWindow(std::string title, int width, int height) :
  m_Width(width), m_Height(height), m_Title(title), m_bClose(false)
{
  
}

CSFMLWindow::~CSFMLWindow()
{
  ImGui::SFML::Shutdown();
  m_window->close();
}

bool CSFMLWindow::init(unsigned int width, unsigned int height, unsigned int cbpp, unsigned int zbpp, unsigned int sbits, bool fullscreen)
{
  sf::ContextSettings settings;
  settings.depthBits = zbpp;
  settings.stencilBits = sbits;
  settings.antialiasingLevel = 4;
  settings.majorVersion = 3;
  settings.minorVersion = 3;

  sf::Uint32 style;
  // Create the main window
  if (fullscreen)
    style = sf::Style::Fullscreen;
    //mode =  sf::VideoMode::getFullscreenModes()[0];
  else {
    style = sf::Style::Default;
    //mode = sf::VideoMode::getDesktopMode();
  }
  m_window = new sf::RenderWindow(sf::VideoMode(width, height), DEFAULT_TITLE, style, settings);//, sf::Style::Fullscreen);
  m_window->setVerticalSyncEnabled(true);
  m_window->setFramerateLimit(60);
	m_window->setMouseCursorGrabbed(true);
  // Make it the active window for OpenGL calls
  m_window->setActive();

  ImGui::SFML::Init(*m_window);

  if (!OpenGLLoader())
    return false;
  glInit();

  return true;
}

void CSFMLWindow::update()
{
  //ImGui::SFML::Update(*m_window, deltaClock.restart());
}

void CSFMLWindow::clear()
{
  float depth = 1.0f;
  glClearBufferfv(GL_COLOR, 0, &m_BackColor[0]);
  glClearBufferfv(GL_DEPTH, 0, &depth);
  //glClearBufferfv(GL_DEPTH, 0 );
}

bool CSFMLWindow::closed()
{
  return m_bClose;
}

void CSFMLWindow::swap()
{

  //ImGui::SFML::Render(*m_window);
  m_window->display();
}

void CSFMLWindow::setTitle(const char *title)
{
  m_window->setTitle(title);
}

void CSFMLWindow::show(bool show)
{
  m_window->setVisible(show);
}

void *CSFMLWindow::getHandle()
{
  return m_window;
}

int CSFMLWindow::getWidth()
{
  return m_Width;
}

int CSFMLWindow::getHeight()
{
  return m_Height;
}

void CSFMLWindow::setFlags(int flags)
{
	m_flags = flags;
}

void CSFMLWindow::glInit()
{
}

void CSFMLWindow::showCursor(bool show)
{
  m_window->setMouseCursorVisible(show);
}
