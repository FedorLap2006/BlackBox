#pragma once

#include <BlackBox/IRender.hpp>
#include <BlackBox/CVertexBuffer.hpp>
#include <BlackBox/CIndexBuffer.hpp>

struct ViewPort
{
  glm::vec2 pos;
  glm::vec2 size;
};

class CGLRender : public IRender
{
private:
  IWindow *m_Window;
  IEngine *m_Engine;
  ViewPort m_viewPort;

  glm::vec4 m_BackColor = { 0.5f, 0.5f, 0.5f, 1.0f };

public:
  CGLRender();

  // IRender interface
public:
  virtual IWindow *Init(glm::vec2 pos, glm::vec2 size, unsigned int cbpp, int zbpp, bool fullscreen) override;
  virtual bool ChangeResolution(int nNewWidth, int nNewHeight, int nNewColDepth, int nNewRefreshHZ, bool bFullScreen) override;
  virtual void BeginFrame() override;
  virtual void Render(Model *pModel) override;
  virtual void EndFrame() override;
  virtual void Update() override;
  virtual void GetViewport(int *x, int *y, int *width, int *height) override;
  virtual void SetViewport(int x, int y, int width, int height) override;
  virtual void DrawTriStrip(CVertexBuffer *src, int vert_num) override;
  virtual CVertexBuffer *CreateBuffer(int vertexcount, int vertexformat, const char *szSource, bool bDynamic) override;
  virtual void ReleaseBuffer(CVertexBuffer *bufptr) override;
  virtual void DrawBuffer(CVertexBuffer *src, CIndexBuffer *indicies, int numindices, int offsindex, int prmode, int vert_start, int vert_stop, CMatInfo *mi) override;
  virtual void UpdateBuffer(CVertexBuffer *dest, const void *src, int vertexcount, bool bUnLock, int nOffs, int Type) override;
  virtual void CreateIndexBuffer(CIndexBuffer *dest, const void *src, int indexcount) override;
  virtual void UpdateIndexBuffer(CIndexBuffer *dest, const void *src, int indexcount, bool bUnLock) override;
  virtual void ReleaseIndexBuffer(CIndexBuffer *dest) override;
  virtual void SetCamera(const CCamera &cam) override;
  virtual const CCamera &GetCamera() override;
  virtual void ChangeViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;
  virtual void WriteXY(CFont *currfont, int x, int y, float xscale, float yscale, float r, float g, float b, float a, const char *message, ...) override;
  virtual void Draw2dText(float posX, float posY, const char *szText, SDrawTextInfo &info) override;
  virtual void Draw2dImage(float xpos, float ypos, float w, float h, int texture_id, float s0, float t0, float s1, float t1, float angle, float r, float g, float b, float a, float z) override;
  virtual int SetPolygonMode(int mode) override;
  virtual int GetWidth() override;
  virtual int GetHeight() override;
  virtual void ScreenShot(const char *filename) override;
  virtual void ProjectToScreen(float ptx, float pty, float ptz, float *sx, float *sy, float *sz) override;
  virtual int UnProject(float sx, float sy, float sz, float *px, float *py, float *pz, const float modelMatrix[], const float projMatrix[], const int viewport[]) override;
  virtual int UnProjectFromScreen(float sx, float sy, float sz, float *px, float *py, float *pz) override;
  virtual void GetModelViewMatrix(float *mat) override;
  virtual void GetModelViewMatrix(double *mat) override;
  virtual void GetProjectionMatrix(double *mat) override;
  virtual void GetProjectionMatrix(float *mat) override;
  virtual glm::vec3 GetUnProject(const glm::vec3 &WindowCoords, const CCamera &cam) override;
  virtual void RenderToViewport(const CCamera &cam, float x, float y, float width, float height) override;
  virtual void SetClearColor(const glm::vec3 &vColor) override;
private:
  void InitGL();
};
