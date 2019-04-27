#include <BlackBox/ObjLoader.hpp>
#include <BlackBox/IGeometry.hpp>
#include <cstring>
#include <cstdio>
#include <string>


bool loadOBJ(const char * path, std::vector <Vertex> & out_vertices, std::vector<GLuint> &out_indeces)
{
  std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
  std::vector< glm::vec3 > temp_vertices;
  std::vector< glm::vec2 > temp_uvs;
  std::vector< glm::vec3 > temp_normals;
  bool has_uv = false;
  unsigned int current_face = 0;
  bool first_fase = true;

  FILE * file = fopen(path, "r");
  if (file == nullptr) {
    printf("Impossible to open the file !\n");
    return false;
  }
  while (1) {

    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
      break; // EOF = End Of File. Quit the loop.

    // else : parse lineHeader
    if (strcmp(lineHeader, "v") == 0) {
      glm::vec3 vertex;
      fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
      temp_vertices.push_back(vertex);
    }
    else if (strcmp(lineHeader, "vt") == 0) {
      has_uv = true;
      glm::vec2 uv;
      fscanf(file, "%f %f\n", &uv.x, &uv.y);
      temp_uvs.push_back(uv);
    }
    else if (strcmp(lineHeader, "vn") == 0) {
      glm::vec3 normal;
      fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
      temp_normals.push_back(normal);
    }
    else if (strcmp(lineHeader, "f") == 0) {
      if (first_fase)
      {
        out_vertices.resize(temp_vertices.size());
        first_fase = false;
      }
      std::string vertex1, vertex2, vertex3;
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      int cnt = 6;
      char *pattern[2] = {
        "%d/%d/%d %d/%d/%d %d/%d/%d\n",
        "%d//%d %d//%d %d//%d\n",
      };
      if (has_uv) cnt = 9;
      int matches;
      if (has_uv)
        matches = fscanf(file, pattern[0],
          &vertexIndex[0], &uvIndex[0], &normalIndex[0],
          &vertexIndex[1], &uvIndex[1], &normalIndex[1],
          &vertexIndex[2], &uvIndex[2], &normalIndex[2]
        );
      else
        matches = fscanf(file, pattern[1],
          &vertexIndex[0], &normalIndex[0],
          &vertexIndex[1], &normalIndex[1],
          &vertexIndex[2], &normalIndex[2]
        );

      if (matches != cnt) {
        printf("File can't be read by our simple parser : ( Try exporting with other options\n");
        return false;
      }
      vertexIndices.push_back(vertexIndex[0]);
      vertexIndices.push_back(vertexIndex[1]);
      vertexIndices.push_back(vertexIndex[2]);
      if (has_uv)
      {
        uvIndices.push_back(uvIndex[0]);
        uvIndices.push_back(uvIndex[1]);
        uvIndices.push_back(uvIndex[2]);
      }
      normalIndices.push_back(normalIndex[0]);
      normalIndices.push_back(normalIndex[1]);
      normalIndices.push_back(normalIndex[2]);

      // For each vertex of each triangle
      Vertex vertex;

      //for (unsigned int i = 0; i < vertexIndices.size(); i++) {
      for (; current_face < vertexIndices.size(); current_face++) {
        unsigned int vertexIndex = vertexIndices[current_face] - 1;
        unsigned int normalIndex = normalIndices[current_face] - 1;

        glm::vec3 pos = temp_vertices[vertexIndex];
        vertex.pos = pos;

        if (has_uv)
        {
          unsigned int uvIndex = uvIndices[current_face] - 1;
          glm::vec2 uv = temp_uvs[uvIndex];
          vertex.uv = uv;
        }

        glm::vec3 normal = temp_normals[normalIndex];
        vertex.n = normal;
        out_vertices[vertexIndex] = vertex;
        out_indeces.push_back((vertexIndex));
      }
    }
    else {
      // Probably a comment, eat up the rest of the line
      char stupidBuffer[1000];
      fgets(stupidBuffer, 1000, file);
    }
  }

  return true;
}
