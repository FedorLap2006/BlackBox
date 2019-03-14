#pragma once

#include <glm/fwd.hpp>


enum OBJType {
  TCAM,
  TPRIMITIVE //, // triangle, circle
  // ...
};

struct IObject
{
  virtual void move(glm::vec3 m) = 0;
  virtual void rotate(double angle, glm::vec3 m) = 0;
  virtual void draw() = 0;
  // virtual OBJType getType() = 0;
};
