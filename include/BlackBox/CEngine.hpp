#pragma once

#include <BlackBox/IEngine.hpp>
#include <BlackBox/CWindow.hpp>

class CEngine : public IEngine
{
private:
  ILog *m_pLog;
  IConsole *m_pConsole;
  IGame *m_pGame;
	IFont* m_pFont;
	IWindow* m_pWindow;
	IInputHandler* m_InputHandler;
public:
  // ������������ ����� ISystem
  virtual bool Init() override;
  virtual void Start() override;
  virtual void Release() override;
  virtual IShaderManager * getShaderManager() override;
  virtual IRender * getIRender() override;

  // ������������ ����� IEngine
  virtual ILog* getILog() override;

  // ������������ ����� IEngine
  virtual IConsole* getIConsole() override;

  // ������������ ����� IEngine
  virtual IGame* getIGame() override;

  // ������������ ����� IEngine
  virtual IGame* CreateGame(IGame* game) override;

	// ������������ ����� IEngine
	virtual IFont* getIFont() override;

	// ������������ ����� IEngine
	virtual IWindow* getIWindow() override;

	// ������������ ����� IEngine
	virtual IWindow* getIWindow() override;
	virtual IInputHandler* getIInputHandler() override;
};
