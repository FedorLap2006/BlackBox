#ifndef TEXTUREXTURE_HPP
#define TEXTUREXTURE_HPP

#include <string>
#include <memory>
#include <BlackBox/Render/Opengl.hpp>
#include <BlackBox/Render/BaseTexture.hpp>
#include <SFML/Graphics.hpp>
#ifdef NVTT
#include <nvtt/nvtt.h>
#endif

class Texture : public BaseTexture
{
public:
  Texture();
  Texture(std::string name);
#ifdef NVTT
	void GetMipMapLevel(int level, nvtt::Surface &surface);
	void SaveMipMaps();
#endif
  virtual void setType(const char* TextureType) override;
  virtual std::string typeToStr() override;

	// ������������ ����� BaseTexture
	virtual bool load(const char* name) override;
};

#endif // TEXTUREXTURE_HPP
