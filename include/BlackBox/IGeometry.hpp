#pragma once
#include <BlackBox/common.h>
#include <cassert>
#include <glm/glm.hpp>

class CVertexBuffer;
class CIndexBuffer;
class CVertexArrayObject;

//typedef glm::vec3 Vertex;
struct Vertex
{
  glm::vec3 pos;
  glm::vec2 uv;
  glm::vec3 n;
};

struct Mesh {
protected:
  CVertexArrayObject *m_VAO;
public:
  Mesh(CVertexBuffer *verts, CIndexBuffer *indxs);

  void draw();
};

