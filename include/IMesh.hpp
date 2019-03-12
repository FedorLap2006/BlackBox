#pragma once

#include <glm/fwd.hpp>

struct IMesh {
  virtual void draw(glm::mat4 mat) = 0;
  virtual void rotate(double angle,glm::vec3 v) = 0;
  virtual void translate(glm::vec3 v) = 0;
  virtual void scale(glm::vec3 v) = 0;
};