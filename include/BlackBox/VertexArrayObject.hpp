#ifndef VERTEXARRAYOBJECT_H
#define VERTEXARRAYOBJECT_H
#include <BlackBox/Opengl.hpp>
#include <BlackBox/CVertexBuffer.hpp>
#include <BlackBox/CIndexBuffer.hpp>
#include <BlackBox/IGeometry.hpp>

#include <vector>

class CVertexArrayObject
{
private:
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;
  GLsizei m_IndexCount;
public:
  CVertexArrayObject(CVertexBuffer &vb, CIndexBuffer &ib);

  void draw();
};

#endif // VERTEXARRAYOBJECT_H
