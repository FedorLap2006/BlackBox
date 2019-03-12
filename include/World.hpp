#pragma once


#include "Object.hpp"
#include <MatrixTranform.hpp>
#include "VertexBuffer.hpp"
#include "Camera.hpp"
#include <map>
#include <string>

using std::string;
// using std::map;

class World {
private:
  std::map<string,Object*> m_Objs;
  std::map<string, Camera*> m_Cams;
  Camera* m_CurCam;

  glm::mat4 m_ProjMatrix;
public:
  void draw() {
    for (const auto object : m_Objs) {

      if (m_CurCam->checkFrustum(object.second)) {
        object.second->draw(m_ProjMatrix * m_CurCam->getViewMatrix() * glm::mat4(1.0f));
      }

    }
  }

  void add(string name, Object* o) { 
    m_Objs[name] = o;
  }
  void add(string name, Camera* cam) {
    m_Cams[name] = cam;
  }
  void del(string name) { m_Objs.erase(name); }
  void delCam(string name) { m_Cams.erase(name); }

  Object*& operator[] (string name) { return m_Objs[name]; }

};