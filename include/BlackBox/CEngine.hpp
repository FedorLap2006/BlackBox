#pragma once

#include <BlackBox/IEngine.hpp>

class CEngine : public IEngine
{
public:
  ILog *m_pLog;
  // ������������ ����� ISystem
  virtual void Init() override;
  virtual void Start() override;
  virtual void Release() override;
  virtual IShaderManager * getShaderManager() override;
  virtual IRender * getIRender() override;

  // ������������ ����� IEngine
  virtual ILog* getILog() override;
};
