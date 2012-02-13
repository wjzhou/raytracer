/* Wujun Zhou
 * zwj.echo@gmail.com
 * CS 566
 * Spring 2012
 *
 * $Id: Ray.hpp Wed Feb  1 15:05:17 2012 wujun $
 * 
 *
 * The ray object also recode the raytracer status in it.
 * For efficient, this class is intended to be POD type
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
  float distance;
  Object3D* hitObject;  
  Vec3f currView;
  Vec3f currViewY;
  void cleanUp(){hitObject=NULL;distance=INFINITY;}
};


#endif /* _RAY_H_ */
