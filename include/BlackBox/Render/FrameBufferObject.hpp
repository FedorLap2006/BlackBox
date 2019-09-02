#pragma once
#include <BlackBox/Render/Opengl.hpp>
#include <vector>

struct ITexture;
class Texture;

class FrameBufferObject
{
public:
  enum BufferType
  {
    DEPTH_BUFFER,
    SCENE_BUFFER,
    HDR_BUFFER,
  };


  static FrameBufferObject *create(BufferType type, int width, int height, int nColors);
  void bind();
  void unbind();
  ITexture* getTexture();
private:
  FrameBufferObject(BufferType type, int width, int height, int nColors);
  void createSceneBuffer();
  void createDepthBuffer();
public:
  GLuint id;
  std::vector<GLuint> texture;
  GLuint rbo;
  int width;
  int height;
  BufferType type;
};
