/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: Camera.hpp Fri Feb 10 00:52:49 2012 wujun $
 * 
 *
 * define the Camera, Orthographic and PerspectiveCamera
 */
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "common.hpp"
#include "Ray.hpp"
#include "ViewPlane.hpp"
#include "SuperSampling.hpp"
class Camera
{
  friend class Scene;
public:
  Camera(Vec3f center,Vec3f direction,Vec3f up)
    :center(center),direction(direction),up(up){}
  virtual ~Camera(){};
  virtual void updateRayAt(Ray& ray, int x,int y)const=0;
  virtual void updateRayX(Ray&)const=0;
  virtual void updateRayY(Ray&)const=0;
  virtual void initSuperSampling();
  virtual void adjust(Ray& ray, int i)const=0;
protected:
  Vec3f center;
  Vec3f direction;
  Vec3f up;
  ViewPlane viewplane;
  SuperSampling* sampling;
};

class OrthographicCamera : public Camera
{
public:
  OrthographicCamera(Vec3f& center, Vec3f& direction, Vec3f& up,
                     float width, float height, float pixelsize);
  virtual ~OrthographicCamera(){};
  virtual void updateRayAt(Ray& ray,int x,int y)const;
  virtual void updateRayX(Ray&)const;
  virtual void updateRayY(Ray&)const;
  virtual void adjust(Ray& ray, int i)const;
};

class PerspectiveCamera : public Camera
{
public:
  PerspectiveCamera(Vec3f& center, Vec3f& direction, Vec3f& up,
                    float fov, float dist=1.0);
  virtual ~PerspectiveCamera(){};
  virtual void updateRayAt(Ray& ray,int x,int y)const;
  virtual void updateRayX(Ray&)const;
  virtual void updateRayY(Ray&)const;
  virtual void adjust(Ray& ray, int i)const;
};


#endif /* _CAMERA_H_ */
