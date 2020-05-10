﻿#include <BlackBox/Core/Platform/Platform.hpp>
#include <Game.hpp>
#include <GameObject.hpp>

#include <BlackBox/Renderer/Camera.hpp>
#include <BlackBox/Renderer/IFont.hpp>
#include <BlackBox/Renderer/IRender.hpp>
#include <BlackBox/Renderer/Material.hpp>
#include <BlackBox/Renderer/Texture.hpp>
#include <BlackBox/Renderer/ISceneManager.hpp>
#include <BlackBox/Renderer/ITechniqueManager.hpp>
#include <BlackBox/Renderer/ITechnique.hpp>
#include <BlackBox/3DEngine/I3DEngine.hpp>
#include <BlackBox/Scene/IScene.hpp>
#include <BlackBox/Input/IHardwareMouse.hpp>

#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <sstream>

#if 0
class CRender : public IQuadTreeRender {
public:
	CRender(IRenderer* pRender)
	{

	}
  void draw_plane(double ox, double oy, double size, color3 color) override {
		m_Plane->moveTo(Vec3(ox, 0, oy));
		m_Plane->scale(Vec3(size, size, size));

  }
	std::shared_ptr<Object> m_Plane;
};

class TreeRender : public ITreeVisitorCallback {
public:
  TreeRender(IQuadTreeRender *render) : render(render) {}
  // Inherited via ITreeVisitorCallback
  virtual void BeforVisit(QuadTree *qt) override {

  }
  virtual void OnLeaf(QuadTree *qt, bool is_last, int level) override {
    render->draw_plane(qt->m_x, qt->m_y, qt->m_size, qt->m_color);
  }

  IQuadTreeRender *render = nullptr;
};

class TreeObject : public Object
{
	TreeObject(TreeRender *treeRender) : m_TreeRender(std::unique_ptr<TreeRender>(treeRender)) {
	
	
	}
	virtual void draw(SRenderParams& renderParams) final
	{
		Object::draw(renderParams);
	}

	std::unique_ptr<TreeRender> m_TreeRender;
};
namespace {
#if 0
  sf::RenderWindow& getWindow()
  {
    return *static_cast<sf::RenderWindow*>(GetISystem()->GetIWindow()->getHandle());
  }
#endif
}
#endif

void CGame::PreRender()
{
  //glCheck(glViewport(0, 0, 1366, 768));
}

CGame::CGame() :
  g_scene(nullptr),
  listener(nullptr),
  m_Console(nullptr),
  m_Font(nullptr),
  m_pLog(nullptr),
  m_inputHandler(nullptr),
  m_player(nullptr),
  m_pSystem(nullptr),
  m_3DEngine(nullptr),
  m_Title("Test"),
  m_pScriptObjectGame(nullptr),
  m_pRender(nullptr),
  m_pInput(nullptr),
  m_pScriptSystem(nullptr),
  r_displayinfo(nullptr),
  r_cap_profile(nullptr),
  r_profile(nullptr),
  m_pCVarCheatMode(nullptr),

  m_currentLevelFolder("tmp")
{
#pragma warning(push)
#pragma warning(disable : 4244)
  srand(time(nullptr));
#pragma warning(push)
  m_deltaTime = 0.0f;
  m_lastTime = 0.0f;
#ifdef ENABLE_MUSIC_LIST
  m_PlayList.setRootPath("res/music/");
  m_PlayList.addTrack("background.ogg");
  m_PlayList.addTrack("japan.ogg");
#endif
}

bool CGame::Init(ISystem* pSystem, bool bDedicatedSrv, bool bInEditor, const char* szGameMod)
{
  m_pSystem /*= gISystem */ = pSystem;
  m_bDedicatedServer  = bDedicatedSrv;
  m_pRender = m_pSystem->GetIRenderer();
  m_pInput = m_pSystem->GetIInput();
  m_pScriptSystem = m_pSystem->GetIScriptSystem();
  m_pLog = m_pSystem->GetILog();
  m_Console = m_pSystem->GetIConsole();
  if (!bDedicatedSrv)
  {
    m_pInput->AddEventListener(this);
    m_pInput->AddEventListener(&m_CameraController);
  }
  m_pNetwork = m_pSystem->GetINetwork();
  m_bUpdateRet = true;
  m_HardwareMouse = m_pSystem->GetIHardwareMouse();


#if 0
  if (!m_pNetwork->Init())
    return false;

  m_pClient = m_pNetwork->CreateClient();
  if (!m_pClient || !m_pClient->Init())
    return false;

  m_pServer = m_pNetwork->CreateServer();
  if (!m_pServer)
    return false;
#endif

	InitConsoleVars();
  initCommands();
  InitScripts();
  auto init_cfg = m_Console->GetCVar("game_config");
  if (init_cfg == nullptr)
  {
    //TODO: log: game config not specified
    return false;
  }
  m_Console->ExecuteFile((std::string("res/scripts/") + init_cfg->GetString()).c_str());
  auto is_complete = m_Console->GetCVar("g_init_complete");
  if (is_complete == nullptr)
  {
    //TODO: log: error load Init.cfg
    return false;
  }

	// init key-bindings
	if(!m_bDedicatedServer)
		InitInputMap();
	if(!m_bDedicatedServer)
	{
		//m_pSystem->GetIConsole()->ShowConsole(0);
#if 0
		if (!bInEditor)
		{
			//////////////////////////////////////////////////////////////////////
			m_pUISystem = new CUISystem;

			if (m_pUISystem)
			{
				m_pUISystem->Create(this, m_pSystem, m_pScriptSystem, "Scripts/MenuScreens/UISystem.lua", 1);
			}
			else
			{
				m_pLog->Log("Failed to create UI System!");
			}
			//////////////////////////////////////////////////////////////////////
		}
		
		if (m_pUISystem)
		{
			m_bMenuOverlay = 1;
		}
#endif
	}
	else
		m_pSystem->GetIConsole()->ShowConsole(true);
	
  InitConsoleCommands();

  DevModeInit();

#if 0
  if (!loadScene()) {
    m_pLog->Log("[FAILED] Failed init objects\n");
    return false;
  }
#endif
  initPlayer();
  m_pInput->ShowCursor(false);
  m_pInput->GrabInput(true);

	if (m_pRender)
	{
		m_Font = gEnv->pRenderer->GetIFont();
		m_Font->Init("arial.ttf", 16, 18);

	}

  // other
  //TODO: FIX IT
#if 0
  mousePrev = sf::Mouse::getPosition();
  mouseDelta = sf::Vector2i(0, 0);
#endif
#if CURSOR_FIXED
  cursor.loadFromSystem(sf::Cursor::Arrow);
  m_pSystem->GetIWindow()->setCursor(reinterpret_cast<Cursor*>(&cursor));
#endif

  m_Console->ExecuteFile("res/scripts/postinit.cfg");
  if (m_Console->GetCVar("nsightDebug"))
  {
    m_Console->ExecuteString("r_displayinfo 0");
  }

  m_QuadTree = std::make_shared<QuadTree>(8, 10, 0, 0, color3(1, 0, 0));
  //m_QuadTreeRender = std::make_shared<CRender>(m_pRender);
  //TreeRender treeRender(m_QuadTreeRender.get());

  return true;
}

bool CGame::Update() {
	static const auto& render_game = m_Console->GetCVar("render_game");
  bool bRenderFrame = !m_bDedicatedServer;
  m_pSystem->Update(0, IsInPause());
  {
    // TODO: FIX IT
    m_deltaTime = m_pSystem->GetDeltaTime();
    m_time += m_deltaTime;
    fps = 1.0f / m_deltaTime;
    ExecScripts();
    m_CameraController.update(m_deltaTime);


#if 0
    auto camera = m_World->GetActiveScene()->getCurrentCamera();
    camera->ProcessKeyboard(direction, m_deltaTime);
		if (m_time_to_random >= 4.0f)
		{
			m_time_to_random = 0.0f;
			direction		 = static_cast<Movement>(std::rand() % 6);
			float xo		 = (std::rand() % 10)  - 5;
			camera->ProcessMouseMovement(xo, 0);
		}
		m_time_to_random += m_deltaTime;
#endif

    if (bRenderFrame)
    {
			SetRenderState();
      m_pSystem->RenderBegin();
			if (render_game)
			{
				if (render_game->GetIVal() != 0)
				{
					m_pSystem->Render();
				}
			}
      //PROFILER_PUSH_CPU_MARKER("DrawHud", Utils::COLOR_CYAN);
      DrawHud(fps);
      //PROFILER_POP_CPU_MARKER();
    }
  }
  //////////////////////////////////////////////////////////////////////////
  // Special update function for developers mode.
  //////////////////////////////////////////////////////////////////////////
  if (IsDevModeEnable() && false)
    DevModeUpdate();
  //////////////////////////////////////////////////////////////////////////
  while (!m_qMessages.empty())
  {
    string smsg = m_qMessages.front();
    m_qMessages.pop();
    ProcessPMessages(smsg.c_str());
  }
  //////////////////////////////////////////////////////////////////////////

  if (bRenderFrame)
    m_pSystem->RenderEnd();

  return m_bUpdateRet;
}

void CGame::ExecScripts()
{
}

void CGame::DrawHud(float fps)
{
  m_pRender->SetViewport(0, 0, m_pRender->GetWidth(), m_pRender->GetHeight());
  if (r_displayinfo->GetIVal() != 0)
  {
    DisplayInfo(fps);
  }
  if (m_Console->IsOpened())
  {
    m_Console->Draw();
  }
}

void CGame::DisplayInfo(float fps)
{
  size_t num_objects;
  num_objects = m_3DEngine->GetLoadedObjectCount();
  auto line = m_pRender->GetHeight();
  auto step = 18;

  std::string mode = m_Mode == MENU ? "MENU"
    : m_Mode == FPS ? "FPS"
    : m_Mode == FLY ? "FLY"
    : "EDIT";

  // Info
  TextRenderInfo info(m_Font, Vec4(0.5, 1.0f, 0.6f, 1.0));
  SDrawTextInfo dti = info.getDTI();
  SDrawTextInfo MenuDTI;
  MenuDTI.color[0] = 0;
  MenuDTI.color[0] = 1;
  MenuDTI.color[0] = 0;
  MenuDTI.color[0] = 1;
  MenuDTI.font = m_Font;
  

  //
  auto render = m_pSystem->GetIRenderer();

  //===========

  m_Font->SetXPos(0);
  m_Font->SetYPos(18);
  auto& text = info.text;
  auto& color = info.color;
  //auto camera = m_World->getActiveScene()->getCurrentCamera();

  //auto objPos = m_World->getActiveScene()->selectedObject()->second->m_transform.position;
  info.AddLine("FPS: " + std::to_string(fps));
  //info.AddLine("NUM OBJECTS: "			+ std::to_string(num_objects));
  info.AddLine("Current mode: " + mode);
  info.AddLine("Width = " + std::to_string(m_pRender->GetWidth()) + "Height = " + std::to_string(m_pRender->GetHeight()));
  //info.AddLine("Active scene: "			+ m_World->getActiveScene()->name);
  //info.AddLine("Selected Object: "	+ m_World->getActiveScene()->selectedObject()->first);
  //info.AddLine("  visible: "				+ std::to_string(m_World->getActiveScene()->selectedObject()->second->visible()));
  /*
  info.AddLine("  Pos: "						+
    std::to_string(objPos.x) + ", " +
    std::to_string(objPos.y) + ", " +
    std::to_string(objPos.z) + "; ");
  */
  //info.AddLine("Camera speed: " + std::to_string(camera->MovementSpeed->GetFVal()));
  //auto camPos = camera->getPosition();
  //auto camRot = camera->getRotation();
  /*
  auto pos = "Pos: " +
    std::to_string(camPos.x) + ", " +
    std::to_string(camPos.y) + ", " +
    std::to_string(camPos.z) + "; " +
    "Yaw: " +
    std::to_string(camRot.y) + "; " +
    "Pitch: " +
    std::to_string(camRot.x) + "; "
    ;
  */

  for (auto& text : info.text)
  {
    render->PrintLine(text.c_str(), dti);
  }

  //render->PrintLine("To hide depth buffer press <;>\n", dti);
  render->PrintLine((std::string("Camera width = ") + std::to_string(GET_CVAR("r_cam_w")->GetIVal()) + "\n").c_str(), dti);
  render->PrintLine((std::string("Camera height = ") + std::to_string(GET_CVAR("r_cam_h")->GetIVal()) + "\n").c_str(), dti);

  info.color = Vec4(1.0f, 0.f, 0.f, 1.0f);
  //render->PrintLine(pos.c_str(), info.getDTI());
  if (canDragViewPortWidth)
    render->PrintLine("CanDrag\n", info.getDTI());
  if (mousePressed)
    render->PrintLine("Mouse pressed\n", info.getDTI());

  if (m_Mode == MENU)
  {
	  Vec2 c;
		m_pSystem->GetIHardwareMouse()->GetHardwareMouseClientPosition(&c.x, &c.y);
		render->PrintLine(("Cursor: " + std::to_string(c.x) + std::string(", ") + std::to_string(/*m_pRender->GetHeight() - */c.y)).c_str(), info.getDTI());
		m_Font->SetYPos(m_pRender->GetHeight() / 2);
		for (size_t i = 0; i < test_text.size(); i++)
		{
			m_Font->SetXPos((m_pRender->GetWidth() - m_Font->TextWidth(test_text[i])) / 2);
			render->PrintLine(test_text[i].data(), i == m_MenuEntryIdx ? MenuDTI : info.getDTI());
		}
  }
}

bool CGame::Run(bool& bRelaunch) {
  m_pLog->Log("[OK] Game started\n");
  m_pSystem->Log("[OK] Game started\n");
  StartupServer(true, "test_server");

  m_bRelaunch=false;
  while(1) 
  {		
    if (!Update()) 
      break;
  }

		bRelaunch=m_bRelaunch;

	return true;
}

bool CGame::loadScene(std::string name) {
	GetISystem()->Log("Scene loading");
  std::string& path = name;
  if (gEnv->p3DEngine->LoadLevel(path.data(), ""))
  {
		if (!gEnv->IsDedicated())
		{

			//scene->setCamera("main", new CCamera());
      m_CameraController.m_Camera = &gEnv->pRenderer->GetCamera();
      m_CameraController.InitCVars();
      CPlayer* player = nullptr;// static_cast<CPlayer*>(scene->getObject("MyPlayer"));
			if (player != nullptr)
			{
				//player->attachCamera(scene->getCurrentCamera());
				player->setGame(this);
				this->setPlayer(player);
			}
		}
    return true;
  }

  return false;
}

void CGame::saveScene(std::string name, std::string as)
{
  // TODO: Fix it
  // Need implement custom save file format to save needed state
#if 0
  std::string& path = name;
  if (gEnv->pRenderer->GetISceneManager()->exist(path))
  {
    auto scene = gEnv->pRenderer->GetISceneManager()->getScene(path, this);
    scene->save(as.c_str());
  }
#endif
}

void CGame::SetRenderState()
{
  m_pRender->SetState(IRenderer::State::DEPTH_TEST, true);
  m_pRender->SetState(IRenderer::State::BLEND, false);
  if (culling)
  {
    m_pRender->SetState(IRenderer::State::CULL_FACE, true);
    m_pRender->SetCullMode(IRenderer::CullMode::BACK);
  }
  else
  {
    m_pRender->SetState(IRenderer::State::CULL_FACE, false);
  }
}

void CGame::setPlayer(CPlayer* player)
{
  m_player = player;
}

void CGame::setCamera(CCamera* camera)
{
  //m_active_camera = camera;
  //m_World->setCamera(camera);
}

IGAME_API IGame * CreateIGame() {
  CGame* game = new CGame();
  return (game);
}

bool CGame::OnInputEvent(const SInputEvent& event)
{
  {
    bool retflag;
    bool retval = ShouldHandleEvent(event, retflag);
    if (retflag) return retval;
  }
  bool result = false;
  if (!IsInPause())
    OnInputEventProxy(event);
  PersistentHandler(event);
  return result;
}

void CGame::PersistentHandler(const SInputEvent& event)
{
  auto useBoxFilter = m_Console->GetCVar("bf");
  auto lpx = m_Console->GetCVar("lpx");
  auto lpy = m_Console->GetCVar("lpy");
  auto lpz = m_Console->GetCVar("lpz");
  ////////////////////////
  bool keyPressed = event.deviceType == eIDT_Keyboard && event.state == event.state == eIS_Pressed;
  bool control = event.modifiers & eMM_Ctrl;
  bool shift = event.modifiers & eMM_Shift;
  bool alt = event.modifiers & eMM_Alt;
  ////////////////////////
  if (keyPressed)
  {
    if (event.keyId == eKI_Semicolon)
      openShadowMap = !openShadowMap;
    if (event.keyId >= eKI_F1 && event.keyId <= eKI_F12)
    {
      if (control)
      {
        DevMode_SavePlayerPos(event.keyId - eKI_F1, "BloomTest");
      }
      else if (shift)
      {
        DevMode_LoadPlayerPos(event.keyId - eKI_F1, "BloomTest");
      }
    }
    switch (event.keyId)
    {
    case eKI_Up:
    {
      lpy->Set(lpy->GetFVal() + 0.5f);
      break;
    }
    case eKI_Down:
    {
      lpy->Set(lpy->GetFVal() - 0.5f);
      break;
    }
    case eKI_Left:
    {
      lpx->Set(lpx->GetFVal() - 0.5f);
      break;
    }
    case eKI_Right:
    {
      lpx->Set(lpx->GetFVal() + 0.5f);
      break;
    }
    case eKI_Insert:
    {
      bool ubf = useBoxFilter->GetIVal();
      useBoxFilter->Set(!ubf);
      break;
    }
    case eKI_Pause:
    {
      m_bInPause = !m_bInPause;
      break;
    }
    default:
      break;
    }
  }
}

void CGame::gotoGame()
{
  //if (m_player != nullptr)
  {
    //m_World->GetActiveScene()->getCurrentCamera()->mode = CCamera::Mode::FPS;
    m_Mode = FPS;
    m_pInput->ShowCursor(false);
    m_pInput->GrabInput(true);
    m_Console->ShowConsole(false);
  }
}

void CGame::gotoFly()
{
  m_Mode = FLY;
}

void CGame::gotoEdit()
{
  m_Mode = EDIT;
}

void CGame::showMenu()
{
}

bool CGame::initPlayer()
{
  // TODO: rewirte it
#if 0
  if (m_player != nullptr)
  {
    delete m_player;
  }
  if ((m_player = reinterpret_cast<CPlayer*>(m_scene->getObject("MyPlayer"))) != nullptr)
  {
    m_player->attachCamera(m_World->GetActiveScene()->getCurrentCamera());
    m_player->setGame(this);
    return true;
  }
#endif
  return false;
}

bool CGame::FpsInputEvent(const SInputEvent& event)
{
  /*
  if (m_Console->IsOpened())
    return false;
  */

  ////////////////////////
  bool keyPressed = event.deviceType == eIDT_Keyboard && event.state == eIS_Pressed;
  bool control = event.modifiers & eMM_Ctrl;
  bool shift = event.modifiers & eMM_Shift;
  bool alt = event.modifiers & eMM_Alt;
  ////////////////////////
  auto camera = gEnv->pRenderer->GetCamera();
  if (keyPressed)
  {
    switch (event.keyId)
    {
      /*
      case eKI_P:
        isWireFrame = !isWireFrame;
        return true;
      */
    case eKI_Backspace:
      return true;
    case eKI_M:
      camera.mode = CCamera::Mode::FLY;
      m_Mode = Mode::FLY;
      return true;
    case eKI_Escape:
      gotoMenu();
      return true;
    case eKI_P:
      camera.MovementSpeed += 5.0f;
      return true;
    case eKI_E:
      //m_inputHandler->mouseLock(false);
      m_Mode = EDIT;
      return true;
    /*case eKI_M:
      camera->MovementSpeed->Set(camera->MovementSpeed->GetFVal() + 5.0f);
      return true;*/
    case eKI_B:
      culling = !culling;
      return true;
    case eKI_F9:
      if (shift)
        ++currPP;
      else
        --currPP;
      //m_World->GetActiveScene()->setPostProcessor(postProcessors[currPP % postProcessors.size()]);
      return true;
    case eKI_Enter:
      if (alt == true)
        gotoFullscreen();
      return true;
    }
  }
  //return m_player->OnInputEvent(event);
  return false;
}

bool CGame::FlyInputEvent(const SInputEvent& event)
{
  ////////////////////////
  bool keyPressed = event.deviceType == eIDT_Keyboard && event.state == eIS_Pressed;
  bool control = event.modifiers & eMM_Ctrl;
  bool shift = event.modifiers & eMM_Shift;
  bool alt = event.modifiers & eMM_Alt;
  ////////////////////////
  if (keyPressed)
  {
    switch (event.keyId)
    {
    case eKI_P:
      isWireFrame = !isWireFrame;
      return true;
    case eKI_Backspace:
      return true;
    case eKI_Space:
      gotoGame();
      return true;
    case eKI_Escape:
      //TODO: FIX IT
      //m_inputHandler->mouseLock(false);
      m_Mode = Mode::MENU;
      return true;
    }
  }
  return false;
  //return m_player->OnInputEvent(event);
}

bool CGame::MenuInputEvent(const SInputEvent& event)
{
  ////////////////////////
  bool keyPressed = event.deviceType == eIDT_Keyboard && event.state == eIS_Pressed;
  bool control = event.modifiers & eMM_Ctrl;
  bool shift = event.modifiers & eMM_Shift;
  bool alt = event.modifiers & eMM_Alt;
  ////////////////////////
  if (keyPressed)
  {
    switch (event.keyId)
    {
    case eKI_Escape:
      //m_inputHandler->mouseLock(false);
      //m_Mode = Mode::MENU;
      //Stop();
      return true;
    case eKI_Enter:
      gotoGame();
      return true;
    case eKI_J:
			m_MenuEntryIdx = ++m_MenuEntryIdx % test_text.size();
      return true;
    case eKI_K:
			m_MenuEntryIdx = --m_MenuEntryIdx % test_text.size();
      return true;
    default:
      return false;
    }
  }
    return false;
}

bool CGame::DefaultInputEvent(const SInputEvent& event)
{
  return false;
}

bool CGame::EditInputEvent(const SInputEvent& event)
{
#if 0
  ////////////////////////
  bool keyPressed = event.deviceType == eIDT_Keyboard && event.state == eIS_Pressed;
  bool control = event.modifiers & eMM_Ctrl;
  bool shift = event.modifiers & eMM_Shift;
  bool alt = event.modifiers & eMM_Alt;
  ////////////////////////
  if (keyPressed)
  {
    IObject* obj = m_World->GetActiveScene()->selectedObject()->second;
    switch (event.keyId)
    {
    case eKI_Escape:
      gotoMenu();
      return true;
    case eKI_I:
      obj->move(Movement::FORWARD);
      return true;
    case eKI_U:
      obj->move(Movement::BACKWARD);
      return true;
    case eKI_J:
      obj->move(Movement::DOWN);
      return true;
    case eKI_K:
      obj->move(Movement::UP);
      return true;
    case eKI_V:
      obj->setVisibility(!obj->visible());
      return true;
    case eKI_Tab:
      if (shift)
      {
        m_World->GetActiveScene()->selectPrevObject();
      }
      else
      {
        m_World->GetActiveScene()->selectNextObject();
      }
      return true;
    //default:
      //return m_player->OnInputEvent(event);
    }
  }
  else
  {
    //return m_player->OnInputEvent(event);
  }
#endif

  return false;
}

bool CGame::OnInputEventProxy(const SInputEvent& event)
{
  switch (m_Mode)
  {
  case CGame::FPS:
    //if (m_player != nullptr) return FpsInputEvent(event);
    return FpsInputEvent(event);
  case CGame::MENU:
    return MenuInputEvent(event);
  case CGame::FLY:
    return FlyInputEvent(event);
  case CGame::EDIT:
    return EditInputEvent(event);
  default:
    break;
  }
  return false;
}

bool CGame::ShouldHandleEvent(const SInputEvent& event, bool& retflag)
{
  bool keyPressed = event.deviceType == eIDT_Keyboard && event.state == eIS_Pressed;
  bool control = event.modifiers & eMM_Ctrl;
  bool shift = event.modifiers & eMM_Shift;
  bool alt = event.modifiers & eMM_Alt;
  retflag = true;

  if (keyPressed)
  {
    switch (event.keyId)
    {
    case eKI_Tilde:
      if (m_Console->IsOpened())
        m_Console->ShowConsole(false);
      else
        m_Console->ShowConsole(true);
      return true;
    }
  }

  if (m_Console->IsOpened())
    return false;
  retflag = false;
  return {};
}

void CGame::ProcessPMessages(const char* szMsg)
{
  if (stricmp(szMsg, "Quit") == 0)	// quit message
  {
		GetISystem()->Log("Quiting");
    m_bUpdateRet = false;
    return;
  }
  else
    if (stricmp(szMsg, "Relaunch") == 0)	// relaunch message
    {
      m_bRelaunch = true;
      m_bUpdateRet = false;
      return;
    }
}

bool CGame::IsInPause()
{
  return m_bInPause;
}

void CGame::Stop()
{
	GetISystem()->Log("Stopping");
  m_bUpdateRet = false;
}

void CGame::PostRender()
{
}

void CGame::gotoMenu()
{
  m_Mode = MENU;
	m_bInPause = true;
  m_pInput->ShowCursor(true);
  m_pInput->GrabInput(false);
}

void CGame::gotoFullscreen()
{
  isFullScreen = !isFullScreen;
}


bool CGame::InitScripts()
{
  m_pScriptObjectGame = new CScriptObjectGame();
  m_pScriptObjectGame->InitializeTemplate(m_pScriptSystem);

#if 0
  m_pScriptClient = new CScriptObjectClient();
  m_pScriptClient->InitializeTemplate(m_pScriptSystem);

  m_pScriptServer = new CScriptObjectServer();
  m_pScriptServer->InitializeTemplate(m_pScriptSystem);
#endif

  m_pScriptObjectGame->Init(m_pSystem->GetIScriptSystem(), this);
#if 0
  m_pScriptServer->Init(m_pSystem->GetIScriptSystem(), m_pServer);
  m_pScriptClient->Init(m_pSystem->GetIScriptSystem(), m_pClient);
#endif

  m_pScriptSystem->ExecuteFile("scripts/common.lua", true, false);

  fps = 35.f;
  m_pScriptSystem->ExecuteFile("scripts/game.lua", true, false);
  class toogle_viewport_drag : public IConsoleCommand
  {
    CGame* game;
  public:
    toogle_viewport_drag(CGame* game) : game(game) {}
    bool execute(CommandDesc& cd)
    {
      game->can_drag_vp = !game->can_drag_vp;
      return true;
    }
  };

  m_Console->AddCommand("toogle_viewport_drag", new toogle_viewport_drag(this));
#if 0
  m_Console->AddCommand(
    "enumd",
    R"(
		local formats = System:EnumDisplayFormats()
		for i=1, #formats do
			Console:PrintLine("["..i.."]".. formats[i].width .. " x " .. formats[i].height .. " x " .. formats[i].bpp)
		end
		Console:PrintLine(%2)
		Console:PrintLine(%1)
		)",
    0,
    "Enum Display formats"
  );
#endif

  m_pScriptSystem->ExecuteFile("scripts/utils.lua");

  return true;
}

bool CGame::TestScriptSystem(bool& retflag)
{
  retflag = true;
  m_playerObject = m_pScriptSystem->CreateEmptyObject();
  if (!m_pScriptSystem->GetGlobalValue("Player", m_playerObject))
  {
    delete m_playerObject;
    m_pSystem->Log("\002 ERROR: can't find player table ");
    return false;
  }
  const char* name;
  int age;
  m_playerObject->GetValue("name", name);
  m_playerObject->GetValue("age", age);
  m_Console->PrintLine("Player name: %s", name);
  m_Console->PrintLine("Player age: %d", age);


#if 0
  HSCRIPTFUNCTION psina;
  m_playerObject->GetValue("TestChanges", psina);

  m_playerObject->SetValue("name", "Psina");
  //m_pScriptSystem->BeginCall(m_playerObject, "TestChanges");
  IScriptObject* console = nullptr;
  m_pScriptSystem->BeginCall("Console", "PrintLine");
  m_pScriptSystem->PushFuncParam(m_ScriptObjectConsole->GetScriptObject());
  m_pScriptSystem->PushFuncParam("alskdjfa;lsdjf call!!!");
  m_pScriptSystem->EndCall(console);

  m_pScriptSystem->BeginCall("player", "TestChanges");
  m_pScriptSystem->PushFuncParam(m_playerObject);
  m_pScriptSystem->PushFuncParam("Test HSCRIPTFUNCTION call!!!");
  m_pScriptSystem->EndCall(console);

  m_pScriptSystem->BeginCall(m_playerObject, "TestChanges");
  m_pScriptSystem->PushFuncParam(m_playerObject);
  m_pScriptSystem->PushFuncParam("Test lkjakldfj call!!!");
  m_pScriptSystem->EndCall(console);

  HSCRIPTFUNCTION PrintLine = 0;
  console->GetValue("PrintLine", PrintLine);
  m_pScriptSystem->BeginCall(PrintLine);
  m_pScriptSystem->PushFuncParam(console);
  m_pScriptSystem->PushFuncParam("=====================Test HSCRIPTFUNCTION call!!!");
  m_pScriptSystem->EndCall();

  int n;
  m_pScriptSystem->BeginCall(console, "PrintLine");
  m_pScriptSystem->PushFuncParam(console);
  m_pScriptSystem->PushFuncParam("Call by table reference");
  m_pScriptSystem->EndCall(console);

  m_playerObject->GetValue("name", name);
  m_Console->PrintLine("Player name: %s", name);
#endif
  retflag = false;
  return {};
}

void CGame::SaveConfiguration(const char* sSystemCfg, const char* sGameCfg, const char* sProfile)
{
}

void CGame::ReloadScripts()
{
}

bool CGame::GetModuleState(EGameCapability eCap)
{
  return false;
}

void CGame::UpdateDuringLoading()
{
}

IXAreaMgr* CGame::GetAreaManager()
{
  return nullptr;
}

ITagPointManager* CGame::GetTagPointManager()
{
  return nullptr;
}

Object* CGame::OnLoad(Object* object, std::string type)
{
#if 0
  if (type == "player")
    return nullptr;// new CPlayer(object);
  else if (type == "gameobject")
    return new GameObject(object);
  else 
#endif
    return object;
}

void CGame::MainMenu()
{

}
