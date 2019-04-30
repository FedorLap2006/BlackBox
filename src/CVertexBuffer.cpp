#include <BlackBox/CVertexBuffer.hpp>
#include <BlackBox/IGeometry.hpp>

#include <glm/glm.hpp>
#include <iostream>

using namespace std;

CVertexBuffer::CVertexBuffer(const void *data, GLint count) :
  m_Data(data), m_Count(count)
{

}

CVertexBuffer::~CVertexBuffer()
{
  glDeleteBuffers(1, &id);
}

void CVertexBuffer::bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, id);
}

void CVertexBuffer::unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
