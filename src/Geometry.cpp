#include <BlackBox/IGeometry.hpp>
#include <BlackBox/VertexArrayObject.hpp>

Mesh::Mesh(CVertexBuffer *verts, CIndexBuffer *indxs)

{
  m_VAO = new CVertexArrayObject(*verts, *indxs);
}

void Mesh::draw()
{
  m_VAO->draw();
}
