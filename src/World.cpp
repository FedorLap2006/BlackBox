#include "World.hpp"


World::World()
{

}

void World::draw() {
  for (const auto &object : m_Objs) {
    object.second->rotate(0.01f/3, {0,1,0});
    object.second->getShaderProgram()->use();
    object.second->getShaderProgram()->setUniformValue("Model", object.second->getTransform());
    object.second->getShaderProgram()->setUniformValue("View", m_Camera->getView());
    object.second->getShaderProgram()->setUniformValue("Projection", m_Camera->getProj());

    object.second->draw();
  }
  // Camera ...
}

void World::setCamera(ICamera *camera)
{
  m_Camera = camera;
}

void World::add(string name, Object * o) {
  if (o->getType() == OBJType::TCAM)
    m_Cams[name] = o;
  else if (o->getType() == OBJType::TPRIMITIVE)
    m_Objs[name] = o;
}
