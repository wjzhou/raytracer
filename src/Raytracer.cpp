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
  const Camera& camera=scenep->getCamera();
  Group* topGroup=scenep->getTopGroup();
  //cout<<0<<" "<<0<<" "<<ray.origin<<" "<<ray.direction<<endl;
  int x,y;
  int height=imagep->height;
  int width=imagep->width;
  
  /*using default shared, because on mac os x the const Camera will be 
   * predetermined as shard and have error 
   * 'camera' is predetermined 'shared' for 'shared'
   * while on linux it must been marked as shared*/
#ifdef _OPENMP
  #pragma omp parallel for schedule(dynamic) default(shared)              \
    private(x,y) shared(height,width,topGroup)
#endif
  /*int nthreads, tid;
    #pragma omp parallel private(nthreads, tid)
  tid = omp_get_thread_num();
  nthreads = omp_get_num_threads();*/

  for (y=0;y<height;y++){
    Ray ray;
    camera.updateRayAt(ray,0,y);
    for (x=0;x<width;x++){
      ray.cleanUp();
      //cout<<x<<" "<<y<<" "<<ray.origin<<" "<<ray.direction<<endl;
      topGroup->intersection(ray);
      if (ray.hitObject==NULL){ /// not hit terminal ray
        imagep->setColor(x,y,scenep->getBackground());
      }else{     
        imagep->setDepth(x,y,ray.distance);
        Color color=shaderp->doShading(ray);
#ifndef RELEASE
        if(color.x<0||color.y<0||color.z<0){
          cout<<"suspect point:px="<<x<<",py="<<y<<"color:"<<color<<endl;
          //          cout<<x<<" "<<y<<"hit,distance:"<<ray.distance<<" hitpoint:"<<hitPoint<<"normal:"<<normal<<"ray"<<ray.direction<<endl<<endl;
          color.x=color.y=color.z=1.0f; //to make the point easier to seen
        }
#endif /*RELEASE*/

        imagep->setColor(x,y,color);
      }
      camera.updateRayX(ray);
    }
  }
}
