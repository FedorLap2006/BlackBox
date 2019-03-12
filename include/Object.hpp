#pragma once

#include <IObject.hpp>
#include <IGeometry.hpp>
#include <glm/glm.hpp>
#include <Mesh.hpp>

struct BoundSphere {
  float radius;
  glm::vec3 pos;
};

class Object : public IObject {
protected:

  CShaderProgram *m_Shader;
	glm::vec3 m_Pos;
  std::vector<Mesh> m_Meshs;
  // float m_BRadius = 0.0;
  BoundSphere m_boundS;
  // Geometry *m_Geom;
  // OBJType ty;
  glm::mat4 m_WorldMatrix; // Model Matrix

  Object(glm::vec3 pos) : m_Pos(pos) {}
  Object() : m_Pos(0) {}
public:
  float calcBRadius(float rad,std::vector<float> verts) {
    float radius = rad;
    for (int it = 0; it < verts.size() - 3; it += 3) { // removed
      if (abs(verts[it]) > radius || abs(verts[it + 1]) > radius || abs(verts[it + 2]) > radius) radius++;
    }
    return radius;
  }

  void setWorldMatrix(glm::mat4 m) { m_WorldMatrix = m; }


  BoundSphere getBSphere() { return m_boundS; }

  void addMesh(glm::vec3 pos,std::vector<float> verts) { 
    if (verts.size() <= 0 || !(verts.size() % 3)) return;
    Mesh mesh(m_Shader, verts);
    mesh.translate(pos);
    m_Meshs.push_back(mesh);

    //float radius = m_BRadius;

    //for (int it = 0; it < verts.size() - 3; it += 3) { // removed
    //  if (abs(verts[it]) > radius || abs(verts[it+1]) > radius || abs(verts[it+2]) > radius) radius++;
    //}



    m_boundS = { calcBRadius(m_boundS.radius,verts), m_Pos };
  }
	static Object* Load(string path);
  virtual void move() override;
  virtual void rotate() override;
  virtual void draw() override;
  // virtual OBJType getType() override { return ty; }
};
