#include <BlackBox/Renderer/ReflectShader.hpp>
#if 0
ReflectShader::ReflectShader() : m_Engine(GetISystem()), CBaseShaderProgram(CShader::load("res/shaders/reflect.vs", CShader::E_VERTEX), CShader::load("res/shaders/reflect.frag", CShader::E_FRAGMENT))
{
}

ReflectShader::~ReflectShader()
{
}

void ReflectShader::setup()
{
  glCheck(glActiveTexture(GL_TEXTURE0));
  glCheck(glBindTexture(GL_TEXTURE_2D, 0));
  glCheck(glActiveTexture(GL_TEXTURE0));
  glCheck(glBindTexture(GL_TEXTURE_CUBE_MAP, Pipeline::instance()->skyBox->id));
  Uniform(0, "skybox");
}
#endif