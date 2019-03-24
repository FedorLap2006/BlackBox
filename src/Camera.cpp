#include "Camera.hpp"

/*


from GameDev.ru -> http://www.gamedev.ru/code/articles/FrustumCulling

bool SphereInFrustum(vec3 &pos, float &radius, vec4 *frustum_planes)
{
  bool res = true;
  // тестируем 6 плоскостей фрустума
  for (int i = 0; i < 6; i++)
  {
    // считаем расстояние от центра сферы до плоскости
    // если центр сферы находится за плоскостью и расстояние больше чем радиус сферы,
    // то объект не попадает во фрустум
    if (frustum_planes[i].x * pos.x + frustum_planes[i].y * pos.y +
        frustum_planes[i].z * pos.z + frustum_planes[i].w <= -radius)
      res = false;
      // return false; // флаг работает быстрее
  }
  return res;
  // return true;
}

*/


std::ostream& operator << (std::ostream &th, glm::mat4 m) {
  for (size_t it = 0; it < 4; it++) {
    for (size_t it2 = 0; it2 < 4; it2++) {
      th << m[it][it2] << "|";
    }
    for (size_t it2 = 0; it2 < 4; it2++) {
      th << "-";
    }
    th << "\n";
  }
  return th;
}

bool Camera::checkFrustum(Object* obj) {
  bool res = true;
  
  BoundSphere bs = obj->getBSphere();
  for (int i = 0; i < 6; i++) {
    auto fr_plane = m_Frustum[i];
    if (
          fr_plane.pos.x * bs.pos.x + 
          fr_plane.pos.y * bs.pos.y + 
          fr_plane.pos.z * bs.pos.z + 
          fr_plane.pos.x * bs.pos.x + 
          fr_plane.pos.w <= -bs.radius
       ) res = false;
  }

  return res;
}


Camera::Camera() {}
CameraFPS::CameraFPS() {}