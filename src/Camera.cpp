#include "Camera.hpp"
#include "SuperSampling.hpp"
void
Camera::initSuperSampling()
{
  sampling=SuperSampling::getSuperSamplingByName(options.getSuperSamplingMethod(),
                                                 options.getSuperSamplingSamples(),
                                                 viewplane.dxaxis,viewplane.dyaxis);
}

/** 
 * Prepare the Orthographic Camera for generate Rays.
 * 
 * @param center the position of camera
 * @param direction  the direction of view, must a normal vector
 * @param up the direction of up
 * @param width the width of viewplane
 * @param height the height of viewplane
 * @param pixelsize size of pixelsize
 */
OrthographicCamera::
OrthographicCamera(Vec3f& center, Vec3f& direction, Vec3f& up,
                   float width, float height, float pixelsize)
  :Camera(center,direction,up)
{
  if(garg_override_pixelsize) //pixelsize command line have highest priority.
    pixelsize=garg_pixelsize;
  else if(garg_override_xres) //then is command line xres
    pixelsize=width/garg_override_xres;
  else if(pixelsize==UNDEFINEDF)
    pixelsize=garg_pixelsize; //using the default value
  garg_xres=width/garg_pixelsize;
  garg_yres=height/garg_pixelsize;
  //a copy of viewplane is not very costy, using it to simplify the code ..
  viewplane=ViewPlane(center,direction,up,width,height,pixelsize,0.0f);
  //this->direction.normalize();//the direction may not normalized. //change to new math library
  this->direction/=abs(this->direction);
  initSuperSampling();
}

inline void
OrthographicCamera::updateRayAt(Ray&ray, int x,int y) const
{
  //this function will not been called often.
  //using double here to reduce the round error may be a good idea.
  ray.currView=ray.currViewY=viewplane.leftTop+float(x)*viewplane.dxaxis+float(y)*viewplane.dyaxis;
  ray.origin=ray.currView;
  ray.direction=direction;
}

inline void
OrthographicCamera::updateRayX(Ray& ray) const
{
  ray.currView+=viewplane.dxaxis;
  ray.origin=ray.currView;
}
inline void
OrthographicCamera::updateRayY(Ray& ray) const
{
  ray.currViewY+=viewplane.dyaxis;
  ray.origin=ray.currView=ray.currViewY;
}
void
OrthographicCamera::adjust(Ray& ray,int i) const
{
  ray.origin=ray.currView+sampling->adjustPosition(i);  
}

/** 
 * Prepare the Prespective Camera for generate Rays.
 * 
 * @param center the position of camera
 * @param direction  the direction of view, must a normal vector
 * @param up the direction of up
 * @param fov field of view of horizontal
 * @param dist  distance between viewplan and camera 
 */
PerspectiveCamera::PerspectiveCamera(Vec3f& center, Vec3f& direction, Vec3f& up,
                                     float fov, float dist)
  :Camera(center,direction,up)
{
  float width=std::tan(fov*M_PI/360);//fov/2/360*2*M_PI
  float pixelsize=width/garg_xres;
  float height=pixelsize*garg_yres;
  viewplane=ViewPlane(center,direction,up,width,height,pixelsize,1.0f);
  initSuperSampling();
}

inline void
PerspectiveCamera::updateRayAt(Ray& ray, int x,int y) const
{
  //this function will not been called often.
  //using double here to reduce the round error may be a good idea.
  ray.currView=ray.currViewY=viewplane.leftTop+float(x)*viewplane.dxaxis+float(y)*viewplane.dyaxis;

  ray.origin=center;
  ray.direction=ray.currView-ray.origin;
  //ray.direction.normalize(); //change to new math library
  ray.direction/=abs(ray.direction);
}

inline void
PerspectiveCamera::updateRayX(Ray& ray) const
{
  ray.currView+=viewplane.dxaxis;
  ray.direction=ray.currView-ray.origin;
  //ray.direction.normalize(); //change to new math library
  ray.direction/=abs(ray.direction);
}
inline void
PerspectiveCamera::updateRayY(Ray& ray) const
{
  ray.currViewY+=viewplane.dyaxis;
  ray.currView=ray.currViewY;
  ray.direction=ray.currView-ray.origin;
  //ray.direction.normalize(); //change to new math library
  ray.direction/=abs(ray.direction);
}
void
PerspectiveCamera::adjust(Ray& ray, int i) const
{
  ray.direction=ray.currView+sampling->adjustPosition(i)-ray.origin;
  ray.direction/=abs(ray.direction);
}
