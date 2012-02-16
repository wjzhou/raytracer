/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: Scene.hpp Mon Jan 30 22:00:09 2012 wujun $
 * 
 *
 * this is the infertace between the raytrace engine and input file parser
 */
#ifndef _SCENE_H_
#define _SCENE_H_
#include "common.hpp"
#include "math.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Object3D.hpp"
#include "Transformation.hpp"
#include <vector>

#include <boost/ptr_container/ptr_vector.hpp>
// all the object of scene belong to scene
namespace yy
{
class SceneParser;
}

class Scene
{
  friend class yy::SceneParser;
private:
  void setCamera(const Camera* ca){camera=ca;}
  void newLights(const size_t size){}
  void addLight(Light* light){}
  void setBackground(const Color& bg){background=bg;}
  void newMaterials(size_t size){materials=boost::ptr_vector<Material>(size);}
  void addMaterial(Material* material){materials.push_back(material);}
  void newGroup(size_t size);
  void endGroup(size_t size);
  void addObject3D(Object3D* object3D );
public:
  Scene();
  const Camera& getCamera(){return *camera;}
  boost::ptr_vector<Light>& getLights(){return lights;}
  Color& getBackground(){return background;}
  Material& getMaterial(int index){return materials[index];}
  boost::ptr_vector<Material>& getMaterials(){return materials;}
  Group* getTopGroup(){return topGroup;}
private:
  const Camera* camera;
  Color background;
  boost::ptr_vector<Light> lights;
  boost::ptr_vector<Material> materials;
  Group* topGroup;
  Group* currGroup;
  std::vector<Group*> groups;
};


#endif /* _SCENE_H_ */
