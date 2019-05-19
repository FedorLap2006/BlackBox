#pragma once

#include <BlackBox/IEngine.hpp>

class CEngine : public IEngine
{
private:
  ILog *m_pLog;
  IConsole *m_pConsole;
public:
  // ������������ ����� ISystem
  virtual void Init() override;
  virtual void Start() override;
  virtual void Release() override;
  virtual IShaderManager * getShaderManager() override;
  virtual IRender * getIRender() override;

  // ������������ ����� IEngine
  virtual ILog* getILog() override;

  // ������������ ����� IEngine
  virtual IConsole* getIConsole() override;
};
