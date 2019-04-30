#include <BlackBox/CGame.hpp>
#include <BlackBox/GameObject.hpp>
#include <BlackBox/CWindow.hpp>
#include <BlackBox/Triangle.hpp>
#include <BlackBox/Texture.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <glm/ext/matrix_transform.hpp>
#include <ctime>

#include <sstream>

using namespace std;

IGame *p_gIGame;

//////////////////////////////////////////////////////////////////////
// Pointer to Global ISystem.
static IEngine* gISystem = nullptr;
IEngine* GetIEngine()
{
  return gISystem;
}

CGame::CGame(std::string title) :
  m_World(new World()),m_Title(title)
{
  srand(time(nullptr));
  m_deltaTime = 0.0f;
  m_lastTime = 0.0f;
  m_PlayList.setRootPath("res/music/");
  m_PlayList.addTrack("background.ogg");
  m_PlayList.addTrack("japan.ogg");
}

CGame::~CGame()
{
  delete m_World;
}

bool CGame::init(IEngine *pSystem)  {
  m_pSystem = pSystem;
  m_pRender = pSystem->getIRender();
  p_gIGame = reinterpret_cast<IGame*>(this);
  m_Gui = new GUI(this);
  if (m_Gui == nullptr)
    return false;
  m_inputHandler = m_pSystem->getIInputHandler();
  m_inputHandler->keepMouseInCenter(true);
  if (!init_opbject()) {
    cout << "Failed init objects" << endl;
    return false;
  }
  cout << "Objects inited" << endl;
  glm::vec3 player_pos = {0,0,0};//m_World->operator[]("MyPlayer")->m_transform.position;
  glm::vec3 pos = {0,0,3};//glm::vec3(player_pos.x, player_pos.y + 15, player_pos.z);
  // create an camera looking at the light
  m_camera1 = new CCamera(
    pos,
    player_pos,
    glm::vec3(0,1,0)
  );
	camControl = new CameraController(m_camera1);
  m_camera1->setView(0,0,m_pRender->GetWidth(),m_pRender->GetHeight());
  m_camera2 = new CCamera();
  m_player->attachCamera(m_camera1);
  m_inputHandler->PushEventListener(m_camera1);
  m_inputHandler->PushEventListener(reinterpret_cast<CGame*>(this));
  //m_inputHandler->PushEventListener(m_player);
  m_World->setCamera(m_camera1);
  m_active_camera = m_camera1;
  //m_World->setCamera(camera2);

  return true;
}

bool CGame::update() {
  sf::Time deltaTime = deltaClock.restart();

  m_deltaTime = deltaTime.asSeconds();
  input();
  m_pRender->Update();
  if (!m_isPaused)
  {
    gotoGame();
    m_World->update(m_deltaTime);
  }
  else gotoMenu();

  setRenderState();
  m_pRender->BeginFrame();
  render();
  if (m_isPaused)
    m_Gui->Draw();
  m_pRender->EndFrame();

  return m_running;
}

bool CGame::run() {
	cout << "Game started" << endl;
  deltaClock.restart();
  m_PlayList.setVolume(10.f);
  m_PlayList.play();
  m_isMusicPlaying = true;
	gotoGame();
  return true;
}

void CGame::release()
{
  cout << "Game released" << endl;
  delete this;
}

void CGame::input()
{
  ICommand *cmd;
  //std::vector<ICommand*> qcmd;  
  while ((cmd = m_inputHandler->handleInput()) != nullptr)
    ;//cmd->execute();
}

bool CGame::init_object() {
  Texture *text_container = new Texture("container.jpg");
  Texture *plane_texture = new Texture("check.jpg");
  Texture *player_texture = new Texture("pengium.png");
  Object *obj;
  glm::vec3 light_pos(4,4,-4);
  Object *cube = Primitive::create(Primitive::CUBE, "vertex.glsl", "fragment.glsl");
  Object *BB = Primitive::create(Primitive::CUBE, "vertex.glsl", "fragment.glsl");
  Object *plane = Primitive::create(Primitive::PLANE, "vertex.glsl", "fragment.glsl");
  m_player = new CPlayer();
  CShaderProgram *shader = new CShaderProgram("res/" "vertex.glsl", "res/""fragment.glsl");
  Object *light =  Primitive::create(Primitive::CUBE,"vertex.glsl", "basecolor.frag");
  light->move(light_pos);
  light->scale(glm::vec3(0.3f));
  plane->moveTo(glm::vec3(0,0,0));
  plane->scale(glm::vec3(50,50,50));
  plane->setTexture(plane_texture);
  plane->move(glm::vec3(0,-3,0));
  m_player->setShaderProgram(shader);
  m_player->scale({10,10,10});
  m_player->setTexture(player_texture);

  BB->scale(glm::vec3(70,70,70));
  cube->scale(glm::vec3(2));
  cube->move(glm::vec3(3,1, 3));
  cube->setTexture(text_container);
  //cube->rotate(10, glm::vec3(0,1,0));
  //m_World->add("light", light);
  //m_World->add("plane", plane);
  m_World->add("MyCube", cube);
  //m_World->add("MyPlayer", m_player);
  //m_World->add("BB", BB);
  shader->create();
  for (int i = 0; i < 0; i++)
  {
    obj = Object::load("cube.obj");
    obj->setShaderProgram(shader);
    obj->setType(OBJType::TPRIMITIVE);
    obj->moveTo({
     (glm::vec3(0,0,0))
                });
    obj->scale(glm::vec3(i*20));

    obj->setTexture(plane_texture);
    m_World->add("cube" + std::to_string(i), obj);
  }
  //m_World->add("listener", reinterpret_cast<Object*>(go));
  /*
  world.add("triangle", new Triangle(m_ShaderProgram));

	*/
  //GameObject *go = GameObject::create(Primitive::CUBE);
  //go->setTexture(text);
  //go->setShaderProgram(cube->getShaderProgram());
  //m_inputHandler->PushEventListener(go);
  m_inputHandler->PushEventListener(m_player);
  return true;
}

void CGame::setRenderState()
{
  if (isWireFrame)
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  else
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);

}

void CGame::render()
{
  m_active_camera->update(m_deltaTime);
  m_World->setCamera(m_camera1);
  m_World->draw(m_deltaTime);
}

extern "C" IGame *CreateIGame(const char *title) {
  CGame *game = new CGame(title);
  return (game);
}

bool CGame::OnInputEvent(sf::Event &event)
{
  switch (event.type)
    {
    case sf::Event::KeyPressed:
    if (event.key.control) {
      switch (event.key.code) {
      case sf::Keyboard::Right:
        m_PlayList.next();
        return true;
      }
      switch (event.key.code) {
      case sf::Keyboard::Left:
        m_PlayList.prev();
        return true;
      }
      switch (event.key.code) {
      case sf::Keyboard::Up:
        m_PlayList.setVolume(m_PlayList.getVolume() + 2.f);
        return true;
      }
      switch (event.key.code) {
      case sf::Keyboard::Down:
        m_PlayList.setVolume(m_PlayList.getVolume() - 2.f);
        return true;
      }
    }
    else {
      switch(event.key.code)
      {
      case sf::Keyboard::P:
        isWireFrame = !isWireFrame;
        return true;
      case sf::Keyboard::Num9:
        m_active_camera = m_camera1;
        return true;
      case sf::Keyboard::Num0:
        m_active_camera = m_camera2;
        return true;
      case sf::Keyboard::Space:
        if (!m_isMusicPlaying){
          m_PlayList.play();
        }
        else {
          m_PlayList.pause();
        }
        m_isMusicPlaying = !m_isMusicPlaying;
        return true;
      case sf::Keyboard::Escape:
        //m_isPaused = !m_isPaused;
        m_running = false;
        return true;
      }
    }
  }
  return false;
}

IInputHandler *CGame::getInputHandler()
{
  return m_inputHandler;
}

void CGame::gotoGame()
{
	if (!m_InGame)
	{
		m_InGame = true;
    //reinterpret_cast<sf::RenderWindow*>(m_Window->getHandle())->setMouseCursorVisible(false);
    m_inputHandler->keepMouseInCenter(true);
  }
}

void CGame::gotoMenu()
{
	if (m_InGame)
	{
		m_InGame = false;
    //reinterpret_cast<sf::RenderWindow*>(m_Window->getHandle())->setMouseCursorVisible(true);
    m_inputHandler->keepMouseInCenter(false);
  }
}
