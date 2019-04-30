#pragma once

#define EXPORT extern "C"

struct IWindow {
  virtual bool init(unsigned int width, unsigned int height, unsigned int cbpp = 32, unsigned int zbpp = 24, unsigned int sbits = 8, bool fullscreen = false) = 0;
  virtual void update() = 0;
  virtual void clear() = 0;
  virtual bool closed() = 0;
  virtual void swap() = 0;
  virtual void setTitle(const char *) = 0;
  virtual void show(bool show) = 0;
  virtual int getWidth() = 0;
  virtual int getHeight() = 0;
  virtual void *getHandle() = 0;
  virtual void setFlags(int flags) = 0;
  virtual void showCursor(bool show) = 0;
};

EXPORT IWindow* CreateIWindow();
