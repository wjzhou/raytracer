/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: Scene.cpp Fri Feb 10 15:09:47 2012 wujun $
 * 
 *
 * 
 */
#include "Scene.hpp"
#include "iostream"
Scene::Scene()
{
  Object3D::scenep=this;
  topGroup=NULL;  //otherwise the topGoup may contain random values..
}
void
Scene::setDefaultLights()
{
  newLights(1);
  PointLight* pl=new PointLight(camera->center);
  Color white(1.0f,1.0f,1.0f);
  pl->setColor(&white);
  addLight(pl);
}


void
Scene::newGroup(size_t size)
{
  currGroup=new Group(size);
  if(topGroup==NULL)
    topGroup=currGroup;
  groups.push_back(currGroup);
}
void
Scene::endGroup(size_t check)
{
  if(check!=currGroup->getSize())
    std::cout<<"wrong objects in group,ignore numObject parameter."<<std::endl;
  currGroup=groups.back();
  groups.pop_back();
}
void
Scene::addObject3D(Object3D* object3D )
{
  currGroup->addObject3D(object3D);
}
