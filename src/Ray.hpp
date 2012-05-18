/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: Ray.hpp Wed Feb  1 15:05:17 2012 wujun $
 * 
 * For efficient, this class is intended to be POD type. 
 * I also let ray object to recode the raytracer status in it.
 * Reduce the parameter needed for hit and shader functions.
 * Because these functions are called most frequently .
 *
 * Finnally, it may be helpful to seperate ray and trace state.
 * 
 */
#ifndef _RAY_H_
#define _RAY_H_
#include "common.hpp"
#include "Object3D.hpp"
class Object3D;
struct Ray
{
  friend class Camera;
public:
  Vec3f origin;
  Vec3f direction;
  float distance;      /* these field are most used, */
  Object3D* hitObject; /* make then on the same 64 byte cache line*/
  Vec3f currView;
  Vec3f currViewY;
  void cleanUp(){hitObject=NULL;distance=INFINITY;}
};


#endif /* _RAY_H_ */
