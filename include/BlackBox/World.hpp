#pragma once
#include <BlackBox/CCamera.hpp>
#include <BlackBox/Object.hpp>
#include <BlackBox/CVertexBuffer.hpp>
#include <BlackBox/Light.hpp>

#include <map>
#include <string>

using std::string;

class World {
private:
  std::map<string,Object*> m_Objs;
  std::map<string, Object*> m_Cams;
<<<<<<< HEAD:include/World.hpp
  ICamera *m_Camera;
=======
  CCamera *m_Camera;
  Light *m_Light;
>>>>>>> 26042aa6c1aad47c88986e1fd98b7ff6d350dd5f:include/BlackBox/World.hpp
public:
  World();
  ~World();
  void draw(float dt);

<<<<<<< HEAD:include/World.hpp
  void setCamera(ICamera *camera);
=======
  void setCamera(CCamera *camera);
>>>>>>> 26042aa6c1aad47c88986e1fd98b7ff6d350dd5f:include/BlackBox/World.hpp
  void add(string name, Object* o);
  inline void del(string name) { m_Objs.erase(name); }
  inline void delCam(string name) { m_Cams.erase(name); }
  void update(float deltatime);
  std::map<string,Object*> &getObjects();

  Object*& operator[] (string name) { return m_Objs[name]; }

};
