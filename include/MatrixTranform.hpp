#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

std::vector<float> operator * (std::vector<float> vec, glm::mat4 m);
glm::vec3 operator * (glm::vec3 v, glm::mat4 m) {
  return glm::vec4(v, 1.0) * m;
}
glm::vec3 operator * (glm::mat4 m,glm::vec3 v) {
  return m * glm::vec4(v, 1.0);
}


// vector = vector * m && vector = vector / m

// vec = changeMatrix(vec,mat,vec2,'*')