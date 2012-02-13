/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: Raytracer.cpp Tue Jan 31 16:02:33 2012 wujun $
 * 
 *
 * 
 */

#include "Raytracer.hpp"
#include "math.hpp"
#include <boost/ptr_container/ptr_array.hpp>

void
Raytracer::doRaytrace()
{
  const Camera& camera=scene.getCamera();
  Group* topGroup=scene.getTopGroup();
  Ray ray;
  camera.updateRayAt(ray,0,0);
  //cout<<0<<" "<<0<<" "<<ray.origin<<" "<<ray.direction<<endl;
  int x,y;
  for (y=0;y<image.height;y++,camera.updateRayY(ray)){
    for (x=0;x<image.width;x++,camera.updateRayX(ray)){
      ray.cleanUp();
      //cout<<x<<" "<<y<<" "<<ray.origin<<" "<<ray.direction<<endl;
      topGroup->intersection(ray);
      if (ray.hitObject==NULL){ /// not hit terminal ray
         image.setColor(x,y,scene.getBackground());
      }else{
        Vec3f hitPoint=ray.origin+ray.distance*ray.direction;
        Vec3f normal=ray.hitObject->getNormal(hitPoint);
        Material& material=scene.getMaterial(ray.hitObject->getMaterialIndex());
        
        image.setDepth(x,y,ray.distance);
        image.setColor(x,y,DOT(normal,-ray.direction)*(material.diffuseColor));
        //cout<<x<<" "<<y<<"hit,distance:"<<ray.distance<<" hitpoint:"<<hitPoint<<"normal:"<<normal<<endl<<endl;
      }
    }
  }  
}
