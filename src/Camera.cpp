#include "Camera.hpp"

/*


from GameDev.ru -> http://www.gamedev.ru/code/articles/FrustumCulling

bool SphereInFrustum(vec3 &pos, float &radius, vec4 *frustum_planes)
{
  bool res = true;
  // ��������� 6 ���������� ��������
  for (int i = 0; i < 6; i++)
  {
    // ������� ���������� �� ������ ����� �� ���������
    // ���� ����� ����� ��������� �� ���������� � ���������� ������ ��� ������ �����,
    // �� ������ �� �������� �� �������
    if (frustum_planes[i].x * pos.x + frustum_planes[i].y * pos.y +
        frustum_planes[i].z * pos.z + frustum_planes[i].w <= -radius)
      res = false;
      // return false; // ���� �������� �������
  }
  return res;
  // return true;
}

*/

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