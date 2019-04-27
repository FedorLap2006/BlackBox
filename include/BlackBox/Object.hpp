#pragma once

#include <BlackBox/IObject.hpp>
#include <BlackBox/IGeometry.hpp>
#include <BlackBox/IDrawable.hpp>
#include <BlackBox/CShader.hpp>
#include <BlackBox/Texture.hpp>
#include <BlackBox/Material.hpp>
#include <glm/glm.hpp>

struct Transform
{
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

  Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
    position(position), rotation(rotation), scale(scale){}
};

class Object : public IObject, public IDrawable {
protected:
  Mesh *m_Mesh;
  CShaderProgram *m_Shader;
  OBJType m_type;
  Material *m_material;
  Object();
  Object(const Object &obj);
  static void parse(std::string filename, std::vector<Vertex> &vs, CShaderProgram **shader);
public:
  Transform m_transform;

  static Object* load(std::string path);
  virtual void move(glm::vec3 v) override;
  virtual void moveTo(glm::vec3 v);
  virtual void rotate(float angle, glm::vec3 v) override;
  virtual void scale(glm::vec3 v) override;
  virtual void draw() override;
  virtual OBJType getType() override { return m_type; }
  virtual void setType(OBJType) override;
  virtual CShaderProgram * getShaderProgram() override;
  virtual glm::mat4 getTransform() override;

  // Унаследовано через IObject
  virtual void setShaderProgram(CShaderProgram* shader) override;

  // IObject interface
public:
  virtual void update(float deltatime) override;

  // IObject interface
public:
  virtual void setTexture(Texture *texture) override;
};
