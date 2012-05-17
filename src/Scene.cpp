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
Scene gScene;
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
  groups.push_back(currGroup);
}
void
Scene::endGroup(size_t check)
{
  if(check!=currGroup->getSize())
    std::cout<<"wrong objects in group,ignore numObject parameter."<<std::endl;
  if(topGroup==NULL)
    topGroup=currGroup;
  else{    
    Group* newGroup=currGroup;
    groups.pop_back();
    currGroup=groups.back();
    currGroup->addObject3D(newGroup);
  }
  
}
void
Scene::addObject3D(Object3D* object3D )
{
  currGroup->addObject3D(object3D);
}
