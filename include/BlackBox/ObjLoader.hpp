#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <BlackBox/IGeometry.hpp>
#include <BlackBox/Opengl.hpp>

bool loadOBJ(const char * path,
  std::vector <Vertex> & out_vertices,
  std::vector<GLuint> &out_indeces
);
