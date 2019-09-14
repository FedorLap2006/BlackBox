#pragma once

#include <BlackBox/IEngine.hpp>
#include <BlackBox/CWindow.hpp>
#include <BlackBox/IConsole.hpp>

#define SAFE_RELEASE(o) if (o) o->Release();

class CConsole;
class CRender;

class CEngine : public ISystem
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

  // ������������ ����� ISystem
  virtual ILog* getILog() override;

  // ������������ ����� ISystem
  virtual IConsole* getIConsole() override;

  // ������������ ����� ISystem
  virtual IGame* getIGame() override;

  // ������������ ����� ISystem
  virtual IGame* CreateGame(IGame* game) override;

	// ������������ ����� ISystem
	virtual IFont* getIFont() override;

	// ������������ ����� ISystem
	virtual IWindow* getIWindow() override;

	// ������������ ����� ISystem
	virtual IInputHandler* getIInputHandler() override;

	bool ConfigLoad(const char* file);
private:
	ICVar* r_window_width;
	ICVar* r_window_height;
	ICVar* r_bpp;
	ICVar* r_zbpp;
	ICVar* r_sbpp;

};
