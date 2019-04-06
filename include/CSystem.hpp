#pragma once

#include <ISystem.hpp>

class CSystem : public ISystem
{
  // ������������ ����� ISystem
  virtual void Init() override;
  virtual void Start() override;
  virtual void Release() override;
  virtual IShaderManager * getShaderManager() override;
  virtual IRender * getIRender() override;
};
