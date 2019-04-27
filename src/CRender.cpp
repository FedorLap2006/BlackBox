#include <BlackBox/CRender.hpp>
#include <BlackBox/CWindow.hpp>
#include <BlackBox/Opengl.hpp>

IRender* CreateIRender(IEngine *engine)
{
  IRender *render =  new CGLRender();
  return render;
}

CGLRender::CGLRender()
{

}

IWindow *CGLRender::Init(glm::vec2 pos, glm::vec2 size, unsigned int cbpp, int zbpp, bool fullscreen)
{
  m_Window = new CWindow("MyGame");
  m_Window->init(size.x, size.y, cbpp, zbpp, 8, false);
  InitGL();
  return  m_Window;
}

bool CGLRender::ChangeResolution(int nNewWidth, int nNewHeight, int nNewColDepth, int nNewRefreshHZ, bool bFullScreen)
{

}

void CGLRender::BeginFrame()
{
  float depth = 1.0f;
  glClearBufferfv(GL_COLOR, 0, &m_BackColor[0]);
  glClearBufferfv(GL_DEPTH, 0, &depth);
}

void CGLRender::Render(Model *pModel)
{

}

void CGLRender::EndFrame()
{
  m_Window->swap();
}

void CGLRender::Update()
{
  m_Window->update();
}

void CGLRender::GetViewport(int *x, int *y, int *width, int *height)
{

}

void CGLRender::SetViewport(int x, int y, int width, int height)
{

}

void CGLRender::DrawTriStrip(CVertexBuffer *src, int vert_num)
{

}

CVertexBuffer *CGLRender::CreateBuffer(int vertexcount, int vertexformat, const char *szSource, bool bDynamic)
{

}

void CGLRender::ReleaseBuffer(CVertexBuffer *bufptr)
{

}

void CGLRender::DrawBuffer(CVertexBuffer *src, CIndexBuffer *indicies, int numindices, int offsindex, int prmode, int vert_start, int vert_stop, CMatInfo *mi)
{

}

void CGLRender::UpdateBuffer(CVertexBuffer *dest, const void *src, int vertexcount, bool bUnLock, int nOffs, int Type)
{

}

void CGLRender::CreateIndexBuffer(CIndexBuffer *dest, const void *src, int indexcount)
{

}

void CGLRender::UpdateIndexBuffer(CIndexBuffer *dest, const void *src, int indexcount, bool bUnLock)
{

}

void CGLRender::ReleaseIndexBuffer(CIndexBuffer *dest)
{

}

void CGLRender::SetCamera(const CCamera &cam)
{

}

const CCamera &CGLRender::GetCamera()
{

}

void CGLRender::ChangeViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
  m_viewPort.pos.x = x;
  m_viewPort.pos.y = y;
  m_viewPort.size.x = width;
  m_viewPort.size.y = height;
}

void CGLRender::WriteXY(CFont *currfont, int x, int y, float xscale, float yscale, float r, float g, float b, float a, const char *message, ...)
{

}

void CGLRender::Draw2dText(float posX, float posY, const char *szText, SDrawTextInfo &info)
{

}

void CGLRender::Draw2dImage(float xpos, float ypos, float w, float h, int texture_id, float s0, float t0, float s1, float t1, float angle, float r, float g, float b, float a, float z)
{

}

int CGLRender::SetPolygonMode(int mode)
{

}

int CGLRender::GetWidth()
{
  m_Window->getWidth();
}

int CGLRender::GetHeight()
{
  m_Window->getHeight();
}

void CGLRender::ScreenShot(const char *filename)
{

}

void CGLRender::ProjectToScreen(float ptx, float pty, float ptz, float *sx, float *sy, float *sz)
{

}

int CGLRender::UnProject(float sx, float sy, float sz, float *px, float *py, float *pz, const float modelMatrix[], const float projMatrix[], const int viewport[])
{

}

int CGLRender::UnProjectFromScreen(float sx, float sy, float sz, float *px, float *py, float *pz)
{

}

void CGLRender::GetModelViewMatrix(float *mat)
{

}

void CGLRender::GetModelViewMatrix(double *mat)
{

}

void CGLRender::GetProjectionMatrix(double *mat)
{

}

void CGLRender::GetProjectionMatrix(float *mat)
{

}

glm::vec3 CGLRender::GetUnProject(const glm::vec3 &WindowCoords, const CCamera &cam)
{

}

void CGLRender::RenderToViewport(const CCamera &cam, float x, float y, float width, float height)
{

}

void CGLRender::SetClearColor(const glm::vec3 &vColor)
{
  m_BackColor = glm::vec4(vColor, 1.0);
}

void CGLRender::InitGL()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_SMOOTH);
  glEnable(GL_TEXTURE_2D);
  //glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
}
