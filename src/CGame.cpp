#include "CGame.hpp"
#include "CWindow.hpp"
#include <iostream>


using namespace std;

CGame::CGame(char *title) : 
  m_Title(title)
{

}

bool CGame::init(bool debug) {
#ifdef _DEBUG
  if ( debug ) _asm { int 0x3 }
#endif
  m_Window = new CWindow(m_Title); 
  if (m_Window != nullptr ) {
    if (!m_Window->init() || !m_Window->create())
      return false;
    m_ShaderProgram = new CShaderProgram("../res/vertex.glsl", "../res/fragment.glsl");
    if (m_ShaderProgram == nullptr) return false;
    else {
	  m_ShaderProgram->create();
      Triangle* t = new Triangle(m_ShaderProgram);
      t->move(glm::vec3(0.0f, 0.5f, 0.0f));
      world.add("triangle",t);
      Camera *cam = new CameraFPS();
      cam->move(glm::vec3(0.0, 0.0, 0.2));
      world.add("test-cam", cam);
      world.setCurrentCamera("test-cam");

    return true;
    }
  } 
  return false;
}

bool CGame::update() {
  while (!m_Window->closed()) {
    m_Window->clear();
    m_Window->update();
    /* Rendering code here */
    world.draw();
    m_Window->swap();
  }
	return true;
}

bool CGame::run() {
  update();
  return true;
}


IGame *CreateIGame(char *title) {
  CGame *game = new CGame(title);
  return (game);
}
