#pragma once

struct Material
{
  Texture *texture;
  glm::vec4  ambient;
  glm::vec4  diffuse;
  glm::vec4  specular;
  glm::vec4  emission;
  float shininess;
};