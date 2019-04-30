#include <BlackBox/VertexArrayObject.hpp>
#include <BlackBox/Opengl.hpp>

CVertexArrayObject::CVertexArrayObject(CVertexBuffer &vb, CIndexBuffer &ib)
{

  m_IndexCount = ib.m_Count;
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 2. Копируем наши вершины в буфер для OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vb.m_Count, vb.m_Data, GL_STATIC_DRAW);
    // 3. Копируем наши индексы в в буфер для OpenGL
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ib.m_Count, ib.m_Data, GL_STATIC_DRAW);
    // 4. Устанавливаем указатели на вершинные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, n));
    glEnableVertexAttribArray(2);
  glBindVertexArray(0);
}

void CVertexArrayObject::draw()
{
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, static_cast<GLvoid*>(nullptr));
  glBindVertexArray(0);
}
