#pragma once

#define RENDER_API

#include <glm/glm.hpp>

struct IEngine;
struct IWindow;
struct ViewPort;
struct Model;
struct CCamera;
struct CVertexBuffer;
struct CIndexBuffer;
struct CFont;
struct SDrawTextInfo;
struct CMatInfo;

//////////////////////////////////////////////////////////////////////
#define R_SOLID_MODE		1
#define R_WIREFRAME_MODE	2


enum EBufferType
{
  eBT_Static = 0,
  eBT_Dynamic,
};


struct IRender
{
  //! Init the renderer, params are self-explanatory
  virtual IWindow *Init(glm::vec2 pos, glm::vec2 size, unsigned int cbpp = 32, int zbpp = 24, bool fullscreen = false) = 0;

  //! Changes resolution of the window/device (doen't require to reload the level
  virtual bool ChangeResolution(int nNewWidth, int nNewHeight, int nNewColDepth, int nNewRefreshHZ, bool bFullScreen) = 0;

  virtual void BeginFrame() = 0;
  virtual void Render(Model *pModel) = 0;
  virtual void EndFrame() = 0;

  //! Should be called at the end of every frame
  virtual void	Update(void)=0;

  virtual	void	GetViewport(int *x, int *y, int *width, int *height)=0;
  virtual	void	SetViewport(int x=0, int y=0, int width=0, int height=0)=0;

  //! Draw a triangle strip
  virtual void  DrawTriStrip(CVertexBuffer *src, int vert_num=4)=0;

  //! Create a vertex buffer
  virtual	CVertexBuffer	*CreateBuffer(int  vertexcount,int vertexformat, const char *szSource, bool bDynamic=false)=0;

  //! Release a vertex buffer
  virtual void	ReleaseBuffer(CVertexBuffer *bufptr)=0;

  //! Draw a vertex buffer
  virtual void	DrawBuffer(CVertexBuffer *src,CIndexBuffer *indicies,int numindices, int offsindex, int prmode,int vert_start=0,int vert_stop=0, CMatInfo *mi=NULL)=0;

    //! Update a vertex buffer
  virtual void	UpdateBuffer(CVertexBuffer *dest,const void *src,int vertexcount, bool bUnLock, int nOffs=0, int Type=0)=0;

  virtual void  CreateIndexBuffer(CIndexBuffer *dest,const void *src,int indexcount)=0;
  //! Update indicies
  virtual void  UpdateIndexBuffer(CIndexBuffer *dest,const void *src, int indexcount, bool bUnLock=true)=0;
  virtual void  ReleaseIndexBuffer(CIndexBuffer *dest)=0;


  //! Set the renderer camera
  virtual	void	SetCamera(const CCamera &cam)=0;
  //! Get the renderer camera
  virtual	const CCamera& GetCamera()=0;

  //! Chenge viewport size
  virtual void  ChangeViewport(unsigned int x,unsigned int y,unsigned int width,unsigned int height)=0;

    //! Write a message on the screen
  virtual void	WriteXY(CFont *currfont,int x,int y, float xscale,float yscale,float r,float g,float b,float a,const char *message, ...)=0;
  //! Write a message on the screen with additional flags.
  //! for flags @see
  virtual void	Draw2dText( float posX,float posY,const char *szText,SDrawTextInfo &info )=0;

  //! Draw a 2d image on the screen (Hud etc.)
  virtual void	Draw2dImage	(float xpos,float ypos,float w,float h,int texture_id,float s0=0,float t0=0,float s1=1,float t1=1,float angle=0,float r=1,float g=1,float b=1,float a=1,float z=1)=0;

  //! Set the polygon mode (wireframe, solid)
  virtual int	SetPolygonMode(int mode)=0;

  //! Get screen width
  virtual	int		GetWidth() = 0;

  //! Get screen height
  virtual	int		GetHeight() = 0;

  //! Get a screenshot and save to a file
  virtual void ScreenShot(const char *filename=NULL)=0;

  //! Project to screen
  virtual void ProjectToScreen( float ptx, float pty, float ptz,
                                float *sx, float *sy, float *sz )=0;

  //! Unproject to screen
  virtual int UnProject(float sx, float sy, float sz,
                float *px, float *py, float *pz,
                const float modelMatrix[16],
                const float projMatrix[16],
                const int    viewport[4])=0;

  //! Unproject from screen
  virtual int UnProjectFromScreen( float  sx, float  sy, float  sz,
                           float *px, float *py, float *pz)=0;

  //! for editor
  virtual void  GetModelViewMatrix(float *mat)=0;

  //! for editor
  virtual void  GetModelViewMatrix(double *mat)=0;

  //! for editor
  virtual void  GetProjectionMatrix(double *mat)=0;

  //! for editor
  virtual void  GetProjectionMatrix(float *mat)=0;

  //! for editor
  virtual glm::vec3 GetUnProject(const glm::vec3 &WindowCoords,const CCamera &cam)=0;

  virtual void RenderToViewport(const CCamera &cam, float x, float y, float width, float height)=0;

  // 3d engine set this color to fog color
  virtual void SetClearColor(const glm::vec3 & vColor)=0;


};


struct VeiwPort
{
  glm::vec2 size;
};


// interface of the DLL
extern "C"
{
  RENDER_API IRender* CreateIRender(IEngine *engine);
}
