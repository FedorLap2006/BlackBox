#pragma once

#include <BlackBox/IEngine.hpp>
#include <BlackBox/CWindow.hpp>
#include <BlackBox/IConsole.hpp>

class CConsole;
class CRender;

class CEngine : public IEngine
{
private:
  ILog *m_pLog;
  CConsole *m_pConsole;
  IGame *m_pGame;
	IFont* m_pFont;
	IWindow* m_pWindow;
	IInputHandler* m_InputHandler;
	IRender* m_Render;
public:
	CEngine();
	~CEngine();
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
	virtual IInputHandler* getIInputHandler() override;

	bool ConfigLoad(const char* file);
private:
	ICVar* r_window_width;
	ICVar* r_window_height;
	ICVar* r_bpp;
	ICVar* r_zbpp;
	ICVar* r_sbpp;

};
