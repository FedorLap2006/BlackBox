#pragma once
#include <BlackBox/Opengl.hpp>

class CVertexBuffer {
public:
  GLuint id;
  const void *m_Data;
  GLint m_Count;
public:
  CVertexBuffer(const void *data, GLint size);
  ~CVertexBuffer();

  void bind();
  void unbind();
  void draw();
};
