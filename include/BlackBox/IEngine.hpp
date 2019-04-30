#pragma once

#define SYSTEM_API

struct IGame;
struct IShaderManager;
struct IRender;
struct IInputHandler;

/**
 * @brief The IEngine struct
 */
struct IEngine
{
  virtual bool Init() = 0;
  virtual void Start() = 0;
  virtual void Release() = 0;
  virtual void Update() = 0;

  virtual IShaderManager *getShaderManager() = 0;
  virtual IRender *getIRender() = 0;
  virtual IInputHandler *getIInputHandler() = 0;
};

/**
 * @brief GetIEngine Get the system interface (must be defined locally in each module)
 * @return
 */
extern IEngine *GetIEngine();

// interface of the DLL
extern "C"
{
  SYSTEM_API IEngine* CreateIEngine(void *);
}
