#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <map>

class CShader; 
class CShaderProgram; 

struct ShaderStatus
{
 GLchar infoLog[512]; 
 GLint m_Status;
 CShader *m_Shader;

 ShaderStatus(CShader *shader);
 bool get(int statusType);
};

struct ShaderProgramStatus
{
 GLchar infoLog[512]; 
 GLint m_Status;
 CShaderProgram *m_Program;

 ShaderProgramStatus(CShaderProgram *program);
 bool get(int statusType);
};


class CShader 
{
private:
	GLuint m_Shader;
	std::string m_Path;
	std::string m_Text;
  ShaderStatus m_Status;
  int m_Type; 
public:
  enum type : int{
    E_VERTEX = GL_VERTEX_SHADER,
    E_FRAGMENT = GL_FRAGMENT_SHADER
  };
  CShader(std::string text, CShader::type type);
  ~CShader();
  static CShader *load(std::string path, CShader::type type);
  bool create();
  bool compile();
  bool bind();
  void print();
  std::string getName();
  GLuint get();
};

class CShaderProgram {
private:
  CShader *m_Vertex;
  CShader *m_Fragment;
  GLuint m_Program;
  GLchar infoLog[512];
  ShaderProgramStatus m_Status;

  bool status();
public:
  CShaderProgram(std::string vertex, std::string fragment);
  ~CShaderProgram();

  void setVariable(std::string name,float val) {
    GLuint varID = glGetUniformLocation(m_Program, name.c_str());
    glUniform1f(varID, val);
  }

  void setVariable(std::string name, double val) {
    GLuint varID = glGetUniformLocation(m_Program, name.c_str());
    glUniform1d(varID, val);
  }

  void setVariable(std::string name,size_t size, float* val) {
    GLuint varID = glGetUniformLocation(m_Program, name.c_str());
    glUniform1fv(varID, size,val);
  }

  void setVariable(std::string name, size_t size, double* val) {
    GLuint varID = glGetUniformLocation(m_Program, name.c_str());
    glUniform1dv(varID, size, val);
  }

  void setVariable(std::string name, glm::vec2 val) {
    GLuint varID = glGetUniformLocation(m_Program, name.c_str());
    glUniform2f(varID, val.x,val.y);
  }

  void setVariable(std::string name, glm::vec3 val) {
    GLuint varID = glGetUniformLocation(m_Program, name.c_str());
    glUniform3f(varID, val.x, val.y, val.z);
  }

  void setVariable(std::string name, glm::vec4 val) {
    GLuint varID = glGetUniformLocation(m_Program, name.c_str());
    glUniform4f(varID, val.x, val.y, val.z,val.w);
  }

  void setVariable(std::string name, glm::mat2 val) {
    GLuint varID = glGetUniformLocation(m_Program, name.c_str());
    // glUniformMatrix4fv(varID, val.x, val.y, val.z, val.w);
    glUniformMatrix2fv(varID, val.length(), GL_FALSE, glm::value_ptr(val));
  }

  void setVariable(std::string name, glm::mat3 val) {
    GLuint varID = glGetUniformLocation(m_Program, name.c_str());
    // glUniformMatrix4fv(varID, val.x, val.y, val.z, val.w);
    glUniformMatrix3fv(varID, val.length(), GL_FALSE, glm::value_ptr(val));
  }

  void setVariable(std::string name, glm::mat4 val) {
    GLuint varID = glGetUniformLocation(m_Program, name.c_str());
    // glUniformMatrix4fv(varID, val.x, val.y, val.z, val.w);
    glUniformMatrix4fv(varID, val.length(), GL_FALSE, glm::value_ptr(val));
  }

  bool create();
  bool attach(CShader *shader);
  bool link();
  void use();
  GLuint get();
};
