#pragma once

#include <BlackBox/ISystem.hpp>
#include <BlackBox/Window.hpp>
#include <BlackBox/IConsole.hpp>
#include <BlackBox/IInput.hpp>
#include <BlackBox/IScriptSystem.hpp>
#include <BlackBox/ScriptObjectConsole.hpp>
#include <BlackBox/ScriptObjectScript.hpp>
#include <BlackBox/Common/CmdLine.hpp>

class CConsole;
class CRender;

class CSystem : public ISystem, public IInputEventListener, public IConsoleVarSink
{
public:
	CSystem(SSystemInitParams& initParams);
	~CSystem();
  
	// Inherited via ISystem
  virtual bool Init() override;
  virtual void Start() override;
	virtual bool Update(int updateFlags = 0, int nPauseMode = 0) override;
	virtual void BeginFrame() override;
	virtual void EndFrame() override;
  virtual void Release() override;

  virtual IShaderManager*						GetShaderManager() override;
  virtual IRender*									GetIRender() override;
  virtual ILog*											GetILog() override;
  virtual IConsole*									GetIConsole() override;
  virtual IInput*										GetIInput() override;
  virtual IGame*										GetIGame() override;
	virtual IFont*										GetIFont() override;
	virtual IWindow*									GetIWindow() override;
#if 0
	virtual IInputHandler*						GetIInputHandler() override;
#endif
	virtual IScriptSystem*						GetIScriptSystem() override;
	virtual ISystemEventDispatcher*		GetISystemEventDispatcher() override { return m_pSystemEventDispatcher; }

  virtual IGame*						CreateGame(IGame* game) override;

	virtual void Quit() override;

	virtual void ShowMessage(const char* message, const char* caption, MessageType messageType) override;
	virtual void Log(const char* message) override;

	virtual bool OnInputEvent(const SInputEvent& event) override;
	// Inherited via IConsoleVarSink
	virtual bool OnBeforeVarChange(ICVar* pVar, const char* sNewValue) override;

	bool ConfigLoad(const char* file);

private:
	void ParseCMD();
private:
  ILog *m_pLog;
  CConsole *m_pConsole;
	IInput* m_pInput;
  IGame *m_pGame;
	IFont* m_pFont;
	IWindow* m_pWindow;
	IInputHandler* m_InputHandler;
	IRender* m_Render;
	IScriptSystem* m_pScriptSystem;
	//! system event dispatcher
	ISystemEventDispatcher* m_pSystemEventDispatcher;

	CScriptObjectConsole* m_ScriptObjectConsole;
	CScriptObjectScript* m_ScriptObjectScript;

private:
	ICVar* r_window_width;
	ICVar* r_window_height;
	ICVar* r_bpp;
	ICVar* r_zbpp;
	ICVar* r_sbpp;
	ICVar* r_fullscreen;

	SSystemInitParams& m_startupParams;
	CCmdLine* m_pCmdLine;

	// Inherited via ISystem
	virtual bool IsDevMode() override;

	// Inherited via ISystem
	virtual void Error(const char* message) override;
};
