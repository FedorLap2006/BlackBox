#pragma once
#include <BlackBox/Renderer/IShaderManager.hpp>
#include <BlackBox/Utils/smartptr.hpp>

#include <map>
#include <string>

class ShaderManager : public IShaderManager
{
  static ShaderManager* manager;
  std::map<std::string, _smart_ptr<CShader>> cache;
  std::string root = "res/shaders/";
  //ShaderManager();
public:
  static ShaderManager* instance();
  ShaderProgramRef getProgram(const char* vShader, const char* fShader) override;
  ShaderProgramRef getProgram(const char* vShader, const char* fShader, const char* gShader) override;
  ShaderProgramRef getProgram(const char* vShader, const char* fShader, const char* gShader, const char* cShader) override;
  ShaderProgramRef getDefaultProgram() override;
  ShaderRef getShader(ShaderDesc const& desc, bool isReload) override;
  ShaderRef addShader(const ShaderDesc& desc) override;
  void removeShader(const char* name) override;
  static bool init();
private:
};