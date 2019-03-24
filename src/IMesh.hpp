#pragma once

class IMesh {
public:
  virtual void draw(void** matrix) = 0;
  virtual void setVert(size_t index, double x, double y, double z) = 0;
};