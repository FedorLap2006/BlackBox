#pragma once

#include <IObject.hpp>
#include <IGeometry.hpp>
#include <glm/glm.hpp>
#include <Mesh.hpp>


class Object : public IObject {
protected:
  CShaderProgram *m_Shader;
	glm::vec3 m_Pos;
  Mesh *m_Mesh;
  // Geometry *m_Geom;
  OBJType ty;

  Object(glm::vec3 pos) : m_Pos(pos) {}
  Object() : m_Pos(0) {}
public:

	static Object* Load(string path);
  virtual void move() override;
  virtual void rotate() override;
  virtual void draw() override;
  virtual OBJType getType() override { return ty; }
};
