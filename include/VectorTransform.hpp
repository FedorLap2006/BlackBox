#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>



glm::vec3 rotateVector(glm::vec3 src,glm::vec3 angle) {
  float angleX = angle.x;
  float angleY = angle.y;
  float angleZ = angle.z;

  glm::vec3 out = { 0,0,0 };

  if (angle.x > 0) {
    out.x = src.x * sin(angle.x) * 1;
  }
  if (angle.y > 0) {
    out.y = src.y * sin(angle.y) * 1;
  }
  if (angle.z > 0) {
    out.z = src.z * sin(angle.z) * 1;
  }
  return out;
}