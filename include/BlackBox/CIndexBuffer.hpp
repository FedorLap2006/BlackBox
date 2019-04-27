#pragma once
#include <BlackBox/Opengl.hpp>

class CIndexBuffer
{
public:
  GLuint id;
  const void *m_Data;
  GLint m_Count;
public:
  CIndexBuffer(const void *data, GLint size);
  ~CIndexBuffer();
};
